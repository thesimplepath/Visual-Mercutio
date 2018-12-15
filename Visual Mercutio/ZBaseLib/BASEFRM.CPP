// basrfrm.cpp : implementation of the ZIBaseMainFrame class

#include "stdafx.h"

#include "basefrm.h"
#include "draw.h"
#include "VTools.h"
#include "Message.h"
#include "BaseMdi.h"

// Utility class for floating toolbar management
#include "ZUFloatingToolbar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 18 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#define def_SaveWindowStateStr _T( "zForms_Save_Window_State" )

// Note: the toolbar buttons sends a wmSECToolBarWndNotify registered
// message for button notifications. Unfortunately, this value is a
// const int which can not be mapped properly across the Dll boundary.
// If using a static library, wmSECToolBarWndNotify can be safely used 
// in the ON_REGISTERED_MESSAGE macro below, but if using OT as a DLL,
// you must issue the following call to get the appropriate value.
// Since this mechanism is safe for static libraries as well, using
// for both.
const int wmAppToolBarWndNotify = RegisterWindowMessage( _T( "WM_ZFORMS_TOOLBARWNDNOTIFY" ) );

/////////////////////////////////////////////////////////////////////////////
// ZIBaseMainFrame

IMPLEMENT_DYNAMIC( ZIBaseMainFrame, SECMDIFrameWnd )

BEGIN_MESSAGE_MAP( ZIBaseMainFrame, SECMDIFrameWnd )
    //{{AFX_MSG_MAP(ZIBaseMainFrame)
    ON_WM_CREATE()
    ON_WM_CLOSE()
    ON_WM_INITMENUPOPUP()
    ON_COMMAND(ID_VIEW_POINTER, OnViewPointer)
    ON_UPDATE_COMMAND_UI(ID_VIEW_POINTER, OnUpdateViewPointer)
    ON_MESSAGE(FSM_SETMODE, OnFSModeChange)
    // Global help commands
    ON_COMMAND(ID_HELP_INDEX, CMDIFrameWnd::OnHelpIndex)
    ON_UPDATE_COMMAND_UI(ID_HELP_INDEX, OnUpdateHelpIndex)
    ON_COMMAND(ID_HELP_USING, CMDIFrameWnd::OnHelpUsing)
    ON_UPDATE_COMMAND_UI(ID_HELP_USING, OnUpdateHelpUsing)
    ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelpIndex)//OnHelp)
    ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
    ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpIndex)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIBaseMainFrame construction/destruction

ZIBaseMainFrame::ZIBaseMainFrame( bool MustSaveBarState /*= true*/ )
    : m_pwndToolBar                        ( NULL ),
      m_MustSaveBarState                ( MustSaveBarState ),
      m_SaveBarStateHasBeenInitialized    ( false )
{
    m_pControlBarManager    = new SECToolBarManager( this );
    m_pMenuBar                = new SECMDIMenuBar;            // or SECMenuBar for SDI

    // Use the cool bitmap menu support
    EnableBmpMenus();

    // Initialize the Floating Toolbar
    ZUFloatingToolbar::Initialize( &m_WindowConfiguration,
                                   dynamic_cast<SECToolBarManager*>( m_pControlBarManager ),
                                   m_pMenuBar );
}

ZIBaseMainFrame::~ZIBaseMainFrame()
{
    if ( m_pwndToolBar )
    {
        delete m_pwndToolBar;
        m_pwndToolBar = NULL;
    }

    // Delete the control bar manager
    if ( m_pControlBarManager )
    {
        delete m_pControlBarManager;
        m_pControlBarManager = NULL;
    }

    if( m_pMenuBar )
    {
        delete m_pMenuBar;
        m_pMenuBar = NULL;
    }
}

#ifdef __CREATE_LOGO_
// To paint subclass the Main MDI Client window 
int ZIBaseMainFrame::CreateClient( LPCREATESTRUCT lpCreateStruct, CMenu *pMenu )
{
    if( !CMDIFrameWnd::CreateClient( lpCreateStruct, pMenu ) )
    {
        return( FALSE );
    }

    m_MDIClient.SubclassWindow( m_hWndMDIClient );        // m_hWndMDIClient is the 
                                                        // pointer to the MDI Client

    return( TRUE );
}
#endif // __CREATE_LOGO_

int ZIBaseMainFrame::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
    if ( SECMDIFrameWnd::OnCreate( lpCreateStruct ) == -1 )
    {
        return -1;
    }

    // Calls the derived method to create the menus
    if ( !CreateMenuBars() )
    {
        return -1;
    }

    // Calls the derived method to create the toolbars
    if ( !CreateToolBars() )
    {
        return -1;
    }

    // Calls the derived method to create the status bar
    if ( !CreateStatusBar() )
    {
        return -1;
    }

    EnableDocking( CBRS_ALIGN_ANY );

    // Calls the derived method to initialize the docking windows
    if ( !InitializeDockingWindows() )
    {
        return -1;
    }

    // Call this to position the default toolbars as configured by
    // the DefineDefaultToolBar    commands above. Don't do this
    // if you are going immediately use LoadBarState/LoadState below,
    // as these functions will call it anyways on nonexistant state info.
    ASSERT( m_pControlBarManager != NULL );
    ASSERT_KINDOF( SECToolBarManager, m_pControlBarManager );

    dynamic_cast<SECToolBarManager*>( m_pControlBarManager )->EnableCoolLook();

    // The 'context list' mode provides a pop-up menu listing all the control bars that are present in this frame. Similar
    // to the Visual Studio UI, docking windows can be turned on or off using this menu.
    EnableContextListMode( TRUE );

    // Required to restore state
    OnReloadBarState();

    // Set by default the edition tool
    ZIVisualTool::m_CurrentToolType = VToolEdit;

    return 0;
}

BOOL ZIBaseMainFrame::PreCreateWindow( CREATESTRUCT& cs )
{
    if( !SECMDIFrameWnd::PreCreateWindow( cs ) )
    {
        return FALSE;
    }

    return TRUE;
}

void ZIBaseMainFrame::LoadMenuBar( UINT nIDMenu )
{
    if ( m_pMenuBar && m_pControlBarManager )
    {
        ASSERT( m_pControlBarManager != NULL );
        ASSERT_KINDOF( SECToolBarManager, m_pControlBarManager );
        dynamic_cast<SECToolBarManager*>( m_pControlBarManager )->SetMenuInfo( 1, nIDMenu );
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZIBaseMainFrame diagnostics

#ifdef _DEBUG
void ZIBaseMainFrame::AssertValid() const
{
    CMDIFrameWnd::AssertValid();
}

void ZIBaseMainFrame::Dump( CDumpContext& dc ) const
{
    CMDIFrameWnd::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZIBaseMainFrame message handlers

#ifdef __CREATE_LOGO_

/////////////////////////////////////////////////////////////////////////////
// MainMDIClient

BEGIN_MESSAGE_MAP( MainMDIClient, CWnd )
    //{{AFX_MSG_MAP(MainMDIClient)
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

MainMDIClient::MainMDIClient()
{
}

MainMDIClient::~MainMDIClient()
{
}

WNDPROC *MainMDIClient::GetSuperWndProcAddr()
{
    static WNDPROC pOldProc;
    return( &pOldProc );
}

void MainMDIClient::DisplayLogo( CDC *pDC )
{
    CRect        rect;
    CPoint        pt;

    GetClientRect( &rect );

    // After display the logo
    GetSizeOfBitmapFile( MAKEINTRESOURCE ( IDB_MDI ), AfxGetInstanceHandle(), &pt );

    // Calculate the middle of the area
    // to display the bitmap
    DisplayBitmapFile( MAKEINTRESOURCE ( IDB_MDI ),
                       pDC->m_hDC,
                       AfxGetInstanceHandle(),
                      ( rect.right - rect.left ) / 2 - ( pt.x / 2 ),
                      ( rect.bottom - rect.top ) / 2 - ( pt.y / 2 ) );
}

/////////////////////////////////////////////////////////////////////////////
// MainMDIClient message handlers

void MainMDIClient::OnSize( UINT nType, int cx, int cy )
{
    CWnd::OnSize( nType, cx, cy );

    CRect rect;
    GetClientRect( &rect );
    InvalidateRect( &rect );
}

BOOL MainMDIClient::OnEraseBkgnd( CDC* pDC )
{
    ASSERT_VALID( pDC );

    // Fill background with APPWORKSPACE
    CBrush backBrush( defCOLOR_LTGRAY );
    CBrush* pOldBrush = pDC->SelectObject( &backBrush );

    // Erase the area needed
    CRect rect;
    pDC->GetClipBox( &rect );

    pDC->PatBlt( rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY );
    pDC->SelectObject( pOldBrush );

    DisplayLogo( pDC );
    return( TRUE );
}
#endif // __CREATE_LOGO_

void ZIBaseMainFrame::OnInitMenuPopup( CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu )
{
    if ( pPopupMenu->GetMenuItemCount() )
    {
        if ( pPopupMenu->GetMenuItemID( 0 ) >= MENU_COMMAND && pPopupMenu->GetMenuItemID( 0 ) <= MAX_MENU_COMMAND )
        {
            m_bAutoMenuEnable = FALSE;
        }
    }

    CMDIFrameWnd::OnInitMenuPopup( pPopupMenu, nIndex, bSysMenu );
    m_bAutoMenuEnable = TRUE;
}

BOOL ZIBaseMainFrame::OnCommand( WPARAM wParam, LPARAM lParam )
{
    if ( wParam >= MENU_COMMAND && wParam <= MAX_MENU_COMMAND )
    {
        AfxGetMainWnd()->SendMessageToDescendants( ID_SPECIALHELPMENU, wParam );
        return 1;
    }

    return CWnd::OnCommand( wParam, lParam );
}

void ZIBaseMainFrame::OnViewFullScreen()
{
    //Bitmap toolbar with OT defined resource
    m_FSView.SetFSMode();
}

LRESULT ZIBaseMainFrame::OnFSModeChange( WPARAM wPar, LPARAM )
{
    //wPar is TRUE when the full screen mode is being set
    //Notify the active view so that it can restore the toolbar
    CMDIChildWnd* pMDIChild = MDIGetActive();

    if( pMDIChild && ::IsWindow( pMDIChild->GetSafeHwnd() ) )
    {
        CView* pActvView = pMDIChild->GetActiveView();
        pActvView->PostMessage( WM_NOTIFYVIEW_ONFULLSCREEN,WPARAM( wPar ) );
        pMDIChild->PostMessage( WM_NOTIFYVIEW_ONFULLSCREEN,WPARAM( wPar ) );
    }

    return TRUE;
}

void ZIBaseMainFrame::OnViewPointer()
{
    if ( PointerWindowIsVisible() )
    {
        HidePointerWindow();
    }
    else
    {
        ShowPointerWindow();
    }
}

void ZIBaseMainFrame::OnUpdateViewPointer( CCmdUI* pCmdUI )
{
    pCmdUI->SetCheck( PointerWindowIsVisible() );
}

// JMR-MODIF - Le 10 octobre 2007 - Cette fonction désactive l'entrée "Index" du menu "Aide".
void ZIBaseMainFrame::OnUpdateHelpIndex( CCmdUI* pCmdUI )
{
    pCmdUI->Enable( FALSE );
}

// JMR-MODIF - Le 10 octobre 2007 - Cette fonction désactive l'entrée "Utilisation de l'aide" du menu "Aide".
void ZIBaseMainFrame::OnUpdateHelpUsing( CCmdUI* pCmdUI )
{
    pCmdUI->Enable( FALSE );
}

void ZIBaseMainFrame::OnReloadBarState( bool Reset /*= false*/ )
{
    if ( MustSaveBarState() )
    {
        m_WindowConfiguration.Create( AfxGetApp()->m_pszProfileName );
        m_WindowConfiguration.RestoreWindowPosition( this, _T( "MainWindow" ) );

        if ( m_pControlBarManager )
        {
            if ( Reset )
            {
                LoadBarState( _T( "Unknown profile" ) );
            }
            else
            {
                LoadBarState( def_SaveWindowStateStr );
            }

            ASSERT( m_pControlBarManager != NULL );
            ASSERT_KINDOF( SECToolBarManager, m_pControlBarManager );

            if ( Reset )
            {
                dynamic_cast<SECToolBarManager*>( m_pControlBarManager )->LoadState( _T( "Unknown profile" ) );
            }
            else
            {
                dynamic_cast<SECToolBarManager*>( m_pControlBarManager )->LoadState( def_SaveWindowStateStr );
            }
        }

        m_SaveBarStateHasBeenInitialized = true;
    }
    else
    {
        ASSERT( m_pControlBarManager != NULL );
        ASSERT_KINDOF( SECToolBarManager, m_pControlBarManager );
        dynamic_cast<SECToolBarManager*>( m_pControlBarManager )->SetDefaultDockState();
    }
}

void ZIBaseMainFrame::OnSaveBarState()
{
    if ( MustSaveBarState() )
    {
        // If not initialized, do it before saving space
        if ( !m_SaveBarStateHasBeenInitialized )
        {
            m_WindowConfiguration.Create( AfxGetApp()->m_pszProfileName );
        }

        m_WindowConfiguration.SaveWindowPosition( this, _T( "MainWindow" ) );

        if ( m_pControlBarManager )
        {
            SaveBarState( def_SaveWindowStateStr );

            ASSERT( m_pControlBarManager != NULL );
            ASSERT_KINDOF( SECToolBarManager, m_pControlBarManager );
            dynamic_cast<SECToolBarManager*>( m_pControlBarManager )->SaveState( def_SaveWindowStateStr );
        }
    }
}

void ZIBaseMainFrame::OnClose()
{
    // JMR-MODIF - Le 30 août 2005 - Sauvegarde effectuée dans la fonction OnClose de ZIMainFrame.
    // Save Settings flag
//    if ( MustSaveBarState() )
//    {
//        OnSaveBarState();
//    }

    SECMDIFrameWnd::OnClose();
}
