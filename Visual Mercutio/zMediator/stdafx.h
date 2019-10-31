/****************************************************************************
 * ==> StdAfx --------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file for standard system include files, or project *
 *               specific include files that are used frequently, but are   *
 *               changed infrequently                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef AFX_STDAFX_H__AA3SDCF4_2899_A4A8_78DR_123400DF0056__INCLUDED_
#define AFX_STDAFX_H__AA3SDCF4_2899_A4A8_78DR_123400DF0056__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// exclude rarely-used stuff from Windows headers
#ifndef VC_EXTRALEAN
    #define VC_EXTRALEAN
#endif

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

// make several CString constructor explicit
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

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

// visual mercutio
#include "PSS_Constants.h"
#include "PSS_Defines.h"
#include "PSS_Messages.h"
#include "Planfin.hdf"
#include "PSS_SrvMsgs.h"

// use Objective Toolkit as a DLL
#define _SECDLL

// stingray studio
#include "toolkit\secall.h"
#include "toolkit\secres.h"

// use Objective Views as a DLL
#define _OVDLL

#include "views\OdAll.h"

// resources
#include "..\zFormsRes\zFormsRes.h"
#include "..\zRes32\zRes.h"
#include "zMediatorRes.h"

// undefine the SubclassWindow macro
#undef SubclassWindow

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
