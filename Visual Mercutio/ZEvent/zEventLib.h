// zEventLib.h : header file
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

#ifndef __ZEVENTLIB_H__
#define __ZEVENTLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zEventd.lib") 
#pragma message("Automatically linking with zEventd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zEvent.lib") 
#pragma message("Automatically linking with zEvent.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#ifndef __ZEVTRES_H__
#include "zEvtRes.h"
#endif


#endif // __ZEVENTLIB_H__