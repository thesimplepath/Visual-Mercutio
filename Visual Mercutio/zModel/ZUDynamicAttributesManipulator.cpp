// ZUDynamicAttributesManipulator.cpp: implementation of the ZUDynamicAttributesManipulator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUDynamicAttributesManipulator.h"

#include "ZBSymbol.h"
#include "PSS_LinkSymbol.h"

#include "ZUExtractCategoryAttributes.h"
#include "ZUAssignDynamicAttributesToModel.h"
#include "ZUReassignDynamicAttributesToModel.h"
#include "ZUDeleteDynamicAttributesToModel.h"
#include "ZUExtractModelAttributes.h"
#include "zBaseSym\PSS_BasicSymbol.h"
#include "zProperty\ZBDynamicPropertiesManager.h"
#include "zProperty\ZBDynamicProperties.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUDynamicAttributesManipulator::ZUDynamicAttributesManipulator()
{}

ZUDynamicAttributesManipulator::~ZUDynamicAttributesManipulator()
{}

void ZUDynamicAttributesManipulator::GetCategories(ZDProcessGraphModelMdl*    pModel,
                                                   CStringArray&            StaticAttributes,
                                                   CStringArray&            DynamicAttributes)
{
    ZUExtractCategoryAttributes extract(pModel, &StaticAttributes, &DynamicAttributes);
    extract.Navigate();
}

bool ZUDynamicAttributesManipulator::AssignProperty(ZDProcessGraphModelMdl*    pModel,
                                                    ZBProperty*                pProperty,
                                                    CRuntimeClass*                pRTClass    /*= NULL*/)
{
    ZUAssignDynamicAttributesToModel assign(pModel, pProperty, pRTClass);
    return assign.Navigate();
}

bool ZUDynamicAttributesManipulator::ReassignProperty(ZDProcessGraphModelMdl* pModel, ZBProperty* pProperty)
{
    ZUReassignDynamicAttributesToModel assign(pModel, pProperty);
    return assign.Navigate();
}

bool ZUDynamicAttributesManipulator::DeleteProperty(ZDProcessGraphModelMdl* pModel, ZBProperty* pProperty)
{
    ZUDeleteDynamicAttributesToModel assign(pModel, pProperty);
    return assign.Navigate();
}

void ZUDynamicAttributesManipulator::ExtractUniqueAttributes(ZDProcessGraphModelMdl* pModel, ZBPropertySet& Set)
{
    ZUExtractModelAttributes extract(pModel, &Set);
    extract.Navigate();
}

bool ZUDynamicAttributesManipulator::AssignDynamicPropertyOnSymbol(ZBDynamicPropertiesManager*    pDynamicPropertiesManager,
                                                                   ZBSymbol*                    pSymbol)
{
    // To use the runtime class info
    return ZUDynamicAttributesManipulator::AssignDynamicPropertyOnSymbol(pDynamicPropertiesManager,
                                                                         pSymbol,
                                                                         pSymbol->GetRuntimeClass()->m_lpszClassName);
}

bool ZUDynamicAttributesManipulator::AssignDynamicPropertyOnSymbol(ZBDynamicPropertiesManager*    pDynamicPropertiesManager,
                                                                   PSS_LinkSymbol*                pSymbol)
{
    // To use the runtime class info
    return ZUDynamicAttributesManipulator::AssignDynamicPropertyOnSymbol(pDynamicPropertiesManager,
                                                                         pSymbol,
                                                                         pSymbol->GetRuntimeClass()->m_lpszClassName);
}

bool ZUDynamicAttributesManipulator::AssignDynamicPropertyOnSymbol(ZBDynamicPropertiesManager*    pDynamicPropertiesManager,
                                                                   PSS_BasicSymbol*                pSymbol,
                                                                   const CString&                ClassName)
{
    if (!pDynamicPropertiesManager)
    {
        return false;
    }

    // Run through all dynamic properties and check if this symbol needs
    ZBDynamicPropertiesInfoIterator i(&pDynamicPropertiesManager->GetDynamicPropertiesInfoSet());

    for (_ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // If for the whole model
        // or for a specific class name
        // or for a specific symbol
        if (!pProp->m_pSelectableClass && pProp->m_SymbolRef == -1 ||
            (pProp->m_SymbolName == pSymbol->GetSymbolName()) ||
            (pProp->m_pSelectableClass && pProp->m_pSelectableClass->m_lpszClassName == ClassName))
        {
            pSymbol->GetDynamicPropertiesManager()->AddDynamicProperty(pProp->m_pProperty->Dup());
        }
    }

    return true;
}
