/****************************************************************************
 * ==> PSS_UrlWnd ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an url window                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UrlWnd.h"

// processsoft
#include "zBaseLib\PSS_ToolbarObserverMsg.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const int g_FlatToolbarHeight    = 22;
const int g_URLEditControlHeight = 18;
const int g_GoButtonControlSize  = 18;

// resource constants
const int IDC_URLWND_URL         = 400;
const int IDC_URLWND_GOWEB       = 401;
const int IDC_URLWND_FLATTOOLBAR = 402;
const int IDC_URLWND_WEBBROWSER  = 403;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UrlWndAddressIntelliEdit, PSS_IntelliEdit)
    //{{AFX_MSG_MAP(PSS_UrlWndAddressIntelliEdit)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UrlWndAddressIntelliEdit
//---------------------------------------------------------------------------
PSS_UrlWndAddressIntelliEdit::PSS_UrlWndAddressIntelliEdit(CWnd* pParent, CStringArray* pArrayOfValues) :
    PSS_IntelliEdit(pArrayOfValues),
    m_pParent(pParent)
{}
//---------------------------------------------------------------------------
PSS_UrlWndAddressIntelliEdit::~PSS_UrlWndAddressIntelliEdit()
{}
//---------------------------------------------------------------------------
void PSS_UrlWndAddressIntelliEdit::SetParent(CWnd* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
void PSS_UrlWndAddressIntelliEdit::OnEnter()
{
    PSS_ToolbarObserverMsg msg(UM_GOWEB);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UrlWndButtonToolBar, CStatic)
    //{{AFX_MSG_MAP(PSS_UrlWndButtonToolBar)
    ON_BN_CLICKED(IDC_STOPWEB, OnStopWebButton)
    ON_BN_CLICKED(IDC_REFRESHWEB, OnRefreshWebButton)
    ON_BN_CLICKED(IDC_PREVWEB, OnPrevWebButton)
    ON_BN_CLICKED(IDC_NEXTWEB, OnNextWebButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UrlWndButtonToolBar
//---------------------------------------------------------------------------
PSS_UrlWndButtonToolBar::PSS_UrlWndButtonToolBar(CWnd* pParent) :
    m_pParent(pParent)
{
    m_ImageList.Create(IDB_URL_FV_BUTTONS, 14, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_UrlWndButtonToolBar::~PSS_UrlWndButtonToolBar()
{}
//---------------------------------------------------------------------------
void PSS_UrlWndButtonToolBar::SetParent(CWnd* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
BOOL PSS_UrlWndButtonToolBar::PreTranslateMessage(MSG* pMsg)
{
    // let the ToolTip process this message
    m_ToolTip.RelayEvent(pMsg);

    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
int PSS_UrlWndButtonToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rc;
    GetWindowRect(&rc);
    ScreenToClient(&rc);

    rc.top    += 1;
    rc.bottom -= 1;
    rc.left   += 1;
    rc.right   = rc.left + 20;

    int iconIndex = 0;

    if (!m_PrevWebButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_PREVWEB))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_PrevWebButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(14, 14));
    rc.OffsetRect(20, 0);

    if (!m_NextWebButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_NEXTWEB))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_NextWebButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(14, 14));
    rc.OffsetRect(20, 0);

    if (!m_StopWebButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_STOPWEB))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_StopWebButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(14, 14));
    rc.OffsetRect(20, 0);

    if (!m_RefreshWebButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_REFRESHWEB))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_RefreshWebButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(14, 14));

    // create the tooltip control
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);

    m_ToolTip.AddTool(GetDlgItem(IDC_PREVWEB), IDS_PREVWEB);
    m_ToolTip.AddTool(GetDlgItem(IDC_NEXTWEB), IDS_NEXTWEB);
    m_ToolTip.AddTool(GetDlgItem(IDC_STOPWEB), IDS_STOPWEB);
    m_ToolTip.AddTool(GetDlgItem(IDC_REFRESHWEB), IDS_REFRESHWEB);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_UrlWndButtonToolBar::OnStopWebButton()
{
    PSS_ToolbarObserverMsg msg(UM_STOPWEB);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_UrlWndButtonToolBar::OnRefreshWebButton()
{
    PSS_ToolbarObserverMsg msg(UM_REFRESHWEB);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_UrlWndButtonToolBar::OnPrevWebButton()
{
    PSS_ToolbarObserverMsg msg(UM_PREVWEB);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_UrlWndButtonToolBar::OnNextWebButton()
{
    PSS_ToolbarObserverMsg msg(UM_NEXTWEB);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_UrlWnd, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UrlWnd, CWnd)
    //{{AFX_MSG_MAP(PSS_UrlWnd)
    ON_WM_CREATE()
    ON_BN_CLICKED(IDC_URLWND_GOWEB, OnGo)
    ON_WM_SIZE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UrlWnd
//---------------------------------------------------------------------------
PSS_UrlWnd::PSS_UrlWnd() :
    m_pBrowser(NULL),
    m_URL(_T(""))
{
    m_ClrBtnFace = ::GetSysColor(COLOR_BTNFACE);
}
//---------------------------------------------------------------------------
PSS_UrlWnd::~PSS_UrlWnd()
{
    if (m_pBrowser)
        delete m_pBrowser;
}
//---------------------------------------------------------------------------
int PSS_UrlWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate( lpCreateStruct ) == -1)
        return -1;

    // create the flat toolbar
    static_cast<CStatic&>(m_FlatToolBar).Create(_T(""),
                                                WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                CRect(0, 0, 100, g_FlatToolbarHeight),
                                                this,
                                                IDC_URLWND_FLATTOOLBAR );

    // create the flat toolbar
    m_GoButton.Create(_T(""),
                      WS_CHILD | WS_VISIBLE,
                      CRect(0, 0, g_GoButtonControlSize, g_GoButtonControlSize),
                      this,
                      IDC_URLWND_GOWEB);

    // create the url edit
    m_URLEdit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER,
                     CRect(0, 0, 100, g_URLEditControlHeight),
                     this,
                     IDC_URLWND_URL);

    m_GoButton.SetIcon(IDI_GOWEB);
    m_GoButton.SetAlign(PSS_FlatButton::IE_ST_ALIGN_HORZ_RIGHT);
    m_GoButton.SetTooltipText(IDS_GOWEB);
    m_GoButton.DrawTransparent();

    // create the control
    m_pBrowser = new PSS_WebBrowser;
    ASSERT(m_pBrowser);

    if (!m_pBrowser->Create(NULL, NULL, WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_URLWND_WEBBROWSER))
    {
        TRACE("Failed to create browser\n");
        delete m_pBrowser;
        m_pBrowser = NULL;
        return -1;
    }

    COleVariant noArg;

    // initialize the first url
    if (!m_URL.IsEmpty())
        m_pBrowser->Navigate(m_URL);

    // attach us as an observer for messages
    m_FlatToolBar.AttachObserver(this);

    // attach us as an observer for edit
    m_URLEdit.AttachObserver(this);

    // assign the parent's toolbar
    m_FlatToolBar.SetParent(this);

    // assign the pointer to the value array
    m_URLEdit.Initialize(&m_ValueArray);

    // assign the parent's edit
    m_URLEdit.SetParent(this);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_UrlWnd::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_ToolbarObserverMsg* pToolbarObsMsg = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

    if (pToolbarObsMsg)
        switch (pToolbarObsMsg->GetMessageID())
        {
            case UM_GOWEB:      OnGo();               break;
            case UM_STOPWEB:    OnStopWebButton();    break;
            case UM_REFRESHWEB: OnRefreshWebButton(); break;
            case UM_PREVWEB:    OnPrevWebButton();    break;
            case UM_NEXTWEB:    OnNextWebButton();    break;
        }
}
//---------------------------------------------------------------------------
void PSS_UrlWnd::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (m_pBrowser && ::IsWindow(m_pBrowser->GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, g_FlatToolbarHeight);

        m_URLEdit.MoveWindow(5, g_FlatToolbarHeight + 5, cx - 15 - g_GoButtonControlSize, g_URLEditControlHeight);

        m_GoButton.MoveWindow(cx - 5 - g_GoButtonControlSize,
                              g_FlatToolbarHeight + 5,
                              g_GoButtonControlSize,
                              g_GoButtonControlSize);

        m_pBrowser->MoveWindow(0,
                               g_FlatToolbarHeight + 10 + g_URLEditControlHeight,
                               cx,
                               cy - (g_FlatToolbarHeight + 10 + g_URLEditControlHeight));
    }
}
//---------------------------------------------------------------------------
void PSS_UrlWnd::OnPaint()
{
    // obtain the device context for painting
    CPaintDC dc(this);

    // get the client rect for this control
    CRect rc;
    GetClientRect(&rc);

    // set the background to transparent, and draw a 3D border around the control
    dc.SetBkMode(TRANSPARENT);
    dc.FillSolidRect(rc, m_ClrBtnFace);
}
//---------------------------------------------------------------------------
void PSS_UrlWnd::OnGo()
{
    // get the window text
    m_URLEdit.GetWindowText(m_URL);

    const int  valueCount = m_ValueArray.GetSize();
          bool found      = false;

    for (int i = 0; i < valueCount; ++i)
        if (m_ValueArray.GetAt(i) == m_URL)
        {
            found = true;
            break;
        }

    if (!found)
    {
        m_ValueArray.Add(m_URL);
        m_URLEdit.ReloadListOfValues();
    }

    if (!m_URL.IsEmpty())
        m_pBrowser->Navigate(m_URL);
}
//---------------------------------------------------------------------------
void PSS_UrlWnd::OnStopWebButton()
{
    if (m_pBrowser)
        m_pBrowser->Stop();
}
//---------------------------------------------------------------------------
void PSS_UrlWnd::OnRefreshWebButton()
{
    if (m_pBrowser)
        m_pBrowser->Refresh();
}
//---------------------------------------------------------------------------
void PSS_UrlWnd::OnPrevWebButton()
{
    if (m_pBrowser)
        m_pBrowser->GoBack();
}
//---------------------------------------------------------------------------
void PSS_UrlWnd::OnNextWebButton()
{
    if (m_pBrowser)
        m_pBrowser->GoForward();
}
//---------------------------------------------------------------------------
