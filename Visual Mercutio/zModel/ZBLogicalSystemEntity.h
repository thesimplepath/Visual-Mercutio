// ZBLogicalSystemEntity.h: interface for the ZBLogicalSystemEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBLogicalSystemEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_)
#define AFX_ZBLogicalSystemEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_

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

#include "ZBSystemEntity.h"

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Constant
const CString gLogicalSystemKey = _T( "$LS=" );

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBSystemEntitySet | An array of ZBSystemEntity pointers.
//@iex typedef CCArray_T<ZBSystemEntity*,ZBSystemEntity*> ZBSystemEntitySet;
typedef CCArray_T<ZBSystemEntity*,ZBSystemEntity*> ZBSystemEntitySet;

//@type ZBSystemEntityIterator | An iterator for ZBSystemEntitySet collections.
//@iex typedef Iterator_T<ZBSystemEntity*> ZBSystemEntityIterator;
typedef Iterator_T<ZBSystemEntity*> ZBSystemEntityIterator;

class AFX_EXT_CLASS ZBLogicalSystemEntity : public ZBSystemEntity
{
    DECLARE_SERIAL( ZBLogicalSystemEntity )

public:

    ZBLogicalSystemEntity(    const CString    Name        = _T( "" ),
                            const CString    Description    = _T( "" ),
                            ZBSystemEntity*    pParent        = NULL );

    virtual ~ZBLogicalSystemEntity();

    void RemoveAllSystemEntities();

    virtual bool ContainEntity() const
    {
        return true;
    };

    virtual size_t GetEntityCount() const
    {
        return m_EntitySet.GetSize();
    };

    virtual ZBSystemEntity* GetEntityAt( size_t Index )
    {
        return ( Index < GetEntityCount() ) ? m_EntitySet.GetAt( Index ) : NULL;
    };

    virtual ZBSystemEntitySet* GetEntitySet()
    {
        return &m_EntitySet;
    };

    // Modified flag functions
    virtual BOOL IsModified()
    {
        return m_bModified;
    };

    virtual void SetModifiedFlag( BOOL bModified = TRUE )
    {
        m_bModified = bModified;
    };

    ////////////////////////////////////////////////////////////////
    // Group management functions
    ZBLogicalSystemEntity* AddSystem( const CString Name, const CString Description );
    ZBLogicalSystemEntity* AddSystem( const CString Name, const CString Description, const CString InSystemName );
    ZBLogicalSystemEntity* AddSystem( const CString                Name,
                                      const CString                Description,
                                      ZBLogicalSystemEntity*    pInSystem );

    bool RemoveSystem( const CString Name, bool Deeper = false );
    bool RemoveSystem( const CString Name, const CString InSystemName );
    bool RemoveSystem( const CString Name, ZBLogicalSystemEntity* pInSystem );
    bool RemoveSystem( ZBLogicalSystemEntity* pGroup );

    ZBSystemEntity* FindSystemByGUID( const CString GUID, bool Deeper = false );

    ZBSystemEntitySet* FindSystem( const CString Name, bool Deeper = false );
    ZBSystemEntitySet* FindSystem( const CString Name, const CString InSystemName );
    ZBSystemEntitySet* FindSystem( const CString Name, ZBLogicalSystemEntity* pInSystem );
    bool SystemExist( const CString Name, bool Deeper = false );
    bool SystemExist( const CString Name, const CString InSystemName );
    bool SystemExist( const CString Name, ZBLogicalSystemEntity* pInSystem );

    // JMR-MODIF - Le 27 février 2006 - Ajout de la fonction MoveSystem.
    bool MoveSystem( ZBSystemEntity* pSystem );

    // Serialization mechanism
    virtual void Serialize( CArchive& ar );   // overridden for document i/o

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

    // JMR-MODIF - Le 27 février 2006 - Ajout de la fonction AddSystem.
    bool AddSystem( ZBSystemEntity* pSystem )
    {
        m_EntitySet.Add( pSystem );
        return true;
    };

    // JMR-MODIF - Le 27 février 2006 - Ajout de la fonction RemoveSystemFromSet.
    bool RemoveSystemFromSet( ZBSystemEntity* pSystem );

    ////////////////////////////////////////////////////////////////
    // Group management functions
    ZBSystemEntity* _FindSystemByGUID( const CString GUID, bool Deeper = false );
    void _FindSystem( const CString Name, ZBLogicalSystemEntity* pInSystem );
    void _FindSystem( const CString Name, bool Deeper = false );
    ZBLogicalSystemEntity* _FindFirstSystem( const CString Name, ZBLogicalSystemEntity* pInSystem );
    ZBLogicalSystemEntity* _FindFirstSystem( const CString Name, bool Deeper = false );
    bool _RemoveSystems( ZBSystemEntitySet& Set );

    void RecalculateParent();

// Members are protected, since they need to be access directly by sub-class
protected:

    ZBSystemEntitySet            m_EntitySet;

    static ZBSystemEntitySet    m_FindSet;
    static BOOL                    m_bModified;
};

#endif // !defined(AFX_ZBLogicalSystemEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_)