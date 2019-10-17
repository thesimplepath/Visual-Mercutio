/****************************************************************************
 * ==> PSS_Trace -----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides several trace functions for debugging             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

// if enable trace is defined
#ifdef _ENABLETRACE
    #ifndef _DEBUG
        // std
        #include <malloc.h>
        #include <stdio.h>
        #include <stdarg.h>
        #include <string.h>
        #include <stdlib.h>
        #include <time.h>
        #include <windows.h>
        #include <winnt.h>
        #include <assert.h>
        #include <crtdbg.h>

        // processsoft
        #include "ZAConst.h"
        #include "ZGTrace.h"

        //---------------------------------------------------------------------------
        // Serialization
        //---------------------------------------------------------------------------
        void ZGTrace(const PSTR ref, ...)
        {}
        //---------------------------------------------------------------------------
        void ZGTraceT(const PSTR ref, ...)
        {}
        //---------------------------------------------------------------------------
    #endif
#endif
