// ZSearchEdit.cpp : implementation file
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZSearchEdit.h"
#include "SHFileInfo.h"
#include "zBaseLib\FileDlg.h"

#ifndef _WIN32
    #include "ZWinUtil.h"
#else
    #include "ZWinUtil32.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 14 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZEditButton class
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP( ZEditButton, CButton )
    ON_CONTROL_REFLECT( BN_CLICKED, OnClicked )
END_MESSAGE_MAP()

ZEditButton::ZEditButton()
    : m_pEdit                    ( NULL ),
      m_IsProcessingMenuItems    ( false )
{
    NONCLIENTMETRICS ncm;

    ncm.cbSize = sizeof( NONCLIENTMETRICS );

    VERIFY( ::SystemParametersInfo( SPI_GETNONCLIENTMETRICS, sizeof( NONCLIENTMETRICS ), &ncm, 0 ) );

    m_Font.CreateFontIndirect( &ncm.lfMessageFont );
}

ZEditButton::~ZEditButton()
{
}

BOOL ZEditButton::Create( ZCSearchEdit*        pWnd,
                          ZSEARCHEDIT_TYPE    eType,
                          UINT                nMenu,
                          CString            Title,
                          CString            InitialDirectory,
                          CString            Filters,
                          size_t            FilterCount,
                          bool                EnableMenuItems,
                          bool                NoNotify,
                          bool                Resize )
{
    ASSERT        ( eType != -1 );
    ASSERT_VALID( pWnd );

    // Assign values
    m_eType                = eType;
    m_nMenu                = nMenu;
    m_pMenu                = NULL;
    m_Title                = Title;
    m_InitialDirectory    = InitialDirectory;
    m_Filters            = Filters;
    m_FilterCount        = FilterCount;
    m_pEdit                = pWnd;
    m_EnableMenuItems    = EnableMenuItems;
    m_NoNotify            = NoNotify;

    return ZEditButton::CreateButton( pWnd, eType, Resize );
}

BOOL ZEditButton::Create( ZCSearchEdit*        pWnd,
                          ZSEARCHEDIT_TYPE    eType,
                          CMenu*            pMenu,
                          CString            Title,
                          CString            InitialDirectory,
                          CString            Filters,
                          size_t            FilterCount,
                          bool                EnableMenuItems,
                          bool                NoNotify,
                          bool                Resize )
{
    ASSERT        ( eType != -1 );
    ASSERT_VALID( pWnd );

    // Assign values
    m_eType                = eType;
    m_pMenu                = pMenu;
    m_nMenu                = -1;
    m_Title                = Title;
    m_InitialDirectory    = InitialDirectory;
    m_Filters            = Filters;
    m_FilterCount        = FilterCount;
    m_pEdit                = pWnd;
    m_EnableMenuItems    = EnableMenuItems;
    m_NoNotify            = NoNotify;

    return ZEditButton::CreateButton( pWnd, eType, Resize );
}


BOOL ZEditButton::CreateButton( CWnd* pWnd, ZSEARCHEDIT_TYPE eType, bool Resize )
{
    m_pWnd                = pWnd;
    CWnd* pParentWnd    = pWnd->GetParent();
    ASSERT_VALID( pParentWnd );
    
    CRect rc;
    m_pWnd->GetWindowRect( &rc );

    if ( Resize )
    {
        m_pWnd->SetWindowPos( NULL,
                              0,
                              0,
                              rc.Width() - 23,
                              rc.Height(),
                              SWP_NOZORDER|SWP_NOMOVE );
    }

    pParentWnd->ScreenToClient( &rc );
    rc.left = rc.right - 18;

    DWORD dwStyle = WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_CENTER|BS_VCENTER;

    switch ( m_eType )
    {
        case ZSEARCHEDIT_DIRECTORY:
        case ZSEARCHEDIT_FILE:
        case ZSEARCHEDIT_EXTENDED:
        {
            if ( CButton::Create( _T( "..." ),
                                  dwStyle,
                                  rc,
                                  pParentWnd,
                                  GetNextID( pParentWnd ) ) )
            {
                SetWindowPos( m_pWnd, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE );
                EnableWindow( m_pWnd->IsWindowEnabled() );
                SetFont( &m_Font );

                return TRUE;
            }
        }

        case ZSEARCHEDIT_POPUP:
        {
            if ( CButton::Create( _T( "..." ),
                                  dwStyle|BS_ICON,
                                  rc,
                                  pParentWnd,
                                  GetNextID( pParentWnd ) ) )
            {
                SetWindowPos( m_pWnd, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE );
                EnableWindow( m_pWnd->IsWindowEnabled() );
                SetFont( &m_Font );

                CImageList    imageList;
                CBitmap        bitmap;

                bitmap.LoadBitmap( IDB_MENU_BUTTON );
                imageList.Create( 15, 17, ILC_COLORDDB|ILC_MASK, 1, 1 );
                imageList.Add( &bitmap, RGB( 255, 0, 255 ) );

                SetIcon( imageList.ExtractIcon( 0 ) );

                imageList.Detach();
                bitmap.Detach();

                return TRUE;
            }
        }
    }

    return FALSE;
}

void ZEditButton::OnClicked()
{
    if ( m_IsProcessingMenuItems )
    {
        return;
    }

    switch ( m_eType )
    {
        case ZSEARCHEDIT_DIRECTORY:
        {
            CSHFileInfo sfi;
            sfi.m_strTitle = _T( m_Title );

            if ( sfi.BrowseForFolder( GetParent() ) == IDOK )
            {
                m_pWnd->SetWindowText( sfi.m_strPath );
            }

            break;
        }

        case ZSEARCHEDIT_FILE:
        {
            ZIFileDialog dlg( m_Title, m_Filters, m_FilterCount, m_InitialDirectory );

            if ( dlg.DoModal() == IDOK )
            {
                m_pWnd->SetWindowText( dlg.GetFilename() );
            }

            break;
        }

        case ZSEARCHEDIT_POPUP:
        {
            ASSERT( m_nMenu!=-1 || m_pMenu!=NULL );
            SetState( TRUE );

            CRect rc;
            GetWindowRect( &rc );
            CWnd* pParentWnd = m_pWnd->GetParent();

            CMenu menu;
            CMenu* pPopup = NULL;

            if ( m_pMenu )
            {
                pPopup = m_pMenu->GetSubMenu( 0 );
            }
            else
            {
                VERIFY( menu.LoadMenu( m_nMenu ) );
                pPopup = menu.GetSubMenu( 0 );
            }

            ASSERT( pPopup != NULL );

            CWnd* pWndPopupOwner = this;

            while ( pWndPopupOwner->GetStyle() & WS_CHILD )
            {
                pWndPopupOwner = pWndPopupOwner->GetParent();
            }

            if ( pPopup )
            {
                // Enable all menu items
                if ( m_EnableMenuItems )
                {
                    UINT Count = pPopup->GetMenuItemCount();

                    for ( UINT i = 0; i < Count; ++i )
                    {
                        pPopup->EnableMenuItem( i, MF_BYPOSITION | MF_ENABLED );
                    }
                }

                UINT uFlags = TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL|TPM_RETURNCMD;

                if ( m_NoNotify )
                {
                    uFlags |= TPM_NONOTIFY;
                }

                // Sets the flag for menu processing
                m_IsProcessingMenuItems = true;

                int Value = pPopup->TrackPopupMenu( uFlags,
                                                    rc.right,
                                                    rc.top,
                                                    ( m_EnableMenuItems ) ? pParentWnd : pWndPopupOwner,
                                                    &rc );

                if ( m_pEdit && Value > 0 )
                {
                    m_pEdit->OnMenuCommand( Value );
                }

                // Resets the flag
                m_IsProcessingMenuItems = false;
            }

            // Return the button state to normal.
            SetState( FALSE );

            break;
        }

        case ZSEARCHEDIT_EXTENDED:
        {
            if ( m_pEdit )
            {
                m_pEdit->OnExtendedCommand();
            }

            break;
        }
    }
}

UINT ZEditButton::GetNextID( CWnd* pWnd ) const
{
    for ( UINT nID = 32767; nID != 1; --nID )
    {
        if( !pWnd->GetDlgItem( nID ) )
        {
            return nID;
        }
    }

    return -1;
}

/////////////////////////////////////////////////////////////////////////////
// ZCSearchEdit

BEGIN_MESSAGE_MAP( ZCSearchEdit, ZBDragEdit )
    //{{AFX_MSG_MAP(ZCSearchEdit)
    ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
    ON_WM_SIZE()
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZCSearchEdit::ZCSearchEdit()
    : m_BeingResized( false ),
      m_BeingCreated( false )
{
    m_eType                = ZSEARCHEDIT_DIRECTORY;
    m_nMenu                = -1;
    m_pMenu                = NULL;
    m_FilterCount        = 0;
    m_pParentWnd        = NULL;
    m_EnableMenuItems    = false;

    // JMR-MODIF - Le 11 août 2005 - Ajout de l'initialisation de la variable m_bDoCreateButton.
    m_bDoCreateButton    = FALSE;
}

ZCSearchEdit::~ZCSearchEdit()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZCSearchEdit message handlers

void ZCSearchEdit::OnEnable( BOOL bEnable )
{
    ZBDragEdit::OnEnable    ( bEnable );

    // JMR-MODIF - Le 11 août 2005 - Ajout du test pour savoir si le bouton a été crée avant de le mettre à jour.
    if ( m_bDoCreateButton == TRUE )
    {
        m_button.EnableWindow( bEnable );
    }
}

void ZCSearchEdit::OnShowWindow( BOOL bShow, UINT nStatus )
{
    ZBDragEdit::OnShowWindow( bShow, nStatus );

    // JMR-MODIF - Le 11 août 2005 - Ajout du test pour savoir si le bouton a été crée avant de le mettre à jour.
    if ( m_bDoCreateButton == TRUE )
    {
        m_button.ShowWindow( bShow ? SW_SHOW : SW_HIDE );
    }
}

BOOL ZCSearchEdit::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID )
{
    m_BeingCreated = true;

    BOOL RetValue = CEdit::Create( dwStyle, rect, pParentWnd, nID );

    return RetValue;
}

BOOL ZCSearchEdit::Create( LPCTSTR            lpszClassName,
                           LPCTSTR            lpszWindowName,
                           DWORD            dwStyle,
                           const RECT&        rect,
                           CWnd*            pParentWnd,
                           UINT                nID,
                           CCreateContext*    pContext )
{
    return CWnd::Create( lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext );
}

int ZCSearchEdit::OnCreate( LPCREATESTRUCT lpCreateStruct ) 
{
    if ( ZBDragEdit::OnCreate( lpCreateStruct ) == -1 )
    {
        return -1;
    }

    // JMR-MODIF - Le 11 août 2005 - Ajout de la variable m_bDoCreateButton dans le test de création du bouton.
    if ( m_BeingCreated && m_bDoCreateButton )
    {
        CreateButton( false );
    }

    return 0;
}

void ZCSearchEdit::CreateButton( bool Resize )
{
    if ( m_pMenu )
    {
        if ( !m_button.Create( this,
                               m_eType,
                               m_pMenu,
                               m_Title,
                               m_InitialDirectory,
                               m_Filters,
                               m_FilterCount,
                               m_EnableMenuItems,
                               m_NoNotify,
                               Resize ) ) 
        {
            TRACE0( _T( "Failed to create browse button.\n" ) );
            return;
        }
    }
    else
    {
        if ( !m_button.Create( this,
                               m_eType,
                               m_nMenu,
                               m_Title,
                               m_InitialDirectory,
                               m_Filters,
                               m_FilterCount,
                               m_EnableMenuItems,
                               m_NoNotify,
                               Resize ) ) 
        {
            TRACE0( _T( "Failed to create browse button.\n" ) );
            return;
        }
    }
}

void ZCSearchEdit::PreSubclassWindow()
{
    ZBDragEdit::PreSubclassWindow();

    if ( m_BeingCreated )
    {
        return;
    }

    // Created when invoked from a dialog
    CreateButton( true );
}

void ZCSearchEdit::SetSearchType( ZSEARCHEDIT_TYPE eType )
{
    m_eType                = eType;
    m_nMenu                = -1;
    m_pMenu                = NULL;
    m_EnableMenuItems    = false;
    m_NoNotify            = false;
    m_Title                = _T( "" );
    m_InitialDirectory    = _T( "" );
}

void ZCSearchEdit::SetSearchType( ZSEARCHEDIT_TYPE    eType,
                                  UINT                nMenu,
                                  bool                EnableMenuItems    /*= false*/,
                                  bool                NoNotify        /*= false*/ )
{
    m_eType                = eType;
    m_nMenu                = nMenu;
    m_pMenu                = NULL;
    m_EnableMenuItems    = EnableMenuItems;
    m_NoNotify            = NoNotify;
}

void ZCSearchEdit::SetSearchType( ZSEARCHEDIT_TYPE    eType,
                                  CMenu*            pMenu,
                                  bool                EnableMenuItems    /*= false*/,
                                  bool                NoNotify        /*= false*/ )
{
    m_eType                = eType;
    m_nMenu                = -1;
    m_pMenu                = pMenu;
    m_EnableMenuItems    = EnableMenuItems;
    m_NoNotify            = NoNotify;
}

void ZCSearchEdit::SetSearchType( ZSEARCHEDIT_TYPE eType, CString Title, CString InitialDirectory )
{
    m_eType = eType;

    if ( eType == ZSEARCHEDIT_DIRECTORY || eType == ZSEARCHEDIT_FILE )
    {
        m_nMenu = -1;
        m_pMenu = NULL;
    }

    m_Title                = Title;
    m_InitialDirectory    = InitialDirectory;
}

void ZCSearchEdit::SetSearchType( ZSEARCHEDIT_TYPE    eType,
                                  CString            Title,
                                  CString            InitialDirectory,
                                  CString            Filters,
                                  size_t            FilterCount)
{
    m_eType = eType;

    if ( eType == ZSEARCHEDIT_DIRECTORY || eType == ZSEARCHEDIT_FILE )
    {
        m_nMenu = -1;
        m_pMenu = NULL;
    }

    m_Title                = Title;
    m_InitialDirectory    = InitialDirectory;
    m_Filters            = Filters;
    m_FilterCount        = FilterCount;
}

void ZCSearchEdit::SetSearchType( ZSEARCHEDIT_TYPE eType, UINT nID, CString InitialDirectory )
{
    m_eType = eType;

    if ( eType == ZSEARCHEDIT_DIRECTORY || eType == ZSEARCHEDIT_FILE )
    {
        m_nMenu = -1;
        m_pMenu = NULL;
    }

    m_Title.LoadString( nID );
    m_InitialDirectory = InitialDirectory;
}

void ZCSearchEdit::SetSearchType( ZSEARCHEDIT_TYPE    eType,
                                  UINT                nID,
                                  CString            InitialDirectory,
                                  CString            Filters,
                                  size_t            FilterCount )
{
    m_eType = eType;

    if ( eType == ZSEARCHEDIT_DIRECTORY || eType == ZSEARCHEDIT_FILE )
    {
        m_nMenu = -1;
        m_pMenu = NULL;
    }

    m_Title.LoadString( nID );
    m_InitialDirectory    = InitialDirectory;
    m_Filters            = Filters;
    m_FilterCount        = FilterCount;
}

void ZCSearchEdit::OnSize( UINT nType, int cx, int cy )
{
    // To avoid recursion
    if ( m_BeingResized )
    {
        return;
    }

    ZBDragEdit::OnSize( nType, cx, cy );
    
    if ( !::IsWindow( m_button.GetSafeHwnd() ) )
    {
        return;
    }

    // Start resize controls
    m_BeingResized = true;

    CRect rc;

    GetWindowRect( &rc );

    SetWindowPos( NULL,
                  0,
                  0,
                  rc.Width() - 23,
                  rc.Height(),
                  SWP_NOZORDER|SWP_NOMOVE );

    CWnd* pWndParent = GetParent();
    ASSERT_VALID( pWndParent );

    pWndParent->ScreenToClient( &rc );
    rc.left = rc.right - 18;

    m_button.MoveWindow( &rc );

    // End resize controls
    m_BeingResized = false;
}
