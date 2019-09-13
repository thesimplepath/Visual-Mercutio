/****************************************************************************
 * ==> PSS_Style -----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a style                                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Style.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_Style, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_Style
//---------------------------------------------------------------------------
PSS_Style::PSS_Style() :
    CObject(),
    m_hStyle(g_NoStyleDefined),
    m_hFont(0),
    m_pBorder(NULL),
    m_BackColor(-1),
    m_Justify(DT_LEFT | DT_BOTTOM | DT_SINGLELINE)
{}
//---------------------------------------------------------------------------
PSS_Style::PSS_Style(const PSS_Style& other) :
    CObject(),
    m_hStyle(g_NoStyleDefined),
    m_hFont(0),
    m_pBorder(NULL),
    m_BackColor(-1),
    m_Justify(DT_LEFT | DT_BOTTOM | DT_SINGLELINE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_Style::~PSS_Style()
{
    if (m_pBorder)
        delete m_pBorder;
}
//---------------------------------------------------------------------------
const PSS_Style& PSS_Style::operator = (const PSS_Style& other)
{
    m_hStyle    = other.m_hStyle;
    m_hFont     = other.m_hFont;
    m_BackColor = other.m_BackColor;
    m_StyleName = other.m_StyleName;
    m_Justify   = other.m_Justify;

    if (other.m_pBorder)
        m_pBorder = other.m_pBorder->Clone();

    return *this;
}
//---------------------------------------------------------------------------
PSS_Style* PSS_Style::Clone() const
{
    std::unique_ptr<PSS_Style> pObject(new PSS_Style(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_Style::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_hFont;
        ar << m_BackColor;
        ar << m_pBorder;
        ar << LONG(m_hStyle);
        ar << m_StyleName;
        ar << DWORD(m_Justify);
    }
    else
    {
        ar >> m_hFont;
        ar >> m_BackColor;
        ar >> m_pBorder;

        LONG lValue;
        ar >> lValue;
        m_hStyle = (Handle)lValue;

        ar >> m_StyleName;

        DWORD dwValue;
        ar >> dwValue;
        m_Justify = UINT(dwValue);
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_Style::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_Style::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
