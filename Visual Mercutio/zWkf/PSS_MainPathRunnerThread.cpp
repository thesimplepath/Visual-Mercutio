/****************************************************************************
 * ==> PSS_MainPathRunnerThread --------------------------------------------*
 ****************************************************************************
 * Description : The main path runner thread                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_MainPathRunnerThread.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "PSS_PathMachine.h"
#include "PSS_StateMachine.h"
#include "PSS_StateMachineCollection.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_MainPathRunnerThread
//---------------------------------------------------------------------------
PSS_MainPathRunnerThread::PSS_MainPathRunnerThread() :
    PSS_ThinThread(),
    m_pPathMachine(NULL),
    m_pLog(NULL),
    m_Timeout(-1),
    m_LoopCounter(0),
    m_WaitingCounter(0),
    m_IsPausedCounter(0)
{}
//---------------------------------------------------------------------------
PSS_MainPathRunnerThread::PSS_MainPathRunnerThread(PSS_PathMachine* pAutomationMachine,
                                                   int              timeout,
                                                   PSS_Log*         pLog) :
    PSS_ThinThread(),
    m_pPathMachine(pAutomationMachine),
    m_pLog(pLog),
    m_Timeout(timeout),
    m_LoopCounter(0),
    m_WaitingCounter(0),
    m_IsPausedCounter(0)
{}
//---------------------------------------------------------------------------
PSS_MainPathRunnerThread::~PSS_MainPathRunnerThread()
{}
//---------------------------------------------------------------------------
BOOL PSS_MainPathRunnerThread::StartThread()
{
    // create the thread only if the context has been correctly assigned
    if (!m_pPathMachine || !m_pPathMachine->GetModel())
        return FALSE;

    // comment the next following two line for having a multi-threaded operation
    Start((void*)this);
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_MainPathRunnerThread::StartWork()
{
    ASSERT(m_pPathMachine && m_pPathMachine->GetModel());

    // delete all state machines
    m_pPathMachine->DeleteAllStateMachines();
    m_pPathMachine->DeleteAllFinishedStateMachines();

    if (!m_pPathMachine->GetSymbol())
        return;

    // create a model state machine for each start symbol
    PSS_StateMachineHandle hStateMachine =
            m_pPathMachine->GetStateMachineCollection().CreateNewStateMachine(m_pPathMachine->GetSymbol(), NULL);

    if (hStateMachine == -1)
        // todo -cFeature -oJean: Log error
        return;

    m_MachineHandleSet.Add(hStateMachine);

    // call the derived method
    m_pPathMachine->OnStart(m_pLog);

    // initialize internal variabes
    m_LoopCounter     = 0;
    m_WaitingCounter  = 0;
    m_IsPausedCounter = 0;
}
//---------------------------------------------------------------------------
void PSS_MainPathRunnerThread::DoWork()
{
    PSS_StateMachineCollection collection;
    m_pPathMachine->MergeAllStateObjects(collection);

    if (!collection.GetStateMachineCount())
    {
        // now it's finished
        Stop();
        return;
    }

    ++m_LoopCounter;

    if (m_pPathMachine->GetMaxLoop() != -1 && m_LoopCounter > m_pPathMachine->GetMaxLoop())
    {
        // stop the worker thread
        Stop();

        // call the virtual function for notification
        m_pPathMachine->OnReachMaxLoopCounter(m_pLog);
        return;
    }
    PSS_StateMachineIterator it(&collection.GetStateMachineSetConst());

    // for each state machine, do the work
    for (PSS_StateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext())
    {
        // call the callback function
        if (!m_pPathMachine->OnBeforeRequestMoveForward(pStateMachine->GetCurrentStateObject(),
                                                        pStateMachine, 
                                                        m_pLog))
            return;
        
        PSS_SymbolSet     symbolSet;
        PSS_StateLinksSet stateLinkSet;

        switch (m_pPathMachine->RequestMoveForward(pStateMachine->GetCurrentStateObject(),
                                                   pStateMachine, 
                                                   symbolSet,
                                                   stateLinkSet, 
                                                   m_pLog))
        {
            case PSS_PathMachine::IE_PS_IsWaitingForLinks:
                // call the callback for waiting for other links object
                m_pPathMachine->OnObjectIsWaitingForOtherLinks(pStateMachine->GetCurrentStateObject(),
                                                               pStateMachine, 
                                                               m_pLog);

                // increment the waiting counter
                ++m_WaitingCounter;

                if (m_pPathMachine->GetMaxWaitingForOtherLinks() != -1 &&
                    m_WaitingCounter > m_pPathMachine->GetMaxWaitingForOtherLinks())
                {
                    // stop the worker thread
                    Stop();

                    // call the virtual function for notification
                    m_pPathMachine->OnReachMaxWaitingForOtherLinksCounter(m_pLog);
                    return;
                }

                break;

            case PSS_PathMachine::IE_PS_IsPaused:
                // call the callback for in paused object
                m_pPathMachine->OnObjectIsPaused(pStateMachine->GetCurrentStateObject(),
                                                 pStateMachine, 
                                                 m_pLog);

                // increment the pause counter
                ++m_IsPausedCounter;

                if (m_pPathMachine->GetMaxPaused() != -1 && m_IsPausedCounter > m_pPathMachine->GetMaxPaused())
                {
                    // stop the worker thread
                    Stop();

                    // call the virtual function for notification
                    m_pPathMachine->OnReachMaxInPauseCounter(m_pLog);
                    return;
                }

                break;

            case PSS_PathMachine::IE_PS_IsFinished:
                // call the callback function
                if (!m_pPathMachine->OnBeforeMoveForward(pStateMachine->GetCurrentStateObject(),
                                                         pStateMachine,
                                                         m_pLog))
                    return;

                // call the callback for finished object
                m_pPathMachine->OnObjectIsFinished(pStateMachine->GetCurrentStateObject(),
                                                   pStateMachine,
                                                   m_pLog);

                // do nothing
                if (!m_pPathMachine->MoveFinishedStateMachine(pStateMachine))
                {
                    // stop the worker thread
                    Stop();
                    return;
                }

                break;

            case PSS_PathMachine::IE_PS_CanMoveForward:
                // call the callback function
                if (!m_pPathMachine->OnBeforeMoveForward(pStateMachine->GetCurrentStateObject(),
                                                         pStateMachine,
                                                         m_pLog))
                    return;

                // push the new symbol set and the associated state links
                if (symbolSet.GetSize() == 1)
                {
                    // No more demultiplication, just push the new symbol on the stack. Locate the original
                    // state machines and merge them if necessary
                    PSS_StateMachine* pOriginalStateMachine =
                            m_pPathMachine->MergeSourceStateMachines(pStateMachine);

                    // call the callback function
                    if (!m_pPathMachine->OnAfterMoveForward(pOriginalStateMachine->GetCurrentStateObject(),
                                                            pOriginalStateMachine, 
                                                            m_pLog))
                        return;

                    // push the symbol and the state link
                    if (pOriginalStateMachine)
                        pOriginalStateMachine->PushSymbol(symbolSet.GetAt(0), stateLinkSet.GetAt(0));

                    // call the callback function
                    if (!m_pPathMachine->OnNextSymbolAfterMoveForward(pOriginalStateMachine->GetCurrentStateObject(),
                                                                      pOriginalStateMachine,
                                                                      m_pLog))
                        return;
                }
                else
                if (symbolSet.GetSize() > 1)
                {
                    // for each symbol, create a new state machine. Locate the original state machines
                    // and merge them if necessary
                    PSS_StateMachine* pOriginalStateMachine =
                            m_pPathMachine->MergeSourceStateMachines(pStateMachine);

                    // push the symbol and the state link
                    if (pOriginalStateMachine)
                    {
                        // for each symbol, create a new state machine, except for the first one for which
                        // the existing one continue to be used. Get the current state object from the current
                        // state machine
                        PSS_StateObject* pInitialStateObject = pOriginalStateMachine->GetCurrentStateObject();

                        // call the callback function
                        if (!m_pPathMachine->OnAfterMoveForward(pOriginalStateMachine->GetCurrentStateObject(),
                                                                pOriginalStateMachine,
                                                                m_pLog))
                            return;

                        // push the first symbol and the first state link on the existing state machine
                        pOriginalStateMachine->PushSymbol(symbolSet.GetAt(0), stateLinkSet.GetAt(0));

                        // call the callback function
                        if (!m_pPathMachine->OnNextSymbolAfterMoveForward(pOriginalStateMachine->GetCurrentStateObject(),
                                                                          pOriginalStateMachine,
                                                                          m_pLog))
                            return;

                        // for all others, create a new state machine. The start point is a clone
                        // of the current state object
                        for (int i = 1; i < symbolSet.GetSize(); ++i)
                        {
                            // create a model state machine for each state object
                            PSS_StateMachineHandle hStateMachine =
                                    m_pPathMachine->GetStateMachineCollection().CreateNewStateMachine(pInitialStateObject->Clone());

                            if (hStateMachine == -1)
                            {
                                // todo -cFeature -oJean: Log error
                                // stop the worker thread
                                Stop();
                                return;
                            }

                            m_MachineHandleSet.Add(hStateMachine);

                            // push the state link and the symbol to the newly created state machine
                            PSS_StateMachine* pNewStateMachine = m_pPathMachine->GetStateMachine(hStateMachine);

                            if (!pNewStateMachine)
                            {
                                // todo -cFeature -oJean: Log error
                                // stop the worker thread
                                Stop();
                                return;
                            }

                            pNewStateMachine->PushSymbol(symbolSet.GetAt(i), stateLinkSet.GetAt(i));

                            // call the callback function
                            if (!m_pPathMachine->OnNextSymbolAfterMoveForward(pNewStateMachine->GetCurrentStateObject(),
                                                                              pNewStateMachine,
                                                                              m_pLog))
                                return;
                        }
                    }
                }

                break;

            default:
                // error and unknown state generates the end of the work. Call the callback for error on object
                m_pPathMachine->OnObjectError(pStateMachine->GetCurrentStateObject(),
                                              pStateMachine,
                                              m_pLog);

                // stop the worker thread
                Stop();
                return;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_MainPathRunnerThread::EndWork()
{
    // call the derived method
    m_pPathMachine->OnStop(m_pLog);
}
//---------------------------------------------------------------------------
