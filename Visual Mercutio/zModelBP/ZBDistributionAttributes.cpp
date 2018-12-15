// ZBDistributionAttributes.cpp: implementation of the ZBDistributionAttribute class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBDistributionAttributes.h"

#include "zModel\ZBUserGroupEntity.h"
#include "zModel\ZBUserRoleEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// ZBDistributionRulesForRole class implementation

IMPLEMENT_SERIAL( ZBDistributionRulesForRole, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBDistributionRulesForRole::ZBDistributionRulesForRole( CString RoleGUID /*= ""*/ )
    : m_RoleGUID( RoleGUID )
{
}

ZBDistributionRulesForRole::~ZBDistributionRulesForRole()
{
}

ZBDistributionRulesForRole::ZBDistributionRulesForRole( const ZBDistributionRulesForRole& src )
{
    *this = src;
}

ZBDistributionRulesForRole& ZBDistributionRulesForRole::operator=( const ZBDistributionRulesForRole& src )
{
    m_RoleGUID        = src.m_RoleGUID;
    m_RulesManager    = src.m_RulesManager;

    return *this;
}

ZBDistributionRulesForRole* ZBDistributionRulesForRole::Dup() const
{
    return ( new ZBDistributionRulesForRole( *this ) );
}

void ZBDistributionRulesForRole::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        TRACE( "ZBDistributionRulesForRole::Serialize : Start Save\n" );

        ar << m_RoleGUID;

        TRACE( "ZBDistributionRulesForRole::Serialize : End Save\n" );
    }
    else
    {
        TRACE( "ZBDistributionRulesForRole::Serialize : Start Read\n" );

        ar >> m_RoleGUID;

        TRACE( "ZBDistributionRulesForRole::Serialize : End Read\n" );
    }

    m_RulesManager.Serialize( ar );
}

//////////////////////////////////////////////////////////////////////
// ZBDistributionAttribute class implementation

IMPLEMENT_SERIAL( ZBDistributionAttribute, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBDistributionAttribute::ZBDistributionAttribute()
{
}

ZBDistributionAttribute::~ZBDistributionAttribute()
{
}

ZBDistributionAttribute::ZBDistributionAttribute( const ZBDistributionAttribute& src )
{
    *this = src;
}

ZBDistributionAttribute& ZBDistributionAttribute::operator=( const ZBDistributionAttribute& src )
{
    m_CategoryID    = src.m_CategoryID;
    m_ItemID        = src.m_ItemID;
    m_SymbolRef        = src.m_SymbolRef;
    m_UserGroupGUID    = src.m_UserGroupGUID;

    ZBDistributionRulesForRoleIterator i( &src.m_Set );

    for ( ZBDistributionRulesForRole* pRulesForRole = i.GetFirst(); pRulesForRole; pRulesForRole = i.GetNext() )
    {
        AddDistributionRulesForRole( pRulesForRole->Dup() );
    }

    return *this;
}

ZBDistributionAttribute* ZBDistributionAttribute::Dup() const
{
    return ( new ZBDistributionAttribute( *this ) );
}

void ZBDistributionAttribute::DeleteAllDistributionRulesForAllRoles()
{
    ZBDistributionRulesForRoleIterator i( &m_Set );

    for ( ZBDistributionRulesForRole* pRulesForRole = i.GetFirst(); pRulesForRole; pRulesForRole = i.GetNext() )
        delete pRulesForRole;

    m_Set.RemoveAll();
}

void ZBDistributionAttribute::DeleteAllDistributionRulesForRole( const CString RoleGUID )
{
    ZBDistributionRulesForRoleIterator i( &m_Set );

    for ( ZBDistributionRulesForRole* pRulesForRole = i.GetFirst(); pRulesForRole; pRulesForRole = i.GetNext() )
    {
        if ( pRulesForRole->GetRoleGUID() == RoleGUID )
        {
            delete pRulesForRole;
            i.Remove();

            // Go back to one, to avoid skipping elements
            i.GetPrev();
        }
    }
}

void ZBDistributionAttribute::AddDistributionRulesForRole( const CString RoleGUID )
{
    ZBDistributionRulesForRole* pRole = FindDistributionRulesForRole( RoleGUID );

    if ( !pRole )
    {
        pRole = new ZBDistributionRulesForRole( RoleGUID );
        AddDistributionRulesForRole( pRole );
    }
}

void ZBDistributionAttribute::AddDistributionRulesForRole( const CString    RoleGUID,
                                                           int                Operator,
                                                           CString            Value,
                                                           int                LogicalOperator /*= -1*/ )
{
    ZBDistributionRulesForRole* pRole = FindDistributionRulesForRole( RoleGUID );

    if ( !pRole )
    {
        pRole = new ZBDistributionRulesForRole( RoleGUID );
        AddDistributionRulesForRole( pRole );
    }

    ASSERT( pRole );
    pRole->AddDistributionRule( Operator, Value, LogicalOperator );
}

void ZBDistributionAttribute::AddDistributionRulesForRole( ZBDistributionRulesForRole* pDistributionRulesForRole )
{
    if ( !pDistributionRulesForRole )
        return;

    m_Set.Add( pDistributionRulesForRole );
}

ZBDistributionRulesForRole* ZBDistributionAttribute::FindDistributionRulesForRole( const CString RoleGUID )    const
{
    ZBDistributionRulesForRoleIterator i( &m_Set );

    for ( ZBDistributionRulesForRole* pRulesForRole = i.GetFirst(); pRulesForRole; pRulesForRole = i.GetNext() )
    {
        if ( pRulesForRole->GetRoleGUID() == RoleGUID )
            return pRulesForRole;
    }

    return NULL;
}

bool ZBDistributionAttribute::DeleteDistributionRulesForRole( ZBDistributionRulesForRole* pDistributionRulesForRole )
{
    ZBDistributionRulesForRoleIterator i( &m_Set );

    for ( ZBDistributionRulesForRole* pRulesForRole = i.GetFirst(); pRulesForRole; pRulesForRole = i.GetNext() )
    {
        if ( pRulesForRole == pDistributionRulesForRole )
        {
            delete pRulesForRole;
            i.Remove();
            return true;
        }
    }

    return false;
}

bool ZBDistributionAttribute::Exist( ZBDistributionRulesForRole* pDistributionRulesForRole ) const
{
    if ( !pDistributionRulesForRole )
        return NULL;

    ZBDistributionRulesForRoleIterator i( &m_Set );

    for ( ZBDistributionRulesForRole* pRulesForRole = i.GetFirst(); pRulesForRole; pRulesForRole = i.GetNext() )
    {
        if ( pRulesForRole == pDistributionRulesForRole )
            return true;
    }

    return false;
}

bool ZBDistributionAttribute::ExistDistributionRule( ZBDistributionRule* pRule )
{
    ZBDistributionRulesForRoleIterator i( &m_Set );

    for ( ZBDistributionRulesForRole* pRulesForRole = i.GetFirst(); pRulesForRole; pRulesForRole = i.GetNext() )
    {
        if ( pRulesForRole->Exist( pRule ) )
            return true;
    }

    return false;
}

bool ZBDistributionAttribute::DeleteDistributionRule( ZBDistributionRule* pRule )
{
    if ( !pRule )
        return false;

    ZBDistributionRulesForRoleIterator i( &m_Set );

    for ( ZBDistributionRulesForRole* pRulesForRole = i.GetFirst(); pRulesForRole; pRulesForRole = i.GetNext() )
    {
        if ( pRulesForRole->Exist( pRule ) )
            return pRulesForRole->DeleteDistributionRule( pRule );
    }

    return false;
}

ZBDistributionRuleSet* ZBDistributionAttribute::GetDistributionRuleSet( const CString RoleGUID )
{
    ZBDistributionRulesForRole* pRole = FindDistributionRulesForRole( RoleGUID );
    return ( pRole ) ? &pRole->GetDistributionRuleSet() : NULL;
}

ZBDistributionRule* ZBDistributionAttribute::GetDistributionRuleAt(  const CString RoleGUID, size_t Index )
{
    ZBDistributionRulesForRole* pRole = FindDistributionRulesForRole( RoleGUID );
    return ( pRole ) ? pRole->GetDistributionRuleAt( Index ) : NULL;
}

size_t ZBDistributionAttribute::GetDistributionRuleCount( const CString RoleGUID ) const
{
    ZBDistributionRulesForRole* pRole = FindDistributionRulesForRole( RoleGUID );
    return ( pRole ) ? pRole->GetDistributionRuleCount() : 0;
}

void ZBDistributionAttribute::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        TRACE( "ZBDistributionAttribute::Serialize : Start Save\n" );

        ar << m_CategoryID;
        ar << m_ItemID;
        ar << m_SymbolRef;
        ar << m_UserGroupGUID;

        // Serialize the size
        ar << m_Set.GetSize();

        ZBDistributionRulesForRoleIterator i( &m_Set );

        for ( ZBDistributionRulesForRole* pRulesForRole = i.GetFirst(); pRulesForRole; pRulesForRole = i.GetNext() )
        {        
            ar << pRulesForRole;
        }

        TRACE( "ZBDistributionAttribute::Serialize : End Save\n" );
    }
    else
    {
        TRACE( "ZBDistributionAttribute::Serialize : Start Read\n" );

        ar >> m_CategoryID;
        ar >> m_ItemID;
        ar >> m_SymbolRef;
        ar >> m_UserGroupGUID;

        int Size;
        ar >> Size;

        ZBDistributionRulesForRole* pRulesForRole;

        for ( int i = 0; i < Size; ++i )
        {
            ar >> pRulesForRole;
            AddDistributionRulesForRole( pRulesForRole );
        }

        TRACE( "ZBDistributionAttribute::Serialize : End Read\n" );
    }
}

//////////////////////////////////////////////////////////////////////
// ZBDistributionAttributeManager class implementation

IMPLEMENT_SERIAL( ZBDistributionAttributeManager, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBDistributionAttributeManager::ZBDistributionAttributeManager()
{
}

ZBDistributionAttributeManager::~ZBDistributionAttributeManager()
{
    FreePropertiesSet();
}

ZBDistributionAttributeManager::ZBDistributionAttributeManager( const ZBDistributionAttributeManager& src )
{
    *this = src;
}

ZBDistributionAttributeManager& ZBDistributionAttributeManager::operator=( const ZBDistributionAttributeManager& src )
{
    ZBDistributionAttributeIterator i(&src.m_Set);

    for ( ZBDistributionAttribute* pDistribAttrib = i.GetFirst(); pDistribAttrib; pDistribAttrib = i.GetNext() )
    {
        AddDistributionAttribute( pDistribAttrib->Dup() );
    }

    return *this;
}

ZBDistributionAttributeManager* ZBDistributionAttributeManager::Dup() const
{
    return ( new ZBDistributionAttributeManager( *this ) );
}

void ZBDistributionAttributeManager::FreePropertiesSet()
{
    ZBDistributionAttributeIterator i( &m_Set );

    for ( ZBDistributionAttribute* pDistribAttrib = i.GetFirst(); pDistribAttrib; pDistribAttrib = i.GetNext() )
        delete pDistribAttrib;

    m_Set.RemoveAll();
}

void ZBDistributionAttributeManager::AddDistributionAttribute( ZBDistributionAttribute*    pDistributionAttribute,
                                                               bool                        ReplaceExisting /*= true*/ )
{
    if ( !pDistributionAttribute )
        return;

    if ( !Exist( pDistributionAttribute ) )
        m_Set.Add( pDistributionAttribute );
    else
    if ( ReplaceExisting )
    {
        ReplaceDistributionAttribute( pDistributionAttribute );

        ZBDistributionAttribute* pOldAttribute = pDistributionAttribute;

        // and don't forget to delete the object,
        // since he is not assigned to our set
        // and set the pointer to the existing object
        pDistributionAttribute = FindDistributionAttribute( pDistributionAttribute->GetCategoryID(), 
                                                            pDistributionAttribute->GetItemID(),
                                                            pDistributionAttribute->GetUserGroupGUID() );

        delete pOldAttribute;
    }
}

bool ZBDistributionAttributeManager::DeleteDistributionAttribute( ZBDistributionAttribute* pDistributionAttribute )
{
    ZBDistributionAttributeIterator i( &m_Set );

    for ( ZBDistributionAttribute* pDistribAttrib = i.GetFirst(); pDistribAttrib; pDistribAttrib = i.GetNext() )
    {
        if ( pDistribAttrib == pDistributionAttribute )
        {
            delete pDistribAttrib;
            i.Remove();
            return true;
        }
    }

    return false;
}

ZBDistributionAttribute* ZBDistributionAttributeManager::FindDistributionAttribute( int        CategoryID,
                                                                                    int        ItemID,
                                                                                    CString    UserGroupGUID )
{
    ZBDistributionAttributeIterator i( &m_Set );

    for ( ZBDistributionAttribute* pDistribAttrib = i.GetFirst(); pDistribAttrib; pDistribAttrib = i.GetNext() )
    {
        if ( pDistribAttrib->GetCategoryID() == CategoryID &&
             pDistribAttrib->GetItemID() == ItemID &&
             pDistribAttrib->GetUserGroupGUID() == UserGroupGUID )
            return pDistribAttrib;
    }

    return NULL;
}

bool ZBDistributionAttributeManager::Exist( ZBDistributionAttribute* pDistributionAttribute )
{
    if ( !pDistributionAttribute )
        return false;

    return ( FindDistributionAttribute( pDistributionAttribute->GetCategoryID(), 
                                        pDistributionAttribute->GetItemID(), 
                                        pDistributionAttribute->GetUserGroupGUID()) != NULL ) ? true : false;
}

void ZBDistributionAttributeManager::ReplaceDistributionAttribute( ZBDistributionAttribute* pDistributionAttribute )
{
    ZBDistributionAttribute* pAttr = FindDistributionAttribute( pDistributionAttribute->GetCategoryID(), 
                                                                pDistributionAttribute->GetItemID(), 
                                                                pDistributionAttribute->GetUserGroupGUID() );

    if ( pAttr )
    {
        // Use assignment operator
        *pAttr = *pDistributionAttribute;
    }
}

bool ZBDistributionAttributeManager::DeleteDistributionRule( ZBDistributionRule* pRule )
{
    ZBDistributionAttributeIterator i( &m_Set );

    for ( ZBDistributionAttribute* pDistribAttrib = i.GetFirst(); pDistribAttrib; pDistribAttrib = i.GetNext() )
    {
        if ( pDistribAttrib->ExistDistributionRule( pRule ) )
            return pDistribAttrib->DeleteDistributionRule( pRule );
    }

    return false;
}

bool ZBDistributionAttributeManager::CheckDistributionRole( ZBDistributionAttribute*    pDistributionAttribute,
                                                            ZBUserGroupEntity*            pMainUserGroup )
{
    // Check if the distribution attribute exists
    // and a main usergroup defined
    if ( !pDistributionAttribute || !pMainUserGroup ) // || !Exist( pDistributionAttribute ) )
        return false;

    ZBUserEntity* pEntity = pMainUserGroup->FindGroupByGUID( pDistributionAttribute->GetUserGroupGUID(), true );

    if ( !pEntity || !ISA(pEntity,ZBUserGroupEntity) )
        return false;

    // Check role against rule only if the distribution attribute
    // is already defined in the manager
    if ( Exist( pDistributionAttribute ) )
    {
        // Check if the distribution rules defined match the role defined in the group
        size_t Size = pDistributionAttribute->GetDistributionRulesForRoleCount();

        for ( int i = 0; i < Size; ++i )
        {
            ZBDistributionRulesForRole* pRole = pDistributionAttribute->GetDistributionRulesForRoleAt( i );

            if ( !pRole )
                continue;

            // If the role is not found in the group hierarchy,
            // then delete it.
            if ( !dynamic_cast<ZBUserGroupEntity*>(pEntity)->FindRoleByGUID( pRole->GetRoleGUID(), false ) )
            {
                pDistributionAttribute->DeleteDistributionRulesForRoleAt( i );
                --i;
            }
        }
    }

    // Now run through roles and check if exists for this distribution attribute
    size_t Size = dynamic_cast<ZBUserGroupEntity*>( pEntity )->GetEntityCount();

    for ( int i = 0; i < Size; ++i )
    {
        ZBUserEntity* pRole = dynamic_cast<ZBUserGroupEntity*>( pEntity )->GetEntityAt( i );

        if ( pRole && ISA( pRole, ZBUserRoleEntity ) )
        {
            // If no distribution rule exist for
            // this role, then create an empty one
            if ( !pDistributionAttribute->Exist( pRole->GetGUID() ) )
            {
                pDistributionAttribute->AddDistributionRulesForRole( pRole->GetGUID() );
            }
        }
    }

    return true;
}

void ZBDistributionAttributeManager::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        TRACE( "ZBDistributionAttributeManager::Serialize : Start Save\n" );

        // JMR-MODIF - Le 7 septembre 2005 - Ajout de la conversion explicite de SEC_INT en int.
        // Serialize the size
        ar << (int)m_Set.GetSize();

        ZBDistributionAttributeIterator i( &m_Set );

        for ( ZBDistributionAttribute* pDistribAttrib = i.GetFirst(); pDistribAttrib; pDistribAttrib = i.GetNext() )
        {        
            ar << pDistribAttrib;
        }

        TRACE( "ZBDistributionAttributeManager::Serialize : End Save\n" );
    }
    else
    {
        TRACE( "ZBDistributionAttributeManager::Serialize : Start Read\n" );

        int Size;
        ar >> Size;

        ZBDistributionAttribute* pDistribAttrib;

        for ( int i = 0; i < (int)Size; ++i )
        {
            ar >> pDistribAttrib;
            AddDistributionAttribute( pDistribAttrib );
        }

        TRACE( "ZBDistributionAttributeManager::Serialize : End Read\n" );
    }
}
