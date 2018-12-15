// ZBDistributionAttributes.h: interface for the ZBDistributionAttribute class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBDistributionAttributes_H__30293825_AA01_4900_B87E_808BA14EE11B__INCLUDED_)
#define AFX_ZBDistributionAttributes_H__30293825_AA01_4900_B87E_808BA14EE11B__INCLUDED_

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


#include "zModelBP\ZBDistributionRules.h"

//////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBUserGroupEntity;


#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


///////////////////////////////////////////////////////////////////////////
// ZBDistributionRulesForRole class definition


class AFX_EXT_CLASS ZBDistributionRulesForRole : public CObject  
{
    DECLARE_SERIAL(ZBDistributionRulesForRole)
public:
    ZBDistributionRulesForRole(CString RoleGUID = "");
    virtual ~ZBDistributionRulesForRole();

    /* Copy constructor. */
    ZBDistributionRulesForRole(const ZBDistributionRulesForRole& src);
    /* Assignment operator. */
    ZBDistributionRulesForRole& operator=(const ZBDistributionRulesForRole& src);
    /* Equal operator */
    BOOL operator == (const ZBDistributionRulesForRole& Distrib);
    /* Not Equal operator */
    BOOL operator != (const ZBDistributionRulesForRole& Distrib);
    /* Create a duplicate copy of this object. */
    virtual ZBDistributionRulesForRole* Dup() const;

    // Member accessors.
    CString GetRoleGUID() const;
    void SetRoleGUID( CString value );


    // Distrubution rule methods
    ZBDistributionRuleSet& GetDistributionRuleSet()
    {
        return m_RulesManager.GetDistributionRuleSet();
    };
    void DeleteAllDistributionRule()
    {
        m_RulesManager.DeleteAllDistributionRule();
    };
    ZBDistributionRule* GetDistributionRuleAt( size_t Index )
    {
        return m_RulesManager.GetDistributionRuleAt( Index );
    };
    size_t GetDistributionRuleCount() const
    {
        return m_RulesManager.GetDistributionRuleCount();
    };
    void AddDistributionRule( ZBDistributionRule* pDistributionRule )
    {
        m_RulesManager.AddDistributionRule(pDistributionRule);
    };
    void AddDistributionRule( int Operator, CString Value, int LogicalOperator = -1 )
    {
        m_RulesManager.AddDistributionRule(Operator, Value, LogicalOperator);
    };
    bool Exist( ZBDistributionRule* pDistributionRule )
    {
        return m_RulesManager.Exist(pDistributionRule);
    };
    bool DeleteDistributionRule( ZBDistributionRule* pDistributionRule )
    {
        return m_RulesManager.DeleteDistributionRule(pDistributionRule);
    };

    /* Serializes the symbol. */
    virtual void Serialize(CArchive& ar);


private:
    CString m_RoleGUID;
    ZBDistributionRuleManager m_RulesManager;
};


inline CString ZBDistributionRulesForRole::GetRoleGUID() const 
{
    return m_RoleGUID;
}
inline void ZBDistributionRulesForRole::SetRoleGUID( CString value )
{
    m_RoleGUID = value;
}


inline BOOL ZBDistributionRulesForRole::operator == (const ZBDistributionRulesForRole& Distrib)
{
      return (Distrib.m_RoleGUID == this->m_RoleGUID);
}

inline BOOL ZBDistributionRulesForRole::operator != (const ZBDistributionRulesForRole& Distrib)
{
      return (Distrib.m_RoleGUID != this->m_RoleGUID);
}



/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;


///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBDistributionRulesForRoleSet | An array of ZBDistributionRulesForRole pointers.
//@iex typedef CCArray_T<ZBDistributionRulesForRole*,ZBDistributionRulesForRole*> ZBDistributionRulesForRoleSet;
typedef CCArray_T<ZBDistributionRulesForRole*,ZBDistributionRulesForRole*> ZBDistributionRulesForRoleSet;

//@type ZBDistributionRulesForRole | An iterator for ZBDistributionRulesForRoleSet collections.
//@iex typedef Iterator_T<ZBDistributionRulesForRole*> ZBDistributionRulesForRoleIterator;
typedef Iterator_T<ZBDistributionRulesForRole*> ZBDistributionRulesForRoleIterator;




///////////////////////////////////////////////////////////////////////////
// ZBDistributionAttribute class definition

class AFX_EXT_CLASS ZBDistributionAttribute : public CObject  
{
    DECLARE_SERIAL(ZBDistributionAttribute)
public:
    ZBDistributionAttribute();
    virtual ~ZBDistributionAttribute();

    /* Copy constructor. */
    ZBDistributionAttribute(const ZBDistributionAttribute& src);
    /* Assignment operator. */
    ZBDistributionAttribute& operator=(const ZBDistributionAttribute& src);
    /* Equal operator */
    BOOL operator == (const ZBDistributionAttribute& Distrib);
    /* Not Equal operator */
    BOOL operator != (const ZBDistributionAttribute& Distrib);
    /* Create a duplicate copy of this object. */
    virtual ZBDistributionAttribute* Dup() const;

    // Member accessors.
    int GetCategoryID() const;
    void SetCategoryID( int value );

    int GetItemID() const;
    void SetItemID( int value );

    int GetSymbolRef() const;
    void SetSymbolRef( int value );

    CString GetUserGroupGUID() const;
    void SetUserGroupGUID( CString value );


    // Role distribution rule methods
    void DeleteAllDistributionRulesForAllRoles();
    void DeleteAllDistributionRulesForRole( const CString RoleGUID );
    void AddDistributionRulesForRole( const CString RoleGUID );
    void AddDistributionRulesForRole( const CString RoleGUID, int Operator, CString Value, int LogicalOperator = -1 );
    void AddDistributionRulesForRole( ZBDistributionRulesForRole* pDistributionRulesForRole );
    ZBDistributionRulesForRole* FindDistributionRulesForRole( const CString RoleGUID ) const;
    bool DeleteDistributionRulesForRole( ZBDistributionRulesForRole* pDistributionRulesForRole );
    bool Exist( ZBDistributionRulesForRole* pDistributionRulesForRole ) const;
    bool Exist( const CString RoleGUID ) const
    {
        return (FindDistributionRulesForRole( RoleGUID ) != NULL) ? true : false;
    };

    bool ExistDistributionRule( ZBDistributionRule* pRule );
    bool DeleteDistributionRule( ZBDistributionRule* pRule );

    ZBDistributionRuleSet* GetDistributionRuleSet( const CString RoleGUID );
    ZBDistributionRule* GetDistributionRuleAt(  const CString RoleGUID, size_t Index );
    size_t GetDistributionRuleCount( const CString RoleGUID ) const;

    ZBDistributionRulesForRoleSet& GetDistributionRulesForRoleSet()
    {
        return m_Set;
    };
    ZBDistributionRulesForRole* GetDistributionRulesForRoleAt( size_t Index )
    {
        if (Index < GetDistributionRulesForRoleCount())
            return m_Set.GetAt( Index );
        return NULL;
    };
    bool DeleteDistributionRulesForRoleAt( size_t Index )
    {
        if (Index < GetDistributionRulesForRoleCount())
        {
            // Delete the object first
            delete GetDistributionRulesForRoleAt( Index );
            m_Set.RemoveAt( Index );
            return true;
        }
        return false;
    };
    size_t GetDistributionRulesForRoleCount() const
    {
        return m_Set.GetSize();
    };

    /* Serializes the symbol. */
    virtual void Serialize(CArchive& ar);


private:
    int m_CategoryID;
    int m_ItemID;
    int m_SymbolRef;
    CString m_UserGroupGUID;
    ZBDistributionRulesForRoleSet m_Set;
};


inline int ZBDistributionAttribute::GetCategoryID() const 
{
    return m_CategoryID;
}
inline void ZBDistributionAttribute::SetCategoryID( int value )
{
    m_CategoryID = value;
}


inline int ZBDistributionAttribute::GetItemID() const 
{
    return m_ItemID;
}
inline void ZBDistributionAttribute::SetItemID( int value )
{
    m_ItemID = value;
}


inline int ZBDistributionAttribute::GetSymbolRef() const 
{
    return m_SymbolRef;
}
inline void ZBDistributionAttribute::SetSymbolRef( int value )
{
    m_SymbolRef = value;
}


inline CString ZBDistributionAttribute::GetUserGroupGUID() const 
{
    return m_UserGroupGUID;
}
inline void ZBDistributionAttribute::SetUserGroupGUID( CString value )
{
    m_UserGroupGUID = value;
}


inline BOOL ZBDistributionAttribute::operator == (const ZBDistributionAttribute& Distrib)
{
      return (Distrib.m_CategoryID == this->m_CategoryID &&
            Distrib.m_ItemID == this->m_ItemID &&
            Distrib.m_UserGroupGUID == this->m_UserGroupGUID);
}

inline BOOL ZBDistributionAttribute::operator != (const ZBDistributionAttribute& Distrib)
{
      return (Distrib.m_CategoryID != this->m_CategoryID ||
            Distrib.m_ItemID != this->m_ItemID ||
            Distrib.m_UserGroupGUID != this->m_UserGroupGUID);
}






///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBDistributionAttributeSet | An array of ZBDistributionAttribute pointers.
//@iex typedef CCArray_T<ZBDistributionAttribute*,ZBDistributionAttribute*> ZBDistributionAttributeSet;
typedef CCArray_T<ZBDistributionAttribute*,ZBDistributionAttribute*> ZBDistributionAttributeSet;

//@type ZBDistributionAttribute | An iterator for ZBDistributionAttributeSet collections.
//@iex typedef Iterator_T<ZBDistributionAttribute*> ZBDistributionAttributeIterator;
typedef Iterator_T<ZBDistributionAttribute*> ZBDistributionAttributeIterator;


///////////////////////////////////////////////////////////////////////////
// ZBDistributionAttributeManager class definition


class AFX_EXT_CLASS ZBDistributionAttributeManager : public CObject
{
    DECLARE_SERIAL(ZBDistributionAttributeManager)

public:
    ZBDistributionAttributeManager();
    virtual ~ZBDistributionAttributeManager();
    /* Copy constructor. */
    ZBDistributionAttributeManager(const ZBDistributionAttributeManager& src);
    /* Assignment operator. */
    ZBDistributionAttributeManager& operator=(const ZBDistributionAttributeManager& src);
    /* Create a duplicate copy of this object. */
    virtual ZBDistributionAttributeManager* Dup() const;

    /* Serializes the symbol. */
    virtual void Serialize(CArchive& ar);

    ZBDistributionAttributeSet& GetDistributionAttributeSet()
    {
        return m_Set;
    };
    void FreePropertiesSet();
    void AddDistributionAttribute( ZBDistributionAttribute* pDistributionAttribute, bool ReplaceExisting = true );
    bool Exist( ZBDistributionAttribute* pDistributionAttribute );
    bool DeleteDistributionAttribute( ZBDistributionAttribute* pDistributionAttribute );
    ZBDistributionAttribute* FindDistributionAttribute( int CategoryID, int ItemID, CString UserGroupGUID );

    bool DeleteDistributionRule( ZBDistributionRule* pRule );

    bool CheckDistributionRole( ZBDistributionAttribute* pDistributionAttribute, ZBUserGroupEntity* pMainUserGroup );

private:
    void ReplaceDistributionAttribute( ZBDistributionAttribute* pDistributionAttribute );

private:
    ZBDistributionAttributeSet m_Set;

};

#endif // !defined(AFX_ZBDistributionAttributes_H__30293825_AA01_4900_B87E_808BA14EE11B__INCLUDED_)



