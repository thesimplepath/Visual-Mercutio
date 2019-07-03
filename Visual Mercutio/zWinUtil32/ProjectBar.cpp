// ProjectBar.cpp : implementation file
//  

#include "stdafx.h"
#include "ProjectBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIProjectBar

ZIProjectBar::ZIProjectBar(BOOL OnlyVisible)
 : m_OnlyVisible(OnlyVisible)
{
}

ZIProjectBar::~ZIProjectBar()
{
}


void ZIProjectBar::Initialize( BOOL OnlyVisible )
{
    m_OnlyVisible = OnlyVisible;
}

BEGIN_MESSAGE_MAP(ZIProjectBar, CCJControlBar)
    //{{AFX_MSG_MAP(ZIProjectBar)
    ON_WM_CREATE()
    ON_MESSAGE(UM_DOCUMENTHASBEENSELECTED, OnDocumentHasBeenSelected)
    ON_NOTIFY(TVN_SELCHANGED, IDC_PROJECTWINDOWLIST_CTRL, OnSelchanged)
    ON_NOTIFY(NM_DBLCLK, IDC_PROJECTWINDOWLIST_CTRL, OnDblClick)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIProjectBar message handlers


int ZIProjectBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CCJControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_ProjectWindowCtrl.Create (WS_TABSTOP|WS_VISIBLE|WS_CHILD|TVS_DISABLEDRAGDROP,
        CRect(0,0,0,0), this, IDC_PROJECTWINDOWLIST_CTRL))
    {
        TRACE0("Failed to create project window tree control\n");
        return -1;
    }
    m_ProjectWindowCtrl.ModifyStyleEx(0, WS_EX_STATICEDGE);
    SetChild(&m_ProjectWindowCtrl);

    return 0;
}



afx_msg LRESULT ZIProjectBar::OnDocumentHasBeenSelected( WPARAM wParam, LPARAM lParam )
{
    ZDDocument* pDoc = (ZDDocument*)lParam;

    if (pDoc)
    {
        m_ProjectWindowCtrl.Initialize( pDoc, m_OnlyVisible );
    }
    else
    {
        m_ProjectWindowCtrl.Empty();
    }
    return 1;
}


void ZIProjectBar::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // If something selected.
    if (!m_ProjectWindowCtrl.GetSelectedDocumentTitle().IsEmpty())
        AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE, 
                                                   1, // Change the file
                                                   (LPARAM)(const char*)m_ProjectWindowCtrl.GetSelectedDocumentTitle() );

    *pResult = 0;
}

void ZIProjectBar::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // If something selected.
    if (!m_ProjectWindowCtrl.GetSelectedDocumentTitle().IsEmpty())
        AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE_OPEN, 
                                                   1, // Change the file
                                                   (LPARAM)(const char*)m_ProjectWindowCtrl.GetSelectedDocumentTitle() );

    *pResult = 0;
}
