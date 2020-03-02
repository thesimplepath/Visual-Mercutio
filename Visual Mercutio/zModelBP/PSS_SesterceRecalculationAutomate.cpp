/****************************************************************************
 * ==> PSS_SesterceRecalculationAutomate -----------------------------------*
 ****************************************************************************
 * Description : Provides the Sesterce recalculation automate               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SesterceRecalculationAutomate.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_ODSymbolManipulator.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "zWkf\PSS_StateMachine.h"
#include "PSS_CheckSesterceConsistency.h"
#include "PSS_CheckSesterceUnit.h"
#include "ZUProcessCalculateTotals.h"
#include "PSS_DoorSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "PSS_StopSymbolBP.h"
#include "PSS_DeliverableLinkSymbolBP.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_SesterceRecalculationAutomate
//---------------------------------------------------------------------------
PSS_SesterceRecalculationAutomate::PSS_SesterceRecalculationAutomate(PSS_ProcessGraphModelMdl* pModel, PSS_Log* pLog) :
    PSS_AutomateBP(pModel, pLog)
{}
//---------------------------------------------------------------------------
PSS_SesterceRecalculationAutomate::~PSS_SesterceRecalculationAutomate()
{}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnStart(PSS_Log* pLog)
{
    const bool result = PSS_AutomateBP::OnStart(pLog);

    // can log?
    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_START_SESTERCESCALCULATION);
        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    // perform a deep check before running the model calculation
    PSS_CheckSesterceConsistency checkConsistency(m_pModel, pLog);
    checkConsistency.CheckModel();

    // assign the error and warning counters
    SetErrorCounter  (checkConsistency.GetErrorCounter());
    SetWarningCounter(checkConsistency.GetWarningCounter());

    PSS_ProcessGraphModelMdl* pProcessGraphModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pModel);

    if (pProcessGraphModel && pProcessGraphModel->MainUserGroupIsValid())
    {
        // perform an unit check and assignement before running the model calculation
        PSS_CheckSesterceUnit checkUnit(m_pModel);
        checkUnit.SetLog(pLog);
        checkUnit.Navigate();

        // assign the error and warning counters
        SetErrorCounter  (GetErrorCounter()   + checkUnit.GetErrorCounter());
        SetWarningCounter(GetWarningCounter() + checkUnit.GetWarningCounter());
    }
    else
    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_USERGROUP_NOTINLINE);
        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    // don't continue if an error occurred
    if (checkConsistency.GetErrorCounter() > 0)
        return false;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnStop(PSS_Log* pLog)
{
    // can log?
    if (pLog)
    {
        CString message;
        message.Format(IDS_AL_START_PROCESSCALCULATION, m_pModel->GetModelName());
        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    // at the model calculation end, calculate the process forecast values
    ZUProcessCalculateTotals processCalculateTotals(m_pModel, NULL);
    processCalculateTotals.Navigate();

    // can log?
    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_STOP_PROCESSCALCULATION);
        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    return PSS_AutomateBP::OnStop(pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnPause(PSS_Log* pLog)
{
    return PSS_AutomateBP::OnPause(pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnResume(PSS_Log* pLog)
{
    return PSS_AutomateBP::OnResume(pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnObjectIsFinished(PSS_StateObject*  pState,
                                                           PSS_StateMachine* pStateMachine,
                                                           PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnObjectIsFinished(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnObjectIsPaused(PSS_StateObject*  pState,
                                                         PSS_StateMachine* pStateMachine,
                                                         PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnObjectIsPaused(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnObjectIsWaitingForOtherLinks(PSS_StateObject*  pState,
                                                                       PSS_StateMachine* pStateMachine,
                                                                       PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnObjectIsWaitingForOtherLinks(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnBeforeRequestMoveForward(PSS_StateObject*  pState,
                                                                   PSS_StateMachine* pStateMachine,
                                                                   PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnBeforeRequestMoveForward(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnNextSymbolAfterMoveForward(PSS_StateObject*  pState,
                                                                     PSS_StateMachine* pStateMachine,
                                                                     PSS_Log*          pLog)
{
    if (!PSS_AutomateBP::OnNextSymbolAfterMoveForward(pState, pStateMachine, pLog))
        return false;

    if (!pState)
        return true;

    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pState->GetSymbol());

    if (!pSymbol)
        return true;

    #ifdef _DEBUG
        TRACE1(_T("OnNextSymbolAfterMoveForward - Symbol in the stack is %s\n"), pSymbol->GetSymbolName());
    #endif

    PSS_ProcedureSymbolBP* pProcedure =                     dynamic_cast<PSS_ProcedureSymbolBP*>(pState->GetSymbol());
    PSS_PageSymbolBP*      pPage      = pProcedure ? NULL : dynamic_cast<PSS_PageSymbolBP*>(pState->GetSymbol());
    PSS_DoorSymbolBP*      pDoor      = pPage      ? NULL : dynamic_cast<PSS_DoorSymbolBP*>(pState->GetSymbol());
    PSS_StopSymbolBP*      pStop      = pDoor      ? NULL : dynamic_cast<PSS_StopSymbolBP*>(pState->GetSymbol());

    // found the symbol and the link should be found. Check if an entering up link may be found.
    // Now check if a procedure, a page, a door or a stop symbol exists. If yes:
    // 1. Calculate the procedure activation of the last stacked procedure
    // 2. The deliverable quantity
    // 3. The deliverable workload forecast
    // 4. The deliverable cost
    // 5. The procedure cost
    // 6. The procedure forecast cost
    // 7. The procedure cost per activity
    if (pProcedure || pPage || pDoor || pStop)
    {
        TRACE1(_T("OnNextSymbolAfterMoveForward - Current symbol is %s\n"), pSymbol->GetSymbolName());

        // normally should contain only one link
        if (!pState->GetStateLinkCount())
            return false;

        // get the object before the current one from the state machine
        PSS_StateObject* pStateObjectBefore = pStateMachine->PopStateObjectNoRemove(1);

        if (!pStateObjectBefore)
            return false;

        // not necessarily an error so return true
        if (!pStateObjectBefore->GetSymbol())
        {
            TRACE(_T("OnNextSymbolAfterMoveForward - No object before\n"));
            return true;
        }

        PSS_ProcedureSymbolBP* pProcedureBefore = dynamic_cast<PSS_ProcedureSymbolBP*>(pStateObjectBefore->GetSymbol());

        // check the object before
        if (pProcedureBefore)
        {
            PSS_ProcedureSymbolBP* pLocalProcedureBefore = NULL;

            // check if it's a local symbol
            if (!pProcedureBefore->IsLocal())
            {
                // get the local symbol
                pLocalProcedureBefore = dynamic_cast<PSS_ProcedureSymbolBP*>(pProcedureBefore->GetLocalSymbol());

                if (!pLocalProcedureBefore)
                    return false;

                TRACE1(_T("OnNextSymbolAfterMoveForward - Get local procedure %s\n"), pLocalProcedureBefore->GetSymbolName());
            }

            TRACE1(_T("OnNextSymbolAfterMoveForward: procedure before is %s\n"), pProcedureBefore->GetSymbolName());

            // iterate through all links and calculate their quantities
            for (std::size_t index = 0; index < pState->GetStateLinkCount(); ++index)
            {
                PSS_StateLink* pStateLink = pState->GetStateLinkAt(index);

                if (!pStateLink || !pStateLink->GetLinkSymbol())
                    return false;

                PSS_DeliverableLinkSymbolBP* pDeliverable =
                        dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pStateLink->GetLinkSymbol());

                // check if a deliverable was found
                if (pDeliverable)
                {
                    TRACE1(_T("OnNextSymbolAfterMoveForward: deliverable in the stack%s\n"), pDeliverable->GetSymbolName());

                    // check if it's a local symbol
                    if (!pDeliverable->IsLocal())
                    {
                        // get the local symbol
                        pDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pDeliverable->GetLocalSymbol());

                        if (!pDeliverable)
                            return false;

                        TRACE1(_T("OnNextSymbolAfterMoveForward: retrieve local deliverable %s\n"), pDeliverable->GetSymbolName());
                    }

                    PSS_AnnualNumberPropertiesBP qValue;

                    // if the quantity is not locked
                    if (!pDeliverable->GetLockQuantityYear())
                    {
                        if (pLocalProcedureBefore)
                            qValue = pLocalProcedureBefore->GetProcedureActivation() *
                                     double(pLocalProcedureBefore->GetMultiplier());
                        else
                            qValue = pProcedureBefore->GetProcedureActivation() * double(pProcedureBefore->GetMultiplier());

                        qValue *= double(pDeliverable->GetOutWorkloadPercent());
                    }
                    else
                    {
                        qValue = pDeliverable->GetQuantity();

                        // can log?
                        if (pLog)
                        {
                            PSS_GenericSymbolErrorLine e(IDS_AL_DELIV_QUANTITY_LOCKED,
                                                         pDeliverable->GetSymbolName(),
                                                         pDeliverable->GetAbsolutePath());
                            pLog->AddLine(e);
                        }

                        IncrementWarningCounter();
                    }

                    // check if the equalizer should be forced
                    if (pDeliverable->GetForceEqualizer())
                    {
                        pDeliverable->SetQuantityUsingOriginalEqualizer(qValue);

                        // if can log, notify about forcing the equalizer
                        if (pLog)
                        {
                            PSS_GenericSymbolErrorLine e(IDS_AL_DELIV_QUANTITY_FORCED,
                                                         pDeliverable->GetSymbolName(),
                                                         pDeliverable->GetAbsolutePath());
                            pLog->AddLine(e);
                        }

                        IncrementWarningCounter();
                    }
                    else
                        // if the equalizer should not be forced
                        pDeliverable->SetQuantity(qValue);

                    // if can log and debug mode is enabled
                    if (pLog && pLog->IsInDebugMode())
                    {
                        CString message;
                        message.Format(IDS_AL_DELIV_QUANTITY_SUM,
                                       pDeliverable->GetSymbolName(),
                                       double(pDeliverable->GetQuantity()));

                        PSS_GenericSymbolErrorLine e(message);
                        pLog->AddLine(e);

                        IncrementWarningCounter();
                    }

                    // calculate the workload forecast
                    qValue = pDeliverable->GetQuantity() * pDeliverable->GetProcessingTime();
                    pDeliverable->SetWorkloadForecast(qValue);

                    // if can log and debug mode is enabled
                    if (pLog && pLog->IsInDebugMode())
                    {
                        CString message;
                        message.Format(IDS_AL_DELIV_WORKLOAD,
                                       pDeliverable->GetSymbolName(),
                                       double(pDeliverable->GetWorkloadForecast()));

                        PSS_GenericSymbolErrorLine e(message);
                        pLog->AddLine(e);

                        IncrementWarningCounter();
                    }
                }
            }
        }

        // the cost for each deliverables can be calculated, iterate through all links
        for (std::size_t index = 0; index < pState->GetStateLinkCount(); ++index)
        {
            PSS_StateLink* pStateLink = pState->GetStateLinkAt(index);

            if (!pStateLink || !pStateLink->GetLinkSymbol())
                return false;

            PSS_DeliverableLinkSymbolBP* pDeliverable =
                    dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pStateLink->GetLinkSymbol());

            // check if a deliverable exists
            if (pDeliverable)
            {
                // check if it's a local symbol
                if (!pDeliverable->IsLocal())
                {
                    // get the local symbol
                    pDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pDeliverable->GetLocalSymbol());

                    if (!pDeliverable)
                        return false;
                }

                // Now calculate the cost
                PSS_AnnualNumberPropertiesBP qValue = pDeliverable->GetQuantity() * double(pDeliverable->GetUnitaryCost());

                pDeliverable->SetCost(qValue);

                // if can log and debug mode is enabled
                if (pLog && pLog->IsInDebugMode())
                {
                    CString message;
                    message.Format(IDS_AL_DELIV_COST,
                                   pDeliverable->GetSymbolName(),
                                   double(pDeliverable->GetCost()));

                    PSS_GenericSymbolErrorLine e(message);
                    pLog->AddLine(e);

                    IncrementWarningCounter();
                }
            }
        }

        // prepare the procedure cost calculation after the forecast cost and the cost per activation
        if (pProcedureBefore)
        {
            PSS_ProcedureSymbolBP* pLocalProcedureBefore = NULL;

            // check if it's a local symbol
            if (!pProcedureBefore->IsLocal())
            {
                // get the local symbol
                pLocalProcedureBefore = dynamic_cast<PSS_ProcedureSymbolBP*>(pProcedureBefore->GetLocalSymbol());

                if (!pLocalProcedureBefore)
                    return false;

                TRACE1(_T("OnNextSymbolAfterMoveForward: retrieve local procedure %s\n"), pLocalProcedureBefore->GetSymbolName());
            }

            PSS_AnnualNumberPropertiesBP qValue;

            if (pLocalProcedureBefore)
                qValue = pLocalProcedureBefore->GetProcedureActivation() * double(pLocalProcedureBefore->GetUnitaryCost());
            else
                qValue = pProcedureBefore->GetProcedureActivation() * double(pProcedureBefore->GetUnitaryCost());

            // get all leaving down and right deliverables
            CODEdgeArray      leavingRightEdges;
            const std::size_t leavingRightLinkCount = pProcedureBefore->GetEdgesLeaving_Right(leavingRightEdges);

            if (leavingRightLinkCount > 0)
                for (std::size_t i = 0; i < leavingRightLinkCount; ++i)
                {
                    IODEdge*                     pIEdge = leavingRightEdges.GetAt(i);
                    PSS_DeliverableLinkSymbolBP* pLink  = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pLink)
                        continue;

                    // check if it's a local symbol
                    if (!pLink->IsLocal())
                    {
                        // get the local symbol
                        pLink = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pLink->GetLocalSymbol());

                        if (!pLink)
                            return false;
                    }

                    // add the deliverable cost value
                    qValue += pLink->GetCost();
                }

            CODEdgeArray      leavingDownEdges;
            const std::size_t leavingDownLinkCount = pProcedureBefore->GetEdgesLeaving_Down(leavingDownEdges);

            if (leavingDownLinkCount > 0)
            {
                for (std::size_t i = 0; i < leavingDownLinkCount; ++i)
                {
                    IODEdge*                     pIEdge = leavingDownEdges.GetAt(i);
                    PSS_DeliverableLinkSymbolBP* pLink  = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pLink)
                        continue;

                    // check if it's a local symbol
                    if (!pLink->IsLocal())
                    {
                        // get the local symbol
                        pLink = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pLink->GetLocalSymbol());

                        if (!pLink)
                            return false;
                    }

                    // add the deliverable cost value
                    qValue += pLink->GetCost();
                }
            }

            if (pLocalProcedureBefore)
                pLocalProcedureBefore->SetProcedureCost(qValue);
            else
                pProcedureBefore->SetProcedureCost(qValue);

            // if can log and debug mode is enabled
            if (pLog && pLog->IsInDebugMode())
            {
                CString message;

                if (pLocalProcedureBefore)
                    message.Format(IDS_AL_PROCESS_COST_OUTOFTIME,
                                   pLocalProcedureBefore->GetSymbolName(),
                                   double(pLocalProcedureBefore->GetProcedureCost()));
                else
                    message.Format(IDS_AL_PROCESS_COST_OUTOFTIME,
                                   pProcedureBefore->GetSymbolName(),
                                   double(pProcedureBefore->GetProcedureCost()));

                PSS_GenericSymbolErrorLine e(message);
                pLog->AddLine(e);

                IncrementWarningCounter();
            }

            // calculate the procedure cost forecast
            if (pLocalProcedureBefore)
            {
                qValue  = pLocalProcedureBefore->GetProcedureWorkloadForecast() * double(pLocalProcedureBefore->GetUnitCost());
                qValue += pLocalProcedureBefore->GetProcedureCost();
                pLocalProcedureBefore->SetProcedureCostForecast(qValue);
            }
            else
            {
                qValue  = pProcedureBefore->GetProcedureWorkloadForecast() * double(pProcedureBefore->GetUnitCost());
                qValue += pProcedureBefore->GetProcedureCost();
                pProcedureBefore->SetProcedureCostForecast(qValue);
            }

            // if can log and debug mode is enabled
            if (pLog && pLog->IsInDebugMode())
            {
                CString message;

                if (pLocalProcedureBefore)
                    message.Format(IDS_AL_PROCESS_COST_PREV,
                                   pLocalProcedureBefore->GetSymbolName(),
                                   double(pLocalProcedureBefore->GetProcedureCostForecast()));
                else
                    message.Format(IDS_AL_PROCESS_COST_PREV,
                                   pProcedureBefore->GetSymbolName(),
                                   double(pProcedureBefore->GetProcedureCostForecast()));

                PSS_GenericSymbolErrorLine e(message);
                pLog->AddLine(e);

                IncrementWarningCounter();
            }

            // calculate the procedure cost per activation
            double value = 0;

            if (pLocalProcedureBefore)
            {
                if (pLocalProcedureBefore->GetProcedureActivation())
                    value = double(pLocalProcedureBefore->GetProcedureCostForecast()) /
                            double(pLocalProcedureBefore->GetProcedureActivation());

                pLocalProcedureBefore->SetProcedureCostPerActivity(value);
            }
            else
            {
                if (pProcedureBefore->GetProcedureActivation())
                    value = double(pProcedureBefore->GetProcedureCostForecast()) /
                            double(pProcedureBefore->GetProcedureActivation());

                pProcedureBefore->SetProcedureCostPerActivity(value);
            }

            // if can log and debug mode is enabled
            if (pLog && pLog->IsInDebugMode())
            {
                CString message;
                message.Format(IDS_AL_PROCESS_COST_BYPROC,
                               pProcedureBefore->GetSymbolName(),
                               value);

                PSS_GenericSymbolErrorLine e(message);
                pLog->AddLine(e);

                IncrementWarningCounter();
            }
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnBeforeMoveForward(PSS_StateObject*  pState,
                                                            PSS_StateMachine* pStateMachine,
                                                            PSS_Log*          pLog)
{
    if (!PSS_AutomateBP::OnBeforeMoveForward(pState, pStateMachine, pLog))
        return false;

    if (!pState)
        return true;

    #ifdef _DEBUG
        PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pState->GetSymbol());

        if (pSymbol)
        {
            TRACE1(_T("OnBeforeMoveForward - Symbol in the stack is %s\n"), pSymbol->GetSymbolName());
        }
    #endif

    PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pState->GetSymbol());

    // check if a procedure was found, and calculate the procedure activation
    if (pProcedure)
    {
        PSS_ProcedureSymbolBP* pLocalProcedureBefore = NULL;

        // check if it's a local symbol
        if (!pProcedure->IsLocal())
        {
            // get the local symbol
            pLocalProcedureBefore = dynamic_cast<PSS_ProcedureSymbolBP*>(pProcedure->GetLocalSymbol());

            if (!pLocalProcedureBefore)
                return false;

            TRACE1(_T("OnNextSymbolAfterMoveForward - Get local procedure %s\n"), pLocalProcedureBefore->GetSymbolName());
        }

        TRACE1(_T("OnBeforeMoveForward - Procedure in the stack is %s\n"), pProcedure->GetSymbolName());

        if (pLocalProcedureBefore)
            pLocalProcedureBefore->SetProcedureActivation(pLocalProcedureBefore->CalculateProcedureActivation());
        else
        {
            PSS_AnnualNumberPropertiesBP equalizer = pProcedure->CalculateProcedureActivation();
            pProcedure->SetProcedureActivation(equalizer);
        }

        // if can log and debug mode is enabled
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;

            if (pLocalProcedureBefore)
                message.Format(IDS_AL_PROCESS_CALC_ACTIV,
                               pLocalProcedureBefore->GetSymbolName(),
                               double(pLocalProcedureBefore->GetProcedureActivation()));
            else
                message.Format(IDS_AL_PROCESS_CALC_ACTIV,
                               pProcedure->GetSymbolName(),
                               double(pProcedure->GetProcedureActivation()));

            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);

            IncrementWarningCounter();
        }

        // calculate the procedure workload per activity. Get all leaving down, right and left deliverables
        CODEdgeArray      leavingRightEdges;
        const std::size_t leavingRightLinkCount = pProcedure->GetEdgesLeaving_Right(leavingRightEdges);
        double            value                 = 0;

        if (leavingRightLinkCount > 0)
            value += CalculateSumOfOutDeliverables(leavingRightEdges,
                                                   leavingRightLinkCount,
                                                   pProcedure,
                                                   pLocalProcedureBefore);

        CODEdgeArray      leavingDownEdges;
        const std::size_t leavingDownLinkCount = pProcedure->GetEdgesLeaving_Down(leavingDownEdges);

        if (leavingDownLinkCount > 0)
            value += CalculateSumOfOutDeliverables(leavingDownEdges,
                                                   leavingDownLinkCount,
                                                   pProcedure,
                                                   pLocalProcedureBefore);

        CODEdgeArray      leavingLeftEdges;
        const std::size_t leavingLeftLinkCount = pProcedure->GetEdgesLeaving_Left(leavingLeftEdges);

        if (leavingLeftLinkCount > 0)
            value += CalculateSumOfOutDeliverables(leavingLeftEdges,
                                                   leavingLeftLinkCount,
                                                   pProcedure,
                                                   pLocalProcedureBefore);

        // use the multiplier
        if (pLocalProcedureBefore)
        {
            value *= double(pLocalProcedureBefore->GetMultiplier());
            value += pLocalProcedureBefore->GetProcessingTime();
            pLocalProcedureBefore->SetProcedureWorkloadPerActivity(value);
        }
        else
        {
            value *= double(pProcedure->GetMultiplier());
            value += pProcedure->GetProcessingTime();
            pProcedure->SetProcedureWorkloadPerActivity(value);
        }

        // get the procedure processing time and add it to the value
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;
            message.Format(IDS_AL_PROCESS_LOADBYACTIV, pProcedure->GetSymbolName(), value);

            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);

            IncrementWarningCounter();
        }

        // calculate the workload forecast
        PSS_AnnualNumberPropertiesBP qValue;

        if (pLocalProcedureBefore)
        {
            qValue = pLocalProcedureBefore->GetProcedureActivation() *
                     pLocalProcedureBefore->GetProcedureWorkloadPerActivity();
            pLocalProcedureBefore->SetProcedureWorkloadForecast(qValue);
        }
        else
        {
            qValue = pProcedure->GetProcedureActivation() *
                     pProcedure->GetProcedureWorkloadPerActivity();
            pProcedure->SetProcedureWorkloadForecast(qValue);
        }

        // if can log and debug mode is enabled
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;

            if (pLocalProcedureBefore)
                message.Format(IDS_AL_PROCESS_WORKLOAD,
                               pLocalProcedureBefore->GetSymbolName(),
                               double(pLocalProcedureBefore->GetProcedureWorkloadForecast()));
            else
                message.Format(IDS_AL_PROCESS_WORKLOAD,
                               pProcedure->GetSymbolName(),
                               double(pProcedure->GetProcedureWorkloadForecast()));

            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);

            IncrementWarningCounter();
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnAfterMoveForward(PSS_StateObject*  pState,
                                                           PSS_StateMachine* pStateMachine,
                                                           PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnAfterMoveForward(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnBeforeMoveBackward(PSS_StateObject*  pState,
                                                             PSS_StateMachine* pStateMachine,
                                                             PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnBeforeMoveBackward(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnAfterMoveBackward(PSS_StateObject*  pState,
                                                            PSS_StateMachine* pStateMachine,
                                                            PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnAfterMoveBackward(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnObjectError(PSS_StateObject*  pState,
                                                      PSS_StateMachine* pStateMachine,
                                                      PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnObjectError(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnReachMaximumLoopCounter(PSS_Log* pLog)
{
    return PSS_AutomateBP::OnReachMaximumLoopCounter(pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnReachMaximumInPauseCounter(PSS_Log* pLog)
{
    return PSS_AutomateBP::OnReachMaximumInPauseCounter(pLog);
}
//---------------------------------------------------------------------------
bool PSS_SesterceRecalculationAutomate::OnReachMaximumWaitingForOtherLinksCounter(PSS_Log* pLog)
{
    return PSS_AutomateBP::OnReachMaximumWaitingForOtherLinksCounter(pLog);
}
//---------------------------------------------------------------------------
double PSS_SesterceRecalculationAutomate::CalculateSumOfOutDeliverables(CODEdgeArray&          leavingEdges,
                                                                        std::size_t            leavingLinkCount,
                                                                        PSS_ProcedureSymbolBP* pProcedure,
                                                                        PSS_ProcedureSymbolBP* pLocalProcedureBefore)
{
    double value = 0;
    double percentOut;

    for (std::size_t i = 0; i < leavingLinkCount; ++i)
    {
        IODEdge*                     pIEdge = leavingEdges.GetAt(i);
        PSS_DeliverableLinkSymbolBP* pLink  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

        if (!pLink)
            continue;

        // check if it's a local symbol
        if (!pLink->IsLocal())
        {
            // get the local symbol
            pLink = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pLink->GetLocalSymbol());

            if (!pLink)
                return false;
        }

        // if the quantity is not locked
        if (!pLink->GetLockQuantityYear())
            percentOut = double(pLink->GetOutWorkloadPercent());
        else
        {
            // quantity / activation * multiplier
            if (pLocalProcedureBefore)
                percentOut = pLink->GetQuantityYear() / (double(pLocalProcedureBefore->GetProcedureActivation()) *
                                                                pLocalProcedureBefore->GetMultiplier());
            else
                percentOut = pLink->GetQuantityYear() / (double(pProcedure->GetProcedureActivation()) *
                                                                pProcedure->GetMultiplier());
        }

        // add the value
        value += (percentOut * pLink->GetProcessingTime());
    }

    return value;
}
//---------------------------------------------------------------------------
