/****************************************************************************
 * ==> StdAfh --------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file for standard system files, or project         *
 *               specific include files that are used frequently, but are   *
 *               changed infrequently                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_STDAFX_H__F4BC3BEA_BDC3_11D2_94FB_0000B45D7C6F__INCLUDED_)
#define AFX_STDAFX_H__F4BC3BEA_BDC3_11D2_94FB_0000B45D7C6F__INCLUDED_

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
#include <afxcoll.h>

#ifdef _WIN32
    #ifndef _AFX_NO_OLE_SUPPORT
        #include <afxole.h>       // MFC OLE classes
        #include <afxodlgs.h>     // MFC OLE dialog classes
        #include <afxdisp.h>      // MFC Automation classes
    #endif
#endif

#ifndef _AFX_NO_DB_SUPPORT
    #include <afxdb.h>            // MFC ODBC database classes
#endif

#ifdef _WIN32
    #ifndef _AFX_NO_DAO_SUPPORT
        #include <afxdao.h>       // MFC DAO database classes
    #endif
    #include <afxdtctl.h>         // MFC support for Internet Explorer 4 Common Controls
    #ifndef _AFX_NO_AFXCMN_SUPPORT
        #include <afxcmn.h>       // MFC support for Windows Common Controls
    #endif
#endif

#include <afxmt.h>                // MFC Mutex Support

#ifdef _ENABLETRACE
    #include "zBaseLib\ZGTrace.h" // if enabled, trace is defined
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// CodeJoke Library components
#include <CJ60Lib.h>

// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT

// processsoft
#include <zBaseLib\zBaseLib.h>
#include <zEvent\zEventLib.h>
#include <zWeb\zWebLib.h>
#include <zRes32\zRes32Lib.h>
#include "PSS_Defines.h"
#include "PSS_Constants.h"
#include "PSS_Macros.h"
#include "PSS_Messages.h"
#include "PSS_SrvMsgs.h"

// stingray studio
#define _SECDLL

#include "toolkit\secres.h"
#include "toolkit/secall.h"

// resources
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F4BC3BEA_BDC3_11D2_94FB_0000B45D7C6F__INCLUDED_)
