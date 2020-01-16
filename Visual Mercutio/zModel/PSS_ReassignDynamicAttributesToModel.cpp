/****************************************************************************
 * ==> PSS_ReassignDynamicAttributesToModel --------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which navigates through the model and *
 *               reassigns the property object to symbols                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ReassignDynamicAttributesToModel.h"

// processsoft
#include "zProperty\ZBDynamicProperties.h"
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ReassignDynamicAttributesToModel
//---------------------------------------------------------------------------
PSS_ReassignDynamicAttributesToModel::PSS_ReassignDynamicAttributesToModel(PSS_ProcessGraphModelMdl* pModel,
                                                                           ZBProperty*               pProperty,
                                                                           void*                     pClass)
    : PSS_ModelNavigation(pModel, pClass),
    m_pProperty(pProperty)
{}
//---------------------------------------------------------------------------
PSS_ReassignDynamicAttributesToModel::~PSS_ReassignDynamicAttributesToModel()
{}
//---------------------------------------------------------------------------
bool PSS_ReassignDynamicAttributesToModel::OnStart()
{
    if (!m_pProperty)
        return false;

    // nothing else to do
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ReassignDynamicAttributesToModel::OnFinish()
{
    // send it to the soap server
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ReassignDynamicAttributesToModel::OnSymbol(PSS_Symbol* pSymbol)
{
    // if the symbol contains the same property, delete it and assign the new one
    if (pSymbol->GetDynamicPropertiesManager()->DeleteProperty(m_pProperty))
        pSymbol->GetDynamicPropertiesManager()->AddDynamicProperty(m_pProperty->Dup());

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ReassignDynamicAttributesToModel::OnLink(PSS_LinkSymbol* pLink)
{
    // if the symbol contains the same property, delete it and assign the new one
    if (pLink->GetDynamicPropertiesManager()->DeleteProperty(m_pProperty))
        pLink->GetDynamicPropertiesManager()->AddDynamicProperty(m_pProperty->Dup());

    return true;
}
//---------------------------------------------------------------------------
