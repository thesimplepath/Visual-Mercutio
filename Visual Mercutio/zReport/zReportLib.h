/****************************************************************************
 * ==> zReportLib ----------------------------------------------------------*
 ****************************************************************************
 * Description : zReport global linking                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zReportLibH
#define zReportLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zReportd.lib")
        #pragma message("Automatically linking with zReportd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zReport.lib")
        #pragma message("Automatically linking with zReport.dll")
    #endif
#endif

// resources
#include "zReportRes.h"

#endif
