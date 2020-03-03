/****************************************************************************
 * ==> PSS_CheckValidUnit --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to check the valid units              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CheckValidUnit.h"

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
// PSS_CheckValidUnit
//---------------------------------------------------------------------------
PSS_CheckValidUnit::PSS_CheckValidUnit(PSS_ProcessGraphModelMdl* pModel, void* pClass) :
    PSS_ProcessNavigation(pModel, pClass)
{}
//---------------------------------------------------------------------------
PSS_CheckValidUnit::~PSS_CheckValidUnit()
{}
//---------------------------------------------------------------------------
bool PSS_CheckValidUnit::OnStart()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckValidUnit::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckValidUnit::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    // check if it's a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
        return true;

    // check if an unit is defined for this procedure
    if (!pSymbol->GetUnitGUID().IsEmpty())
    {
        bool error;

        // get the unit name
        const CString unitName = pSymbol->RetrieveUnitName(pSymbol->GetUnitGUID(), error);

        if (unitName.IsEmpty())
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

            // increment the error counter
            ++m_ErrorCounter;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckValidUnit::OnStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    // check if it's a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
        return true;

    // check if unit defined for procedure
    if (!pSymbol->GetUnitGUID().IsEmpty())
    {
        bool error;

        // get the unit name
        const CString unitName = pSymbol->RetrieveUnitName(pSymbol->GetUnitGUID(), error);

        if (unitName.IsEmpty())
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

            // increment the error counter
            ++m_ErrorCounter;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckValidUnit::OnStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    // check if it's a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
        return true;

    // check if an unit is defined for the procedure
    if (!pSymbol->GetUnitGUID().IsEmpty())
    {
        bool error;

        // get the unit name
        const CString unitName = pSymbol->RetrieveUnitName(pSymbol->GetUnitGUID(), error);

        if (unitName.IsEmpty())
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

            // increment the error counter
            ++m_ErrorCounter;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
