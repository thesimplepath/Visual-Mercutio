/****************************************************************************
 * ==> zBaseLib ------------------------------------------------------------*
 ****************************************************************************
 * Description : zBaseLib library global linking                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zBaseLibH
#define zBaseLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zBaseLibd.lib") 
        #pragma message("Automatically linking with zBaseLibd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zBaseLib.lib") 
        #pragma message("Automatically linking with zBaseLib.dll") 
    #endif
#endif

// resources
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"
#include "zBaseLibRes.h"

#endif
