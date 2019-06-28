/****************************************************************************
 * ==> PSS_StringConversion ------------------------------------------------*
 ****************************************************************************
 * Description : String conversion helper class                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/
 
#ifndef PSS_StringConversionH
#define PSS_StringConversionH

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
#include "PSS_String16.h"

#ifdef _ZCONVERSIONEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Utf8 <=> Utf16 string conversion helper class
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StringTools
{
    public:
        /**
        * Converts a xml (ANSI7) string to string
        *@param str - string to convert
        *@return converted string
        */
        static PSS_String16 ConvertFrom(const std::string& str);

        /**
        * Converts a string to xml (ANSI7) string
        *@param str - string to convert
        *@return converted string
        */
        static std::string ConvertTo(const PSS_String16& str);

        /**
        * Converts several forbidden chars to allowed ones
        *@param str - string to convert
        *@return converted string
        *@note This function isn't very efficient. It may be used in the context of Visual Mercutio,
        *      but isn't generic, and his purpose is a little obscure
        */
        static CString ConvertSpecialChar(const CString& str);
};

#endif
