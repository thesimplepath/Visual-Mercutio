// ZVFileWnd.cpp : implementation file

#include "stdafx.h"
#include "ZVFileWnd.h"

#include "zBaseLib\ZBToolbarObserverMsg.h"

#include "zRes32\ZRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Constant definition
const int _FlatToolbarHeight		= 22;
const int _FilenameControlHeight	= 18;

const int IDC_FILEWND_FILENAME		= 300;
const int IDC_FILEWND_FILETREE		= 301;
const int IDC_FILEWND_FLATTOOLBAR	= 302;

/////////////////////////////////////////////////////////////////////////////
// ZVFileWnd

IMPLEMENT_DYNCREATE( ZVFileWnd, CWnd )

BEGIN_MESSAGE_MAP( ZVFileWnd, CWnd )
	//{{AFX_MSG_MAP(ZVFileWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_FILEWND_FILETREE, OnSelchangedDirectory)
	ON_NOTIFY(NM_DBLCLK, IDC_FILEWND_FILETREE, OnDblclkDirectory)
	ON_NOTIFY(NM_CLICK, IDC_FILEWND_FILETREE, OnClickDirectory)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVFileWnd::ZVFileWnd()
{
	m_clrBtnFace = ::GetSysColor( COLOR_BTNFACE );
}

ZVFileWnd::~ZVFileWnd()
{
}

int ZVFileWnd::OnCreate( LPCREATESTRUCT lpCreateStruct )
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
														IDC_FILEWND_FLATTOOLBAR );

	// Defines the edit as search for file
	m_Filename.SetSearchType( ZSEARCHEDIT_FILE, _T( "" ) );

	// Create the edit
	m_Filename.Create ( WS_CHILD | WS_VISIBLE | WS_BORDER,
						CRect( 0, 0, 100, _FilenameControlHeight ),
						this,
						IDC_FILEWND_FILENAME );

	// Create the list control
	m_DirTreeCtrl.Create( WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL,
						  CRect( 0, 0, 0, 0 ),
						  this,
						  IDC_FILEWND_FILETREE );
	
	// Attach us as an observer for messages
	m_FlatToolBar.AttachObserver( this );

	// Initialize the directory tree control
	m_DirTreeCtrl.Initialize( _T( "" ), true, true);

	// Assign the parent's toolbar
	m_FlatToolBar.SetParent( this );

	// Initialize the edit for drag & drop
	m_Filename.Init();

	return 0;
}

void ZVFileWnd::ReflectChangedDirectory()
{
	if ( m_DirTreeCtrl.IsValid() )
	{
		CString Filename = m_DirTreeCtrl.GetSelectedDirectory();
		m_Filename.GetWindowText( Filename );
	}
}

/////////////////////////////////////////////////////////////////////////////
// ZVFileWnd message handlers

void ZVFileWnd::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
	if ( pMsg && ISA( pMsg, ZBToolbarObserverMsg ) )
	{
		switch ( dynamic_cast<ZBToolbarObserverMsg*>( pMsg )->GetMessageID() )
		{
			case UM_STOPFILE:
			{
				OnStopFileButton();
				break;
			}

			case UM_REFRESHFILE:
			{
				OnRefreshButton();
				break;
			}

			default:
			{
				break;
			}
		}
	}
}

void ZVFileWnd::OnSelchangedDirectory( NMHDR* pNMHDR, LRESULT* pResult )
{
	ReflectChangedDirectory();
	*pResult = 0;
}

void ZVFileWnd::OnDblclkDirectory( NMHDR* pNMHDR, LRESULT* pResult )
{
	ReflectChangedDirectory();
	*pResult = 0;
}

void ZVFileWnd::OnClickDirectory( NMHDR* pNMHDR, LRESULT* pResult )
{
	ReflectChangedDirectory();
	*pResult = 0;
}

void ZVFileWnd::OnStopFileButton()
{
}

void ZVFileWnd::OnRefreshButton()
{
	m_DirTreeCtrl.Refresh();
}

void ZVFileWnd::OnSize( UINT nType, int cx, int cy )
{
	CWnd::OnSize( nType, cx, cy );

	if ( ::IsWindow( m_Filename.GetSafeHwnd() ) )
	{
		m_FlatToolBar.MoveWindow( 0, 0, cx, _FlatToolbarHeight );

		m_Filename.MoveWindow( 5, _FlatToolbarHeight + 5, cx - 5, _FilenameControlHeight );

		m_DirTreeCtrl.MoveWindow( 0,
								  _FlatToolbarHeight + 10 + _FilenameControlHeight,
								  cx,
								  cy - ( _FlatToolbarHeight + 10 + _FilenameControlHeight ) );
	}
}

void ZVFileWnd::OnPaint()
{
	// Device context for painting
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
// _ZVFileWndButtonToolBar

BEGIN_MESSAGE_MAP( _ZVFileWndButtonToolBar, CStatic )
	//{{AFX_MSG_MAP(_ZVFileWndButtonToolBar)
	ON_BN_CLICKED(IDC_STOPFILE, OnStopFileButton)
	ON_BN_CLICKED(IDC_REFRESHFILE, OnRefreshFileButton)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZVFileWndButtonToolBar::_ZVFileWndButtonToolBar( CWnd* pParent /*=NULL*/ )
	: m_pParent( pParent )
{
	m_ImageList.Create( IDB_FILE_FV_BUTTONS, 14, 1, RGB( 255, 0, 255 ) );
}

_ZVFileWndButtonToolBar::~_ZVFileWndButtonToolBar()
{
}

void _ZVFileWndButtonToolBar::SetParent(CWnd* pParent)
{
	m_pParent = pParent;
}

/////////////////////////////////////////////////////////////////////////////
// _ZVFileWndButtonToolBar message handlers

int _ZVFileWndButtonToolBar::OnCreate( LPCREATESTRUCT lpCreateStruct )
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
	rc.right	 = rc.left+20;

	if ( !m_StopWebButton.Create( NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
								  rc,
								  this,
								  IDC_STOPFILE ) )
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
									 IDC_REFRESHFILE ) )
	{
		TRACE0( _T( "Unable to create button.\n" ) );
		return -1;
	}

	m_RefreshWebButton.SetIcon( m_ImageList.ExtractIcon( IconIndex++ ), CSize( 14, 14 ) );

	// Create the ToolTip control.
	m_tooltip.Create( this );
	m_tooltip.Activate( TRUE );

	m_tooltip.AddTool( GetDlgItem( IDC_STOPFILE ), IDS_STOPFILE );
	m_tooltip.AddTool( GetDlgItem( IDC_REFRESHFILE ), IDS_REFRESHFILE );

	return 0;
}

void _ZVFileWndButtonToolBar::OnStopFileButton()
{
	ZBToolbarObserverMsg Msg( UM_STOPFILE );
	NotifyAllObservers( &Msg );
}

void _ZVFileWndButtonToolBar::OnRefreshFileButton()
{
	ZBToolbarObserverMsg Msg( UM_REFRESHFILE );
	NotifyAllObservers( &Msg );
}

BOOL _ZVFileWndButtonToolBar::PreTranslateMessage( MSG* pMsg )
{
	// Let the ToolTip process this message.
	m_tooltip.RelayEvent( pMsg );
	return CStatic::PreTranslateMessage( pMsg );
}
