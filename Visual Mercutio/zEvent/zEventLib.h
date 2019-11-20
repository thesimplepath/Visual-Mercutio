/****************************************************************************
 * ==> zEventLib -----------------------------------------------------------*
 ****************************************************************************
 * Description : zEventLib global linking                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef __ZEVENTLIB_H__
#define __ZEVENTLIB_H__

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zEventd.lib")
        #pragma message("Automatically linking with zEventd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zEvent.lib")
        #pragma message("Automatically linking with zEvent.dll")
    #endif
#endif

// resources
#ifndef __ZEVTRES_H__
    #include "zEvtRes.h"
#endif

#endif
