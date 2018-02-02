// ZIProjectView.cpp : implementation file
//

#include "stdafx.h"
#include "ZIProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIProjectView

IMPLEMENT_DYNCREATE(ZIProjectView, CTreeView)

ZIProjectView::ZIProjectView()
 : m_OnlyVisible(FALSE)
{
}

ZIProjectView::~ZIProjectView()
{
}

void ZIProjectView::Initialize( BOOL OnlyVisible )
{
	m_OnlyVisible = OnlyVisible;
	m_ProjectTree.Initialize( (ZITreeCtrl*)&GetTreeCtrl(), NULL, m_OnlyVisible );
}




BEGIN_MESSAGE_MAP(ZIProjectView, CTreeView)
	//{{AFX_MSG_MAP(ZIProjectView)
	ON_MESSAGE(UM_DOCUMENTHASBEENSELECTED, OnDocumentHasBeenSelected)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblClick)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIProjectView drawing

void ZIProjectView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// ZIProjectView diagnostics

#ifdef _DEBUG
void ZIProjectView::AssertValid() const
{
	CTreeView::AssertValid();
}

void ZIProjectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG





/////////////////////////////////////////////////////////////////////////////
// ZIProjectView message handlers



afx_msg LRESULT ZIProjectView::OnDocumentHasBeenSelected( WPARAM wParam, LPARAM lParam )
{
	if (!::IsWindow(GetSafeHwnd()))
		return 1;

    ZDDocument* pDoc = (ZDDocument*)lParam;

	if (pDoc)
	{
		m_ProjectTree.Initialize( (ZITreeCtrl*)&GetTreeCtrl(), pDoc, m_OnlyVisible );
	}
	else
	{
		m_ProjectTree.Empty();
	}
	return 1;
}



void ZIProjectView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (!AfxGetMainWnd())
		return;

	// If something selected.
	if (!m_ProjectTree.GetSelectedDocumentTitle().IsEmpty())
		AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE, 
												   1, // Change the file
												   (LPARAM)(const char*)m_ProjectTree.GetSelectedDocumentTitle() );

	*pResult = 0;
}

void ZIProjectView::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (!AfxGetMainWnd())
		return;

	// If something selected.
	if (!m_ProjectTree.GetSelectedDocumentTitle().IsEmpty())
		AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE_OPEN, 
												   1, // Change the file
												   (LPARAM)(const char*)m_ProjectTree.GetSelectedDocumentTitle() );

	*pResult = 0;
}

int ZIProjectView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CCtrlView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}
