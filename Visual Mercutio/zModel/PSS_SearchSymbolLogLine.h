/****************************************************************************
 * ==> PSS_SearchSymbolLogLine ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a search symbol log line                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SearchSymbolLogLineH
#define PSS_SearchSymbolLogLineH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_GenericSymbolErrorLine.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Search symbol log line
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SearchSymbolLogLine : public PSS_GenericSymbolErrorLine
{
    public:
        PSS_SearchSymbolLogLine();

        /**
        * Constructor
        *@¼param symbolName - the symbol name
        *@¼param symbolPath - the symbol path
        *@¼param message - the message
        */
        PSS_SearchSymbolLogLine(const CString& symbolName,
                                const CString& symbolPath,
                                const CString& message = "");

        /**
        * Constructor
        *@¼param symbolName - the symbol name
        *@¼param symbolPath - the symbol path
        *@¼param messageID - the message identifier
        */
        PSS_SearchSymbolLogLine(const CString& symbolName,
                                const CString& symbolPath,
                                UINT           messageID);

        virtual ~PSS_SearchSymbolLogLine();
};

#endif
