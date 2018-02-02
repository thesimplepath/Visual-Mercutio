// ZBWorkspaceGroupEntity.cpp: implementation of the ZBWorkspaceGroupEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBWorkspaceGroupEntity.h"
#include "ZBWorkspaceFileEntity.h"

#include "ZBTokenizer.h"

#include "zBaseLibRes.h"

#include "ZVWorkspaceGroupNameDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 18 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Static variables

ZBWorkspaceEntitySet ZBWorkspaceGroupEntity::m_FindSet;

IMPLEMENT_SERIAL( ZBWorkspaceGroupEntity, ZBWorkspaceEntity, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBWorkspaceGroupEntity::ZBWorkspaceGroupEntity( const CString Name /*= ""*/, ZBWorkspaceEntity* pParent /*= NULL*/ )
	: ZBWorkspaceEntity( Name, pParent )
{
}

ZBWorkspaceGroupEntity::ZBWorkspaceGroupEntity( const CString		Name,
												CStringArray*		pExtensionList,
												ZBWorkspaceEntity*	pParent			/*= NULL*/ )
	: ZBWorkspaceEntity( Name, pParent )
{
	if ( pExtensionList )
	{
		SetExtensionList( *pExtensionList );
	}
}

ZBWorkspaceGroupEntity::~ZBWorkspaceGroupEntity()
{
	RemoveAllEntities();
}

void ZBWorkspaceGroupEntity::RemoveAllEntities()
{
	// Sets the iterator to the right entity set
	ZBWorkspaceEntityIterator i( &m_EntitySet );

	for ( ZBWorkspaceEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
	{
		delete pEnv;
	}

	m_EntitySet.RemoveAll();
}

void ZBWorkspaceGroupEntity::SetExtensionList( CStringArray& ExtensionArray )
{
	// First, remove all elements
	m_ExtensionList.RemoveAll();

	// Then, copy all elements
	ZBWorkspaceGroupEntity::AddElementToExtensionList( ExtensionArray );
}

void ZBWorkspaceGroupEntity::AddElementToExtensionList( CStringArray& ExtensionArray )
{
	// Just add all elments
	int Count = ExtensionArray.GetSize();

	for ( int i = 0; i < Count; ++i )
	{
		m_ExtensionList.Add( ExtensionArray.GetAt( i ) );
	}
}

bool ZBWorkspaceGroupEntity::ContainThisExtension( const CString Extension )
{
	// Just add all elments
	int Count = m_ExtensionList.GetSize();

	for ( int i = 0; i < Count; ++i )
	{
		// If correspond
		if ( m_ExtensionList.GetAt(i).CompareNoCase( Extension ) == 0 )
		{
			return true;
		}
	}

	// Not found
	return false;
}

void ZBWorkspaceGroupEntity::SetExtensionList( const CString Extensions )
{
	ParseExtension( Extensions, m_ExtensionList );
}

void ZBWorkspaceGroupEntity::GetExtensionList( CString& Extensions )
{
	Extensions.Empty();

	// Initialize the token class with the separator char
	ZBTokenizer Token( ';' );

	// Just add all elments
	int Count = m_ExtensionList.GetSize();

	for ( int i = 0; i < Count; ++i )
	{
		// If correspond
		Token.AddToken( m_ExtensionList.GetAt( i ) );
	}

	Extensions = Token.GetString();
}

bool ZBWorkspaceGroupEntity::ParseExtension( const CString Extensions, CStringArray& ExtensionArray )
{
	// First, clear the array
	ExtensionArray.RemoveAll();

	// Initialize the token class with the separator char
	ZBTokenizer Token( ';' );

	CString sExt = Token.GetFirstToken( Extensions );

	while ( !sExt.IsEmpty() )
	{
		// Add the extension to the array
		ExtensionArray.Add( sExt );

		// Get next token
		sExt = Token.GetNextToken();
	}

	return true;
}

////////////////////////////////////////////////////////////////
// Group management functions

ZBWorkspaceGroupEntity* ZBWorkspaceGroupEntity::AddGroup( const CString	Name,
														  CStringArray*	pExtensionList,
														  const CString	InGroupName )
{
	ZBWorkspaceGroupEntity* pGroup = NULL;

	// If in group name defined, try to locate the group name
	if ( !InGroupName.IsEmpty() )
	{
		pGroup = _FindFirstGroup( InGroupName );
	}

	// Call the AddGroup function with the pGroup pointer passed has parameter
	return AddGroup( Name, pExtensionList, pGroup );
}

ZBWorkspaceGroupEntity* ZBWorkspaceGroupEntity::AddGroup( const CString				Name,
														  CStringArray*				pExtensionList,
														  ZBWorkspaceGroupEntity*	pInGroup )
{
	// If no group defined
	if ( !pInGroup )
	{
		pInGroup = this;
	}

	return pInGroup->AddGroup( Name, pExtensionList );
}

ZBWorkspaceGroupEntity* ZBWorkspaceGroupEntity::AddGroup( const CString Name, CStringArray* pExtensionList )
{
	ZBWorkspaceGroupEntity* pNewGroup = new ZBWorkspaceGroupEntity( Name, pExtensionList, this );
	m_EntitySet.Add( pNewGroup );
	return pNewGroup;
}

ZBWorkspaceGroupEntity* ZBWorkspaceGroupEntity::AddGroup( const CString Name, CString& Extensions )
{
	CStringArray ExtensionArray;

	if ( ParseExtension( Extensions, ExtensionArray) )
	{
		return AddGroup( Name, &ExtensionArray );
	}

	return NULL;
}

ZBWorkspaceGroupEntity* ZBWorkspaceGroupEntity::AddGroup( const CString	Name,
														  CString&		Extensions,
														  const CString	InGroupName )
{
	CStringArray ExtensionArray;

	if ( ParseExtension( Extensions, ExtensionArray ) )
	{
		return AddGroup( Name, &ExtensionArray, InGroupName );
	}

	return NULL;
}

ZBWorkspaceGroupEntity* ZBWorkspaceGroupEntity::AddGroup( const CString				Name,
														  CString&					Extensions,
														  ZBWorkspaceGroupEntity*	pInGroup )
{
	CStringArray ExtensionArray;

	if ( ParseExtension( Extensions, ExtensionArray ) )
	{
		return AddGroup( Name, &ExtensionArray, pInGroup );
	}

	return NULL;
}

bool ZBWorkspaceGroupEntity::RemoveGroup( const CString Name, bool Deeper /*= false*/ )
{
	ZBWorkspaceEntitySet* pSet = FindGroup( Name, Deeper );

	if ( pSet && pSet->GetSize() > 0 )
	{
		return _RemoveGroups( *pSet );
	}

	return false;
}

bool ZBWorkspaceGroupEntity::RemoveGroup( const CString Name, const CString InGroupName )
{
	ZBWorkspaceEntitySet* pSet = FindGroup( Name, InGroupName );

	if ( pSet && pSet->GetSize() > 0 )
	{
		return _RemoveGroups( *pSet );
	}

	return false;
}

bool ZBWorkspaceGroupEntity::RemoveGroup( const CString Name, ZBWorkspaceGroupEntity* pInGroup )
{
	ZBWorkspaceEntitySet* pSet = FindGroup( Name, pInGroup );

	if ( pSet && pSet->GetSize() > 0 )
	{
		return _RemoveGroups( *pSet );
	}

	return false;
}

bool ZBWorkspaceGroupEntity::RemoveGroup( ZBWorkspaceGroupEntity* pGroup )
{
	// Sets the iterator to the right entity set
	ZBWorkspaceEntityIterator i( &m_EntitySet );

	for ( ZBWorkspaceEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
	{
		if ( pEnv == pGroup && ISA( pEnv, ZBWorkspaceGroupEntity ) )
		{
			// Free the memory
			delete pGroup;

			// Remove the current element
			i.Remove();
			return true;
		}
	}

	return false;
}

bool ZBWorkspaceGroupEntity::_RemoveGroups( ZBWorkspaceEntitySet& Set )
{
	// Initialize to false
	bool RetValue = false;

	if ( Set.GetSize() > 0 )
	{
		// If elements, set to true
		RetValue = true;

		// For each elements,
		// check if a group and if he has a parent
		// then call the parent to remove the group
		int Count = Set.GetSize();

		for ( int i = 0; i < Count; ++i )
		{
			if ( Set.GetAt( i ) &&
				 ISA( Set.GetAt( i ), ZBWorkspaceGroupEntity ) &&
				 dynamic_cast<ZBWorkspaceGroupEntity*>( Set.GetAt( i ) )->GetParent() != NULL )
			{
				ZBWorkspaceGroupEntity* pGroup = dynamic_cast<ZBWorkspaceGroupEntity*>( Set.GetAt( i ) );

				// If problem sets to false at least one time
				if ( !dynamic_cast<ZBWorkspaceGroupEntity*>( pGroup->GetParent() )->RemoveGroup( pGroup ) )
				{
					RetValue = false;
				}
			}
		}
	}

	return RetValue;
}

ZBWorkspaceEntitySet* ZBWorkspaceGroupEntity::FindGroup( const CString Name, bool Deeper /*= false*/ )
{
	m_FindSet.RemoveAll();
	_FindGroup( Name, Deeper );
	return &m_FindSet;
}

ZBWorkspaceEntitySet* ZBWorkspaceGroupEntity::FindGroup( const CString Name, const CString InGroupName )
{
	ZBWorkspaceGroupEntity* pGroup = NULL;

	// If in group name defined,
	// Try to locate the group name
	if ( !InGroupName.IsEmpty() )
	{
		pGroup = _FindFirstGroup( InGroupName );
	}

	// Call the FindGroup function with the pGroup pointer passed has parameter
	return FindGroup( Name, pGroup );
}

ZBWorkspaceEntitySet* ZBWorkspaceGroupEntity::FindGroup( const CString Name, ZBWorkspaceGroupEntity* pInGroup )
{
	m_FindSet.RemoveAll();
	_FindGroup( Name, pInGroup );
	return &m_FindSet;
}

void ZBWorkspaceGroupEntity::_FindGroup( const CString Name, ZBWorkspaceGroupEntity* pInGroup )
{
	if ( !pInGroup )
	{
		pInGroup = this;
	}

	pInGroup->_FindGroup( Name, false );
}

// The _FindGroup function will search all groups corresponding to the name passed as parameter
// The function will fill the m_FindSet static variable with elements found
void ZBWorkspaceGroupEntity::_FindGroup( const CString Name, bool Deeper /*= false*/ )
{
	// Sets the iterator to the right entity set
	ZBWorkspaceEntityIterator i( &m_EntitySet );

	for ( ZBWorkspaceEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
	{
		if ( ISA( pEnv, ZBWorkspaceGroupEntity ) )
		{
			// If correspond to the requested name
			// add it to the find set
			if ( dynamic_cast<ZBWorkspaceGroupEntity*>( pEnv )->GetEntityName() == Name )
			{
				m_FindSet.Add( pEnv );
			}

			// If the group has entity
			// call the group's function 
			if ( Deeper && dynamic_cast<ZBWorkspaceGroupEntity*>( pEnv )->ContainEntity() )
			{
				dynamic_cast<ZBWorkspaceGroupEntity*>(pEnv)->_FindGroup( Name, Deeper );
			}
		}
	}
}

ZBWorkspaceGroupEntity* ZBWorkspaceGroupEntity::_FindFirstGroup( const CString				Name,
																 ZBWorkspaceGroupEntity*	pInGroup )
{
	if ( !pInGroup )
	{
		pInGroup = this;
	}

	return pInGroup->_FindFirstGroup( Name, false );
}

ZBWorkspaceGroupEntity* ZBWorkspaceGroupEntity::_FindFirstGroup( const CString Name, bool Deeper /*= false*/ )
{
	ZBWorkspaceEntityIterator i( &m_EntitySet );

	for ( ZBWorkspaceEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
	{
		if ( ISA( pEnv, ZBWorkspaceGroupEntity ) )
		{
			// If correspond to the requested group name
			// return it
			if ( dynamic_cast<ZBWorkspaceGroupEntity*>( pEnv )->GetEntityName() == Name )
			{
				return dynamic_cast<ZBWorkspaceGroupEntity*>( pEnv );
			}

			// If the group has entity
			if ( Deeper && dynamic_cast<ZBWorkspaceGroupEntity*>( pEnv )->ContainEntity() )
			{
				ZBWorkspaceGroupEntity* pGroup =
					dynamic_cast<ZBWorkspaceGroupEntity*>( pEnv )->_FindFirstGroup( Name, Deeper );

				if ( pGroup )
				{
					return pGroup;
				}
			}
		}
	}

	return NULL;
}

bool ZBWorkspaceGroupEntity::GroupExist( const CString Name, bool Deeper /*= false*/ )
{
	// Sets the iterator to the right entity set
	ZBWorkspaceEntityIterator i( &m_EntitySet );

	for ( ZBWorkspaceEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
	{
		if ( ISA( pEnv, ZBWorkspaceGroupEntity ) )
		{
			// If correspond to the requested name
			if ( dynamic_cast<ZBWorkspaceGroupEntity*>( pEnv )->GetEntityName() == Name )
			{
				return true;
			}

			// If the group has entity
			if ( Deeper && dynamic_cast<ZBWorkspaceGroupEntity*>(pEnv)->ContainEntity() )
			{
				if ( dynamic_cast<ZBWorkspaceGroupEntity*>( pEnv )->GroupExist( Name, Deeper ) )
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool ZBWorkspaceGroupEntity::GroupExist( const CString Name, const CString InGroupName )
{
	ZBWorkspaceGroupEntity* pGroup = NULL;

	// If in group name defined,
	// Try to locate the group name
	if ( !InGroupName.IsEmpty() )
	{
		pGroup = _FindFirstGroup( InGroupName );
	}

	// Call the function with the group pointer
	return GroupExist( Name, pGroup );
}

bool ZBWorkspaceGroupEntity::GroupExist( const CString Name, ZBWorkspaceGroupEntity* pInGroup )
{
	if ( !pInGroup )
	{
		pInGroup = this;
	}

	return pInGroup->GroupExist( Name, false );
}

////////////////////////////////////////////////////////////////
// File management functions
ZBWorkspaceFileEntity* ZBWorkspaceGroupEntity::AddFile( const CString Filename )
{
	ZBWorkspaceFileEntity* pNewFile = new ZBWorkspaceFileEntity( Filename, this );
	m_EntitySet.Add( pNewFile );
	return pNewFile;
}

ZBWorkspaceFileEntity* ZBWorkspaceGroupEntity::AddFile( const CString Filename, const CString InGroupName )
{
	ZBWorkspaceGroupEntity* pGroup = NULL;

	// If in group name defined,
	// Try to locate the group name
	if ( !InGroupName.IsEmpty() )
	{
		pGroup = _FindFirstGroup( InGroupName );
	}

	// Call the AddFile function with the pGroup pointer passed has parameter
	return AddFile( Filename, pGroup );
}

ZBWorkspaceFileEntity* ZBWorkspaceGroupEntity::AddFile( const CString Filename, ZBWorkspaceGroupEntity* pInGroup )
{
	if ( !pInGroup )
	{
		pInGroup = this;
	}

	return pInGroup->AddFile( Filename );
}

bool ZBWorkspaceGroupEntity::RemoveFile( ZBWorkspaceFileEntity* pFile )
{
	// Sets the iterator to the right entity set
	ZBWorkspaceEntityIterator i( &m_EntitySet );

	for ( ZBWorkspaceEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
	{
		if ( ISA( pEnv, ZBWorkspaceFileEntity ) && dynamic_cast<ZBWorkspaceFileEntity*>( pEnv ) == pFile )
		{
			// Free the memory
			delete pEnv;

			// Remove the current element
			i.Remove();
			return true;
		}

		// If we have a group entity,
		// and the group has entity
		// call the recalculate group function 
		if ( ISA( pEnv, ZBWorkspaceGroupEntity ) && dynamic_cast<ZBWorkspaceGroupEntity*>( pEnv )->ContainEntity() )
		{
			if ( dynamic_cast<ZBWorkspaceGroupEntity*>( pEnv )->RemoveFile( pFile ) )
			{
				return true;
			}
		}
	}

	return false;
}

bool ZBWorkspaceGroupEntity::RemoveFile( const CString Filename )
{
	// Sets the iterator to the right entity set
	ZBWorkspaceEntityIterator i( &m_EntitySet );

	for ( ZBWorkspaceEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
	{
		if ( ISA( pEnv, ZBWorkspaceFileEntity ) &&
			 dynamic_cast<ZBWorkspaceFileEntity*>( pEnv )->GetFilename() == Filename )
		{
			// Free the memory
			delete pEnv;

			// Remove the current element
			i.Remove();
			return true;
		}
	}

	return false;
}

bool ZBWorkspaceGroupEntity::RemoveFile( const CString Filename, const CString InGroupName )
{
	ZBWorkspaceGroupEntity* pGroup = NULL;

	// If in group name defined,
	// Try to locate the group name
	if ( !InGroupName.IsEmpty() )
	{
		pGroup = _FindFirstGroup( InGroupName );
	}

	// Call the RemoveFile function with the pGroup pointer passed has parameter
	return RemoveFile( Filename, pGroup );
}

bool ZBWorkspaceGroupEntity::RemoveFile( const CString Filename, ZBWorkspaceGroupEntity* pInGroup )
{
	if ( !pInGroup )
	{
		pInGroup = this;
	}

	return pInGroup->RemoveFile( Filename );
}

void ZBWorkspaceGroupEntity::RecalculateParent()
{
	// Sets the iterator to the right entity set
	ZBWorkspaceEntityIterator i( &m_EntitySet );

	for ( ZBWorkspaceEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
	{
		// Set the parent pointer
		pEnv->SetParent( this );

		// If we have a group entity,
		// and the group has entity
		// call the recalculate group function 
		if ( ISA( pEnv, ZBWorkspaceGroupEntity ) &&
			 dynamic_cast<ZBWorkspaceGroupEntity*>( pEnv )->ContainEntity() )
		{
			dynamic_cast<ZBWorkspaceGroupEntity*>( pEnv )->RecalculateParent();
		}
	}
}

bool ZBWorkspaceGroupEntity::DisplayProperties()
{
	CString Extensions;
	GetExtensionList( Extensions );

	// Asks for the name
	ZVWorkspaceGroupNameDlg dlg( ( GetParent() && ISA( GetParent(), ZBWorkspaceGroupEntity ) ) ? dynamic_cast<ZBWorkspaceGroupEntity*>( GetParent() ) : NULL,
								 GetEntityName(),
								 Extensions );

	if ( dlg.DoModal() == IDOK )
	{
		SetExtensionList( dlg.GetExtensions() );
		return true;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceGroupEntity diagnostics

#ifdef _DEBUG
void ZBWorkspaceGroupEntity::AssertValid() const
{
	ZBWorkspaceEntity::AssertValid();
}

void ZBWorkspaceGroupEntity::Dump( CDumpContext& dc ) const
{
	ZBWorkspaceEntity::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceGroupEntity serialization

void ZBWorkspaceGroupEntity::Serialize ( CArchive& ar )
{
	ZBWorkspaceEntity::Serialize( ar );
	
	// If something else to serialize, do it below
	if ( ar.IsStoring() )
	{
		// Write the elements
		ar << static_cast<int>( GetEntityCount() );

		for ( int nIdx = 0; nIdx < (int)GetEntityCount(); nIdx++ )
		{
			ZBWorkspaceEntity* pEntity = GetEntityAt( nIdx );
			ar << pEntity;
		}
	}
	else
	{
		// Read the elements

		// Before reading elements, remove all
		RemoveAllEntities();

		int nCount;
		ZBWorkspaceEntity* pEntity;

		ar >> nCount;

		for ( int i=0; i<nCount; i++ )
		{
			ar >> pEntity;
			m_EntitySet.Add( pEntity );
			pEntity->SetParent( this );
		}
	}

	// Serialize the extension list
	m_ExtensionList.Serialize( ar );
}
