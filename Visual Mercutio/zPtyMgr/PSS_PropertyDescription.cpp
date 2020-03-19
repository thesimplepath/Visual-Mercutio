/****************************************************************************
 * ==> PSS_PropertyDescription ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a property description                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PropertyDescription.h"

// processsoft
#include "zProperty\PSS_Property.h"
#include "zProperty\PSS_PropertyObserverMsg.h"
#include "zProperty\PSS_PropertyItemObserverMsg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PropertyDescription, CStatic)
    //{{AFX_MSG_MAP(PSS_PropertyDescription)
    ON_WM_PAINT()
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PropertyDescription
//---------------------------------------------------------------------------
PSS_PropertyDescription::PSS_PropertyDescription() :
    CStatic(),
    PSS_Observer()
{
    m_Background = ::GetSysColor(COLOR_MENU);
    m_Text       = ::GetSysColor(COLOR_WINDOWTEXT);
}
//---------------------------------------------------------------------------
PSS_PropertyDescription::~PSS_PropertyDescription()
{}
//---------------------------------------------------------------------------
void PSS_PropertyDescription::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (!pMsg)
        return;

    PSS_PropertyItemObserverMsg* pPropItemMsg = dynamic_cast<PSS_PropertyItemObserverMsg*>(pMsg);

    if (pPropItemMsg)
    {
        PSS_Property* pProp = pPropItemMsg->GetProperty();

        if (pProp)
            UpdateControlData(pProp);

        return;
    }

    PSS_PropertyObserverMsg* pPropMsg = dynamic_cast<PSS_PropertyObserverMsg*>(pMsg);

    if (pPropMsg)
        EmptyControlData();
}
//---------------------------------------------------------------------------
int PSS_PropertyDescription::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create the caption font
    if (!m_Font.CreateFont(14,
                           6,
                           0,
                           0,
                           FW_NORMAL,
                           0,
                           0,
                           0,
                           ANSI_CHARSET,
                           OUT_TT_PRECIS,
                           CLIP_DEFAULT_PRECIS,
                           PROOF_QUALITY,
                           0,
                           _T("Tahoma")))
    {
        TRACE0(_T("Unable to create caption font.\n"));
        return -1;
    }

    // create the bold caption font
    if (!m_FontBold.CreateFont(14,
                               6,
                               0,
                               0,
                               FW_BOLD,
                               0,
                               0,
                               0,
                               ANSI_CHARSET,
                               OUT_TT_PRECIS,
                               CLIP_DEFAULT_PRECIS,
                               PROOF_QUALITY,
                               0,
                               _T("Tahoma")))
    {
        TRACE0(_T("Unable to create caption font.\n"));
        return -1;
    }

    return 0;
}
//---------------------------------------------------------------------------
void PSS_PropertyDescription::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);

    // get the component rect
    CRect rect;
    GetClientRect(rect);

    // draw the background
    dc.FillSolidRect(rect, m_Background);

    // draw the outline
    CRect borderRect(rect);
    borderRect.DeflateRect(2, 2);
    dc.FrameRect(borderRect, CBrush::FromHandle(HBRUSH(GetStockObject(BLACK_BRUSH))));

    COLORREF oldBkColor   = dc.SetBkColor(m_Background);
    COLORREF oldTextColor = dc.SetTextColor(m_Text);
    CFont*   pOldFont     = NULL;

    try
    {
        CRect titleRect(rect.left + 4, rect.top + 4, rect.right - 4, rect.top + 20);
        pOldFont = dc.SelectObject(&m_FontBold);

        // draw the title
        dc.DrawText(m_Title, &titleRect, DT_SINGLELINE | DT_LEFT | DT_TOP);

        CRect  descriptionRect(rect.left + 4, rect.top + 25, rect.right - 4, rect.bottom - 4);
        CFont* pOldDescFont = dc.SelectObject(&m_Font);

        if (!pOldFont)
            pOldFont = pOldDescFont;

        // draw the description
        dc.DrawText(m_Description, &descriptionRect, DT_WORDBREAK | DT_LEFT);
    }
    catch (...)
    {
        dc.SetTextColor(oldTextColor);
        dc.SetBkColor(oldBkColor);

        if (pOldFont)
            dc.SelectObject(pOldFont);

        throw;
    }

    dc.SetTextColor(oldTextColor);
    dc.SetBkColor(oldBkColor);

    if (pOldFont)
        dc.SelectObject(pOldFont);
}
//---------------------------------------------------------------------------
void PSS_PropertyDescription::EmptyControlData()
{
    // update the data members
    m_Title.Empty();
    m_Description.Empty();
    Invalidate();
}
//---------------------------------------------------------------------------
void PSS_PropertyDescription::UpdateControlData(PSS_Property* pProp)
{
    // update the data members
    m_Title       = pProp->GetLabel();
    m_Description = pProp->GetDescription();
    Invalidate();
}
//---------------------------------------------------------------------------
