/****************************************************************************
 * ==> PSS_DistributionRules -----------------------------------------------*
 ****************************************************************************
 * Description : Provides the distribution rules                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DistributionRules.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_DistributionRule, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DistributionRule
//---------------------------------------------------------------------------
PSS_DistributionRule::PSS_DistributionRule(int ruleOp, const CString& value, int logicalOperator) :
    m_Value(value),
    m_Operator(ruleOp),
    m_LogicalOperator(logicalOperator)
{}
//---------------------------------------------------------------------------
PSS_DistributionRule::PSS_DistributionRule(const PSS_DistributionRule& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_DistributionRule::~PSS_DistributionRule()
{}
//---------------------------------------------------------------------------
PSS_DistributionRule& PSS_DistributionRule::operator = (const PSS_DistributionRule& other)
{
    m_Value           = other.m_Value;
    m_Operator        = other.m_Operator;
    m_LogicalOperator = other.m_LogicalOperator;

    return *this;
}
//---------------------------------------------------------------------------
PSS_DistributionRule* PSS_DistributionRule::Dup() const
{
    return new PSS_DistributionRule(*this);
}
//---------------------------------------------------------------------------
CString PSS_DistributionRule::GetOperatorString() const
{
    switch (m_Operator)
    {
        case 1:  return _T("==");
        case 2:  return _T("<");
        case 3:  return _T("<=");
        case 4:  return _T(">=");
        case 5:  return _T(">");
        case 6:  return _T("!=");
        default: break;
    }

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_DistributionRule::GetLogicalOperatorString() const
{
    switch (m_LogicalOperator)
    {
        case 0:  return _T("&");
        case 1:  return _T("|");
        default: break;
    }

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_DistributionRule::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE("PSS_DistributionRule::Serialize - Start save\n");

        ar << m_Operator;
        ar << m_LogicalOperator;
        ar << m_Value;

        TRACE("PSS_DistributionRule::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_DistributionRule::Serialize - Start read\n");

        ar >> m_Operator;
        ar >> m_LogicalOperator;
        ar >> m_Value;

        TRACE("PSS_DistributionRule::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_DistributionRuleManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DistributionRuleManager
//---------------------------------------------------------------------------
PSS_DistributionRuleManager::PSS_DistributionRuleManager() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_DistributionRuleManager::PSS_DistributionRuleManager(const PSS_DistributionRuleManager& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_DistributionRuleManager::~PSS_DistributionRuleManager()
{
    DeleteAllDistributionRule();
}
//---------------------------------------------------------------------------
PSS_DistributionRuleManager& PSS_DistributionRuleManager::operator = (const PSS_DistributionRuleManager& other)
{
    IDistributionRuleIterator it(&other.m_Set);

    for (PSS_DistributionRule* pDistribRule = it.GetFirst(); pDistribRule; pDistribRule = it.GetNext())
        AddDistributionRule(pDistribRule->Dup());

    return *this;
}
//---------------------------------------------------------------------------
PSS_DistributionRuleManager* PSS_DistributionRuleManager::Dup() const
{
    return new PSS_DistributionRuleManager(*this);
}
//---------------------------------------------------------------------------
void PSS_DistributionRuleManager::DeleteAllDistributionRule()
{
    IDistributionRuleIterator it(&m_Set);

    for (PSS_DistributionRule* pDistribRule = it.GetFirst(); pDistribRule; pDistribRule = it.GetNext())
        delete pDistribRule;

    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_DistributionRuleManager::AddDistributionRule(PSS_DistributionRule* pDistributionRule)
{
    if (!pDistributionRule)
        return;

    m_Set.Add(pDistributionRule);
}
//---------------------------------------------------------------------------
void PSS_DistributionRuleManager::AddDistributionRule(int ruleOp, const CString& value, int logicalOperator)
{
    std::unique_ptr<PSS_DistributionRule> pDistributionRule(new PSS_DistributionRule(ruleOp, value, logicalOperator));
    AddDistributionRule(pDistributionRule.get());
    pDistributionRule.release();
}
//---------------------------------------------------------------------------
bool PSS_DistributionRuleManager::Exist(PSS_DistributionRule* pDistributionRule)
{
    if (!pDistributionRule)
        return NULL;

    IDistributionRuleIterator it(&m_Set);

    for (PSS_DistributionRule* pDistribRule = it.GetFirst(); pDistribRule; pDistribRule = it.GetNext())
        if (pDistribRule == pDistributionRule)
            return true;

    return false;
}
//---------------------------------------------------------------------------
bool PSS_DistributionRuleManager::DeleteDistributionRule(PSS_DistributionRule* pDistributionRule)
{
    IDistributionRuleIterator it(&m_Set);

    for (PSS_DistributionRule* pDistribRule = it.GetFirst(); pDistribRule; pDistribRule = it.GetNext())
        if (pDistribRule == pDistributionRule)
        {
            delete pDistribRule;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
void PSS_DistributionRuleManager::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE("PSS_DistributionRuleManager::Serialize - Start save\n");

        // Serialize the size
        ar << m_Set.GetSize();

        IDistributionRuleIterator it(&m_Set);

        for (PSS_DistributionRule* pDistribRule = it.GetFirst(); pDistribRule; pDistribRule = it.GetNext())
            ar << pDistribRule;

        TRACE("PSS_DistributionRuleManager::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_DistributionRuleManager::Serialize - Start read\n");

        int size;
        ar >> size;

        PSS_DistributionRule* pDistribRule;

        for (int i = 0; i < size; ++i)
        {
            ar >> pDistribRule;
            AddDistributionRule(pDistribRule);
        }

        TRACE("PSS_DistributionRuleManager::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
