// ZVSpanWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ZVSpanWnd.h"
#include "ZVSpanView.h"

#include "zRes32\zRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// ZVSpanWnd

ZVSpanWnd::ZVSpanWnd(ZVSpanView *pPanView /*= NULL*/)
{
    m_pPanView  = pPanView;
    m_bCaptured = FALSE;
    m_hOverviewCursor = AfxGetApp()->LoadCursor(IDC_OD_PAN);
    m_hOverviewOnMoveCursor = AfxGetApp()->LoadCursor(IDC_OD_PAN_READY);
	m_hCurrentOverviewCursor = NULL;
	m_rectLogPan = CRect(0,0,0,0);
	m_bClipVerified = FALSE;
}

ZVSpanWnd::~ZVSpanWnd()
{
//    if (m_pPanView)
//		m_pPanView->OverviewDestroyed();
    
    if (m_hOverviewCursor)
		DestroyCursor(m_hOverviewCursor);
    if (m_hOverviewOnMoveCursor)
		DestroyCursor(m_hOverviewOnMoveCursor);
}

BEGIN_MESSAGE_MAP(ZVSpanWnd, CWnd)
	//{{AFX_MSG_MAP(ZVSpanWnd)
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_SETCURSOR()
    ON_WM_PAINT()
    ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL ZVSpanWnd::Create(CRect rectCreate, CWnd* pParent, UINT nID, LPCTSTR lpszTitle /*= NULL*/)
{
    CString strDum;
	strDum.LoadString(IDS_SEC_PWND_TITL);
	BOOL bRetVal =
	CWnd::CreateEx(WS_EX_WINDOWEDGE/*WS_EX_TOPMOST*/,
		       AfxRegisterWndClass(CS_CLASSDC,
					   NULL,
					   (HBRUSH)(COLOR_WINDOW + 1),
					   NULL),
					   NULL, // No window title
		       WS_CHILD /*WS_POPUP*/ | WS_VISIBLE| WS_CLIPSIBLINGS|WS_BORDER,
		       rectCreate, pParent, nID, NULL);
    return bRetVal;
}

void ZVSpanWnd::AssignPanView(ZVSpanView *pView)
{
	m_pPanView = pView;
	if (pView)
		dynamic_cast<ZVSpanView*>(m_pPanView)->AssignSpanWnd( this );
}

//	
//	PreCreateWindow
//	
//	Make sure that the framework thinks we're a view
//	
//@doc ZVSpanWnd
//@mfunc Implements the overview window’s style settings at creation.
//@rdesc Default: Returns TRUE.
//@parm CREATESTRUCT& | cs | The overview window’s style settings.
//@xref<mf ZVSpanWnd::SECPanWnd>
//@xref<mf ZVSpanWnd::Create>
//@xref<c ZVSpanWnd>
BOOL ZVSpanWnd::PreCreateWindow(CREATESTRUCT& cs)
{
    if (cs.lpszClass == NULL)
	{
		cs.lpszClass = _T("SECPanWnd");
    }
    
    return TRUE;
}

//
//	SetPanRect
// 
//	The viewport for the view has changed
//	so store the new overview panning rectangle
//	coords in m_rectLogPan and draw the new
//	rectangle, erasing the old one first.
//
//      rectNewPan is in logical coordinates
//
//@doc ZVSpanWnd
//@mfunc Sets the rectangle representing the overview window.
//@rdesc void 
//@parm CRect | rectNewLogPan | The rectangle representing the newly created or updated overview window.
//@xref<mf ZVSpanWnd::DrawPanRect>
//@xref<c ZVSpanWnd>
void ZVSpanWnd::SetPanRect(CRect rectNewLogPan)
{
    ASSERT_VALID(this);
    CClientDC dc(this);
    
    m_pPanView->PreOverview();
    m_pPanView->OnPrepareDC(&dc);

	// erase old pan rect
    if(m_rectLogPan.Width() > 0) 
		DrawPanRect(&dc);

    
//
//  Code to fix pan rectangle problem
//
    CRect rectDevClient;
    //Device coords
    GetClientRect(&rectDevClient);
    ClientToScreen(&rectDevClient); //Device screen coords

    CPoint tmpPoint;
    CRect rectDevPan = rectNewLogPan;
	
    tmpPoint.x = rectDevPan.left;
    tmpPoint.y = rectDevPan.top;
    dc.LPtoDP(&tmpPoint);
    rectDevPan.left = tmpPoint.x;
    rectDevPan.top = tmpPoint.y;
	
    tmpPoint.x = rectDevPan.right;
    tmpPoint.y = rectDevPan.bottom;
    dc.LPtoDP(&tmpPoint);
    rectDevPan.right = tmpPoint.x;
    rectDevPan.bottom = tmpPoint.y;

    if (rectDevPan.Width() > rectDevClient.Width())
    {
	rectNewLogPan.right -= rectNewLogPan.left;
	rectNewLogPan.left = 0;
    }
    if (rectDevPan.Height() > rectDevClient.Height())
    {
	rectNewLogPan.bottom -= rectNewLogPan.top;
	rectNewLogPan.top = 0;
    }
//  draw new pan rect
    m_rectLogPan = rectNewLogPan;
    DrawPanRect(&dc);
    m_pPanView->PostOverview();    
}


//	
//	DrawPanRect
//	
//      Draws a dotted rectangle around the currently
//	visible viewing area for panning.
// 
//      Assumes that m_rectLogPan is in log coords
//
//@doc ZVSpanWnd
//@mfunc Draws the rectangle representing the overview window.
//@rdesc void 
//@parm CDC * | pDC | Pointer to the device context used to draw the rectangle.
//@xref<mf SECPanWnd::SetPanRect>
//@xref<c SECPanWnd>
void ZVSpanWnd::DrawPanRect(CDC * pDC)
{
    ASSERT_VALID(this);
    ASSERT(pDC != NULL);
    
    CPen pen;
    
    pDC->SaveDC();
    pDC->SetROP2(R2_NOTXORPEN);
    pen.CreatePen(PS_DOT,  0, RGB(0, 0, 0));
    
    pDC->SelectObject(&pen);
    
    pDC->Rectangle(m_rectLogPan);
    pDC->RestoreDC(-1);
    return;    
}


//	
//	ClipOverviewCursor
//	
//	Uses the size of the panning rectangle and
//	the point where the user clicked in the rectangle
//	plust the client window rect to calculate a rectangle
//	to clip the cursor too so that the user can't drag
//	the pan rectangle out of the visible part of the view.
//
void ZVSpanWnd::ClipOverviewCursor()
{
    //Don't let them move the rect out of the window!
    CRect rectDevClip;
    CRect rectDevClient;
    CSize szDevDrag  = m_szLogDrag;
    CRect rectDevPan = m_rectLogPan;
    
    // Convert m_szLogDrag and m_rectLogPan
    // to device coords for clipping rectangle calculations.
    {
	CClientDC dc(this);
	m_pPanView->PreOverview();
	m_pPanView->OnPrepareDC(&dc);
	dc.LPtoDP(&szDevDrag);
	
	CPoint tmpPoint;
	
	tmpPoint.x = rectDevPan.left;
	tmpPoint.y = rectDevPan.top;
	dc.LPtoDP(&tmpPoint);
	rectDevPan.left = tmpPoint.x;
	rectDevPan.top = tmpPoint.y;
	
	tmpPoint.x = rectDevPan.right;
	tmpPoint.y = rectDevPan.bottom;
	dc.LPtoDP(&tmpPoint);
	rectDevPan.right = tmpPoint.x;
	rectDevPan.bottom = tmpPoint.y;
	
	m_pPanView->PostOverview();
    } //BLOCK DC off
    
    //Device coords
    GetClientRect(&rectDevClient);
    ClientToScreen(&rectDevClient); //Device screen coords
    
    //Now calculate the cursor clipping rectangle in device coords.
    rectDevClip.left  = rectDevClient.left + szDevDrag.cx;
    rectDevClip.top   = rectDevClient.top + szDevDrag.cy;
    rectDevClip.right = rectDevClient.right -
	(rectDevPan.Width() - szDevDrag.cx);
    rectDevClip.bottom = rectDevClient.bottom -
	(rectDevPan.Height() - szDevDrag.cy);

//
//  Code to fix clip rectangle problem:
//  When the viewport is larger than the actual diagram, the pan rectangle
//  is larger than the pan window, so the clip rectangle is invalid.
//  Adjust the clip rectangle accordingly.
//
    if (rectDevClip.right < rectDevClip.left)
		rectDevClip.right = rectDevClip.left + rectDevPan.left;
    if (rectDevClip.bottom < rectDevClip.top)
		rectDevClip.bottom = rectDevClip.top + rectDevPan.top;
        
    //Clip the cursor in device coords.
    ::ClipCursor(&rectDevClip);
	
	m_bClipVerified = FALSE; // clipping set but not verified -- see OnMouseMove()
}

//	
//	OverviewDPtoLP
//	
//	Takes a point in device coords and does
//	the overview window magic to convert it to
//	logical coordinates.
//	
void ZVSpanWnd::OverviewDPtoLP(CPoint * pointConvert)
{    
    ASSERT_VALID(this);
    ASSERT(pointConvert != NULL);
    
    m_pPanView->PreOverview();    
    {
		CClientDC dc(this);
		m_pPanView->OnPrepareDC(&dc);
		dc.DPtoLP(pointConvert);
    }//block of DC
    
    m_pPanView->PostOverview();
    
}


/////////////////////////////////////////////////////////////////////////////
// ZVSpanWnd message handlers

//	
//	OnPaint
//	
//	Put the view into overview window mode
//	and then call OnDraw so that the view
//	does all the drawing for us.
//	
void ZVSpanWnd::OnPaint()
{
	if (m_pPanView)
	{
		ASSERT_VALID(this);
		CPaintDC dc(this);
		BOOL bDirty = FALSE;
		CRect rectClip;
		CRect rectTest = m_rectLogPan;
		dc.GetClipBox(&rectClip);
		rectClip.InflateRect(2,2);
		if (rectTest.IntersectRect(&rectTest,&rectClip))
		{
			bDirty = TRUE;
		}
    
		m_pPanView->PreOverview();
		m_pPanView->OnPrepareDC(&dc);
		m_pPanView->OnDrawPan(&dc);
		m_pPanView->PostOverview();

    
		if (bDirty)
			DrawPanRect(&dc);
	}
}


//	
//	OnLButtonDown
//	
//	If we get a button down inside the pan rect,
//	grab the cursor, clip it and start dragging
//	the pan rectangle
//	
void ZVSpanWnd::OnLButtonDown(UINT nFlags, CPoint pointDev) 
{
    if (!m_pPanView)
	{
		CWnd::OnLButtonDown(nFlags, pointDev);
		return;
	}

    nFlags;     //UNUSED
    CPoint pointLog = pointDev;
    
    //Did the user press in the panner rectangle in the overview wnd?
    if (m_rectLogPan.PtInRect(pointDev))
	{
//	    OverviewDPtoLP(&pointLog);
		m_bCaptured = TRUE;
		SetCapture();
		::SetCursor( m_hCurrentOverviewCursor = m_hOverviewCursor);
		OnSetCursor(NULL,HTCLIENT,0); //Force update of cursor
		
		//Record where they are from the upper left corner of the rect.
		m_szLogDrag.cx = pointLog.x - m_rectLogPan.left;
		m_szLogDrag.cy = pointLog.y - m_rectLogPan.top;
		ClipOverviewCursor();

		//Tell the view where we started
		m_pPanView->m_ptLogStartDrag = pointLog;
	
    } // end if - it's not in the panner rect, ignore.    
}

//	
//	OnMouseMove
//	
//	If the user is dragging the panner rectangle,
//	calculate the new location, erase the old rect,
//	draw the new one and update everything.
//	
void ZVSpanWnd::OnMouseMove(UINT nFlags, CPoint pointDev) 
{
    nFlags; //UNUSED
    CPoint pointLog = pointDev;

	// Only interested if dragging mouse
    if (m_bCaptured)
	{
		// Verify that ClipOverviewCursor() worked when called from OnLButtonDown()
		if(!m_bClipVerified)
		{
			// make sure cursor is restricted to overview window
			CRect rectDevClient, rectDevClip;
			GetClientRect(&rectDevClient);
			if ((!::GetClipCursor(rectDevClip)) ||
				rectDevClip.Width() > rectDevClient.Width() ||
				rectDevClip.Height() > rectDevClient.Height() )
			{ // ClipOverviewCursor() did not work -- try again
				::ClipCursor(NULL);
				ClipOverviewCursor();
			}
			else 
			{  // It worked! -- don't check again
				m_bClipVerified = TRUE;
			}
		}
	
		// Calculate new pan rect
//		OverviewDPtoLP(&pointLog);	
		CRect rectNewLogPan;
		rectNewLogPan.left   = pointLog.x - m_szLogDrag.cx;
		rectNewLogPan.top    = pointLog.y - m_szLogDrag.cy;
		rectNewLogPan.right  = rectNewLogPan.left + m_rectLogPan.Width();
		rectNewLogPan.bottom = rectNewLogPan.top  + m_rectLogPan.Height();

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
	{
//		OverviewDPtoLP(&pointLog);
    
		//Did the user move the cursor ove the panner rectangle in the overview wnd?
		if (m_rectLogPan.PtInRect(pointLog))
		{
			SetCapture();
			::SetCursor( m_hCurrentOverviewCursor = m_hOverviewOnMoveCursor );
			OnSetCursor(NULL,HTCLIENT,0); //Force update of cursor
		}		
		else
		{
			ReleaseCapture();
			m_hCurrentOverviewCursor = NULL;
			OnSetCursor(NULL,HTCLIENT,0); //Force update of cursor
		}
	}
}

//	
//	OnLButtonUp
//	
//	User is done dragging the panning rectangle
//	undo the capture and the clipped cursor, then
//	update everything and change the cursor back too.
//	
void ZVSpanWnd::OnLButtonUp(UINT nFlags, CPoint pointDev) 
{
    nFlags; //UNUSED
    if (m_bCaptured)
	{
		CPoint pointLog = pointDev;
		OverviewDPtoLP(&pointLog);
		
		ReleaseCapture();
		m_bCaptured = FALSE;
		m_hCurrentOverviewCursor = NULL;
		::ClipCursor(NULL); //Release the cursor
		
		CRect rectNewLogPan;
		rectNewLogPan.left   = pointLog.x - m_szLogDrag.cx;
		rectNewLogPan.top    = pointLog.y - m_szLogDrag.cy;
		rectNewLogPan.right  = rectNewLogPan.left + m_rectLogPan.Width();
		rectNewLogPan.bottom = rectNewLogPan.top  + m_rectLogPan.Height();
		SetPanRect(rectNewLogPan);
		
		m_pPanView->UpdatePanViewport(&pointLog);
    }    
    //Nothing going on, ignore onlbuttonup
}

//	
//	OnSetCursor
//	
//	Set the cursor to the cool hand with dotted rect
//	if the user is dragging the pan rectangle.
//	
BOOL ZVSpanWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
   // ASSERT(pWnd != NULL);
    ASSERT_VALID(this);
    if (nHitTest != HTCLIENT)
		return CWnd::OnSetCursor(pWnd,nHitTest,message);
    
    if (m_hCurrentOverviewCursor != NULL)
		::SetCursor(m_hCurrentOverviewCursor);
    else
		::SetCursor(::LoadCursor(NULL,IDC_ARROW));
    
    return TRUE;
}

//	
//	OnUpdate
//	
//	Called to invalidate the correct regions
//	of the overview wnd when needed.
//	
//@doc ZVSpanWnd
//@mfunc Updates the overview window when the user scrolls or updates the panning view.  Invalidates the overview
// window’s client area to force a repaint.
//@rdesc void 
//@parm CView * | pSender | Identifies the panning view being scrolled or updated by the user.
//@parm  LPARAM | lHint | Specifies what part of the overview window needs updating.
//@parm  CObject * |  pHint | Address of overview window being updated.
//@xref<c ZVSpanWnd>
void ZVSpanWnd::OnUpdate(CView * pSender, LPARAM lHint, CObject * pHint)
{
    ASSERT(pSender != NULL);
    ASSERT_VALID(this);
    
    CClientDC dc(this);
    m_pPanView->PreOverview();
    m_pPanView->OnPrepareDC(&dc);
    m_pPanView->OnUpdateOverview(pSender,lHint,pHint,&dc,this);
    m_pPanView->PostOverview();
}

void ZVSpanWnd::OnClose() 
{
    if (m_pPanView)
		m_pPanView->OverviewDestroyed();
    CWnd::OnClose();
}


#ifdef _DEBUG

void ZVSpanWnd::Dump(CDumpContext & dc)
{
    CWnd::Dump(dc);

    dc << "panview pointer is\n ";
    m_pPanView->Dump(dc);

    dc << "overview cursor = "<< (SEC_UINT)m_hOverviewCursor << "\n";
    dc << "viewport  = " << m_rectLogPan << "\n";
    
}

void ZVSpanWnd::AssertValid()
{
    CWnd::AssertValid();
    ASSERT (m_pPanView != NULL);
}



#endif

