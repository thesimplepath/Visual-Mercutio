// ZVOutputView.cpp : implementation file

#include "stdafx.h"
#include "ZVOutputView.h"
#include "ZBToolbarObserverMsg.h"
#include ".\zvoutputview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 29 septembre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// _ZVOutputViewListBox

BEGIN_MESSAGE_MAP( _ZVOutputViewListBox, CListBox )
    //{{AFX_MSG_MAP(_ZVOutputViewListBox)
    ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelchange)
    ON_CONTROL_REFLECT(LBN_DBLCLK, OnDblclk)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZVOutputViewListBox::_ZVOutputViewListBox()
{
}

_ZVOutputViewListBox::~_ZVOutputViewListBox()
{
}

/////////////////////////////////////////////////////////////////////////////
// _ZVOutputViewListBox message handlers

void _ZVOutputViewListBox::OnSelchange()
{
    ZBToolbarObserverMsg msg( LBN_SELCHANGE );
    NotifyAllObservers( &msg );
}

void _ZVOutputViewListBox::OnDblclk()
{
    ZBToolbarObserverMsg msg( LBN_DBLCLK );
    NotifyAllObservers( &msg );
}

/////////////////////////////////////////////////////////////////////////////
// ZVOutputView

IMPLEMENT_DYNAMIC( ZVOutputView, CWnd )

BEGIN_MESSAGE_MAP( ZVOutputView, CWnd )
    //{{AFX_MSG_MAP(ZVOutputView)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVOutputView::ZVOutputView()
    : m_IsInDebugMode    ( false ),
      m_SelectLast        ( false ),
      m_List            ( NULL )
{
    m_clrBtnFace = ::GetSysColor( COLOR_BTNFACE );

    m_List = new _ZVOutputViewListBox();
}

ZVOutputView::~ZVOutputView()
{
}

// JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release pour permettre un nettoyage de la mémoire.
void ZVOutputView::Release()
{
    if ( m_List != NULL )
    {
        m_List->DetachObserver( this );
        delete m_List;
        m_List = NULL;
    }
}

void ZVOutputView::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
    if ( pMsg && ISA( pMsg, ZBToolbarObserverMsg ) )
    {
        switch ( dynamic_cast<ZBToolbarObserverMsg*>( pMsg )->GetMessageID() )
        {
            case LBN_SELCHANGE:
            {
                OnSelChanged();
                break;
            }

            case LBN_DBLCLK:
            {
                OnDoubleClick();
                break;
            }
        }
    }
}

int ZVOutputView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
    if ( CWnd::OnCreate( lpCreateStruct ) == -1 )
    {
        return -1;
    }

    // JMR-MODIF - Le 29 septembre 2005 - Contrôle que m_List existe avant de tenter de l'utiliser.
    if ( m_List == NULL )
    {
        return -1;
    }

    if ( !m_List->Create ( WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_DISABLENOSCROLL | LBS_NOTIFY,
                           CRect( 0, 0, 0, 0 ),
                           this,
                           IDC_OUTPUTVIEW_LIST ) )
    {
        TRACE0( _T( "Failed to create view for the CListBox in ZVOutputView\n" ) );
        return -1;
    }

    // Get the log font.
    NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof( NONCLIENTMETRICS );

    VERIFY( ::SystemParametersInfo( SPI_GETNONCLIENTMETRICS,
                                    sizeof( NONCLIENTMETRICS ),
                                    &ncm,
                                    0 ) );

    m_Font.CreateFontIndirect( &ncm.lfMessageFont );
    m_List->SetFont( &m_Font );
    m_List->SetHorizontalExtent( 2000 );

    m_List->AttachObserver( this );

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// ZVOutputView message handlers

BOOL ZVOutputView::OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo )
{
    // JMR-MODIF - Le 29 septembre 2005 - Contrôle que m_List existe avant de tenter de l'utiliser.
    if ( m_List == NULL )
    {
        return FALSE;
    }

    // first pump through normal channels.  This allows you to override
    // the components default handling inside the view class.
    if ( CWnd::OnCmdMsg( nID, nCode, pExtra, pHandlerInfo ) )
    {
        return TRUE;
    }

    // then pump through the visual component
    return m_List->OnCmdMsg( nID, nCode, pExtra, pHandlerInfo );
}

BOOL ZVOutputView::OnWndMsg( UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult )
{
    BOOL bHandled = FALSE;
    LRESULT lResult;

    if ( m_List != NULL )
    {
        bHandled = m_List->OnWndMsg( message, wParam, lParam, &lResult );
    }

    if( !bHandled )
    {
        bHandled = CWnd::OnWndMsg( message, wParam, lParam, pResult );
    }

    return bHandled;
}

void ZVOutputView::OnSize( UINT nType, int cx, int cy )
{
    // JMR-MODIF - Le 29 septembre 2005 - Contrôle que m_List existe avant de tenter de l'utiliser.
    if ( m_List == NULL )
    {
        return;
    }

    CWnd::OnSize( nType, cx, cy );
    
    if ( ::IsWindow( m_List->GetSafeHwnd() ) )
    {
        m_List->MoveWindow( 0, 0, cx, cy );
    }
}

void ZVOutputView::OnPaint()
{
    CPaintDC dc( this ); // device context for painting

    // Get the client rect for this control.
    CRect rc;
    GetClientRect( &rc );

    // Set the background to transparent, and draw a 3D
    // border around the control.
    dc.SetBkMode( TRANSPARENT );
    dc.FillSolidRect( rc, m_clrBtnFace );
}
