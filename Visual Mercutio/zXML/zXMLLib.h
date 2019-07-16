/****************************************************************************
 * ==> zXMLLib -------------------------------------------------------------*
 ****************************************************************************
 * Description : zXML library global linking                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zXMLLibH
#define zXMLLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
        #pragma comment(lib, "zXMLd.lib") 
        #pragma message("Automatically linking with zXMLd.dll")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib, "zXML.lib") 
        #pragma message("Automatically linking with zXML.dll") 
    #endif
#endif

// resources
#include "zXML\zXMLRes.h"

#endif
