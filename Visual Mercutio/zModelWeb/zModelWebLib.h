/****************************************************************************
 * ==> zModelWebLib --------------------------------------------------------*
 ****************************************************************************
 * Description : zModelWeb global linking                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zModelWebLibH
#define zModelWebLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zModelWebd.lib")
        #pragma message("Automatically linking with zModelWebd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zModelWeb.lib")
        #pragma message("Automatically linking with zModelWeb.dll")
    #endif
#endif

// resources
#include "zModelWeb\zModelWebRes.h"

#endif
