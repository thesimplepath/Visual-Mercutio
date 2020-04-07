/****************************************************************************
 * ==> zReportWebLib -------------------------------------------------------*
 ****************************************************************************
 * Description : zReportWeb global linking                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zReportWebLibH
#define zReportWebLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zReportWebd.lib")
        #pragma message("Automatically linking with zReportWebd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zReportWeb.lib")
        #pragma message("Automatically linking with zReportWeb.dll")
    #endif
#endif

// resources
#include "zReportWeb\zReportWebRes.h"

#endif
