// ******************************************************************************************************************
// *                                        Classe ZDLogicalRulesEntity                                                *
// ******************************************************************************************************************
// * JMR-MODIF - Le 14 novembre 2006 - Ajout de la classe ZDLogicalRulesEntity.                                        *
// ******************************************************************************************************************
// * Cette classe représente une entité de type règle.    Une entité peut être considérée comme un élément du            *
// * document.                                                                                                        *
// ******************************************************************************************************************

#if !defined(AFX_ZBLogicalRulesEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_)
#define AFX_ZBLogicalRulesEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_

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

#include "ZBRulesEntity.h"

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
const CString gLogicalRulesKey = _T( "$LR=" );

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBRulesEntitySet | An array of ZBRulesEntity pointers.
//@iex typedef CCArray_T<ZBRulesEntity*,ZBRulesEntity*> ZBRulesEntitySet;
typedef CCArray_T<ZBRulesEntity*,ZBRulesEntity*> ZBRulesEntitySet;

//@type ZBRulesEntityIterator | An iterator for ZBRulesEntitySet collections.
//@iex typedef Iterator_T<ZBRulesEntity*> ZBRulesEntityIterator;
typedef Iterator_T<ZBRulesEntity*> ZBRulesEntityIterator;

class AFX_EXT_CLASS ZBLogicalRulesEntity : public ZBRulesEntity
{
    DECLARE_SERIAL( ZBLogicalRulesEntity )

public:

    ZBLogicalRulesEntity( const CString        Name        = _T( "" ),
                          const CString        Description    = _T( "" ),
                          ZBRulesEntity*    pParent        = NULL );

    ~ZBLogicalRulesEntity();

    void RemoveAllRulesEntities();

    virtual bool ContainEntity() const
    {
        return true;
    }

    virtual size_t GetEntityCount() const
    {
        return m_EntitySet.GetSize();
    }

    virtual ZBRulesEntity* GetEntityAt( size_t Index )
    {
        return ( Index < GetEntityCount() ) ? m_EntitySet.GetAt( Index ) : NULL;
    }

    virtual ZBRulesEntitySet* GetEntitySet()
    {
        return &m_EntitySet;
    }

    // Modified flag functions
    virtual BOOL IsModified()
    {
        return m_bModified;
    }

    virtual void SetModifiedFlag( BOOL bModified = TRUE )
    {
        m_bModified = bModified;
    }

    ////////////////////////////////////////////////////////////////
    // Group management functions
    ZBLogicalRulesEntity* AddRule( const CString Name, const CString Description );

    ZBLogicalRulesEntity* AddRule( const CString Name,
                                   const CString Description,
                                   const CString InRuleName );

    ZBLogicalRulesEntity* AddRule( const CString            Name,
                                   const CString            Description,
                                   ZBLogicalRulesEntity*    pInRule );

    bool RemoveRule( const CString Name, bool Deeper = false );
    bool RemoveRule( const CString Name, const CString InRuleName );
    bool RemoveRule( const CString Name, ZBLogicalRulesEntity* pInRule );
    bool RemoveRule( ZBLogicalRulesEntity* pRule );

    ZBRulesEntity* FindRuleByGUID( const CString GUID, bool Deeper = false );

    ZBRulesEntitySet* FindRule( const CString Name, bool Deeper = false );
    ZBRulesEntitySet* FindRule( const CString Name, const CString InRuleName );
    ZBRulesEntitySet* FindRule( const CString Name, ZBLogicalRulesEntity* pInRule );

    bool RuleExist( const CString Name, bool Deeper = false );
    bool RuleExist( const CString Name, const CString InRuleName );
    bool RuleExist( const CString Name, ZBLogicalRulesEntity* pInRule );

    bool MoveRule( ZBRulesEntity* pRule );

    // Serialization mechanism
    virtual void Serialize( CArchive& ar );    // Overridden for document i/o

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

    bool AddRule( ZBRulesEntity* pRule )
    {
        m_EntitySet.Add( pRule );
        return true;
    }

    bool RemoveRuleFromSet( ZBRulesEntity* pRule );

    ////////////////////////////////////////////////////////////////
    // Group management functions
    ZBRulesEntity* _FindRuleByGUID( const CString GUID, bool Deeper = false );

    void _FindRule( const CString Name, ZBLogicalRulesEntity* pInRule );
    void _FindRule( const CString Name, bool Deeper = false );

    ZBLogicalRulesEntity* _FindFirstRule( const CString Name, ZBLogicalRulesEntity* pInRule );
    ZBLogicalRulesEntity* _FindFirstRule( const CString Name, bool Deeper = false );

    bool _RemoveRules( ZBRulesEntitySet& Set );

    void RecalculateParent();

// Members are protected, since they need to be access directly by sub-class
protected:

    ZBRulesEntitySet        m_EntitySet;

    static ZBRulesEntitySet    m_FindSet;
    static BOOL                m_bModified;
};

#endif // !defined(AFX_ZBLogicalRulesEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_)