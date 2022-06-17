/****************************************************************************
 * ==> PSS_FileFormView ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file form view                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_FileFormView.h"

// processsoft
#include "zRes32\ZRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FileFormViewButtonToolBar, CStatic)
    //{{AFX_MSG_MAP(PSS_FileFormViewButtonToolBar)
    ON_BN_CLICKED(IDC_STOPFILE, OnStopFileButton)
    ON_BN_CLICKED(IDC_REFRESHFILE, OnRefreshFileButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FileFormViewButtonToolBar
//---------------------------------------------------------------------------
PSS_FileFormViewButtonToolBar::PSS_FileFormViewButtonToolBar(CWnd* pParent) :
    m_pParent(pParent)
{
    m_ImageList.Create(IDB_FILE_FV_BUTTONS, 14, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_FileFormViewButtonToolBar::~PSS_FileFormViewButtonToolBar()
{}
//---------------------------------------------------------------------------
void PSS_FileFormViewButtonToolBar::SetParent(CWnd* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
void PSS_FileFormViewButtonToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();

    int iconIndex = 0;

    CRect rc;
    GetWindowRect(&rc);
    ScreenToClient(&rc);
    rc.top    += 1;
    rc.bottom -= 1;
    rc.left   += 1;
    rc.right   = rc.left + 20;

    if (!m_StopWebButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_STOPFILE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_StopWebButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(14, 14));
    rc.OffsetRect(20, 0);

    if (!m_RefreshWebButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_REFRESHFILE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_RefreshWebButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(14, 14));

    // create the tooltip control
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);

    m_ToolTip.AddTool(GetDlgItem(IDC_STOPFILE), IDS_STOPFILE);
    m_ToolTip.AddTool(GetDlgItem(IDC_REFRESHFILE), IDS_REFRESHFILE);
}
//---------------------------------------------------------------------------
BOOL PSS_FileFormViewButtonToolBar::PreTranslateMessage(MSG* pMsg)
{
    // let the tooltip process this message
    m_ToolTip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
int PSS_FileFormViewButtonToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}
//---------------------------------------------------------------------------
void PSS_FileFormViewButtonToolBar::OnStopFileButton()
{
    if (m_pParent)
        m_pParent->SendMessage(UM_STOPFILE);
}
//---------------------------------------------------------------------------
void PSS_FileFormViewButtonToolBar::OnRefreshFileButton()
{
    if (m_pParent)
        m_pParent->SendMessage(UM_REFRESHFILE);
}
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_FileFormView, CFormView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FileFormView, CFormView)
    //{{AFX_MSG_MAP(PSS_FileFormView)
    ON_WM_SIZE()
    ON_NOTIFY(TVN_SELCHANGED, IDC_FILETREE, OnSelchangedDirectory)
    ON_NOTIFY(NM_DBLCLK, IDC_FILETREE, OnDblclkDirectory)
    ON_NOTIFY(NM_CLICK, IDC_FILETREE, OnClickDirectory)
    ON_MESSAGE(UM_STOPFILE, OnStopFileButton)
    ON_MESSAGE(UM_REFRESHFILE, OnRefreshWebButton)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FileFormView
//---------------------------------------------------------------------------
PSS_FileFormView::PSS_FileFormView() :
    CFormView(PSS_FileFormView::IDD)
{
    // defines the edit as search for file
    m_FileName.SetSearchType(PSS_SearchEditButton::IEType::IE_T_File, "");
}
//---------------------------------------------------------------------------
PSS_FileFormView::~PSS_FileFormView()
{}
//---------------------------------------------------------------------------
void PSS_FileFormView::OnInitialUpdate( )
{
    CFormView::OnInitialUpdate();

    m_DirTreeCtrl.Initialize("", true, true);

    // assign the parent's toolbar
    m_FlatToolBar.SetParent(this);

    // initialize the edit for drag & drop
    m_FileName.Init();
}
//---------------------------------------------------------------------------
void PSS_FileFormView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(ZVFileFormView)
    DDX_Control(pDX, IDC_FILENAME,    m_FileName);
    DDX_Control(pDX, IDC_FILETREE,    m_DirTreeCtrl);
    DDX_Control(pDX, IDC_FLATTOOLBAR, m_FlatToolBar);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FileFormView::AssertValid() const
    {
        CFormView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FileFormView::Dump(CDumpContext& dc) const
    {
        CFormView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_FileFormView::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);
    SizeControl();
}
void PSS_FileFormView::OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult)
{
    ReflectChangedDirectory();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_FileFormView::OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult)
{
    ReflectChangedDirectory();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_FileFormView::OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult)
{
    ReflectChangedDirectory();
    *pResult = 0;
}
//---------------------------------------------------------------------------
LRESULT PSS_FileFormView::OnStopFileButton(WPARAM wParam, LPARAM lParam)
{
    return 1;
}
//---------------------------------------------------------------------------
LRESULT PSS_FileFormView::OnRefreshWebButton(WPARAM wParam, LPARAM lParam)
{
    m_DirTreeCtrl.Refresh();
    return 1;
}
//---------------------------------------------------------------------------
void PSS_FileFormView::SizeControl()
{
    if (GetDlgItem(IDC_FILENAME) && ::IsWindow(GetDlgItem(IDC_FILENAME)->GetSafeHwnd()))
    {
        CRect rect;
        GetClientRect(&rect);

        // if the rect is empty, nothing to do
        if (rect.IsRectEmpty())
            return;

        if (GetDlgItem(IDC_FILENAME))
        {
            CRect editRect;
            GetDlgItem(IDC_FILENAME)->GetClientRect(&editRect);

            editRect.top    = rect.top     + 25;
            editRect.bottom = editRect.top + __max(editRect.Height(), 20);
            editRect.left   = rect.left    + 2;
            editRect.right  = rect.right   - 2;
            GetDlgItem(IDC_FILENAME)->MoveWindow(&editRect);
        }

        if (::IsWindow(m_DirTreeCtrl.GetSafeHwnd()))
        {
            CRect dirTreeRect;
            m_DirTreeCtrl.GetClientRect(&dirTreeRect);

            dirTreeRect.bottom = rect.bottom - 2;
            dirTreeRect.right  = rect.right  - 2;
            dirTreeRect.top    = rect.top    + 50;
            dirTreeRect.left   = rect.left   + 2;
            m_DirTreeCtrl.MoveWindow(&dirTreeRect);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_FileFormView::ReflectChangedDirectory()
{
    if (m_DirTreeCtrl.IsValid())
    {
        CString fileName = m_DirTreeCtrl.GetSelectedDirectory();
        m_FileName.GetWindowText(fileName);
    }
}
//---------------------------------------------------------------------------
