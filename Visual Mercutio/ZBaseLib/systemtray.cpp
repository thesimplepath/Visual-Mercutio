/////////////////////////////////////////////////////////////////////////////
// SystemTray.cpp : implementation file
//
//
/////////////////////////////////////////////////////////////////////////////
    
#include "stdafx.h"
#include "SystemTray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 4 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile (En commentaires).

UINT ZISystemTray::m_nIDEvent = 4567;

IMPLEMENT_DYNAMIC( ZISystemTray, CWnd )

/////////////////////////////////////////////////////////////////////////////
// ZISystemTray message handlers

BEGIN_MESSAGE_MAP( ZISystemTray, CWnd )
    //{{AFX_MSG_MAP(ZISystemTray)
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZISystemTray construction/creation/destruction

ZISystemTray::ZISystemTray()
{
    Initialise();
}

ZISystemTray::ZISystemTray( CWnd* pParent, UINT uCallbackMessage, LPCTSTR szToolTip, HICON icon, UINT uID )
{
    Initialise();
    Create( pParent, uCallbackMessage, szToolTip, icon, uID );
}

void ZISystemTray::Initialise()
{
    memset( &m_tnd, 0, sizeof( m_tnd ) );

    m_bEnabled                = FALSE;
    m_bHidden                = FALSE;
    m_uIDTimer                = 0;
    m_hSavedIcon            = NULL;
    m_DefaultMenuItemID        = 0;
    m_DefaultMenuItemByPos    = TRUE;
    m_pSubMenu                = NULL;
}

BOOL ZISystemTray::Create( CWnd* pParent, UINT uCallbackMessage, LPCTSTR szToolTip, HICON icon, UINT uID )
{
    // this is only for Windows 95 (or higher)
    VERIFY( m_bEnabled = ( GetVersion() & 0xff ) >= 4 );

    if ( !m_bEnabled ) return FALSE;

    // Make sure we avoid conflict with other messages
    ASSERT( uCallbackMessage >= WM_USER );

    // Tray only supports tooltip text up to 64 characters
    ASSERT( _tcslen(szToolTip) <= 64 );

    // Create an invisible window
    CWnd::CreateEx( 0, AfxRegisterWndClass( 0 ), _T( "" ), WS_POPUP, 0, 0, 10, 10, NULL, 0 );

    // Load up the NOTIFYICONDATA structure
    m_tnd.cbSize = sizeof( NOTIFYICONDATA );

    m_tnd.hWnd   = pParent->GetSafeHwnd()? pParent->GetSafeHwnd() : m_hWnd;
    m_tnd.uID    = uID;
    m_tnd.hIcon  = icon;
    m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    m_tnd.uCallbackMessage = uCallbackMessage;
    _tcscpy( m_tnd.szTip, szToolTip );

    if ( m_Menu.LoadMenu( m_tnd.uID ) )
    {
        m_pSubMenu = m_Menu.GetSubMenu( 0 ); 
    }

    // Set the tray icon
    VERIFY( m_bEnabled = Shell_NotifyIcon( NIM_ADD, &m_tnd ) );

    return m_bEnabled;
}

ZISystemTray::~ZISystemTray()
{
    RemoveIcon();
    m_IconList.RemoveAll();
    DestroyWindow();
}

/////////////////////////////////////////////////////////////////////////////
// ZISystemTray icon manipulation

void ZISystemTray::MoveToRight()
{
    HideIcon();
    ShowIcon();
}

void ZISystemTray::RemoveIcon()
{
    if ( !m_bEnabled ) return;

    m_tnd.uFlags = 0;
    Shell_NotifyIcon( NIM_DELETE, &m_tnd );
    m_bEnabled = FALSE;
}

void ZISystemTray::HideIcon()
{
    if ( m_bEnabled && !m_bHidden )
    {
        m_tnd.uFlags = NIF_ICON;
        Shell_NotifyIcon ( NIM_DELETE, &m_tnd );
        m_bHidden = TRUE;
    }
}

void ZISystemTray::ShowIcon()
{
    if (m_bEnabled && m_bHidden)
    {
        m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        Shell_NotifyIcon( NIM_ADD, &m_tnd );
        m_bHidden = FALSE;
    }
}

BOOL ZISystemTray::SetIcon( HICON hIcon )
{
    if ( !m_bEnabled ) return FALSE;

    m_tnd.uFlags = NIF_ICON;
    m_tnd.hIcon = hIcon;

    return Shell_NotifyIcon( NIM_MODIFY, &m_tnd );
}

BOOL ZISystemTray::SetIcon( LPCTSTR lpszIconName )
{
    HICON hIcon = AfxGetApp()->LoadIcon( lpszIconName );

    return SetIcon( hIcon );
}

BOOL ZISystemTray::SetIcon( UINT nIDResource )
{
    HICON hIcon = AfxGetApp()->LoadIcon( nIDResource );

    return SetIcon( hIcon );
}

BOOL ZISystemTray::SetStandardIcon( LPCTSTR lpIconName )
{
    HICON hIcon = LoadIcon( NULL, lpIconName );

    return SetIcon( hIcon );
}

BOOL ZISystemTray::SetStandardIcon( UINT nIDResource )
{
    HICON hIcon = LoadIcon( NULL, MAKEINTRESOURCE( nIDResource ) );

    return SetIcon( hIcon );
}

HICON ZISystemTray::GetIcon() const
{
    return ( m_bEnabled ) ? m_tnd.hIcon : NULL;
}

BOOL ZISystemTray::SetIconList( UINT uFirstIconID, UINT uLastIconID )
{
    if ( uFirstIconID > uLastIconID )
        return FALSE;

    UINT uIconArraySize = uLastIconID - uFirstIconID + 1;
    const CWinApp * pApp = AfxGetApp();
    ASSERT( pApp != 0 );

    m_IconList.RemoveAll();

    try
    {
        for ( UINT i = uFirstIconID; i <= uLastIconID; i++ )
            m_IconList.Add( pApp->LoadIcon( i ) );
    }
    catch ( CMemoryException *e )
    {
        e->ReportError();
        e->Delete();
        m_IconList.RemoveAll();
        return FALSE;
    }

    return TRUE;
}

BOOL ZISystemTray::SetIconList( HICON* pHIconList, UINT nNumIcons )
{
    m_IconList.RemoveAll();

    try
    {
        for ( UINT i = 0; i <= nNumIcons; i++ )
            m_IconList.Add( pHIconList[i] );
    }
    catch ( CMemoryException *e )
    {
        e->ReportError();
        e->Delete();
        m_IconList.RemoveAll();
        return FALSE;
    }

    return TRUE;
}

BOOL ZISystemTray::Animate( UINT nDelayMilliSeconds, int nNumSeconds /*=-1*/ )
{
    StopAnimation();

    m_nCurrentIcon        = 0;
    m_StartTime            = COleDateTime::GetCurrentTime();
    m_nAnimationPeriod    = nNumSeconds;
    m_hSavedIcon        = GetIcon();

    // Setup a timer for the animation
    m_uIDTimer = SetTimer( m_nIDEvent, nDelayMilliSeconds, NULL );

    return ( m_uIDTimer != 0 );
}

BOOL ZISystemTray::StepAnimation()
{
    if ( !m_IconList.GetSize() )
        return FALSE;

    m_nCurrentIcon++;

    if ( m_nCurrentIcon >= m_IconList.GetSize() )
        m_nCurrentIcon = 0;

    return SetIcon( m_IconList[m_nCurrentIcon] );
}

BOOL ZISystemTray::StopAnimation()
{
    BOOL bResult = FALSE;

    if ( m_uIDTimer )
        bResult = KillTimer(m_uIDTimer);

    m_uIDTimer = 0;

    if ( m_hSavedIcon )
        SetIcon(m_hSavedIcon);

    m_hSavedIcon = NULL;

    return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// ZISystemTray tooltip text manipulation

BOOL ZISystemTray::SetTooltipText( LPCTSTR pszTip )
{
    if ( !m_bEnabled ) return FALSE;

    m_tnd.uFlags = NIF_TIP;
    _tcscpy( m_tnd.szTip, pszTip );

    return Shell_NotifyIcon( NIM_MODIFY, &m_tnd );
}

BOOL ZISystemTray::SetTooltipText( UINT nID )
{
    CString strText;
    VERIFY( strText.LoadString( nID ) );

    return SetTooltipText(strText);
}

CString ZISystemTray::GetTooltipText() const
{
    CString strText;

    if ( m_bEnabled )
        strText = m_tnd.szTip;

    return strText;
}

/////////////////////////////////////////////////////////////////////////////
// ZISystemTray notification window stuff

BOOL ZISystemTray::SetNotificationWnd( CWnd* pWnd )
{
    if ( !m_bEnabled ) return FALSE;

    // Make sure Notification window is valid
    ASSERT( pWnd && ::IsWindow( pWnd->GetSafeHwnd() ) );

    m_tnd.hWnd = pWnd->GetSafeHwnd();
    m_tnd.uFlags = 0;

    return Shell_NotifyIcon( NIM_MODIFY, &m_tnd );
}

CWnd* ZISystemTray::GetNotificationWnd() const
{
    return CWnd::FromHandle( m_tnd.hWnd );
}

/////////////////////////////////////////////////////////////////////////////
// ZISystemTray menu manipulation

BOOL ZISystemTray::SetMenuDefaultItem( UINT uItem, BOOL bByPos )
{
    if ( ( m_DefaultMenuItemID == uItem ) && ( m_DefaultMenuItemByPos == bByPos ) )
        return TRUE;

    m_DefaultMenuItemID        = uItem;
    m_DefaultMenuItemByPos    = bByPos;   

    ::SetMenuDefaultItem( m_pSubMenu->m_hMenu, m_DefaultMenuItemID, m_DefaultMenuItemByPos );

    return TRUE;
}

void ZISystemTray::GetMenuDefaultItem( UINT& uItem, BOOL& bByPos )
{
    uItem    = m_DefaultMenuItemID;
    bByPos    = m_DefaultMenuItemByPos;
}

BOOL ZISystemTray::CheckMenuItem( UINT uItem, BOOL bStatus )
{
    ::CheckMenuItem( m_pSubMenu->m_hMenu, uItem, ( bStatus ) ? MF_CHECKED | MF_BYPOSITION : MF_UNCHECKED | MF_BYPOSITION );
    return TRUE;
}

BOOL ZISystemTray::EnableMenuItem( UINT uItem, BOOL bStatus )
{
    ::EnableMenuItem( m_pSubMenu->m_hMenu, uItem, ( bStatus ) ? MF_ENABLED | MF_BYPOSITION : MF_DISABLED | MF_BYPOSITION );
    return TRUE;
}

BOOL ZISystemTray::SetMenuTextItem( UINT uItem, CString Text )
{
    ::ModifyMenu( m_pSubMenu->m_hMenu, uItem, MF_BYPOSITION | MF_STRING, 0, static_cast<LPCSTR>( Text ) );
    ::DrawMenuBar( this->GetSafeHwnd() );

    return TRUE;
}

void ZISystemTray::OnTimer( UINT nIDEvent )
{
    ASSERT( nIDEvent == m_nIDEvent );

    COleDateTime CurrentTime    = COleDateTime::GetCurrentTime();
    COleDateTimeSpan period        = CurrentTime - m_StartTime;

    if ( m_nAnimationPeriod > 0 && m_nAnimationPeriod < period.GetTotalSeconds() )
    {
        StopAnimation();
        return;
    }

    StepAnimation();
}

LRESULT ZISystemTray::OnTrayNotification( UINT wParam, LONG lParam )
{
    //Return quickly if its not for this tray icon
    if ( wParam != m_tnd.uID )
        return 0L;

    CWnd* pTarget = AfxGetMainWnd();
    
    // No main window assigned
    if ( !pTarget )
        return 1;

    // Clicking with right button brings up a context menu
    if ( LOWORD( lParam ) == WM_RBUTTONUP )
    {
        // Make chosen menu item the default (bold font)
        ::SetMenuDefaultItem( m_pSubMenu->m_hMenu, m_DefaultMenuItemID, m_DefaultMenuItemByPos );

        // Display and track the popup menu
        CPoint pos;
        GetCursorPos( &pos );

        pTarget->SetForegroundWindow();
        ::TrackPopupMenu( m_pSubMenu->m_hMenu, 0, pos.x, pos.y, 0, pTarget->GetSafeHwnd(), NULL );

        // BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
        pTarget->PostMessage( WM_NULL, 0, 0 );
    } 
    else if ( LOWORD( lParam ) == WM_LBUTTONDBLCLK )
    {
        // Double click received, the default action is to execute default menu item
        pTarget->SetForegroundWindow();  

        UINT uItem;

        if ( m_DefaultMenuItemByPos )
        {
            uItem = m_pSubMenu->GetMenuItemID( m_DefaultMenuItemID );
        }
        else uItem = m_DefaultMenuItemID;

        pTarget->SendMessage( WM_COMMAND, uItem, 0 );
    }

    return 1;
}

LRESULT ZISystemTray::WindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
    if ( message == m_tnd.uCallbackMessage )
        return OnTrayNotification( wParam, lParam );

    return CWnd::WindowProc( message, wParam, lParam );
}
