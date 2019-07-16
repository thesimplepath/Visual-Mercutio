/****************************************************************************
 * ==> zSctyLib ------------------------------------------------------------*
 ****************************************************************************
 * Description : zScty library global linking                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zSctyLibH
#define zSctyLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zSctyD.lib")
        #pragma message("Automatically linking with zSctyD.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zScty.lib")
        #pragma message("Automatically linking with zScty.dll")
    #endif
#endif

// resources
#include "zSctyRes.h"

#endif
