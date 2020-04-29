/****************************************************************************
 * ==> PSS_DecisionListPropertiesBP ----------------------------------------*
 ****************************************************************************
 * Description : Provides the decision list properties for banking process  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DecisionListPropertiesBP.h"

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
IMPLEMENT_SERIAL(PSS_DecisionListPropertiesBP, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DecisionListPropertiesBP
//---------------------------------------------------------------------------
PSS_DecisionListPropertiesBP::PSS_DecisionListPropertiesBP(int propID) :
    CODIntProperty(propID)
{
    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_DecisionListPropertiesBP::PSS_DecisionListPropertiesBP(const PSS_DecisionListPropertiesBP& other) :
    CODIntProperty(other.GetId())
{
    m_DecisionList = other.GetDecisionList();

    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_DecisionListPropertiesBP::~PSS_DecisionListPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_DecisionListPropertiesBP& PSS_DecisionListPropertiesBP::operator = (const PSS_DecisionListPropertiesBP& other)
{
    SetId(other.GetId());
    SetDecisionList(other.GetDecisionList());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::operator == (const PSS_DecisionListPropertiesBP& other) const
{
    return (GetDecisionList() == other.GetDecisionList());
}
//---------------------------------------------------------------------------
void PSS_DecisionListPropertiesBP::Merge(CODProperty* pProp, DWORD changeFlags)
{
    PSS_DecisionListPropertiesBP* pProcessProps = dynamic_cast<PSS_DecisionListPropertiesBP*>(pProp);

    if (pProcessProps)
        if (changeFlags & IE_CT_Change_Decision_List)
            m_DecisionList = pProcessProps->GetDecisionList();
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Decision_List_ID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_DecisionListPropertiesBP* pProcessProp = dynamic_cast<PSS_DecisionListPropertiesBP*>(pProp);

        if (pProcessProp)
            return (*this == *pProcessProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_DecisionListPropertiesBP::SetDecisionList(LPCTSTR pValue)
{
    if (pValue)
        m_DecisionList = pValue;
    else
        THROW("PSS_DecisionListPropertiesBP - Invalid decision list");
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Decision_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_Decision_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Decision_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Decision_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Decision_List_ID: value = m_DecisionList; break;
        default:                                         return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Decision_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_Decision_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Decision_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Decision_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DecisionListPropertiesBP::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Decision_List_ID: m_DecisionList = pValue; break;
        default:                                          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DecisionListPropertiesBP::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_DecisionListPropertiesBP::Serialize - Start Save\n");

        PUT_SCHEMA(ar, PSS_DecisionListPropertiesBP);
        ar << m_DecisionList;

        TRACE("PSS_DecisionListPropertiesBP::Serialize - End Save\n");
    }
    else
    {
        TRACE("PSS_DecisionListPropertiesBP::Serialize - Start Read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);

        ar >> m_DecisionList;

        TRACE("PSS_DecisionListPropertiesBP::Serialize - End Read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_DecisionListPropertiesBP::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_DecisionListPropertiesBP::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);

        dc << _T("Decision list = ") << m_DecisionList << _T("\n");
    }
#endif
//---------------------------------------------------------------------------
void PSS_DecisionListPropertiesBP::SetDecisionListEx(const CString value)
{
    SetDecisionList(value);
}
//---------------------------------------------------------------------------
bool PSS_DecisionListPropertiesBP::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        const bool success = RegisterProperty(M_Decision_List_ID,
                                              IDS_Z_DECISION_LIST_NAME,
                                              IDS_Z_DECISION_LIST_DESC,
                                              _PropertyAccessor(&PSS_DecisionListPropertiesBP::GetDecisionList,
                                                                &PSS_DecisionListPropertiesBP::SetDecisionListEx),
                                              VT_BSTR,
                                              PROP_DIRECT);

        if (!success)
            PSS_DecisionListPropertiesBP::GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
