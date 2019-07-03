/****************************************************************************
 * ==> zSplRes -------------------------------------------------------------*
 ****************************************************************************
 * Description : DLL main entry point                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include <afxdllx.h>

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static AFX_EXTENSION_MODULE g_zSplResDLL = {NULL, NULL};
//---------------------------------------------------------------------------
// DLL entry point
//---------------------------------------------------------------------------
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    // remove this if you use lpReserved
    UNREFERENCED_PARAMETER(lpReserved);

    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            TRACE0("ZSPLRES.DLL Initializing!\n");

            // extension DLL one-time initialization
            if (!AfxInitExtensionModule(g_zSplResDLL, hInstance))
                return 0;

            break;
        }

        case DLL_PROCESS_DETACH:
        {
            TRACE0("ZSPLRES.DLL Terminating!\n");

            // terminate the library before destructors are called
            AfxTermExtensionModule(g_zSplResDLL);

            break;
        }
    }

    return 1;
}
//---------------------------------------------------------------------------
/// Exported DLL initialization is run in context of application or Regular DLL
extern "C" void WINAPI InitZSplResDLL()   
{
    TRACE0("ZSPLRES.DLL initialization started\n");

    // create a new CDynLinkLibrary for this app
    new CDynLinkLibrary(g_zSplResDLL);
}
//---------------------------------------------------------------------------
