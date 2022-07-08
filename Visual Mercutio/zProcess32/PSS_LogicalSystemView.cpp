/****************************************************************************
 * ==> PSS_LogicalSystemView -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a logical system view                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LogicalSystemView.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"

// resources
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int g_FlatLogicalSystemToolbarHeight = 22;
//---------------------------------------------------------------------------
// Global messages
//---------------------------------------------------------------------------
const int IDC_LGS_ADDSYSTEM    = 3000;
const int IDC_LGS_RENAMESYSTEM = 3001;
const int IDC_LGS_DELETESYSTEM = 3002;
const int IDC_LGS_MOVESYSTEM   = 3003;
const int IDC_LGS_PROPERTIES   = 3004;
const int IDC_LGS_REFRESHVIEWS = 3005;
const int IDC_LGS_FLATTOOLBAR  = 11005;
const int IDC_LGS_CTRL         = 11006;
const int UM_LGS_ADDSYSTEM     = 3000;
const int UM_LGS_RENAMESYSTEM  = 3001;
const int UM_LGS_DELETESYSTEM  = 3002;
const int UM_LGS_MOVESYSTEM    = 3003;
const int UM_LGS_PROPERTIES    = 3004;
const int UM_LGS_REFRESH       = 3005;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_LogicalSystemView::ILogicalSystemFlatToolBar, CStatic)
    //{{AFX_MSG_MAP(PSS_LogicalSystemView::ILogicalSystemFlatToolBar)
    ON_BN_CLICKED(IDC_LGS_ADDSYSTEM, OnAddSystemButton)
    ON_BN_CLICKED(IDC_LGS_RENAMESYSTEM, OnRenameSystemButton)
    ON_BN_CLICKED(IDC_LGS_DELETESYSTEM, OnDeleteSystemButton)
    ON_BN_CLICKED(IDC_LGS_MOVESYSTEM, OnMoveSystemButton)
    ON_BN_CLICKED(IDC_LGS_PROPERTIES, OnPropertiesButton)
    ON_BN_CLICKED(IDC_LGS_REFRESHVIEWS, OnRefreshButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_LogicalSystemView::ILogicalSystemFlatToolBar
//---------------------------------------------------------------------------
PSS_LogicalSystemView::ILogicalSystemFlatToolBar::ILogicalSystemFlatToolBar() :
    CStatic(),
    PSS_Subject()
{
    m_ImageList.Create(IDB_LOGICALSYSTEM_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_LogicalSystemView::ILogicalSystemFlatToolBar::~ILogicalSystemFlatToolBar()
{}
//---------------------------------------------------------------------------
BOOL PSS_LogicalSystemView::ILogicalSystemFlatToolBar::PreTranslateMessage(MSG* pMsg)
{
    // let the tooltip process this message
    m_ToolTip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::ILogicalSystemFlatToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}
//---------------------------------------------------------------------------
int PSS_LogicalSystemView::ILogicalSystemFlatToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;

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
                                IDC_LGS_REFRESHVIEWS))
    {
        TRACE0("Unable to create refresh button in system workspace.\n");
        return -1;
    }

    int iconIndex = 0;

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_AddSystemButton.Create(NULL,
                                  WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                  rc,
                                  this,
                                  IDC_LGS_ADDSYSTEM))
    {
        TRACE0("Unable to create add button in system workspace.\n");
        return -1;
    }

    m_AddSystemButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_RenameSystemButton.Create(NULL,
                                     WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                     rc,
                                     this,
                                     IDC_LGS_RENAMESYSTEM))
    {
        TRACE0("Unable to create rename button in system workspace.\n");
        return -1;
    }

    m_RenameSystemButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_DeleteSystemButton.Create(NULL,
                                     WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                     rc,
                                     this,
                                     IDC_LGS_DELETESYSTEM))
    {
        TRACE0("Unable to create delete button in system workspace.\n");
        return -1;
    }

    m_DeleteSystemButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_MoveSystemButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_LGS_MOVESYSTEM))
    {
        TRACE0("Unable to create move button in system workspace.\n");
        return -1;
    }

    m_MoveSystemButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_PropertiesButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_LGS_PROPERTIES))
    {
        TRACE0("Unable to create properties button in system workspace.\n");
        return -1;
    }

    m_PropertiesButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // create the tooltip control
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);
    m_ToolTip.AddTool(GetDlgItem(IDC_LGS_ADDSYSTEM),    IDS_LGS_ADDSYSTEM);
    m_ToolTip.AddTool(GetDlgItem(IDC_LGS_RENAMESYSTEM), IDS_LGS_RENAMESYSTEM);
    m_ToolTip.AddTool(GetDlgItem(IDC_LGS_DELETESYSTEM), IDS_LGS_DELETESYSTEM);
    m_ToolTip.AddTool(GetDlgItem(IDC_LGS_MOVESYSTEM),   IDS_LGS_MOVESYSTEM);
    m_ToolTip.AddTool(GetDlgItem(IDC_LGS_PROPERTIES),   IDS_LGS_PROPERTIES);
    m_ToolTip.AddTool(GetDlgItem(IDC_LGS_REFRESHVIEWS), IDS_REFRESH);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::ILogicalSystemFlatToolBar::OnAddSystemButton()
{
    PSS_ToolbarObserverMsg msg(UM_LGS_ADDSYSTEM);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::ILogicalSystemFlatToolBar::OnRenameSystemButton()
{
    PSS_Application* pApp = PSS_Application::Instance();

    if (!pApp)
        return;

    PSS_ToolbarObserverMsg msg(UM_LGS_RENAMESYSTEM);
    NotifyAllObservers(&msg);

    pApp->RefreshPropertiesWorkspace();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::ILogicalSystemFlatToolBar::OnDeleteSystemButton()
{
    PSS_Application* pApp = PSS_Application::Instance();

    if (!pApp)
        return;

    PSS_ToolbarObserverMsg msg(UM_LGS_DELETESYSTEM);
    NotifyAllObservers(&msg);

    pApp->RefreshPropertiesWorkspace();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::ILogicalSystemFlatToolBar::OnMoveSystemButton()
{
    PSS_ToolbarObserverMsg msg(UM_LGS_MOVESYSTEM);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::ILogicalSystemFlatToolBar::OnPropertiesButton()
{
    PSS_ToolbarObserverMsg msg(UM_LGS_PROPERTIES);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::ILogicalSystemFlatToolBar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg msg(UM_LGS_REFRESH);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_LogicalSystemView, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_LogicalSystemView, CWnd)
    //{{AFX_MSG_MAP(PSS_LogicalSystemView)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_LogicalSystemView
//---------------------------------------------------------------------------
PSS_LogicalSystemView::PSS_LogicalSystemView() :
    CWnd(),
    PSS_Subject(),
    PSS_Observer(),
    m_ClrBtnFace(::GetSysColor(COLOR_BTNFACE))
{}
//---------------------------------------------------------------------------
PSS_LogicalSystemView::~PSS_LogicalSystemView()
{}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::Release()
{
    m_Ctrl.Release();
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemView::CanAddSystem()
{
    // can add a new system?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanNewLogicalSystem();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemView::CanRenameSystem()
{
    // can rename the selected system?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanRenameLogicalSystem();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemView::CanDeleteSystem()
{
    // can delete the selected system?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanDeleteLogicalSystem();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemView::CanProperties()
{
    // can show the properties?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanLogicalSystemProperties();

    return false;
}
//---------------------------------------------------------------------------
int PSS_LogicalSystemView::HasContextMenu(CWnd* pWnd, const CPoint& point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.HasContextMenu(pWnd, point);

    return -1;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::ShowContextMenu(CWnd* pWnd, const CPoint& point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.ShowContextMenu(pWnd, point);
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::OnRefresh()
{
    CWaitCursor cursor;

    // refresh the system control
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.Refresh();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::OnExpandBranch()
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnExpandBranch();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::OnCollapseBranch()
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnCollapseBranch();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::OnAddSystem()
{
    // add a new system
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnNewLogicalSystem();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::OnRenameSystem()
{
    // rename the selected system
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnRenameLogicalSystem();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::OnDeleteSystem()
{
    // delete the selected system
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnDeleteLogicalSystem();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::OnMoveSystem()
{
    // move the selected system
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnMoveLogicalSystem();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::OnProperties()
{
    // show the properties
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnLogicalSystemProperties();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // forward the message to the property control
    m_Ctrl.OnUpdate(pSubject, pMsg);

    PSS_ToolbarObserverMsg* pToolbarMsg = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

    if (pToolbarMsg)
        switch (pToolbarMsg->GetMessageID())
        {
            case UM_LGS_REFRESH:      OnRefresh();      break;
            case UM_LGS_ADDSYSTEM:    OnAddSystem();    break;
            case UM_LGS_RENAMESYSTEM: OnRenameSystem(); break;
            case UM_LGS_DELETESYSTEM: OnDeleteSystem(); break;
            case UM_LGS_MOVESYSTEM:   OnMoveSystem();   break;
            case UM_LGS_PROPERTIES:   OnProperties();   break;
        }
}
//---------------------------------------------------------------------------
int PSS_LogicalSystemView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create the flat toolbar
    static_cast<CStatic&>(m_FlatToolBar).Create(_T(""),
                                                WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                CRect(0, 0, 100, g_FlatLogicalSystemToolbarHeight),
                                                this,
                                                IDC_LGS_FLATTOOLBAR);

    // create the system control
    m_Ctrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS,
                  CRect(0, 0, 0, 0),
                  this,
                  IDC_LGS_CTRL);

    // attach the system control to the observer for notification
    m_FlatToolBar.AttachObserver(this);
    AttachObserver(&m_Ctrl);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, g_FlatLogicalSystemToolbarHeight);
        m_Ctrl.MoveWindow(0,
                          g_FlatLogicalSystemToolbarHeight + 1,
                          cx,
                          cy - (g_FlatLogicalSystemToolbarHeight + 2));
    }
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemView::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);

    // get the client rect for the control
    CRect rc;
    GetClientRect(&rc);

    // set the background to transparent, and draw a 3D border around the control
    dc.SetBkMode(TRANSPARENT);
    dc.FillSolidRect(rc, m_ClrBtnFace);
}
//---------------------------------------------------------------------------
