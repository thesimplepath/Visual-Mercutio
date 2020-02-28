/****************************************************************************
 * ==> zModelLib -----------------------------------------------------------*
 ****************************************************************************
 * Description : zModel library global linking                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef __ZMODELLIB_H__
#define __ZMODELLIB_H__

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zModeld.lib") 
        #pragma message("Automatically linking with zModeld.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zModel.lib") 
        #pragma message("Automatically linking with zModel.dll") 
    #endif
#endif

// resources
#ifndef __ZMODELRES_H__
    #include "zModelRes.h"
#endif

#endif
