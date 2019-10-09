/****************************************************************************
 * ==> PSS_UrlFormView -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an url form view                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UrlFormView.h"

#include "zRes32\ZRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_AddressIntelliEdit, PSS_IntelliEdit)
    //{{AFX_MSG_MAP(PSS_AddressIntelliEdit)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_AddressIntelliEdit
//---------------------------------------------------------------------------
PSS_AddressIntelliEdit::PSS_AddressIntelliEdit(CWnd* pParent, CStringArray* pArrayOfValues) :
    PSS_IntelliEdit(pArrayOfValues),
    m_pParent(pParent)
{}
//---------------------------------------------------------------------------
PSS_AddressIntelliEdit::~PSS_AddressIntelliEdit()
{}
//---------------------------------------------------------------------------
void PSS_AddressIntelliEdit::SetParent(CWnd* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
void PSS_AddressIntelliEdit::OnEnter()
{
    if (m_pParent)
        m_pParent->SendMessage(UM_GOWEB);
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UrlFormViewButtonToolBar, CStatic)
    //{{AFX_MSG_MAP(PSS_UrlFormViewButtonToolBar)
    ON_BN_CLICKED(IDC_STOPWEB, OnStopWebButton)
    ON_BN_CLICKED(IDC_REFRESHWEB, OnRefreshWebButton)
    ON_BN_CLICKED(IDC_PREVWEB, OnPrevWebButton)
    ON_BN_CLICKED(IDC_NEXTWEB, OnNextWebButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UrlFormViewButtonToolBar
//---------------------------------------------------------------------------
PSS_UrlFormViewButtonToolBar::PSS_UrlFormViewButtonToolBar(CWnd* pParent) :
    CStatic(),
    m_pParent(pParent)
{
    m_ImageList.Create(IDB_URL_FV_BUTTONS, 14, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_UrlFormViewButtonToolBar::~PSS_UrlFormViewButtonToolBar()
{}
//---------------------------------------------------------------------------
void PSS_UrlFormViewButtonToolBar::SetParent(CWnd* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
void PSS_UrlFormViewButtonToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();

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
        return;
    }

    m_PrevWebButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(14, 14));
    rc.OffsetRect(20, 0);

    if (!m_NextWebButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_NEXTWEB))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_NextWebButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(14, 14));
    rc.OffsetRect(20, 0);

    if (!m_StopWebButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_STOPWEB))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_StopWebButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(14, 14));
    rc.OffsetRect(20, 0);

    if (!m_RefreshWebButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_REFRESHWEB))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_RefreshWebButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(14, 14));

    // create the tooltip control
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);

    m_ToolTip.AddTool(GetDlgItem(IDC_PREVWEB), IDS_PREVWEB);
    m_ToolTip.AddTool(GetDlgItem(IDC_NEXTWEB), IDS_NEXTWEB);
    m_ToolTip.AddTool(GetDlgItem(IDC_STOPWEB), IDS_STOPWEB);
    m_ToolTip.AddTool(GetDlgItem(IDC_REFRESHWEB), IDS_REFRESHWEB);
}
//---------------------------------------------------------------------------
BOOL PSS_UrlFormViewButtonToolBar::PreTranslateMessage(MSG* pMsg)
{
    // let the ToolTip process this message
    m_ToolTip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
int PSS_UrlFormViewButtonToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}
//---------------------------------------------------------------------------
void PSS_UrlFormViewButtonToolBar::OnRefreshWebButton()
{
    if (m_pParent)
        m_pParent->SendMessage(UM_REFRESHWEB);
}
//---------------------------------------------------------------------------
void PSS_UrlFormViewButtonToolBar::OnStopWebButton()
{
    if (m_pParent)
        m_pParent->SendMessage(UM_STOPWEB);
}
//---------------------------------------------------------------------------
void PSS_UrlFormViewButtonToolBar::OnPrevWebButton()
{
    if (m_pParent)
        m_pParent->SendMessage(UM_PREVWEB);
}
//---------------------------------------------------------------------------
void PSS_UrlFormViewButtonToolBar::OnNextWebButton()
{
    if (m_pParent)
        m_pParent->SendMessage(UM_NEXTWEB);
}
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_UrlFormView, CFormView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UrlFormView, CFormView)
    //{{AFX_MSG_MAP(PSS_UrlFormView)
    ON_BN_CLICKED(IDC_GOWEB, OnGo)
    ON_WM_SIZE()
    ON_MESSAGE(UM_STOPWEB, OnStopWebButton)
    ON_MESSAGE(UM_REFRESHWEB, OnRefreshWebButton)
    ON_MESSAGE(UM_PREVWEB, OnPrevWebButton)
    ON_MESSAGE(UM_NEXTWEB, OnNextWebButton)
    ON_MESSAGE(UM_GOWEB, OnGoMessage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UrlFormView
//---------------------------------------------------------------------------
PSS_UrlFormView::PSS_UrlFormView() :
    CFormView(PSS_UrlFormView::IDD),
    m_pBrowser(NULL),
    m_URL(_T(""))
{}
//---------------------------------------------------------------------------
PSS_UrlFormView::~PSS_UrlFormView()
{
    if (m_pBrowser)
        delete m_pBrowser;

    m_pBrowser = NULL;
}
//---------------------------------------------------------------------------
void PSS_UrlFormView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_UrlFormView)
    DDX_Control(pDX, IDC_URL,         m_URLEdit);
    DDX_Control(pDX, IDC_GOWEB,       m_GoButton);
    DDX_Control(pDX, IDC_FLATTOOLBAR, m_FlatToolBar);
    DDX_Text   (pDX, IDC_URL,         m_URL);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_UrlFormView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    m_GoButton.SetIcon(IDI_GOWEB);
    m_GoButton.SetAlign(PSS_FlatButton::IE_ST_ALIGN_HORZ_RIGHT);
    m_GoButton.SetTooltipText(IDS_GOWEB);

    m_GoButton.DrawTransparent();

    // create web control
    if (GetDlgItem(IDC_WEBCTRL))
    {
        CRect rect;
        GetDlgItem(IDC_WEBCTRL)->GetClientRect(&rect);
        GetDlgItem(IDC_WEBCTRL)->MapWindowPoints(this, &rect);

        m_pBrowser = new PSS_WebBrowser;
        ASSERT (m_pBrowser);

        // create control
        if (!m_pBrowser->Create(NULL, NULL, WS_VISIBLE, rect, this, NULL))
        {
            TRACE("failed to create browser\n");
            delete m_pBrowser;
            m_pBrowser = NULL;
            return;
        }

        COleVariant noArg;

        // initialize the first url
        if (!m_URL.IsEmpty())
            m_pBrowser->Navigate(m_URL);
    }

    // assign the parent's toolbar
    m_FlatToolBar.SetParent(this);

    // assign the pointer to the value array
    m_URLEdit.Initialize(&m_ValueArray);

    // assign the parent's edit
    m_URLEdit.SetParent(this);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UrlFormView::AssertValid() const
    {
        CFormView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UrlFormView::Dump(CDumpContext& dc) const
    {
        CFormView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_UrlFormView::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);
    SizeControl();
}
//---------------------------------------------------------------------------
LRESULT PSS_UrlFormView::OnStopWebButton(WPARAM wParam, LPARAM lParam)
{
    if (m_pBrowser)
        m_pBrowser->Stop();

    return 1;
}
//---------------------------------------------------------------------------
LRESULT PSS_UrlFormView::OnRefreshWebButton(WPARAM wParam, LPARAM lParam)
{
    if (m_pBrowser)
        m_pBrowser->Refresh();

    return 1;
}
//---------------------------------------------------------------------------
LRESULT PSS_UrlFormView::OnPrevWebButton(WPARAM wParam, LPARAM lParam)
{
    if (m_pBrowser)
        m_pBrowser->GoBack();

    return 1;
}
//---------------------------------------------------------------------------
LRESULT PSS_UrlFormView::OnNextWebButton(WPARAM wParam, LPARAM lParam)
{
    if (m_pBrowser)
        m_pBrowser->GoForward();

    return 1;
}
//---------------------------------------------------------------------------
LRESULT PSS_UrlFormView::OnGoMessage(WPARAM wParam, LPARAM lParam)
{
    OnGo();
    return 1;
}
//---------------------------------------------------------------------------
void PSS_UrlFormView::OnGo()
{
    UpdateData();

    const int  valueCount = m_ValueArray.GetSize();
          bool found      = false;

    for (int i = 0; i < valueCount; ++i)
        if (m_ValueArray.GetAt(i) == m_URL)
        {
            found = true;
            break;
        }

    if (!found)
        m_ValueArray.Add(m_URL);

    if (!m_URL.IsEmpty())
        m_pBrowser->Navigate(m_URL);
}
//---------------------------------------------------------------------------
void PSS_UrlFormView::SizeControl()
{
    if (GetDlgItem(IDC_WEBCTRL) && ::IsWindow(GetDlgItem(IDC_WEBCTRL)->GetSafeHwnd()))
    {
        CRect rect;
        GetClientRect(&rect);

        // if the rect is empty, nothing to do
        if (rect.IsRectEmpty())
            return;

        if (GetDlgItem(IDC_URL))
        {
            CRect editRect;
            GetDlgItem(IDC_URL)->GetClientRect(&editRect);
            editRect.top    = rect.top + 25;
            editRect.bottom = editRect.top + __max(editRect.Height(), 20);
            editRect.left   = rect.left + 2;
            editRect.right  = rect.right - 25;
            GetDlgItem(IDC_URL)->MoveWindow(&editRect);
        }

        if (GetDlgItem(IDC_GOWEB))
        {
            CRect buttonRect;
            GetDlgItem(IDC_GOWEB)->GetClientRect(&buttonRect);
            buttonRect.top    = rect.top         + 25;
            buttonRect.bottom = buttonRect.top   + buttonRect.Height();
            buttonRect.right  = rect.right       - 2;
            buttonRect.left   = buttonRect.right - buttonRect.Width();
            GetDlgItem(IDC_GOWEB)->MoveWindow(&buttonRect);
        }

        if (m_pBrowser)
        {
            CRect browserRect;
            m_pBrowser->GetClientRect(&browserRect);
            browserRect.bottom = rect.bottom - 2;
            browserRect.right  = rect.right - 2;
            browserRect.top    = rect.top + 50;
            browserRect.left   = rect.left + 2;
            m_pBrowser->MoveWindow(&browserRect);
        }
    }
}
//---------------------------------------------------------------------------
