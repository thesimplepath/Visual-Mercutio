// zWinUtil32Lib.h : header file
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

#ifndef __ZWINUTIL32LIB_H__
#define __ZWINUTIL32LIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zWinUtil32d.lib") 
#pragma message("Automatically linking with zWinUtil32d.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zWinUtil32.lib") 
#pragma message("Automatically linking with zWinUtil32.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#ifndef __ZWINUTIL32_H__
#include "zWinUtil32\zWinUtil32.h"
#endif


#endif // __ZWINUTIL32LIB_H__