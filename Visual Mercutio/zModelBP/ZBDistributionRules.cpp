// ZBDistributionRules.cpp: implementation of the ZBDistributionRule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBDistributionRules.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// ZBDistributionRule class implementation



IMPLEMENT_SERIAL(ZBDistributionRule, CObject, def_Version)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBDistributionRule::ZBDistributionRule(int Operator /*= -1*/, CString Value /*= ""*/, int LogicalOperator /*= -1*/)
: m_Operator(Operator),
  m_Value(Value),
  m_LogicalOperator(LogicalOperator)
{

}

ZBDistributionRule::~ZBDistributionRule()
{

}


ZBDistributionRule::ZBDistributionRule(const ZBDistributionRule& src)
{
    *this = src;
}

ZBDistributionRule& ZBDistributionRule::operator=(const ZBDistributionRule& src)
{
    m_Operator = src.m_Operator;
    m_LogicalOperator = src.m_LogicalOperator;
    m_Value = src.m_Value;

    return *this;
}


ZBDistributionRule* ZBDistributionRule::Dup() const
{
    return (new ZBDistributionRule(*this));
}


CString ZBDistributionRule::GetOperatorString() const
{
    switch (m_Operator)
    {
        case 1: return _T("==");
        case 2: return _T("<");
        case 3: return _T("<=");
        case 4: return _T(">=");
        case 5: return _T(">");
        case 6: return _T("!=");
        default: break;
    }
    return _T("");
}

CString ZBDistributionRule::GetLogicalOperatorString() const
{
    switch (m_LogicalOperator)
    {
        case 0: return _T("&");
        case 1: return _T("|");
        default: break;

    }
    return _T("");
}


void ZBDistributionRule::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE( "ZBDistributionRule::Serialize : Start Save\n" );

        ar << m_Operator;
        ar << m_LogicalOperator;
        ar << m_Value;

        TRACE( "ZBDistributionRule::Serialize : End Save\n" );
    }
    else
    {
        TRACE( "ZBDistributionRule::Serialize : Start Read\n" );

        ar >> m_Operator;
        ar >> m_LogicalOperator;
        ar >> m_Value;

        TRACE( "ZBDistributionRule::Serialize : End Read\n" );
    }

}

//////////////////////////////////////////////////////////////////////
// ZBDistributionRuleManager class implementation



IMPLEMENT_SERIAL(ZBDistributionRuleManager, CObject, def_Version)
  
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBDistributionRuleManager::ZBDistributionRuleManager()
{

}

ZBDistributionRuleManager::~ZBDistributionRuleManager()
{
    DeleteAllDistributionRule();
}



ZBDistributionRuleManager::ZBDistributionRuleManager(const ZBDistributionRuleManager& src)
{
    *this = src;
}

ZBDistributionRuleManager& ZBDistributionRuleManager::operator=(const ZBDistributionRuleManager& src)
{
    ZBDistributionRuleIterator i(&src.m_Set);
    for (ZBDistributionRule* pDistribRule = i.GetFirst(); pDistribRule; pDistribRule = i.GetNext())
    {
        AddDistributionRule( pDistribRule->Dup() );
    }
    return *this;
}


ZBDistributionRuleManager* ZBDistributionRuleManager::Dup() const
{
    return (new ZBDistributionRuleManager(*this));
}


void ZBDistributionRuleManager::DeleteAllDistributionRule()
{
    ZBDistributionRuleIterator i(&m_Set);
    for (ZBDistributionRule* pDistribRule = i.GetFirst(); pDistribRule; pDistribRule = i.GetNext())
        delete pDistribRule;

    m_Set.RemoveAll();
}

void ZBDistributionRuleManager::AddDistributionRule( int Operator, CString Value, int LogicalOperator /*= -1*/ )
{
    ZBDistributionRule* pDistributionRule = new ZBDistributionRule( Operator, Value, LogicalOperator );
    ASSERT( pDistributionRule );
    AddDistributionRule( pDistributionRule );
}

void ZBDistributionRuleManager::AddDistributionRule( ZBDistributionRule* pDistributionRule )
{
    if (!pDistributionRule)
        return;
    m_Set.Add( pDistributionRule );
}

bool ZBDistributionRuleManager::DeleteDistributionRule( ZBDistributionRule* pDistributionRule )
{
    ZBDistributionRuleIterator i(&m_Set);
    for (ZBDistributionRule* pDistribRule = i.GetFirst(); pDistribRule; pDistribRule = i.GetNext())
    {
        if (pDistribRule == pDistributionRule)
        {
            delete pDistribRule;
            i.Remove();
            return true;
        }
    }
    return false;
}


bool ZBDistributionRuleManager::Exist( ZBDistributionRule* pDistributionRule )
{
    if (!pDistributionRule)
        return NULL;
    ZBDistributionRuleIterator i(&m_Set);
    for (ZBDistributionRule* pDistribRule = i.GetFirst(); pDistribRule; pDistribRule = i.GetNext())
    {
        if (pDistribRule == pDistributionRule)
            return true;
    }
    return false;
}


void ZBDistributionRuleManager::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE( "ZBDistributionRuleManager::Serialize : Start Save\n" );

        // Serialize the size
        ar << m_Set.GetSize();

        ZBDistributionRuleIterator i(&m_Set);
        for (ZBDistributionRule* pDistribRule = i.GetFirst(); pDistribRule; pDistribRule = i.GetNext())
        {        
            ar << pDistribRule;
        }

        TRACE( "ZBDistributionRuleManager::Serialize : End Save\n" );
    }
    else
    {
        TRACE( "ZBDistributionRuleManager::Serialize : Start Read\n" );

        int Size;
        ar >> Size;

        ZBDistributionRule* pDistribRule;
        for (int i = 0; i < Size; ++i)
        {
            ar >> pDistribRule;
            AddDistributionRule( pDistribRule );
        }
    
        TRACE( "ZBDistributionRuleManager::Serialize : End Read\n" );
    }

}


