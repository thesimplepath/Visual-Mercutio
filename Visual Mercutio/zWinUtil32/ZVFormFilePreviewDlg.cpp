/****************************************************************************
 * ==> PSS_FormFilePreviewDialog -------------------------------------------*
 ****************************************************************************
 * Description : Provides a form file preview dialog                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "ZVFormFilePreviewDlg.h"

#include "zBaseLib\File.h"
// ZAGlobal
#include "zBaseLib\ZAGlobal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVFormFilePreviewDlg dialog


ZVFormFilePreviewDlg::ZVFormFilePreviewDlg(const CString Filename, ZDDocTemplateEx* pDocTemplate, CWnd* pParent /*=NULL*/)
    : CDialog(ZVFormFilePreviewDlg::IDD, pParent),
    m_Filename(Filename), m_pDocTemplate(pDocTemplate), 
    m_pView(NULL), m_pFrameWindow(NULL), m_pDocument(NULL)
{
    //{{AFX_DATA_INIT(ZVFormFilePreviewDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


ZVFormFilePreviewDlg::~ZVFormFilePreviewDlg()
{
}

void ZVFormFilePreviewDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVFormFilePreviewDlg)
    DDX_Control(pDX, IDC_FLATTOOLBAR, m_FlatToolBar);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVFormFilePreviewDlg, CDialog)
    //{{AFX_MSG_MAP(ZVFormFilePreviewDlg)
    ON_WM_SIZE()
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ZVFormFilePreviewDlg::CloseDocument()
{
    // Set silent mode before closing the file
    ZAGlobal::SetOpenFileInSilentMode();
    // If the document exists, close it
    if (m_pDocument)
        m_pDocument->OnCloseDocument();
    m_pDocument = NULL;
    m_pFrameWindow = NULL;
    m_pView = NULL;
    // Set back silent mode after having closed the file
    ZAGlobal::SetOpenFileInSilentMode( FALSE );
}

void ZVFormFilePreviewDlg::SizeControl() 
{
    if (GetDlgItem(IDC_FILE_CONTROL) &&
        ::IsWindow(GetDlgItem(IDC_FILE_CONTROL)->GetSafeHwnd()))
    {
        CRect rect;
        GetClientRect(&rect);
/*
        if (GetDlgItem(IDOK))
        {
            CRect ButtonRect;
            GetDlgItem(IDOK)->GetClientRect(&ButtonRect);
            int cx = ButtonRect.Width();
            int cy = ButtonRect.Height();
            ButtonRect.bottom = rect.bottom - 5;
            ButtonRect.right = rect.right - 5;
            ButtonRect.top = ButtonRect.bottom - cy;
            ButtonRect.left = ButtonRect.right - cx;
            GetDlgItem(IDOK)->MoveWindow( &ButtonRect );
        }
*/
        if (m_pView && m_pFrameWindow)
        {
            CRect FrameRect;
            m_pFrameWindow->GetClientRect(&FrameRect);
            CRect ViewRect(FrameRect);
            ScreenToClient(&FrameRect); 

            int cx = FrameRect.Width();
            int cy = FrameRect.Height();
            FrameRect.bottom = rect.bottom - 5;
            FrameRect.right = rect.right - 5;
            FrameRect.top = 38;
            FrameRect.left = 5;
            m_pFrameWindow->MoveWindow( &FrameRect );
            m_pView->MoveWindow( &ViewRect );
        }
    }    
}

/////////////////////////////////////////////////////////////////////////////
// ZVFormFilePreviewDlg message handlers

BOOL ZVFormFilePreviewDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

    if (!GetDlgItem(IDC_FILE_CONTROL))
    {
        // Display error message
        return FALSE;
    }
    
    ZFile    File(m_Filename);
    if (!File.Exist())
    {
        // Display error message
        return FALSE;
    }
    if (!m_pDocTemplate)
    {
        // Display error message
        return FALSE;
    }


    // Set silent mode before opening the file
    ZAGlobal::SetOpenFileInSilentMode();
    m_pDocument = (ZDDocument*) m_pDocTemplate->OpenDocumentFile( (const char*)m_Filename, FALSE );
    // Set back silent mode after having opened the file
    ZAGlobal::SetOpenFileInSilentMode( FALSE );
    
    if (!m_pDocument)
    {
        return FALSE;
    }


    CRect FrameRect; 
    CRect ViewRect; 

    GetDlgItem(IDC_FILE_CONTROL)->GetWindowRect (&FrameRect); 
    ViewRect = FrameRect; 
    ScreenToClient(&FrameRect); 

    m_pFrameWindow = new CFrameWnd; 
    m_pFrameWindow->Create(NULL,NULL,WS_CHILD|WS_VISIBLE,FrameRect,this); 

    if (m_pFrameWindow == NULL) 
    { 
        return FALSE; 
    } 

    m_pFrameWindow ->ScreenToClient(&ViewRect); 

    m_Context.m_pNewViewClass = RUNTIME_CLASS(ZIViewRead); 

    // This is the Document of your view. 
    m_Context.m_pCurrentDoc = m_pDocument; 

    m_Context.m_pNewDocTemplate = m_pDocTemplate; 
    m_Context.m_pLastView = NULL; 
    m_Context.m_pCurrentFrame = m_pFrameWindow; 

    m_pView = new ZIViewRead; 
    if (!m_pView->Create(NULL,NULL,AFX_WS_DEFAULT_VIEW, ViewRect, m_pFrameWindow, AFX_IDW_PANE_FIRST,&m_Context)) 
    { 
        AfxMessageBox ("Could Not Create View"); 
        return FALSE; 
    } 
    m_pView->Initialize();

    m_pView->ShowWindow(SW_SHOW); 
    
    // Finally, size the controls
    SizeControl();
    
    m_FlatToolBar.SetParent(this);
    // Set handle window for pump message
    ZAGlobal::SetModalDialogCWnd( this );

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVFormFilePreviewDlg::OnSize(UINT nType, int cx, int cy) 
{
    CDialog::OnSize(nType, cx, cy);
    
    SizeControl();
    
}


BOOL ZVFormFilePreviewDlg::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
    if (m_pFrameWindow)
        m_pFrameWindow->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
    return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL ZVFormFilePreviewDlg::PreTranslateMessage(MSG* pMsg) 
{
    BOOL    Proceed = CDialog::PreTranslateMessage(pMsg);
    if (pMsg->message == ID_FILE_PREV)
    {
        TRACE(" AAA ");
    }
    if (m_pFrameWindow)
        m_pFrameWindow->PreTranslateMessage(pMsg);
//    if (m_pView)
//        m_pView->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam );
    return Proceed;
}

void ZVFormFilePreviewDlg::PostNcDestroy() 
{
    // Clear handle window for pump message
    ZAGlobal::ClearModalDialogCWnd();
    
    CDialog::PostNcDestroy();
}

void ZVFormFilePreviewDlg::OnClose() 
{
    CloseDocument();
    CDialog::OnClose();
}

void ZVFormFilePreviewDlg::OnOK() 
{
    CloseDocument();
    CDialog::OnOK();
}





/////////////////////////////////////////////////////////////////////////////
// ZIButtonToolBarFormFilePreview

ZIButtonToolBarFormFilePreview::ZIButtonToolBarFormFilePreview()
{
    // Create the image list used by frame buttons.
    m_ImageList.Create(IDB_BUTTONSFILEPREVIEWDLG,
        18, 1, RGB(255,0,255));
}

ZIButtonToolBarFormFilePreview::~ZIButtonToolBarFormFilePreview()
{
}

void ZIButtonToolBarFormFilePreview::SetParent(CWnd* pParent) 
{
    m_pParent = pParent;
}

BEGIN_MESSAGE_MAP(ZIButtonToolBarFormFilePreview, CStatic)
    //{{AFX_MSG_MAP(ZIButtonToolBarFormFilePreview)
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

/////////////////////////////////////////////////////////////////////////////
// ZIButtonToolBarFormFilePreview message handlers

int ZIButtonToolBarFormFilePreview::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;


    return 0;
}

void ZIButtonToolBarFormFilePreview::PreSubclassWindow() 
{
    CStatic::PreSubclassWindow();

    int    IconIndex = 0;

    CRect rc;
    GetWindowRect(&rc);
    ScreenToClient(&rc);
    rc.top+=1; rc.bottom-=1;
    rc.left+=1;
    rc.right = rc.left+20;

    if (!m_PreviousPageButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
        rc, this, IDC_PREVPAGE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }
    m_PreviousPageButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(18,18));
    rc.OffsetRect(20,0);

    if (!m_NextPageButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
        rc, this, IDC_NEXTPAGE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }
    m_NextPageButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(18,18));
    rc.OffsetRect(20,0);

    if (!m_RefreshButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
        rc, this, IDC_REFRESH))
    {
        TRACE0("Unable to create button.\n");
        return;
    }
    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(18,18));
    rc.OffsetRect(20,0);

    if (!m_ZoomOutButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
        rc, this, IDC_ZOOM_OUT))
    {
        TRACE0("Unable to create button.\n");
        return;
    }
    m_ZoomOutButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(18,18));
    rc.OffsetRect(20,0);

    if (!m_ZoomInButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
        rc, this, IDC_ZOOM_IN))
    {
        TRACE0("Unable to create button.\n");
        return;
    }
    m_ZoomInButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(18,18));
    rc.OffsetRect(20,0);

    if (!m_PreviousFileButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
        rc, this, IDC_PREVFILE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }
    m_PreviousFileButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(18,18));
    rc.OffsetRect(20,0);

    if (!m_NextFileButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
        rc, this, IDC_NEXTFILE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }
    m_NextFileButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(18,18));
    rc.OffsetRect(20,0);

    if (!m_CloseFileButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
        rc, this, IDC_CLOSEFILE))
    {
        TRACE0("Unable to create button.\n");
        return;
    }
    m_CloseFileButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(18,18));



    // Create the ToolTip control.
    m_tooltip.Create(this);
    m_tooltip.Activate(TRUE);

    // TODO: Use one of the following forms to add controls:
    m_tooltip.AddTool(GetDlgItem(IDC_NEXTPAGE), IDS_NEXTPAGE_BUTTON);
    m_tooltip.AddTool(GetDlgItem(IDC_PREVPAGE), IDS_PREVPAGE_BUTTON);
    m_tooltip.AddTool(GetDlgItem(IDC_REFRESH), IDS_REFRESH_BUTTON);
    m_tooltip.AddTool(GetDlgItem(IDC_ZOOM_OUT), IDS_ZOOM_OUT_BUTTON);
    m_tooltip.AddTool(GetDlgItem(IDC_ZOOM_IN), IDS_ZOOM_IN_BUTTON);
    m_tooltip.AddTool(GetDlgItem(IDC_NEXTFILE), IDS_NEXTFILE_BUTTON);
    m_tooltip.AddTool(GetDlgItem(IDC_PREVFILE), IDS_PREVFILE_BUTTON);
    m_tooltip.AddTool(GetDlgItem(IDC_CLOSEFILE), IDS_CLOSEFILE_BUTTON);
}




void ZIButtonToolBarFormFilePreview::OnNextPageButton() 
{
    if (m_pParent)
        m_pParent->PostMessage( ID_PAGE_NEXT );
}

void ZIButtonToolBarFormFilePreview::OnPreviousPageButton() 
{
    if (m_pParent)
        m_pParent->PostMessage( ID_PAGE_PREV );
}

void ZIButtonToolBarFormFilePreview::OnRefreshButton() 
{
    if (m_pParent)
        m_pParent->PostMessage( ID_PAGE_REFRESH );
}

void ZIButtonToolBarFormFilePreview::OnZoomOutButton() 
{
    if (m_pParent)
        m_pParent->PostMessage( ID_VIEW_ZOOMOUT );
}

void ZIButtonToolBarFormFilePreview::OnZoomInButton() 
{
    if (m_pParent)
        m_pParent->PostMessage( ID_VIEW_ZOOMIN );
}


void ZIButtonToolBarFormFilePreview::OnNextFileButton() 
{
    if (m_pParent)
        m_pParent->PostMessage( ID_FILE_NEXT );
}

void ZIButtonToolBarFormFilePreview::OnPrevFileButton() 
{
    if (m_pParent)
        m_pParent->PostMessage( ID_FILE_PREV );
}

void ZIButtonToolBarFormFilePreview::OnCloseButton() 
{
    if (m_pParent)
        m_pParent->PostMessage( WM_CLOSE );
}



BOOL ZIButtonToolBarFormFilePreview::PreTranslateMessage(MSG* pMsg) 
{
    // Let the ToolTip process this message.
    m_tooltip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}

