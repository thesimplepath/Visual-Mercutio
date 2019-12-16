// ZUProcessCalculateTotals.cpp: implementation of the ZUProcessCalculateTotals class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUProcessCalculateTotals.h"

#include "ZUProcedureCalculateTotals.h"

#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"

#include "ZBBPDoorSymbol.h"
#include "ZBBPPageSymbol.h"
#include "ZBBPProcedureSymbol.h"
#include "ZBBPProcessSymbol.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"
#include "ZBDeliverableLinkSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 14 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUProcessCalculateTotals::ZUProcessCalculateTotals(PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                    void*                    pClass    /*= NULL*/ )
    : ZUProcessNavigation( pModel, pClass )
{
}

ZUProcessCalculateTotals::~ZUProcessCalculateTotals()
{
}

bool ZUProcessCalculateTotals::OnStart()
{
    m_ProcedureCost                = 0;
    m_ProcedureWorkloadForecast    = 0;
    m_ProcedureCostForecast        = 0;

    // Reset all members
    return true;
}

bool ZUProcessCalculateTotals::OnFinish()
{
    return true;
}

bool ZUProcessCalculateTotals::OnDoorSymbol( ZBBPDoorSymbol* pSymbol )
{
    return true;
}

bool ZUProcessCalculateTotals::OnPageSymbol( ZBBPPageSymbol* pSymbol )
{
    return true;
}

bool ZUProcessCalculateTotals::OnProcedureSymbol( ZBBPProcedureSymbol* pSymbol )
{
    return true;
}

bool ZUProcessCalculateTotals::OnProcessSymbol( ZBBPProcessSymbol* pSymbol )
{
    // Now initiate the procedure totals for the process
    ZUProcedureCalculateTotals ProcedureTotals( dynamic_cast<PSS_ProcessGraphModelMdl*>( pSymbol->GetChildModel() ),
                                                NULL );

    if ( ProcedureTotals.Navigate() )
    {
        // The total procedure workload forecast
        pSymbol->SetProcessWorkloadForecast( ProcedureTotals.GetProcedureWorkloadForecast() );

        // The procedure cost forecast
        pSymbol->SetProcessCostForecast( ProcedureTotals.GetProcedureCostForecast() );

        // JMR-MODIF - Le 14 mars 2006 - Ajout de la prise en charge du coût HMO pour les processus.
        pSymbol->SetProcessCost( ProcedureTotals.GetProcedureCost() );
    }

    return true;
}

bool ZUProcessCalculateTotals::OnStartSymbol( ZBBPStartSymbol* pSymbol )
{
    return true;
}

bool ZUProcessCalculateTotals::OnStopSymbol( ZBBPStopSymbol* pSymbol )
{
    return true;
}

bool ZUProcessCalculateTotals::OnDeliverableLinkSymbol( ZBDeliverableLinkSymbol* pSymbol )
{
    return true;
}
