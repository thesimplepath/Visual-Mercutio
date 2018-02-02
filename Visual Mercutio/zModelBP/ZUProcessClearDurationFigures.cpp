// ZUProcessClearDurationFigures.cpp: implementation of the ZUProcessClearDurationFigures class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "zModel\ProcGraphModelMdl.h"
#include "ZUProcessClearDurationFigures.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

#include "ZBBPProcedureSymbol.h"
#include "ZBDeliverableLinkSymbol.h"

// Include files for log
#include "zBaseLib\ZILog.h"
#include "zModel\ZBGenericSymbolErrorLine.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUProcessClearDurationFigures::ZUProcessClearDurationFigures(ZDProcessGraphModelMdl* pModel /*= NULL*/, void* pClass /*= NULL*/)
: ZUProcessNavigation(pModel,pClass)
{
}

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


bool ZUProcessClearDurationFigures::OnProcedureSymbol( ZBBPProcedureSymbol* pSymbol )
{
	if (pSymbol)
	{
		pSymbol->SetProcessingDuration( -1 );
		pSymbol->SetProcessingDurationMax( -1 );
		// If log and debug mode is required
		if (m_pLog && m_pLog->IsInDebugMode())
		{
			CString message;
			message.Format( IDS_DB_PROCEDURE_INC_1, pSymbol->GetSymbolName() );
			ZBGenericSymbolErrorLine e( message );
			m_pLog->AddLine( e );
		}
	}
	return true;
}

bool ZUProcessClearDurationFigures::OnDeliverableLinkSymbol( ZBDeliverableLinkSymbol* pSymbol )
{
	if (pSymbol)
	{
		pSymbol->SetCaseDuration( -1 );
		pSymbol->SetCaseDurationMax( -1 );
		// If log and debug mode is required
		if (m_pLog && m_pLog->IsInDebugMode())
		{
			CString message;
			message.Format( IDS_DB_DELIVERABLE_INC_1, pSymbol->GetSymbolName() );
			ZBGenericSymbolErrorLine e( message );
			m_pLog->AddLine( e );
		}
	}
	return true;
}

