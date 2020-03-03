/****************************************************************************
 * ==> PSS_ProcessClearDurationFigures -------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to clear the process duration figures *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessClearDurationFigures.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_DeliverableLinkSymbolBP.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ProcessClearDurationFigures
//---------------------------------------------------------------------------
PSS_ProcessClearDurationFigures::PSS_ProcessClearDurationFigures(PSS_ProcessGraphModelMdl* pModel, void* pClass) :
    PSS_ProcessNavigation(pModel, pClass)
{}
//---------------------------------------------------------------------------
PSS_ProcessClearDurationFigures::~PSS_ProcessClearDurationFigures()
{}
//---------------------------------------------------------------------------
bool PSS_ProcessClearDurationFigures::OnStart()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessClearDurationFigures::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessClearDurationFigures::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    if (pSymbol)
    {
        pSymbol->SetProcessingDuration(-1);
        pSymbol->SetProcessingDurationMax(-1);

        // can log and debug mode is required?
        if (m_pLog && m_pLog->IsInDebugMode())
        {
            CString message;
            message.Format(IDS_DB_PROCEDURE_INC_1, pSymbol->GetSymbolName());
            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessClearDurationFigures::OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
{
    if (pSymbol)
    {
        pSymbol->SetCaseDuration(-1);
        pSymbol->SetCaseDurationMax(-1);

        // can log and debug mode is required?
        if (m_pLog && m_pLog->IsInDebugMode())
        {
            CString message;
            message.Format(IDS_DB_DELIVERABLE_INC_1, pSymbol->GetSymbolName());
            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
