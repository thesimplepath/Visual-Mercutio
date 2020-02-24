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
class AFX_EXT_CLASS ZBDistributionRule : public CObject
{
    DECLARE_SERIAL(ZBDistributionRule)

public:
    ZBDistributionRule(int Operator = -1, CString Value = "", int LogicalOperator = -1);
    virtual ~ZBDistributionRule();

    /* Copy constructor. */
    ZBDistributionRule(const ZBDistributionRule& src);
    /* Assignment operator. */
    ZBDistributionRule& operator=(const ZBDistributionRule& src);
    /* Equal operator */
    BOOL operator == (const ZBDistributionRule& Rule);
    /* Not Equal operator */
    BOOL operator != (const ZBDistributionRule& Rule);
    /* Create a duplicate copy of this object. */
    virtual ZBDistributionRule* Dup() const;

    // Member accessors.
    int GetOperator() const;
    CString GetOperatorString() const;
    void SetOperator( int value );

    int GetLogicalOperator() const;
    CString GetLogicalOperatorString() const;
    void SetLogicalOperator( int value );
    
    CString GetValue() const;
    void SetValue( CString value );

    /* Serializes the symbol. */
    virtual void Serialize(CArchive& ar);


private:
    int m_Operator;
    /*
    1   ==
    2  <
    3  <=
    4  >=
    5  >
    6  !=
    */

    int m_LogicalOperator; // (0=AND 1=OR)
    CString m_Value;

};


inline int ZBDistributionRule::GetOperator() const 
{
    return m_Operator;
}
inline void ZBDistributionRule::SetOperator( int value )
{
    m_Operator = value;
}


inline int ZBDistributionRule::GetLogicalOperator() const 
{
    return m_LogicalOperator;
}
inline void ZBDistributionRule::SetLogicalOperator( int value )
{
    m_LogicalOperator = value;
}


inline CString ZBDistributionRule::GetValue() const 
{
    return m_Value;
}
inline void ZBDistributionRule::SetValue( CString value )
{
    m_Value = value;
}


inline BOOL ZBDistributionRule::operator == (const ZBDistributionRule& Rule)
{
      return (Rule.m_Value == this->m_Value &&
            Rule.m_Operator == this->m_Operator &&
            Rule.m_LogicalOperator == this->m_LogicalOperator);
}

inline BOOL ZBDistributionRule::operator != (const ZBDistributionRule& Rule)
{
      return (Rule.m_Value != this->m_Value ||
            Rule.m_Operator != this->m_Operator ||
            Rule.m_LogicalOperator != this->m_LogicalOperator);
}

typedef CCArray_T<ZBDistributionRule*,ZBDistributionRule*> ZBDistributionRuleSet;
typedef Iterator_T<ZBDistributionRule*> ZBDistributionRuleIterator;

/**
* Distribution rules
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZBDistributionRuleManager : public CObject
{
    DECLARE_SERIAL(ZBDistributionRuleManager)

public:
    ZBDistributionRuleManager();
    virtual ~ZBDistributionRuleManager();
    /* Copy constructor. */
    ZBDistributionRuleManager(const ZBDistributionRuleManager& src);
    /* Assignment operator. */
    ZBDistributionRuleManager& operator=(const ZBDistributionRuleManager& src);
    /* Create a duplicate copy of this object. */
    virtual ZBDistributionRuleManager* Dup() const;

    /* Serializes the symbol. */
    virtual void Serialize(CArchive& ar);

    ZBDistributionRuleSet& GetDistributionRuleSet()
    {
        return m_Set;
    };
    void DeleteAllDistributionRule();
    ZBDistributionRule* GetDistributionRuleAt( size_t Index )
    {
        if (Index < GetDistributionRuleCount())
            return m_Set.GetAt( Index );
        return NULL;
    };
    size_t GetDistributionRuleCount() const
    {
        return m_Set.GetSize();
    };
    void AddDistributionRule( ZBDistributionRule* pDistributionRule );
    void AddDistributionRule( int Operator, CString Value, int LogicalOperator = -1 );
    bool Exist( ZBDistributionRule* pDistributionRule );
    bool DeleteDistributionRule( ZBDistributionRule* pDistributionRule );

private:
    ZBDistributionRuleSet m_Set;
};

#endif
