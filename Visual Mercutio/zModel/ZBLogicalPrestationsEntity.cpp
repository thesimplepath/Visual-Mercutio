// ******************************************************************************************************************
// *                                        Classe ZDLogicalPrestationsEntity                                        *
// ******************************************************************************************************************
// * JMR-MODIF - Le 7 octobre 2005 - Ajout de la classe ZDLogicalPrestationsEntity.                                    *
// ******************************************************************************************************************
// * Cette classe représente une entité de type prestation.    Une entité peut être considérée comme un élément du        *
// * document.                                                                                                        *
// ******************************************************************************************************************

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "stdafx.h"
#include "ZBLogicalPrestationsEntity.h"

//////////////////////////////////////////////////////////////////////
// Static variables

ZBPrestationsEntitySet    ZBLogicalPrestationsEntity::m_FindSet;

BOOL                    ZBLogicalPrestationsEntity::m_bModified = FALSE;

IMPLEMENT_SERIAL( ZBLogicalPrestationsEntity, ZBPrestationsEntity, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBLogicalPrestationsEntity::ZBLogicalPrestationsEntity( const CString            Name        /*= _T( "" )*/,
                                                        const CString            Description    /*= _T( "" )*/,
                                                        ZBPrestationsEntity*    pParent        /*= NULL*/ )
    : ZBPrestationsEntity( Name, Description, pParent )
{
}

ZBLogicalPrestationsEntity::~ZBLogicalPrestationsEntity()
{
    RemoveAllPrestationsEntities();
}

void ZBLogicalPrestationsEntity::RemoveAllPrestationsEntities()
{
    // Sets the iterator to the right entity set
    ZBPrestationsEntityIterator i( &m_EntitySet );

    for ( ZBPrestationsEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        delete pEnv;
    }

    m_EntitySet.RemoveAll();
}

////////////////////////////////////////////////////////////////
// Group management functions

ZBLogicalPrestationsEntity* ZBLogicalPrestationsEntity::AddPrestation( const CString Name,
                                                                       const CString Description,
                                                                       const CString InPrestationName )
{
    ZBLogicalPrestationsEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if ( !InPrestationName.IsEmpty() )
    {
        pGroup = _FindFirstPrestation( InPrestationName );
    }

    // Call the AddPrestation function with the pGroup pointer passed has parameter
    return AddPrestation( Name, Description, pGroup );
}

ZBLogicalPrestationsEntity* ZBLogicalPrestationsEntity::AddPrestation( const CString                Name,
                                                                       const CString                Description,
                                                                       ZBLogicalPrestationsEntity*    pInPrestation )
{
    // If no group defined
    if ( !pInPrestation )
    {
        pInPrestation = this;
    }

    return pInPrestation->AddPrestation( Name, Description );
}

ZBLogicalPrestationsEntity* ZBLogicalPrestationsEntity::AddPrestation( const CString Name,
                                                                       const CString Description )
{
    ZBLogicalPrestationsEntity* pNewGroup = new ZBLogicalPrestationsEntity( Name, Description, this );
    m_EntitySet.Add( pNewGroup );

    return pNewGroup;
}

bool ZBLogicalPrestationsEntity::RemovePrestation( const CString Name, bool Deeper /*= false*/ )
{
    ZBPrestationsEntitySet* pSet = FindPrestation( Name, Deeper );

    if ( pSet && pSet->GetSize() > 0 )
    {
        return _RemovePrestations( *pSet );
    }

    return false;
}
bool ZBLogicalPrestationsEntity::RemovePrestation( const CString Name, const CString InPrestationName )
{
    ZBPrestationsEntitySet* pSet = FindPrestation( Name, InPrestationName );

    if ( pSet && pSet->GetSize() > 0 )
    {
        return _RemovePrestations( *pSet );
    }

    return false;
}
bool ZBLogicalPrestationsEntity::RemovePrestation( const CString Name, ZBLogicalPrestationsEntity* pInPrestation )
{
    ZBPrestationsEntitySet* pSet = FindPrestation( Name, pInPrestation );

    if ( pSet && pSet->GetSize() > 0 )
    {
        return _RemovePrestations( *pSet );
    }

    return false;
}
bool ZBLogicalPrestationsEntity::RemovePrestation( ZBLogicalPrestationsEntity* pPrestation )
{
    // Sets the iterator to the right entity set
    ZBPrestationsEntityIterator i( &m_EntitySet );

    for ( ZBPrestationsEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( pEnv == pPrestation && ISA( pEnv, ZBLogicalPrestationsEntity ) )
        {
            // Free the memory
            delete pPrestation;

            // Remove the current element
            i.Remove();
            return true;
        }

        // If we have a group entity,
        // and the group has entity
        // call the recalculate group function 
        if ( ISA( pEnv, ZBLogicalPrestationsEntity ) &&
             dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->ContainEntity() )
        {
            if ( dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->RemovePrestation( pPrestation ) )
            {
                return true;
            }
        }
    }

    return false;
}

bool ZBLogicalPrestationsEntity::_RemovePrestations( ZBPrestationsEntitySet& Set )
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
                 ISA( Set.GetAt( i ), ZBLogicalPrestationsEntity ) &&
                 dynamic_cast<ZBLogicalPrestationsEntity*>( Set.GetAt( i ) )->GetParent() != NULL )
            {
                ZBLogicalPrestationsEntity* pGroup = dynamic_cast<ZBLogicalPrestationsEntity*>( Set.GetAt( i ) );

                // If problem sets to false at least one time
                if ( !dynamic_cast<ZBLogicalPrestationsEntity*>( pGroup->GetParent() )->RemovePrestation( pGroup ) )
                {
                    RetValue = false;
                }
            }
        }
    }

    return RetValue;
}

bool ZBLogicalPrestationsEntity::RemovePrestationFromSet( ZBPrestationsEntity* pPrestation )
{
    // Sets the iterator to the right entity set
    ZBPrestationsEntityIterator i( &m_EntitySet );

    for ( ZBPrestationsEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( pEnv == pPrestation )
        {
            // Remove the current element
            i.Remove();
            return true;
        }
    }

    return false;
}

ZBPrestationsEntity* ZBLogicalPrestationsEntity::FindPrestationByGUID( const CString GUID, bool Deeper /*= false*/ )
{
    // First, check if the main group correspond to the requested GUID
    // add it to the find set
    if ( GetGUID() == GUID )
    {
        return this;
    }

    // Then search in the group itself
    return _FindPrestationByGUID( GUID, Deeper );
}

ZBPrestationsEntitySet* ZBLogicalPrestationsEntity::FindPrestation( const CString Name, bool Deeper /*= false*/ )
{
    m_FindSet.RemoveAll();

    // First, check if the main group correspond to the requested name
    // add it to the find set
    if ( GetEntityName() == Name )
    {
        m_FindSet.Add( this );
    }

    // Then search in the group itself
    _FindPrestation( Name, Deeper );

    return &m_FindSet;
}

ZBPrestationsEntitySet* ZBLogicalPrestationsEntity::FindPrestation( const CString Name,
                                                                    const CString InPrestationName )
{
    ZBLogicalPrestationsEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if ( !InPrestationName.IsEmpty() )
    {
        pGroup = _FindFirstPrestation( InPrestationName );
    }

    // Call the FindPrestation function with the pGroup pointer passed has parameter
    return FindPrestation( Name, pGroup );
}

ZBPrestationsEntitySet* ZBLogicalPrestationsEntity::FindPrestation( const CString Name,
                                                                    ZBLogicalPrestationsEntity* pInPrestation )
{
    m_FindSet.RemoveAll();

    // First, check if the main group correspond to the requested name
    // add it to the find set
    if ( GetEntityName() == Name )
    {
        m_FindSet.Add( this );
    }

    // Then search in the group itself
    _FindPrestation( Name, pInPrestation );

    return &m_FindSet;
}

void ZBLogicalPrestationsEntity::_FindPrestation( const CString Name, ZBLogicalPrestationsEntity* pInPrestation )
{
    if ( !pInPrestation )
    {
        pInPrestation = this;
    }

    pInPrestation->_FindPrestation( Name, false );
}

// The _FindPrestationByGUID function will search all groups corresponding to the GUID passed as parameter
ZBPrestationsEntity* ZBLogicalPrestationsEntity::_FindPrestationByGUID( const CString    GUID,
                                                                        bool            Deeper    /*= false*/ )
{
    // Sets the iterator to the right entity set
    ZBPrestationsEntityIterator i( &m_EntitySet );

    for ( ZBPrestationsEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( ISA( pEnv, ZBLogicalPrestationsEntity ) )
        {
            // If correspond to the requested name
            // add it to the find set
            if ( dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->GetGUID() == GUID )
            {
                return pEnv;
            }

            // If the group has entity
            // call the group's function 
            if ( Deeper && dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->ContainEntity() )
            {
                ZBPrestationsEntity* pFoundEnv =
                    dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->_FindPrestationByGUID( GUID, Deeper );

                if ( pFoundEnv )
                {
                    return pFoundEnv;
                }
            }
        }
    }

    return NULL;
}

// The _FindPrestation function will search all groups corresponding to the name passed as parameter
// The function will fill the m_FindSet static variable with elements found
void ZBLogicalPrestationsEntity::_FindPrestation( const CString Name, bool Deeper /*= false*/ )
{
    // Sets the iterator to the right entity set
    ZBPrestationsEntityIterator i( &m_EntitySet );

    for ( ZBPrestationsEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( ISA( pEnv, ZBLogicalPrestationsEntity ) )
        {
            // If correspond to the requested name
            // add it to the find set
            if ( dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->GetEntityName() == Name )
            {
                m_FindSet.Add( pEnv );
            }

            // If the group has entity
            // call the group's function 
            if ( Deeper && dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->ContainEntity() )
            {
                dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->_FindPrestation( Name, Deeper );
            }
        }
    }
}

ZBLogicalPrestationsEntity* ZBLogicalPrestationsEntity::_FindFirstPrestation( const CString                    Name,
                                                                              ZBLogicalPrestationsEntity*    pInPrestation )
{
    if ( !pInPrestation )
    {
        pInPrestation = this;
    }

    return pInPrestation->_FindFirstPrestation( Name, false );
}

ZBLogicalPrestationsEntity* ZBLogicalPrestationsEntity::_FindFirstPrestation( const CString    Name,
                                                                              bool            Deeper    /*= false*/ )
{
    ZBPrestationsEntityIterator i( &m_EntitySet );

    for ( ZBPrestationsEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( ISA( pEnv, ZBLogicalPrestationsEntity ) )
        {
            // If correspond to the requested group name
            // return it
            if ( dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->GetEntityName() == Name )
            {
                return dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv );
            }

            // If the group has entity
            if ( Deeper && dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->ContainEntity() )
            {
                ZBLogicalPrestationsEntity* pGroup =
                    dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->_FindFirstPrestation( Name, Deeper );

                if ( pGroup )
                {
                    return pGroup;
                }
            }
        }
    }

    return NULL;
}

bool ZBLogicalPrestationsEntity::MovePrestation( ZBPrestationsEntity* pPrestation )
{
    // First, remove the entity from the old group
    ZBPrestationsEntity* pParent = pPrestation->GetParent();

    if ( pParent && ISA( pParent, ZBLogicalPrestationsEntity ) && ISA( pPrestation, ZBLogicalPrestationsEntity ) )
    {
        if ( !dynamic_cast<ZBLogicalPrestationsEntity*>( pParent )->RemovePrestationFromSet( dynamic_cast<ZBLogicalPrestationsEntity*>( pPrestation ) ) )
        {
            return false;
        }
    }

    // Then, add the entity to the new group
    AddPrestation( pPrestation );

    // Sets the new parent
    pPrestation->SetParent( this );

    return true;
}

bool ZBLogicalPrestationsEntity::PrestationExist( const CString Name, bool Deeper /*= false*/ )
{
    // Sets the iterator to the right entity set
    ZBPrestationsEntityIterator i( &m_EntitySet );

    for ( ZBPrestationsEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( ISA( pEnv, ZBLogicalPrestationsEntity ) )
        {
            // If correspond to the requested name
            if ( dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->GetEntityName() == Name )
            {
                return true;
            }

            // If the group has entity
            if ( Deeper && dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->ContainEntity() )
            {
                if ( dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->PrestationExist( Name, Deeper ) )
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool ZBLogicalPrestationsEntity::PrestationExist( const CString Name, const CString InPrestationName )
{
    ZBLogicalPrestationsEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if ( !InPrestationName.IsEmpty() )
    {
        pGroup = _FindFirstPrestation( InPrestationName );
    }

    // Call the function with the group pointer
    return PrestationExist( Name, pGroup );
}

bool ZBLogicalPrestationsEntity::PrestationExist( const CString Name, ZBLogicalPrestationsEntity* pInPrestation )
{
    if ( !pInPrestation )
    {
        pInPrestation = this;
    }

    return pInPrestation->PrestationExist( Name, false );
}

void ZBLogicalPrestationsEntity::RecalculateParent()
{
    // Sets the iterator to the right entity set
    ZBPrestationsEntityIterator i( &m_EntitySet );

    for ( ZBPrestationsEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        // Set the parent pointer
        pEnv->SetParent( this );

        // If we have a group entity,
        // and the group has entity
        // call the recalculate group function 
        if ( ISA( pEnv, ZBLogicalPrestationsEntity ) &&
             dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->ContainEntity() )
        {
            dynamic_cast<ZBLogicalPrestationsEntity*>( pEnv )->RecalculateParent();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBLogicalPrestationsEntity diagnostics

#ifdef _DEBUG
void ZBLogicalPrestationsEntity::AssertValid() const
{
    ZBPrestationsEntity::AssertValid();
}

void ZBLogicalPrestationsEntity::Dump( CDumpContext& dc ) const
{
    ZBPrestationsEntity::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBLogicalPrestationsEntity serialization

void ZBLogicalPrestationsEntity::Serialize ( CArchive& ar )
{
    ZBPrestationsEntity::Serialize( ar );

    // If something else to serialize, do it below
    if ( ar.IsStoring() )
    {
        // Write the elements
        ar << static_cast<int>( GetEntityCount() );

        for ( int nIdx = 0; nIdx < (int)GetEntityCount(); nIdx++ )
        {
            ZBPrestationsEntity* pEntity = GetEntityAt( nIdx );
            ar << pEntity;
        }
    }
    else
    {
        // Read the elements

        // Before reading elements, remove all
        RemoveAllPrestationsEntities();
        
        int nCount;
        ZBPrestationsEntity* pEntity;

        ar >> nCount;

        for ( int i=0; i<nCount; i++ )
        {
            ar >> pEntity;
            m_EntitySet.Add( pEntity );
            pEntity->SetParent( this );
        }
    }
}
