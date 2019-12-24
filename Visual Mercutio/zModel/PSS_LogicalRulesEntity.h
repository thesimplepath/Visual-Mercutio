/****************************************************************************
 * ==> PSS_LogicalRulesEntity ----------------------------------------------*
 ****************************************************************************
 * Description : Provides the logical rules entity                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LogicalRulesEntityH
#define PSS_LogicalRulesEntityH

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
#ifndef PSS_LogicalRulesEntity
    #define PSS_LogicalRulesEntity ZBLogicalRulesEntity
#endif

// processsoft
#include "ZBRulesEntity.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

using namespace sfl;

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const CString g_LogicalRulesKey = _T("$LR=");
//---------------------------------------------------------------------------

/**
* Logical rules entity
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_LogicalRulesEntity : public ZBRulesEntity
{
    DECLARE_SERIAL(PSS_LogicalRulesEntity)

    public:
        typedef CCArray_T <ZBRulesEntity*, ZBRulesEntity*> IEntitySet;
        typedef Iterator_T<ZBRulesEntity*>                 IEntityIterator;

        /**
        * Constructor
        *@param name - the entity name
        *@param description - the entity description
        *@param pParent - the parent entity to add in, root entity if NULL
        */
        PSS_LogicalRulesEntity(const CString& name        = _T(""),
                               const CString& description = _T(""),
                               ZBRulesEntity* pParent     = NULL);

        virtual ~PSS_LogicalRulesEntity();

        /**
        * Checks if the entity contains children entities
        *@return true the entity contains children entities, otherwise false
        */
        virtual inline bool ContainEntity() const;

        /**
        * Gets the child entity count
        *@return true the child entity count
        */
        virtual inline std::size_t GetEntityCount() const;

        /**
        * Gets the entity at index
        *@param index - the index
        *@return the entity, NULL if not found or on error
        */
        virtual inline ZBRulesEntity* GetEntityAt(std::size_t index);

        /**
        * Gets the entity set
        *@return the entity set
        */
        virtual inline IEntitySet* GetEntitySet();

        /**
        * Checks if the entity was modified
        *@return TRUE if the entity was modified, otherwise FALSE
        */
        virtual inline BOOL IsModified();

        /**
        * Sets the entity as modified
        *@param value - if TRUE, the entity was modified
        */
        virtual inline void SetModifiedFlag(BOOL modified = TRUE);

        /**
        * Adds a new rule
        *@param name - the rule name
        *@param description - the rule description
        *@return the newly added rule, NULL on error
        */
        virtual PSS_LogicalRulesEntity* AddRule(const CString& name, const CString& description);

        /**
        * Adds a new rule
        *@param name - the rule name
        *@param description - the rule description
        *@param inRuleName - the parent rule name to add in
        *@return the newly added rule, NULL on error
        */
        virtual PSS_LogicalRulesEntity* AddRule(const CString& name,
                                                const CString& description,
                                                const CString& inRuleName);

        /**
        * Adds a new rule
        *@param name - the rule name
        *@param description - the rule description
        *@param pInRule - the parent rule to add in
        *@return the newly added rule, NULL on error
        */
        virtual PSS_LogicalRulesEntity* AddRule(const CString&          name,
                                                const CString&          description,
                                                PSS_LogicalRulesEntity* pInRule);

        /**
        * Removes an existing rule
        *@param name - the rule name to remove
        *@param deeper - if true, the search will also be performed in children
        *@return true on success, otherwise false
        */
        virtual bool RemoveRule(const CString& name, bool deeper = false);

        /**
        * Removes an existing rule
        *@param name - the rule name to remove
        *@param inRuleName - the parent rule name to remove from
        *@return true on success, otherwise false
        */
        virtual bool RemoveRule(const CString& name, const CString& inRuleName);

        /**
        * Removes an existing rule
        *@param name - the rule name to remove
        *@param pInRule - the parent rule to remove from
        *@return true on success, otherwise false
        */
        virtual bool RemoveRule(const CString& name, PSS_LogicalRulesEntity* pInRule);

        /**
        * Removes an existing rule
        *@param pRule - the rule to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveRule(PSS_LogicalRulesEntity* pRule);

        /**
        * Removes all the rule entities
        */
        virtual void RemoveAllRulesEntities();

        /**
        * Finds a rule from its guid
        *@param guid - the rule guid to find
        *@param deeper - if true, the search will continue recursively in rule children
        *@return the rule, NULL if not found or on error
        */
        virtual ZBRulesEntity* FindRuleByGUID(const CString& guid, bool deeper = false);

        /**
        * Finds a rule
        *@param name - the rule name to find
        *@param deeper - if true, the search will continue recursively in rule children
        *@return the matching rules, NULL if not found or on error
        */
        virtual IEntitySet* FindRule(const CString& name, bool deeper = false);

        /**
        * Finds a rule
        *@param name - the rule name to find
        *@param inRuleName - the rule entity name in which the search should begin
        *@return the matching rules, NULL if not found or on error
        */
        virtual IEntitySet* FindRule(const CString& name, const CString& inRuleName);

        /**
        * Finds a rule
        *@param name - the rule name to find
        *@param pInRule - the rule entity in which the search should begin
        *@return the matching rules, NULL if not found or on error
        */
        virtual IEntitySet* FindRule(const CString& name, PSS_LogicalRulesEntity* pInRule);

        /**
        * Checks if a rule exists
        *@param name - the rule name to find
        *@param deeper - if true, the search will continue recursively in rule children
        *@return true if the rule exists, otherwise false
        */
        virtual bool RuleExist(const CString& name, bool deeper = false);

        /**
        * Checks if a rule exists
        *@param name - the rule name to find
        *@param inRuleName - the rule entity name in which the search should begin
        *@return true if the rule exists, otherwise false
        */
        virtual bool RuleExist(const CString& name, const CString& inRuleName);

        /**
        * Checks if a rule exists
        *@param name - the rule name to find
        *@param pInRule - the rule entity in which the search should begin
        *@return true if the rule exists, otherwise false
        */
        virtual bool RuleExist(const CString& name, PSS_LogicalRulesEntity* pInRule);

        /**
        * Moves a rule
        *@param pRule - the rule to move
        *@return true on success, otherwise false
        */
        bool MoveRule(ZBRulesEntity* pRule);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        /**
        * Adds a new rule
        *@param pRule - the rule to add
        *@return true on success, otherwise false
        */
        virtual inline bool AddRule(ZBRulesEntity* pRule);

        /**
        * Removes a rule from the rule set
        *@param pRule - the rule to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveRuleFromSet(ZBRulesEntity* pRule);

        /**
        * Finds a rule from its guid
        *@param guid - the rule guid to find
        *@param deeper - if true, the search will continue recursively in rule children
        *@return the rule, NULL if not found or on error
        */
        virtual ZBRulesEntity* FindRuleByGUIDPvt(const CString& guid, bool deeper = false);

        /**
        * Finds a rule
        *@param name - the rule name to find
        *@param inRuleName - the rule entity name in which the search should begin
        *@return true if the rule exists, otherwise false
        */
        virtual void FindRulePvt(const CString& name, bool deeper = false);

        /**
        * Finds a rule
        *@param name - the rule name to find
        *@param deeper - if true, the search will continue recursively in rule children
        *@return the matching rules, NULL if not found or on error
        */
        virtual void FindRulePvt(const CString& name, PSS_LogicalRulesEntity* pInRule);

        /**
        * Finds the first rule matching with the name
        *@param name - the rule name to find
        *@param deeper - if true, the search will continue recursively in rule children
        *@return the matching rules, NULL if not found or on error
        */
        virtual PSS_LogicalRulesEntity* FindFirstRule(const CString& name, bool deeper = false);

        /**
        * Finds the first rule matching with the name
        *@param name - the rule name to find
        *@param inPrestationName - the rule entity name in which the search should begin
        *@return true if the rule exists, otherwise false
        */
        virtual PSS_LogicalRulesEntity* FindFirstRule(const CString& name, PSS_LogicalRulesEntity* pInRule);

        /**
        * Removes all rules in a set
        *@param set - the rule set containing the rules to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveRules(IEntitySet& Set);

        /**
        * Recalculates the parent rule
        */
        void RecalculateParent();

    protected:
        static IEntitySet m_FindSet;
        static BOOL       m_Modified;
        IEntitySet        m_EntitySet;
};

//---------------------------------------------------------------------------
// PSS_LogicalRulesEntity
//---------------------------------------------------------------------------
bool PSS_LogicalRulesEntity::ContainEntity() const
{
    return true;
}
//---------------------------------------------------------------------------
std::size_t PSS_LogicalRulesEntity::GetEntityCount() const
{
    return m_EntitySet.GetSize();
}
//---------------------------------------------------------------------------
ZBRulesEntity* PSS_LogicalRulesEntity::GetEntityAt(std::size_t index)
{
    return (index < GetEntityCount() ? m_EntitySet.GetAt(index) : NULL);
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity::IEntitySet* PSS_LogicalRulesEntity::GetEntitySet()
{
    return &m_EntitySet;
}
//---------------------------------------------------------------------------
BOOL PSS_LogicalRulesEntity::IsModified()
{
    return m_Modified;
}
//---------------------------------------------------------------------------
void PSS_LogicalRulesEntity::SetModifiedFlag(BOOL modified)
{
    m_Modified = modified;
}
//---------------------------------------------------------------------------
bool PSS_LogicalRulesEntity::AddRule(ZBRulesEntity* pRule)
{
    m_EntitySet.Add(pRule);
    return true;
}
//---------------------------------------------------------------------------

#endif
