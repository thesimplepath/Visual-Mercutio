/////////////////////////////////////////////////////////////////////////////
//@doc ZUStringConversion
//@module ZUStringConversion.h | Interface of the <c ZUStringConversion> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:		 05/2002
// <nl>Description:  ZUStringConversion utility class for string conversion
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSTRINGCONVERSION_H__5D6CD631_750B_4BCB_B41A_B3FF45CA06F3__INCLUDED_)
#define AFX_ZUSTRINGCONVERSION_H__5D6CD631_750B_4BCB_B41A_B3FF45CA06F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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

class AFX_EXT_CLASS ZUStringConversion
{
public:

	ZUStringConversion();
	virtual ~ZUStringConversion();

	static CString ConvertSpecialChar( CString s );
};

#endif // !defined(AFX_ZUSTRINGCONVERSION_H__5D6CD631_750B_4BCB_B41A_B3FF45CA06F3__INCLUDED_)