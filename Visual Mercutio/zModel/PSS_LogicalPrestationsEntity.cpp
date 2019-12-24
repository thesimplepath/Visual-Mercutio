/****************************************************************************
 * ==> PSS_LogicalPrestationsEntity ----------------------------------------*
 ****************************************************************************
 * Description : Provides a logical prestations entity                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LogicalPrestationsEntity.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity::IEntitySet PSS_LogicalPrestationsEntity::m_FindSet;
BOOL                                     PSS_LogicalPrestationsEntity::m_Modified = FALSE;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_LogicalPrestationsEntity, ZBPrestationsEntity, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_LogicalPrestationsEntity
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity::PSS_LogicalPrestationsEntity(const CString&       name,
                                                           const CString&       description,
                                                           ZBPrestationsEntity* pParent) :
    ZBPrestationsEntity(name, description, pParent)
{}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity::~PSS_LogicalPrestationsEntity()
{
    // NOTE use fully qualified name here to avoid to call a pure virtual function during the destruction
    PSS_LogicalPrestationsEntity::RemoveAllPrestationsEntities();
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity* PSS_LogicalPrestationsEntity::AddPrestation(const CString& name,
                                                                          const CString& description)
{
    PSS_LogicalPrestationsEntity* pNewGroup = new PSS_LogicalPrestationsEntity(name, description, this);
    m_EntitySet.Add(pNewGroup);

    return pNewGroup;
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity* PSS_LogicalPrestationsEntity::AddPrestation(const CString& name,
                                                                          const CString& description,
                                                                          const CString& inPrestationName)
{
    PSS_LogicalPrestationsEntity* pGroup = NULL;

    if (!inPrestationName.IsEmpty())
        pGroup = FindFirstPrestation(inPrestationName);

    return AddPrestation(name, description, pGroup);
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity* PSS_LogicalPrestationsEntity::AddPrestation(const CString&                name,
                                                                          const CString&                description,
                                                                          PSS_LogicalPrestationsEntity* pInPrestation)
{
    // if no group defined, use this one
    if (!pInPrestation)
        pInPrestation = this;

    return pInPrestation->AddPrestation(name, description);
}
//---------------------------------------------------------------------------
bool PSS_LogicalPrestationsEntity::RemovePrestation(const CString& name, bool deeper)
{
    IEntitySet* pSet = FindPrestation(name, deeper);

    if (pSet && pSet->GetSize() > 0)
        return RemovePrestations(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalPrestationsEntity::RemovePrestation(const CString& name, const CString& inPrestationName)
{
    IEntitySet* pSet = FindPrestation(name, inPrestationName);

    if (pSet && pSet->GetSize() > 0)
        return RemovePrestations(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalPrestationsEntity::RemovePrestation(const CString& name, PSS_LogicalPrestationsEntity* pInPrestation)
{
    IEntitySet* pSet = FindPrestation(name, pInPrestation);

    if (pSet && pSet->GetSize() > 0)
        return RemovePrestations(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalPrestationsEntity::RemovePrestation(PSS_LogicalPrestationsEntity* pPrestation)
{
    IEntityIterator it(&m_EntitySet);

    for (ZBPrestationsEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalPrestationsEntity* pPrestationEntity = dynamic_cast<PSS_LogicalPrestationsEntity*>(pEnv);

        if (!pPrestationEntity)
            continue;

        if (pEnv == pPrestation)
        {
            // free the memory
            delete pPrestation;

            // remove the current element
            it.Remove();
            return true;
        }

        // recursively remove the prestation from the children
        if (pPrestationEntity->ContainEntity())
            if (pPrestationEntity->RemovePrestation(pPrestation))
                return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_LogicalPrestationsEntity::RemoveAllPrestationsEntities()
{
    IEntityIterator it(&m_EntitySet);

    for (ZBPrestationsEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
        delete pEnv;

    m_EntitySet.RemoveAll();
}
//---------------------------------------------------------------------------
ZBPrestationsEntity* PSS_LogicalPrestationsEntity::FindPrestationByGUID(const CString& guid, bool deeper)
{
    // check if the main group matches with the requested guid, add it to the find set if yes
    if (GetGUID() == guid)
        return this;

    // search in the group itself
    return FindPrestationByGUIDPvt(guid, deeper);
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity::IEntitySet* PSS_LogicalPrestationsEntity::FindPrestation(const CString& name,
                                                                                       bool           deeper)
{
    m_FindSet.RemoveAll();

    // check if the main group matches with the name to find, add it to the find set if yes
    if (GetEntityName() == name)
        m_FindSet.Add(this);

    // search in the group itself
    FindPrestationPvt(name, deeper);

    return &m_FindSet;
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity::IEntitySet* PSS_LogicalPrestationsEntity::FindPrestation(const CString& name,
                                                                                       const CString& inPrestationName)
{
    PSS_LogicalPrestationsEntity* pGroup = NULL;

    if (!inPrestationName.IsEmpty())
        pGroup = FindFirstPrestation(inPrestationName);

    return FindPrestation(name, pGroup);
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity::IEntitySet* PSS_LogicalPrestationsEntity::FindPrestation(const CString&                name,
                                                                                       PSS_LogicalPrestationsEntity* pInPrestation)
{
    m_FindSet.RemoveAll();

    // check if the main group matches with the name to find, add it to the find set if yes
    if (GetEntityName() == name)
        m_FindSet.Add(this);

    // search in the group itself
    FindPrestationPvt(name, pInPrestation);

    return &m_FindSet;
}
//---------------------------------------------------------------------------
bool PSS_LogicalPrestationsEntity::PrestationExist(const CString& name, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (ZBPrestationsEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalPrestationsEntity* pPrestationsEntity = dynamic_cast<PSS_LogicalPrestationsEntity*>(pEnv);

        if (!pPrestationsEntity)
            continue;

        // if matches with the requested name
        if (pPrestationsEntity->GetEntityName() == name)
            return true;

        // if the group has entity
        if (deeper && pPrestationsEntity->ContainEntity())
            if (pPrestationsEntity->PrestationExist(name, deeper))
                return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalPrestationsEntity::PrestationExist(const CString& name, const CString& inPrestationName)
{
    PSS_LogicalPrestationsEntity* pGroup = NULL;

    if (!inPrestationName.IsEmpty())
        pGroup = FindFirstPrestation(inPrestationName);

    return PrestationExist(name, pGroup);
}
//---------------------------------------------------------------------------
bool PSS_LogicalPrestationsEntity::PrestationExist(const CString& name, PSS_LogicalPrestationsEntity* pInPrestation)
{
    if (!pInPrestation)
        pInPrestation = this;

    return pInPrestation->PrestationExist(name, false);
}
//---------------------------------------------------------------------------
bool PSS_LogicalPrestationsEntity::MovePrestation(ZBPrestationsEntity* pPrestation)
{
    if (!pPrestation)
        return false;

    PSS_LogicalPrestationsEntity* pEntity = dynamic_cast<PSS_LogicalPrestationsEntity*>(pPrestation);
    PSS_LogicalPrestationsEntity* pParent = dynamic_cast<PSS_LogicalPrestationsEntity*>(pPrestation->GetParent());

    // remove the entity from the old group
    if (pEntity && pParent)
        if (!pParent->RemovePrestationFromSet(pEntity))
            return false;

    // add the entity to the new group
    AddPrestation(pPrestation);

    // set the new parent
    pPrestation->SetParent(this);

    return true;
}
//---------------------------------------------------------------------------
void PSS_LogicalPrestationsEntity::Serialize(CArchive& ar)
{
    ZBPrestationsEntity::Serialize(ar);

    if (ar.IsStoring())
    {
        const int entityCount = GetEntityCount();
        ar << entityCount;

        // write the elements
        for (int i = 0; i < entityCount; ++i)
        {
            ZBPrestationsEntity* pEntity = GetEntityAt(i);
            ar << pEntity;
        }
    }
    else
    {
        // before reading elements, remove all the existing ones
        RemoveAllPrestationsEntities();

        int count;
        ar >> count;

        ZBPrestationsEntity* pEntity;

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
    void PSS_LogicalPrestationsEntity::AssertValid() const
    {
        ZBPrestationsEntity::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_LogicalPrestationsEntity::Dump(CDumpContext& dc) const
    {
        ZBPrestationsEntity::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
bool PSS_LogicalPrestationsEntity::RemovePrestationFromSet(ZBPrestationsEntity* pPrestation)
{
    IEntityIterator it(&m_EntitySet);

    for (ZBPrestationsEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
        if (pEnv == pPrestation)
        {
            // remove the current element
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
ZBPrestationsEntity* PSS_LogicalPrestationsEntity::FindPrestationByGUIDPvt(const CString& guid, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (ZBPrestationsEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalPrestationsEntity* pEntity = dynamic_cast<PSS_LogicalPrestationsEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matches with the name to find, add it to the find set
        if (pEntity->GetGUID() == guid)
            return pEnv;

        // continue to search recursively in the children
        if (deeper && pEntity->ContainEntity())
        {
            ZBPrestationsEntity* pFoundEnv = pEntity->FindPrestationByGUIDPvt(guid, deeper);

            if (pFoundEnv)
                return pFoundEnv;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_LogicalPrestationsEntity::FindPrestationPvt(const CString& name, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (ZBPrestationsEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalPrestationsEntity* pEntity = dynamic_cast<PSS_LogicalPrestationsEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matching with the name to find, add it to the find set
        if (pEntity->GetEntityName() == name)
            m_FindSet.Add(pEnv);

        // continue to search recursively in the children
        if (deeper && pEntity->ContainEntity())
            pEntity->FindPrestationPvt(name, deeper);
    }
}
//---------------------------------------------------------------------------
void PSS_LogicalPrestationsEntity::FindPrestationPvt(const CString& name, PSS_LogicalPrestationsEntity* pInPrestation)
{
    if (!pInPrestation)
        pInPrestation = this;

    pInPrestation->FindPrestationPvt(name, false);
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity* PSS_LogicalPrestationsEntity::FindFirstPrestation(const CString& name, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (ZBPrestationsEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalPrestationsEntity* pEntity = dynamic_cast<PSS_LogicalPrestationsEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matches with the group name to find, return it
        if (pEntity->GetEntityName() == name)
            return pEntity;

        // continue to search recursively in the children
        if (deeper && pEntity->ContainEntity())
        {
            PSS_LogicalPrestationsEntity* pGroup = pEntity->FindFirstPrestation(name, deeper);

            if (pGroup)
                return pGroup;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity* PSS_LogicalPrestationsEntity::FindFirstPrestation(const CString&                name,
                                                                                PSS_LogicalPrestationsEntity* pInPrestation)
{
    if (!pInPrestation)
        pInPrestation = this;

    return pInPrestation->FindFirstPrestation(name, false);
}
//---------------------------------------------------------------------------
bool PSS_LogicalPrestationsEntity::RemovePrestations(IEntitySet& set)
{
    bool result = false;

    if (set.GetSize() > 0)
    {
        result = true;

        const int count = set.GetSize();

        // for each elements, check if a group exists and if he has a parent, then remove the group in parent
        for (int i = 0; i < count; ++i)
        {
            PSS_LogicalPrestationsEntity* pEntity = dynamic_cast<PSS_LogicalPrestationsEntity*>(set.GetAt(i));

            if (!pEntity)
                continue;

            PSS_LogicalPrestationsEntity* pParent = dynamic_cast<PSS_LogicalPrestationsEntity*>(pEntity->GetParent());

            // continue to remove recursively in the children. On error, set result to false at least one time
            if (pParent && !pParent->RemovePrestation(pEntity))
                result = false;
        }
    }

    return result;
}
//---------------------------------------------------------------------------
void PSS_LogicalPrestationsEntity::RecalculateParent()
{
    IEntityIterator it(&m_EntitySet);

    for (ZBPrestationsEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        // set the parent pointer
        pEnv->SetParent(this);

        PSS_LogicalPrestationsEntity* pEntity = dynamic_cast<PSS_LogicalPrestationsEntity*>(pEnv);

        // continue to recalculate recursively in the children
        if (pEntity && pEntity->ContainEntity())
            pEntity->RecalculateParent();
    }
}
//---------------------------------------------------------------------------
