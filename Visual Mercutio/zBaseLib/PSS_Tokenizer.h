/****************************************************************************
 * ==> PSS_Tokenizer -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a tokenizer                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TokenizerH
#define PSS_TokenizerH

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
* Tokenizer
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Tokenizer
{
    public:
        /**
        * Constructor
        *@param separatorChar - separator char
        */
        PSS_Tokenizer(const char separatorChar = ';');

        /**
        * Constructor
        *@param line - line to parse
        *@param separatorChar - separator char
        */
        PSS_Tokenizer(const CString& line, const char separatorChar = ';');

        virtual ~PSS_Tokenizer();

        /**
        * Sets the separator
        *@param separatorChar - separator char
        */
        virtual inline void SetSeparator(const char separatorChar);

        /**
        * Initializes the line to parse
        *@param line - line to parse
        */
        virtual void InitializeString(const CString& line);

        /**
        * Gets the first token
        *@param line - line to parse
        *@return the first token
        */
        virtual CString GetFirstToken(const CString& line);

        /**
        * Gets the next token
        *@return the next token
        */
        virtual CString GetNextToken();

        /**
        * Clears all the tokens
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ClearAllTokens();

        /**
        * Gets the line to parse
        *@return the line to parse
        */
        virtual CString GetString();

        /**
        * Adds a token
        *@param value - token value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddToken(const CString& value);
        virtual BOOL AddToken(int            value);
        virtual BOOL AddToken(float          value);
        virtual BOOL AddToken(double         value);

        /**
        * Adds a token if still not exists
        *@param value - token value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddUniqueToken(const CString& value);
        virtual BOOL AddUniqueToken(int            value);
        virtual BOOL AddUniqueToken(float          value);
        virtual BOOL AddUniqueToken(double         value);

        /**
        * Removes a token
        *@param value - token value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveToken(const CString& value);
        virtual BOOL RemoveToken(int            value);
        virtual BOOL RemoveToken(float          value);
        virtual BOOL RemoveToken(double         value);

        /**
        * Checks if a token exists
        *@param value - token value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL TokenExist(const CString& value);
        virtual BOOL TokenExist(int            value);
        virtual BOOL TokenExist(float          value);
        virtual BOOL TokenExist(double         value);

        /**
        * Gets a token at index
        *@param index - index
        *@param[out] value - token value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GetTokenAt(std::size_t index, CString& value);

        /**
        * Gets the token count
        *@return the token count
        */
        virtual std::size_t GetTokenCount();

        /**
        * Fills the array with tokens
        *@param[out] tokenArray - array to fill with tokens
        */
        void FillArray(CStringArray& tokenArray);

    private:
        CString m_Line;
        char    m_SeparatorChar;
        char*   m_pCurrent;
        char*   m_pNext;

        /**
        * Gets the first token
        *@return the first token
        */
        inline CString GetFirstToken();
};

//---------------------------------------------------------------------------
// PSS_Tokenizer
//---------------------------------------------------------------------------
void PSS_Tokenizer::SetSeparator(const char separatorChar)
{
    m_SeparatorChar = separatorChar;
}
//---------------------------------------------------------------------------
CString PSS_Tokenizer::GetFirstToken()
{
    m_pCurrent = m_Line.GetBuffer(m_Line.GetLength() + 2);
    m_pNext    = NULL;

    return GetNextToken();
}
//---------------------------------------------------------------------------

#endif
