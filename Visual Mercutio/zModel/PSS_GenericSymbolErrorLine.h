/****************************************************************************
 * ==> PSS_GenericSymbolErrorLine ------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic symbol error line                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GenericSymbolErrorLineH
#define PSS_GenericSymbolErrorLineH

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
#include "zBaseLib\PSS_ErrorLine.h"

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
* Generic symbol error line
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GenericSymbolErrorLine : public PSS_ErrorLine
{
    public:
        /**
        * Constructor
        *@param message - the message
        */
        PSS_GenericSymbolErrorLine(const CString& message = _T(""));

        /**
        * Constructor
        *@param message - the message
        *@param symbolName - the symbol name
        *@param symbolPath - the symbol path
        *@param error - the error number
        *@param type - the type
        */
        PSS_GenericSymbolErrorLine(const CString& message,
                                   const CString& symbolName,
                                   const CString& symbolPath,
                                   int            error = -1,
                                   int            type  =  0);

        /**
        * Constructor
        *@param messageID - the message identifier
        *@param symbolName - the symbol name
        *@param symbolPath - the symbol path
        *@param error - the error number
        *@param type - the type
        */
        PSS_GenericSymbolErrorLine(UINT           messageID,
                                   const CString& symbolname,
                                   const CString& symbolpath,
                                   int            error = -1,
                                   int            type = 0);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_GenericSymbolErrorLine(const PSS_GenericSymbolErrorLine& other);

        virtual ~PSS_GenericSymbolErrorLine();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_GenericSymbolErrorLine& operator = (const PSS_GenericSymbolErrorLine& other);

        /**
        * Gets the symbol name
        *@return the symbol name
        */
        virtual inline CString GetSymbolName() const;

        /**
        * Sets the symbol name
        *@param value - the symbol name
        */
        virtual inline void SetSymbolName(const CString& name);

        /**
        * Gets the symbol path
        *@return the symbol path
        */
        virtual inline CString GetSymbolPath() const;

        /**
        * Sets the symbol path
        *@param value - the symbol path
        */
        virtual inline void SetSymbolPath(const CString& path);

    protected:
        /**
        * Builds a string
        */
        virtual void BuildString();

        /**
        * Parses a string
        */
        virtual void Parse();

    private:
        CString m_SymbolName;
        CString m_SymbolPath;
};

//---------------------------------------------------------------------------
// PSS_GenericSymbolErrorLine
//---------------------------------------------------------------------------
CString PSS_GenericSymbolErrorLine::GetSymbolName() const
{
    return m_SymbolName;
}
//---------------------------------------------------------------------------
void PSS_GenericSymbolErrorLine::SetSymbolName(const CString& name)
{
    m_SymbolName = name;
    BuildString();
}
//---------------------------------------------------------------------------
CString PSS_GenericSymbolErrorLine::GetSymbolPath() const
{
    return m_SymbolPath;
}
//---------------------------------------------------------------------------
void PSS_GenericSymbolErrorLine::SetSymbolPath(const CString& path)
{
    m_SymbolPath = path;
    BuildString();
}
//---------------------------------------------------------------------------

#endif
