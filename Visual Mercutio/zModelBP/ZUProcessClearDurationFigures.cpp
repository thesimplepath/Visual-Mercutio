// ZUProcessClearDurationFigures.cpp: implementation of the ZUProcessClearDurationFigures class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUProcessClearDurationFigures.h"

#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"

#include "ZBBPProcedureSymbol.h"
#include "ZBDeliverableLinkSymbol.h"

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

ZUProcessClearDurationFigures::ZUProcessClearDurationFigures(PSS_ProcessGraphModelMdl* pModel /*= NULL*/, void* pClass /*= NULL*/)
    : ZUProcessNavigation(pModel, pClass)
{}

ZUProcessClearDurationFigures::~ZUProcessClearDurationFigures()
{

}

bool ZUProcessClearDurationFigures::OnStart()
{
    return true;
}

bool ZUProcessClearDurationFigures::OnFinish()
{
    return true;
}


bool ZUProcessClearDurationFigures::OnProcedureSymbol(ZBBPProcedureSymbol* pSymbol)
{
    if (pSymbol)
    {
        pSymbol->SetProcessingDuration(-1);
        pSymbol->SetProcessingDurationMax(-1);
        // If log and debug mode is required
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

bool ZUProcessClearDurationFigures::OnDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol)
{
    if (pSymbol)
    {
        pSymbol->SetCaseDuration(-1);
        pSymbol->SetCaseDurationMax(-1);
        // If log and debug mode is required
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
