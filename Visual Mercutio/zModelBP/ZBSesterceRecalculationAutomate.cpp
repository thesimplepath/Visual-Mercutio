// ZBSesterceRecalculationAutomate.cpp: implementation of the ZBSesterceRecalculationAutomate class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ZBSesterceRecalculationAutomate.h"

// processsoft
#include "zWkf\PSS_StateMachine.h"

#include "ZUCheckSesterceConsistency.h"
#include "ZUCheckSesterceUnit.h"
#include "ZUProcessCalculateTotals.h"

#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"

#include "ZBBPDoorSymbol.h"
#include "ZBBPPageSymbol.h"
#include "ZBBPProcedureSymbol.h"
#include "ZBBPProcessSymbol.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"
#include "ZBDeliverableLinkSymbol.h"

#include "zModel\PSS_ODSymbolManipulator.h"

// Include files for log
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 20 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBSesterceRecalculationAutomate::ZBSesterceRecalculationAutomate(PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                                 PSS_Log*                    pLog    /*= NULL*/)
    : ZBBPAutomate(pModel, pLog)
{}

ZBSesterceRecalculationAutomate::~ZBSesterceRecalculationAutomate()
{}

bool ZBSesterceRecalculationAutomate::OnStart(PSS_Log* pLog)
{
    bool RetValue = ZBBPAutomate::OnStart(pLog);

    // If log
    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_START_SESTERCESCALCULATION);
        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    // Do an deep check before lauching the calculation of the model
    ZUCheckSesterceConsistency Check(m_pModel, pLog);
    Check.CheckModel();

    // Assigns the error counter and the warning counter
    SetErrorCounter(Check.GetErrorCounter());
    SetWarningCounter(Check.GetWarningCounter());

    if (m_pModel && ISA(m_pModel, PSS_ProcessGraphModelMdl) &&
        dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pModel)->MainUserGroupIsValid())
    {
        // Do a unit check and assignement before lauching the calculation of the model
        ZUCheckSesterceUnit CheckUnit(m_pModel);
        CheckUnit.SetLog(pLog);
        CheckUnit.Navigate();

        // Assigns the error counter and the warning counter
        SetErrorCounter(GetErrorCounter() + CheckUnit.GetErrorCounter());
        SetWarningCounter(GetWarningCounter() + CheckUnit.GetWarningCounter());
    }
    else
    {
        // If log
        if (pLog)
        {
            CString message;
            message.LoadString(IDS_AL_USERGROUP_NOTINLINE);
            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);
        }
    }

    // Don't continue if we encounter error.
    if (Check.GetErrorCounter() > 0)
    {
        return false;
    }

    return RetValue;
}
bool ZBSesterceRecalculationAutomate::OnStop(PSS_Log* pLog)
{
    // If log
    if (pLog)
    {
        CString message;
        message.Format(IDS_AL_START_PROCESSCALCULATION, m_pModel->GetModelName());
        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    // At the end of the model calculation,
    // calculates process forecast values.
    ZUProcessCalculateTotals ProcessCalculateTotals(m_pModel, NULL);

    ProcessCalculateTotals.Navigate();

    // If log
    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_STOP_PROCESSCALCULATION);
        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    return ZBBPAutomate::OnStop(pLog);
}

bool ZBSesterceRecalculationAutomate::OnPause(PSS_Log* pLog)
{
    return ZBBPAutomate::OnPause(pLog);
}

bool ZBSesterceRecalculationAutomate::OnResume(PSS_Log* pLog)
{
    return ZBBPAutomate::OnResume(pLog);
}

//////////////////////////////////////////////////////////////////////
// Call-back workflow operations
bool ZBSesterceRecalculationAutomate::OnObjectIsFinished(PSS_StateObject*  pState,
                                                         PSS_StateMachine* pStateMachine,
                                                         PSS_Log*            pLog)
{
    return ZBBPAutomate::OnObjectIsFinished(pState, pStateMachine, pLog);
}

bool ZBSesterceRecalculationAutomate::OnObjectIsPaused(PSS_StateObject*  pState,
                                                       PSS_StateMachine* pStateMachine,
                                                       PSS_Log*            pLog)
{
    return ZBBPAutomate::OnObjectIsPaused(pState, pStateMachine, pLog);
}

bool ZBSesterceRecalculationAutomate::OnObjectIsWaitingForOtherLinks(PSS_StateObject*  pState,
                                                                     PSS_StateMachine* pStateMachine,
                                                                     PSS_Log*            pLog)
{
    return ZBBPAutomate::OnObjectIsWaitingForOtherLinks(pState, pStateMachine, pLog);
}

bool ZBSesterceRecalculationAutomate::OnBeforeRequestMoveForward(PSS_StateObject*  pState,
                                                                 PSS_StateMachine* pStateMachine,
                                                                 PSS_Log*            pLog)
{
    return ZBBPAutomate::OnBeforeRequestMoveForward(pState, pStateMachine, pLog);
}

bool ZBSesterceRecalculationAutomate::OnNextSymbolAfterMoveForward(PSS_StateObject*  pState,
                                                                   PSS_StateMachine* pStateMachine,
                                                                   PSS_Log*            pLog)
{
    if (!ZBBPAutomate::OnNextSymbolAfterMoveForward(pState, pStateMachine, pLog))
    {
        return false;
    }

#ifdef _DEBUG
    if (pState && pState->GetSymbol() && ISA(pState->GetSymbol(), PSS_Symbol))
    {
        TRACE1(_T("OnNextSymbolAfterMoveForward: symbol in the stack is %s\n"),
               dynamic_cast<PSS_Symbol*>(pState->GetSymbol())->GetSymbolName());
    }
#endif

    // We must found the symbol and the link.
    // Check that we have an Entering up link
    // Now check if we are a procedure, a page, a door or a stop symbol
    // If we are,
    // 1. calculate the procedure activation of the last stacked procedure
    // 2. the deliverable quantity
    // 3. the deliverable workload forecast
    // 4. the deliverable cost
    // 5. the procedure cost
    // 6. the procedure forecast cost
    // 7. the procedure cost per activity
    if (pState && pState->GetSymbol() &&
        (ISA(pState->GetSymbol(), ZBBPProcedureSymbol) ||
         ISA(pState->GetSymbol(), ZBBPPageSymbol) ||
         ISA(pState->GetSymbol(), ZBBPDoorSymbol) ||
         ISA(pState->GetSymbol(), ZBBPStopSymbol)))
    {
        TRACE1(_T("OnNextSymbolAfterMoveForward: current symbol is %s\n"),
               dynamic_cast<PSS_Symbol*>(pState->GetSymbol())->GetSymbolName());

        // Normally we should have at least one link only
        if (pState->GetStateLinkCount() == 0)
        {
            // Log the error
            return false;
        }

        // Retrieve from the state machine the object before the current.
        // One object before the current
        PSS_StateObject* pStateObjectBefore = pStateMachine->PopStateObjectNoRemove(1);

        if (!pStateObjectBefore)
        {
            // Log the error
            return false;
        }

        if (!pStateObjectBefore->GetSymbol())
        {
            // Not necessarily an error, then return true
            TRACE(_T("OnNextSymbolAfterMoveForward: no object before\n"));
            return true;
        }

        // Now check the object before
        if (ISA(pStateObjectBefore->GetSymbol(), ZBBPProcedureSymbol))
        {
            ZBBPProcedureSymbol* pProcedureBefore =
                dynamic_cast<ZBBPProcedureSymbol*>(pStateObjectBefore->GetSymbol());

            ZBBPProcedureSymbol* pLocalProcedureBefore = NULL;

            // Test if it is a local symbol
            if (!pProcedureBefore->IsLocal())
            {
                // Locate the local symbol
                CODComponent* pComp = pProcedureBefore->GetLocalSymbol();

                if (pComp && ISA(pComp, ZBBPProcedureSymbol))
                {
                    pLocalProcedureBefore = dynamic_cast<ZBBPProcedureSymbol*>(pComp);
                }
                else
                {
                    // Log the error
                    return false;
                }

                TRACE1(_T("OnNextSymbolAfterMoveForward: retrieve local procedure %s\n"),
                       pLocalProcedureBefore->GetSymbolName());
            }

            TRACE1(_T("OnNextSymbolAfterMoveForward: procedure before is %s\n"),
                   pProcedureBefore->GetSymbolName());

            // Now rung through all links and calculate their quantities
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

                    TRACE1(_T("OnNextSymbolAfterMoveForward: deliverable in the stack%s\n"),
                           pDeliverable->GetSymbolName());

                    // Test if it is a local symbol
                    if (!pDeliverable->IsLocal())
                    {
                        // Locate the local symbol
                        CODComponent* pComp = pDeliverable->GetLocalSymbol();

                        if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
                        {
                            pDeliverable = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
                        }
                        else
                        {
                            // Log the error
                            return false;
                        }

                        TRACE1(_T("OnNextSymbolAfterMoveForward: retrieve local deliverable %s\n"),
                               pDeliverable->GetSymbolName());
                    }

                    PSS_AnnualNumberPropertiesBP qValue;

                    // If the quantity is not locked
                    if (pDeliverable->GetLockQuantityYear() == false)
                    {
                        // Now calculate
                        if (pLocalProcedureBefore)
                        {
                            qValue = pLocalProcedureBefore->GetProcedureActivation() *
                                (double)pLocalProcedureBefore->GetMultiplier();
                        }
                        else
                        {
                            qValue = pProcedureBefore->GetProcedureActivation() *
                                (double)pProcedureBefore->GetMultiplier();
                        }

                        qValue *= (double)pDeliverable->GetOutWorkloadPercent();
                    }
                    else
                    {
                        qValue = pDeliverable->GetQuantity();

                        // If log 
                        if (pLog)
                        {
                            PSS_GenericSymbolErrorLine e(IDS_AL_DELIV_QUANTITY_LOCKED,
                                                         pDeliverable->GetSymbolName(),
                                                         pDeliverable->GetAbsolutePath());

                            pLog->AddLine(e);
                        }

                        // JMR-MODIF - Le 21 mars 2006 - Ajout du code d'incrémentation des avertissements.
                        IncrementWarningCounter();
                    }

                    // Check if the force equalizer is set
                    if (pDeliverable->GetForceEqualizer())
                    {
                        pDeliverable->SetQuantityUsingOriginalEqualizer(qValue);

                        // If log, advise about forcing the equalizer
                        if (pLog)
                        {
                            PSS_GenericSymbolErrorLine e(IDS_AL_DELIV_QUANTITY_FORCED,
                                                         pDeliverable->GetSymbolName(),
                                                         pDeliverable->GetAbsolutePath());

                            pLog->AddLine(e);
                        }

                        // JMR-MODIF - Le 21 mars 2006 - Ajout du code d'incrémentation des avertissements.
                        IncrementWarningCounter();
                    }
                    else
                    {
                        // If not necessary to force
                        pDeliverable->SetQuantity(qValue);
                    }

                    // If log and debug mode is required
                    if (pLog && pLog->IsInDebugMode())
                    {
                        CString message;
                        message.Format(IDS_AL_DELIV_QUANTITY_SUM,
                                       pDeliverable->GetSymbolName(),
                                       (double)pDeliverable->GetQuantity());

                        PSS_GenericSymbolErrorLine e(message);
                        pLog->AddLine(e);

                        // JMR-MODIF - Le 21 mars 2006 - Ajout du code d'incrémentation des avertissements.
                        IncrementWarningCounter();
                    }

                    // Now calculate the workload forecast
                    qValue = pDeliverable->GetQuantity() * pDeliverable->GetProcessingTime();
                    pDeliverable->SetWorkloadForecast(qValue);

                    // If log and debug mode is required
                    if (pLog && pLog->IsInDebugMode())
                    {
                        CString message;
                        message.Format(IDS_AL_DELIV_WORKLOAD,
                                       pDeliverable->GetSymbolName(),
                                       (double)pDeliverable->GetWorkloadForecast());

                        PSS_GenericSymbolErrorLine e(message);
                        pLog->AddLine(e);

                        // JMR-MODIF - Le 21 mars 2006 - Ajout du code d'incrémentation des avertissements.
                        IncrementWarningCounter();
                    }
                }
            }
        }

        // We can calculate the cost for each deliverables
        // Now rung through all links
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

                // Test if it is a local symbol
                if (!pDeliverable->IsLocal())
                {
                    // Locate the local symbol
                    CODComponent* pComp = pDeliverable->GetLocalSymbol();

                    if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
                    {
                        pDeliverable = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
                    }
                    else
                    {
                        // Log the error
                        return false;
                    }
                }

                // Now calculate the cost
                PSS_AnnualNumberPropertiesBP qValue =
                    pDeliverable->GetQuantity() * (double)pDeliverable->GetUnitaryCost();

                pDeliverable->SetCost(qValue);

                // If log and debug mode is required
                if (pLog && pLog->IsInDebugMode())
                {
                    CString message;
                    message.Format(IDS_AL_DELIV_COST,
                                   pDeliverable->GetSymbolName(),
                                   (double)pDeliverable->GetCost());

                    PSS_GenericSymbolErrorLine e(message);
                    pLog->AddLine(e);

                    // JMR-MODIF - Le 21 mars 2006 - Ajout du code d'incrémentation des avertissements.
                    IncrementWarningCounter();
                }
            }
        }

        // Prepare the procedure cost calculation
        // and after the forecast cost and the cost per activation
        if (ISA(pStateObjectBefore->GetSymbol(), ZBBPProcedureSymbol))
        {
            ZBBPProcedureSymbol* pProcedureBefore =
                dynamic_cast<ZBBPProcedureSymbol*>(pStateObjectBefore->GetSymbol());

            ZBBPProcedureSymbol* pLocalProcedureBefore = NULL;

            // Test if it is a local symbol
            if (!pProcedureBefore->IsLocal())
            {
                // Locate the local symbol
                CODComponent* pComp = pProcedureBefore->GetLocalSymbol();

                if (pComp && ISA(pComp, ZBBPProcedureSymbol))
                {
                    pLocalProcedureBefore = dynamic_cast<ZBBPProcedureSymbol*>(pComp);
                }
                else
                {
                    // Log the error
                    return false;
                }

                TRACE1(_T("OnNextSymbolAfterMoveForward: retrieve local procedure %s\n"),
                       pLocalProcedureBefore->GetSymbolName());
            }

            PSS_AnnualNumberPropertiesBP qValue;

            if (pLocalProcedureBefore)
            {
                qValue = pLocalProcedureBefore->GetProcedureActivation() *
                    ((double)pLocalProcedureBefore->GetUnitaryCost());
            }
            else
            {
                qValue = pProcedureBefore->GetProcedureActivation() *
                    ((double)pProcedureBefore->GetUnitaryCost());
            }

            // Take all leaving down and right deliverables
            CODEdgeArray LeavingRightEdges;
            size_t LeavingRightLinkCount = pProcedureBefore->GetEdgesLeaving_Right(LeavingRightEdges);

            if (LeavingRightLinkCount > 0)
            {
                for (size_t nEdgeIdx = 0; nEdgeIdx < LeavingRightLinkCount; ++nEdgeIdx)
                {
                    IODEdge* pIEdge = LeavingRightEdges.GetAt(nEdgeIdx);

                    // Check if a PSS_LinkSymbol
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

                    // Test if it is a local symbol
                    if (!pLink->IsLocal())
                    {
                        // Locate the local symbol
                        CODComponent* pComp = pLink->GetLocalSymbol();

                        if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
                        {
                            pLink = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
                        }
                        else
                        {
                            // Log the error
                            return false;
                        }
                    }

                    // Now add the deliverable cost value
                    qValue += pLink->GetCost();
                }
            }

            CODEdgeArray LeavingDownEdges;
            size_t LeavingDownLinkCount = pProcedureBefore->GetEdgesLeaving_Down(LeavingDownEdges);

            if (LeavingDownLinkCount > 0)
            {
                for (size_t nEdgeIdx = 0; nEdgeIdx < LeavingDownLinkCount; ++nEdgeIdx)
                {
                    IODEdge* pIEdge = LeavingDownEdges.GetAt(nEdgeIdx);

                    // Check if a PSS_LinkSymbol
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

                    // Test if it is a local symbol
                    if (!pLink->IsLocal())
                    {
                        // Locate the local symbol
                        CODComponent* pComp = pLink->GetLocalSymbol();

                        if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
                        {
                            pLink = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
                        }
                        else
                        {
                            // Log the error
                            return false;
                        }
                    }

                    // Now add the deliverable cost value
                    qValue += pLink->GetCost();
                }
            }

            if (pLocalProcedureBefore)
            {
                pLocalProcedureBefore->SetProcedureCost(qValue);
            }
            else
            {
                pProcedureBefore->SetProcedureCost(qValue);
            }

            // If log and debug mode is required
            if (pLog && pLog->IsInDebugMode())
            {
                CString message;

                if (pLocalProcedureBefore)
                {
                    message.Format(IDS_AL_PROCESS_COST_OUTOFTIME,
                                   pLocalProcedureBefore->GetSymbolName(),
                                   (double)pLocalProcedureBefore->GetProcedureCost());
                }
                else
                {
                    message.Format(IDS_AL_PROCESS_COST_OUTOFTIME,
                                   pProcedureBefore->GetSymbolName(),
                                   (double)pProcedureBefore->GetProcedureCost());
                }

                PSS_GenericSymbolErrorLine e(message);
                pLog->AddLine(e);

                // JMR-MODIF - Le 21 mars 2006 - Ajout du code d'incrémentation des avertissements.
                IncrementWarningCounter();
            }

            // Calculate the procedure cost forecast
            if (pLocalProcedureBefore)
            {
                qValue = pLocalProcedureBefore->GetProcedureWorkloadForecast() *
                    (double)pLocalProcedureBefore->GetUnitCost();
                qValue += pLocalProcedureBefore->GetProcedureCost();
                pLocalProcedureBefore->SetProcedureCostForecast(qValue);
            }
            else
            {
                qValue = pProcedureBefore->GetProcedureWorkloadForecast() *
                    (double)pProcedureBefore->GetUnitCost();
                qValue += pProcedureBefore->GetProcedureCost();
                pProcedureBefore->SetProcedureCostForecast(qValue);
            }

            // If log and debug mode is required
            if (pLog && pLog->IsInDebugMode())
            {
                CString message;

                if (pLocalProcedureBefore)
                {
                    message.Format(IDS_AL_PROCESS_COST_PREV,
                                   pLocalProcedureBefore->GetSymbolName(),
                                   (double)pLocalProcedureBefore->GetProcedureCostForecast());
                }
                else
                {
                    message.Format(IDS_AL_PROCESS_COST_PREV,
                                   pProcedureBefore->GetSymbolName(),
                                   (double)pProcedureBefore->GetProcedureCostForecast());
                }

                PSS_GenericSymbolErrorLine e(message);
                pLog->AddLine(e);

                // JMR-MODIF - Le 21 mars 2006 - Ajout du code d'incrémentation des avertissements.
                IncrementWarningCounter();
            }

            // Calculate the procedure cost per activation
            double value = 0;

            if (pLocalProcedureBefore)
            {
                if (pLocalProcedureBefore->GetProcedureActivation() != 0)
                {
                    value = (double)pLocalProcedureBefore->GetProcedureCostForecast() /
                        (double)pLocalProcedureBefore->GetProcedureActivation();
                }

                pLocalProcedureBefore->SetProcedureCostPerActivity(value);
            }
            else
            {
                if (pProcedureBefore->GetProcedureActivation() != 0)
                {
                    value = (double)pProcedureBefore->GetProcedureCostForecast() /
                        (double)pProcedureBefore->GetProcedureActivation();
                }

                pProcedureBefore->SetProcedureCostPerActivity(value);
            }

            // If log and debug mode is required
            if (pLog && pLog->IsInDebugMode())
            {
                CString message;
                message.Format(IDS_AL_PROCESS_COST_BYPROC,
                               pProcedureBefore->GetSymbolName(),
                               value);

                PSS_GenericSymbolErrorLine e(message);
                pLog->AddLine(e);

                // JMR-MODIF - Le 21 mars 2006 - Ajout du code d'incrémentation des avertissements.
                IncrementWarningCounter();
            }
        }
    }

    return true;
}

bool ZBSesterceRecalculationAutomate::OnBeforeMoveForward(PSS_StateObject*  pState,
                                                          PSS_StateMachine* pStateMachine,
                                                          PSS_Log*            pLog)
{
    if (!ZBBPAutomate::OnBeforeMoveForward(pState, pStateMachine, pLog))
        return false;

#ifdef _DEBUG
    if (pState && pState->GetSymbol() && ISA(pState->GetSymbol(), PSS_Symbol))
    {
        TRACE1(_T("OnBeforeMoveForward: symbol in the stack is %s\n"),
               dynamic_cast<PSS_Symbol*>(pState->GetSymbol())->GetSymbolName());
    }
#endif

    // Now check if we are a procedure
    // If we are, calculate the procedure activation
    if (pState && pState->GetSymbol() && ISA(pState->GetSymbol(), ZBBPProcedureSymbol))
    {
        ZBBPProcedureSymbol* pProcedure = dynamic_cast<ZBBPProcedureSymbol*>(pState->GetSymbol());
        ZBBPProcedureSymbol* pLocalProcedureBefore = NULL;

        // Test if it is a local symbol
        if (!pProcedure->IsLocal())
        {
            // Locate the local symbol
            CODComponent* pComp = pProcedure->GetLocalSymbol();

            if (pComp && ISA(pComp, ZBBPProcedureSymbol))
            {
                pLocalProcedureBefore = dynamic_cast<ZBBPProcedureSymbol*>(pComp);
            }
            else
            {
                // Log the error
                return false;
            }

            TRACE1(_T("OnNextSymbolAfterMoveForward: retrieve local procedure %s\n"),
                   pLocalProcedureBefore->GetSymbolName());
        }

        TRACE1(_T("OnBeforeMoveForward: procedure in the stack is %s\n"),
               pProcedure->GetSymbolName());

        if (pLocalProcedureBefore)
        {
            pLocalProcedureBefore->SetProcedureActivation(pLocalProcedureBefore->CalculateProcedureActivation());
        }
        else
        {
            // RS-MODIF 18.08.05 cette routine effectue une égalisation alors qu'on veut conserver la saisonnalité
            //pProcedure->SetProcedureActivation( pProcedure->CalculateProcedureActivation() );
            PSS_AnnualNumberPropertiesBP myEqualizer = pProcedure->CalculateProcedureActivation();
            pProcedure->SetProcedureActivation(myEqualizer);
        }

        // If log and debug mode is required
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;

            if (pLocalProcedureBefore)
            {
                message.Format(IDS_AL_PROCESS_CALC_ACTIV,
                               pLocalProcedureBefore->GetSymbolName(),
                               (double)pLocalProcedureBefore->GetProcedureActivation());
            }
            else
            {
                message.Format(IDS_AL_PROCESS_CALC_ACTIV,
                               pProcedure->GetSymbolName(),
                               (double)pProcedure->GetProcedureActivation());
            }

            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);

            // JMR-MODIF - Le 21 mars 2006 - Ajout du code d'incrémentation des avertissements.
            IncrementWarningCounter();
        }

        // Now calculate the procedure workload per activity
        // Take all leaving down, right and left deliverables
        double dValue = 0;    // Reset the value
        CODEdgeArray LeavingRightEdges;
        size_t LeavingRightLinkCount = pProcedure->GetEdgesLeaving_Right(LeavingRightEdges);

        if (LeavingRightLinkCount > 0)
        {
            dValue += CalculateSumOfOutDeliverables(LeavingRightEdges,
                                                    LeavingRightLinkCount,
                                                    pProcedure,
                                                    pLocalProcedureBefore);
        }

        CODEdgeArray LeavingDownEdges;
        size_t LeavingDownLinkCount = pProcedure->GetEdgesLeaving_Down(LeavingDownEdges);

        if (LeavingDownLinkCount > 0)
            dValue += CalculateSumOfOutDeliverables(LeavingDownEdges,
                                                    LeavingDownLinkCount,
                                                    pProcedure,
                                                    pLocalProcedureBefore);

        CODEdgeArray LeavingLeftEdges;
        size_t LeavingLeftLinkCount = pProcedure->GetEdgesLeaving_Left(LeavingLeftEdges);

        if (LeavingLeftLinkCount > 0)
        {
            dValue += CalculateSumOfOutDeliverables(LeavingLeftEdges,
                                                    LeavingLeftLinkCount,
                                                    pProcedure,
                                                    pLocalProcedureBefore);
        }

        if (pLocalProcedureBefore)
        {
            // Uses the multiplier
            dValue *= (double)pLocalProcedureBefore->GetMultiplier();
            dValue += pLocalProcedureBefore->GetProcessingTime();
            pLocalProcedureBefore->SetProcedureWorkloadPerActivity(dValue);
        }
        else
        {
            dValue *= (double)pProcedure->GetMultiplier();
            dValue += pProcedure->GetProcessingTime();
            pProcedure->SetProcedureWorkloadPerActivity(dValue);
        }

        // Now take the procedure processing time and add it to the value
        // If log and debug mode is required
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;
            message.Format(IDS_AL_PROCESS_LOADBYACTIV,
                           pProcedure->GetSymbolName(),
                           dValue);

            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);

            // JMR-MODIF - Le 21 mars 2006 - Ajout du code d'incrémentation des avertissements.
            IncrementWarningCounter();
        }

        // Now calculate the workload forecast
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

        // If log and debug mode is required
        if (pLog && pLog->IsInDebugMode())
        {
            CString message;

            if (pLocalProcedureBefore)
            {
                message.Format(IDS_AL_PROCESS_WORKLOAD,
                               pLocalProcedureBefore->GetSymbolName(),
                               (double)pLocalProcedureBefore->GetProcedureWorkloadForecast());
            }
            else
            {
                message.Format(IDS_AL_PROCESS_WORKLOAD,
                               pProcedure->GetSymbolName(),
                               (double)pProcedure->GetProcedureWorkloadForecast());
            }

            PSS_GenericSymbolErrorLine e(message);
            pLog->AddLine(e);

            // JMR-MODIF - Le 21 mars 2006 - Ajout du code d'incrémentation des avertissements.
            IncrementWarningCounter();
        }
    }

    return true;
}

bool ZBSesterceRecalculationAutomate::OnAfterMoveForward(PSS_StateObject*  pState,
                                                         PSS_StateMachine* pStateMachine,
                                                         PSS_Log*            pLog)
{
    return ZBBPAutomate::OnAfterMoveForward(pState, pStateMachine, pLog);
}

bool ZBSesterceRecalculationAutomate::OnBeforeMoveBackward(PSS_StateObject*  pState,
                                                           PSS_StateMachine* pStateMachine,
                                                           PSS_Log*            pLog)
{
    return ZBBPAutomate::OnBeforeMoveBackward(pState, pStateMachine, pLog);
}

bool ZBSesterceRecalculationAutomate::OnAfterMoveBackward(PSS_StateObject*  pState,
                                                          PSS_StateMachine* pStateMachine,
                                                          PSS_Log*            pLog)
{
    return ZBBPAutomate::OnAfterMoveBackward(pState, pStateMachine, pLog);
}

bool ZBSesterceRecalculationAutomate::OnObjectError(PSS_StateObject*  pState,
                                                    PSS_StateMachine* pStateMachine,
                                                    PSS_Log*            pLog)
{
    return ZBBPAutomate::OnObjectError(pState, pStateMachine, pLog);
}

bool ZBSesterceRecalculationAutomate::OnReachMaximumLoopCounter(PSS_Log* pLog)
{
    return ZBBPAutomate::OnReachMaximumLoopCounter(pLog);
}

bool ZBSesterceRecalculationAutomate::OnReachMaximumWaitingForOtherLinksCounter(PSS_Log* pLog)
{
    return ZBBPAutomate::OnReachMaximumWaitingForOtherLinksCounter(pLog);
}

bool ZBSesterceRecalculationAutomate::OnReachMaximumInPauseCounter(PSS_Log* pLog)
{
    return ZBBPAutomate::OnReachMaximumInPauseCounter(pLog);
}

double ZBSesterceRecalculationAutomate::CalculateSumOfOutDeliverables(CODEdgeArray&        LeavingEdges,
                                                                      size_t                LeavingLinkCount,
                                                                      ZBBPProcedureSymbol*    pProcedure,
                                                                      ZBBPProcedureSymbol*    pLocalProcedureBefore)
{
    double dValue = 0;
    double dPercentOut;

    for (size_t nEdgeIdx = 0; nEdgeIdx < LeavingLinkCount; ++nEdgeIdx)
    {
        IODEdge* pIEdge = LeavingEdges.GetAt(nEdgeIdx);

        // Check if a PSS_LinkSymbol
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

        // Test if it is a local symbol
        if (!pLink->IsLocal())
        {
            // Locate the local symbol
            CODComponent* pComp = pLink->GetLocalSymbol();

            if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
            {
                pLink = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
            }
            else
            {
                // Log the error
                return false;
            }
        }

        // If the quantity is not locked
        if (pLink->GetLockQuantityYear() == false)
        {
            dPercentOut = (double)pLink->GetOutWorkloadPercent();
        }
        else
        {
            // Quantity / Activation * Multiplier
            if (pLocalProcedureBefore)
            {
                dPercentOut = pLink->GetQuantityYear() /
                    ((double)pLocalProcedureBefore->GetProcedureActivation() *
                     pLocalProcedureBefore->GetMultiplier());
            }
            else
            {
                dPercentOut = pLink->GetQuantityYear() /
                    ((double)pProcedure->GetProcedureActivation() *
                     pProcedure->GetMultiplier());
            }
        }

        // Add the value
        dValue += (dPercentOut * pLink->GetProcessingTime());
    }

    return dValue;
}
