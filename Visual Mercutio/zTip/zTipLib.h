/****************************************************************************
 * ==> zTipLib -------------------------------------------------------------*
 ****************************************************************************
 * Description : zTip library global linking                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zTipLibH
#define zTipLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zTipd.lib") 
        #pragma message("Automatically linking with zTipd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zTip.lib") 
        #pragma message("Automatically linking with zTip.dll") 
    #endif
#endif

// resources
#ifndef zTipResH
    #include "zTipRes.h"
#endif

#endif
