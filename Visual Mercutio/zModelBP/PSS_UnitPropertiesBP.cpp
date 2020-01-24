/****************************************************************************
 * ==> PSS_UnitPropertiesBP ------------------------------------------------*
 ****************************************************************************
 * Description : Provides the unit properties                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UnitPropertiesBP.h"

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
IMPLEMENT_SERIAL(PSS_UnitPropertiesBP, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_UnitPropertiesBP
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP::PSS_UnitPropertiesBP(int propID) :
    CODIntProperty(propID),
    m_UnitCost(0.0f)
{
    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP::PSS_UnitPropertiesBP(const PSS_UnitPropertiesBP& other) :
    CODIntProperty(other.GetId())
{
    m_UnitName = other.GetUnitName();
    m_UnitCost = other.GetUnitCost();

    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP::~PSS_UnitPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP& PSS_UnitPropertiesBP::operator = (const PSS_UnitPropertiesBP& other)
{
    SetId(other.GetId());
    SetUnitName(other.GetUnitName());
    SetUnitCost(other.GetUnitCost());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::operator == (const PSS_UnitPropertiesBP& other) const
{
    return (GetUnitName() == other.GetUnitName() &&
            GetUnitCost() == other.GetUnitCost());
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::Merge(CODProperty* pProperty, DWORD changeFlags)
{
    PSS_UnitPropertiesBP* pProcessProps = dynamic_cast<PSS_UnitPropertiesBP*>(pProperty);

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
BOOL PSS_UnitPropertiesBP::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Unit_GUID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_UnitPropertiesBP* pProcessProp = dynamic_cast<PSS_UnitPropertiesBP*>(pProp);

        if (pProcessProp)
            return (*this == *pProcessProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::SetUnitName(LPCTSTR pValue)
{
    if (pValue)
        m_UnitName = pValue;
    else
    {
        TRACE0("PSS_UnitPropertiesBP -> Invalid unit name!\n");
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Unit_Name:
        case M_Unit_Cost:
        case M_Unit_GUID: throw new CODPropertyConversionException();
        default:          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_Unit_Name:
        case M_Unit_Cost:
        case M_Unit_GUID: throw new CODPropertyConversionException();
        default:          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Unit_Name:
        case M_Unit_Cost:
        case M_Unit_GUID: throw new CODPropertyConversionException();
        default:          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Unit_Cost: value = m_UnitCost; break;
        case M_Unit_Name:
        case M_Unit_GUID: throw new CODPropertyConversionException();
        default:          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Unit_Name: value = m_UnitName; break;
        default:          throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Unit_Name:
        case M_Unit_Cost:
        case M_Unit_GUID: throw new CODPropertyConversionException();
        default:          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_Unit_Name:
        case M_Unit_Cost:
        case M_Unit_GUID: throw new CODPropertyConversionException();
        default:          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Unit_Name:
        case M_Unit_Cost:
        case M_Unit_GUID: throw new CODPropertyConversionException();
        default:          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Unit_Cost: m_UnitCost = value; break;
        case M_Unit_Name:
        case M_Unit_GUID: throw new CODPropertyConversionException();
        default:          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UnitPropertiesBP::SetValue(const int propId, LPCTSTR pValue)
{
    switch (propId)
    {
        case M_Unit_Name: m_UnitName = pValue; break;
        default:          throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_UnitPropertiesBP::Serialize : Start Save\n");

        PUT_SCHEMA(ar, PSS_UnitPropertiesBP);
        ar << m_UnitName;
        ar << m_UnitCost;

        TRACE("PSS_UnitPropertiesBP::Serialize : End Save\n");
    }
    else
    {
        TRACE("PSS_UnitPropertiesBP::Serialize : Start Read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);
        ar >> m_UnitName;
        ar >> m_UnitCost;

        TRACE("PSS_UnitPropertiesBP::Serialize : End Read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UnitPropertiesBP::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
void PSS_UnitPropertiesBP::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);

        dc << "Unit name = " << m_UnitName << "\n";
        dc << "Unit Cost = " << m_UnitCost << "\n";
    }
#endif
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::SetUnitNameEx(const CString value)
{
    SetUnitName(value);
}
//---------------------------------------------------------------------------
bool PSS_UnitPropertiesBP::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        bool success = RegisterProperty(M_Unit_Name,
                                        IDS_Z_UNIT_NAME_NAME,
                                        IDS_Z_UNIT_NAME_DESC,
                                        _PropertyAccessor(&PSS_UnitPropertiesBP::GetUnitName,
                                                          &PSS_UnitPropertiesBP::SetUnitNameEx),
                                        VT_BSTR,
                                        PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Unit_Cost,
                                       IDS_Z_UNIT_COST_NAME,
                                       IDS_Z_UNIT_COST_DESC,
                                       _PropertyAccessor(&PSS_UnitPropertiesBP::GetUnitCost,
                                                         &PSS_UnitPropertiesBP::SetUnitCost),
                                       VT_R4,
                                       PROP_DIRECT);

        // todo -cFeature -oJean: do implement the missing unit GUID property

        if (!success)
            PSS_UnitPropertiesBP::GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
