/****************************************************************************
 * ==> PSS_ExtractCategoryAttributes ---------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which navigates through the model and *
 *               extracts unique attribute categories                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ExtractCategoryAttributes.h"

// processsoft
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ExtractCategoryAttributes
//---------------------------------------------------------------------------
PSS_ExtractCategoryAttributes::PSS_ExtractCategoryAttributes(PSS_ProcessGraphModelMdl* pModel,
                                                             CStringArray*             pStaticArray,
                                                             CStringArray*             pDynamicArray,
                                                             void*                     pClass) :
    PSS_ModelNavigation(pModel, pClass),
    m_pDynamicArray(pDynamicArray),
    m_pStaticArray(pStaticArray)
{}
//---------------------------------------------------------------------------
PSS_ExtractCategoryAttributes::~PSS_ExtractCategoryAttributes()
{}
//---------------------------------------------------------------------------
bool PSS_ExtractCategoryAttributes::OnStart()
{
    // reset the categories array
    ResetStringsArray();

    if (m_pDynamicArray)
        m_pDynamicArray->RemoveAll();

    if (m_pStaticArray)
        m_pStaticArray->RemoveAll();

    // nothing else to do
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractCategoryAttributes::OnFinish()
{
    // send it to the soap server
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractCategoryAttributes::OnSymbol(PSS_Symbol* pSymbol)
{
    PSS_Properties::IPropertySet propSet;

    // get the property set from object
    pSymbol->FillProperties(propSet, true);

    // add the attributes to the pPublishAttribDef class
    FillAttribCategory(propSet);

    PSS_Properties::IPropertyIterator it(&propSet);

    // remove all properties
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractCategoryAttributes::OnLink(PSS_LinkSymbol* pLink)
{
    PSS_Properties::IPropertySet PropSet;

    // get the property set from object
    pLink->FillProperties(PropSet, true);

    // add the attributes to the pPublishAttribDef class
    FillAttribCategory(PropSet);

    PSS_Properties::IPropertyIterator it(&PropSet);

    // remove all properties
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    PropSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
void PSS_ExtractCategoryAttributes::FillAttribCategory(PSS_Properties::IPropertySet& propSet)
{
    PSS_Properties::IPropertyIterator it(&propSet);

    // remove all properties
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        // check if the category has already been generated
        if (!StringAlreadyGenerated(pProp->GetCategory()))
            if (pProp->IsDynamic() && m_pDynamicArray)
                m_pDynamicArray->Add(pProp->GetCategory());
            else
            if (m_pStaticArray)
                m_pStaticArray->Add(pProp->GetCategory());
}
//---------------------------------------------------------------------------
