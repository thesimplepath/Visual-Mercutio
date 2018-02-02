// ZBStateMachine.cpp: implementation of the ZBStateMachine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBStateMachine.h"

#include "ZBStateObject.h"
#include "zBaseSym\ZIBasicSymbol.h"
#include "zModel\ProcGraphModelMdl.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(ZBStateMachine, CObject, def_Version)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBStateMachine::ZBStateMachine(ZDProcessGraphModelMdl* pModel /*= NULL*/)
: m_pModel(pModel)
{

}

ZBStateMachine::~ZBStateMachine()
{
	RemoveAllObjects();

}

ZBStateMachine::ZBStateMachine(const ZBStateMachine& src)
{
	*this = src;
}

ZBStateMachine& ZBStateMachine::operator=(const ZBStateMachine& src)
{
	m_pModel = src.m_pModel;
	// Now, copy all state objects
	ZBStateObjectIterator i(&src.GetStateObjectSetConst());
	for (ZBStateObject* pStateObj = i.GetFirst(); pStateObj; pStateObj = i.GetNext())
	{
		AddStateObject( pStateObj->Clone() );
	}

	return *this;
}

ZBStateMachine* ZBStateMachine::Clone() const
{
	return (new ZBStateMachine(*this));
}

bool ZBStateMachine::IsEqual( ZBStateMachine* pRight )
{
	// Test if we have the same number of objects
	if (!pRight ||
		(GetStateObjectCount() != pRight->GetStateObjectCount()))
		return false;

	int Counter = GetStateObjectCount();
	for (int i = 0; i < Counter; ++i)
	{
		ZBStateObject* pStateLeft = GetStateObjectAt( i );
		ZBStateObject* pStateRight = pRight->GetStateObjectAt( i );
		// test if one of both objects is null, not equal
		if (!pStateLeft || !pStateRight)
			return false;
		// test if left is not equal to right
		if (!pStateLeft->IsEqual( pStateRight ))
			return false;
	}
	// if all objects are equal, then the state machines are equal
	return true;
}

///////////////////////////////////////////////////////////////////////////
// Stack functions
void ZBStateMachine::PushSymbol( ZBSymbol* pSymbol, ZBLinkSymbol* pLinkSymbol, ZBStateLink::LinkDirection Direction )
{
	ZBStateObject* pStateObj = new ZBStateObject( pSymbol, pLinkSymbol, Direction, m_pModel );
	AddStateObject( pStateObj );
}

void ZBStateMachine::PushSymbol( ZBSymbol* pSymbol, ZBStateLink* pStateLink )
{
	ZBStateObject* pStateObj = new ZBStateObject( pSymbol, pStateLink, m_pModel );
	AddStateObject( pStateObj );
}

void ZBStateMachine::PushStateObject( ZBStateObject* pStateObj )
{
	if (pStateObj)
		AddStateObject( pStateObj );
}


ZBStateObject* ZBStateMachine::_PopStateObject( bool RemoveFromStack, size_t Level )
{
	ZBStateObject* pStateObj = NULL;
	// Increment to one, because 0 means the current object
	++Level;
	if (GetStateObjectCount() >= Level)
	{
		// Retreive the state object
		pStateObj = m_Set.GetAt( GetStateObjectCount()-Level );
		// Don't delete pStateObj otherwise the returned object will be invalid
		// If necessary to remove from stack,
		// remove the element from the stack
		if (RemoveFromStack)
			m_Set.RemoveAt( GetStateObjectCount()-Level );
	}
	return pStateObj;
}

void ZBStateMachine::RemoveAllObjects()
{
	ZBStateObjectIterator i(&m_Set);
	for (ZBStateObject* pStateObj = i.GetFirst(); pStateObj; pStateObj = i.GetNext())
	{
		delete pStateObj;
	}
	// Then remove all elements
	m_Set.RemoveAll();

}

int ZBStateMachine::AddStateObject( ZBStateObject* pStateObj )
{
	if (pStateObj)
	{
		m_Set.Add( pStateObj );
		// Returns the index
		return GetStateObjectCount() - 1;
	}
	return -1;
}

void ZBStateMachine::RemoveStateObjectAt( size_t Index, bool DeleteObject /*= true*/ )
{
	ZBStateObject* pStateObject = GetStateObjectAt( Index );
	if (pStateObject)
	{
		m_Set.RemoveAt( Index );
		if (DeleteObject)
			delete pStateObject;
	}
}

/////////////////////////////////////////////////////////////////////////////
// Model assignement
void ZBStateMachine::AssignModel( ZDProcessGraphModelMdl* pModel )
{
	// First, assigns the model
	m_pModel = pModel;
	// And then reassigns the model to all state machines
	AssignModelToStateObjects();
}

void ZBStateMachine::AssignModelToStateObjects()
{
	ZBStateObjectIterator i(&m_Set);
	for (ZBStateObject* pStateObj = i.GetFirst(); pStateObj; pStateObj = i.GetNext())
	{
		pStateObj->AssignModel( m_pModel );
	}
}

/////////////////////////////////////////////////////////////////////////////
// Merge functions
bool ZBStateMachine::MergeAllStates()
{
	bool bError = false;
	size_t Count = GetStateObjectCount();
	for (int i = Count-1; i >= 0; --i)
	{
		ZBStateObject* pStateObject = GetStateObjectAt( i );
		int iSimilar = FindSimilar( pStateObject );
		if (iSimilar != -1)
		{
			if (!MergeStates( i, iSimilar ))
				bError = true;
		}
	}
	return (bError == true) ? false : true;
}

bool ZBStateMachine::Merge( ZBStateMachine* pRight )
{
	// First, merge the states of both state machines
	if (!MergeAllStates())
		return false;
	if (!pRight || !pRight->MergeAllStates())
		return false;
	// Merging two state machines means merging only the last state object
	// That means also, the stack has no more consistency
	ZBStateObject* pStateLeft = GetCurrentStateObject();
	ZBStateObject* pStateRight = pRight->GetCurrentStateObject();
	if (!pStateLeft || !pStateRight)
		return false;
	if (!pStateLeft->Merge( pStateRight ))
		return false;

	return true;
}

bool ZBStateMachine::Merge( ZBStateMachineSet& SetRight )
{
	// First, merge the states of both state machines
	if (!MergeAllStates())
		return false;
	ZBStateMachineIterator i(&SetRight);
	for (ZBStateMachine* pStateMachine = i.GetFirst(); pStateMachine; pStateMachine = i.GetNext())
	{
		if (!Merge( pStateMachine ))
			return false;
	}
	return true;
}

bool ZBStateMachine::MergeStates( int iLeft, int iRight, bool DeleteRight /*= true*/ )
{
	ZBStateObject* pLeft = GetStateObjectAt( iLeft );
	ZBStateObject* pRight = GetStateObjectAt( iRight );
	if (!pLeft || !pRight)
		return false;
	if (!pLeft->Merge( pRight ))
		return false;

	if (DeleteRight)
	{
		RemoveStateObjectAt( iRight, true );
	}
	return true;
}


int ZBStateMachine::FindSimilar( ZBStateObject* pStateObjectToFind )
{
	size_t Count = GetStateObjectCount();
	for (size_t i = 0; i < Count; ++i)
	{
		ZBStateObject* pStateObj = GetStateObjectAt( i );
		if ((pStateObj != pStateObjectToFind) &&	// Not compared to itself
			pStateObjectToFind->IsEqual( pStateObj )) // Is Equal in terms of reference
			return i;
	}
	return -1;
}

/////////////////////////////////////////////////////////////////////////////
// ZBStateMachine serialization

void ZBStateMachine::Serialize (CArchive& ar)
{
	if (ar.IsStoring())
	{	// Write the elements

		// Serialize the size of the set
		ar << m_Set.GetSize();
		ZBStateObjectIterator i(&m_Set);
		for (ZBStateObject* pStateObj = i.GetFirst(); pStateObj; pStateObj = i.GetNext())
		{
			ar << pStateObj;
		}
	}
	else
	{	// Read the elements

		// Remove all objects from the set
		RemoveAllObjects();
		// Read the size of the set
		int Count;
		ar >> Count;
		ZBStateObject* pStateObj;
		for (int i = 0; i < Count; ++i)
		{
			ar >> pStateObj;
			AddStateObject( pStateObj );
		}
		if (m_pModel)
			AssignModelToStateObjects();
	}
}


/////////////////////////////////////////////////////////////////////////////
// ZBStateMachine diagnostics
#ifdef _DEBUG
void ZBStateMachine::AssertValid() const
{
	CObject::AssertValid();
}

void ZBStateMachine::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

