/****************************************************************************
 * ==> PSS_GenericErrorLine ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic error line                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GenericErrorLineH
#define PSS_GenericErrorLineH

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
#include "PSS_ErrorLine.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Generic error line
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GenericErrorLine : public PSS_ErrorLine
{
    public:
        /**
        * Constructor
        *@param message - message
        *@param line - line number
        *@param error - error number
        *@param type - error type, 0 for warning or 1 for error
        */
        PSS_GenericErrorLine(const CString& message = "", int line = -1, int error = -1, int type = -1);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_GenericErrorLine(const PSS_GenericErrorLine& other);

        virtual ~PSS_GenericErrorLine();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_GenericErrorLine& operator = (const PSS_GenericErrorLine& other);

    protected:
        /**
        * Builds the string
        */
        virtual void BuildString();

        /**
        * Parses the line content
        */
        virtual void Parse();
};

#endif
