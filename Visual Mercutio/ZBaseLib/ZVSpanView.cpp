// ZVSpanView.cpp : implementation file
//

#include "stdafx.h"
#include "ZVSpanView.h"
#include "ZVSpanWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVSpanView

IMPLEMENT_DYNAMIC(ZVSpanView, CScrollView)

BEGIN_MESSAGE_MAP(ZVSpanView, CScrollView)
    //{{AFX_MSG_MAP(ZVSpanView)
    //}}AFX_MSG_MAP
    ON_WM_HSCROLL()
    ON_WM_VSCROLL()
    ON_WM_SIZE()
END_MESSAGE_MAP()


ZVSpanView::ZVSpanView()
 : CScrollView()
{
    m_nCursorID   = 0;
    m_panMode     = ZVP_PANDELAY; //Default
    m_bPanning    = FALSE;
    m_hOrigCursor = 0;
    m_hDragCursor = 0;
    m_pOverview   = NULL;
	m_InVirtualDraw = FALSE;
}

ZVSpanView::~ZVSpanView()
{
    if (m_hDragCursor)
		DestroyCursor(m_hDragCursor);
    
    if (m_pOverview)
	{
		m_pOverview->DestroyWindow();
		m_pOverview = NULL;
    }

/*
	// clean up any overview allocations
	CWnd* pWnd;
	POSITION pos=m_listAllocOverview.GetHeadPosition();
	while(pos) 
	{
		pWnd=(CWnd *)m_listAllocOverview.GetNext(pos);
		delete pWnd;
	}
*/
}


void ZVSpanView::AssignSpanWnd( ZVSpanWnd *pWnd )
{
	if (pWnd == m_pOverview)
		return;
    m_pOverview = pWnd;

    if (pWnd) 
	{
	
        ASSERT(m_pOverview != NULL);
	
//		m_listAllocOverview.AddTail(m_pOverview);
    }
	if (m_pOverview)
	{
		m_pOverview->OnUpdate(this,0L,NULL);
	    m_pOverview->UpdateWindow();
	    UpdateOverviewRect();
    }
}

//Operations

//	
//	SetPanMode
//	
//	Just change the mode
//	

//@doc ZVSpanView
//@mfunc Changes the pan mode to either ZVP_PANINSTANT or ZVP_PANDELAY.
//@rdesc void 
//@parm SECPanMode | newPanMode | ZVP_PANINSTANT or ZVP_PANDELAY
//@xref<mf ZVSpanView::GetPanMode>
//@xref<c ZVSpanView>
void ZVSpanView::SetPanMode(ZVPanMode newPanMode)
{
    ASSERT(newPanMode != ZVP_PANDELAY ||
	   newPanMode != ZVP_PANINSTANT);
    
    m_panMode = newPanMode;
}

//	
//	StartPan
//
//      Start the panning process.  Store the starting
//      point so that when we're done, we know what to do.
//
//	ptPan is in logical points, up to caller to
//	translate from device to logical coords.
//
//@doc ZVSpanView
//@mfunc Call StartPan to signal ZVSpanView that the user has started panning the view.  ZVSpanView displays the pan 
// cursor if one is available.  This member function can be overridden if you want to change some aspect of the panning behavior.
//@rdesc void 
//@parm CPoint * | ptPan | The start of the pan, used by ZVSpanView to calculate the amount of panning that takes place.
//@parm UINT | nCursorID | The resource ID for a cursor you would like to be displayed when the user pans.
//@xref<mf ZVSpanView::ContinuePan>
//@xref<mf ZVSpanView::EndPan>
//@xref<c ZVSpanView>
//@end
void ZVSpanView::StartPan(CPoint * ptPan,
			  UINT nCursorID /* = 0 */)
{
    ASSERT(ptPan != NULL);
    ASSERT_VALID(this);
    
    m_bPanning = TRUE;
    
    //Change the cursor
    m_nCursorID   = nCursorID;    
    m_hDragCursor = AfxGetApp()->LoadCursor(m_nCursorID);
    
	// SEC User's::>
	// If you ASSERT here, there's a problem			 
	// with your resource setup in your DLL/LIB.
	// Be sure to follow what the SEC Samples										 
	// are doing..
	
    ASSERT (m_hDragCursor != 0);


    OnSetCursor(NULL,HTCLIENT,0);
    
    m_ptLogStartDrag = *ptPan;
    
    SetCapture();
}

//	
//	ContinuePan
//	
//	Continue panning, if we're in delay mode
//	just update pan rectangle.  If we're in instant
//	mode, actually perform a pan.
//
//	ptPan should be logical coordinates.
//	
//@doc ZVSpanView
//@mfunc As the user pans the view, you must call ContinuePan so that ZVSpanView will know what the user is doing with the
// view.  In ZVP_PANINSTANT mode, ContinuePan automatically updates the view to reflect the panning.  This member function
// can be overridden if you want to change some aspect of the panning behavior.
//@rdesc void 
//@parm CPoint * | ptPan | The next point in the pan process.
//@xref<mf ZVSpanView::StartPan>
//@xref<mf ZVSpanView::EndPan>
//@xref<c ZVSpanView>
void ZVSpanView::ContinuePan(CPoint * ptPan)
{
    ASSERT(m_bPanning != FALSE);
    
    // Move the pan rectangle to reflect the new panning.    
    
    if (m_panMode == ZVP_PANINSTANT)
	{
		PerformPan(ptPan);
		UpdateOverviewRect();
    }
}

//	EndPan
//	
//	Turn out the lights, the panning's over!
//    
//      Release the capture, return the
//      cursor to the original value, 
//      do the final pan and update the overview wnd.
//
//      ptPan should be in logical coordinates
//  
//@doc ZVSpanView
//@mfunc To end the panning process, call EndPan.  If the ZVSpanView is in ZVP_PANDELAY mode, the view will not be updated
// until this point.  Even if you are in ZVP_PANINSTANT, you have to call EndPan because the view performs internal calculations
// and frees any panning resources.  This member function can be overridden if you want to change some aspect of the panning behavior.
//@rdesc void 
//@parm CPoint * | ptPan | The final point in the pan process.
//@xref<mf ZVSpanView::StartPan>
//@xref<mf ZVSpanView::ContinuePan>
//@xref<c ZVSpanView>
void ZVSpanView::EndPan(CPoint * ptPan)
{
    ASSERT(m_bPanning != FALSE);
    ReleaseCapture();
    
    m_bPanning = FALSE;
    OnSetCursor(NULL,HTCLIENT,0);
    
    PerformPan(ptPan);
    UpdateOverviewRect();
}

//	
//	PerformPan
//	
//	Does the actual scrolling of the window and
//	also the updating of scrollbars.
//	
//      ptEndPan must be in logical coords.
//      bReversePan indicates that it's not a drag, but
//      a reverse pan, like the overview does.
//
//      12/10 - broke out scrolling logic into DoScroll()
//   
//
void ZVSpanView::PerformPan(CPoint * ptEndPan, BOOL bReversePan /* FALSE */)
{
    CClientDC dc(this);

    OnPrepareDC(&dc);
    CSize sizeScroll;
    if (bReversePan)
	{
		sizeScroll.cx = ptEndPan->x - m_ptLogStartDrag.x;
		sizeScroll.cy = ptEndPan->y - m_ptLogStartDrag.y;
    }
    else
	{
		sizeScroll.cx = m_ptLogStartDrag.x - ptEndPan->x;
		sizeScroll.cy = m_ptLogStartDrag.y - ptEndPan->y;
    }
    dc.LPtoDP(&sizeScroll);
    DoScroll(sizeScroll,TRUE);    
}


//
//   Overview Window Operations 
//


//	
//	PreOverview
//	
//	We're about to call preparedc/ondraw
//	with the values necessary to draw the
//	overview window, so save the current state
//	so that our view doesn't get messed up by having
//	a new zoom level.
//
void ZVSpanView::PreOverview()
{
    ASSERT(m_pOverview != NULL);

    CPoint pt;
    CRect  clientRect;
    
    //Store state
    m_orig_szTotalDev = m_totalDev;
    m_orig_bCenter    = m_bCenter;
//    m_orig_zoomMode   = m_zoomMode;
	m_InVirtualDraw   = TRUE;
    
    //Setup a special zoom mode for the pan overview window
    //So that the view's OnDraw will be tricked into drawing
    //our overview window for us.
    m_bCenter  = FALSE;
//    m_zoomMode = SEC_ZOOMPANOVER;

    //The overview window shows the entire view
    //in it's borders, so setup the device size to
    //the client size.
    m_pOverview->GetClientRect(&clientRect);
    
    ASSERT(clientRect.top == 0 && clientRect.left == 0);
    m_totalDev.cx = clientRect.right;
    m_totalDev.cy = clientRect.bottom;

    // Make sure that the overview looks just like the
    // panview derivative.
    PersistRatio(m_totalLog,m_totalDev,pt);
}

//	
//	PostOverview
//	
//	The overview has been painted, so now revert
//	back to our original state as preserved in 
//	PreOverview() so that when the view draws, it
//      doesn't get messed up by drawing using the
//      stuff we setup for the overview window
//
void ZVSpanView::PostOverview()
{
    //ReStore state
    m_totalDev   = m_orig_szTotalDev;
    m_bCenter    = m_orig_bCenter;
//    m_zoomMode   = m_orig_zoomMode;
	m_InVirtualDraw = FALSE;
}

//	
//	UpdateOverviewRect
//
//      The viewport has changed, so we need to
//      let the overview window know.
//
//      Calculate the currently visible rectangle      
//      in logical coordinates and let it know.
//
void ZVSpanView::UpdateOverviewRect()
{
    ASSERT_VALID(this);

    //Ok for m_pOverview to be NULL.
    if (m_pOverview == NULL) //protect here, so callers don't have to
		return;
    
    CRect rectClient;
    GetClientRect(&rectClient);
    {
		CClientDC dc(this);
		OnPrepareDC(&dc);
		dc.DPtoLP(&rectClient);
    } //BLOCK for DC

    m_pOverview->SetPanRect(rectClient);
}

//	
//	OverviewDestroyed
//	
//	Called from the overview wnd to notify
//	the view that it has been destroyed.
//	
void ZVSpanView::OverviewDestroyed()
{
    ASSERT_VALID(this);
    if (m_pOverview)
	{
		m_pOverview = NULL;
    }
}

//	
//	UpdatePanViewport
//	
//	The user has changed our viewport
//	using the overview window dragging rect.
//	Update our viewport to reflect the changes
//	
//      rectNewLog is the new rectangle in log coords.
//      Similar to onscrollby.
//
//
void ZVSpanView::UpdatePanViewport(CPoint * lpPtNewLog)
{
    ASSERT_VALID(this);
    ASSERT(lpPtNewLog != NULL);
	
    PerformPan(lpPtNewLog,TRUE);
}

//	
//	UpdateOverviewWnd
//	
//	Similar behavior of CDoc::UpdateAllViews
//	
//	PanView user must call this after
//	UpdateAllViews with same args
//      to get overview window behavior
//

//@doc ZVSpanView
//@mfunc Updates the overview window.
//@rdesc void 
//@parm CView * | pSender | View initiating the update.
//@parm LPARAM | lHint | Contains information about the modifications.
//@parm CObject * | pHint | Points to an object containing information about the modifications.
//@xref<mf ZVSpanView::ShowOverviewWnd>
//@xref<mf ZVSpanView::HideOverviewWnd>
//@xref<mf ZVSpanView::OnUpdateOverview>
//@xref<c ZVSpanView>
//@end
void ZVSpanView::UpdateOverviewWnd(CView * pSender,
				   LPARAM lHint /* = 0L */,
				   CObject * pHint /* = NULL */)
{
    if (m_pOverview)
		m_pOverview->OnUpdate(pSender,lHint,pHint);
}

//	
//	OnUpdateOverview
//	
//	ZVSpanView user should override this
//	and treat it just like CView::OnUpdate
//	but be sure to use the CDC * provided
//	and the CWnd * for any invalidates.
//
//      Default implementation invalidates everything,
//      but this will cause flashing unless
//      user overrides this and calls his invalidate
//      logic instead.
//

//@doc ZVSpanView
//@mfunc When overview window is updated, invalidates all of the window or, using hints, only some regions for repainting.
// Override this function if you want to update only those regions that map to the modified portions of the document. To
// do this you must pass information about the modifications using the hint parameters.
//@rdesc void 
//@parm CView * | pSender | View initiating the update.
//@parm LPARAM | lHint | Contains information about the modifications.
//@parm CObject * | pHint | Points to an object containing information about the modifications.
//@parm CDC * | pOverviewDC | Points to a device context for repainting the overview window.
//@parm  CWnd * | pWndOverview | Points to the overview window to be repainted.
//@xref<mf ZVSpanView::ShowOverviewWnd>
//@xref<mf ZVSpanView::HideOverviewWnd>
//@xref<mf ZVSpanView::UpdateOverviewWnd>
//@xref<c ZVSpanView>
void ZVSpanView::OnUpdateOverview(CView * pSender,
			      LPARAM lHint,CObject * pHint,
			      CDC * pOverviewDC, CWnd * pWndOverview)
{
//UNUSED
 pOverviewDC;
 pHint;
 lHint;
 pSender;
    pWndOverview->InvalidateRect(NULL);
}

//
//  ZVSpanView Message handlers
//


//	
//	OnSetCursor
//	
//	If we're in pan mode set the cursor to a hand, else
//	default to the original cursor.
//	
BOOL ZVSpanView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    if (nHitTest != HTCLIENT)
		return CScrollView::OnSetCursor(pWnd,nHitTest,message);

    if (m_bPanning)
	{
		if (!m_hOrigCursor)
			m_hOrigCursor = ::SetCursor(m_hDragCursor);
		else
			::SetCursor(m_hDragCursor);
		return TRUE;
    }

    //If we make it here, we're not panning, so set back.
    if (m_hOrigCursor)
	{
		::SetCursor(m_hOrigCursor);
		m_hOrigCursor = 0;
		return TRUE;
    }
    return CScrollView::OnSetCursor(pWnd,nHitTest,message);
    
}

//	
//	OnHScroll
//	
//	User has changed the viewport, update the
//	overview window
//	
void ZVSpanView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CScrollView::OnHScroll(nSBCode,nPos,pScrollBar);
	if (m_InVirtualDraw == FALSE)
		UpdateOverviewRect();
}
	
//	OnVScroll
//	
//	User has changed the viewport, update the
//	overview window.
//	
void ZVSpanView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CScrollView::OnVScroll(nSBCode,nPos,pScrollBar);
	if (m_InVirtualDraw == FALSE)
		UpdateOverviewRect();
}

//	
//	OnSize handler
//	
//      Let the overview window know the viewport's changed.
//	
void ZVSpanView::OnSize(UINT nType, int cx, int cy) 
{
    CScrollView::OnSize(nType, cx, cy);
    
	if (m_InVirtualDraw == FALSE)
		UpdateOverviewRect();
} 

//	
//	ZoomLevelChanged
//	
//	The user has changed the zoom level
//	update the overview window rectangle
//	because this affects the viewport.
//	
void ZVSpanView::ZoomLevelChanged(void)
{ 
	if (m_InVirtualDraw == FALSE)
		UpdateOverviewRect();
}

//	
//	ZVSpanView::DoScroll()
//	
//	Broke this out of PerformPan to isolate 
//	device/logical coordinate issues.
//	
//	sizeScroll - the amount to scroll in DEVICE coordinates
//	
BOOL ZVSpanView::DoScroll(CSize sizeScroll, BOOL bDoScroll)
{
    int xOrig, x, xMax;
    int yOrig, y, yMax;

    CScrollBar* pBar;
    DWORD dwStyle = GetStyle();
    //If no scroll bars, don't do anything
    // e.g. the user has a small scale in a zoom, or a large
    //     window and there are no scroll bars.  Everything is
    //     in view, so no panning needed.
    
    pBar = GetScrollBarCtrl(SB_VERT);
    if ((pBar != NULL && !pBar->IsWindowEnabled()) ||
		(pBar == NULL && !(dwStyle & WS_VSCROLL)))
	{
		sizeScroll.cy = 0;
	}

    pBar = GetScrollBarCtrl(SB_HORZ);
    if ((pBar != NULL && !pBar->IsWindowEnabled()) ||
		(pBar == NULL && !(dwStyle & WS_HSCROLL)))
	{
		sizeScroll.cx = 0;
	}
    // Adjust current x position based on scroll bar constraints.
    xOrig = x = GetScrollPos(SB_HORZ);
    
    xMax = GetScrollLimit(SB_HORZ);
    x += sizeScroll.cx;

    if (x < 0)
		x = 0;
    else 
	if (x > xMax)
		x = xMax;

    
    // Adjust current y position based on scroll bar constraints.
    yOrig = y = GetScrollPos(SB_VERT);
    yMax = GetScrollLimit(SB_VERT);
    
    y += sizeScroll.cy;
    if (y < 0)
		y = 0;
    else 
		if (y > yMax)
		y = yMax;
    
    // If nothing changed, just return, no work to do.
    if (x == xOrig && y == yOrig)
		return FALSE;
    
    if (bDoScroll)
    {
		// This order and combination of calls generates the smoothest
		// scrolling.
		// UpdateWindow slows down things, but without it items are
		// 'stretched' around the scrollbar zomes because of multiple
		// ScrollWindow calls - this is especially noticable in realtime
		// panning.
		
		if (x != xOrig)
			SetScrollPos(SB_HORZ, x);
		if (y != yOrig)
			SetScrollPos(SB_VERT, y);
		ScrollWindow(-(x-xOrig), -(y-yOrig));
		
		UpdateWindow();
    }
    return TRUE;
}



//	
//	CenterOnLogicalPoint
//	
//	Same as CScrollView::CenterOnPoint, but for log point.
//	
//	
void ZVSpanView::CenterOnLogicalPoint(CPoint pt)
{
    // Convert the point to device coordinates
    ViewLPtoDP(&pt);
    // Account for scroll bar position
    ClientToDevice(pt);
    // Use CScrollView's function for device coordinates
    CScrollView::CenterOnPoint(pt);
} 

//	
//	GetLogicalCenterPoint
//	
CPoint ZVSpanView::GetLogicalCenterPoint (void)  
{
    CPoint pt;
    CRect rect;
    // Get the center of screen
    GetClientRect(&rect);
    pt.x = (rect.Width()  / 2);
    pt.y = (rect.Height() / 2);
    
    // Convert the point to logical coordinates
    ViewDPtoLP(&pt);
    return pt;
} 

//	
//	ViewDPtoLP
//	
//	Same as DPtoLP, but uses Client DC.
void ZVSpanView::ViewDPtoLP (
    LPPOINT lpPoints,
    int     nCount)
{
    // Convert to logical units
    // Called from View when no DC is available
    ASSERT(m_nMapMode > 0); // must be set
    CWindowDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(lpPoints, nCount);
} 

//	
//	Same as LPtoDP, but uses Client DC
//	
void ZVSpanView::ViewLPtoDP (
    LPPOINT lpPoints,
    int     nCount)
{
    // Convert to logical units
    // Called from View when no DC is available
    ASSERT(m_nMapMode > 0); // must be set
    CWindowDC dc(this);
    OnPrepareDC(&dc);
    dc.LPtoDP(lpPoints, nCount);
} 

void ZVSpanView::ClientToDevice (
    CPoint &point)
{
    // Need to account for scrollbar position
    CPoint scrollPt = GetDeviceScrollPosition();
    point.x += scrollPt.x;
    point.y += scrollPt.y;
} 

//	
//	PersistRatio
//	
//	Since we're not ISOTROPIC, make sure we maintain
//	the same x/y ratios.
//	
void ZVSpanView::PersistRatio (
    const CSize &orig,
    CSize       &dest,
    CPoint      &remainder)
{
    float ratio1 = (float) orig.cx / orig.cy;
    float ratio2 = (float) dest.cx / dest.cy;
    int   newSize;
    
    // Do nothing if they are the same
    if (ratio1 > ratio2) {
	// Shrink hieght
	newSize = (int)(dest.cx / ratio1);
	remainder.x = 0;
	remainder.y = dest.cy - newSize;
	dest.cy = newSize;
    } else if (ratio2 > ratio1) {
	// Shrink width
	newSize = (int)(dest.cy * ratio1);
	remainder.x = dest.cx - newSize;
	remainder.y = 0;
	dest.cx = newSize;
    }
} 


/////////////////////////////////////////////////////////////////////////////
// ZVSpanView diagnostics

#ifdef _DEBUG
void ZVSpanView::AssertValid() const
{
	CScrollView::AssertValid();
}

void ZVSpanView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG


