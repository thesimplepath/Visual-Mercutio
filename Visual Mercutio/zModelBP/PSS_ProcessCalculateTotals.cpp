/****************************************************************************
 * ==> PSS_ProcessCalculateTotals ------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to calculates the process totals      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessCalculateTotals.h"

// processsoft
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "PSS_DoorSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "PSS_StopSymbolBP.h"
#include "PSS_DeliverableLinkSymbolBP.h"
#include "PSS_ProcedureCalculateTotals.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ProcessCalculateTotals
//---------------------------------------------------------------------------
PSS_ProcessCalculateTotals::PSS_ProcessCalculateTotals(PSS_ProcessGraphModelMdl* pModel, void* pClass) :
    PSS_ProcessNavigation(pModel, pClass),
    m_ProcedureCost(0.0),
    m_ProcedureWorkloadForecast(0.0),
    m_ProcedureCostForecast(0.0)
{}
//---------------------------------------------------------------------------
PSS_ProcessCalculateTotals::~PSS_ProcessCalculateTotals()
{}
//---------------------------------------------------------------------------
bool PSS_ProcessCalculateTotals::OnStart()
{
    m_ProcedureCost             = 0.0;
    m_ProcedureWorkloadForecast = 0.0;
    m_ProcedureCostForecast     = 0.0;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessCalculateTotals::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessCalculateTotals::OnDoorSymbol(PSS_DoorSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessCalculateTotals::OnPageSymbol(PSS_PageSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessCalculateTotals::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessCalculateTotals::OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    // initialize the procedure totals for the process
    PSS_ProcedureCalculateTotals procedureTotals(dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel()), NULL);

    if (procedureTotals.Navigate())
    {
        // the total procedure workload forecast
        pSymbol->SetProcessWorkloadForecast(procedureTotals.GetProcedureWorkloadForecast());

        // the procedure cost forecast
        pSymbol->SetProcessCostForecast(procedureTotals.GetProcedureCostForecast());

        // the HMO cost for the processes
        pSymbol->SetProcessCostHMO(procedureTotals.GetProcedureCost());
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessCalculateTotals::OnStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessCalculateTotals::OnStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessCalculateTotals::OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
