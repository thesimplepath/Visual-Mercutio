/////////////////////////////////////////////////////////////////////////////
// zPropertyLib.h : header file
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
// <nl>Created:		 05/2002
// <nl>Description:  PropertyLib include file for automatic library linking
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ZPROPERTYLIB_H__
#define __ZPROPERTYLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zPropertyD.lib") 
#pragma message("Automatically linking with zPropertyD.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zProperty.lib") 
#pragma message("Automatically linking with zProperty.dll") 
#endif // NDEBUG
#endif // _AFXDLL



#endif // __ZPROPERTYLIB_H__