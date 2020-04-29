/****************************************************************************
 * ==> PSS_TextAlignButton -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a text button with alignement style               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_TextAlignButton.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_TextAlignButton, CBitmapButton)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_TextAlignButton, CBitmapButton)
    //{{AFX_MSG_MAP(PSS_TextAlignButton)
    ON_WM_DRAWITEM()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_TextAlignButton
//---------------------------------------------------------------------------
PSS_TextAlignButton::PSS_TextAlignButton(const CString& text, UINT style, BOOL check, CWnd* pParentWnd, UINT resID) :
    CBitmapButton(),
    m_pParentWnd(pParentWnd),
    m_Text(text),
    m_Style(style),
    m_ResID(resID),
    m_Check(check)
{
    if (m_pParentWnd)
        SubclassDlgItem(m_ResID, m_pParentWnd);
}
//---------------------------------------------------------------------------
PSS_TextAlignButton::PSS_TextAlignButton(const PSS_TextAlignButton& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_TextAlignButton::~PSS_TextAlignButton()
{}
//---------------------------------------------------------------------------
const PSS_TextAlignButton& PSS_TextAlignButton::operator = (const PSS_TextAlignButton& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_TextAlignButton::Create(const CString& text, UINT style, BOOL check, CWnd* pParentWnd, UINT resID)
{
    m_Text       = text;
    m_Style      = style;
    m_Check      = check;
    m_pParentWnd = pParentWnd;
    m_ResID      = resID;

    SubclassDlgItem(m_ResID, m_pParentWnd);
}
//---------------------------------------------------------------------------
void PSS_TextAlignButton::DrawItem (LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CPen*   pOldPen;
    CPen    newPen(PS_SOLID, 1, defCOLOR_BLACK);
    CPen    shadowPen(PS_SOLID, 1, defCOLOR_WHITE);
    CBrush* pOldBrush;
    CBrush  newBrush;
    CDC*    pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    PSS_Assert(pDC);

    CRect rect;
    GetClientRect(&rect);
    
    if (GetCheck())
        newBrush.CreateSolidBrush(defCOLOR_BLUE);
    else
        newBrush.CreateSolidBrush(defCOLOR_LTLTGRAY);
        
    pOldPen   = pDC->SelectObject(&newPen);
    pOldBrush = pDC->SelectObject(&newBrush);
    pDC->Rectangle(rect);
    pDC->SelectObject(&shadowPen);
    pDC->MoveTo(rect.left  - 1, rect.bottom - 1);
    pDC->LineTo(rect.right,     rect.bottom - 1);
    pDC->MoveTo(rect.right - 1, rect.top    - 1);
    pDC->LineTo(rect.right - 1, rect.bottom);
    pDC->SetBkMode(TRANSPARENT);
    rect.InflateRect(-2, -2);
    pDC->SetTextColor(defCOLOR_WHITE);
    pDC->DrawText(m_Text, -1, &rect, m_Style);
    rect.OffsetRect(2, 2);
    pDC->SetTextColor(defCOLOR_BLACK);
    pDC->DrawText(m_Text, -1, &rect, m_Style);
    rect.OffsetRect(-1, -1);
    pDC->SetTextColor(defCOLOR_GRAY);
    pDC->DrawText(m_Text, -1, &rect, m_Style);
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}
//---------------------------------------------------------------------------
