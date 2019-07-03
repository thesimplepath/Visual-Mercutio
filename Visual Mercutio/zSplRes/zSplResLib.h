/****************************************************************************
 * ==> zSplResLib ----------------------------------------------------------*
 ****************************************************************************
 * Description : zSplRes library global linking                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zSplResLibH
#define zSplResLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zSplResd.lib") 
        #pragma message("Automatically linking with zSplResd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zSplRes.lib") 
        #pragma message("Automatically linking with zSplRes.dll") 
    #endif
#endif

#ifndef zSplResH
    #include "zSplRes.h"
#endif

#endif
