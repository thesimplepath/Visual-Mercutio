// zWkfLib.h : header file
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

#ifndef __ZWKFLIB_H__
#define __ZWKFLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zWkfd.lib") 
#pragma message("Automatically linking with zWkfd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zWkf.lib") 
#pragma message("Automatically linking with zWkf.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#include "zWkfRes.h"


#endif // __ZWKFLIB_H__