/****************************************************************************
 * ==> StdAfx --------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file for standard system include files, or project *
 *               specific include files that are used frequently, but are   *
 *               changed infrequently                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_STDAFX_H__8239F789_BDDD_11D2_94FB_0000B45D7C6F__INCLUDED_)
#define AFX_STDAFX_H__8239F789_BDDD_11D2_94FB_0000B45D7C6F__INCLUDED_

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
#include <afxwin.h>
#include <afxext.h>

#ifdef _WIN32
    #ifndef _AFX_NO_OLE_SUPPORT
        #include <afxole.h>
        #include <afxodlgs.h>
        #include <afxdisp.h>
    #endif
#endif

#ifndef _AFX_NO_DB_SUPPORT
    #include <afxdb.h>
#endif

#ifdef _WIN32
    #ifndef _AFX_NO_DAO_SUPPORT
        #include <afxdao.h>
    #endif

    #include <afxdtctl.h>

    #ifndef _AFX_NO_AFXCMN_SUPPORT
        #include <afxcmn.h>
    #endif
#endif

#include <AFXPRIV.H>

// processsoft
#include "ZAConst.h"

#ifdef _ENABLETRACE
    #include "zBaseLib\ZGTrace.h"
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
