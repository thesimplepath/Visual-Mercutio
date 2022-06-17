/****************************************************************************
 * ==> PSS_CostPropertiesDeliverableBP_Beta1 -------------------------------*
 ****************************************************************************
 * Description : Provides the cost properties for deliverables (beta 1)     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CostPropertiesDeliverableBP_Beta1.h"

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
IMPLEMENT_SERIAL(PSS_CostPropertiesDeliverableBP_Beta1, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_CostPropertiesDeliverableBP_Beta1
//---------------------------------------------------------------------------
PSS_CostPropertiesDeliverableBP_Beta1::PSS_CostPropertiesDeliverableBP_Beta1(int propID) :
    CODIntProperty(propID),
    m_ProcessingTime(0.0),
    m_InWorkloadPercent(1.0f),
    m_OutWorkloadPercent(1.0f),
    m_UnitaryCost(0.0f)
{
    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_CostPropertiesDeliverableBP_Beta1::PSS_CostPropertiesDeliverableBP_Beta1(const PSS_CostPropertiesDeliverableBP_Beta1& other) :
    CODIntProperty(other.GetId()),
    m_ProcessingTime(0.0),
    m_InWorkloadPercent(1.0f),
    m_OutWorkloadPercent(1.0f),
    m_UnitaryCost(0.0f)
{
    *this = other;

    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_CostPropertiesDeliverableBP_Beta1::~PSS_CostPropertiesDeliverableBP_Beta1()
{}
//---------------------------------------------------------------------------
PSS_CostPropertiesDeliverableBP_Beta1& PSS_CostPropertiesDeliverableBP_Beta1::operator = (const PSS_CostPropertiesDeliverableBP_Beta1& other)
{
    SetProcessingTime(other.GetProcessingTime());
    SetInWorkloadPercent(other.GetInWorkloadPercent());
    SetOutWorkloadPercent(other.GetOutWorkloadPercent());
    SetUnitaryCost(other.GetUnitaryCost());
    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::operator == (const PSS_CostPropertiesDeliverableBP_Beta1& other) const
{
    return (GetProcessingTime()     == other.GetProcessingTime()     &&
            GetInWorkloadPercent()  == other.GetInWorkloadPercent()  &&
            GetOutWorkloadPercent() == other.GetOutWorkloadPercent() &&
            GetUnitaryCost()        == other.GetUnitaryCost());
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesDeliverableBP_Beta1::Merge(CODProperty* pProp, DWORD changeFlags)
{
    PSS_CostPropertiesDeliverableBP_Beta1* pOrientationProp = dynamic_cast<PSS_CostPropertiesDeliverableBP_Beta1*>(pProp);

    if (pOrientationProp)
    {
        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Cost_Processing_Time)
            m_ProcessingTime = pOrientationProp->GetProcessingTime();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Cost_In_Workload_Percent)
            m_InWorkloadPercent = pOrientationProp->GetInWorkloadPercent();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Cost_Out_Workload_Percent)
            m_OutWorkloadPercent = pOrientationProp->GetOutWorkloadPercent();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Cost_Unitary_Cost)
            m_UnitaryCost = pOrientationProp->GetUnitaryCost();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Cost_Deliv_Unitary_Cost_Beta1_ID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_CostPropertiesDeliverableBP_Beta1* pOrientationProp = dynamic_cast<PSS_CostPropertiesDeliverableBP_Beta1*>(pProp);

        if (pOrientationProp)
            return (*this == *pOrientationProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::GetValue(const int propId, int& value) const
{
    if (propId >= M_Cost_Deliv_Processing_Time_Beta1_ID && propId <= M_Cost_Deliv_Unitary_Cost_Beta1_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::GetValue(const int propId, UINT& value) const
{
    if (propId >= M_Cost_Deliv_Processing_Time_Beta1_ID && propId <= M_Cost_Deliv_Unitary_Cost_Beta1_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::GetValue(const int propId, DWORD& value) const
{
    if (propId >= M_Cost_Deliv_Processing_Time_Beta1_ID && propId <= M_Cost_Deliv_Unitary_Cost_Beta1_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::GetValue(const int propId, float& fValue) const
{
    switch (propId)
    {
        case M_Cost_Deliv_In_Workload_Percent_Beta1_ID:  fValue = m_InWorkloadPercent;  break;
        case M_Cost_Deliv_Out_Workload_Percent_Beta1_ID: fValue = m_OutWorkloadPercent; break;
        case M_Cost_Deliv_Unitary_Cost_Beta1_ID:         fValue = m_UnitaryCost;        break;
        default:                                                                        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::GetValue(const int propId, double& dValue) const
{
    switch (propId)
    {
        case M_Cost_Deliv_Processing_Time_Beta1_ID: dValue = m_ProcessingTime; break;
        default:                                                         return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::GetValue(const int propId, CString& strValue) const
{
    switch (propId)
    {
        case M_Cost_Deliv_Processing_Time_Beta1_ID:      strValue.Format("%.0f", m_ProcessingTime);              break;
        case M_Cost_Deliv_In_Workload_Percent_Beta1_ID:  strValue.Format("%.0f", m_InWorkloadPercent  * 100.0f); break;
        case M_Cost_Deliv_Out_Workload_Percent_Beta1_ID: strValue.Format("%.0f", m_OutWorkloadPercent * 100.0f); break;
        case M_Cost_Deliv_Unitary_Cost_Beta1_ID:         strValue.Format("%.0f", m_UnitaryCost);                 break;
        default:                                                                                                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::SetValue(const int propId, const int value)
{
    if (propId >= M_Cost_Deliv_Processing_Time_Beta1_ID && propId <= M_Cost_Deliv_Unitary_Cost_Beta1_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::SetValue(const int propId, const UINT value)
{
    if (propId >= M_Cost_Deliv_Processing_Time_Beta1_ID && propId <= M_Cost_Deliv_Unitary_Cost_Beta1_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::SetValue(const int propId, const DWORD value)
{
    if (propId >= M_Cost_Deliv_Processing_Time_Beta1_ID && propId <= M_Cost_Deliv_Unitary_Cost_Beta1_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Cost_Deliv_In_Workload_Percent_Beta1_ID:  m_InWorkloadPercent  = value; break;
        case M_Cost_Deliv_Out_Workload_Percent_Beta1_ID: m_OutWorkloadPercent = value; break;
        case M_Cost_Deliv_Unitary_Cost_Beta1_ID:         m_UnitaryCost        = value; break;
        default:                                                                       return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::SetValue(const int propId, const double value)
{
    switch (propId)
    {
        case M_Cost_Deliv_Processing_Time_Beta1_ID: m_ProcessingTime = value; break;
        default:                                                              return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP_Beta1::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Cost_Deliv_Processing_Time_Beta1_ID:      m_ProcessingTime     = std::atof(pValue);                              break;
        case M_Cost_Deliv_In_Workload_Percent_Beta1_ID:  m_InWorkloadPercent  = static_cast<float>(std::atof(pValue) / 100.0f); break;
        case M_Cost_Deliv_Out_Workload_Percent_Beta1_ID: m_OutWorkloadPercent = static_cast<float>(std::atof(pValue) / 100.0f); break;
        case M_Cost_Deliv_Unitary_Cost_Beta1_ID:         m_UnitaryCost        = static_cast<float>(std::atof(pValue));          break;
        default:                                                                                                                return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesDeliverableBP_Beta1::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_CostPropertiesDeliverableBP_Beta1::Serialize - Start Save\n");

        PUT_SCHEMA(ar, PSS_CostPropertiesDeliverableBP_Beta1);
        ar << m_ProcessingTime;
        ar << m_InWorkloadPercent;
        ar << m_OutWorkloadPercent;
        ar << m_UnitaryCost;

        TRACE("PSS_CostPropertiesDeliverableBP_Beta1::Serialize - End Save\n");
    }
    else
    {
        TRACE("PSS_CostPropertiesDeliverableBP_Beta1::Serialize - Start Read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);
        ar >> m_ProcessingTime;
        ar >> m_InWorkloadPercent;
        ar >> m_OutWorkloadPercent;
        ar >> m_UnitaryCost;

        TRACE("PSS_CostPropertiesDeliverableBP_Beta1::Serialize - End Read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CostPropertiesDeliverableBP_Beta1::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CostPropertiesDeliverableBP_Beta1::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
bool PSS_CostPropertiesDeliverableBP_Beta1::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        bool success = RegisterProperty(M_Cost_Deliv_Processing_Time_Beta1_ID,
                                        IDS_Z_COST_PROCESSING_TIME_NAME,
                                        IDS_Z_COST_PROCESSING_TIME_DESC,
                                        _PropertyAccessor(&PSS_CostPropertiesDeliverableBP_Beta1::GetProcessingTime,
                                                          &PSS_CostPropertiesDeliverableBP_Beta1::SetProcessingTime),
                                        VT_R4,
                                        PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Cost_Deliv_In_Workload_Percent_Beta1_ID,
                                       IDS_Z_COST_IN_WORKLOAD_PERCENT_NAME,
                                       IDS_Z_COST_IN_WORKLOAD_PERCENT_DESC,
                                       _PropertyAccessor(&PSS_CostPropertiesDeliverableBP_Beta1::GetInWorkloadPercent,
                                                         &PSS_CostPropertiesDeliverableBP_Beta1::SetInWorkloadPercent),
                                       VT_R4,
                                       PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Cost_Deliv_Out_Workload_Percent_Beta1_ID,
                                       IDS_Z_COST_OUT_WORKLOAD_PERCENT_NAME,
                                       IDS_Z_COST_OUT_WORKLOAD_PERCENT_DESC,
                                       _PropertyAccessor(&PSS_CostPropertiesDeliverableBP_Beta1::GetOutWorkloadPercent,
                                                         &PSS_CostPropertiesDeliverableBP_Beta1::SetOutWorkloadPercent),
                                       VT_R4,
                                       PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Cost_Deliv_Unitary_Cost_Beta1_ID,
                                       IDS_Z_COST_UNITARY_COST_NAME,
                                       IDS_Z_COST_UNITARY_COST_DESC,
                                       _PropertyAccessor(&PSS_CostPropertiesDeliverableBP_Beta1::GetUnitaryCost,
                                                         &PSS_CostPropertiesDeliverableBP_Beta1::SetUnitaryCost),
                                       VT_R4,
                                       PROP_DIRECT);

        if (!success)
            PSS_CostPropertiesDeliverableBP_Beta1::GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
