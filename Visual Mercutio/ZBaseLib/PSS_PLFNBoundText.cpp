/****************************************************************************
 * ==> PSS_PLFNBoundText ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan bounding text object             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNBoundText.h"

// processsoft
#include "ZIView.h"
#include "ZDDoc.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNBoundText, PLFNString, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNBoundText
//---------------------------------------------------------------------------
PSS_PLFNBoundText::PSS_PLFNBoundText(BOOL isStatic) :
    PLFNString(),
    m_Hanging(0.0),
    m_InterLine(0.0),
    m_HangingLines(0)
{
    SetJustify(DT_LEFT | DT_BOTTOM | DT_WORDBREAK);
    SetIsStatic(isStatic);
}
//---------------------------------------------------------------------------
PSS_PLFNBoundText::PSS_PLFNBoundText(const PSS_PLFNBoundText& other) :
    PLFNString(),
    m_Hanging(0.0),
    m_InterLine(0.0),
    m_HangingLines(0)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNBoundText::~PSS_PLFNBoundText()
{}
//---------------------------------------------------------------------------
const PSS_PLFNBoundText& PSS_PLFNBoundText::operator = (const PSS_PLFNBoundText& other)
{
    PLFNString::operator = ((inherited&)other);

    m_Hanging      = other.m_Hanging;
    m_HangingLines = other.m_HangingLines;
    m_InterLine    = other.m_InterLine;

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNBoundText& PSS_PLFNBoundText::operator = (const PSS_PLFNBoundText* pOther)
{
    PLFNString::operator = ((inherited*)pOther);

    if (!pOther)
    {
    }
    else
    {
        m_Hanging      = pOther->m_Hanging;
        m_HangingLines = pOther->m_HangingLines;
        m_InterLine    = pOther->m_InterLine;
    }

    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNBoundText::Clone() const
{
    std::unique_ptr<PSS_PLFNBoundText> pObject(new PSS_PLFNBoundText(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNBoundText::CopyObject(PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNBoundText*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNBoundText::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    if (IsEmpty())
        DrawEmpty(pDC, pView);
    else
    {
        CFont* pOldFont = pDC->SelectObject(GetFont(pView));

        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(GetColor(pView));

        // before drawing the object, format it, but in this version it's not necessary for string
        pDC->SetTextAlign(0);

        if (GetHanging())
        {
            const CSize textSize = pDC->GetTextExtent(m_Str, m_Str.GetLength());
            const UINT  tabChar  = UINT(GetHanging() / (double(textSize.cx) / double(m_Str.GetLength())));

            pDC->DrawText("\t" + m_Str,
                          -1,
                          &m_rctObject,
                          GetJustify(pView->GetDocument()) & ~DT_SINGLELINE | DT_WORDBREAK | DT_EXPANDTABS | DT_TABSTOP | (tabChar << 8));
        }
        else
            pDC->DrawText(m_Str, -1, &m_rctObject, (GetJustify(pView->GetDocument()) & ~DT_SINGLELINE) | DT_WORDBREAK);

        pDC->SelectObject(pOldFont);
    }

    PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
void PSS_PLFNBoundText::DrawEmpty(CDC* pDC, ZIView* pView)
{
    // if printing and the empty style isn't required, just return
    if (pDC->IsPrinting() && !pView->GetDocument()->GetDocOptions().GetPrintEmptyStyleWhenEmpty())
        return;

    CFont* pOldFont = pDC->SelectObject(GetFont(pView));

    // get the text size to be able to draw correct number of lines
    const CSize textSize = pDC->GetTextExtent("A", 1);
    pDC->SelectObject(pOldFont);

    // draw the doted line without the dotted line style (bugged on printing)
    CPen        pen(PS_SOLID, 1, GetColor(pView));
    CPen*       pOldPen     = pDC->SelectObject(&pen);
    const int   line        = __max(1, m_rctObject.Height() / (textSize.cy + 2));
    const UINT  leftHanging = UINT(GetHanging());

    switch (pView->GetDocument()->GetDocOptions().GetEmptyStyle())
    {
        case E_LT_Dotted:
        {
            register int y = 0;

            // if hanging, the first line is drawn differently
            if (GetHanging())
            {
                // calculate the start point
                for (int i = m_rctObject.left + leftHanging; i < m_rctObject.right; i += 2)
                {
                    pDC->MoveTo(i,     (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                    pDC->LineTo(i + 1, (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                }

                y = 1;
            }

            for (; y < line; ++y)
                for (int i = m_rctObject.left; i < m_rctObject.right; i += 2)
                {
                    pDC->MoveTo(i,     (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                    pDC->LineTo(i + 1, (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                }

            break;
        }

        case E_LT_Small:
        {
            register int y = 0;

            // if hanging, the first line is drawn differently
            if (GetHanging())
            {
                // calculate the start point
                for (int i = m_rctObject.left + leftHanging; i < m_rctObject.right; i += 8)
                {
                    pDC->MoveTo(i,     (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                    pDC->LineTo(i + 4, (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                }

                y = 1;
            }

            for (; y < line; ++y)
                for (int i = m_rctObject.left; i < m_rctObject.right; i += 8)
                {
                    pDC->MoveTo(i,     (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                    pDC->LineTo(i + 4, (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                }

            break;
        }

        case E_LT_Solid:
        {
            register int y = 0;

            // if hanging, the first line is drawn differently
            if (GetHanging())
            {
                // calculate the start point
                pDC->MoveTo(m_rctObject.left + leftHanging, (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                pDC->LineTo(m_rctObject.right,              (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);

                y = 1;
            }

            for (; y < line; ++y)
            {
                pDC->MoveTo(m_rctObject.left,  (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                pDC->LineTo(m_rctObject.right, (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
            }

            break;
        }

        case E_LT_Dash:
        {
            register int y = 0;

            // if hanging, the first line is drawn differently
            if (GetHanging())
            {
                // calculate the start point
                for (int i = m_rctObject.left + leftHanging; i < m_rctObject.right; i += 4)
                {
                    pDC->MoveTo(i,     (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                    pDC->LineTo(i + 2, (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                }

                y = 1;
            }

            for (; y < line; ++y)
                for (int i = m_rctObject.left; i < m_rctObject.right; i += 4)
                {
                    pDC->MoveTo(i,     (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                    pDC->LineTo(i + 2, (m_rctObject.top + (y * (textSize.cy + 2))) + textSize.cy);
                }

            break;
        }

        default:
            break;
    }

    pDC->SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
void PSS_PLFNBoundText::Serialize(CArchive& ar)
{
    PLFNString::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << m_Hanging;
        ar << WORD(m_HangingLines);
        ar << m_InterLine;
    }
    else
    {
        // read the elements
        if (((ZDDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        {
            ar >> m_Hanging;

            WORD temp;
            ar >> temp;
            m_HangingLines = UINT(temp);

            ar >> m_InterLine;

        }
    }
}
//---------------------------------------------------------------------------