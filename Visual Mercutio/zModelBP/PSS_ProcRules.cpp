/****************************************************************************
 * ==> PSS_ProcRules -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the procedures for rules                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcRules.h"

// processsoft
#include "PSS_RulesPropertiesBP.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int g_LastRuleIDProperties = ZS_BP_PROP_RULES + 39;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ProcRules, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ProcRules
//---------------------------------------------------------------------------
PSS_ProcRules::PSS_ProcRules(CODSymbolComponent* pParent) :
    CObject(),
    m_pParent(pParent)
{}
//---------------------------------------------------------------------------
PSS_ProcRules::PSS_ProcRules(const PSS_ProcRules& other) :
    CObject(),
    m_pParent(NULL)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ProcRules::~PSS_ProcRules()
{
    RemoveAllRules();
}
//---------------------------------------------------------------------------
PSS_ProcRules& PSS_ProcRules::operator = (const PSS_ProcRules& other)
{
    IRulesPropertiesIterator it(&const_cast<PSS_ProcRules&>(other).GetRuleSet());

    // copy the members
    for (PSS_RulesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        AddRule(pProp->Dup());

    m_pParent = other.m_pParent;

    return *this;
}
//---------------------------------------------------------------------------
PSS_ProcRules* PSS_ProcRules::Dup() const
{
    return new PSS_ProcRules(*this);
}
//---------------------------------------------------------------------------
void PSS_ProcRules::SetParent(CODSymbolComponent* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
int PSS_ProcRules::AddNewRule()
{
    std::unique_ptr<PSS_RulesPropertiesBP> pProps(new PSS_RulesPropertiesBP());

    const int index = AddRule(pProps.get());
    pProps.release();

    return index;
}
//---------------------------------------------------------------------------
int PSS_ProcRules::AddRule(PSS_RulesPropertiesBP* pProperty)
{
    if (pProperty)
    {
        // if no rule name defined, set one by default
        if (pProperty->GetRuleName().IsEmpty())
            pProperty->SetRuleName(GetNextRuleValidName());

        m_Set.Add(pProperty);

        // return the index
        return GetRulesCount() - 1;
    }

    return -1;
}
//---------------------------------------------------------------------------
bool PSS_ProcRules::DeleteRule(std::size_t index)
{
    if (index < GetRulesCount())
    {
        PSS_RulesPropertiesBP* pProperty = GetProperty(index);

        if (pProperty)
        {
            m_Set.RemoveAt(index);
            delete pProperty;
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcRules::DeleteRule(PSS_RulesPropertiesBP* pProperty)
{
    IRulesPropertiesIterator it(&m_Set);

    for (PSS_RulesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProperty == pProp)
        {
            it.Remove();
            delete pProp;
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcRules::RuleNameExist(const CString& name) const
{
    IRulesPropertiesIterator it(&m_Set);

    // iterate through the rules and build the string
    for (PSS_RulesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetRuleName() == name)
            return true;

    return false;
}
//---------------------------------------------------------------------------
CString PSS_ProcRules::GetNextRuleValidName() const
{
    CString str;
    int     i = 1;

    do
    {
        str.Format(_T("Règle %d"), i);
        ++i;
    }
    while (RuleNameExist(str));

    return str;
}
//---------------------------------------------------------------------------
PSS_RulesPropertiesBP* PSS_ProcRules::LocateRuleByDescription(const CString& description) const
{
    const int index = LocateRuleIndexByDescription(description);

    if (index == -1)
        return NULL;

    return GetProperty(index);
}
//---------------------------------------------------------------------------
int PSS_ProcRules::LocateRuleIndexByDescription(const CString& description) const
{
    IRulesPropertiesIterator it(&m_Set);
    int                      index = 0;

    // iterate through the rules and check if one is matching with the description
    for (PSS_RulesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext(), ++index)
        if (!pProp->GetRuleDescription().IsEmpty() && pProp->GetRuleDescription() == description)
            return index;

    return -1;
}
//---------------------------------------------------------------------------
void PSS_ProcRules::RemoveAllRules()
{
    IRulesPropertiesIterator it(&m_Set);

    for (PSS_RulesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    // remove all elements
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
CString PSS_ProcRules::GetRuleName(std::size_t index) const
{
    if (index < GetRulesCount())
        return m_Set.GetAt(index)->GetRuleName();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcRules::SetRuleName(std::size_t index, const CString& value)
{
    if (index < GetRulesCount())
        m_Set.GetAt(index)->SetRuleName(value);
}
//---------------------------------------------------------------------------
CString PSS_ProcRules::GetRuleDescription(std::size_t index) const
{
    if (index < GetRulesCount())
        return m_Set.GetAt(index)->GetRuleDescription();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcRules::SetRuleDescription(std::size_t index, const CString& value)
{
    if (index < GetRulesCount())
        m_Set.GetAt(index)->SetRuleDescription(value);
}
//---------------------------------------------------------------------------
CString PSS_ProcRules::GetRuleGUID(std::size_t index) const
{
    if (index < GetRulesCount())
        return m_Set.GetAt(index)->GetRuleGUID();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcRules::SetRuleGUID(std::size_t index, const CString& value)
{
    if (index < GetRulesCount())
        m_Set.GetAt(index)->SetRuleGUID(value);
}
//---------------------------------------------------------------------------
void PSS_ProcRules::Serialize(CArchive& ar)
{
    // only if the object is serialize from or to a document
    if (ar.m_pDocument)
        if (ar.IsStoring())
        {
            TRACE(_T("PSS_ProcRules::Serialize - Start save\n"));

            // serialize the size
            ar << int(m_Set.GetSize());

            IRulesPropertiesIterator it(&m_Set);

            for (PSS_RulesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                ar << pProp;

            TRACE(_T("PSS_ProcRules::Serialize - End save\n"));
        }
        else
        {
            TRACE(_T("PSS_ProcRules::Serialize - Start read\n"));

            RemoveAllRules();

            // read the size
            int count;
            ar >> count;

            PSS_RulesPropertiesBP* pProp;

            for (int i = 0; i < count; ++i)
            {
                ar >> pProp;
                AddRule(pProp);
            }

            TRACE(_T("PSS_ProcRules::Serialize - End read\n"));
        }
}
//---------------------------------------------------------------------------
