// zReportWebLib.h : header file
//
// Copyright © 1993-2000 Jean-Milost Reymond - ProcessSoft
//		http://www.processsoft.com
//
//
// ==========================================================================  
// HISTORY:	
// ==========================================================================
//
//////////////////////////////////////////////////////////////////////

#ifndef __ZREPORTWEBLIB_H__
#define __ZREPORTWEBLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zReportWebd.lib") 
#pragma message("Automatically linking with zReportWebd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zReportWeb.lib") 
#pragma message("Automatically linking with zReportWeb.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#include "zReportWeb\zReportWebRes.h"

#endif // __ZREPORTWEBLIB_H__