/****************************************************************************
 * ==> PSS_SpanWnd ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a span window                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SpanWnd.h"

// processsoft
#include "ZVSpanView.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SpanWnd, CWnd)
    //{{AFX_MSG_MAP(PSS_SpanWnd)
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_SETCURSOR()
    ON_WM_PAINT()
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SpanWnd
//---------------------------------------------------------------------------
PSS_SpanWnd::PSS_SpanWnd(ZVSpanView* pPanView) :
    m_pPanView(pPanView),
    m_hOverviewCursor(NULL),
    m_hCurrentOverviewCursor(NULL),
    m_hOverviewOnMoveCursor(NULL),
    m_Captured(FALSE),
    m_ClipVerified(FALSE)
{
    m_hOverviewCursor       = AfxGetApp()->LoadCursor(IDC_OD_PAN);
    m_hOverviewOnMoveCursor = AfxGetApp()->LoadCursor(IDC_OD_PAN_READY);
}
//---------------------------------------------------------------------------
PSS_SpanWnd::~PSS_SpanWnd()
{
    if (m_hOverviewCursor)
        DestroyCursor(m_hOverviewCursor);

    if (m_hOverviewOnMoveCursor)
        DestroyCursor(m_hOverviewOnMoveCursor);
}
//---------------------------------------------------------------------------
BOOL PSS_SpanWnd::Create(const CRect& rectCreate, CWnd* pParent, UINT id, LPCTSTR pTitle)
{
    CString dummy;
    dummy.LoadString(IDS_SEC_PWND_TITL);

    return CWnd::CreateEx(WS_EX_WINDOWEDGE,
                          AfxRegisterWndClass(CS_CLASSDC,
                                              NULL,
                                              HBRUSH(COLOR_WINDOW + 1),
                                              NULL),
                          NULL,
                          WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_BORDER,
                          rectCreate,
                          pParent,
                          id,
                          NULL);
}
//---------------------------------------------------------------------------
void PSS_SpanWnd::AssignPanView(ZVSpanView* pView)
{
    m_pPanView = pView;

    if (pView)
        dynamic_cast<ZVSpanView*>(m_pPanView)->AssignSpanWnd(this);
}
//---------------------------------------------------------------------------
BOOL PSS_SpanWnd::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!cs.lpszClass)
        cs.lpszClass = _T("SECPanWnd");

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SpanWnd::SetPanRect(CRect& rectNewLogPan)
{
    ASSERT_VALID(this);
    CClientDC dc(this);

    m_pPanView->PreOverview();
    m_pPanView->OnPrepareDC(&dc);

    // erase old pan rect
    if (m_RectLogPan.Width() > 0)
        DrawPanRect(&dc);

    CRect rectDevClient;

    // device coords
    GetClientRect(&rectDevClient);

    //Device screen coords
    ClientToScreen(&rectDevClient);

    CPoint tmpPoint;
    CRect  rectDevPan = rectNewLogPan;

    tmpPoint.x = rectDevPan.left;
    tmpPoint.y = rectDevPan.top;
    dc.LPtoDP(&tmpPoint);

    rectDevPan.left = tmpPoint.x;
    rectDevPan.top  = tmpPoint.y;

    tmpPoint.x = rectDevPan.right;
    tmpPoint.y = rectDevPan.bottom;
    dc.LPtoDP(&tmpPoint);

    rectDevPan.right  = tmpPoint.x;
    rectDevPan.bottom = tmpPoint.y;

    if (rectDevPan.Width() > rectDevClient.Width())
    {
        rectNewLogPan.right -= rectNewLogPan.left;
        rectNewLogPan.left   = 0;
    }

    if (rectDevPan.Height() > rectDevClient.Height())
    {
        rectNewLogPan.bottom -= rectNewLogPan.top;
        rectNewLogPan.top     = 0;
    }

    // draw new pan rect
    m_RectLogPan = rectNewLogPan;
    DrawPanRect(&dc);
    m_pPanView->PostOverview();
}
//---------------------------------------------------------------------------
void PSS_SpanWnd::DrawPanRect(CDC* pDC)
{
    ASSERT_VALID(this);
    ASSERT(pDC);

    pDC->SaveDC();
    pDC->SetROP2(R2_NOTXORPEN);

    CPen pen;
    pen.CreatePen(PS_DOT, 0, RGB(0, 0, 0));
    pDC->SelectObject(&pen);

    pDC->Rectangle(m_RectLogPan);
    pDC->RestoreDC(-1);
    return;
}
//---------------------------------------------------------------------------
void PSS_SpanWnd::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    ASSERT(pSender);
    ASSERT_VALID(this);

    CClientDC dc(this);

    m_pPanView->PreOverview();
    m_pPanView->OnPrepareDC(&dc);
    m_pPanView->OnUpdateOverview(pSender, lHint, pHint, &dc, this);
    m_pPanView->PostOverview();
}
//---------------------------------------------------------------------------
void PSS_SpanWnd::ClipOverviewCursor()
{
    // don't let the rect be moved out of the window
    CRect rectDevClip;
    CRect rectDevClient;
    CSize devDragSize = m_LogDrag;
    CRect rectDevPan  = m_RectLogPan;

    // convert m_LogDrag and m_RectLogPan to device coords for clipping rectangle calculation
    CClientDC dc(this);
    m_pPanView->PreOverview();
    m_pPanView->OnPrepareDC(&dc);
    dc.LPtoDP(&devDragSize);

    CPoint tmpPoint;
    tmpPoint.x = rectDevPan.left;
    tmpPoint.y = rectDevPan.top;
    dc.LPtoDP(&tmpPoint);

    rectDevPan.left = tmpPoint.x;
    rectDevPan.top  = tmpPoint.y;

    tmpPoint.x = rectDevPan.right;
    tmpPoint.y = rectDevPan.bottom;
    dc.LPtoDP(&tmpPoint);

    rectDevPan.right  = tmpPoint.x;
    rectDevPan.bottom = tmpPoint.y;

    m_pPanView->PostOverview();

    // device coords
    GetClientRect(&rectDevClient);

    // device screen coords
    ClientToScreen(&rectDevClient);

    // calculate the cursor clipping rectangle in device coords
    rectDevClip.left   = rectDevClient.left   + devDragSize.cx;
    rectDevClip.top    = rectDevClient.top    + devDragSize.cy;
    rectDevClip.right  = rectDevClient.right  - (rectDevPan.Width()  - devDragSize.cx);
    rectDevClip.bottom = rectDevClient.bottom - (rectDevPan.Height() - devDragSize.cy);

    // when the viewport is larger than the actual diagram, the pan rectangle is larger than
    // the pan window, so the clip rectangle is invalid. Adjust the clip rectangle accordingly
    if (rectDevClip.right < rectDevClip.left)
        rectDevClip.right = rectDevClip.left + rectDevPan.left;

    if (rectDevClip.bottom < rectDevClip.top)
        rectDevClip.bottom = rectDevClip.top + rectDevPan.top;

    // clip the cursor in device coords
    ::ClipCursor(&rectDevClip);

    // clipping set but not verified -- see OnMouseMove()
    m_ClipVerified = FALSE;
}
//---------------------------------------------------------------------------
void PSS_SpanWnd::OverviewDPtoLP(CPoint* pPoint)
{
    ASSERT_VALID(this);
    ASSERT(pPoint);

    m_pPanView->PreOverview();

    CClientDC dc(this);
    m_pPanView->OnPrepareDC(&dc);
    dc.DPtoLP(pPoint);

    m_pPanView->PostOverview();

}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SpanWnd::AssertValid()
    {
        CWnd::AssertValid();
        ASSERT(m_pPanView);
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SpanWnd::Dump(CDumpContext& dc)
    {
        CWnd::Dump(dc);

        dc << "panview pointer is\n";
        m_pPanView->Dump(dc);

        dc << "overview cursor = " << SEC_UINT(m_hOverviewCursor) << "\n";
        dc << "viewport  = "       << m_RectLogPan                << "\n";

    }
#endif
//---------------------------------------------------------------------------
void PSS_SpanWnd::OnClose()
{
    if (m_pPanView)
        m_pPanView->OverviewDestroyed();

    CWnd::OnClose();
}
//---------------------------------------------------------------------------
void PSS_SpanWnd::OnLButtonDown(UINT nFlags, CPoint pointDev)
{
    if (!m_pPanView)
    {
        CWnd::OnLButtonDown(nFlags, pointDev);
        return;
    }

    const CPoint pointLog = pointDev;

    // did the user press in the panner rectangle in the overview wnd?
    if (m_RectLogPan.PtInRect(pointDev))
    {
        m_Captured = TRUE;
        SetCapture();

        ::SetCursor(m_hCurrentOverviewCursor = m_hOverviewCursor);

        // force the cursor update
        OnSetCursor(NULL, HTCLIENT, 0);

        // record where they are from the upper left corner of the rect
        m_LogDrag.cx = pointLog.x - m_RectLogPan.left;
        m_LogDrag.cy = pointLog.y - m_RectLogPan.top;
        ClipOverviewCursor();

        // tell the view where we started
        m_pPanView->m_ptLogStartDrag = pointLog;
    }
}
//---------------------------------------------------------------------------
void PSS_SpanWnd::OnLButtonUp(UINT nFlags, CPoint pointDev)
{
    if (m_Captured)
    {
        CPoint pointLog = pointDev;
        OverviewDPtoLP(&pointLog);

        ReleaseCapture();
        m_Captured               = FALSE;
        m_hCurrentOverviewCursor = NULL;

        // release the cursor
        ::ClipCursor(NULL);

        CRect rectNewLogPan;
        rectNewLogPan.left   = pointLog.x         - m_LogDrag.cx;
        rectNewLogPan.top    = pointLog.y         - m_LogDrag.cy;
        rectNewLogPan.right  = rectNewLogPan.left + m_RectLogPan.Width();
        rectNewLogPan.bottom = rectNewLogPan.top  + m_RectLogPan.Height();
        SetPanRect(rectNewLogPan);

        m_pPanView->UpdatePanViewport(&pointLog);
    }
}
//---------------------------------------------------------------------------
void PSS_SpanWnd::OnMouseMove(UINT nFlags, CPoint pointDev)
{
    CPoint pointLog = pointDev;

    // only interested if dragging mouse
    if (m_Captured)
    {
        // verify that ClipOverviewCursor() worked when called from OnLButtonDown()
        if (!m_ClipVerified)
        {
            CRect rectDevClient, rectDevClip;
            GetClientRect(&rectDevClient);

            // make sure cursor is restricted to overview window
            if ((!::GetClipCursor(rectDevClip))             ||
                rectDevClip.Width() > rectDevClient.Width() ||
                rectDevClip.Height() > rectDevClient.Height())
            {
                // ClipOverviewCursor() did not work -- try again
                ::ClipCursor(NULL);
                ClipOverviewCursor();
            }
            else
                // It worked! -- don't check again
                m_ClipVerified = TRUE;
        }

        // Calculate new pan rect
        CRect rectNewLogPan;
        rectNewLogPan.left   = pointLog.x         - m_LogDrag.cx;
        rectNewLogPan.top    = pointLog.y         - m_LogDrag.cy;
        rectNewLogPan.right  = rectNewLogPan.left + m_RectLogPan.Width();
        rectNewLogPan.bottom = rectNewLogPan.top  + m_RectLogPan.Height();

        // Erase old pan rect and draw new one
        SetPanRect(rectNewLogPan);

        // Update the view, if desired
        if (m_pPanView->m_panMode == ZVP_PANINSTANT)
        {
            m_pPanView->UpdatePanViewport(&pointLog);
            m_pPanView->m_ptLogStartDrag = pointLog;
        }
    }
    else
    if (m_RectLogPan.PtInRect(pointLog))
    {
        // the user moved the cursor over the panner rectangle in the overview wnd
        SetCapture();
        ::SetCursor(m_hCurrentOverviewCursor = m_hOverviewOnMoveCursor);

        // force cursor update
        OnSetCursor(NULL, HTCLIENT, 0);
    }
    else
    {
        ReleaseCapture();
        m_hCurrentOverviewCursor = NULL;

        // force cursor update
        OnSetCursor(NULL, HTCLIENT, 0);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_SpanWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    ASSERT_VALID(this);

    if (nHitTest != HTCLIENT)
        return CWnd::OnSetCursor(pWnd, nHitTest, message);

    if (m_hCurrentOverviewCursor)
        ::SetCursor(m_hCurrentOverviewCursor);
    else
        ::SetCursor(::LoadCursor(NULL, IDC_ARROW));

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SpanWnd::OnPaint()
{
    if (m_pPanView)
    {
        ASSERT_VALID(this);

        CPaintDC dc(this);

        CRect rectClip;
        dc.GetClipBox(&rectClip);
        rectClip.InflateRect(2, 2);

        CRect rectTest = m_RectLogPan;
        BOOL  dirty = FALSE;

        if (rectTest.IntersectRect(&rectTest, &rectClip))
            dirty = TRUE;

        m_pPanView->PreOverview();
        m_pPanView->OnPrepareDC(&dc);
        m_pPanView->OnDrawPan(&dc);
        m_pPanView->PostOverview();

        if (dirty)
            DrawPanRect(&dc);
    }
}
//---------------------------------------------------------------------------
