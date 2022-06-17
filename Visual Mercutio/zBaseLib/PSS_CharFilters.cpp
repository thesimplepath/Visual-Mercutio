/****************************************************************************
 * ==> PSS_CharFilters -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides common functions to filter characters and texts   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CharFilters.h"

//---------------------------------------------------------------------------
// Class members
//---------------------------------------------------------------------------
const CString PSS_CharFilters::m_Filter =
        _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890יטךכבאגדהףעפץצםלמןתשûüח. ");
//---------------------------------------------------------------------------
// PSS_CharFilters
//---------------------------------------------------------------------------
BOOL PSS_CharFilters::DoEscape(const char c)
{
    // allow the backspace char
    if (c == 0x08)
        return FALSE;

    const std::size_t length = m_Filter.GetLength();

    // check if char is allowed
    for (std::size_t i = 0; i < length; ++i)
        if (m_Filter.GetAt(i) == c)
            return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CharFilters::FilterNumEdit(const char c)
{
    if (!std::isdigit(c) && c != '.' && c != '-' && c != '+' && c != '\'' && c != ',' && c != '%' && c != 0x08)
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CharFilters::FilterTimeEdit(const char c)
{
    if (!std::isdigit(c) && c != '.' && c != '/' && c != 0x08)
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CharFilters::FilterNumEditHistoric(const char c)
{
    if (!std::isdigit(c)	&& c != '.' && c != ',' && c != '\'' && c != '%' && c != 0x08)
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CharFilters::FilterInPlacePropItemNumberEdit(const char c)
{
    if (!std::isdigit(c) && c != '.' && c != '-' && c != '+' && c != '\'' && c != ',' && c != '%' && c != 0x08)
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_CharFilters::CheckSpaces(const CString& text)
{
    CString result           = _T("");
    BOOL    doInsertSpace    = FALSE;
    BOOL    firstCharReached = FALSE;

    const std::size_t length = text.GetLength();

    for (std::size_t i = 0; i < length; ++i)
    {
        const char c = text.GetAt(i);

        switch (c)
        {
            case ' ':
            {
                if (firstCharReached)
                    doInsertSpace = TRUE;

                break;
            }

            default:
            {
                if (doInsertSpace)
                {
                    result        += _T(" ");
                    doInsertSpace  = FALSE;
                }

                result           += c;
                firstCharReached  = TRUE;
            }
        }
    }

    return result;
}
//---------------------------------------------------------------------------
CString PSS_CharFilters::FilterText(const CString& text)
{
    CString result    = _T("");
    BOOL    charAdded = FALSE;

    const std::size_t textLength   = text.GetLength();
    const std::size_t filterLength = m_Filter.GetLength();

    for (std::size_t i = 0; i < textLength; ++i)
    {
        for (std::size_t j = 0; j < filterLength; ++j)
        {
            const char c = text.GetAt(i);

            if (m_Filter.GetAt(j) == c)
            {
                result    += c;
                charAdded  = TRUE;
            }
        }

        if (!charAdded)
            result += _T(" ");

        charAdded = FALSE;
    }

    return CheckSpaces(result);
}
//---------------------------------------------------------------------------
