/****************************************************************************
 * ==> PSS_UserView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user view                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_UserView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_UserView, ZITreeView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UserView, ZITreeView)
    //{{AFX_MSG_MAP(PSS_UserView)
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
//---------------------------------------------------------------------------
// PSS_UserView
//---------------------------------------------------------------------------
PSS_UserView::PSS_UserView() :
    m_pUserManager(NULL)
{}
//---------------------------------------------------------------------------
PSS_UserView::~PSS_UserView()
{}
//---------------------------------------------------------------------------
void PSS_UserView::Initialize(PSS_UserManager* pUserManager)
{
    m_pUserManager = pUserManager;

    // enable drag and drop
    ((ZITreeCtrl*)&GetTreeCtrl())->DisableDragDrop(false);

    m_UserTree.Initialize((ZITreeCtrl*)&GetTreeCtrl(), m_pUserManager);
}
//---------------------------------------------------------------------------
void PSS_UserView::ReInitialize(PSS_UserManager* pUserManager)
{
    m_pUserManager = pUserManager;
    m_UserTree.ReInitialize(m_pUserManager);
}
//---------------------------------------------------------------------------
void PSS_UserView::Refresh()
{
    m_UserTree.Refresh();
}
//---------------------------------------------------------------------------
ZUser* PSS_UserView::GetSelectedUser()
{
    return m_UserTree.GetSelectedUser();
}
//---------------------------------------------------------------------------
CString PSS_UserView::GetSelectedDepartement()
{
    return m_UserTree.GetSelectedDepartement();
}
//---------------------------------------------------------------------------
void PSS_UserView::OnSelChangedEvent()
{}
//---------------------------------------------------------------------------
void PSS_UserView::OnClickEvent()
{}
//---------------------------------------------------------------------------
void PSS_UserView::OnDblClickEvent()
{}
//---------------------------------------------------------------------------
void PSS_UserView::OnRightClickEvent()
{}
//---------------------------------------------------------------------------
void PSS_UserView::OnRightDblClickEvent()
{}
//---------------------------------------------------------------------------
void PSS_UserView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();

    // todo -cFeature -oJean: add draw code here
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_UserView::OnInitializeUserManager(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pUserManager = (PSS_UserManager*)lParam;

    if (m_pUserManager)
        Initialize(m_pUserManager);

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_UserView::OnReloadUserManager(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pUserManager = (PSS_UserManager*)lParam;

    if (m_pUserManager)
        ReInitialize(m_pUserManager);

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_UserView::OnRefreshUserManager(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    Refresh();
    return 1;
}
//---------------------------------------------------------------------------
void PSS_UserView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the Event Handler
    OnSelChangedEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_UserView::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the Event Handler
    OnClickEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_UserView::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the Event Handler
    OnDblClickEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_UserView::OnRightClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the Event Handler
    OnRightClickEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_UserView::OnRightDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the Event Handler
    OnRightDblClickEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UserView::AssertValid() const
    {
        ZITreeView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UserView::Dump(CDumpContext& dc) const
    {
        ZITreeView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
