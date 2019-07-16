/****************************************************************************
 * ==> zWkfLib -------------------------------------------------------------*
 ****************************************************************************
 * Description : zWkf library global linking                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef __ZWKFLIB_H__
#define __ZWKFLIB_H__

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zWkfd.lib") 
        #pragma message("Automatically linking with zWkfd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zWkf.lib") 
        #pragma message("Automatically linking with zWkf.dll") 
    #endif
#endif

// resources
#include "zWkfRes.h"

#endif
