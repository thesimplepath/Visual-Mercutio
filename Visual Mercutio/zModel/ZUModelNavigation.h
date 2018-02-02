/////////////////////////////////////////////////////////////////////////////
//@doc ZUModelNavigation
//@module ZUModelNavigation.h | Interface of the <c ZUModelNavigation> class.
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
// <nl>Created:		 06/2001
// <nl>Description:  ZUModelNavigation offers the possibility to navigate
//					 through process symbols
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUModelNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUModelNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

// Forward declaration
class ZBSymbol;
class ZBLinkSymbol;
class ZDProcessGraphModelMdl;
class ZILog;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 23 mai 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZUModelNavigation : public ZIBasicSymbolVisitor
{
public:

	ZUModelNavigation( ZDProcessGraphModelMdl* pModel = NULL, void* pClass = NULL );
	virtual ~ZUModelNavigation();

	bool Navigate( ZDProcessGraphModelMdl* pModel, void* pClass );
	bool Navigate( ZDProcessGraphModelMdl* pModel );
	bool Navigate();

	// Call-back methods
	virtual bool OnStart()
	{
		return true;
	};

	virtual bool OnFinish()
	{
		return true;
	};

	virtual bool OnSymbol( ZBSymbol* pSymbol )
	{
		return true;
	};

	virtual bool OnLink( ZBLinkSymbol* pLink )
	{
		return true;
	};

	void SetLog( ZILog* pLog )
	{
		m_pLog = pLog;
	};

	/* Each concrete derived ZIBasicSymbolVisitor class
	   must implement Visit to implement the appropriate algorithm
	   In this concrete class the Visit will On the
	   BasicSymbol passes as an argument */
	virtual bool Visit( CODComponent& Symbol );

protected:

	ZDProcessGraphModelMdl*	m_pModel;
	void*					m_pClass;
	ZILog*					m_pLog;
};

#endif // !defined(AFX_ZUModelNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)