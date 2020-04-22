/****************************************************************************
 * ==> PSS_PrestationsView -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a prestations view                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PrestationsView.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "Resources.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global constant
//---------------------------------------------------------------------------
const int g_FlatPrestationsToolbarHeight = 22;
//---------------------------------------------------------------------------
// Global messages
//---------------------------------------------------------------------------
const int IDC_PRS_ADDPRESTATION    = 4000;
const int IDC_PRS_RENAMEPRESTATION = 4001;
const int IDC_PRS_DELETEPRESTATION = 4002;
const int IDC_PRS_MOVEPRESTATION   = 4003;
const int IDC_PRS_PROPERTIES       = 4004;
const int IDC_PRS_REFRESHVIEWS     = 4005;
const int IDC_PRS_FLATTOOLBAR      = 12005;
const int IDC_PRS_CTRL             = 12006;
const int UM_PRS_ADDPRESTATION     = 4000;
const int UM_PRS_RENAMEPRESTATION  = 4001;
const int UM_PRS_DELETEPRESTATION  = 4002;
const int UM_PRS_MOVEPRESTATION    = 4003;
const int UM_PRS_PROPERTIES        = 4004;
const int UM_PRS_REFRESH           = 4005;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PrestationsView::IPrestationsFlatToolBar, CStatic)
    //{{AFX_MSG_MAP(PSS_PrestationsView::IPrestationsFlatToolBar)
    ON_BN_CLICKED(IDC_PRS_ADDPRESTATION, OnAddPrestationButton)
    ON_BN_CLICKED(IDC_PRS_RENAMEPRESTATION, OnRenamePrestationButton)
    ON_BN_CLICKED(IDC_PRS_DELETEPRESTATION, OnDeletePrestationButton)
    ON_BN_CLICKED(IDC_PRS_MOVEPRESTATION, OnMovePrestationButton)
    ON_BN_CLICKED(IDC_PRS_PROPERTIES, OnPropertiesButton)
    ON_BN_CLICKED(IDC_PRS_REFRESHVIEWS, OnRefreshButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PrestationsView::IPrestationsFlatToolBar
//---------------------------------------------------------------------------
PSS_PrestationsView::IPrestationsFlatToolBar::IPrestationsFlatToolBar() :
    CStatic(),
    PSS_Subject()
{
    m_ImageList.Create(IDB_PRESTATIONS_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_PrestationsView::IPrestationsFlatToolBar::~IPrestationsFlatToolBar()
{}
//---------------------------------------------------------------------------
BOOL PSS_PrestationsView::IPrestationsFlatToolBar::PreTranslateMessage(MSG* pMsg)
{
    // let the tooltip process this message
    m_ToolTip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::IPrestationsFlatToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}
//---------------------------------------------------------------------------
int PSS_PrestationsView::IPrestationsFlatToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
                                IDC_PRS_REFRESHVIEWS))
    {
        TRACE0(_T("Unable to create refresh button in prestations workspace.\n"));
        return -1;
    }

    int iconIndex = 0;

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_AddPrestationButton.Create(NULL,
                                      WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                      rc,
                                      this,
                                      IDC_PRS_ADDPRESTATION))
    {
        TRACE0(_T("Unable to create add button in prestations workspace.\n"));
        return -1;
    }

    m_AddPrestationButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_RenamePrestationButton.Create(NULL,
                                         WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                         rc,
                                         this,
                                         IDC_PRS_RENAMEPRESTATION))
    {
        TRACE0(_T("Unable to create rename button in prestations workspace.\n"));
        return -1;
    }

    m_RenamePrestationButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_DeletePrestationButton.Create(NULL,
                                         WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                         rc,
                                         this,
                                         IDC_PRS_DELETEPRESTATION))
    {
        TRACE0(_T("Unable to create delete button in prestations workspace.\n"));
        return -1;
    }

    m_DeletePrestationButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_MovePrestationButton.Create(NULL,
                                       WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                       rc,
                                       this,
                                       IDC_PRS_MOVEPRESTATION))
    {
        TRACE0(_T("Unable to create move button in prestations workspace.\n"));
        return -1;
    }

    m_MovePrestationButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_PropertiesButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_PRS_PROPERTIES))
    {
        TRACE0(_T("Unable to create properties button in prestations workspace.\n"));
        return -1;
    }

    m_PropertiesButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // create the tooltip control
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PRS_ADDPRESTATION),    IDS_PRS_ADDPRESTATION);
    m_ToolTip.AddTool(GetDlgItem(IDC_PRS_RENAMEPRESTATION), IDS_PRS_RENAMEPRESTATION);
    m_ToolTip.AddTool(GetDlgItem(IDC_PRS_DELETEPRESTATION), IDS_PRS_DELETEPRESTATION);
    m_ToolTip.AddTool(GetDlgItem(IDC_PRS_MOVEPRESTATION),   IDS_PRS_MOVEPRESTATION);
    m_ToolTip.AddTool(GetDlgItem(IDC_PRS_PROPERTIES),       IDS_PRS_PROPERTIES);
    m_ToolTip.AddTool(GetDlgItem(IDC_PRS_REFRESHVIEWS),     IDS_REFRESH);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::IPrestationsFlatToolBar::OnAddPrestationButton()
{
    PSS_ToolbarObserverMsg msg(UM_PRS_ADDPRESTATION);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::IPrestationsFlatToolBar::OnRenamePrestationButton()
{
    PSS_Application* pApp = PSS_Application::Instance();

    if (!pApp)
        return;

    PSS_ToolbarObserverMsg msg(UM_PRS_RENAMEPRESTATION);
    NotifyAllObservers(&msg);

    pApp->RefreshPropertiesWorkspace();
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::IPrestationsFlatToolBar::OnDeletePrestationButton()
{
    PSS_Application* pApp = PSS_Application::Instance();

    if (!pApp)
        return;

    PSS_ToolbarObserverMsg msg(UM_PRS_DELETEPRESTATION);
    NotifyAllObservers(&msg);

    pApp->RefreshPropertiesWorkspace();
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::IPrestationsFlatToolBar::OnMovePrestationButton()
{
    PSS_ToolbarObserverMsg msg(UM_PRS_MOVEPRESTATION);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::IPrestationsFlatToolBar::OnPropertiesButton()
{
    PSS_ToolbarObserverMsg msg(UM_PRS_PROPERTIES);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::IPrestationsFlatToolBar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg msg(UM_PRS_REFRESH);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_PrestationsView, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PrestationsView, CWnd)
    //{{AFX_MSG_MAP(PSS_PrestationsView)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PrestationsView
//---------------------------------------------------------------------------
PSS_PrestationsView::PSS_PrestationsView() :
    CWnd(),
    PSS_Subject(),
    PSS_Observer(),
    m_ClrBtnFace(::GetSysColor(COLOR_BTNFACE))
{}
//---------------------------------------------------------------------------
PSS_PrestationsView::~PSS_PrestationsView()
{}
//---------------------------------------------------------------------------
void PSS_PrestationsView::Release()
{
    m_Ctrl.Release();
}
//---------------------------------------------------------------------------
bool PSS_PrestationsView::CanAddPrestation()
{
    // can add a new prestation?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanNewPrestation();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_PrestationsView::CanRenamePrestation()
{
    // can rename the selected prestation?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanRenamePrestation();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_PrestationsView::CanDeletePrestation()
{
    // can delete the selected prestation?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanDeletePrestation();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_PrestationsView::CanProperties()
{
    // can show the properties?
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.CanPrestationProperties();

    return false;
}
//---------------------------------------------------------------------------
int PSS_PrestationsView::HasContextMenu(CWnd* pWnd, const CPoint& point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        return m_Ctrl.HasContextMenu(pWnd, point);

    return -1;
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::ShowContextMenu(CWnd* pWnd, const CPoint& point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.ShowContextMenu(pWnd, point);
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::OnRefresh()
{
    CWaitCursor cursor;

    // refresh the user group control
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.Refresh();
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::OnAddPrestation()
{
    // add a new prestation
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnNewPrestation();
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::OnRenamePrestation()
{
    // rename the selected prestation
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnRenamePrestation();
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::OnDeletePrestation()
{
    // delete the selected prestation
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnDeletePrestation();
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::OnMovePrestation()
{
    // move the selected prestation
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnMovePrestation();
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::OnProperties()
{
    // show the properties
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
        m_Ctrl.OnPrestationProperties();
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // forward the message to the property control
    m_Ctrl.OnUpdate(pSubject, pMsg);

    PSS_ToolbarObserverMsg* pToolbarMsg = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

    if (pToolbarMsg)
        switch (pToolbarMsg->GetMessageID())
        {
            case UM_PRS_REFRESH:          OnRefresh();          break;
            case UM_PRS_ADDPRESTATION:    OnAddPrestation();    break;
            case UM_PRS_RENAMEPRESTATION: OnRenamePrestation(); break;
            case UM_PRS_DELETEPRESTATION: OnDeletePrestation(); break;
            case UM_PRS_MOVEPRESTATION:   OnMovePrestation();   break;
            case UM_PRS_PROPERTIES:       OnProperties();       break;
        }
}
//---------------------------------------------------------------------------
int PSS_PrestationsView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create the flat toolbar
    static_cast<CStatic&>(m_FlatToolBar).Create(_T(""),
                                                WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                CRect(0, 0, 100,
                                                g_FlatPrestationsToolbarHeight),
                                                this,
                                                IDC_PRS_FLATTOOLBAR);

    // create the user group control
    m_Ctrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS,
                  CRect(0, 0, 0, 0),
                  this,
                  IDC_PRS_CTRL);

    // attach the prestation control to the observer for notification
    m_FlatToolBar.AttachObserver(this);
    AttachObserver(&m_Ctrl);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, g_FlatPrestationsToolbarHeight);
        m_Ctrl.MoveWindow(0, g_FlatPrestationsToolbarHeight + 1, cx, cy - (g_FlatPrestationsToolbarHeight + 2));
    }
}
//---------------------------------------------------------------------------
void PSS_PrestationsView::OnPaint()
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
