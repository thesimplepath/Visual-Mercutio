/****************************************************************************
 * ==> PSS_Border ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a border component                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Border.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_Border, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_Border
//---------------------------------------------------------------------------
PSS_Border::PSS_Border() :
    m_LeftType(E_LT_No),
    m_TopType(E_LT_No),
    m_RightType(E_LT_No),
    m_BottomType(E_LT_No),
    m_LeftColor(defCOLOR_BLACK),
    m_TopColor(defCOLOR_BLACK),
    m_RightColor(defCOLOR_BLACK),
    m_BottomColor(defCOLOR_BLACK),
    m_LeftWidth(1),
    m_TopWidth(1),
    m_RightWidth(1),
    m_BottomWidth(1),
    m_Shadow(FALSE)
{}
//---------------------------------------------------------------------------
PSS_Border::PSS_Border(const PSS_Border& other) :
    m_LeftType(E_LT_No),
    m_TopType(E_LT_No),
    m_RightType(E_LT_No),
    m_BottomType(E_LT_No),
    m_LeftColor(defCOLOR_BLACK),
    m_TopColor(defCOLOR_BLACK),
    m_RightColor(defCOLOR_BLACK),
    m_BottomColor(defCOLOR_BLACK),
    m_LeftWidth(1),
    m_TopWidth(1),
    m_RightWidth(1),
    m_BottomWidth(1),
    m_Shadow(FALSE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_Border::~PSS_Border()
{}
//---------------------------------------------------------------------------
const PSS_Border& PSS_Border::operator = (const PSS_Border& other)
{
    m_LeftType    = other.m_LeftType;
    m_TopType     = other.m_TopType;
    m_RightType   = other.m_RightType;
    m_BottomType  = other.m_BottomType;
    m_LeftColor   = other.m_LeftColor;
    m_TopColor    = other.m_TopColor;
    m_RightColor  = other.m_RightColor;
    m_BottomColor = other.m_BottomColor;
    m_LeftWidth   = other.m_LeftWidth;
    m_TopWidth    = other.m_TopWidth;
    m_RightWidth  = other.m_RightWidth;
    m_BottomWidth = other.m_BottomWidth;
    m_Shadow      = other.m_Shadow;
    return *this;
}
//---------------------------------------------------------------------------
PSS_Border* PSS_Border::Clone() const
{
    std::unique_ptr<PSS_Border> pObject(new PSS_Border(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_Border::DrawBorderRect(CDC* pDC, const CRect& rect)
{
    DrawBorderTopLine   (pDC, CPoint(rect.left,  rect.top),    CPoint(rect.right, rect.top));
    DrawBorderBottomLine(pDC, CPoint(rect.left,  rect.bottom), CPoint(rect.right, rect.bottom));
    DrawBorderLeftLine  (pDC, CPoint(rect.left,  rect.top),    CPoint(rect.left,  rect.bottom));
    DrawBorderRightLine (pDC, CPoint(rect.right, rect.top),    CPoint(rect.right, rect.bottom));
}
//---------------------------------------------------------------------------
void PSS_Border::DrawBorderTopLine(CDC* pDC, const CPoint& startPoint, const CPoint& endPoint)
{
    CPen  pen(PS_SOLID, GetTopWidth(), GetTopColor());
    CPen* pOldPen = pDC->SelectObject(&pen);
    DrawBorderHorizontalLine(pDC, startPoint, endPoint, GetTopType());
    pDC->SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
void PSS_Border::DrawBorderBottomLine(CDC* pDC, const CPoint& startPoint, const CPoint& endPoint)
{
    CPen  pen(PS_SOLID, GetBottomWidth(), GetBottomColor());
    CPen* pOldPen = pDC->SelectObject(&pen);
    DrawBorderHorizontalLine(pDC, startPoint, endPoint, GetBottomType());
    pDC->SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
void PSS_Border::DrawBorderLeftLine(CDC* pDC, const CPoint& startPoint, const CPoint& endPoint)
{
    CPen  pen(PS_SOLID, GetLeftWidth(), GetLeftColor());
    CPen* pOldPen = pDC->SelectObject(&pen);
    DrawBorderVerticalLine(pDC, startPoint, endPoint, GetLeftType());
    pDC->SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
void PSS_Border::DrawBorderRightLine(CDC* pDC, const CPoint& startPoint, const CPoint& endPoint)
{
    CPen  pen(PS_SOLID, GetRightWidth(), GetRightColor());
    CPen* pOldPen = pDC->SelectObject(&pen);
    DrawBorderVerticalLine(pDC, startPoint, endPoint, GetRightType());
    pDC->SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
void PSS_Border::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_LeftWidth;
        ar << m_TopWidth;
        ar << m_RightWidth;
        ar << m_BottomWidth;
        ar << WORD(m_LeftType);
        ar << WORD(m_RightType);
        ar << WORD(m_TopType);
        ar << WORD(m_BottomType);
        ar << WORD(m_Shadow);
        ar << m_TopColor;
        ar << m_BottomColor;
        ar << m_LeftColor;
        ar << m_RightColor;
    }
    else
    {
        ar >> m_LeftWidth;
        ar >> m_TopWidth;
        ar >> m_RightWidth;
        ar >> m_BottomWidth;

        WORD wValue;

        ar >> wValue;
        m_LeftType = ELineType(wValue);

        ar >> wValue;
        m_RightType = ELineType(wValue);

        ar >> wValue;
        m_TopType = ELineType(wValue);

        ar >> wValue;
        m_BottomType = ELineType(wValue);

        ar >> wValue;
        m_Shadow = ELineType(wValue);

        ar >> m_TopColor;
        ar >> m_BottomColor;
        ar >> m_LeftColor;
        ar >> m_RightColor;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_Border::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_Border::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_Border::DrawBorderHorizontalLine(CDC* pDC, const CPoint& startPoint, const CPoint& endPoint, ELineType type)
{
    switch (type)
    {
        case E_LT_Dotted:
            for (int i = startPoint.x; i < endPoint.x; i += 2)
            {
                pDC->MoveTo(i,     startPoint.y);
                pDC->LineTo(i + 1, startPoint.y);
            }

            break;

        case E_LT_Small:
            for (int i = startPoint.x; i < endPoint.x; i += 8)
            {
                pDC->MoveTo(i,     startPoint.y);
                pDC->LineTo(i + 4, startPoint.y);
            }

            break;

        case E_LT_Solid:
            pDC->MoveTo(startPoint.x, startPoint.y);
            pDC->LineTo(endPoint.x,   endPoint.y);
            break;

        case E_LT_Dash:
            for (int i = startPoint.x; i < endPoint.x; i += 4)
            {
                pDC->MoveTo(i,     startPoint.y);
                pDC->LineTo(i + 2, startPoint.y);
            }

            break;

        default: break;
    }
}
//---------------------------------------------------------------------------
void PSS_Border::DrawBorderVerticalLine(CDC* pDC, const CPoint& startPoint, const CPoint& endPoint, ELineType type)
{
    switch (type)
    {
        case E_LT_Dotted:
            for (int i = startPoint.y; i < endPoint.y; i += 2)
            {
                pDC->MoveTo(startPoint.x, i);
                pDC->LineTo(startPoint.x, i + 1);
            }

            break;

        case E_LT_Small:
            for (int i = startPoint.y; i < endPoint.y; i += 8)
            {
                pDC->MoveTo(startPoint.x, i);
                pDC->LineTo(startPoint.x, i + 4);
            }

            break;

        case E_LT_Solid:
            pDC->MoveTo(startPoint.x, startPoint.y);
            pDC->LineTo(endPoint.x,   endPoint.y);
            break;

        case E_LT_Dash:
            for (int i = startPoint.y; i < endPoint.y; i += 4)
            {
                pDC->MoveTo(startPoint.x, i);
                pDC->LineTo(startPoint.x, i + 2);
            }

            break;

        default: break;
    }
}
//---------------------------------------------------------------------------
