/****************************************************************************
 * ==> StdAfx.h ------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file for standard system files, or project         *
 *               specific include files that are used frequently, but are   *
 *               changed infrequently                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_STDAFX_H__116E6E22_2B39_4BF0_882F_0E92B86F5F89__INCLUDED_)
#define AFX_STDAFX_H__116E6E22_2B39_4BF0_882F_0E92B86F5F89__INCLUDED_

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

// several CString constructors will become explicit
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

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

// this was added by Stingray Appwizard. If you wish to define _GXDLL
// as a preprocessor symbol you may remove this and add this definition to
// the settings in Developer Studio.
#ifdef _AFXDLL
    #ifndef _GXDLL
        #define _GXDLL
    #endif
#endif
#include <grid\gxall.h>

// use objective views as a DLL
#define _OVDLL

// objective views header files
#include "Views\OdAll.h"

// processsoft
#include "zConversion\zConversionLib.h"
#include "zBaseLib\zBaseLib.h"
#include "zBaseSym\zBaseSymLib.h"
#include "zProperty\zPropertyLib.h"
#include "zDB\zDBLib.h"
#include "zWinUtil32\zWinUtil32Lib.h"
#include "zEvent\zEventLib.h"
#include "zRes32\zRes32Lib.h"
#include "zModel\zModelLib.h"
#include "zModelBP\zModelBPLib.h"
#include "zModelWeb\zModelWebLib.h"
#include "zWeb\zWebLib.h"
#include "zResMgr\zResMgrLib.h"
#include "PSS_Macros.h"

// resources
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // AFX_STDAFX_H__116E6E22_2B39_4BF0_882F_0E92B86F5F89__INCLUDED_
