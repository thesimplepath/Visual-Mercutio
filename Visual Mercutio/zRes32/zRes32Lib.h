/****************************************************************************
 * ==> zRes32Lib -----------------------------------------------------------*
 ****************************************************************************
 * Description : zRes32 global linking                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zRes32LibH
#define zRes32LibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zRes32d.lib") 
        #pragma message("Automatically linking with zRes32d.dll")
    #endif

    #ifdef NDEBUG
        #pragma comment(lib, "zRes32.lib") 
        #pragma message("Automatically linking with zRes32.dll") 
    #endif
#endif

// resources
#include "zRes.h"

#endif
