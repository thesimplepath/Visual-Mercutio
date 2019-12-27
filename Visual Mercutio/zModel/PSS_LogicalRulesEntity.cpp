/****************************************************************************
 * ==> PSS_LogicalRulesEntity ----------------------------------------------*
 ****************************************************************************
 * Description : Provides the logical rules entity                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LogicalRulesEntity.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity::IEntitySet PSS_LogicalRulesEntity::m_FindSet;
BOOL                               PSS_LogicalRulesEntity::m_Modified = FALSE;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_LogicalRulesEntity, PSS_RulesEntity, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_LogicalRulesEntity
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity::PSS_LogicalRulesEntity(const CString&   name,
                                               const CString&   description,
                                               PSS_RulesEntity* pParent) :
    PSS_RulesEntity(name, description, pParent)
{}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity::~PSS_LogicalRulesEntity()
{
    // NOTE use fully qualified name here to avoid to call a pure virtual function during the destruction
    PSS_LogicalRulesEntity::RemoveAllRulesEntities();
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity* PSS_LogicalRulesEntity::AddRule(const CString& name, const CString& description)
{
    std::unique_ptr<PSS_LogicalRulesEntity> pRules(new PSS_LogicalRulesEntity(name, description, this));
    m_EntitySet.Add(pRules.get());
    return pRules.release();
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity* PSS_LogicalRulesEntity::AddRule(const CString& name,
                                                        const CString& description,
                                                        const CString& inRuleName)
{
    PSS_LogicalRulesEntity* pRules = NULL;

    if (!inRuleName.IsEmpty())
        pRules = FindFirstRule(inRuleName);

    return AddRule(name, description, pRules);
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity* PSS_LogicalRulesEntity::AddRule(const CString&          name,
                                                        const CString&          description,
                                                        PSS_LogicalRulesEntity* pInRule)
{
    // if no rules defined
    if (!pInRule)
        pInRule = this;

    return pInRule->AddRule(name, description);
}
//---------------------------------------------------------------------------
bool PSS_LogicalRulesEntity::RemoveRule(const CString& name, bool deeper)
{
    IEntitySet* pSet = FindRule(name, deeper);

    if (pSet && pSet->GetSize() > 0)
        return RemoveRules(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalRulesEntity::RemoveRule(const CString& name, const CString& inRuleName)
{
    IEntitySet* pSet = FindRule(name, inRuleName);

    if (pSet && pSet->GetSize() > 0)
        return RemoveRules(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalRulesEntity::RemoveRule(const CString& name, PSS_LogicalRulesEntity* pInRule)
{
    IEntitySet* pSet = FindRule(name, pInRule);

    if (pSet && pSet->GetSize() > 0)
        return RemoveRules(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalRulesEntity::RemoveRule(PSS_LogicalRulesEntity* pRule)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_RulesEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalRulesEntity* pCurRule = dynamic_cast<PSS_LogicalRulesEntity*>(pEnv);

        if (!pCurRule)
            continue;

        if (pCurRule == pRule)
        {
            // free the memory
            delete pRule;

            // remove the current element
            it.Remove();
            return true;
        }

        // recursively remove the rule from the children
        if (pCurRule->ContainEntity())
            if (pCurRule->RemoveRule(pRule))
                return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_LogicalRulesEntity::RemoveAllRulesEntities()
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_RulesEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
        delete pEnv;

    m_EntitySet.RemoveAll();
}
//---------------------------------------------------------------------------
PSS_RulesEntity* PSS_LogicalRulesEntity::FindRuleByGUID(const CString& guid, bool deeper)
{
    // check if the main group matches with the guid to find, add it to the find set if yes
    if (GetGUID() == guid)
        return this;

    // search in the group itself
    return FindRuleByGUIDPvt(guid, deeper);
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity::IEntitySet* PSS_LogicalRulesEntity::FindRule(const CString& name, bool deeper)
{
    m_FindSet.RemoveAll();

    // check if the main group matches with the name to find, add it to the find set if yes
    if (GetEntityName() == name)
        m_FindSet.Add(this);

    // search in the group itself
    FindRulePvt(name, deeper);

    return &m_FindSet;
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity::IEntitySet* PSS_LogicalRulesEntity::FindRule(const CString& name, const CString& inRuleName)
{
    PSS_LogicalRulesEntity* pGroup = NULL;

    if (!inRuleName.IsEmpty())
        pGroup = FindFirstRule(inRuleName);

    return FindRule(name, pGroup);
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity::IEntitySet* PSS_LogicalRulesEntity::FindRule(const CString&          name,
                                                                     PSS_LogicalRulesEntity* pInRule)
{
    m_FindSet.RemoveAll();

    // check if the main group matches with the name to find, add it to the find set if yes
    if (GetEntityName() == name)
        m_FindSet.Add(this);

    // search in the group itself
    FindRulePvt(name, pInRule);

    return &m_FindSet;
}
//---------------------------------------------------------------------------
bool PSS_LogicalRulesEntity::RuleExist(const CString& name, bool deeper)
{
    PSS_LogicalRulesEntity::IEntityIterator it(&m_EntitySet);

    for (PSS_RulesEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalRulesEntity* pEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matches with the name to find
        if (pEntity->GetEntityName() == name)
            return true;

        // continue the search recursively
        if (deeper && pEntity->ContainEntity())
            if (pEntity->RuleExist(name, deeper))
                return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalRulesEntity::RuleExist(const CString& name, const CString& inRuleName)
{
    PSS_LogicalRulesEntity* pGroup = NULL;

    if (!inRuleName.IsEmpty())
        pGroup = FindFirstRule(inRuleName);

    return RuleExist(name, pGroup);
}
//---------------------------------------------------------------------------
bool PSS_LogicalRulesEntity::RuleExist(const CString& name, PSS_LogicalRulesEntity* pInRule)
{
    if (!pInRule)
        pInRule = this;

    return pInRule->RuleExist(name, false);
}
//---------------------------------------------------------------------------
bool PSS_LogicalRulesEntity::MoveRule(PSS_RulesEntity* pRule)
{
    if (!pRule)
        return false;

    // remove the entity from the old group
    PSS_LogicalRulesEntity* pEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pRule);
    PSS_LogicalRulesEntity* pParent = dynamic_cast<PSS_LogicalRulesEntity*>(pRule->GetParent());

    if (pEntity && pParent)
        if (!pParent->RemoveRuleFromSet(pEntity))
            return false;

    // add the entity to the new group
    AddRule(pRule);

    // set the new parent
    pRule->SetParent(this);

    return true;
}
//---------------------------------------------------------------------------
void PSS_LogicalRulesEntity::Serialize(CArchive& ar)
{
    PSS_RulesEntity::Serialize(ar);

    // if something else to serialize, do it below
    if (ar.IsStoring())
    {
        // write the elements
        ar << static_cast<int>(GetEntityCount());

        for (int index = 0; index < int(GetEntityCount()); ++index)
        {
            PSS_RulesEntity* pEntity = GetEntityAt(index);
            ar << pEntity;
        }
    }
    else
    {
        // before reading elements, remove all the previous ones
        RemoveAllRulesEntities();

        int count;
        ar >> count;

        PSS_RulesEntity* pEntity;

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
    void PSS_LogicalRulesEntity::AssertValid() const
    {
        PSS_RulesEntity::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_LogicalRulesEntity::Dump(CDumpContext& dc) const
    {
        PSS_RulesEntity::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
bool PSS_LogicalRulesEntity::RemoveRuleFromSet(PSS_RulesEntity* pRule)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_RulesEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
        if (pEnv == pRule)
        {
            // remove the current element
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
PSS_RulesEntity* PSS_LogicalRulesEntity::FindRuleByGUIDPvt(const CString& guid, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_RulesEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalRulesEntity* pEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matching with the name to find, add it to the find set
        if (pEntity->GetGUID() == guid)
            return pEnv;

        // continue to search recursively
        if (deeper && pEntity->ContainEntity())
        {
            PSS_RulesEntity* pFoundEnv = pEntity->FindRuleByGUIDPvt(guid, deeper);

            if (pFoundEnv)
                return pFoundEnv;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_LogicalRulesEntity::FindRulePvt(const CString& name, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_RulesEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalRulesEntity* pEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if mazches with the name to find, add it to the find set
        if (pEntity->GetEntityName() == name)
            m_FindSet.Add(pEnv);

        // continue to search recursively
        if (deeper && pEntity->ContainEntity())
            pEntity->FindRulePvt(name, deeper);
    }
}
//---------------------------------------------------------------------------
void PSS_LogicalRulesEntity::FindRulePvt(const CString& name, PSS_LogicalRulesEntity* pInRule)
{
    if (!pInRule)
        pInRule = this;

    pInRule->FindRulePvt(name, false);
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity* PSS_LogicalRulesEntity::FindFirstRule(const CString& name, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_RulesEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_LogicalRulesEntity* pEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pEnv);

        if (!pEntity)
            continue;

        // if matches with the group name to find, return it
        if (pEntity->GetEntityName() == name)
            return pEntity;

        // continue to search recursively
        if (deeper && pEntity->ContainEntity())
        {
            PSS_LogicalRulesEntity* pGroup = pEntity->FindFirstRule(name, deeper);

            if (pGroup)
                return pGroup;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity* PSS_LogicalRulesEntity::FindFirstRule(const CString& name, PSS_LogicalRulesEntity* pInRule)
{
    if (!pInRule)
        pInRule = this;

    return pInRule->FindFirstRule(name, false);
}
//---------------------------------------------------------------------------
bool PSS_LogicalRulesEntity::RemoveRules(IEntitySet& set)
{
    bool result = false;

    if (set.GetSize() > 0)
    {
        // if contains elements, set the result to true
        result = true;

        const int count = set.GetSize();

        // for each elements, check if is a group and if he has a parent, then call the parent to remove the group
        for (int i = 0; i < count; ++i)
        {
            PSS_LogicalRulesEntity* pGroup = dynamic_cast<PSS_LogicalRulesEntity*>(set.GetAt(i));

            if (pGroup)
            {
                PSS_LogicalRulesEntity* pParent = dynamic_cast<PSS_LogicalRulesEntity*>(pGroup->GetParent());

                // on error, set the result to false at least one time
                if (pParent && !pParent->RemoveRule(pGroup))
                    result = false;
            }
        }
    }

    return result;
}
//---------------------------------------------------------------------------
void PSS_LogicalRulesEntity::RecalculateParent()
{
    // Sets the iterator to the right entity set
    IEntityIterator it(&m_EntitySet);

    for (PSS_RulesEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        // set the parent
        pEnv->SetParent(this);

        PSS_LogicalRulesEntity* pEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pEnv);

        // continue to recalculate recursively
        if (pEntity && pEntity->ContainEntity())
            pEntity->RecalculateParent();
    }
}
//---------------------------------------------------------------------------
