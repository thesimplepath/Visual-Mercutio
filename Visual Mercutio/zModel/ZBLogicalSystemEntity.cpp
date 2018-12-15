// ZBLogicalSystemEntity.cpp: implementation of the ZBLogicalSystemEntity class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBLogicalSystemEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Static variables

ZBSystemEntitySet    ZBLogicalSystemEntity::m_FindSet;

BOOL                ZBLogicalSystemEntity::m_bModified    = FALSE;

IMPLEMENT_SERIAL( ZBLogicalSystemEntity, ZBSystemEntity, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBLogicalSystemEntity::ZBLogicalSystemEntity( const CString        Name        /*= _T( "" )*/, 
                                              const CString        Description    /*= _T( "" )*/, 
                                              ZBSystemEntity*    pParent        /*= NULL*/ )
    : ZBSystemEntity( Name, Description, pParent )
{
}

ZBLogicalSystemEntity::~ZBLogicalSystemEntity()
{
    RemoveAllSystemEntities();
}

void ZBLogicalSystemEntity::RemoveAllSystemEntities()
{
    // Sets the iterator to the right entity set
    ZBSystemEntityIterator i( &m_EntitySet );

    for ( ZBSystemEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        delete pEnv;
    }

    m_EntitySet.RemoveAll();
}

////////////////////////////////////////////////////////////////
// Group management functions

ZBLogicalSystemEntity* ZBLogicalSystemEntity::AddSystem( const CString Name,
                                                         const CString Description,
                                                         const CString InSystemName )
{
    ZBLogicalSystemEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if ( !InSystemName.IsEmpty() )
    {
        pGroup = _FindFirstSystem( InSystemName );
    }

    // Call the AddSystem function with the pGroup pointer passed has parameter
    return AddSystem( Name, Description, pGroup );
}

ZBLogicalSystemEntity* ZBLogicalSystemEntity::AddSystem( const CString            Name,
                                                         const CString            Description,
                                                         ZBLogicalSystemEntity*    pInSystem )
{
    // If no group defined
    if ( !pInSystem )
    {
        pInSystem = this;
    }

    return pInSystem->AddSystem( Name, Description );
}

ZBLogicalSystemEntity* ZBLogicalSystemEntity::AddSystem( const CString Name, const CString Description )
{
    ZBLogicalSystemEntity* pNewGroup = new ZBLogicalSystemEntity( Name, Description, this );
    m_EntitySet.Add( pNewGroup );

    return pNewGroup;
}

bool ZBLogicalSystemEntity::RemoveSystem( const CString Name, bool Deeper /*= false*/ )
{
    ZBSystemEntitySet* pSet = FindSystem( Name, Deeper );

    if ( pSet && pSet->GetSize() > 0 )
    {
        return _RemoveSystems( *pSet );
    }

    return false;
}
bool ZBLogicalSystemEntity::RemoveSystem( const CString Name, const CString InSystemName )
{
    ZBSystemEntitySet* pSet = FindSystem( Name, InSystemName );

    if ( pSet && pSet->GetSize() > 0 )
    {
        return _RemoveSystems( *pSet );
    }

    return false;
}
bool ZBLogicalSystemEntity::RemoveSystem( const CString Name, ZBLogicalSystemEntity* pInSystem )
{
    ZBSystemEntitySet* pSet = FindSystem( Name, pInSystem );

    if ( pSet && pSet->GetSize() > 0 )
    {
        return _RemoveSystems( *pSet );
    }

    return false;
}
bool ZBLogicalSystemEntity::RemoveSystem( ZBLogicalSystemEntity* pGroup )
{
    // Sets the iterator to the right entity set
    ZBSystemEntityIterator i( &m_EntitySet );

    for ( ZBSystemEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( pEnv == pGroup && ISA( pEnv, ZBLogicalSystemEntity ) )
        {
            // Free the memory
            delete pGroup;

            // Remove the current element
            i.Remove();
            return true;
        }

        // If we have a group entity,
        // and the group has entity
        // call the recalculate group function 
        if ( ISA( pEnv, ZBLogicalSystemEntity ) && dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->ContainEntity() )
        {
            if ( dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->RemoveSystem( pGroup ) )
            {
                return true;
            }
        }
    }

    return false;
}

bool ZBLogicalSystemEntity::_RemoveSystems( ZBSystemEntitySet& Set )
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
                 ISA( Set.GetAt( i ), ZBLogicalSystemEntity ) &&
                 dynamic_cast<ZBLogicalSystemEntity*>( Set.GetAt( i ) )->GetParent() != NULL )
            {
                ZBLogicalSystemEntity* pGroup = dynamic_cast<ZBLogicalSystemEntity*>( Set.GetAt( i ) );

                // If problem sets to false at least one time
                if ( !dynamic_cast<ZBLogicalSystemEntity*>( pGroup->GetParent() )->RemoveSystem( pGroup ) )
                {
                    RetValue = false;
                }
            }
        }
    }

    return RetValue;
}

// JMR-MODIF - Le 27 février 2006 - Ajout de la fonction RemoveSystemFromSet.
bool ZBLogicalSystemEntity::RemoveSystemFromSet( ZBSystemEntity* pSystem )
{
    // Sets the iterator to the right entity set
    ZBSystemEntityIterator i( &m_EntitySet );

    for ( ZBSystemEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( pEnv == pSystem )
        {
            // Remove the current element
            i.Remove();
            return true;
        }
    }

    return false;
}

ZBSystemEntity* ZBLogicalSystemEntity::FindSystemByGUID( const CString GUID, bool Deeper /*= false*/ )
{
    // First, check if the main group correspond to the requested GUID
    // add it to the find set
    if ( GetGUID() == GUID )
    {
        return this;
    }

    // Then search in the group itself
    return _FindSystemByGUID( GUID, Deeper );
}

ZBSystemEntitySet* ZBLogicalSystemEntity::FindSystem( const CString Name, bool Deeper /*= false*/ )
{
    m_FindSet.RemoveAll();

    // First, check if the main group correspond to the requested name
    // add it to the find set
    if ( GetEntityName() == Name )
    {
        m_FindSet.Add( this );
    }

    // Then search in the group itself
    _FindSystem( Name, Deeper );

    return &m_FindSet;
}

ZBSystemEntitySet* ZBLogicalSystemEntity::FindSystem( const CString Name, const CString InSystemName )
{
    ZBLogicalSystemEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if ( !InSystemName.IsEmpty() )
    {
        pGroup = _FindFirstSystem( InSystemName );
    }

    // Call the FindSystem function with the pGroup pointer passed has parameter
    return FindSystem( Name, pGroup );
}

ZBSystemEntitySet* ZBLogicalSystemEntity::FindSystem( const CString Name, ZBLogicalSystemEntity* pInSystem )
{
    m_FindSet.RemoveAll();

    // First, check if the main group correspond to the requested name
    // add it to the find set
    if ( GetEntityName() == Name )
    {
        m_FindSet.Add( this );
    }

    // Then search in the group itself
    _FindSystem( Name, pInSystem );
    return &m_FindSet;
}

void ZBLogicalSystemEntity::_FindSystem( const CString Name, ZBLogicalSystemEntity* pInSystem )
{
    if ( !pInSystem )
    {
        pInSystem = this;
    }

    pInSystem->_FindSystem( Name, false );
}

// The _FindSystemByGUID function will search all groups corresponding to the GUID passed as parameter
ZBSystemEntity* ZBLogicalSystemEntity::_FindSystemByGUID( const CString GUID, bool Deeper /*= false*/ )
{
    // Sets the iterator to the right entity set
    ZBSystemEntityIterator i( &m_EntitySet );

    for ( ZBSystemEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( ISA( pEnv, ZBLogicalSystemEntity ) )
        {
            // If correspond to the requested name
            // add it to the find set
            if ( dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->GetGUID() == GUID )
            {
                return pEnv;
            }

            // If the group has entity
            // call the group's function 
            if ( Deeper && dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->ContainEntity() )
            {
                ZBSystemEntity* pFoundEnv =
                    dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->_FindSystemByGUID( GUID, Deeper );

                if ( pFoundEnv )
                {
                    return pFoundEnv;
                }
            }
        }
    }

    return NULL;
}

// The _FindSystem function will search all groups corresponding to the name passed as parameter
// The function will fill the m_FindSet static variable with elements found
void ZBLogicalSystemEntity::_FindSystem( const CString Name, bool Deeper /*= false*/ )
{
    // Sets the iterator to the right entity set
    ZBSystemEntityIterator i( &m_EntitySet );

    for ( ZBSystemEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( ISA( pEnv, ZBLogicalSystemEntity ) )
        {
            // If correspond to the requested name
            // add it to the find set
            if ( dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->GetEntityName() == Name )
            {
                m_FindSet.Add( pEnv );
            }

            // If the group has entity
            // call the group's function 
            if ( Deeper && dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->ContainEntity() )
            {
                dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->_FindSystem( Name, Deeper );
            }
        }
    }
}

ZBLogicalSystemEntity* ZBLogicalSystemEntity::_FindFirstSystem( const CString Name,
                                                                ZBLogicalSystemEntity* pInSystem )
{
    if ( !pInSystem )
    {
        pInSystem = this;
    }

    return pInSystem->_FindFirstSystem( Name, false );
}

ZBLogicalSystemEntity* ZBLogicalSystemEntity::_FindFirstSystem( const CString Name, bool Deeper /*= false*/ )
{
    ZBSystemEntityIterator i( &m_EntitySet );

    for ( ZBSystemEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( ISA( pEnv, ZBLogicalSystemEntity ) )
        {
            // If correspond to the requested group name
            // return it
            if ( dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->GetEntityName() == Name )
            {
                return dynamic_cast<ZBLogicalSystemEntity*>( pEnv );
            }

            // If the group has entity
            if ( Deeper && dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->ContainEntity() )
            {
                ZBLogicalSystemEntity* pGroup =
                    dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->_FindFirstSystem( Name, Deeper );

                if ( pGroup )
                {
                    return pGroup;
                }
            }
        }
    }

    return NULL;
}

// JMR-MODIF - Le 27 février 2006 - Ajout de la fonction MoveSystem.
bool ZBLogicalSystemEntity::MoveSystem( ZBSystemEntity* pSystem )
{
    // First, remove the entity from the old group
    ZBSystemEntity* pParent = pSystem->GetParent();

    if ( pParent && ISA( pParent, ZBLogicalSystemEntity ) && ISA( pSystem, ZBLogicalSystemEntity ) )
    {
        if ( !dynamic_cast<ZBLogicalSystemEntity*>( pParent )->RemoveSystemFromSet( dynamic_cast<ZBLogicalSystemEntity*>( pSystem ) ) )
        {
            return false;
        }
    }

    // Then, add the entity to the new group
    AddSystem( pSystem );

    // Sets the new parent
    pSystem->SetParent( this );

    return true;
}

bool ZBLogicalSystemEntity::SystemExist( const CString Name, bool Deeper /*= false*/ )
{
    // Sets the iterator to the right entity set
    ZBSystemEntityIterator i( &m_EntitySet );

    for ( ZBSystemEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( ISA( pEnv, ZBLogicalSystemEntity ) )
        {
            // If correspond to the requested name
            if ( dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->GetEntityName() == Name )
            {
                return true;
            }

            // If the group has entity
            if ( Deeper && dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->ContainEntity() )
            {
                if ( dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->SystemExist( Name, Deeper ) )
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool ZBLogicalSystemEntity::SystemExist( const CString Name, const CString InSystemName )
{
    ZBLogicalSystemEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if ( !InSystemName.IsEmpty() )
    {
        pGroup = _FindFirstSystem( InSystemName );
    }

    // Call the function with the group pointer
    return SystemExist( Name, pGroup );
}

bool ZBLogicalSystemEntity::SystemExist( const CString Name, ZBLogicalSystemEntity* pInSystem )
{
    if ( !pInSystem )
    {
        pInSystem = this;
    }

    return pInSystem->SystemExist( Name, false );
}

void ZBLogicalSystemEntity::RecalculateParent()
{
    // Sets the iterator to the right entity set
    ZBSystemEntityIterator i( &m_EntitySet );

    for ( ZBSystemEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        // Set the parent pointer
        pEnv->SetParent( this );

        // If we have a group entity,
        // and the group has entity
        // call the recalculate group function 
        if ( ISA( pEnv, ZBLogicalSystemEntity ) && dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->ContainEntity() )
        {
            dynamic_cast<ZBLogicalSystemEntity*>( pEnv )->RecalculateParent();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBLogicalSystemEntity diagnostics

#ifdef _DEBUG
void ZBLogicalSystemEntity::AssertValid() const
{
    ZBSystemEntity::AssertValid();
}

void ZBLogicalSystemEntity::Dump( CDumpContext& dc ) const
{
    ZBSystemEntity::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBLogicalSystemEntity serialization

void ZBLogicalSystemEntity::Serialize ( CArchive& ar )
{
    ZBSystemEntity::Serialize( ar );
    
    // If something else to serialize, do it below
    if ( ar.IsStoring() )
    {
        // Write the elements
        ar << static_cast<int>( GetEntityCount() );

        for ( int nIdx = 0; nIdx < (int)GetEntityCount(); nIdx++ )
        {
            ZBSystemEntity* pEntity = GetEntityAt( nIdx );
            ar << pEntity;
        }
    }
    else
    {
        // Read the elements

        // Before reading elements, remove all
        RemoveAllSystemEntities();
        
        int nCount;
        ZBSystemEntity* pEntity;

        ar >> nCount;

        for ( int i=0; i<nCount; i++ )
        {
            ar >> pEntity;
            m_EntitySet.Add( pEntity );
            pEntity->SetParent( this );
        }
    }
}
