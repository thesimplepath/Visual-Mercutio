/****************************************************************************
 * ==> StdAfx.h ------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file for standard system files, or project         *
 *               specific include files that are used frequently, but are   *
 *               changed infrequently                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_STDAFX_H__116E6E10_2B39_4BF0_882F_0E92B86F5F89__INCLUDED_)
#define AFX_STDAFX_H__116E6E10_2B39_4BF0_882F_0E92B86F5F89__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

#define VC_EXTRALEAN        // exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN // exclude rarely-used stuff from Windows headers

#ifndef WINVER
    #define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT
    #define _WIN32_WINNT _WIN32_WINNT_WINXP
#endif                        

#ifndef _WIN32_WINDOWS
    #define _WIN32_WINDOWS 0x0410
#endif

#ifndef _WIN32_IE
    #define _WIN32_IE 0x0400
#endif

#include <afxwin.h>               // MFC core and standard components
#include <afxext.h>               // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
    #include <afxole.h>           // MFC OLE classes
    #include <afxodlgs.h>         // MFC OLE dialog classes
    #include <afxdisp.h>          // MFC Automation classes
#endif

#ifndef _AFX_NO_DB_SUPPORT
    #include <afxdb.h>            // MFC ODBC database classes
#endif

#ifndef _AFX_NO_DAO_SUPPORT
    #include <afxdao.h>           // MFC DAO database classes
#endif

#include <afxdtctl.h>             // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
    #include <afxcmn.h>           // MFC support for Windows Common Controls
#endif

#ifdef _ENABLETRACE
    #include "zBaseLib\ZGTrace.h" // If enabled, trace is defined
#endif

#include <atlbase.h>

// use stingray foundation classes as a dll
#define _SFLDLL

// stingray studio
#include <Foundation\sflcommon.h>
#include <Foundation\apps\Application.h>
#include <Foundation\Patterns\MFC\Collect.h>
#include <Foundation\Patterns\MFC\CollectMfc.h>

using namespace stingray;
using namespace foundation;

// processsoft
#include <zBaseLib\zBaseLib.h>
#include <zBaseSym\zBaseSymLib.h>
#include "PlanFin.hdf"
#include "PSS_Constants.h"
#include "PSS_Defines.h"
#include "PSS_Messages.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__116E6E10_2B39_4BF0_882F_0E92B86F5F89__INCLUDED_)
