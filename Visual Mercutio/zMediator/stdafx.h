// stdafx.h : Fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés

#if !defined(AFX_STDAFX_H__AA3SDCF4_2899_A4A8_78DR_123400DF0056__INCLUDED_)
#define AFX_STDAFX_H__AA3SDCF4_2899_A4A8_78DR_123400DF0056__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN        // Exclure les en-têtes Windows rarement utilisés
#endif

// Modifiez les définitions suivantes si vous devez cibler une plate-forme avant celles spécifiées ci-dessous.
// Reportez-vous à MSDN pour obtenir les dernières informations sur les valeurs correspondantes pour les différentes plates-formes.
#ifndef WINVER                // Autorise l'utilisation des fonctionnalités spécifiques à Windows 95 et Windows NT 4 ou version ultérieure.
#define WINVER 0x0400        // Attribuez la valeur appropriée à cet élément pour cibler Windows 98 et Windows 2000 ou version ultérieure.
#endif

#ifndef _WIN32_WINNT        // Autorise l'utilisation des fonctionnalités spécifiques à Windows NT 4 ou version ultérieure.
#define _WIN32_WINNT 0x0400    // Attribuez la valeur appropriée à cet élément pour cibler Windows 2000 ou version ultérieure.
#endif

#ifndef _WIN32_WINDOWS        // Autorise l'utilisation des fonctionnalités spécifiques à Windows 98 ou version ultérieure.
#define _WIN32_WINDOWS 0x0410 // Attribuez la valeur appropriée à cet élément pour cibler Windows Me ou version ultérieure.
#endif

#ifndef _WIN32_IE            // Autorise l'utilisation des fonctionnalités spécifiques à IE 4.0 ou version ultérieure.
#define _WIN32_IE 0x0400    // Attribuez la valeur appropriée à cet élément pour cibler IE 5.0 ou version ultérieure.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS    // certains constructeurs CString seront explicites

#include <afxwin.h>         // Composants MFC principaux et standard
#include <afxext.h>         // Extensions MFC

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // Classes OLE MFC
#include <afxodlgs.h>       // Classes de boîte de dialogue OLE MFC
#include <afxdisp.h>        // Classes MFC Automation
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>            // Classes de base de données ODBC MFC
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>            // Classes de base de données DAO MFC
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>        // Prise en charge des MFC pour les contrôles communs Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>            // Prise en charge des MFC pour les contrôles communs Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxmt.h>

#include "ZAConst.h"
#include "Define.h"
#include "Message.h"
#include "Planfin.hdf"

#include "ZSrvMess.h"

// Use Objective Toolkit as a DLL
#define _SECDLL

// Stingray Objective Toolkit
#include "toolkit/secall.h"
// Objective Toolkit Resources
#include "toolkit\secres.h"

// Use Objective Views as a DLL
#define _OVDLL

// Objective Views Header Files
#include "views\OdAll.h"

// ***********************************************************
// *
// *  zForms Resources
// *
// ***********************************************************

#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"

// ***********************************************************
// *
// *  zBaseLib Resources
// *
// ***********************************************************

#include "zMediatorRes.h"

// Undefine the SubclassWindow macro
#undef SubclassWindow

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__AA3SDCF4_2899_A4A8_78DR_123400DF0056__INCLUDED_)
