// ZBMainAutomationRunnerThread.cpp : implementation file

#include "stdafx.h"
#include "ZBMainAutomationRunnerThread.h"

#include "ZBAutomationMachine.h"
#include "ZBStateMachine.h"
#include "ZBStateMachineCollection.h"
#include "zModel\ProcGraphModelMdl.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

// Include files for log
#include "zBaseLib\ZILog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 4 septembre 2006 - Ajout des décorations unicode _T(), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBMainAutomationRunnerThread

ZBMainAutomationRunnerThread::ZBMainAutomationRunnerThread()
    : m_pAutomationMachine    ( NULL ),
      m_ElapseTime            ( -1 ),
      m_pLog                ( NULL )
{
}

ZBMainAutomationRunnerThread::ZBMainAutomationRunnerThread( ZBAutomationMachine*    pAutomationMachine,
                                                            int                        ElapseTime            /*= -1*/,
                                                            ZILog*                    pLog                /*= NULL*/ )
    : m_pAutomationMachine    ( pAutomationMachine ),
      m_ElapseTime            ( ElapseTime ),
      m_pLog                ( pLog )
{
}

ZBMainAutomationRunnerThread::~ZBMainAutomationRunnerThread()
{
}

BOOL ZBMainAutomationRunnerThread::StartThread()
{
    // Create the thread only if the context has been correctly assigned
    if ( !m_pAutomationMachine || !m_pAutomationMachine->GetModel() )
    {
        return FALSE;
    }

    // Comment the next following two line for having a multi-threaded operation
    Start( (void*)this );

    return TRUE;
}

void ZBMainAutomationRunnerThread::StartWork()
{
    ASSERT( m_pAutomationMachine && m_pAutomationMachine->GetModel() );

    // First, delete all state machines
    m_pAutomationMachine->DeleteAllStateMachines();
    m_pAutomationMachine->DeleteAllFinishedStateMachines();

    // If a specific start symbol is defined,
    // then initialize the new state machine with it
    if ( m_pAutomationMachine->GetStartSymbol() )
    {
        // Create a model state machine for each start symbol
        StateMachineHandle hStateMachine =
            m_pAutomationMachine->GetStateMachineCollection().CreateNewStateMachine( m_pAutomationMachine->GetStartSymbol(),    // The start symbol
                                                                                     NULL );                                    // No link before

        if ( hStateMachine == -1 )
        {
            // Log error
            return;
        }

        m_MachineHandleSet.Add( hStateMachine );
    }
    else
    {
        CODNodeArray Nodes;

        // True for deeply retrieval
        int StartSymbolCount = (int)m_pAutomationMachine->GetModel()->GetStartSymbols( Nodes, true );

        for ( int nNodeIdx = 0; nNodeIdx < StartSymbolCount; ++nNodeIdx )
        {
            IODNode*    pINode    = Nodes.GetAt( nNodeIdx );
            ZBSymbol*    pSymbol    = static_cast<ZBSymbol*>( pINode );

            if ( !pSymbol )
            {
                continue;
            }

            // Create a model state machine for each start symbol
            StateMachineHandle hStateMachine =
                m_pAutomationMachine->GetStateMachineCollection().CreateNewStateMachine( pSymbol,    // The start symbol
                                                                                         NULL );    // No link before

            if ( hStateMachine == -1 )
            {
                // Log error
                continue;
            }

            m_MachineHandleSet.Add( hStateMachine );
        }
    }

    // Call the derived method
    m_pAutomationMachine->OnStart( m_pLog );

    // Initialize internal variabes
    m_LoopCounter        = 0;
    m_WaitingCounter    = 0;
    m_IsPausedCounter    = 0;
}

void ZBMainAutomationRunnerThread::DoWork()
{
    ZBStateMachineCollection Collection;
    m_pAutomationMachine->MergeAllStateObjects( Collection );

    if ( Collection.GetStateMachineCount() == 0 )
    {
        // Now it is finished
        Stop();
        return;
    }

    ++m_LoopCounter;

    if ( m_pAutomationMachine->GetMaximumLoop() != -1 &&
         m_LoopCounter > m_pAutomationMachine->GetMaximumLoop() )
    {
        // Stop the worker thread
        Stop();

        // Call the virtual function for advise
        m_pAutomationMachine->OnReachMaximumLoopCounter( m_pLog );

        return;
    }

    // For each state machine,
    // do the work
    ZBStateMachineIterator i( &Collection.GetStateMachineSetConst() );

    for ( ZBStateMachine* pStateMachine = i.GetFirst(); pStateMachine; pStateMachine = i.GetNext() )
    {
        // Call the call-back function
        if ( !m_pAutomationMachine->OnBeforeRequestMoveForward( pStateMachine->GetCurrentStateObject(),
                                                                pStateMachine,
                                                                m_pLog ) )
        {
            return;
        }

        ZBSymbolSet SymbolSet;
        ZBStateLinksSet StateLinkSet;

        switch ( m_pAutomationMachine->RequestMoveForward( pStateMachine->GetCurrentStateObject(),
                                                           pStateMachine,
                                                           SymbolSet,
                                                           StateLinkSet,
                                                           m_pLog ) )
        {
            case ZBAutomationMachine::AS_IsWaitingForLinks:
            {
                // Call the call-back for waiting for other links object
                m_pAutomationMachine->OnObjectIsWaitingForOtherLinks( pStateMachine->GetCurrentStateObject(),
                                                                      pStateMachine,
                                                                      m_pLog );

                // Increment the waiting counter
                ++m_WaitingCounter;

                if ( m_pAutomationMachine->GetMaximumWaitingForOtherLinks() != -1 &&
                     m_WaitingCounter > m_pAutomationMachine->GetMaximumWaitingForOtherLinks() )
                {
                    // Stop the worker thread
                    Stop();

                    // Call the virtual function for advise
                    m_pAutomationMachine->OnReachMaximumWaitingForOtherLinksCounter( m_pLog );

                    return;
                }

                break;
            }

            case ZBAutomationMachine::AS_IsPaused:
            {
                // Call the call-back for in paused object
                m_pAutomationMachine->OnObjectIsPaused( pStateMachine->GetCurrentStateObject(),
                                                        pStateMachine,
                                                        m_pLog );

                // Increment the pause counter
                ++m_IsPausedCounter;

                if ( m_pAutomationMachine->GetMaximumPaused() != -1 &&
                     m_IsPausedCounter > m_pAutomationMachine->GetMaximumPaused() )
                {
                    // Stop the worker thread
                    Stop();

                    // Call the virtual function for advise
                    m_pAutomationMachine->OnReachMaximumInPauseCounter( m_pLog );

                    return;
                }

                break;
            }

            case ZBAutomationMachine::AS_IsFinished:
            {
                // Call the call-back function
                if ( !m_pAutomationMachine->OnBeforeMoveForward( pStateMachine->GetCurrentStateObject(),
                                                                 pStateMachine,
                                                                 m_pLog ) )
                {
                    return;
                }

                // Call the call-back for finished object
                m_pAutomationMachine->OnObjectIsFinished( pStateMachine->GetCurrentStateObject(),
                                                          pStateMachine,
                                                          m_pLog );

                // Does nothing 
                if ( !m_pAutomationMachine->MoveFinishedStateMachine( pStateMachine ) )
                {
                    // Stop the worker thread
                    Stop();
                    return;
                }

                break;
            }

            case ZBAutomationMachine::AS_CanMoveForward:
            {
                // Call the call-back function
                if ( !m_pAutomationMachine->OnBeforeMoveForward( pStateMachine->GetCurrentStateObject(),
                                                                 pStateMachine,
                                                                 m_pLog ) )
                {
                    return;
                }

                // Now, push the new symbol set and the associated state links 
                if ( SymbolSet.GetSize() == 1 )
                {
                    // No more demultiplication, just push the new symbol on the stack
                    // First, locate the original state machine 
                    // and merge them if necessary
                    ZBStateMachine* pOriginalStateMachine =
                                        m_pAutomationMachine->MergeSourceStateMachines( pStateMachine );

                    // Call the call-back function
                    if ( !m_pAutomationMachine->OnAfterMoveForward( pOriginalStateMachine->GetCurrentStateObject(),
                                                                    pOriginalStateMachine,
                                                                    m_pLog ) )
                    {
                        return;
                    }

                    // Then, push the symbol and the state link
                    if ( pOriginalStateMachine )
                    {
                        pOriginalStateMachine->PushSymbol( SymbolSet.GetAt( 0 ),
                                                           StateLinkSet.GetAt( 0 ) );
                    }

                    // Call the call-back function
                    if ( !m_pAutomationMachine->OnNextSymbolAfterMoveForward( pOriginalStateMachine->GetCurrentStateObject(),
                                                                              pOriginalStateMachine,
                                                                              m_pLog ) )
                    {
                        return;
                    }
                }
                else if ( SymbolSet.GetSize() > 1 )
                {
                    // Now for each symbol, create a new state machine
                    // First, locate the original state machine 
                    // and merge them if necessary
                    ZBStateMachine* pOriginalStateMachine =
                                        m_pAutomationMachine->MergeSourceStateMachines( pStateMachine );

                    // Then, push the symbol and the state link
                    if ( pOriginalStateMachine )
                    {
                        // For each symbol, create a new state machine.
                        // Except for the first one where we continue to 
                        // use the existing.
                        // Retreive the current state object of the current state machine
                        ZBStateObject* pInitialStateObject = pOriginalStateMachine->GetCurrentStateObject();

                        // Call the call-back function
                        if ( !m_pAutomationMachine->OnAfterMoveForward( pOriginalStateMachine->GetCurrentStateObject(),
                                                                        pOriginalStateMachine,
                                                                        m_pLog ) )
                        {
                            return;
                        }

                        // Then, push the first symbol and the first state link
                        // on the existing state machine
                        pOriginalStateMachine->PushSymbol( SymbolSet.GetAt( 0 ),
                                                           StateLinkSet.GetAt( 0 ) );

                        // Call the call-back function
                        if ( !m_pAutomationMachine->OnNextSymbolAfterMoveForward( pOriginalStateMachine->GetCurrentStateObject(),
                                                                                  pOriginalStateMachine,
                                                                                  m_pLog ) )
                        {
                            return;
                        }

                        // For all others, create a new state machine.
                        // The starter point is a clone of the current state object
                        for ( int i = 1; i < SymbolSet.GetSize(); ++i )
                        {
                            // Create a model state machine for each state object
                            StateMachineHandle hStateMachine =
                                m_pAutomationMachine->GetStateMachineCollection().CreateNewStateMachine( pInitialStateObject->Clone() );

                            if ( hStateMachine == -1 )
                            {
                                // Log error
                                // Stop the worker thread
                                Stop();
                                return;
                            }

                            m_MachineHandleSet.Add( hStateMachine );

                            // And now push the state link and the symbol
                            // to the newly created state machine
                            ZBStateMachine* pNewStateMachine = m_pAutomationMachine->GetStateMachine( hStateMachine );

                            if ( !pNewStateMachine )
                            {
                                // Log error
                                // Stop the worker thread
                                Stop();
                                return;
                            }

                            pNewStateMachine->PushSymbol( SymbolSet.GetAt( i ), StateLinkSet.GetAt( i ) );

                            // Call the call-back function
                            if ( !m_pAutomationMachine->OnNextSymbolAfterMoveForward( pNewStateMachine->GetCurrentStateObject(),
                                                                                      pNewStateMachine,
                                                                                      m_pLog ) )
                            {
                                return;
                            }
                        }
                    }
                }

                break;
            }

            case ZBAutomationMachine::AS_Error:
            default:
            {
                // Error and Unknown state generates the end of the work
                // Call the call-back for error on object
                m_pAutomationMachine->OnObjectError( pStateMachine->GetCurrentStateObject(),
                                                     pStateMachine,
                                                     m_pLog );

                // Stop the worker thread
                Stop();
                return;
            }
        }
    } // End state machine loop
}

void ZBMainAutomationRunnerThread::EndWork()
{
    // Call the derived method
    m_pAutomationMachine->OnStop( m_pLog );
}
