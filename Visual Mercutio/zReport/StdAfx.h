// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__7AAE53AE_597F_4A00_BDAD_4A0A32B6A4BC__INCLUDED_)
#define AFX_STDAFX_H__7AAE53AE_597F_4A00_BDAD_4A0A32B6A4BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

// Disable non-critical warnings
#pragma warning(disable:4786) // identifier was truncated to '255' characters in the debug information

//#ifdef _WINNT_40
//// For compatibility reason with platform sdk used
//// with Visual C++ 6.0
//// Dominique Aigroz october 2002
//#define  WINVER  0x0400
//#else
//#define WINVER 0x0501
//#endif // _WINNT_40

// Version de Winver définie pour Windows NT4 et supérieures.
#ifndef WINVER
#define WINVER 0x0400
#endif

// Plateforme cible définie à Windows NT4 et supérieures pour les versions NT de Windows.
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif						

// Plateforme cible définie à Windows98 et supérieures pour les versions standards de Windows.
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410
#endif

// Internet Explorer définie à la version NT4.
#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#ifdef _ENABLETRACE			// If enable trace is defined
#include "zBaseLib\ZGTrace.h"
#endif


#include "ZAConst.h"

#include "Define.h"

#include "Message.h"

#include "PlanFin.hdf"

#include <zBaseLib\zBaseLib.h>		// The base library

#include <zBaseSym\zBaseSymLib.h>	// The base symbol library

#include <zModel\zModelLib.h>		// The base model library

#include <zDB\zDBLib.h>			// The Database library

#include <zRes32\zRes32Lib.h>		// Resource library


//this was added by Stingray Appwizard. If you wish to define _GXDLL
//as a preprocessor symbol you may remove this and add this definition to 
//the settings in Developer Studio. 
#ifdef _AFXDLL
#ifndef _GXDLL
#define _GXDLL
#endif
#endif


#include <grid\gxall.h>


// Use Objective Views as a DLL
#define _OVDLL

// Objective Views Header Files
#include "views\OdAll.h"


// ***********************************************************
// *
// *  zForms Resources
// *
// ***********************************************************
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__7AAE53AE_597F_4A00_BDAD_4A0A32B6A4BC__INCLUDED_)
