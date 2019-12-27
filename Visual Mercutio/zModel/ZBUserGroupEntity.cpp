// ZBUserGroupEntity.cpp: implementation of the ZBUserGroupEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBUserGroupEntity.h"
#include "ZBUserRoleEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 7 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Static variables

ZBUserEntitySet ZBUserGroupEntity::m_FindSet;

BOOL            ZBUserGroupEntity::m_bModified = FALSE;

IMPLEMENT_SERIAL(ZBUserGroupEntity, PSS_UserEntity, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBUserGroupEntity::ZBUserGroupEntity(const CString    Name        /*= _T( "" )*/,
                                     const CString    Description    /*= _T( "" )*/,
                                     const float    Cost        /*= 0*/,
                                     PSS_UserEntity*    pParent        /*= NULL*/)
    : PSS_UserEntity(Name, Description, Cost, pParent)
{}

ZBUserGroupEntity::~ZBUserGroupEntity()
{
    RemoveAllUserEntities();
}

ZBUserGroupEntity::ZBUserGroupEntity(const ZBUserGroupEntity& src)
{
    *this = src;
}

ZBUserGroupEntity& ZBUserGroupEntity::operator=(const ZBUserGroupEntity& src)
{
    // Call the base class assignement operator
    PSS_UserEntity::operator=((const PSS_UserEntity&)src);

    // Sets the iterator to the right entity set
    ZBUserEntityIterator i(src.GetEntitySetConst());

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        // Clone the object
        PSS_UserEntity* pEntity = pEnv->Clone();

        // Set the parent pointer
        pEntity->SetParent(this);

        // Add it to the array
        m_EntitySet.Add(pEntity);
    }

    return *this;
}

PSS_UserEntity* ZBUserGroupEntity::Clone() const
{
    return new ZBUserGroupEntity(*this);
}

void ZBUserGroupEntity::RemoveAllUserEntities()
{
    // Sets the iterator to the right entity set
    ZBUserEntityIterator i(&m_EntitySet);

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        delete pEnv;
    }

    m_EntitySet.RemoveAll();
}

bool ZBUserGroupEntity::ContainThisRole(const CString Role)
{
    // Need to be implemented

    // Not found
    return false;
}

size_t ZBUserGroupEntity::FillGroupNameArray(CStringArray& NameArray)
{
    // Sets the iterator to the right entity set
    ZBUserEntityIterator i(&m_EntitySet);

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        // Add the name to the array
        NameArray.Add(pEnv->GetEntityName());

        // If we have a group entity,
        // and the group has entity
        // call the FillGroupNameArray group function 
        if (ISA(pEnv, ZBUserGroupEntity) && dynamic_cast<ZBUserGroupEntity*>(pEnv)->ContainEntity())
        {
            dynamic_cast<ZBUserGroupEntity*>(pEnv)->FillGroupNameArray(NameArray);
        }
    }

    return NameArray.GetSize();
}

////////////////////////////////////////////////////////////////
// Group management functions

ZBUserGroupEntity* ZBUserGroupEntity::AddGroup(const CString    Name,
                                               const CString    Description,
                                               const float        Cost,
                                               const CString    InGroupName)
{
    ZBUserGroupEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if (!InGroupName.IsEmpty())
    {
        pGroup = _FindFirstGroup(InGroupName);
    }

    // Call the AddGroup function with the pGroup pointer passed has parameter
    return AddGroup(Name, Description, Cost, pGroup);
}

ZBUserGroupEntity* ZBUserGroupEntity::AddGroup(const CString        Name,
                                               const CString        Description,
                                               const float            Cost,
                                               ZBUserGroupEntity*    pInGroup)
{
    // If no group defined
    if (!pInGroup)
    {
        pInGroup = this;
    }

    return pInGroup->AddGroup(Name, Description, Cost);
}

ZBUserGroupEntity* ZBUserGroupEntity::AddGroup(const CString Name, const CString Description, const float Cost)
{
    ZBUserGroupEntity* pNewGroup = new ZBUserGroupEntity(Name, Description, Cost, this);
    m_EntitySet.Add(pNewGroup);
    return pNewGroup;
}

bool ZBUserGroupEntity::MoveEntity(PSS_UserEntity* pEntity)
{
    // First, remove the entity from the old group
    PSS_UserEntity* pParent = pEntity->GetParent();

    if (pParent && ISA(pParent, ZBUserGroupEntity))
    {
        if (!dynamic_cast<ZBUserGroupEntity*>(pParent)->RemoveEntityFromSet(pEntity))
        {
            return false;
        }
    }

    // Then, add the entity to the new group
    AddEntity(pEntity);

    // Sets the new parent
    pEntity->SetParent(this);

    return true;
}

bool ZBUserGroupEntity::RemoveEntityFromSet(PSS_UserEntity* pEntity)
{
    // Sets the iterator to the right entity set
    ZBUserEntityIterator i(&m_EntitySet);

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        if (pEnv == pEntity)
        {
            // Remove the current element
            i.Remove();
            return true;
        }
    }

    return false;
}

bool ZBUserGroupEntity::RemoveGroup(const CString Name, bool Deeper /*= false*/)
{
    ZBUserEntitySet* pSet = FindGroup(Name, Deeper);

    if (pSet && pSet->GetSize() > 0)
    {
        return _RemoveGroups(*pSet);
    }

    return false;
}

bool ZBUserGroupEntity::RemoveGroup(const CString Name, const CString InGroupName)
{
    ZBUserEntitySet* pSet = FindGroup(Name, InGroupName);

    if (pSet && pSet->GetSize() > 0)
    {
        return _RemoveGroups(*pSet);
    }

    return false;
}
bool ZBUserGroupEntity::RemoveGroup(const CString Name, ZBUserGroupEntity* pInGroup)
{
    ZBUserEntitySet* pSet = FindGroup(Name, pInGroup);

    if (pSet && pSet->GetSize() > 0)
    {
        return _RemoveGroups(*pSet);
    }

    return false;
}

bool ZBUserGroupEntity::RemoveGroup(ZBUserGroupEntity* pGroup)
{
    // Sets the iterator to the right entity set
    ZBUserEntityIterator i(&m_EntitySet);

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        if (pEnv == pGroup && ISA(pEnv, ZBUserGroupEntity))
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
        if (ISA(pEnv, ZBUserGroupEntity) && dynamic_cast<ZBUserGroupEntity*>(pEnv)->ContainEntity())
        {
            if (dynamic_cast<ZBUserGroupEntity*>(pEnv)->RemoveGroup(pGroup))
            {
                return true;
            }
        }
    }

    return false;
}

bool ZBUserGroupEntity::_RemoveGroups(ZBUserEntitySet& Set)
{
    // Initialize to false
    bool RetValue = false;

    if (Set.GetSize() > 0)
    {
        // If elements, set to true
        RetValue = true;

        // For each elements,
        // check if a group and if he has a parent
        // then call the parent to remove the group
        int Count = Set.GetSize();

        for (int i = 0; i < Count; ++i)
        {
            if (Set.GetAt(i) &&
                ISA(Set.GetAt(i), ZBUserGroupEntity) &&
                dynamic_cast<ZBUserGroupEntity*>(Set.GetAt(i))->GetParent() != NULL)
            {
                ZBUserGroupEntity* pGroup = dynamic_cast<ZBUserGroupEntity*>(Set.GetAt(i));

                // If problem sets to false at least one time
                if (!dynamic_cast<ZBUserGroupEntity*>(pGroup->GetParent())->RemoveGroup(pGroup))
                {
                    RetValue = false;
                }
            }
        }
    }

    return RetValue;
}

PSS_UserEntity* ZBUserGroupEntity::FindGroupByGUID(const CString GUID, bool Deeper /*= false*/)
{
    // First, check if the main group correspond to the requested GUID
    // add it to the find set
    if (GetGUID() == GUID)
    {
        return this;
    }

    // Then search in the group itself
    return _FindGroupByGUID(GUID, Deeper);
}

ZBUserEntitySet* ZBUserGroupEntity::FindGroup(const CString Name, bool Deeper /*= false*/)
{
    m_FindSet.RemoveAll();

    // First, check if the main group correspond to the requested name
    // add it to the find set
    if (GetEntityName() == Name)
    {
        m_FindSet.Add(this);
    }

    // Then search in the group itself
    _FindGroup(Name, Deeper);

    return &m_FindSet;
}

ZBUserEntitySet* ZBUserGroupEntity::FindGroup(const CString Name, const CString InGroupName)
{
    ZBUserGroupEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if (!InGroupName.IsEmpty())
    {
        pGroup = _FindFirstGroup(InGroupName);
    }

    // Call the FindGroup function with the pGroup pointer passed has parameter
    return FindGroup(Name, pGroup);
}

ZBUserEntitySet* ZBUserGroupEntity::FindGroup(const CString Name, ZBUserGroupEntity* pInGroup)
{
    m_FindSet.RemoveAll();

    // First, check if the main group correspond to the requested name
    // add it to the find set
    if (GetEntityName() == Name)
    {
        m_FindSet.Add(this);
    }

    // Then search in the group itself
    _FindGroup(Name, pInGroup);
    return &m_FindSet;
}

void ZBUserGroupEntity::_FindGroup(const CString Name, ZBUserGroupEntity* pInGroup)
{
    if (!pInGroup)
    {
        pInGroup = this;
    }

    pInGroup->_FindGroup(Name, false);
}

// The _FindGroupByGUID function will search all groups corresponding to the GUID passed as parameter
PSS_UserEntity* ZBUserGroupEntity::_FindGroupByGUID(const CString GUID, bool Deeper /*= false*/)
{
    // Sets the iterator to the right entity set
    ZBUserEntityIterator i(&m_EntitySet);

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        if (ISA(pEnv, ZBUserGroupEntity))
        {
            // If correspond to the requested name
            // add it to the find set
            if (dynamic_cast<ZBUserGroupEntity*>(pEnv)->GetGUID() == GUID)
            {
                return pEnv;
            }

            // If the group has entity
            // call the group's function 
            if (Deeper && dynamic_cast<ZBUserGroupEntity*>(pEnv)->ContainEntity())
            {
                PSS_UserEntity* pFoundEnv =
                    dynamic_cast<ZBUserGroupEntity*>(pEnv)->_FindGroupByGUID(GUID, Deeper);

                if (pFoundEnv)
                {
                    return pFoundEnv;
                }
            }
        }
    }

    return NULL;
}

// The _FindGroup function will search all groups corresponding to the name passed as parameter
// The function will fill the m_FindSet static variable with elements found
void ZBUserGroupEntity::_FindGroup(const CString Name, bool Deeper /*= false*/)
{
    // Sets the iterator to the right entity set
    ZBUserEntityIterator i(&m_EntitySet);

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        if (ISA(pEnv, ZBUserGroupEntity))
        {
            // If correspond to the requested name
            // add it to the find set
            if (dynamic_cast<ZBUserGroupEntity*>(pEnv)->GetEntityName() == Name)
            {
                m_FindSet.Add(pEnv);
            }

            // If the group has entity
            // call the group's function 
            if (Deeper && dynamic_cast<ZBUserGroupEntity*>(pEnv)->ContainEntity())
            {
                dynamic_cast<ZBUserGroupEntity*>(pEnv)->_FindGroup(Name, Deeper);
            }
        }
    }
}

ZBUserGroupEntity* ZBUserGroupEntity::_FindFirstGroup(const CString Name, ZBUserGroupEntity* pInGroup)
{
    if (!pInGroup)
    {
        pInGroup = this;
    }

    return pInGroup->_FindFirstGroup(Name, false);
}

ZBUserGroupEntity* ZBUserGroupEntity::_FindFirstGroup(const CString Name, bool Deeper /*= false*/)
{
    ZBUserEntityIterator i(&m_EntitySet);

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        if (ISA(pEnv, ZBUserGroupEntity))
        {
            // If correspond to the requested group name
            // return it
            if (dynamic_cast<ZBUserGroupEntity*>(pEnv)->GetEntityName() == Name)
            {
                return dynamic_cast<ZBUserGroupEntity*>(pEnv);
            }

            // If the group has entity
            if (Deeper && dynamic_cast<ZBUserGroupEntity*>(pEnv)->ContainEntity())
            {
                ZBUserGroupEntity* pGroup =
                    dynamic_cast<ZBUserGroupEntity*>(pEnv)->_FindFirstGroup(Name, Deeper);

                if (pGroup)
                {
                    return pGroup;
                }
            }
        }
    }

    return NULL;
}

bool ZBUserGroupEntity::GroupExist(const CString Name, bool Deeper /*= false*/)
{
    // Sets the iterator to the right entity set
    ZBUserEntityIterator i(&m_EntitySet);

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        if (ISA(pEnv, ZBUserGroupEntity))
        {
            // If correspond to the requested name
            if (dynamic_cast<ZBUserGroupEntity*>(pEnv)->GetEntityName() == Name)
            {
                return true;
            }

            // If the group has entity
            if (Deeper && dynamic_cast<ZBUserGroupEntity*>(pEnv)->ContainEntity())
            {
                if (dynamic_cast<ZBUserGroupEntity*>(pEnv)->GroupExist(Name, Deeper))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool ZBUserGroupEntity::GroupExist(const CString Name, const CString InGroupName)
{
    ZBUserGroupEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if (!InGroupName.IsEmpty())
    {
        pGroup = _FindFirstGroup(InGroupName);
    }

    // Call the function with the group pointer
    return GroupExist(Name, pGroup);
}

bool ZBUserGroupEntity::GroupExist(const CString Name, ZBUserGroupEntity* pInGroup)
{
    if (!pInGroup)
    {
        pInGroup = this;
    }

    return pInGroup->GroupExist(Name, false);
}

////////////////////////////////////////////////////////////////
// File management functions
ZBUserRoleEntity* ZBUserGroupEntity::AddRole(const CString Rolename, const CString Description)
{
    ZBUserRoleEntity* pNewFile = new ZBUserRoleEntity(Rolename, Description, this);
    m_EntitySet.Add(pNewFile);
    return pNewFile;
}

ZBUserRoleEntity* ZBUserGroupEntity::AddRole(const CString Rolename,
                                             const CString Description,
                                             const CString InGroupName)
{
    ZBUserGroupEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if (!InGroupName.IsEmpty())
    {
        pGroup = _FindFirstGroup(InGroupName);
    }

    // Call the AddRole function with the pGroup pointer passed has parameter
    return AddRole(Rolename, Description, pGroup);
}

ZBUserRoleEntity* ZBUserGroupEntity::AddRole(const CString            Rolename,
                                             const CString            Description,
                                             ZBUserGroupEntity*    pInGroup)
{
    if (!pInGroup)
    {
        pInGroup = this;
    }

    return pInGroup->AddRole(Rolename, Description);
}

bool ZBUserGroupEntity::RemoveRole(ZBUserRoleEntity* pRole)
{
    // Sets the iterator to the right entity set
    ZBUserEntityIterator i(&m_EntitySet);

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        if (ISA(pEnv, ZBUserRoleEntity) && dynamic_cast<ZBUserRoleEntity*>(pEnv) == pRole)
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
        if (ISA(pEnv, ZBUserGroupEntity) && dynamic_cast<ZBUserGroupEntity*>(pEnv)->ContainEntity())
        {
            if (dynamic_cast<ZBUserGroupEntity*>(pEnv)->RemoveRole(pRole))
            {
                return true;
            }
        }
    }

    return false;
}

bool ZBUserGroupEntity::RemoveRole(const CString Rolename)
{
    // Sets the iterator to the right entity set
    ZBUserEntityIterator i(&m_EntitySet);

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        if (ISA(pEnv, ZBUserRoleEntity) && dynamic_cast<ZBUserRoleEntity*>(pEnv)->GetEntityName() == Rolename)
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

bool ZBUserGroupEntity::RemoveRole(const CString Rolename, const CString InGroupName)
{
    ZBUserGroupEntity* pGroup = NULL;

    // If in group name defined,
    // Try to locate the group name
    if (!InGroupName.IsEmpty())
    {
        pGroup = _FindFirstGroup(InGroupName);
    }

    // Call the RemoveRole function with the pGroup pointer passed has parameter
    return RemoveRole(Rolename, pGroup);
}

bool ZBUserGroupEntity::RemoveRole(const CString Rolename, ZBUserGroupEntity* pInGroup)
{
    if (!pInGroup)
    {
        pInGroup = this;
    }

    return pInGroup->RemoveRole(Rolename);
}

PSS_UserEntity* ZBUserGroupEntity::FindRoleByGUID(const CString GUID, bool Deeper /*= false*/)
{
    // Then search in the group itself
    return _FindRoleByGUID(GUID, Deeper);
}

// The _FindRoleByGUID function will search all roles corresponding to the GUID passed as parameter
PSS_UserEntity* ZBUserGroupEntity::_FindRoleByGUID(const CString GUID, bool Deeper /*= false*/)
{
    // Sets the iterator to the right entity set
    ZBUserEntityIterator i(&m_EntitySet);

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        if (ISA(pEnv, ZBUserRoleEntity))
        {
            // If correspond to the requested name
            // add it to the find set
            if (dynamic_cast<ZBUserRoleEntity*>(pEnv)->GetGUID() == GUID)
            {
                return pEnv;
            }
        }
        else if (ISA(pEnv, ZBUserGroupEntity))
        {
            // If the group has entity
            // call the group's function 
            if (Deeper && dynamic_cast<ZBUserGroupEntity*>(pEnv)->ContainEntity())
            {
                PSS_UserEntity* pFoundEnv = dynamic_cast<ZBUserGroupEntity*>(pEnv)->_FindRoleByGUID(GUID, Deeper);

                if (pFoundEnv)
                {
                    return pFoundEnv;
                }
            }
        }
    }

    return NULL;
}

void ZBUserGroupEntity::RecalculateParent()
{
    // Sets the iterator to the right entity set
    ZBUserEntityIterator i(&m_EntitySet);

    for (PSS_UserEntity* pEnv = i.GetFirst(); pEnv != NULL; pEnv = i.GetNext())
    {
        // Set the parent pointer
        pEnv->SetParent(this);

        // If we have a group entity,
        // and the group has entity
        // call the recalculate group function 
        if (ISA(pEnv, ZBUserGroupEntity) && dynamic_cast<ZBUserGroupEntity*>(pEnv)->ContainEntity())
        {
            dynamic_cast<ZBUserGroupEntity*>(pEnv)->RecalculateParent();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBUserGroupEntity diagnostics

#ifdef _DEBUG
void ZBUserGroupEntity::AssertValid() const
{
    PSS_UserEntity::AssertValid();
}

void ZBUserGroupEntity::Dump(CDumpContext& dc) const
{
    PSS_UserEntity::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBUserGroupEntity serialization

void ZBUserGroupEntity::Serialize(CArchive& ar)
{
    PSS_UserEntity::Serialize(ar);

    // If something else to serialize, do it below
    if (ar.IsStoring())
    {
        // Write the elements
        ar << static_cast<int>(GetEntityCount());

        for (int nIdx = 0; nIdx < (int)GetEntityCount(); nIdx++)
        {
            PSS_UserEntity* pEntity = GetEntityAt(nIdx);
            ar << pEntity;
        }
    }
    else
    {
        // Read the elements

        // Before reading elements, remove all
        RemoveAllUserEntities();

        int nCount;
        PSS_UserEntity* pEntity;

        ar >> nCount;

        for (int i = 0; i < nCount; i++)
        {
            ar >> pEntity;
            m_EntitySet.Add(pEntity);
            pEntity->SetParent(this);
        }
    }
}
