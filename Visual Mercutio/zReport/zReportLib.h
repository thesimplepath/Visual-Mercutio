/////////////////////////////////////////////////////////////////////////////
// zReportLib.h : header file
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         06/2001
// <nl>Description:  ReportLib include file for automatic library linking
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ZREPORTLIB_H__
#define __ZREPORTLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zReportd.lib") 
#pragma message("Automatically linking with zReportd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zReport.lib") 
#pragma message("Automatically linking with zReport.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#include "zReportRes.h"


#endif // __ZREPORTLIB_H__