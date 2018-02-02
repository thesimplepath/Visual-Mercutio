/////////////////////////////////////////////////////////////////////////////
//@doc ZVLogicalSystem
//@module ZVLogicalSystem.cpp | Implementation of the <c ZVLogicalSystem> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 05/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZVLogicalSystem.h"

// JMR-MODIF - Le 1er janvier 2007 - Ajout de l'en-tête ZBMediator.h
#include "zMediator\ZBMediator.h"

#include "zBaseLib\ZBToolbarObserverMsg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Constant definition
const int _FlatLogicalSystemToolbarHeight	= 22;

const int IDC_LGS_ADDSYSTEM					= 3000;
const int IDC_LGS_RENAMESYSTEM				= 3001;
const int IDC_LGS_DELETESYSTEM				= 3002;
// JMR-MODIF - Le 27 février 2006 - Ajout de l'ID IDC_LGS_MOVESYSTEM
const int IDC_LGS_MOVESYSTEM				= 3003;
const int IDC_LGS_PROPERTIES				= 3004;
const int IDC_LGS_REFRESHVIEWS				= 3005;

const int UM_LGS_ADDSYSTEM					= 3000;
const int UM_LGS_RENAMESYSTEM				= 3001;
const int UM_LGS_DELETESYSTEM				= 3002;
// JMR-MODIF - Le 27 février 2006 - Ajout de l'ID UM_LGS_MOVESYSTEM
const int UM_LGS_MOVESYSTEM					= 3003;
const int UM_LGS_PROPERTIES					= 3004;
const int UM_LGS_REFRESH					= 3005;

const int IDC_LGS_FLATTOOLBAR				= 11005;
const int IDC_LGS_CTRL						= 11006;

/////////////////////////////////////////////////////////////////////////////
// _ZILogicalSystemFlatToolBar

BEGIN_MESSAGE_MAP( _ZILogicalSystemFlatToolBar, CStatic )
	//{{AFX_MSG_MAP(_ZILogicalSystemFlatToolBar)
	ON_BN_CLICKED(IDC_LGS_ADDSYSTEM, OnAddSystemButton)
	ON_BN_CLICKED(IDC_LGS_RENAMESYSTEM, OnRenameSystemButton)
	ON_BN_CLICKED(IDC_LGS_DELETESYSTEM, OnDeleteSystemButton)
	ON_BN_CLICKED(IDC_LGS_MOVESYSTEM, OnMoveSystemButton)
	ON_BN_CLICKED(IDC_LGS_PROPERTIES, OnPropertiesButton)
	ON_BN_CLICKED(IDC_LGS_REFRESHVIEWS, OnRefreshButton)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZILogicalSystemFlatToolBar::_ZILogicalSystemFlatToolBar()
{
	m_ImageList.Create( IDB_LOGICALSYSTEM_FLATTOOLBAR, 20, 1, RGB( 255, 0, 255 ) );
}

_ZILogicalSystemFlatToolBar::~_ZILogicalSystemFlatToolBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// _ZILogicalSystemFlatToolBar message handlers

int _ZILogicalSystemFlatToolBar::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CStatic::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	int	IconIndex = 0;

	CRect rc;
	GetWindowRect( &rc );
	ScreenToClient( &rc );

	rc.top		+= 1;
	rc.bottom	-= 1;
	rc.left		+= 1;
	rc.right	 = rc.left + 24;

	
	if ( !m_RefreshButton.Create( NULL,
								  WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
								  rc,
								  this,
								  IDC_LGS_REFRESHVIEWS ) )
	{
		TRACE0( _T( "Unable to create refresh button in system workspace.\n" ) );
		return -1;
	}

	m_RefreshButton.SetIcon( m_ImageList.ExtractIcon( IconIndex++ ), CSize( 20, 20 ) );
	rc.OffsetRect( 24, 0 );

	if ( !m_AddSystemButton.Create( NULL,
									WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
									rc,
									this,
									IDC_LGS_ADDSYSTEM ) )
	{
		TRACE0( _T( "Unable to create add button in system workspace.\n" ) );
		return -1;
	}

	m_AddSystemButton.SetIcon( m_ImageList.ExtractIcon( IconIndex++ ), CSize( 20, 20 ) );
	rc.OffsetRect( 24, 0 );

	if ( !m_RenameSystemButton.Create( NULL,
									   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
									   rc,
									   this,
									   IDC_LGS_RENAMESYSTEM ) )
	{
		TRACE0( _T( "Unable to create rename button in system workspace.\n" ) );
		return -1;
	}

	m_RenameSystemButton.SetIcon( m_ImageList.ExtractIcon( IconIndex++ ), CSize( 20, 20 ) );
	rc.OffsetRect( 24, 0 );

	if ( !m_DeleteSystemButton.Create( NULL,
									   WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
									   rc,
									   this,
									   IDC_LGS_DELETESYSTEM ) )
	{
		TRACE0( _T( "Unable to create delete button in system workspace.\n" ) );
		return -1;
	}

	m_DeleteSystemButton.SetIcon( m_ImageList.ExtractIcon( IconIndex++ ), CSize( 20, 20 ) );
	rc.OffsetRect( 24, 0 );

	// **********************************************************************************************
	// JMR-MODIF - Le 27 février 2006 - Ajout du bouton Move dans la barre.
	if ( !m_MoveSystemButton.Create( NULL,
									 WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
									 rc,
									 this,
									 IDC_LGS_MOVESYSTEM ) )
	{
		TRACE0( _T( "Unable to create move button in system workspace.\n" ) );
		return -1;
	}

	m_MoveSystemButton.SetIcon( m_ImageList.ExtractIcon( IconIndex++ ), CSize( 20, 20 ) );
	rc.OffsetRect( 24, 0 );
	// **********************************************************************************************

	if ( !m_PropertiesButton.Create( NULL,
									 WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
									 rc,
									 this,
									 IDC_LGS_PROPERTIES ) )
	{
		TRACE0( _T( "Unable to create properties button in system workspace.\n" ) );
		return -1;
	}

	m_PropertiesButton.SetIcon( m_ImageList.ExtractIcon( IconIndex++ ), CSize( 20, 20 ) );
	rc.OffsetRect( 24, 0 );

	// Create the ToolTip control.
	m_tooltip.Create( this );
	m_tooltip.Activate( TRUE );

	m_tooltip.AddTool( GetDlgItem( IDC_LGS_ADDSYSTEM ),		IDS_LGS_ADDSYSTEM );
	m_tooltip.AddTool( GetDlgItem( IDC_LGS_RENAMESYSTEM ),	IDS_LGS_RENAMESYSTEM );
	m_tooltip.AddTool( GetDlgItem( IDC_LGS_DELETESYSTEM ),	IDS_LGS_DELETESYSTEM );
	// JMR-MODIF - Le 27 février 2006 - Ajout de l'aide pour le bouton Move.
	m_tooltip.AddTool( GetDlgItem( IDC_LGS_MOVESYSTEM ),	IDS_LGS_MOVESYSTEM );
	m_tooltip.AddTool( GetDlgItem( IDC_LGS_PROPERTIES ),	IDS_LGS_PROPERTIES );
	m_tooltip.AddTool( GetDlgItem( IDC_LGS_REFRESHVIEWS ),	IDS_REFRESH );

	return 0;
}

void _ZILogicalSystemFlatToolBar::PreSubclassWindow()
{
	CStatic::PreSubclassWindow();
}

void _ZILogicalSystemFlatToolBar::OnAddSystemButton()
{
	ZBToolbarObserverMsg Msg( UM_LGS_ADDSYSTEM );
	NotifyAllObservers( &Msg );
}

void _ZILogicalSystemFlatToolBar::OnRenameSystemButton()
{
	ZBToolbarObserverMsg Msg( UM_LGS_RENAMESYSTEM );
	NotifyAllObservers( &Msg );

	// JMR-MODIF - Le 1er janvier 2007 - Ordonne au médiateur de rafraîchir l'affichage.
	ZBMediator::Instance()->RefreshPropertiesWorkspace();
}

void _ZILogicalSystemFlatToolBar::OnDeleteSystemButton()
{
	ZBToolbarObserverMsg Msg( UM_LGS_DELETESYSTEM );
	NotifyAllObservers( &Msg );

	// JMR-MODIF - Le 1er janvier 2007 - Ordonne au médiateur de rafraîchir l'affichage.
	ZBMediator::Instance()->RefreshPropertiesWorkspace();
}

// JMR-MODIF - Le 27 février 2006 - Ajout de la fonction de réponse à l'événement du bouton Move.
void _ZILogicalSystemFlatToolBar::OnMoveSystemButton()
{
	ZBToolbarObserverMsg Msg( UM_LGS_MOVESYSTEM );
	NotifyAllObservers( &Msg );
}

void _ZILogicalSystemFlatToolBar::OnPropertiesButton()
{
	ZBToolbarObserverMsg Msg( UM_LGS_PROPERTIES );
	NotifyAllObservers( &Msg );
}

void _ZILogicalSystemFlatToolBar::OnRefreshButton()
{
	ZBToolbarObserverMsg Msg( UM_LGS_REFRESH );
	NotifyAllObservers( &Msg );
}

BOOL _ZILogicalSystemFlatToolBar::PreTranslateMessage( MSG* pMsg )
{
	// Let the ToolTip process this message.
	m_tooltip.RelayEvent( pMsg );
	return CStatic::PreTranslateMessage( pMsg );
}

/////////////////////////////////////////////////////////////////////////////
// ZVLogicalSystem

IMPLEMENT_DYNCREATE( ZVLogicalSystem, CWnd )

BEGIN_MESSAGE_MAP( ZVLogicalSystem, CWnd )
	//{{AFX_MSG_MAP(ZVLogicalSystem)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVLogicalSystem::ZVLogicalSystem()
{
	m_clrBtnFace = ::GetSysColor( COLOR_BTNFACE );
}

ZVLogicalSystem::~ZVLogicalSystem()
{
}

// JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release pour permettre un nettoyage de la mémoire.
void ZVLogicalSystem::Release()
{
	m_Ctrl.Release();
}

void ZVLogicalSystem::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
	// Forward the message to the property control
	m_Ctrl.OnUpdate( pSubject, pMsg );

	if ( pMsg && ISA( pMsg, ZBToolbarObserverMsg ) )
	{
		switch ( dynamic_cast<ZBToolbarObserverMsg*>( pMsg )->GetMessageID() )
		{
			case UM_LGS_REFRESH:
			{
				OnRefresh();
				break;
			}

			case UM_LGS_ADDSYSTEM:
			{
				OnAddSystem();
				break;
			}

			case UM_LGS_RENAMESYSTEM:
			{
				OnRenameSystem();
				break;
			}

			case UM_LGS_DELETESYSTEM:
			{
				OnDeleteSystem();
				break;
			}

			// JMR-MODIF - Le 27 février 2006 - Redirection de l'événement du bouton Move.
			case UM_LGS_MOVESYSTEM:
			{
				OnMoveSystem();
				break;
			}

			case UM_LGS_PROPERTIES:
			{
				OnProperties();
				break;
			}
		}
	}
}

int ZVLogicalSystem::HasContextMenu( CWnd* pWnd, CPoint point )
{
	if ( ::IsWindow( m_Ctrl.GetSafeHwnd() ) )
	{
		return m_Ctrl.HasContextMenu( pWnd, point );
	}

	return -1;
}

void ZVLogicalSystem::DisplayContextMenu( CWnd* pWnd, CPoint point )
{
	if ( ::IsWindow( m_Ctrl.GetSafeHwnd() ) )
	{
		m_Ctrl.DisplayContextMenu( pWnd, point );
	}
}

/////////////////////////////////////////////////////////////////////////////
// ZVLogicalSystem message handlers

int ZVLogicalSystem::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CWnd::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	// Create the flat toolbar
	reinterpret_cast<CStatic&>( m_FlatToolBar ).Create( _T( "" ),
														WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
														CRect( 0, 0, 100,
														_FlatLogicalSystemToolbarHeight ),
														this,
														IDC_LGS_FLATTOOLBAR );

	// Create the user group control
	m_Ctrl.Create( WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS,
				   CRect( 0, 0, 0, 0 ),
				   this,
				   IDC_LGS_CTRL );
	
	// Attach us as an observer for messages
	m_FlatToolBar.AttachObserver( this );

	// Attach the user group control for notification
	AttachObserver( &m_Ctrl );

	return 0;
}

void ZVLogicalSystem::OnSize( UINT nType, int cx, int cy )
{
	CWnd::OnSize( nType, cx, cy );

	if ( ::IsWindow( m_FlatToolBar.GetSafeHwnd() ) )
	{
		m_FlatToolBar.MoveWindow( 0, 0, cx, _FlatLogicalSystemToolbarHeight );
		m_Ctrl.MoveWindow( 0,
						   _FlatLogicalSystemToolbarHeight + 1,
						   cx,
						   cy - ( _FlatLogicalSystemToolbarHeight + 2 ) );
	}
}

void ZVLogicalSystem::OnPaint()
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

/////////////////////////////////////////////////////////////////////////////
// ZVLogicalSystem message handlers from toolbar

void ZVLogicalSystem::OnRefresh()
{
	CWaitCursor Cursor;

	// Refresh the user group control
	if ( ::IsWindow( m_Ctrl.GetSafeHwnd() ) )
	{
		m_Ctrl.Refresh();
	}
}

void ZVLogicalSystem::OnAddSystem()
{
	// Add a new group
	if ( ::IsWindow( m_Ctrl.GetSafeHwnd() ) )
	{
		m_Ctrl.OnNewLogicalSystem();
	}
}

void ZVLogicalSystem::OnRenameSystem()
{
	// Rename the selected group
	if ( ::IsWindow( m_Ctrl.GetSafeHwnd() ) )
	{
		m_Ctrl.OnRenameLogicalSystem();
	}
}

void ZVLogicalSystem::OnDeleteSystem()
{
	// Delete the selected group
	if ( ::IsWindow( m_Ctrl.GetSafeHwnd() ) )
	{
		m_Ctrl.OnDeleteLogicalSystem();
	}
}

void ZVLogicalSystem::OnMoveSystem()
{
	// Delete the selected group
	if ( ::IsWindow( m_Ctrl.GetSafeHwnd() ) )
	{
		m_Ctrl.OnMoveLogicalSystem();
	}
}

void ZVLogicalSystem::OnProperties()
{
	// Display the properties
	if ( ::IsWindow( m_Ctrl.GetSafeHwnd() ) )
	{
		m_Ctrl.OnLogicalSystemProperties();
	}
}

bool ZVLogicalSystem::CanAddSystem()
{
	// Can Add a new group
	if ( ::IsWindow( m_Ctrl.GetSafeHwnd() ) )
	{
		return m_Ctrl.CanNewLogicalSystem();
	}

	return false;
}

bool ZVLogicalSystem::CanRenameSystem()
{
	// Can Rename the selected group
	if ( ::IsWindow( m_Ctrl.GetSafeHwnd() ) )
	{
		return m_Ctrl.CanRenameLogicalSystem();
	}

	return false;
}

bool ZVLogicalSystem::CanDeleteSystem()
{
	// Can Delete the selected group
	if ( ::IsWindow( m_Ctrl.GetSafeHwnd() ) )
	{
		return m_Ctrl.CanDeleteLogicalSystem();
	}

	return false;
}

bool ZVLogicalSystem::CanProperties()
{
	// Can Display the properties
	if ( ::IsWindow( m_Ctrl.GetSafeHwnd() ) )
	{
		return m_Ctrl.CanLogicalSystemProperties();
	}

	return false;
}
