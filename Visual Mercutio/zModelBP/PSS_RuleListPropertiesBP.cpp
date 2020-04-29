/****************************************************************************
 * ==> PSS_RuleListPropertiesBP --------------------------------------------*
 ****************************************************************************
 * Description : Provides the rule list properties for banking process      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RuleListPropertiesBP.h"

// resources
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

using namespace sfl;

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_RuleListPropertiesBP, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_RuleListPropertiesBP
//---------------------------------------------------------------------------
PSS_RuleListPropertiesBP::PSS_RuleListPropertiesBP(int propID) :
    CODIntProperty(propID)
{
    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_RuleListPropertiesBP::PSS_RuleListPropertiesBP(const PSS_RuleListPropertiesBP& other) :
    CODIntProperty(other.GetId())
{
    m_RuleList = other.GetRuleList();

    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_RuleListPropertiesBP::~PSS_RuleListPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_RuleListPropertiesBP& PSS_RuleListPropertiesBP::operator = (const PSS_RuleListPropertiesBP& other)
{
    SetId(other.GetId());
    SetRuleList(other.GetRuleList());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::operator == (const PSS_RuleListPropertiesBP& other) const
{
    return (GetRuleList() == other.GetRuleList());
}
//---------------------------------------------------------------------------
void PSS_RuleListPropertiesBP::Merge(CODProperty* pProp, DWORD changeFlags)
{
    PSS_RuleListPropertiesBP* pRuleProp = dynamic_cast<PSS_RuleListPropertiesBP*>(pProp);

    if (pRuleProp)
        if (changeFlags & IE_CT_Change_Rule_List)
            m_RuleList = pRuleProp->GetRuleList();
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Rule_List_ID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::IsEqual(CODProperty* pProp)
{
    if (!pProp)
        return FALSE;

    if (GetId() == pProp->GetId())
    {
        PSS_RuleListPropertiesBP* pRuleProp = dynamic_cast<PSS_RuleListPropertiesBP*>(pProp);

        if (pRuleProp)
            return (*this == *pRuleProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_RuleListPropertiesBP::SetRuleList(LPCTSTR pValue)
{
    if (pValue)
        m_RuleList = pValue;
    else
        THROW("PSS_RuleListPropertiesBP - Invalid task list");
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Rule_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_Rule_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Rule_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Rule_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Rule_List_ID: value = m_RuleList; break;
        default:                                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Rule_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_Rule_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Rule_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Rule_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RuleListPropertiesBP::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Rule_List_ID: m_RuleList = pValue; break;
        default:                                  return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_RuleListPropertiesBP::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_RuleListPropertiesBP::Serialize - Start save\n");

        PUT_SCHEMA(ar, PSS_RuleListPropertiesBP);

        ar << m_RuleList;

        TRACE("PSS_RuleListPropertiesBP::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_RuleListPropertiesBP::Serialize - Start read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);

        ar >> m_RuleList;

        TRACE("PSS_RuleListPropertiesBP::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
void PSS_RuleListPropertiesBP::AssertValid() const
{
    CODIntProperty::AssertValid();
}
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
void PSS_RuleListPropertiesBP::Dump(CDumpContext& dc) const
{
    CODIntProperty::Dump(dc);

    dc << _T("Rule list = ") << m_RuleList << _T("\n");
}
#endif
//---------------------------------------------------------------------------
void PSS_RuleListPropertiesBP::SetRuleListEx(const CString value)
{
    SetRuleList(value);
}
//---------------------------------------------------------------------------
bool PSS_RuleListPropertiesBP::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        const bool success = RegisterProperty(M_Rule_List_ID,
                                              IDS_Z_RULE_LIST_NAME,
                                              IDS_Z_RULE_LIST_DESC,
                                              _PropertyAccessor(&PSS_RuleListPropertiesBP::GetRuleList,
                                                                &PSS_RuleListPropertiesBP::SetRuleListEx),
                                              VT_BSTR,
                                              PROP_DIRECT);

        if (!success)
            GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
