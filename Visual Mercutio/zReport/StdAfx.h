/****************************************************************************
 * ==> StdAfx --------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file for standard system include files, or project *
 *               specific include files that are used frequently, but are   *
 *               changed infrequently                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_STDAFX_H__7AAE53AE_597F_4A00_BDAD_4A0A32B6A4BC__INCLUDED_)
#define AFX_STDAFX_H__7AAE53AE_597F_4A00_BDAD_4A0A32B6A4BC__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// exclude rarely-used stuff from Windows headers
#define VC_EXTRALEAN

// disable non-critical warnings
#pragma warning(disable:4786) // identifier was truncated to '255' characters in the debug information

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

// this was added by Stingray App Wizard. If you wish to define _GXDLL as a preprocessor symbol,
// you may remove this and add this definition to  the settings in Developer Studio
#ifdef _AFXDLL
    #ifndef _GXDLL
        #define _GXDLL
    #endif
#endif

// stringray studio
#include <grid\gxall.h>

// use objective views as a DLL
#define _OVDLL

// objective views header files
#include "views\OdAll.h"

// processsoft
#include "PSS_Constants.h"
#include "PSS_Defines.h"
#include "PSS_Messages.h"
#include "PlanFin.hdf"
#include <zBaseLib\zBaseLib.h>
#include <zBaseSym\zBaseSymLib.h>
#include <zModel\zModelLib.h>
#include <zDB\zDBLib.h>
#include <zRes32\zRes32Lib.h>

// resources
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__7AAE53AE_597F_4A00_BDAD_4A0A32B6A4BC__INCLUDED_)
