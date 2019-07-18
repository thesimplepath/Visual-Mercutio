/****************************************************************************
 * ==> zWinUtil32Lib -------------------------------------------------------*
 ****************************************************************************
 * Description : zWinUtil32 library global linking                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zWinUtil32LibH
#define zWinUtil32LibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zWinUtil32d.lib") 
        #pragma message("Automatically linking with zWinUtil32d.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zWinUtil32.lib") 
        #pragma message("Automatically linking with zWinUtil32.dll") 
    #endif
#endif

// resources
#ifndef zWinUtil32ResH
    #include "zWinUtil32Res.h"
    #define zWinUtil32ResH
#endif

#endif
