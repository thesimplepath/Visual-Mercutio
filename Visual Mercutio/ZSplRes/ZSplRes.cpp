// ZSplRes.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE ZSplResDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    // Remove this if you use lpReserved
    UNREFERENCED_PARAMETER(lpReserved);

    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("ZSPLRES.DLL Initializing!\n");
        
        // Extension DLL one-time initialization
        if (!AfxInitExtensionModule(ZSplResDLL, hInstance))
            return 0;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("ZSPLRES.DLL Terminating!\n");
        // Terminate the library before destructors are called
        AfxTermExtensionModule(ZSplResDLL);
    }
    return 1;   // ok
}


// Exported DLL initialization is run in context of application
// or Regular DLL.   
extern "C" void WINAPI InitZSplResDLL()   
{
    TRACE0("ZRES32.DLL Initializing!\n");
    // Create a new CDynLinkLibrary for this app.
    new CDynLinkLibrary(ZSplResDLL);
}

