// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__AF334CFA_949D_4540_B2EC_BD5CF3EB362B__INCLUDED_)
#define AFX_STDAFX_H__AF334CFA_949D_4540_B2EC_BD5CF3EB362B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

//#ifdef _WINNT_40
//// For compatibility reason with platform sdk used
//// with Visual C++ 6.0
//// Dominique Aigroz october 2002
//#define  WINVER  0x0501
//#else
//#define WINVER 0x0501
//#endif // _WINNT_40

// Version de Winver d�finie pour Windows NT4 et sup�rieures.
#ifndef WINVER
#define WINVER 0x0501
#endif

// Plateforme cible d�finie � Windows NT4 et sup�rieures pour les versions NT de Windows.
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif                        

// Plateforme cible d�finie � Windows98 et sup�rieures pour les versions standards de Windows.
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410
#endif

// Internet Explorer d�finie � la version NT4.
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
#include <afxdb.h>            // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>            // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>        // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>            // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <winver.h>

#include "ShellApi.h"
#include <direct.h>
#include <dos.h>
#include <fstream>

using namespace std;

#ifdef _ENABLETRACE            // If enable trace is defined
#include "zBaseLib\ZGTrace.h"
#endif


#include "ZAConst.h"

#include "Define.h"

#include "Message.h"

#include "PlanFin.hdf"

#include <zBaseLib\zBaseLib.h>        // The base library

#include <zRes32\zRes32Lib.h>        // Resource library

#include <CJ60Lib.h>        // CJ60 Library components


// ***********************************************************
// *
// *  zForms Resources
// *
// ***********************************************************
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__AF334CFA_949D_4540_B2EC_BD5CF3EB362B__INCLUDED_)
