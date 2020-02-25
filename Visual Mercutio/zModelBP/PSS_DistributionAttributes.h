/****************************************************************************
 * ==> PSS_DistributionAttributes ------------------------------------------*
 ****************************************************************************
 * Description : Provides the distribution attributes                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DistributionAttributesH
#define PSS_DistributionAttributesH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_DistributionRulesForRole
    #define PSS_DistributionRulesForRole ZBDistributionRulesForRole
#endif
#ifndef PSS_DistributionAttribute
    #define PSS_DistributionAttribute ZBDistributionAttribute
#endif
#ifndef PSS_DistributionAttributeManager
    #define PSS_DistributionAttributeManager ZBDistributionAttributeManager
#endif

// processsoft
#include "zModelBP\PSS_DistributionRules.h"

// old class name mapping
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif

// forward class declaration
class PSS_UserGroupEntity;

#ifdef _ZMODELBPEXPORT
    //put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// scope symbols in stingray foundation library
using namespace sfl;

/**
* Distribution rules for a role
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DistributionRulesForRole : public CObject
{
    DECLARE_SERIAL(PSS_DistributionRulesForRole)

    public:
        /**
        * Constructor
        *@param roleGUID - the role GUID
        */
        PSS_DistributionRulesForRole(const CString& roleGUID = "");

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DistributionRulesForRole(const PSS_DistributionRulesForRole& other);

        virtual ~PSS_DistributionRulesForRole();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DistributionRulesForRole& operator = (const PSS_DistributionRulesForRole& other);

        /**
        * Checks if the content of another object is equal to this one
        *@param other - the other object to compare with
        *@return TRUE if the other object content is equal, otherwise FALSE
        */
        inline BOOL operator == (const PSS_DistributionRulesForRole& other);

        /**
        * Checks if the content of another object differs from this one
        *@param other - the other object to compare with
        *@return TRUE if the other object content differs, otherwise FALSE
        */
        inline BOOL operator != (const PSS_DistributionRulesForRole& other);

        /**
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual PSS_DistributionRulesForRole* Dup() const;

        /**
        * Gets the role guid
        *@return the role guid
        */
        virtual inline CString GetRoleGUID() const;

        /**
        * Sets the role guid
        *@param value - the role guid
        */
        virtual inline void SetRoleGUID(const CString& value);

        /**
        * Gets the distribution ruleset
        *@return the distribution ruleset
        */
        virtual inline PSS_DistributionRuleManager::IDistributionRuleset& GetDistributionRuleset();

        /**
        * Deletes all the distribution rules
        */
        virtual inline void DeleteAllDistributionRule();

        /**
        * Gets the distribution rule at index
        *@param index - the index
        *@return the distribution rule, NULL if not found or on error
        */
        virtual inline PSS_DistributionRule* GetDistributionRuleAt(std::size_t index);

        /**
        * Gets the distribution rule count
        *@return the distribution rule count
        */
        virtual inline std::size_t GetDistributionRuleCount() const;

        /**
        * Adds a distribution rule
        *@param pDistributionRule - the rule to add
        */
        virtual inline void AddDistributionRule(PSS_DistributionRule* pDistributionRule);

        /**
        * Adds a distribution rule
        *@param ruleOp - the rule operator, which may be one of the following:
        *               -1 none
        *                1 ==
        *                2 <
        *                3 <=
        *                4 >=
        *                5 >
        *                6 !=
        *@param value - the value
        *@param logicalOperator - the rule logical operator, which may be one of the following:
        *                        -1 none
        *                         0 AND
        *                         1 OR
        */
        virtual inline void AddDistributionRule(int ruleOp, const CString& value, int logicalOperator = -1);

        /**
        * Checks if a distribution rule exists
        *@param pDistributionRule - the rule to check
        *@return true if the distribution rule exists, otherwise false
        */
        virtual inline bool Exist(PSS_DistributionRule* pDistributionRule);

        /**
        * Deletes a distribution rule
        *@param pDistributionRule - the rule to delete
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteDistributionRule(PSS_DistributionRule* pDistributionRule);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        PSS_DistributionRuleManager m_RulesManager;
        CString                     m_RoleGUID;
};

//---------------------------------------------------------------------------
// PSS_DistributionRulesForRole
//---------------------------------------------------------------------------
BOOL PSS_DistributionRulesForRole::operator == (const PSS_DistributionRulesForRole& other)
{
    return (m_RoleGUID == other.m_RoleGUID);
}
//---------------------------------------------------------------------------
BOOL PSS_DistributionRulesForRole::operator != (const PSS_DistributionRulesForRole& other)
{
    return (m_RoleGUID != other.m_RoleGUID);
}
//---------------------------------------------------------------------------
CString PSS_DistributionRulesForRole::GetRoleGUID() const
{
    return m_RoleGUID;
}
//---------------------------------------------------------------------------
void PSS_DistributionRulesForRole::SetRoleGUID(const CString& value)
{
    m_RoleGUID = value;
}
//---------------------------------------------------------------------------
PSS_DistributionRuleManager::IDistributionRuleset& PSS_DistributionRulesForRole::GetDistributionRuleset()
{
    return m_RulesManager.GetDistributionRuleset();
}
//---------------------------------------------------------------------------
void PSS_DistributionRulesForRole::DeleteAllDistributionRule()
{
    m_RulesManager.DeleteAllDistributionRule();
}
//---------------------------------------------------------------------------
PSS_DistributionRule* PSS_DistributionRulesForRole::GetDistributionRuleAt(std::size_t index)
{
    return m_RulesManager.GetDistributionRuleAt(index);
}
//---------------------------------------------------------------------------
std::size_t PSS_DistributionRulesForRole::GetDistributionRuleCount() const
{
    return m_RulesManager.GetDistributionRuleCount();
}
//---------------------------------------------------------------------------
void PSS_DistributionRulesForRole::AddDistributionRule(PSS_DistributionRule* pDistributionRule)
{
    m_RulesManager.AddDistributionRule(pDistributionRule);
}
//---------------------------------------------------------------------------
void PSS_DistributionRulesForRole::AddDistributionRule(int ruleOp, const CString& value, int logicalOperator)
{
    m_RulesManager.AddDistributionRule(ruleOp, value, logicalOperator);
}
//---------------------------------------------------------------------------
bool PSS_DistributionRulesForRole::Exist(PSS_DistributionRule* pDistributionRule)
{
    return m_RulesManager.Exist(pDistributionRule);
}
//---------------------------------------------------------------------------
bool PSS_DistributionRulesForRole::DeleteDistributionRule(PSS_DistributionRule* pDistributionRule)
{
    return m_RulesManager.DeleteDistributionRule(pDistributionRule);
}
//---------------------------------------------------------------------------

/**
* Distribution attribute
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DistributionAttribute : public CObject
{
    DECLARE_SERIAL(PSS_DistributionAttribute)

    public:
        typedef CCArray_T <PSS_DistributionRulesForRole*, PSS_DistributionRulesForRole*> IDistributionRulesForRoleSet;
        typedef Iterator_T<PSS_DistributionRulesForRole*>                                IDistributionRulesForRoleIterator;

        PSS_DistributionAttribute();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DistributionAttribute(const PSS_DistributionAttribute& other);

        virtual ~PSS_DistributionAttribute();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DistributionAttribute& operator = (const PSS_DistributionAttribute& other);

        /**
        * Checks if the content of another object is equal to this one
        *@param other - the other object to compare with
        *@return TRUE if the other object content is equal, otherwise FALSE
        */
        inline BOOL operator == (const PSS_DistributionAttribute& other);

        /**
        * Checks if the content of another object differs from this one
        *@param other - the other object to compare with
        *@return TRUE if the other object content differs, otherwise FALSE
        */
        inline BOOL operator != (const PSS_DistributionAttribute& other);

        /**
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual PSS_DistributionAttribute* Dup() const;

        /**
        * Gets the category identifier
        *@return the category identifier
        */
        virtual inline int GetCategoryID() const;

        /**
        * Sets the category identifier
        *@param value - the category identifier
        */
        virtual inline void SetCategoryID(int value);

        /**
        * Gets the item identifier
        *@return the item identifier
        */
        virtual inline int GetItemID() const;

        /**
        * Sets the item identifier
        *@param value - the item identifier
        */
        virtual inline void SetItemID(int value);

        /**
        * Gets the symbol reference
        *@return the symbol reference
        */
        virtual inline int GetSymbolRef() const;

        /**
        * Sets the symbol reference
        *@param value - the symbol reference
        */
        virtual inline void SetSymbolRef(int value);

        /**
        * Gets the user group GUID
        *@return the user group GUID
        */
        virtual inline CString GetUserGroupGUID() const;

        /**
        * Sets the user group GUID
        *@param value - the user group GUID
        */
        virtual inline void SetUserGroupGUID(const CString& value);

        /**
        * Adds distribution rules for a role
        *@param roleGUID - the role GUID
        *@param ruleOp - the rule operator, which may be one of the following:
        *               -1 none
        *                1 ==
        *                2 <
        *                3 <=
        *                4 >=
        *                5 >
        *                6 !=
        *@param value - the value
        *@param logicalOperator - the rule logical operator, which may be one of the following:
        *                        -1 none
        *                         0 AND
        *                         1 OR
        */
        virtual void AddDistributionRulesForRole(const CString& roleGUID);
        virtual void AddDistributionRulesForRole(const CString& roleGUID,
                                                 int            ruleOp,
                                                 const CString& value,
                                                 int            logicalOperator = -1);

        /**
        * Adds distribution rules for a role
        *@param pDistributionRulesForRole - the distribution rules for the role
        */
        virtual void AddDistributionRulesForRole(PSS_DistributionRulesForRole* pDistributionRulesForRole);

        /**
        * Deletes all the distribution rules for all roles
        */
        virtual void DeleteAllDistributionRulesForAllRoles();

        /**
        * Deletes all the distribution rules for a role
        *@param roleGUID - the role guid
        */
        virtual void DeleteAllDistributionRulesForRole(const CString& roleGUID);

        /**
        * Deletes a distribution rule for a role
        *@param pDistributionRulesForRole - the rule to delete
        */
        virtual bool DeleteDistributionRulesForRole(PSS_DistributionRulesForRole* pDistributionRulesForRole);

        /**
        * Deletes a distribution rule
        *@param pRule - the rule to delete
        */
        virtual bool DeleteDistributionRule(PSS_DistributionRule* pRule);

        /**
        * Finds the distribution rules for a role
        *@param roleGUID - the role guid
        *@return the distribution rules, NULL if not found or on error
        */
        virtual PSS_DistributionRulesForRole* FindDistributionRulesForRole(const CString& roleGUID) const;

        /**
        * Checks if a distribution rules for a role exists
        *@param pDistributionRulesForRole - the rules
        *@return true if the distribution rules for a role exists, otherwise false
        */
        virtual bool Exist(PSS_DistributionRulesForRole* pDistributionRulesForRole) const;

        /**
        * Checks if a role exists
        *@param roleGUID - the role GUID
        *@return true if the role exists, otherwise false
        */
        virtual inline bool Exist(const CString& roleGUID) const;

        /**
        * Checks if a distribution rule exists
        *@param pRule - the rule
        *@return true if the distribution rule exists, otherwise false
        */
        virtual bool ExistDistributionRule(PSS_DistributionRule* pRule) const;

        /**
        * Gets the distribution ruleset for a role
        *@param roleGUID - the role GUID
        *@return the distribution ruleset, NULL if not found or on error
        */
        virtual PSS_DistributionRuleManager::IDistributionRuleset* GetDistributionRuleset(const CString& roleGUID);

        /**
        * Gets the distribution rules for a role at index
        *@param roleGUID - the role GUID
        *@param index - the index
        *@return the distribution rule, NULL if not found or on error
        */
        virtual PSS_DistributionRule* GetDistributionRuleAt(const CString& roleGUID, std::size_t index);

        /**
        * Gets the distribution rules for a role count
        *@param roleGUID - the role GUID
        *@return the rule count
        */
        virtual std::size_t GetDistributionRuleCount(const CString& roleGUID) const;

        /**
        * Gets the distribution rules for a role ruleset
        *@return the distribution rules for a role ruleset
        */
        virtual inline IDistributionRulesForRoleSet& GetDistributionRulesForRoleSet();

        /**
        * Gets the distribution rules for a role at index
        *@return the distribution rules for a role, NULL if not found or on error
        */
        virtual inline PSS_DistributionRulesForRole* GetDistributionRulesForRoleAt(std::size_t index);

        /**
        * Deletes the distribution rules for a role at index
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteDistributionRulesForRoleAt(std::size_t index);

        /**
        * Gets the distribution rules for a role count
        *@return the distribution rules for a role count
        */
        virtual inline std::size_t GetDistributionRulesForRoleCount() const;

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        IDistributionRulesForRoleSet m_Set;
        CString                      m_UserGroupGUID;
        int                          m_CategoryID;
        int                          m_ItemID;
        int                          m_SymbolRef;
};

//---------------------------------------------------------------------------
// PSS_DistributionAttribute
//---------------------------------------------------------------------------
BOOL PSS_DistributionAttribute::operator == (const PSS_DistributionAttribute& other)
{
    return (m_CategoryID    == other.m_CategoryID &&
            m_ItemID        == other.m_ItemID     &&
            m_UserGroupGUID == other.m_UserGroupGUID);
}
//---------------------------------------------------------------------------
BOOL PSS_DistributionAttribute::operator != (const PSS_DistributionAttribute& other)
{
    return (m_CategoryID    != other.m_CategoryID ||
            m_ItemID        != other.m_ItemID     ||
            m_UserGroupGUID != other.m_UserGroupGUID);
}
//---------------------------------------------------------------------------
int PSS_DistributionAttribute::GetCategoryID() const
{
    return m_CategoryID;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttribute::SetCategoryID(int value)
{
    m_CategoryID = value;
}
//---------------------------------------------------------------------------
int PSS_DistributionAttribute::GetItemID() const
{
    return m_ItemID;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttribute::SetItemID(int value)
{
    m_ItemID = value;
}
//---------------------------------------------------------------------------
int PSS_DistributionAttribute::GetSymbolRef() const
{
    return m_SymbolRef;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttribute::SetSymbolRef(int value)
{
    m_SymbolRef = value;
}
//---------------------------------------------------------------------------
CString PSS_DistributionAttribute::GetUserGroupGUID() const
{
    return m_UserGroupGUID;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttribute::SetUserGroupGUID(const CString& value)
{
    m_UserGroupGUID = value;
}
//---------------------------------------------------------------------------
bool PSS_DistributionAttribute::Exist(const CString& roleGUID) const
{
    return FindDistributionRulesForRole(roleGUID);
}
//---------------------------------------------------------------------------
PSS_DistributionAttribute::IDistributionRulesForRoleSet& PSS_DistributionAttribute::GetDistributionRulesForRoleSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------
PSS_DistributionRulesForRole* PSS_DistributionAttribute::GetDistributionRulesForRoleAt(std::size_t index)
{
    if (index < GetDistributionRulesForRoleCount())
        return m_Set.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_DistributionAttribute::DeleteDistributionRulesForRoleAt(std::size_t index)
{
    if (index < GetDistributionRulesForRoleCount())
    {
        // delete the object first
        delete GetDistributionRulesForRoleAt(index);
        m_Set.RemoveAt(index);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
std::size_t PSS_DistributionAttribute::GetDistributionRulesForRoleCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------

/**
* Distribution attribute manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DistributionAttributeManager : public CObject
{
    DECLARE_SERIAL(PSS_DistributionAttributeManager)

    public:
        typedef CCArray_T <PSS_DistributionAttribute*, PSS_DistributionAttribute*> IDistributionAttributeSet;
        typedef Iterator_T<PSS_DistributionAttribute*>                             IDistributionAttributeIterator;

        PSS_DistributionAttributeManager();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DistributionAttributeManager(const PSS_DistributionAttributeManager& other);

        virtual ~PSS_DistributionAttributeManager();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DistributionAttributeManager& operator = (const PSS_DistributionAttributeManager& other);

        /**
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual PSS_DistributionAttributeManager* Dup() const;

        /**
        * Frees the properties set
        */
        virtual void FreePropertiesSet();

        /**
        * Gets the distribution attribute set
        *@return the distribution attribute set
        */
        virtual inline IDistributionAttributeSet& GetDistributionAttributeSet();

        /**
        * Adds a distribution attribute
        *@param pDistributionAttribute - the distribution attribute
        *@param replaceExisting - if true, the existing distribution attribute will be replaced, if exists
        */
        virtual void AddDistributionAttribute(PSS_DistributionAttribute* pDistributionAttribute, bool replaceExisting = true);

        /**
        * Deletes a distribution attribute
        *@param pDistributionAttribute - the distribution attribute
        *@param replaceExisting - if true, the existing distribution attribute will be replaced, if exists
        */
        virtual bool DeleteDistributionAttribute(PSS_DistributionAttribute* pDistributionAttribute);

        /**
        * Finds a distribution attribute
        *@param categoryID - the category identifier
        *@param itemID - the item identifier
        *@param userGroupGUID - the user group GUID
        *@return the distribution attribute, NULL if not found or on error
        */
        virtual PSS_DistributionAttribute* FindDistributionAttribute(int categoryID, int itemID, const CString& userGroupGUID);

        /**
        * Checks if a distribution attribute exists
        *@param pDistributionAttribute - the distribution attribute
        *@return true if the distribution attribute exists, otherwise false
        */
        virtual bool Exist(PSS_DistributionAttribute* pDistributionAttribute);

        /**
        * Deletes a distribution rule
        *@param pRule - the rule to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteDistributionRule(PSS_DistributionRule* pRule);

        /**
        * Checks the distribution role
        *@param pDistributionAttribute - the distribution attribute
        *@param pMainUserGroup - the main user group
        */
        virtual bool CheckDistributionRole(PSS_DistributionAttribute* pDistributionAttribute, PSS_UserGroupEntity* pMainUserGroup);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        IDistributionAttributeSet m_Set;

        /**
        * Replaces the distribution attribute
        *@param pDistributionAttribute - the distribution attribute to replace with
        */
        void ReplaceDistributionAttribute(PSS_DistributionAttribute* pDistributionAttribute);
};

//---------------------------------------------------------------------------
// PSS_DistributionAttributeManager
//---------------------------------------------------------------------------
PSS_DistributionAttributeManager::IDistributionAttributeSet& PSS_DistributionAttributeManager::GetDistributionAttributeSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------

#endif
