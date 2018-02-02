// ZUDynamicAttributesManipulator.h: interface for the ZUDynamicAttributesManipulator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUDYNAMICATTRIBUTESMANIPULATOR_H__2D70943F_BFF5_4D6B_B874_3DA54C957314__INCLUDED_)
#define AFX_ZUDYNAMICATTRIBUTESMANIPULATOR_H__2D70943F_BFF5_4D6B_B874_3DA54C957314__INCLUDED_

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

#include "zProperty\ZIProperties.h"

//////////////////////////////////////////////////////////////////////
// Forward declaration
class ZDProcessGraphModelMdl;
class ZBProperty;
class ZBDynamicPropertiesManager;
class ZIBasicSymbol;
class ZBSymbol;
class ZBLinkSymbol;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZUDynamicAttributesManipulator
{
public:

	ZUDynamicAttributesManipulator();
	virtual ~ZUDynamicAttributesManipulator();

	static void GetCategories( ZDProcessGraphModelMdl*	pModel,
							   CStringArray&			StaticAttributes,
							   CStringArray&			DynamicAttributes );

	static bool AssignProperty( ZDProcessGraphModelMdl*	pModel,
								ZBProperty*				pProperty,
								CRuntimeClass*			pRTClass	= NULL );

	static bool ReassignProperty		( ZDProcessGraphModelMdl* pModel, ZBProperty* pProperty );
	static bool DeleteProperty			( ZDProcessGraphModelMdl* pModel, ZBProperty* pProperty );
	static void ExtractUniqueAttributes	( ZDProcessGraphModelMdl* pModel, ZBPropertySet& Set );

	static bool AssignDynamicPropertyOnSymbol( ZBDynamicPropertiesManager*	pDynamicPropertiesManager,
											   ZBSymbol*					pSymbol );

	static bool AssignDynamicPropertyOnSymbol( ZBDynamicPropertiesManager*	pDynamicPropertiesManager,
											   ZBLinkSymbol*				pSymbol );

private:

	static bool AssignDynamicPropertyOnSymbol( ZBDynamicPropertiesManager*	pDynamicPropertiesManager,
											   ZIBasicSymbol*				pSymbol,
											   const CString&				ClassName );
};

#endif // !defined(AFX_ZUDYNAMICATTRIBUTESMANIPULATOR_H__2D70943F_BFF5_4D6B_B874_3DA54C957314__INCLUDED_)