/****************************************************************************
 * ==> zSplashLib ----------------------------------------------------------*
 ****************************************************************************
 * Description : zSplash global header file                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zSplashLibH
#define zSplashLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib,"zSplashd.lib") 
        #pragma message("Automatically linking with zSplashd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib,"zSplash.lib") 
        #pragma message("Automatically linking with zSplash.dll") 
    #endif
#endif

#ifndef zSplashResH
    #include "zSplashRes.h"
#endif

#endif
