/****************************************************************************
 * ==> zModelBPLib ---------------------------------------------------------*
 ****************************************************************************
 * Description : zModelBP library global linking                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef __ZMODELBPLIB_H__
#define __ZMODELBPLIB_H__

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zModelBPd.lib")
        #pragma message("Automatically linking with zModelBPd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zModelBP.lib")
        #pragma message("Automatically linking with zModelBP.dll")
    #endif
#endif

// resources
#include "zModelBPRes.h"

#endif
