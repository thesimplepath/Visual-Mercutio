/****************************************************************************
 * ==> PSS_DeleteDynamicAttributesToModel ----------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which navigates through the model and *
 *               deletes the property object to all symbols                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DeleteDynamicAttributesToModel.h"

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
// PSS_DeleteDynamicAttributesToModel
//---------------------------------------------------------------------------
PSS_DeleteDynamicAttributesToModel::PSS_DeleteDynamicAttributesToModel(PSS_ProcessGraphModelMdl* pModel,
                                                                       ZBProperty*               pProperty,
                                                                       void*                     pClass) :
    ZUModelNavigation(pModel, pClass),
    m_pProperty(pProperty)
{}
//---------------------------------------------------------------------------
PSS_DeleteDynamicAttributesToModel::~PSS_DeleteDynamicAttributesToModel()
{}
//---------------------------------------------------------------------------
bool PSS_DeleteDynamicAttributesToModel::OnStart()
{
    if (!m_pProperty)
        return false;

    // nothing else to do
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeleteDynamicAttributesToModel::OnFinish()
{
    // send it to the soap server
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeleteDynamicAttributesToModel::OnSymbol(PSS_Symbol* pSymbol)
{
    // if the symbol contains the same property, delete it and assign a new one
    pSymbol->GetDynamicPropertiesManager()->DeleteProperty(m_pProperty);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeleteDynamicAttributesToModel::OnLink(PSS_LinkSymbol* pLink)
{
    // if the symbol contains the same property, delete it and assign a new one
    pLink->GetDynamicPropertiesManager()->DeleteProperty(m_pProperty);

    return true;
}
//---------------------------------------------------------------------------
