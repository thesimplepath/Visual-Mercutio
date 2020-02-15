/****************************************************************************
 * ==> StdAfx --------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file for standard system include files, or project *
 *               specific include files that are used frequently, but are   *
 *               changed infrequently                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_STDAFX_H__5D434D8E_1708_4B81_81AC_3A92251FDB4B__INCLUDED_)
#define AFX_STDAFX_H__5D434D8E_1708_4B81_81AC_3A92251FDB4B__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// exclude rarely-used stuff from Windows headers
#define VC_EXTRALEAN

// disable non-critical warnings
#pragma warning(disable:4786) // identifier was truncated to '255' characters in the debug information
#pragma warning(disable:4355) // assume that this pointer is used in several constructors

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

// std
#include <string>
#include <list>

using namespace std;

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
    #include "zBaseLib\ZGTrace.h" // if enabld, trace is defined
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// CJ60 Library components
#include <CJ60Lib.h>

// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT

// stingray studio
#define _SECDLL             // use Objective Toolkit as a DLL
#include "toolkit\secres.h" // objective Toolkit Resources
#include "toolkit\secall.h" // stingray Objective Toolkit

#define _OVDLL              // use Objective Views as a DLL
#include "Views/OdAll.h"    // objective Views Header Files

#include "PSS_Constants.h"
#include "PSS_Defines.h"
#include "PSS_Messages.h"
#include "PlanFin.hdf"

// visual mercutio
#include <zBaseLib\zBaseLib.h>
#include <zBaseSym\zBaseSymLib.h>
#include <zProperty\zPropertyLib.h>
#include <zModel\zModelLib.h>
#include <zModelWeb\zModelWebLib.h>
#include <zWeb\zWebLib.h>
#include <zWkf\zWkfLib.h>
#include <zSOAP\zSOAPLib.h>
#include <zSOAP\zSOAPIncAll.h>
#include "zConversion\zConversionLib.h"
#include <zDB\zDBLib.h>
#include <zPtyMgr\zPtyMgrAll.h>
#include <zWinUtil32\zWinUtil32Lib.h>
#include <zEvent\zEventLib.h>
#include <zRes32\zRes32Lib.h>

// resources
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5D434D8E_1708_4B81_81AC_3A92251FDB4B__INCLUDED_)
