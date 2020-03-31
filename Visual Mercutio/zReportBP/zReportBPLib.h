/****************************************************************************
 * ==> zReportBPLib --------------------------------------------------------*
 ****************************************************************************
 * Description : zReportBP global linking                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zReportBPLibH
#define zReportBPLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zReportBPd.lib")
        #pragma message("Automatically linking with zReportBPd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zReportBP.lib")
        #pragma message("Automatically linking with zReportBP.dll")
    #endif
#endif

// resources
#include "zReportBPRes.h"

#endif
