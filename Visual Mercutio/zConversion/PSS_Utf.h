/****************************************************************************
 * ==> PSS_StringConversion ------------------------------------------------*
 ****************************************************************************
 * Description : Utf8 <=> Utf16 conversion helper class                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UtfH
#define PSS_UtfH

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// std
#include <string>

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
* Utf8 <=> Utf16 conversion helper class
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Utf
{
    public:
        /**
        * Converts Utf16 string to Utf8
        *@param str - string to convert
        *@return converted string
        */
        static std::string UTF16toUTF8(const PSS_String16& src);

        /**
        * Converts Utf8 string to Utf16
        *@param str - string to convert
        *@return converted string
        */
        static PSS_String16 UTF8toUTF16(const std::string& src);
};

#endif
