/****************************************************************************
 * ==> PSS_ErrorLine -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an error line for logger                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ErrorLineH
#define PSS_ErrorLineH

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
* Error line for logger
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ErrorLine : public CString
{
    public:
        /**
        * Constructor
        *@param message - message
        *@param line - line number
        *@param error - error code
        *@param type - error type
        */
        PSS_ErrorLine(const CString& message = _T(""),
                      int            line    = -1,
                      int            error   = -1,
                      int            type    = -1);

        /**
        * Constructor
        *@param messageID - message identifier in resources
        *@param line - line number
        *@param error - error code
        *@param type - error type
        */
        PSS_ErrorLine(UINT messageID,
                      int  line  = -1,
                      int  error = -1,
                      int  type  = -1);

        /**
        * Constructor
        *@param string - string containing the error message
        */
        inline PSS_ErrorLine(const CString& string);

        /**
        * Constructor
        *@param ch - char
        *@param repeat - number of occurrences the char should be repeated
        */
        inline PSS_ErrorLine(TCHAR ch, int repeat = 1);

        /**
        * Constructor
        *@param pString - ANSI string containing the error message (convert to TCHAR)
        */
        inline PSS_ErrorLine(LPCSTR pString);

        /**
        * Constructor
        *@param pString - Unicode string containing the error message (convert to TCHAR)
        */
        inline PSS_ErrorLine(LPCWSTR pString);

        /**
        * Constructor
        *@param pCh - subset of characters from an ANSI string (converts to TCHAR)
        *@param length - char subset length
        */
        inline PSS_ErrorLine(LPCSTR pCh, int length);

        /**
        * Constructor
        *@param pCh - subset of characters from an Unicode string (converts to TCHAR)
        *@param length - char subset length
        */
        inline PSS_ErrorLine(LPCWSTR pCh, int length);

        /**
        * Constructor
        *@param pCh - unsigned characters array
        */
        inline PSS_ErrorLine(const unsigned char* pCh);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_ErrorLine(const PSS_ErrorLine& other);

        virtual inline ~PSS_ErrorLine();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ErrorLine& operator = (const PSS_ErrorLine& src);

        /**
        * Ref-counted copy operator from another CString
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline const PSS_ErrorLine& operator = (const CString& other);

        /**
        * Assignment operator, sets the string content to a single character
        *@param ch - char to set
        *@return copy of itself
        */
        inline const PSS_ErrorLine& operator = (TCHAR ch);

        /**
        * Assignment operator, sets the string content to a single character
        *@param ch - char to set
        *@return copy of itself
        */
        #ifdef _UNICODE
            inline const PSS_ErrorLine& operator = (char ch);
        #endif

        /**
        * Copy operator, copies the string content from an ANSI string (converts to TCHAR)
        *@param pString - string to copy from
        *@return copy of itself
        */
        inline const PSS_ErrorLine& operator = (LPCSTR pString);

        /**
        * Copy operator, copies the string content from an Unicode string (converts to TCHAR)
        *@param pString - string to copy from
        *@return copy of itself
        */
        inline const PSS_ErrorLine& operator = (LPCWSTR pString);

        /**
        * Copy operator, copies the string content from unsigned chars
        *@param pString - string to copy from
        *@return copy of itself
        */
        inline const PSS_ErrorLine& operator = (const unsigned char* pString);

        /**
        * Concatenation operator from another CString
        *@param string - string to concatenate from
        *@return copy of itself
        */
        inline const PSS_ErrorLine& operator += (const CString& string);

        /**
        * Concatenation operator, concatenates a single character
        *@param ch - character to concatenate
        *@return copy of itself
        */
        inline const PSS_ErrorLine& operator += (TCHAR ch);

        /**
        * Concatenation operator, concatenates an ANSI character after converting it to TCHAR
        *@param ch - character to concatenate
        *@return copy of itself
        */
        #ifdef _UNICODE
            inline const PSS_ErrorLine& operator += (char ch);
        #endif

        /**
        * Concatenation operator, concatenates an Unicode character after converting it to TCHAR
        *@param pString - string to concatenate
        *@return copy of itself
        */
        inline const PSS_ErrorLine& operator += (LPCTSTR pString);

        /**
        * Gets the error message
        *@return the error message
        */
        virtual inline CString GetErrorMessage() const;

        /**
        * Sets the error message
        *@param message - the error message
        */
        virtual inline void SetErrorMessage(const CString& message);

        /**
        * Gets the line number
        *@return the line number
        */
        virtual inline int GetLineNumber() const;

        /**
        * Sets the line number
        *@param line - the line number
        */
        virtual inline void SetLineNumber(int line);

        /**
        * Gets the error number
        *@return the error number
        */
        virtual inline int GetErrorNumber() const;

        /**
        * Sets the error number
        *@param error - the error number
        */
        virtual inline void SetErrorNumber(int error);

        /**
        * Gets the error type
        *@return the error type
        */
        virtual inline int GetErrorType() const;

        /**
        * Sets the error type
        *@param type - the error type
        */
        virtual inline void SetErrorType(int type);

    protected:
        /**
        * Builds the error string
        */
        virtual inline void BuildString();

        /**
        * Parses the error string
        */
        virtual inline void Parse();

        /**
        * Assigns the string without parsing it again. Typically used in BuildString function
        *@param str - string to assign
        */
        virtual inline void AssignString(const CString& str);

    private:
        CString m_ErrorMessage;
        int     m_LineNumber;
        int     m_ErrorNumber;
        int     m_ErrorType;
};

//---------------------------------------------------------------------------
// PSS_ErrorLine
//---------------------------------------------------------------------------
PSS_ErrorLine::PSS_ErrorLine(const CString& string) :
    CString(string)
{
    Parse();
}
//---------------------------------------------------------------------------
PSS_ErrorLine::PSS_ErrorLine(TCHAR ch, int repeat) :
    CString(ch, repeat)
{
    Parse();
}
//---------------------------------------------------------------------------
PSS_ErrorLine::PSS_ErrorLine(LPCSTR pString) :
    CString(pString)
{
    Parse();
}
//---------------------------------------------------------------------------
PSS_ErrorLine::PSS_ErrorLine(LPCWSTR pString) :
    CString(pString)
{
    Parse();
}
//---------------------------------------------------------------------------
PSS_ErrorLine::PSS_ErrorLine(LPCSTR pCh, int length) :
    CString(pCh, length)
{
    Parse();
}
//---------------------------------------------------------------------------
PSS_ErrorLine::PSS_ErrorLine(LPCWSTR pCh, int length) :
    CString(pCh, length)
{
    Parse();
}
//---------------------------------------------------------------------------
PSS_ErrorLine::PSS_ErrorLine(const unsigned char* pCh) :
    CString(pCh)
{
    Parse();
}
//---------------------------------------------------------------------------
PSS_ErrorLine::PSS_ErrorLine(const PSS_ErrorLine& other) :
    CString(other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ErrorLine::~PSS_ErrorLine()
{}
//---------------------------------------------------------------------------
const PSS_ErrorLine& PSS_ErrorLine::operator = (const CString& other)
{
    dynamic_cast<CString&>(*this) = CString::operator = (other);
    Parse();

    return *this;
};
//---------------------------------------------------------------------------
const PSS_ErrorLine& PSS_ErrorLine::operator = (TCHAR ch)
{
    dynamic_cast<CString&>(*this) = CString::operator = (ch);
    Parse();

    return *this;
}
//---------------------------------------------------------------------------
#ifdef _UNICODE
    const PSS_ErrorLine& PSS_ErrorLine::operator = (char ch)
    {
        dynamic_cast<CString&>(*this) = CString::operator = (ch);
        Parse();

        return *this;
    }
#endif
//---------------------------------------------------------------------------
const PSS_ErrorLine& PSS_ErrorLine::operator = (LPCSTR pString)
{
    dynamic_cast<CString&>(*this) = CString::operator = (pString);
    Parse();

    return *this;
}
//---------------------------------------------------------------------------
const PSS_ErrorLine& PSS_ErrorLine::operator = (LPCWSTR pString)
{
    dynamic_cast<CString&>(*this) = CString::operator = (pString);
    Parse();

    return *this;
}
//---------------------------------------------------------------------------
const PSS_ErrorLine& PSS_ErrorLine::operator = (const unsigned char* pString)
{
    dynamic_cast<CString&>(*this) = CString::operator = (pString);
    Parse();

    return *this;
}
//---------------------------------------------------------------------------
const PSS_ErrorLine& PSS_ErrorLine::operator += (const CString& string)
{
    dynamic_cast<CString&>(*this) = CString::operator = (string);
    Parse();

    return *this;
}
//---------------------------------------------------------------------------
const PSS_ErrorLine& PSS_ErrorLine::operator += (TCHAR ch)
{
    dynamic_cast<CString&>(*this) = CString::operator = (ch);
    Parse();

    return *this;
}
//---------------------------------------------------------------------------
#ifdef _UNICODE
    const PSS_ErrorLine& PSS_ErrorLine::operator += (char ch)
    {
        dynamic_cast<CString&>(*this) = CString::operator = (ch);
        Parse();

        return *this;
    }
#endif
//---------------------------------------------------------------------------
const PSS_ErrorLine& PSS_ErrorLine::operator += (LPCTSTR pString)
{
    dynamic_cast<CString&>(*this) = CString::operator = (pString);
    Parse();

    return *this;
}
//---------------------------------------------------------------------------
CString PSS_ErrorLine::GetErrorMessage() const
{
    return m_ErrorMessage;
}
//---------------------------------------------------------------------------
void PSS_ErrorLine::SetErrorMessage(const CString& message)
{
    m_ErrorMessage = message;
    BuildString();
}
//---------------------------------------------------------------------------
int PSS_ErrorLine::GetLineNumber() const
{
    return m_LineNumber;
}
//---------------------------------------------------------------------------
void PSS_ErrorLine::SetLineNumber(int line)
{
    m_LineNumber = line;
    BuildString();
}
//---------------------------------------------------------------------------
int PSS_ErrorLine::GetErrorNumber() const
{
    return m_ErrorNumber;
}
//---------------------------------------------------------------------------
void PSS_ErrorLine::SetErrorNumber(int error)
{
    m_ErrorNumber = error;
    BuildString();
}
//---------------------------------------------------------------------------
int PSS_ErrorLine::GetErrorType() const
{
    return m_ErrorType;
}
//---------------------------------------------------------------------------
void PSS_ErrorLine::SetErrorType(int type)
{
    m_ErrorType = type;
    BuildString();
}
//---------------------------------------------------------------------------
void PSS_ErrorLine::BuildString()
{}
//---------------------------------------------------------------------------
void PSS_ErrorLine::Parse()
{}
//---------------------------------------------------------------------------
void PSS_ErrorLine::AssignString(const CString& str)
{
    dynamic_cast<CString&>(*this) = CString::operator = (str);
}
//---------------------------------------------------------------------------

#endif
