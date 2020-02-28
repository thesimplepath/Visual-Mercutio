/****************************************************************************
 * ==> zModelBP ------------------------------------------------------------*
 ****************************************************************************
 * Description : DLL main entry point                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static AFX_EXTENSION_MODULE g_zModelBPDLL = { NULL, NULL };
//---------------------------------------------------------------------------
// DLL main entry point
//---------------------------------------------------------------------------
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    // remove this if you use lpReserved
    UNREFERENCED_PARAMETER(lpReserved);

    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            TRACE0("ZMODELBP.DLL Initializing!\n");

            // extension DLL one-time initialization
            if (!AfxInitExtensionModule(g_zModelBPDLL, hInstance))
                return 0;

            // insert this DLL into the resource chain. NOTE: If this Extension DLL is being implicitly linked to by
            // an MFC Regular DLL (such as an ActiveX Control) instead of an MFC application, then you will want to
            // remove this line from DllMain and put it in a separate function exported from this Extension DLL. The
            // Regular DLL that uses this Extension DLL should then explicitly call that function to initialize this
            // Extension DLL. Otherwise, the CDynLinkLibrary object will not be attached to the regular DLL's resource
            // chain, and serious problems will result
            new CDynLinkLibrary(g_zModelBPDLL);

            break;

        case DLL_PROCESS_DETACH:
            TRACE0("ZMODELBP.DLL Terminating!\n");

            // terminate the library before destructors are called
            AfxTermExtensionModule(g_zModelBPDLL);

            break;
    }

    return 1;
}
//---------------------------------------------------------------------------
