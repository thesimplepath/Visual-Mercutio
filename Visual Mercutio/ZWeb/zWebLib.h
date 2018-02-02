// zWebLib.h : header file
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

#ifndef __ZWEBLIB_H__
#define __ZWEBLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zWebd.lib") 
#pragma message("Automatically linking with zWebd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zWeb.lib") 
#pragma message("Automatically linking with zWeb.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#ifndef __ZWEBRES_H__
#include "zWebRes.h"
#endif

#endif // __ZWEBLIB_H__