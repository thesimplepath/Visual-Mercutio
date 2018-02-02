// ZIUserView.cpp : implementation file
//

#include "stdafx.h"
#include "ZIUserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIUserView

IMPLEMENT_DYNCREATE(ZIUserView, ZITreeView)

ZIUserView::ZIUserView()
	:	m_pUserManager(NULL)
{
}

ZIUserView::~ZIUserView()
{
}


void ZIUserView::Initialize (ZUUserManager* pUserManager)
{
	m_pUserManager = pUserManager;
	// Enable drag and drop
	((ZITreeCtrl*)&GetTreeCtrl())->DisableDragDrop( false );

	m_UserTree.Initialize( (ZITreeCtrl*)&GetTreeCtrl(), m_pUserManager );
}

void ZIUserView::ReInitialize (ZUUserManager* pUserManager)
{
	m_pUserManager = pUserManager;
	m_UserTree.ReInitialize( m_pUserManager );
}

void ZIUserView::Refresh ()
{
	m_UserTree.Refresh();
}

ZUser*	ZIUserView::GetSelectedUser()
{
	return m_UserTree.GetSelectedUser();
}

CString	ZIUserView::GetSelectedDepartement()
{
	return m_UserTree.GetSelectedDepartement();
}

BEGIN_MESSAGE_MAP(ZIUserView, ZITreeView)
	//{{AFX_MSG_MAP(ZIUserView)
	ON_MESSAGE(UM_INITIALIZE_USERMANAGER, OnInitializeUserManager)
	ON_MESSAGE(UM_RELOAD_USERMANAGER, OnReloadUserManager)
	ON_MESSAGE(UM_REFRESH_USERMANAGER, OnRefreshUserManager)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblClick)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRightClick)
	ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRightDblClick)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIUserView drawing

void ZIUserView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// ZIUserView diagnostics

#ifdef _DEBUG
void ZIUserView::AssertValid() const
{
	ZITreeView::AssertValid();
}

void ZIUserView::Dump(CDumpContext& dc) const
{
	ZITreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZIUserView message handlers



afx_msg LRESULT ZIUserView::OnInitializeUserManager( WPARAM wParam, LPARAM lParam )
{
	if (!::IsWindow(GetSafeHwnd()))
		return 1;

    m_pUserManager = (ZUUserManager*)lParam;

	if (m_pUserManager)
	{
		ZIUserView::Initialize( m_pUserManager );
	}
	return 1;
}


afx_msg LRESULT ZIUserView::OnReloadUserManager( WPARAM wParam, LPARAM lParam )
{
	if (!::IsWindow(GetSafeHwnd()))
		return 1;

    m_pUserManager = (ZUUserManager*)lParam;

	if (m_pUserManager)
	{
		ZIUserView::ReInitialize( m_pUserManager );
	}
	return 1;
}


afx_msg LRESULT ZIUserView::OnRefreshUserManager( WPARAM wParam, LPARAM lParam )
{
	if (!::IsWindow(GetSafeHwnd()))
		return 1;

	ZIUserView::Refresh();
	return 1;
}


void ZIUserView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (!AfxGetMainWnd())
		return;

	// Call the Event Handler
	OnClickEvent();

	*pResult = 0;
}

void ZIUserView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (!AfxGetMainWnd())
		return;

	// Call the Event Handler
	OnSelChangedEvent();

	*pResult = 0;
}

void ZIUserView::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (!AfxGetMainWnd())
		return;

	// Call the Event Handler
	OnDblClickEvent();

	*pResult = 0;
}

void ZIUserView::OnRightClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (!AfxGetMainWnd())
		return;

	// Call the Event Handler
	OnRightClickEvent();

	*pResult = 0;
}

void ZIUserView::OnRightDblClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (!AfxGetMainWnd())
		return;

	// Call the Event Handler
	OnRightDblClickEvent();

	*pResult = 0;
}

