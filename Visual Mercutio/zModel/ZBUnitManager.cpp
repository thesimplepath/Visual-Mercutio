// ZBUnitManager.cpp: implementation of the ZBUnitManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBUnitManager.h"

// processsoft
#include "PSS_ProcessGraphModelDoc.h"
#include "PSS_ModelSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(ZBUnitManager, CObject, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBUnitManager::ZBUnitManager(PSS_ProcessModelDocTmpl* pDocTmpl) :
    m_pDocTmpl(pDocTmpl)
{}

ZBUnitManager::~ZBUnitManager()
{
    UnloadAllUnits();
}

void    ZBUnitManager::Initialize(PSS_ProcessModelDocTmpl* pDocTmpl)
{
    m_pDocTmpl = pDocTmpl;
}

std::size_t ZBUnitManager::FillModelSet(PSS_ModelSet& Set)
{
    Set.RemoveAllModel();
    for (size_t i = 0; i < GetUnitCount(); ++i)
    {
        PSS_Unit*    pU = GetUnitAt(i);
        if (pU && pU->GetUnitDocument()->GetModel())
            Set.AddModel(pU->GetUnitDocument()->GetModel());
    }
    return Set.GetModelCount();
}

// Load and Unload unit functions

bool    ZBUnitManager::LoadAllUnits()
{
    // No document template, error
    if (!m_pDocTmpl)
        return false;

    bool    ContainsError = false;
    for (size_t i = 0; i < GetUnitCount(); ++i)
    {
        PSS_Unit*    pU = GetUnitAt(i);
        if (!pU->LoadUnit(m_pDocTmpl))
        {
            ContainsError = true;
        }
    }
    return ContainsError;
}

bool    ZBUnitManager::LoadUnit(PSS_Unit* pUnit)
{
    // No document template, error
    if (!m_pDocTmpl)
        return false;
    return pUnit->LoadUnit(m_pDocTmpl);
}

bool    ZBUnitManager::LoadUnit(const CString Name)
{
    // No document template, error
    if (!m_pDocTmpl)
        return false;

    PSS_Unit*    pU = FindUnit(Name);
    if (pU)
        return pU->LoadUnit(m_pDocTmpl);
    return false;
}

bool    ZBUnitManager::LoadUnitByKey(const CString Key)
{
    // No document template, error
    if (!m_pDocTmpl)
        return false;

    PSS_Unit*    pU = FindUnitByKey(Key);
    if (pU)
        return pU->LoadUnit(m_pDocTmpl);
    return false;
}


bool    ZBUnitManager::UnloadAllUnits()
{
    bool    ContainsError = false;
    for (size_t i = 0; i < GetUnitCount(); ++i)
    {
        PSS_Unit*    pU = GetUnitAt(i);
        if (!pU->UnloadUnit())
        {
            ContainsError = true;
        }
    }
    return ContainsError;
}

bool    ZBUnitManager::UnloadUnit(PSS_Unit* pUnit)
{
    return pUnit->UnloadUnit();
}

bool    ZBUnitManager::UnloadUnit(const CString Name)
{
    PSS_Unit*    pU = FindUnit(Name);
    if (pU)
        return pU->UnloadUnit();
    return false;
}

bool    ZBUnitManager::UnloadUnitByKey(const CString Key)
{
    PSS_Unit*    pU = FindUnitByKey(Key);
    if (pU)
        return pU->UnloadUnit();
    return false;
}



// UnitSet management

void    ZBUnitManager::RemoveAllUnits()
{
    m_UnitSet.RemoveAll();
}


bool    ZBUnitManager::RemoveUnitAt(size_t Index)
{
    if (Index < GetUnitCount())
    {
        m_UnitSet.RemoveAt(Index);
        return true;
    }
    return false;
}

bool    ZBUnitManager::RemoveUnit(PSS_Unit* pUnit)
{
    for (size_t i = 0; i < GetUnitCount(); ++i)
    {
        PSS_Unit*    pU = GetUnitAt(i);
        if (pU == pUnit)
        {
            RemoveUnitAt(i);
            return true;
        }
    }
    return false;
}

bool    ZBUnitManager::RemoveUnit(const CString Name)
{
    for (size_t i = 0; i < GetUnitCount(); ++i)
    {
        PSS_Unit*    pU = GetUnitAt(i);
        if (pU->GetName() == Name)
        {
            RemoveUnitAt(i);
            return true;
        }
    }
    return false;
}

bool    ZBUnitManager::RemoveUnitByKey(const CString Key)
{
    for (size_t i = 0; i < GetUnitCount(); ++i)
    {
        PSS_Unit*    pU = GetUnitAt(i);
        if (pU->GetKey() == Key)
        {
            RemoveUnitAt(i);
            return true;
        }
    }
    return false;
}


PSS_Unit*    ZBUnitManager::FindUnit(const CString Name)
{
    for (size_t i = 0; i < GetUnitCount(); ++i)
    {
        ZBUnit*    pU = GetUnitAt(i);
        if (pU->GetName() == Name)
            return pU;
    }
    return NULL;
}


PSS_Unit*    ZBUnitManager::FindUnitByKey(const CString Key)
{
    for (size_t i = 0; i < GetUnitCount(); ++i)
    {
        PSS_Unit*    pU = GetUnitAt(i);
        if (pU->GetKey() == Key)
            return pU;
    }
    return NULL;
}


int    ZBUnitManager::FindUnitIndex(const CString Name)
{
    for (size_t i = 0; i < GetUnitCount(); ++i)
    {
        ZBUnit*    pU = GetUnitAt(i);
        if (pU->GetName() == Name)
            return (int)i;
    }
    return -1;
}

int    ZBUnitManager::FindUnitIndexByKey(const CString Key)
{
    for (size_t i = 0; i < GetUnitCount(); ++i)
    {
        PSS_Unit*    pU = GetUnitAt(i);
        if (pU->GetKey() == Key)
            return (int)i;
    }
    return -1;

}

PSS_Unit*    ZBUnitManager::GetUnitAt(size_t Index)
{
    if (Index < GetUnitCount())
        return (PSS_Unit*)m_UnitSet.GetAt(Index);
    return NULL;
}

bool    ZBUnitManager::AddUnit(PSS_Unit* pUnit)
{
    size_t    PreviousCount = GetUnitCount();
    m_UnitSet.Add(pUnit);
    return GetUnitCount() > PreviousCount;
}

PSS_Unit*    ZBUnitManager::CreateNewUnit(const CString Name, const CString fileName /*= ""*/)
{
    PSS_Unit*    pNewUnit = new PSS_Unit;
    if (!pNewUnit->Create(Name, fileName))
    {
        delete pNewUnit;
        pNewUnit = NULL;
    }
    if (!AddUnit(pNewUnit))
    {
        delete pNewUnit;
        pNewUnit = NULL;
    }

    return pNewUnit;
}


// Serializes the unit
void ZBUnitManager::Serialize(CArchive& ar)
{
    m_UnitSet.Serialize(ar);
}
