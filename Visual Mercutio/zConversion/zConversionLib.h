/////////////////////////////////////////////////////////////////////////////
// zConversionLib.h : header file
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         04/2002
// <nl>Description:  ConversionLib include file for automatic library linking
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ZCONVERSIONLIB_H__
#define __ZCONVERSIONLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// JMR-MODIF - Le 10 janvier 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment( lib, _T( "zConversionD.lib" ) )
#pragma message( _T( "Automatically linking with zConversionD.dll" ) )
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment( lib,_T( "zConversion.lib" ) )
#pragma message( _T( "Automatically linking with zConversion.dll" ) )
#endif // NDEBUG
#endif // _AFXDLL

#include "zConversionRes.h"

#endif // __ZCONVERSIONLIB_H__