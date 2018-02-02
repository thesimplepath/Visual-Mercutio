// ZBStateObject.cpp: implementation of the ZBStateObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBStateObject.h"

#include "zModel\ProcGraphModelMdl.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 1er février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZBStateObject, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBStateObject::ZBStateObject( ZBSymbol*						pSymbol		/*= NULL*/, 
							  ZBLinkSymbol*					pLinkSymbol	/*= NULL*/, 
							  ZBStateLink::LinkDirection	Direction	/*= ZBStateLink::EnteringUp*/, 
							  ZDProcessGraphModelMdl*		pModel		/*= NULL*/)
	: m_pModel	( pModel ),
	  m_pSymbol	( pSymbol )
{
	if ( pSymbol && pLinkSymbol )
	{
		AddLink( pLinkSymbol, Direction );
	}
}

ZBStateObject::ZBStateObject( ZBSymbol*					pSymbol,
							  ZBStateLink*				pStateLink,
							  ZDProcessGraphModelMdl*	pModel		/*= NULL*/ )
	: m_pModel	( pModel ),
	  m_pSymbol	( pSymbol )
{
	if ( pStateLink )
	{
		AddStateLink( pStateLink );
	}
}

ZBStateObject::~ZBStateObject()
{
	RemoveAllLinks();
}

ZBStateObject::ZBStateObject( const ZBStateObject& src )
{
	*this = src;
}

ZBStateObject& ZBStateObject::operator=( const ZBStateObject& src )
{
	m_pSymbol	= src.m_pSymbol;
	m_pModel	= src.m_pModel;

	// Now, copy all state link objects
	ZBStateLinksIterator i( &src.GetLinkSetConst() );

	for ( ZBStateLink* pStateLink = i.GetFirst(); pStateLink; pStateLink = i.GetNext() )
	{
		AddStateLink( pStateLink->Clone() );
	}

	return *this;
}

ZBStateObject* ZBStateObject::Clone() const
{
	return ( new ZBStateObject( *this ) );
}

///////////////////////////////////////////////////////////////////////////
// Stack functions

void ZBStateObject::AddLink( ZBLinkSymbol* pLinkSymbol, ZBStateLink::LinkDirection Direction )
{
	ZBStateLink* pStateLink = new ZBStateLink( pLinkSymbol, Direction, m_pModel );
	AddStateLink( pStateLink );
}

bool ZBStateObject::RemoveLink( ZBLinkSymbol* pLinkSymbol )
{
	ZBStateLinksIterator i( &m_Set );

	for ( ZBStateLink* pStateLink = i.GetFirst(); pStateLink; pStateLink = i.GetNext() )
	{
		if ( pStateLink->GetpLinkSymbol() == pLinkSymbol )
		{
			i.Remove();
			delete pStateLink;

			return true;
		}
	}

	return false;
}

bool ZBStateObject::RemoveLink( int ReferenceNumber )
{
	ZBStateLinksIterator i( &m_Set );

	for ( ZBStateLink* pStateLink = i.GetFirst(); pStateLink; pStateLink = i.GetNext() )
	{
		if ( pStateLink->GetpLinkSymbol() &&
			 pStateLink->GetpLinkSymbol()->GetSymbolReferenceNumber() == ReferenceNumber )
		{
			i.Remove();
			delete pStateLink;

			return true;
		}
	}

	return false;
}

void ZBStateObject::RemoveAllLinks()
{
	ZBStateLinksIterator i( &m_Set );

	for ( ZBStateLink* pStateLink = i.GetFirst(); pStateLink; pStateLink = i.GetNext() )
	{
		delete pStateLink;
	}

	// Then remove all elements
	m_Set.RemoveAll();
}

int ZBStateObject::AddStateLink( ZBStateLink* pStateLink )
{
	if ( pStateLink )
	{
		m_Set.Add( pStateLink );

		// Returns the index
		return GetStateLinkCount() - 1;
	}

	return -1;
}

/////////////////////////////////////////////////////////////////////////////
// Model assignement
void ZBStateObject::AssignModel( ZDProcessGraphModelMdl* pModel )
{
	// First, assigns the model
	m_pModel = pModel;

	// And then reassigns the model to all state links
	AssignModelToStateLinks();
}

void ZBStateObject::AssignModelToStateLinks()
{
	ZBStateLinksIterator i( &m_Set );

	for ( ZBStateLink* pStateLink = i.GetFirst(); pStateLink; pStateLink = i.GetNext() )
	{
		pStateLink->AssignModel( m_pModel );
	}
}

// Compare the reference number of both objects
bool ZBStateObject::IsEqual( ZBStateObject* pRight )
{
	return ( pRight					&&
			 pRight->GetpSymbol()	&&
			 GetpSymbol()			&&
			 pRight->GetpSymbol()->GetSymbolReferenceNumber() == GetpSymbol()->GetSymbolReferenceNumber()) ?
			 true : false;
}


bool ZBStateObject::Exist( ZBLinkSymbol& LinkSymbol )
{
	// Run through all link from the pRight object
	ZBStateLinksIterator i( &GetLinkSet() );

	for ( ZBStateLink* pStateLink = i.GetFirst(); pStateLink; pStateLink = i.GetNext() )
	{
		if ( pStateLink->IsEqual( LinkSymbol ) )
		{
			return true;
		}
	}

	return false;
}

// All edges must exist in the state object. Otherwise false is returned
size_t ZBStateObject::EdgesExist( CODEdgeArray& Edges )
{
	size_t Counter		= 0;
	size_t ElementCount = Edges.GetSize();

	for ( size_t nEdgeIdx = 0; nEdgeIdx < ElementCount; ++nEdgeIdx )
	{
		IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );

		// Check if a ZBLinkSymbol
		if ( !static_cast<CODLinkComponent*>( pIEdge ) ||
			 !ISA(static_cast<CODLinkComponent*>( pIEdge ), ZBLinkSymbol ) )
		{
			continue;
		}

		ZBLinkSymbol* pLink = static_cast<ZBLinkSymbol*>( pIEdge );

		if ( !pLink )
		{
			continue;
		}

		if ( Exist( *pLink ) )
		{
			++Counter;
		}
	}

	return Counter;
}

/////////////////////////////////////////////////////////////////////////////
// Merge functions
bool ZBStateObject::Merge( ZBStateObject* pRight )
{
	if ( !pRight )
	{
		return false;
	}

	// Run through all link from the pRight object
	ZBStateLinksIterator i( &pRight->GetLinkSet() );

	for ( ZBStateLink* pStateLink = i.GetFirst(); pStateLink; pStateLink = i.GetNext() )
	{
		AddStateLink( pStateLink->Clone() );
	}

	return true;
}

bool ZBStateObject::Merge( ZBStateObjectSet& SetRight )
{
	// Run through all state objects, and merge their links
	ZBStateObjectIterator i( &SetRight );

	for ( ZBStateObject* pStateObj = i.GetFirst(); pStateObj; pStateObj = i.GetNext() )
	{
		if ( !Merge( pStateObj ) )
		{
			return false;
		}
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
// ZBStateObject diagnostics
#ifdef _DEBUG
void ZBStateObject::AssertValid() const
{
	CObject::AssertValid();
}

void ZBStateObject::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBStateObject serialization

void ZBStateObject::Serialize ( CArchive& ar )
{
	if ( ar.IsStoring() )
	{
		// Write the elements
		// Serialize the current object reference number
		CString EmptyString;
		EmptyString.Empty();

		if ( m_pSymbol )
		{
			ar << m_pSymbol->GetSymbolReferenceNumberStr();
		}
		else
		{
			ar << EmptyString;
		}

		// Serialize the size of the set
		ar << m_Set.GetSize();

		// Serialize all objects
		ZBStateLinksIterator i( &m_Set );

		for ( ZBStateLink* pStateLink = i.GetFirst(); pStateLink; pStateLink = i.GetNext() )
		{
			ar << pStateLink;
		}
	}
	else
	{
		// Read the elements
		// Retreive the object reference number
		CString ReferenceNumberStr;
		ar >> ReferenceNumberStr;

		// Initialize current object to null
		m_pSymbol = NULL;

		if ( !ReferenceNumberStr.IsEmpty() && m_pModel != NULL )
		{
			// Find back the right symbol pointer
			int RefNumber = atoi( ReferenceNumberStr );

			CODComponentSet* pSet = m_pModel->FindSymbolByRefNumber( RefNumber, true );

			if ( pSet && pSet->GetSize() > 0 && ISA( pSet->GetAt( 0 ), ZBSymbol ) )
			{
				m_pSymbol = dynamic_cast<ZBSymbol*>( pSet->GetAt( 0 ) );
			}
		}

		// Remove all objects from the set
		RemoveAllLinks();

		// Read the size of the set
		int Count;
		ar >> Count;

		ZBStateLink* pStateLink;

		for ( int i = 0; i < Count; ++i )
		{
			ar >> pStateLink;
			AddStateLink( pStateLink );
		}

		if ( m_pModel )
		{
			AssignModelToStateLinks();
		}
	}
}
