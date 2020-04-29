/****************************************************************************
 * ==> StdAfx --------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file for standard system include files, or project *
 *               specific include files that are used frequently, but are   *
 *               changed infrequently                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_STDAFX_H__345101E9_12FD_11D4_970C_0000B45D7C6F__INCLUDED_)
#define AFX_STDAFX_H__345101E9_12FD_11D4_970C_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// exclude rarely-used stuff from Windows headers
#define VC_EXTRALEAN

// disable non-critical warnings
#pragma warning(disable:4786)
#pragma warning(disable:4355)

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

// CJ60 library components
#include <CJ60Lib.h>

// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT

// stingray studio
#define _SECDLL                         // use objective toolkit as a DLL
#include "toolkit\secres.h"             // objective toolkit resources
#include "toolkit\secall.h"             // stingray objective toolkit

#define _OVDLL                          // use objective views as a DLL
#include "views\OdAll.h"                // objective views header Files

// processsoft
#include <zBaseLib\zBaseLib.h>          // the base library
#include <zConversion\zConversionLib.h> // to include the zConversion library
#include <zBaseSym\zBaseSymLib.h>       // the base symbol library
#include <zProperty\zPropertyLib.h>     // the property library
#include <zWinUtil32\zWinUtil32Lib.h>   // the windows utility library
#include <zWeb\zWebLib.h>               // the web library
#include <zXML\zXMLLib.h>               // the XML utility library
#include <zSOAP\zSOAPLib.h>             // the SOAP utility library
#include <zEvent\zEventLib.h>           // the event library
#include <zDB\zDBLib.h>                 // the Database library

// resources
#include <zRes32\zRes32Lib.h>           // resource library
#include <zResMgr\zResMgrLib.h>         // the resource manager library
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"
#include "PSS_Constants.h"
#include "PSS_Macros.h"
#include "PSS_Defines.h"
#include "PSS_Messages.h"
#include "PlanFin.hdf"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__345101E9_12FD_11D4_970C_0000B45D7C6F__INCLUDED_)
