/****************************************************************************
 * ==> PSS_PLFNRadioBtn ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan radio button object              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNRadioBtn.h"

// processsoft
#include "PSS_Document.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNRadioBtn, PSS_PLFNTwoStates, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNRadioBtn
//---------------------------------------------------------------------------
PSS_PLFNRadioBtn::PSS_PLFNRadioBtn() :
    PSS_PLFNTwoStates()
{}
//---------------------------------------------------------------------------
PSS_PLFNRadioBtn::PSS_PLFNRadioBtn(const PSS_PLFNRadioBtn& other) :
    PSS_PLFNTwoStates()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNRadioBtn::~PSS_PLFNRadioBtn()
{}
//---------------------------------------------------------------------------
const PSS_PLFNRadioBtn& PSS_PLFNRadioBtn::operator = (const PSS_PLFNRadioBtn& other)
{
    PSS_PLFNTwoStates::operator = ((inherited&)other);
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNRadioBtn& PSS_PLFNRadioBtn::operator = (const PSS_PLFNRadioBtn* pOther)
{
    PSS_PLFNTwoStates::operator = ((inherited*)pOther);
    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNRadioBtn::Clone() const
{
    return new PSS_PLFNRadioBtn(*this);
}
//---------------------------------------------------------------------------
void PSS_PLFNRadioBtn::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNRadioBtn*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNRadioBtn::DrawObject(CDC* pDC, ZIView* pView)
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
            {
                pDC->Ellipse(rectControl.left, rectControl.top, rectControl.left + GetSize(), rectControl.top + GetSize());

                // draw the round
                if (GetCheckState())
                {
                    CBrush    brush(defCOLOR_GRAY);
                    CBrush*   pOldBrush = pDC->SelectObject(&brush);
                    CRect     pointRect(rectControl.left, rectControl.top, rectControl.left + GetSize(), rectControl.top + GetSize());
                    const int size = pointRect.Width();

                    pointRect.InflateRect(-size / 4, -size / 4);

                    pDC->Ellipse(&pointRect);
                    pDC->SelectObject(pOldBrush);
                }

                break;
            }

            case E_CB_Squared:
            {
                // draw the square
                pDC->MoveTo(rectControl.left,             rectControl.top);
                pDC->LineTo(rectControl.left,             rectControl.top + GetSize());
                pDC->LineTo(rectControl.left + GetSize(), rectControl.top + GetSize());
                pDC->LineTo(rectControl.left + GetSize(), rectControl.top);
                pDC->LineTo(rectControl.left,             rectControl.top);

                // draw the cross
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
    }

    // draw the text
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
                pDC->MoveTo(m_ObjectRect.left + 1, m_ObjectRect.top + (m_ObjectRect.Height() / 2));
                pDC->LineTo(m_ObjectRect.right,    m_ObjectRect.top + (m_ObjectRect.Height() / 2));
            }
        }

        pDC->SelectObject(pOldFont);
    }

    pDC->SelectObject(pOldPen);

    PSS_PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
void PSS_PLFNRadioBtn::EditObject(CWnd* pParentWnd, CDC* pDC, PSS_Document* pDoc)
{
    // get the group number. If greather than zero, iterate through all elments and reset all values
    // belonging to the same group
    if (GetGroupNumber() > 0)
    {
        PSS_PlanFinObject* pObj;

        // search wich element is selected
        if ((pObj = ((PSS_Document*)pDoc)->GetHead()) != NULL)
            do
            {
                // is in the same group?
                if (pObj->GetGroupNumber() == GetGroupNumber())
                {
                    PSS_PLFNRadioBtn* pRadioBtn = dynamic_cast<PSS_PLFNRadioBtn*>(pObj);

                    if (pRadioBtn)
                    {
                        pRadioBtn->SetCheckState(FALSE);

                        if (pParentWnd->IsWindowVisible())
                            pObj->InvalidateObjectRect(pDC, pParentWnd);
                    }
                }
            }
            while ((pObj = ((PSS_Document*)pDoc)->GetNext()) != NULL);
    }

    SetCheckState(!GetCheckState());

    if (pParentWnd->IsWindowVisible())
        InvalidateObjectRect(pDC, pParentWnd);
}
//---------------------------------------------------------------------------
void PSS_PLFNRadioBtn::Serialize(CArchive& ar)
{
    PSS_PLFNTwoStates::Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNRadioBtn::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNRadioBtn::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
