/****************************************************************************
 * ==> PSS_UnitPropertiesBP_Beta1 ------------------------------------------*
 ****************************************************************************
 * Description : Provides the unit properties for banking process (beta 1)  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UnitPropertiesBP_Beta1.h"

// processsoft
#include "zBaseLib\PSS_BaseDocument.h"

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
IMPLEMENT_SERIAL(PSS_UnitPropertiesBP_Beta1, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_UnitPropertiesBP_Beta1
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP_Beta1::PSS_UnitPropertiesBP_Beta1(int propID) :
    CODIntProperty(propID),
    m_UnitCost(0.0f)
{
    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP_Beta1::PSS_UnitPropertiesBP_Beta1(const PSS_UnitPropertiesBP_Beta1& other) :
    CODIntProperty(other.GetId())
{
    m_UnitName = other.GetUnitName();
    m_UnitCost = other.GetUnitCost();

    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP_Beta1::~PSS_UnitPropertiesBP_Beta1()
{}
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP_Beta1& PSS_UnitPropertiesBP_Beta1::operator = (const PSS_UnitPropertiesBP_Beta1& other)
{
    SetId(other.GetId());
    SetUnitName(other.GetUnitName());
    SetUnitCost(other.GetUnitCost());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::operator == (const PSS_UnitPropertiesBP_Beta1& other) const
{
    return (GetUnitName() == other.GetUnitName() &&
            GetUnitCost() == other.GetUnitCost());
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP_Beta1::Merge(CODProperty* pProp, DWORD changeFlags)
{
    PSS_UnitPropertiesBP_Beta1* pProcessProps = dynamic_cast<PSS_UnitPropertiesBP_Beta1*>(pProp);

    if (pProcessProps)
    {
        if (changeFlags & IE_CT_Change_Unit_Name)
            m_UnitName = pProcessProps->GetUnitName();

        if (changeFlags & IE_CT_Change_Unit_Cost)
            m_UnitCost = pProcessProps->GetUnitCost();

        // todo -cFeature -oJean: do implement the missing unit GUID property
    }
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Unit_GUID_Beta1_ID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_UnitPropertiesBP_Beta1* pProcessProp = dynamic_cast<PSS_UnitPropertiesBP_Beta1*>(pProp);

        if (pProcessProp)
            return (*this == *pProcessProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP_Beta1::SetUnitName(LPCTSTR pValue)
{
    if (pValue)
        m_UnitName = pValue;
    else
        THROW("PSS_UnitPropertiesBP_Beta1 - Invalid unit name");
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Unit_Name_Beta1_ID:
        case M_Unit_Cost_Beta1_ID:
        case M_Unit_GUID_Beta1_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_Unit_Name_Beta1_ID:
        case M_Unit_Cost_Beta1_ID:
        case M_Unit_GUID_Beta1_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Unit_Name_Beta1_ID:
        case M_Unit_Cost_Beta1_ID:
        case M_Unit_GUID_Beta1_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Unit_Cost_Beta1_ID: value = m_UnitCost; break;
        case M_Unit_Name_Beta1_ID:
        case M_Unit_GUID_Beta1_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Unit_Name_Beta1_ID: value = m_UnitName; break;
        default:                   throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Unit_Name_Beta1_ID:
        case M_Unit_Cost_Beta1_ID:
        case M_Unit_GUID_Beta1_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_Unit_Name_Beta1_ID:
        case M_Unit_Cost_Beta1_ID:
        case M_Unit_GUID_Beta1_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Unit_Name_Beta1_ID:
        case M_Unit_Cost_Beta1_ID:
        case M_Unit_GUID_Beta1_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Unit_Cost_Beta1_ID: m_UnitCost = value; break;
        case M_Unit_Name_Beta1_ID:
        case M_Unit_GUID_Beta1_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP_Beta1::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Unit_Name_Beta1_ID: m_UnitName = pValue; break;
        default:                   throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP_Beta1::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_UnitPropertiesBP_Beta1::Serialize - Start Save\n");

        PUT_SCHEMA(ar, PSS_UnitPropertiesBP_Beta1);
        ar << m_UnitName;
        ar << m_UnitCost;

        TRACE("PSS_UnitPropertiesBP_Beta1::Serialize - End Save\n");
    }
    else
    {
        TRACE("PSS_UnitPropertiesBP_Beta1::Serialize - Start Read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);
        ar >> m_UnitName;
        ar >> m_UnitCost;

        TRACE("PSS_UnitPropertiesBP_Beta1::Serialize - End Read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UnitPropertiesBP_Beta1::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
void PSS_UnitPropertiesBP_Beta1::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);

        dc << "Unit name = " << m_UnitName << "\n";
        dc << "Unit Cost = " << m_UnitCost << "\n";
    }
#endif
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP_Beta1::SetUnitNameEx(const CString value)
{
    SetUnitName(value);
}
//---------------------------------------------------------------------------
bool PSS_UnitPropertiesBP_Beta1::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        bool success = RegisterProperty(M_Unit_Name_Beta1_ID,
                                        IDS_Z_UNIT_NAME_NAME,
                                        IDS_Z_UNIT_NAME_DESC,
                                        _PropertyAccessor(&PSS_UnitPropertiesBP_Beta1::GetUnitName,
                                                          &PSS_UnitPropertiesBP_Beta1::SetUnitNameEx),
                                        VT_BSTR,
                                        PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Unit_Cost_Beta1_ID,
                                       IDS_Z_UNIT_COST_NAME,
                                       IDS_Z_UNIT_COST_DESC,
                                       _PropertyAccessor(&PSS_UnitPropertiesBP_Beta1::GetUnitCost,
                                                         &PSS_UnitPropertiesBP_Beta1::SetUnitCost),
                                       VT_R4,
                                       PROP_DIRECT);

        // todo -cFeature -oJean: do implement the missing unit GUID property

        if (!success)
            PSS_UnitPropertiesBP_Beta1::GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
