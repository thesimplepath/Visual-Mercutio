// ZUCheckValidUnit.cpp: implementation of the ZUCheckValidUnit class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUCheckValidUnit.h"

#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
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

// JMR-MODIF - Le 21 juillet 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUCheckValidUnit::ZUCheckValidUnit(PSS_ProcessGraphModelMdl* pModel /*= NULL*/, void* pClass /*= NULL*/)
    : ZUProcessNavigation(pModel, pClass)
{}

ZUCheckValidUnit::~ZUCheckValidUnit()
{}

bool ZUCheckValidUnit::OnStart()
{
    return true;
}

bool ZUCheckValidUnit::OnFinish()
{
    return true;
}

bool ZUCheckValidUnit::OnProcedureSymbol(ZBBPProcedureSymbol* pSymbol)
{
    // Test if it is a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
    {
        return true;
    }

    // Check if unit defined for procedure
    if (!pSymbol->GetUnitGUID().IsEmpty())
    {
        bool Error;

        // Retrieve the price defined and copy it to the symbol
        CString UnitName = pSymbol->RetrieveUnitName(pSymbol->GetUnitGUID(), Error);

        if (UnitName.IsEmpty())
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_16,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath(),
                                             -1,
                                             1);

                m_pLog->AddLine(e);
            }

            // Increment error counter
            ++m_ErrorCounter;
        }
    }

    return true;
}

bool ZUCheckValidUnit::OnStartSymbol(ZBBPStartSymbol* pSymbol)
{
    // Test if it is a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
    {
        return true;
    }

    // Check if unit defined for procedure
    if (!pSymbol->GetUnitGUID().IsEmpty())
    {
        bool Error;

        // Retrieve the price defined and copy it to the symbol
        CString UnitName = pSymbol->RetrieveUnitName(pSymbol->GetUnitGUID(), Error);

        if (UnitName.IsEmpty())
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_AL_START_INC_13,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath(),
                                             -1,
                                             1);

                m_pLog->AddLine(e);
            }

            // Increment error counter
            ++m_ErrorCounter;
        }
    }

    return true;
}

bool ZUCheckValidUnit::OnStopSymbol(ZBBPStopSymbol* pSymbol)
{
    // Test if it is a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
    {
        return true;
    }

    // Check if unit defined for procedure
    if (!pSymbol->GetUnitGUID().IsEmpty())
    {
        bool Error;

        // Retrieve the price defined and copy it to the symbol
        CString UnitName = pSymbol->RetrieveUnitName(pSymbol->GetUnitGUID(), Error);

        if (UnitName.IsEmpty())
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_AL_STOP_INC_6,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath(),
                                             -1,
                                             1);

                m_pLog->AddLine(e);
            }

            // Increment error counter
            ++m_ErrorCounter;
        }
    }

    return true;
}
