// ******************************************************************************************************************
// *                                        Classe ZDLogicalPrestationsEntity                                        *
// ******************************************************************************************************************
// * JMR-MODIF - Le 7 octobre 2005 - Ajout de la classe ZDLogicalPrestationsEntity.                                    *
// ******************************************************************************************************************
// * Cette classe représente une entité de type prestation.    Une entité peut être considérée comme un élément du        *
// * document.                                                                                                        *
// ******************************************************************************************************************

#if !defined(AFX_ZBLogicalPrestationsEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_)
#define AFX_ZBLogicalPrestationsEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ZBPrestationsEntity.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//////////////////////////////////////////////////////////////////////
// Constant
const CString gLogicalPrestationsKey = _T( "$LP=" );

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBPrestationsEntitySet | An array of ZBPrestationsEntity pointers.
//@iex typedef CCArray_T<ZBPrestationsEntity*,ZBPrestationsEntity*> ZBPrestationsEntitySet;
typedef CCArray_T<ZBPrestationsEntity*,ZBPrestationsEntity*> ZBPrestationsEntitySet;

//@type ZBPrestationsEntityIterator | An iterator for ZBPrestationsEntitySet collections.
//@iex typedef Iterator_T<ZBPrestationsEntity*> ZBPrestationsEntityIterator;
typedef Iterator_T<ZBPrestationsEntity*> ZBPrestationsEntityIterator;

class AFX_EXT_CLASS ZBLogicalPrestationsEntity : public ZBPrestationsEntity
{
    DECLARE_SERIAL( ZBLogicalPrestationsEntity )

public:

    ZBLogicalPrestationsEntity( const CString            Name        = _T( "" ),
                                const CString            Description    = _T( "" ),
                                ZBPrestationsEntity*    pParent        = NULL );

    ~ZBLogicalPrestationsEntity();

    void RemoveAllPrestationsEntities();

    virtual bool ContainEntity() const
    {
        return true;
    };

    virtual size_t GetEntityCount() const
    {
        return m_EntitySet.GetSize();
    };

    virtual ZBPrestationsEntity* GetEntityAt( size_t Index )
    {
        return ( Index < GetEntityCount() ) ? m_EntitySet.GetAt( Index ) : NULL;
    };

    virtual ZBPrestationsEntitySet* GetEntitySet()
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
    ZBLogicalPrestationsEntity* AddPrestation( const CString Name, const CString Description );

    ZBLogicalPrestationsEntity* AddPrestation( const CString Name,
                                               const CString Description,
                                               const CString InPrestationName );

    ZBLogicalPrestationsEntity* AddPrestation( const CString                Name,
                                               const CString                Description,
                                               ZBLogicalPrestationsEntity*    pInPrestation );

    bool RemovePrestation( const CString Name, bool Deeper = false );
    bool RemovePrestation( const CString Name, const CString InPrestationName );
    bool RemovePrestation( const CString Name, ZBLogicalPrestationsEntity* pInPrestation );
    bool RemovePrestation( ZBLogicalPrestationsEntity* pPrestation );

    ZBPrestationsEntity* FindPrestationByGUID( const CString GUID, bool Deeper = false );

    ZBPrestationsEntitySet* FindPrestation( const CString Name, bool Deeper = false );
    ZBPrestationsEntitySet* FindPrestation( const CString Name, const CString InPrestationName );
    ZBPrestationsEntitySet* FindPrestation( const CString Name, ZBLogicalPrestationsEntity* pInPrestation );

    bool PrestationExist( const CString Name, bool Deeper = false );
    bool PrestationExist( const CString Name, const CString InPrestationName );
    bool PrestationExist( const CString Name, ZBLogicalPrestationsEntity* pInPrestation );

    bool MovePrestation( ZBPrestationsEntity* pPrestation );

    // Serialization mechanism
    virtual void Serialize( CArchive& ar );    // Overridden for document i/o

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

    bool AddPrestation( ZBPrestationsEntity* pPrestation )
    {
        m_EntitySet.Add( pPrestation );
        return true;
    };

    bool RemovePrestationFromSet( ZBPrestationsEntity* pPrestation );

    ////////////////////////////////////////////////////////////////
    // Group management functions
    ZBPrestationsEntity* _FindPrestationByGUID( const CString GUID, bool Deeper = false );

    void _FindPrestation( const CString Name, ZBLogicalPrestationsEntity* pInPrestation );
    void _FindPrestation( const CString Name, bool Deeper = false );

    ZBLogicalPrestationsEntity* _FindFirstPrestation( const CString Name, ZBLogicalPrestationsEntity* pInPrestation );
    ZBLogicalPrestationsEntity* _FindFirstPrestation( const CString Name, bool Deeper = false );

    bool _RemovePrestations( ZBPrestationsEntitySet& Set );

    void RecalculateParent();

// Members are protected, since they need to be access directly by sub-class
protected:

    ZBPrestationsEntitySet            m_EntitySet;

    static ZBPrestationsEntitySet    m_FindSet;
    static BOOL                        m_bModified;
};

#endif // !defined(AFX_ZBLogicalPrestationsEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_)