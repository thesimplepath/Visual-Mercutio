/****************************************************************************
 * ==> PSS_PLFNSquare ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan form square object               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNSquare.h"

// processsoft
#include "ZDDoc.h"
#include "PSS_PaintResources.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNSquare, PSS_PlanFinObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNSquare
//---------------------------------------------------------------------------
PSS_PLFNSquare::PSS_PLFNSquare() :
    PSS_PlanFinObject(),
    m_pObject(NULL),
    m_SquareType(E_SQ_Normal),
    m_ParsingMode(E_PM_Normal),
    m_SquareSize(CSize(15, 15)),
    m_SquareMaxLength(-1),
    m_CharPerSquare(1),
    m_AutoAdjustSize(FALSE)
{}
//---------------------------------------------------------------------------
PSS_PLFNSquare::PSS_PLFNSquare(const CSize& squareSize, int maxLength) :
    PSS_PlanFinObject(),
    m_pObject(NULL),
    m_SquareType(E_SQ_Normal),
    m_ParsingMode(E_PM_Normal),
    m_SquareSize(squareSize),
    m_SquareMaxLength(maxLength),
    m_CharPerSquare(1),
    m_AutoAdjustSize(FALSE)
{}
//---------------------------------------------------------------------------
PSS_PLFNSquare::PSS_PLFNSquare(const PSS_PLFNSquare& other) :
    PSS_PlanFinObject(),
    m_pObject(NULL),
    m_SquareType(E_SQ_Normal),
    m_ParsingMode(E_PM_Normal),
    m_SquareSize(CSize(15, 15)),
    m_SquareMaxLength(-1),
    m_CharPerSquare(1),
    m_AutoAdjustSize(FALSE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNSquare::~PSS_PLFNSquare()
{
    if (m_pObject)
        delete m_pObject;
}
//---------------------------------------------------------------------------
const PSS_PLFNSquare& PSS_PLFNSquare::operator = (const PSS_PLFNSquare& other)
{
    PSS_PlanFinObject::operator = ((inherited&)other);
    m_pObject         = other.m_pObject->Clone();
    m_SquareType      = other.m_SquareType;
    m_ParsingMode     = other.m_ParsingMode;
    m_SquareSize      = other.m_SquareSize;
    m_SquareMaxLength = other.m_SquareMaxLength;
    m_CharPerSquare   = other.m_CharPerSquare;
    m_AutoAdjustSize  = other.m_AutoAdjustSize;
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNSquare& PSS_PLFNSquare::operator = (const PSS_PLFNSquare* pOther)
{
    PSS_PlanFinObject::operator = ((inherited*)pOther);

    if (!pOther)
    {
        m_pObject         = NULL;
        m_SquareType      = E_SQ_Normal;
        m_ParsingMode     = E_PM_Normal;
        m_SquareSize      = CSize(15, 15);
        m_SquareMaxLength = -1;
        m_CharPerSquare   = 1;
        m_AutoAdjustSize  = FALSE;
    }
    else
    {
        m_pObject         = pOther->m_pObject->Clone();
        m_SquareType      = pOther->m_SquareType;
        m_ParsingMode     = pOther->m_ParsingMode;
        m_SquareSize      = pOther->m_SquareSize;
        m_SquareMaxLength = pOther->m_SquareMaxLength;
        m_CharPerSquare   = pOther->m_CharPerSquare;
        m_AutoAdjustSize  = pOther->m_AutoAdjustSize;
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNSquare::Clone() const
{
    std::unique_ptr<PSS_PLFNSquare> pObject(new PSS_PLFNSquare(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNSquare::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNSquare*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNSquare::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    // if no object defined, nothing to do
    if (!m_pObject)
        return;

    const CString str      = m_pObject->GetFormattedObject();
    CFont*        pOldFont = pDC->SelectObject(GetFont(pView));

    if (str.GetLength())
    {
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(GetColor(pView));
    }

    // measure the text
    const CSize sizeText(pDC->GetTextExtent("A", 1));

    // if auto-size enabled, calculate the square size
    if (m_AutoAdjustSize)
    {
        m_SquareSize     = CSize(sizeText.cx + 4, sizeText.cy + 4);
        m_ObjectRect.top = m_ObjectRect.bottom - m_SquareSize.cy;

        CRect rect(m_ObjectRect);
        rect.InflateRect(5, 5);

        ::InvalidateRect(::GetActiveWindow(), &rect, TRUE);
    }

    DrawSquares(pDC);

    const int baseText = (m_ObjectRect.Height() - sizeText.cy) / 2;

    pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);

    for (int i = 0; i < str.GetLength(); ++i)
        pDC->TextOut(m_ObjectRect.left   + (m_SquareSize.cx / 2) + (i * m_SquareSize.cx) + 1,
                     m_ObjectRect.bottom - baseText,
                     str[i]);

    pDC->SelectObject(pOldFont);

    PSS_PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
CString PSS_PLFNSquare::GetFormattedObject()
{
    if (m_pObject)
        return m_pObject->GetFormattedObject();

    return "";
}
//---------------------------------------------------------------------------
CString PSS_PLFNSquare::GetUnformattedObject()
{
    if (m_pObject)
        return m_pObject->GetUnformattedObject();

    return "";
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNSquare::ConvertFormattedObject(const CString& value, BOOL locateFormat, BOOL emptyWhenZero)
{
    if (m_pObject)
        return m_pObject->ConvertFormattedObject(value, locateFormat, emptyWhenZero);

    // hasn't changed
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_PLFNSquare::Serialize(CArchive& ar)
{
    PSS_PlanFinObject::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << m_SquareSize;
        ar << DWORD(m_SquareMaxLength);
        ar << WORD(m_AutoAdjustSize);
        ar << DWORD(m_CharPerSquare);
        ar << WORD(m_SquareType);
        ar << WORD(m_ParsingMode);

        // serialize the oject
        ar << m_pObject;
    }
    else
    {
        // read the elements
        ar >> m_SquareSize;

        DWORD dwValue;
        ar >> dwValue;
        m_SquareMaxLength = int(dwValue);

        WORD wValue;
        ar >> wValue;
        m_AutoAdjustSize = wValue;

        ar >> dwValue;
        m_CharPerSquare = unsigned(dwValue);

        ar >> wValue;
        m_SquareType = ESquareType(wValue);

        ar >> wValue;
        m_ParsingMode = EParsingModeType(wValue);

        // serialize the oject defined
        ar >> m_pObject;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNSquare::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNSquare::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_PLFNSquare::DrawSquares(CDC* pDC)
{
    // if no object defined, nothing to do
    if (!m_pObject)
        return;

    const CString str         = m_pObject->GetFormattedObject();
    int           squareCount = m_SquareMaxLength;
    CPen*         pOldPen     = pDC->SelectObject(&PSS_PaintResources::GetBlackPen());

    // only draw squares if the length is defined
    if (m_SquareMaxLength == -1)
    {
        squareCount = __max(1, str.GetLength());

        // sdjust the right side
        m_ObjectRect.right = m_ObjectRect.left + (squareCount * m_SquareSize.cx);
    }

    if (m_AutoAdjustSize)
        // adjust the right side
        m_ObjectRect.right = m_ObjectRect.left + (squareCount * m_SquareSize.cx);

    // draw the outside rect
    pDC->MoveTo(m_ObjectRect.left,  m_ObjectRect.top);
    pDC->LineTo(m_ObjectRect.left,  m_ObjectRect.bottom);
    pDC->LineTo(m_ObjectRect.right, m_ObjectRect.bottom);
    pDC->LineTo(m_ObjectRect.right, m_ObjectRect.top);
    pDC->LineTo(m_ObjectRect.left,  m_ObjectRect.top);

    // iterate through each square and draw the vertical line
    for (int i = m_CharPerSquare; i < squareCount; i += m_CharPerSquare)
    {
        pDC->MoveTo(m_ObjectRect.left + (i * m_SquareSize.cx), m_ObjectRect.top);
        pDC->LineTo(m_ObjectRect.left + (i * m_SquareSize.cx), m_ObjectRect.bottom);
    }

    pDC->SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
