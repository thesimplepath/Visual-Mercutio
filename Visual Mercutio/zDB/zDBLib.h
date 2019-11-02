/****************************************************************************
 * ==> zDBLib --------------------------------------------------------------*
 ****************************************************************************
 * Description : zDBLib global linking                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zDBLibH
#define zDBLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zDBd.lib")
        #pragma message("Automatically linking with zDBd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zDB.lib")
        #pragma message("Automatically linking with zDB.dll")
    #endif
#endif

// resources
#include "zDBRes.h"

#endif
