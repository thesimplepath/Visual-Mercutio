/****************************************************************************
 * ==> PSS_DistributionRules -----------------------------------------------*
 ****************************************************************************
 * Description : Provides the distribution rules                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DistributionRulesH
#define PSS_DistributionRulesH

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
#ifndef PSS_DistributionRule
    #define PSS_DistributionRule ZBDistributionRule
#endif
#ifndef PSS_DistributionRuleManager
    #define PSS_DistributionRuleManager ZBDistributionRuleManager
#endif

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
* Distribution rule
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DistributionRule : public CObject
{
    DECLARE_SERIAL(PSS_DistributionRule)

    public:
        /**
        * Constructor
        *@param ruleOp - the rule operator, which may be one of the following:
        *               -1 none
        *                1 ==
        *                2 <
        *                3 <=
        *                4 >=
        *                5 >
        *                6 !=
        *@param value - the rule value
        *@param logicalOperator - the rule logical operator, which may be one of the following:
        *                        -1 none
        *                         0 AND
        *                         1 OR
        */
        PSS_DistributionRule(int ruleOp = -1, const CString& value = "", int logicalOperator = -1);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DistributionRule(const PSS_DistributionRule& src);

        virtual ~PSS_DistributionRule();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DistributionRule& operator = (const PSS_DistributionRule& other);

        /**
        * Checks if the content of another object is equal to this one
        *@param other - the other object to compare with
        *@return TRUE if the other object content is equal, otherwise FALSE
        */
        inline BOOL operator == (const PSS_DistributionRule& other);

        /**
        * Checks if the content of another object differs from this one
        *@param other - the other object to compare with
        *@return TRUE if the other object content differs, otherwise FALSE
        */
        inline BOOL operator != (const PSS_DistributionRule& other);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual PSS_DistributionRule* Dup() const;

        /**
        * Gets the operator
        *@return the operator
        */
        virtual inline int GetOperator() const;

        /**
        * Gets the operator as a string
        *@return the string containing the operator
        */
        virtual CString GetOperatorString() const;

        /**
        * Sets the operator
        *@param value - the rule operator, which may be one of the following:
        *              -1 none
        *               1 ==
        *               2 <
        *               3 <=
        *               4 >=
        *               5 >
        *               6 !=
        */
        virtual inline void SetOperator(int value);

        /**
        * Gets the logical operator
        *@return the logical operator
        */
        virtual inline int GetLogicalOperator() const;

        /**
        * Gets the logical operator as a string
        *@return the string containing the logical operator
        */
        virtual CString GetLogicalOperatorString() const;

        /**
        * Sets the logical operator
        *@param value - the rule logical operator, which may be one of the following:
        *              -1 none
        *               0 AND
        *               1 OR
        */
        virtual inline void SetLogicalOperator(int value);

        /**
        * Gets the value
        *@return the value
        */
        virtual inline CString GetValue() const;

        /**
        * Sets the value
        *@param value - the value
        */
        virtual inline void SetValue(const CString& value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CString m_Value;
        int     m_Operator;
        int     m_LogicalOperator;
};

//---------------------------------------------------------------------------
// PSS_DistributionRule
//---------------------------------------------------------------------------
BOOL PSS_DistributionRule::operator == (const PSS_DistributionRule& other)
{
    return (m_Operator        == other.m_Operator        &&
            m_LogicalOperator == other.m_LogicalOperator &&
            m_Value           == other.m_Value);
}
//---------------------------------------------------------------------------
BOOL PSS_DistributionRule::operator != (const PSS_DistributionRule& other)
{
    return (m_Operator        != other.m_Operator        ||
            m_LogicalOperator != other.m_LogicalOperator ||
            m_Value           != other.m_Value);
}
//---------------------------------------------------------------------------
int PSS_DistributionRule::GetOperator() const
{
    return m_Operator;
}
//---------------------------------------------------------------------------
void PSS_DistributionRule::SetOperator(int value)
{
    m_Operator = value;
}
//---------------------------------------------------------------------------
int PSS_DistributionRule::GetLogicalOperator() const
{
    return m_LogicalOperator;
}
//---------------------------------------------------------------------------
void PSS_DistributionRule::SetLogicalOperator(int value)
{
    m_LogicalOperator = value;
}
//---------------------------------------------------------------------------
CString PSS_DistributionRule::GetValue() const
{
    return m_Value;
}
//---------------------------------------------------------------------------
void PSS_DistributionRule::SetValue(const CString& value)
{
    m_Value = value;
}
//---------------------------------------------------------------------------

/**
* Distribution rules
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DistributionRuleManager : public CObject
{
    DECLARE_SERIAL(PSS_DistributionRuleManager)

    public:
        typedef CCArray_T <PSS_DistributionRule*, PSS_DistributionRule*> IDistributionRuleset;
        typedef Iterator_T<PSS_DistributionRule*>                        IDistributionRuleIterator;

        PSS_DistributionRuleManager();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DistributionRuleManager(const PSS_DistributionRuleManager& other);

        virtual ~PSS_DistributionRuleManager();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DistributionRuleManager& operator = (const PSS_DistributionRuleManager& other);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual PSS_DistributionRuleManager* Dup() const;

        /**
        * Gets the distribution ruleset
        *@return the distribution ruleset
        */
        virtual inline IDistributionRuleset& GetDistributionRuleset();

        /**
        * Deletes all the distribution rules
        */
        virtual void DeleteAllDistributionRule();

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
        *@param pDistributionRule - the distribution rule to add
        */
        virtual void AddDistributionRule(PSS_DistributionRule* pDistributionRule);

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
        *@param value - the rule value
        *@param logicalOperator - the rule logical operator, which may be one of the following:
        *                        -1 none
        *                         0 AND
        *                         1 OR
        */
        virtual void AddDistributionRule(int ruleOp, const CString& value, int logicalOperator = -1);

        /**
        * Checks if a rule exists
        *@param pDistributionRule - the rule to check
        *@return true if the rule exists, otherwise false
        */
        virtual bool Exist(PSS_DistributionRule* pDistributionRule);

        /**
        * Deletes a rule
        *@param pDistributionRule - the rule to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteDistributionRule(PSS_DistributionRule* pDistributionRule);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        IDistributionRuleset m_Set;
};

//---------------------------------------------------------------------------
// PSS_DistributionRuleManager
//---------------------------------------------------------------------------
PSS_DistributionRuleManager::IDistributionRuleset& PSS_DistributionRuleManager::GetDistributionRuleset()
{
    return m_Set;
}
//---------------------------------------------------------------------------
PSS_DistributionRule* PSS_DistributionRuleManager::GetDistributionRuleAt(std::size_t index)
{
    if (index < GetDistributionRuleCount())
        return m_Set.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------
std::size_t PSS_DistributionRuleManager::GetDistributionRuleCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------

#endif
