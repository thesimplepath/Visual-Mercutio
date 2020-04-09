// ******************************************************************************************************************
// *                                  Classes _ZIRulesFlatToolBar et ZVRules                                        *
// ******************************************************************************************************************
// * JMR-MODIF - Le 14 novembre 2006 - Ajout des classes _ZIRulesFlatToolBar et ZVRules.                            *
// ******************************************************************************************************************
// * Ces classes représentent la vue et les boutons utilisés pour représenter l'affichage des règles.                *
// ******************************************************************************************************************

#include "stdafx.h"
#include "ZVRules.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "Resources.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Constant definition
const int _FlatRulesToolbarHeight = 22;

const int IDC_RUL_ADDRULE = 4500;
const int IDC_RUL_RENAMERULE = 4501;
const int IDC_RUL_DELETERULE = 4502;
const int IDC_RUL_MOVERULE = 4503;
const int IDC_RUL_PROPERTIES = 4504;
const int IDC_RUL_REFRESHVIEWS = 4505;

const int UM_RUL_ADDRULE = 4500;
const int UM_RUL_RENAMERULE = 4501;
const int UM_RUL_DELETERULE = 4502;
const int UM_RUL_MOVERULE = 4503;
const int UM_RUL_PROPERTIES = 4504;
const int UM_RUL_REFRESH = 4505;

const int IDC_RUL_FLATTOOLBAR = 13005;
const int IDC_RUL_CTRL = 13006;

/////////////////////////////////////////////////////////////////////////////
// _ZIRulesFlatToolBar

BEGIN_MESSAGE_MAP(_ZIRulesFlatToolBar, CStatic)
    //{{AFX_MSG_MAP(_ZIRulesFlatToolBar)
    ON_BN_CLICKED(IDC_RUL_ADDRULE, OnAddRuleButton)
    ON_BN_CLICKED(IDC_RUL_RENAMERULE, OnRenameRuleButton)
    ON_BN_CLICKED(IDC_RUL_DELETERULE, OnDeleteRuleButton)
    ON_BN_CLICKED(IDC_RUL_MOVERULE, OnMoveRuleButton)
    ON_BN_CLICKED(IDC_RUL_PROPERTIES, OnPropertiesButton)
    ON_BN_CLICKED(IDC_RUL_REFRESHVIEWS, OnRefreshButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZIRulesFlatToolBar::_ZIRulesFlatToolBar()
{
    m_ImageList.Create(IDB_RULES_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}

_ZIRulesFlatToolBar::~_ZIRulesFlatToolBar()
{}

/////////////////////////////////////////////////////////////////////////////
// _ZIRulesFlatToolBar message handlers

int _ZIRulesFlatToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    int IconIndex = 0;

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
                                IDC_RUL_REFRESHVIEWS))
    {
        TRACE0(_T("Unable to create refresh button in Rules workspace.\n"));
        return -1;
    }

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_AddRuleButton.Create(NULL,
                                WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                rc,
                                this,
                                IDC_RUL_ADDRULE))
    {
        TRACE0(_T("Unable to create add button in Rules workspace.\n"));
        return -1;
    }

    m_AddRuleButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_RenameRuleButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_RUL_RENAMERULE))
    {
        TRACE0(_T("Unable to create rename button in Rules workspace.\n"));
        return -1;
    }

    m_RenameRuleButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_DeleteRuleButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_RUL_DELETERULE))
    {
        TRACE0(_T("Unable to create delete button in Rules workspace.\n"));
        return -1;
    }

    m_DeleteRuleButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_MoveRuleButton.Create(NULL,
                                 WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                 rc,
                                 this,
                                 IDC_RUL_MOVERULE))
    {
        TRACE0(_T("Unable to create move button in Rules workspace.\n"));
        return -1;
    }

    m_MoveRuleButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_PropertiesButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_RUL_PROPERTIES))
    {
        TRACE0(_T("Unable to create properties button in Rules workspace.\n"));
        return -1;
    }

    m_PropertiesButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // Create the ToolTip control.
    m_tooltip.Create(this);
    m_tooltip.Activate(TRUE);

    m_tooltip.AddTool(GetDlgItem(IDC_RUL_ADDRULE), IDS_RUL_ADDRULE);
    m_tooltip.AddTool(GetDlgItem(IDC_RUL_RENAMERULE), IDS_RUL_RENAMERULE);
    m_tooltip.AddTool(GetDlgItem(IDC_RUL_DELETERULE), IDS_RUL_DELETERULE);
    m_tooltip.AddTool(GetDlgItem(IDC_RUL_MOVERULE), IDS_RUL_MOVERULE);
    m_tooltip.AddTool(GetDlgItem(IDC_RUL_PROPERTIES), IDS_RUL_PROPERTIES);
    m_tooltip.AddTool(GetDlgItem(IDC_RUL_REFRESHVIEWS), IDS_REFRESH);

    return 0;
}

void _ZIRulesFlatToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}

void _ZIRulesFlatToolBar::OnAddRuleButton()
{
    PSS_ToolbarObserverMsg msg(UM_RUL_ADDRULE);
    NotifyAllObservers(&msg);
}

void _ZIRulesFlatToolBar::OnRenameRuleButton()
{
    PSS_ToolbarObserverMsg msg(UM_RUL_RENAMERULE);
    NotifyAllObservers(&msg);
    PSS_Application::Instance()->RefreshPropertiesWorkspace();
}

void _ZIRulesFlatToolBar::OnDeleteRuleButton()
{
    PSS_ToolbarObserverMsg msg(UM_RUL_DELETERULE);
    NotifyAllObservers(&msg);
    PSS_Application::Instance()->RefreshPropertiesWorkspace();
}

void _ZIRulesFlatToolBar::OnMoveRuleButton()
{
    PSS_ToolbarObserverMsg msg(UM_RUL_MOVERULE);
    NotifyAllObservers(&msg);
}

void _ZIRulesFlatToolBar::OnPropertiesButton()
{
    PSS_ToolbarObserverMsg msg(UM_RUL_PROPERTIES);
    NotifyAllObservers(&msg);
}

void _ZIRulesFlatToolBar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg msg(UM_RUL_REFRESH);
    NotifyAllObservers(&msg);
}

BOOL _ZIRulesFlatToolBar::PreTranslateMessage(MSG* pMsg)
{
    // Let the ToolTip process this message.
    m_tooltip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// ZVRules

IMPLEMENT_DYNCREATE(ZVRules, CWnd)

BEGIN_MESSAGE_MAP(ZVRules, CWnd)
    //{{AFX_MSG_MAP(ZVRules)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVRules::ZVRules()
{
    m_clrBtnFace = ::GetSysColor(COLOR_BTNFACE);
}

ZVRules::~ZVRules()
{}

// JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release pour permettre un nettoyage de la mémoire.
void ZVRules::Release()
{
    m_Ctrl.Release();
}

void ZVRules::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // Forward the message to the property control
    m_Ctrl.OnUpdate(pSubject, pMsg);

    if (pMsg && ISA(pMsg, PSS_ToolbarObserverMsg))
    {
        switch (dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg)->GetMessageID())
        {
            case UM_RUL_REFRESH:
            {
                OnRefresh();
                break;
            }

            case UM_RUL_ADDRULE:
            {
                OnAddRule();
                break;
            }

            case UM_RUL_RENAMERULE:
            {
                OnRenameRule();
                break;
            }

            case UM_RUL_DELETERULE:
            {
                OnDeleteRule();
                break;
            }

            case UM_RUL_MOVERULE:
            {
                OnMoveRule();
                break;
            }

            case UM_RUL_PROPERTIES:
            {
                OnProperties();
                break;
            }
        }
    }
}

int ZVRules::HasContextMenu(CWnd* pWnd, CPoint point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.HasContextMenu(pWnd, point);
    }

    return -1;
}

void ZVRules::DisplayContextMenu(CWnd* pWnd, CPoint point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.ShowContextMenu(pWnd, point);
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZVRules message handlers

int ZVRules::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    // Create the flat toolbar
    reinterpret_cast<CStatic&>(m_FlatToolBar).Create(_T(""),
                                                     WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                     CRect(0, 0, 100,
                                                           _FlatRulesToolbarHeight),
                                                     this,
                                                     IDC_RUL_FLATTOOLBAR);

    // Create the user group control
    m_Ctrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS,
                  CRect(0, 0, 0, 0),
                  this,
                  IDC_RUL_CTRL);

    // Attach us as an observer for messages
    m_FlatToolBar.AttachObserver(this);

    // Attach the user group control for notification
    AttachObserver(&m_Ctrl);

    return 0;
}

void ZVRules::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, _FlatRulesToolbarHeight);
        m_Ctrl.MoveWindow(0, _FlatRulesToolbarHeight + 1, cx, cy - (_FlatRulesToolbarHeight + 2));
    }
}

void ZVRules::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    // Get the client rect for this control.
    CRect rc;
    GetClientRect(&rc);

    // Set the background to transparent, and draw a 3D
    // border around the control.
    dc.SetBkMode(TRANSPARENT);
    dc.FillSolidRect(rc, m_clrBtnFace);
}

/////////////////////////////////////////////////////////////////////////////
// ZVRules message handlers from toolbar

void ZVRules::OnRefresh()
{
    CWaitCursor Cursor;

    // Refresh the user group control
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.Refresh();
    }
}

void ZVRules::OnAddRule()
{
    // Add a new group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnNewRule();
    }
}

void ZVRules::OnRenameRule()
{
    // Rename the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnRenameRule();
    }
}

void ZVRules::OnDeleteRule()
{
    // Delete the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnDeleteRule();
    }
}

void ZVRules::OnMoveRule()
{
    // Delete the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnMoveRule();
    }
}

void ZVRules::OnProperties()
{
    // Display the properties
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnRuleProperties();
    }
}

bool ZVRules::CanAddRule()
{
    // Can Add a new group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanNewRule();
    }

    return false;
}

bool ZVRules::CanRenameRule()
{
    // Can Rename the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanRenameRule();
    }

    return false;
}

bool ZVRules::CanDeleteRule()
{
    // Can Delete the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanDeleteRule();
    }

    return false;
}

bool ZVRules::CanProperties()
{
    // Can Display the properties
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanRuleProperties();
    }

    return false;
}
