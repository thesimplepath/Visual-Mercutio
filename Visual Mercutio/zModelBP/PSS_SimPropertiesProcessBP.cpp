/****************************************************************************
 * ==> PSS_SimPropertiesProcessBP ------------------------------------------*
 ****************************************************************************
 * Description : Provides the simulation properties for process             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SimPropertiesProcessBP.h"

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
IMPLEMENT_SERIAL(PSS_SimPropertiesProcessBP, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_SimPropertiesProcessBP
//---------------------------------------------------------------------------
PSS_SimPropertiesProcessBP::PSS_SimPropertiesProcessBP() :
    CObject(),
    m_ProcessWorkloadForecast(1.0),
    m_ProcessCostForecast(0.0),
    m_ProcessCostHMO(0.0)
{}
//---------------------------------------------------------------------------
PSS_SimPropertiesProcessBP::PSS_SimPropertiesProcessBP(const PSS_SimPropertiesProcessBP& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_SimPropertiesProcessBP::~PSS_SimPropertiesProcessBP()
{}
//---------------------------------------------------------------------------
PSS_SimPropertiesProcessBP& PSS_SimPropertiesProcessBP::operator = (const PSS_SimPropertiesProcessBP& other)
{
    SetProcessWorkloadForecast(const_cast<PSS_SimPropertiesProcessBP&>(other).GetProcessWorkloadForecast());
    SetProcessCostForecast    (const_cast<PSS_SimPropertiesProcessBP&>(other).GetProcessCostForecast());
    SetProcessCostHMO         (const_cast<PSS_SimPropertiesProcessBP&>(other).GetProcessCostHMO());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::operator == (const PSS_SimPropertiesProcessBP& other) const
{
    return (const_cast<PSS_SimPropertiesProcessBP*>(this)->GetProcessWorkloadForecast() == const_cast<PSS_SimPropertiesProcessBP&>(other).GetProcessWorkloadForecast() &&
            const_cast<PSS_SimPropertiesProcessBP*>(this)->GetProcessCostForecast()     == const_cast<PSS_SimPropertiesProcessBP&>(other).GetProcessCostForecast()     &&
            const_cast<PSS_SimPropertiesProcessBP*>(this)->GetProcessCostHMO()          == const_cast<PSS_SimPropertiesProcessBP&>(other).GetProcessCostHMO());
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcessBP::Merge(PSS_SimPropertiesProcessBP* pProp, DWORD changeFlags)
{
    if (pProp)
    {
        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Sim_Process_Workload_Forecast)
            m_ProcessWorkloadForecast = pProp->GetProcessWorkloadForecast();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Sim_Process_Cost_Forecast)
            m_ProcessCostForecast = pProp->GetProcessCostForecast();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Sim_Process_Cost_HMO)
            m_ProcessCostHMO = pProp->GetProcessCostHMO();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::IsEqual(PSS_SimPropertiesProcessBP* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::GetValue(const int propId, int& value) const
{
    if (propId >= M_Sim_Process_Workload_Forecast_ID && propId <= M_Sim_Process_Cost_HMO_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::GetValue(const int propId, UINT& value) const
{
    if (propId >= M_Sim_Process_Workload_Forecast_ID && propId <= M_Sim_Process_Cost_HMO_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::GetValue(const int propId, DWORD& value) const
{
    if (propId >= M_Sim_Process_Workload_Forecast_ID && propId <= M_Sim_Process_Cost_HMO_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Sim_Process_Workload_Forecast_ID: value = float(double(m_ProcessWorkloadForecast)); break;
        case M_Sim_Process_Cost_Forecast_ID:     value = float(double(m_ProcessCostForecast));     break;
        case M_Sim_Process_Cost_HMO_ID:          value = float(double(m_ProcessCostHMO));          break;
        default:                                                                                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::GetValue(const int propId, double& value) const
{
    switch (propId)
    {
        case M_Sim_Process_Workload_Forecast_ID: value = double(m_ProcessWorkloadForecast); break;
        case M_Sim_Process_Cost_Forecast_ID:     value = double(m_ProcessCostForecast);     break;
        case M_Sim_Process_Cost_HMO_ID:          value = double(m_ProcessCostHMO);          break;
        default:                                                                            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Sim_Process_Workload_Forecast_ID: value.Format(_T("%.0f"), double(m_ProcessWorkloadForecast)); break;
        case M_Sim_Process_Cost_Forecast_ID:     value.Format(_T("%.0f"), double(m_ProcessCostForecast));     break;
        case M_Sim_Process_Cost_HMO_ID:          value.Format(_T("%.0f"), double(m_ProcessCostHMO));          break;
        default:                                 throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::SetValue(const int propId, const int value)
{
    if (propId >= M_Sim_Process_Workload_Forecast_ID && propId <= M_Sim_Process_Cost_HMO_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::SetValue(const int propId, const UINT value)
{
    if (propId >= M_Sim_Process_Workload_Forecast_ID && propId <= M_Sim_Process_Cost_HMO_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::SetValue(const int propId, const DWORD value)
{
    if (propId >= M_Sim_Process_Workload_Forecast_ID && propId <= M_Sim_Process_Cost_HMO_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Sim_Process_Workload_Forecast_ID: m_ProcessWorkloadForecast = double(value); break;
        case M_Sim_Process_Cost_Forecast_ID:     m_ProcessCostForecast     = double(value); break;
        case M_Sim_Process_Cost_HMO_ID:          m_ProcessCostHMO          = double(value); break;
        default:                                                                            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::SetValue(const int propId, const double value)
{
    switch (propId)
    {
        case M_Sim_Process_Workload_Forecast_ID: m_ProcessWorkloadForecast = value; break;
        case M_Sim_Process_Cost_Forecast_ID:     m_ProcessCostForecast     = value; break;
        case M_Sim_Process_Cost_HMO_ID:          m_ProcessCostHMO          = value; break;
        default:                                                                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcessBP::SetValue(const int propId, LPCTSTR pValue)
{
    switch (propId)
    {
        case M_Sim_Process_Workload_Forecast_ID: m_ProcessWorkloadForecast = std::atof(pValue); break;
        case M_Sim_Process_Cost_Forecast_ID:     m_ProcessCostForecast     = std::atof(pValue); break;
        case M_Sim_Process_Cost_HMO_ID:          m_ProcessCostHMO          = std::atof(pValue); break;
        default:                                                                                return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcessBP::Serialize(CArchive& ar)
{
    m_ProcessWorkloadForecast.Serialize(ar);
    m_ProcessCostForecast.Serialize(ar);

    if (ar.IsStoring())
        m_ProcessCostHMO.Serialize(ar);
    else
    {
        PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 24)
            m_ProcessCostHMO.Serialize(ar);
    }

    if (ar.IsStoring())
    {
        TRACE("PSS_SimPropertiesProcessBP::Serialize - Start save\n");

        PUT_SCHEMA(ar, PSS_SimPropertiesProcessBP);

        TRACE("PSS_SimPropertiesProcessBP::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_SimPropertiesProcessBP::Serialize - Start read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);

        TRACE("PSS_SimPropertiesProcessBP::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SimPropertiesProcessBP::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SimPropertiesProcessBP::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
