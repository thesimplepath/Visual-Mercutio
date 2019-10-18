/****************************************************************************
 * ==> PSS_Trace -----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides several trace functions for debugging             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TraceH
#define PSS_TraceH

// if enable trace is defined
#ifdef _ENABLETRACE
    #ifndef _DEBUG
        // for global APIs
        #ifndef AFX_API_EXPORT
            #define AFX_API_EXPORT __declspec(dllexport)
        #endif

        #ifndef AFX_API_IMPORT
            #define AFX_API_IMPORT __declspec(dllimport)
        #endif

        // change the definition of AFX_EXT... to make it import
        #undef AFX_EXT_API
        #define AFX_EXT_API AFX_API_IMPORT
            #ifdef _ZBASELIBEXPORT
                // put the values back to make AFX_EXT_CLASS export again
                #undef AFX_EXT_API
                #define AFX_EXT_API AFX_API_EXPORT
            #endif

            #ifdef __cplusplus
                extern "C"
                {
            #endif
                    /**
                    * Traces a debug message
                    *@param pMsg - message to trace
                    *@param ... - additional values
                    */
                    AFX_EXT_API void ZGTrace (const PSTR pMsg, ...);
                    AFX_EXT_API void ZGTraceT(const PSTR pMsg, ...);
            #ifdef __cplusplus
                }
            #endif

            #ifdef TRACE
                #undef TRACE
            #endif

            #define TRACE(xxx) ZGTrace(xxx)

            #ifdef TRACET
                #undef TRACET
            #endif

            #define TRACET( xxx ) ZGTraceT( xxx )
        #endif
    #endif
#endif
