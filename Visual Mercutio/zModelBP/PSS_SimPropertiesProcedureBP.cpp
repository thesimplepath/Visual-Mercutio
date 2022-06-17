/****************************************************************************
 * ==> PSS_SimPropertiesProcedureBP ----------------------------------------*
 ****************************************************************************
 * Description : Provides the simulation properties for procedure           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SimPropertiesProcedureBP.h"

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
IMPLEMENT_SERIAL(PSS_SimPropertiesProcedureBP, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_SimPropertiesProcedureBP
//---------------------------------------------------------------------------
PSS_SimPropertiesProcedureBP::PSS_SimPropertiesProcedureBP() :
    CObject(),
    m_ProcedureActivation(1.0),
    m_ProcedureCost(0.0),
    m_ProcedureWorkloadForecast(1.0),
    m_ProcedureCostForecast(0.0),
    m_ProcedureWorkloadPerActivity(0.0),
    m_ProcedureCostPerActivity(0.0)
{}
//---------------------------------------------------------------------------
PSS_SimPropertiesProcedureBP::PSS_SimPropertiesProcedureBP(const PSS_SimPropertiesProcedureBP& other) :
    CObject(),
    m_ProcedureActivation(1.0),
    m_ProcedureCost(0.0),
    m_ProcedureWorkloadForecast(1.0),
    m_ProcedureCostForecast(0.0),
    m_ProcedureWorkloadPerActivity(0.0),
    m_ProcedureCostPerActivity(0.0)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_SimPropertiesProcedureBP::~PSS_SimPropertiesProcedureBP()
{}
//---------------------------------------------------------------------------
PSS_SimPropertiesProcedureBP& PSS_SimPropertiesProcedureBP::operator = (const PSS_SimPropertiesProcedureBP& other)
{
    SetProcedureActivation         (double(const_cast<PSS_SimPropertiesProcedureBP&>(other).GetProcedureActivation()));
    SetProcedureCost               (double(const_cast<PSS_SimPropertiesProcedureBP&>(other).GetProcedureCost()));
    SetProcedureWorkloadForecast   (double(const_cast<PSS_SimPropertiesProcedureBP&>(other).GetProcedureWorkloadForecast()));
    SetProcedureCostForecast       (double(const_cast<PSS_SimPropertiesProcedureBP&>(other).GetProcedureCostForecast()));
    SetProcedureWorkloadPerActivity(double(const_cast<PSS_SimPropertiesProcedureBP&>(other).GetProcedureWorkloadPerActivity()));
    SetProcedureCostPerActivity    (double(const_cast<PSS_SimPropertiesProcedureBP&>(other).GetProcedureCostPerActivity()));

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::operator == (const PSS_SimPropertiesProcedureBP& other) const
{
    return (const_cast<PSS_SimPropertiesProcedureBP*>(this)->GetProcedureActivation()          == const_cast<PSS_SimPropertiesProcedureBP&>(other).GetProcedureActivation()          &&
            const_cast<PSS_SimPropertiesProcedureBP*>(this)->GetProcedureCost()                == const_cast<PSS_SimPropertiesProcedureBP&>(other).GetProcedureCost()                &&
            const_cast<PSS_SimPropertiesProcedureBP*>(this)->GetProcedureWorkloadForecast()    == const_cast<PSS_SimPropertiesProcedureBP&>(other).GetProcedureWorkloadForecast()    &&
            const_cast<PSS_SimPropertiesProcedureBP*>(this)->GetProcedureCostForecast()        == const_cast<PSS_SimPropertiesProcedureBP&>(other).GetProcedureCostForecast()        &&
            const_cast<PSS_SimPropertiesProcedureBP*>(this)->GetProcedureWorkloadPerActivity() == const_cast<PSS_SimPropertiesProcedureBP&>(other).GetProcedureWorkloadPerActivity() &&
            const_cast<PSS_SimPropertiesProcedureBP*>(this)->GetProcedureCostPerActivity()     == const_cast<PSS_SimPropertiesProcedureBP&>(other).GetProcedureCostPerActivity());
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcedureBP::Merge(PSS_SimPropertiesProcedureBP* pProp, DWORD changeFlags)
{
    if (pProp)
    {
        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Sim_Procedure_Activation)
            m_ProcedureActivation = pProp->GetProcedureActivation();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Sim_Procedure_Cost)
            m_ProcedureCost = pProp->GetProcedureCost();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Sim_Procedure_Workload_Forecast)
            m_ProcedureWorkloadForecast = pProp->GetProcedureWorkloadForecast();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Sim_Procedure_Cost_Forecast)
            m_ProcedureCostForecast = pProp->GetProcedureCostForecast();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Sim_Procedure_Workload_Per_Activ_Forecast)
            m_ProcedureWorkloadPerActivity = pProp->GetProcedureWorkloadPerActivity();

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Sim_Procedure_Cost_Per_Activ_Forecast)
            m_ProcedureCostPerActivity = pProp->GetProcedureCostPerActivity();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::IsEqual(PSS_SimPropertiesProcedureBP* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::GetValue(const int propId, int& value) const
{
    if (propId >= M_Sim_Procedure_Activation_ID && propId <= M_Sim_Procedure_Cost_Per_Activ_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::GetValue(const int propId, UINT& value) const
{
    if (propId >= M_Sim_Procedure_Activation_ID && propId <= M_Sim_Procedure_Cost_Per_Activ_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::GetValue(const int propId, DWORD& value) const
{
    if (propId >= M_Sim_Procedure_Activation_ID && propId <= M_Sim_Procedure_Cost_Per_Activ_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Sim_Procedure_Activation_ID:         value = float(double(m_ProcedureActivation));          break;
        case M_Sim_Procedure_Cost_ID:               value = float(double(m_ProcedureCost));                break;
        case M_Sim_Procedure_Workload_Forecast_ID:  value = float(double(m_ProcedureWorkloadForecast));    break;
        case M_Sim_Procedure_Cost_Forecast_ID:      value = float(double(m_ProcedureCostForecast));        break;
        case M_Sim_Procedure_Workload_Per_Activ_ID: value = float(double(m_ProcedureCostPerActivity));     break;
        case M_Sim_Procedure_Cost_Per_Activ_ID:     value = float(double(m_ProcedureWorkloadPerActivity)); break;
        default:                                                                                           return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::GetValue(const int propId, double& value) const
{
    switch (propId)
    {
        case M_Sim_Procedure_Activation_ID:         value = double(m_ProcedureActivation);          break;
        case M_Sim_Procedure_Cost_ID:               value = double(m_ProcedureCost);                break;
        case M_Sim_Procedure_Workload_Forecast_ID:  value = double(m_ProcedureWorkloadForecast);    break;
        case M_Sim_Procedure_Cost_Forecast_ID:      value = double(m_ProcedureCostForecast);        break;
        case M_Sim_Procedure_Workload_Per_Activ_ID: value = double(m_ProcedureCostPerActivity);     break;
        case M_Sim_Procedure_Cost_Per_Activ_ID:     value = double(m_ProcedureWorkloadPerActivity); break;
        default:                                                                                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Sim_Procedure_Activation_ID:         value.Format(_T("%.0f"), double(m_ProcedureActivation));          break;
        case M_Sim_Procedure_Cost_ID:               value.Format(_T("%.0f"), double(m_ProcedureCost));                break;
        case M_Sim_Procedure_Workload_Forecast_ID:  value.Format(_T("%.0f"), double(m_ProcedureWorkloadForecast));    break;
        case M_Sim_Procedure_Cost_Forecast_ID:      value.Format(_T("%.0f"), double(m_ProcedureCostForecast));        break;
        case M_Sim_Procedure_Workload_Per_Activ_ID: value.Format(_T("%.0f"), double(m_ProcedureWorkloadPerActivity)); break;
        case M_Sim_Procedure_Cost_Per_Activ_ID:     value.Format(_T("%.0f"), double(m_ProcedureCostPerActivity));     break;
        default:                                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::SetValue(const int propId, const int value)
{
    if (propId >= M_Sim_Procedure_Activation_ID && propId <= M_Sim_Procedure_Cost_Per_Activ_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::SetValue(const int propId, const UINT value)
{
    if (propId >= M_Sim_Procedure_Activation_ID && propId <= M_Sim_Procedure_Cost_Per_Activ_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::SetValue(const int propId, const DWORD value)
{
    if (propId >= M_Sim_Procedure_Activation_ID && propId <= M_Sim_Procedure_Cost_Per_Activ_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Sim_Procedure_Activation_ID:         m_ProcedureActivation          = double(value); break;
        case M_Sim_Procedure_Cost_ID:               m_ProcedureCost                = double(value); break;
        case M_Sim_Procedure_Workload_Forecast_ID:  m_ProcedureWorkloadForecast    = double(value); break;
        case M_Sim_Procedure_Cost_Forecast_ID:      m_ProcedureCostForecast        = double(value); break;
        case M_Sim_Procedure_Workload_Per_Activ_ID: m_ProcedureCostPerActivity     = double(value); break;
        case M_Sim_Procedure_Cost_Per_Activ_ID:     m_ProcedureWorkloadPerActivity = double(value); break;
        default:                                                                                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::SetValue(const int propId, const double value)
{
    switch (propId)
    {
        case M_Sim_Procedure_Activation_ID:         m_ProcedureActivation          = value; break;
        case M_Sim_Procedure_Cost_ID:               m_ProcedureCost                = value; break;
        case M_Sim_Procedure_Workload_Forecast_ID:  m_ProcedureWorkloadForecast    = value; break;
        case M_Sim_Procedure_Cost_Forecast_ID:      m_ProcedureCostForecast        = value; break;
        case M_Sim_Procedure_Workload_Per_Activ_ID: m_ProcedureCostPerActivity     = value; break;
        case M_Sim_Procedure_Cost_Per_Activ_ID:     m_ProcedureWorkloadPerActivity = value; break;
        default:                                                                            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SimPropertiesProcedureBP::SetValue(const int propId, LPCTSTR pValue)
{
    switch (propId)
    {
        case M_Sim_Procedure_Activation_ID:         m_ProcedureActivation          = std::atof(pValue); break;
        case M_Sim_Procedure_Cost_ID:               m_ProcedureCost                = std::atof(pValue); break;
        case M_Sim_Procedure_Workload_Forecast_ID:  m_ProcedureWorkloadForecast    = std::atof(pValue); break;
        case M_Sim_Procedure_Cost_Forecast_ID:      m_ProcedureCostForecast        = std::atof(pValue); break;
        case M_Sim_Procedure_Workload_Per_Activ_ID: m_ProcedureWorkloadPerActivity = std::atof(pValue); break;
        case M_Sim_Procedure_Cost_Per_Activ_ID:     m_ProcedureCostPerActivity     = std::atof(pValue); break;
        default:                                                                                        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcedureBP::Serialize(CArchive& ar)
{
    m_ProcedureActivation.Serialize(ar);
    m_ProcedureCost.Serialize(ar);
    m_ProcedureWorkloadForecast.Serialize(ar);
    m_ProcedureCostForecast.Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_SimPropertiesProcedureBP::Serialize - Start save\n");

        PUT_SCHEMA(ar, PSS_SimPropertiesProcedureBP);

        ar << m_ProcedureWorkloadPerActivity;
        ar << m_ProcedureCostPerActivity;

        TRACE("PSS_SimPropertiesProcedureBP::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_SimPropertiesProcedureBP::Serialize - Start read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);

        ar >> m_ProcedureWorkloadPerActivity;
        ar >> m_ProcedureCostPerActivity;

        TRACE("PSS_SimPropertiesProcedureBP::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SimPropertiesProcedureBP::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SimPropertiesProcedureBP::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
