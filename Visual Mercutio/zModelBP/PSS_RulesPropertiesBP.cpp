/****************************************************************************
 * ==> PSS_RulesPropertiesBP -----------------------------------------------*
 ****************************************************************************
 * Description : Provides the rule properties for banking process           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RulesPropertiesBP.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_BaseDocument.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

using namespace sfl;

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_RulesPropertiesBP, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_RulesPropertiesBP
//---------------------------------------------------------------------------
PSS_RulesPropertiesBP::PSS_RulesPropertiesBP() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_RulesPropertiesBP::PSS_RulesPropertiesBP(const PSS_RulesPropertiesBP& other)
{
    m_RuleName        = other.GetRuleName();
    m_RuleDescription = other.GetRuleDescription();
    m_RuleGUID        = other.GetRuleGUID();
}
//---------------------------------------------------------------------------
PSS_RulesPropertiesBP::~PSS_RulesPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_RulesPropertiesBP& PSS_RulesPropertiesBP::operator = (const PSS_RulesPropertiesBP& other)
{
    SetRuleName(other.GetRuleName());
    SetRuleDescription(other.GetRuleDescription());
    SetRuleGUID(other.GetRuleGUID());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_RulesPropertiesBP::operator == (const PSS_RulesPropertiesBP& other) const
{
    return (GetRuleName()        == other.GetRuleName()        &&
            GetRuleDescription() == other.GetRuleDescription() &&
            GetRuleGUID()        == other.GetRuleGUID());
}
//---------------------------------------------------------------------------
void PSS_RulesPropertiesBP::Merge(PSS_RulesPropertiesBP* pProp, DWORD changeFlags)
{
    if (pProp)
    {
        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Rule_Name)
            m_RuleName = pProp->GetRuleName();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Rule_Description)
            m_RuleDescription = pProp->GetRuleDescription();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Rule_GUID)
            m_RuleGUID = pProp->GetRuleGUID();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_RulesPropertiesBP::IsEqual(PSS_RulesPropertiesBP* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_RulesPropertiesBP::SetRuleName(LPCTSTR pValue)
{
    if (pValue)
        m_RuleName = pValue;
    else
        THROW("PSS_RulesPropertiesBP - Invalid rule name");
}
//---------------------------------------------------------------------------
void PSS_RulesPropertiesBP::SetRuleDescription(LPCTSTR pValue)
{
    if (pValue)
        m_RuleDescription = pValue;
    else
        THROW("PSS_RulesPropertiesBP - Invalid rule description");
}
//---------------------------------------------------------------------------
void PSS_RulesPropertiesBP::SetRuleGUID(LPCTSTR pValue)
{
    if (pValue)
        m_RuleGUID = pValue;
    else
        THROW("PSS_RulesPropertiesBP - Invalid rule GUID");
}
//---------------------------------------------------------------------------
BOOL PSS_RulesPropertiesBP::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Rule_Name_ID:
        case M_Rule_Description_ID:
        case M_Rule_Identifier_ID:  THROW("Unsupported value");
        default:                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RulesPropertiesBP::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_Rule_Name_ID:
        case M_Rule_Description_ID:
        case M_Rule_Identifier_ID:  THROW("Unsupported value");
        default:                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RulesPropertiesBP::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Rule_Name_ID:
        case M_Rule_Description_ID:
        case M_Rule_Identifier_ID:  THROW("Unsupported value");
        default:                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RulesPropertiesBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Rule_Name_ID:
        case M_Rule_Description_ID:
        case M_Rule_Identifier_ID:  THROW("Unsupported value");
        default:                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RulesPropertiesBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Rule_Name_ID:        value = m_RuleName;        break;
        case M_Rule_Description_ID: value = m_RuleDescription; break;
        case M_Rule_Identifier_ID:  value = m_RuleGUID;        break;
        default:                    THROW("Unsupported value");
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RulesPropertiesBP::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Rule_Name_ID:
        case M_Rule_Description_ID:
        case M_Rule_Identifier_ID:  THROW("Unsupported value");
        default:                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RulesPropertiesBP::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_Rule_Name_ID:
        case M_Rule_Description_ID:
        case M_Rule_Identifier_ID:  THROW("Unsupported value");
        default:                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RulesPropertiesBP::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Rule_Name_ID:
        case M_Rule_Description_ID:
        case M_Rule_Identifier_ID:  THROW("Unsupported value");
        default:                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RulesPropertiesBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Rule_Name_ID:
        case M_Rule_Description_ID:
        case M_Rule_Identifier_ID:  THROW("Unsupported value");
        default:                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RulesPropertiesBP::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Rule_Name_ID:        m_RuleName        = pValue; break;
        case M_Rule_Description_ID: m_RuleDescription = pValue; break;
        case M_Rule_Identifier_ID:  m_RuleGUID        = pValue; break;
        default:                    THROW("Unsupported value");
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_RulesPropertiesBP::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE("PSS_RulesPropertiesBP::Serialize - Start save\n");

        ar << m_RuleName;
        ar << m_RuleDescription;
        ar << m_RuleGUID;

        TRACE("PSS_RulesPropertiesBP::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_RulesPropertiesBP::Serialize - Start read\n");

        ar >> m_RuleName;
        ar >> m_RuleDescription;
        ar >> m_RuleGUID;

        TRACE("PSS_RulesPropertiesBP::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_RulesPropertiesBP::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_RulesPropertiesBP::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);

        dc << _T("Name = ")        << m_RuleName        << _T("\n");
        dc << _T("Description = ") << m_RuleDescription << _T("\n");
        dc << _T("GUID = ")        << m_RuleGUID        << _T("\n");
    }
#endif
//---------------------------------------------------------------------------
void PSS_RulesPropertiesBP::SetRuleNameEx(const CString value)
{
    SetRuleName(value);
}
//---------------------------------------------------------------------------
void PSS_RulesPropertiesBP::SetRuleDescriptionEx(const CString value)
{
    SetRuleDescription(value);
}
//---------------------------------------------------------------------------
void PSS_RulesPropertiesBP::SetRuleGUIDEx(const CString value)
{
    SetRuleGUID(value);
}
//---------------------------------------------------------------------------
