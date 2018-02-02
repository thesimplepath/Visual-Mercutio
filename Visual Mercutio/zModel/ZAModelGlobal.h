// ZAModelGlobal.h: interface for the ZAModelGlobal class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZAMODELGLOBAL_H__EE1AEA1E_DC05_4884_BD63_36A1EC1EEC87__INCLUDED_)
#define AFX_ZAMODELGLOBAL_H__EE1AEA1E_DC05_4884_BD63_36A1EC1EEC87__INCLUDED_

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

// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 25 décembre 2006 - Ajout des décorations unicode _T(), nettoyage du code inutile. (En commentaires)

using namespace sfl;

//@type ZBPropertyAttributesSet | An array of ZBPropertyAttributes pointers.
//@iex typedef CCArray_T<ZBPropertyAttributes*,ZBPropertyAttributes*> ZBPropertyAttributesSet;
typedef CCArray_T<ZBPropertyAttributes*, ZBPropertyAttributes*> ZBPropertyAttributesSet;

//@type ZBPropertyAttributesIterator | An iterator for ZBPropertyAttributesSet collections.
//@iex typedef Iterator_T<ZBPropertyAttributes*> ZBPropertyAttributesIterator;
typedef Iterator_T<ZBPropertyAttributes*> ZBPropertyAttributesIterator;

class AFX_EXT_CLASS ZAModelGlobal
{
public:

	ZAModelGlobal();
	virtual ~ZAModelGlobal();

	static bool LoadStateGlobalPropertyAttributes( const CString Filename )
	{
		// Only save the filename.
		m_Filename = Filename;
		return true;
	};

	static bool SaveStateGlobalPropertyAttributes( const CString Filename );

	static ZBPropertyAttributes& GetGlobalPropertyAttributes( int ObjectID );

	// JMR-MODIF - Le 31 août 2005 - Ajout de la fonction Release.
	static void Release();

private:

	static ZBPropertyAttributesSet	m_Set;

	static CString					m_Filename;
};

#endif // !defined(AFX_ZAMODELGLOBAL_H__EE1AEA1E_DC05_4884_BD63_36A1EC1EEC87__INCLUDED_)