/****************************************************************************
 * ==> PSS_CharFilters -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides common functions to filter characters and texts   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CharFiltersH
#define PSS_CharFiltersH

#if _MSC_VER >= 1000
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
* Common functions to filter characters and texts
*@author Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CharFilters
{
    public:
        /**
        * Checks if the character should be escaped
        *@param c - character
        *@return TRUE if character should be escaped, otherwise FALSE
        */
        static BOOL DoEscape(const char c);

        /**
        * Filter the characters allowed by the PSS_NumEdit class
        *@param c - character
        *@return TRUE if character is allowed, otherwise false
        */
        static BOOL FilterNumEdit(const char c);

        /**
        * Filter the characters allowed by the PSS_TimeEdit class
        *@param c - character
        *@return TRUE if character is allowed, otherwise false
        */
        static BOOL FilterTimeEdit(const char c);

        /**
        * Filter the characters allowed by the PSS_NumEditHistoric class
        *@param c - character
        *@return TRUE if character is allowed, otherwise false
        */
        static BOOL FilterNumEditHistoric(const char c);

        /**
        * Filter the characters allowed by the PSS_FilterInPlacePropItemNumberEdit class
        *@param c - character
        *@return TRUE if character is allowed, otherwise false
        */
        static BOOL FilterInPlacePropItemNumberEdit(const char c);

        /**
        * Left trims the string but keep the first space
        *@param text - text to trim
        *@return trimmed text
        */
        static CString CheckSpaces(const CString& text);

        /**
        * Filters a text
        *@param text - text to filter
        *@return filtered text
        */
        static CString FilterText(const CString& text);

    private:
        static const CString m_Filter;
};

#endif
