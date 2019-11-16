// ******************************************************************************************************************
// *                              Classes _ZIPrestationsFlatToolBar et ZVPrestations                                *
// ******************************************************************************************************************
// * JMR-MODIF - Le 11 octobre 2005 - Ajout des classes _ZIPrestationsFlatToolBar et ZVPrestations.                    *
// ******************************************************************************************************************
// * Ces classes représentent la vue et les boutons utilisés pour représenter l'affichage des prestations.            *
// ******************************************************************************************************************

#include "stdafx.h"
#include "ZVPrestations.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Constant definition
const int _FlatPrestationsToolbarHeight = 22;

const int IDC_PRS_ADDPRESTATION = 4000;
const int IDC_PRS_RENAMEPRESTATION = 4001;
const int IDC_PRS_DELETEPRESTATION = 4002;
const int IDC_PRS_MOVEPRESTATION = 4003;
const int IDC_PRS_PROPERTIES = 4004;
const int IDC_PRS_REFRESHVIEWS = 4005;

const int UM_PRS_ADDPRESTATION = 4000;
const int UM_PRS_RENAMEPRESTATION = 4001;
const int UM_PRS_DELETEPRESTATION = 4002;
const int UM_PRS_MOVEPRESTATION = 4003;
const int UM_PRS_PROPERTIES = 4004;
const int UM_PRS_REFRESH = 4005;

const int IDC_PRS_FLATTOOLBAR = 12005;
const int IDC_PRS_CTRL = 12006;

/////////////////////////////////////////////////////////////////////////////
// _ZIPrestationsFlatToolBar

BEGIN_MESSAGE_MAP(_ZIPrestationsFlatToolBar, CStatic)
    //{{AFX_MSG_MAP(_ZIPrestationsFlatToolBar)
    ON_BN_CLICKED(IDC_PRS_ADDPRESTATION, OnAddPrestationButton)
    ON_BN_CLICKED(IDC_PRS_RENAMEPRESTATION, OnRenamePrestationButton)
    ON_BN_CLICKED(IDC_PRS_DELETEPRESTATION, OnDeletePrestationButton)
    ON_BN_CLICKED(IDC_PRS_MOVEPRESTATION, OnMovePrestationButton)
    ON_BN_CLICKED(IDC_PRS_PROPERTIES, OnPropertiesButton)
    ON_BN_CLICKED(IDC_PRS_REFRESHVIEWS, OnRefreshButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZIPrestationsFlatToolBar::_ZIPrestationsFlatToolBar()
{
    m_ImageList.Create(IDB_PRESTATIONS_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}

_ZIPrestationsFlatToolBar::~_ZIPrestationsFlatToolBar()
{}

/////////////////////////////////////////////////////////////////////////////
// _ZIPrestationsFlatToolBar message handlers

int _ZIPrestationsFlatToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
                                IDC_PRS_REFRESHVIEWS))
    {
        TRACE0(_T("Unable to create refresh button in prestations workspace.\n"));
        return -1;
    }

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_AddPrestationButton.Create(NULL,
                                      WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                      rc,
                                      this,
                                      IDC_PRS_ADDPRESTATION))
    {
        TRACE0(_T("Unable to create add button in prestations workspace.\n"));
        return -1;
    }

    m_AddPrestationButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_RenamePrestationButton.Create(NULL,
                                         WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                         rc,
                                         this,
                                         IDC_PRS_RENAMEPRESTATION))
    {
        TRACE0(_T("Unable to create rename button in prestations workspace.\n"));
        return -1;
    }

    m_RenamePrestationButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_DeletePrestationButton.Create(NULL,
                                         WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                         rc,
                                         this,
                                         IDC_PRS_DELETEPRESTATION))
    {
        TRACE0(_T("Unable to create delete button in prestations workspace.\n"));
        return -1;
    }

    m_DeletePrestationButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_MovePrestationButton.Create(NULL,
                                       WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                       rc,
                                       this,
                                       IDC_PRS_MOVEPRESTATION))
    {
        TRACE0(_T("Unable to create move button in prestations workspace.\n"));
        return -1;
    }

    m_MovePrestationButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_PropertiesButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_PRS_PROPERTIES))
    {
        TRACE0(_T("Unable to create properties button in prestations workspace.\n"));
        return -1;
    }

    m_PropertiesButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // Create the ToolTip control.
    m_tooltip.Create(this);
    m_tooltip.Activate(TRUE);

    m_tooltip.AddTool(GetDlgItem(IDC_PRS_ADDPRESTATION), IDS_PRS_ADDPRESTATION);
    m_tooltip.AddTool(GetDlgItem(IDC_PRS_RENAMEPRESTATION), IDS_PRS_RENAMEPRESTATION);
    m_tooltip.AddTool(GetDlgItem(IDC_PRS_DELETEPRESTATION), IDS_PRS_DELETEPRESTATION);
    m_tooltip.AddTool(GetDlgItem(IDC_PRS_MOVEPRESTATION), IDS_PRS_MOVEPRESTATION);
    m_tooltip.AddTool(GetDlgItem(IDC_PRS_PROPERTIES), IDS_PRS_PROPERTIES);
    m_tooltip.AddTool(GetDlgItem(IDC_PRS_REFRESHVIEWS), IDS_REFRESH);

    return 0;
}

void _ZIPrestationsFlatToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}

void _ZIPrestationsFlatToolBar::OnAddPrestationButton()
{
    PSS_ToolbarObserverMsg msg(UM_PRS_ADDPRESTATION);
    NotifyAllObservers(&msg);
}

void _ZIPrestationsFlatToolBar::OnRenamePrestationButton()
{
    PSS_ToolbarObserverMsg msg(UM_PRS_RENAMEPRESTATION);
    NotifyAllObservers(&msg);
    PSS_Application::Instance()->RefreshPropertiesWorkspace();
}

void _ZIPrestationsFlatToolBar::OnDeletePrestationButton()
{
    PSS_ToolbarObserverMsg msg(UM_PRS_DELETEPRESTATION);
    NotifyAllObservers(&msg);
    PSS_Application::Instance()->RefreshPropertiesWorkspace();
}

void _ZIPrestationsFlatToolBar::OnMovePrestationButton()
{
    PSS_ToolbarObserverMsg msg(UM_PRS_MOVEPRESTATION);
    NotifyAllObservers(&msg);
}

void _ZIPrestationsFlatToolBar::OnPropertiesButton()
{
    PSS_ToolbarObserverMsg msg(UM_PRS_PROPERTIES);
    NotifyAllObservers(&msg);
}

void _ZIPrestationsFlatToolBar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg msg(UM_PRS_REFRESH);
    NotifyAllObservers(&msg);
}

BOOL _ZIPrestationsFlatToolBar::PreTranslateMessage(MSG* pMsg)
{
    // Let the ToolTip process this message.
    m_tooltip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// ZVPrestations

IMPLEMENT_DYNCREATE(ZVPrestations, CWnd)

BEGIN_MESSAGE_MAP(ZVPrestations, CWnd)
    //{{AFX_MSG_MAP(ZVPrestations)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVPrestations::ZVPrestations()
{
    m_clrBtnFace = ::GetSysColor(COLOR_BTNFACE);
}

ZVPrestations::~ZVPrestations()
{}

// JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release pour permettre un nettoyage de la mémoire.
void ZVPrestations::Release()
{
    m_Ctrl.Release();
}

void ZVPrestations::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // Forward the message to the property control
    m_Ctrl.OnUpdate(pSubject, pMsg);

    if (pMsg && ISA(pMsg, PSS_ToolbarObserverMsg))
    {
        switch (dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg)->GetMessageID())
        {
            case UM_PRS_REFRESH:
            {
                OnRefresh();
                break;
            }

            case UM_PRS_ADDPRESTATION:
            {
                OnAddPrestation();
                break;
            }

            case UM_PRS_RENAMEPRESTATION:
            {
                OnRenamePrestation();
                break;
            }

            case UM_PRS_DELETEPRESTATION:
            {
                OnDeletePrestation();
                break;
            }

            case UM_PRS_MOVEPRESTATION:
            {
                OnMovePrestation();
                break;
            }

            case UM_PRS_PROPERTIES:
            {
                OnProperties();
                break;
            }
        }
    }
}

int ZVPrestations::HasContextMenu(CWnd* pWnd, CPoint point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.HasContextMenu(pWnd, point);
    }

    return -1;
}

void ZVPrestations::DisplayContextMenu(CWnd* pWnd, CPoint point)
{
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.DisplayContextMenu(pWnd, point);
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZVPrestations message handlers

int ZVPrestations::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    // Create the flat toolbar
    reinterpret_cast<CStatic&>(m_FlatToolBar).Create(_T(""),
                                                     WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                     CRect(0, 0, 100,
                                                           _FlatPrestationsToolbarHeight),
                                                     this,
                                                     IDC_PRS_FLATTOOLBAR);

    // Create the user group control
    m_Ctrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS,
                  CRect(0, 0, 0, 0),
                  this,
                  IDC_PRS_CTRL);

    // Attach us as an observer for messages
    m_FlatToolBar.AttachObserver(this);

    // Attach the user group control for notification
    AttachObserver(&m_Ctrl);

    return 0;
}

void ZVPrestations::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, _FlatPrestationsToolbarHeight);
        m_Ctrl.MoveWindow(0, _FlatPrestationsToolbarHeight + 1, cx, cy - (_FlatPrestationsToolbarHeight + 2));
    }
}

void ZVPrestations::OnPaint()
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
// ZVPrestations message handlers from toolbar

void ZVPrestations::OnRefresh()
{
    CWaitCursor Cursor;

    // Refresh the user group control
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.Refresh();
    }
}

void ZVPrestations::OnAddPrestation()
{
    // Add a new group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnNewPrestation();
    }
}

void ZVPrestations::OnRenamePrestation()
{
    // Rename the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnRenamePrestation();
    }
}

void ZVPrestations::OnDeletePrestation()
{
    // Delete the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnDeletePrestation();
    }
}

void ZVPrestations::OnMovePrestation()
{
    // Delete the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnMovePrestation();
    }
}

void ZVPrestations::OnProperties()
{
    // Display the properties
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        m_Ctrl.OnPrestationProperties();
    }
}

bool ZVPrestations::CanAddPrestation()
{
    // Can Add a new group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanNewPrestation();
    }

    return false;
}

bool ZVPrestations::CanRenamePrestation()
{
    // Can Rename the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanRenamePrestation();
    }

    return false;
}

bool ZVPrestations::CanDeletePrestation()
{
    // Can Delete the selected group
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanDeletePrestation();
    }

    return false;
}

bool ZVPrestations::CanProperties()
{
    // Can Display the properties
    if (::IsWindow(m_Ctrl.GetSafeHwnd()))
    {
        return m_Ctrl.CanPrestationProperties();
    }

    return false;
}
