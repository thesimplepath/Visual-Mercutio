/****************************************************************************
 * ==> PSS_PLFNTwoStates ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a two state for financial plan radio and check    *
 *               button object                                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PLFNTwoStates.h"

// processsoft
#include "PSS_Document.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNTwoStates, PSS_PLFNGraphic, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNTwoStates
//---------------------------------------------------------------------------
PSS_PLFNTwoStates::PSS_PLFNTwoStates() :
    PSS_PLFNGraphic(),
    m_CheckType(ECheckButtonType::E_CB_Rounded),
    m_OffsetText(10),
    m_Size(10),
    m_CheckState(FALSE),
    m_ShowText(TRUE),
    m_TextIsCtrl(FALSE),
    m_LeftText(FALSE)
{}
//---------------------------------------------------------------------------
PSS_PLFNTwoStates::PSS_PLFNTwoStates(const PSS_PLFNTwoStates& other) :
    PSS_PLFNGraphic(),
    m_CheckType(ECheckButtonType::E_CB_Rounded),
    m_OffsetText(10),
    m_Size(10),
    m_CheckState(FALSE),
    m_ShowText(TRUE),
    m_TextIsCtrl(FALSE),
    m_LeftText(FALSE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNTwoStates::~PSS_PLFNTwoStates()
{}
//---------------------------------------------------------------------------
const PSS_PLFNTwoStates& PSS_PLFNTwoStates::operator = (const PSS_PLFNTwoStates& other)
{
    PSS_PLFNGraphic::operator = ((inherited&)other);
    m_CheckType   = other.m_CheckType;
    m_Text        = other.m_Text;
    m_OffsetText  = other.m_OffsetText;
    m_Size        = other.m_Size;
    m_CheckState  = other.m_CheckState;
    m_ShowText    = other.m_ShowText;
    m_TextIsCtrl  = other.m_TextIsCtrl;
    m_LeftText    = other.m_LeftText;
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNTwoStates& PSS_PLFNTwoStates::operator = (const PSS_PLFNTwoStates* pOther)
{
    PSS_PLFNGraphic::operator = ((inherited*)pOther);

    if (!pOther)
    {
        m_CheckType  = ECheckButtonType::E_CB_Rounded;
        m_OffsetText = 10;
        m_Size       = 10;
        m_CheckState = FALSE;
        m_ShowText   = TRUE;
        m_TextIsCtrl = FALSE;
        m_LeftText   = FALSE;

        m_Text.Empty();
    }
    else
    {
        m_CheckType  = pOther->m_CheckType;
        m_Text       = pOther->m_Text;
        m_OffsetText = pOther->m_OffsetText;
        m_Size       = pOther->m_Size;
        m_CheckState = pOther->m_CheckState;
        m_ShowText   = pOther->m_ShowText;
        m_TextIsCtrl = pOther->m_TextIsCtrl;
        m_LeftText   = pOther->m_LeftText;
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNTwoStates::Clone() const
{
    return new PSS_PLFNTwoStates(*this);
}
//---------------------------------------------------------------------------
void PSS_PLFNTwoStates::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNTwoStates*>(pSrc));
}
//---------------------------------------------------------------------------
CString PSS_PLFNTwoStates::GetUnformattedObject()
{
    return (m_CheckState ? "1" : "0");
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNTwoStates::ConvertFormattedObject(const CString& value, BOOL locateFormat, BOOL emptyWhenZero)
{
    if (value.IsEmpty())
        return FALSE;

    // save the old value to make comparison
    const BOOL oldValue = m_CheckState;
    m_CheckState        = (value[0] == '0' ? FALSE : TRUE);

    // has changed?
    return (oldValue != m_CheckState);
}
//---------------------------------------------------------------------------
void PSS_PLFNTwoStates::Serialize(CArchive& ar)
{
    PSS_PLFNGraphic::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << DWORD(m_CheckType);
        ar << WORD(m_Size);

        PSS_BaseDocument* pDoc = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

        // serialize the status if not a template or a default value is required
        if (pDoc && pDoc->GetDocumentStamp().GetFileType() == PSS_Stamp::IEFileTypeDefinition::IE_FD_TemplateType && !GetDefaultValue())
        {
            const BOOL checkState = FALSE;
            ar << WORD(checkState);
        }
        else
            ar << WORD(m_CheckState);

        ar << WORD(m_ShowText);
        ar << WORD(m_TextIsCtrl);
        ar << m_Text;
        ar << m_OffsetText;
        ar << WORD(m_LeftText);
    }
    else
    {
        // read the elements
        DWORD dwValue;
        ar >> dwValue;
        m_CheckType = ECheckButtonType(dwValue);

        WORD wValue;
        ar >> wValue;
        m_Size = wValue;

        ar >> wValue;
        m_CheckState = wValue;

        PSS_Document* pDoc = dynamic_cast<PSS_Document*>(ar.m_pDocument);

        if (pDoc && pDoc->GetDocumentStamp().GetInternalVersion() >= 5)
        {
            ar >> wValue;
            m_ShowText = wValue;

            ar >> wValue;
            m_TextIsCtrl = wValue;

            ar >> m_Text;
            ar >> m_OffsetText;

            ar >> wValue;
            m_LeftText = BOOL(wValue);
        }
        else
        {
            m_ShowText   = FALSE;
            m_TextIsCtrl = FALSE;
            m_LeftText   = FALSE;
        }
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNTwoStates::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNTwoStates::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
