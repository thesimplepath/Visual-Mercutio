/////////////////////////////////////////////////////////////////////////////
// zResMgrLib.h : header file
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
// <nl>Created:         10/2002
// <nl>Description:  ReportLib include file for automatic library linking
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ZRESMGRLIB_H__
#define __ZRESMGRLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zResMgrd.lib") 
#pragma message("Automatically linking with zResMgrd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zResMgr.lib") 
#pragma message("Automatically linking with zResMgr.dll") 
#endif // NDEBUG
#endif // _AFXDLL



#endif // __ZRESMGRLIB_H__