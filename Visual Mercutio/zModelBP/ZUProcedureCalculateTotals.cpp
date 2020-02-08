// ZUProcedureCalculateTotals.cpp: implementation of the ZUProcedureCalculateTotals class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUProcedureCalculateTotals.h"

#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModelBP\PSS_DoorSymbolBP.h"
#include "zModelBP\PSS_PageSymbolBP.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zModel\PSS_UserGroupEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 14 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUProcedureCalculateTotals::ZUProcedureCalculateTotals(PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                       void*                    pClass    /*= NULL*/)
    : ZUProcessNavigation(pModel, pClass)
{}

ZUProcedureCalculateTotals::~ZUProcedureCalculateTotals()
{}

bool ZUProcedureCalculateTotals::OnStart()
{
    // Start by casting the unit name string
    ZBProcedureCalculateTotalsInformation* pInfo = static_cast<ZBProcedureCalculateTotalsInformation*>(m_pClass);

    if (pInfo)
    {
        m_UnitName = pInfo->m_UnitName;
        m_Consolidated = pInfo->m_Consolidated;
        m_pGroup = pInfo->m_pGroup;
    }
    else
    {
        m_UnitName.Empty();
        m_Consolidated = false;
        m_pGroup = NULL;
    }

    m_ProcedureCost = 0;
    m_ProcedureWorkloadForecast = 0;
    m_ProcedureCostForecast = 0;
    m_ProcedureWorkloadPerActivity = 0;
    m_ProcedureCostPerActivity = 0;

    // Reset all members
    return true;
}

bool ZUProcedureCalculateTotals::OnFinish()
{
    return true;
}

bool ZUProcedureCalculateTotals::OnDoorSymbol(PSS_DoorSymbolBP* pSymbol)
{
    return true;
}

bool ZUProcedureCalculateTotals::OnPageSymbol(PSS_PageSymbolBP* pSymbol)
{
    return true;
}

bool ZUProcedureCalculateTotals::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    // Calculate totals only for local symbols
    if (!pSymbol->IsLocal())
    {
        return true;
    }

    // If no unit specified or the same unit
    // then calculates all totals
    // Check also if consolidated is set and check if the symbol's unitname 
    // is part of the group
    if (m_UnitName.IsEmpty() ||
        m_UnitName == pSymbol->GetUnitName() ||
        (m_Consolidated && m_pGroup && m_pGroup->GroupExist(pSymbol->GetUnitName(), true)))
    {
        if ((double)pSymbol->GetProcedureCost() > 0)
        {
            m_ProcedureCost += pSymbol->GetProcedureCost();
        }

        if ((double)pSymbol->GetProcedureWorkloadForecast() > 0)
        {
            m_ProcedureWorkloadForecast += pSymbol->GetProcedureWorkloadForecast();
        }

        if ((double)pSymbol->GetProcedureCostForecast() > 0)
        {
            m_ProcedureCostForecast += pSymbol->GetProcedureCostForecast();
        }

        if ((double)pSymbol->GetProcedureWorkloadPerActivity() > 0)
        {
            m_ProcedureWorkloadPerActivity += pSymbol->GetProcedureWorkloadPerActivity();
        }

        if ((double)pSymbol->GetProcedureCostPerActivity() > 0)
        {
            m_ProcedureCostPerActivity += pSymbol->GetProcedureCostPerActivity();
        }
    }

    return true;
}

bool ZUProcedureCalculateTotals::OnProcessSymbol(ZBBPProcessSymbol* pSymbol)
{
    return true;
}

bool ZUProcedureCalculateTotals::OnStartSymbol(ZBBPStartSymbol* pSymbol)
{
    return true;
}

bool ZUProcedureCalculateTotals::OnStopSymbol(ZBBPStopSymbol* pSymbol)
{
    return true;
}

bool ZUProcedureCalculateTotals::OnDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol)
{
    return true;
}
