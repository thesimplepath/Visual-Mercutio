// ProcGraphModelView.cpp : implementation of the ZIProcessGraphModelView class

#include "stdafx.h"

#include "ProcGraphModelMdl.h"
#include "ProcGraphModelCtlr.h"

#include "ProcGraphModelDoc.h"
#include "ProcGraphModelView.h"
#include "zBaseLib\ZVSpanWnd.h"

#include "ZBModelObserverMsg.h"

// FileDlg
#include "zBaseLib\FileDlg.h"

#include "zRes32\zRes.h"
#include "zBaseLib\MsgBox.h"

#include "zBaseLib\ZAGlobal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 29 septembre 2005 - Ajout des décorations unicoder _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphModelView

IMPLEMENT_DYNCREATE( ZIProcessGraphModelView, ZIDropScrollView )

BEGIN_MESSAGE_MAP( ZIProcessGraphModelView, ZIDropScrollView )
	//{{AFX_MSG_MAP(ZIProcessGraphModelView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_CREATEMETAFILE, OnExportModelToImageFile)
	ON_MESSAGE(UM_REFRESH_SYMBOL, OnRefreshSymbol)
	ON_MESSAGE(UM_REFRESH_SYMBOLSET, OnRefreshSymbolSet)
	ON_MESSAGE(UM_BROWSE_SYMBOL, OnBrowseSymbol)
	ON_MESSAGE(UM_OPEN_MODELPAGE, OnOpenModelPage)
	ON_MESSAGE(UM_ENSUREVISIBLE_SYMBOL, OnEnsureVisibleSymbol)
	ON_MESSAGE(UM_DOCUMENTMODELHASCHANGED, OnModelDocumentHasChanged)
	ON_MESSAGE(UM_START_PROPERTY_EDITION, OnAdviseStartPropertyEdition)
	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphModelView construction/destruction

ZIProcessGraphModelView::ZIProcessGraphModelView()
	: m_pModelOfView	( NULL ),
	  m_CurrentRatio	( 1 ),
	  m_PanInitialized	( false )
{
}

ZIProcessGraphModelView::~ZIProcessGraphModelView()
{
	m_ToolTip.DestroyWindow();
}

BOOL ZIProcessGraphModelView::PreCreateWindow( CREATESTRUCT& cs )
{
	// Modify the Window class or styles here by modifying
	// the CREATESTRUCT cs

	return ZIDropScrollView::PreCreateWindow( cs );
}

ZDProcessGraphModelController* ZIProcessGraphModelView::GetModelController()
{
	if ( GetViewport() )
	{
		return GetViewport()->GetModelController();
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphModelView attributes

const CString ZIProcessGraphModelView::GetViewName()
{
	if ( GetModel() )
	{
		return GetModel()->GetAbsolutePath();
	}

	return _T( "" );
}

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphModelView drawing

void ZIProcessGraphModelView::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo )
{
	ZIProcessGraphModelViewport::OnPrepareDC( pDC, pInfo );
}

void ZIProcessGraphModelView::SetRatio()
{
	// Protect here, so callers don't have to
	if ( m_pOverview == NULL || m_PanInitialized == false )
	{
		return;
	}

	CPoint	pt;
	CRect	clientRect;

	//The overview window shows the entire view
	//in it's borders, so setup the device size to
	//the client size.
	m_pOverview->GetClientRect( &clientRect );

	ASSERT( clientRect.top == 0 && clientRect.left == 0 );

	// Make sure that the overview looks just like the
	// panview derivative.
	PersistRatio( m_totalLog, m_totalDev, pt );

	double RatioX = (double)clientRect.right  / (double)m_totalDev.cx;
	double RatioY = (double)clientRect.bottom / (double)m_totalDev.cy;
	m_CurrentRatio = __min( RatioX, RatioY );

	m_vpPan.SetMagnification( static_cast<int>( (double)100*m_CurrentRatio ),
							  static_cast<int>( (double)100*m_CurrentRatio ) );
}

// UpdateOverviewRect. The viewport has changed, so we need to let the overview window know.
// Calculate the currently visible rectangle in logical coordinates and let it know.
void ZIProcessGraphModelView::UpdateOverviewRect()
{
	ASSERT_VALID( this );

	//Ok for m_pOverview to be NULL.
	//Protect here, so callers don't have to
	if ( m_pOverview == NULL )
	{
		return;
	}

	SetRatio();

	CRect rectClient;
	GetClientRect( &rectClient );

	//BLOCK for DC
	rectClient.left		= static_cast<int>( (double)rectClient.left * m_CurrentRatio );
	rectClient.top		= static_cast<int>( (double)rectClient.top * m_CurrentRatio );
	rectClient.right	= static_cast<int>( (double)rectClient.right * m_CurrentRatio );
	rectClient.bottom	= static_cast<int>( (double)rectClient.bottom * m_CurrentRatio );

	CClientDC dc( this );
	OnPrepareDC( &dc );
	dc.DPtoLP( &rectClient );

	m_pOverview->SetPanRect( rectClient );
}

// PreOverview. We're about to call preparedc/ondraw with the values necessary to draw the
// overview window, so save the current state so that our view doesn't get messed up by having
// a new zoom level.
void ZIProcessGraphModelView::PreOverview()
{
	m_InVirtualDraw = TRUE;
}

// PostOverview. The overview has been painted, so now revert back to our original state as preserved in 
// PreOverview() so that when the view draws, it doesn't get messed up by drawing using the
// stuff we setup for the overview window.
void ZIProcessGraphModelView::PostOverview()
{
	m_InVirtualDraw = FALSE;
}

void ZIProcessGraphModelView::InitializePanViewport()
{
	// Create the pan viewport
	m_vpPan.SetModel( GetModel() );
	m_vpPan.Create( m_pOverview, NULL);

	CRect rcClient;
	GetClientRect( &rcClient );
	m_vpPan.SetSize( rcClient.Width(), rcClient.Height() );

	// Hide the ruler
	m_vpPan.SetRulerVisible( odg_nHorizontalRuler, FALSE );
	m_vpPan.SetRulerVisible( odg_nVerticalRuler, FALSE );
	m_vpPan.OnInitialUpdate();
	
	m_PanInitialized = true;

	UpdateOverviewRect();
}

void ZIProcessGraphModelView::OnDraw( CDC* pDC )
{
	// Update the window with the contents of the viewport buffer.
	ZIProcessGraphModelViewport::Draw( pDC );
}

void ZIProcessGraphModelView::OnDrawPan( CDC* pDC )
{
	if ( m_pOverview != NULL )
	{
		if ( m_PanInitialized == false )
		{
			InitializePanViewport();
		}

		//Setup a special zoom mode for the pan overview window
		//So that the view's OnDraw will be tricked into drawing
		//our overview window for us.
		m_bCenter  = FALSE;

		// Update the window with the contents of the viewport buffer.
		m_vpPan.Draw( pDC );
		TRACE( _T( "DRAW PAN  " ) );
	}
}

int ZIProcessGraphModelView::OnCreate( LPCREATESTRUCT lpcs )
{
	if ( ZIDropScrollView::OnCreate( lpcs ) == -1 )
	{
		return -1;
	}

	// Check the model existance
	ZDProcessGraphModelMdl* pModel = GetModel();

	if ( !pModel )
	{
		return -1;
	}

	GetViewport()->SetModel( pModel );
	ZIProcessGraphModelView::SizeVpToModel();

	return 0;
}

void ZIProcessGraphModelView::SetModel( ZDProcessGraphModelMdl* pModel, bool SizeViewport /*= true*/ )
{
	m_pModelOfView = pModel;
	GetViewport()->SetModel( pModel );

	if ( SizeViewport )
	{
		SizeVpToModel();
	}

	ZIProcessGraphModelViewport::UpdateAll();

	// Protect here, so callers don't have to
	if ( m_pOverview == NULL || m_PanInitialized == false )
	{
		return;
	}

	// At the same time, sets the model to the pan viewport
	m_vpPan.SetModel( pModel );

	// Only if the pan is initialized, update the area
	if ( m_PanInitialized )
	{
		m_vpPan.UpdateAll();
	}
}

ZDProcessGraphModelMdl* ZIProcessGraphModelView::GetModel()
{
	if ( m_pModelOfView )
	{
		return m_pModelOfView;
	}

	// If can't activate a view with model's name, create a new view
	if ( GetDocument() && ISA( GetDocument(), ZDProcessGraphModelDoc ) )
	{
		return ( (ZDProcessGraphModelDoc*)GetDocument() )->GetModel();
	}

	return NULL;
}

void ZIProcessGraphModelView::SizeVpToModel()
{
	if ( !::IsWindow( GetSafeHwnd() ) || !GetViewport()->GetWnd() )
	{
		return;
	}

	if ( GetDocument() && ISA( GetDocument(), ZDProcessGraphModelDoc ) )
	{
		ZVDocumentPageSetup* m_pPageSetup = ( (ZDProcessGraphModelDoc*)GetDocument() )->GetPrinterPageSize();

		ZIProcessGraphModelViewport::SizeVp( m_pPageSetup );
	}
}

void ZIProcessGraphModelView::OnInitialUpdate()
{
	ZTMvcScrollView<ZIProcessGraphModelViewport>::OnInitialUpdate();

	// Set the document page units
	if ( GetDocument() && ISA( GetDocument(), ZDProcessGraphModelDoc ) )
	{
		ZIProcessGraphModelViewport::SetPageUnits( ( (ZDProcessGraphModelDoc*)GetDocument() )->GetPageUnits() );
	}

	// Size the viewport
	ZIProcessGraphModelView::SizeVpToModel();

	// Create the floating tooltip
	if ( m_ToolTip.Create( this, TTS_ALWAYSTIP ) && m_ToolTip.AddTool( this ) )
	{
		m_ToolTip.SendMessage( TTM_SETMAXTIPWIDTH, 0, SHRT_MAX );
		m_ToolTip.SendMessage( TTM_SETDELAYTIME, TTDT_AUTOPOP, SHRT_MAX );
		m_ToolTip.SendMessage( TTM_SETDELAYTIME, TTDT_INITIAL, 200 );
		m_ToolTip.SendMessage( TTM_SETDELAYTIME, TTDT_RESHOW, 200 );

		// Set the text color and the background color
		m_ToolTip.SendMessage( TTM_SETTIPTEXTCOLOR, defCOLOR_WHITE, 0L );
		m_ToolTip.SendMessage( TTM_SETTIPBKCOLOR, defCOLOR_BLUE, 0L );
	}
	else
	{
		TRACE( _T( "Error in creating ToolTip" ) );
	}
}

// Drag and drop functions
bool ZIProcessGraphModelView::DropItem( CObject* pObj, CPoint pt )
{
	ZDProcessGraphModelController* pCtrl = ZIProcessGraphModelViewport::GetModelController();

	if ( pCtrl )
	{
		return pCtrl->DropItem( pObj, pt );
	}

	return false;
}

bool ZIProcessGraphModelView::AcceptDropItem( CObject* pObj, CPoint pt )
{
	ZDProcessGraphModelController* pCtrl = ZIProcessGraphModelViewport::GetModelController();

	if ( pCtrl )
	{
		return pCtrl->AcceptDropItem( pObj, pt );
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphModelView printing

BOOL ZIProcessGraphModelView::OnPreparePrinting( CPrintInfo* pInfo )
{
	// JMR-MODIF - Le 12 juillet 2005 - Supprimé l'appel pour la mise en page de Stingray Studio; conflit avec MFC.
	// Prepare the CPrintInfo object to print the diagram.
//	if (!ZIProcessGraphModelViewport::PreparePrinting(pInfo))
//		return FALSE;

	// JMR-MODIF - Le 20 juillet 2005 - Ajout du code pour la reconfiguration de l'imprimante en fonction des
	// données en provenance du modèle.
	ZVDocumentPageSetup* m_pPageSetup = GetPrinterPageSize();

	if ( m_pPageSetup != NULL )
	{
		m_pPageSetup->OnUpdatePrinterSettings();
	}

	// JMR-MODIF - Le 20 juillet 2005 - Préparation du nombre de pages à imprimer.
	// Pour l'instant, on limite les dégâts : On autorise seulement l'impression de la page courante. Mais à
	// l'avenir, il faudrait penser à améliorer le système.
	pInfo->SetMinPage( 1 );
	pInfo->SetMaxPage( 1 );

	// default preparation
	return DoPreparePrinting( pInfo );
}

void ZIProcessGraphModelView::OnBeginPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ )
{
}

void ZIProcessGraphModelView::OnEndPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ )
{
}

void ZIProcessGraphModelView::OnPrint( CDC* pDC, CPrintInfo* pInfo )
{
	// add customized printing code here

	// Print the canvas
	ZIProcessGraphModelViewport::Print( pDC, pInfo );
}

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphModelView diagnostics

#ifdef _DEBUG

void ZIProcessGraphModelView::AssertValid() const
{
	ZIDropScrollView::AssertValid();
}

void ZIProcessGraphModelView::Dump( CDumpContext& dc ) const
{
	ZIDropScrollView::Dump( dc );
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphModelView message handlers

BOOL ZIProcessGraphModelView::OnToolTipNeedText( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
	BOOL bHandledNotify	= FALSE;
	TOOLTIPTEXT *pTTT	= (TOOLTIPTEXT *)pNMHDR;
	pTTT->hinst			= NULL;

	CPoint CursorPos;

	VERIFY( ::GetCursorPos( &CursorPos ) );
	ScreenToClient( &CursorPos );

	CRect ClientRect;
	GetClientRect( ClientRect );

	// Make certain that the cursor is in the client rect, because the
	// mainframe also wants these messages to provide tooltips for the
	// toolbar.
	if ( pTTT->uFlags & TTF_IDISHWND && ClientRect.PtInRect( CursorPos ) )
	{
		m_StrToolTip.Empty();

		if ( ZIProcessGraphModelViewport::GetModelController() && 
			 ZIProcessGraphModelViewport::GetModelController()->OnToolTip( m_StrToolTip,
																		   CursorPos,
																		   ( ZAGlobal::GetpType() == zProcess ) ? ZBSymbol::DesignToolTip : ZBSymbol::NormalToolTip ) )
		{
			pTTT->hinst = NULL;
			pTTT->lpszText = m_StrToolTip.GetBuffer( m_StrToolTip.GetLength() + 1 );
			bHandledNotify = TRUE;
			TRACE( (const char*)m_StrToolTip );
		}
	}

	return bHandledNotify;
}

void ZIProcessGraphModelView::OnExportModelToImageFile()
{
	ChooseExportModelToImageFile();
}

void ZIProcessGraphModelView::OnSize( UINT nType, int cx, int cy )
{
	ZIDropScrollView::OnSize( nType, cx, cy );

	if ( GetViewport() && GetViewport()->GetWnd() )
	{
		// Have canvas viewport take up entire container.
		GetViewport()->SetSize( cx, cy );
	}
}

BOOL ZIProcessGraphModelView::OnEraseBkgnd( CDC* pDC )
{
	// Don't erase the background!
	return TRUE;
}

BOOL ZIProcessGraphModelView::PreTranslateMessage ( MSG* pMsg )
{
	// Tooltip 
	if ( ::IsWindow( m_ToolTip.m_hWnd ) && pMsg->hwnd == m_hWnd )
	{
		switch( pMsg->message )
		{
			case WM_LBUTTONDOWN :
			case WM_MOUSEMOVE :
			case WM_LBUTTONUP :
			case WM_RBUTTONDOWN :
			case WM_MBUTTONDOWN :
			case WM_RBUTTONUP :
			case WM_MBUTTONUP :
			{
				m_ToolTip.RelayEvent( pMsg );
				break;
			}
		}
	}

	// Follow
	return FALSE;
}

afx_msg LRESULT ZIProcessGraphModelView::OnRefreshSymbol( WPARAM wParam, LPARAM lParam )
{
	if ( !::IsWindow( GetSafeHwnd() ) )
	{
		return 0;
	}

	ZIObserverMsg* pMsg = (ZIObserverMsg*)lParam;

	if ( pMsg && ISA( pMsg, ZBModelObserverMsg ) && ZIProcessGraphModelViewport::GetModelController() )
	{
		ZBModelObserverMsg* pModelMsg = (ZBModelObserverMsg*)pMsg;

		if ( pModelMsg->GetpElement() )
		{
			ZIProcessGraphModelViewport::GetModelController()->ReDrawComponent( *pModelMsg->GetpElement() );
			return 1;
		}
	}

	return 0;
}

afx_msg LRESULT ZIProcessGraphModelView::OnRefreshSymbolSet( WPARAM wParam, LPARAM lParam )
{
	if ( !::IsWindow( GetSafeHwnd() ) )
	{
		return 0;
	}

	ZIObserverMsg* pMsg = (ZIObserverMsg*)lParam;

	if ( pMsg && ISA( pMsg, ZBModelObserverMsg ) && ZIProcessGraphModelViewport::GetModelController() )
	{
		ZBModelObserverMsg*	pModelMsg = (ZBModelObserverMsg*)pMsg;

		if ( pModelMsg->GetpElementSet() )
		{
			ZIProcessGraphModelViewport::GetModelController()->ReDrawComponentSet( *pModelMsg->GetpElementSet() );
			return 1;
		}
	}

	return 0;
}

afx_msg LRESULT ZIProcessGraphModelView::OnBrowseSymbol( WPARAM wParam, LPARAM lParam )
{
	if ( !::IsWindow( GetSafeHwnd() ) )
	{
		return 0;
	}

	ZIObserverMsg* pMsg = (ZIObserverMsg*)lParam;

	if ( pMsg && ISA( pMsg, ZBModelObserverMsg ) && ZIProcessGraphModelViewport::GetModelController() )
	{
		ZBModelObserverMsg* pModelMsg = (ZBModelObserverMsg*)pMsg;

		if ( pModelMsg->GetpElement() )
		{
			if ( ZIProcessGraphModelViewport::GetModelController()->OpenSymbol( pModelMsg->GetpElement() ) )
			{
				return 1;
			}
		}
	}

	return 0;
}

afx_msg LRESULT ZIProcessGraphModelView::OnOpenModelPage( WPARAM wParam, LPARAM lParam )
{
	if ( !::IsWindow( GetSafeHwnd() ) )
	{
		return 0;
	}

	ZIObserverMsg* pMsg = (ZIObserverMsg*)lParam;

	if ( pMsg && ISA(pMsg,ZBModelObserverMsg ) && ZIProcessGraphModelViewport::GetModelController() )
	{
		ZBModelObserverMsg* pModelMsg = (ZBModelObserverMsg*)pMsg;

		// If a page specified
		if ( pModelMsg->GetpPage() )
		{
			if ( ZIProcessGraphModelViewport::GetModelController()->OpenPage( pModelMsg->GetpPage() ) )
			{
				return 1;
			}
		}
		else if ( pModelMsg->GetpModel() )
		{
			// Browse the model
			if ( ZIProcessGraphModelViewport::GetModelController()->BrowseModel( pModelMsg->GetpModel(),
																				 pModelMsg->GetpModel()->GetParent() ) )
			{
				return 1;
			}
		}
	}

	return 0;
}

afx_msg LRESULT ZIProcessGraphModelView::OnEnsureVisibleSymbol( WPARAM wParam, LPARAM lParam )
{
	if ( !::IsWindow( GetSafeHwnd() ) )
	{
		return 0;
	}

	ZIObserverMsg* pMsg = (ZIObserverMsg*)lParam;

	if ( pMsg && ISA( pMsg, ZBModelObserverMsg ) && ZIProcessGraphModelViewport::GetModelController() )
	{
		ZBModelObserverMsg* pModelMsg = (ZBModelObserverMsg*)pMsg;

		if ( pModelMsg->GetpElement() )
		{
			if ( ZIProcessGraphModelViewport::GetModelController()->EnsureSymbolVisible( pModelMsg->GetpElement() ) )
			{
				// Do selection if necessary
				if ( pModelMsg->GetActionType() == ZBModelObserverMsg::SelectElement )
				{
					ZIProcessGraphModelViewport::GetModelController()->SelectComponent( *pModelMsg->GetpElement() );
				}

				return 1;
			}
		}
	}

	return 0;
}

LRESULT ZIProcessGraphModelView::OnModelDocumentHasChanged( WPARAM wParam, LPARAM lParam )
{
	if ( !ZIProcessGraphModelViewport::GetModelController() )
	{
		return 0;
	}

	ZIProcessGraphModelViewport::GetModelController()->OnModelDocumentHasChanged();

	return 0;
}

LRESULT ZIProcessGraphModelView::OnAdviseStartPropertyEdition( WPARAM wParam, LPARAM lParam )
{
	if ( !ZIProcessGraphModelViewport::GetModelController() )
	{
		return 0;
	}

	ZIProcessGraphModelViewport::GetModelController()->OnAdviseStartPropertyEdition();

	return 0;
}

bool ZIProcessGraphModelView::ChooseExportModelToImageFile()
{
	CString title;

	VERIFY( title.LoadString( IDS_EXPORTFILE_CHOOSETITLE ) );

	CString strRes;
	CString strFilter;

	// append the "*.jpg" files filter
	VERIFY( strRes.LoadString( IDS_EXPORTFILE_FILTERJPEG ) );
	strFilter += strRes;
	strFilter += (char)'\0';		// next string please
	strFilter += _T( "*.jpg" );
	strFilter += (char)'\0';		// last string

	// set the "*.gif" files filter
	VERIFY( strRes.LoadString( IDS_EXPORTFILE_FILTERGIF ) );
	strFilter += strRes;
	strFilter += (char)'\0';		// next string please
	strFilter += _T( "*.gif" );
	strFilter += (char)'\0';		// last string

	// append the "*.pcx" files filter
	VERIFY( strRes.LoadString( IDS_EXPORTFILE_FILTERPCX ) );
	strFilter += strRes;
	strFilter += (char)'\0';		// next string please
	strFilter += _T( "*.pcx" );
	strFilter += (char)'\0';		// last string

	// append the "*.dib" files filter
	VERIFY( strRes.LoadString( IDS_EXPORTFILE_FILTERDIB ) );
	strFilter += strRes;
	strFilter += (char)'\0';		// next string please
	strFilter += _T( "*.dib" );
	strFilter += (char)'\0';		// last string

	// append the "*.tga" files filter
	VERIFY( strRes.LoadString( IDS_EXPORTFILE_FILTERTGA ) );
	strFilter += strRes;
	strFilter += (char)'\0';		// next string please
	strFilter += _T( "*.tga" );
	strFilter += (char)'\0';		// last string

	// append the "*.tif" files filter
	VERIFY( strRes.LoadString( IDS_EXPORTFILE_FILTERTIF ) );
	strFilter += strRes;
	strFilter += (char)'\0';		// next string please
	strFilter += _T( "*.tif" );
	strFilter += (char)'\0';		// last string

	ZIFileDialog FileDialog( title, strFilter, 6, _T( "" ) );

	if ( FileDialog.DoModal() == IDCANCEL )
	{
		return false; 
	}

	CClientDC attribDC( this );

	if ( !ExportModelToImageFile( FileDialog.GetFilename(), attribDC ) )
	{
		// In write mode no chance, file corruption
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_EXPORTFILE_FAIL, MB_OK );

		return false;
	}

	return true;
}
