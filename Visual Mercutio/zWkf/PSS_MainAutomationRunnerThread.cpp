/****************************************************************************
 * ==> PSS_MainAutomationRunnerThread --------------------------------------*
 ****************************************************************************
 * Description : The main automation runner thread                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_MainAutomationRunnerThread.h"

// processsoft
#include "zBaseLib\ZILog.h"
#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "PSS_AutomationMachine.h"
#include "ZBStateMachine.h"
#include "ZBStateMachineCollection.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_MainAutomationRunnerThread
//---------------------------------------------------------------------------
PSS_MainAutomationRunnerThread::PSS_MainAutomationRunnerThread() :
    m_pAutomationMachine(NULL),
    m_pLog(NULL),
    m_Timeout(-1),
    m_LoopCounter(0),
    m_WaitingCounter(0),
    m_IsPausedCounter(0)
{}
//---------------------------------------------------------------------------
PSS_MainAutomationRunnerThread::PSS_MainAutomationRunnerThread(PSS_AutomationMachine* pAutomationMachine,
                                                               int                    timeout,
                                                               ZILog*                 pLog) :
    m_pAutomationMachine(pAutomationMachine),
    m_pLog(pLog),
    m_Timeout(timeout),
    m_LoopCounter(0),
    m_WaitingCounter(0),
    m_IsPausedCounter(0)
{}
//---------------------------------------------------------------------------
PSS_MainAutomationRunnerThread::~PSS_MainAutomationRunnerThread()
{}
//---------------------------------------------------------------------------
BOOL PSS_MainAutomationRunnerThread::StartThread()
{
    // create the thread only if the context has been correctly assigned
    if (!m_pAutomationMachine || !m_pAutomationMachine->GetModel())
        return FALSE;

    // comment the next following two line for having a multi-threaded operation
    Start((void*)this);

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_MainAutomationRunnerThread::StartWork()
{
    ASSERT(m_pAutomationMachine && m_pAutomationMachine->GetModel());

    // delete all state machines
    m_pAutomationMachine->DeleteAllStateMachines();
    m_pAutomationMachine->DeleteAllFinishedStateMachines();

    // if a specific start symbol is defined, initialize the new state machine with it
    if (m_pAutomationMachine->GetStartSymbol())
    {
        // create a model state machine for each start symbol
        StateMachineHandle hStateMachine =
                m_pAutomationMachine->GetStateMachineCollection().CreateNewStateMachine(m_pAutomationMachine->GetStartSymbol(), NULL);

        // todo -cFeature -oJean: log the error
        if (hStateMachine == -1)
            return;

        m_MachineHandleSet.Add(hStateMachine);
    }
    else
    {
        CODNodeArray nodes;

        // true for deeply retrieval
        const int startSymbolCount = int(m_pAutomationMachine->GetModel()->GetStartSymbols(nodes, true));

        for (int nodeIndex = 0; nodeIndex < startSymbolCount; ++nodeIndex)
        {
            // get next symbol
            IODNode*  pINode  = nodes.GetAt(nodeIndex);
            ZBSymbol* pSymbol = static_cast<ZBSymbol*>(pINode);

            if (!pSymbol)
                continue;

            // create a model state machine for each start symbol
            StateMachineHandle hStateMachine =
                    m_pAutomationMachine->GetStateMachineCollection().CreateNewStateMachine(pSymbol, NULL);

            // todo -cFeature -oJean: log the error
            if (hStateMachine == -1)
                continue;

            m_MachineHandleSet.Add(hStateMachine);
        }
    }

    // call the derived method
    m_pAutomationMachine->OnStart(m_pLog);

    // initialize internal variabes
    m_LoopCounter     = 0;
    m_WaitingCounter  = 0;
    m_IsPausedCounter = 0;
}
//---------------------------------------------------------------------------
void PSS_MainAutomationRunnerThread::DoWork()
{
    ZBStateMachineCollection collection;
    m_pAutomationMachine->MergeAllStateObjects(collection);

    if (!collection.GetStateMachineCount())
    {
        Stop();
        return;
    }

    ++m_LoopCounter;

    if (m_pAutomationMachine->GetMaxLoop() != -1 && m_LoopCounter > m_pAutomationMachine->GetMaxLoop())
    {
        // stop the worker thread
        Stop();

        // call the virtual function for advise
        m_pAutomationMachine->OnReachMaxLoopCounter(m_pLog);

        return;
    }

    ZBStateMachineIterator it(&collection.GetStateMachineSetConst());

    // for each state machine, do the work
    for (ZBStateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext())
    {
        // call the callback function
        if (!m_pAutomationMachine->OnBeforeRequestMoveForward(pStateMachine->GetCurrentStateObject(),
                                                              pStateMachine,
                                                              m_pLog))
            return;

        ZBSymbolSet     symbolSet;
        ZBStateLinksSet stateLinkSet;

        switch (m_pAutomationMachine->RequestMoveForward(pStateMachine->GetCurrentStateObject(),
                                                         pStateMachine,
                                                         symbolSet,
                                                         stateLinkSet,
                                                         m_pLog))
        {
            case PSS_AutomationMachine::IE_AS_IsWaitingForLinks:
                // call the callback for waiting for other links object
                m_pAutomationMachine->OnObjectIsWaitingForOtherLinks(pStateMachine->GetCurrentStateObject(),
                                                                     pStateMachine,
                                                                     m_pLog);

                // increment the waiting counter
                ++m_WaitingCounter;

                if (m_pAutomationMachine->GetMaxWaitingForOtherLinks() != -1 &&
                    m_WaitingCounter > m_pAutomationMachine->GetMaxWaitingForOtherLinks())
                {
                    // stop the worker thread
                    Stop();

                    // call the virtual function for notification
                    m_pAutomationMachine->OnReachMaxWaitingForOtherLinksCounter(m_pLog);

                    return;
                }

                break;

            case PSS_AutomationMachine::IE_AS_IsPaused:
                // call the callback for in paused object
                m_pAutomationMachine->OnObjectIsPaused(pStateMachine->GetCurrentStateObject(),
                                                       pStateMachine,
                                                       m_pLog);

                // increment the pause counter
                ++m_IsPausedCounter;

                if (m_pAutomationMachine->GetMaxPaused() != -1 &&
                    m_IsPausedCounter > m_pAutomationMachine->GetMaxPaused())
                {
                    // stop the worker thread
                    Stop();

                    // call the virtual function for notification
                    m_pAutomationMachine->OnReachMaxInPauseCounter(m_pLog);

                    return;
                }

                break;

            case PSS_AutomationMachine::IE_AS_IsFinished:
                // call the callback function
                if ( !m_pAutomationMachine->OnBeforeMoveForward(pStateMachine->GetCurrentStateObject(),
                                                                pStateMachine,
                                                                m_pLog))
                    return;

                // call the finished object callback
                m_pAutomationMachine->OnObjectIsFinished(pStateMachine->GetCurrentStateObject(),
                                                         pStateMachine,
                                                         m_pLog);

                // do nothing
                if (!m_pAutomationMachine->MoveFinishedStateMachine(pStateMachine))
                {
                    // stop the worker thread
                    Stop();
                    return;
                }

                break;

            case PSS_AutomationMachine::IE_AS_CanMoveForward:
                // call the callback function
                if (!m_pAutomationMachine->OnBeforeMoveForward(pStateMachine->GetCurrentStateObject(),
                                                               pStateMachine,
                                                               m_pLog))
                    return;

                // push the new symbol set and the associated state links 
                if (symbolSet.GetSize() == 1)
                {
                    // no more demultiplication, just push the new symbol on the stack. First, locate the original
                    // state machines and merge them if necessary
                    ZBStateMachine* pOriginalStateMachine =
                            m_pAutomationMachine->MergeSourceStateMachines(pStateMachine);

                    // call the callback function
                    if (!m_pAutomationMachine->OnAfterMoveForward(pOriginalStateMachine->GetCurrentStateObject(),
                                                                  pOriginalStateMachine,
                                                                  m_pLog))
                        return;

                    // push the symbol and the state link
                    if (pOriginalStateMachine)
                        pOriginalStateMachine->PushSymbol(symbolSet.GetAt(0),
                                                          stateLinkSet.GetAt(0));

                    // call the callback function
                    if (!m_pAutomationMachine->OnNextSymbolAfterMoveForward(pOriginalStateMachine->GetCurrentStateObject(),
                                                                            pOriginalStateMachine,
                                                                            m_pLog))
                        return;
                }
                else
                if (symbolSet.GetSize() > 1)
                {
                    // for each symbol, create a new state machine. First, locate the original state machines
                    // and merge them if necessary
                    ZBStateMachine* pOriginalStateMachine =
                            m_pAutomationMachine->MergeSourceStateMachines(pStateMachine);

                    // push the symbol and the state link
                    if (pOriginalStateMachine)
                    {
                        // for each symbol, create a new state machine, except for the first one, which continue to
                        // use the existing. Get the current state object of the current state machine
                        ZBStateObject* pInitialStateObject = pOriginalStateMachine->GetCurrentStateObject();

                        // call the callback function
                        if (!m_pAutomationMachine->OnAfterMoveForward(pOriginalStateMachine->GetCurrentStateObject(),
                                                                      pOriginalStateMachine,
                                                                      m_pLog))
                            return;

                        // push the first symbol and the first state link on the existing state machine
                        pOriginalStateMachine->PushSymbol(symbolSet.GetAt(0),
                                                          stateLinkSet.GetAt(0));

                        // call the callback function
                        if (!m_pAutomationMachine->OnNextSymbolAfterMoveForward(pOriginalStateMachine->GetCurrentStateObject(),
                                                                                pOriginalStateMachine,
                                                                                m_pLog))
                            return;

                        // for all others, create a new state machine. The starter point is a clone of the current
                        // state object
                        for (int i = 1; i < symbolSet.GetSize(); ++i)
                        {
                            // create a model state machine for each state object
                            StateMachineHandle hStateMachine =
                                    m_pAutomationMachine->GetStateMachineCollection().CreateNewStateMachine(pInitialStateObject->Clone());

                            if (hStateMachine == -1)
                            {
                                // log error, stop the worker thread
                                Stop();
                                return;
                            }

                            m_MachineHandleSet.Add(hStateMachine);

                            // push the state link and the symbol to the newly created state machine
                            ZBStateMachine* pNewStateMachine = m_pAutomationMachine->GetStateMachine(hStateMachine);

                            if (!pNewStateMachine)
                            {
                                // log error, stop the worker thread
                                Stop();
                                return;
                            }

                            pNewStateMachine->PushSymbol(symbolSet.GetAt(i), stateLinkSet.GetAt(i));

                            // call the callback function
                            if (!m_pAutomationMachine->OnNextSymbolAfterMoveForward(pNewStateMachine->GetCurrentStateObject(),
                                                                                    pNewStateMachine,
                                                                                    m_pLog))
                                return;
                        }
                    }
                }

                break;

            default:
                // error and unknown state generates the end of the work. Call the callback for error on object
                m_pAutomationMachine->OnObjectError(pStateMachine->GetCurrentStateObject(),
                                                    pStateMachine,
                                                    m_pLog);

                // stop the worker thread
                Stop();
                return;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_MainAutomationRunnerThread::EndWork()
{
    // call the derived method
    m_pAutomationMachine->OnStop(m_pLog);
}
//---------------------------------------------------------------------------
