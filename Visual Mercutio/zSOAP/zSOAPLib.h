// zSOAPLib.h : header file
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
// <nl>Created:         03/2002
// <nl>Description:  XXXClass frame window support
//
// ==========================================================================  
// HISTORY:    
// ==========================================================================
//
//////////////////////////////////////////////////////////////////////

#ifndef __ZSOAPLIB_H__
#define __ZSOAPLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zSOAPd.lib") 
#pragma message("Automatically linking with zSOAPd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zSOAP.lib") 
#pragma message("Automatically linking with zSOAP.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#include "zSOAP\zSOAPRes.h"


#endif // __ZSOAPLIB_H__