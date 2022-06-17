/****************************************************************************
 * ==> StdAfx.h ------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file for standard system files, or project         *
 *               specific include files that are used frequently, but are   *
 *               changed infrequently                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(__STDAFX_H)
#define __STDAFX_H

#if _MSC_VER > 1000
    #pragma once
#endif

// required in 32 bit
#define SECURITY_WIN32

// disable non-critical warnings
#pragma warning(disable : 4786) // identifier was truncated to '255' characters in the debug information
#pragma warning(disable : 4996)

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

#ifdef _WIN32
    #ifndef _AFX_NO_DAO_SUPPORT
        #include <afxdao.h>       // MFC DAO database classes
        #include <dbdao.h>
    #endif
    #include <afxdtctl.h>         // MFC support for Internet Explorer 4 Common Controls
    #ifndef _AFX_NO_AFXCMN_SUPPORT
        #include <afxcmn.h>       // MFC support for Windows Common Controls
    #endif
#endif

#ifdef _ENABLETRACE
    #include "zBaseLib\ZGTrace.h" // if enabled, trace is defined
#endif

// mfc
#include <AfxPriv.h>
#include <dde.h>

// CJ60 library components
#include <CJ60Lib.h>

// this was added by Stingray app wizard. If you wish to define _GXDLL
// as a preprocessor symbol you may remove this and add this definition to
// the settings in Developer Studio
#ifdef _AFXDLL
    #ifndef _GXDLL
        #define _GXDLL
    #endif
#endif

// stingray studio
#include <grid\gxall.h>

#define _SECDLL             // Use Objective Toolkit as a DLL
#include "toolkit\secres.h" // Objective Toolkit Resources
#include "toolkit\secall.h" // Stingray Objective Toolkit
#define _OVDLL              // Use Objective Views as a DLL
#include "Views\OdAll.h"    // Objective Views Header Files

// processsoft
#include "zBaseLib\zBaseLib.h"
#include "zBaseSym\zBaseSymLib.h"
#include "zProperty\zPropertyLib.h"
#include "zModel\zModelLib.h"
#include "zWkf\zWkfLib.h"
#include "zDB\zDBLib.h"
#include "zReport\zReportLib.h"
#include "zReportBP\zReportBPLib.h"
#include "zModelBP\zModelBPLib.h"
#include "zModelWeb\zModelWebLib.h"
#include "zReportWeb\zReportWebLib.h"
#include "zSOAP\zSOAPLib.h"
#include "zSOAP\zSOAPIncAll.h"
#include "zPtyMgr\zPtyMgrAll.h"
#include "zScty\zSctyAll.h"
#include "zWinUtil32\zWinUtil32Lib.h"
#include "zEvent\zEventLib.h"
#include "zSplash\zSplashLib.h"
#include "zWeb\zWebLib.h"
#include "zTip\zTipLib.h"
#include "zRes32\zRes32Lib.h"
#include "zSplRes\zSplResLib.h"
#include "zResMgr\zResMgrLib.h"
#include "PSS_Constants.h"
#include "PSS_Macros.h"
#include "PSS_Defines.h"
#include "PSS_Messages.h"
#include "PlanFin.hdf"

// resources
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"

#endif
