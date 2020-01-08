/****************************************************************************
 * ==> PSS_UserGroupEntity -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user group entity                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UserGroupEntity.h"

// processsoft
#include "PSS_UserRoleEntity.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
PSS_UserGroupEntity::IEntitySet PSS_UserGroupEntity::m_FindSet;
BOOL                            PSS_UserGroupEntity::m_Modified = FALSE;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_UserGroupEntity, PSS_UserEntity, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_UserGroupEntity
//---------------------------------------------------------------------------
PSS_UserGroupEntity::PSS_UserGroupEntity(const CString&  name,
                                         const CString&  description,
                                         const float     cost,
                                         PSS_UserEntity* pParent) :
    PSS_UserEntity(name, description, cost, pParent)
{}
//---------------------------------------------------------------------------
PSS_UserGroupEntity::PSS_UserGroupEntity(const PSS_UserGroupEntity& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity::~PSS_UserGroupEntity()
{
    RemoveAllUserEntities();
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity& PSS_UserGroupEntity::operator = (const PSS_UserGroupEntity& other)
{
    PSS_UserEntity::operator = ((const PSS_UserEntity&)other);

    IEntityIterator it(other.GetEntitySet());

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_UserEntity* pEntity = pEnv->Clone();
        pEntity->SetParent(this);
        m_EntitySet.Add(pEntity);
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserGroupEntity::Clone() const
{
    return new PSS_UserGroupEntity(*this);
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity* PSS_UserGroupEntity::AddGroup(const CString& name, const CString& description, const float cost)
{
    std::unique_ptr<PSS_UserGroupEntity> pNewGroup(new PSS_UserGroupEntity(name, description, cost, this));
    m_EntitySet.Add(pNewGroup.get());
    return pNewGroup.release();
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity* PSS_UserGroupEntity::AddGroup(const CString& name,
                                                   const CString& description,
                                                   const float    cost,
                                                   const CString& inGroupName)
{
    PSS_UserGroupEntity* pGroup = NULL;

    // locate the group name
    if (!inGroupName.IsEmpty())
        pGroup = FindFirstGroup(inGroupName);

    return AddGroup(name, description, cost, pGroup);
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity* PSS_UserGroupEntity::AddGroup(const CString&       name,
                                                   const CString&       description,
                                                   const float          cost,
                                                   PSS_UserGroupEntity* pInGroup)
{
    // if no group defined
    if (!pInGroup)
        pInGroup = this;

    return pInGroup->AddGroup(name, description, cost);
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::RemoveGroup(const CString& name, bool deeper)
{
    IEntitySet* pSet = FindGroup(name, deeper);

    if (pSet && pSet->GetSize() > 0)
        return RemoveGroups(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::RemoveGroup(const CString& name, const CString& inGroupName)
{
    IEntitySet* pSet = FindGroup(name, inGroupName);

    if (pSet && pSet->GetSize() > 0)
        return RemoveGroups(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::RemoveGroup(const CString& name, PSS_UserGroupEntity* pInGroup)
{
    IEntitySet* pSet = FindGroup(name, pInGroup);

    if (pSet && pSet->GetSize() > 0)
        return RemoveGroups(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::RemoveGroup(PSS_UserGroupEntity* pGroup)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_UserGroupEntity* pEntity = dynamic_cast<PSS_UserGroupEntity*>(pEnv);

        if (!pEntity)
            continue;

        if (pEntity == pGroup)
        {
            // free the memory
            delete pGroup;

            // remove the current element
            it.Remove();
            return true;
        }

        // continue to search recursively
        if (pEntity->ContainEntity())
            if (pEntity->RemoveGroup(pGroup))
                return true;
    }

    return false;
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserGroupEntity::FindGroupByGUID(const CString& guid, bool deeper)
{
    // check if the main group matches with the requested GUID to find, add it to the find set if yes
    if (GetGUID() == guid)
        return this;

    // search in the group itself
    return FindGroupByGUIDPvt(guid, deeper);
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity::IEntitySet* PSS_UserGroupEntity::FindGroup(const CString& name, bool deeper)
{
    m_FindSet.RemoveAll();

    // check if the main group matches with the name to find, add it to the find set if yes
    if (GetEntityName() == name)
        m_FindSet.Add(this);

    // search in the group itself
    FindGroupPvt(name, deeper);

    return &m_FindSet;
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity::IEntitySet* PSS_UserGroupEntity::FindGroup(const CString& name, const CString& inGroupName)
{
    PSS_UserGroupEntity* pGroup = NULL;

    // locate the group name
    if (!inGroupName.IsEmpty())
        pGroup = FindFirstGroup(inGroupName);

    return FindGroup(name, pGroup);
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity::IEntitySet* PSS_UserGroupEntity::FindGroup(const CString& name, PSS_UserGroupEntity* pInGroup)
{
    m_FindSet.RemoveAll();

    // check if the main group matches with the name to find, add it to the find set if yes
    if (GetEntityName() == name)
        m_FindSet.Add(this);

    // search in the group itself
    FindGroupPvt(name, pInGroup);
    return &m_FindSet;
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity* PSS_UserGroupEntity::FindFirstGroup(const CString& name, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_UserGroupEntity* pEntity = dynamic_cast<PSS_UserGroupEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matches with the group name to find, return it
        if (pEntity->GetEntityName() == name)
            return pEntity;

        // continue to search recursively
        if (deeper && pEntity->ContainEntity())
        {
            PSS_UserGroupEntity* pGroup = pEntity->FindFirstGroup(name, deeper);

            if (pGroup)
                return pGroup;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::GroupExist(const CString& name, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_UserGroupEntity* pEntity = dynamic_cast<PSS_UserGroupEntity*>(pEnv);

        if (pEntity)
        {
            // if matches with the name to find
            if (pEntity->GetEntityName() == name)
                return true;

            // continue to search recursively
            if (deeper && pEntity->ContainEntity())
                if (pEntity->GroupExist(name, deeper))
                    return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::GroupExist(const CString& name, const CString& inGroupName)
{
    PSS_UserGroupEntity* pGroup = NULL;

    // locate the group name
    if (!inGroupName.IsEmpty())
        pGroup = FindFirstGroup(inGroupName);

    return GroupExist(name, pGroup);
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::GroupExist(const CString& name, PSS_UserGroupEntity* pInGroup)
{
    if (!pInGroup)
        pInGroup = this;

    return pInGroup->GroupExist(name, false);
}
//---------------------------------------------------------------------------
std::size_t PSS_UserGroupEntity::FillGroupNameArray(CStringArray& nameArray)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        // add the name to the array
        nameArray.Add(pEnv->GetEntityName());

        PSS_UserGroupEntity* pEntity = dynamic_cast<PSS_UserGroupEntity*>(pEnv);

        // continue to search recursively
        if (pEntity && pEntity->ContainEntity())
            pEntity->FillGroupNameArray(nameArray);
    }

    return nameArray.GetSize();
}
//---------------------------------------------------------------------------
PSS_UserRoleEntity* PSS_UserGroupEntity::AddRole(const CString& name, const CString& description)
{
    std::unique_ptr<PSS_UserRoleEntity> pNewRole(new PSS_UserRoleEntity(name, description, this));
    m_EntitySet.Add(pNewRole.get());
    return pNewRole.release();
}
//---------------------------------------------------------------------------
PSS_UserRoleEntity* PSS_UserGroupEntity::AddRole(const CString& name, const CString& description, const CString& inGroupName)
{
    PSS_UserGroupEntity* pGroup = NULL;

    // locate the group name
    if (!inGroupName.IsEmpty())
        pGroup = FindFirstGroup(inGroupName);

    return AddRole(name, description, pGroup);
}
//---------------------------------------------------------------------------
PSS_UserRoleEntity* PSS_UserGroupEntity::AddRole(const CString& name, const CString& description, PSS_UserGroupEntity* pInGroup)
{
    if (!pInGroup)
        pInGroup = this;

    return pInGroup->AddRole(name, description);
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::RemoveRole(const CString& name)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_UserRoleEntity* pEntity = dynamic_cast<PSS_UserRoleEntity*>(pEnv);

        if (pEntity && pEntity->GetEntityName() == name)
        {
            // free the memory
            delete pEnv;

            // remove the current element
            it.Remove();

            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::RemoveRole(const CString& name, const CString& inGroupName)
{
    PSS_UserGroupEntity* pGroup = NULL;

    // locate the group name
    if (!inGroupName.IsEmpty())
        pGroup = FindFirstGroup(inGroupName);

    return RemoveRole(name, pGroup);
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::RemoveRole(const CString& name, PSS_UserGroupEntity* pInGroup)
{
    if (!pInGroup)
        pInGroup = this;

    return pInGroup->RemoveRole(name);
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::RemoveRole(PSS_UserRoleEntity* pRole)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_UserRoleEntity* pRoleEntity = dynamic_cast<PSS_UserRoleEntity*>(pEnv);

        if (pRoleEntity && pRoleEntity == pRole)
        {
            // free the memory
            delete pEnv;

            // remove the current element
            it.Remove();

            return true;
        }

        PSS_UserGroupEntity* pGroupEntity = dynamic_cast<PSS_UserGroupEntity*>(pEnv);

        // continue to search recursively
        if (pGroupEntity && pGroupEntity->ContainEntity())
            if (pGroupEntity->RemoveRole(pRole))
                return true;
    }

    return false;
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserGroupEntity::FindRoleByGUID(const CString& guid, bool deeper)
{
    // search in the group itself
    return FindRoleByGUIDPvt(guid, deeper);
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::ContainThisRole(const CString& name)
{
    // todo -cFeature -oJean: need to be implemented
    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::MoveEntity(PSS_UserEntity* pEntity)
{
    // remove the entity from the old group
    PSS_UserGroupEntity* pParent = dynamic_cast<PSS_UserGroupEntity*>(pEntity->GetParent());

    if (pParent && !pParent->RemoveEntityFromSet(pEntity))
        return false;

    // add the entity to the new group
    AddEntity(pEntity);

    // set the new parent
    pEntity->SetParent(this);

    return true;
}
//---------------------------------------------------------------------------
void PSS_UserGroupEntity::RemoveAllUserEntities()
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
        delete pEnv;

    m_EntitySet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_UserGroupEntity::Serialize(CArchive& ar)
{
    PSS_UserEntity::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << static_cast<int>(GetEntityCount());

        const int entityCount = GetEntityCount();

        for (int i = 0; i < entityCount; ++i)
        {
            PSS_UserEntity* pEntity = GetEntityAt(i);
            ar << pEntity;
        }
    }
    else
    {
        // before reading elements, remove all the previous ones
        RemoveAllUserEntities();

        int entityCount;
        ar >> entityCount;

        PSS_UserEntity* pEntity;

        // read the elements
        for (int i = 0; i < entityCount; ++i)
        {
            ar >> pEntity;
            m_EntitySet.Add(pEntity);
            pEntity->SetParent(this);
        }
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UserGroupEntity::AssertValid() const
    {
        PSS_UserEntity::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UserGroupEntity::Dump(CDumpContext& dc) const
    {
        PSS_UserEntity::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::RemoveEntityFromSet(PSS_UserEntity* pEntity)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
        if (pEnv == pEntity)
        {
            // remove the current element
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserGroupEntity::FindGroupByGUIDPvt(const CString& guid, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_UserGroupEntity* pEntity = dynamic_cast<PSS_UserGroupEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matches with the name to find, add it to the find set
        if (pEntity->GetGUID() == guid)
            return pEnv;

        // continue to search recursively
        if (deeper && pEntity->ContainEntity())
        {
            PSS_UserEntity* pFoundEnv = pEntity->FindGroupByGUIDPvt(guid, deeper);

            if (pFoundEnv)
                return pFoundEnv;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_UserGroupEntity::FindGroupPvt(const CString& name, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_UserGroupEntity* pEntity = dynamic_cast<PSS_UserGroupEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matching with the name to find, add it to the find set
        if (pEntity->GetEntityName() == name)
            m_FindSet.Add(pEnv);

        // continue to search recursively
        if (deeper && pEntity->ContainEntity())
            pEntity->FindGroupPvt(name, deeper);
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupEntity::FindGroupPvt(const CString& name, PSS_UserGroupEntity* pInGroup)
{
    if (!pInGroup)
        pInGroup = this;

    pInGroup->FindGroupPvt(name, false);
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity* PSS_UserGroupEntity::FindFirstGroup(const CString& name, PSS_UserGroupEntity* pInGroup)
{
    if (!pInGroup)
        pInGroup = this;

    return pInGroup->FindFirstGroup(name, false);
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::RemoveGroups(IEntitySet& set)
{
    bool result = false;

    if (set.GetSize() > 0)
    {
        result = true;

        // for each elements, check if a group exists and if it has a parent, then call the parent to remove the group
        const int count = set.GetSize();

        for (int i = 0; i < count; ++i)
        {
            PSS_UserGroupEntity* pEntity = dynamic_cast<PSS_UserGroupEntity*>(set.GetAt(i));

            if (pEntity)
            {
                PSS_UserGroupEntity* pParent = dynamic_cast<PSS_UserGroupEntity*>(pEntity->GetParent());

                // on error, set the result to false at least one time
                if (pParent && !pParent->RemoveGroup(pEntity))
                    result = false;
            }
        }
    }

    return result;
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserGroupEntity::FindRoleByGUIDPvt(const CString& guid, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_UserRoleEntity* pRoleEntity = dynamic_cast<PSS_UserRoleEntity*>(pEnv);

        if (pRoleEntity)
        {
            // if matches with the name to find, add it to the find set
            if (pRoleEntity->GetGUID() == guid)
                return pEnv;

            continue;
        }

        PSS_UserGroupEntity* pGroupEntity = dynamic_cast<PSS_UserGroupEntity*>(pEnv);

        if (!pGroupEntity)
            continue;

        // continue to search recursively
        if (deeper && pGroupEntity->ContainEntity())
        {
            PSS_UserEntity* pFoundEnv = pGroupEntity->FindRoleByGUIDPvt(guid, deeper);

            if (pFoundEnv)
                return pFoundEnv;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_UserGroupEntity::RecalculateParent()
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_UserEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        pEnv->SetParent(this);

        PSS_UserGroupEntity* pEntity = dynamic_cast<PSS_UserGroupEntity*>(pEnv);

        // continue to search recursively
        if (pEntity && pEntity->ContainEntity())
            pEntity->RecalculateParent();
    }
}
//---------------------------------------------------------------------------
