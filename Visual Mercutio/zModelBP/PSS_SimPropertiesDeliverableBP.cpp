/****************************************************************************
 * ==> PSS_SimPropertiesDeliverableBP --------------------------------------*
 ****************************************************************************
 * Description : Provides the simulation properties for deliverable         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SimPropertiesDeliverableBP.h"

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
IMPLEMENT_SERIAL(PSS_SimPropertiesDeliverableBP, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_SimPropertiesDeliverableBP
//---------------------------------------------------------------------------
PSS_SimPropertiesDeliverableBP::PSS_SimPropertiesDeliverableBP() :
    CObject(),
    m_Cost(0.0),
    m_WorkloadForecast(0.0)
{}
//---------------------------------------------------------------------------
PSS_SimPropertiesDeliverableBP::PSS_SimPropertiesDeliverableBP(const PSS_SimPropertiesDeliverableBP& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_SimPropertiesDeliverableBP::~PSS_SimPropertiesDeliverableBP()
{}
//---------------------------------------------------------------------------
PSS_SimPropertiesDeliverableBP& PSS_SimPropertiesDeliverableBP::operator = (const PSS_SimPropertiesDeliverableBP& other)
{
    SetCost(const_cast<PSS_SimPropertiesDeliverableBP&>(other).GetCost());
    SetWorkloadForecast(const_cast<PSS_SimPropertiesDeliverableBP&>(other).GetWorkloadForecast());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::operator == (const PSS_SimPropertiesDeliverableBP& other) const
{
    return (const_cast<PSS_SimPropertiesDeliverableBP*>(this)->GetCost()             == const_cast<PSS_SimPropertiesDeliverableBP&>(other).GetCost() &&
            const_cast<PSS_SimPropertiesDeliverableBP*>(this)->GetWorkloadForecast() == const_cast<PSS_SimPropertiesDeliverableBP&>(other).GetWorkloadForecast());
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesDeliverableBP::Merge(PSS_SimPropertiesDeliverableBP* pProp, DWORD changeFlags)
{
    if (pProp)
    {
        if (changeFlags & IE_CT_Change_Sim_Deliv_Cost)
            m_Cost = pProp->GetCost();

        if (changeFlags & IE_CT_Change_Sim_Deliv_Workload_Forecast)
            m_WorkloadForecast = pProp->GetWorkloadForecast();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::IsEqual(PSS_SimPropertiesDeliverableBP* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::GetValue(const int propId, int& value) const
{
    if (propId >= M_Sim_Deliv_Cost_ID && propId <= M_Sim_Deliv_Workload_Forecast_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::GetValue(const int propId, UINT& value) const
{
    if (propId >= M_Sim_Deliv_Cost_ID && propId <= M_Sim_Deliv_Workload_Forecast_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::GetValue(const int propId, DWORD& value) const
{
    if (propId >= M_Sim_Deliv_Cost_ID && propId <= M_Sim_Deliv_Workload_Forecast_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Sim_Deliv_Cost_ID:              value = float(double(m_Cost));             break;
        case M_Sim_Deliv_Workload_Forecast_ID: value = float(double(m_WorkloadForecast)); break;
        default:                                                                          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::GetValue(const int propId, double& value) const
{
    switch (propId)
    {
        case M_Sim_Deliv_Cost_ID:              value = double(m_Cost);             break;
        case M_Sim_Deliv_Workload_Forecast_ID: value = double(m_WorkloadForecast); break;
        default:                                                                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Sim_Deliv_Cost_ID:              value.Format(_T("%.0f"), float(double(m_Cost)             * 100.0)); break;
        case M_Sim_Deliv_Workload_Forecast_ID: value.Format(_T("%.0f"), float(double(m_WorkloadForecast) * 100.0)); break;
        default:                                                                                                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::SetValue(const int propId, const int value)
{
    if (propId >= M_Sim_Deliv_Cost_ID && propId <= M_Sim_Deliv_Workload_Forecast_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::SetValue(const int propId, const UINT value)
{
    if (propId >= M_Sim_Deliv_Cost_ID && propId <= M_Sim_Deliv_Workload_Forecast_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::SetValue(const int propId, const DWORD value)
{
    if (propId >= M_Sim_Deliv_Cost_ID && propId <= M_Sim_Deliv_Workload_Forecast_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Sim_Deliv_Cost_ID:              m_Cost             = double(value); break;
        case M_Sim_Deliv_Workload_Forecast_ID: m_WorkloadForecast = double(value); break;
        default:                                                                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::SetValue(const int propId, const double value)
{
    switch (propId)
    {
        case M_Sim_Deliv_Cost_ID:              m_Cost             = value; break;
        case M_Sim_Deliv_Workload_Forecast_ID: m_WorkloadForecast = value; break;
        default:                                                           return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesDeliverableBP::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Sim_Deliv_Cost_ID:              m_Cost             = std::atof(pValue) / 100.0; break;
        case M_Sim_Deliv_Workload_Forecast_ID: m_WorkloadForecast = std::atof(pValue) / 100.0; break;
        default:                                                                               return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesDeliverableBP::Serialize(CArchive& ar)
{
    m_Cost.Serialize(ar);
    m_WorkloadForecast.Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_SimPropertiesDeliverableBP::Serialize - Start save\n");

        PUT_SCHEMA(ar, PSS_SimPropertiesDeliverableBP);

        TRACE("PSS_SimPropertiesDeliverableBP::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_SimPropertiesDeliverableBP::Serialize - Start read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);

        TRACE("PSS_SimPropertiesDeliverableBP::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SimPropertiesDeliverableBP::AssertValid() const
    {
        CObject::AssertValid();
    }
#ifdef _DEBUG
//---------------------------------------------------------------------------
#endif
    void PSS_SimPropertiesDeliverableBP::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
