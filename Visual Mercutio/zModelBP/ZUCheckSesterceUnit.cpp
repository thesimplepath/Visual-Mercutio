// ZUCheckSesterceUnit.cpp: implementation of the ZUCheckSesterceUnit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUCheckSesterceUnit.h"

#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\PSS_StartSymbolBP.h"
#include "zModelBP\ZBBPStopSymbol.h"

#include "zModel\PSS_UserGroupEntity.h"

// Include files for log
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUCheckSesterceUnit::ZUCheckSesterceUnit(PSS_ProcessGraphModelMdl* pModel /*= NULL*/, void* pClass /*= NULL*/)
    : ZUProcessNavigation(pModel, pClass)
{}

ZUCheckSesterceUnit::~ZUCheckSesterceUnit()
{

}

bool ZUCheckSesterceUnit::OnStart()
{
    return true;
}

bool ZUCheckSesterceUnit::OnFinish()
{
    return true;
}

bool ZUCheckSesterceUnit::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    // Test if it is a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
        return true;
    // Check if unit defined for procedure
    if (!pSymbol->GetUnitGUID().IsEmpty())
    {
        bool Error;
        // Retrieve the price defined and copy it to the symbol
        float UnitCost = pSymbol->RetrieveUnitCost(pSymbol->GetUnitGUID(), Error);
        if (!Error)
            pSymbol->SetUnitCost(UnitCost);
        else
        {
            // Display warning message
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_15, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath());
                m_pLog->AddLine(e);
            }
            // Increment warning counter
            ++m_WarningCounter;
        }
    }
    return true;
}
bool ZUCheckSesterceUnit::OnStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    // Test if it is a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
        return true;
    // Check if unit defined for procedure
    if (!pSymbol->GetUnitGUID().IsEmpty())
    {
        bool Error;
        // Retrieve the price defined and copy it to the symbol
        float UnitCost = pSymbol->RetrieveUnitCost(pSymbol->GetUnitGUID(), Error);
        if (!Error)
            pSymbol->SetUnitCost(UnitCost);
        else
        {
            // Display warning message
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_AL_START_INC_12, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath());
                m_pLog->AddLine(e);
            }
            // Increment warning counter
            ++m_WarningCounter;
        }
    }
    return true;
}
bool ZUCheckSesterceUnit::OnStopSymbol(ZBBPStopSymbol* pSymbol)
{
    // Test if it is a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
        return true;
    // Check if unit defined for procedure
    if (!pSymbol->GetUnitGUID().IsEmpty())
    {
        bool Error;
        // Retrieve the price defined and copy it to the symbol
        float UnitCost = pSymbol->RetrieveUnitCost(pSymbol->GetUnitGUID(), Error);
        if (!Error)
            pSymbol->SetUnitCost(UnitCost);
        else
        {
            // Display warning message
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_AL_STOP_INC_5, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath());
                m_pLog->AddLine(e);
            }
            // Increment warning counter
            ++m_WarningCounter;
        }
    }
    return true;
}
