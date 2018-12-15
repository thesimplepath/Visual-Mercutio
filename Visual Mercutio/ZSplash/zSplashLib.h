// zSplashLib.h : header file
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

#ifndef __ZSPLASHLIB_H__
#define __ZSPLASHLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zSplashd.lib") 
#pragma message("Automatically linking with zSplashd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zSplash.lib") 
#pragma message("Automatically linking with zSplash.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#ifndef __ZSPLASHRES_H__
#include "zSplashRes.h"
#endif


#endif // __ZSPLASHLIB_H__