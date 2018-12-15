// zBaseLib.h : header file
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

#ifndef __ZBASELIB_H__
#define __ZBASELIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zBaseLibd.lib") 
#pragma message("Automatically linking with zBaseLibd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zBaseLib.lib") 
#pragma message("Automatically linking with zBaseLib.dll") 
#endif // NDEBUG
#endif // _AFXDLL

// ***********************************************************
// *
// *  zForms Resources
// *
// ***********************************************************

#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"

// ***********************************************************
// *
// *  zBaseLib Resources
// *
// ***********************************************************

#include "zBaseLibRes.h"

#endif // __ZRES32LIB_H__