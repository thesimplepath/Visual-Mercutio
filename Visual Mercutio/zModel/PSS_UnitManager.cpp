/****************************************************************************
 * ==> PSS_UnitManager -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an unit manager                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UnitManager.h"

// processsoft
#include "PSS_ProcessGraphModelDoc.h"
#include "PSS_ModelSet.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_UnitManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_UnitManager
//---------------------------------------------------------------------------
PSS_UnitManager::PSS_UnitManager(PSS_ProcessModelDocTmpl* pDocTmpl) :
    CObject(),
    m_pDocTmpl(pDocTmpl)
{}
//---------------------------------------------------------------------------
PSS_UnitManager::PSS_UnitManager(const PSS_UnitManager& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_UnitManager::~PSS_UnitManager()
{
    // NOTE use the fully qualified name here to avoid to call a pure virtual function during the destruction
    PSS_UnitManager::UnloadAllUnits();
}
//---------------------------------------------------------------------------
const PSS_UnitManager& PSS_UnitManager::operator = (const PSS_UnitManager& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_UnitManager::Initialize(PSS_ProcessModelDocTmpl* pDocTmpl)
{
    m_pDocTmpl = pDocTmpl;
}
//---------------------------------------------------------------------------
std::size_t PSS_UnitManager::FillModelSet(PSS_ModelSet& set)
{
    set.RemoveAllModel();

    for (std::size_t i = 0; i < GetUnitCount(); ++i)
    {
        PSS_Unit* pUnit = GetUnitAt(i);

        if (!pUnit)
            continue;

        ZDProcessGraphModelDoc* pDoc = pUnit->GetUnitDocument();

        if (!pDoc)
            continue;

        ZDProcessGraphModelMdl* pModel = pUnit->GetUnitDocument()->GetModel();

        if (!pModel)
            continue;

        set.AddModel(pModel);
    }

    return set.GetModelCount();
}
//---------------------------------------------------------------------------
PSS_Unit* PSS_UnitManager::CreateNewUnit(const CString& name, const CString& fileName)
{
    std::unique_ptr<PSS_Unit> pNewUnit(new PSS_Unit());

    if (!pNewUnit->Create(name, fileName))
        return NULL;

    if (!AddUnit(pNewUnit.get()))
        return NULL;

    return pNewUnit.release();
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::AddUnit(PSS_Unit* pUnit)
{
    const std::size_t prevCount = GetUnitCount();
    m_UnitSet.Add(pUnit);
    return (GetUnitCount() > prevCount);
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::LoadAllUnits()
{
    // no document template, error
    if (!m_pDocTmpl)
        return false;

    const std::size_t unitCount     = GetUnitCount();
    bool              containsError = false;

    for (std::size_t i = 0; i < unitCount; ++i)
    {
        PSS_Unit* pUnit = GetUnitAt(i);

        if (!pUnit || !pUnit->LoadUnit(m_pDocTmpl))
            containsError = true;
    }

    return containsError;
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::LoadUnit(PSS_Unit* pUnit)
{
    // no document template, error
    if (!m_pDocTmpl)
        return false;

    return pUnit->LoadUnit(m_pDocTmpl);
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::LoadUnit(const CString& name)
{
    // no document template, error
    if (!m_pDocTmpl)
        return false;

    PSS_Unit* pUnit = FindUnit(name);

    if (pUnit)
        return pUnit->LoadUnit(m_pDocTmpl);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::LoadUnitByKey(const CString& key)
{
    // no document template, error
    if (!m_pDocTmpl)
        return false;

    PSS_Unit* pUnit = FindUnitByKey(key);

    if (pUnit)
        return pUnit->LoadUnit(m_pDocTmpl);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::UnloadAllUnits()
{
    const std::size_t unitCount     = GetUnitCount();
    bool              containsError = false;

    for (std::size_t i = 0; i < unitCount; ++i)
    {
        PSS_Unit* pUnit = GetUnitAt(i);

        if (!pUnit || !pUnit->UnloadUnit())
            containsError = true;
    }

    return containsError;
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::UnloadUnit(PSS_Unit* pUnit)
{
    return pUnit->UnloadUnit();
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::UnloadUnit(const CString& name)
{
    PSS_Unit* pUnit = FindUnit(name);

    if (pUnit)
        return pUnit->UnloadUnit();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::UnloadUnitByKey(const CString& key)
{
    PSS_Unit* pUnit = FindUnitByKey(key);

    if (pUnit)
        return pUnit->UnloadUnit();

    return false;
}
//---------------------------------------------------------------------------
void PSS_UnitManager::RemoveAllUnits()
{
    m_UnitSet.RemoveAll();
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::RemoveUnitAt(std::size_t index)
{
    if (index < GetUnitCount())
    {
        m_UnitSet.RemoveAt(index);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::RemoveUnit(PSS_Unit* pUnit)
{
    if (!pUnit)
        return false;

    const std::size_t unitCount = GetUnitCount();

    for (std::size_t i = 0; i < unitCount; ++i)
    {
        PSS_Unit* pCurUnit = GetUnitAt(i);

        if (pCurUnit == pUnit)
        {
            RemoveUnitAt(i);
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::RemoveUnit(const CString& name)
{
    const std::size_t unitCount = GetUnitCount();

    for (std::size_t i = 0; i < unitCount; ++i)
    {
        PSS_Unit* pUnit = GetUnitAt(i);

        if (pUnit && pUnit->GetName() == name)
        {
            RemoveUnitAt(i);
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UnitManager::RemoveUnitByKey(const CString& key)
{
    const std::size_t unitCount = GetUnitCount();

    for (size_t i = 0; i < unitCount; ++i)
    {
        PSS_Unit* pUnit = GetUnitAt(i);

        if (pUnit && pUnit->GetKey() == key)
        {
            RemoveUnitAt(i);
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
PSS_Unit* PSS_UnitManager::FindUnit(const CString& name)
{
    const std::size_t unitCount = GetUnitCount();

    for (std::size_t i = 0; i < unitCount; ++i)
    {
        PSS_Unit* pUnit = GetUnitAt(i);

        if (pUnit && pUnit->GetName() == name)
            return pUnit;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_Unit* PSS_UnitManager::FindUnitByKey(const CString& key)
{
    const std::size_t unitCount = GetUnitCount();

    for (std::size_t i = 0; i < unitCount; ++i)
    {
        PSS_Unit* pUnit = GetUnitAt(i);

        if (pUnit->GetKey() == key)
            return pUnit;
    }

    return NULL;
}
//---------------------------------------------------------------------------
int PSS_UnitManager::FindUnitIndex(const CString& name)
{
    const std::size_t unitCount = GetUnitCount();

    for (std::size_t i = 0; i < unitCount; ++i)
    {
        PSS_Unit* pUnit = GetUnitAt(i);

        if (pUnit && pUnit->GetName() == name)
            return int(i);
    }

    return -1;
}
//---------------------------------------------------------------------------
int PSS_UnitManager::FindUnitIndexByKey(const CString& key)
{
    const std::size_t unitCount = GetUnitCount();

    for (std::size_t i = 0; i < unitCount; ++i)
    {
        PSS_Unit* pUnit = GetUnitAt(i);

        if (pUnit && pUnit->GetKey() == key)
            return int(i);
    }

    return -1;
}
//---------------------------------------------------------------------------
PSS_Unit* PSS_UnitManager::GetUnitAt(std::size_t index)
{
    if (index < GetUnitCount())
        return static_cast<PSS_Unit*>(m_UnitSet.GetAt(index));

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_UnitManager::Serialize(CArchive& ar)
{
    m_UnitSet.Serialize(ar);
}
//---------------------------------------------------------------------------
