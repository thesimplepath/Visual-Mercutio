/****************************************************************************
 * ==> PSS_DynamicAttributesManipulator ------------------------------------*
 ****************************************************************************
 * Description : Provides a dynamic attributes manipulator                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DynamicAttributesManipulator.h"

// processsoft
#include "zBaseSym\PSS_BasicSymbol.h"
#include "zProperty\ZBDynamicPropertiesManager.h"
#include "zProperty\ZBDynamicProperties.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"
#include "PSS_ExtractCategoryAttributes.h"
#include "PSS_ExtractModelAttributes.h"
#include "PSS_AssignDynamicAttributesToModel.h"
#include "ZUReassignDynamicAttributesToModel.h"
#include "PSS_DeleteDynamicAttributesToModel.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_DynamicAttributesManipulator
//---------------------------------------------------------------------------
PSS_DynamicAttributesManipulator::PSS_DynamicAttributesManipulator()
{}
//---------------------------------------------------------------------------
PSS_DynamicAttributesManipulator::~PSS_DynamicAttributesManipulator()
{}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesManipulator::GetCategories(PSS_ProcessGraphModelMdl* pModel,
                                                     CStringArray&             staticAttributes,
                                                     CStringArray&             dynamicAttributes)
{
    PSS_ExtractCategoryAttributes extract(pModel, &staticAttributes, &dynamicAttributes);
    extract.Navigate();
}
//---------------------------------------------------------------------------
bool PSS_DynamicAttributesManipulator::AssignProperty(PSS_ProcessGraphModelMdl* pModel,
                                                      ZBProperty*               pProperty,
                                                      CRuntimeClass*            pRTClass)
{
    PSS_AssignDynamicAttributesToModel assign(pModel, pProperty, pRTClass);
    return assign.Navigate();
}
//---------------------------------------------------------------------------
bool PSS_DynamicAttributesManipulator::AssignDynamicPropertyOnSymbol(ZBDynamicPropertiesManager* pDynamicPropertiesManager,
                                                                     PSS_Symbol*                 pSymbol)
{
    // to use the runtime class info
    return AssignDynamicPropertyOnSymbol(pDynamicPropertiesManager, pSymbol, pSymbol->GetRuntimeClass()->m_lpszClassName);
}
//---------------------------------------------------------------------------
bool PSS_DynamicAttributesManipulator::AssignDynamicPropertyOnSymbol(ZBDynamicPropertiesManager* pDynamicPropertiesManager,
                                                                     PSS_LinkSymbol*             pSymbol)
{
    // to use the runtime class info
    return AssignDynamicPropertyOnSymbol(pDynamicPropertiesManager, pSymbol, pSymbol->GetRuntimeClass()->m_lpszClassName);
}
//---------------------------------------------------------------------------
bool PSS_DynamicAttributesManipulator::ReassignProperty(PSS_ProcessGraphModelMdl* pModel, ZBProperty* pProperty)
{
    ZUReassignDynamicAttributesToModel assign(pModel, pProperty);
    return assign.Navigate();
}
//---------------------------------------------------------------------------
bool PSS_DynamicAttributesManipulator::DeleteProperty(PSS_ProcessGraphModelMdl* pModel, ZBProperty* pProperty)
{
    PSS_DeleteDynamicAttributesToModel assign(pModel, pProperty);
    return assign.Navigate();
}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesManipulator::ExtractUniqueAttributes(PSS_ProcessGraphModelMdl* pModel, ZBPropertySet& set)
{
    PSS_ExtractModelAttributes extract(pModel, &set);
    extract.Navigate();
}
//---------------------------------------------------------------------------
bool PSS_DynamicAttributesManipulator::AssignDynamicPropertyOnSymbol(ZBDynamicPropertiesManager* pDynamicPropertiesManager,
                                                                     PSS_BasicSymbol*            pSymbol,
                                                                     const CString&              className)
{
    if (!pDynamicPropertiesManager)
        return false;

    ZBDynamicPropertiesInfoIterator it(&pDynamicPropertiesManager->GetDynamicPropertiesInfoSet());

    // iterate through all dynamic properties
    for (_ZBDynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        // if for the entire model, or for a specific class name, or for a specific symbol
        if (!pProp->m_pSelectableClass && pProp->m_SymbolRef == -1 ||
            (pProp->m_SymbolName == pSymbol->GetSymbolName())      ||
            (pProp->m_pSelectableClass && pProp->m_pSelectableClass->m_lpszClassName == className))
            pSymbol->GetDynamicPropertiesManager()->AddDynamicProperty(pProp->m_pProperty->Dup());

    return true;
}
//---------------------------------------------------------------------------
