/****************************************************************************
 * ==> PSS_CheckSesterceConsistency ----------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to check Sesterce consistency         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CheckSesterceConsistency.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_ODSymbolManipulator.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "zModelBP\PSS_DoorSymbolBP.h"
#include "zModelBP\PSS_PageSymbolBP.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zModelBP\PSS_StartSymbolBP.h"
#include "zModelBP\PSS_StopSymbolBP.h"
#include "zModelBP\PSS_DeliverableLinkSymbolBP.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_CheckSesterceConsistency
//---------------------------------------------------------------------------
PSS_CheckSesterceConsistency::PSS_CheckSesterceConsistency(PSS_ProcessGraphModelMdl* pModel, PSS_Log* pLog) :
    PSS_BasicSymbolVisitor(),
    m_pModel(pModel),
    m_pLog(pLog),
    m_ErrorCounter(0),
    m_WarningCounter(0)
{}
//---------------------------------------------------------------------------
PSS_CheckSesterceConsistency::~PSS_CheckSesterceConsistency()
{}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceConsistency::CheckModel()
{
    // initialize the counters
    m_ErrorCounter   = 0;
    m_WarningCounter = 0;

    if (m_pModel)
    {
        m_pModel->AcceptVisitor(*this);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceConsistency::Visit(CODComponent& component)
{
    CODComponent*                pComponent   = &component;
    PSS_ProcedureSymbolBP*       pProcedure   =                       dynamic_cast<PSS_ProcedureSymbolBP*>(pComponent);
    PSS_DeliverableLinkSymbolBP* pDeliverable = pProcedure   ? NULL : dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pComponent);
    PSS_DoorSymbolBP*            pDoor        = pDeliverable ? NULL : dynamic_cast<PSS_DoorSymbolBP*>(pComponent);
    PSS_PageSymbolBP*            pPage        = pDoor        ? NULL : dynamic_cast<PSS_PageSymbolBP*>(pComponent);
    PSS_ProcessSymbolBP*         pProcess     = pPage        ? NULL : dynamic_cast<PSS_ProcessSymbolBP*>(pComponent);
    PSS_StartSymbolBP*           pStart       = pProcess     ? NULL : dynamic_cast<PSS_StartSymbolBP*>(pComponent);
    PSS_StopSymbolBP*            pStop        = pStart       ? NULL : dynamic_cast<PSS_StopSymbolBP*>(pComponent);
    PSS_Symbol*                  pSymbol      = pStop        ? NULL : dynamic_cast<PSS_Symbol*>(pComponent);
    PSS_LinkSymbol*              pLink        = pSymbol      ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComponent);

    if (pProcedure)
        return CheckProcedureSymbol(pProcedure);
    else
    if (pDeliverable)
        return CheckDeliverableLinkSymbol(pDeliverable);
    else
    if (pDoor)
        return CheckDoorSymbol(pDoor);
    else
    if (pPage)
        return CheckPageSymbol(pPage);
    else
    if (pProcess)
        return CheckProcessSymbol(pProcess);
    else
    if (pStart)
        return CheckStartSymbol(pStart);
    else
    if (pStop)
        return CheckStopSymbol(pStop);
    else
    if (pSymbol)
        return CheckSymbol(pSymbol);
    else
    if (pLink)
        return CheckLink(pLink);

    // not a known symbol or not needed to be visited
    return false;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceConsistency::CheckDoorSymbol(PSS_DoorSymbolBP* pSymbol)
{
    ASSERT(pSymbol);
    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceConsistency::CheckPageSymbol(PSS_PageSymbolBP* pSymbol)
{
    ASSERT(pSymbol);
    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceConsistency::CheckProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // check if it's a local symbol
    if (!pSymbol->IsLocal())
    {
        // get the local symbol
        pSymbol = dynamic_cast<PSS_ProcedureSymbolBP*>(pSymbol->GetLocalSymbol());

        if (!pSymbol)
            return true;
    }

    // Check if unit defined for procedure
    if (pSymbol->GetUnitName().IsEmpty())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_10,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }
    else
    if (!pSymbol->GetUnitCost())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_11,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }

    // check the multiplier
    if (!pSymbol->GetMultiplier())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_12,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }

    // check if a master was defined for each combination
    const int count = pSymbol->GetCombinationCount();

    for (int i = 0; i < count; ++i)
        if (pSymbol->GetCombinationMaster(i).IsEmpty())
        {
            if (m_pLog)
            {
                CString str;
                str.Format(IDS_AL_PROCEDURE_INC_14, pSymbol->GetCombinationName(i));
                PSS_GenericSymbolErrorLine e(str, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 1);
                m_pLog->AddLine(e);
            }

            // increment the error counter
            ++m_ErrorCounter;
        }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceConsistency::CheckProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    const int count = pSymbol->GetDeliveriesCount();

    for (int i = 0; i < count; ++i)
        if (pSymbol->GetDeliveryMain(i).IsEmpty())
        {
            if (m_pLog)
            {
                CString str;
                str.Format(IDS_AL_PROCESS_INC_1, pSymbol->GetDeliveryName(i));
                PSS_GenericSymbolErrorLine e(str, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 1);
                m_pLog->AddLine(e);
            }

            // increment the error counter
            ++m_ErrorCounter;
        }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceConsistency::CheckStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // check if an unit is defined for the procedure
    if (pSymbol->GetUnitName().IsEmpty())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_START_INC_10,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }
    else
    if (!pSymbol->GetUnitCost())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_START_INC_11,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceConsistency::CheckStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // check if an unit is defined for the procedure
    if (pSymbol->GetUnitName().IsEmpty())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_STOP_INC_10,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }
    else
    if (!pSymbol->GetUnitCost())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_STOP_INC_11,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceConsistency::CheckDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // check if it's a local symbol
    if (!pSymbol->IsLocal())
    {
        // get the local symbol
        pSymbol = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pSymbol->GetLocalSymbol());

        if (!pSymbol)
            return true;
    }

    // check the quantity
    if (pSymbol->GetQuantityYear() <= 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_DELIVERABLE_INC_1,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }

    // check the output percentage
    if (pSymbol->GetOutWorkloadPercent() <= 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_DELIVERABLE_INC_4,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }

    if (pSymbol->GetOutWorkloadPercent() > 1)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_DELIVERABLE_INC_5,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceConsistency::CheckSymbol(PSS_Symbol* pSymbol)
{
    ASSERT(pSymbol);
    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSesterceConsistency::CheckLink(PSS_LinkSymbol* pLink)
{
    ASSERT(pLink);
    return true;
}
//---------------------------------------------------------------------------
