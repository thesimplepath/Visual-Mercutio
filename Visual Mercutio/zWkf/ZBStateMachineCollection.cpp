// ZBStateMachineCollection.cpp: implementation of the ZBStateMachineCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBStateMachineCollection.h"

#include "ZBStateMachine.h"
#include "zModel\ProcGraphModelMdl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 17 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZBStateMachineCollection, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBStateMachineCollection::ZBStateMachineCollection( ZDProcessGraphModelMdl* pModel /*= NULL*/ )
	: m_pModel( pModel )
{
}

ZBStateMachineCollection::~ZBStateMachineCollection()
{
	// JMR-MODIF - Le 20 mars 2006 - Nettoyage des memory leaks, ajout du code de destruction de l'objet.
	RemoveAllObjects();
}

ZBStateMachineCollection::ZBStateMachineCollection( const ZBStateMachineCollection& src )
{
	*this = src;
}

ZBStateMachineCollection& ZBStateMachineCollection::operator=( const ZBStateMachineCollection& src )
{
	m_pModel = src.m_pModel;

	// Now, copy all state objects
	ZBStateMachineIterator i( &src.GetStateMachineSetConst() );

	for ( ZBStateMachine* pStateMachine = i.GetFirst(); pStateMachine; pStateMachine = i.GetNext() )
	{
		AddStateMachine( pStateMachine->Clone() );
	}

	return *this;
}

ZBStateMachineCollection* ZBStateMachineCollection::Clone() const
{
	return ( new ZBStateMachineCollection( *this ) );
}

void ZBStateMachineCollection::AssignModel( ZDProcessGraphModelMdl* pModel )
{
	// First, assigns the model
	m_pModel = pModel;

	// And then reassigns the model to all state machines
	AssignModelToStateMachines();
}

void ZBStateMachineCollection::AssignModelToStateMachines()
{
	ZBStateMachineIterator i( &m_Set );

	for ( ZBStateMachine* pStateMachine = i.GetFirst(); pStateMachine; pStateMachine = i.GetNext() )
	{
		pStateMachine->AssignModel( m_pModel );
	}
}

bool ZBStateMachineCollection::CopyCurrentStateObjects( const	ZBStateMachineCollection& src,
														bool	MergeObjectsFirst				/*= false*/ )
{
	// Now, copy all state objects
	ZBStateMachineIterator i( &src.GetStateMachineSetConst() );

	for ( ZBStateMachine* pStateMachine = i.GetFirst(); pStateMachine; pStateMachine = i.GetNext() )
	{
		ZBStateObject* pStateObj = NULL;

		if ( MergeObjectsFirst )
		{
			// First clone the state machine
			ZBStateMachine* pStateMachineClone = pStateMachine->Clone();
			ASSERT( pStateMachineClone );
			pStateMachineClone->MergeAllStates();

			if ( pStateMachineClone->GetCurrentStateObject() )
			{
				pStateObj = pStateMachineClone->GetCurrentStateObject()->Clone();
			}

			// Now the cloned state machine can be deleted
			delete pStateMachineClone;
		}
		else
		{
			if ( pStateMachine->GetCurrentStateObject() )
			{
				pStateObj = pStateMachine->GetCurrentStateObject()->Clone();
			}
		}

		// If no state object, error
		if ( !pStateObj )
		{
			return false;
		}

		// Now create a new state machine
		if ( CreateNewStateMachine( pStateObj ) == -1 )
		{
			return false;
		}
	}

	return true;
}

void ZBStateMachineCollection::RemoveAllObjects()
{
	ZBStateMachineIterator i( &m_Set );

	for ( ZBStateMachine* pStateMachine = i.GetFirst(); pStateMachine; pStateMachine = i.GetNext() )
	{
		delete pStateMachine;
	}

	// Then remove all elements
	m_Set.RemoveAll();
}

int ZBStateMachineCollection::AddStateMachine( ZBStateMachine* pStateMachine )
{
	if ( pStateMachine )
	{
		m_Set.Add( pStateMachine );

		// Returns the index
		return GetStateMachineCount() - 1;
	}

	return -1;
};

StateMachineHandle ZBStateMachineCollection::CreateNewStateMachine( ZBSymbol*					pSymbol,
																	ZBLinkSymbol*				pLinkSymbol,
																	ZBStateLink::LinkDirection	Direction	/*= ZBStateLink::LinkDirection::UnknownDirection*/ )
{
	ZBStateMachine* pNewStateMachine = new ZBStateMachine( m_pModel );
	ASSERT( pNewStateMachine );

	pNewStateMachine->PushSymbol( pSymbol, pLinkSymbol, Direction );
	return AddStateMachine( pNewStateMachine );
}

StateMachineHandle ZBStateMachineCollection::CreateNewStateMachine( ZBStateObject* pStateObj )
{
	ZBStateMachine* pNewStateMachine = new ZBStateMachine( m_pModel );
	ASSERT( pNewStateMachine );

	pNewStateMachine->PushStateObject( pStateObj );
	return AddStateMachine( pNewStateMachine );
}

bool ZBStateMachineCollection::DeleteStateMachine( StateMachineHandle hStateMachine )
{
	if ( hStateMachine < (int)GetStateMachineCount() )
	{
		ZBStateMachine* pStateMachine = m_Set.GetAt( hStateMachine );

		if ( pStateMachine )
		{
			delete pStateMachine;
		}

		m_Set.RemoveAt( hStateMachine );

		return true;
	}

	return false;
}

ZBSymbol* ZBStateMachineCollection::GetCurrentStateMachineSymbol( StateMachineHandle hStateMachine )
{
	if ( hStateMachine < (int)GetStateMachineCount() )
	{
		ZBStateMachine* pStateMachine = m_Set.GetAt( hStateMachine );
		return ( pStateMachine != NULL ) ? pStateMachine->GetCurrentSymbol() : NULL;
	}

	return NULL;
}

ZBStateObject* ZBStateMachineCollection::GetCurrentStateMachineObject( StateMachineHandle hStateMachine )
{
	if ( hStateMachine < (int)GetStateMachineCount() )
	{
		ZBStateMachine* pStateMachine = m_Set.GetAt( hStateMachine );
		return ( pStateMachine != NULL ) ? pStateMachine->GetCurrentStateObject() : NULL;
	}

	return NULL;
}

bool ZBStateMachineCollection::PushSymbol( StateMachineHandle			hStateMachine,
										   ZBSymbol*					pSymbol,
										   ZBLinkSymbol*				pLinkSymbol,
										   ZBStateLink::LinkDirection	Direction		/*= ZBStateLink::LinkDirection::UnknownDirection*/ )
{
	ZBStateMachine* pStateMachine = GetStateMachine( hStateMachine );

	if ( pStateMachine )
	{
		pStateMachine->PushSymbol( pSymbol, pLinkSymbol, Direction );
		return true;
	}

	return false;
}

bool ZBStateMachineCollection::PushStateObject( StateMachineHandle hStateMachine, ZBStateObject* pStateObj )
{
	ZBStateMachine* pStateMachine = GetStateMachine( hStateMachine );

	if ( pStateMachine )
	{
		pStateMachine->PushStateObject( pStateObj );
		return true;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
// ZBStateMachineCollection diagnostics
#ifdef _DEBUG
void ZBStateMachineCollection::AssertValid() const
{
	CObject::AssertValid();
}

void ZBStateMachineCollection::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBStateMachineCollection serialization

void ZBStateMachineCollection::Serialize ( CArchive& ar )
{
	if ( ar.IsStoring() )
	{
		// Write the elements
		// Serialize the size of the set
		ar << m_Set.GetSize();

		ZBStateMachineIterator i( &m_Set );

		for ( ZBStateMachine* pStateMachine = i.GetFirst(); pStateMachine; pStateMachine = i.GetNext() )
		{
			ar << pStateMachine;
		}
	}
	else
	{
		// Read the elements
		RemoveAllObjects();

		// Read the size of the set
		int Count;
		ar >> Count;

		ZBStateMachine* pStateMachine;

		for ( int i = 0; i < Count; ++i )
		{
			ar >> pStateMachine;
			AddStateMachine( pStateMachine );
		}

		if ( m_pModel )
		{
			AssignModelToStateMachines();
		}
	}
}
