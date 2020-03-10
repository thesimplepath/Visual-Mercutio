// ZCPropertyDescription.cpp : implementation file

#include "stdafx.h"
#include "ZCPropertyDescription.h"

#include "zProperty\PSS_Property.h"
#include "zProperty\ZBPropertyObserverMsg.h"
#include "zProperty\ZBPropertyItemObserverMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 14 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZCPropertyDescription

BEGIN_MESSAGE_MAP(ZCPropertyDescription, CStatic)
    //{{AFX_MSG_MAP(ZCPropertyDescription)
    ON_WM_PAINT()
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZCPropertyDescription::ZCPropertyDescription()
{
    m_crBackground = ::GetSysColor(COLOR_MENU);
    m_crText = ::GetSysColor(COLOR_WINDOWTEXT);
}

ZCPropertyDescription::~ZCPropertyDescription()
{}

void ZCPropertyDescription::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (!pMsg)
    {
        return;
    }

    if (ISA(pMsg, ZBPropertyItemObserverMsg))
    {
        PSS_Property* pProp = ((ZBPropertyItemObserverMsg*)pMsg)->GetProperty();

        if (pProp)
        {
            UpdateControlData(pProp);
        }
    }
    else if (ISA(pMsg, ZBPropertyObserverMsg))
    {
        EmptyControlData();
    }
}

void ZCPropertyDescription::EmptyControlData()
{
    // Update data members
    m_Title.Empty();
    m_Description.Empty();
    Invalidate();
}

void ZCPropertyDescription::UpdateControlData(PSS_Property* pProp)
{
    // Update data members
    m_Title = pProp->GetLabel();
    m_Description = pProp->GetDescription();
    Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
// ZCPropertyDescription message handlers

int ZCPropertyDescription::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    // Create the caption font.
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

    // Create the caption font.
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

void ZCPropertyDescription::OnPaint()
{
    // Device context for painting
    CPaintDC dc(this);

    CFont* pOldFont = NULL;

    // Get the rect area
    CRect rect;
    GetClientRect(rect);

    dc.FillSolidRect(rect, m_crBackground);

    COLORREF crOldBkColor = dc.SetBkColor(m_crBackground);
    COLORREF crOldTextColor = dc.SetTextColor(m_crText);

    // Draw the rectangle
    CRect BorderRect(rect);
    BorderRect.DeflateRect(2, 2);
    dc.FrameRect(BorderRect, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));

    // Draw the title
    CRect TitleRect(rect.left + 4, rect.top + 4, rect.right - 4, rect.top + 20);
    pOldFont = dc.SelectObject(&m_FontBold);
    dc.DrawText(m_Title, &TitleRect, DT_SINGLELINE | DT_LEFT | DT_TOP);

    // Draw the description
    CRect DescriptionRect(rect.left + 4, rect.top + 25, rect.right - 4, rect.bottom - 4);
    pOldFont = dc.SelectObject(&m_Font);
    dc.DrawText(m_Description, &DescriptionRect, DT_WORDBREAK | DT_LEFT);

    dc.SetTextColor(crOldTextColor);
    dc.SetBkColor(crOldBkColor);

    if (pOldFont != NULL)
    {
        dc.SelectObject(pOldFont);
    }
}
