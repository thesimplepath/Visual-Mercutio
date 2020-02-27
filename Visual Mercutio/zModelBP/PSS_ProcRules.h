/****************************************************************************
 * ==> PSS_ProcRules -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the procedures for rules                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcRulesH
#define PSS_ProcRulesH

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
#ifndef PSS_ProcRules
    #define PSS_ProcRules ZBProcRules
#endif

// old class name mapping
#ifndef PSS_RulesPropertiesBP
    #define PSS_RulesPropertiesBP ZBBPRulesProperties
#endif

class PSS_RulesPropertiesBP;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
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
* Procedures for rules
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcRules : public CObject
{
    DECLARE_SERIAL(PSS_ProcRules)

    public:
        typedef CCArray_T <PSS_RulesPropertiesBP*, PSS_RulesPropertiesBP*> IRulesPropertiesSet;
        typedef Iterator_T<PSS_RulesPropertiesBP*>                         IRulesPropertiesIterator;

        /**
        * Constructor
        *@param pParent - the parent component
        */
        PSS_ProcRules(CODSymbolComponent* pParent = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProcRules(const PSS_ProcRules& other);

        virtual ~PSS_ProcRules();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ProcRules& operator = (const PSS_ProcRules& other);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual PSS_ProcRules* Dup() const;

        /**
        * Sets the parent symbol object
        *@param pParent - the parent symbol object
        */
        virtual void SetParent(CODSymbolComponent* pParent);

        /**
        * Adds a new empty rule
        *@return the new added rule index, -1 on error
        */
        virtual int AddNewRule();

        /**
        * Adds a rule
        *@param pProperty - the rule property to add
        *@return the new added rule index, -1 on error
        */
        virtual int AddRule(PSS_RulesPropertiesBP* pProperty);

        /**
        * Deletes a rule at index
        *@param index - the index
        *@return true on success, otherwise false
        */
        virtual bool DeleteRule(std::size_t index);

        /**
        * Deletes a rule
        *@param pProperty - the rule property to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteRule(PSS_RulesPropertiesBP* pProperty);

        /**
        * Checks if the rule name exists
        *@return true if the rule name exists, otherwise false
        */
        virtual bool RuleNameExist(const CString& name) const;

        /**
        * Gets the next valid rule name
        *@return the next valid rule name
        */
        virtual CString GetNextRuleValidName() const;

        /**
        * Locates the rule by its description
        *@param description - the description
        *@return the rule, NULL if not found or on error
        */
        virtual PSS_RulesPropertiesBP* LocateRuleByDescription(const CString& description) const;

        /**
        * Locates the rule index by its description
        *@param description - the description
        *@return the rule index, -1 if not found or on error
        */
        virtual int LocateRuleIndexByDescription(const CString& description) const;

        /**
        * Gets the rule set
        *@return the rule set
        */
        virtual inline IRulesPropertiesSet& GetRuleSet();

        /**
        * Gets the rule count
        *@return the rule count
        */
        virtual inline std::size_t GetRulesCount() const;

        /**
        * Gets the property at index
        *@param index - the index
        *@return the property, NULL if not found or on error
        */
        virtual inline PSS_RulesPropertiesBP* GetProperty(std::size_t index) const;

        /**
        * Removes all the rules
        */
        virtual void RemoveAllRules();

        /**
        * Gets the rule name at index
        *@param index - the index
        *@return the rule name, empty string if not found or on error
        */
        virtual CString GetRuleName(std::size_t index) const;

        /**
        * Sets the rule name at index
        *@param index - the index
        *@param value - the rule name
        */
        virtual void SetRuleName(std::size_t index, const CString& value);

        /**
        * Gets the rule description at index
        *@param index - the index
        *@return the rule description, empty string if not found or on error
        */
        virtual CString GetRuleDescription(std::size_t index) const;

        /**
        * Sets the rule description at index
        *@param index - the index
        *@param value - the rule description
        */
        virtual void SetRuleDescription(std::size_t index, const CString& value);

        /**
        * Gets the rule GUID at index
        *@param index - the index
        *@return the rule GUID, empty string if not found or on error
        */
        virtual CString GetRuleGUID(std::size_t index) const;

        /**
        * Sets the rule GUID at index
        *@param index - the index
        *@param value - the rule GUID
        */
        virtual void SetRuleGUID(std::size_t index, const CString& value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CODSymbolComponent* m_pParent;
        IRulesPropertiesSet m_Set;
};

//---------------------------------------------------------------------------
// PSS_ProcRules
//---------------------------------------------------------------------------
PSS_ProcRules::IRulesPropertiesSet& PSS_ProcRules::GetRuleSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcRules::GetRulesCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------
PSS_RulesPropertiesBP* PSS_ProcRules::GetProperty(std::size_t index) const
{
    if (index < GetRulesCount())
        return m_Set.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------

#endif
