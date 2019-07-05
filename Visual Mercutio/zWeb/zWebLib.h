/****************************************************************************
 * ==> zWebLib -------------------------------------------------------------*
 ****************************************************************************
 * Description : zWeb library global linking                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zWebLibH
#define zWebLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zWebd.lib") 
        #pragma message("Automatically linking with zWebd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zWeb.lib") 
        #pragma message("Automatically linking with zWeb.dll") 
    #endif
#endif

// resources
#ifndef zWebResH
    #include "zWebRes.h"
#endif

#endif
