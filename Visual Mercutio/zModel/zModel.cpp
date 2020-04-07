/****************************************************************************
 * ==> zModel --------------------------------------------------------------*
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

// objective views
#ifdef _OVDLL
    #include "initguid.h"
    #include "Views/OdGuids.h"
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static AFX_EXTENSION_MODULE g_ZModelDLL = {NULL, NULL};
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
        {
            TRACE0("ZMODEL.DLL Initializing!\n");

            // extension DLL one-time initialization
            if (!::AfxInitExtensionModule(g_ZModelDLL, hInstance))
                return 0;

            // insert this DLL into the resource chain. NOTE: If this Extension DLL is being implicitly linked to by
            // an MFC Regular DLL (such as an ActiveX Control) instead of an MFC application, then you will want to
            // remove this line from DllMain and put it in a separate function exported from this Extension DLL. The
            // Regular DLL that uses this Extension DLL should then explicitly call that function to initialize this
            // Extension DLL. Otherwise, the CDynLinkLibrary object will not be attached to the regular DLL's resource
            // chain, and serious problems will result
            new CDynLinkLibrary(g_ZModelDLL);

            WNDCLASS               wcls;
            const TCHAR BASED_CODE szWnd[] = _T("_ZVGraphModelWnd");

            if (!::GetClassInfo(hInstance, szWnd, &wcls))
            {
                // set new values
                wcls.style         = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
                wcls.lpfnWndProc   = DefWindowProc;
                wcls.cbClsExtra    = 0;
                wcls.cbWndExtra    = 0;
                wcls.hInstance     = hInstance;
                wcls.lpszClassName = szWnd;
                wcls.hIcon         = 0;
                wcls.hCursor       = 0;
                wcls.hbrBackground = 0;
                wcls.lpszMenuName  = NULL;
                AfxRegisterClass(&wcls);
            }

            break;
        }

        case DLL_PROCESS_DETACH:
            TRACE0("ZMODEL.DLL Terminating!\n");

            // terminate the library before destructors are called
            ::AfxTermExtensionModule(g_ZModelDLL);

            break;
    }

    return 1;
}
//---------------------------------------------------------------------------
