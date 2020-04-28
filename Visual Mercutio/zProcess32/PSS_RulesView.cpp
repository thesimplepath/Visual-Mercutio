/****************************************************************************
 * ==> PSS_RulesView -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a rules view                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RulesView.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"

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
const int g_FlatRulesToolbarHeight = 22;
//---------------------------------------------------------------------------
// Message constants
//---------------------------------------------------------------------------
const int IDC_RUL_ADDRULE      = 4500;
const int IDC_RUL_RENAMERULE   = 4501;
const int IDC_RUL_DELETERULE   = 4502;
const int IDC_RUL_MOVERULE     = 4503;
const int IDC_RUL_PROPERTIES   = 4504;
const int IDC_RUL_REFRESHVIEWS = 4505;
const int IDC_RUL_FLATTOOLBAR  = 13005;
const int IDC_RUL_CTRL         = 13006;
const int UM_RUL_ADDRULE       = 4500;
const int UM_RUL_RENAMERULE    = 4501;
const int UM_RUL_DELETERULE    = 4502;
const int UM_RUL_MOVERULE      = 4503;
const int UM_RUL_PROPERTIES    = 4504;
const int UM_RUL_REFRESH       = 4505;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_RulesView::IRulesFlatToolBar, CStatic)
    //{{AFX_MSG_MAP(PSS_RulesView::IRulesFlatToolBar)
    ON_BN_CLICKED(IDC_RUL_ADDRULE, OnAddRuleButton)
    ON_BN_CLICKED(IDC_RUL_RENAMERULE, OnRenameRuleButton)
    ON_BN_CLICKED(IDC_RUL_DELETERULE, OnDeleteRuleButton)
    ON_BN_CLICKED(IDC_RUL_MOVERULE, OnMoveRuleButton)
    ON_BN_CLICKED(IDC_RUL_PROPERTIES, OnPropertiesButton)
    ON_BN_CLICKED(IDC_RUL_REFRESHVIEWS, OnRefreshButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_RulesView::IRulesFlatToolBar
//---------------------------------------------------------------------------
PSS_RulesView::IRulesFlatToolBar::IRulesFlatToolBar()
{
    m_ImageList.Create(IDB_RULES_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_RulesView::IRulesFlatToolBar::~IRulesFlatToolBar()
{}
//---------------------------------------------------------------------------
BOOL PSS_RulesView::IRulesFlatToolBar::PreTranslateMessage(MSG* pMsg)
{
    // let the tooltip process this message
    m_ToolTip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_RulesView::IRulesFlatToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}
//---------------------------------------------------------------------------
int PSS_RulesView::IRulesFlatToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
                                IDC_RUL_REFRESHVIEWS))
    {
        TRACE0("Unable to create refresh button in Rules workspace.\n");
        return -1;
    }

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_AddRuleButton.Create(NULL,
                                WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                rc,
                                this,
                                IDC_RUL_ADDRULE))
    {
        TRACE0("Unable to create add button in Rules workspace.\n");
        return -1;
    }

    m_AddRuleButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_RenameRuleButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_RUL_RENAMERULE))
    {
        TRACE0("Unable to create rename button in Rules workspace.\n");
        return -1;
    }

    m_RenameRuleButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_DeleteRuleButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_RUL_DELETERULE))
    {
        TRACE0("Unable to create delete button in Rules workspace.\n");
        return -1;
    }

    m_DeleteRuleButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_MoveRuleButton.Create(NULL,
                                 WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                 rc,
                                 this,
                                 IDC_RUL_MOVERULE))
    {
        TRACE0("Unable to create move button in Rules workspace.\n");
        return -1;
    }

    m_MoveRuleButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_PropertiesButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_RUL_PROPERTIES))
    {
        TRACE0("Unable to create properties button in Rules workspace.\n");
        return -1;
    }

    m_PropertiesButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // create the tooltip control
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);
    m_ToolTip.AddTool(GetDlgItem(IDC_RUL_ADDRULE),      IDS_RUL_ADDRULE);
    m_ToolTip.AddTool(GetDlgItem(IDC_RUL_RENAMERULE),   IDS_RUL_RENAMERULE);
    m_ToolTip.AddTool(GetDlgItem(IDC_RUL_DELETERULE),   IDS_RUL_DELETERULE);
    m_ToolTip.AddTool(GetDlgItem(IDC_RUL_MOVERULE),     IDS_RUL_MOVERULE);
    m_ToolTip.AddTool(GetDlgItem(IDC_RUL_PROPERTIES),   IDS_RUL_PROPERTIES);
    m_ToolTip.AddTool(GetDlgItem(IDC_RUL_REFRESHVIEWS), IDS_REFRESH);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_RulesView::IRulesFlatToolBar::OnAddRuleButton()
{
    PSS_ToolbarObserverMsg msg(UM_RUL_ADDRULE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_RulesView::IRulesFlatToolBar::OnRenameRuleButton()
{
    PSS_ToolbarObserverMsg msg(UM_RUL_RENAMERULE);
    NotifyAllObservers(&msg);

    PSS_Application* pApp = PSS_Application::Instance();

    if (pApp)
        pApp->RefreshPropertiesWorkspace();
}
//---------------------------------------------------------------------------
void PSS_RulesView::IRulesFlatToolBar::OnDeleteRuleButton()
{
    PSS_ToolbarObserverMsg msg(UM_RUL_DELETERULE);
    NotifyAllObservers(&msg);

    PSS_Application* pApp = PSS_Application::Instance();

    if (pApp)
        pApp->RefreshPropertiesWorkspace();
}
//---------------------------------------------------------------------------
void PSS_RulesView::IRulesFlatToolBar::OnMoveRuleButton()
{
    PSS_ToolbarObserverMsg msg(UM_RUL_MOVERULE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_RulesView::IRulesFlatToolBar::OnPropertiesButton()
{
    PSS_ToolbarObserverMsg msg(UM_RUL_PROPERTIES);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_RulesView::IRulesFlatToolBar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg msg(UM_RUL_REFRESH);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_RulesView, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_RulesView, CWnd)
    //{{AFX_MSG_MAP(PSS_RulesView)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_RulesView
//---------------------------------------------------------------------------
PSS_RulesView::PSS_RulesView() :
    CWnd(),
    PSS_Subject(),
    PSS_Observer(),
    m_ClrBtnFace(::GetSysColor(COLOR_BTNFACE))
{}
//---------------------------------------------------------------------------
PSS_RulesView::~PSS_RulesView()
{}
//---------------------------------------------------------------------------
void PSS_RulesView::Release()
{
    m_Ctrl.Release();
}
//---------------------------------------------------------------------------
bool PSS_RulesView::CanAddRule()
{
    // can add a new group?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanNewRule();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_RulesView::CanRenameRule()
{
    // can rename the selected group?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanRenameRule();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_RulesView::CanDeleteRule()
{
    // can delete the selected group?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanDeleteRule();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_RulesView::CanProperties()
{
    // can show the properties
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanRuleProperties();

    return false;
}
//---------------------------------------------------------------------------
int PSS_RulesView::HasContextMenu(CWnd* pWnd, const CPoint& point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.HasContextMenu(pWnd, point);

    return -1;
}
//---------------------------------------------------------------------------
void PSS_RulesView::ShowContextMenu(CWnd* pWnd, const CPoint& point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.ShowContextMenu(pWnd, point);
}
//---------------------------------------------------------------------------
void PSS_RulesView::OnRefresh()
{
    CWaitCursor cursor;

    // refresh the rules control
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.Refresh();
}
//---------------------------------------------------------------------------
void PSS_RulesView::OnAddRule()
{
    // add a new rule
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnNewRule();
}
//---------------------------------------------------------------------------
void PSS_RulesView::OnRenameRule()
{
    // rename the selected rule
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnRenameRule();
}
//---------------------------------------------------------------------------
void PSS_RulesView::OnDeleteRule()
{
    // delete the selected rule
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnDeleteRule();
}
//---------------------------------------------------------------------------
void PSS_RulesView::OnMoveRule()
{
    // move the selected rule
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnMoveRule();
}
//---------------------------------------------------------------------------
void PSS_RulesView::OnProperties()
{
    // show the properties
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnRuleProperties();
}
//---------------------------------------------------------------------------
void PSS_RulesView::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // forward the message to the property control
    m_Ctrl.OnUpdate(pSubject, pMsg);

    PSS_ToolbarObserverMsg* pToolbarMsg = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

    if (pToolbarMsg)
        switch (pToolbarMsg->GetMessageID())
        {
            case UM_RUL_REFRESH:    OnRefresh();    break;
            case UM_RUL_ADDRULE:    OnAddRule();    break;
            case UM_RUL_RENAMERULE: OnRenameRule(); break;
            case UM_RUL_DELETERULE: OnDeleteRule(); break;
            case UM_RUL_MOVERULE:   OnMoveRule();   break;
            case UM_RUL_PROPERTIES: OnProperties(); break;
        }
}
//---------------------------------------------------------------------------
int PSS_RulesView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create the flat toolbar
    static_cast<CStatic&>(m_FlatToolBar).Create(_T(""),
                                                WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                CRect(0, 0, 100, g_FlatRulesToolbarHeight),
                                                this,
                                                IDC_RUL_FLATTOOLBAR);

    // create the user group control
    m_Ctrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS,
                  CRect(0, 0, 0, 0),
                  this,
                  IDC_RUL_CTRL);

    // attach us as an observer for messages
    m_FlatToolBar.AttachObserver(this);

    // attach the user group control for notification
    AttachObserver(&m_Ctrl);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_RulesView::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, g_FlatRulesToolbarHeight);
        m_Ctrl.MoveWindow(0, g_FlatRulesToolbarHeight + 1, cx, cy - (g_FlatRulesToolbarHeight + 2));
    }
}
//---------------------------------------------------------------------------
void PSS_RulesView::OnPaint()
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
