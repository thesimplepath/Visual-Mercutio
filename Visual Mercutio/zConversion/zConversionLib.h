/****************************************************************************
 * ==> zConversionLib ------------------------------------------------------*
 ****************************************************************************
 * Description : zConversion library global linking                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zConversionLibH
#define zConversionLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zConversionD.lib")
        #pragma message("Automatically linking with zConversionD.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zConversion.lib")
        #pragma message("Automatically linking with zConversion.dll")
    #endif
#endif

// resources
#include "zConversionRes.h"

#endif
