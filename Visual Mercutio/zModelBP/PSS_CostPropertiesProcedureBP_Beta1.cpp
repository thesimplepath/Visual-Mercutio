/****************************************************************************
 * ==> PSS_CostPropertiesProcedureBP_Beta1 ---------------------------------*
 ****************************************************************************
 * Description : Provides the cost properties for procedures (beta 1)       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CostPropertiesProcedureBP_Beta1.h"

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
IMPLEMENT_SERIAL(PSS_CostPropertiesProcedureBP_Beta1, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_CostPropertiesProcedureBP_Beta1
//---------------------------------------------------------------------------
PSS_CostPropertiesProcedureBP_Beta1::PSS_CostPropertiesProcedureBP_Beta1(int propID) :
    CODIntProperty(propID),
    m_ProcessingTime(0.0),
    m_Multiplier(1.0f),
    m_UnitaryCost(0.0f)
{
    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_CostPropertiesProcedureBP_Beta1::PSS_CostPropertiesProcedureBP_Beta1(const PSS_CostPropertiesProcedureBP_Beta1& other) :
    CODIntProperty(other.GetId()),
    m_ProcessingTime(0.0),
    m_Multiplier(1.0f),
    m_UnitaryCost(0.0f)
{
    *this = other;

    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_CostPropertiesProcedureBP_Beta1::~PSS_CostPropertiesProcedureBP_Beta1()
{}
//---------------------------------------------------------------------------
PSS_CostPropertiesProcedureBP_Beta1& PSS_CostPropertiesProcedureBP_Beta1::operator = (const PSS_CostPropertiesProcedureBP_Beta1& other)
{
    SetMultiplier(other.GetMultiplier());
    SetProcessingTime(other.GetProcessingTime());
    SetUnitaryCost(other.GetUnitaryCost());
    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::operator == (const PSS_CostPropertiesProcedureBP_Beta1& other) const
{
    return (GetMultiplier()     == other.GetMultiplier()     &&
            GetProcessingTime() == other.GetProcessingTime() &&
            GetUnitaryCost()    == other.GetUnitaryCost());
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesProcedureBP_Beta1::Merge(CODProperty* pProp, DWORD changeFlags)
{
    PSS_CostPropertiesProcedureBP_Beta1* pOrientationProp = dynamic_cast<PSS_CostPropertiesProcedureBP_Beta1*>(pProp);

    if (pOrientationProp)
    {
        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Cost_Multiplier)
            m_Multiplier = pOrientationProp->GetMultiplier();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Cost_Processing_Time)
            m_ProcessingTime = pOrientationProp->GetProcessingTime();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Cost_Unitary_Cost)
            m_UnitaryCost = pOrientationProp->GetUnitaryCost();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Cost_Proc_Unitary_Cost_Beta1_ID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_CostPropertiesProcedureBP_Beta1* pOrientationProp = dynamic_cast<PSS_CostPropertiesProcedureBP_Beta1*>(pProp);

        if (pOrientationProp)
            return (*this == *pOrientationProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::GetValue(const int propId, int& value) const
{
    if (propId >= M_Cost_Proc_Multiplier_Beta1_ID && propId <= M_Cost_Proc_Unitary_Cost_Beta1_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::GetValue(const int propId, UINT& value) const
{
    if (propId >= M_Cost_Proc_Multiplier_Beta1_ID && propId <= M_Cost_Proc_Unitary_Cost_Beta1_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::GetValue(const int propId, DWORD& value) const
{
    if (propId >= M_Cost_Proc_Multiplier_Beta1_ID && propId <= M_Cost_Proc_Unitary_Cost_Beta1_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Cost_Proc_Multiplier_Beta1_ID:   value = m_Multiplier;  break;
        case M_Cost_Proc_Unitary_Cost_Beta1_ID: value = m_UnitaryCost; break;
        default:                                                       return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::GetValue(const int propId, double& value) const
{
    switch (propId)
    {
        case M_Cost_Proc_Processing_Time_Beta1_ID: value = m_ProcessingTime; break;
        default:                                                             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Cost_Proc_Multiplier_Beta1_ID:      value.Format("%.0f", m_Multiplier);     break;
        case M_Cost_Proc_Processing_Time_Beta1_ID: value.Format("%.0f", m_ProcessingTime); break;
        case M_Cost_Proc_Unitary_Cost_Beta1_ID:    value.Format("%.0f", m_UnitaryCost);    break;
        default:                                   throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::SetValue(const int propId, const int value)
{
    if (propId >= M_Cost_Proc_Multiplier_Beta1_ID && propId <= M_Cost_Proc_Unitary_Cost_Beta1_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::SetValue(const int propId, const UINT value)
{
    if (propId >= M_Cost_Proc_Multiplier_Beta1_ID && propId <= M_Cost_Proc_Unitary_Cost_Beta1_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::SetValue(const int propId, const DWORD value)
{
    if (propId >= M_Cost_Proc_Multiplier_Beta1_ID && propId <= M_Cost_Proc_Unitary_Cost_Beta1_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Cost_Proc_Multiplier_Beta1_ID:   m_Multiplier  = value; break;
        case M_Cost_Proc_Unitary_Cost_Beta1_ID: m_UnitaryCost = value; break;
        default:                                                       return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::SetValue(const int propId, const double value)
{
    switch (propId)
    {
        case M_Cost_Proc_Processing_Time_Beta1_ID: m_ProcessingTime = value; break;
        default:                                                             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP_Beta1::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Cost_Proc_Multiplier_Beta1_ID:      m_Multiplier     = static_cast<float>(std::atof(pValue)); break;
        case M_Cost_Proc_Processing_Time_Beta1_ID: m_ProcessingTime = std::atof(pValue);                     break;
        case M_Cost_Proc_Unitary_Cost_Beta1_ID:    m_UnitaryCost    = static_cast<float>(std::atof(pValue)); break;
        default:                                                                                             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesProcedureBP_Beta1::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_CostPropertiesProcedureBP_Beta1::Serialize - Start Save\n");

        PUT_SCHEMA(ar, PSS_CostPropertiesProcedureBP_Beta1);
        ar << m_Multiplier;
        ar << m_ProcessingTime;
        ar << m_UnitaryCost;

        TRACE("PSS_CostPropertiesProcedureBP_Beta1::Serialize - End Save\n");
    }
    else
    {
        TRACE("PSS_CostPropertiesProcedureBP_Beta1::Serialize - Start Read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);
        ar >> m_Multiplier;
        ar >> m_ProcessingTime;
        ar >> m_UnitaryCost;

        TRACE("PSS_CostPropertiesProcedureBP_Beta1::Serialize - End Read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CostPropertiesProcedureBP_Beta1::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CostPropertiesProcedureBP_Beta1::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
bool PSS_CostPropertiesProcedureBP_Beta1::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        bool success = RegisterProperty(M_Cost_Proc_Multiplier_Beta1_ID,
                                        IDS_Z_COST_MULTIPLIER_NAME,
                                        IDS_Z_COST_MULTIPLIER_DESC,
                                        _PropertyAccessor(&PSS_CostPropertiesProcedureBP_Beta1::GetMultiplier,
                                                          &PSS_CostPropertiesProcedureBP_Beta1::SetMultiplier),
                                        VT_R4,
                                        PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Cost_Proc_Processing_Time_Beta1_ID,
                                       IDS_Z_COST_PROCESSING_TIME_NAME,
                                       IDS_Z_COST_PROCESSING_TIME_DESC,
                                       _PropertyAccessor(&PSS_CostPropertiesProcedureBP_Beta1::GetProcessingTime,
                                                         &PSS_CostPropertiesProcedureBP_Beta1::SetProcessingTime),
                                       VT_R4,
                                       PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Cost_Proc_Unitary_Cost_Beta1_ID,
                                       IDS_Z_COST_UNITARY_COST_NAME,
                                       IDS_Z_COST_UNITARY_COST_DESC,
                                       _PropertyAccessor(&PSS_CostPropertiesProcedureBP_Beta1::GetUnitaryCost,
                                                         &PSS_CostPropertiesProcedureBP_Beta1::SetUnitaryCost),
                                       VT_R4,
                                       PROP_DIRECT);

        if (!success)
            PSS_CostPropertiesProcedureBP_Beta1::GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
