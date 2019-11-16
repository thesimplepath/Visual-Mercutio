/****************************************************************************
 * ==> PSS_PLFNCheckBtn ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan check button object              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNCheckBtn.h"

// processsoft
#include "PSS_Document.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNCheckBtn, PSS_PLFNTwoStates, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNCheckBtn
//---------------------------------------------------------------------------
PSS_PLFNCheckBtn::PSS_PLFNCheckBtn() :
    PSS_PLFNTwoStates()
{}
//---------------------------------------------------------------------------
PSS_PLFNCheckBtn::PSS_PLFNCheckBtn(const PSS_PLFNCheckBtn& other) :
    PSS_PLFNTwoStates()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNCheckBtn::~PSS_PLFNCheckBtn()
{}
//---------------------------------------------------------------------------
const PSS_PLFNCheckBtn& PSS_PLFNCheckBtn::operator = (const PSS_PLFNCheckBtn& other)
{
    PSS_PLFNTwoStates::operator = ((inherited&)other);
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNCheckBtn& PSS_PLFNCheckBtn::operator = (const PSS_PLFNCheckBtn* pOther)
{
    PSS_PLFNTwoStates::operator = ((inherited*)pOther);
    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNCheckBtn::Clone() const
{
    return new PSS_PLFNCheckBtn(*this);
}
//---------------------------------------------------------------------------
void PSS_PLFNCheckBtn::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNCheckBtn*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNCheckBtn::DrawObject(CDC* pDC, PSS_View* pView)
{
    DrawFillObject(pDC, pView);

    CPen  pen;
    CPen* pOldPen = pDC->SelectObject(&GetGraphicPen(pen));

    if (!GetTextIsCtrl())
    {
        CRect rectControl(m_ObjectRect);

        // check if the control is on the right
        if (GetLeftText())
            rectControl.left = rectControl.right - GetSize();

        switch (GetCheckType())
        {
            case E_CB_Rounded:
                pDC->Ellipse(rectControl.left, rectControl.top, rectControl.left + GetSize(), rectControl.top + GetSize());

                // show a point
                if (GetCheckState())
                {
                    // draw the hand check
                    CPoint endPoint(rectControl.left + (GetSize() / 2), rectControl.top + GetSize() - (GetSize() / 3));
                    pDC->MoveTo(rectControl.left, rectControl.top);
                    pDC->LineTo(endPoint);
                    pDC->MoveTo(rectControl.left, rectControl.top + 1);
                    pDC->LineTo(endPoint);

                    CRect rect(rectControl.left, rectControl.top, rectControl.left + GetSize(), rectControl.top + GetSize());
                    rect.top   -= (GetSize() / 3);
                    rect.right += (GetSize() / 6);
                    pDC->MoveTo(rect.right,     rect.top);
                    pDC->LineTo(endPoint.x - 1, endPoint.y + 1);
                    pDC->MoveTo(rect.right,     rect.top   + 1);
                    pDC->LineTo(endPoint.x - 1, endPoint.y + 1);
                }

                break;

            case E_CB_Squared:
                // draw the square
                pDC->MoveTo(rectControl.left,             rectControl.top);
                pDC->LineTo(rectControl.left,             rectControl.top + GetSize());
                pDC->LineTo(rectControl.left + GetSize(), rectControl.top + GetSize());
                pDC->LineTo(rectControl.left + GetSize(), rectControl.top);
                pDC->LineTo(rectControl.left,             rectControl.top);

                // show a cross
                if (GetCheckState())
                {
                    pDC->MoveTo(rectControl.left + 1,             rectControl.top + 1);
                    pDC->LineTo(rectControl.left + GetSize() - 1, rectControl.top + GetSize() - 1);
                    pDC->MoveTo(rectControl.left + GetSize() - 1, rectControl.top + 1);
                    pDC->LineTo(rectControl.left + 1,             rectControl.top + GetSize() - 1);
                }

                break;
        }
    }

    // draw Text
    if (GetShowText())
    {
        CFont* pOldFont = pDC->SelectObject(GetFont(pView));
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(GetColor(pView));
        pDC->SetTextAlign(TA_LEFT | TA_BASELINE);

        // if the text does not act as a control 
        if (!GetTextIsCtrl() && !GetLeftText())
            pDC->TextOut(m_ObjectRect.left + GetSize() + GetOffsetText(), m_ObjectRect.top + GetSize(), GetText());
        else
        {
            pDC->TextOut(m_ObjectRect.left, m_ObjectRect.top + GetSize(), GetText());

            if (GetCheckState() && GetTextIsCtrl())
            {
                pDC->MoveTo(m_ObjectRect.left + 1, m_ObjectRect.top);
                pDC->LineTo(m_ObjectRect.right,    m_ObjectRect.bottom - 1);
                pDC->MoveTo(m_ObjectRect.right,    m_ObjectRect.top);
                pDC->LineTo(m_ObjectRect.left + 1, m_ObjectRect.bottom - 1);
            }
        }

        pDC->SelectObject(pOldFont);
    }

    pDC->SelectObject(pOldPen);

    PSS_PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
void PSS_PLFNCheckBtn::EditObject(CWnd* pParentWnd, CDC* pDC, PSS_Document* pDoc)
{
    SetCheckState(!GetCheckState());

    if (pParentWnd->IsWindowVisible())
    {
        CRect rect(m_ObjectRect);
        rect.InflateRect(GetSize(), GetSize());
        InvalidateObjectRect(pDC, pParentWnd, &rect);
    }
}
//---------------------------------------------------------------------------
void PSS_PLFNCheckBtn::Serialize(CArchive& ar)
{
    PSS_PLFNTwoStates::Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNCheckBtn::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNCheckBtn::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
