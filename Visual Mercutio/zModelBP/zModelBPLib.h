// zModelBPLib.h : header file
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

#ifndef __ZMODELBPLIB_H__
#define __ZMODELBPLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zModelBPd.lib") 
#pragma message("Automatically linking with zModelBPd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zModelBP.lib") 
#pragma message("Automatically linking with zModelBP.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#include "zModelBPRes.h"


#endif // __ZMODELBPLIB_H__