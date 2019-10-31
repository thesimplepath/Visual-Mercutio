// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#if !defined(__STDAFX_H)
#define __STDAFX_H

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

// required in 32 bit
#define SECURITY_WIN32

// Disable non-critical warnings
#pragma warning(disable : 4786)    // identifier was truncated to '255' characters in the debug information
#pragma warning(disable : 4996)

// exclude rarely-used stuff from Windows headers
#define VC_EXTRALEAN

// Version de Winver définie pour Windows NT4 et supérieures.
#ifndef WINVER
#define WINVER 0x0501
#endif

// Plateforme cible définie à Windows NT4 et supérieures pour les versions NT de Windows.
#ifndef _WIN32_WINNT
#define _WIN32_WINNT _WIN32_WINNT_WINXP
#endif                        

// Plateforme cible définie à Windows98 et supérieures pour les versions standards de Windows.
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410
#endif

// Internet Explorer définie à la version NT4.
#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>                // MFC OLE classes
#include <afxodlgs.h>            // MFC OLE dialog classes
#include <afxdisp.h>            // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifdef _WIN32
    #ifndef _AFX_NO_DAO_SUPPORT
    #include <afxdao.h>            // MFC DAO database classes
    #include <dbdao.h>
    #endif // _AFX_NO_DAO_SUPPORT

    #include <afxdtctl.h>        // MFC support for Internet Explorer 4 Common Controls
    
    #ifndef _AFX_NO_AFXCMN_SUPPORT
    #include <afxcmn.h>            // MFC support for Windows Common Controls
    #endif // _AFX_NO_AFXCMN_SUPPORT

#endif

#ifdef _ENABLETRACE                // If enable trace is defined
#include "zBaseLib\ZGTrace.h"
#endif

#include <AFXPRIV.H>            // For MFC messages

// JMR-MODIF - Le 16 août 2005 - Ajout de l'en-tête <dde> pour implémenter les fonctions d'échange de données dynamiques.
#include <dde.h>
#include "PSS_Constants.h"
#include "PSS_Defines.h"
#include "PSS_Messages.h"
#include "PlanFin.hdf"
#include <CJ60Lib.h>            // CJ60 Library components

//this was added by Stingray Appwizard. If you wish to define _GXDLL
//as a preprocessor symbol you may remove this and add this definition to 
//the settings in Developer Studio. 
#ifdef _AFXDLL
#ifndef _GXDLL
#define _GXDLL
#endif
#endif

#include <grid\gxall.h>

#define _SECDLL                    // Use Objective Toolkit as a DLL
#include "toolkit\secres.h"        // Objective Toolkit Resources
#include "toolkit\secall.h"        // Stingray Objective Toolkit
#define _OVDLL                    // Use Objective Views as a DLL

#include "Views\OdAll.h"        // Objective Views Header Files

// ***********************************************************
// *
// *  zForms Resources
// *
// ***********************************************************
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"

#include <zBaseLib\zBaseLib.h>            // The base library
#include <zBaseSym\zBaseSymLib.h>        // The base symbol library
#include <zProperty\zPropertyLib.h>        // The property library
#include <zModel\zModelLib.h>            // The model library
#include <zWkf\zWkfLib.h>                // The workflow library
#include <zDB\zDBLib.h>                    // The Database library
#include <zReport\zReportLib.h>            // The Report library
#include <zReportBP\zReportBPLib.h>        // The Mercutio Report library
#include <zModelBP\zModelBPLib.h>        // The BP model library
#include <zModelWeb\zModelWebLib.h>        // The model Web library
#include <zReportWeb\zReportWebLib.h>    // JMR-MODIF - Le 21 juillet 2005 - Ajout de la référence vers le nouveau projet zReportWeb
#include <zSOAP\zSOAPLib.h>                // The SOAP library
#include <zSOAP\zSOAPIncAll.h>            // Include files for SOAP
#include <zPtyMgr\zPtyMgrAll.h>            // The Property Manager include files and library
#include <zScty\zSctyAll.h>                // The Security include files and library
#include <zWinUtil32\zWinUtil32Lib.h>    // The windows utility library
#include <zEvent\zEventLib.h>            // The event library
#include <zSplash\zSplashLib.h>            // The splash screen library
#include <zWeb\zWebLib.h>                // The web library
#include <zTip\zTipLib.h>                // The tip components library
#include <zRes32\zRes32Lib.h>            // Resource library
#include <zSplRes\zSplResLib.h>            // The splash resource library
#include <zResMgr\zResMgrLib.h>            // The resource manager library

#endif // __STDAFX_H
