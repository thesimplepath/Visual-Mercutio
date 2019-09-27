// ZVProperties.cpp : implementation file

#include "stdafx.h"
#include "ZVProperties.h"

#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zModel\ProcGraphModelDoc.h"

#include "zPtyMgrRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 23 septembre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Constant definition
const int _FlatToolbarHeight = 22;
const int _PropertyDescHeight = 80;

const int IDC_SHOWALLTYPES = 7000;
const int IDC_SHOWSTATICTYPE = 7001;
const int IDC_SHOWDYNAMICTYPE = 7002;
const int IDC_REFRESHVIEWS = 7003;

const int UM_REFRESH = 20000;
const int UM_SHOWALLTYPES = 20001;
const int UM_SHOWSTATICTYPE = 20002;
const int UM_SHOWDYNAMICTYPE = 20003;

const int IDC_PROP_FLATTOOLBAR = 10000;
const int IDC_PROP_LISTCTRL = 10001;
const int IDC_PROP_DESCRIPTIONCTRL = 10002;

/////////////////////////////////////////////////////////////////////////////
// _ZIFlatToolBar

BEGIN_MESSAGE_MAP(_ZIFlatToolBar, CStatic)
    //{{AFX_MSG_MAP(_ZIFlatToolBar)
    ON_BN_CLICKED(IDC_SHOWALLTYPES, OnShowAllTypesButton)
    ON_BN_CLICKED(IDC_SHOWSTATICTYPE, OnShowStaticTypeButton)
    ON_BN_CLICKED(IDC_SHOWDYNAMICTYPE, OnShowDynamicTypeButton)
    ON_BN_CLICKED(IDC_REFRESHVIEWS, OnRefreshButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZIFlatToolBar::_ZIFlatToolBar()
{
    m_ImageList.Create(IDB_PROP_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}

_ZIFlatToolBar::~_ZIFlatToolBar()
{}

/////////////////////////////////////////////////////////////////////////////
// _ZIFlatToolBar message handlers

int _ZIFlatToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
                                IDC_REFRESHVIEWS))
    {
        TRACE0(_T("Unable to create button.\n"));
        return -1;
    }

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_ShowAllTypesButton.Create(NULL,
                                     WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                     rc,
                                     this,
                                     IDC_SHOWALLTYPES))
    {
        TRACE0(_T("Unable to create button.\n"));
        return -1;
    }

    m_ShowAllTypesButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_ShowStaticTypeButton.Create(NULL,
                                       WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                       rc,
                                       this,
                                       IDC_SHOWSTATICTYPE))
    {
        TRACE0(_T("Unable to create button.\n"));
        return -1;
    }

    m_ShowStaticTypeButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_ShowDynamicTypeButton.Create(NULL,
                                        WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                        rc,
                                        this,
                                        IDC_SHOWDYNAMICTYPE))
    {
        TRACE0(_T("Unable to create button.\n"));
        return -1;
    }

    m_ShowDynamicTypeButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // Create the ToolTip control.
    m_tooltip.Create(this);
    m_tooltip.Activate(TRUE);

    m_tooltip.AddTool(GetDlgItem(IDC_REFRESHVIEWS), IDS_REFRESH);
    m_tooltip.AddTool(GetDlgItem(IDC_SHOWALLTYPES), IDS_SHOWALLTYPES);
    m_tooltip.AddTool(GetDlgItem(IDC_SHOWSTATICTYPE), IDS_SHOWSTATICTYPE);
    m_tooltip.AddTool(GetDlgItem(IDC_SHOWDYNAMICTYPE), IDS_SHOWDYNAMICTYPE);

    return 0;
}

void _ZIFlatToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}

void _ZIFlatToolBar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg msg(UM_REFRESH);
    NotifyAllObservers(&msg);
}

void _ZIFlatToolBar::OnShowAllTypesButton()
{
    PSS_ToolbarObserverMsg msg(UM_SHOWALLTYPES);
    NotifyAllObservers(&msg);
}

void _ZIFlatToolBar::OnShowStaticTypeButton()
{
    PSS_ToolbarObserverMsg msg(UM_SHOWSTATICTYPE);
    NotifyAllObservers(&msg);
}

void _ZIFlatToolBar::OnShowDynamicTypeButton()
{
    PSS_ToolbarObserverMsg msg(UM_SHOWDYNAMICTYPE);
    NotifyAllObservers(&msg);
}

BOOL _ZIFlatToolBar::PreTranslateMessage(MSG* pMsg)
{
    // Let the ToolTip process this message.
    m_tooltip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// ZVProperties

IMPLEMENT_DYNCREATE(ZVProperties, CWnd)

BEGIN_MESSAGE_MAP(ZVProperties, CWnd)
    //{{AFX_MSG_MAP(ZVProperties)
    ON_WM_CREATE()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVProperties::ZVProperties()
    : m_CurrentView(AllTypes)
{}

ZVProperties::~ZVProperties()
{}

void ZVProperties::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // Forward the message to the property control
    m_listctrl.OnUpdate(pSubject, pMsg);

    // Forward the message to the property description control
    m_PropDesc.OnUpdate(pSubject, pMsg);

    if (pMsg && ISA(pMsg, PSS_ToolbarObserverMsg))
    {
        switch (dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg)->GetMessageID())
        {
            case UM_REFRESH:
            {
                OnRefresh();
                break;
            }

            case UM_SHOWALLTYPES:
            {
                OnShowAllTypes();
                break;
            }

            case UM_SHOWSTATICTYPE:
            {
                OnShowStaticType();
                break;
            }

            case UM_SHOWDYNAMICTYPE:
            {
                OnShowDynamicType();
                break;
            }
        }
    }
    // Check about document close
    else if (pMsg                                    &&
             ISA(pMsg, PSS_DocumentObserverMsg) &&
             ISA(dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetDocument(), ZDProcessGraphModelDoc))
    {
        switch (dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetMessageID())
        {
            case UM_REFRESHDOCUMENT:
            case UM_OPENDOCUMENT:
            {
                break;
            }

            case UM_CLOSEDOCUMENT:
            {
                OnEmptyControl();
                break;
            }
        }
    }
}

void ZVProperties::SwitchToView(ZVProperties::ZPropertiesView View /*= AllTypes*/)
{
    // Save the current view
    m_CurrentView = View;

    // Switch to view 
    switch (View)
    {
        case AllTypes:
        {
            ShowAllTypes();
            break;
        }

        case StaticType:
        {
            ShowStaticType();
            break;
        }

        case DynamicType:
        {
            ShowDynamicType();
            break;
        }
    }

    // Reload the control data
    if (::IsWindow(m_listctrl.GetSafeHwnd()))
    {
        m_listctrl.Refresh(true, true);
    }
}

void ZVProperties::RefreshCurrentView()
{
    CWaitCursor Cursor;

    // Refresh controls
    if (::IsWindow(m_listctrl.GetSafeHwnd()))
    {
        m_listctrl.Refresh();
    }

    if (::IsWindow(m_PropDesc.GetSafeHwnd()))
    {
        m_PropDesc.UpdateWindow();
    }
}

void ZVProperties::OnEmptyControl()
{
    CWaitCursor    Cursor;

    // Refresh controls
    if (::IsWindow(m_listctrl.GetSafeHwnd()))
    {
        m_listctrl.Empty();
    }
}

void ZVProperties::ShowAllTypes()
{
    if (::IsWindow(m_listctrl.GetSafeHwnd()))
    {
        m_listctrl.SetDisplayType(AllProperties);
    }
}

void ZVProperties::ShowStaticType()
{
    if (::IsWindow(m_listctrl.GetSafeHwnd()))
    {
        m_listctrl.SetDisplayType(StaticProperties);
    }
}

void ZVProperties::ShowDynamicType()
{
    if (::IsWindow(m_listctrl.GetSafeHwnd()))
    {
        m_listctrl.SetDisplayType(DynamicProperties);
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZVProperties message handlers

int ZVProperties::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
                                                     IDC_PROP_FLATTOOLBAR);

    // Create the list control
    m_listctrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_NOINTEGRALHEIGHT,
                      CRect(0, 0, 0, 0),
                      this,
                      IDC_PROP_LISTCTRL);

    // Create the property description control
    reinterpret_cast<CStatic&>(m_PropDesc).Create(_T(""),
                                                  WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                  CRect(0, 0, 0, 0),
                                                  this,
                                                  IDC_PROP_DESCRIPTIONCTRL);

    // Attach us as an observer for messages
    m_FlatToolBar.AttachObserver(this);

    // Attach the property description control as an observer
    m_listctrl.AttachObserver(&m_PropDesc);

    return 0;
}

void ZVProperties::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, _FlatToolbarHeight);
        m_listctrl.MoveWindow(0, _FlatToolbarHeight, cx, cy - (_FlatToolbarHeight + _PropertyDescHeight));
        m_PropDesc.MoveWindow(0, cy - _PropertyDescHeight, cx, _PropertyDescHeight);
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZVProperties message handlers from toolbar

void ZVProperties::OnRefresh()
{
    RefreshCurrentView();
}

void ZVProperties::OnShowAllTypes()
{
    SwitchToView(AllTypes);
}

void ZVProperties::OnShowStaticType()
{
    SwitchToView(StaticType);
}

void ZVProperties::OnShowDynamicType()
{
    SwitchToView(DynamicType);
}
