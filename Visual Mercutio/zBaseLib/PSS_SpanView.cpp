/****************************************************************************
 * ==> PSS_SpanView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a span view                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SpanView.h"

// processsoft
#include "PSS_SpanWnd.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_SpanView, CScrollView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SpanView, CScrollView)
    //{{AFX_MSG_MAP(PSS_SpanView)
    ON_WM_HSCROLL()
    ON_WM_VSCROLL()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SpanView
//---------------------------------------------------------------------------
PSS_SpanView::PSS_SpanView() :
    CScrollView(),
    m_pOverview(NULL),
    m_PanMode(IE_PM_Delay),
    m_hOrigCursor(0),
    m_hDragCursor(0),
    m_CursorID(0),
    m_OriginalZoomMode(0),
    m_Panning(FALSE),
    m_InVirtualDraw(FALSE),
    m_OriginalCenter(FALSE)
{}
//---------------------------------------------------------------------------
PSS_SpanView::~PSS_SpanView()
{
    if (m_hDragCursor)
        ::DestroyCursor(m_hDragCursor);
    
    if (m_pOverview)
    {
        m_pOverview->DestroyWindow();
        m_pOverview = NULL;
    }
}
//---------------------------------------------------------------------------
void PSS_SpanView::AssignSpanWnd(PSS_SpanWnd* pWnd)
{
    if (pWnd == m_pOverview)
        return;

    m_pOverview = pWnd;

    if (pWnd)
        PSS_Assert(m_pOverview);

    if (m_pOverview)
    {
        m_pOverview->OnUpdate(this, 0L, NULL);
        m_pOverview->UpdateWindow();
        UpdateOverviewRect();
    }
}
//---------------------------------------------------------------------------
void PSS_SpanView::SetPanMode(IEPanMode mode)
{
    PSS_Assert(mode != IE_PM_Delay || mode != IE_PM_Instant);

    m_PanMode = mode;
}
//---------------------------------------------------------------------------
void PSS_SpanView::StartPan(CPoint* pPanPoint, UINT cursorID)
{
    PSS_Assert(pPanPoint);
    ASSERT_VALID(this);

    m_Panning = TRUE;

    CWinApp* pApp = ::AfxGetApp();

    // change the cursor
    if (pApp)
    {
        m_CursorID = cursorID;
        m_hDragCursor = pApp->LoadCursor(m_CursorID);
    }
    else
        m_hDragCursor = NULL;

    // on assertion, there's a problem with the resource setup in the DLL/LIB.
    // Be sure to follow what the SEC samples are doing
    PSS_Assert(m_hDragCursor);

    OnSetCursor(NULL, HTCLIENT, 0);

    m_LogStartDrag = *pPanPoint;

    SetCapture();
}
//---------------------------------------------------------------------------
void PSS_SpanView::ContinuePan(CPoint* pPanPoint)
{
    PSS_Assert(m_Panning);

    // move the pan rectangle to reflect the new panning
    if (m_PanMode == IE_PM_Instant)
    {
        PerformPan(pPanPoint);
        UpdateOverviewRect();
    }
}
//---------------------------------------------------------------------------
void PSS_SpanView::EndPan(CPoint* pPanPoint)
{
    PSS_Assert(m_Panning);

    ReleaseCapture();

    m_Panning = FALSE;
    OnSetCursor(NULL, HTCLIENT, 0);

    PerformPan(pPanPoint);
    UpdateOverviewRect();
}
//---------------------------------------------------------------------------
void PSS_SpanView::UpdateOverviewWnd(CView* pSender, LPARAM lHint, CObject* pHint)
{
    if (m_pOverview)
        m_pOverview->OnUpdate(pSender, lHint, pHint);
}
//---------------------------------------------------------------------------
void PSS_SpanView::OnUpdateOverview(CView* pSender, LPARAM lHint, CObject* pHint, CDC* pOverviewDC, CWnd* pWndOverview)
{
    pWndOverview->InvalidateRect(NULL);
}
//---------------------------------------------------------------------------
void PSS_SpanView::CenterOnLogicalPoint(CPoint& point)
{
    // convert the point to device coordinates
    ViewLPtoDP(&point);

    // account for scroll bar position
    ClientToDevice(point);

    // use CScrollView's function for device coordinates
    CScrollView::CenterOnPoint(point);
}
//---------------------------------------------------------------------------
CPoint PSS_SpanView::GetLogicalCenterPoint()
{
    CRect rect;

    // get the screen center
    GetClientRect(&rect);

    CPoint pt;
    pt.x = (rect.Width()  / 2);
    pt.y = (rect.Height() / 2);

    // convert the point to logical coordinates
    ViewDPtoLP(&pt);

    return pt;
}
//---------------------------------------------------------------------------
void PSS_SpanView::ViewDPtoLP(LPPOINT pPoints, int count)
{
    PSS_Assert(m_nMapMode > 0);

    // convert to logical units. Called from view when no DC is available
    CWindowDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(pPoints, count);
}
//---------------------------------------------------------------------------
void PSS_SpanView::ViewLPtoDP(LPPOINT pPoints, int count)
{
    // convert to logical units. Called from view when no DC is available
    PSS_Assert(m_nMapMode > 0);

    CWindowDC dc(this);
    OnPrepareDC(&dc);
    dc.LPtoDP(pPoints, count);
}
//---------------------------------------------------------------------------
void PSS_SpanView::ClientToDevice(CPoint& point)
{
    // need to take in account for scrollbar position
    const CPoint scrollPt  = GetDeviceScrollPosition();
    point.x               += scrollPt.x;
    point.y               += scrollPt.y;
}
//---------------------------------------------------------------------------
BOOL PSS_SpanView::OnSetCursor(CWnd* pWnd, UINT hitTest, UINT message)
{
    if (hitTest != HTCLIENT)
        return CScrollView::OnSetCursor(pWnd, hitTest, message);

    if (m_Panning)
    {
        if (!m_hOrigCursor)
            m_hOrigCursor = ::SetCursor(m_hDragCursor);
        else
            ::SetCursor(m_hDragCursor);

        return TRUE;
    }

    // panning not started, so set cursor back
    if (m_hOrigCursor)
    {
        ::SetCursor(m_hOrigCursor);
        m_hOrigCursor = 0;
        return TRUE;
    }

    return CScrollView::OnSetCursor(pWnd, hitTest, message);
}
//---------------------------------------------------------------------------
void PSS_SpanView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);

    if (!m_InVirtualDraw)
        UpdateOverviewRect();
}
//---------------------------------------------------------------------------
void PSS_SpanView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);

    if (!m_InVirtualDraw)
        UpdateOverviewRect();
}
//---------------------------------------------------------------------------
void PSS_SpanView::OnSize(UINT nType, int cx, int cy)
{
    CScrollView::OnSize(nType, cx, cy);

    if (!m_InVirtualDraw)
        UpdateOverviewRect();
}
//---------------------------------------------------------------------------
void PSS_SpanView::PersistRatio(const CSize& origin, CSize& dest, CPoint& remainder)
{
    const float ratio1 = float(origin.cx / origin.cy);
    const float ratio2 = float(dest.cx   / dest.cy);
    int         newSize;

    // do nothing if ratios are the same
    if (ratio1 > ratio2)
    {
        // shrink height
        newSize     = int(dest.cx / ratio1);
        remainder.x = 0;
        remainder.y = dest.cy - newSize;
        dest.cy     = newSize;
    }
    else
    if (ratio2 > ratio1)
    {
        // shrink width
        newSize     = int(dest.cy * ratio1);
        remainder.x = dest.cx - newSize;
        remainder.y = 0;
        dest.cx     = newSize;
    }
}
//---------------------------------------------------------------------------
void PSS_SpanView::ZoomLevelChanged()
{
    if (!m_InVirtualDraw)
        UpdateOverviewRect();
}
//---------------------------------------------------------------------------
void PSS_SpanView::OnDrawPan(CDC* pDC)
{}
//---------------------------------------------------------------------------
void PSS_SpanView::PerformPan(CPoint* pEndPan, BOOL reversePan)
{
    if (!pEndPan)
        return;

    CClientDC dc(this);
    OnPrepareDC(&dc);

    CSize sizeScroll;

    if (reversePan)
    {
        sizeScroll.cx = pEndPan->x - m_LogStartDrag.x;
        sizeScroll.cy = pEndPan->y - m_LogStartDrag.y;
    }
    else
    {
        sizeScroll.cx = m_LogStartDrag.x - pEndPan->x;
        sizeScroll.cy = m_LogStartDrag.y - pEndPan->y;
    }
    dc.LPtoDP(&sizeScroll);
    DoScroll(sizeScroll, TRUE);
}
//---------------------------------------------------------------------------
void PSS_SpanView::UpdateOverviewRect()
{
    ASSERT_VALID(this);

    // Ok for m_pOverview to be NULL. Protect here, so callers don't have to
    if (!m_pOverview)
        return;

    CRect rectClient;
    GetClientRect(&rectClient);

    try
    {
        CClientDC dc(this);
        OnPrepareDC(&dc);
        dc.DPtoLP(&rectClient);
    }
    catch (...)
    {
        throw;
    }

    m_pOverview->SetPanRect(rectClient);
}
//---------------------------------------------------------------------------
void PSS_SpanView::PreOverview()
{
    PSS_Assert(m_pOverview);

    CPoint pt;
    CRect  clientRect;

    // store state
    m_OriginalTotalDev = m_totalDev;
    m_OriginalCenter   = m_bCenter;
    m_InVirtualDraw    = TRUE;

    // setup a special zoom mode for the pan overview window, so the view's OnDraw will be tricked into drawing
    // the overview window automatically
    m_bCenter = FALSE;

    // the overview window shows the entire view in it's borders, so setup the device size to the client size
    m_pOverview->GetClientRect(&clientRect);

    PSS_Assert(!clientRect.top && !clientRect.left);
    m_totalDev.cx = clientRect.right;
    m_totalDev.cy = clientRect.bottom;

    // make sure the overview looks just like the panview derivative
    PersistRatio(m_totalLog, m_totalDev, pt);
}
//---------------------------------------------------------------------------
void PSS_SpanView::PostOverview()
{
    // restore state
    m_totalDev      = m_OriginalTotalDev;
    m_bCenter       = m_OriginalCenter;
    m_InVirtualDraw = FALSE;
}
//---------------------------------------------------------------------------
void PSS_SpanView::OverviewDestroyed()
{
    ASSERT_VALID(this);

    if (m_pOverview)
        m_pOverview = NULL;
}
//---------------------------------------------------------------------------
void PSS_SpanView::UpdatePanViewport(CPoint* pNewLog)
{
    ASSERT_VALID(this);
    PSS_Assert(pNewLog);

    PerformPan(pNewLog, TRUE);
}
//---------------------------------------------------------------------------
BOOL PSS_SpanView::DoScroll(CSize& sizeScroll, BOOL doScroll)
{
    const DWORD style = GetStyle();

    // if no scrollbars, don't do anything. E.g. the user has a small scale in a zoom, or a large
    // window and there are no scroll bars.  Everything is in view, so no panning needed
    CScrollBar* pBar = GetScrollBarCtrl(SB_VERT);

    if ((pBar && !pBar->IsWindowEnabled()) || (!pBar && !(style & WS_VSCROLL)))
        sizeScroll.cy = 0;

    pBar = GetScrollBarCtrl(SB_HORZ);

    if ((pBar && !pBar->IsWindowEnabled()) || (!pBar && !(style & WS_HSCROLL)))
        sizeScroll.cx = 0;

    // adjust current x position based on scroll bar constraints
    int       x     = GetScrollPos(SB_HORZ);
    const int xOrig = x;
    const int xMax  = GetScrollLimit(SB_HORZ);

    x += sizeScroll.cx;

    if (x < 0)
        x = 0;
    else
    if (x > xMax)
        x = xMax;

    // adjust current y position based on scroll bar constraints
    int       y     = GetScrollPos(SB_VERT);
    const int yOrig = y;
    const int yMax  = GetScrollLimit(SB_VERT);

    y += sizeScroll.cy;

    if (y < 0)
        y = 0;
    else
    if (y > yMax)
        y = yMax;

    // if nothing changed, just return, no work to do
    if (x == xOrig && y == yOrig)
        return FALSE;

    if (doScroll)
    {
        // this order and combination of calls generates the smoothest scrolling. UpdateWindow() slows down things,
        // but without it items are 'stretched' around the scrollbar zomes because of multiple ScrollWindow() calls,
        // this is especially noticable in realtime panning
        if (x != xOrig)
            SetScrollPos(SB_HORZ, x);

        if (y != yOrig)
            SetScrollPos(SB_VERT, y);

        ScrollWindow(-(x - xOrig), -(y - yOrig));

        UpdateWindow();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SpanView::AssertValid() const
    {
        CScrollView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SpanView::Dump(CDumpContext& dc) const
    {
        CScrollView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
