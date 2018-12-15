// zRes32Lib.h : header file
//
// Copyright © 1993-2000 Aigroz Dominique - Advanced Dedicated Software
//        mailto:dominique.aigroz@adsoft-form.com
//        http://www.adsoft-form.com
//
//
// ==========================================================================  
// HISTORY:    
// ==========================================================================
//
//////////////////////////////////////////////////////////////////////

#ifndef __ZRES32LIB_H__
#define __ZRES32LIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zRes32d.lib") 
#pragma message("Automatically linking with zRes32d.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zRes32.lib") 
#pragma message("Automatically linking with zRes32.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#ifndef __ZRES_H__
#include "zRes.h"
#endif


#endif // __ZRES32LIB_H__