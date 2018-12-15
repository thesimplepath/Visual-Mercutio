// zBaseSymLib.h : header file
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

#ifndef __ZBASESYMBLIB_H__
#define __ZBASESYMBLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zBaseSymd.lib") 
#pragma message("Automatically linking with zBaseSymd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zBaseSym.lib") 
#pragma message("Automatically linking with zBaseSym.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#ifndef __ZBASESYMRES_H__
#include "zBaseSymRes.h"
#endif


#endif // __ZBASESYMBLIB_H__