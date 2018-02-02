// ZISubject.cpp: implementation of the ZISubject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZISubject.h"
#include "ZIObserver.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 27 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (en commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZISubject::ZISubject()
{
}

ZISubject::~ZISubject()
{
	DetachAllObservers();
}

void ZISubject::AttachObserver( ZIObserver* pObserver )
{
	bool Found = false;

	for ( register int i = 0; i < m_ObserverSet.GetSize(); ++i )
	{
		if ( (ZIObserver*)m_ObserverSet.GetAt( i ) == pObserver )
		{
			Found = true;
			break;
		}
	}

	// Only if not already in
	if ( !Found )
	{
		m_ObserverSet.Add( (CObject*)pObserver );
	}
}

void ZISubject::DetachObserver( ZIObserver* pObserver )
{
	for ( register int i = 0; i < m_ObserverSet.GetSize(); ++i )
	{
		if ( (ZIObserver*)m_ObserverSet.GetAt( i ) == pObserver )
		{
			m_ObserverSet.RemoveAt( i );
		}
	}
}

void ZISubject::DetachAllObservers()
{
	for ( register int i = 0; i < m_ObserverSet.GetSize(); ++i )
	{
		m_ObserverSet.RemoveAt( i );
	}
}

void ZISubject::NotifyAllObservers( ZIObserverMsg* pMsg )
{
	for ( register int i = 0; i < m_ObserverSet.GetSize(); ++i )
	{
		( (ZIObserver*)m_ObserverSet.GetAt( i ) )->OnUpdate( this, pMsg );
	}
}
