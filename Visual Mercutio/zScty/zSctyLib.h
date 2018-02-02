/////////////////////////////////////////////////////////////////////////////
// zSctyLib.h : header file
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
// <nl>Created:		 02/2002
// <nl>Description:  zSctyLib include file for automatic library linking
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ZSCTYLIB_H__
#define __ZSCTYLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zSctyD.lib") 
#pragma message("Automatically linking with zSctyD.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zScty.lib") 
#pragma message("Automatically linking with zScty.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#include "zSctyRes.h"


#endif // __ZSCTYLIB_H__