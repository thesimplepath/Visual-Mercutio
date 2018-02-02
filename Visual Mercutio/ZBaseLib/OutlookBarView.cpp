	// OutlookBarView.cpp : implementation file
//

#include "stdafx.h"
#include "OutlookBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIOutlookBarView

IMPLEMENT_DYNCREATE(ZIOutlookBarView, CView)

ZIOutlookBarView::ZIOutlookBarView()
{
}

ZIOutlookBarView::~ZIOutlookBarView()
{
}


BEGIN_MESSAGE_MAP(ZIOutlookBarView, CView)
	//{{AFX_MSG_MAP(ZIOutlookBarView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_OUTLOOKBAR_NOTIFY, (LRESULT(CWnd::*)(WPARAM, LPARAM))OnOutbarNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIOutlookBarView drawing

void ZIOutlookBarView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// ZIOutlookBarView diagnostics

#ifdef _DEBUG
void ZIOutlookBarView::AssertValid() const
{
	CView::AssertValid();
}

void ZIOutlookBarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZIOutlookBarView message handlers

void ZIOutlookBarView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Size the outlook style menu, and set 
	// the column size same as view
	m_Pager.MoveWindow(0,0,cx,cy);
	m_OutBar.Invalidate(true);
}

int ZIOutlookBarView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the pager control and set its parent to 'this'
	if (!m_Pager.Create(WS_CHILD|WS_VISIBLE|PGS_VERT,
		CRect(0,0,0,0), this, IDC_PAGER_CONTROL ))
	{
		TRACE0("Failed to create CPagerCtrl...\n");
		return -1;
	}

	// Define the style to use with the COutlookBar.
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | LBS_OWNERDRAWVARIABLE | 
		LBS_NOINTEGRALHEIGHT | WS_TABSTOP;

	// Create the COutlookBar, and set its parent to CPagerCtrl.
	if (!m_OutBar.Create( dwStyle, CRect(0,0,0,0),
		&m_Pager, IDC_OUTLOOK_BAR ))
	{
		TRACE0("Failed to create COutlookBar...\n");
		return -1;
	}
	
	// Set the CWnd object you want messages sent to.
	m_OutBar.SetOwner (this);

	// Set the Vert/Horz scroll area for pager.
	m_Pager.SetScrollArea(0,575);

	// Set the child HWND to COutlookBar, and button size to 15.
	m_Pager.SetChild(m_OutBar.m_hWnd);
	m_Pager.SetButtonSize(15);
	
	return 0;
}

void ZIOutlookBarView::InitializeMenuControl(CContentItems* pContents, size_t ContentSize, CImageList* pImageListSmall /*=NULL*/, CImageList* pImageListLarge /*=NULL*/)
{
    // Define the font to be used for the menu control
	m_Font.CreatePointFont (85, _T("Tahoma"));
    m_OutBar.SetFont(&m_Font);

	// Set the image list for the menu control
	m_OutBar.SetImageLists(pImageListSmall, pImageListLarge);
	m_OutBar.SetItems(pContents, ContentSize);
}

BOOL ZIOutlookBarView::OnOutbarNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case OBM_ITEMCLICK:
		{
			return ChangeContext( (size_t)lParam );
		}
	}
	
	return FALSE;
}


BOOL	ZIOutlookBarView::ChangeContext( size_t Context )
{
	return TRUE;
}