// ******************************************************************************************************
// *										  Classe ZIBasicSymbolVisitor								*
// ******************************************************************************************************
// * Cette classe est une classe abstraite permettant la construction de classes prenant en charge la	*
// * navigation dans les documents.																		*
// ******************************************************************************************************

#if !defined(AFX_ZIBASICSYMBOLVISITOR_H__5E8D98F6_0424_4AE5_B29B_0C5BB460B1CB__INCLUDED_)
#define AFX_ZIBASICSYMBOLVISITOR_H__5E8D98F6_0424_4AE5_B29B_0C5BB460B1CB__INCLUDED_

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

// ******************************************************************************************************
// *											  Forward declaration									*
// ******************************************************************************************************
// No declaration.

#ifdef _ZBASESYMEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// ******************************************************************************************************
// *										  Class ZIBasicSymbolVisitor								*
// ******************************************************************************************************
// * Define the basic interface for visiting objects implementing										*
// * the ZIBasicSymbol interface																		*
// ******************************************************************************************************

class AFX_EXT_CLASS ZIBasicSymbolVisitor
{
public:

	ZIBasicSymbolVisitor();
	virtual ~ZIBasicSymbolVisitor();

	/* Each concrete derived ZIBasicSymbolVisitor class
	   must implement Visit to implement the appropriate 
	   algorithm */
	virtual bool Visit( CODComponent& Symbol ) = 0;
};

#endif // !defined(AFX_ZIBASICSYMBOLVISITOR_H__5E8D98F6_0424_4AE5_B29B_0C5BB460B1CB__INCLUDED_)