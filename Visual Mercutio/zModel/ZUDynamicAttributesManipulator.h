// ZUDynamicAttributesManipulator.h: interface for the ZUDynamicAttributesManipulator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUDYNAMICATTRIBUTESMANIPULATOR_H__2D70943F_BFF5_4D6B_B874_3DA54C957314__INCLUDED_)
#define AFX_ZUDYNAMICATTRIBUTESMANIPULATOR_H__2D70943F_BFF5_4D6B_B874_3DA54C957314__INCLUDED_

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
#include "zProperty\ZIProperties.h"

// class name mapping
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif
#ifndef PSS_Symbol
    //#define PSS_Symbol ZBSymbol
#endif
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif

// forward class declaration
class PSS_ProcessGraphModelMdl;
class ZBProperty;
class ZBDynamicPropertiesManager;
class PSS_BasicSymbol;
class PSS_Symbol;
class PSS_LinkSymbol;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
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

    static void GetCategories(PSS_ProcessGraphModelMdl*    pModel,
                              CStringArray&            StaticAttributes,
                              CStringArray&            DynamicAttributes);

    static bool AssignProperty(PSS_ProcessGraphModelMdl*    pModel,
                               ZBProperty*                pProperty,
                               CRuntimeClass*            pRTClass = NULL);

    static bool ReassignProperty(PSS_ProcessGraphModelMdl* pModel, ZBProperty* pProperty);
    static bool DeleteProperty(PSS_ProcessGraphModelMdl* pModel, ZBProperty* pProperty);
    static void ExtractUniqueAttributes(PSS_ProcessGraphModelMdl* pModel, ZBPropertySet& Set);

    static bool AssignDynamicPropertyOnSymbol(ZBDynamicPropertiesManager* pDynamicPropertiesManager,
                                              PSS_Symbol*                 pSymbol);

    static bool AssignDynamicPropertyOnSymbol(ZBDynamicPropertiesManager*    pDynamicPropertiesManager,
                                              PSS_LinkSymbol*                pSymbol);

private:

    static bool AssignDynamicPropertyOnSymbol(ZBDynamicPropertiesManager*    pDynamicPropertiesManager,
                                              PSS_BasicSymbol*                pSymbol,
                                              const CString&                ClassName);
};

#endif
