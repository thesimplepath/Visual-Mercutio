/****************************************************************************
 * ==> PSS_RiskPropertiesBP ------------------------------------------------*
 ****************************************************************************
 * Description : Provides the risk properties for banking process           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RiskPropertiesBP.h"

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
IMPLEMENT_SERIAL(PSS_RiskPropertiesBP, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_RiskPropertiesBP
//---------------------------------------------------------------------------
PSS_RiskPropertiesBP::PSS_RiskPropertiesBP() :
    CObject(),
    m_RiskImpact(0),
    m_RiskProbability(0),
    m_RiskSeverity(0),
    m_RiskUE(0.0f),
    m_RiskPOA(0.0f),
    m_RiskAction(false)
{}
//---------------------------------------------------------------------------
PSS_RiskPropertiesBP::PSS_RiskPropertiesBP(const PSS_RiskPropertiesBP& other)
{
    m_RiskName        = other.GetRiskName();
    m_RiskDesc        = other.GetRiskDesc();
    m_RiskType        = other.GetRiskType();
    m_RiskImpact      = other.GetRiskImpact();
    m_RiskProbability = other.GetRiskProbability();
    m_RiskSeverity    = other.GetRiskSeverity();
    m_RiskUE          = other.GetRiskUE();
    m_RiskPOA         = other.GetRiskPOA();
    m_RiskAction      = other.GetRiskAction();
}
//---------------------------------------------------------------------------
PSS_RiskPropertiesBP::~PSS_RiskPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_RiskPropertiesBP& PSS_RiskPropertiesBP::operator = (const PSS_RiskPropertiesBP& other)
{
    SetRiskName(other.GetRiskName());
    SetRiskDesc(other.GetRiskDesc());
    SetRiskType(other.GetRiskType());
    SetRiskImpact(other.GetRiskImpact());
    SetRiskProbability(other.GetRiskProbability());
    SetRiskSeverity(other.GetRiskSeverity());
    SetRiskUE(other.GetRiskUE());
    SetRiskPOA(other.GetRiskPOA());
    SetRiskAction(other.GetRiskAction());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::operator == (const PSS_RiskPropertiesBP& other) const
{
    return (GetRiskName()        == other.GetRiskName()        &&
            GetRiskDesc()        == other.GetRiskDesc()        &&
            GetRiskType()        == other.GetRiskType()        &&
            GetRiskImpact()      == other.GetRiskImpact()      &&
            GetRiskProbability() == other.GetRiskProbability() &&
            GetRiskSeverity()    == other.GetRiskSeverity()    &&
            GetRiskUE()          == other.GetRiskUE()          &&
            GetRiskPOA()         == other.GetRiskPOA()         &&
            GetRiskAction()      == other.GetRiskAction());
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::Merge(PSS_RiskPropertiesBP* pProp, DWORD changeFlags)
{
    if (pProp)
    {
        if (changeFlags & IE_CT_Change_Risk_Name)
            m_RiskName = pProp->GetRiskName();

        if (changeFlags & IE_CT_Change_Risk_Desc)
            m_RiskDesc = pProp->GetRiskDesc();

        if (changeFlags & IE_CT_Change_Risk_Type)
            m_RiskType = pProp->GetRiskType();

        if (changeFlags & IE_CT_Change_Risk_Impact)
            m_RiskImpact = pProp->GetRiskImpact();

        if (changeFlags & IE_CT_Change_Risk_Probability)
            m_RiskProbability = pProp->GetRiskProbability();

        if (changeFlags & IE_CT_Change_Risk_Severity)
            m_RiskSeverity = pProp->GetRiskSeverity();

        if (changeFlags & IE_CT_Change_Risk_UE)
            m_RiskUE = pProp->GetRiskUE();

        if (changeFlags & IE_CT_Change_Risk_POA)
            m_RiskPOA = pProp->GetRiskPOA();

        if (changeFlags & IE_CT_Change_Risk_Action)
            m_RiskAction = pProp->GetRiskAction();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::IsEqual(PSS_RiskPropertiesBP* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::SetRiskName(LPCTSTR pValue)
{
    if (pValue)
        m_RiskName = pValue;
    else
    {
        TRACE0("PSS_RiskPropertiesBP - Invalid risk name!\n");
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::SetRiskDesc(LPCTSTR pValue)
{
    if (pValue)
        m_RiskDesc = pValue;
    else
    {
        TRACE0("PSS_RiskPropertiesBP - Invalid risk description!\n");
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::SetRiskType(LPCTSTR pValue)
{
    if (pValue)
        m_RiskType = pValue;
    else
    {
        TRACE0("PSS_RiskPropertiesBP - Invalid risk type!\n");
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Risk_Impact_ID:      value = m_RiskImpact;      break;
        case M_Risk_Probability_ID: value = m_RiskProbability; break;
        case M_Risk_Severity_ID:    value = m_RiskSeverity;    break;
        default:                    ASSERT(FALSE);             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_Risk_Name_ID:
        case M_Risk_Desc_ID:
        case M_Risk_Type_ID:
        case M_Risk_Impact_ID:
        case M_Risk_Probability_ID:
        case M_Risk_Severity_ID:
        case M_Risk_UE_ID:
        case M_Risk_POA_ID:
        case M_Risk_Action_ID:      ASSERT(FALSE); return FALSE;
        default:                    ASSERT(FALSE); return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Risk_Name_ID:
        case M_Risk_Desc_ID:
        case M_Risk_Type_ID:
        case M_Risk_Impact_ID:
        case M_Risk_Probability_ID:
        case M_Risk_Severity_ID:
        case M_Risk_UE_ID:
        case M_Risk_POA_ID:
        case M_Risk_Action_ID:      ASSERT(FALSE); return FALSE;
        default:                    ASSERT(FALSE); return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Risk_UE_ID:  value = m_RiskUE;  break;
        case M_Risk_POA_ID: value = m_RiskPOA; break;
        default:            ASSERT(FALSE);     return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::GetValue(const int propId, bool& value) const
{
    switch (propId)
    {
        case M_Risk_Action_ID: value = m_RiskAction; break;
        default:               ASSERT(FALSE);        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Risk_Name_ID: value = m_RiskName; break;
        case M_Risk_Desc_ID: value = m_RiskDesc; break;
        case M_Risk_Type_ID: value = m_RiskType; break;
        default:             ASSERT(FALSE);      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Risk_Impact_ID:      m_RiskImpact = value;      break;
        case M_Risk_Probability_ID: m_RiskProbability = value; break;
        case M_Risk_Severity_ID:    m_RiskSeverity = value;    break;
        default:                    ASSERT(FALSE);             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_Risk_Name_ID:
        case M_Risk_Desc_ID:
        case M_Risk_Type_ID:
        case M_Risk_Impact_ID:
        case M_Risk_Probability_ID:
        case M_Risk_Severity_ID:
        case M_Risk_UE_ID:
        case M_Risk_POA_ID:
        case M_Risk_Action_ID:      ASSERT(FALSE); return FALSE;
        default:                    ASSERT(FALSE); return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Risk_Name_ID:
        case M_Risk_Desc_ID:
        case M_Risk_Type_ID:
        case M_Risk_Impact_ID:
        case M_Risk_Probability_ID:
        case M_Risk_Severity_ID:
        case M_Risk_UE_ID:
        case M_Risk_POA_ID:
        case M_Risk_Action_ID:      ASSERT(FALSE); return FALSE;
        default:                    ASSERT(FALSE); return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Risk_UE_ID:  m_RiskUE  = value; break;
        case M_Risk_POA_ID: m_RiskPOA = value; break;
        default:            ASSERT(FALSE);     return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::SetValue(const int propId, const bool value)
{
    switch (propId)
    {
        case M_Risk_Action_ID: m_RiskAction = value; break;
        default:               ASSERT(FALSE);        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskPropertiesBP::SetValue(const int propId, LPCTSTR pValue)
{
    switch (propId)
    {
        case M_Risk_Name_ID: m_RiskName = pValue; break;
        case M_Risk_Desc_ID: m_RiskDesc = pValue; break;
        case M_Risk_Type_ID: m_RiskType = pValue; break;
        default:             ASSERT(FALSE);       return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE("PSS_RiskPropertiesBP::Serialize - Start save\n");

        ar << m_RiskName;
        ar << m_RiskDesc;
        ar << m_RiskType;
        ar << m_RiskImpact;
        ar << m_RiskProbability;
        ar << m_RiskSeverity;
        ar << m_RiskUE;
        ar << m_RiskPOA;
        ar << (WORD)m_RiskAction;

        TRACE("PSS_RiskPropertiesBP::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_RiskPropertiesBP::Serialize - Start read\n");

        ar >> m_RiskName;
        ar >> m_RiskDesc;
        ar >> m_RiskType;
        ar >> m_RiskImpact;
        ar >> m_RiskProbability;
        ar >> m_RiskSeverity;
        ar >> m_RiskUE;
        ar >> m_RiskPOA;

        WORD wValue;
        ar >> wValue;
        m_RiskAction = ((wValue == 1) ? (true) : (false));

        TRACE("PSS_RiskPropertiesBP::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_RiskPropertiesBP::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_RiskPropertiesBP::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);

        dc << _T("Name = ") << m_RiskName << _T("\n");
        dc << _T("Desc = ") << m_RiskDesc << _T("\n");
        dc << _T("Type = ") << m_RiskType << _T("\n");
    }
#endif
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::SetRiskNameEx(const CString value)
{
    SetRiskName(value);
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::SetRiskDescEx(const CString value)
{
    SetRiskDesc(value);
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::SetRiskTypeEx(const CString value)
{
    SetRiskType(value);
}
//---------------------------------------------------------------------------
