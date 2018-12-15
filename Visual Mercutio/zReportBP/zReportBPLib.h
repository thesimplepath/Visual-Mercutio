/////////////////////////////////////////////////////////////////////////////
// zReportBPLib.h : header file
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
// <nl>Description:  ReportBPLib include file for automatic library linking
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ZREPORTBPLIB_H__
#define __ZREPORTBPLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zReportBPd.lib") 
#pragma message("Automatically linking with zReportBPd.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zReportBP.lib") 
#pragma message("Automatically linking with zReportBP.dll") 
#endif // NDEBUG
#endif // _AFXDLL

#include "zReportBPRes.h"


#endif // __ZREPORTBPLIB_H__