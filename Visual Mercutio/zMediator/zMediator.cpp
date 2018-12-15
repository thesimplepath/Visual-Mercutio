// zMediator.cpp : définit les fonctions d'initialisation pour la DLL.

#include "stdafx.h"

// Cette ligne est à décommenter si l'outil Visual Leak Detector est utilisé.
//#include <VLD.h>

#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

AFX_EXT_DATA AFX_EXTENSION_MODULE ZMediatorDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved )
{
    // Remove this if you use lpReserved
    UNREFERENCED_PARAMETER( lpReserved );

    if ( dwReason == DLL_PROCESS_ATTACH )
    {
        TRACE0( "ZMEDIATOR.DLL Initializing!\n" );
        
        // Extension DLL one-time initialization
        if ( !AfxInitExtensionModule( ZMediatorDLL, hInstance ) )
        {
            return 0;
        }

        // Insert this DLL into the resource chain
        // NOTE: If this Extension DLL is being implicitly linked to by
        //  an MFC Regular DLL (such as an ActiveX Control)
        //  instead of an MFC application, then you will want to
        //  remove this line from DllMain and put it in a separate
        //  function exported from this Extension DLL.  The Regular DLL
        //  that uses this Extension DLL should then explicitly call that
        //  function to initialize this Extension DLL.  Otherwise,
        //  the CDynLinkLibrary object will not be attached to the
        //  Regular DLL's resource chain, and serious problems will
        //  result.

        new CDynLinkLibrary( ZMediatorDLL );
    }
    else if ( dwReason == DLL_PROCESS_DETACH )
    {
        TRACE0( "ZMEDIATOR.DLL Terminating!\n" );

        // Terminate the library before destructors are called
        AfxTermExtensionModule( ZMediatorDLL );
    }

    // Ok
    return 1;
}
