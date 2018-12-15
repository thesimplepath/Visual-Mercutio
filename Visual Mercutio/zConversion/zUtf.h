/////////////////////////////////////////////////////////////////////////////
//@doc zUtf
//@module zUtf.cpp | Header of the <c zUtf> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Gaya
// <nl>Created: 04/2002
// 
/////////////////////////////////////////////////////////////////////////////

#ifndef zutf_h
#define zutf_h 1

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "String16.h"
#include <string>

#ifdef _ZCONVERSIONEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 janvier 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS zUtf
{
public:

    static std::string UTF16toUTF8( const String16& src );
    static String16 UTF8toUTF16( const std::string& src );
};

#endif