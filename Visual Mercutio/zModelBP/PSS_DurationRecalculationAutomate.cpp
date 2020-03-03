/****************************************************************************
 * ==> PSS_DurationRecalculationAutomate -----------------------------------*
 ****************************************************************************
 * Description : Provides the duration recalculation automate               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DurationRecalculationAutomate.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zWkf\PSS_StateMachine.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_ODSymbolManipulator.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "PSS_CheckSesterceConsistency.h"
#include "PSS_ProcessClearDurationFigures.h"
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
// PSS_DurationRecalculationAutomate
//---------------------------------------------------------------------------
PSS_DurationRecalculationAutomate::PSS_DurationRecalculationAutomate(PSS_Symbol*               pSymbol,
                                                                     PSS_ProcessGraphModelMdl* pModel,
                                                                     PSS_Log*                  pLog) :
    PSS_AutomateBP(pSymbol, pModel, pLog),
    m_Pass(0)
{}
//---------------------------------------------------------------------------
PSS_DurationRecalculationAutomate::~PSS_DurationRecalculationAutomate()
{}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnStart(PSS_Log* pLog)
{
    const bool result = PSS_AutomateBP::OnStart(!m_Pass ? pLog : NULL);

    // only for the first pass
    if (!m_Pass)
    {
        // can log?
        if (pLog)
        {
            CString message;
            message.LoadString(IDS_AL_START_DURATIONCALCULATION);
            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }

        // clear all values before calculating the model duration
        PSS_ProcessClearDurationFigures clearDuration(m_pModel, pLog);
        clearDuration.SetLog(pLog);
        clearDuration.Navigate();

        // preform a deep check before starting the calculation of the model
        PSS_CheckSesterceConsistency checkConsistency(m_pModel, pLog);
        checkConsistency.CheckModel();

        // Assigns the error counter and the warning counter
        SetErrorCounter(checkConsistency.GetErrorCounter());
        SetWarningCounter(checkConsistency.GetWarningCounter());

        // don't continue if we encounter error.
        if (checkConsistency.GetErrorCounter() > 0)
            return false;
    }

    return result;
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnStop(PSS_Log* pLog)
{
    // only for the last pass
    if (!m_Pass)
        // can log?
        if (pLog)
        {
            CString message;
            message.LoadString(IDS_AL_STOP_DURATIONCALCULATION);
            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }

    return PSS_AutomateBP::OnStop(pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnPause(PSS_Log* pLog)
{
    return PSS_AutomateBP::OnPause(pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnResume(PSS_Log* pLog)
{
    return PSS_AutomateBP::OnResume(pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnObjectIsFinished(PSS_StateObject*  pState,
                                                           PSS_StateMachine* pStateMachine,
                                                           PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnObjectIsFinished(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnObjectIsPaused(PSS_StateObject*  pState,
                                                         PSS_StateMachine* pStateMachine,
                                                         PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnObjectIsPaused(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnObjectIsWaitingForOtherLinks(PSS_StateObject*  pState,
                                                                       PSS_StateMachine* pStateMachine,
                                                                       PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnObjectIsWaitingForOtherLinks(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnBeforeRequestMoveForward(PSS_StateObject*  pState,
                                                                   PSS_StateMachine* pStateMachine,
                                                                   PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnBeforeRequestMoveForward(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnNextSymbolAfterMoveForward(PSS_StateObject*  pState,
                                                                     PSS_StateMachine* pStateMachine,
                                                                     PSS_Log*          pLog)
{
    if (!PSS_AutomateBP::OnNextSymbolAfterMoveForward(pState, pStateMachine, pLog))
        return false;

    // only valid for the second pass
    if (m_Pass != 1)
        return true;

    if (pState)
    {
        #ifdef _DEBUG
            PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pState->GetSymbol());

            if (pSymbol)
            {
                TRACE1(_T("OnNextSymbolAfterMoveForward - Symbol in the stack is %s\n"), pSymbol->GetSymbolName());
            }
        #endif

        PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pState->GetSymbol());

        // the symbol and the link should be found
        if (pProcedure)
        {
            TRACE1(_T("OnNextSymbolAfterMoveForward - Current Procedure is %s\n"), pProcedure->GetSymbolName());

            // normally should have at least one link
            if (!pState->GetStateLinkCount())
                return false;

            CODEdgeArray      leavingDownEdges;
            const std::size_t leavingDownLinkCount = pProcedure->GetEdgesLeaving_Down(leavingDownEdges);

            if (leavingDownLinkCount > 0)
                SetCaseDurationOfProcedure(pState, leavingDownEdges, leavingDownLinkCount, pProcedure, pLog);
        }
    }

    // the symbol and the link must be found
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnBeforeMoveForward(PSS_StateObject*  pState,
                                                            PSS_StateMachine* pStateMachine,
                                                            PSS_Log*          pLog)
{
    if (!PSS_AutomateBP::OnBeforeMoveForward(pState, pStateMachine, pLog))
        return false;

    // only valid for the first pass
    if (m_Pass)
        return true;

    if (pState)
    {
        #ifdef _DEBUG
            PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pState->GetSymbol());

            if (pSymbol)
            {
                TRACE1(_T("OnBeforeMoveForward - Symbol in the stack is %s\n"), pSymbol->GetSymbolName());
            }
        #endif

        PSS_StartSymbolBP* pStartSymbol = dynamic_cast<PSS_StartSymbolBP*>(pState->GetSymbol());

        // is a start symbol? Calculate the deliverables down durations
        if (pStartSymbol)
        {
            TRACE1(_T("OnBeforeMoveForward - Start in the stack is %s\n"), pStartSymbol->GetSymbolName());

            CODEdgeArray      leavingEdges;
            const std::size_t leavingLinkCount = pStartSymbol->GetEdgesLeaving(leavingEdges);

            if (leavingLinkCount > 0)
                SetStartSymbolCaseDurationOfDownDeliverables(pState, leavingEdges, leavingLinkCount, pLog);

            return true;
        }

        PSS_DoorSymbolBP* pDoorSymbol = dynamic_cast<PSS_DoorSymbolBP*>(pState->GetSymbol());

        // if is a door symbol, duplicate the deliverable symbols duration information
        if (pDoorSymbol)
        {
            TRACE1(_T("OnBeforeMoveForward - Door in the stack is %s\n"), pDoorSymbol->GetSymbolName());

            CODEdgeArray      enteringEdges;
            const std::size_t enteringLinkCount = pDoorSymbol->GetEdgesEntering(enteringEdges);
            PSS_DoorSymbolBP* pTwinDoor         = pDoorSymbol->GetTwinDoorSymbol();

            // get the twin door leaving edge and get its link
            if (enteringLinkCount > 0 && pTwinDoor)
            {
                CODEdgeArray      leavingEdges;
                const std::size_t leavingLinkCount = pTwinDoor->GetEdgesLeaving(leavingEdges);

                if (leavingLinkCount > 0)
                {
                    // copy the duration information coming from the entering deliverable to the leaving deliverable
                    // attached to the target door
                    IODEdge*                     pIEdge   = enteringEdges.GetAt(0);
                    PSS_DeliverableLinkSymbolBP* pSrcLink = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pSrcLink)
                        return true;

                    // get the twin door deliverable
                    pIEdge                                = leavingEdges.GetAt(0);
                    PSS_DeliverableLinkSymbolBP* pDstLink = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pDstLink)
                        return true;

                    // copy the duration
                    pDstLink->SetCaseDuration(pSrcLink->GetCaseDuration());
                    pDstLink->SetCaseDurationMax(pSrcLink->GetCaseDurationMax());
                    pDstLink->SetGreenLineDuration(pSrcLink->GetGreenLineDuration());
                    pDstLink->SetTargetDuration(pSrcLink->GetTargetDuration());

                    // if can log and debug mode is enabled
                    if (pLog && pLog->IsInDebugMode())
                    {
                        CString message;
                        message.Format(IDS_DB_DELIV_INC_7,
                                       pSrcLink->GetSymbolName(),
                                       pDstLink->GetSymbolName(),
                                       pDstLink->GetCaseDuration(),
                                       pDstLink->GetCaseDurationMax());

                        PSS_GenericSymbolErrorLine e(message);
                        pLog->AddLine(e);
                    }
                }
            }

            return true;
        }

        PSS_PageSymbolBP* pPageSymbol = dynamic_cast<PSS_PageSymbolBP*>(pState->GetSymbol());

        // if is a page symbol, duplicate the deliverable symbols duration information
        if (pPageSymbol)
        {
            TRACE1(_T("OnBeforeMoveForward - Page in the stack is %s\n"), pPageSymbol->GetSymbolName());

            CODEdgeArray      enteringEdges;
            const std::size_t enteringLinkCount = pPageSymbol->GetEdgesEntering(enteringEdges);

            if (enteringLinkCount > 0 && pPageSymbol->GetTwinPageSymbol())
            {
                PSS_PageSymbolBP* pTwinPage = pPageSymbol->GetTwinPageSymbol();

                // copy the duration information coming from the entering deliverable to the leaving deliverable
                // attached to the target page
                CODEdgeArray      leavingEdges;
                const std::size_t leavingLinkCount = pTwinPage->GetEdgesLeaving(leavingEdges);

                if (leavingLinkCount > 0)
                {
                    // copy the duration information coming from the entering deliverable to the leaving deliverable
                    // attached to the target door
                    IODEdge*                     pIEdge   = enteringEdges.GetAt(0);
                    PSS_DeliverableLinkSymbolBP* pSrcLink = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pSrcLink)
                        return true;

                    // get the twin page deliverable
                    pIEdge                                = leavingEdges.GetAt(0);
                    PSS_DeliverableLinkSymbolBP* pDstLink = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pDstLink)
                        return true;

                    // copy the duration
                    pDstLink->SetCaseDuration(pSrcLink->GetCaseDuration());
                    pDstLink->SetCaseDurationMax(pSrcLink->GetCaseDurationMax());
                    pDstLink->SetGreenLineDuration(pSrcLink->GetGreenLineDuration());
                    pDstLink->SetTargetDuration(pSrcLink->GetTargetDuration());

                    // if can log and debug mode is enabled
                    if (pLog && pLog->IsInDebugMode())
                    {
                        CString message;

                        message.Format(IDS_DB_DELIV_INC_7,
                                       pSrcLink->GetSymbolName(),
                                       pDstLink->GetSymbolName(),
                                       pDstLink->GetCaseDuration(),
                                       pDstLink->GetCaseDurationMax());

                        PSS_GenericSymbolErrorLine e(message);
                        pLog->AddLine(e);
                    }
                }
            }

            return true;
        }

        PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pState->GetSymbol());

        // if is a procedure symbol, calculate the deliverable durations
        if (pProcedure)
        {
            TRACE1(_T("OnBeforeMoveForward: procedure in the stack is %s\n"), pProcedure->GetSymbolName());

            PSS_ProcedureSymbolBP* pLocalProcedureBefore = NULL;

            // calculate the deliverable durations for all leaving right deliverables
            CODEdgeArray      leavingRightEdges;
            const std::size_t leavingRightLinkCount = pProcedure->GetEdgesLeaving_Right(leavingRightEdges);

            if (leavingRightLinkCount > 0)
                SetCaseDurationOfLateralDeliverables(leavingRightEdges, leavingRightLinkCount, pProcedure, pLog);

            // calculate the deliverable durations for all leaving left deliverables
            CODEdgeArray      leavingLeftEdges;
            const std::size_t leavingLeftLinkCount = pProcedure->GetEdgesLeaving_Left(leavingLeftEdges);

            if (leavingLeftLinkCount > 0)
                SetCaseDurationOfLateralDeliverables(leavingLeftEdges, leavingLeftLinkCount, pProcedure, pLog);

            // calculate the deliverable durations for all leaving down deliverables
            CODEdgeArray      leavingDownEdges;
            const std::size_t leavingDownLinkCount = pProcedure->GetEdgesLeaving_Down(leavingDownEdges);

            if (leavingDownLinkCount > 0)
                SetCaseDurationOfDownDeliverables(pState, leavingDownEdges, leavingDownLinkCount, pProcedure, pLog);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnAfterMoveForward(PSS_StateObject*  pState,
                                                           PSS_StateMachine* pStateMachine,
                                                           PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnAfterMoveForward(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnBeforeMoveBackward(PSS_StateObject*  pState,
                                                             PSS_StateMachine* pStateMachine,
                                                             PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnBeforeMoveBackward(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnAfterMoveBackward(PSS_StateObject*  pState,
                                                            PSS_StateMachine* pStateMachine,
                                                            PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnAfterMoveBackward(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnObjectError(PSS_StateObject*  pState,
                                                      PSS_StateMachine* pStateMachine,
                                                      PSS_Log*          pLog)
{
    return PSS_AutomateBP::OnObjectError(pState, pStateMachine, pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnReachMaximumLoopCounter(PSS_Log* pLog)
{
    return PSS_AutomateBP::OnReachMaximumLoopCounter(pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnReachMaximumInPauseCounter(PSS_Log* pLog)
{
    return PSS_AutomateBP::OnReachMaximumInPauseCounter(pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::OnReachMaximumWaitingForOtherLinksCounter(PSS_Log* pLog)
{
    return PSS_AutomateBP::OnReachMaximumWaitingForOtherLinksCounter(pLog);
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::SetCaseDurationOfLateralDeliverables(CODEdgeArray&          leavingEdges,
                                                                             std::size_t            leavingLinkCount,
                                                                             PSS_ProcedureSymbolBP* pProcedure,
                                                                             PSS_Log*               pLog)
{
    for (std::size_t i = 0; i < leavingLinkCount; ++i)
    {
        IODEdge*                     pIEdge = leavingEdges.GetAt(i);
        PSS_DeliverableLinkSymbolBP* pLink  = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

        if (!pLink)
            continue;

        PSS_DeliverableLinkSymbolBP* pLocalLink = NULL;

        // check if it's a local symbol
        if (!pLink->IsLocal())
        {
            // get the local symbol
            pLocalLink = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pLink->GetLocalSymbol());

            if (!pLocalLink)
                return false;
        }

        pLink->SetCaseDuration   (pLocalLink ? pLocalLink->GetTargetDuration() : pLink->GetTargetDuration());
        pLink->SetCaseDurationMax(pLocalLink ? pLocalLink->GetTargetDuration() : pLink->GetTargetDuration());

        // if can log and debug mode is enabled
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;
            message.Format(IDS_DB_DELIV_INC_1,
                           pLink->GetSymbolName(),
                           pLink->GetCaseDuration(),
                           pLink->GetCaseDurationMax());

            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::SetCaseDurationOfDownDeliverables(PSS_StateObject*       pState,
                                                                          CODEdgeArray&          leavingEdges,
                                                                          std::size_t            leavingLinkCount,
                                                                          PSS_ProcedureSymbolBP* pProcedure,
                                                                          PSS_Log*               pLog)
{
    CODEdgeArray enteringEdgesRight;
    CODEdgeArray enteringEdgesLeft;

    // get the entering edges for the maximum duration, the entering deliverables are added  and not used in the maximum
    pProcedure->GetEdgesEntering_Right(enteringEdgesRight);
    pProcedure->GetEdgesEntering_Left(enteringEdgesLeft);

    for (std::size_t i = 0; i < leavingLinkCount; ++i)
    {
        IODEdge*                     pIEdge = leavingEdges.GetAt(i);
        PSS_DeliverableLinkSymbolBP* pLink  = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

        if (!pLink)
            continue;

        PSS_DeliverableLinkSymbolBP* pLocalLink = NULL;

        // check if it's a local symbol
        if (!pLink->IsLocal())
        {
            // get the local symbol
            pLocalLink = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pLink->GetLocalSymbol());

            if (!pLocalLink)
                return false;
        }

        double totalCombination = 0.0;

        // before performing the calculation, check which deliverable should be included to the calculation path.
        // To achieve that, assume that any deliverable with a duration equals to -1 should be excluded from the path
        for (std::size_t index = 0; index < pState->GetStateLinkCount(); ++index)
        {
            PSS_StateLink* pStateLink = pState->GetStateLinkAt(index);

            if (!pStateLink)
                return false;

            PSS_DeliverableLinkSymbolBP* pDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pStateLink->GetLinkSymbol());

            // found a deliverable?
            if (pDeliverable)
            {
                // not applicable for entering lateral deliverables
                if (enteringEdgesLeft.ContainsEdge(pDeliverable) || enteringEdgesRight.ContainsEdge(pDeliverable))
                    continue;

                // check if this deliverable is a master of the combination
                if (!pDeliverable->IsMasterOfCombination())
                    continue;

                // if the deliverable has no duration and no max duration, assume that this deliverable
                // should be excluded from the calculation
                if (pDeliverable->GetCaseDuration() == -1 && pDeliverable->GetCaseDurationMax() == -1)
                    continue;

                PSS_DeliverableLinkSymbolBP* pLocalDeliverable = NULL;

                // check if it'ss a local symbol
                if (!pDeliverable->IsLocal())
                {
                    // get the local symbol
                    pLocalDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pDeliverable->GetLocalSymbol());

                    if (!pLocalDeliverable)
                        return false;
                }

                // calculate the average value
                const float combMaxPercentage = pLocalDeliverable ? pLocalDeliverable->GetCombinationMaxPercentage() :
                                                                    pDeliverable->GetCombinationMaxPercentage();

                if (combMaxPercentage == float(INT_MAX))
                    continue;

                totalCombination += double(combMaxPercentage);
            }
        }

        double value           = 0.0;
        double valueMax        = 0.0;
        double lateralValue    = 0.0;
        double lateralValueMax = 0.0;

        // calculate the sum of durations for each incoming deliverables. For the maximum, take the maximum of
        // entering deliverables, and the maximum of lateral entering deliverables. For the average, take the
        // sum of entering deliverables * by the % of the combination based 100, and the maximum of lateral
        // entering deliverables * deliverable quantity / procedure activation
        for (std::size_t index = 0; index < pState->GetStateLinkCount(); ++index)
        {
            PSS_StateLink* pStateLink = pState->GetStateLinkAt(index);

            if (!pStateLink)
                return false;

            PSS_DeliverableLinkSymbolBP* pDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pStateLink->GetLinkSymbol());

            // check a deliverable was found
            if (pDeliverable)
            {
                PSS_DeliverableLinkSymbolBP* pLocalDeliverable = NULL;

                // is a local symbol?
                if (!pDeliverable->IsLocal())
                {
                    // get the local symbol
                    pLocalDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pDeliverable->GetLocalSymbol());

                    if (!pLocalDeliverable)
                        return false;
                }

                // calculate the max value
                double sum     = pLocalDeliverable ? pLocalDeliverable->GetCaseDuration() : pDeliverable->GetCaseDuration();
                sum           += pDeliverable->GetGreenLineDuration();
                double sumMax  = pLocalDeliverable ? pLocalDeliverable->GetCaseDurationMax() : pDeliverable->GetCaseDurationMax();
                sumMax        += pDeliverable->GetGreenLineDuration();

                // if an entering lateral deliverable
                if (enteringEdgesLeft.ContainsEdge(pDeliverable) || enteringEdgesRight.ContainsEdge(pDeliverable))
                {
                    // calculate the max
                    lateralValueMax = __max(sumMax, lateralValueMax);

                    // calculate the average value by taking the maximum of laterals
                    double quantity = (pLocalDeliverable ? double(pLocalDeliverable->GetQuantity()) :
                                                           double(pDeliverable->GetQuantity()));

                    if (quantity == 0.0)
                    {
                        if (pLog)
                        {
                            PSS_GenericSymbolErrorLine e(IDS_AL_DELIV_QUANTITY_ZERO,
                                                         pDeliverable->GetSymbolName(),
                                                         pDeliverable->GetAbsolutePath());
                            pLog->AddLine(e);
                        }

                        quantity = 1.0;
                    }

                    const double procActivation = double(pProcedure->GetProcedureActivation());
                    const double avg            = quantity / (procActivation ? procActivation : 1.0);
                    lateralValue                = __max((sum * avg), lateralValue);
                }
                else
                {
                    // check if this deliverable is a master of the combination
                    if (!pDeliverable->IsMasterOfCombination())
                        continue;

                    // calculate the max
                    valueMax = __max(sumMax, valueMax);

                    // calculate the average Value
                    float combMaxPercentage = pLocalDeliverable ? pLocalDeliverable->GetCombinationMaxPercentage() :
                                                                  pDeliverable->GetCombinationMaxPercentage();

                    if (combMaxPercentage == float(INT_MAX))
                    {
                        if (pLog)
                        {
                            PSS_GenericSymbolErrorLine e(IDS_AL_DELIV_NOTDEFINED_COMBINATION,
                                                         pDeliverable->GetSymbolName(),
                                                         pDeliverable->GetAbsolutePath());

                            pLog->AddLine(e);
                        }

                        combMaxPercentage = 1.0f;
                    }

                    // divide by the sum of the combination percentage. This to rebalance in base 100%
                    value += (sum * double(combMaxPercentage) / (totalCombination ? totalCombination : 1.0));
                }

                // if can log and debug mode is enabled
                if (pLog && pLog->IsInDebugMode())
                {
                    CString message;
                    message.Format(IDS_DB_DELIV_INC_2,
                                   pLink->GetSymbolName(),
                                   pDeliverable->GetSymbolName(),
                                   value,
                                   valueMax);

                    PSS_GenericSymbolErrorLine e(message);
                    pLog->AddLine(e);

                    message.Format(IDS_DB_DELIV_INC_5,
                                   pLink->GetSymbolName(),
                                   pDeliverable->GetSymbolName(),
                                   lateralValue,
                                   lateralValueMax);

                    PSS_GenericSymbolErrorLine e2(message);
                    pLog->AddLine(e2);
                }
            }
        }

        pLink->SetCaseDuration   ((pLocalLink ? pLocalLink->GetTargetDuration() : pLink->GetTargetDuration()) + value    + lateralValue);
        pLink->SetCaseDurationMax((pLocalLink ? pLocalLink->GetTargetDuration() : pLink->GetTargetDuration()) + valueMax + lateralValueMax);

        // if can log and debug mode is enabled
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;
            message.Format(IDS_DB_DELIV_INC_1,
                           pLink->GetSymbolName(),
                           pLink->GetCaseDuration(),
                           pLink->GetCaseDurationMax());

            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::SetStartSymbolCaseDurationOfDownDeliverables(PSS_StateObject* pState,
                                                                                     CODEdgeArray&    leavingEdges,
                                                                                     std::size_t      leavingLinkCount,
                                                                                     PSS_Log*         pLog)
{
    for (std::size_t i = 0; i < leavingLinkCount; ++i)
    {
        IODEdge*                     pIEdge = leavingEdges.GetAt(i);
        PSS_DeliverableLinkSymbolBP* pLink  = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

        if (!pLink)
            continue;

        // assign the duration and duration maximum using the target duration
        pLink->SetCaseDuration(pLink->GetTargetDuration());
        pLink->SetCaseDurationMax(pLink->GetTargetDuration());

        // if can log and debug mode is enabled
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;
            message.Format(IDS_DB_DELIV_INC_3,
                           pLink->GetSymbolName(),
                           pLink->GetCaseDuration(),
                           pLink->GetCaseDurationMax());

            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DurationRecalculationAutomate::SetCaseDurationOfProcedure(PSS_StateObject*       pState,
                                                                   CODEdgeArray&          leavingEdges,
                                                                   std::size_t            leavingLinkCount,
                                                                   PSS_ProcedureSymbolBP* pProcedure,
                                                                   PSS_Log*               pLog)
{
    CODEdgeArray enteringEdgesRight;
    CODEdgeArray enteringEdgesLeft;

    // need to check if coming back from a lateral loop. To detect that, check if contains a coming up
    // deliverable. If not, do nothing. Get entering edges for laterals
    pProcedure->GetEdgesEntering_Right(enteringEdgesRight);
    pProcedure->GetEdgesEntering_Left(enteringEdgesLeft);

    bool hasDeliverable = false;

    for (std::size_t i = 0; i < pState->GetStateLinkCount(); ++i)
    {
        PSS_StateLink* pStateLink = pState->GetStateLinkAt(i);

        if (!pStateLink)
            return false;

        PSS_DeliverableLinkSymbolBP* pDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pStateLink->GetLinkSymbol());

        // check if a deliverable was found
        if (pDeliverable)
        {
            // is an entering lateral deliverable?
            if (enteringEdgesLeft.ContainsEdge(pDeliverable) || enteringEdgesRight.ContainsEdge(pDeliverable))
                continue;

            hasDeliverable = true;
        }
    }

    if (!hasDeliverable)
        return true;

    double numeratorValue    = 0.0;
    double numeratorValueMax = 0.0;
    double denomValue        = 0.0;

    for (std::size_t i = 0; i < leavingLinkCount; ++i)
    {
        IODEdge*                     pIEdge = leavingEdges.GetAt(i);
        PSS_DeliverableLinkSymbolBP* pLink  = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

        if (!pLink)
            continue;

        PSS_DeliverableLinkSymbolBP* pLocalLink = NULL;

        // check if it's a local symbol
        if (!pLink->IsLocal())
        {
            // get the local symbol
            pLocalLink = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pLink->GetLocalSymbol());

            if (!pLocalLink)
                return false;
        }

        // calculate the numerator Value
        const double val = (pLocalLink ? pLocalLink->GetCaseDuration()               : pLink->GetCaseDuration()) *
                           (pLocalLink ? double(pLocalLink->GetOutWorkloadPercent()) : double(pLink->GetOutWorkloadPercent()));

        numeratorValue += val;

        const double valMax = (pLocalLink ? pLocalLink->GetCaseDurationMax()            : pLink->GetCaseDurationMax()) *
                              (pLocalLink ? double(pLocalLink->GetOutWorkloadPercent()) : double(pLink->GetOutWorkloadPercent()));

        numeratorValueMax += valMax;

        // if can log and debug mode is enabled
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;
            message.Format(IDS_DB_PROCEDURE_INC_3,
                           pProcedure->GetSymbolName(),
                           pLink->GetSymbolName(),
                           val);

            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }

        // calculate the denominator value
        denomValue += (pLocalLink ? double(pLocalLink->GetOutWorkloadPercent()) : double(pLink->GetOutWorkloadPercent()));
    }

    double delivDurationValue    = 0.0;
    double delivDurationValueMax = 0.0;
    double sumQuantityDeliv      = 0.0;

    CODEdgeArray enteringEdgesUp;
    std::size_t  enteringEdgesUpCount = pProcedure->GetEdgesEntering_Up(enteringEdgesUp);

    for (std::size_t i = 0; i < enteringEdgesUpCount; ++i)
    {
        IODEdge*                     pIEdge       = enteringEdgesUp.GetAt(i);
        PSS_DeliverableLinkSymbolBP* pDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

        if (!pDeliverable)
            continue;

        PSS_DeliverableLinkSymbolBP* pLocalDeliverable = NULL;

        // check if it's a local symbol
        if (!pDeliverable->IsLocal())
        {
            // get the local symbol
            pLocalDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pDeliverable->GetLocalSymbol());

            if (!pLocalDeliverable)
                return false;
        }

        // if the deliverable duration and max duration are empty, assume that this deliverable should be excluded
        // from the calculation
        if (pDeliverable->GetCaseDuration() == -1 && pDeliverable->GetCaseDurationMax() == -1)
            continue;

        // keep the sum of quantity deliverables
        sumQuantityDeliv += (pLocalDeliverable ? double(pLocalDeliverable->GetQuantity()) : double(pDeliverable->GetQuantity()));

        // sum the values of duration
        delivDurationValue += ((pLocalDeliverable ? pLocalDeliverable->GetCaseDuration()     : pDeliverable->GetCaseDuration()) *
                               (pLocalDeliverable ? double(pLocalDeliverable->GetQuantity()) : double(pDeliverable->GetQuantity())));

        delivDurationValueMax += ((pLocalDeliverable ? pLocalDeliverable->GetCaseDurationMax()  : pDeliverable->GetCaseDurationMax()) *
                                  (pLocalDeliverable ? double(pLocalDeliverable->GetQuantity()) : double(pDeliverable->GetQuantity())));

        // if can log and debug mode is enabled
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;
            message.Format(IDS_DB_DELIV_INC_6,
                           pDeliverable->GetSymbolName(),
                           (pLocalDeliverable ? pLocalDeliverable->GetCaseDuration()     : pDeliverable->GetCaseDuration()),
                           (pLocalDeliverable ? pLocalDeliverable->GetCaseDurationMax()  : pDeliverable->GetCaseDurationMax()),
                           (pLocalDeliverable ? double(pLocalDeliverable->GetQuantity()) : double(pDeliverable->GetQuantity())));

            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }
    }

    // set the procedure processing duration
    pProcedure->SetProcessingDuration   ((numeratorValue    / (denomValue ? denomValue : 1.0)) - (delivDurationValue    / (sumQuantityDeliv ? sumQuantityDeliv : 1.0)));
    pProcedure->SetProcessingDurationMax((numeratorValueMax / (denomValue ? denomValue : 1.0)) - (delivDurationValueMax / (sumQuantityDeliv ? sumQuantityDeliv : 1.0)));

    // if can log and debug mode is enabled
    if (pLog && pLog->IsInDebugMode())
    {
        CString message;
        message.Format(IDS_DB_PROCEDURE_INC_2,
                       pProcedure->GetSymbolName(),
                       pProcedure->GetProcessingDuration(),
                       pProcedure->GetProcessingDurationMax());

        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);

        message.Format(IDS_DB_PROCEDURE_INC_4,
                       pProcedure->GetSymbolName(),
                       numeratorValue,
                       denomValue,
                       delivDurationValue,
                       sumQuantityDeliv);

        PSS_GenericSymbolErrorLine e2(message);
        pLog->AddLine(e2);

        message.Format(IDS_DB_PROCEDURE_INC_6,
                       pProcedure->GetSymbolName(),
                       numeratorValueMax,
                       denomValue,
                       delivDurationValueMax,
                       sumQuantityDeliv);

        PSS_GenericSymbolErrorLine e3(message);
        pLog->AddLine(e3);
    }

    return true;
}
//---------------------------------------------------------------------------
