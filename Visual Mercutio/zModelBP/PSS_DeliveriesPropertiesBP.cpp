/****************************************************************************
 * ==> PSS_DeliveriesPropertiesBP ------------------------------------------*
 ****************************************************************************
 * Description : Provides the deliveries properties for banking process     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DeliveriesPropertiesBP.h"

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
IMPLEMENT_SERIAL(PSS_DeliveriesPropertiesBP, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DeliveriesPropertiesBP
//---------------------------------------------------------------------------
PSS_DeliveriesPropertiesBP::PSS_DeliveriesPropertiesBP() :
    CObject(),
    m_DeliveryQuantity(0.0f),
    m_DeliveryPercentage(0.0f)
{}
//---------------------------------------------------------------------------
PSS_DeliveriesPropertiesBP::PSS_DeliveriesPropertiesBP(const PSS_DeliveriesPropertiesBP& other)
{
    m_DeliveryName         = other.GetDeliveryName();
    m_DeliveryDeliverables = other.GetDeliveryDeliverables();
    m_DeliveryQuantity     = other.GetDeliveryQuantity();
    m_DeliveryPercentage   = other.GetDeliveryPercentage();
    m_DeliveryMain         = other.GetDeliveryMain();
}
//---------------------------------------------------------------------------
PSS_DeliveriesPropertiesBP::~PSS_DeliveriesPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_DeliveriesPropertiesBP& PSS_DeliveriesPropertiesBP::operator = (const PSS_DeliveriesPropertiesBP& other)
{
    SetDeliveryName(other.GetDeliveryName());
    SetDeliveryDeliverables(other.GetDeliveryDeliverables());
    SetDeliveryQuantity(other.GetDeliveryQuantity());
    SetDeliveryPercentage(other.GetDeliveryPercentage());
    SetDeliveryMain(other.GetDeliveryMain());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliveriesPropertiesBP::operator == (const PSS_DeliveriesPropertiesBP& other) const
{
    return (GetDeliveryName()         == other.GetDeliveryName()         &&
            GetDeliveryDeliverables() == other.GetDeliveryDeliverables() &&
            GetDeliveryQuantity()     == other.GetDeliveryQuantity()     &&
            GetDeliveryPercentage()   == other.GetDeliveryPercentage()   &&
            GetDeliveryMain()         == other.GetDeliveryMain());
}
//---------------------------------------------------------------------------
void PSS_DeliveriesPropertiesBP::Merge(PSS_DeliveriesPropertiesBP* pProp, DWORD changeFlags)
{
    if (pProp)
    {
        if (changeFlags & IE_CT_Change_Delivery_Name)
            m_DeliveryName = pProp->GetDeliveryName();

        if (changeFlags & IE_CT_Change_Delivery_Deliverables)
            m_DeliveryDeliverables = pProp->GetDeliveryDeliverables();

        if (changeFlags & IE_CT_Change_Delivery_Quantity)
            m_DeliveryQuantity = pProp->GetDeliveryQuantity();

        if (changeFlags & IE_CT_Change_Delivery_Percentage)
            m_DeliveryPercentage = pProp->GetDeliveryPercentage();

        if (changeFlags & IE_CT_Change_Delivery_Main)
            m_DeliveryMain = pProp->GetDeliveryMain();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_DeliveriesPropertiesBP::IsEqual(PSS_DeliveriesPropertiesBP* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_DeliveriesPropertiesBP::SetDeliveryName(LPCTSTR pValue)
{
    if (pValue)
        m_DeliveryName = pValue;
    else
    {
        TRACE0(_T("PSS_DeliveriesPropertiesBP - Invalid delivery name!\n"));
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
void PSS_DeliveriesPropertiesBP::SetDeliveryDeliverables(LPCTSTR pValue)
{
    if (pValue)
        m_DeliveryDeliverables = pValue;
    else
    {
        TRACE0(_T("PSS_DeliveriesPropertiesBP - Invalid delivery deliverables list!\n"));
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
bool PSS_DeliveriesPropertiesBP::IsDeliverableInDelivery(LPCTSTR pValue)
{
    if (!pValue)
        return false;

    // initialize the token with ; as separator
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
void PSS_DeliveriesPropertiesBP::SetDeliveryMain(LPCTSTR pValue)
{
    if (pValue)
        m_DeliveryMain = pValue;
    else
    {
        TRACE0(_T("PSS_DeliveriesPropertiesBP - Invalid delivery main name!\n"));
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_DeliveriesPropertiesBP::GetValue(const int propId, int& nValue) const
{
    switch (propId)
    {
        case M_Delivery_Name_ID:
        case M_Delivery_Deliverables_ID:
        case M_Delivery_Quantity_ID:
        case M_Delivery_Percentage_ID:
        case M_Delivery_Main_ID:         ASSERT(FALSE); return FALSE;
        default:                                        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliveriesPropertiesBP::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_Delivery_Name_ID:
        case M_Delivery_Deliverables_ID:
        case M_Delivery_Quantity_ID:
        case M_Delivery_Percentage_ID:
        case M_Delivery_Main_ID:         ASSERT(FALSE); return FALSE;
        default:                                        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliveriesPropertiesBP::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Delivery_Name_ID:
        case M_Delivery_Deliverables_ID:
        case M_Delivery_Quantity_ID:
        case M_Delivery_Percentage_ID:
        case M_Delivery_Main_ID:         ASSERT(FALSE); return FALSE;
        default:                                        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliveriesPropertiesBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Delivery_Name_ID:
        case M_Delivery_Deliverables_ID:
        case M_Delivery_Main_ID:         ASSERT(FALSE);                return FALSE;
        case M_Delivery_Quantity_ID:     value = m_DeliveryQuantity;   break;
        case M_Delivery_Percentage_ID:   value = m_DeliveryPercentage; break;
        default:                                                       return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliveriesPropertiesBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Delivery_Name_ID:         value = m_DeliveryName;         break;
        case M_Delivery_Deliverables_ID: value = m_DeliveryDeliverables; break;
        case M_Delivery_Main_ID:         value = m_DeliveryMain;         break;
        default:                         ASSERT(FALSE);                  return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliveriesPropertiesBP::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Delivery_Name_ID:
        case M_Delivery_Deliverables_ID:
        case M_Delivery_Quantity_ID:
        case M_Delivery_Percentage_ID:
        case M_Delivery_Main_ID:         ASSERT(FALSE); return FALSE;
        default:                                        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliveriesPropertiesBP::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_Delivery_Name_ID:
        case M_Delivery_Deliverables_ID:
        case M_Delivery_Quantity_ID:
        case M_Delivery_Percentage_ID:
        case M_Delivery_Main_ID:         ASSERT(FALSE); return FALSE;
        default:                                        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliveriesPropertiesBP::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Delivery_Name_ID:
        case M_Delivery_Deliverables_ID:
        case M_Delivery_Quantity_ID:
        case M_Delivery_Percentage_ID:
        case M_Delivery_Main_ID:         ASSERT(FALSE); return FALSE;
        default:                                        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliveriesPropertiesBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Delivery_Name_ID:
        case M_Delivery_Deliverables_ID:
        case M_Delivery_Main_ID:         ASSERT(FALSE);                return FALSE;
        case M_Delivery_Quantity_ID:     m_DeliveryQuantity = value;   break;
        case M_Delivery_Percentage_ID:   m_DeliveryPercentage = value; break;
        default:                                                       return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliveriesPropertiesBP::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Delivery_Name_ID:         m_DeliveryName         = pValue; break;
        case M_Delivery_Deliverables_ID: m_DeliveryDeliverables = pValue; break;
        case M_Delivery_Main_ID:         m_DeliveryMain         = pValue; break;
        default:                         ASSERT(FALSE);                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DeliveriesPropertiesBP::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE(_T("PSS_DeliveriesPropertiesBP::Serialize - Start save\n"));

        ar << m_DeliveryName;
        ar << m_DeliveryDeliverables;
        ar << m_DeliveryQuantity;
        ar << m_DeliveryPercentage;
        ar << m_DeliveryMain;

        TRACE(_T("PSS_DeliveriesPropertiesBP::Serialize - End save\n"));
    }
    else
    {
        TRACE(_T("PSS_DeliveriesPropertiesBP::Serialize - Start read\n"));

        ar >> m_DeliveryName;
        ar >> m_DeliveryDeliverables;
        ar >> m_DeliveryQuantity;
        ar >> m_DeliveryPercentage;
        ar >> m_DeliveryMain;

        TRACE(_T("PSS_DeliveriesPropertiesBP::Serialize - End read\n"));
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_DeliveriesPropertiesBP::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_DeliveriesPropertiesBP::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);

        dc << _T("Name = ")         << m_DeliveryName         << _T("\n");
        dc << _T("Deliverables = ") << m_DeliveryDeliverables << _T("\n");
        dc << _T("Main = ")         << m_DeliveryMain         << _T("\n");
    }
#endif
//---------------------------------------------------------------------------
void PSS_DeliveriesPropertiesBP::SetDeliveryNameEx(const CString value)
{
    SetDeliveryName(value);
}
//---------------------------------------------------------------------------
void PSS_DeliveriesPropertiesBP::SetDeliveryDeliverablesEx(const CString value)
{
    SetDeliveryDeliverables(value);
}
//---------------------------------------------------------------------------
void PSS_DeliveriesPropertiesBP::SetDeliveryMainEx(const CString value)
{
    SetDeliveryMain(value);
}
//---------------------------------------------------------------------------
