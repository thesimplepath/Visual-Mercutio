/****************************************************************************
 * ==> PSS_CostPropertiesProcedureBP ---------------------------------------*
 ****************************************************************************
 * Description : Provides the cost properties for procedures                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CostPropertiesProcedureBP.h"

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
IMPLEMENT_SERIAL(PSS_CostPropertiesProcedureBP, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_CostPropertiesProcedureBP
//---------------------------------------------------------------------------
PSS_CostPropertiesProcedureBP::PSS_CostPropertiesProcedureBP(int propID) :
    CODIntProperty(propID),
    m_ProcessingTime(0.0),
    m_Multiplier(1.0f),
    m_UnitaryCost(0.0f)
{
    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_CostPropertiesProcedureBP::PSS_CostPropertiesProcedureBP(const PSS_CostPropertiesProcedureBP& other) :
    CODIntProperty(other.GetId())
{
    *this = other;

    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_CostPropertiesProcedureBP::~PSS_CostPropertiesProcedureBP()
{}
//---------------------------------------------------------------------------
PSS_CostPropertiesProcedureBP& PSS_CostPropertiesProcedureBP::operator = (const PSS_CostPropertiesProcedureBP& other)
{
    SetMultiplier(other.GetMultiplier());
    SetProcessingTime(other.GetProcessingTime());
    SetUnitaryCost(other.GetUnitaryCost());
    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::operator == (const PSS_CostPropertiesProcedureBP& other) const
{
    return (GetMultiplier()     == other.GetMultiplier()     &&
            GetProcessingTime() == other.GetProcessingTime() &&
            GetUnitaryCost()    == other.GetUnitaryCost());
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesProcedureBP::Merge(CODProperty* pProperty, DWORD changeFlags)
{
    PSS_CostPropertiesProcedureBP* pOrientationProp = dynamic_cast<PSS_CostPropertiesProcedureBP*>(pProperty);

    if (pOrientationProp)
    {
        if (changeFlags & IE_CT_Change_Cost_Multiplier)
            m_Multiplier = pOrientationProp->GetMultiplier();

        if (changeFlags & IE_CT_Change_Cost_Processing_Time)
            m_ProcessingTime = pOrientationProp->GetProcessingTime();

        if (changeFlags & IE_CT_Change_Cost_Unitary_Cost)
            m_UnitaryCost = pOrientationProp->GetUnitaryCost();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Cost_Unitary_Cost;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_CostPropertiesProcedureBP* pOrientationProp = dynamic_cast<PSS_CostPropertiesProcedureBP*>(pProp);

        if (pOrientationProp)
            return (*this == *pOrientationProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::GetValue(const int propId, int& value) const
{
    if (propId >= M_Cost_Multiplier && propId <= M_Cost_Unitary_Cost)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::GetValue(const int propId, UINT& value) const
{
    if (propId >= M_Cost_Multiplier && propId <= M_Cost_Unitary_Cost)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::GetValue(const int propId, DWORD& value) const
{
    if (propId >= M_Cost_Multiplier && propId <= M_Cost_Unitary_Cost)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Cost_Multiplier:   value = m_Multiplier;  break;
        case M_Cost_Unitary_Cost: value = m_UnitaryCost; break;
        default:                                         return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::GetValue(const int propId, double& value) const
{
    switch (propId)
    {
        case M_Cost_Processing_Time: value = m_ProcessingTime; break;
        default:                                               return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Cost_Multiplier:      value.Format("%.0f", m_Multiplier);     break;
        case M_Cost_Processing_Time: value.Format("%.0f", m_ProcessingTime); break;
        case M_Cost_Unitary_Cost:    value.Format("%.0f", m_UnitaryCost);    break;
        default:                     throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::SetValue(const int propId, const int value)
{
    if (propId >= M_Cost_Multiplier && propId <= M_Cost_Unitary_Cost)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::SetValue(const int propId, const UINT value)
{
    if (propId >= M_Cost_Multiplier && propId <= M_Cost_Unitary_Cost)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::SetValue(const int propId, const DWORD value)
{
    if (propId >= M_Cost_Multiplier && propId <= M_Cost_Unitary_Cost)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Cost_Multiplier:   m_Multiplier  = value; break;
        case M_Cost_Unitary_Cost: m_UnitaryCost = value; break;
        default:                                         return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::SetValue(const int propId, const double value)
{
    switch (propId)
    {
        case M_Cost_Processing_Time: m_ProcessingTime = value; break;
        default:                                               return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::SetValue(const int propId, LPCTSTR pValue)
{
    switch (propId)
    {
        case M_Cost_Multiplier:      m_Multiplier     = static_cast<float>(std::atof(pValue)); break;
        case M_Cost_Processing_Time: m_ProcessingTime = std::atof(pValue);                     break;
        case M_Cost_Unitary_Cost:    m_UnitaryCost    = static_cast<float>(std::atof(pValue)); break;
        default:                                                                               return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesProcedureBP::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_CostPropertiesProcedureBP::Serialize : Start Save\n");

        PUT_SCHEMA(ar, PSS_CostPropertiesProcedureBP);
        ar << m_Multiplier;
        ar << m_ProcessingTime;
        ar << m_UnitaryCost;

        TRACE("PSS_CostPropertiesProcedureBP::Serialize : End Save\n");
    }
    else
    {
        TRACE("PSS_CostPropertiesProcedureBP::Serialize : Start Read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);
        ar >> m_Multiplier;
        ar >> m_ProcessingTime;
        ar >> m_UnitaryCost;

        TRACE("PSS_CostPropertiesProcedureBP::Serialize : End Read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CostPropertiesProcedureBP::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CostPropertiesProcedureBP::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
bool PSS_CostPropertiesProcedureBP::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        bool success = RegisterProperty(M_Cost_Multiplier,
                                        IDS_Z_COST_MULTIPLIER_NAME,
                                        IDS_Z_COST_MULTIPLIER_DESC,
                                        _PropertyAccessor(&PSS_CostPropertiesProcedureBP::GetMultiplier,
                                                          &PSS_CostPropertiesProcedureBP::SetMultiplier),
                                        VT_R4,
                                        PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Cost_Processing_Time,
                                       IDS_Z_COST_PROCESSING_TIME_NAME,
                                       IDS_Z_COST_PROCESSING_TIME_DESC,
                                       _PropertyAccessor(&PSS_CostPropertiesProcedureBP::GetProcessingTime,
                                                         &PSS_CostPropertiesProcedureBP::SetProcessingTime),
                                       VT_R4,
                                       PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Cost_Unitary_Cost,
                                       IDS_Z_COST_UNITARY_COST_NAME,
                                       IDS_Z_COST_UNITARY_COST_DESC,
                                       _PropertyAccessor(&PSS_CostPropertiesProcedureBP::GetUnitaryCost,
                                                         &PSS_CostPropertiesProcedureBP::SetUnitaryCost),
                                       VT_R4,
                                       PROP_DIRECT);

        if (!success)
            PSS_CostPropertiesProcedureBP::GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
