// ZBUnitManager.h: interface for the ZBUnitManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBUNITMANAGER_H__B10D7C0F_7F60_408B_80A8_803A62263396__INCLUDED_)
#define AFX_ZBUNITMANAGER_H__B10D7C0F_7F60_408B_80A8_803A62263396__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_ProcessModelDocTmpl.h"
#include "PSS_Unit.h"

// class name mapping
#ifndef PSS_ModelSet
    #define PSS_ModelSet ZBModelSet
#endif

class PSS_ModelSet;

#ifdef _ZMODELEXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZBUnitManager : public CObject
{
    DECLARE_SERIAL(ZBUnitManager)

public:
    ZBUnitManager(PSS_ProcessModelDocTmpl* pDocTmpl = NULL);
    virtual ~ZBUnitManager();

    void    Initialize(PSS_ProcessModelDocTmpl* pDocTmpl);

    std::size_t FillModelSet(PSS_ModelSet& set);

    bool    LoadAllUnits();
    bool    LoadUnit(PSS_Unit* pUnit);
    bool    LoadUnit(const CString Name);
    bool    LoadUnitByKey(const CString Key);

    bool    UnloadAllUnits();
    bool    UnloadUnit(PSS_Unit* pUnit);
    bool    UnloadUnit(const CString Name);
    bool    UnloadUnitByKey(const CString Key);

    void    RemoveAllUnits();
    bool    RemoveUnitAt(size_t Index);
    bool    RemoveUnit(PSS_Unit* pUnit);
    bool    RemoveUnit(const CString Name);
    bool    RemoveUnitByKey(const CString Key);

    PSS_Unit*    FindUnit(const CString Name);
    PSS_Unit*    FindUnitByKey(const CString Key);
    int        FindUnitIndex(const CString Name);
    int        FindUnitIndexByKey(const CString Key);


    size_t    GetUnitCount() const;
    PSS_Unit*    GetUnitAt(size_t Index);
    bool    AddUnit(PSS_Unit* pUnit);
    PSS_Unit*    CreateNewUnit(const CString Name, const CString fileName = "");

    // Serializes the unit manager
    virtual void Serialize(CArchive& ar);

private:
    CObArray                 m_UnitSet;
    PSS_ProcessModelDocTmpl* m_pDocTmpl;

private:
    // No Copy constructor
    ZBUnitManager(const ZBUnitManager& src);
    // No Assignment operator
    ZBUnitManager& operator=(const ZBUnitManager& src);

};

inline std::size_t ZBUnitManager::GetUnitCount() const
{
    return std::size_t(m_UnitSet.GetSize());
}

#endif
