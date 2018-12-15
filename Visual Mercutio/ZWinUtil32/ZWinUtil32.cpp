// ZWinUtil32.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


AFX_EXTENSION_MODULE extensionZWinUtil32DLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    // Remove this if you use lpReserved
    UNREFERENCED_PARAMETER(lpReserved);

    if (dwReason == DLL_PROCESS_ATTACH)
    {
        // Extension DLL one-time initialization
        if (!AfxInitExtensionModule(extensionZWinUtil32DLL, hInstance))
            return 0;
        TRACE0("ZWINUTIL32.DLL Initializing!\n");
        // Create a new CDynLinkLibrary for this app.
        new CDynLinkLibrary(extensionZWinUtil32DLL);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("ZWINUTIL32.DLL Terminating!\n");
        // Terminate the library before destructors are called
        AfxTermExtensionModule(extensionZWinUtil32DLL);
    }
    return 1;   // ok
}



