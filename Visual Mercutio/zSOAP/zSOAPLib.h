/****************************************************************************
 * ==> zSOAPLib ------------------------------------------------------------*
 ****************************************************************************
 * Description : zSOAP global linking                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zSOAPLibH
#define zSOAPLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zSOAPd.lib") 
        #pragma message("Automatically linking with zSOAPd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zSOAP.lib") 
        #pragma message("Automatically linking with zSOAP.dll") 
    #endif
#endif

// resources
#include "zSOAPRes.h"

#endif
