// ******************************************************************************************************************
// *                                        Classe ZDLogicalRulesEntity                                                *
// ******************************************************************************************************************
// * JMR-MODIF - Le 14 novembre 2006 - Ajout de la classe ZDLogicalRulesEntity.                                        *
// ******************************************************************************************************************
// * Cette classe représente une entité de type règle.    Une entité peut être considérée comme un élément du            *
// * document.                                                                                                        *
// ******************************************************************************************************************

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "stdafx.h"
#include "ZBLogicalRulesEntity.h"

//////////////////////////////////////////////////////////////////////
// Static variables

ZBRulesEntitySet    ZBLogicalRulesEntity::m_FindSet;

BOOL                ZBLogicalRulesEntity::m_bModified = FALSE;

IMPLEMENT_SERIAL( ZBLogicalRulesEntity, ZBRulesEntity, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBLogicalRulesEntity::ZBLogicalRulesEntity( const CString    Name        /*= _T( "" )*/,
                                            const CString    Description    /*= _T( "" )*/,
                                            ZBRulesEntity*    pParent        /*= NULL*/ )
    : ZBRulesEntity( Name, Description, pParent )
{
}

ZBLogicalRulesEntity::~ZBLogicalRulesEntity()
{
    RemoveAllRulesEntities();
}

void ZBLogicalRulesEntity::RemoveAllRulesEntities()
{
    // Sets the iterator to the right entity set
    ZBRulesEntityIterator i( &m_EntitySet );

    for ( ZBRulesEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        delete pEnv;
    }

    m_EntitySet.RemoveAll();
}

////////////////////////////////////////////////////////////////
// Group management functions

ZBLogicalRulesEntity* ZBLogicalRulesEntity::AddRule( const CString Name,
                                                     const CString Description,
                                                     const CString InRuleName )
{
    ZBLogicalRulesEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if ( !InRuleName.IsEmpty() )
    {
        pGroup = _FindFirstRule( InRuleName );
    }

    // Call the AddRule function with the pGroup pointer passed has parameter
    return AddRule( Name, Description, pGroup );
}

ZBLogicalRulesEntity* ZBLogicalRulesEntity::AddRule( const CString            Name,
                                                     const CString            Description,
                                                     ZBLogicalRulesEntity*    pInRule )
{
    // If no group defined
    if ( !pInRule )
    {
        pInRule = this;
    }

    return pInRule->AddRule( Name, Description );
}

ZBLogicalRulesEntity* ZBLogicalRulesEntity::AddRule( const CString Name,
                                                     const CString Description )
{
    ZBLogicalRulesEntity* pNewGroup = new ZBLogicalRulesEntity( Name, Description, this );
    m_EntitySet.Add( pNewGroup );

    return pNewGroup;
}

bool ZBLogicalRulesEntity::RemoveRule( const CString Name, bool Deeper /*= false*/ )
{
    ZBRulesEntitySet* pSet = FindRule( Name, Deeper );

    if ( pSet && pSet->GetSize() > 0 )
    {
        return _RemoveRules( *pSet );
    }

    return false;
}
bool ZBLogicalRulesEntity::RemoveRule( const CString Name, const CString InRuleName )
{
    ZBRulesEntitySet* pSet = FindRule( Name, InRuleName );

    if ( pSet && pSet->GetSize() > 0 )
    {
        return _RemoveRules( *pSet );
    }

    return false;
}
bool ZBLogicalRulesEntity::RemoveRule( const CString Name, ZBLogicalRulesEntity* pInRule )
{
    ZBRulesEntitySet* pSet = FindRule( Name, pInRule );

    if ( pSet && pSet->GetSize() > 0 )
    {
        return _RemoveRules( *pSet );
    }

    return false;
}
bool ZBLogicalRulesEntity::RemoveRule( ZBLogicalRulesEntity* pRule )
{
    // Sets the iterator to the right entity set
    ZBRulesEntityIterator i( &m_EntitySet );

    for ( ZBRulesEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( pEnv == pRule && ISA( pEnv, ZBLogicalRulesEntity ) )
        {
            // Free the memory
            delete pRule;

            // Remove the current element
            i.Remove();
            return true;
        }

        // If we have a group entity,
        // and the group has entity
        // call the recalculate group function 
        if ( ISA( pEnv, ZBLogicalRulesEntity ) &&
             dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->ContainEntity() )
        {
            if ( dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->RemoveRule( pRule ) )
            {
                return true;
            }
        }
    }

    return false;
}

bool ZBLogicalRulesEntity::_RemoveRules( ZBRulesEntitySet& Set )
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
                 ISA( Set.GetAt( i ), ZBLogicalRulesEntity ) &&
                 dynamic_cast<ZBLogicalRulesEntity*>( Set.GetAt( i ) )->GetParent() != NULL )
            {
                ZBLogicalRulesEntity* pGroup = dynamic_cast<ZBLogicalRulesEntity*>( Set.GetAt( i ) );

                // If problem sets to false at least one time
                if ( !dynamic_cast<ZBLogicalRulesEntity*>( pGroup->GetParent() )->RemoveRule( pGroup ) )
                {
                    RetValue = false;
                }
            }
        }
    }

    return RetValue;
}

bool ZBLogicalRulesEntity::RemoveRuleFromSet( ZBRulesEntity* pRule )
{
    // Sets the iterator to the right entity set
    ZBRulesEntityIterator i( &m_EntitySet );

    for ( ZBRulesEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( pEnv == pRule )
        {
            // Remove the current element
            i.Remove();
            return true;
        }
    }

    return false;
}

ZBRulesEntity* ZBLogicalRulesEntity::FindRuleByGUID( const CString GUID, bool Deeper /*= false*/ )
{
    // First, check if the main group correspond to the requested GUID
    // add it to the find set
    if ( GetGUID() == GUID )
    {
        return this;
    }

    // Then search in the group itself
    return _FindRuleByGUID( GUID, Deeper );
}

ZBRulesEntitySet* ZBLogicalRulesEntity::FindRule( const CString Name, bool Deeper /*= false*/ )
{
    m_FindSet.RemoveAll();

    // First, check if the main group correspond to the requested name
    // add it to the find set
    if ( GetEntityName() == Name )
    {
        m_FindSet.Add( this );
    }

    // Then search in the group itself
    _FindRule( Name, Deeper );

    return &m_FindSet;
}

ZBRulesEntitySet* ZBLogicalRulesEntity::FindRule( const CString Name,
                                                  const CString InRuleName )
{
    ZBLogicalRulesEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if ( !InRuleName.IsEmpty() )
    {
        pGroup = _FindFirstRule( InRuleName );
    }

    // Call the FindRule function with the pGroup pointer passed has parameter
    return FindRule( Name, pGroup );
}

ZBRulesEntitySet* ZBLogicalRulesEntity::FindRule( const CString            Name,
                                                  ZBLogicalRulesEntity*    pInRule )
{
    m_FindSet.RemoveAll();

    // First, check if the main group correspond to the requested name
    // add it to the find set
    if ( GetEntityName() == Name )
    {
        m_FindSet.Add( this );
    }

    // Then search in the group itself
    _FindRule( Name, pInRule );

    return &m_FindSet;
}

void ZBLogicalRulesEntity::_FindRule( const CString Name, ZBLogicalRulesEntity* pInRule )
{
    if ( !pInRule )
    {
        pInRule = this;
    }

    pInRule->_FindRule( Name, false );
}

// The _FindRuleByGUID function will search all groups corresponding to the GUID passed as parameter
ZBRulesEntity* ZBLogicalRulesEntity::_FindRuleByGUID( const CString    GUID,
                                                      bool            Deeper    /*= false*/ )
{
    // Sets the iterator to the right entity set
    ZBRulesEntityIterator i( &m_EntitySet );

    for ( ZBRulesEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( ISA( pEnv, ZBLogicalRulesEntity ) )
        {
            // If correspond to the requested name
            // add it to the find set
            if ( dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->GetGUID() == GUID )
            {
                return pEnv;
            }

            // If the group has entity
            // call the group's function 
            if ( Deeper && dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->ContainEntity() )
            {
                ZBRulesEntity* pFoundEnv =
                    dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->_FindRuleByGUID( GUID, Deeper );

                if ( pFoundEnv )
                {
                    return pFoundEnv;
                }
            }
        }
    }

    return NULL;
}

// The _FindRule function will search all groups corresponding to the name passed as parameter
// The function will fill the m_FindSet static variable with elements found
void ZBLogicalRulesEntity::_FindRule( const CString Name, bool Deeper /*= false*/ )
{
    // Sets the iterator to the right entity set
    ZBRulesEntityIterator i( &m_EntitySet );

    for ( ZBRulesEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( ISA( pEnv, ZBLogicalRulesEntity ) )
        {
            // If correspond to the requested name
            // add it to the find set
            if ( dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->GetEntityName() == Name )
            {
                m_FindSet.Add( pEnv );
            }

            // If the group has entity
            // call the group's function 
            if ( Deeper && dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->ContainEntity() )
            {
                dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->_FindRule( Name, Deeper );
            }
        }
    }
}

ZBLogicalRulesEntity* ZBLogicalRulesEntity::_FindFirstRule( const CString            Name,
                                                            ZBLogicalRulesEntity*    pInRule )
{
    if ( !pInRule )
    {
        pInRule = this;
    }

    return pInRule->_FindFirstRule( Name, false );
}

ZBLogicalRulesEntity* ZBLogicalRulesEntity::_FindFirstRule( const CString    Name,
                                                            bool            Deeper    /*= false*/ )
{
    ZBRulesEntityIterator i( &m_EntitySet );

    for ( ZBRulesEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( ISA( pEnv, ZBLogicalRulesEntity ) )
        {
            // If correspond to the requested group name
            // return it
            if ( dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->GetEntityName() == Name )
            {
                return dynamic_cast<ZBLogicalRulesEntity*>( pEnv );
            }

            // If the group has entity
            if ( Deeper && dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->ContainEntity() )
            {
                ZBLogicalRulesEntity* pGroup =
                    dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->_FindFirstRule( Name, Deeper );

                if ( pGroup )
                {
                    return pGroup;
                }
            }
        }
    }

    return NULL;
}

bool ZBLogicalRulesEntity::MoveRule( ZBRulesEntity* pRule )
{
    // First, remove the entity from the old group
    ZBRulesEntity* pParent = pRule->GetParent();

    if ( pParent && ISA( pParent, ZBLogicalRulesEntity ) && ISA( pRule, ZBLogicalRulesEntity ) )
    {
        if ( !dynamic_cast<ZBLogicalRulesEntity*>( pParent )->RemoveRuleFromSet( dynamic_cast<ZBLogicalRulesEntity*>( pRule ) ) )
        {
            return false;
        }
    }

    // Then, add the entity to the new group
    AddRule( pRule );

    // Sets the new parent
    pRule->SetParent( this );

    return true;
}

bool ZBLogicalRulesEntity::RuleExist( const CString Name, bool Deeper /*= false*/ )
{
    // Sets the iterator to the right entity set
    ZBRulesEntityIterator i( &m_EntitySet );

    for ( ZBRulesEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        if ( ISA( pEnv, ZBLogicalRulesEntity ) )
        {
            // If correspond to the requested name
            if ( dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->GetEntityName() == Name )
            {
                return true;
            }

            // If the group has entity
            if ( Deeper && dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->ContainEntity() )
            {
                if ( dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->RuleExist( Name, Deeper ) )
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool ZBLogicalRulesEntity::RuleExist( const CString Name, const CString InRuleName )
{
    ZBLogicalRulesEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if ( !InRuleName.IsEmpty() )
    {
        pGroup = _FindFirstRule( InRuleName );
    }

    // Call the function with the group pointer
    return RuleExist( Name, pGroup );
}

bool ZBLogicalRulesEntity::RuleExist( const CString Name, ZBLogicalRulesEntity* pInRule )
{
    if ( !pInRule )
    {
        pInRule = this;
    }

    return pInRule->RuleExist( Name, false );
}

void ZBLogicalRulesEntity::RecalculateParent()
{
    // Sets the iterator to the right entity set
    ZBRulesEntityIterator i( &m_EntitySet );

    for ( ZBRulesEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext() )
    {
        // Set the parent pointer
        pEnv->SetParent( this );

        // If we have a group entity,
        // and the group has entity
        // call the recalculate group function 
        if ( ISA( pEnv, ZBLogicalRulesEntity ) &&
             dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->ContainEntity() )
        {
            dynamic_cast<ZBLogicalRulesEntity*>( pEnv )->RecalculateParent();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBLogicalRulesEntity diagnostics

#ifdef _DEBUG
void ZBLogicalRulesEntity::AssertValid() const
{
    ZBRulesEntity::AssertValid();
}

void ZBLogicalRulesEntity::Dump( CDumpContext& dc ) const
{
    ZBRulesEntity::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBLogicalRulesEntity serialization

void ZBLogicalRulesEntity::Serialize ( CArchive& ar )
{
    ZBRulesEntity::Serialize( ar );
    
    // If something else to serialize, do it below
    if ( ar.IsStoring() )
    {
        // Write the elements
        ar << static_cast<int>( GetEntityCount() );

        for ( int nIdx = 0; nIdx < (int)GetEntityCount(); nIdx++ )
        {
            ZBRulesEntity* pEntity = GetEntityAt( nIdx );
            ar << pEntity;
        }
    }
    else
    {
        // Read the elements

        // Before reading elements, remove all
        RemoveAllRulesEntities();
        
        int nCount;
        ZBRulesEntity* pEntity;

        ar >> nCount;

        for ( int i = 0; i < nCount; i++ )
        {
            ar >> pEntity;
            m_EntitySet.Add( pEntity );
            pEntity->SetParent( this );
        }
    }
}
