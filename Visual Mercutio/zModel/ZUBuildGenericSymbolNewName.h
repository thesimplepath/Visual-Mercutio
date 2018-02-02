// **************************************************************************************************************
// *								  Classe ZUBuildGenericSymbolNewName										*
// **************************************************************************************************************
// * JMR-MODIF - Le 4 avril 2006 - Création de la classe ZUBuildGenericSymbolNewName.							*
// **************************************************************************************************************
// * Cette classe permet la création d'un nom valide et unique pour les symboles génériques.					*
// **************************************************************************************************************

#if !defined(AFX_ZUBuildGenericSymbolNewName_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUBuildGenericSymbolNewName_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

#include "zBaseSym\ZIBasicSymbolVisitor.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZUBuildGenericSymbolNewName : public ZIBasicSymbolVisitor
{
public:

	ZUBuildGenericSymbolNewName( const CString BaseName = _T( "" ) );
	virtual ~ZUBuildGenericSymbolNewName();

	CString GetNextAvailableSymbolName( CODModel& Model );

	/* Each concrete derived ZIBasicSymbolVisitor class
	   must implement Visit to implement the appropriate 
	   algorithm 
	   In this concrete class the Visit will check the
	   BasicSymbol passes as an argument */
	virtual bool Visit( CODComponent& Symbol );

private:

	void _GetNextAvailableSymbolName( CODModel& Model );

private:

	bool	m_Found;
	CString	m_GenericSymbolName;
	CString	m_BaseName;
};

#endif // !defined(AFX_ZUBuildSymbolNewName_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)