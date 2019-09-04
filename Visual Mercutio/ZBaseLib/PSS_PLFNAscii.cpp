/****************************************************************************
 * ==> PSS_PLFNAscii -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an ascii based financial plan object              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNAscii.h"

// processsoft
#include "ZDDoc.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNAscii, PlanFinObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNAscii
//---------------------------------------------------------------------------
PSS_PLFNAscii::PSS_PLFNAscii() :
    PlanFinObject(),
    m_StrikeStyle(IE_SS_NormalStrike),
    m_Justify(g_NoAlignement),
    m_IsStriked(FALSE),
    m_KeepHistory(FALSE)
{}
//---------------------------------------------------------------------------
PSS_PLFNAscii::PSS_PLFNAscii(const PSS_PLFNAscii& other) :
    PlanFinObject(),
    m_StrikeStyle(IE_SS_NormalStrike),
    m_Justify(g_NoAlignement),
    m_IsStriked(FALSE),
    m_KeepHistory(FALSE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNAscii::~PSS_PLFNAscii()
{}
//---------------------------------------------------------------------------
const PSS_PLFNAscii& PSS_PLFNAscii::operator = (const PSS_PLFNAscii& other)
{
    PlanFinObject::operator = ((inherited&)other);

    m_StrikeStyle = other.m_StrikeStyle;
    m_Justify     = other.m_Justify;
    m_IsStriked   = other.m_IsStriked;
    m_KeepHistory = other.m_KeepHistory;

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNAscii& PSS_PLFNAscii::operator = (const PSS_PLFNAscii* pOther)
{
    PlanFinObject::operator = ((inherited*)pOther);

    if (!pOther)
    {
        // reset to default values
        m_StrikeStyle = IE_SS_NormalStrike;
        m_Justify     = g_NoAlignement;
        m_IsStriked   = FALSE;
        m_KeepHistory = FALSE;
    }
    else
    {
        m_StrikeStyle = pOther->m_StrikeStyle;
        m_Justify     = pOther->m_Justify;
        m_IsStriked   = pOther->m_IsStriked;
        m_KeepHistory = pOther->m_KeepHistory;
    }

    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNAscii::Clone() const
{
    std::unique_ptr<PSS_PLFNAscii> pObject(new PSS_PLFNAscii(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
UINT PSS_PLFNAscii::GetJustify(ZDDocument* pDoc) const
{
    if (m_Justify != g_NoAlignement)
        return m_Justify;

    if (pDoc)
    {
        ZAStyle* pStyle = pDoc->GetStyleManager().GetStyle(GethStyle());

        if (pStyle)
            return pStyle->GetJustify();
    }

    return 0;
}
//---------------------------------------------------------------------------
void PSS_PLFNAscii::Serialize(CArchive& ar)
{
    PlanFinObject::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << (WORD)m_Justify;
        ar << (WORD)m_IsStriked;
        ar << (WORD)m_StrikeStyle;
        ar << (WORD)m_KeepHistory;
    }
    else
    {
        // read the elements
        const long version = ((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion();
        WORD       temp;

        if (version >= 0)
        {
            ar >> temp;
            m_Justify = temp;
        }

        if (version >= 5)
        {
            ar >> temp;
            m_IsStriked = BOOL(temp);

            ar >> temp;
            m_StrikeStyle = IEStrikeStyles(temp);
        }

        if (version >= 7)
        {
            ar >> temp;
            m_KeepHistory = BOOL(temp);
        }
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNAscii::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNAscii::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------