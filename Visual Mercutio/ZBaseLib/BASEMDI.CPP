// BaseMDI.cpp : implementation file
//

#include "stdafx.h"
#include "BaseMDI.h"
#include "basefrm.h"

#include "ZDDoc.h"

// DocData
#include "DocData.h"

#include "ZIView.h"
#include "ZAGlobal.h"

#include "ZBCommandObserverMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#define    def_ORIGINALSIZESTR        _T( "100%" )

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

struct ZOOM_TYPES
{
    char*   pZoom;
    int     nZoom;
};

static ZOOM_TYPES zoomNames[] =
{
    _T( "25%" ),            25,
    _T( "50%" ),            50,
    _T( "75%" ),            75,
    _T( "80%" ),            80,
    _T( "90%" ),            90,
    def_ORIGINALSIZESTR,    100,
    _T( "125%" ),            125,
    _T( "150%" ),            150,
    _T( "200%" ),            200,
    _T( "300%" ),            300,
    NULL,                    0
};

/////////////////////////////////////////////////////////////////////////////
// ZIBaseMDIPage

IMPLEMENT_DYNCREATE( ZIBaseMDIPage, ZIBaseTitleMDIPage )

BEGIN_MESSAGE_MAP( ZIBaseMDIPage, ZIBaseTitleMDIPage )
    //{{AFX_MSG_MAP(ZIBaseMDIPage)
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

ZIBaseMDIPage::ZIBaseMDIPage()
    : m_HasBeenMaximized    ( FALSE ), 
      m_IsZoomed            ( FALSE ), 
      m_IsIconic            ( FALSE ), 
      m_bIsHtmlViewVisible    ( FALSE ), 
      m_ShowOnlyHtmlView    ( FALSE ), 
      m_pHtmlView            ( NULL )
{
}

ZIBaseMDIPage::~ZIBaseMDIPage()
{
}

CView* ZIBaseMDIPage::SwitchTopView( CView* pView )
{
    CView*            pOldActiveView    = GetTopView();
    CDocument*        pDoc            = pOldActiveView->GetDocument();
    ASSERT( pDoc );

    int row;
    int col;

    VERIFY( m_wndSplitter.IsChildPane( pOldActiveView, row, col ) );

    // set flag so that document will not be deleted when view is destroyed
    pDoc->m_bAutoDelete = FALSE;    

    // Dettach existing view
    pDoc->RemoveView( pOldActiveView );

    // set flag back to default 
    pDoc->m_bAutoDelete = TRUE;

    // Set the child window ID of the active view to the ID of the corresponding
    // pane. Set the child ID of the previously active view to some other ID.
    ::SetWindowLong( pOldActiveView->m_hWnd, GWL_ID, 0 );
    ::SetWindowLong( pView->m_hWnd, GWL_ID, m_wndSplitter.IdFromRowCol( row, col ) );

    // Show the newly active view and hide the inactive view.
    pView->ShowWindow( SW_SHOW );
    pOldActiveView->ShowWindow( SW_HIDE );

    // Attach new view
    pDoc->AddView( pView );

    // Set active 
    m_wndSplitter.GetParentFrame()->SetActiveView( pView );

    m_wndSplitter.RecalcLayout();
    pView->SendMessage( WM_PAINT );

    return pOldActiveView;
}

CView* ZIBaseMDIPage::GetTopView()
{
    CView* pView = DYNAMIC_DOWNCAST( CView, m_wndSplitter.GetPane( 0, 0 ) );

    ASSERT( pView );
    return pView;
}

CView* ZIBaseMDIPage::SwitchBottomView( CView* pView )
{
    CView*            pOldActiveView    = GetBottomView();
    CDocument*        pDoc            = pOldActiveView->GetDocument();

    ASSERT( pDoc );

    int row;
    int col;

    VERIFY( m_wndSplitter.IsChildPane( pOldActiveView, row, col ) );

    // set flag so that document will not be deleted when view is destroyed
    pDoc->m_bAutoDelete = FALSE;    

    // Dettach existing view
    pDoc->RemoveView( pOldActiveView );

    // set flag back to default 
    pDoc->m_bAutoDelete = TRUE;

    // Set the child window ID of the active view to the ID of the corresponding
    // pane. Set the child ID of the previously active view to some other ID.
    ::SetWindowLong( pOldActiveView->m_hWnd, GWL_ID, 0 );
    ::SetWindowLong( pView->m_hWnd, GWL_ID, m_wndSplitter.IdFromRowCol( row, col ) );

    // Show the newly active view and hide the inactive view.
    pView->ShowWindow( SW_SHOW );
    pOldActiveView->ShowWindow( SW_HIDE );

    // Attach new view
    pDoc->AddView( pView );

    // Set active 
    m_wndSplitter.GetParentFrame()->SetActiveView( pView );

    m_wndSplitter.RecalcLayout();
    pView->SendMessage( WM_PAINT );

    return pOldActiveView;
}

CView* ZIBaseMDIPage::GetBottomView()
{
    CView* pView = DYNAMIC_DOWNCAST( CView, m_wndSplitter.GetPane( 1, 0 ) );

    ASSERT( pView );
    return pView;
}

void ZIBaseMDIPage::AddSchema( const CString& sValue )
{
    if ( ::IsWindow( m_cbxSchema.GetSafeHwnd() ) )
        m_cbxSchema.AddString( (const char*) sValue );
}

void ZIBaseMDIPage::RemoveAllSchema()
{
    if ( ::IsWindow( m_cbxSchema.GetSafeHwnd() ) )
        m_cbxSchema.ResetContent();
}

/////////////////////////////////////////////////////////////////////////////
// ZIBaseMDIPage message handlers

afx_msg void ZIBaseMDIPage::OnZoomChange()
{
    CComboBox* pDrop = (CComboBox*)CWnd::FromHandle( (HWND)LOWORD( GetCurrentMessage()->lParam ) );

    ASSERT( pDrop != NULL );
    ASSERT( pDrop->IsKindOf( RUNTIME_CLASS( CWnd ) ) );

    if ( GetActiveDocument() && ISA( GetActiveDocument(), ZDDocument ) )
    {
        // Assign the new zoom percentage
        ( (ZDDocument*)GetActiveDocument())->GetMainView()->SetZoomPercentage( (int)pDrop->GetItemData( pDrop->GetCurSel() ) );

        ( (ZDDocument*)GetActiveDocument() )->UpdateAllViews( NULL );
    }
}

afx_msg void ZIBaseMDIPage::OnSchemaChange()
{
    CComboBox* pDrop = (CComboBox*)CWnd::FromHandle( (HWND)LOWORD( GetCurrentMessage()->lParam ) );

    ASSERT( pDrop != NULL );
    ASSERT( pDrop->IsKindOf( RUNTIME_CLASS( CWnd ) ) );

    // Assign the new zoom percentage
    CString    sSel;
    pDrop->GetLBText( pDrop->GetCurSel(), sSel );

    if ( GetActiveDocument() && ISA( GetActiveDocument(), ZDDocument ) )
    {
        ( (ZDDocument*)GetActiveDocument() )->ChangeCurrentSchema( sSel );

        // Send a message to the shema view to specify that current schema has changed
        ZBCommandObserverMsg Msg( UM_DEFAULTSCHEMAHASCHANGED );
        dynamic_cast<ZISubject*>( AfxGetMainWnd() )->NotifyAllObservers( &Msg );

        // Redraw all views
        ( (ZDDocument*)GetActiveDocument() )->UpdateAllViews( NULL );
    }
}

afx_msg void ZIBaseMDIPage::OnFileChange()
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

afx_msg LONG ZIBaseMDIPage::OnFileListChanged( UINT message, LONG lParam )
{
    if ( !::IsWindow( m_cbxFileList.GetSafeHwnd() ) )
        return 0;

    if ( GetActiveDocument() && ISA( GetActiveDocument(), ZDDocument ) )
    {
        ZDDocument*    pDoc = ( (ZDDocument*)GetActiveDocument() );

        if ( !pDoc )
            pDoc = ZAGlobal::GetpCurrentDocumentForSerialization();

        CStringArray StringArray;
        pDoc->GetDocumentDataName( StringArray );
        m_cbxFileList.ResetContent();

        for ( int i = 0; i < StringArray.GetSize(); ++i )
            m_cbxFileList.AddString( (const char*) StringArray[i] );
    }

    return 0;
}

afx_msg LONG ZIBaseMDIPage::OnSetDefaultSchema( UINT message, LONG wParam )
{
    // If there is items, it is not necessary to initialize the list
    if ( !::IsWindow( m_cbxSchema.GetSafeHwnd() ) )
        return 0;

    if ( m_cbxSchema.GetCount() <= 0 )
        OnSchemaHasChanged( 0, 0L );

    int iIndex = m_cbxSchema.FindString( -1, (const char*)wParam );

    if ( iIndex != CB_ERR )
        m_cbxSchema.SetCurSel( iIndex );

    return( 1 );
}

afx_msg LONG ZIBaseMDIPage::OnSetDefaultFile( UINT message, LONG wParam )
{
    if ( !::IsWindow( m_cbxFileList.GetSafeHwnd() ) )
        return 0;

    // If there is no item, do nothing
    if ( m_cbxFileList.GetCount() <= 0 )
        return 1;

    int iIndex = m_cbxFileList.FindString( -1, (const char*)wParam );

    if ( iIndex != CB_ERR )
        m_cbxFileList.SetCurSel( iIndex );

    if ( message == 1 && GetActiveDocument() && ISA( GetActiveDocument(), ZDDocument ) )
    {
        CWaitCursor    Cursor;
        ( (ZDDocument*)GetActiveDocument() )->ChangeCurrentFile ( iIndex );
        ( (ZDDocument*)GetActiveDocument() )->UpdateAllViews( NULL );
    }

    return 1;
}

afx_msg LONG ZIBaseMDIPage::OnHideHtmlView( WPARAM wParam, LPARAM lParam )
{
    CDocument*    pDoc = (CDocument*)lParam;

    // If we are on the right document
    if ( GetActiveView() && GetActiveView()->GetDocument() && GetActiveView()->GetDocument() == pDoc )
    {
        ChangeContext( PROC_CONTEXT );
        return 1;
    }

    return 0;
}
afx_msg LONG ZIBaseMDIPage::OnShowHtmlView( WPARAM wParam, LPARAM lParam )
{
    CDocument*    pDoc = (CDocument*)lParam;

    // If we are on the right document
    if ( GetActiveView() && GetActiveView()->GetDocument() && GetActiveView()->GetDocument() == pDoc )
    {
        ChangeContext( HTML_CONTEXT );
        return 1;
    }

    return 0;
}

afx_msg LONG ZIBaseMDIPage::OnNavigateURL( WPARAM wParam, LPARAM lParam )
{
    if ( GetActiveDocument() && ISA( GetActiveDocument(), ZDDocument ) )
    {
        ZDDocument*    pDoc = ( (ZDDocument*)GetActiveDocument() );

        if ( pDoc->GetHtmlView() )
        {
            pDoc->GetHtmlView()->Navigate( (const char*)lParam, FALSE );
        }

        return 1;
    }

    return 0;
}

afx_msg LONG ZIBaseMDIPage::OnSetDefaultFileOpen( WPARAM wParam, LPARAM lParam )
{
    if ( !::IsWindow( m_cbxFileList.GetSafeHwnd() ) )
        return 0;

    // If there is no item, do nothing
    if ( m_cbxFileList.GetCount() <= 0 )
        return 1;

    int iIndex = m_cbxFileList.FindString( -1, (const char*)lParam );

    if ( iIndex != CB_ERR )
        m_cbxFileList.SetCurSel( iIndex );

    if ( wParam == 1 && GetActiveDocument() && ISA( GetActiveDocument(), ZDDocument ) )
    {
        ( (ZDDocument*)GetActiveDocument() )->ChangeCurrentFileOpen ( iIndex );
        ( (ZDDocument*)GetActiveDocument() )->UpdateAllViews( NULL );

        return 1;
    }

    return 0;
}

afx_msg LONG ZIBaseMDIPage::OnSchemaHasChanged( UINT message, LONG wParam )
{
    if ( !::IsWindow( m_cbxSchema.GetSafeHwnd() ) )
        return 0;

    if ( GetActiveDocument() && ISA( GetActiveDocument(), ZDDocument ) )
    {
        ZDDocument*    pDoc = ( (ZDDocument*)GetActiveDocument() );

        if ( !pDoc )
            pDoc = ZAGlobal::GetpCurrentDocumentForSerialization();

        if ( pDoc->GetActiveDocumentData() )
        {
            CStringArray& StringArray = pDoc->GetActiveDocumentData()->GetSchema().GetFormulaArrayName();
            RemoveAllSchema();

            for ( int i = 0; i < StringArray.GetSize(); ++i )
                AddSchema( StringArray[i] );
        }

        return 1;
    }

    return 0;
}

void ZIBaseMDIPage::OnViewFullScreen()
{
    // If not in full screen, maximize the window first
    if ( !( (ZIBaseMainFrame*)GetMDIFrame() )->IsFullScreen() )
    {
        // Retreive the window state
        m_IsZoomed = IsZoomed();
        m_IsIconic = IsIconic();

        WINDOWPLACEMENT    wp;
        wp.length = sizeof( WINDOWPLACEMENT );
        GetWindowPlacement( &wp );

        // And then, maximize the mdi frame
        if ( wp.showCmd != SW_SHOWMAXIMIZED )
        {
            m_HasBeenMaximized = TRUE;
            MDIMaximize();
        }

        m_wndToolBar.ShowWindow( SW_HIDE );
        ( (ZIBaseMainFrame*)GetMDIFrame() )->OnViewFullScreen();
    }
    else
    {
        m_wndToolBar.ShowWindow( SW_SHOW );
        ( (ZIBaseMainFrame*)GetMDIFrame() )->OnViewFullScreen();

        if ( m_HasBeenMaximized )
        {
            MDIRestore();
            m_HasBeenMaximized = FALSE;
        }
    }
}

void ZIBaseMDIPage::OnUpdateViewFullScreen( CCmdUI* pCmdUI )
{
    pCmdUI->SetCheck( ( (ZIBaseMainFrame*)GetMDIFrame() )->IsFullScreen() );
}

int ZIBaseMDIPage::CreateZoom()
{
    // Create the zoom ComboBox
    CRect    rect;
    m_wndToolBar.GetItemRect( INDEX_DROPLIST, &rect );

    int cyFit    = rect.Height();
    rect.top    = 1;                    // 1 pixel down from top of statusbar
    rect.left  += m_BaseOffset;
    rect.right    = rect.left + iSizeZoomCombo;
    rect.bottom    = rect.top + 200;        // drop height

    if( !m_cbxPercentage.Create( WS_CHILD|WS_BORDER|WS_VISIBLE|CBS_DROPDOWNLIST,
                                 rect,
                                 &m_wndToolBar,
                                 IDC_ZOOM ) )
    {
        TRACE( _T( "Failed to create combobox inside toolbar\n" ) );
        return -1;      // fail to create
    }

    for ( ZOOM_TYPES* pZoom = zoomNames; pZoom->pZoom != NULL; pZoom++ )
    {
        int index = m_cbxPercentage.AddString( pZoom->pZoom );
        m_cbxPercentage.SetItemData( index, pZoom->nZoom );
    }

    m_cbxPercentage.SelectString( -1, def_ORIGINALSIZESTR );
    return 0;
}

int ZIBaseMDIPage::CreateFileList()
{
    // Create the zoom ComboBox
    CRect rect;
    m_wndToolBar.GetItemRect( INDEX_DROPLIST_FILE, &rect );

    int cyFit    = rect.Height();
    rect.top    = 1;                    // 1 pixel down from top of statusbar
    rect.left  += m_BaseOffset + iSizeZoomCombo + iSizeStyleCombo + iSizeSchemaCombo;
    rect.right    = rect.left + iSizeFileListCombo;
    rect.bottom    = rect.top + 200;        // drop height

    if( !m_cbxFileList.Create( WS_CHILD|WS_BORDER|WS_VISIBLE|CBS_DROPDOWNLIST,
                               rect,
                               &m_wndToolBar,
                               IDC_FILELIST ) )
    {
        TRACE( _T( "Failed to create File List combobox inside toolbar\n" ) );
        return -1;      // fail to create
    }

    return 0;
}

int ZIBaseMDIPage::CreateSchema()
{
    // Create the zoom ComboBox
    CRect    rect;
    m_wndToolBar.GetItemRect( INDEX_DROPLIST_SCHEMA, &rect );

    int cyFit    = rect.Height();
    rect.top    = 1;   // 1 pixel down from top of statusbar
    rect.left  += m_BaseOffset + iSizeZoomCombo + iSizeStyleCombo;
    rect.right    = rect.left + iSizeSchemaCombo;
    rect.bottom    = rect.top + 200;       // drop height

    if( !m_cbxSchema.Create( WS_CHILD|WS_BORDER|WS_VISIBLE|CBS_DROPDOWNLIST|CBS_SORT,
                             rect,
                             &m_wndToolBar,
                             IDC_SCHEMA ) )
    {
        TRACE( _T( "Failed to create combobox inside toolbar\n" ) );
        return -1;      // fail to create
    }

    return 0;
}

void ZIBaseMDIPage::OnMDIActivate( BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd )
{
    CMDIChildWnd::OnMDIActivate( bActivate, pActivateWnd, pDeactivateWnd );
    
    AfxGetMainWnd()->SendMessageToDescendants( UM_DOCUMENTHASBEENSELECTED, 0, (LPARAM)GetActiveDocument() );

    // Send a message to the shema view to specify that current schema has changed
    ZBCommandObserverMsg Msg( UM_DEFAULTSCHEMAHASCHANGED );
    dynamic_cast<ZISubject*>( AfxGetMainWnd() )->NotifyAllObservers( &Msg );
}

void ZIBaseMDIPage::OnClose() 
{
    ZIBaseTitleMDIPage::OnClose();

    AfxGetMainWnd()->SendMessageToDescendants( UM_DOCUMENTHASBEENSELECTED, 0, (LPARAM)NULL );
}
