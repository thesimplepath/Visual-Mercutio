/****************************************************************************
 * ==> PSS_AutomateBP ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a Mercutio automate for banking process           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_AutomateBP.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zWkf\PSS_StateMachine.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_ODSymbolManipulator.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "PSS_DoorSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "PSS_StopSymbolBP.h"
#include "ZBDeliverableLinkSymbol.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_AutomateBP
//---------------------------------------------------------------------------
PSS_AutomateBP::PSS_AutomateBP(PSS_ProcessGraphModelMdl* pModel, PSS_Log* pLog) :
    PSS_AutomationMachine(pModel, pLog)
{}
//---------------------------------------------------------------------------
PSS_AutomateBP::PSS_AutomateBP(PSS_Symbol* pSymbol, PSS_ProcessGraphModelMdl* pModel, PSS_Log* pLog) :
    PSS_AutomationMachine(pSymbol, pModel, pLog)
{}
//---------------------------------------------------------------------------
PSS_AutomateBP::~PSS_AutomateBP()
{}
//---------------------------------------------------------------------------
PSS_AutomationMachine::IEAutomationMoveStatus PSS_AutomateBP::RequestMoveForward(PSS_StateObject*   pState,
                                                                                 PSS_StateMachine*  pStateMachine,
                                                                                 PSS_SymbolSet&     symbolSet,
                                                                                 PSS_StateLinksSet& stateLinkSet,
                                                                                 PSS_Log*           pLog)
{
    PSS_Symbol* pSymbol = pState->GetSymbol();

    if (pSymbol)
        if (ISA(pSymbol, PSS_StartSymbolBP))
            return RequestMoveForwardStartSymbol(pState, symbolSet, stateLinkSet, pLog);
        else
        if (ISA(pSymbol, PSS_ProcedureSymbolBP))
            return RequestMoveForwardProcedureSymbol(pState, symbolSet, stateLinkSet, pLog);
        else
        if (ISA(pSymbol, PSS_DoorSymbolBP))
            return RequestMoveForwardDoorSymbol(pState, symbolSet, stateLinkSet, pLog);
        else
        if (ISA(pSymbol, PSS_PageSymbolBP))
            return RequestMoveForwardPageSymbol(pState, symbolSet, stateLinkSet, pLog);
        else
        if (ISA(pSymbol, PSS_StopSymbolBP))
            return RequestMoveForwardStopSymbol(pState, symbolSet, stateLinkSet, pLog);

    // increment the error counter
    IncrementErrorCounter();
    return PSS_AutomationMachine::IE_AS_Error;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnStart(PSS_Log* pLog)
{
    // if log required
    if (pLog && pLog->InitializeLog())
    {
        pLog->ClearLog();

        CString message;
        message.Format(IDS_AL_START, m_pModel->GetModelName());
        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    // reset the error and warning counter
    ResetErrorCounter();
    ResetWarningCounter();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnStop(PSS_Log* pLog)
{
    // if log required
    if (pLog)
    {
        const std::size_t errorCount   = GetErrorCounter();
        const std::size_t warningCount = GetWarningCounter();
        CString           message;

        if (errorCount || warningCount)
            message.Format(IDS_AL_STOP2, errorCount, warningCount);
        else
            message.LoadString(IDS_AL_STOP);

        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnPause(PSS_Log* pLog)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnResume(PSS_Log* pLog)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnObjectIsFinished(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // if debug mode and log is required
    if (pLog && pLog->IsInDebugMode())
    {
        PSS_Symbol* pSymbol = pState ? pState->GetSymbol() : NULL;
        CString     message;

        if (pSymbol)
            message.Format(IDS_AL_SYMB_ISFINISHED_DBG, pSymbol->GetSymbolName());
        else
            message.Format(IDS_AL_SYMB_ISFINISHED_DBG, _T("error!!!"));

        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnObjectIsPaused(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // if debug mode and log is required
    if (pLog && pLog->IsInDebugMode())
    {
        PSS_Symbol* pSymbol = pState ? pState->GetSymbol() : NULL;
        CString     message;

        if (pSymbol)
            message.Format(IDS_AL_SYMB_ISPAUSED_DBG, pSymbol->GetSymbolName());
        else
            message.Format(IDS_AL_SYMB_ISPAUSED_DBG, _T("error!!!"));

        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnObjectIsWaitingForOtherLinks(PSS_StateObject*  pState,
                                                    PSS_StateMachine* pStateMachine,
                                                    PSS_Log*          pLog)
{
    // if debug mode and log is required
    if (pLog && pLog->IsInDebugMode())
    {
        PSS_Symbol* pSymbol = pState ? pState->GetSymbol() : NULL;
        CString     message;

        if (pSymbol)
            message.Format(IDS_AL_SYMB_ISWAITINGONOTHER_DBG, pSymbol->GetSymbolName());
        else
            message.Format(IDS_AL_SYMB_ISWAITINGONOTHER_DBG, _T("error!!!"));

        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnBeforeRequestMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // if debug mode and log is required
    if (pLog && pLog->IsInDebugMode())
    {
        PSS_Symbol* pSymbol = pState ? pState->GetSymbol() : NULL;
        CString     message;

        if (pSymbol)
            message.Format(IDS_AL_SYMB_REQUESTMOVE_DBG, pSymbol->GetSymbolName());
        else
            message.Format(IDS_AL_SYMB_REQUESTMOVE_DBG, _T("error!!!"));

        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnNextSymbolAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // if debug mode and log is required
    if (pLog && pLog->IsInDebugMode())
    {
        PSS_Symbol* pSymbol = pState ? pState->GetSymbol(): NULL;
        CString     message;

        if (pSymbol)
            message.Format(IDS_AL_SYMB_REACHED_DBG, pSymbol->GetSymbolName());
        else
            message.Format(IDS_AL_SYMB_REACHED_DBG, _T("error!!!"));

        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnBeforeMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // if debug mode and log is required
    if (pLog && pLog->IsInDebugMode())
    {
        PSS_Symbol* pSymbol = pState ? pState->GetSymbol() : NULL;
        CString     message;

        if (pSymbol)
            message.Format(IDS_AL_SYMB_BEFOREMOVE_DBG, pSymbol->GetSymbolName());
        else
            message.Format(IDS_AL_SYMB_BEFOREMOVE_DBG, _T("error!!!"));

        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // if debug mode and log is required
    if (pLog && pLog->IsInDebugMode())
    {
        PSS_Symbol* pSymbol = pState ? pState->GetSymbol() : NULL;
        CString     message;

        if (pSymbol)
            message.Format(IDS_AL_SYMB_AFTERMOVE_DBG, pSymbol->GetSymbolName());
        else
            message.Format(IDS_AL_SYMB_AFTERMOVE_DBG, _T("error!!!"));

        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnBeforeMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnAfterMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnObjectError(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // if debug mode and log is required
    if (pLog && pLog->IsInDebugMode())
    {
        PSS_Symbol* pSymbol = pState ? pState->GetSymbol() : NULL;
        CString     message;

        if (pSymbol)
            message.Format(IDS_AL_SYMB_ISINERROR_DBG, pSymbol->GetSymbolName());
        else
            message.Format(IDS_AL_SYMB_ISINERROR_DBG, _T("error!!!"));

        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnReachMaximumLoopCounter(PSS_Log* pLog)
{
    // if log required
    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_MAXIMUMLOOP_REACHED);
        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);

        // increment the error counter
        IncrementErrorCounter();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnReachMaximumInPauseCounter(PSS_Log* pLog)
{
    // if log required
    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_INPAUSECOUNTER_REACHED);
        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);

        // increment the error counter
        IncrementErrorCounter();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomateBP::OnReachMaximumWaitingForOtherLinksCounter(PSS_Log* pLog)
{
    // if log required
    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_WAITINGFOROTHER_REACHED);
        PSS_GenericSymbolErrorLine e(message);
        pLog->AddLine(e);

        // increment the error counter
        IncrementErrorCounter();
    }

    return true;
}
//---------------------------------------------------------------------------
PSS_AutomationMachine::IEAutomationMoveStatus PSS_AutomateBP::RequestMoveForwardStartSymbol(PSS_StateObject*   pState,
                                                                                            PSS_SymbolSet&     symbolSet,
                                                                                            PSS_StateLinksSet& stateLinkSet,
                                                                                            PSS_Log*           pLog)
{
    if (!pState)
    {
        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    PSS_StartSymbolBP* pStart = dynamic_cast<PSS_StartSymbolBP*>(pState->GetSymbol());

    if (!pStart)
    {
        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // get the following nodes
    CODNodeArray      followingNodes;
    const std::size_t followingSymbolCount = pStart->GetFollowingSymbols(followingNodes);

    if (followingSymbolCount)
        CopyNodeArrayToSymbolSet(followingNodes, symbolSet);
    else
    {
        // error, no following symbol attached to this start symbol
        if (pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_START_INC_3, pStart->GetSymbolName(), pStart->GetAbsolutePath());
            pLog->AddLine(e);
        }

        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // get the leaving links
    CODEdgeArray      leavingEdges;
    const std::size_t leavingLinkCount = pStart->GetEdgesLeaving(leavingEdges);

    if (leavingLinkCount)
        CopyEdgeArrayToStateLinksSet(leavingEdges, PSS_StateLink::IE_LD_EnteringUp, stateLinkSet);
    else
    {
        // error, no following symbol attached to this start symbol
        if (pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_START_INC_3, pStart->GetSymbolName(), pStart->GetAbsolutePath());
            pLog->AddLine(e);
        }

        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // ok to move forward
    return PSS_AutomationMachine::IE_AS_CanMoveForward;
}
//---------------------------------------------------------------------------
PSS_AutomationMachine::IEAutomationMoveStatus PSS_AutomateBP::RequestMoveForwardProcedureSymbol(PSS_StateObject*   pState,
                                                                                                PSS_SymbolSet&     symbolSet,
                                                                                                PSS_StateLinksSet& stateLinkSet,
                                                                                                PSS_Log*           pLog)
{
    if (!pState)
    {
        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pState->GetSymbol());

    if (!pProcedure);
    {
        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    bool enteringUpEdgesCompleted    = false;
    bool enteringRightEdgesCompleted = false;
    bool enteringLeftEdgesCompleted  = false;

    // get the entering up links
    CODEdgeArray      enteringUpEdges;
    const std::size_t enteringUpCount = pProcedure->GetEdgesEntering_Up(enteringUpEdges);

    // know if all entering up links were already get
    if (pState->EdgesExist(enteringUpEdges) == enteringUpCount)
        enteringUpEdgesCompleted = true;
    else
    if (AllowIncompletePath() && GetWaitingCounter() > 100)
    {
        // after hundred iteration and if the allow incomplete path flag is set, reset the waiting counter
        // and set the enteringUpEdgesCompleted flag to true
        enteringUpEdgesCompleted = true;
        ResetWaitingCounter();
    }
    else
        // the first step wasn't completed, it's not necessary to check further
        return PSS_AutomationMachine::IE_AS_IsWaitingForLinks;

    // get the entering right links
    CODEdgeArray      enteringRightEdges;
    const std::size_t enteringRightCount = pProcedure->GetEdgesEntering_Right(enteringRightEdges);

    // get the entering left links
    CODEdgeArray      enteringLeftEdges;
    const std::size_t enteringLeftCount = pProcedure->GetEdgesEntering_Left(enteringLeftEdges);

    // check if lateral links should be wait
    if (enteringLeftCount || enteringRightCount)
    {
        std::size_t existingEnteringLeftCount  = 0;
        std::size_t existingEnteringRightCount = 0;

        if (enteringRightCount)
        {
            if ((existingEnteringRightCount = pState->EdgesExist(enteringRightEdges)) == enteringRightCount)
                enteringRightEdgesCompleted = true;
            else
            {
                // determine if should continue on the right or wait on other links
                if (!existingEnteringRightCount && enteringUpEdgesCompleted)
                {
                    // start on the right and get the following right nodes and links
                    CODNodeArray      followingRightNodes;
                    const std::size_t followingRightSymbolCount = pProcedure->GetFollowingSymbols_Right(followingRightNodes);

                    if (followingRightSymbolCount)
                        CopyNodeArrayToSymbolSet(followingRightNodes, symbolSet);
                    else
                    {
                        // log error message
                        if (pLog)
                        {
                            PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_8,
                                                         pProcedure->GetSymbolName(),
                                                         pProcedure->GetAbsolutePath());
                            pLog->AddLine(e);
                        }

                        // increment the error counter
                        IncrementErrorCounter();
                        return PSS_AutomationMachine::IE_AS_Error;
                    }

                    CODEdgeArray      leavingRightEdges;
                    const std::size_t leavingRightLinkCount = pProcedure->GetEdgesLeaving_Right(leavingRightEdges);

                    if (leavingRightLinkCount)
                        CopyEdgeArrayToStateLinksSet(leavingRightEdges, PSS_StateLink::IE_LD_EnteringRight, stateLinkSet);
                    else
                    {
                        // log error message
                        if (pLog)
                        {
                            PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_8,
                                                         pProcedure->GetSymbolName(),
                                                         pProcedure->GetAbsolutePath());
                            pLog->AddLine(e);
                        }

                        // increment the error counter
                        IncrementErrorCounter();
                        return PSS_AutomationMachine::IE_AS_Error;
                    }

                    // before allowing to move forward, continue to check the remaining lateral links
                }
            }
        }

        // check if lateral links should be wait
        if (enteringLeftCount)
        {
            if ((existingEnteringLeftCount = pState->EdgesExist(enteringLeftEdges)) == enteringLeftCount)
                enteringLeftEdgesCompleted = true;
            else
            {
                // determine if should continue on the right or wait on other links
                if (!existingEnteringLeftCount && enteringUpEdgesCompleted)
                {
                    // start on the right and get the following right nodes and links
                    CODNodeArray      followingLeftNodes;
                    const std::size_t followingLeftSymbolCount = pProcedure->GetFollowingSymbols_Left(followingLeftNodes);

                    if (followingLeftSymbolCount)
                        CopyNodeArrayToSymbolSet(followingLeftNodes, symbolSet);
                    else
                    {
                        // log error message
                        if (pLog)
                        {
                            PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_9,
                                                         pProcedure->GetSymbolName(),
                                                         pProcedure->GetAbsolutePath());
                            pLog->AddLine(e);
                        }

                        // increment the error counter
                        IncrementErrorCounter();
                        return PSS_AutomationMachine::IE_AS_Error;
                    }

                    CODEdgeArray      leavingLeftEdges;
                    const std::size_t leavingLeftLinkCount = pProcedure->GetEdgesLeaving_Left(leavingLeftEdges);

                    if (leavingLeftLinkCount)
                        CopyEdgeArrayToStateLinksSet(leavingLeftEdges, PSS_StateLink::IE_LD_EnteringLeft, stateLinkSet);
                    else
                    {
                        // log error message
                        if (pLog)
                        {
                            PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_9,
                                                         pProcedure->GetSymbolName(),
                                                         pProcedure->GetAbsolutePath());
                            pLog->AddLine(e);
                        }

                        // increment the error counter
                        IncrementErrorCounter();
                        return PSS_AutomationMachine::IE_AS_Error;
                    }
                }
            }
        }

        // entering links were already found and the up is completed, wait on all links
        if (enteringUpEdgesCompleted &&
          ((enteringRightCount       && !enteringRightEdgesCompleted) ||
           (enteringLeftCount        && !enteringLeftEdgesCompleted)))
        {
            if (existingEnteringRightCount && !enteringRightEdgesCompleted)
                return PSS_AutomationMachine::IE_AS_IsWaitingForLinks;

            // entering links were already found and the up is completed, wait on all links
            if (existingEnteringLeftCount && !enteringLeftEdgesCompleted)
                return PSS_AutomationMachine::IE_AS_IsWaitingForLinks;

            // ok to move forward
            return PSS_AutomationMachine::IE_AS_CanMoveForward;
        }
    }

    if ((!enteringRightCount || enteringRightEdgesCompleted) && (!enteringLeftCount || enteringLeftEdgesCompleted))
    {
        // get the following down nodes and links
        CODNodeArray      followingDownNodes;
        const std::size_t followingDownSymbolCount = pProcedure->GetFollowingSymbols_Down(followingDownNodes);

        if (followingDownSymbolCount)
            CopyNodeArrayToSymbolSet(followingDownNodes, symbolSet);
        else
        {
            // log error message
            if (pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_5,
                                             pProcedure->GetSymbolName(),
                                             pProcedure->GetAbsolutePath());
                pLog->AddLine(e);
            }

            // increment the error counter
            IncrementErrorCounter();
            return PSS_AutomationMachine::IE_AS_Error;
        }

        CODEdgeArray      leavingDownEdges;
        const std::size_t leavingDownLinkCount = pProcedure->GetEdgesLeaving_Down(leavingDownEdges);

        if (leavingDownLinkCount)
            CopyEdgeArrayToStateLinksSet(leavingDownEdges, PSS_StateLink::IE_LD_EnteringUp, stateLinkSet);
        else
        {
            // log error message
            if (pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_5,
                                             pProcedure->GetSymbolName(),
                                             pProcedure->GetAbsolutePath());
                pLog->AddLine(e);
            }

            // increment the error counter
            IncrementErrorCounter();
            return PSS_AutomationMachine::IE_AS_Error;
        }

        // ok to move forward
        return PSS_AutomationMachine::IE_AS_CanMoveForward;
    }

    // an issue occurred
    return PSS_AutomationMachine::IE_AS_Error;
}
//---------------------------------------------------------------------------
PSS_AutomationMachine::IEAutomationMoveStatus PSS_AutomateBP::RequestMoveForwardDoorSymbol(PSS_StateObject*   pState,
                                                                                           PSS_SymbolSet&     symbolSet,
                                                                                           PSS_StateLinksSet& stateLinkSet,
                                                                                           PSS_Log*           pLog)
{
    if (!pState)
    {
        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    PSS_DoorSymbolBP* pDoor = dynamic_cast<PSS_DoorSymbolBP*>(pState->GetSymbol());

    if (!pDoor)
    {
        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    PSS_DoorSymbolBP* pTwinDoor = pDoor->GetTwinDoorSymbol();

    if (!pTwinDoor)
    {
        // log error message
        if (pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_DOOR_INC_IN_3,
                                         pDoor->GetSymbolName(),
                                         pDoor->GetAbsolutePath());
            pLog->AddLine(e);
        }

        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // get the next symbol attached to the twin and get the following nodes
    CODNodeArray      followingNodes;
    const std::size_t followingSymbolCount = pTwinDoor->GetFollowingSymbols(followingNodes);

    if (followingSymbolCount)
        CopyNodeArrayToSymbolSet(followingNodes, symbolSet);
    else
    {
        // error, no following symbol attached to this start symbol
        if (pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_DOOR_INC_OUT_1,
                                         pTwinDoor->GetSymbolName(),
                                         pTwinDoor->GetAbsolutePath());
            pLog->AddLine(e);
        }

        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // get the leaving links
    CODEdgeArray      leavingEdges;
    const std::size_t leavingLinkCount = pTwinDoor->GetEdgesLeaving(leavingEdges);

    if (leavingLinkCount)
        CopyEdgeArrayToStateLinksSet(leavingEdges, PSS_StateLink::IE_LD_EnteringUp, stateLinkSet);
    else
    {
        // error, no following symbol attached to this start symbol
        if (pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_DOOR_INC_OUT_1,
                                         pTwinDoor->GetSymbolName(),
                                         pTwinDoor->GetAbsolutePath());
            pLog->AddLine(e);
        }

        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // ok to move forward
    return PSS_AutomationMachine::IE_AS_CanMoveForward;
}
//---------------------------------------------------------------------------
PSS_AutomationMachine::IEAutomationMoveStatus PSS_AutomateBP::RequestMoveForwardPageSymbol(PSS_StateObject*   pState,
                                                                                           PSS_SymbolSet&     symbolSet,
                                                                                           PSS_StateLinksSet& stateLinkSet,
                                                                                           PSS_Log*           pLog)
{
    if (!pState)
    {
        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    PSS_PageSymbolBP* pPage = dynamic_cast<PSS_PageSymbolBP*>(pState->GetSymbol());

    if (!pPage)
    {
        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    PSS_PageSymbolBP* pTwinPage = pPage->GetTwinPageSymbol();

    if (!pTwinPage)
    {
        // log error message
        if (pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PAGE_INC_IN_3,
                                         pPage->GetSymbolName(),
                                         pPage->GetAbsolutePath());
            pLog->AddLine(e);
        }

        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // get the next symbol attached to the twin and get the following nodes
    CODNodeArray      followingNodes;
    const std::size_t followingSymbolCount = pTwinPage->GetFollowingSymbols_Down(followingNodes);

    if (followingSymbolCount)
        CopyNodeArrayToSymbolSet(followingNodes, symbolSet);
    else
    {
        // error, no following symbol attached to this page symbol
        if (pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PAGE_INC_OUT_1,
                                         pTwinPage->GetSymbolName(),
                                         pTwinPage->GetAbsolutePath());
            pLog->AddLine(e);
        }

        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // get the leaving links
    CODEdgeArray      leavingEdges;
    const std::size_t leavingLinkCount = pTwinPage->GetEdgesLeaving_Down(leavingEdges);

    if (leavingLinkCount)
        CopyEdgeArrayToStateLinksSet(leavingEdges, PSS_StateLink::IE_LD_EnteringUp, stateLinkSet);
    else
    {
        // error, no following symbol attached to this page symbol
        if (pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PAGE_INC_OUT_1,
                                         pTwinPage->GetSymbolName(),
                                         pTwinPage->GetAbsolutePath());
            pLog->AddLine(e);
        }

        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // ok to move forward
    return PSS_AutomationMachine::IE_AS_CanMoveForward;
}
//---------------------------------------------------------------------------
PSS_AutomationMachine::IEAutomationMoveStatus PSS_AutomateBP::RequestMoveForwardStopSymbol(PSS_StateObject*   pState,
                                                                                           PSS_SymbolSet&     symbolSet,
                                                                                           PSS_StateLinksSet& stateLinkSet,
                                                                                           PSS_Log*           pLog)
{
    if (!pState)
    {
        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    PSS_StopSymbolBP* pStop = dynamic_cast<PSS_StopSymbolBP*>(pState->GetSymbol());

    if (!pStop)
    {
        // increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // the task ends when a stop symbol is reached
    return PSS_AutomationMachine::IE_AS_IsFinished;
}
//---------------------------------------------------------------------------
