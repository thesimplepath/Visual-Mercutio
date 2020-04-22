//
// isapi.c : Defines the entry point for the DLL application.
//
// $Id: isapi.cpp,v 1.12 2001/12/11 02:41:07 dcrowley Exp $
//
// This file implements the standard DLL entry points for an
// ISAPI module.  This is free code.  It was taken and derived
// by several examples in the Microsoft documentation.
//
// This module creates a thread pool for processing the incoming
// requests.  Each thread executes the external method
// ThreadProc() which is where we put the SOAP server dispatch
// stuff.  Each thread will have it's own dispatch object and
// should make it easier to keep things thread safe.
//
//
// This file needs to be compiled and linked with code
// which implements the ThreadProc() method.
//
// BE SURE TO INCLUDE isapi.def IN YOUR PROJECT
// Or, like me, you might spend a couple hours trying to figure
// out why the freaking DLL isn't loading....
//
#include <httpext.h>

//
// Predeclare the thread method we're going to call.
DWORD WINAPI ThreadProc(void *);

//
//  It would be cool if this was configurable through
//  a registry key or something...
//
#define numWorkerThreads 10


//
// This can be changed to anything you want...
const char *extensionDesc = "EasySoap++ ISAPI DLL";


//
// Global variable to keep track of our threads
// and our IoPort.
//
HANDLE	gWorkerThreads[numWorkerThreads];
HANDLE	gIoPort;

static const char *
HTTPReasonByStatus(int code)
{
	static struct _HTTPReasons {
		int status;
		const char *reason;
	} *r,reasons[] = 
	{
		{ 100, "Continue" }, 
		{ 101, "Switching Protocols" },
		{ 200, "OK" },
		{ 201, "Created" }, 
		{ 202, "Accepted" }, 
		{ 203, "Non-Authoritative Information" }, 
		{ 204, "No Content" }, 
		{ 205, "Reset Content" }, 
		{ 206, "Partial Content" }, 
		{ 300, "Multiple Choices" }, 
		{ 301, "Moved Permanently" }, 
		{ 302, "Moved Temporarily" }, 
		{ 303, "See Other" }, 
		{ 304, "Not Modified" }, 
		{ 305, "Use Proxy" }, 
		{ 400, "Bad Request" }, 
		{ 401, "Unauthorized" }, 
		{ 402, "Payment Required" }, 
		{ 403, "Forbidden" }, 
		{ 404, "Not Found" }, 
		{ 405, "Method Not Allowed" }, 
		{ 406, "Not Acceptable" }, 
		{ 407, "Proxy Authentication Required" }, 
		{ 408, "Request Timeout" }, 
		{ 409, "Conflict" }, 
		{ 410, "Gone" }, 
		{ 411, "Length Required" }, 
		{ 412, "Precondition Failed" }, 
		{ 413, "Request Entity Too Large" }, 
		{ 414, "Request-URI Too Long" }, 
		{ 415, "Unsupported Media Type" }, 
		{ 500, "Internal Server Error" }, 
		{ 501, "Not Implemented" }, 
		{ 502, "Bad Gateway" }, 
		{ 503, "Service Unavailable" }, 
		{ 504, "Gateway Timeout" }, 
		{ 505, "HTTP Version Not Supported" },
		{ 000, NULL }
	};

	r=reasons;

	while (r->status<=code)
		if (r->status==code)
			return (r->reason);
		else
			r++;

	return "No Reason";
}

static void
WriteErrorMessage(EXTENSION_CONTROL_BLOCK *pECB, int error, const char *szBuffer)
{
	HSE_SEND_HEADER_EX_INFO header;
	DWORD					dwBufLen;
	char szStatus[128];
	char szHeader[] = "Content-Type: text/html\r\n\r\n";

	int statlen = wsprintfA(szStatus, "%d %s", error, HTTPReasonByStatus(error));

	header.pszStatus = szStatus;
	header.cchStatus = statlen;
	header.pszHeader = szHeader;
	header.cchHeader = sizeof(szHeader);
	header.fKeepConn = 0;

	dwBufLen = lstrlenA(szBuffer);

	pECB->ServerSupportFunction(pECB->ConnID, HSE_REQ_SEND_RESPONSE_HEADER_EX,
		&header, 0, 0);
	pECB->WriteClient(pECB->ConnID, (void *)szBuffer, &dwBufLen, 0);
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}




//
// This method is called by IIS when the module
// is first loaded.  We use this to initialize
// our thread pool.
//
BOOL WINAPI
GetExtensionVersion( HSE_VERSION_INFO* pVer )
{
	long n;

	if (pVer)
	{
		pVer->dwExtensionVersion = HSE_VERSION;
		lstrcpynA(pVer->lpszExtensionDesc, extensionDesc, HSE_MAX_EXT_DLL_NAME_LEN);
	}

	gIoPort = CreateIoCompletionPort((HANDLE)INVALID_HANDLE_VALUE, NULL, 0, 0);

	//
	// Before creating the worker threads
	// we need to RevertToSelf() so the threads
	// get proper permissions.
	//
	// First, keep track of who we are.
	HANDLE htok = NULL;
	OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE, TRUE, &htok);

	//
	// RevertToSelf()
	SetThreadToken(NULL, NULL);

	for (n = 0; n < numWorkerThreads; ++n)
	{
		DWORD id;
		gWorkerThreads[n] = CreateThread(NULL, 0, ThreadProc, gIoPort, 0, &id);
	}

	//
	// Switch back to who we were
	SetThreadToken(NULL, htok);
	CloseHandle(htok);

	return TRUE;
}

//
// This method is called by IIS for each request the
// module receives.  We pass the ECB to one of the
// the threads in our pool to complete the processing
// and then return.
//
DWORD WINAPI
HttpExtensionProc( EXTENSION_CONTROL_BLOCK *pECB )
{
	if (!pECB)
		return HSE_STATUS_ERROR;

	if (lstrcmpA(pECB->lpszMethod, "POST"))
	{
		WriteErrorMessage(pECB, 405, "<H1>Invalid method, only POST is supported.</H1>");
		return HSE_STATUS_ERROR;
	}

	if (!PostQueuedCompletionStatus(gIoPort, (DWORD)pECB, 0, NULL))
	{
		char	szBuffer[128];

		wsprintfA(szBuffer, "<H1>Error posting to completion port! Win32 Error = %i</H1>", GetLastError());
		WriteErrorMessage(pECB, 500, szBuffer);
		return HSE_STATUS_ERROR;
	}
	return HSE_STATUS_PENDING;
}

//
// This method is called by IIS when the module is going to
// be unloaded.  We tell all the threads to terminate, wait
// for them, clean up our IoPort and then exit.
//
BOOL WINAPI
TerminateExtension( DWORD dwFlags )
{
	long n;
	for (n = 0; n < numWorkerThreads; ++n)
		PostQueuedCompletionStatus(gIoPort, 0, 0, (OVERLAPPED*)0xFFFFFFFF);

	WaitForMultipleObjects(numWorkerThreads, gWorkerThreads, TRUE, 120000);
	CloseHandle(gIoPort);

	return TRUE;
}

 

