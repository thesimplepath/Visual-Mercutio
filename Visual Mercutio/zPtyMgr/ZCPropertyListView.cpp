// ZCPropertyListView.cpp : implementation file
//

#include "stdafx.h"
#include "ZCPropertyListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// ZCPropertyListView

IMPLEMENT_DYNCREATE(ZCPropertyListView, CView)

ZCPropertyListView::ZCPropertyListView()
{
}

ZCPropertyListView::~ZCPropertyListView()
{
}


BEGIN_MESSAGE_MAP(ZCPropertyListView, CView)
	//{{AFX_MSG_MAP(ZCPropertyListView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZCPropertyListView drawing

void ZCPropertyListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// ZCPropertyListView diagnostics

#ifdef _DEBUG
void ZCPropertyListView::AssertValid() const
{
	CView::AssertValid();
}

void ZCPropertyListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG



void ZCPropertyListView::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
	m_listctrl.OnUpdate( pSubject, pMsg );
}

/////////////////////////////////////////////////////////////////////////////
// ZCPropertyListView message handlers

int ZCPropertyListView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_listctrl.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|LBS_NOINTEGRALHEIGHT, CRect(0,0,0,0), this, 1); 
	
	return 0;
}

void ZCPropertyListView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	m_listctrl.MoveWindow(0, 0, cx, cy); 	
}
