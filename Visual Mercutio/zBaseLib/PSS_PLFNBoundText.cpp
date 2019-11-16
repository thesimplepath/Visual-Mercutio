/****************************************************************************
 * ==> PSS_PLFNBoundText ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan bounding text object             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNBoundText.h"

// processsoft
#include "PSS_Document.h"
#include "PSS_View.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNBoundText, PSS_PLFNString, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNBoundText
//---------------------------------------------------------------------------
PSS_PLFNBoundText::PSS_PLFNBoundText(BOOL isStatic) :
    PSS_PLFNString(),
    m_Hanging(0.0),
    m_InterLine(0.0),
    m_HangingLines(0)
{
    SetJustify(DT_LEFT | DT_BOTTOM | DT_WORDBREAK);
    SetIsStatic(isStatic);
}
//---------------------------------------------------------------------------
PSS_PLFNBoundText::PSS_PLFNBoundText(const PSS_PLFNBoundText& other) :
    PSS_PLFNString(),
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
    PSS_PLFNString::operator = ((inherited&)other);

    m_Hanging      = other.m_Hanging;
    m_HangingLines = other.m_HangingLines;
    m_InterLine    = other.m_InterLine;

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNBoundText& PSS_PLFNBoundText::operator = (const PSS_PLFNBoundText* pOther)
{
    PSS_PLFNString::operator = ((inherited*)pOther);

    if (!pOther)
    {
        m_Hanging      = 0.0;
        m_InterLine    = 0.0;
        m_HangingLines = 0;
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
PSS_PlanFinObject* PSS_PLFNBoundText::Clone() const
{
    return new PSS_PLFNBoundText(*this);
}
//---------------------------------------------------------------------------
void PSS_PLFNBoundText::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNBoundText*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNBoundText::DrawObject(CDC* pDC, PSS_View* pView)
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
                          &m_ObjectRect,
                          GetJustify(pView->GetDocument()) & ~DT_SINGLELINE | DT_WORDBREAK | DT_EXPANDTABS | DT_TABSTOP | (tabChar << 8));
        }
        else
            pDC->DrawText(m_Str, -1, &m_ObjectRect, (GetJustify(pView->GetDocument()) & ~DT_SINGLELINE) | DT_WORDBREAK);

        pDC->SelectObject(pOldFont);
    }

    PSS_PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
void PSS_PLFNBoundText::DrawEmpty(CDC* pDC, PSS_View* pView)
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
    const int   line        = __max(1, m_ObjectRect.Height() / (textSize.cy + 2));
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
                for (int i = m_ObjectRect.left + leftHanging; i < m_ObjectRect.right; i += 2)
                {
                    pDC->MoveTo(i,     (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
                    pDC->LineTo(i + 1, (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
                }

                y = 1;
            }

            for (; y < line; ++y)
                for (int i = m_ObjectRect.left; i < m_ObjectRect.right; i += 2)
                {
                    pDC->MoveTo(i,     (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
                    pDC->LineTo(i + 1, (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
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
                for (int i = m_ObjectRect.left + leftHanging; i < m_ObjectRect.right; i += 8)
                {
                    pDC->MoveTo(i,     (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
                    pDC->LineTo(i + 4, (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
                }

                y = 1;
            }

            for (; y < line; ++y)
                for (int i = m_ObjectRect.left; i < m_ObjectRect.right; i += 8)
                {
                    pDC->MoveTo(i,     (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
                    pDC->LineTo(i + 4, (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
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
                pDC->MoveTo(m_ObjectRect.left + leftHanging, (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
                pDC->LineTo(m_ObjectRect.right,              (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);

                y = 1;
            }

            for (; y < line; ++y)
            {
                pDC->MoveTo(m_ObjectRect.left,  (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
                pDC->LineTo(m_ObjectRect.right, (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
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
                for (int i = m_ObjectRect.left + leftHanging; i < m_ObjectRect.right; i += 4)
                {
                    pDC->MoveTo(i,     (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
                    pDC->LineTo(i + 2, (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
                }

                y = 1;
            }

            for (; y < line; ++y)
                for (int i = m_ObjectRect.left; i < m_ObjectRect.right; i += 4)
                {
                    pDC->MoveTo(i,     (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
                    pDC->LineTo(i + 2, (m_ObjectRect.top + (y * (textSize.cy + 2))) + textSize.cy);
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
    PSS_PLFNString::Serialize(ar);

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
        if (((PSS_Document*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        {
            ar >> m_Hanging;

            WORD wValue;
            ar >> wValue;
            m_HangingLines = UINT(wValue);

            ar >> m_InterLine;

        }
    }
}
//---------------------------------------------------------------------------
