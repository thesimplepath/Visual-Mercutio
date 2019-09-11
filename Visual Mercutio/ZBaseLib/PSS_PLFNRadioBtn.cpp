/****************************************************************************
 * ==> PSS_PLFNRadioBtn ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan radio button object              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNRadioBtn.h"

// processsoft
#include "ZDDoc.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNRadioBtn, PLFNTwoStates, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNRadioBtn
//---------------------------------------------------------------------------
PSS_PLFNRadioBtn::PSS_PLFNRadioBtn() :
    PLFNTwoStates()
{}
//---------------------------------------------------------------------------
PSS_PLFNRadioBtn::PSS_PLFNRadioBtn(const PSS_PLFNRadioBtn& other) :
    PLFNTwoStates()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNRadioBtn::~PSS_PLFNRadioBtn()
{}
//---------------------------------------------------------------------------
const PSS_PLFNRadioBtn& PSS_PLFNRadioBtn::operator = (const PSS_PLFNRadioBtn& other)
{
    PLFNTwoStates::operator = ((inherited&)other);
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNRadioBtn& PSS_PLFNRadioBtn::operator = (const PSS_PLFNRadioBtn* pOther)
{
    PLFNTwoStates::operator = ((inherited*)pOther);
    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNRadioBtn::Clone() const
{
    std::unique_ptr<PSS_PLFNRadioBtn> pObject(new PSS_PLFNRadioBtn(*this));
    return pObject.release();
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

    if (!GetbTextIsCtrl())
    {
        CRect rectControl(m_ObjectRect);

        // check if the control is on the right
        if (GetbLeftText())
            rectControl.left = rectControl.right - GetuSize();

        switch (GetCheckType())
        {
            case E_CB_Rounded:
            {
                pDC->Ellipse(rectControl.left, rectControl.top, rectControl.left + GetuSize(), rectControl.top + GetuSize());

                // draw the round
                if (GetbCheckState())
                {
                    CBrush    brush(defCOLOR_GRAY);
                    CBrush*   pOldBrush = pDC->SelectObject(&brush);
                    CRect     pointRect(rectControl.left, rectControl.top, rectControl.left + GetuSize(), rectControl.top + GetuSize());
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
                pDC->MoveTo(rectControl.left,              rectControl.top);
                pDC->LineTo(rectControl.left,              rectControl.top + GetuSize());
                pDC->LineTo(rectControl.left + GetuSize(), rectControl.top + GetuSize());
                pDC->LineTo(rectControl.left + GetuSize(), rectControl.top);
                pDC->LineTo(rectControl.left,              rectControl.top);

                // draw the cross
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
    }

    // draw the text
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
void PSS_PLFNRadioBtn::EditObject(CWnd* pParentWnd, CDC* pDC, ZDDocument* pDoc)
{
    // get the group number. If greather than zero, iterate through all elments and reset all values
    // belonging to the same group
    if (GetGroupNumber() > 0)
    {
        PSS_PlanFinObject* pObj;

        // search wich element is selected
        if ((pObj = ((ZDDocument*)pDoc)->GetHead()) != NULL)
            do
            {
                // is in the same group?
                if (pObj->GetGroupNumber() == GetGroupNumber())
                {
                    PSS_PLFNRadioBtn* pRadioBtn = dynamic_cast<PSS_PLFNRadioBtn*>(pObj);

                    if (pRadioBtn)
                    {
                        pRadioBtn->SetbCheckState(FALSE);

                        if (pParentWnd->IsWindowVisible())
                            pObj->InvalidateObjectRect(pDC, pParentWnd);
                    }
                }
            }
            while ((pObj = ((ZDDocument*)pDoc)->GetNext()) != NULL);
    }

    SetbCheckState(!GetbCheckState());

    if (pParentWnd->IsWindowVisible())
        InvalidateObjectRect(pDC, pParentWnd);
}
//---------------------------------------------------------------------------
void PSS_PLFNRadioBtn::Serialize(CArchive& ar)
{
    PLFNTwoStates::Serialize(ar);
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
