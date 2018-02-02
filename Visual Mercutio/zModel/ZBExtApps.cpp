/////////////////////////////////////////////////////////////////////////////
//@doc ZBExtApps
//@module ZBExtApps.cpp | Implementation of the <c ZBExtApps> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 07/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBExtApps.h"

#include "ZBExtAppProp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 13 octobre - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// constant definition
const int LastExtAppIDProperties = ZS_BP_PROP_EXTAPP + 39;

IMPLEMENT_SERIAL( ZBExtApps, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBExtApps::ZBExtApps( CODSymbolComponent* pParent /*= NULL*/ )
	: m_pParent( pParent )
{
}

ZBExtApps::~ZBExtApps()
{
	RemoveAllExtApps();
}

ZBExtApps::ZBExtApps( const ZBExtApps& src )
{
	*this = src;
}

ZBExtApps& ZBExtApps::operator=( const ZBExtApps& src )
{
	// Copy the members.
	ZBExtAppPropertiesIterator i( &const_cast<ZBExtApps&>( src ).GetExtAppSet() );

	for ( ZBExtAppProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
	{
		AddExtApp( pProp->Dup() );
	}

	m_pParent = src.m_pParent;

	return *this;
}

ZBExtApps* ZBExtApps::Dup() const
{
	return ( new ZBExtApps( *this ) );
}

void ZBExtApps::SetParent( CODSymbolComponent* pParent )
{
	m_pParent = pParent;
}

bool ZBExtApps::CreateInitialProperties()
{
	if ( GetExtAppCount() > 0 )
	{
		return true;
	}

	ZBExtAppProperties* pProps = new ZBExtAppProperties;

	if ( AddExtApp( pProps ) >= 0 )
	{
		return true;
	}

	return false;
}

int ZBExtApps::AddNewExtApp()
{
	ZBExtAppProperties* pProps = new ZBExtAppProperties;

	return AddExtApp( pProps );
}

int ZBExtApps::AddExtApp( ZBExtAppProperties* pProperty )
{
	if ( pProperty )
	{
		m_Set.Add( pProperty );

		// Returns the index
		return GetExtAppCount() - 1;
	}

	return -1;
}

bool ZBExtApps::DeleteExtApp( size_t Index )
{
	if ( Index < GetExtAppCount() )
	{
		ZBExtAppProperties* pProperty = GetProperty( Index );

		if ( pProperty )
		{
			m_Set.RemoveAt( Index );
			delete pProperty;
			return true;
		}
	}

	return false;
}

bool ZBExtApps::DeleteExtApp( const CString CommandTitle )
{
	// Run through the set of deliverables and check if found
	ZBExtAppPropertiesIterator i( &m_Set );

	for ( ZBExtAppProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
	{
		if ( pProp->GetCommandTitle() == CommandTitle )
		{
			delete pProp;
			i.Remove();
			return true;
		}
	}

	return false;
}

bool ZBExtApps::DeleteExtApp( ZBExtAppProperties* pProperty )
{
	ZBExtAppPropertiesIterator i( &m_Set );

	for ( ZBExtAppProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
	{
		if ( pProperty == pProp )
		{
			i.Remove();
			delete pProp;
			return true;
		}
	}

	return false;
}

int ZBExtApps::LocateFirstEmptyExtApp() const
{
	int Idx = 0;
	ZBExtAppPropertiesIterator i( &m_Set );

	for ( ZBExtAppProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext(), ++Idx )
	{
		if ( pProp->IsEmpty() )
		{
			return Idx;
		}
	}

	return -1;
}

void ZBExtApps::RemoveAllEmptyExtApps()
{
	ZBExtAppPropertiesIterator i( &m_Set );

	for ( ZBExtAppProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
	{
		if ( pProp->IsEmpty() )
		{
			delete pProp;
			i.Remove();
		}
	}
}

void ZBExtApps::RemoveAllExtApps()
{
	ZBExtAppPropertiesIterator i( &m_Set );

	for ( ZBExtAppProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
	{
		delete pProp;
	}

	// Then, remove all elements
	m_Set.RemoveAll();
}

CString ZBExtApps::GetCommandTitle( size_t Index ) const
{
	if ( Index < GetExtAppCount() )
	{
		return m_Set.GetAt( Index )->GetCommandTitle();
	}

	return _T( "" );
}

void ZBExtApps::SetCommandTitle( size_t Index, CString Value )
{
	if ( Index < GetExtAppCount() )
	{
		m_Set.GetAt( Index )->SetCommandTitle( Value );
	}
}

CString ZBExtApps::GetCommandLine( size_t Index ) const
{
	if ( Index < GetExtAppCount() )
	{
		return m_Set.GetAt( Index )->GetCommandLine();
	}

	return _T( "" );
}

void ZBExtApps::SetCommandLine( size_t Index, CString Value )
{
	if ( Index < GetExtAppCount() )
	{
		m_Set.GetAt( Index )->SetCommandLine( Value );
	}
}

CString ZBExtApps::GetCommandParameters( size_t Index ) const
{
	if ( Index < GetExtAppCount() )
	{
		return m_Set.GetAt( Index )->GetCommandParameters();
	}

	return _T( "" );
}

void ZBExtApps::SetCommandParameters( size_t Index, CString Value )
{
	if ( Index < GetExtAppCount() )
	{
		m_Set.GetAt( Index )->SetCommandParameters( Value );
	}
}

CString ZBExtApps::GetCommandStartupDirectory( size_t Index ) const
{
	if ( Index < GetExtAppCount() )
	{
		return m_Set.GetAt( Index )->GetCommandStartupDirectory();
	}

	return _T( "" );
}

void ZBExtApps::SetCommandStartupDirectory( size_t Index, CString Value )
{
	if ( Index < GetExtAppCount() )
	{
		m_Set.GetAt( Index )->SetCommandStartupDirectory( Value );
	}
}

int ZBExtApps::GetPriorityLevel( size_t Index ) const
{
	if ( Index < GetExtAppCount() )
	{
		return m_Set.GetAt( Index )->GetPriorityLevel();
	}

	return 0;
}

void ZBExtApps::SetPriorityLevel( size_t Index, const int value )
{
	if ( Index < GetExtAppCount() )
	{
		m_Set.GetAt( Index )->SetPriorityLevel( value );
	}
}

int ZBExtApps::GetWindowStartMode( size_t Index ) const
{
	if ( Index < GetExtAppCount() )
	{
		return m_Set.GetAt( Index )->GetWindowStartMode();
	}

	return 0;
}

void ZBExtApps::SetWindowStartMode( size_t Index, const int value )
{
	if ( Index < GetExtAppCount() )
	{
		m_Set.GetAt( Index )->SetWindowStartMode( value );
	}
}

bool ZBExtApps::ExtAppExist( const CString CommandTitle ) const
{
	// Run through the set and build the string
	ZBExtAppPropertiesIterator i( &m_Set );

	for ( ZBExtAppProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
	{
		if ( pProp->GetCommandTitle() == CommandTitle )
		{
			return true;
		}
	}

	return false;
}

ZBExtAppProperties* ZBExtApps::LocateExtApp( const CString CommandTitle ) const
{
	// Run through the set of deliverables and check if found
	ZBExtAppPropertiesIterator i( &m_Set );

	for ( ZBExtAppProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
	{
		if ( pProp->GetCommandTitle() == CommandTitle )
		{
			return pProp;
		}
	}

	return NULL;
}

void ZBExtApps::Serialize( CArchive& ar )
{
	if ( ar.IsStoring() )
	{
		// Serialize the size of the set
		ar << m_Set.GetSize();

		ZBExtAppPropertiesIterator i( &m_Set );

		for ( ZBExtAppProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
		{
			ar << pProp;
		}
	}
	else
	{
		RemoveAllExtApps();

		// Read the size of the set
		int Count;

		ar >> Count;

		ZBExtAppProperties* pProp;

		for ( int i = 0; i < Count; ++i )
		{
			ar >> pProp;
			AddExtApp( pProp );
		}
	}
}
