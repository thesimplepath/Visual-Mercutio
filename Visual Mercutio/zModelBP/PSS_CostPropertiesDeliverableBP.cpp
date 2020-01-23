/****************************************************************************
 * ==> PSS_CostPropertiesDeliverableBP -------------------------------------*
 ****************************************************************************
 * Description : Provides the cost properties for deliverables              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CostPropertiesDeliverableBP.h"

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
IMPLEMENT_SERIAL(PSS_CostPropertiesDeliverableBP, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_CostPropertiesDeliverableBP
//---------------------------------------------------------------------------
PSS_CostPropertiesDeliverableBP::PSS_CostPropertiesDeliverableBP(int propID) :
    CODIntProperty(propID),
    m_ProcessingTime(0.0),
    m_InWorkloadPercent(1.0f),
    m_OutWorkloadPercent(1.0f),
    m_UnitaryCost(0.0f)
{
    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_CostPropertiesDeliverableBP::PSS_CostPropertiesDeliverableBP(const PSS_CostPropertiesDeliverableBP& other) :
    CODIntProperty(other.GetId())
{
    *this = other;

    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_CostPropertiesDeliverableBP::~PSS_CostPropertiesDeliverableBP()
{}
//---------------------------------------------------------------------------
PSS_CostPropertiesDeliverableBP& PSS_CostPropertiesDeliverableBP::operator = (const PSS_CostPropertiesDeliverableBP& other)
{
    SetProcessingTime(other.GetProcessingTime());
    SetInWorkloadPercent(other.GetInWorkloadPercent());
    SetOutWorkloadPercent(other.GetOutWorkloadPercent());
    SetUnitaryCost(other.GetUnitaryCost());
    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::operator == (const PSS_CostPropertiesDeliverableBP& other) const
{
    return (GetProcessingTime()     == other.GetProcessingTime()     &&
            GetInWorkloadPercent()  == other.GetInWorkloadPercent()  &&
            GetOutWorkloadPercent() == other.GetOutWorkloadPercent() &&
            GetUnitaryCost()        == other.GetUnitaryCost());
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesDeliverableBP::Merge(CODProperty* pProperty, DWORD changeFlags)
{
    PSS_CostPropertiesDeliverableBP* pOrientationProp = dynamic_cast<PSS_CostPropertiesDeliverableBP*>(pProperty);

    if (pOrientationProp)
    {
        if (changeFlags & IE_CT_Change_Cost_Processing_Time)
            m_ProcessingTime = pOrientationProp->GetProcessingTime();

        if (changeFlags & IE_CT_Change_Cost_In_Workload_Percent)
            m_InWorkloadPercent = pOrientationProp->GetInWorkloadPercent();

        if (changeFlags & IE_CT_Change_Cost_Out_Workload_Percent)
            m_OutWorkloadPercent = pOrientationProp->GetOutWorkloadPercent();

        if (changeFlags & IE_CT_Change_Cost_Unitary_Cost)
            m_UnitaryCost = pOrientationProp->GetUnitaryCost();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Cost_Unitary_Cost_ID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_CostPropertiesDeliverableBP* pOrientationProp = dynamic_cast<PSS_CostPropertiesDeliverableBP*>(pProp);

        if (pOrientationProp)
            return (*this == *pOrientationProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::GetValue(const int propId, int& value) const
{
    if (propId >= M_Cost_Processing_Time_ID && propId <= M_Cost_Unitary_Cost_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::GetValue(const int propId, UINT& value) const
{
    if (propId >= M_Cost_Processing_Time_ID && propId <= M_Cost_Unitary_Cost_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::GetValue(const int propId, DWORD& value) const
{
    if (propId >= M_Cost_Processing_Time_ID && propId <= M_Cost_Unitary_Cost_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::GetValue(const int propId, float& fValue) const
{
    switch (propId)
    {
        case M_Cost_In_Workload_Percent_ID:  fValue = m_InWorkloadPercent;  break;
        case M_Cost_Out_Workload_Percent_ID: fValue = m_OutWorkloadPercent; break;
        case M_Cost_Unitary_Cost_ID:         fValue = m_UnitaryCost;        break;
        default:                                                            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::GetValue(const int propId, double& dValue) const
{
    switch (propId)
    {
        case M_Cost_Processing_Time_ID: dValue = m_ProcessingTime; break;
        default:                                                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::GetValue(const int propId, CString& strValue) const
{
    switch (propId)
    {
        case M_Cost_Processing_Time_ID:      strValue.Format("%.0f", m_ProcessingTime);              break;
        case M_Cost_In_Workload_Percent_ID:  strValue.Format("%.0f", m_InWorkloadPercent  * 100.0f); break;
        case M_Cost_Out_Workload_Percent_ID: strValue.Format("%.0f", m_OutWorkloadPercent * 100.0f); break;
        case M_Cost_Unitary_Cost_ID:         strValue.Format("%.0f", m_UnitaryCost);                 break;
        default:                                                                                     return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::SetValue(const int propId, const int value)
{
    if (propId >= M_Cost_Processing_Time_ID && propId <= M_Cost_Unitary_Cost_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::SetValue(const int propId, const UINT value)
{
    if (propId >= M_Cost_Processing_Time_ID && propId <= M_Cost_Unitary_Cost_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::SetValue(const int propId, const DWORD value)
{
    if (propId >= M_Cost_Processing_Time_ID && propId <= M_Cost_Unitary_Cost_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Cost_In_Workload_Percent_ID:  m_InWorkloadPercent  = value; break;
        case M_Cost_Out_Workload_Percent_ID: m_OutWorkloadPercent = value; break;
        case M_Cost_Unitary_Cost_ID:         m_UnitaryCost        = value; break;
        default:                                                           return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::SetValue(const int propId, const double value)
{
    switch (propId)
    {
        case M_Cost_Processing_Time_ID: m_ProcessingTime = value; break;
        default:                                                  return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::SetValue(const int propId, LPCTSTR pValue)
{
    switch (propId)
    {
        case M_Cost_Processing_Time_ID:      m_ProcessingTime     = std::atof(pValue);                              break;
        case M_Cost_In_Workload_Percent_ID:  m_InWorkloadPercent  = static_cast<float>(std::atof(pValue) / 100.0f); break;
        case M_Cost_Out_Workload_Percent_ID: m_OutWorkloadPercent = static_cast<float>(std::atof(pValue) / 100.0f); break;
        case M_Cost_Unitary_Cost_ID:         m_UnitaryCost        = static_cast<float>(std::atof(pValue));          break;
        default:                                                                                                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesDeliverableBP::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_CostPropertiesDeliverableBP::Serialize : Start Save\n");

        PUT_SCHEMA(ar, PSS_CostPropertiesDeliverableBP);
        ar << m_ProcessingTime;
        ar << m_InWorkloadPercent;
        ar << m_OutWorkloadPercent;
        ar << m_UnitaryCost;

        TRACE("PSS_CostPropertiesDeliverableBP::Serialize : End Save\n");
    }
    else
    {
        TRACE("PSS_CostPropertiesDeliverableBP::Serialize : Start Read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);
        ar >> m_ProcessingTime;
        ar >> m_InWorkloadPercent;
        ar >> m_OutWorkloadPercent;
        ar >> m_UnitaryCost;

        TRACE("PSS_CostPropertiesDeliverableBP::Serialize : End Read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CostPropertiesDeliverableBP::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CostPropertiesDeliverableBP::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
bool PSS_CostPropertiesDeliverableBP::RegisterProperties()
{
    static bool propsRegistered = false;
    
    if (!propsRegistered)
    {
        bool success = RegisterProperty(M_Cost_Processing_Time_ID,
                                        IDS_Z_COST_PROCESSING_TIME_NAME,
                                        IDS_Z_COST_PROCESSING_TIME_DESC,
                                        _PropertyAccessor(&PSS_CostPropertiesDeliverableBP::GetProcessingTime,
                                                          &PSS_CostPropertiesDeliverableBP::SetProcessingTime),
                                        VT_R4,
                                        PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Cost_In_Workload_Percent_ID,
                                       IDS_Z_COST_IN_WORKLOAD_PERCENT_NAME, 
                                       IDS_Z_COST_IN_WORKLOAD_PERCENT_DESC,
                                       _PropertyAccessor(&PSS_CostPropertiesDeliverableBP::GetInWorkloadPercent,
                                                         &PSS_CostPropertiesDeliverableBP::SetInWorkloadPercent),
                                       VT_R4,
                                       PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Cost_Out_Workload_Percent_ID,
                                       IDS_Z_COST_OUT_WORKLOAD_PERCENT_NAME, 
                                       IDS_Z_COST_OUT_WORKLOAD_PERCENT_DESC,
                                       _PropertyAccessor(&PSS_CostPropertiesDeliverableBP::GetOutWorkloadPercent,
                                                         &PSS_CostPropertiesDeliverableBP::SetOutWorkloadPercent),
                                       VT_R4,
                                       PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Cost_Unitary_Cost_ID,
                                       IDS_Z_COST_UNITARY_COST_NAME, 
                                       IDS_Z_COST_UNITARY_COST_DESC,
                                       _PropertyAccessor(&PSS_CostPropertiesDeliverableBP::GetUnitaryCost,
                                                         &PSS_CostPropertiesDeliverableBP::SetUnitaryCost),
                                       VT_R4,
                                       PROP_DIRECT);

        if (!success)
            PSS_CostPropertiesDeliverableBP::GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
