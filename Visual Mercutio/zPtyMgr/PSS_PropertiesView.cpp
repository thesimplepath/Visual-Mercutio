/****************************************************************************
 * ==> PSS_PropertiesView --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a properties view                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PropertiesView.h"

// processsoft
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"

// resources
#include "zPtyMgrRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int g_FlatToolbarHeight  = 22;
const int g_PropertyDescHeight = 80;
//---------------------------------------------------------------------------
// Custom Windows messages
//---------------------------------------------------------------------------
const int IDC_SHOWALLTYPES         = 7000;
const int IDC_SHOWSTATICTYPE       = 7001;
const int IDC_SHOWDYNAMICTYPE      = 7002;
const int IDC_REFRESHVIEWS         = 7003;
const int UM_REFRESH               = 20000;
const int UM_SHOWALLTYPES          = 20001;
const int UM_SHOWSTATICTYPE        = 20002;
const int UM_SHOWDYNAMICTYPE       = 20003;
const int IDC_PROP_FLATTOOLBAR     = 10000;
const int IDC_PROP_LISTCTRL        = 10001;
const int IDC_PROP_DESCRIPTIONCTRL = 10002;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PropertiesView::IFlatToolBar, CStatic)
    //{{AFX_MSG_MAP(PSS_PropertiesView::IFlatToolBar)
    ON_BN_CLICKED(IDC_SHOWALLTYPES, OnShowAllTypesButton)
    ON_BN_CLICKED(IDC_SHOWSTATICTYPE, OnShowStaticTypeButton)
    ON_BN_CLICKED(IDC_SHOWDYNAMICTYPE, OnShowDynamicTypeButton)
    ON_BN_CLICKED(IDC_REFRESHVIEWS, OnRefreshButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PropertiesView::IFlatToolBar
//---------------------------------------------------------------------------
PSS_PropertiesView::IFlatToolBar::IFlatToolBar()
{
    m_ImageList.Create(IDB_PROP_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_PropertiesView::IFlatToolBar::~IFlatToolBar()
{}
//---------------------------------------------------------------------------
BOOL PSS_PropertiesView::IFlatToolBar::PreTranslateMessage(MSG* pMsg)
{
    // let the tooltip process this message
    m_ToolTip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::IFlatToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::IFlatToolBar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg msg(UM_REFRESH);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::IFlatToolBar::OnShowAllTypesButton()
{
    PSS_ToolbarObserverMsg msg(UM_SHOWALLTYPES);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::IFlatToolBar::OnShowStaticTypeButton()
{
    PSS_ToolbarObserverMsg msg(UM_SHOWSTATICTYPE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::IFlatToolBar::OnShowDynamicTypeButton()
{
    PSS_ToolbarObserverMsg msg(UM_SHOWDYNAMICTYPE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
int PSS_PropertiesView::IFlatToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
                                IDC_REFRESHVIEWS))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_ShowAllTypesButton.Create(NULL,
                                     WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                     rc,
                                     this,
                                     IDC_SHOWALLTYPES))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_ShowAllTypesButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_ShowStaticTypeButton.Create(NULL,
                                       WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                       rc,
                                       this,
                                       IDC_SHOWSTATICTYPE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_ShowStaticTypeButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_ShowDynamicTypeButton.Create(NULL,
                                        WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                        rc,
                                        this,
                                        IDC_SHOWDYNAMICTYPE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_ShowDynamicTypeButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // create the tooltip control
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);

    m_ToolTip.AddTool(GetDlgItem(IDC_REFRESHVIEWS),    IDS_REFRESH);
    m_ToolTip.AddTool(GetDlgItem(IDC_SHOWALLTYPES),    IDS_SHOWALLTYPES);
    m_ToolTip.AddTool(GetDlgItem(IDC_SHOWSTATICTYPE),  IDS_SHOWSTATICTYPE);
    m_ToolTip.AddTool(GetDlgItem(IDC_SHOWDYNAMICTYPE), IDS_SHOWDYNAMICTYPE);

    return 0;
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_PropertiesView, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PropertiesView, CWnd)
    //{{AFX_MSG_MAP(PSS_PropertiesView)
    ON_WM_CREATE()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PropertiesView
//---------------------------------------------------------------------------
PSS_PropertiesView::PSS_PropertiesView() :
    CWnd(),
    PSS_Subject(),
    PSS_Observer(),
    m_CurrentView(IEPropertiesView::IE_PV_AllTypes)
{}
//---------------------------------------------------------------------------
PSS_PropertiesView::~PSS_PropertiesView()
{}
//---------------------------------------------------------------------------
void PSS_PropertiesView::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // forward the message to the property control
    m_ListCtrl.OnUpdate(pSubject, pMsg);

    // forward the message to the property description control
    m_PropDesc.OnUpdate(pSubject, pMsg);

    PSS_ToolbarObserverMsg* pToolbarMsg = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

    if (pToolbarMsg)
        switch (pToolbarMsg->GetMessageID())
        {
            case UM_REFRESH:         OnRefresh();         break;
            case UM_SHOWALLTYPES:    OnShowAllTypes();    break;
            case UM_SHOWSTATICTYPE:  OnShowStaticType();  break;
            case UM_SHOWDYNAMICTYPE: OnShowDynamicType(); break;
        }

    PSS_DocumentObserverMsg* pDocMsg = dynamic_cast<PSS_DocumentObserverMsg*>(pMsg);

    if (pDocMsg)
    {
        PSS_ProcessGraphModelDoc* pGraphMdlDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDocMsg->GetDocument());

        if (pGraphMdlDoc)
            switch (pDocMsg->GetMessageID())
            {
                case UM_REFRESHDOCUMENT:
                case UM_OPENDOCUMENT:                      break;
                case UM_CLOSEDOCUMENT:   OnEmptyControl(); break;
            }
    }
}
//---------------------------------------------------------------------------
int PSS_PropertiesView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create the flat toolbar
    static_cast<CStatic&>(m_FlatToolBar).Create(_T(""),
                                                WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                CRect(0, 0, 100, g_FlatToolbarHeight),
                                                this,
                                                IDC_PROP_FLATTOOLBAR);

    // create the list control
    m_ListCtrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_NOINTEGRALHEIGHT,
                      CRect(0, 0, 0, 0),
                      this,
                      IDC_PROP_LISTCTRL);

    // create the property description control
    static_cast<CStatic&>(m_PropDesc).Create(_T(""),
                                             WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                             CRect(0, 0, 0, 0),
                                             this,
                                             IDC_PROP_DESCRIPTIONCTRL);

    // attach it as an observer for messages
    m_FlatToolBar.AttachObserver(this);

    // Attach the property description control as an observer
    m_ListCtrl.AttachObserver(&m_PropDesc);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0,                         cx, g_FlatToolbarHeight);
        m_ListCtrl.MoveWindow   (0, g_FlatToolbarHeight,       cx, cy - (g_FlatToolbarHeight + g_PropertyDescHeight));
        m_PropDesc.MoveWindow   (0, cy - g_PropertyDescHeight, cx, g_PropertyDescHeight);
    }
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::SwitchToView(IEPropertiesView view)
{
    // save the current view
    m_CurrentView = view;

    // switch to view
    switch (view)
    {
        case IEPropertiesView::IE_PV_AllTypes:    ShowAllTypes();    break;
        case IEPropertiesView::IE_PV_StaticType:  ShowStaticType();  break;
        case IEPropertiesView::IE_PV_DynamicType: ShowDynamicType(); break;
    }

    // reload the control data
    if (::IsWindow(m_ListCtrl.GetSafeHwnd()))
        m_ListCtrl.Refresh(true, true);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::RefreshCurrentView()
{
    CWaitCursor Cursor;

    // refresh controls
    if (::IsWindow(m_ListCtrl.GetSafeHwnd()))
        m_ListCtrl.Refresh();

    if (::IsWindow(m_PropDesc.GetSafeHwnd()))
        m_PropDesc.UpdateWindow();
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::ShowAllTypes()
{
    if (::IsWindow(m_ListCtrl.GetSafeHwnd()))
        m_ListCtrl.SetShowType(PSS_PropertyItemManager::IEPropertyShowType::IE_ST_AllProperties);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::ShowStaticType()
{
    if (::IsWindow(m_ListCtrl.GetSafeHwnd()))
        m_ListCtrl.SetShowType(PSS_PropertyItemManager::IEPropertyShowType::IE_ST_StaticProperties);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::ShowDynamicType()
{
    if (::IsWindow(m_ListCtrl.GetSafeHwnd()))
        m_ListCtrl.SetShowType(PSS_PropertyItemManager::IEPropertyShowType::IE_ST_DynamicProperties);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::OnShowAllTypes()
{
    SwitchToView(IEPropertiesView::IE_PV_AllTypes);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::OnShowStaticType()
{
    SwitchToView(IEPropertiesView::IE_PV_StaticType);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::OnShowDynamicType()
{
    SwitchToView(IEPropertiesView::IE_PV_DynamicType);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::OnRefresh()
{
    RefreshCurrentView();
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::OnEmptyControl()
{
    CWaitCursor cursor;

    // refresh controls
    if (::IsWindow(m_ListCtrl.GetSafeHwnd()))
        m_ListCtrl.Empty();
}
//---------------------------------------------------------------------------
