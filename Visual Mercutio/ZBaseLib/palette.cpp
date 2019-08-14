/****************************************************************************
 * ==> PSS_PaletteBar ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a palette bar                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "palette.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_CaptionHeight 9
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PaletteBar, CToolBar)
    //{{AFX_MSG_MAP(PSS_PaletteBar)
    #ifndef _WIN32
        ON_WM_LBUTTONDOWN()
        ON_WM_MOUSEMOVE()
        ON_WM_LBUTTONUP()
        ON_WM_MOUSEACTIVATE()
        ON_WM_RBUTTONDOWN()
        ON_MESSAGE(ID_PALMENU_PROP, OnPropriety)
        ON_MESSAGE(ID_PALMENU_HIDE, OnHide)
    #endif
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PaletteBar
//---------------------------------------------------------------------------
PSS_PaletteBar::PSS_PaletteBar() :
    m_Columns(1)
    #ifndef _WIN32
        ,
        m_pParent(NULL),
        m_CxRightBorder(3),
        m_TrackMove(FALSE)
    #endif
{
    #ifndef _WIN32
        m_cyTopBorder    = CYCAPTION + 2;
        m_cxLeftBorder   = 3;
        m_cyBottomBorder = 3;

        // create the menu
        m_Menu.CreatePopupMenu();

        CString label;
        label.LoadString(IDS_PALMENU_PROP);
        m_Menu.AppendMenu(MF_STRING, ID_PALMENU_PROP, label);

        label.LoadString(IDS_PALMENU_HIDE);
        m_Menu.AppendMenu(MF_STRING, ID_PALMENU_HIDE, label);
    #endif
}
//---------------------------------------------------------------------------
PSS_PaletteBar::~PSS_PaletteBar()
{}
//---------------------------------------------------------------------------
#ifndef _WIN32
    BOOL PSS_PaletteBar::Create(CWnd* pParent, int x, int y)
    {
        ASSERT(pParent);
        m_pParent = pParent;

        return CWnd::CreateEx(0,
                              "AfxControlBar",
                              NULL,
                              WS_POPUP,
                              x,
                              y,
                              0,
                              0,
                              pParent->GetSafeHwnd(),
                              NULL,
                              NULL);
    }
#endif
//---------------------------------------------------------------------------
void PSS_PaletteBar::SetColumnCount(UINT columns)
{
    m_Columns = columns;

    #ifndef _WIN32
        RecalcLayout(count);
    #else
        const int btnCount = GetToolBarCtrl().GetButtonCount();

        for (int i = 0; i < btnCount; ++i)
        {
                  UINT style = GetButtonStyle(i);
            const BOOL wrap  = !((i + 1) % columns);

            if (wrap)
                style |=  TBBS_WRAPPED;
            else
                style &= ~TBBS_WRAPPED;

            SetButtonStyle(i, style);
        }

        Invalidate();
        GetParentFrame()->RecalcLayout();
    #endif
}
//---------------------------------------------------------------------------
void PSS_PaletteBar::SetSizes(const SIZE& sizeButton, const SIZE& sizeImage, UINT columns)
{
    SetColumns(columns);
    CToolBar::SetSizes(sizeButton, sizeImage);
}
//---------------------------------------------------------------------------
BOOL PSS_PaletteBar::SetButtons(const UINT FAR* pIDArray, int idCount, UINT columns)
{
    if (CToolBar::SetButtons(pIDArray, idCount))
    {
        SetColumns(columns);
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PaletteBar::AssertValid() const
    {
        CToolBar::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PaletteBar::Dump(CDumpContext& dc) const
    {
        CToolBar::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    void PSS_PaletteBar::GetItemRect(int index, LPRECT pRect) const
    {
        ASSERT(index >= 0 && index < m_nCount);
        ASSERT(AfxIsValidAddress(pRect, sizeof(RECT)));

        pRect->left  = m_cxLeftBorder + (index - (index / m_Columns) * m_Columns) * (m_sizeButton.cx - 1);
        pRect->right = pRect->left + m_sizeButton.cx;

        pRect->top    = m_cyTopBorder + (index / m_Columns) * (m_sizeButton.cy - 1);
        pRect->bottom = pRect->top + m_sizeButton.cy;
}
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    int PSS_PaletteBar::HitTest(const CPoint& point)
    {
        // check for x hit
        if (point.x < m_cxLeftBorder || point.x >= int(m_cxLeftBorder + m_sizeButton.cx * m_Columns))
            return -1;

        const UINT rows = (m_nCount + m_Columns - 1) / m_Columns;

        // check for y hit
        if (point.y < m_cyTopBorder || point.y >= int(m_cyTopBorder + m_sizeButton.cy * rows))
            return -1;

        const int button =
                ((point.y - m_cyTopBorder)  / (m_sizeButton.cy - 1) * m_Columns +
                 (point.x - m_cxLeftBorder) / (m_sizeButton.cx - 1));

        return (button < m_nCount) ? button : -1;
    }
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    void PSS_PaletteBar::DoPaint(CDC* pDC)
    {
        // draws any borders
        CControlBar::DoPaint(pDC);

        CRect rect;
        GetClientRect(&rect);

        // draw the frame border
        CBrush brBlack;
        brBlack.CreateSolidBrush(::GetSysColor(COLOR_WINDOWFRAME));
        pDC->FrameRect(rect, &brBlack);
        rect.bottom = CYCAPTION;
        pDC->FrameRect(rect, &brBlack);

        // fill in the caption color
        CBrush brCaption;
        brCaption.CreateSolidBrush(::GetSysColor(COLOR_ACTIVECAPTION));
        rect.InflateRect(-1, -1);
        pDC->FillRect(rect, &brCaption);

        DrawState ds;

        // initialize the bitmap selection process
        if (!PrepareDrawButton(ds))
            return;

        GetClientRect(&rect);
        rect.top    = m_cyTopBorder;
        rect.bottom = rect.top + m_sizeButton.cy;

        // draw each visible button
        for (int i = 0; i < m_nCount;)
        {
            rect.left = m_cxLeftBorder;

            for (UINT nCol = 0; nCol < m_nColumns; ++nCol, ++i)
            {
                rect.right = rect.left + m_sizeButton.cx;

                if (pDC->RectVisible(&rect))
                {
                    UINT id, style;
                    int  image;

                    GetButtonInfo(i, id, style, image);
                    DrawButton(pDC->m_hDC, rect.left, rect.top, image, style);
                }

                // prepare for overlap
                rect.left = rect.right - 1;
            }

            rect.top    = rect.bottom - 1;
            rect.bottom = rect.top    + m_sizeButton.cy;
        }

        EndDrawButton(ds);
}
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    void PSS_PaletteBar::InvertTracker(const CPoint& point)
    {
        CRect rectFrame;
        GetWindowRect(&rectFrame);

        CDC dc;
        dc.Attach(::GetDC(NULL));

        dc.PatBlt(point.x - m_Mouse.x,                     point.y - m_Mouse.y,                      rectFrame.Width(),     2,                      PATINVERT);
        dc.PatBlt(point.x - m_Mouse.x + rectFrame.Width(), point.y - m_Mouse.y,                      2,                     rectFrame.Height(),     PATINVERT);
        dc.PatBlt(point.x - m_Mouse.x,                     point.y - m_Mouse.y + rectFrame.Height(), rectFrame.Width() + 2, 2,                      PATINVERT);
        dc.PatBlt(point.x - m_Mouse.x,                     point.y - m_Mouse.y + 2,                  2,                     rectFrame.Height() - 2, PATINVERT);
        ::ReleaseDC(NULL, dc.Detach());
    }
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    void PSS_PaletteBar::RecalcLayout(UINT buttonCount)
    {
        ::SetWindowPos(NULL,
                       0,
                       0,
                       m_cxLeftBorder + (m_sizeButton.cx - 1) * m_Columns  +  m_CxRightBorder + 1,
                       m_cyTopBorder  + m_cyBottomBorder                   + (m_sizeButton.cy - 1) *
                       ((buttonCount  + m_Columns        - 1) / m_Columns) + 1,
                       SWP_NOZORDER | SWP_NOMOVE);
 
        Invalidate();
    }
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    int PSS_PaletteBar::OnMouseActivate(CWnd*, UINT, UINT)
    {
        return MA_NOACTIVATE;
    }
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    void PSS_PaletteBar::OnLButtonDown(UINT nFlags, CPoint point)
    {
        if (point.y <= m_cyTopBorder)
        {
            m_TrackMove = TRUE;
            m_Mouse     = point;

            SetCapture();
            ClientToScreen(&point);
            InvertTracker(point);

            m_Last = point;
        }
        else
            CToolBar::OnLButtonDown(nFlags, point);
    }
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    void PSS_PaletteBar::OnLButtonUp(UINT nFlags, CPoint point)
    {
        if (m_TrackMove)
        {
            m_TrackMove = FALSE;

            ReleaseCapture();
            InvertTracker(m_ptLast);
            ClientToScreen(&point);

            SetWindowPos(NULL, point.x - m_ptMouse.x, point.y - m_ptMouse.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
            ShowWindow(SW_SHOW);
        }
        else
            CToolBar::OnLButtonUp(nFlags, point);
    }
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    void PSS_PaletteBar::OnRButtonDown(UINT nFlags, CPoint point)
    {
        // show the context menu
        ClientToScreen(&point);
        m_Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
        CToolBar::OnRButtonDown(nFlags, point);
    }
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    void PSS_PaletteBar::OnMouseMove(UINT nFlags, CPoint point)
    {
        if (m_TrackMove)
        {
            CPoint pt(point);
            ClientToScreen(&point);

            InvertTracker(m_Last);
            m_Last = point;
            InvertTracker(m_Last);
        }
        else
            CToolBar::OnMouseMove(nFlags, point);
    }
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    LONG PSS_PaletteBar::OnPropriety(UINT, LONG)
    {
        return 1;
    }
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    LONG PSS_PaletteBar::OnHide(UINT, LONG)
    {
        ShowWindow(SW_HIDE);
        return 1;
    }
#endif
//---------------------------------------------------------------------------
