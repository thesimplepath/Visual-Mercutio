/****************************************************************************
 * ==> PSS_UnitPropertiesBP ------------------------------------------------*
 ****************************************************************************
 * Description : Provides the unit properties for banking process           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UnitPropertiesBP.h"

// processsoft
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
IMPLEMENT_SERIAL(PSS_UnitPropertiesBP, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_UnitPropertiesBP
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP::PSS_UnitPropertiesBP() :
    CObject(),
    m_UnitCost(0.0f),
    m_DoubleValidationType(0)
{}
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP::PSS_UnitPropertiesBP(const PSS_UnitPropertiesBP& other) :
    CObject(),
    m_UnitCost(0.0f),
    m_DoubleValidationType(0)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP::~PSS_UnitPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP& PSS_UnitPropertiesBP::operator = (const PSS_UnitPropertiesBP& other)
{
    SetUnitName(other.GetUnitName());
    SetUnitCost(other.GetUnitCost());
    SetUnitGUID(other.GetUnitGUID());
    SetUnitDoubleValidationType(other.GetUnitDoubleValidationType());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::operator == (const PSS_UnitPropertiesBP& other) const
{
    return (GetUnitName()                 == other.GetUnitName()                 &&
            GetUnitCost()                 == other.GetUnitCost()                 &&
            GetUnitDoubleValidationType() == other.GetUnitDoubleValidationType() &&
            GetUnitGUID()                 == other.GetUnitGUID());
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::Merge(PSS_UnitPropertiesBP* pProp, DWORD changeFlags)
{
    if (pProp)
    {
        if (changeFlags & IE_CT_Change_Unit_Name)
            m_UnitName = pProp->GetUnitName();

        if (changeFlags & IE_CT_Change_Unit_Cost)
            m_UnitCost = pProp->GetUnitCost();

        if (changeFlags & IE_CT_Change_Unit_GUID)
            m_UnitGUID = pProp->GetUnitGUID();

        if (changeFlags & IE_CT_Change_Unit_Double_Validation)
            m_DoubleValidationType = pProp->GetUnitDoubleValidationType();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::IsEqual(PSS_UnitPropertiesBP* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::SetUnitName(LPCTSTR pValue)
{
    if (pValue)
        m_UnitName = pValue;
    else
        THROW("PSS_UnitPropertiesBP - Invalid task list");
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::SetUnitGUID(LPCTSTR pValue)
{
    if (pValue)
        m_UnitGUID = pValue;
    else
        THROW("PSS_UnitPropertiesBP - Invalid unit GUID");
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::GetUnitDoubleValidationTypeStringArray(CStringArray& strArray) const
{
    CString str;
    str.LoadString(IDS_DOUBLEVALID_NONE);
    strArray.Add(str);
    str.LoadString(IDS_DOUBLEVALID_EMPLOYEE);
    strArray.Add(str);
    str.LoadString(IDS_DOUBLEVALID_MANAGER);
    strArray.Add(str);
}
//---------------------------------------------------------------------------
int PSS_UnitPropertiesBP::ConvertUnitDoubleValidationString2Type(const CString& type) const
{
    CString str;
    str.LoadString(IDS_DOUBLEVALID_NONE);

    if (str == type)
        return 0;

    str.LoadString(IDS_DOUBLEVALID_EMPLOYEE);

    if (str == type)
        return 1;

    str.LoadString(IDS_DOUBLEVALID_MANAGER);

    if (str == type)
        return 2;

    // error
    return -1;
}
//---------------------------------------------------------------------------
CString PSS_UnitPropertiesBP::GetUnitDoubleValidationTypeString(const int value) const
{
    CString str;

    switch (value)
    {
        case 0: str.LoadString(IDS_DOUBLEVALID_NONE);     break;
        case 1: str.LoadString(IDS_DOUBLEVALID_EMPLOYEE); break;
        case 2: str.LoadString(IDS_DOUBLEVALID_MANAGER);  break;
    }

    return str;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Unit_Double_Validation_ID: value = m_DoubleValidationType; break;
        case M_Unit_Name_ID:
        case M_Unit_Cost_ID:
        case M_Unit_GUID_ID:              throw new CODPropertyConversionException();
        default:                          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_Unit_Double_Validation_ID: value = m_DoubleValidationType; break;
        case M_Unit_Name_ID:
        case M_Unit_Cost_ID:
        case M_Unit_GUID_ID:              throw new CODPropertyConversionException();
        default:                          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Unit_Double_Validation_ID:
        case M_Unit_Name_ID:
        case M_Unit_Cost_ID:
        case M_Unit_GUID_ID:              throw new CODPropertyConversionException();
        default:                          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Unit_Cost_ID:              value = m_UnitCost; break;
        case M_Unit_Double_Validation_ID:
        case M_Unit_Name_ID:
        case M_Unit_GUID_ID:              throw new CODPropertyConversionException();
        default:                          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Unit_Name_ID: value = m_UnitName; break;
        case M_Unit_GUID_ID: value = m_UnitGUID; break;
        default:             throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Unit_Double_Validation_ID: m_DoubleValidationType = value; break;
        case M_Unit_Name_ID:
        case M_Unit_Cost_ID:
        case M_Unit_GUID_ID:              throw new CODPropertyConversionException();
        default:                          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_Unit_Double_Validation_ID: m_DoubleValidationType = value; break;
        case M_Unit_Name_ID:
        case M_Unit_Cost_ID:
        case M_Unit_GUID_ID:              throw new CODPropertyConversionException();
        default:                          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Unit_Double_Validation_ID:
        case M_Unit_Name_ID:
        case M_Unit_Cost_ID:
        case M_Unit_GUID_ID:              throw new CODPropertyConversionException();
        default:                          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Unit_Cost_ID:              m_UnitCost = value; break;
        case M_Unit_Double_Validation_ID:
        case M_Unit_Name_ID:
        case M_Unit_GUID_ID:              throw new CODPropertyConversionException();
        default:                          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::SetValue(const int propId, LPCTSTR pValue)
{
    switch (propId)
    {
        case M_Unit_Name_ID: m_UnitName = pValue; break;
        case M_Unit_GUID_ID: m_UnitGUID = pValue; break;
        default:             throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::Serialize(CArchive& ar)
{
    CObject::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_UnitPropertiesBP::Serialize - Start save\n");

        PUT_SCHEMA(ar, PSS_UnitPropertiesBP);

        ar << m_UnitName;
        ar << m_UnitCost;
        ar << m_UnitGUID;
        ar << m_DoubleValidationType;

        TRACE("PSS_UnitPropertiesBP::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_UnitPropertiesBP::Serialize - Start read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);

        PSS_BaseDocument* pBaseDoc = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

        if (!ar.m_pDocument || (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 19))
        {
            ar >> m_UnitName;
            ar >> m_UnitCost;
            ar >> m_UnitGUID;
        }
        else
        {
            ar >> m_UnitName;
            ar >> m_UnitCost;
            m_UnitGUID.Empty();
        }

        if (!ar.m_pDocument || (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 20))
            ar >> m_DoubleValidationType;

        TRACE("PSS_UnitPropertiesBP::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UnitPropertiesBP::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UnitPropertiesBP::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);

        dc << _T("Unit name = ") << m_UnitName << _T("\n");
        dc << _T("Unit Cost = ") << m_UnitCost << _T("\n");
        dc << _T("Unit GUID = ") << m_UnitGUID << _T("\n");
    }
#endif
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::SetUnitNameEx(const CString value)
{
    SetUnitName(value);
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::SetUnitGUIDEx(const CString value)
{
    SetUnitGUID(value);
}
//---------------------------------------------------------------------------
