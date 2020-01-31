/****************************************************************************
 * ==> PSS_CostPropertiesDeliverableBP -------------------------------------*
 ****************************************************************************
 * Description : Provides the cost properties for deliverables              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CostPropertiesDeliverableBP.h"

// processsodt
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
IMPLEMENT_SERIAL(PSS_CostPropertiesDeliverableBP, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_CostPropertiesDeliverableBP
//---------------------------------------------------------------------------
PSS_CostPropertiesDeliverableBP::PSS_CostPropertiesDeliverableBP() :
    CObject(),
    m_ProcessingTime(0.0),
    m_CaseDuration(0.0),
    m_CaseDurationMax(0.0),
    m_TargetDuration(0.0),
    m_GreenLineDuration(0.0),
    m_InWorkloadPercent(1.0f),
    m_OutWorkloadPercent(1.0f),
    m_UnitaryCost(0.0f)
{}
//---------------------------------------------------------------------------
PSS_CostPropertiesDeliverableBP::PSS_CostPropertiesDeliverableBP(const PSS_CostPropertiesDeliverableBP& other)
{
    *this = other;
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
    SetCaseDuration(other.GetCaseDuration());
    SetCaseDurationMax(other.GetCaseDurationMax());
    SetTargetDuration(other.GetTargetDuration());
    SetGreenLineDuration(other.GetGreenLineDuration());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::operator == (const PSS_CostPropertiesDeliverableBP& other) const
{
    return (GetProcessingTime()     == other.GetProcessingTime()     &&
            GetInWorkloadPercent()  == other.GetInWorkloadPercent()  &&
            GetOutWorkloadPercent() == other.GetOutWorkloadPercent() &&
            GetUnitaryCost()        == other.GetUnitaryCost()        &&
            GetCaseDuration()       == other.GetCaseDuration()       &&
            GetCaseDurationMax()    == other.GetCaseDurationMax()    &&
            GetTargetDuration()     == other.GetTargetDuration()     &&
            GetGreenLineDuration()  == other.GetGreenLineDuration());
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesDeliverableBP::Merge(PSS_CostPropertiesDeliverableBP* pProperty, DWORD changeFlags)
{
    if (pProperty)
    {
        if (changeFlags & IE_CT_Change_Cost_Processing_Time)
            m_ProcessingTime = pProperty->GetProcessingTime();

        if (changeFlags & IE_CT_Change_Cost_In_Workload_Percent)
            m_InWorkloadPercent = pProperty->GetInWorkloadPercent();

        if (changeFlags & IE_CT_Change_Cost_Out_Workload_Percent)
            m_OutWorkloadPercent = pProperty->GetOutWorkloadPercent();

        if (changeFlags & IE_CT_Change_Cost_Unitary_Cost)
            m_UnitaryCost = pProperty->GetUnitaryCost();

        if (changeFlags & IE_CT_Change_Cost_Case_Duration)
            m_CaseDuration = pProperty->GetCaseDuration();

        if (changeFlags & IE_CT_Change_Cost_Case_Duration_Max)
            m_CaseDurationMax = pProperty->GetCaseDurationMax();

        if (changeFlags & IE_CT_Change_Cost_Target_Duration)
            m_TargetDuration = pProperty->GetTargetDuration();

        if (changeFlags & IE_CT_Change_Cost_Green_Line_Duration)
            m_GreenLineDuration = pProperty->GetGreenLineDuration();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::IsEqual(PSS_CostPropertiesDeliverableBP* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::GetValue(const int propId, int& value) const
{
    if (propId >= M_Cost_Deliv_Processing_Time_ID && propId <= M_Cost_Deliv_Case_Duration_Max_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::GetValue(const int propId, UINT& value) const
{
    if (propId >= M_Cost_Deliv_Processing_Time_ID && propId <= M_Cost_Deliv_Case_Duration_Max_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::GetValue(const int propId, DWORD& value) const
{
    if (propId >= M_Cost_Deliv_Processing_Time_ID && propId <= M_Cost_Deliv_Case_Duration_Max_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Cost_Deliv_In_Workload_Percent_ID:  value = m_InWorkloadPercent;  break;
        case M_Cost_Deliv_Out_Workload_Percent_ID: value = m_OutWorkloadPercent; break;
        case M_Cost_Deliv_Unitary_Cost_ID:         value = m_UnitaryCost;        break;
        default:                                                                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::GetValue(const int propId, double& value) const
{
    switch (propId)
    {
        case M_Cost_Deliv_Processing_Time_ID:     value = m_ProcessingTime;    break;
        case M_Cost_Deliv_Case_Duration_ID:       value = m_CaseDuration;      break;
        case M_Cost_Deliv_Case_Duration_Max_ID:   value = m_CaseDurationMax;   break;
        case M_Cost_Deliv_Target_Duration_ID:     value = m_TargetDuration;    break;
        case M_Cost_Deliv_Green_Line_Duration_ID: value = m_GreenLineDuration; break;
        default:                                                               return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Cost_Deliv_Processing_Time_ID:      value.Format(_T("%.0f"), m_ProcessingTime);              break;
        case M_Cost_Deliv_In_Workload_Percent_ID:  value.Format(_T("%.0f"), m_InWorkloadPercent  * 100.0f); break;
        case M_Cost_Deliv_Out_Workload_Percent_ID: value.Format(_T("%.0f"), m_OutWorkloadPercent * 100.0f); break;
        case M_Cost_Deliv_Unitary_Cost_ID:         value.Format(_T("%.0f"), m_UnitaryCost);                 break;
        case M_Cost_Deliv_Case_Duration_ID:        value.Format(_T("%.0f"), m_CaseDuration);                break;
        case M_Cost_Deliv_Case_Duration_Max_ID:    value.Format(_T("%.0f"), m_CaseDurationMax);             break;
        case M_Cost_Deliv_Target_Duration_ID:      value.Format(_T("%.0f"), m_TargetDuration);              break;
        case M_Cost_Deliv_Green_Line_Duration_ID:  value.Format(_T("%.0f"), m_GreenLineDuration);           break;
        default:                                                                                            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::SetValue(const int propId, const int value)
{
    if (propId >= M_Cost_Deliv_Processing_Time_ID && propId <= M_Cost_Deliv_Case_Duration_Max_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::SetValue(const int propId, const UINT value)
{
    if (propId >= M_Cost_Deliv_Processing_Time_ID && propId <= M_Cost_Deliv_Case_Duration_Max_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::SetValue(const int propId, const DWORD value)
{
    if (propId >= M_Cost_Deliv_Processing_Time_ID && propId <= M_Cost_Deliv_Case_Duration_Max_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Cost_Deliv_In_Workload_Percent_ID:  m_InWorkloadPercent  = value; break;
        case M_Cost_Deliv_Out_Workload_Percent_ID: m_OutWorkloadPercent = value; break;
        case M_Cost_Deliv_Unitary_Cost_ID:         m_UnitaryCost        = value; break;
        default:                                                                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::SetValue(const int propId, const double value)
{
    switch (propId)
    {
        case M_Cost_Deliv_Processing_Time_ID:     m_ProcessingTime    = value; break;
        case M_Cost_Deliv_Case_Duration_ID:       m_CaseDuration      = value; break;
        case M_Cost_Deliv_Case_Duration_Max_ID:   m_CaseDurationMax   = value; break;
        case M_Cost_Deliv_Target_Duration_ID:     m_TargetDuration    = value; break;
        case M_Cost_Deliv_Green_Line_Duration_ID: m_GreenLineDuration = value; break;
        default:                                                               return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesDeliverableBP::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Cost_Deliv_Processing_Time_ID:      m_ProcessingTime     = std::atof(pValue);                              break;
        case M_Cost_Deliv_In_Workload_Percent_ID:  m_InWorkloadPercent  = static_cast<float>(std::atof(pValue) / 100.0f); break;
        case M_Cost_Deliv_Out_Workload_Percent_ID: m_OutWorkloadPercent = static_cast<float>(std::atof(pValue) / 100.0f); break;
        case M_Cost_Deliv_Unitary_Cost_ID:         m_UnitaryCost        = static_cast<float>(std::atof(pValue));          break;
        case M_Cost_Deliv_Case_Duration_ID:        m_CaseDuration       = std::atof(pValue);                              break;
        case M_Cost_Deliv_Case_Duration_Max_ID:    m_CaseDurationMax    = std::atof(pValue);                              break;
        case M_Cost_Deliv_Target_Duration_ID:      m_TargetDuration     = std::atof(pValue);                              break;
        case M_Cost_Deliv_Green_Line_Duration_ID:  m_GreenLineDuration  = std::atof(pValue);                              break;
        default:                                                                                                          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesDeliverableBP::Serialize(CArchive& ar)
{
    CObject::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE(_T("PSS_CostPropertiesDeliverableBP::Serialize - Start Save\n"));

        PUT_SCHEMA(ar, PSS_CostPropertiesDeliverableBP);

        ar << m_ProcessingTime;
        ar << m_InWorkloadPercent;
        ar << m_OutWorkloadPercent;
        ar << m_UnitaryCost;
        ar << m_CaseDuration;
        ar << m_CaseDurationMax;
        ar << m_TargetDuration;
        ar << m_GreenLineDuration;

        TRACE(_T("PSS_CostPropertiesDeliverableBP::Serialize - End Save\n"));
    }
    else
    {
        TRACE(_T("PSS_CostPropertiesDeliverableBP::Serialize - Start Read\n"));

        UINT schema;
        GET_SCHEMA(ar, schema);

        ar >> m_ProcessingTime;
        ar >> m_InWorkloadPercent;
        ar >> m_OutWorkloadPercent;
        ar >> m_UnitaryCost;

        PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 20)
            ar >> m_CaseDuration;

        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 21)
            ar >> m_CaseDurationMax;

        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 20)
        {
            ar >> m_TargetDuration;
            ar >> m_GreenLineDuration;
        }

        TRACE(_T("PSS_CostPropertiesDeliverableBP::Serialize - End Read\n"));
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CostPropertiesDeliverableBP::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CostPropertiesDeliverableBP::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
