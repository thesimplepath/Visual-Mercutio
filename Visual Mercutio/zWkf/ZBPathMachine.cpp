// ZBPathMachine.cpp: implementation of the ZBPathMachine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBPathMachine.h"

#include "ZBMainPathRunnerThread.h"
#include "ZBStateMachine.h"

#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

// Include files for log
#include "zBaseLib\ZILog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBPathMachine::ZBPathMachine(ZDProcessGraphModelMdl* pModel /*= NULL*/, 
							 ZBSymbol* pSymbol /*= NULL*/,
							 ZILog* pLog /*= NULL*/,
							 int MaximumLoop /*= -1*/, 
							 int MaximumPaused /*= -1*/, 
							 int MaximumWaitingForOtherLinks /*= -1*/)

: m_pModel(pModel), 
  m_pLog(pLog), 
  m_pSymbol(pSymbol),
  m_MaximumLoop(MaximumLoop), 
  m_MaximumPaused(MaximumPaused), 
  m_MaximumWaitingForOtherLinks(MaximumWaitingForOtherLinks),
  m_pMainThread(NULL)
{
	m_StateMachineCollection.AssignModel( m_pModel );
}

ZBPathMachine::~ZBPathMachine()
{

}


bool ZBPathMachine::Start( int ElapseTime /*= -1*/ )
{
	if (!m_pModel)
		return false;

	
	m_pMainThread = new ZBMainPathRunnerThread(this, ElapseTime, m_pLog);
	return (m_pMainThread->StartThread()) ? true : false;
}

bool ZBPathMachine::Stop()
{
	if (m_pMainThread)
		m_pMainThread->Stop();
	return true;
}

bool ZBPathMachine::Pause()
{
	if (!m_pMainThread)
		return false;

//	DWORD retValue = m_pMainThread->SuspendThread();
	// Check for errors
//	if (retValue == 0xFFFFFFFF)
//		return false;
	return true;
}

bool ZBPathMachine::Resume()
{
	if (!m_pMainThread)
		return false;
//	DWORD retValue = m_pMainThread->ResumeThread();
	// Check for errors
//	if (retValue == 0xFFFFFFFF)
//		return false;
	return true;
}


bool ZBPathMachine::MergeAllStateObjects( ZBStateMachineCollection& Collection )
{
	// First copy our collection to the collection passed has parameter
	Collection.CopyCurrentStateObjects( m_StateMachineCollection, true );

	// Run through all elements of the collection
	for (int i = 0; i < (int)Collection.GetStateMachineCount(); ++i)
	{
		ZBStateMachine* pSrcStateMachine = Collection.GetStateMachine( i );
		ASSERT( pSrcStateMachine );
		// Now, from the next element till then end of the collection,
		// Compare if the last element of the state machine is equal
		for (int j=i+1; j < (int)Collection.GetStateMachineCount(); ++j)
		{
			ZBStateMachine* pDstStateMachine = Collection.GetStateMachine( j );
			ASSERT( pDstStateMachine );
			// Try to locate if we have the same state machine object id
			if (pSrcStateMachine->IsLastObjectEqual( pDstStateMachine ))
			{
				if (!MergeStateMachine( i, j, Collection, true ))
					return false;
				--j;
			}
		}
	}
	return true;
}


bool ZBPathMachine::MergeStateMachine( size_t i, size_t j, ZBStateMachineCollection& Collection, bool DeleteDestination /*= false*/ )
{
	// Retreive and merge the state machine together
	ZBStateMachine* pSrcStateMachine = Collection.GetStateMachine( i );
	ASSERT( pSrcStateMachine );

	ZBStateMachine* pDstStateMachine = Collection.GetStateMachine( j );
	ASSERT( pDstStateMachine );
	if (!pSrcStateMachine->Merge( pDstStateMachine ))
		return false;

	if (DeleteDestination)
		Collection.DeleteStateMachine( j );

	return true;
}

ZBStateMachine* ZBPathMachine::MergeSourceStateMachines( ZBStateMachine* pStateMachineToMerge )
{
	// Run through the original state machine collection
	// and try to locate the same state machine
	// When found, merge them and return the merged machine

	// First, locate the first original state machine
	ZBStateMachine* pFirstStateMachine = ZBPathMachine::FindOriginalStateMachine( pStateMachineToMerge  );
	if (!pFirstStateMachine)
		return NULL;
	// Merge all states
	pFirstStateMachine->MergeAllStates();

	ZBStateMachineIterator i(&GetStateMachineSet());
	for (ZBStateMachine* pStateMachine = i.GetFirst(); pStateMachine; )
	{
		if (pStateMachine != pFirstStateMachine &&
			pStateMachine->IsLastObjectEqual( pFirstStateMachine ))
		{
			// If equal, then merge the two objects together
			if (!pFirstStateMachine->Merge( pStateMachine ))
				return NULL;
			// Then delete the second state machine
			delete pStateMachine;
			// Then remove it from the set
			i.Remove();
			// Get the current element once removed
			pStateMachine = i.Get();
		}
		else
			// Get the next element
			pStateMachine = i.GetNext();
	}
	return pFirstStateMachine;
}

ZBStateMachine* ZBPathMachine::FindOriginalStateMachine( ZBStateMachine* pStateMachineToLocate )
{
	// Run through the original state machine collection
	// and try to locate the same state machine
	// do the work
	ZBStateMachineIterator i(&GetStateMachineSetConst());
	for (ZBStateMachine* pStateMachine = i.GetFirst(); pStateMachine; pStateMachine = i.GetNext())
	{
		if (pStateMachine->IsLastObjectEqual( pStateMachineToLocate ))
			return pStateMachine;
	}
	return NULL;
}

bool ZBPathMachine::MoveFinishedStateMachine( ZBStateMachine* pFinishedStateMachine )
{
	// First, locate the first original state machine
	ZBStateMachine* pStateMachineToMove = ZBPathMachine::FindOriginalStateMachine( pFinishedStateMachine );
	if (!pStateMachineToMove)
		return false;

	ZBStateMachineIterator i(&GetStateMachineSet());
	for (ZBStateMachine* pStateMachine = i.GetFirst(); pStateMachine; pStateMachine = i.GetNext())
	{
		if (pStateMachine == pStateMachineToMove)
		{
			// Add the state machine to the finished state machine collection
			if (AddFinishedStateMachine( pStateMachine ) == -1)
				return false;
			// Then remove it from the set
			i.Remove();
			break;
		}
	}
	return true;
}

size_t ZBPathMachine::CopyNodeArrayToSymbolSet( CODNodeArray& Nodes, ZBSymbolSet& SymbolSet )
{
	size_t ElementCount = Nodes.GetSize();
	for (size_t nNodeIdx = 0; nNodeIdx < ElementCount; ++nNodeIdx)
	{
		IODNode* pINode = Nodes.GetAt(nNodeIdx);
		// Check if a ZBSymbol
		if (!static_cast<CODSymbolComponent*>(pINode) ||
			!ISA(static_cast<CODSymbolComponent*>(pINode),ZBSymbol))
			continue;
		ZBSymbol* pSymbol = static_cast<ZBSymbol*>(pINode);

		if (!pSymbol)
			continue;
		// Copy the symbol pointer to the symbol set
		SymbolSet.Add( pSymbol );
	}
	return SymbolSet.GetSize();
}

size_t ZBPathMachine::CopyEdgeArrayToStateLinksSet( CODEdgeArray& Edges, ZBStateLink::LinkDirection Direction, ZBStateLinksSet& StateLinkSet ) 
{
	size_t ElementCount = Edges.GetSize();
	for (size_t nEdgeIdx = 0; nEdgeIdx < ElementCount; ++nEdgeIdx)
	{
		IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
		// Check if a ZBLinkSymbol
		if (!static_cast<CODLinkComponent*>(pIEdge) ||
			!ISA(static_cast<CODLinkComponent*>(pIEdge),ZBLinkSymbol))
			continue;
		ZBLinkSymbol* pLink = static_cast<ZBLinkSymbol*>(pIEdge);

		if (!pLink)
			continue;
		ZBStateLink* pStateLink = new ZBStateLink( pLink, Direction, GetModel() );
		StateLinkSet.Add( pStateLink );
	}
	return StateLinkSet.GetSize();
}



