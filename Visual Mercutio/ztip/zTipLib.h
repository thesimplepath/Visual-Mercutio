// zTipLib.h : header file
//
// Copyright © 1993-2000 Aigroz Dominique - Advanced Dedicated Software
//		mailto:dominique.aigroz@adsoft-form.com
//		http://www.adsoft-form.com
//
//
// ==========================================================================  
// HISTORY:	
// ==========================================================================
//
//////////////////////////////////////////////////////////////////////

#ifndef __ZTIPLIB_H__
#define __ZTIPLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zTipd.lib") 
#pragma message("Automatically linking with zTipd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zTip.lib") 
#pragma message("Automatically linking with zTip.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#ifndef __ZTIPRES_H__
#include "zTipRes.h"
#endif


#endif // __ZTIPLIB_H__