/****************************************************************************
 * ==> PSS_ProcedureCalculateTotals ----------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to calculates the procedure totals    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcedureCalculateTotals.h"

// processsoft
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "PSS_DoorSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "PSS_StopSymbolBP.h"
#include "PSS_DeliverableLinkSymbolBP.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ProcedureCalculateTotals::IInfo
//---------------------------------------------------------------------------
PSS_ProcedureCalculateTotals::IInfo::IInfo(const CString&       unitName,
                                           bool                 consolidated,
                                           PSS_UserGroupEntity* pGroup) :
    m_pGroup(pGroup),
    m_UnitName(unitName),
    m_Consolidated(consolidated)
{}
//---------------------------------------------------------------------------
PSS_ProcedureCalculateTotals::IInfo::~IInfo()
{}
//---------------------------------------------------------------------------
// PSS_ProcedureCalculateTotals
//---------------------------------------------------------------------------
PSS_ProcedureCalculateTotals::PSS_ProcedureCalculateTotals(PSS_ProcessGraphModelMdl* pModel, void* pClass) :
    PSS_ProcessNavigation(pModel, pClass),
    m_pGroup(NULL),
    m_ProcedureWorkloadPerActivity(0.0),
    m_ProcedureCostPerActivity(0.0),
    m_Consolidated(false)
{}
//---------------------------------------------------------------------------
PSS_ProcedureCalculateTotals::~PSS_ProcedureCalculateTotals()
{}
//---------------------------------------------------------------------------
bool PSS_ProcedureCalculateTotals::OnStart()
{
    IInfo* pInfo = static_cast<IInfo*>(m_pClass);

    if (pInfo)
    {
        m_pGroup       = pInfo->m_pGroup;
        m_UnitName     = pInfo->m_UnitName;
        m_Consolidated = pInfo->m_Consolidated;
    }
    else
    {
        m_pGroup       = NULL;
        m_UnitName.Empty();
        m_Consolidated = false;
    }

    m_ProcedureCost                = 0;
    m_ProcedureWorkloadForecast    = 0;
    m_ProcedureCostForecast        = 0;
    m_ProcedureWorkloadPerActivity = 0.0;
    m_ProcedureCostPerActivity     = 0.0;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureCalculateTotals::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureCalculateTotals::OnDoorSymbol(PSS_DoorSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureCalculateTotals::OnPageSymbol(PSS_PageSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureCalculateTotals::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    // calculate totals only for local symbols
    if (!pSymbol->IsLocal())
        return true;

    // if no unit defined or if the same unit, calculate all totals. Check also if consolidated
    // is set and check if the symbol unit name belongs to the group
    if (m_UnitName.IsEmpty() || m_UnitName == pSymbol->GetUnitName() ||
       (m_Consolidated && m_pGroup && m_pGroup->GroupExist(pSymbol->GetUnitName(), true)))
    {
        if (double(pSymbol->GetProcedureCost()) > 0.0)
            m_ProcedureCost += pSymbol->GetProcedureCost();

        if (double(pSymbol->GetProcedureWorkloadForecast()) > 0.0)
            m_ProcedureWorkloadForecast += pSymbol->GetProcedureWorkloadForecast();

        if (double(pSymbol->GetProcedureCostForecast()) > 0.0)
            m_ProcedureCostForecast += pSymbol->GetProcedureCostForecast();

        if (double(pSymbol->GetProcedureWorkloadPerActivity()) > 0.0)
            m_ProcedureWorkloadPerActivity += pSymbol->GetProcedureWorkloadPerActivity();

        if (double(pSymbol->GetProcedureCostPerActivity()) > 0.0)
            m_ProcedureCostPerActivity += pSymbol->GetProcedureCostPerActivity();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureCalculateTotals::OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureCalculateTotals::OnStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureCalculateTotals::OnStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureCalculateTotals::OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
