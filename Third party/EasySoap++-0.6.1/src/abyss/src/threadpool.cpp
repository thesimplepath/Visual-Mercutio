#include <windows.h>
#include "abyss.h"
#include "threadpool.h"

////////////////////////////////////////////////////////////////////
//C Interface
CHttpThreadPool ThreadPool;

HANDLE
PoolCreateThread(
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    DWORD dwStackSize,
    LPTHREAD_START_ROUTINE lpStartAddress,
    LPVOID lpParameter,
    DWORD dwCreationFlags,
    LPDWORD lpThreadId
    )
{
	return ThreadPool.Start( lpStartAddress, lpParameter, dwCreationFlags);
}

BOOL
PoolTerminateThread(
    HANDLE hThread,
    DWORD dwExitCode
    )
{
	return ThreadPool.Terminate( hThread, dwExitCode);
}

////////////////////////////////////////////////////////////////////
//CHttpThread
CHttpThread::CHttpThread()
:	m_hThread(NULL),
	m_ThreadId(0),
	m_AbortEvent(NULL),
	m_ContinueEvent(NULL),
	m_AbortSet(FALSE),
	m_Param( NULL),
	m_StartProc( NULL),
	m_InUse( FALSE)
{
}

CHttpThread::~CHttpThread() 
{
	if (::GetCurrentThreadId() != m_ThreadId)
		Stop();
	if (m_AbortEvent != NULL)
		CloseHandle( m_AbortEvent);
	if (m_ContinueEvent != NULL)
		CloseHandle( m_ContinueEvent);
}

int WINAPI StartThread (CHttpThread * pThread) {
  	return pThread->ThreadRoutine();
}

int CHttpThread::ThreadRoutine()
{
	HANDLE handles[2] = {m_AbortEvent, m_ContinueEvent};

	for (;;) {
		DWORD dw = WaitForMultipleObjects( 2, handles, FALSE, INFINITE);
		m_InUse = TRUE;
		if (dw == WAIT_OBJECT_0) {
			break;
		} else if (dw == (WAIT_OBJECT_0+1)) {
			//Call the specified procedure
			if (m_StartProc != NULL)
				m_StartProc(  m_Param);
			//Reset the wait flag
			ResetEvent( m_ContinueEvent);
		}
		m_InUse = FALSE;
	}
	m_hThread=0;
	m_ThreadId = 0;
	return 0;
}

HANDLE CHttpThread::Start( LPTHREAD_START_ROUTINE StartProc, LPVOID param, DWORD dwCreationFlags) {
	m_Param = param;
	m_StartProc = StartProc;

	if (m_AbortEvent == NULL)
		m_AbortEvent=::CreateEvent( NULL, TRUE, FALSE, NULL);
	if (m_ContinueEvent == NULL)
		m_ContinueEvent=::CreateEvent( NULL, TRUE, FALSE, NULL);

	m_InUse = TRUE;
	if (m_hThread == NULL) {
		m_hThread = ::CreateThread( NULL, 4096, (LPTHREAD_START_ROUTINE)StartThread, (LPVOID)this, dwCreationFlags, &m_ThreadId);
		SetEvent( m_ContinueEvent);
	} else {
		if ((dwCreationFlags & CREATE_SUSPENDED) == CREATE_SUSPENDED) {
			SuspendThread( m_hThread);
		}
		SetEvent( m_ContinueEvent);
	}

	return m_hThread;
}

void CHttpThread::SetAbortEvent() 
{
	if (m_AbortEvent != NULL)
		SetEvent( m_AbortEvent);
}

BOOL CHttpThread::Stop() {
	if (m_hThread == NULL)
		return TRUE;

	SetAbortEvent();
	WaitForSingleObject( m_hThread, 30);
	BOOL b = TerminateThread (m_hThread, 0xFFFF);
	if (b) {
		CloseHandle (m_hThread);
	}

    return TRUE;
}

BOOL CHttpThread:: Terminate( DWORD dwExitCode)
{
	HANDLE h = m_hThread;
	m_hThread=NULL;
	m_InUse = FALSE;
	return TerminateThread (h, 0xFFFF);
}

////////////////////////////////////////////////////////////////////
//CHttpThreadPool
CHttpThreadPool::CHttpThreadPool()
{
}

CHttpThreadPool::~CHttpThreadPool()
{
	StopAll();
}

HANDLE CHttpThreadPool::Start( LPTHREAD_START_ROUTINE StartProc, LPVOID param, DWORD dwCreationFlags)
{
	int n=0;
	HANDLE hRet = NULL;

	m_Section.Enter();
	for (n=0; n< MAX_THREAD; n++) {
		if (m_Pool[n].GetInUseFlag() == FALSE) {
			m_Pool[n].SetInUseFlag();
			hRet = m_Pool[n].Start(StartProc, param, dwCreationFlags);
			break;
		}
	}
	m_Section.Leave();
	return hRet;
}

DWORD CHttpThreadPool::StopAll()
{
	int n=0;
	m_Section.Enter();
	for (n=0; n< MAX_THREAD; n++) {
		m_Pool[n].Stop();
	}
	m_Section.Leave();
	return 0;
}

BOOL CHttpThreadPool:: Terminate( HANDLE hThread, DWORD dwExitCode)
{
	int n=0;
	int nThread =0 ;
	BOOL b = FALSE;
	m_Section.Enter();
	for (n=0; n< MAX_THREAD; n++) {
		if (m_Pool[n].GetHandle() == hThread) {
			nThread = n;
			break;
		}
	}
	m_Section.Leave();
	if (nThread != 0) {
		b= m_Pool[ nThread].Terminate( dwExitCode);
	}
	return b;
}