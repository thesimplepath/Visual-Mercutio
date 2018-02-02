// zModel.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Define the Objective Views GUIDs. The GUIDs are declared in OdGuids.h.
// Including initguid.h before OdGuids.h forces the GUIDs to be defined
// in this module. Skip this if statically linking to the Objective Views
// library, because the GUIDs will be linked into the app from the library.
#ifdef _OVDLL
#include "initguid.h"
#include "Views/OdGuids.h"
// OV Compatibility problem
//#include "CmnGuids.h"
#endif


static AFX_EXTENSION_MODULE ZModelDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("ZMODEL.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(ZModelDLL, hInstance))
			return 0;

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

		new CDynLinkLibrary(ZModelDLL);

		WNDCLASS wcls;
		const TCHAR BASED_CODE szWnd[] = _T("_ZVGraphModelWnd");

		if (!::GetClassInfo(hInstance, szWnd, &wcls))
		{
			// set new values
			wcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
			wcls.lpfnWndProc = DefWindowProc;
			wcls.cbClsExtra = 0;
			wcls.cbWndExtra = 0;
			wcls.hInstance = hInstance;
			wcls.lpszClassName = szWnd;
			wcls.hIcon = 0;
			wcls.hCursor = 0;
			wcls.hbrBackground = 0;
			wcls.lpszMenuName = NULL;
			AfxRegisterClass(&wcls);
		}

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("ZMODEL.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(ZModelDLL);
	}
	return 1;   // ok
}
