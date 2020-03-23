/****************************************************************************
 * ==> zPropertyLib --------------------------------------------------------*
 ****************************************************************************
 * Description : zProperty global linking                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zPropertyLibH
#define zPropertyLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zPropertyD.lib")
        #pragma message("Automatically linking with zPropertyD.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zProperty.lib")
        #pragma message("Automatically linking with zProperty.dll")
    #endif
#endif

#endif
