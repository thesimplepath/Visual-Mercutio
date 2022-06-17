/****************************************************************************
 * ==> PSS_UserGroupView ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user group view                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UserGroupView.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"

// resources
#include "Resources.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int g_FlatToolbarHeight = 22;
//---------------------------------------------------------------------------
// Message constants
//---------------------------------------------------------------------------
const int IDC_UGP_ADDGROUP     = 2000;
const int IDC_UGP_RENAMEGROUP  = 2001;
const int IDC_UGP_DELETEGROUP  = 2002;
const int IDC_UGP_ADDROLE      = 2003;
const int IDC_UGP_RENAMEROLE   = 2004;
const int IDC_UGP_DELETEROLE   = 2005;
const int IDC_UGP_PROPERTIES   = 2006;
const int IDC_UGP_REFRESHVIEWS = 2007;
const int IDC_UGP_MOVE         = 2008;
const int IDC_UGP_FLATTOOLBAR  = 10005;
const int IDC_UGP_CTRL         = 10006;
const int UM_UGP_ADDGROUP      = 2000;
const int UM_UGP_RENAMEGROUP   = 2001;
const int UM_UGP_DELETEGROUP   = 2002;
const int UM_UGP_ADDROLE       = 2003;
const int UM_UGP_RENAMEROLE    = 2004;
const int UM_UGP_DELETEROLE    = 2005;
const int UM_UGP_PROPERTIES    = 2006;
const int UM_UGP_REFRESH       = 2007;
const int UM_UGP_MOVE          = 2008;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UserGroupView::IUserGroupFlatToolBar, CStatic)
    //{{AFX_MSG_MAP(PSS_UserGroupView::IUserGroupFlatToolBar)
    ON_BN_CLICKED(IDC_UGP_ADDGROUP, OnAddGroupButton)
    ON_BN_CLICKED(IDC_UGP_RENAMEGROUP, OnRenameGroupButton)
    ON_BN_CLICKED(IDC_UGP_DELETEGROUP, OnDeleteGroupButton)
    ON_BN_CLICKED(IDC_UGP_ADDROLE, OnAddRoleButton)
    ON_BN_CLICKED(IDC_UGP_RENAMEROLE, OnRenameRoleButton)
    ON_BN_CLICKED(IDC_UGP_DELETEROLE, OnDeleteRoleButton)
    ON_BN_CLICKED(IDC_UGP_MOVE, OnMoveButton)
    ON_BN_CLICKED(IDC_UGP_PROPERTIES, OnPropertiesButton)
    ON_BN_CLICKED(IDC_UGP_REFRESHVIEWS, OnRefreshButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UserGroupView::IUserGroupFlatToolBar
//---------------------------------------------------------------------------
PSS_UserGroupView::IUserGroupFlatToolBar::IUserGroupFlatToolBar()
{
    m_ImageList.Create(IDB_UGP_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_UserGroupView::IUserGroupFlatToolBar::~IUserGroupFlatToolBar()
{}
//---------------------------------------------------------------------------
void PSS_UserGroupView::IUserGroupFlatToolBar::RefreshButtonNow()
{
    bool       isMessenger = false;
    CFrameWnd* pFrameWnd   = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

    if (pFrameWnd)
    {
        CFrameWnd* pActiveFrame = pFrameWnd->GetActiveFrame();

        if (pActiveFrame)
        {
            PSS_ProcessGraphModelDoc* pProcGraphMdl = dynamic_cast<PSS_ProcessGraphModelDoc*>(pActiveFrame->GetActiveDocument());

            if (pProcGraphMdl && pProcGraphMdl->GetUseWorkflow())
                isMessenger = true;
        }
    }

    // activate or deactivate role button depending on Messenger
    if (isMessenger)
    {
        m_AddRoleButton.EnableWindow(TRUE);
        m_RenameRoleButton.EnableWindow(TRUE);
        m_DeleteRoleButton.EnableWindow(TRUE);
    }
    else
    {
        m_AddRoleButton.EnableWindow(FALSE);
        m_RenameRoleButton.EnableWindow(FALSE);
        m_DeleteRoleButton.EnableWindow(FALSE);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_UserGroupView::IUserGroupFlatToolBar::PreTranslateMessage(MSG* pMsg)
{
    // let the tooltip process this message
    m_ToolTip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::IUserGroupFlatToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}
//---------------------------------------------------------------------------
int PSS_UserGroupView::IUserGroupFlatToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;

    int iconIndex = 0;

    CRect rc;
    GetWindowRect(&rc);
    ScreenToClient(&rc);

    rc.top    += 1;
    rc.bottom -= 1;
    rc.left   += 1;
    rc.right   = rc.left + 24;

    if (!m_RefreshButton.Create(NULL,
                                WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                rc,
                                this,
                                IDC_UGP_REFRESHVIEWS))
    {
        TRACE0("Unable to create refresh button in user group workspace.\n");
        return -1;
    }

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_AddGroupButton.Create(NULL,
                                 WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                 rc,
                                 this,
                                 IDC_UGP_ADDGROUP))
    {
        TRACE0("Unable to create add group button in user group workspace.\n");
        return -1;
    }

    m_AddGroupButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_RenameGroupButton.Create(NULL,
                                    WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                    rc,
                                    this,
                                    IDC_UGP_RENAMEGROUP))
    {
        TRACE0("Unable to create rename group button in user group workspace.\n");
        return -1;
    }

    m_RenameGroupButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_DeleteGroupButton.Create(NULL,
                                    WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                    rc,
                                    this,
                                    IDC_UGP_DELETEGROUP))
    {
        TRACE0("Unable to create delete group button in user group workspace.\n");
        return -1;
    }

    m_DeleteGroupButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_AddRoleButton.Create(NULL,
                                WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                rc,
                                this,
                                IDC_UGP_ADDROLE))
    {
        TRACE0("Unable to create add role button in user group workspace.\n");
        return -1;
    }

    m_AddRoleButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_RenameRoleButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_UGP_RENAMEROLE))
    {
        TRACE0("Unable to create rename role button in user group workspace.\n");
        return -1;
    }

    m_RenameRoleButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_DeleteRoleButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_UGP_DELETEROLE))
    {
        TRACE0("Unable to create delete role button in user group workspace.\n");
        return -1;
    }

    m_DeleteRoleButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_MoveButton.Create(NULL,
                             WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                             rc,
                             this,
                             IDC_UGP_MOVE))
    {
        TRACE0("Unable to create move button in user group workspace.\n");
        return -1;
    }

    m_MoveButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_PropertiesButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_UGP_PROPERTIES))
    {
        TRACE0("Unable to create properties button in user group workspace.\n");
        return -1;
    }

    m_PropertiesButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // create the ToolTip control
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);
    m_ToolTip.AddTool(GetDlgItem(IDC_UGP_ADDGROUP), IDS_UGP_ADDGROUP);
    m_ToolTip.AddTool(GetDlgItem(IDC_UGP_RENAMEGROUP), IDS_UGP_RENAMEGROUP);
    m_ToolTip.AddTool(GetDlgItem(IDC_UGP_DELETEGROUP), IDS_UGP_DELETEGROUP);
    m_ToolTip.AddTool(GetDlgItem(IDC_UGP_ADDROLE), IDS_UGP_ADDROLE);
    m_ToolTip.AddTool(GetDlgItem(IDC_UGP_RENAMEROLE), IDS_UGP_RENAMEROLE);
    m_ToolTip.AddTool(GetDlgItem(IDC_UGP_DELETEROLE), IDS_UGP_DELETEROLE);
    m_ToolTip.AddTool(GetDlgItem(IDC_UGP_PROPERTIES), IDS_UGP_PROPERTIES);
    m_ToolTip.AddTool(GetDlgItem(IDC_UGP_MOVE), IDS_UGP_MOVE);
    m_ToolTip.AddTool(GetDlgItem(IDC_UGP_REFRESHVIEWS), IDS_REFRESH);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::IUserGroupFlatToolBar::OnAddGroupButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_ADDGROUP);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::IUserGroupFlatToolBar::OnRenameGroupButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_RENAMEGROUP);
    NotifyAllObservers(&msg);

    PSS_Application* pApp = PSS_Application::Instance();

    if (pApp)
        pApp->RefreshSelectedSymbolAndProperties();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::IUserGroupFlatToolBar::OnDeleteGroupButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_DELETEGROUP);
    NotifyAllObservers(&msg);

    PSS_Application* pApp = PSS_Application::Instance();

    if (pApp)
        pApp->RefreshSelectedSymbolAndProperties();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::IUserGroupFlatToolBar::OnAddRoleButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_ADDROLE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::IUserGroupFlatToolBar::OnRenameRoleButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_RENAMEROLE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::IUserGroupFlatToolBar::OnDeleteRoleButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_DELETEROLE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::IUserGroupFlatToolBar::OnMoveButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_MOVE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::IUserGroupFlatToolBar::OnPropertiesButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_PROPERTIES);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::IUserGroupFlatToolBar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_REFRESH);
    NotifyAllObservers(&msg);

    bool       isMessenger = false;
    CFrameWnd* pFrameWnd   = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

    if (pFrameWnd)
    {
        CFrameWnd* pActiveFrame = pFrameWnd->GetActiveFrame();

        if (pActiveFrame)
        {
            PSS_ProcessGraphModelDoc* pProcGraphMdl = dynamic_cast<PSS_ProcessGraphModelDoc*>(pActiveFrame->GetActiveDocument());

            if (pProcGraphMdl && pProcGraphMdl->GetUseWorkflow())
                isMessenger = true;
        }
    }

    // activate or deactivate role button depending on Messenger
    if (isMessenger)
    {
        m_AddRoleButton.EnableWindow(TRUE);
        m_RenameRoleButton.EnableWindow(TRUE);
        m_DeleteRoleButton.EnableWindow(TRUE);
    }
    else
    {
        m_AddRoleButton.EnableWindow(FALSE);
        m_RenameRoleButton.EnableWindow(FALSE);
        m_DeleteRoleButton.EnableWindow(FALSE);
    }
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_UserGroupView, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UserGroupView, CWnd)
    //{{AFX_MSG_MAP(PSS_UserGroupView)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UserGroupView
//---------------------------------------------------------------------------
PSS_UserGroupView::PSS_UserGroupView() :
    CWnd(),
    PSS_Subject(),
    PSS_Observer(),
    m_ClrBtnFace(::GetSysColor(COLOR_BTNFACE))
{}
//---------------------------------------------------------------------------
PSS_UserGroupView::~PSS_UserGroupView()
{}
//---------------------------------------------------------------------------
bool PSS_UserGroupView::CanAddGroup()
{
    // can add a new group?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanUgpNewGroup();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupView::CanRenameGroup()
{
    // can rename the selected group?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanUgpRenameGroup();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupView::CanDeleteGroup()
{
    // can delete the selected group?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanUgpDeleteGroup();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupView::CanAddRole()
{
    // can add a new role?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanUgpAddRole();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupView::CanRenameRole()
{
    // can rename the selected role?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanUgpRenameRole();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupView::CanDeleteRole()
{
    // can delete the selected role?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanUgpDeleteRole();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupView::CanMove()
{
    // can delete the selected role?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanUgpMove();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupView::CanProperties()
{
    // can show the properties?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanUgpProperties();

    return false;
}
//---------------------------------------------------------------------------
int PSS_UserGroupView::HasContextMenu(CWnd* pWnd, const CPoint& point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.HasContextMenu(pWnd, point);

    return -1;
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::ShowContextMenu(CWnd* pWnd, const CPoint& point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.ShowContextMenu(pWnd, point);
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnRefresh()
{
    CWaitCursor Cursor;

    // refresh the user group control
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.Refresh();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnExpandBranch()
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnExpandBranch();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnCollapseBranch()
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnCollapseBranch();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnAddGroup()
{
    // add a new group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnUgpNewGroup();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnRenameGroup()
{
    // rename the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnUgpRenameGroup();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnDeleteGroup()
{
    // delete the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnUgpDeleteGroup();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnAddRole()
{
    // add a new role
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnUgpAddRole();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnRenameRole()
{
    // rename the selected role
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnUgpRenameRole();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnDeleteRole()
{
    // delete the selected role
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnUgpDeleteRole();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnMove()
{
    // move a group or a role
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnUgpMove();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnProperties()
{
    // show the properties
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnUgpProperties();
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // forward the message to the property control
    m_Ctrl.OnUpdate(pSubject, pMsg);

    PSS_ToolbarObserverMsg* pToolbarMsg = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

    if (pToolbarMsg)
        switch (pToolbarMsg->GetMessageID())
        {
            case UM_UGP_REFRESH:     OnRefresh();     break;
            case UM_UGP_ADDGROUP:    OnAddGroup();    break;
            case UM_UGP_RENAMEGROUP: OnRenameGroup(); break;
            case UM_UGP_DELETEGROUP: OnDeleteGroup(); break;
            case UM_UGP_ADDROLE:     OnAddRole();     break;
            case UM_UGP_RENAMEROLE:  OnRenameRole();  break;
            case UM_UGP_DELETEROLE:  OnDeleteRole();  break;
            case UM_UGP_MOVE:        OnMove();        break;
            case UM_UGP_PROPERTIES:  OnProperties();  break;
        }

    // update buttons
    m_FlatToolBar.RefreshButtonNow();
}
//---------------------------------------------------------------------------
int PSS_UserGroupView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create the flat toolbar
    static_cast<CStatic&>(m_FlatToolBar).Create(_T(""),
                                                WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                CRect(0, 0, 100, g_FlatToolbarHeight),
                                                this,
                                                IDC_UGP_FLATTOOLBAR);

    // create the user group control
    m_Ctrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS,
                  CRect(0, 0, 0, 0),
                  this,
                  IDC_UGP_CTRL);

    // attach the message observer
    m_FlatToolBar.AttachObserver(this);

    // attach the user group control for notification
    AttachObserver(&m_Ctrl);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, g_FlatToolbarHeight);
        m_Ctrl.MoveWindow(0, g_FlatToolbarHeight + 1, cx, cy - (g_FlatToolbarHeight + 2));
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupView::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);

    // get the control client rect
    CRect rc;
    GetClientRect(&rc);

    // set the background to transparent, and draw a 3D border around the control
    dc.SetBkMode(TRANSPARENT);
    dc.FillSolidRect(rc, m_ClrBtnFace);
}
//---------------------------------------------------------------------------
