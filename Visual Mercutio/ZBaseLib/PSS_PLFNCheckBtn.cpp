/****************************************************************************
 * ==> PSS_PLFNCheckBtn ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan check button object              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNCheckBtn.h"

// processsoft
#include "ZDDoc.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNCheckBtn, PLFNTwoStates, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNCheckBtn
//---------------------------------------------------------------------------
PSS_PLFNCheckBtn::PSS_PLFNCheckBtn() :
    PLFNTwoStates()
{}
//---------------------------------------------------------------------------
PSS_PLFNCheckBtn::PSS_PLFNCheckBtn(const PSS_PLFNCheckBtn& other) :
    PLFNTwoStates()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNCheckBtn::~PSS_PLFNCheckBtn()
{}
//---------------------------------------------------------------------------
const PSS_PLFNCheckBtn& PSS_PLFNCheckBtn::operator = (const PSS_PLFNCheckBtn& other)
{
    PLFNTwoStates::operator = ((inherited&)other);
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNCheckBtn& PSS_PLFNCheckBtn::operator = (const PSS_PLFNCheckBtn* pOther)
{
    PLFNTwoStates::operator = ((inherited*)pOther);
    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNCheckBtn::Clone() const
{
    std::unique_ptr<PSS_PLFNCheckBtn> pObject(new PSS_PLFNCheckBtn(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNCheckBtn::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNCheckBtn*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNCheckBtn::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    CPen  pen;
    CPen* pOldPen = pDC->SelectObject(&GetGraphicPen(pen));

    if (!GetbTextIsCtrl())
    {
        CRect rectControl(m_ObjectRect);

        // check if the control is on the right
        if (GetbLeftText())
            rectControl.left = rectControl.right - GetuSize();

        switch (GetCheckType())
        {
            case E_CB_Rounded:
                pDC->Ellipse(rectControl.left, rectControl.top, rectControl.left + GetuSize(), rectControl.top + GetuSize());

                // show a point
                if (GetbCheckState())
                {
                    // draw the hand check
                    CPoint endPoint(rectControl.left + (GetuSize() / 2), rectControl.top + GetuSize() - (GetuSize() / 3));
                    pDC->MoveTo(rectControl.left, rectControl.top);
                    pDC->LineTo(endPoint);
                    pDC->MoveTo(rectControl.left, rectControl.top + 1);
                    pDC->LineTo(endPoint);

                    CRect rect(rectControl.left, rectControl.top, rectControl.left + GetuSize(), rectControl.top + GetuSize());
                    rect.top   -= (GetuSize() / 3);
                    rect.right += (GetuSize() / 6);
                    pDC->MoveTo(rect.right,     rect.top);
                    pDC->LineTo(endPoint.x - 1, endPoint.y + 1);
                    pDC->MoveTo(rect.right,     rect.top   + 1);
                    pDC->LineTo(endPoint.x - 1, endPoint.y + 1);
                }

                break;

            case E_CB_Squared:
                // draw the square
                pDC->MoveTo(rectControl.left,              rectControl.top);
                pDC->LineTo(rectControl.left,              rectControl.top + GetuSize());
                pDC->LineTo(rectControl.left + GetuSize(), rectControl.top + GetuSize());
                pDC->LineTo(rectControl.left + GetuSize(), rectControl.top);
                pDC->LineTo(rectControl.left,              rectControl.top);

                // show a cross
                if (GetbCheckState())
                {
                    pDC->MoveTo(rectControl.left + 1,              rectControl.top + 1);
                    pDC->LineTo(rectControl.left + GetuSize() - 1, rectControl.top + GetuSize() - 1);
                    pDC->MoveTo(rectControl.left + GetuSize() - 1, rectControl.top + 1);
                    pDC->LineTo(rectControl.left + 1,              rectControl.top + GetuSize() - 1);
                }

                break;
        }
    }

    // draw Text
    if (GetbShowText())
    {
        CFont* pOldFont = pDC->SelectObject(GetFont(pView));
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(GetColor(pView));
        pDC->SetTextAlign(TA_LEFT | TA_BASELINE);

        // if the text does not act as a control 
        if (!GetbTextIsCtrl() && !GetbLeftText())
            pDC->TextOut(m_ObjectRect.left + GetuSize() + GetOffsetText(), m_ObjectRect.top + GetuSize(), GetsText());
        else
        {
            pDC->TextOut(m_ObjectRect.left, m_ObjectRect.top + GetuSize(), GetsText());

            if (GetbCheckState() && GetbTextIsCtrl())
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
void PSS_PLFNCheckBtn::EditObject(CWnd* pParentWnd, CDC* pDC, ZDDocument* pDoc)
{
    SetbCheckState(!GetbCheckState());

    if (pParentWnd->IsWindowVisible())
    {
        CRect rect(m_ObjectRect);
        rect.InflateRect(GetuSize(), GetuSize());
        InvalidateObjectRect(pDC, pParentWnd, &rect);
    }
}
//---------------------------------------------------------------------------
void PSS_PLFNCheckBtn::Serialize(CArchive& ar)
{
    PLFNTwoStates::Serialize(ar);
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
