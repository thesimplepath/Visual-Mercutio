// ZVFileFormView.cpp : implementation file
//

#include "stdafx.h"
#include "ZVFileFormView.h"

#include "zRes32\ZRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVFileFormView

IMPLEMENT_DYNCREATE(ZVFileFormView, CFormView)

ZVFileFormView::ZVFileFormView()
    : CFormView(ZVFileFormView::IDD)
{
    //{{AFX_DATA_INIT(ZVFileFormView)
    //}}AFX_DATA_INIT
    // Defines the edit as search for file
    m_Filename.SetSearchType( ZSEARCHEDIT_FILE, "" );
}

ZVFileFormView::~ZVFileFormView()
{
}

void ZVFileFormView::OnInitialUpdate( )
{
    CFormView::OnInitialUpdate( );

    m_DirTreeCtrl.Initialize( "", true, true);
    // Assign the parent's toolbar
    m_FlatToolBar.SetParent( this );
    // Initialize the edit for drag & drop
    m_Filename.Init();
}



void ZVFileFormView::SizeControl() 
{
    if (GetDlgItem(IDC_FILENAME) &&
        ::IsWindow(GetDlgItem(IDC_FILENAME)->GetSafeHwnd()))
    {
        CRect rect;
        GetClientRect(&rect);
        // If the rect is empty, nothing to do.
        if (rect.IsRectEmpty())
            return;
        if (GetDlgItem(IDC_FILENAME))
        {
            CRect EditRect;
            GetDlgItem(IDC_FILENAME)->GetClientRect(&EditRect);
            int cx = EditRect.Width();
            int cy = __max(EditRect.Height(), 20);
            EditRect.top = rect.top + 25;
            EditRect.bottom = EditRect.top + cy;
            EditRect.left = rect.left + 2;
            EditRect.right = rect.right - 2;
            GetDlgItem(IDC_FILENAME)->MoveWindow( &EditRect );
        }
        if (::IsWindow(m_DirTreeCtrl.GetSafeHwnd()))
        {
            CRect DirTreeRect;
            m_DirTreeCtrl.GetClientRect(&DirTreeRect);
            int cx = DirTreeRect.Width();
            int cy = DirTreeRect.Height();
            DirTreeRect.bottom = rect.bottom - 2;
            DirTreeRect.right = rect.right - 2;
            DirTreeRect.top = rect.top + 50;
            DirTreeRect.left = rect.left + 2;
            m_DirTreeCtrl.MoveWindow( &DirTreeRect );
        }
    }    
}


void ZVFileFormView::ReflectChangedDirectory()
{
    if (m_DirTreeCtrl.IsValid())
    {
        CString    Filename = m_DirTreeCtrl.GetSelectedDirectory();
        m_Filename.GetWindowText( Filename );
    }
}

void ZVFileFormView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVFileFormView)
    DDX_Control(pDX, IDC_FILENAME, m_Filename);
    DDX_Control(pDX, IDC_FILETREE, m_DirTreeCtrl);
    DDX_Control(pDX, IDC_FLATTOOLBAR, m_FlatToolBar);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVFileFormView, CFormView)
    //{{AFX_MSG_MAP(ZVFileFormView)
    ON_WM_SIZE()
    ON_NOTIFY(TVN_SELCHANGED, IDC_FILETREE, OnSelchangedDirectory)
    ON_NOTIFY(NM_DBLCLK, IDC_FILETREE, OnDblclkDirectory)
    ON_NOTIFY(NM_CLICK, IDC_FILETREE, OnClickDirectory)
    ON_MESSAGE(UM_STOPFILE, OnStopFileButton)
    ON_MESSAGE(UM_REFRESHFILE, OnRefreshWebButton)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVFileFormView diagnostics

#ifdef _DEBUG
void ZVFileFormView::AssertValid() const
{
    CFormView::AssertValid();
}

void ZVFileFormView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// ZVFileFormView message handlers


void ZVFileFormView::OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult) 
{
    ReflectChangedDirectory();
    *pResult = 0;
}
void ZVFileFormView::OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult) 
{
    ReflectChangedDirectory();
    *pResult = 0;
}
void ZVFileFormView::OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult) 
{
    ReflectChangedDirectory();
    *pResult = 0;
}


LRESULT ZVFileFormView::OnStopFileButton( WPARAM wParam, LPARAM lParam )
{
    return 1;
}

LRESULT ZVFileFormView::OnRefreshWebButton( WPARAM wParam, LPARAM lParam )
{
    m_DirTreeCtrl.Refresh();
    return 1;
}

void ZVFileFormView::OnSize(UINT nType, int cx, int cy) 
{
    CFormView::OnSize(nType, cx, cy);
    
    SizeControl();
}





/////////////////////////////////////////////////////////////////////////////
// _ZVFileFormViewButtonToolBar

_ZVFileFormViewButtonToolBar::_ZVFileFormViewButtonToolBar(CWnd* pParent /*=NULL*/)
: m_pParent(pParent)
{
    m_ImageList.Create(IDB_FILE_FV_BUTTONS, 14, 1, RGB(255,0,255));
}

_ZVFileFormViewButtonToolBar::~_ZVFileFormViewButtonToolBar()
{
}

void    _ZVFileFormViewButtonToolBar::SetParent(CWnd* pParent)
{
    m_pParent = pParent;
}

BEGIN_MESSAGE_MAP(_ZVFileFormViewButtonToolBar, CStatic)
    //{{AFX_MSG_MAP(_ZVFileFormViewButtonToolBar)
    ON_BN_CLICKED(IDC_STOPFILE, OnStopFileButton)
    ON_BN_CLICKED(IDC_REFRESHFILE, OnRefreshFileButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// _ZVFileFormViewButtonToolBar message handlers

int _ZVFileFormViewButtonToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;


    return 0;
}

void _ZVFileFormViewButtonToolBar::PreSubclassWindow() 
{
    CStatic::PreSubclassWindow();

    int    IconIndex = 0;

    CRect rc;
    GetWindowRect(&rc);
    ScreenToClient(&rc);
    rc.top+=1; rc.bottom-=1;
    rc.left+=1;
    rc.right = rc.left+20;

    if (!m_StopWebButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
        rc, this, IDC_STOPFILE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }
    m_StopWebButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(14,14));
    rc.OffsetRect(20,0);

    if (!m_RefreshWebButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
        rc, this, IDC_REFRESHFILE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }
    m_RefreshWebButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(14,14));

    
    // Create the ToolTip control.
    m_tooltip.Create(this);
    m_tooltip.Activate(TRUE);

    m_tooltip.AddTool(GetDlgItem(IDC_STOPFILE), IDS_STOPFILE);
    m_tooltip.AddTool(GetDlgItem(IDC_REFRESHFILE), IDS_REFRESHFILE);
}


void _ZVFileFormViewButtonToolBar::OnStopFileButton()
{
    if (m_pParent)
        m_pParent->SendMessage( UM_STOPFILE );
}

void _ZVFileFormViewButtonToolBar::OnRefreshFileButton()
{
    if (m_pParent)
        m_pParent->SendMessage( UM_REFRESHFILE );
}

BOOL _ZVFileFormViewButtonToolBar::PreTranslateMessage(MSG* pMsg) 
{
    // Let the ToolTip process this message.
    m_tooltip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}




