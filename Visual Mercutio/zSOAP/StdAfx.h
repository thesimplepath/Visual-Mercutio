/****************************************************************************
 * ==> StdAfx.h ------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file for standard system files, or project         *
 *               specific include files that are used frequently, but are   *
 *               changed infrequently                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_STDAFX_H__C2806406_F266_4FF4_BCA7_D1E542DE4CA3__INCLUDED_)
#define AFX_STDAFX_H__C2806406_F266_4FF4_BCA7_D1E542DE4CA3__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// exclude rarely-used stuff from Windows headers
#define VC_EXTRALEAN

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

// mfc
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
    #include "zBaseLib\ZGTrace.h" // if enabled, trace is defined
#endif

// processsoft
#include "PSS_Macros.h"
#include "zSOAPIncAll.h"
#include "zConversion\zConversionLib.h"

// std
#include <string>
#include <list>

#define ODS(msg)\
{\
    OutputDebugString(msg);\
    OutputDebugString(_T("\n"));\
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C2806406_F266_4FF4_BCA7_D1E542DE4CA3__INCLUDED_)
