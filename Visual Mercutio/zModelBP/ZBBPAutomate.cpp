/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPAutomate
//@module ZBBPAutomate.cpp | Implementation of the <c ZBBPAutomate> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 06/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBBPAutomate.h"

#include "zWkf\PSS_StateMachine.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "zModelBP\ZBBPDoorSymbol.h"
#include "zModelBP\ZBBPPageSymbol.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zModel\ZUODSymbolManipulator.h"

// Include files for log
#include "zBaseLib\ZILog.h"
#include "zModel\ZBGenericSymbolErrorLine.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 20 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBBPAutomate::ZBBPAutomate( ZDProcessGraphModelMdl* pModel /*= NULL*/, ZILog* pLog /*= NULL*/ )
    : PSS_AutomationMachine( pModel, pLog )
{
}

ZBBPAutomate::ZBBPAutomate( ZBSymbol* pSymbol, ZDProcessGraphModelMdl* pModel /*= NULL*/, ZILog* pLog /*= NULL*/ )
    : PSS_AutomationMachine( pSymbol, pModel, pLog )
{
}

ZBBPAutomate::~ZBBPAutomate()
{
}

bool ZBBPAutomate::OnStart( ZILog* pLog )
{
    // If log required
    if ( pLog && pLog->InitializeLog() )
    {
        pLog->ClearLog();

        CString message;
        message.Format( IDS_AL_START, m_pModel->GetModelName() );
        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    // Reset the error and warning counter
    ResetErrorCounter();
    ResetWarningCounter();

    return true;
}

bool ZBBPAutomate::OnStop( ZILog* pLog )
{
    // If log required
    if ( pLog )
    {
        CString message;

        if ( GetErrorCounter() > 0 || GetWarningCounter() > 0 )
        {
            message.Format( IDS_AL_STOP2, GetErrorCounter(), GetWarningCounter() );
        }
        else
        {
            message.LoadString( IDS_AL_STOP );
        }

        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    return true;
}

bool ZBBPAutomate::OnPause( ZILog* pLog )
{
    // Does nothing in the base class
    // Might be implemented in the derived class
    return true;
}

bool ZBBPAutomate::OnResume( ZILog* pLog )
{
    // Does nothing in the base class
    // Might be implemented in the derived class
    return true;
}

//////////////////////////////////////////////////////////////////////
// Call-back workflow operations
bool ZBBPAutomate::OnObjectIsFinished(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog)
{
    // If log and debug mode is required
    if ( pLog && pLog->IsInDebugMode() )
    {
        CString message;

        if ( pState->GetSymbol() )
        {
            message.Format( IDS_AL_SYMB_ISFINISHED_DBG, pState->GetSymbol()->GetSymbolName() );
        }
        else
        {
            message.Format( IDS_AL_SYMB_ISFINISHED_DBG, _T( "error!!!" ) );
        }

        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    return true;
}

bool ZBBPAutomate::OnObjectIsPaused(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog)
{
    // If log and debug mode is required
    if ( pLog && pLog->IsInDebugMode() )
    {
        CString message;

        if ( pState->GetSymbol() )
        {
            message.Format( IDS_AL_SYMB_ISPAUSED_DBG, pState->GetSymbol()->GetSymbolName() );
        }
        else
        {
            message.Format( IDS_AL_SYMB_ISPAUSED_DBG, _T( "error!!!" ) );
        }

        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    return true;
}

bool ZBBPAutomate::OnObjectIsWaitingForOtherLinks(PSS_StateObject*  pState,
                                                  PSS_StateMachine* pStateMachine,
                                                  ZILog*            pLog )
{
    // If log and debug mode is required
    if ( pLog && pLog->IsInDebugMode() )
    {
        CString message;

        if ( pState->GetSymbol() )
        {
            message.Format( IDS_AL_SYMB_ISWAITINGONOTHER_DBG, pState->GetSymbol()->GetSymbolName() );
        }
        else
        {
            message.Format( IDS_AL_SYMB_ISWAITINGONOTHER_DBG, _T( "error!!!" ) );
        }

        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    return true;
}

bool ZBBPAutomate::OnBeforeRequestMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog)
{
    // If log and debug mode is required
    if ( pLog && pLog->IsInDebugMode() )
    {
        CString message;

        if ( pState->GetSymbol() )
        {
            message.Format( IDS_AL_SYMB_REQUESTMOVE_DBG, pState->GetSymbol()->GetSymbolName() );
        }
        else
        {
            message.Format( IDS_AL_SYMB_REQUESTMOVE_DBG, _T( "error!!!" ) );
        }

        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    return true;
}

bool ZBBPAutomate::OnNextSymbolAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog)
{
    // If log and debug mode is required
    if ( pLog && pLog->IsInDebugMode() )
    {
        CString message;

        if ( pState->GetSymbol() )
        {
            message.Format( IDS_AL_SYMB_REACHED_DBG, pState->GetSymbol()->GetSymbolName() );
        }
        else
        {
            message.Format( IDS_AL_SYMB_REACHED_DBG, _T( "error!!!" ) );
        }

        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    return true;
}

bool ZBBPAutomate::OnBeforeMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog)
{
    // If log and debug mode is required
    if ( pLog && pLog->IsInDebugMode() )
    {
        CString message;

        if ( pState->GetSymbol() )
        {
            message.Format( IDS_AL_SYMB_BEFOREMOVE_DBG, pState->GetSymbol()->GetSymbolName() );
        }
        else
        {
            message.Format( IDS_AL_SYMB_BEFOREMOVE_DBG, _T( "error!!!" ) );
        }

        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    return true;
}

bool ZBBPAutomate::OnAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog)
{
    // If log and debug mode is required
    if ( pLog && pLog->IsInDebugMode() )
    {
        CString message;

        if ( pState->GetSymbol() )
        {
            message.Format( IDS_AL_SYMB_AFTERMOVE_DBG, pState->GetSymbol()->GetSymbolName() );
        }
        else
        {
            message.Format( IDS_AL_SYMB_AFTERMOVE_DBG, _T( "error!!!" ) );
        }

        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    return true;
}

bool ZBBPAutomate::OnBeforeMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog)
{
    return true;
}

bool ZBBPAutomate::OnAfterMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog)
{
    return true;
}

bool ZBBPAutomate::OnObjectError(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog)
{
    // If log and debug mode is required
    if ( pLog && pLog->IsInDebugMode() )
    {
        CString message;

        if ( pState->GetSymbol() )
        {
            message.Format( IDS_AL_SYMB_ISINERROR_DBG, pState->GetSymbol()->GetSymbolName() );
        }
        else
        {
            message.Format( IDS_AL_SYMB_ISINERROR_DBG, _T( "error!!!" ) );
        }

        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    return true;
}

bool ZBBPAutomate::OnReachMaximumLoopCounter( ZILog* pLog )
{
    // If log required
    if ( pLog )
    {
        CString message;
        message.LoadString( IDS_AL_MAXIMUMLOOP_REACHED );
        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );

        // Increment the error counter
        IncrementErrorCounter();
    }

    return true;
}

bool ZBBPAutomate::OnReachMaximumWaitingForOtherLinksCounter( ZILog* pLog )
{
    // If log required
    if ( pLog )
    {
        CString message;
        message.LoadString( IDS_AL_WAITINGFOROTHER_REACHED );
        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );

        // Increment the error counter
        IncrementErrorCounter();
    }

    return true;
}

bool ZBBPAutomate::OnReachMaximumInPauseCounter( ZILog* pLog )
{
    // If log required
    if ( pLog )
    {
        CString message;
        message.LoadString( IDS_AL_INPAUSECOUNTER_REACHED );
        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );

        // Increment the error counter
        IncrementErrorCounter();
    }

    return true;
}

//////////////////////////////////////////////////////////////////////
// Workflow operations
PSS_AutomationMachine::IEAutomationMoveStatus ZBBPAutomate::RequestMoveForward(PSS_StateObject*   pState,
                                                                               PSS_StateMachine*  pStateMachine,
                                                                               PSS_SymbolSet&     SymbolSet,
                                                                               PSS_StateLinksSet& StateLinkSet,
                                                                               ZILog*             pLog )
{
    if ( pState->GetSymbol() && ISA( pState->GetSymbol(), ZBBPStartSymbol ) )
    {
        return RequestMoveForwardStartSymbol( pState, SymbolSet, StateLinkSet, pLog );
    }
    else if ( pState->GetSymbol() && ISA( pState->GetSymbol(), ZBBPProcedureSymbol ) )
    {
        return RequestMoveForwardProcedureSymbol( pState, SymbolSet, StateLinkSet, pLog );
    }
    else if ( pState->GetSymbol() && ISA( pState->GetSymbol(), ZBBPDoorSymbol ) )
    {
        return RequestMoveForwardDoorSymbol( pState, SymbolSet, StateLinkSet, pLog );
    }
    else if ( pState->GetSymbol() && ISA( pState->GetSymbol(), ZBBPPageSymbol ) )
    {
        return RequestMoveForwardPageSymbol( pState, SymbolSet, StateLinkSet, pLog );
    }
    else if ( pState->GetSymbol() && ISA( pState->GetSymbol(), ZBBPStopSymbol ) )
    {
        return RequestMoveForwardStopSymbol( pState, SymbolSet, StateLinkSet, pLog );
    }

    // Increment the error counter
    IncrementErrorCounter();
    return PSS_AutomationMachine::IE_AS_Error;
}

//////////////////////////////////////////////////////////////////////
// For start symbol, we only need to fill the symbol set and the state link set with correct objects
// If there is no following symbol or link attached to the start symbol, return error
PSS_AutomationMachine::IEAutomationMoveStatus ZBBPAutomate::RequestMoveForwardStartSymbol(PSS_StateObject*   pState,
                                                                                          PSS_SymbolSet&     SymbolSet,
                                                                                          PSS_StateLinksSet& StateLinkSet,
                                                                                          ZILog*             pLog )
{
    ZBBPStartSymbol* pStart = dynamic_cast<ZBBPStartSymbol*>( pState->GetSymbol() );

    // Retreiving following nodes
    CODNodeArray FollowingNodes;
    size_t FollowingSymbolCount = pStart->GetFollowingSymbols( FollowingNodes );

    if ( FollowingSymbolCount > 0 )
    {
        CopyNodeArrayToSymbolSet( FollowingNodes, SymbolSet );
    }
    else
    {
        // Error, no following symbol attached to this start symbol
        if ( pLog )
        {
            ZBGenericSymbolErrorLine e(IDS_EL_START_INC_3, pStart->GetSymbolName(), pStart->GetAbsolutePath() );
            pLog->AddLine( e );
        }

        // Increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // Retreiving leaving links
    CODEdgeArray LeavingEdges;
    size_t LeavingLinkCount = pStart->GetEdgesLeaving( LeavingEdges );

    if ( LeavingLinkCount > 0 )
    {
        CopyEdgeArrayToStateLinksSet(LeavingEdges, PSS_StateLink::IE_LD_EnteringUp, StateLinkSet);
    }
    else
    {
        // Error, no following symbol attached to this start symbol
        if ( pLog )
        {
            ZBGenericSymbolErrorLine e(IDS_EL_START_INC_3, pStart->GetSymbolName(), pStart->GetAbsolutePath() );
            pLog->AddLine( e );
        }

        // Increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // Ok to move forward
    return PSS_AutomationMachine::IE_AS_CanMoveForward;
}

//////////////////////////////////////////////////////////////////////
// For procedure symbol, we need to check if all links are completed.
// if it is not the case, return the waiting on other links status.
// if all links are completed, we need to fill the symbol set and the state link set with correct objects
PSS_AutomationMachine::IEAutomationMoveStatus ZBBPAutomate::RequestMoveForwardProcedureSymbol(PSS_StateObject*   pState,
                                                                                              PSS_SymbolSet&     SymbolSet,
                                                                                              PSS_StateLinksSet& StateLinkSet,
                                                                                              ZILog*             pLog )
{
    ZBBPProcedureSymbol* pProcedure = dynamic_cast<ZBBPProcedureSymbol*>( pState->GetSymbol() );
    ASSERT( pProcedure );

    bool EnteringUpEdgesCompleted        = false;
    bool EnteringRightEdgesCompleted    = false;
    bool EnteringLeftEdgesCompleted        = false;

    // Retreiving entering up links
    CODEdgeArray EnteringUpEdges;
    size_t EnteringUpCount = pProcedure->GetEdgesEntering_Up( EnteringUpEdges );

    // Now the first check, is to know if we already received all entering up links
    if ( pState->EdgesExist( EnteringUpEdges ) == EnteringUpCount )
    {
        EnteringUpEdgesCompleted = true;
    }
    else
    {
        // After undred iteration and the allow uncomplet path is set
        // then reset the waiting counter and set the EnteringUpEdgesCompleted to true
        if ( AllowUncompletePath() && GetWaitingCounter() > 100 )
        {
            EnteringUpEdgesCompleted = true;
            ResetWaitingCounter();
        }
        else
        {
            // It is not necessary to check further, we have not completed the first step
            return PSS_AutomationMachine::IE_AS_IsWaitingForLinks;
        }
    }

    // Retreiving entering right links
    CODEdgeArray EnteringRightEdges;
    size_t EnteringRightCount = pProcedure->GetEdgesEntering_Right( EnteringRightEdges );

    // Retreiving entering left links
    CODEdgeArray EnteringLeftEdges;
    size_t EnteringLeftCount = pProcedure->GetEdgesEntering_Left( EnteringLeftEdges );

    // Check if we are supposed to wait for lateral links
    if ( EnteringRightCount > 0 || EnteringLeftCount > 0 )
    {
        size_t ExistingEnteringRightCount    = 0;
        size_t ExistingEnteringLeftCount    = 0;

        if ( EnteringRightCount > 0 )
        {
            if ( ( ExistingEnteringRightCount = pState->EdgesExist( EnteringRightEdges ) ) == EnteringRightCount )
            {
                EnteringRightEdgesCompleted = true;
            }
            else
            {
                // Now we need to determine if we can continue on the right
                // or we need to wait on other links
                if ( ExistingEnteringRightCount == 0 && EnteringUpEdgesCompleted == true )
                {
                    // We need to start to the right
                    // then we need to retreive the following right nodes and links
                    CODNodeArray FollowingRightNodes;
                    size_t FollowingRightSymbolCount = pProcedure->GetFollowingSymbols_Right( FollowingRightNodes );

                    if ( FollowingRightSymbolCount > 0 )
                    {
                        CopyNodeArrayToSymbolSet( FollowingRightNodes, SymbolSet );
                    }
                    else
                    {
                        // Log error message
                        if ( pLog )
                        {
                            ZBGenericSymbolErrorLine e( IDS_AL_PROCEDURE_INC_8,
                                                        pProcedure->GetSymbolName(),
                                                        pProcedure->GetAbsolutePath() );

                            pLog->AddLine( e );
                        }

                        // Increment the error counter
                        IncrementErrorCounter();
                        return PSS_AutomationMachine::IE_AS_Error;
                    }

                    CODEdgeArray LeavingRightEdges;
                    size_t LeavingRightLinkCount = pProcedure->GetEdgesLeaving_Right( LeavingRightEdges );

                    if ( LeavingRightLinkCount > 0 )
                    {
                        CopyEdgeArrayToStateLinksSet(LeavingRightEdges,
                                                     PSS_StateLink::IE_LD_EnteringRight,
                                                     StateLinkSet );
                    }
                    else
                    {
                        // Log error message
                        if ( pLog )
                        {
                            ZBGenericSymbolErrorLine e( IDS_AL_PROCEDURE_INC_8,
                                                        pProcedure->GetSymbolName(),
                                                        pProcedure->GetAbsolutePath() );

                            pLog->AddLine( e );
                        }

                        // Increment the error counter
                        IncrementErrorCounter();
                        return PSS_AutomationMachine::IE_AS_Error;
                    }

                    // Before giving the ok to move forward, continue the test to know if left lateral links
                }
            }
        }

        // Check if we are supposed to wait for lateral links
        if ( EnteringLeftCount > 0 )
        {
            if ( ( ExistingEnteringLeftCount = pState->EdgesExist( EnteringLeftEdges ) ) == EnteringLeftCount )
            {
                EnteringLeftEdgesCompleted = true;
            }
            else
            {
                // Now we need to determine if we can continue on the right
                // or we need to wait on other links
                if ( ExistingEnteringLeftCount == 0 && EnteringUpEdgesCompleted == true )
                {
                    // We need to start to the right
                    // then we need to retreive the following right nodes and links
                    CODNodeArray FollowingLeftNodes;
                    size_t FollowingLeftSymbolCount = pProcedure->GetFollowingSymbols_Left( FollowingLeftNodes );

                    if ( FollowingLeftSymbolCount > 0 )
                    {
                        CopyNodeArrayToSymbolSet( FollowingLeftNodes, SymbolSet );
                    }
                    else
                    {
                        // Log error message
                        if ( pLog )
                        {
                            ZBGenericSymbolErrorLine e( IDS_AL_PROCEDURE_INC_9,
                                                        pProcedure->GetSymbolName(),
                                                        pProcedure->GetAbsolutePath() );
                            pLog->AddLine( e );
                        }

                        // Increment the error counter
                        IncrementErrorCounter();
                        return PSS_AutomationMachine::IE_AS_Error;
                    }

                    CODEdgeArray LeavingLeftEdges;
                    size_t LeavingLeftLinkCount = pProcedure->GetEdgesLeaving_Left( LeavingLeftEdges );

                    if ( LeavingLeftLinkCount > 0 )
                    {
                        CopyEdgeArrayToStateLinksSet(LeavingLeftEdges,
                                                     PSS_StateLink::IE_LD_EnteringLeft,
                                                     StateLinkSet );
                    }
                    else
                    {
                        // Log error message
                        if ( pLog )
                        {
                            ZBGenericSymbolErrorLine e( IDS_AL_PROCEDURE_INC_9,
                                                        pProcedure->GetSymbolName(),
                                                        pProcedure->GetAbsolutePath() );

                            pLog->AddLine( e );
                        }

                        // Increment the error counter
                        IncrementErrorCounter();
                        return PSS_AutomationMachine::IE_AS_Error;
                    }
                }
            }
        }

        // We already have entering links and the up is completed,
        // then we need to wait on all links
        if ( EnteringUpEdgesCompleted == true &&
             ( ( EnteringRightCount > 0 && EnteringRightEdgesCompleted == false ) ||
             ( EnteringLeftCount > 0 && EnteringLeftEdgesCompleted == false ) ) )
        {
            if ( ExistingEnteringRightCount > 0 && EnteringRightEdgesCompleted == false )
            {
                return PSS_AutomationMachine::IE_AS_IsWaitingForLinks;
            }

            // We already have entering links and the up is completed,
            // then we need to wait on all links
            if ( ExistingEnteringLeftCount > 0 && EnteringLeftEdgesCompleted == false )
            {
                return PSS_AutomationMachine::IE_AS_IsWaitingForLinks;
            }

            // Ok to move forward
            return PSS_AutomationMachine::IE_AS_CanMoveForward;
        }
    }

    if ( (EnteringRightCount == 0 ||
          EnteringRightEdgesCompleted == true ) &&
          ( EnteringLeftCount == 0 ||
          EnteringLeftEdgesCompleted == true ) )
    {
        // Now we need to retreive following down nodes and links
        // and we can return continue
        CODNodeArray FollowingDownNodes;
        size_t FollowingDownSymbolCount = pProcedure->GetFollowingSymbols_Down( FollowingDownNodes );

        if ( FollowingDownSymbolCount > 0 )
        {
            CopyNodeArrayToSymbolSet( FollowingDownNodes, SymbolSet );
        }
        else
        {
            // Log error message
            if ( pLog )
            {
                ZBGenericSymbolErrorLine e( IDS_EL_PROCEDURE_INC_5,
                                            pProcedure->GetSymbolName(),
                                            pProcedure->GetAbsolutePath() );

                pLog->AddLine( e );
            }

            // Increment the error counter
            IncrementErrorCounter();
            return PSS_AutomationMachine::IE_AS_Error;
        }

        CODEdgeArray LeavingDownEdges;
        size_t LeavingDownLinkCount = pProcedure->GetEdgesLeaving_Down( LeavingDownEdges );

        if ( LeavingDownLinkCount > 0 )
        {
            CopyEdgeArrayToStateLinksSet( LeavingDownEdges, PSS_StateLink::IE_LD_EnteringUp, StateLinkSet );
        }
        else
        {
            // Log error message
            if ( pLog )
            {
                ZBGenericSymbolErrorLine e( IDS_EL_PROCEDURE_INC_5,
                                            pProcedure->GetSymbolName(),
                                            pProcedure->GetAbsolutePath() );

                pLog->AddLine( e );
            }

            // Increment the error counter
            IncrementErrorCounter();
            return PSS_AutomationMachine::IE_AS_Error;
        }

        // Ok to move forward
        return PSS_AutomationMachine::IE_AS_CanMoveForward;
    }

    // Problem
    return PSS_AutomationMachine::IE_AS_Error;
}

PSS_AutomationMachine::IEAutomationMoveStatus ZBBPAutomate::RequestMoveForwardDoorSymbol(PSS_StateObject*   pState,
                                                                                         PSS_SymbolSet&     SymbolSet,
                                                                                         PSS_StateLinksSet& StateLinkSet,
                                                                                         ZILog*             pLog )
{
    ZBBPDoorSymbol* pDoor = dynamic_cast<ZBBPDoorSymbol*>( pState->GetSymbol() );
    ASSERT( pDoor );

    ZBBPDoorSymbol* pTwinDoor = pDoor->GetTwinDoorSymbol();

    if ( !pTwinDoor )
    {
        // Log error message
        if ( pLog )
        {
            ZBGenericSymbolErrorLine e( IDS_EL_DOOR_INC_IN_3,
                                        pDoor->GetSymbolName(),
                                        pDoor->GetAbsolutePath() );

            pLog->AddLine( e );
        }

        // Increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // Now take the next symbol attached to the twin
    // Retreiving following nodes
    CODNodeArray FollowingNodes;
    size_t FollowingSymbolCount = pTwinDoor->GetFollowingSymbols( FollowingNodes );

    if ( FollowingSymbolCount > 0 )
    {
        CopyNodeArrayToSymbolSet( FollowingNodes, SymbolSet );
    }
    else
    {
        // Error, no following symbol attached to this start symbol
        if ( pLog )
        {
            ZBGenericSymbolErrorLine e( IDS_EL_DOOR_INC_OUT_1,
                                        pTwinDoor->GetSymbolName(),
                                        pTwinDoor->GetAbsolutePath() );

            pLog->AddLine( e );
        }

        // Increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // Retreiving leaving links
    CODEdgeArray LeavingEdges;
    size_t LeavingLinkCount = pTwinDoor->GetEdgesLeaving( LeavingEdges );

    if ( LeavingLinkCount > 0 )
    {
        CopyEdgeArrayToStateLinksSet( LeavingEdges, PSS_StateLink::IE_LD_EnteringUp, StateLinkSet );
    }
    else
    {
        // Error, no following symbol attached to this start symbol
        if ( pLog )
        {
            ZBGenericSymbolErrorLine e( IDS_EL_DOOR_INC_OUT_1,
                                        pTwinDoor->GetSymbolName(),
                                        pTwinDoor->GetAbsolutePath() );

            pLog->AddLine( e );
        }

        // Increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // Ok to move forward
    return PSS_AutomationMachine::IE_AS_CanMoveForward;
}

PSS_AutomationMachine::IEAutomationMoveStatus ZBBPAutomate::RequestMoveForwardPageSymbol(PSS_StateObject*   pState,
                                                                                         PSS_SymbolSet&     SymbolSet,
                                                                                         PSS_StateLinksSet& StateLinkSet,
                                                                                         ZILog*             pLog )
{
    ZBBPPageSymbol* pPage = dynamic_cast<ZBBPPageSymbol*>( pState->GetSymbol() );
    ASSERT( pPage );

    ZBBPPageSymbol* pTwinPage = pPage->GetTwinPageSymbol();

    if ( !pTwinPage )
    {
        // Log error message
        if ( pLog )
        {
            ZBGenericSymbolErrorLine e( IDS_EL_PAGE_INC_IN_3,
                                        pPage->GetSymbolName(),
                                        pPage->GetAbsolutePath() );

            pLog->AddLine( e );
        }

        // Increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // Now take the next symbol attached to the twin
    // Retreiving following nodes
    CODNodeArray FollowingNodes;
    size_t FollowingSymbolCount = pTwinPage->GetFollowingSymbols_Down( FollowingNodes );

    if ( FollowingSymbolCount > 0 )
    {
        CopyNodeArrayToSymbolSet( FollowingNodes, SymbolSet );
    }
    else
    {
        // Error, no following symbol attached to this page symbol
        if ( pLog )
        {
            ZBGenericSymbolErrorLine e( IDS_EL_PAGE_INC_OUT_1,
                                        pTwinPage->GetSymbolName(),
                                        pTwinPage->GetAbsolutePath() );

            pLog->AddLine( e );
        }

        // Increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // Retreiving leaving links
    CODEdgeArray LeavingEdges;
    size_t LeavingLinkCount = pTwinPage->GetEdgesLeaving_Down( LeavingEdges );

    if ( LeavingLinkCount > 0 )
    {
        CopyEdgeArrayToStateLinksSet( LeavingEdges, PSS_StateLink::IE_LD_EnteringUp, StateLinkSet );
    }
    else
    {
        // Error, no following symbol attached to this page symbol
        if ( pLog )
        {
            ZBGenericSymbolErrorLine e( IDS_EL_PAGE_INC_OUT_1,
                                        pTwinPage->GetSymbolName(),
                                        pTwinPage->GetAbsolutePath() );

            pLog->AddLine( e );
        }

        // Increment the error counter
        IncrementErrorCounter();
        return PSS_AutomationMachine::IE_AS_Error;
    }

    // Ok to move forward
    return PSS_AutomationMachine::IE_AS_CanMoveForward;
}

PSS_AutomationMachine::IEAutomationMoveStatus ZBBPAutomate::RequestMoveForwardStopSymbol(PSS_StateObject*   pState,
                                                                                         PSS_SymbolSet&     SymbolSet,
                                                                                         PSS_StateLinksSet& StateLinkSet,
                                                                                         ZILog*             pLog )
{
    ZBBPStopSymbol* pStop = dynamic_cast<ZBBPStopSymbol*>( pState->GetSymbol() );

    // It is finished when we reached a stop symbol
    return PSS_AutomationMachine::IE_AS_IsFinished;
}
