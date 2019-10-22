// ZBDurationRecalculationAutomate.cpp: implementation of the ZBDurationRecalculationAutomate class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBDurationRecalculationAutomate.h"

#include "zWkf\PSS_StateMachine.h"

#include "ZUCheckSesterceConsistency.h"
#include "ZUProcessClearDurationFigures.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

#include "ZBBPDoorSymbol.h"
#include "ZBBPPageSymbol.h"
#include "ZBBPProcedureSymbol.h"
#include "ZBBPProcessSymbol.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"
#include "ZBDeliverableLinkSymbol.h"

#include "zModel\ZUODSymbolManipulator.h"

// Include files for log
#include "zBaseLib\PSS_Log.h"
#include "zModel\ZBGenericSymbolErrorLine.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 4 septembre 2006 - Ajout des décorations unicode _T(), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBDurationRecalculationAutomate::ZBDurationRecalculationAutomate(ZBSymbol*                    pSymbol,
                                                                 ZDProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                                 PSS_Log*                    pLog    /*= NULL*/)
    : ZBBPAutomate(pSymbol, pModel, pLog),
    m_Pass(0) // Initialize the pass to zero (first pass)
{}

ZBDurationRecalculationAutomate::~ZBDurationRecalculationAutomate()
{}

bool ZBDurationRecalculationAutomate::OnStart(PSS_Log* pLog)
{
    bool RetValue = ZBBPAutomate::OnStart((GetPass() == 0) ? pLog : NULL);

    // Only for the first pass
    if (GetPass() == 0)
    {
        // If log
        if (pLog)
        {
            CString message;
            message.LoadString(IDS_AL_START_DURATIONCALCULATION);
            ZBGenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }

        // Clear all values before calculating the model duration
        ZUProcessClearDurationFigures Clear(m_pModel, pLog);
        Clear.SetLog(pLog);
        Clear.Navigate();

        // Do a deep check before launching the calculation of the model
        ZUCheckSesterceConsistency    Check(m_pModel, pLog);
        Check.CheckModel();

        // Assigns the error counter and the warning counter
        SetErrorCounter(Check.GetErrorCounter());
        SetWarningCounter(Check.GetWarningCounter());

        // Don't continue if we encounter error.
        if (Check.GetErrorCounter() > 0)
        {
            return false;
        }
    }

    return RetValue;
}

bool ZBDurationRecalculationAutomate::OnStop(PSS_Log* pLog)
{
    // Only for the last pass
    if (GetPass() == 0)
    {
        // If log
        if (pLog)
        {
            CString message;
            message.LoadString(IDS_AL_STOP_DURATIONCALCULATION);
            ZBGenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }
    }

    return ZBBPAutomate::OnStop(pLog);
}

bool ZBDurationRecalculationAutomate::OnPause(PSS_Log* pLog)
{
    return ZBBPAutomate::OnPause(pLog);
}

bool ZBDurationRecalculationAutomate::OnResume(PSS_Log* pLog)
{
    return ZBBPAutomate::OnResume(pLog);
}

//////////////////////////////////////////////////////////////////////
// Call-back workflow operations
bool ZBDurationRecalculationAutomate::OnObjectIsFinished(PSS_StateObject*  pState,
                                                         PSS_StateMachine* pStateMachine,
                                                         PSS_Log*          pLog)
{
    return ZBBPAutomate::OnObjectIsFinished(pState, pStateMachine, pLog);
}

bool ZBDurationRecalculationAutomate::OnObjectIsPaused(PSS_StateObject*  pState,
                                                       PSS_StateMachine* pStateMachine,
                                                       PSS_Log*          pLog)
{
    return ZBBPAutomate::OnObjectIsPaused(pState, pStateMachine, pLog);
}

bool ZBDurationRecalculationAutomate::OnObjectIsWaitingForOtherLinks(PSS_StateObject*  pState,
                                                                     PSS_StateMachine* pStateMachine,
                                                                     PSS_Log*          pLog)
{
    return ZBBPAutomate::OnObjectIsWaitingForOtherLinks(pState, pStateMachine, pLog);
}

bool ZBDurationRecalculationAutomate::OnBeforeRequestMoveForward(PSS_StateObject*  pState,
                                                                 PSS_StateMachine* pStateMachine,
                                                                 PSS_Log*          pLog)
{
    return ZBBPAutomate::OnBeforeRequestMoveForward(pState, pStateMachine, pLog);
}

bool ZBDurationRecalculationAutomate::OnAfterMoveForward(PSS_StateObject*  pState,
                                                         PSS_StateMachine* pStateMachine,
                                                         PSS_Log*          pLog)
{
    return ZBBPAutomate::OnAfterMoveForward(pState, pStateMachine, pLog);
}

bool ZBDurationRecalculationAutomate::OnBeforeMoveBackward(PSS_StateObject*  pState,
                                                           PSS_StateMachine* pStateMachine,
                                                           PSS_Log*          pLog)
{
    return ZBBPAutomate::OnBeforeMoveBackward(pState, pStateMachine, pLog);
}

bool ZBDurationRecalculationAutomate::OnAfterMoveBackward(PSS_StateObject*  pState,
                                                          PSS_StateMachine* pStateMachine,
                                                          PSS_Log*          pLog)
{
    return ZBBPAutomate::OnAfterMoveBackward(pState, pStateMachine, pLog);
}

bool ZBDurationRecalculationAutomate::OnObjectError(PSS_StateObject*  pState,
                                                    PSS_StateMachine* pStateMachine,
                                                    PSS_Log*          pLog)
{
    return ZBBPAutomate::OnObjectError(pState, pStateMachine, pLog);
}

bool ZBDurationRecalculationAutomate::OnReachMaximumLoopCounter(PSS_Log* pLog)
{
    return ZBBPAutomate::OnReachMaximumLoopCounter(pLog);
}

bool ZBDurationRecalculationAutomate::OnReachMaximumWaitingForOtherLinksCounter(PSS_Log* pLog)
{
    return ZBBPAutomate::OnReachMaximumWaitingForOtherLinksCounter(pLog);
}

bool ZBDurationRecalculationAutomate::OnReachMaximumInPauseCounter(PSS_Log* pLog)
{
    return ZBBPAutomate::OnReachMaximumInPauseCounter(pLog);
}

bool ZBDurationRecalculationAutomate::OnNextSymbolAfterMoveForward(PSS_StateObject*  pState,
                                                                   PSS_StateMachine* pStateMachine,
                                                                   PSS_Log*          pLog)
{
    if (!ZBBPAutomate::OnNextSymbolAfterMoveForward(pState, pStateMachine, pLog))
    {
        return false;
    }

    // Only valid for the second pass
    if (GetPass() != 1)
    {
        return true;
    }

#ifdef _DEBUG
    if (pState && pState->GetSymbol() && ISA(pState->GetSymbol(), ZBSymbol))
    {
        TRACE1(_T("OnNextSymbolAfterMoveForward: symbol in the stack is %s\n"),
               dynamic_cast<ZBSymbol*>(pState->GetSymbol())->GetSymbolName());
    }
#endif

    // We must found the symbol and the link.
    // Check that we have an Entering up link
    // Now check if we have a procedure
    if (pState && pState->GetSymbol() && ISA(pState->GetSymbol(), ZBBPProcedureSymbol))
    {
        TRACE1(_T("OnNextSymbolAfterMoveForward: current Procedure is %s\n"),
               dynamic_cast<ZBSymbol*>(pState->GetSymbol())->GetSymbolName());

        // Normally we should have at least one link only
        if (pState->GetStateLinkCount() == 0)
        {
            // Log the error
            return false;
        }

        ZBBPProcedureSymbol* pProcedure = dynamic_cast<ZBBPProcedureSymbol*>(pState->GetSymbol());

        CODEdgeArray LeavingDownEdges;
        size_t LeavingDownLinkCount = pProcedure->GetEdgesLeaving_Down(LeavingDownEdges);

        if (LeavingDownLinkCount > 0)
        {
            SetCaseDurationOfProcedure(pState, LeavingDownEdges, LeavingDownLinkCount, pProcedure, pLog);
        }
    }

    // We must found the symbol and the link.
    return true;
}

bool ZBDurationRecalculationAutomate::OnBeforeMoveForward(PSS_StateObject*  pState,
                                                          PSS_StateMachine* pStateMachine,
                                                          PSS_Log*          pLog)
{
    if (!ZBBPAutomate::OnBeforeMoveForward(pState, pStateMachine, pLog))
    {
        return false;
    }

    // Only valid for the first pass
    if (GetPass() != 0)
    {
        return true;
    }

#ifdef _DEBUG
    if (pState && pState->GetSymbol() && ISA(pState->GetSymbol(), ZBSymbol))
    {
        TRACE1(_T("OnBeforeMoveForward: symbol in the stack is %s\n"),
               dynamic_cast<ZBSymbol*>(pState->GetSymbol())->GetSymbolName());
    }
#endif

    // Now check if we have a start symbol
    // Calculate Deliverables down Durations
    if (pState && pState->GetSymbol() && ISA(pState->GetSymbol(), ZBBPStartSymbol))
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pState->GetSymbol());

        TRACE1(_T("OnBeforeMoveForward: start in the stack is %s\n"), pSymbol->GetSymbolName());

        CODEdgeArray LeavingEdges;
        size_t LeavingLinkCount = pSymbol->GetEdgesLeaving(LeavingEdges);

        if (LeavingLinkCount > 0)
        {
            SetStartSymbolCaseDurationOfDownDeliverables(pState, LeavingEdges, LeavingLinkCount, pLog);
        }
    }
    else if (pState && pState->GetSymbol() && ISA(pState->GetSymbol(), ZBBPDoorSymbol))
    {
        // Now check if we have a door symbol
        // Duplicate duration information of deliverable symbols
        ZBBPDoorSymbol* pSymbol = dynamic_cast<ZBBPDoorSymbol*>(pState->GetSymbol());

        TRACE1(_T("OnBeforeMoveForward: door in the stack is %s\n"), pSymbol->GetSymbolName());

        CODEdgeArray EnteringEdges;
        size_t EnteringLinkCount = pSymbol->GetEdgesEntering(EnteringEdges);

        if (EnteringLinkCount > 0 && pSymbol->GetTwinDoorSymbol())
        {
            ZBBPDoorSymbol* pTwinDoor = pSymbol->GetTwinDoorSymbol();

            // Retreive the leaving edge of the target door
            // We need to have a link
            CODEdgeArray LeavingEdges;
            size_t LeavingLinkCount = pTwinDoor->GetEdgesLeaving(LeavingEdges);

            if (LeavingLinkCount > 0)
            {
                // Now copy the duration information coming from the entering deliverable 
                // to the leaving deliverable attached to the target door
                IODEdge* pIEdge = EnteringEdges.GetAt(0);

                // Check if a ZBLinkSymbol
                if (!static_cast<CODLinkComponent*>(pIEdge) ||
                    !ISA(static_cast<CODLinkComponent*>(pIEdge), ZBDeliverableLinkSymbol))
                {
                    return true;
                }

                ZBDeliverableLinkSymbol* pSrcLink = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

                // Now the deliverable to the target door
                pIEdge = LeavingEdges.GetAt(0);

                // Check if a ZBLinkSymbol
                if (!static_cast<CODLinkComponent*>(pIEdge) ||
                    !ISA(static_cast<CODLinkComponent*>(pIEdge), ZBDeliverableLinkSymbol))
                {
                    return true;
                }

                ZBDeliverableLinkSymbol* pDstLink = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

                // Copy the duration
                pDstLink->SetCaseDuration(pSrcLink->GetCaseDuration());
                pDstLink->SetCaseDurationMax(pSrcLink->GetCaseDurationMax());

                pDstLink->SetGreenLineDuration(pSrcLink->GetGreenLineDuration());
                pDstLink->SetTargetDuration(pSrcLink->GetTargetDuration());

                // If log and debug mode is required
                if (pLog && pLog->IsInDebugMode())
                {
                    CString message;
                    message.Format(IDS_DB_DELIV_INC_7,
                                   pSrcLink->GetSymbolName(),
                                   pDstLink->GetSymbolName(),
                                   pDstLink->GetCaseDuration(),
                                   pDstLink->GetCaseDurationMax());

                    ZBGenericSymbolErrorLine e(message);
                    pLog->AddLine(e);
                }
            }
        }
    }
    else if (pState && pState->GetSymbol() && ISA(pState->GetSymbol(), ZBBPPageSymbol))
    {
        // Now check if we have a page symbol
        // Duplicate duration information of deliverable symbols
        ZBBPPageSymbol* pSymbol = dynamic_cast<ZBBPPageSymbol*>(pState->GetSymbol());

        TRACE1(_T("OnBeforeMoveForward: page in the stack is %s\n"), pSymbol->GetSymbolName());

        CODEdgeArray EnteringEdges;
        size_t EnteringLinkCount = pSymbol->GetEdgesEntering(EnteringEdges);

        if (EnteringLinkCount > 0 && pSymbol->GetTwinPageSymbol())
        {
            ZBBPPageSymbol* pTwinPage = pSymbol->GetTwinPageSymbol();

            // Now copy the duration information coming from the entering deliverable 
            // to the leaving deliverable attached to the target page
            CODEdgeArray LeavingEdges;
            size_t LeavingLinkCount = pTwinPage->GetEdgesLeaving(LeavingEdges);

            if (LeavingLinkCount > 0)
            {
                // Now copy the duration information coming from the entering deliverable 
                // to the leaving deliverable attached to the target door
                IODEdge* pIEdge = EnteringEdges.GetAt(0);

                // Check if a ZBLinkSymbol
                if (!static_cast<CODLinkComponent*>(pIEdge) ||
                    !ISA(static_cast<CODLinkComponent*>(pIEdge), ZBDeliverableLinkSymbol))
                {
                    return true;
                }

                ZBDeliverableLinkSymbol* pSrcLink = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

                // Now the deliverable to the target door
                pIEdge = LeavingEdges.GetAt(0);

                // Check if a ZBLinkSymbol
                if (!static_cast<CODLinkComponent*>(pIEdge) ||
                    !ISA(static_cast<CODLinkComponent*>(pIEdge), ZBDeliverableLinkSymbol))
                {
                    return true;
                }

                ZBDeliverableLinkSymbol* pDstLink = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

                // Copy the duration
                pDstLink->SetCaseDuration(pSrcLink->GetCaseDuration());
                pDstLink->SetCaseDurationMax(pSrcLink->GetCaseDurationMax());

                pDstLink->SetGreenLineDuration(pSrcLink->GetGreenLineDuration());
                pDstLink->SetTargetDuration(pSrcLink->GetTargetDuration());

                // If log and debug mode is required
                if (pLog && pLog->IsInDebugMode())
                {
                    CString message;

                    message.Format(IDS_DB_DELIV_INC_7,
                                   pSrcLink->GetSymbolName(),
                                   pDstLink->GetSymbolName(),
                                   pDstLink->GetCaseDuration(),
                                   pDstLink->GetCaseDurationMax());

                    ZBGenericSymbolErrorLine e(message);
                    pLog->AddLine(e);
                }
            }
        }
    }
    else if (pState && pState->GetSymbol() && ISA(pState->GetSymbol(), ZBBPProcedureSymbol))
    {
        // Now check if we are a procedure
        // Calculate Deliverables Durations
        ZBBPProcedureSymbol* pProcedure = dynamic_cast<ZBBPProcedureSymbol*>(pState->GetSymbol());
        ZBBPProcedureSymbol* pLocalProcedureBefore = NULL;

        TRACE1(_T("OnBeforeMoveForward: procedure in the stack is %s\n"), pProcedure->GetSymbolName());

        // Now calculate the deliverable durations
        // for all leaving down, right and left deliverables
        CODEdgeArray LeavingRightEdges;
        size_t LeavingRightLinkCount = pProcedure->GetEdgesLeaving_Right(LeavingRightEdges);

        if (LeavingRightLinkCount > 0)
        {
            SetCaseDurationOfLateralDeliverables(LeavingRightEdges, LeavingRightLinkCount, pProcedure, pLog);
        }

        CODEdgeArray LeavingLeftEdges;
        size_t LeavingLeftLinkCount = pProcedure->GetEdgesLeaving_Left(LeavingLeftEdges);

        if (LeavingLeftLinkCount > 0)
        {
            SetCaseDurationOfLateralDeliverables(LeavingLeftEdges, LeavingLeftLinkCount, pProcedure, pLog);
        }

        CODEdgeArray LeavingDownEdges;
        size_t LeavingDownLinkCount = pProcedure->GetEdgesLeaving_Down(LeavingDownEdges);

        if (LeavingDownLinkCount > 0)
        {
            SetCaseDurationOfDownDeliverables(pState, LeavingDownEdges, LeavingDownLinkCount, pProcedure, pLog);
        }
    }

    return true;
}

bool ZBDurationRecalculationAutomate::SetCaseDurationOfLateralDeliverables(CODEdgeArray&            LeavingEdges,
                                                                           size_t                    LeavingLinkCount,
                                                                           ZBBPProcedureSymbol*    pProcedure,
                                                                           PSS_Log*                  pLog)
{
    for (size_t nEdgeIdx = 0; nEdgeIdx < LeavingLinkCount; ++nEdgeIdx)
    {
        IODEdge* pIEdge = LeavingEdges.GetAt(nEdgeIdx);

        // Check if a ZBLinkSymbol
        if (!static_cast<CODLinkComponent*>(pIEdge) ||
            !ISA(static_cast<CODLinkComponent*>(pIEdge), ZBDeliverableLinkSymbol))
        {
            continue;
        }

        ZBDeliverableLinkSymbol* pLink = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);
        ZBDeliverableLinkSymbol* pLocalLink = NULL;

        if (!pLink)
        {
            continue;
        }

        // Test if it is a local symbol
        if (!pLink->IsLocal())
        {
            // Locate the local symbol
            CODComponent* pComp = pLink->GetLocalSymbol();

            if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
            {
                pLocalLink = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
            }
            else
            {
                // Log the error
                return false;
            }
        }

        pLink->SetCaseDuration((pLocalLink) ? pLocalLink->GetTargetDuration() : pLink->GetTargetDuration());
        pLink->SetCaseDurationMax((pLocalLink) ? pLocalLink->GetTargetDuration() : pLink->GetTargetDuration());

        // If log and debug mode is required
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;

            message.Format(IDS_DB_DELIV_INC_1,
                           pLink->GetSymbolName(),
                           pLink->GetCaseDuration(),
                           pLink->GetCaseDurationMax());

            ZBGenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }
    }

    return true;
}

bool ZBDurationRecalculationAutomate::SetCaseDurationOfDownDeliverables(PSS_StateObject*     pState,
                                                                        CODEdgeArray&        LeavingEdges,
                                                                        std::size_t          LeavingLinkCount,
                                                                        ZBBPProcedureSymbol* pProcedure,
                                                                        PSS_Log*             pLog)
{
    // Retreive entering edges
    // for the maximum duration, the entering deliverables are added 
    // and not used in the maximum
    CODEdgeArray EnteringEdgesRight;
    CODEdgeArray EnteringEdgesLeft;
    pProcedure->GetEdgesEntering_Right(EnteringEdgesRight);
    pProcedure->GetEdgesEntering_Left(EnteringEdgesLeft);

    for (size_t nEdgeIdx = 0; nEdgeIdx < LeavingLinkCount; ++nEdgeIdx)
    {
        IODEdge* pIEdge = LeavingEdges.GetAt(nEdgeIdx);

        // Check if a ZBLinkSymbol
        if (!static_cast<CODLinkComponent*>(pIEdge) ||
            !ISA(static_cast<CODLinkComponent*>(pIEdge), ZBDeliverableLinkSymbol))
        {
            continue;
        }

        ZBDeliverableLinkSymbol* pLink = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);
        ZBDeliverableLinkSymbol* pLocalLink = NULL;

        if (!pLink)
        {
            continue;
        }

        // Test if it is a local symbol
        if (!pLink->IsLocal())
        {
            // Locate the local symbol
            CODComponent* pComp = pLink->GetLocalSymbol();

            if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
            {
                pLocalLink = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
            }
            else
            {
                // Log the error
                return false;
            }
        }

        // before doing the calculation, check which deliverable is not part of the path generated by the calculation.
        // To do that, we assume that if a duration is equal to -1, not part of the path
        double dTotalCombination = 0;

        for (std::size_t index = 0; index < pState->GetStateLinkCount(); ++index)
        {
            PSS_StateLink* pStateLink = pState->GetStateLinkAt(index);

            if (!pStateLink || !pStateLink->GetLinkSymbol())
                return false;

            // check if we have a deliverable
            if (ISA(pStateLink->GetLinkSymbol(), ZBDeliverableLinkSymbol))
            {
                ZBDeliverableLinkSymbol* pDeliverable = dynamic_cast<ZBDeliverableLinkSymbol*>(pStateLink->GetLinkSymbol());

                // not applicable for entering lateral deliverables
                if (EnteringEdgesLeft.ContainsEdge(pDeliverable) || EnteringEdgesRight.ContainsEdge(pDeliverable))
                    continue;

                // check if this deliverable is a master of the combination
                if (!pDeliverable->IsMasterOfCombination())
                    continue;

                // if the deliverable has zero for the duration and the max duration, we do assume that deliverable
                // is not part of the calculation
                if (pDeliverable->GetCaseDuration() == -1 && pDeliverable->GetCaseDurationMax() == -1)
                    continue;

                ZBDeliverableLinkSymbol* pLocalDeliverable = NULL;

                // test if it is a local symbol
                if (!pDeliverable->IsLocal())
                {
                    // locate the local symbol
                    CODComponent* pComp = pDeliverable->GetLocalSymbol();

                    if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
                        pLocalDeliverable = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
                    else
                        return false;
                }

                // calculate the average Value
                const float CombMaxPercentage =
                    pLocalDeliverable ? pLocalDeliverable->GetCombinationMaxPercentage() :
                    pDeliverable->GetCombinationMaxPercentage();

                // error
                if (CombMaxPercentage == float(INT_MAX))
                    continue;

                dTotalCombination += double(CombMaxPercentage);
            }
        }

        double dValue = 0;
        double dValueMax = 0;
        double dLateralValue = 0;
        double dLateralValueMax = 0;

        // Calculate the sum of durations for each incoming deliverables
        // For the maximum
        // Take the maximum of entering deliverables.
        // And the maximum of lateral entering deliverables
        // For the average
        // Take the sum of entering deliverables * by the % of the combination based 100
        // And the maximum of lateral entering deliverables * Deliverable Quantity / Procedure Activation

        for (std::size_t index = 0; index < pState->GetStateLinkCount(); ++index)
        {
            PSS_StateLink* pStateLink = pState->GetStateLinkAt(index);

            if (!pStateLink || !pStateLink->GetLinkSymbol())
                return false;

            // check if we have a deliverable
            if (ISA(pStateLink->GetLinkSymbol(), ZBDeliverableLinkSymbol))
            {
                ZBDeliverableLinkSymbol* pDeliverable = dynamic_cast<ZBDeliverableLinkSymbol*>(pStateLink->GetLinkSymbol());
                ZBDeliverableLinkSymbol* pLocalDeliverable = NULL;

                // test if it is a local symbol
                if (!pDeliverable->IsLocal())
                {
                    // locate the local symbol
                    CODComponent* pComp = pDeliverable->GetLocalSymbol();

                    if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
                        pLocalDeliverable = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
                    else
                        return false;
                }

                // calculate the max Value
                double sum = pLocalDeliverable ? pLocalDeliverable->GetCaseDuration() : pDeliverable->GetCaseDuration();

                sum += pDeliverable->GetGreenLineDuration();

                double sumMax = pLocalDeliverable ? pLocalDeliverable->GetCaseDurationMax() : pDeliverable->GetCaseDurationMax();

                sumMax += pDeliverable->GetGreenLineDuration();

                // if an entering lateral deliverable
                if (EnteringEdgesLeft.ContainsEdge(pDeliverable) || EnteringEdgesRight.ContainsEdge(pDeliverable))
                {
                    // calculate the max
                    dLateralValueMax = __max(sumMax, dLateralValueMax);

                    // calculate the average value by taking the maximum of laterals
                    double quantity = (pLocalDeliverable ? double(pLocalDeliverable->GetQuantity()) : double(pDeliverable->GetQuantity()));

                    if (quantity == 0.0)
                    {
                        if (pLog)
                        {
                            ZBGenericSymbolErrorLine e(IDS_AL_DELIV_QUANTITY_ZERO,
                                                       pDeliverable->GetSymbolName(),
                                                       pDeliverable->GetAbsolutePath());

                            pLog->AddLine(e);
                        }

                        quantity = 1.0;
                    }

                    double avg = quantity / double(pProcedure->GetProcedureActivation());
                    dLateralValue = __max((sum * avg), dLateralValue);
                }
                else
                {
                    // check if this deliverable is a master of the combination
                    if (!pDeliverable->IsMasterOfCombination())
                        continue;

                    // Calculate the max
                    dValueMax = __max(sumMax, dValueMax);

                    // calculate the average Value
                    float combMaxPercentage = pLocalDeliverable ? pLocalDeliverable->GetCombinationMaxPercentage() : pDeliverable->GetCombinationMaxPercentage();

                    if (combMaxPercentage == float(INT_MAX))
                    {
                        if (pLog)
                        {
                            ZBGenericSymbolErrorLine e(IDS_AL_DELIV_NOTDEFINED_COMBINATION,
                                                       pDeliverable->GetSymbolName(),
                                                       pDeliverable->GetAbsolutePath());

                            pLog->AddLine(e);
                        }

                        combMaxPercentage = 1.0f;
                    }

                    // divide by the sum of the combination percentage. This to rebalance in base 100%
                    dValue += (sum * double(combMaxPercentage) / dTotalCombination);
                }

                // if log and debug mode is required
                if (pLog && pLog->IsInDebugMode())
                {
                    CString message;

                    message.Format(IDS_DB_DELIV_INC_2,
                                   pLink->GetSymbolName(),
                                   pDeliverable->GetSymbolName(),
                                   dValue,
                                   dValueMax);

                    ZBGenericSymbolErrorLine e(message);
                    pLog->AddLine(e);

                    message.Format(IDS_DB_DELIV_INC_5,
                                   pLink->GetSymbolName(),
                                   pDeliverable->GetSymbolName(),
                                   dLateralValue,
                                   dLateralValueMax);

                    ZBGenericSymbolErrorLine e2(message);
                    pLog->AddLine(e2);
                }
            }
        }

        pLink->SetCaseDuration(((pLocalLink) ? pLocalLink->GetTargetDuration() : pLink->GetTargetDuration()) + dValue + dLateralValue);
        pLink->SetCaseDurationMax(((pLocalLink) ? pLocalLink->GetTargetDuration() : pLink->GetTargetDuration()) + dValueMax + dLateralValueMax);

        // If log and debug mode is required
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;

            message.Format(IDS_DB_DELIV_INC_1,
                           pLink->GetSymbolName(),
                           pLink->GetCaseDuration(),
                           pLink->GetCaseDurationMax());

            ZBGenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }
    }

    return true;
}

bool ZBDurationRecalculationAutomate::SetStartSymbolCaseDurationOfDownDeliverables(PSS_StateObject*   pState,
                                                                                   CODEdgeArray&    LeavingEdges,
                                                                                   size_t            LeavingLinkCount,
                                                                                   PSS_Log*          pLog)
{
    for (size_t nEdgeIdx = 0; nEdgeIdx < LeavingLinkCount; ++nEdgeIdx)
    {
        IODEdge* pIEdge = LeavingEdges.GetAt(nEdgeIdx);

        // Check if a ZBLinkSymbol
        if (!static_cast<CODLinkComponent*>(pIEdge) ||
            !ISA(static_cast<CODLinkComponent*>(pIEdge), ZBDeliverableLinkSymbol))
        {
            continue;
        }

        ZBDeliverableLinkSymbol* pLink = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

        if (!pLink)
        {
            continue;
        }

        // Assigns the duration and duration maximum
        // using the target duration
        pLink->SetCaseDuration(pLink->GetTargetDuration());
        pLink->SetCaseDurationMax(pLink->GetTargetDuration());

        // If log and debug mode is required
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;

            message.Format(IDS_DB_DELIV_INC_3,
                           pLink->GetSymbolName(),
                           pLink->GetCaseDuration(),
                           pLink->GetCaseDurationMax());

            ZBGenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }
    }

    return true;
}

bool ZBDurationRecalculationAutomate::SetCaseDurationOfProcedure(PSS_StateObject*     pState,
                                                                 CODEdgeArray&        LeavingEdges,
                                                                 std::size_t          LeavingLinkCount,
                                                                 ZBBPProcedureSymbol* pProcedure,
                                                                 PSS_Log*             pLog)
{
    // First, we need to check if we are coming back from
    // a lateral loop.
    // To detect that, we need to check if we have a coming up
    // deliverable.
    // if not, do nothing.
    // Retreive entering edges for laterals
    CODEdgeArray EnteringEdgesRight;
    CODEdgeArray EnteringEdgesLeft;
    pProcedure->GetEdgesEntering_Right(EnteringEdgesRight);
    pProcedure->GetEdgesEntering_Left(EnteringEdgesLeft);

    bool HasDeliverable = false;

    for (size_t Index = 0; Index < pState->GetStateLinkCount(); ++Index)
    {
        PSS_StateLink* pStateLink = pState->GetStateLinkAt(Index);

        if (!pStateLink || !pStateLink->GetLinkSymbol())
        {
            // Log the error
            return false;
        }

        // Check if we have a deliverable
        if (ISA(pStateLink->GetLinkSymbol(), ZBDeliverableLinkSymbol))
        {
            ZBDeliverableLinkSymbol* pDeliverable =
                dynamic_cast<ZBDeliverableLinkSymbol*>(pStateLink->GetLinkSymbol());

            // If an entering lateral deliverable
            if (EnteringEdgesLeft.ContainsEdge(pDeliverable) ||
                EnteringEdgesRight.ContainsEdge(pDeliverable))
            {
                continue;
            }

            HasDeliverable = true;
        }
    }

    if (HasDeliverable == false)
    {
        return true;
    }

    double dNumeratorValue = 0;
    double dNumeratorValueMax = 0;
    double dDenomValue = 0;

    for (std::size_t nEdgeIdx = 0; nEdgeIdx < LeavingLinkCount; ++nEdgeIdx)
    {
        IODEdge* pIEdge = LeavingEdges.GetAt(nEdgeIdx);

        // Check if a ZBLinkSymbol
        if (!static_cast<CODLinkComponent*>(pIEdge) ||
            !ISA(static_cast<CODLinkComponent*>(pIEdge), ZBDeliverableLinkSymbol))
        {
            continue;
        }

        ZBDeliverableLinkSymbol* pLink = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);
        ZBDeliverableLinkSymbol* pLocalLink = NULL;

        if (!pLink)
        {
            continue;
        }

        // Test if it is a local symbol
        if (!pLink->IsLocal())
        {
            // Locate the local symbol
            CODComponent* pComp = pLink->GetLocalSymbol();

            if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
            {
                pLocalLink = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
            }
            else
            {
                // Log the error
                return false;
            }
        }

        // Calculate the numerator Value
        double val = ((pLocalLink) ? pLocalLink->GetCaseDuration() : pLink->GetCaseDuration()) *
            ((pLocalLink) ? (double)pLocalLink->GetOutWorkloadPercent() : (double)pLink->GetOutWorkloadPercent());

        dNumeratorValue += val;

        double valMax = ((pLocalLink) ? pLocalLink->GetCaseDurationMax() : pLink->GetCaseDurationMax()) *
            ((pLocalLink) ? (double)pLocalLink->GetOutWorkloadPercent() : (double)pLink->GetOutWorkloadPercent());

        dNumeratorValueMax += valMax;

        // If log and debug mode is required
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;

            message.Format(IDS_DB_PROCEDURE_INC_3,
                           pProcedure->GetSymbolName(),
                           pLink->GetSymbolName(),
                           val);

            ZBGenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }

        // Calculate the denominator Value
        dDenomValue += ((pLocalLink) ? (double)pLocalLink->GetOutWorkloadPercent() : (double)pLink->GetOutWorkloadPercent());
    }

    double dDelivDurationValue = 0;
    double dDelivDurationValueMax = 0;
    double SumQuantityDeliv = 0;

    CODEdgeArray EnteringEdgesUp;
    size_t EnteringEdgesUpCount = pProcedure->GetEdgesEntering_Up(EnteringEdgesUp);

    for (std::size_t nEdgeIdx = 0; nEdgeIdx < EnteringEdgesUpCount; ++nEdgeIdx)
    {
        IODEdge* pIEdge = EnteringEdgesUp.GetAt(nEdgeIdx);

        // Check if a ZBLinkSymbol
        if (!static_cast<CODLinkComponent*>(pIEdge) ||
            !ISA(static_cast<CODLinkComponent*>(pIEdge), ZBDeliverableLinkSymbol))
        {
            continue;
        }

        ZBDeliverableLinkSymbol* pDeliverable = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);
        ZBDeliverableLinkSymbol* pLocalDeliverable = NULL;

        // Test if it is a local symbol
        if (!pDeliverable->IsLocal())
        {
            // Locate the local symbol
            CODComponent* pComp = pDeliverable->GetLocalSymbol();

            if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
            {
                pLocalDeliverable = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
            }
            else
            {
                // Log the error
                return false;
            }
        }

        // If the deliverable has -1 for the duration and the max duration,
        // we do assume that deliverable is not part of the calculation
        if (pDeliverable->GetCaseDuration() == -1 &&
            pDeliverable->GetCaseDurationMax() == -1)
        {
            continue;
        }

        // Keep the sum of quantity deliverables
        SumQuantityDeliv += ((pLocalDeliverable) ? (double)pLocalDeliverable->GetQuantity() : (double)pDeliverable->GetQuantity());

        // Sum the values of duration
        dDelivDurationValue += (((pLocalDeliverable) ? pLocalDeliverable->GetCaseDuration() : pDeliverable->GetCaseDuration()) *
            ((pLocalDeliverable) ? (double)pLocalDeliverable->GetQuantity() : (double)pDeliverable->GetQuantity()));

        dDelivDurationValueMax += (((pLocalDeliverable) ? pLocalDeliverable->GetCaseDurationMax() : pDeliverable->GetCaseDurationMax()) *
            ((pLocalDeliverable) ? (double)pLocalDeliverable->GetQuantity() : (double)pDeliverable->GetQuantity()));

        // If log and debug mode is required
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;

            message.Format(IDS_DB_DELIV_INC_6,
                           pDeliverable->GetSymbolName(),
                           ((pLocalDeliverable) ? pLocalDeliverable->GetCaseDuration() : pDeliverable->GetCaseDuration()),
                           ((pLocalDeliverable) ? pLocalDeliverable->GetCaseDurationMax() : pDeliverable->GetCaseDurationMax()),
                           ((pLocalDeliverable) ? (double)pLocalDeliverable->GetQuantity() : (double)pDeliverable->GetQuantity()));

            ZBGenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }
    }

    // Sets the procedure processing duration
    pProcedure->SetProcessingDuration((dNumeratorValue / dDenomValue) - (dDelivDurationValue / SumQuantityDeliv));
    pProcedure->SetProcessingDurationMax((dNumeratorValueMax / dDenomValue) - (dDelivDurationValueMax / SumQuantityDeliv));

    // If log and debug mode is required
    if (pLog && pLog->IsInDebugMode())
    {
        CString message;

        message.Format(IDS_DB_PROCEDURE_INC_2,
                       pProcedure->GetSymbolName(),
                       pProcedure->GetProcessingDuration(),
                       pProcedure->GetProcessingDurationMax());

        ZBGenericSymbolErrorLine e(message);
        pLog->AddLine(e);

        message.Format(IDS_DB_PROCEDURE_INC_4,
                       pProcedure->GetSymbolName(),
                       dNumeratorValue,
                       dDenomValue,
                       dDelivDurationValue,
                       SumQuantityDeliv);

        ZBGenericSymbolErrorLine e2(message);
        pLog->AddLine(e2);

        message.Format(IDS_DB_PROCEDURE_INC_6,
                       pProcedure->GetSymbolName(),
                       dNumeratorValueMax,
                       dDenomValue,
                       dDelivDurationValueMax,
                       SumQuantityDeliv);

        ZBGenericSymbolErrorLine e3(message);
        pLog->AddLine(e3);
    }

    return true;
}
