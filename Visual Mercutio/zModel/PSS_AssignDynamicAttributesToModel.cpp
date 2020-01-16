/****************************************************************************
 * ==> PSS_AssignDynamicAttributesToModel ----------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which navigates through the model and *
 *               assigns the property object to symbols                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_AssignDynamicAttributesToModel.h"

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
// PSS_AssignDynamicAttributesToModel
//---------------------------------------------------------------------------
PSS_AssignDynamicAttributesToModel::PSS_AssignDynamicAttributesToModel(PSS_ProcessGraphModelMdl* pModel,
                                                                       ZBProperty*               pProperty,
                                                                       CRuntimeClass*            pRTClass,
                                                                       void*                     pClass) :
    PSS_ModelNavigation(pModel, pClass),
    m_pProperty(pProperty),
    m_pRTClass(pRTClass)
{}
//---------------------------------------------------------------------------
PSS_AssignDynamicAttributesToModel::~PSS_AssignDynamicAttributesToModel()
{}
//---------------------------------------------------------------------------
bool PSS_AssignDynamicAttributesToModel::OnStart()
{
    if (!m_pProperty)
        return false;

    // nothing else to do
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AssignDynamicAttributesToModel::OnFinish()
{
    // send it to the soap server
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AssignDynamicAttributesToModel::OnSymbol(PSS_Symbol* pSymbol)
{
    // if for the whole model or for a specific class name
    if (!m_pRTClass || (m_pRTClass && m_pRTClass->m_lpszClassName == pSymbol->GetRuntimeClass()->m_lpszClassName))
        pSymbol->GetDynamicPropertiesManager()->AddDynamicProperty(m_pProperty->Dup());

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AssignDynamicAttributesToModel::OnLink(PSS_LinkSymbol* pLink)
{
    // if for the whole model or for a specific class name
    if (!m_pRTClass || (m_pRTClass && m_pRTClass->m_lpszClassName == pLink->GetRuntimeClass()->m_lpszClassName))
        pLink->GetDynamicPropertiesManager()->AddDynamicProperty(m_pProperty->Dup());

    return true;
}
//---------------------------------------------------------------------------
