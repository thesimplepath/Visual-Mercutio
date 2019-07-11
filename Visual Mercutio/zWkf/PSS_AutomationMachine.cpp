/****************************************************************************
 * ==> PSS_AutomationMachine -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an automation machine                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_AutomationMachine.h"

// processsoft
#include "zBaseLib\ZILog.h"
#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "PSS_MainAutomationRunnerThread.h"
#include "ZBStateMachine.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_AutomationMachine
//---------------------------------------------------------------------------
PSS_AutomationMachine::PSS_AutomationMachine(ZDProcessGraphModelMdl* pModel,
                                             ZILog*                  pLog,
                                             int                     maxLoop,
                                             int                     maxPaused,
                                             int                     maxWaitingForOtherLinks,
                                             bool                    allowUncompletePath) :
    m_pModel(pModel),
    m_pMainThread(NULL),
    m_pSymbol(NULL),
    m_pLog(pLog),
    m_ErrorCounter(0),
    m_WarningCounter(0),
    m_MaxLoop(maxLoop),
    m_MaxPaused(maxPaused),
    m_MaxWaitingForOtherLinks(maxWaitingForOtherLinks),
    m_IsLogging(false),
    m_AllowUncompletePath(allowUncompletePath)
{
    m_StateMachineCollection.AssignModel(m_pModel);
}
//---------------------------------------------------------------------------
PSS_AutomationMachine::PSS_AutomationMachine(ZBSymbol*               pSymbol,
                                             ZDProcessGraphModelMdl* pModel,
                                             ZILog*                  pLog,
                                             int                     maxLoop,
                                             int                     maxPaused,
                                             int                     maxWaitingForOtherLinks,
                                             bool                    allowUncompletePath) :
    m_pModel(pModel),
    m_pMainThread(NULL),
    m_pSymbol(pSymbol),
    m_pLog(pLog),
    m_ErrorCounter(0),
    m_WarningCounter(0),
    m_MaxLoop(maxLoop),
    m_MaxPaused(maxPaused),
    m_MaxWaitingForOtherLinks(maxWaitingForOtherLinks),
    m_IsLogging(false),
    m_AllowUncompletePath(allowUncompletePath)
{
    m_StateMachineCollection.AssignModel(m_pModel);
}
//---------------------------------------------------------------------------
PSS_AutomationMachine::~PSS_AutomationMachine()
{
    if (m_pMainThread)
        delete m_pMainThread;
}
//---------------------------------------------------------------------------
int PSS_AutomationMachine::GetLoopCounter() const
{
    return (m_pMainThread ? m_pMainThread->GetLoopCounter() : -1);
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::ResetLoopCounter()
{
    if (m_pMainThread)
        m_pMainThread->ResetLoopCounter();
}
//---------------------------------------------------------------------------
int PSS_AutomationMachine::GetWaitingCounter() const
{
    return (m_pMainThread ? m_pMainThread->GetWaitingCounter() : -1);
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::ResetWaitingCounter()
{
    if (m_pMainThread)
        m_pMainThread->ResetWaitingCounter();
}
//---------------------------------------------------------------------------
int PSS_AutomationMachine::GetIsPausedCounter() const
{
    return (m_pMainThread ? m_pMainThread->GetIsPausedCounter() : -1);
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::ResetIsPausedCounter()
{
    if (m_pMainThread)
        m_pMainThread->ResetIsPausedCounter();
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::Start(int timeout)
{
    if (!m_pModel)
        return false;

    m_pMainThread = new PSS_MainAutomationRunnerThread(this, timeout, m_pLog);

    return (m_pMainThread->StartThread() ? true : false);
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::Stop()
{
    if (m_pMainThread)
        m_pMainThread->Stop();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::Pause()
{
    if (!m_pMainThread)
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::Resume()
{
    if (!m_pMainThread)
        return false;

    return true;
}
//---------------------------------------------------------------------------
PSS_AutomationMachine::IEAutomationMoveStatus PSS_AutomationMachine::RequestMoveForward(ZBStateObject*   pState,
                                                                                        ZBStateMachine*  pStateMachine,
                                                                                        ZBSymbolSet&     symbolSet,
                                                                                        ZBStateLinksSet& stateLinkSet,
                                                                                        ZILog*           pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return IE_AS_Error;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnStart(ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnStop(ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnPause(ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnResume(ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnObjectIsFinished(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnObjectIsPaused(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnObjectIsWaitingForOtherLinks(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnBeforeRequestMoveForward(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnNextSymbolAfterMoveForward(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnBeforeMoveForward(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnAfterMoveForward(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnBeforeMoveBackward(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnAfterMoveBackward(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnObjectError(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnReachMaxLoopCounter(ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnReachMaxWaitingForOtherLinksCounter(ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnReachMaxInPauseCounter(ZILog* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
std::size_t PSS_AutomationMachine::CopyNodeArrayToSymbolSet(CODNodeArray& nodes, ZBSymbolSet& symbolSet)
{
    std::size_t elementCount = nodes.GetSize();

    for (std::size_t nodeIndex = 0; nodeIndex < elementCount; ++nodeIndex)
    {
        IODNode* pINode = nodes.GetAt(nodeIndex);

        if (!pINode)
            continue;

        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pINode);

        if (!pSymbol)
            continue;

        // add the symbol to the symbol set
        symbolSet.Add(pSymbol);
    }

    return symbolSet.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_AutomationMachine::CopyEdgeArrayToStateLinksSet(CODEdgeArray&              edges,
                                                                ZBStateLink::LinkDirection direction,
                                                                ZBStateLinksSet&           stateLinkSet)
{
    std::size_t elementCount = edges.GetSize();

    for (std::size_t edgeIndex = 0; edgeIndex < elementCount; ++edgeIndex)
    {
        IODEdge* pIEdge = edges.GetAt(edgeIndex);

        if (!pIEdge)
            continue;

        ZBLinkSymbol* pLink = dynamic_cast<ZBLinkSymbol*>(pIEdge);

        if (!pLink)
            continue;

        // add the state link to the state link set
        ZBStateLink* pStateLink = new ZBStateLink(pLink, direction, GetModel());
        stateLinkSet.Add(pStateLink);
    }

    return stateLinkSet.GetSize();
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::MergeAllStateObjects(ZBStateMachineCollection& collection)
{
    // copy collection to the collection passed as parameter
    collection.CopyCurrentStateObjects(m_StateMachineCollection, true);

    // iterate through all elements of the collection
    for (int i = 0; i < int(collection.GetStateMachineCount()); ++i)
    {
        ZBStateMachine* pSrcStateMachine = collection.GetStateMachine(i);
        ASSERT(pSrcStateMachine);

        // from the next element till then end of the collection, compare if the state machine last element is equals
        for (int j = i + 1; j < int(collection.GetStateMachineCount()); ++j)
        {
            ZBStateMachine* pDstStateMachine = collection.GetStateMachine(j);
            ASSERT(pDstStateMachine);

            // try to locate if the same state machine object id was found
            if (pSrcStateMachine->IsLastObjectEqual(pDstStateMachine))
            {
                if (!MergeStateMachine(i, j, collection, true))
                    return false;

                --j;
            }
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::MergeStateMachine(std::size_t               srcIndex,
                                              std::size_t               dstIndex,
                                              ZBStateMachineCollection& collection,
                                              bool                      deleteDestination)
{
    // get the source state machine
    ZBStateMachine* pSrcStateMachine = collection.GetStateMachine(srcIndex);
    ASSERT(pSrcStateMachine);

    // get the destination state machine
    ZBStateMachine* pDstStateMachine = collection.GetStateMachine(dstIndex);
    ASSERT(pDstStateMachine);

    // merge the state machines together
    if (!pSrcStateMachine->Merge(pDstStateMachine))
        return false;

    if (deleteDestination)
        collection.DeleteStateMachine(dstIndex);

    return true;
}
//---------------------------------------------------------------------------
ZBStateMachine* PSS_AutomationMachine::MergeSourceStateMachines(ZBStateMachine* pStateMachineToMerge)
{
    // locate the first original state machine
    ZBStateMachine* pFirstStateMachine = FindOriginalStateMachine(pStateMachineToMerge);

    if (!pFirstStateMachine)
        return NULL;

    // merge all states
    pFirstStateMachine->MergeAllStates();

    ZBStateMachineIterator it(&GetStateMachineSet());

    // iterate through the original state machine collection and try to locate the same state machine
    for (ZBStateMachine* pStateMachine = it.GetFirst(); pStateMachine;)
        // if found, merge them and return the merged machine
        if (pStateMachine != pFirstStateMachine && pStateMachine->IsLastObjectEqual(pFirstStateMachine))
        {
            // if equals, merge the two objects together
            if (!pFirstStateMachine->Merge(pStateMachine))
                return NULL;

            // delete the second state machine
            delete pStateMachine;

            // remove it from the set
            it.Remove();

            // get the current element once removed
            pStateMachine = it.Get();
        }
        else
            // get the next element
            pStateMachine = it.GetNext();

    return pFirstStateMachine;
}
//---------------------------------------------------------------------------
ZBStateMachine* PSS_AutomationMachine::FindOriginalStateMachine(ZBStateMachine* pStateMachineToLocate)
{
    ZBStateMachineIterator it(&GetStateMachineSetConst());

    // iterate through the original state machine collection and try to locate the same state machine
    for (ZBStateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext() )
        if (pStateMachine->IsLastObjectEqual(pStateMachineToLocate))
            return pStateMachine;

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::MoveFinishedStateMachine(ZBStateMachine* pFinishedStateMachine)
{
    // locate the first original state machine
    ZBStateMachine* pStateMachineToMove = FindOriginalStateMachine(pFinishedStateMachine);

    if (!pStateMachineToMove)
        return false;

    ZBStateMachineIterator it(&GetStateMachineSet());

    // iterate through state machines
    for (ZBStateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext())
        if (pStateMachine == pStateMachineToMove)
        {
            // add the state machine to the finished state machine collection
            if (AddFinishedStateMachine(pStateMachine) == -1)
                return false;

            // remove it from the set
            it.Remove();
            break;
        }

    return true;
}
//---------------------------------------------------------------------------
