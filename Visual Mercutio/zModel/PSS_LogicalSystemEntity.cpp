/****************************************************************************
 * ==> PSS_LogicalSystemEntity ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a logical system entity                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LogicalSystemEntity.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity::IEntitySet PSS_LogicalSystemEntity::m_FindSet;
BOOL                                PSS_LogicalSystemEntity::m_Modified = FALSE;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_LogicalSystemEntity, PSS_SystemEntity, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_LogicalSystemEntity
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity::PSS_LogicalSystemEntity(const CString&    name,
                                                 const CString&    description,
                                                 PSS_SystemEntity* pParent) :
    PSS_SystemEntity(name, description, pParent)
{}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity::~PSS_LogicalSystemEntity()
{
    // NOTE use fully qualified name here to avoid to call a pure virtual function during the destruction
    PSS_LogicalSystemEntity::RemoveAllSystemEntities();
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity* PSS_LogicalSystemEntity::AddSystem(const CString& name, const CString& description)
{
    std::unique_ptr<PSS_LogicalSystemEntity> pSystem(new PSS_LogicalSystemEntity(name, description, this));
    m_EntitySet.Add(pSystem.get());
    return pSystem.release();
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity* PSS_LogicalSystemEntity::AddSystem(const CString& name,
                                                            const CString& description,
                                                            const CString& inSystemName)
{
    PSS_LogicalSystemEntity* pSystem = NULL;

    if (!inSystemName.IsEmpty())
        pSystem  = FindFirstSystem(inSystemName);

    return AddSystem(name, description, pSystem);
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity* PSS_LogicalSystemEntity::AddSystem(const CString&           name,
                                                            const CString&           description,
                                                            PSS_LogicalSystemEntity* pInSystem)
{
    // if no system defined
    if (!pInSystem)
        pInSystem = this;

    return pInSystem->AddSystem(name, description);
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemEntity::RemoveSystem(const CString& name, bool deeper)
{
    IEntitySet* pSet = FindSystem(name, deeper);

    if (pSet && pSet->GetSize() > 0)
        return RemoveSystems(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemEntity::RemoveSystem(const CString& name, const CString& inSystemName)
{
    IEntitySet* pSet = FindSystem(name, inSystemName);

    if (pSet && pSet->GetSize() > 0)
        return RemoveSystems(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemEntity::RemoveSystem(const CString& name, PSS_LogicalSystemEntity* pInSystem)
{
    IEntitySet* pSet = FindSystem(name, pInSystem);

    if (pSet && pSet->GetSize() > 0)
        return RemoveSystems(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemEntity::RemoveSystem(PSS_LogicalSystemEntity* pSystem)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_SystemEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalSystemEntity* pEntity = dynamic_cast<PSS_LogicalSystemEntity*>(pEnv);

        if (!pEntity)
            continue;

        if (pEntity == pSystem)
        {
            // free the memory
            delete pSystem;

            // remove the current element
            it.Remove();
            return true;
        }

        // continue to search recursively
        if (pEntity->ContainEntity())
            if (pEntity->RemoveSystem(pSystem))
                return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemEntity::RemoveAllSystemEntities()
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_SystemEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
        delete pEnv;

    m_EntitySet.RemoveAll();
}
//---------------------------------------------------------------------------
PSS_SystemEntity* PSS_LogicalSystemEntity::FindSystemByGUID(const CString& guid, bool deeper)
{
    // check if the main group matches with the guid to find, add it to the resulting set if yes
    if (GetGUID() == guid)
        return this;

    // search in the group itself
    return FindSystemByGUIDPvt(guid, deeper);
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity::IEntitySet* PSS_LogicalSystemEntity::FindSystem(const CString& name, bool deeper)
{
    m_FindSet.RemoveAll();

    // check if the main group matches with the name to find, add it to the resulting set if yes
    if (GetEntityName() == name)
        m_FindSet.Add(this);

    // search in the group itself
    FindSystemPvt(name, deeper);

    return &m_FindSet;
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity::IEntitySet* PSS_LogicalSystemEntity::FindSystem(const CString& name, const CString& inSystemName)
{
    PSS_LogicalSystemEntity* pSystem = NULL;

    if (!inSystemName.IsEmpty())
        pSystem = FindFirstSystem(inSystemName);

    return FindSystem(name, pSystem);
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity::IEntitySet* PSS_LogicalSystemEntity::FindSystem(const CString&           name,
                                                                         PSS_LogicalSystemEntity* pInSystem)
{
    m_FindSet.RemoveAll();

    // check if the main group matches with the name to find, add it to the resulting set if yes
    if (GetEntityName() == name)
        m_FindSet.Add(this);

    // search in the group itself
    FindSystemPvt(name, pInSystem);

    return &m_FindSet;
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemEntity::SystemExist(const CString& name, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_SystemEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalSystemEntity* pEntity = dynamic_cast<PSS_LogicalSystemEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matches with the name to find
        if (pEntity->GetEntityName() == name)
            return true;

        // continue to search recursively
        if (deeper && pEntity->ContainEntity())
            if (pEntity->SystemExist(name, deeper))
                return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemEntity::SystemExist(const CString& name, const CString& inSystemName)
{
    PSS_LogicalSystemEntity* pSystem = NULL;

    if (!inSystemName.IsEmpty())
        pSystem = FindFirstSystem(inSystemName);

    return SystemExist(name, pSystem);
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemEntity::SystemExist(const CString& name, PSS_LogicalSystemEntity* pInSystem)
{
    if (!pInSystem)
        pInSystem = this;

    return pInSystem->SystemExist(name, false);
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemEntity::MoveSystem(PSS_SystemEntity* pSystem)
{
    if (!pSystem)
        return false;

    PSS_LogicalSystemEntity* pEntity = dynamic_cast<PSS_LogicalSystemEntity*>(pSystem);
    PSS_LogicalSystemEntity* pParent = dynamic_cast<PSS_LogicalSystemEntity*>(pSystem->GetParent());

    // remove the entity from the previous group
    if (pEntity && pParent)
        if (!pParent->RemoveSystemFromSet(pEntity))
            return false;

    // add the entity to the new group
    AddSystem(pSystem);

    // set the new parent
    pSystem->SetParent(this);

    return true;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemEntity::Serialize(CArchive& ar)
{
    PSS_SystemEntity::Serialize(ar);

    if (ar.IsStoring())
    {
        const int count = GetEntityCount();
        ar << count;

        // write the elements
        for (int index = 0; index < count; ++index)
        {
            PSS_SystemEntity* pEntity = GetEntityAt(index);
            ar << pEntity;
        }
    }
    else
    {
        // before reading elements, remove all the previous ones
        RemoveAllSystemEntities();

        int count;
        ar >> count;

        PSS_SystemEntity* pEntity;

        // read the elements
        for (int i = 0; i < count; ++i)
        {
            ar >> pEntity;
            m_EntitySet.Add(pEntity);
            pEntity->SetParent(this);
        }
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_LogicalSystemEntity::AssertValid() const
    {
        PSS_SystemEntity::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_LogicalSystemEntity::Dump(CDumpContext& dc) const
    {
        PSS_SystemEntity::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
bool PSS_LogicalSystemEntity::RemoveSystemFromSet(PSS_SystemEntity* pSystem)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_SystemEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        if (pEnv == pSystem)
        {
            // remove the current element
            it.Remove();
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
PSS_SystemEntity* PSS_LogicalSystemEntity::FindSystemByGUIDPvt(const CString& guid, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_SystemEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalSystemEntity* pEntity = dynamic_cast<PSS_LogicalSystemEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matching with the name to find, add it to the find set
        if (pEntity->GetGUID() == guid)
            return pEnv;

        // continue to search recursively
        if (deeper && pEntity->ContainEntity())
        {
            PSS_SystemEntity* pFoundEnv = pEntity->FindSystemByGUIDPvt(guid, deeper);

            if (pFoundEnv)
                return pFoundEnv;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemEntity::FindSystemPvt(const CString& name, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_SystemEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalSystemEntity* pEntity = dynamic_cast<PSS_LogicalSystemEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matching with the name to find, add it to the find set
        if (pEntity->GetEntityName() == name)
            m_FindSet.Add(pEnv);

        // continue to search recursively
        if (deeper && pEntity->ContainEntity())
            pEntity->FindSystemPvt(name, deeper);
    }
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemEntity::FindSystemPvt(const CString& name, PSS_LogicalSystemEntity* pInSystem)
{
    if (!pInSystem)
        pInSystem = this;

    pInSystem->FindSystemPvt(name, false);
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity* PSS_LogicalSystemEntity::FindFirstSystem(const CString& name, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_SystemEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalSystemEntity* pEntity = dynamic_cast<PSS_LogicalSystemEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matching with the group name to find, return it
        if (pEntity->GetEntityName() == name)
            return pEntity;

        // continue to search recursively
        if (deeper && pEntity->ContainEntity())
        {
            PSS_LogicalSystemEntity* pGroup = pEntity->FindFirstSystem(name, deeper);

            if (pGroup)
                return pGroup;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity* PSS_LogicalSystemEntity::FindFirstSystem(const CString& name, PSS_LogicalSystemEntity* pInSystem)
{
    if (!pInSystem)
        pInSystem = this;

    return pInSystem->FindFirstSystem(name, false);
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemEntity::RemoveSystems(IEntitySet& set)
{
    bool result = false;

    if (set.GetSize() > 0)
    {
        result = true;

        const int count = set.GetSize();

        // for each elements, check if a group exists and if he has a parent, then call the parent to remove the group
        for (int i = 0; i < count; ++i)
        {
            PSS_LogicalSystemEntity* pEntity = dynamic_cast<PSS_LogicalSystemEntity*>(set.GetAt(i));

            if (pEntity)
            {
                PSS_LogicalSystemEntity* pParent = dynamic_cast<PSS_LogicalSystemEntity*>(pEntity->GetParent());

                if (!pParent->RemoveSystem(pEntity))
                    // on error, should be set to false at least one time
                    result = false;
            }
        }
    }

    return result;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemEntity::RecalculateParent()
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_SystemEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        // set the paren
        pEnv->SetParent(this);

        PSS_LogicalSystemEntity* pEntity = dynamic_cast<PSS_LogicalSystemEntity*>(pEnv);

        // continue to calculate recursively
        if (pEntity && pEntity->ContainEntity())
            pEntity->RecalculateParent();
    }
}
//---------------------------------------------------------------------------
