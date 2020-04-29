/****************************************************************************
 * ==> PSS_DistributionAttributes ------------------------------------------*
 ****************************************************************************
 * Description : Provides the distribution attributes                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DistributionAttributes.h"

// processsoft
#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_UserRoleEntity.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_DistributionRulesForRole, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DistributionRulesForRole
//---------------------------------------------------------------------------
PSS_DistributionRulesForRole::PSS_DistributionRulesForRole(const CString& roleGUID) :
    CObject(),
    m_RoleGUID(roleGUID)
{}
//---------------------------------------------------------------------------
PSS_DistributionRulesForRole::PSS_DistributionRulesForRole(const PSS_DistributionRulesForRole& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_DistributionRulesForRole::~PSS_DistributionRulesForRole()
{}
//---------------------------------------------------------------------------
PSS_DistributionRulesForRole& PSS_DistributionRulesForRole::operator = (const PSS_DistributionRulesForRole& other)
{
    m_RulesManager = other.m_RulesManager;
    m_RoleGUID     = other.m_RoleGUID;

    return *this;
}
//---------------------------------------------------------------------------
PSS_DistributionRulesForRole* PSS_DistributionRulesForRole::Dup() const
{
    return new PSS_DistributionRulesForRole(*this);
}
//---------------------------------------------------------------------------
void PSS_DistributionRulesForRole::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE("PSS_DistributionRulesForRole::Serialize - Start save\n");

        ar << m_RoleGUID;

        TRACE("PSS_DistributionRulesForRole::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_DistributionRulesForRole::Serialize - Start read\n");

        ar >> m_RoleGUID;

        TRACE("PSS_DistributionRulesForRole::Serialize - End read\n");
    }

    m_RulesManager.Serialize(ar);
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_DistributionAttribute, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DistributionAttribute
//---------------------------------------------------------------------------
PSS_DistributionAttribute::PSS_DistributionAttribute() :
    CObject(),
    m_CategoryID(0),
    m_ItemID(0),
    m_SymbolRef(0)
{}
//---------------------------------------------------------------------------
PSS_DistributionAttribute::PSS_DistributionAttribute(const PSS_DistributionAttribute& other) :
    CObject(),
    m_CategoryID(0),
    m_ItemID(0),
    m_SymbolRef(0)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_DistributionAttribute::~PSS_DistributionAttribute()
{}
//---------------------------------------------------------------------------
PSS_DistributionAttribute& PSS_DistributionAttribute::operator = (const PSS_DistributionAttribute& other)
{
    m_UserGroupGUID = other.m_UserGroupGUID;
    m_CategoryID    = other.m_CategoryID;
    m_ItemID        = other.m_ItemID;
    m_SymbolRef     = other.m_SymbolRef;

    IDistributionRulesForRoleIterator it(&other.m_Set);

    for (PSS_DistributionRulesForRole* pRulesForRole = it.GetFirst(); pRulesForRole; pRulesForRole = it.GetNext())
        AddDistributionRulesForRole(pRulesForRole->Dup());

    return *this;
}
//---------------------------------------------------------------------------
PSS_DistributionAttribute* PSS_DistributionAttribute::Dup() const
{
    return new PSS_DistributionAttribute(*this);
}
//---------------------------------------------------------------------------
void PSS_DistributionAttribute::AddDistributionRulesForRole(const CString& roleGUID)
{
    PSS_DistributionRulesForRole* pRole = FindDistributionRulesForRole(roleGUID);

    if (!pRole)
    {
        std::unique_ptr<PSS_DistributionRulesForRole> pRole(new PSS_DistributionRulesForRole(roleGUID));
        AddDistributionRulesForRole(pRole.get());
        pRole.release();
    }
}
//---------------------------------------------------------------------------
void PSS_DistributionAttribute::AddDistributionRulesForRole(const CString& roleGUID,
                                                            int            ruleOp,
                                                            const CString& value,
                                                            int            logicalOperator)
{
    PSS_DistributionRulesForRole* pRole = FindDistributionRulesForRole(roleGUID);

    if (!pRole)
    {
        std::unique_ptr<PSS_DistributionRulesForRole> pNewRole(new PSS_DistributionRulesForRole(roleGUID));
        AddDistributionRulesForRole(pNewRole.get());
        pRole = pNewRole.release();
    }

    PSS_Assert(pRole);
    pRole->AddDistributionRule(ruleOp, value, logicalOperator);
}
//---------------------------------------------------------------------------
void PSS_DistributionAttribute::AddDistributionRulesForRole(PSS_DistributionRulesForRole* pDistributionRulesForRole)
{
    if (!pDistributionRulesForRole)
        return;

    m_Set.Add(pDistributionRulesForRole);
}
//---------------------------------------------------------------------------
void PSS_DistributionAttribute::DeleteAllDistributionRulesForAllRoles()
{
    IDistributionRulesForRoleIterator it(&m_Set);

    for (PSS_DistributionRulesForRole* pRulesForRole = it.GetFirst(); pRulesForRole; pRulesForRole = it.GetNext())
        delete pRulesForRole;

    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_DistributionAttribute::DeleteAllDistributionRulesForRole(const CString& roleGUID)
{
    IDistributionRulesForRoleIterator it(&m_Set);

    for (PSS_DistributionRulesForRole* pRulesForRole = it.GetFirst(); pRulesForRole; pRulesForRole = it.GetNext())
        if (pRulesForRole->GetRoleGUID() == roleGUID)
        {
            delete pRulesForRole;
            it.Remove();

            // go back by one to avoid skipping elements
            it.GetPrev();
        }
}
//---------------------------------------------------------------------------
bool PSS_DistributionAttribute::DeleteDistributionRulesForRole(PSS_DistributionRulesForRole* pDistributionRulesForRole)
{
    IDistributionRulesForRoleIterator it(&m_Set);

    for (PSS_DistributionRulesForRole* pRulesForRole = it.GetFirst(); pRulesForRole; pRulesForRole = it.GetNext())
        if (pRulesForRole == pDistributionRulesForRole)
        {
            delete pRulesForRole;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_DistributionAttribute::DeleteDistributionRule(PSS_DistributionRule* pRule)
{
    if (!pRule)
        return false;

    IDistributionRulesForRoleIterator it(&m_Set);

    for (PSS_DistributionRulesForRole* pRulesForRole = it.GetFirst(); pRulesForRole; pRulesForRole = it.GetNext())
        if (pRulesForRole->Exist(pRule))
            return pRulesForRole->DeleteDistributionRule(pRule);

    return false;
}
//---------------------------------------------------------------------------
PSS_DistributionRulesForRole* PSS_DistributionAttribute::FindDistributionRulesForRole(const CString& roleGUID) const
{
    IDistributionRulesForRoleIterator it(&m_Set);

    for (PSS_DistributionRulesForRole* pRulesForRole = it.GetFirst(); pRulesForRole; pRulesForRole = it.GetNext())
        if (pRulesForRole->GetRoleGUID() == roleGUID)
            return pRulesForRole;

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_DistributionAttribute::Exist(PSS_DistributionRulesForRole* pDistributionRulesForRole) const
{
    if (!pDistributionRulesForRole)
        return NULL;

    IDistributionRulesForRoleIterator it(&m_Set);

    for (PSS_DistributionRulesForRole* pRulesForRole = it.GetFirst(); pRulesForRole; pRulesForRole = it.GetNext())
        if (pRulesForRole == pDistributionRulesForRole)
            return true;

    return false;
}
//---------------------------------------------------------------------------
bool PSS_DistributionAttribute::ExistDistributionRule(PSS_DistributionRule* pRule) const
{
    IDistributionRulesForRoleIterator it(&m_Set);

    for (PSS_DistributionRulesForRole* pRulesForRole = it.GetFirst(); pRulesForRole; pRulesForRole = it.GetNext())
        if (pRulesForRole->Exist(pRule))
            return true;

    return false;
}
//---------------------------------------------------------------------------
PSS_DistributionRuleManager::IDistributionRuleset* PSS_DistributionAttribute::GetDistributionRuleset(const CString& roleGUID)
{
    PSS_DistributionRulesForRole* pRole = FindDistributionRulesForRole(roleGUID);
    return (pRole ? &pRole->GetDistributionRuleset() : NULL);
}
//---------------------------------------------------------------------------
PSS_DistributionRule* PSS_DistributionAttribute::GetDistributionRuleAt(const CString& roleGUID, std::size_t index)
{
    PSS_DistributionRulesForRole* pRole = FindDistributionRulesForRole(roleGUID);
    return (pRole ? pRole->GetDistributionRuleAt(index) : NULL);
}
//---------------------------------------------------------------------------
std::size_t PSS_DistributionAttribute::GetDistributionRuleCount(const CString& roleGUID) const
{
    PSS_DistributionRulesForRole* pRole = FindDistributionRulesForRole(roleGUID);
    return (pRole ? pRole->GetDistributionRuleCount() : 0);
}
//---------------------------------------------------------------------------
void PSS_DistributionAttribute::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE("PSS_DistributionAttribute::Serialize - Start save\n");

        ar << m_CategoryID;
        ar << m_ItemID;
        ar << m_SymbolRef;
        ar << m_UserGroupGUID;

        // serialize the size
        ar << m_Set.GetSize();

        IDistributionRulesForRoleIterator it(&m_Set);

        for (PSS_DistributionRulesForRole* pRulesForRole = it.GetFirst(); pRulesForRole; pRulesForRole = it.GetNext())
            ar << pRulesForRole;

        TRACE("PSS_DistributionAttribute::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_DistributionAttribute::Serialize - Start read\n");

        ar >> m_CategoryID;
        ar >> m_ItemID;
        ar >> m_SymbolRef;
        ar >> m_UserGroupGUID;

        int size;
        ar >> size;

        PSS_DistributionRulesForRole* pRulesForRole;

        for (int i = 0; i < size; ++i)
        {
            ar >> pRulesForRole;
            AddDistributionRulesForRole(pRulesForRole);
        }

        TRACE("PSS_DistributionAttribute::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_DistributionAttributeManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DistributionAttributeManager
//---------------------------------------------------------------------------
PSS_DistributionAttributeManager::PSS_DistributionAttributeManager() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_DistributionAttributeManager::PSS_DistributionAttributeManager(const PSS_DistributionAttributeManager& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_DistributionAttributeManager::~PSS_DistributionAttributeManager()
{
    FreePropertiesSet();
}
//---------------------------------------------------------------------------
PSS_DistributionAttributeManager& PSS_DistributionAttributeManager::operator = (const PSS_DistributionAttributeManager& other)
{
    IDistributionAttributeIterator it(&other.m_Set);

    for (PSS_DistributionAttribute* pDistribAttrib = it.GetFirst(); pDistribAttrib; pDistribAttrib = it.GetNext())
        AddDistributionAttribute(pDistribAttrib->Dup());

    return *this;
}
//---------------------------------------------------------------------------
PSS_DistributionAttributeManager* PSS_DistributionAttributeManager::Dup() const
{
    return new PSS_DistributionAttributeManager(*this);
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributeManager::FreePropertiesSet()
{
    IDistributionAttributeIterator it(&m_Set);

    for (PSS_DistributionAttribute* pDistribAttrib = it.GetFirst(); pDistribAttrib; pDistribAttrib = it.GetNext())
        delete pDistribAttrib;

    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributeManager::AddDistributionAttribute(PSS_DistributionAttribute* pDistributionAttribute,
                                                                bool                       replaceExisting)
{
    if (!pDistributionAttribute)
        return;

    if (!Exist(pDistributionAttribute))
        m_Set.Add(pDistributionAttribute);
    else
    if (replaceExisting)
    {
        ReplaceDistributionAttribute(pDistributionAttribute);

        PSS_DistributionAttribute* pOldAttribute = pDistributionAttribute;

        // don't forget to delete the object, since it's not assigned to the set,
        // and assign the pointer to the existing object
        pDistributionAttribute = FindDistributionAttribute(pDistributionAttribute->GetCategoryID(),
                                                           pDistributionAttribute->GetItemID(),
                                                           pDistributionAttribute->GetUserGroupGUID());

        delete pOldAttribute;
    }
}
//---------------------------------------------------------------------------
bool PSS_DistributionAttributeManager::DeleteDistributionAttribute(PSS_DistributionAttribute* pDistributionAttribute)
{
    IDistributionAttributeIterator it(&m_Set);

    for (PSS_DistributionAttribute* pDistribAttrib = it.GetFirst(); pDistribAttrib; pDistribAttrib = it.GetNext())
        if (pDistribAttrib == pDistributionAttribute)
        {
            delete pDistribAttrib;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
PSS_DistributionAttribute* PSS_DistributionAttributeManager::FindDistributionAttribute(int            categoryID,
                                                                                       int            itemID,
                                                                                       const CString& userGroupGUID)
{
    IDistributionAttributeIterator it(&m_Set);

    for (PSS_DistributionAttribute* pDistribAttrib = it.GetFirst(); pDistribAttrib; pDistribAttrib = it.GetNext())
        if (categoryID    == pDistribAttrib->GetCategoryID() &&
            itemID        == pDistribAttrib->GetItemID()     &&
            userGroupGUID == pDistribAttrib->GetUserGroupGUID())
            return pDistribAttrib;

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_DistributionAttributeManager::Exist(PSS_DistributionAttribute* pDistributionAttribute)
{
    if (!pDistributionAttribute)
        return false;

    return FindDistributionAttribute(pDistributionAttribute->GetCategoryID(),
                                     pDistributionAttribute->GetItemID(),
                                     pDistributionAttribute->GetUserGroupGUID());
}
//---------------------------------------------------------------------------
bool PSS_DistributionAttributeManager::DeleteDistributionRule(PSS_DistributionRule* pRule)
{
    IDistributionAttributeIterator it(&m_Set);

    for (PSS_DistributionAttribute* pDistribAttrib = it.GetFirst(); pDistribAttrib; pDistribAttrib = it.GetNext())
        if (pDistribAttrib->ExistDistributionRule(pRule))
            return pDistribAttrib->DeleteDistributionRule(pRule);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_DistributionAttributeManager::CheckDistributionRole(PSS_DistributionAttribute* pDistributionAttribute,
                                                             PSS_UserGroupEntity*       pMainUserGroup)
{
    // check if the distribution attribute exists and if a main user group is defined
    if (!pDistributionAttribute || !pMainUserGroup)
        return false;

    PSS_UserGroupEntity* pEntity =
            dynamic_cast<PSS_UserGroupEntity*>(pMainUserGroup->FindGroupByGUID(pDistributionAttribute->GetUserGroupGUID(), true));

    if (!pEntity)
        return false;

    // check a role against the rule only if the distribution attribute is already defined in the manager
    if (Exist(pDistributionAttribute))
    {
        // check if the distribution rules defined match the role defined in the group
        const std::size_t size = pDistributionAttribute->GetDistributionRulesForRoleCount();

        for (int i = 0; i < size; ++i)
        {
            PSS_DistributionRulesForRole* pRole = pDistributionAttribute->GetDistributionRulesForRoleAt(i);

            if (!pRole)
                continue;

            // if the role was not found in the group hierarchy, delete it
            if (!pEntity->FindRoleByGUID(pRole->GetRoleGUID(), false))
            {
                pDistributionAttribute->DeleteDistributionRulesForRoleAt(i);
                --i;
            }
        }
    }

    const std::size_t size = pEntity->GetEntityCount();

    // iterate through the roles and check if exists for this distribution attribute
    for (int i = 0; i < size; ++i)
    {
        PSS_UserEntity* pRole = pEntity->GetEntityAt(i);

        // if no distribution rule exist for this role, create an empty one
        if (pRole && ISA(pRole, PSS_UserRoleEntity))
            if (!pDistributionAttribute->Exist(pRole->GetGUID()))
                pDistributionAttribute->AddDistributionRulesForRole(pRole->GetGUID());
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributeManager::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE("PSS_DistributionAttributeManager::Serialize - Start save\n");

        // serialize the size
        ar << int(m_Set.GetSize());

        IDistributionAttributeIterator it(&m_Set);

        for (PSS_DistributionAttribute* pDistribAttrib = it.GetFirst(); pDistribAttrib; pDistribAttrib = it.GetNext())
            ar << pDistribAttrib;

        TRACE("PSS_DistributionAttributeManager::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_DistributionAttributeManager::Serialize - Start read\n");

        int size;
        ar >> size;

        PSS_DistributionAttribute* pDistribAttrib;

        for (int i = 0; i < int(size); ++i)
        {
            ar >> pDistribAttrib;
            AddDistributionAttribute(pDistribAttrib);
        }

        TRACE("PSS_DistributionAttributeManager::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributeManager::ReplaceDistributionAttribute(PSS_DistributionAttribute* pDistributionAttribute)
{
    PSS_DistributionAttribute* pAttr = FindDistributionAttribute(pDistributionAttribute->GetCategoryID(),
                                                                 pDistributionAttribute->GetItemID(),
                                                                 pDistributionAttribute->GetUserGroupGUID());

    if (pAttr)
        *pAttr = *pDistributionAttribute;
}
//---------------------------------------------------------------------------
