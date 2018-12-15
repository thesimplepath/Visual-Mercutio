/****************************************************************************
 * ==> StdAfx --------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file for standard system include files, or project *
 *               specific include files that are used frequently, but are   *
 *               changed infrequently                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef AFX_STDAFX_H__0E120CF9_3875_11D3_95E6_0000B45D7C6F__INCLUDED_
#define AFX_STDAFX_H__0E120CF9_3875_11D3_95E6_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

 // exclude rarely-used stuff from Windows headers
#define VC_EXTRALEAN

// disable non-critical warnings
#pragma warning(disable : 4786)    // identifier was truncated to '255' characters in the debug information
#pragma warning(disable : 4996)

/*
#ifdef _WINNT_40
    // for compatibility reason with platform sdk used with Visual C++ 6.0
    #define  WINVER  0x0501
#else
    #define WINVER 0x0501
#endif
*/

// set Windows version for NT4 and higher
#ifndef WINVER
    #define WINVER 0x0501
#endif

// set target platform to Window NT4 and higher
#ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0400
#endif

// set Win32 Windows version to Windows 98 and higher
#ifndef _WIN32_WINDOWS
    #define _WIN32_WINDOWS 0x0410
#endif

// set Windows Explorer version to 4.x and higher
#ifndef _WIN32_IE
    #define _WIN32_IE 0x0400
#endif

// mfc
#include <afxwin.h>
#include <afxext.h>

#ifndef _AFX_NO_OLE_SUPPORT
    #include <afxole.h>
    #include <afxodlgs.h>
    #include <afxdisp.h>
#endif

#ifndef _AFX_NO_DB_SUPPORT
    #include <afxdb.h>
#endif

#ifndef _AFX_NO_DAO_SUPPORT
    #include <afxdao.h>
#endif

#include <afxdtctl.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
    #include <afxcmn.h>
#endif

#include <afxmt.h>

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// CJ60 Library components
#include <CJ60Lib.h>

//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT

// visual mercutio
#include "Zaconst.h"
#include "Define.h"
#include "Message.h"
#include "Planfin.hdf"
#include "ZSrvMess.h"

#ifdef _ENABLETRACE
    #include "zBaseLib\ZGTrace.h"
#endif

// use Objective Toolkit as a DLL
#define _SECDLL

// Stingray Studio
#include "toolkit\secall.h"
#include "toolkit\secres.h"

// Use Objective Views as a DLL
#define _OVDLL

#include "views\OdAll.h"

// resources
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"
#include "zBaseLibRes.h"

// undefine the SubclassWindow macro
#undef SubclassWindow

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif