/****************************************************************************
 * ==> zResMgrLib ----------------------------------------------------------*
 ****************************************************************************
 * Description : zResMgr library global linking                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zResMgrLibH
#define zResMgrLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zResMgrd.lib") 
        #pragma message("Automatically linking with zResMgrd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zResMgr.lib") 
        #pragma message("Automatically linking with zResMgr.dll") 
    #endif
#endif

#endif
