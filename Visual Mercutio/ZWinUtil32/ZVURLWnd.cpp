// ZVURLWnd.cpp : implementation file

#include "stdafx.h"
#include "ZVURLWnd.h"

#include "zBaseLib\ZBToolbarObserverMsg.h"

#include "zRes32\ZRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage de code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Constant definition
const int _FlatToolbarHeight		= 22;
const int _URLEditControlHeight		= 18;
const int _GoButtonControlSize		= 18;

const int IDC_URLWND_URL			= 400;
const int IDC_URLWND_GOWEB			= 401;
const int IDC_URLWND_FLATTOOLBAR	= 402;
const int IDC_URLWND_WEBBROWSER		= 403;

/////////////////////////////////////////////////////////////////////////////
// ZVURLWnd

IMPLEMENT_DYNCREATE( ZVURLWnd, CWnd )

BEGIN_MESSAGE_MAP( ZVURLWnd, CWnd )
	//{{AFX_MSG_MAP(ZVURLWnd)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_URLWND_GOWEB, OnGo)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVURLWnd::ZVURLWnd()
	: m_pBrowser( NULL )
{
	m_URL			= _T( "" );
	m_clrBtnFace	= ::GetSysColor( COLOR_BTNFACE );
}

ZVURLWnd::~ZVURLWnd()
{
	if ( m_pBrowser )
	{
		delete m_pBrowser;
	}

	m_pBrowser = NULL;
}

int ZVURLWnd::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CWnd::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	// Create the flat toolbar
	reinterpret_cast<CStatic&>( m_FlatToolBar ).Create( _T( "" ),
														WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
														CRect( 0, 0, 100, _FlatToolbarHeight ),
														this,
														IDC_URLWND_FLATTOOLBAR );

	// Create the flat toolbar
	m_GoButton.Create( _T( "" ),
					   WS_CHILD | WS_VISIBLE,
					   CRect( 0, 0, _GoButtonControlSize, _GoButtonControlSize ),
					   this,
					   IDC_URLWND_GOWEB );

	// Create the url edit
	m_URLEdit.Create( WS_CHILD | WS_VISIBLE | WS_BORDER,
					  CRect( 0, 0, 100, _URLEditControlHeight ),
					  this,
					  IDC_URLWND_URL );

	m_GoButton.SetIcon( IDI_GOWEB );
	m_GoButton.SetAlign( ZCFlatButton::ST_ALIGN_HORIZ_RIGHT );
	m_GoButton.SetTooltipText( IDS_GOWEB );

	m_GoButton.DrawTransparent();

	// Create the control.
	m_pBrowser = new ZWebBrowser;
	ASSERT ( m_pBrowser );

	if ( !m_pBrowser->Create( NULL, NULL, WS_VISIBLE, CRect( 0, 0, 0, 0 ), this, IDC_URLWND_WEBBROWSER ) )
	{
		TRACE( _T( "failed to create browser\n" ) );
		delete m_pBrowser;
		m_pBrowser = NULL;
		return -1;
	}

	// Initialize the first URL.
	COleVariant noArg;

	if ( !m_URL.IsEmpty() )
	{
		m_pBrowser->Navigate( m_URL );
	}

	// Attach us as an observer for messages
	m_FlatToolBar.AttachObserver( this );

	// Attach us as an observer for edit
	m_URLEdit.AttachObserver( this );

	// Assign the parent's toolbar
	m_FlatToolBar.SetParent( this );

	// Assign the pointer to the value array
	m_URLEdit.Initialize( &m_ValueArray );

	// Assign the parent's edit
	m_URLEdit.SetParent( this );

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// ZVURLWnd message handlers

void ZVURLWnd::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
	if ( pMsg && ISA( pMsg, ZBToolbarObserverMsg ) )
	{
		switch ( dynamic_cast<ZBToolbarObserverMsg*>( pMsg )->GetMessageID() )
		{
			case UM_GOWEB:
			{
				OnGo();
				break;
			}

			case UM_STOPWEB:
			{
				OnStopWebButton();
				break;
			}

			case UM_REFRESHWEB:
			{
				OnRefreshWebButton();
				break;
			}

			case UM_PREVWEB:
			{
				OnPrevWebButton();
				break;
			}

			case UM_NEXTWEB:
			{
				OnNextWebButton();
				break;
			}

			default:
			{
				break;
			}
		}
	}
}

void ZVURLWnd::OnStopWebButton()
{
	if ( m_pBrowser )
	{
		m_pBrowser->Stop();
	}
}

void ZVURLWnd::OnRefreshWebButton()
{
	if ( m_pBrowser )
	{
		m_pBrowser->Refresh();
	}
}

void ZVURLWnd::OnPrevWebButton() 
{
	if ( m_pBrowser )
	{
		m_pBrowser->GoBack();
	}
}

void ZVURLWnd::OnNextWebButton() 
{
	if ( m_pBrowser )
	{
		m_pBrowser->GoForward();
	}
}

void ZVURLWnd::OnGo()
{
	// Retreive the window text
	m_URLEdit.GetWindowText( m_URL );

	bool Found = false;

	for ( int i = 0; i < m_ValueArray.GetSize(); ++i )
	{
		if ( m_ValueArray.GetAt(i) == m_URL )
		{
			Found = true;
			break;
		}
	}

	if ( !Found )
	{
		m_ValueArray.Add( m_URL );
		m_URLEdit.ReloadListOfValues();
	}

	if ( !m_URL.IsEmpty() )
	{
		m_pBrowser->Navigate( m_URL );
	}
}

void ZVURLWnd::OnSize( UINT nType, int cx, int cy )
{
	CWnd::OnSize( nType, cx, cy );

	if ( m_pBrowser && ::IsWindow( m_pBrowser->GetSafeHwnd() ) )
	{
		m_FlatToolBar.MoveWindow( 0, 0, cx, _FlatToolbarHeight );

		m_URLEdit.MoveWindow( 5, _FlatToolbarHeight + 5, cx - 15 - _GoButtonControlSize, _URLEditControlHeight );

		m_GoButton.MoveWindow( cx - 5 - _GoButtonControlSize,
							   _FlatToolbarHeight + 5,
							   _GoButtonControlSize,
							   _GoButtonControlSize );

		m_pBrowser->MoveWindow( 0,
								_FlatToolbarHeight + 10 + _URLEditControlHeight,
								cx ,
								cy - ( _FlatToolbarHeight + 10 + _URLEditControlHeight ) );
	}
}

void ZVURLWnd::OnPaint()
{
	// Obtain the device context for painting
	CPaintDC dc( this );

	// Get the client rect for this control.
	CRect rc;
	GetClientRect( &rc );

	// Set the background to transparent, and draw a 3D
	// border around the control.
	dc.SetBkMode( TRANSPARENT );
	dc.FillSolidRect( rc, m_clrBtnFace );
}

/////////////////////////////////////////////////////////////////////////////
// _ZVURLWndButtonToolBar

BEGIN_MESSAGE_MAP( _ZVURLWndButtonToolBar, CStatic )
	//{{AFX_MSG_MAP(_ZVURLWndButtonToolBar)
	ON_BN_CLICKED(IDC_STOPWEB, OnStopWebButton)
	ON_BN_CLICKED(IDC_REFRESHWEB, OnRefreshWebButton)
	ON_BN_CLICKED(IDC_PREVWEB, OnPrevWebButton)
	ON_BN_CLICKED(IDC_NEXTWEB, OnNextWebButton)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZVURLWndButtonToolBar::_ZVURLWndButtonToolBar( CWnd* pParent /*=NULL*/ )
	: m_pParent( pParent )
{
	m_ImageList.Create( IDB_URL_FV_BUTTONS, 14, 1, RGB( 255, 0, 255 ) );
}

_ZVURLWndButtonToolBar::~_ZVURLWndButtonToolBar()
{
}

void _ZVURLWndButtonToolBar::SetParent( CWnd* pParent )
{
	m_pParent = pParent;
}

/////////////////////////////////////////////////////////////////////////////
// _ZVURLWndButtonToolBar message handlers

int _ZVURLWndButtonToolBar::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CStatic::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	int IconIndex = 0;

	CRect rc;
	GetWindowRect( &rc );
	ScreenToClient( &rc );

	rc.top		+= 1;
	rc.bottom	-= 1;
	rc.left		+= 1;
	rc.right	 = rc.left + 20;

	
	if ( !m_PrevWebButton.Create( NULL,
								  WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
								  rc,
								  this,
								  IDC_PREVWEB ) )
	{
		TRACE0( _T( "Unable to create button.\n" ) );
		return -1;
	}

	m_PrevWebButton.SetIcon( m_ImageList.ExtractIcon( IconIndex++ ), CSize( 14, 14 ) );
	rc.OffsetRect( 20, 0 );

	if ( !m_NextWebButton.Create( NULL,
								  WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
								  rc,
								  this,
								  IDC_NEXTWEB ) )
	{
		TRACE0( _T( "Unable to create button.\n" ) );
		return -1;
	}

	m_NextWebButton.SetIcon( m_ImageList.ExtractIcon( IconIndex++ ), CSize( 14, 14 ) );
	rc.OffsetRect( 20, 0 );

	if ( !m_StopWebButton.Create( NULL,
								  WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
								  rc,
								  this,
								  IDC_STOPWEB ) )
	{
		TRACE0( _T( "Unable to create button.\n" ) );
		return -1;
	}

	m_StopWebButton.SetIcon( m_ImageList.ExtractIcon( IconIndex++ ), CSize( 14, 14 ) );
	rc.OffsetRect( 20, 0 );

	if ( !m_RefreshWebButton.Create( NULL,
									 WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
									 rc,
									 this,
									 IDC_REFRESHWEB ) )
	{
		TRACE0( _T( "Unable to create button.\n" ) );
		return -1;
	}

	m_RefreshWebButton.SetIcon( m_ImageList.ExtractIcon( IconIndex++ ), CSize( 14, 14 ) );

	// Create the ToolTip control.
	m_tooltip.Create( this );
	m_tooltip.Activate( TRUE );

	m_tooltip.AddTool( GetDlgItem( IDC_PREVWEB ), IDS_PREVWEB );
	m_tooltip.AddTool( GetDlgItem( IDC_NEXTWEB ), IDS_NEXTWEB );
	m_tooltip.AddTool( GetDlgItem( IDC_STOPWEB ), IDS_STOPWEB );
	m_tooltip.AddTool( GetDlgItem( IDC_REFRESHWEB ), IDS_REFRESHWEB );

	return 0;
}

void _ZVURLWndButtonToolBar::OnStopWebButton()
{
	ZBToolbarObserverMsg Msg( UM_STOPWEB );
	NotifyAllObservers( &Msg );
}

void _ZVURLWndButtonToolBar::OnRefreshWebButton()
{
	ZBToolbarObserverMsg Msg( UM_REFRESHWEB );
	NotifyAllObservers( &Msg );
}

void _ZVURLWndButtonToolBar::OnPrevWebButton()
{
	ZBToolbarObserverMsg Msg( UM_PREVWEB );
	NotifyAllObservers( &Msg );
}

void _ZVURLWndButtonToolBar::OnNextWebButton()
{
	ZBToolbarObserverMsg Msg( UM_NEXTWEB );
	NotifyAllObservers( &Msg );
}

BOOL _ZVURLWndButtonToolBar::PreTranslateMessage( MSG* pMsg )
{
	// Let the ToolTip process this message.
	m_tooltip.RelayEvent( pMsg );
	return CStatic::PreTranslateMessage( pMsg );
}

/////////////////////////////////////////////////////////////////////////////
// _ZCURLWndAddressIntelliEdit

BEGIN_MESSAGE_MAP( _ZCURLWndAddressIntelliEdit, ZCIntelliEdit )
	//{{AFX_MSG_MAP(_ZCURLWndAddressIntelliEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZCURLWndAddressIntelliEdit::_ZCURLWndAddressIntelliEdit( CWnd*			pParent			/*=NULL*/,
														  CStringArray*	pArrayOfValues	/*= NULL*/ )
	: ZCIntelliEdit	( pArrayOfValues ),
	  m_pParent		( pParent )
{
}

_ZCURLWndAddressIntelliEdit::~_ZCURLWndAddressIntelliEdit()
{
}

void _ZCURLWndAddressIntelliEdit::SetParent( CWnd* pParent )
{
	m_pParent = pParent;
}

void _ZCURLWndAddressIntelliEdit::OnEnter()
{
	ZBToolbarObserverMsg Msg( UM_GOWEB );
	NotifyAllObservers( &Msg );
}
