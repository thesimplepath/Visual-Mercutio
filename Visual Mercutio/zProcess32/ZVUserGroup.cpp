/////////////////////////////////////////////////////////////////////////////
//@doc ZVUserGroup
//@module ZVUserGroup.cpp | Implementation of the <c ZVUserGroup> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 05/2001
// 
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ZVUserGroup.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Constant definition
const int _FlatToolbarHeight = 22;

const int IDC_UGP_ADDGROUP = 2000;
const int IDC_UGP_RENAMEGROUP = 2001;
const int IDC_UGP_DELETEGROUP = 2002;
const int IDC_UGP_ADDROLE = 2003;
const int IDC_UGP_RENAMEROLE = 2004;
const int IDC_UGP_DELETEROLE = 2005;
const int IDC_UGP_PROPERTIES = 2006;
const int IDC_UGP_REFRESHVIEWS = 2007;
const int IDC_UGP_MOVE = 2008;

const int UM_UGP_ADDGROUP = 2000;
const int UM_UGP_RENAMEGROUP = 2001;
const int UM_UGP_DELETEGROUP = 2002;
const int UM_UGP_ADDROLE = 2003;
const int UM_UGP_RENAMEROLE = 2004;
const int UM_UGP_DELETEROLE = 2005;
const int UM_UGP_PROPERTIES = 2006;
const int UM_UGP_REFRESH = 2007;
const int UM_UGP_MOVE = 2008;

const int IDC_UGP_FLATTOOLBAR = 10005;
const int IDC_UGP_CTRL = 10006;

/////////////////////////////////////////////////////////////////////////////
// _ZIUserGroupFlatToolBar

BEGIN_MESSAGE_MAP(_ZIUserGroupFlatToolBar, CStatic)
    //{{AFX_MSG_MAP(_ZIUserGroupFlatToolBar)
    ON_BN_CLICKED(IDC_UGP_ADDGROUP, OnAddGroupButton)
    ON_BN_CLICKED(IDC_UGP_RENAMEGROUP, OnRenameGroupButton)
    ON_BN_CLICKED(IDC_UGP_DELETEGROUP, OnDeleteGroupButton)
    ON_BN_CLICKED(IDC_UGP_ADDROLE, OnAddRoleButton)
    ON_BN_CLICKED(IDC_UGP_RENAMEROLE, OnRenameRoleButton)
    ON_BN_CLICKED(IDC_UGP_DELETEROLE, OnDeleteRoleButton)
    ON_BN_CLICKED(IDC_UGP_PROPERTIES, OnPropertiesButton)
    ON_BN_CLICKED(IDC_UGP_REFRESHVIEWS, OnRefreshButton)
    ON_BN_CLICKED(IDC_UGP_MOVE, OnMoveButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZIUserGroupFlatToolBar::_ZIUserGroupFlatToolBar()
{
    m_ImageList.Create(IDB_UGP_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}

_ZIUserGroupFlatToolBar::~_ZIUserGroupFlatToolBar()
{}

/////////////////////////////////////////////////////////////////////////////
// _ZIUserGroupFlatToolBar message handlers

int _ZIUserGroupFlatToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    int    IconIndex = 0;

    CRect rc;
    GetWindowRect(&rc);
    ScreenToClient(&rc);

    rc.top += 1;
    rc.bottom -= 1;
    rc.left += 1;
    rc.right = rc.left + 24;

    if (!m_RefreshButton.Create(NULL,
                                WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                rc,
                                this,
                                IDC_UGP_REFRESHVIEWS))
    {
        TRACE0(_T("Unable to create refresh button in user group workspace.\n"));
        return -1;
    }

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_AddGroupButton.Create(NULL,
                                 WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                 rc,
                                 this,
                                 IDC_UGP_ADDGROUP))
    {
        TRACE0(_T("Unable to create add group button in user group workspace.\n"));
        return -1;
    }

    m_AddGroupButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_RenameGroupButton.Create(NULL,
                                    WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                    rc,
                                    this,
                                    IDC_UGP_RENAMEGROUP))
    {
        TRACE0(_T("Unable to create rename group button in user group workspace.\n"));
        return -1;
    }

    m_RenameGroupButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_DeleteGroupButton.Create(NULL,
                                    WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                    rc,
                                    this,
                                    IDC_UGP_DELETEGROUP))
    {
        TRACE0(_T("Unable to create delete group button in user group workspace.\n"));
        return -1;
    }

    m_DeleteGroupButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_AddRoleButton.Create(NULL,
                                WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                rc,
                                this,
                                IDC_UGP_ADDROLE))
    {
        TRACE0(_T("Unable to create add role button in user group workspace.\n"));
        return -1;
    }

    m_AddRoleButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_RenameRoleButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_UGP_RENAMEROLE))
    {
        TRACE0(_T("Unable to create rename role button in user group workspace.\n"));
        return -1;
    }

    m_RenameRoleButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_DeleteRoleButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_UGP_DELETEROLE))
    {
        TRACE0(_T("Unable to create delete role button in user group workspace.\n"));
        return -1;
    }

    m_DeleteRoleButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_MoveButton.Create(NULL,
                             WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                             rc,
                             this,
                             IDC_UGP_MOVE))
    {
        TRACE0(_T("Unable to create move button in user group workspace.\n"));
        return -1;
    }

    m_MoveButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_PropertiesButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_UGP_PROPERTIES))
    {
        TRACE0(_T("Unable to create properties button in user group workspace.\n"));
        return -1;
    }

    m_PropertiesButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // Create the ToolTip control.
    m_tooltip.Create(this);
    m_tooltip.Activate(TRUE);

    m_tooltip.AddTool(GetDlgItem(IDC_UGP_ADDGROUP), IDS_UGP_ADDGROUP);
    m_tooltip.AddTool(GetDlgItem(IDC_UGP_RENAMEGROUP), IDS_UGP_RENAMEGROUP);
    m_tooltip.AddTool(GetDlgItem(IDC_UGP_DELETEGROUP), IDS_UGP_DELETEGROUP);
    m_tooltip.AddTool(GetDlgItem(IDC_UGP_ADDROLE), IDS_UGP_ADDROLE);
    m_tooltip.AddTool(GetDlgItem(IDC_UGP_RENAMEROLE), IDS_UGP_RENAMEROLE);
    m_tooltip.AddTool(GetDlgItem(IDC_UGP_DELETEROLE), IDS_UGP_DELETEROLE);
    m_tooltip.AddTool(GetDlgItem(IDC_UGP_PROPERTIES), IDS_UGP_PROPERTIES);
    m_tooltip.AddTool(GetDlgItem(IDC_UGP_MOVE), IDS_UGP_MOVE);
    m_tooltip.AddTool(GetDlgItem(IDC_UGP_REFRESHVIEWS), IDS_REFRESH);

    return 0;
}

void _ZIUserGroupFlatToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}

void _ZIUserGroupFlatToolBar::OnAddGroupButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_ADDGROUP);
    NotifyAllObservers(&msg);
}

void _ZIUserGroupFlatToolBar::OnRenameGroupButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_RENAMEGROUP);
    NotifyAllObservers(&msg);
    PSS_Application::Instance()->RefreshSelectedSymbolAndProperties();
}

void _ZIUserGroupFlatToolBar::OnDeleteGroupButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_DELETEGROUP);
    NotifyAllObservers(&msg);
    PSS_Application::Instance()->RefreshSelectedSymbolAndProperties();
}

void _ZIUserGroupFlatToolBar::OnAddRoleButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_ADDROLE);
    NotifyAllObservers(&msg);
}

void _ZIUserGroupFlatToolBar::OnRenameRoleButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_RENAMEROLE);
    NotifyAllObservers(&msg);
}

void _ZIUserGroupFlatToolBar::OnDeleteRoleButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_DELETEROLE);
    NotifyAllObservers(&msg);
}

void _ZIUserGroupFlatToolBar::OnPropertiesButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_PROPERTIES);
    NotifyAllObservers(&msg);
}

void _ZIUserGroupFlatToolBar::OnMoveButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_MOVE);
    NotifyAllObservers(&msg);
}

void _ZIUserGroupFlatToolBar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg msg(UM_UGP_REFRESH);
    NotifyAllObservers(&msg);

    // RS-MODIF 20.12.04 activate or deactivate role button depends on Messenger
    bool IsMessenger = false;

    PSS_ProcessGraphModelDoc* test =
        (PSS_ProcessGraphModelDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

    if (test != NULL)
    {
        if (test->GetUseWorkflow())
        {
            IsMessenger = true;
        }
    }

    if (IsMessenger)
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

void _ZIUserGroupFlatToolBar::RefreshButtonNow()
{
    // RS-MODIF 20.12.04 activate or deactivate role button depends on Messenger
    bool IsMessenger = false;

    PSS_ProcessGraphModelDoc* test =
        (PSS_ProcessGraphModelDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

    if (test != NULL)
    {
        if (test->GetUseWorkflow())
        {
            IsMessenger = true;
        }
    }

    if (IsMessenger)
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

BOOL _ZIUserGroupFlatToolBar::PreTranslateMessage(MSG* pMsg)
{
    // Let the ToolTip process this message.
    m_tooltip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// ZVUserGroup

IMPLEMENT_DYNCREATE(ZVUserGroup, CWnd)

BEGIN_MESSAGE_MAP(ZVUserGroup, CWnd)
    //{{AFX_MSG_MAP(ZVUserGroup)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVUserGroup::ZVUserGroup()
{
    m_clrBtnFace = ::GetSysColor(COLOR_BTNFACE);
}

ZVUserGroup::~ZVUserGroup()
{}

void ZVUserGroup::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // Forward the message to the property control
    m_Ctrl.OnUpdate(pSubject, pMsg);

    if (pMsg && ISA(pMsg, PSS_ToolbarObserverMsg))
    {
        switch (dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg)->GetMessageID())
        {
            case UM_UGP_REFRESH:
            {
                OnRefresh();
                break;
            }

            case UM_UGP_ADDGROUP:
            {
                OnAddGroup();
                break;
            }

            case UM_UGP_RENAMEGROUP:
            {
                OnRenameGroup();
                break;
            }

            case UM_UGP_DELETEGROUP:
            {
                OnDeleteGroup();
                break;
            }

            case UM_UGP_ADDROLE:
            {
                OnAddRole();
                break;
            }

            case UM_UGP_RENAMEROLE:
            {
                OnRenameRole();
                break;
            }

            case UM_UGP_DELETEROLE:
            {
                OnDeleteRole();
                break;
            }

            case UM_UGP_MOVE:
            {
                OnMove();
                break;
            }

            case UM_UGP_PROPERTIES:
            {
                OnProperties();
                break;
            }
        }
    }

    // RS-MODIF 20.12.04 update buttons
    m_FlatToolBar.RefreshButtonNow();
}

int ZVUserGroup::HasContextMenu(CWnd* pWnd, CPoint point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.HasContextMenu(pWnd, point);
    }

    return -1;
}

void ZVUserGroup::DisplayContextMenu(CWnd* pWnd, CPoint point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.ShowContextMenu(pWnd, point);
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZVUserGroup message handlers


int ZVUserGroup::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    // Create the flat toolbar
    reinterpret_cast<CStatic&>(m_FlatToolBar).Create(_T(""),
                                                     WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                     CRect(0, 0, 100, _FlatToolbarHeight),
                                                     this,
                                                     IDC_UGP_FLATTOOLBAR);

    // Create the user group control
    m_Ctrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS,
                  CRect(0, 0, 0, 0),
                  this,
                  IDC_UGP_CTRL);

    // Attach us as an observer for messages
    m_FlatToolBar.AttachObserver(this);

    // Attach the user group control for notification
    AttachObserver(&m_Ctrl);

    return 0;
}

void ZVUserGroup::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, _FlatToolbarHeight);
        m_Ctrl.MoveWindow(0, _FlatToolbarHeight + 1, cx, cy - (_FlatToolbarHeight + 2));
    }
}

void ZVUserGroup::OnPaint()
{
    // Device context for painting
    CPaintDC dc(this);

    // Get the client rect for this control.
    CRect rc;
    GetClientRect(&rc);

    // Set the background to transparent, and draw a 3D
    // border around the control.
    dc.SetBkMode(TRANSPARENT);
    dc.FillSolidRect(rc, m_clrBtnFace);
}

/////////////////////////////////////////////////////////////////////////////
// ZVUserGroup message handlers from toolbar

void ZVUserGroup::OnRefresh()
{
    CWaitCursor Cursor;

    // Refresh the user group control
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.Refresh();
    }
}

void ZVUserGroup::OnAddGroup()
{
    // Add a new group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnUgpNewGroup();
    }
}

void ZVUserGroup::OnRenameGroup()
{
    // Rename the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnUgpRenameGroup();
    }
}

void ZVUserGroup::OnDeleteGroup()
{
    // Delete the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnUgpDeleteGroup();
    }
}

void ZVUserGroup::OnAddRole()
{
    // Add a new role
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnUgpAddRole();
    }
}

void ZVUserGroup::OnRenameRole()
{
    // Rename the selected role
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnUgpRenameRole();
    }
}

void ZVUserGroup::OnDeleteRole()
{
    // Delete the selected role
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnUgpDeleteRole();
    }
}

void ZVUserGroup::OnMove()
{
    // Move a group or a role
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnUgpMove();
    }
}

void ZVUserGroup::OnProperties()
{
    // Display the properties
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnUgpProperties();
    }
}

bool ZVUserGroup::CanAddGroup()
{
    // Can Add a new group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanUgpNewGroup();
    }

    return false;
}

bool ZVUserGroup::CanRenameGroup()
{
    // Can Rename the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanUgpRenameGroup();
    }

    return false;
}

bool ZVUserGroup::CanDeleteGroup()
{
    // Can Delete the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanUgpDeleteGroup();
    }

    return false;
}

bool ZVUserGroup::CanAddRole()
{
    // Can Add a new role
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanUgpAddRole();
    }

    return false;
}

bool ZVUserGroup::CanRenameRole()
{
    // Can Rename the selected role
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanUgpRenameRole();
    }

    return false;
}

bool ZVUserGroup::CanDeleteRole()
{
    // Can Delete the selected role
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanUgpDeleteRole();
    }

    return false;
}

bool ZVUserGroup::CanMove()
{
    // Can Delete the selected role
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanUgpMove();
    }

    return false;
}

bool ZVUserGroup::CanProperties()
{
    // Can Display the properties
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanUgpProperties();
    }

    return false;
}
