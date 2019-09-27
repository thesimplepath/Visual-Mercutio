/****************************************************************************
 * ==> PSS_FileWnd ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file window                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FileWnd.h"

// processsoft
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zRes32\ZRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const int g_FlatToolbarHeight     = 22;
const int g_FileNameControlHeight = 18;

// resources constants
const int IDC_FILEWND_FILENAME    = 300;
const int IDC_FILEWND_FILETREE    = 301;
const int IDC_FILEWND_FLATTOOLBAR = 302;
//---------------------------------------------------------------------------
// PSS_FileWndButtonToolBar
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FileWndButtonToolBar, CStatic)
    //{{AFX_MSG_MAP(PSS_FileWndButtonToolBar)
    ON_BN_CLICKED(IDC_STOPFILE, OnStopFileButton)
    ON_BN_CLICKED(IDC_REFRESHFILE, OnRefreshFileButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FileWndButtonToolBar
//---------------------------------------------------------------------------
PSS_FileWndButtonToolBar::PSS_FileWndButtonToolBar(CWnd* pParent) :
    m_pParent(pParent)
{
    m_ImageList.Create(IDB_FILE_FV_BUTTONS, 14, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_FileWndButtonToolBar::~PSS_FileWndButtonToolBar()
{}
//---------------------------------------------------------------------------
void PSS_FileWndButtonToolBar::SetParent(CWnd* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
BOOL PSS_FileWndButtonToolBar::PreTranslateMessage(MSG* pMsg)
{
    // let the tooltip process this message.
    m_ToolTip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
int PSS_FileWndButtonToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
    rc.right   = rc.left + 20;

    if (!m_StopWebButton.Create(NULL,
                                WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                rc,
                                this,
                                IDC_STOPFILE))
    {
        TRACE0(_T("Unable to create button.\n"));
        return -1;
    }

    m_StopWebButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(14, 14));
    rc.OffsetRect(20, 0);

    if (!m_RefreshWebButton.Create(NULL,
                                   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                   rc,
                                   this,
                                   IDC_REFRESHFILE))
    {
        TRACE0(_T("Unable to create button.\n"));
        return -1;
    }

    m_RefreshWebButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(14, 14));

    // create the tooltip control
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);

    m_ToolTip.AddTool(GetDlgItem(IDC_STOPFILE), IDS_STOPFILE);
    m_ToolTip.AddTool(GetDlgItem(IDC_REFRESHFILE), IDS_REFRESHFILE);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_FileWndButtonToolBar::OnStopFileButton()
{
    PSS_ToolbarObserverMsg msg(UM_STOPFILE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_FileWndButtonToolBar::OnRefreshFileButton()
{
    PSS_ToolbarObserverMsg msg(UM_REFRESHFILE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_FileWnd, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FileWnd, CWnd)
    //{{AFX_MSG_MAP(PSS_FileWnd)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_NOTIFY(TVN_SELCHANGED, IDC_FILEWND_FILETREE, OnSelchangedDirectory)
    ON_NOTIFY(NM_DBLCLK, IDC_FILEWND_FILETREE, OnDblclkDirectory)
    ON_NOTIFY(NM_CLICK, IDC_FILEWND_FILETREE, OnClickDirectory)
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
PSS_FileWnd::PSS_FileWnd()
{
    m_clrBtnFace = ::GetSysColor(COLOR_BTNFACE);
}
//---------------------------------------------------------------------------
PSS_FileWnd::~PSS_FileWnd()
{}
//---------------------------------------------------------------------------
void PSS_FileWnd::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_ToolbarObserverMsg* pObserverMsg = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

    if (pObserverMsg)
        switch (pObserverMsg->GetMessageID())
        {
            case UM_STOPFILE:    OnStopFileButton(); break;
            case UM_REFRESHFILE: OnRefreshButton();  break;
        }
}
//---------------------------------------------------------------------------
int PSS_FileWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate( lpCreateStruct ) == -1)
        return -1;

    CStatic& flatToolbar = dynamic_cast<CStatic&>(m_FlatToolBar);

    // create the flat toolbar
    flatToolbar.Create(_T(""),
                       WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                       CRect(0, 0, 100, g_FlatToolbarHeight),
                       this,
                       IDC_FILEWND_FLATTOOLBAR);

    // define the edit as search for file
    m_FileName.SetSearchType(PSS_SearchEditButton::IE_T_File, _T(""));

    // create the edit
    m_FileName.Create (WS_CHILD | WS_VISIBLE | WS_BORDER,
                       CRect(0, 0, 100, g_FileNameControlHeight),
                       this,
                       IDC_FILEWND_FILENAME);

    // create the list control
    m_DirTreeCtrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL,
                         CRect(0, 0, 0, 0),
                         this,
                         IDC_FILEWND_FILETREE);
    
    // attach window as an observer for messages
    m_FlatToolBar.AttachObserver(this);

    // initialize the directory tree control
    m_DirTreeCtrl.Initialize(_T(""), true, true);

    // assign the parent's toolbar
    m_FlatToolBar.SetParent(this);

    // initialize the edit for drag & drop
    m_FileName.Init();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_FileWnd::OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult)
{
    ReflectChangedDirectory();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_FileWnd::OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult)
{
    ReflectChangedDirectory();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_FileWnd::OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult)
{
    ReflectChangedDirectory();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_FileWnd::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FileName.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, g_FlatToolbarHeight);
        m_FileName.MoveWindow(5, g_FlatToolbarHeight + 5, cx - 5, g_FileNameControlHeight);
        m_DirTreeCtrl.MoveWindow(0,
                                 g_FlatToolbarHeight + 10 + g_FileNameControlHeight,
                                 cx,
                                 cy - (g_FlatToolbarHeight + 10 + g_FileNameControlHeight));
    }
}
//---------------------------------------------------------------------------
void PSS_FileWnd::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);

    // get the client rect for this control
    CRect rc;
    GetClientRect(&rc);

    // set the background to transparent, and draw a 3D border around the control
    dc.SetBkMode(TRANSPARENT);
    dc.FillSolidRect(rc, m_clrBtnFace);
}
//---------------------------------------------------------------------------
void PSS_FileWnd::ReflectChangedDirectory()
{
    if (m_DirTreeCtrl.IsValid())
    {
        CString fileName = m_DirTreeCtrl.GetSelectedDirectory();
        m_FileName.GetWindowText(fileName);
    }
}
//---------------------------------------------------------------------------
void PSS_FileWnd::OnStopFileButton()
{}
//---------------------------------------------------------------------------
void PSS_FileWnd::OnRefreshButton()
{
    m_DirTreeCtrl.Refresh();
}
//---------------------------------------------------------------------------
