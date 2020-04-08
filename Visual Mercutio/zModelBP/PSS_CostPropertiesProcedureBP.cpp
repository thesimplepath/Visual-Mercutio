/****************************************************************************
 * ==> PSS_CostPropertiesProcedureBP ---------------------------------------*
 ****************************************************************************
 * Description : Provides the cost properties for procedures                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CostPropertiesProcedureBP.h"

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
IMPLEMENT_SERIAL(PSS_CostPropertiesProcedureBP, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_CostPropertiesProcedureBP
//---------------------------------------------------------------------------
PSS_CostPropertiesProcedureBP::PSS_CostPropertiesProcedureBP() :
    CObject(),
    m_ProcessingTime(0.0),
    m_ProcessingDuration(0.0),
    m_ProcessingDurationMax(0.0),
    m_Multiplier(1.0f),
    m_UnitaryCost(0.0f)
{}
//---------------------------------------------------------------------------
PSS_CostPropertiesProcedureBP::PSS_CostPropertiesProcedureBP(const PSS_CostPropertiesProcedureBP& other) :
    CObject(),
    m_ProcessingTime(0.0),
    m_ProcessingDuration(0.0),
    m_ProcessingDurationMax(0.0),
    m_Multiplier(1.0f),
    m_UnitaryCost(0.0f)
{
    *this = other;
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
    SetProcessingDuration(other.GetProcessingDuration());
    SetProcessingDurationMax(other.GetProcessingDurationMax());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::operator == (const PSS_CostPropertiesProcedureBP& other) const
{
    return (GetMultiplier()            == other.GetMultiplier()         &&
            GetProcessingTime()        == other.GetProcessingTime()     &&
            GetUnitaryCost()           == other.GetUnitaryCost()        &&
            GetProcessingDuration()    == other.GetProcessingDuration() &&
            GetProcessingDurationMax() == other.GetProcessingDurationMax());
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesProcedureBP::Merge(PSS_CostPropertiesProcedureBP* pProp, DWORD changeFlags)
{
    if (pProp)
    {
        if (changeFlags & IE_CT_Change_Cost_Multiplier)
            m_Multiplier = pProp->GetMultiplier();

        if (changeFlags & IE_CT_Change_Cost_Processing_Time)
            m_ProcessingTime = pProp->GetProcessingTime();

        if (changeFlags & IE_CT_Change_Cost_Unitary_Cost)
            m_UnitaryCost = pProp->GetUnitaryCost();

        if (changeFlags & IE_CT_Change_Cost_Processing_Duration)
            m_ProcessingDuration = pProp->GetProcessingDuration();

        if (changeFlags & IE_CT_Change_Cost_Processing_Duration_Max)
            m_ProcessingDurationMax = pProp->GetProcessingDurationMax();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::IsEqual(PSS_CostPropertiesProcedureBP* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::GetValue(const int propId, int& value) const
{
    if (propId >= M_Cost_Proc_Multiplier_ID && propId <= M_Cost_Proc_Processing_Duration_Max_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::GetValue(const int propId, UINT& value) const
{
    if (propId >= M_Cost_Proc_Multiplier_ID && propId <= M_Cost_Proc_Processing_Duration_Max_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::GetValue(const int propId, DWORD& value) const
{
    if (propId >= M_Cost_Proc_Multiplier_ID && propId <= M_Cost_Proc_Processing_Duration_Max_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Cost_Proc_Multiplier_ID:   value = m_Multiplier;  break;
        case M_Cost_Proc_Unitary_Cost_ID: value = m_UnitaryCost; break;
        default:                                                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::GetValue(const int propId, double& value) const
{
    switch (propId)
    {
        case M_Cost_Proc_Processing_Time_ID:     value = m_ProcessingTime;     break;
        case M_Cost_Proc_Processing_Duration_ID: value = m_ProcessingDuration; break;
        default:                                                               return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Cost_Proc_Multiplier_ID:              value.Format(_T("%.0f"), m_Multiplier);            break;
        case M_Cost_Proc_Processing_Time_ID:         value.Format(_T("%.0f"), m_ProcessingTime);        break;
        case M_Cost_Proc_Unitary_Cost_ID:            value.Format(_T("%.0f"), m_UnitaryCost);           break;
        case M_Cost_Proc_Processing_Duration_ID:     value.Format(_T("%.0f"), m_ProcessingDuration);    break;
        case M_Cost_Proc_Processing_Duration_Max_ID: value.Format(_T("%.0f"), m_ProcessingDurationMax); break;
        default:                                     throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::SetValue(const int propId, const int value)
{
    if (propId >= M_Cost_Proc_Multiplier_ID && propId <= M_Cost_Proc_Processing_Duration_Max_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::SetValue(const int propId, const UINT value)
{
    if (propId >= M_Cost_Proc_Multiplier_ID && propId <= M_Cost_Proc_Processing_Duration_Max_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::SetValue(const int nPropId, const DWORD value)
{
    if (nPropId >= M_Cost_Proc_Multiplier_ID && nPropId <= M_Cost_Proc_Processing_Duration_Max_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Cost_Proc_Multiplier_ID:   m_Multiplier  = value; break;
        case M_Cost_Proc_Unitary_Cost_ID: m_UnitaryCost = value; break;
        default:                                                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::SetValue(const int propId, const double value)
{
    switch (propId)
    {
        case M_Cost_Proc_Processing_Time_ID:         m_ProcessingTime        = value; break;
        case M_Cost_Proc_Processing_Duration_ID:     m_ProcessingDuration    = value; break;
        case M_Cost_Proc_Processing_Duration_Max_ID: m_ProcessingDurationMax = value; break;
        default:                                                                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CostPropertiesProcedureBP::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Cost_Proc_Multiplier_ID:              m_Multiplier            = static_cast<float>(std::atof(pValue)); break;
        case M_Cost_Proc_Processing_Time_ID:         m_ProcessingTime        = std::atof(pValue);                     break;
        case M_Cost_Proc_Unitary_Cost_ID:            m_UnitaryCost           = static_cast<float>(std::atof(pValue)); break;
        case M_Cost_Proc_Processing_Duration_ID:     m_ProcessingDuration    = std::atof(pValue);                     break;
        case M_Cost_Proc_Processing_Duration_Max_ID: m_ProcessingDurationMax = std::atof(pValue);                     break;
        default:                                                                                                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesProcedureBP::Serialize(CArchive& ar)
{
    CObject::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE(_T("PSS_CostPropertiesProcedureBP::Serialize - Start Save\n"));

        PUT_SCHEMA(ar, PSS_CostPropertiesProcedureBP);

        ar << m_Multiplier;
        ar << m_ProcessingTime;
        ar << m_UnitaryCost;
        ar << m_ProcessingDuration;
        ar << m_ProcessingDurationMax;

        TRACE(_T("PSS_CostPropertiesProcedureBP::Serialize - End Save\n"));
    }
    else
    {
        TRACE(_T("PSS_CostPropertiesProcedureBP::Serialize - Start Read\n"));

        UINT schema;
        GET_SCHEMA(ar, schema);

        ar >> m_Multiplier;
        ar >> m_ProcessingTime;
        ar >> m_UnitaryCost;

        PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

        if (pDocument)
        {
            if (pDocument->GetDocumentStamp().GetInternalVersion() >= 20)
                ar >> m_ProcessingDuration;

            if (pDocument->GetDocumentStamp().GetInternalVersion() >= 21)
                ar >> m_ProcessingDurationMax;
        }

        TRACE(_T("PSS_CostPropertiesProcedureBP::Serialize - End Read\n"));
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CostPropertiesProcedureBP::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CostPropertiesProcedureBP::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
