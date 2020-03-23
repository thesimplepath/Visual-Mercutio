/****************************************************************************
 * ==> zPtyMgrLib ----------------------------------------------------------*
 ****************************************************************************
 * Description : zPtyMgr global linking                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zPtyMgrLibH
#define zPtyMgrLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zPtyMgrD.lib")
        #pragma message("Automatically linking with zPtyMgrD.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zPtyMgr.lib")
        #pragma message("Automatically linking with zPtyMgr.dll")
    #endif
#endif

// resources
#include "zPtyMgrRes.h"

#endif
