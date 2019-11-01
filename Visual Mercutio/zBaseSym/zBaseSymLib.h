/****************************************************************************
 * ==> zBaseSymLib ---------------------------------------------------------*
 ****************************************************************************
 * Description : zBaseSym global linking                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zBaseSymLibH
#define zBaseSymLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zBaseSymd.lib")
        #pragma message("Automatically linking with zBaseSymd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zBaseSym.lib")
        #pragma message("Automatically linking with zBaseSym.dll")
    #endif
#endif

// resources
#ifndef __ZBASESYMRES_H__
    #include "zBaseSymRes.h"
#endif

#endif
