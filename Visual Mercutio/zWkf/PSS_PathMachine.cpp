/****************************************************************************
 * ==> PSS_PathMachine -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a path machine                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PathMachine.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\ZBSymbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "PSS_MainPathRunnerThread.h"
#include "PSS_StateMachine.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_PathMachine
//---------------------------------------------------------------------------
PSS_PathMachine::PSS_PathMachine(PSS_ProcessGraphModelMdl* pModel,
                                 ZBSymbol*                 pSymbol,
                                 PSS_Log*                  pLog,
                                 int                       maxLoop,
                                 int                       maxPaused,
                                 int                       maxWaitingForOtherLinks) :
    m_pModel(pModel),
    m_pMainThread(NULL),
    m_pSymbol(pSymbol),
    m_pLog(pLog),
    m_ErrorCounter(0),
    m_WarningCounter(0),
    m_MaxLoop(maxLoop),
    m_MaxPaused(maxPaused),
    m_MaxWaitingForOtherLinks(maxWaitingForOtherLinks),
    m_IsLogging(false)
{
    m_StateMachineCollection.AssignModel(m_pModel);
}
//---------------------------------------------------------------------------
PSS_PathMachine::~PSS_PathMachine()
{}
//---------------------------------------------------------------------------
bool PSS_PathMachine::Start(int timeout)
{
    if (!m_pModel)
        return false;

    m_pMainThread = new PSS_MainPathRunnerThread(this, timeout, m_pLog);
    return (m_pMainThread->StartThread()) ? true : false;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::Stop()
{
    if (m_pMainThread)
        m_pMainThread->Stop();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::Pause()
{
    if (!m_pMainThread)
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::Resume()
{
    if (!m_pMainThread)
        return false;

    return true;
}
//---------------------------------------------------------------------------
PSS_PathMachine::IEPathMoveStatus PSS_PathMachine::RequestMoveForward(PSS_StateObject*   pState,
                                                                      PSS_StateMachine*  pStateMachine,
                                                                      PSS_SymbolSet&     symbolSet,
                                                                      PSS_StateLinksSet& stateLinkSet,
                                                                      PSS_Log*           pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return IE_PS_Error;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnStart(PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
};
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnStop(PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnPause(PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnResume(PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnObjectIsFinished(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnObjectIsPaused(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnObjectIsWaitingForOtherLinks(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnBeforeRequestMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnNextSymbolAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnBeforeMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnBeforeMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnAfterMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnObjectError(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnReachMaxLoopCounter(PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
};
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnReachMaxWaitingForOtherLinksCounter(PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
};
//---------------------------------------------------------------------------
bool PSS_PathMachine::OnReachMaxInPauseCounter(PSS_Log* pLog)
{
    // do nothing in the base class, must be implemented in the derived class
    return true;
};
//---------------------------------------------------------------------------
std::size_t PSS_PathMachine::CopyNodeArrayToSymbolSet(CODNodeArray& nodes, PSS_SymbolSet& symbolSet)
{
    const std::size_t elementCount = nodes.GetSize();

    for (std::size_t nodeIndex = 0; nodeIndex < elementCount; ++nodeIndex)
    {
        IODNode*  pINode  = nodes.GetAt(nodeIndex);
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pINode);

        if (!pSymbol)
            continue;

        // add the symbol to the symbol set
        symbolSet.Add(pSymbol);
    }

    return symbolSet.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_PathMachine::CopyEdgeArrayToStateLinksSet(CODEdgeArray&                  edges,
                                                          PSS_StateLink::IELinkDirection direction,
                                                          PSS_StateLinksSet&             stateLinkSet)
{
    const std::size_t elementCount = edges.GetSize();

    for (std::size_t edgeIndex = 0; edgeIndex < elementCount; ++edgeIndex)
    {
        IODEdge*        pIEdge = edges.GetAt(edgeIndex);
        PSS_LinkSymbol* pLink  = static_cast<PSS_LinkSymbol*>(pIEdge);

        if (!pLink)
            continue;

        // add the state link to the state link set
        PSS_StateLink* pStateLink = new PSS_StateLink(pLink, direction, GetModel());
        stateLinkSet.Add(pStateLink);
    }

    return stateLinkSet.GetSize();
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::MergeAllStateObjects(PSS_StateMachineCollection& collection)
{
    // copy our collection to the collection passed has parameter
    collection.CopyCurrentStateObjects( m_StateMachineCollection, true );

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
bool PSS_PathMachine::MergeStateMachine(std::size_t                 srcIndex,
                                        std::size_t                 dstIndex,
                                        PSS_StateMachineCollection& collection,
                                        bool                        deleteDestination)
{
    // get and merge the state machines together
    PSS_StateMachine* pSrcStateMachine = collection.GetStateMachine(srcIndex);
    ASSERT(pSrcStateMachine);

    PSS_StateMachine* pDstStateMachine = collection.GetStateMachine(dstIndex);
    ASSERT(pDstStateMachine);

    if (!pSrcStateMachine->Merge(pDstStateMachine))
        return false;

    if (deleteDestination)
        collection.DeleteStateMachine(dstIndex);

    return true;
}
//---------------------------------------------------------------------------
PSS_StateMachine* PSS_PathMachine::MergeSourceStateMachines(PSS_StateMachine* pStateMachineToMerge)
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

            // Get the current element once removed
            pStateMachine = it.Get();
        }
        else
            // get the next element
            pStateMachine = it.GetNext();

    return pFirstStateMachine;
}
//---------------------------------------------------------------------------
PSS_StateMachine* PSS_PathMachine::FindOriginalStateMachine(PSS_StateMachine* pStateMachineToLocate)
{
    PSS_StateMachineIterator it(&GetStateMachineSetConst());

    // iterate through the original state machine collection and try to locate the same state machine
    for (PSS_StateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext())
        if (pStateMachine->IsLastObjectEqual(pStateMachineToLocate))
            return pStateMachine;

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::MoveFinishedStateMachine(PSS_StateMachine* pFinishedStateMachine)
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
            if (AddFinishedStateMachine( pStateMachine ) == -1)
                return false;

            // remove it from the set
            it.Remove();
            break;
        }

    return true;
}
//---------------------------------------------------------------------------
