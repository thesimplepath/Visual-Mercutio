/****************************************************************************
 * ==> PSS_FileFormPreviewDialog -------------------------------------------*
 ****************************************************************************
 * Description : Provides a file form preview dialog                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FileFormPreviewDialog.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_File.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FileFormPreviewButtonToolBar, CStatic)
    //{{AFX_MSG_MAP(PSS_FileFormPreviewButtonToolBar)
    ON_BN_CLICKED(IDC_NEXTPAGE, OnNextPageButton)
    ON_BN_CLICKED(IDC_PREVPAGE, OnPreviousPageButton)
    ON_BN_CLICKED(IDC_REFRESH, OnRefreshButton)
    ON_BN_CLICKED(IDC_ZOOM_OUT, OnZoomOutButton)
    ON_BN_CLICKED(IDC_ZOOM_IN, OnZoomInButton)
    ON_BN_CLICKED(IDC_NEXTFILE, OnNextFileButton)
    ON_BN_CLICKED(IDC_PREVFILE, OnPrevFileButton)
    ON_BN_CLICKED(IDC_CLOSEFILE, OnCloseButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FileFormPreviewButtonToolBar
//---------------------------------------------------------------------------
PSS_FileFormPreviewButtonToolBar::PSS_FileFormPreviewButtonToolBar() :
    CStatic(),
    m_pParent(NULL)
{
    // create the image list used by frame buttons.
    m_ImageList.Create(IDB_BUTTONSFILEPREVIEWDLG, 18, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_FileFormPreviewButtonToolBar::~PSS_FileFormPreviewButtonToolBar()
{}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewButtonToolBar::SetParent(CWnd* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewButtonToolBar::PreSubclassWindow()
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

    if (!m_PreviousPageButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_PREVPAGE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_PreviousPageButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(18, 18));
    rc.OffsetRect(20, 0);

    if (!m_NextPageButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_NEXTPAGE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_NextPageButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(18, 18));
    rc.OffsetRect(20, 0);

    if (!m_RefreshButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_REFRESH))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(18, 18));
    rc.OffsetRect(20, 0);

    if (!m_ZoomOutButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_ZOOM_OUT))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_ZoomOutButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(18, 18));
    rc.OffsetRect(20, 0);

    if (!m_ZoomInButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_ZOOM_IN))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_ZoomInButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(18, 18));
    rc.OffsetRect(20, 0);

    if (!m_PreviousFileButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_PREVFILE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_PreviousFileButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(18, 18));
    rc.OffsetRect(20, 0);

    if (!m_NextFileButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_NEXTFILE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_NextFileButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(18, 18));
    rc.OffsetRect(20, 0);

    if (!m_CloseFileButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, rc, this, IDC_CLOSEFILE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }

    m_CloseFileButton.SetIcon(m_ImageList.ExtractIcon(++iconIndex), CSize(18, 18));

    // create the ToolTip control.
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);

    m_ToolTip.AddTool(GetDlgItem(IDC_NEXTPAGE), IDS_NEXTPAGE_BUTTON);
    m_ToolTip.AddTool(GetDlgItem(IDC_PREVPAGE), IDS_PREVPAGE_BUTTON);
    m_ToolTip.AddTool(GetDlgItem(IDC_REFRESH), IDS_REFRESH_BUTTON);
    m_ToolTip.AddTool(GetDlgItem(IDC_ZOOM_OUT), IDS_ZOOM_OUT_BUTTON);
    m_ToolTip.AddTool(GetDlgItem(IDC_ZOOM_IN), IDS_ZOOM_IN_BUTTON);
    m_ToolTip.AddTool(GetDlgItem(IDC_NEXTFILE), IDS_NEXTFILE_BUTTON);
    m_ToolTip.AddTool(GetDlgItem(IDC_PREVFILE), IDS_PREVFILE_BUTTON);
    m_ToolTip.AddTool(GetDlgItem(IDC_CLOSEFILE), IDS_CLOSEFILE_BUTTON);
}
//---------------------------------------------------------------------------
BOOL PSS_FileFormPreviewButtonToolBar::PreTranslateMessage(MSG* pMsg)
{
    // let the tooltip process this message
    m_ToolTip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
int PSS_FileFormPreviewButtonToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewButtonToolBar::OnPreviousPageButton()
{
    if (m_pParent)
        m_pParent->PostMessage(ID_PAGE_PREV);
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewButtonToolBar::OnNextPageButton()
{
    if (m_pParent)
        m_pParent->PostMessage(ID_PAGE_NEXT);
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewButtonToolBar::OnRefreshButton()
{
    if (m_pParent)
        m_pParent->PostMessage(ID_PAGE_REFRESH);
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewButtonToolBar::OnZoomInButton()
{
    if (m_pParent)
        m_pParent->PostMessage(ID_VIEW_ZOOMIN);
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewButtonToolBar::OnZoomOutButton()
{
    if (m_pParent)
        m_pParent->PostMessage(ID_VIEW_ZOOMOUT);
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewButtonToolBar::OnPrevFileButton()
{
    if (m_pParent)
        m_pParent->PostMessage(ID_FILE_PREV);
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewButtonToolBar::OnNextFileButton()
{
    if (m_pParent)
        m_pParent->PostMessage(ID_FILE_NEXT);
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewButtonToolBar::OnCloseButton()
{
    if (m_pParent)
        m_pParent->PostMessage(WM_CLOSE);
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FileFormPreviewDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_FileFormPreviewDialog)
    ON_WM_SIZE()
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FileFormPreviewDialog
//---------------------------------------------------------------------------
PSS_FileFormPreviewDialog::PSS_FileFormPreviewDialog(const CString& fileName, PSS_DocTemplateEx* pDocTemplate, CWnd* pParent) :
    CDialog(PSS_FileFormPreviewDialog::IDD, pParent),
    m_pView(NULL),
    m_pFrameWindow(NULL),
    m_pDocument(NULL),
    m_pDocTemplate(pDocTemplate),
    m_FileName(fileName)
{}
//---------------------------------------------------------------------------
PSS_FileFormPreviewDialog::~PSS_FileFormPreviewDialog()
{}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_FileFormPreviewDialog)
    DDX_Control(pDX, IDC_FLATTOOLBAR, m_FlatToolBar);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_FileFormPreviewDialog::PreTranslateMessage(MSG* pMsg)
{
    const BOOL proceed = CDialog::PreTranslateMessage(pMsg);

    if (pMsg->message == ID_FILE_PREV)
        TRACE(" AAA ");

    if (m_pFrameWindow)
        m_pFrameWindow->PreTranslateMessage(pMsg);

    return proceed;
}
//---------------------------------------------------------------------------
BOOL PSS_FileFormPreviewDialog::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    if (m_pFrameWindow)
        m_pFrameWindow->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);

    return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewDialog::PostNcDestroy()
{
    // clear window for pump message
    PSS_Global::ClearModalDialogCWnd();

    CDialog::PostNcDestroy();
}
//---------------------------------------------------------------------------
BOOL PSS_FileFormPreviewDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (!GetDlgItem(IDC_FILE_CONTROL))
        // show error message
        return FALSE;

    PSS_File file(m_FileName);

    if (!file.Exist())
        // show error message
        return FALSE;

    if (!m_pDocTemplate)
        // show error message
        return FALSE;

    // set silent mode before opening the file
    PSS_Global::SetOpenFileInSilentMode();
    m_pDocument = (PSS_Document*)m_pDocTemplate->OpenDocumentFile((const char*)m_FileName, FALSE);

    // set back silent mode after having opened the file
    PSS_Global::SetOpenFileInSilentMode(FALSE);

    if (!m_pDocument)
        return FALSE;

    CRect frameRect;
    CRect viewRect;

    GetDlgItem(IDC_FILE_CONTROL)->GetWindowRect(&frameRect);
    viewRect = frameRect;
    ScreenToClient(&frameRect);

    m_pFrameWindow = new CFrameWnd;
    m_pFrameWindow->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, frameRect, this);

    if (!m_pFrameWindow)
        return FALSE;

    m_pFrameWindow->ScreenToClient(&viewRect);

    m_Context.m_pNewViewClass = RUNTIME_CLASS(PSS_ReadView);

    // this is the view's document
    m_Context.m_pCurrentDoc = m_pDocument;

    m_Context.m_pNewDocTemplate = m_pDocTemplate;
    m_Context.m_pLastView       = NULL;
    m_Context.m_pCurrentFrame   = m_pFrameWindow;

    m_pView = new PSS_ReadView;

    if (!m_pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, viewRect, m_pFrameWindow, AFX_IDW_PANE_FIRST, &m_Context))
    {
        AfxMessageBox(_T("Could Not Create View"));
        return FALSE;
    }

    m_pView->Initialize();
    m_pView->ShowWindow(SW_SHOW);

    // size the controls
    SizeControl();

    m_FlatToolBar.SetParent(this);

    // set window for pump message
    PSS_Global::SetModalDialogCWnd(this);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewDialog::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);
    SizeControl();
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewDialog::OnClose()
{
    CloseDocument();
    CDialog::OnClose();
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewDialog::OnOK()
{
    CloseDocument();
    CDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewDialog::SizeControl()
{
    if (GetDlgItem(IDC_FILE_CONTROL) && ::IsWindow(GetDlgItem(IDC_FILE_CONTROL)->GetSafeHwnd()))
    {
        CRect rect;
        GetClientRect(&rect);

        if (m_pView && m_pFrameWindow)
        {
            CRect frameRect;
            m_pFrameWindow->GetClientRect(&frameRect);

            CRect viewRect(frameRect);
            ScreenToClient(&frameRect);

            frameRect.bottom = rect.bottom - 5;
            frameRect.right  = rect.right  - 5;
            frameRect.top    = 38;
            frameRect.left   = 5;

            m_pFrameWindow->MoveWindow(&frameRect);
            m_pView->MoveWindow(&viewRect);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_FileFormPreviewDialog::CloseDocument()
{
    // set silent mode before closing the file
    PSS_Global::SetOpenFileInSilentMode();

    // if the document exists, close it
    if (m_pDocument)
        m_pDocument->OnCloseDocument();

    m_pDocument    = NULL;
    m_pFrameWindow = NULL;
    m_pView        = NULL;

    // set back silent mode after having closed the file
    PSS_Global::SetOpenFileInSilentMode(FALSE);
}
//---------------------------------------------------------------------------
