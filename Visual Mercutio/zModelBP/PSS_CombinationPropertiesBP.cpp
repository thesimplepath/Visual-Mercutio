/****************************************************************************
 * ==> PSS_CombinationPropertiesBP -----------------------------------------*
 ****************************************************************************
 * Description : Provides the combination properties for banking process    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CombinationPropertiesBP.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
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
IMPLEMENT_SERIAL(PSS_CombinationPropertiesBP, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_CombinationPropertiesBP
//---------------------------------------------------------------------------
PSS_CombinationPropertiesBP::PSS_CombinationPropertiesBP() :
    CObject(),
    m_CombinationActivationPerc(0.0f)
{}
//---------------------------------------------------------------------------
PSS_CombinationPropertiesBP::PSS_CombinationPropertiesBP(const PSS_CombinationPropertiesBP& other) :
    CObject()
{
    m_CombinationName           = other.GetCombinationName();
    m_CombinationDeliverables   = other.GetCombinationDeliverables();
    m_CombinationMaster         = other.GetCombinationMaster();
    m_CombinationActivationPerc = other.GetCombinationActivationPerc();
}
//---------------------------------------------------------------------------
PSS_CombinationPropertiesBP::~PSS_CombinationPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_CombinationPropertiesBP& PSS_CombinationPropertiesBP::operator = (const PSS_CombinationPropertiesBP& other)
{
    SetCombinationName(other.GetCombinationName());
    SetCombinationDeliverables(other.GetCombinationDeliverables());
    SetCombinationActivationPerc(other.GetCombinationActivationPerc());
    SetCombinationMaster(other.GetCombinationMaster());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_CombinationPropertiesBP::operator == (const PSS_CombinationPropertiesBP& other) const
{
    return (GetCombinationName()           == other.GetCombinationName()           &&
            GetCombinationDeliverables()   == other.GetCombinationDeliverables()   &&
            GetCombinationActivationPerc() == other.GetCombinationActivationPerc() &&
            GetCombinationMaster()         == other.GetCombinationMaster());
}
//---------------------------------------------------------------------------
void PSS_CombinationPropertiesBP::Merge(PSS_CombinationPropertiesBP* pProp, DWORD changeFlags)
{
    if (pProp)
    {
        if (changeFlags & IE_CT_Change_Combination_Name)
            m_CombinationName = pProp->GetCombinationName();

        if (changeFlags & IE_CT_Change_Combination_Deliverables)
            m_CombinationDeliverables = pProp->GetCombinationDeliverables();

        if (changeFlags & IE_CT_Change_Combination_Activation_Perc)
            m_CombinationActivationPerc = pProp->GetCombinationActivationPerc();

        if (changeFlags & IE_CT_Change_Combination_Master)
            m_CombinationMaster = pProp->GetCombinationMaster();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_CombinationPropertiesBP::IsEqual(PSS_CombinationPropertiesBP* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_CombinationPropertiesBP::SetCombinationName(LPCTSTR pValue)
{
    if (pValue)
        m_CombinationName = pValue;
    else
    {
        TRACE0("PSS_CombinationPropertiesBP - Invalid combination name!\n");
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
void PSS_CombinationPropertiesBP::SetCombinationDeliverables(LPCTSTR pValue)
{
    if (pValue)
        m_CombinationDeliverables = pValue;
    else
    {
        TRACE0("PSS_CombinationPropertiesBP - Invalid combination deliverable list!\n");
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
bool PSS_CombinationPropertiesBP::IsDeliverableInCombination(LPCTSTR pValue)
{
    if (!pValue)
        return false;

    // Initialize the token with ; as separator
    PSS_Tokenizer token;
    CString       str = token.GetFirstToken(pValue);

    // iterate through all tokens
    while (!str.IsEmpty())
    {
        // found the same deliverable?
        if (str == pValue)
            return true;

        // get the next token
        str = token.GetNextToken();
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_CombinationPropertiesBP::SetCombinationMaster(LPCTSTR pValue)
{
    if (pValue)
        m_CombinationMaster = pValue;
    else
    {
        TRACE0("PSS_CombinationPropertiesBP - Invalid Combination master name!\n");
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_CombinationPropertiesBP::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Combination_Name_ID:
        case M_Combination_Deliverables_ID:
        case M_Combination_Activation_Perc_ID:
        case M_Combination_Master_ID:          ASSERT(FALSE); return FALSE;
        default:                                              return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CombinationPropertiesBP::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_Combination_Name_ID:
        case M_Combination_Deliverables_ID:
        case M_Combination_Activation_Perc_ID:
        case M_Combination_Master_ID:          ASSERT(FALSE); return FALSE;
        default:                                              return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CombinationPropertiesBP::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Combination_Name_ID:
        case M_Combination_Deliverables_ID:
        case M_Combination_Activation_Perc_ID:
        case M_Combination_Master_ID:          ASSERT(FALSE); return FALSE;
        default:                                              return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CombinationPropertiesBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Combination_Name_ID:
        case M_Combination_Deliverables_ID:
        case M_Combination_Master_ID:          ASSERT(FALSE);                       return FALSE;
        case M_Combination_Activation_Perc_ID: value = m_CombinationActivationPerc; break;
        default:                                                                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CombinationPropertiesBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Combination_Name_ID:         value = m_CombinationName;         break;
        case M_Combination_Deliverables_ID: value = m_CombinationDeliverables; break;
        case M_Combination_Master_ID:       value = m_CombinationMaster;       break;
        default:                            ASSERT(FALSE);                     return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CombinationPropertiesBP::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Combination_Name_ID:
        case M_Combination_Deliverables_ID:
        case M_Combination_Activation_Perc_ID:
        case M_Combination_Master_ID:          ASSERT(FALSE); return FALSE;
        default:                                              return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CombinationPropertiesBP::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_Combination_Name_ID:
        case M_Combination_Deliverables_ID:
        case M_Combination_Activation_Perc_ID:
        case M_Combination_Master_ID:          ASSERT(FALSE); return FALSE;
        default:                                              return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CombinationPropertiesBP::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Combination_Name_ID:
        case M_Combination_Deliverables_ID:
        case M_Combination_Activation_Perc_ID:
        case M_Combination_Master_ID:          ASSERT(FALSE); return FALSE;
        default:                                              return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CombinationPropertiesBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Combination_Name_ID:
        case M_Combination_Deliverables_ID:
        case M_Combination_Master_ID:          ASSERT(FALSE);                       return FALSE;
        case M_Combination_Activation_Perc_ID: m_CombinationActivationPerc = value; break;
        default:                                                                    return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CombinationPropertiesBP::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Combination_Name_ID:         m_CombinationName         = pValue; break;
        case M_Combination_Deliverables_ID: m_CombinationDeliverables = pValue; break;
        case M_Combination_Master_ID:       m_CombinationMaster       = pValue; break;
        default:                            ASSERT(FALSE);                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CombinationPropertiesBP::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE("PSS_CombinationPropertiesBP::Serialize - Start Save\n");

        ar << m_CombinationName;
        ar << m_CombinationDeliverables;
        ar << m_CombinationActivationPerc;
        ar << m_CombinationMaster;

        TRACE("PSS_CombinationPropertiesBP::Serialize - End Save\n");
    }
    else
    {
        TRACE("PSS_CombinationPropertiesBP::Serialize - Start Read\n");

        ar >> m_CombinationName;
        ar >> m_CombinationDeliverables;
        ar >> m_CombinationActivationPerc;

        PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

        // check the version for new file format
        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 19)
            ar >> m_CombinationMaster;
        else
            m_CombinationMaster.Empty();

        TRACE("PSS_CombinationPropertiesBP::Serialize - End Read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CombinationPropertiesBP::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_CombinationPropertiesBP::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);

        dc << _T("Name = ")         << m_CombinationName         << _T("\n");
        dc << _T("Deliverables = ") << m_CombinationDeliverables << _T("\n");
        dc << _T("Master = ")       << m_CombinationMaster       << _T("\n");
    }
#endif
//---------------------------------------------------------------------------
void PSS_CombinationPropertiesBP::SetCombinationNameEx(const CString& value)
{
    SetCombinationName(value);
}
//---------------------------------------------------------------------------
void PSS_CombinationPropertiesBP::SetCombinationDeliverablesEx(const CString& value)
{
    SetCombinationDeliverables(value);
}
//---------------------------------------------------------------------------
void PSS_CombinationPropertiesBP::SetCombinationMasterEx(const CString& value)
{
    SetCombinationMaster(value);
}
//---------------------------------------------------------------------------
