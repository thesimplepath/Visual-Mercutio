// ZBUnitManager.h: interface for the ZBUnitManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBUNITMANAGER_H__B10D7C0F_7F60_408B_80A8_803A62263396__INCLUDED_)
#define AFX_ZBUNITMANAGER_H__B10D7C0F_7F60_408B_80A8_803A62263396__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZBUnit.h"
#include "zBaseLib\ProcessModelDocTmpl.h"


class ZBModelSet;


#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZBUnitManager : public CObject  
{
    DECLARE_SERIAL(ZBUnitManager)

public:
    ZBUnitManager(ZDProcessModelDocTmpl* pDocTmpl = NULL);
    virtual ~ZBUnitManager();

    void    Initialize(ZDProcessModelDocTmpl* pDocTmpl);

    size_t    FillModelSet( ZBModelSet& Set );

    bool    LoadAllUnits();
    bool    LoadUnit( ZBUnit* pUnit );
    bool    LoadUnit( const CString Name );
    bool    LoadUnitByKey( const CString Key );

    bool    UnloadAllUnits();
    bool    UnloadUnit( ZBUnit* pUnit );
    bool    UnloadUnit( const CString Name );
    bool    UnloadUnitByKey( const CString Key );

    void    RemoveAllUnits();
    bool    RemoveUnitAt( size_t Index );
    bool    RemoveUnit( ZBUnit* pUnit );
    bool    RemoveUnit( const CString Name );
    bool    RemoveUnitByKey( const CString Key );

    ZBUnit*    FindUnit( const CString Name );
    ZBUnit*    FindUnitByKey( const CString Key );
    int        FindUnitIndex( const CString Name );
    int        FindUnitIndexByKey( const CString Key );


    size_t    GetUnitCount() const;
    ZBUnit*    GetUnitAt( size_t Index );
    bool    AddUnit( ZBUnit* pUnit );
    ZBUnit*    CreateNewUnit( const CString Name, const CString Filename = "" );

    // Serializes the unit manager
    virtual void Serialize(CArchive& ar);

private:
    CObArray                m_UnitSet;
    ZDProcessModelDocTmpl*    m_pDocTmpl;

private:
    // No Copy constructor
    ZBUnitManager(const ZBUnitManager& src);
    // No Assignment operator
    ZBUnitManager& operator=(const ZBUnitManager& src);

};

inline size_t ZBUnitManager::GetUnitCount() const
{
    return (size_t)m_UnitSet.GetSize();
}

#endif // !defined(AFX_ZBUNITMANAGER_H__B10D7C0F_7F60_408B_80A8_803A62263396__INCLUDED_)
