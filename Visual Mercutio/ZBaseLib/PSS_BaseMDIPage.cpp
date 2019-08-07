/****************************************************************************
 * ==> PSS_BaseMDIPage -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic multiple document interface page          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_BaseMDIPage.h"

// processsoft
#include "PSS_BaseMainFrame.h"
#include "ZDDoc.h"
#include "DocData.h"
#include "ZIView.h"
#include "ZAGlobal.h"
#include "ZBCommandObserverMsg.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Def_OriginalSizeStr _T("100%")
//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
static PSS_BaseMDIPage::IZoom g_ZoomNames[] =
{
    _T("25%"),             25,
    _T("50%"),             50,
    _T("75%"),             75,
    _T("80%"),             80,
    _T("90%"),             90,
    M_Def_OriginalSizeStr, 100,
    _T("125%"),            125,
    _T("150%"),            150,
    _T("200%"),            200,
    _T("300%"),            300,
    NULL,                  0
};

const int  g_SizeZoomCombo     = 70;
const int  g_SizeFileListCombo = 170;
const int  g_SizeSchemaCombo   = 120;
const int  g_SizeStyleCombo    = 120;
const UINT g_MainRow           = 0;
const int  g_ProcContext       = 0;
const int  g_HtmlContext       = 1;
const int  g_FormContext       = 2;
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_BaseMDIPage, PSS_BaseTitleMDIPage)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_BaseMDIPage, PSS_BaseTitleMDIPage)
    //{{AFX_MSG_MAP(PSS_BaseMDIPage)
    ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullScreen)
    ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateViewFullScreen)
    ON_CBN_SELCHANGE(IDC_ZOOM, OnZoomChange)
    ON_CBN_SELCHANGE(IDC_SCHEMA, OnSchemaChange)
    ON_CBN_SELCHANGE(IDC_FILELIST, OnFileChange)
    ON_MESSAGE(UM_FILELISTHASCHANGED, OnFileListChanged)
    ON_MESSAGE(UM_SETDEFAULTFILE, OnSetDefaultFile)
    ON_MESSAGE(UM_SETDEFAULTFILE_OPEN, OnSetDefaultFileOpen)
    ON_MESSAGE(ID_SETDEFAULTSCHEMA, OnSetDefaultSchema)
    ON_MESSAGE(ID_SCHEMALISTHASCHANGED, OnSchemaHasChanged)
    ON_WM_MDIACTIVATE()
    ON_WM_CLOSE()
    ON_MESSAGE(UM_NAVIGATEURL, OnNavigateURL)
    ON_MESSAGE(UM_HIDEHTMLVIEW, OnHideHtmlView)
    ON_MESSAGE(UM_SHOWHTMLVIEW, OnShowHtmlView)
    ON_COMMAND(ID_VIEW_BACKFULLSCREEN, OnViewFullScreen)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_BaseMDIPage
//---------------------------------------------------------------------------
PSS_BaseMDIPage::PSS_BaseMDIPage() :
    PSS_BaseTitleMDIPage(),
    m_pHtmlView(NULL),
    m_CurrentContext(0),
    m_BaseOffset(0),
    m_IndexDropList(0),
    m_IndexDropListStyle(0),
    m_IndexDropListSchema(0),
    m_IndexDropListFile(0),
    m_IsZoomed(FALSE),
    m_IsIconic(FALSE),
    m_HasBeenMaximized(FALSE),
    m_IsHtmlViewVisible(FALSE),
    m_ShowHtmlViewOnly(FALSE)
{}
//---------------------------------------------------------------------------
PSS_BaseMDIPage::~PSS_BaseMDIPage()
{}
//---------------------------------------------------------------------------
void PSS_BaseMDIPage::AddSchema(const CString& schema)
{
    if (::IsWindow(m_Schema.GetSafeHwnd()))
        m_Schema.AddString((const char*)schema);
}
//---------------------------------------------------------------------------
void PSS_BaseMDIPage::RemoveAllSchema()
{
    if (::IsWindow(m_Schema.GetSafeHwnd()))
        m_Schema.ResetContent();
}
//---------------------------------------------------------------------------
void PSS_BaseMDIPage::ViewHtmlView(BOOL show)
{}
//---------------------------------------------------------------------------
int PSS_BaseMDIPage::CreateZoom()
{
    CRect rect;

    // create the zoom combobox
    m_ToolBar.GetItemRect(m_IndexDropList, &rect);

    // 1 pixel down from top of statusbar
    rect.top     = 1;
    rect.left   += m_BaseOffset;
    rect.right   = rect.left + g_SizeZoomCombo;
    rect.bottom  = rect.top + 200;

    if (!m_Percentage.Create(WS_CHILD | WS_BORDER | WS_VISIBLE | CBS_DROPDOWNLIST, rect, &m_ToolBar, IDC_ZOOM))
    {
        // fail to create
        TRACE(_T("Failed to create combobox inside toolbar\n"));
        return -1;
    }

    // add all the available zoom factors
    for (IZoom* pZoom = g_ZoomNames; pZoom->m_pName; ++pZoom)
        m_Percentage.SetItemData(m_Percentage.AddString(pZoom->m_pName), pZoom->m_Factor);

    // select the default zoom factor
    m_Percentage.SelectString(-1, M_Def_OriginalSizeStr);

    return 0;
}
//---------------------------------------------------------------------------
int PSS_BaseMDIPage::CreateSchema()
{
    CRect rect;

    // create the schema combobox
    m_ToolBar.GetItemRect(m_IndexDropListSchema, &rect);

    // 1 pixel down from top of statusbar
    rect.top     = 1;
    rect.left   += m_BaseOffset + g_SizeZoomCombo + g_SizeStyleCombo;
    rect.right   = rect.left    + g_SizeSchemaCombo;
    rect.bottom  = rect.top     + 200;

    if (!m_Schema.Create(WS_CHILD | WS_BORDER | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_SORT, rect, &m_ToolBar, IDC_SCHEMA))
    {
        // fail to create
        TRACE(_T("Failed to create combobox inside toolbar\n"));
        return -1;
    }

    return 0;
}
//---------------------------------------------------------------------------
int PSS_BaseMDIPage::CreateFileList()
{
    CRect rect;

    // Create the file list combobox
    m_ToolBar.GetItemRect(m_IndexDropListFile, &rect);

    // 1 pixel down from top of statusbar
    rect.top     = 1;
    rect.left   += m_BaseOffset + g_SizeZoomCombo + g_SizeStyleCombo + g_SizeSchemaCombo;
    rect.right   = rect.left    + g_SizeFileListCombo;
    rect.bottom  = rect.top     + 200;

    if (!m_FileList.Create(WS_CHILD | WS_BORDER | WS_VISIBLE | CBS_DROPDOWNLIST, rect, &m_ToolBar, IDC_FILELIST))
    {
        // fail to create
        TRACE(_T("Failed to create File List combobox inside toolbar\n"));
        return -1;
    }

    return 0;
}
//---------------------------------------------------------------------------
CView* PSS_BaseMDIPage::SwitchBottomView(CView* pView)
{
    CView*     pOldActiveView = GetBottomView();
    CDocument* pDoc           = pOldActiveView->GetDocument();

    ASSERT(pDoc);

    int row;
    int col;

    VERIFY(m_Splitter.IsChildPane(pOldActiveView, row, col));

    // set flag so that document will not be deleted when view is destroyed
    pDoc->m_bAutoDelete = FALSE;

    // Dettach existing view
    pDoc->RemoveView(pOldActiveView);

    // set flag back to default 
    pDoc->m_bAutoDelete = TRUE;

    // set the child window ID of the active view to the ID of the corresponding
    // pane. Set the child ID of the previously active view to some other ID
    ::SetWindowLong(pOldActiveView->m_hWnd, GWL_ID, 0);
    ::SetWindowLong(pView->m_hWnd, GWL_ID, m_Splitter.IdFromRowCol(row, col));

    // show the newly active view and hide the inactive view
    pView->ShowWindow(SW_SHOW);
    pOldActiveView->ShowWindow(SW_HIDE);

    // attach new view
    pDoc->AddView(pView);

    // set active
    m_Splitter.GetParentFrame()->SetActiveView(pView);

    m_Splitter.RecalcLayout();
    pView->SendMessage(WM_PAINT);

    return pOldActiveView;
}
//---------------------------------------------------------------------------
CView* PSS_BaseMDIPage::SwitchTopView(CView* pView)
{
    CView*     pOldActiveView = GetTopView();
    CDocument* pDoc           = pOldActiveView->GetDocument();

    ASSERT(pDoc);

    int row;
    int col;

    VERIFY(m_Splitter.IsChildPane(pOldActiveView, row, col));

    // set flag so that document will not be deleted when view is destroyed
    pDoc->m_bAutoDelete = FALSE;

    // detach existing view
    pDoc->RemoveView(pOldActiveView);

    // set flag back to default
    pDoc->m_bAutoDelete = TRUE;

    // set the child window ID of the active view to the ID of the corresponding
    // pane. Set the child ID of the previously active view to some other ID
    ::SetWindowLong(pOldActiveView->m_hWnd, GWL_ID, 0);
    ::SetWindowLong(pView->m_hWnd, GWL_ID, m_Splitter.IdFromRowCol(row, col));

    // show the newly active view and hide the inactive view
    pView->ShowWindow(SW_SHOW);
    pOldActiveView->ShowWindow(SW_HIDE);

    // attach new view
    pDoc->AddView(pView);

    // set active
    m_Splitter.GetParentFrame()->SetActiveView(pView);

    m_Splitter.RecalcLayout();
    pView->SendMessage(WM_PAINT);

    return pOldActiveView;
}
//---------------------------------------------------------------------------
CView* PSS_BaseMDIPage::GetBottomView()
{
    CView* pView = DYNAMIC_DOWNCAST(CView, m_Splitter.GetPane(1, 0));

    ASSERT(pView);
    return pView;
}
//---------------------------------------------------------------------------
CView* PSS_BaseMDIPage::GetTopView()
{
    CView* pView = DYNAMIC_DOWNCAST(CView, m_Splitter.GetPane(0, 0));

    ASSERT( pView );
    return pView;
}
//---------------------------------------------------------------------------
void PSS_BaseMDIPage::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
    CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

    AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTHASBEENSELECTED, 0, LPARAM(GetActiveDocument()));

    // send a message to the shema view to specify that current schema has changed
    ZBCommandObserverMsg msg(UM_DEFAULTSCHEMAHASCHANGED);
    dynamic_cast<ZISubject*>(AfxGetMainWnd())->NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_BaseMDIPage::OnViewFullScreen()
{
    // if not in full screen, maximize the window first
    if (!((PSS_BaseMainFrame*)GetMDIFrame())->IsFullScreen())
    {
        // get the window state
        m_IsZoomed = IsZoomed();
        m_IsIconic = IsIconic();

        WINDOWPLACEMENT wp;
        wp.length = sizeof(WINDOWPLACEMENT);
        GetWindowPlacement(&wp);

        // maximize the mdi frame
        if (wp.showCmd != SW_SHOWMAXIMIZED)
        {
            m_HasBeenMaximized = TRUE;
            MDIMaximize();
        }

        m_ToolBar.ShowWindow(SW_HIDE);
        ((PSS_BaseMainFrame*)GetMDIFrame())->OnViewFullScreen();
    }
    else
    {
        m_ToolBar.ShowWindow(SW_SHOW);
        ((PSS_BaseMainFrame*)GetMDIFrame())->OnViewFullScreen();

        if (m_HasBeenMaximized)
        {
            MDIRestore();
            m_HasBeenMaximized = FALSE;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_BaseMDIPage::OnUpdateViewFullScreen(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(((PSS_BaseMainFrame*)GetMDIFrame())->IsFullScreen());
}
//---------------------------------------------------------------------------
afx_msg void PSS_BaseMDIPage::OnZoomChange()
{
    CComboBox* pDrop = (CComboBox*)CWnd::FromHandle(HWND(LOWORD(GetCurrentMessage()->lParam)));

    ASSERT(pDrop);
    ASSERT(pDrop->IsKindOf(RUNTIME_CLASS(CWnd)));

    ZDDocument* pDocument = dynamic_cast<ZDDocument*>(GetActiveDocument());

    if (pDocument)
    {
        // set the new zoom percentage
        pDocument->GetMainView()->SetZoomPercentage(int(pDrop->GetItemData(pDrop->GetCurSel())));
        pDocument->UpdateAllViews(NULL);
    }
}
//---------------------------------------------------------------------------
afx_msg void PSS_BaseMDIPage::OnSchemaChange()
{
    CComboBox* pDrop = (CComboBox*)CWnd::FromHandle(HWND(LOWORD(GetCurrentMessage()->lParam)));

    ASSERT(pDrop);
    ASSERT(pDrop->IsKindOf(RUNTIME_CLASS(CWnd)));

    ZDDocument* pDocument = dynamic_cast<ZDDocument*>(GetActiveDocument());

    if (pDocument)
    {
        CString selection;

        // set the new zoom percentage
        pDrop->GetLBText(pDrop->GetCurSel(), selection);

        pDocument->ChangeCurrentSchema(selection);

        // send a message to the shema view to specify that current schema has changed
        ZBCommandObserverMsg msg(UM_DEFAULTSCHEMAHASCHANGED);
        dynamic_cast<ZISubject*>(AfxGetMainWnd())->NotifyAllObservers(&msg);

        // redraw all views
        pDocument->UpdateAllViews(NULL);
    }
}
//---------------------------------------------------------------------------
afx_msg void PSS_BaseMDIPage::OnFileChange()
{
    CComboBox* pDrop = (CComboBox*)CWnd::FromHandle( (HWND)LOWORD( GetCurrentMessage()->lParam ) );

    ASSERT( pDrop != NULL );
    ASSERT( pDrop->IsKindOf( RUNTIME_CLASS( CWnd ) ) );

    if ( GetActiveDocument() && ISA( GetActiveDocument(), ZDDocument ) )
    {
        // Assign the new zoom percentage
        if ( pDrop->GetCurSel() != CB_ERR )
        {
            CWaitCursor    Cursor;
            ( (ZDDocument*)GetActiveDocument() )->ChangeCurrentFile ( pDrop->GetCurSel() );
            ( (ZDDocument*)GetActiveDocument() )->UpdateAllViews( NULL );
        }
    }
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_BaseMDIPage::OnFileListChanged(UINT message, LONG lParam)
{
    if (!::IsWindow(m_FileList.GetSafeHwnd()))
        return 0;

    ZDDocument* pDocument = dynamic_cast<ZDDocument*>(GetActiveDocument());

    if (!pDocument)
        pDocument = ZAGlobal::GetpCurrentDocumentForSerialization();

    if (pDocument)
    {
        CStringArray stringArray;
        pDocument->GetDocumentDataName(stringArray);
        m_FileList.ResetContent();

        for (int i = 0; i < stringArray.GetSize(); ++i)
            m_FileList.AddString((const char*)stringArray[i]);
    }

    return 0;
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_BaseMDIPage::OnSetDefaultFile(UINT message, LONG wParam)
{
    if (!::IsWindow(m_FileList.GetSafeHwnd()))
        return 0;

    // if there is no item, do nothing
    if (m_FileList.GetCount() <= 0)
        return 1;

    const int index = m_FileList.FindString(-1, (const char*)wParam);

    if (index != CB_ERR)
        m_FileList.SetCurSel(index);

    if (message == 1)
    {
        ZDDocument* pDocument = dynamic_cast<ZDDocument*>(GetActiveDocument());

        if (pDocument)
        {
            pDocument->ChangeCurrentFile(index);
            pDocument->UpdateAllViews(NULL);
        }
    }

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_BaseMDIPage::OnSetDefaultFileOpen(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(m_FileList.GetSafeHwnd()))
        return 0;

    // if there is no item, do nothing
    if (m_FileList.GetCount() <= 0)
        return 1;

    const int index = m_FileList.FindString(-1, (const char*)lParam);

    if (index != CB_ERR)
        m_FileList.SetCurSel(index);

    if (wParam == 1)
    {
        ZDDocument* pDocument = dynamic_cast<ZDDocument*>(GetActiveDocument());

        if (pDocument)
        {
            pDocument->ChangeCurrentFileOpen(index);
            pDocument->UpdateAllViews(NULL);
        }

        return 1;
    }

    return 0;
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_BaseMDIPage::OnSetDefaultSchema(UINT message, LONG wParam)
{
    // if there are items, it is not necessary to initialize the list
    if (!::IsWindow(m_Schema.GetSafeHwnd()))
        return 0;

    if (m_Schema.GetCount() <= 0)
        OnSchemaHasChanged(0, 0L);

    const int index = m_Schema.FindString(-1, (const char*)wParam);

    if (index != CB_ERR)
        m_Schema.SetCurSel(index);

    return (1);
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_BaseMDIPage::OnSchemaHasChanged(UINT message, LONG wParam)
{
    if (!::IsWindow(m_Schema.GetSafeHwnd()))
        return 0;

    ZDDocument* pDocument = dynamic_cast<ZDDocument*>(GetActiveDocument());

    if (!pDocument)
        pDocument = ZAGlobal::GetpCurrentDocumentForSerialization();

    if (pDocument)
    {
        if (pDocument->GetActiveDocumentData())
        {
            CStringArray& stringArray = pDocument->GetActiveDocumentData()->GetSchema().GetFormulaArrayName();
            RemoveAllSchema();

            const int arrayCount = stringArray.GetSize();

            for (int i = 0; i < arrayCount; ++i)
                AddSchema(stringArray[i]);
        }

        return 1;
    }

    return 0;
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_BaseMDIPage::OnNavigateURL(WPARAM wParam, LPARAM lParam)
{
    ZDDocument* pDocument = dynamic_cast<ZDDocument*>(GetActiveDocument());

    if (pDocument)
    {
        ZIHtmlView* pHtmlView = pDocument->GetHtmlView();

        if (pHtmlView)
            pHtmlView->Navigate((const char*)lParam, FALSE);

        return 1;
    }

    return 0;
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_BaseMDIPage::OnShowHtmlView(WPARAM wParam, LPARAM lParam)
{
    CDocument* pDoc  = (CDocument*)lParam;
    CView*     pView = GetActiveView();

    if (pView)
    {
        CDocument* pViewDoc = pView->GetDocument();

        // is the right document?
        if (pViewDoc && pViewDoc == pDoc)
        {
            ChangeContext(g_HtmlContext);
            return 1;
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_BaseMDIPage::OnHideHtmlView(WPARAM wParam, LPARAM lParam)
{
    CDocument* pDoc  = (CDocument*)lParam;
    CView*     pView = GetActiveView();

    if (pView)
    {
        CDocument* pViewDoc = pView->GetDocument();

        // is the right document?
        if (pViewDoc && pViewDoc == pDoc)
        {
            ChangeContext(g_ProcContext);
            return 1;
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
void PSS_BaseMDIPage::OnClose()
{
    PSS_BaseTitleMDIPage::OnClose();

    AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTHASBEENSELECTED, 0, LPARAM(NULL));
}
//---------------------------------------------------------------------------
