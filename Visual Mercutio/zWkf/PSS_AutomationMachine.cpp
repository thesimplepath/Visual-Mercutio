/****************************************************************************
 * ==> PSS_AutomationMachine -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an automation machine                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_AutomationMachine.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "PSS_MainAutomationRunnerThread.h"
#include "PSS_StateMachine.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_AutomationMachine
//---------------------------------------------------------------------------
PSS_AutomationMachine::PSS_AutomationMachine(PSS_ProcessGraphModelMdl* pModel,
                                             PSS_Log*                  pLog,
                                             int                       maxLoop,
                                             int                       maxPaused,
                                             int                       maxWaitingForOtherLinks,
                                             bool                      allowUncompletePath) :
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
PSS_AutomationMachine::PSS_AutomationMachine(PSS_Symbol*               pSymbol,
                                             PSS_ProcessGraphModelMdl* pModel,
                                             PSS_Log*                  pLog,
                                             int                       maxLoop,
                                             int                       maxPaused,
                                             int                       maxWaitingForOtherLinks,
                                             bool                      allowUncompletePath) :
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
PSS_AutomationMachine::IEAutomationMoveStatus PSS_AutomationMachine::RequestMoveForward(PSS_StateObject*   pState,
                                                                                        PSS_StateMachine*  pStateMachine,
                                                                                        PSS_SymbolSet&     symbolSet,
                                                                                        PSS_StateLinksSet& stateLinkSet,
                                                                                        PSS_Log*           pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return IE_AS_Error;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnStart(PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnStop(PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnPause(PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnResume(PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnObjectIsFinished(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnObjectIsPaused(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnObjectIsWaitingForOtherLinks(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnBeforeRequestMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnNextSymbolAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnBeforeMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnBeforeMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnAfterMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnObjectError(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnReachMaxLoopCounter(PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnReachMaxWaitingForOtherLinksCounter(PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::OnReachMaxInPauseCounter(PSS_Log* pLog)
{
    // do nothing in the base class, might be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
std::size_t PSS_AutomationMachine::CopyNodeArrayToSymbolSet(CODNodeArray& nodes, PSS_SymbolSet& symbolSet)
{
    const std::size_t elementCount = nodes.GetSize();

    for (std::size_t nodeIndex = 0; nodeIndex < elementCount; ++nodeIndex)
    {
        IODNode*    pINode  = nodes.GetAt(nodeIndex);
        PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pINode);

        if (!pSymbol)
            continue;

        // add the symbol to the symbol set
        symbolSet.Add(pSymbol);
    }

    return symbolSet.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_AutomationMachine::CopyEdgeArrayToStateLinksSet(CODEdgeArray&                  edges,
                                                                PSS_StateLink::IELinkDirection direction,
                                                                PSS_StateLinksSet&             stateLinkSet)
{
    const std::size_t elementCount = edges.GetSize();

    for (std::size_t edgeIndex = 0; edgeIndex < elementCount; ++edgeIndex)
    {
        IODEdge*        pIEdge = edges.GetAt(edgeIndex);
        PSS_LinkSymbol* pLink  = dynamic_cast<PSS_LinkSymbol*>(pIEdge);

        if (!pLink)
            continue;

        // add the state link to the state link set
        PSS_StateLink* pStateLink = new PSS_StateLink(pLink, direction, GetModel());
        stateLinkSet.Add(pStateLink);
    }

    return stateLinkSet.GetSize();
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::MergeAllStateObjects(PSS_StateMachineCollection& collection)
{
    // copy collection to the collection passed as parameter
    collection.CopyCurrentStateObjects(m_StateMachineCollection, true);

    // iterate through all collection elements
    for (int i = 0; i < int(collection.GetStateMachineCount()); ++i)
    {
        PSS_StateMachine* pSrcStateMachine = collection.GetStateMachine(i);
        ASSERT(pSrcStateMachine);

        // from the next element till then end of the collection, compare if the state machine last element is equals
        for (int j = i + 1; j < int(collection.GetStateMachineCount()); ++j)
        {
            PSS_StateMachine* pDstStateMachine = collection.GetStateMachine(j);
            ASSERT(pDstStateMachine);

            // try to locate the same state machine object id
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
bool PSS_AutomationMachine::MergeStateMachine(std::size_t                 srcIndex,
                                              std::size_t                 dstIndex,
                                              PSS_StateMachineCollection& collection,
                                              bool                        deleteDestination)
{
    // get the source state machine
    PSS_StateMachine* pSrcStateMachine = collection.GetStateMachine(srcIndex);
    ASSERT(pSrcStateMachine);

    // get the destination state machine
    PSS_StateMachine* pDstStateMachine = collection.GetStateMachine(dstIndex);
    ASSERT(pDstStateMachine);

    // merge the state machines together
    if (!pSrcStateMachine->Merge(pDstStateMachine))
        return false;

    if (deleteDestination)
        collection.DeleteStateMachine(dstIndex);

    return true;
}
//---------------------------------------------------------------------------
PSS_StateMachine* PSS_AutomationMachine::MergeSourceStateMachines(PSS_StateMachine* pStateMachineToMerge)
{
    // locate the first original state machine
    PSS_StateMachine* pFirstStateMachine = FindOriginalStateMachine(pStateMachineToMerge);

    if (!pFirstStateMachine)
        return NULL;

    // merge all states
    pFirstStateMachine->MergeAllStates();

    PSS_StateMachineIterator it(&GetStateMachineSet());

    // iterate through the original state machine collection and try to locate the same state machine
    for (PSS_StateMachine* pStateMachine = it.GetFirst(); pStateMachine;)
        // if found, merge them and return the merged machine
        if (pStateMachine != pFirstStateMachine && pStateMachine->IsLastObjectEqual(pFirstStateMachine))
        {
            // merge the two machines together
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
PSS_StateMachine* PSS_AutomationMachine::FindOriginalStateMachine(PSS_StateMachine* pStateMachineToLocate)
{
    PSS_StateMachineIterator it(&GetStateMachineSetConst());

    // iterate through the original state machine collection and try to locate the same state machine
    for (PSS_StateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext())
        if (pStateMachine->IsLastObjectEqual(pStateMachineToLocate))
            return pStateMachine;

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::MoveFinishedStateMachine(PSS_StateMachine* pFinishedStateMachine)
{
    // locate the first original state machine
    PSS_StateMachine* pStateMachineToMove = FindOriginalStateMachine(pFinishedStateMachine);

    if (!pStateMachineToMove)
        return false;

    PSS_StateMachineIterator it(&GetStateMachineSet());

    // iterate through state machines
    for (PSS_StateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext())
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
