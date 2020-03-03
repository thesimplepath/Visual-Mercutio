/****************************************************************************
 * ==> PSS_CheckSesterceUnit -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to check a Sesterce unit              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CheckSesterceUnit.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\PSS_StartSymbolBP.h"
#include "zModelBP\PSS_StopSymbolBP.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_CheckSesterceUnit
//---------------------------------------------------------------------------
PSS_CheckSesterceUnit::PSS_CheckSesterceUnit(PSS_ProcessGraphModelMdl* pModel, void* pClass) :
    PSS_ProcessNavigation(pModel, pClass)
{}
//---------------------------------------------------------------------------
PSS_CheckSesterceUnit::~PSS_CheckSesterceUnit()
{}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceUnit::OnStart()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceUnit::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceUnit::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    // check if it's a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
        return true;

    // check if an unit is defined for the procedure
    if (!pSymbol->GetUnitGUID().IsEmpty())
    {
        bool error;

        // get the price and copy it to the symbol
        const float unitCost = pSymbol->RetrieveUnitCost(pSymbol->GetUnitGUID(), error);

        if (!error)
            pSymbol->SetUnitCost(unitCost);
        else
        {
            // show a warning message
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_15, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath());
                m_pLog->AddLine(e);
            }

            // increment the warning counter
            ++m_WarningCounter;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceUnit::OnStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    // check if it's a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
        return true;

    // check if an unit is defined for the procedure
    if (!pSymbol->GetUnitGUID().IsEmpty())
    {
        bool error;

        // get the price and copy it to the symbol
        const float unitCost = pSymbol->RetrieveUnitCost(pSymbol->GetUnitGUID(), error);

        if (!error)
            pSymbol->SetUnitCost(unitCost);
        else
        {
            // show a warning message
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_AL_START_INC_12, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath());
                m_pLog->AddLine(e);
            }

            // increment the warning counter
            ++m_WarningCounter;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceUnit::OnStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    // check if it's a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
        return true;

    // check if an unit is defined for the procedure
    if (!pSymbol->GetUnitGUID().IsEmpty())
    {
        bool error;

        // get the price and copy it to the symbol
        const float unitCost = pSymbol->RetrieveUnitCost(pSymbol->GetUnitGUID(), error);

        if (!error)
            pSymbol->SetUnitCost(unitCost);
        else
        {
            // show a warning message
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_AL_STOP_INC_5, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath());
                m_pLog->AddLine(e);
            }

            // increment the warning counter
            ++m_WarningCounter;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
