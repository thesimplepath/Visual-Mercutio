/****************************************************************************
 * ==> PSS_Tokenizer -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a tokenizer                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_Tokenizer.h"

//---------------------------------------------------------------------------
// PSS_Tokenizer
//---------------------------------------------------------------------------
PSS_Tokenizer::PSS_Tokenizer(const char separatorChar) :
    m_SeparatorChar(separatorChar),
    m_pCurrent(NULL),
    m_pNext(NULL)
{}
//---------------------------------------------------------------------------
PSS_Tokenizer::PSS_Tokenizer(const CString& line, const char separatorChar) :
    m_SeparatorChar(separatorChar),
    m_pCurrent(NULL),
    m_pNext(NULL)
{
    InitializeString(line);
}
//---------------------------------------------------------------------------
PSS_Tokenizer::~PSS_Tokenizer()
{
    m_Line.Empty();
}
//---------------------------------------------------------------------------
void PSS_Tokenizer::InitializeString(const CString& line)
{
    m_Line = line;
}
//---------------------------------------------------------------------------
CString PSS_Tokenizer::GetFirstToken(const CString& line)
{
    m_Line = line;

    return GetFirstToken();
}
//---------------------------------------------------------------------------
CString PSS_Tokenizer::GetNextToken()
{
    if (!m_pCurrent)
    {
        m_Line.ReleaseBuffer();
        return _T("");
    }

    // locate the separator char
    m_pNext = std::strchr(m_pCurrent, m_SeparatorChar);

    if (!m_pNext)
    {
        // if still the last element into the buffer
        if (!*m_pCurrent)
        {
            m_Line.ReleaseBuffer();
            return _T("");
        }

        // copy the user
        const CString token = m_pCurrent;

        // set current to NULL
        m_pCurrent = NULL;

        return token;
    }

    // where next is found, put end of string char
    *m_pNext = 0x00;

    // copy the user
    const CString token = m_pCurrent;

    // put back the separator char
    *m_pNext = m_SeparatorChar;

    // set current to the next char after the next pointer
    m_pCurrent = ++m_pNext;

    return token;
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::ClearAllTokens()
{
    m_Line.Empty();
    return m_Line.IsEmpty();
}
//---------------------------------------------------------------------------
CString PSS_Tokenizer::GetString()
{
    m_Line.ReleaseBuffer();
    return m_Line;
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::AddToken(const CString& value)
{
    if (m_Line.IsEmpty())
        m_Line += value;
    else
    {
        m_Line += m_SeparatorChar;
        m_Line += value;
    }

    return !m_Line.IsEmpty();
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::AddToken(int value)
{
    CString str;
    str.Format(_T("%d"), value);

    return AddToken(str);
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::AddToken(float value)
{
    CString str;
    str.Format(_T("%f"), value);

    return AddToken(str);
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::AddToken(double value)
{
    CString str;
    str.Format(_T("%f"), value);

    return AddToken(str);
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::AddUniqueToken(const CString& value)
{
    // if the token doesn't exists, add it
    if (!TokenExist(value))
    {
        AddToken(value);
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::AddUniqueToken(int value)
{
    CString str;
    str.Format(_T("%d"), value);

    return AddUniqueToken(str);
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::AddUniqueToken(float value)
{
    CString str;
    str.Format(_T("%f"), value);

    return AddUniqueToken(str);
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::AddUniqueToken(double value)
{
    CString str;
    str.Format(_T("%f"), value);

    return AddUniqueToken(str);
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::RemoveToken(const CString& value)
{
    PSS_Tokenizer finalTokens(m_Line, m_SeparatorChar);
    CString       str     = GetFirstToken();
    BOOL          removed = FALSE;

    // iterate through all tokens
    while (!str.IsEmpty())
    {
        // if the same deliverable was found, sets the found flag to true
        if (str != value)
            finalTokens.AddToken(value);
        else
            removed = TRUE;

        // get the next token
        str = GetNextToken();
    }

    // replace the token line only if the token has been removed
    if (removed)
        m_Line = finalTokens.GetString();
    else
        // just release the buffer
        m_Line.ReleaseBuffer();

    return removed;
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::RemoveToken(int value)
{
    CString str;
    str.Format(_T("%d"), value);

    return RemoveToken(str);
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::RemoveToken(float value)
{
    CString str;
    str.Format(_T("%f"), value);

    return RemoveToken(str);
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::RemoveToken(double value)
{
    CString str;
    str.Format(_T("%f"), value);

    return RemoveToken(str);
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::TokenExist(const CString& value)
{
    CString str = GetFirstToken();

    // iterate through all tokens
    while (!str.IsEmpty())
    {
        // if the same deliverable was found, sets the found flag to true
        if (str == value)
        {
            m_Line.ReleaseBuffer();
            return TRUE;
        }

        // get the next token
        str = GetNextToken();
    }

    m_Line.ReleaseBuffer();
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::TokenExist(int value)
{
    CString str;
    str.Format(_T("%d"), value);

    return TokenExist(str);
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::TokenExist(float value)
{
    CString str;
    str.Format(_T("%f"), value);

    return TokenExist(str);
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::TokenExist(double value)
{
    CString str;
    str.Format(_T("%f"), value);

    return TokenExist(str);
}
//---------------------------------------------------------------------------
BOOL PSS_Tokenizer::GetTokenAt(std::size_t index, CString& value)
{
    CString     str     = GetFirstToken();
    std::size_t counter = 0;

    // iterate through all tokens
    while (!str.IsEmpty())
    {
        // if the right index was reached
        if (counter == index)
        {
            // copy the token to the value string
            value = str;
            m_Line.ReleaseBuffer();

            return TRUE;
        }

        // increment the counter
        ++counter;

        // get the next token
        str = GetNextToken();
    }

    m_Line.ReleaseBuffer();

    // return false for an invalid index
    return FALSE;
}
//---------------------------------------------------------------------------
std::size_t PSS_Tokenizer::GetTokenCount()
{
    CString     str     = GetFirstToken();
    std::size_t counter = 0;

    // iterate through all tokens
    while (!str.IsEmpty())
    {
        ++counter;

        // get the next token
        str = GetNextToken();
    }

    // release the buffer after a count
    m_Line.ReleaseBuffer();

    return counter;
}
//---------------------------------------------------------------------------
void PSS_Tokenizer::FillArray(CStringArray& tokenArray)
{
    CString str = GetFirstToken();

    // iterate through all tokens
    while (!str.IsEmpty())
    {
        tokenArray.Add(str);

        // get the next token
        str = GetNextToken();
    }
}
//---------------------------------------------------------------------------
