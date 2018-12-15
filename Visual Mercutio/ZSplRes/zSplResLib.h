// zSplResLib.h : header file
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

#ifndef __ZSPLRESLIB_H__
#define __ZSPLRESLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zSplResd.lib") 
#pragma message("Automatically linking with zSplResd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zSplRes.lib") 
#pragma message("Automatically linking with zSplRes.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#ifndef __ZSPLRES_H__
#include "zSplRes.h"
#endif


#endif // __ZSPLRESLIB_H__