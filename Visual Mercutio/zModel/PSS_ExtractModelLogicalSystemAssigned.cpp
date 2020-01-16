/****************************************************************************
 * ==> PSS_ExtractModelLogicalSystemAssigned -------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which navigates through the model and *
 *               determines which system is attributed to which symbol.     *
 *               From this list it's possible to rebuild the existing link  *
 *               hierarchy between the symbols and the logical systems      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ExtractModelLogicalSystemAssigned.h"

// processsoft
#include "PSS_SystemEntity.h"
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ExtractModelLogicalSystemAssigned
//---------------------------------------------------------------------------
PSS_ExtractModelLogicalSystemAssigned::PSS_ExtractModelLogicalSystemAssigned(PSS_ProcessGraphModelMdl* pModel,
                                                                             void*                     pClass) :
    PSS_ModelNavigation(pModel, pClass),
    m_pLogicalSystem(NULL)
{}
//---------------------------------------------------------------------------
PSS_ExtractModelLogicalSystemAssigned::~PSS_ExtractModelLogicalSystemAssigned()
{}
//---------------------------------------------------------------------------
bool PSS_ExtractModelLogicalSystemAssigned::OnStart()
{
    m_pLogicalSystem = static_cast<PSS_SystemEntity*>(m_pClass);

    if (!m_pLogicalSystem)
        return false;

    // remove all elements from the set
    m_Set.RemoveAll();

    // nothing else to do
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelLogicalSystemAssigned::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelLogicalSystemAssigned::OnSymbol(PSS_Symbol* pSymbol)
{
    if (pSymbol->ExtAppExist(m_pLogicalSystem->GetEntityName()) ||
        pSymbol->ExtAppExist(m_pLogicalSystem->GetGUID()))
        m_Set.Add(pSymbol);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelLogicalSystemAssigned::OnLink(PSS_LinkSymbol* pLink)
{
    if (pLink->ExtAppExist(m_pLogicalSystem->GetEntityName()) ||
        pLink->ExtAppExist(m_pLogicalSystem->GetGUID()))
        m_Set.Add(pLink);

    return true;
}
//---------------------------------------------------------------------------
