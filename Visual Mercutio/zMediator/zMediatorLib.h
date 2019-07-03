/****************************************************************************
 * ==> zMediatorLib --------------------------------------------------------*
 ****************************************************************************
 * Description : zMediator library global linking                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zMediatorLibH
#define zMediatorLibH

#if _MSC_VER >= 1000
    #pragma once
#endif

#ifndef __AFXWIN_H__
    #error 'stdafx.h' must be included before including this file for PCH
#endif

#ifdef _AFXDLL
    #ifdef _DEBUG
            #pragma comment(lib, "zMediatorD.lib") 
            #pragma message("Automatically linking with zMediatorD.dll")
        #endif
        #ifdef NDEBUG
            #pragma comment(lib, "zMediator.lib") 
            #pragma message("Automatically linking with zMediator.dll") 
    #endif
#endif

// resources
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"
#include "zMediatorRes.h"

#endif
