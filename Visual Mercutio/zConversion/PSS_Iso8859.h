/****************************************************************************
 * ==> PSS_Iso8859 ---------------------------------------------------------*
 ****************************************************************************
 * Description : ISO 8859 conversion functions                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_Iso8859H
#define PSS_Iso8859H

// change the definition of AFX_EXT... to make it import
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
* ISO 8859 conversion functions
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Iso8859
{
    public:
        /**
        * Converts ANSI string to ISO 8859
        *@param str - string to convert
        *@return converted string
        */
        static std::string ANSItoISO8859(const std::string& str);

        /**
        * Converts ISO 8859 string to ANSI
        *@param str - string to convert
        *@return converted string
        */
        static std::string ISO8859toANSI(const std::string& str);
};

#endif
