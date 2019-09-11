/****************************************************************************
 * ==> PSS_PLFNGraphic -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan graphical object                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNGraphic.h"

// processsoft
#include "ZDDoc.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNGraphic, PSS_PlanFinObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNGraphic
//---------------------------------------------------------------------------
PSS_PLFNGraphic::PSS_PLFNGraphic() :
    PSS_PlanFinObject(),
    m_GraphicColor(defCOLOR_BLACK),
    m_GraphicStyle(PS_SOLID),
    m_GraphicWidth(1),
    m_Shadow(FALSE)
{}
//---------------------------------------------------------------------------
PSS_PLFNGraphic::PSS_PLFNGraphic(const PSS_PLFNGraphic& other) :
    PSS_PlanFinObject(),
    m_GraphicColor(defCOLOR_BLACK),
    m_GraphicStyle(PS_SOLID),
    m_GraphicWidth(1),
    m_Shadow(FALSE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNGraphic::~PSS_PLFNGraphic()
{}
//---------------------------------------------------------------------------
const PSS_PLFNGraphic& PSS_PLFNGraphic::operator = (const PSS_PLFNGraphic& other)
{
    PSS_PlanFinObject::operator = ((inherited&)other);
    m_GraphicColor = other.m_GraphicColor;
    m_GraphicStyle = other.m_GraphicStyle;
    m_GraphicWidth = other.m_GraphicWidth;
    m_Shadow       = other.m_Shadow;
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNGraphic& PSS_PLFNGraphic::operator = (const PSS_PLFNGraphic* pOther)
{
    PSS_PlanFinObject::operator = ((inherited*)pOther);

    if (!pOther)
    {
        m_GraphicColor = defCOLOR_BLACK;
        m_GraphicStyle = PS_SOLID;
        m_GraphicWidth = 1;
        m_Shadow       = FALSE;
    }
    else
    {
        m_GraphicColor = pOther->m_GraphicColor;
        m_GraphicStyle = pOther->m_GraphicStyle;
        m_GraphicWidth = pOther->m_GraphicWidth;
        m_Shadow       = pOther->m_Shadow;
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNGraphic::Clone() const
{
    std::unique_ptr<PSS_PLFNGraphic> pObject(new PSS_PLFNGraphic(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNGraphic::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNGraphic*>(pSrc));
}
//---------------------------------------------------------------------------
CBrush& PSS_PLFNGraphic::GetGraphicBrush(CBrush& brush) const
{
    if (brush.GetSafeHandle())
        brush.Detach();

    brush.CreateSolidBrush(m_GraphicColor);

    return brush;
}
//---------------------------------------------------------------------------
CPen& PSS_PLFNGraphic::GetGraphicPen(CPen& pen) const
{
    if (pen.GetSafeHandle())
        pen.Detach();

    pen.CreatePen(m_GraphicStyle, m_GraphicWidth, m_GraphicColor);

    return pen;
}
//---------------------------------------------------------------------------
void PSS_PLFNGraphic::Serialize(CArchive& ar)
{
    PSS_PlanFinObject::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << m_GraphicColor;
        ar << WORD(m_GraphicWidth);
        ar << WORD(m_Shadow);
        ar << WORD(m_GraphicStyle);
    }
    else
    {
        // read the elements
        ar >> m_GraphicColor;

        WORD value;
        ar >> value;
        m_GraphicWidth = value;

        ar >> value;
        m_Shadow = value;

        ar >> value;
        m_GraphicStyle = value;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNGraphic::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNGraphic::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
