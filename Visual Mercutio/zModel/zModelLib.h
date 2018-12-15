// zModelLib.h : header file
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

#ifndef __ZMODELLIB_H__
#define __ZMODELLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zModeld.lib") 
#pragma message("Automatically linking with zModeld.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zModel.lib") 
#pragma message("Automatically linking with zModel.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#ifndef __ZMODELRES_H__
#include "zModelRes.h"
#endif


#endif // __ZMODELLIB_H__