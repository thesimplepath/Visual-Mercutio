// ZVGridView.cpp : implementation of the ZVGridView class

#include "stdafx.h"

#include "ZDGridDoc.h"
#include "ZVGridView.h"

#include "ZCGridCheckBox.h"
#include "ZCGridGroup.h"

#include "zRes32\zRes.h"
#include "zBaseLib\MsgBox.h"

// FileDlg
#include "zBaseLib\FileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 8 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Static variable
CMenu ZVGridView::m_PopupMenu;

/////////////////////////////////////////////////////////////////////////////
/////////////////// Stingray Software Objective Grid ////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ZVGridView

GXIMPLEMENT_DYNCREATE( ZVGridView, CGXGridView )

BEGIN_MESSAGE_MAP( ZVGridView, CGXGridView )
	//{{AFX_MSG_MAP(ZVGridView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_EXPORTTEXTFILE, OnExportToTextFile)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORTTEXTFILE, OnUpdateExportToTextFile)
	ON_COMMAND(ID_FILE_IMPORTTEXTFILE, OnImportFromTextFile)
	ON_UPDATE_COMMAND_UI(ID_FILE_IMPORTTEXTFILE, OnUpdateImportFromTextFile)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomIn)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMIN, OnUpdateViewZoomIn)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomOut)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMOUT, OnUpdateViewZoomOut)
	ON_COMMAND(ID_FREEZE_SPLITTER, OnFreezeSplitter)
	ON_UPDATE_COMMAND_UI(ID_FREEZE_SPLITTER, OnUpdateFreezeSplitter)
	ON_COMMAND(ID_UNFREEZE_SPLITTER, OnUnfreezeSplitter)
	ON_UPDATE_COMMAND_UI(ID_UNFREEZE_SPLITTER, OnUpdateUnfreezeSplitter)
	ON_COMMAND(ID_GRID_UNHIDEALL, OnUnhideAll)
	ON_UPDATE_COMMAND_UI(ID_GRID_UNHIDEALL, OnUpdateUnhideAll)
	ON_COMMAND(ID_FILE_PRINT, CGXGridView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CGXGridView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGXGridView::OnFilePrintPreview)
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVGridView construction/destruction

ZVGridView::ZVGridView()
{
}

ZVGridView::~ZVGridView()
{
}

BOOL ZVGridView::PreCreateWindow( CREATESTRUCT& cs )
{
	return CGXGridView::PreCreateWindow( cs );
}

int ZVGridView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	EnableIntelliMouse();

#if _MFC_VER >= 0x0400
	// Enable grid to be used as data source
	EnableGridToolTips();
	EnableOleDropTarget();
	EnableOleDataSource();
#endif

	EnableFormulaEngine();

	if ( CGXGridView::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	m_dwDndDropTargetFlags = GX_DNDEGDESCROLL | GX_DNDAUTOSCROLL | GX_DNDTEXT | GX_DNDSTYLES;

	return 0;
}

// Register all controls for the view
void ZVGridView::SetupControls()
{
	// owner drawn checkbox
	RegisterControl( GX_IDS_CTRL_CHECKBOX, new ZCGridCheckBox( this ) );

}

void ZVGridView::InsertGroupCtrl( ROWCOL		Row,
								  ROWCOL		Col,
								  int			CoveringCells,
								  bool			Horizontal,
								  bool			Collapsed,
								  const CString	Label			/*= ""*/,
								  const CString	ToolTipText		/*= ""*/ )
{
	ASSERT ( GetDocument() );

	GetDocument()->InsertGroupCtrl( Row,
									Col,
									CoveringCells,
									Horizontal,
									Collapsed,
									Label,
									ToolTipText );
}

ZCGridGroup* ZVGridView::FindGroupCtrl( ROWCOL Row, ROWCOL Col )
{
	ASSERT ( GetDocument() );
	return GetDocument()->FindGroupCtrl( Row, Col );
}

/////////////////////////////////////////////////////////////////////////////
// ZVGridView drawing

void ZVGridView::OnDraw( CDC* pDC )
{
	ZDGridDocument* pDoc = GetDocument();
	ASSERT_VALID( pDoc );
	CGXGridView::OnDraw( pDC );
}

void ZVGridView::OnInitialUpdate()
{
	// Do we have a grid param
	if ( GetDocument()->GetGridParam() == NULL )
	{

		// Asks for the grid param creation
		if ( !GetDocument()->CreateGridParam() )
		{
			return;
		}

		// Pass the pointer to the grid view
		// FALSE indicates that document is responsible for deleting the object.
		SetParam( GetDocument()->GetGridParam(), FALSE );

		SetRowCount( 60 );	// 60 rows
		SetColCount( 15 );	// 15 columns
	}
	else
	{
		// bFirstView = FALSE indicates that this is 
		// only another view connected to the document
		// No data need to be initialized. They are all 
		// available in the document already.

		// pass the pointer to the grid view
		// FALSE indicates that document is responsible for deleting the object.
		SetParam( GetDocument()->GetGridParam(), FALSE );
	}

	// Custom initialization of styles map
	if ( GetParam()->GetStylesMap() == NULL )
	{
		// Create a stylesmap and connect it with the parameter-object
		CGXStylesMap* pStyMap = new CGXStylesMap;
		
		GetParam()->SetStylesMap( pStyMap );

		// Add standard styles
		pStyMap->CreateStandardStyles();

		SetupUserAttributes();

		// If you want to specify a specific profile section
		// for load and storing the base styles in the registry,
		// simply uncomment the next line
		// pStyMap->SetSection( _T( "My Base Styles" ) );	// Extra profile section

		pStyMap->ReadProfile();
	}

	// Custom initialization of property object
	if ( GetParam()->GetProperties() == NULL )
	{
		// create a stylesmap and connect it with the parameter-object
		CGXProperties* pProperties = new CGXProperties;

		pProperties->AddDefaultUserProperties();

		// Sets the standard properties
		pProperties->SetDisplayHorzLines( TRUE );
		pProperties->SetDisplayVertLines( TRUE );
		pProperties->SetPrintHorzLines( FALSE );
		pProperties->SetPrintVertLines( FALSE );
		
		pProperties->SetPrintColHeaders( FALSE );
		pProperties->SetPrintRowHeaders( FALSE );
		// END OF SAMPLE CODE

		// If you want to specify a specific profile section
		// for load and storing the properties in the registry,
		// simply uncomment the next line
		// pProperties->SetSection( _T( "My Properties" ) );	// Extra profile section

		pProperties->ReadProfile();

		GetParam()->SetProperties( pProperties );
	}

	// Custom initialization of printer settings
	if ( GetParam()->GetPrintDevice() == NULL )
	{
		// Initialize printer object if you want to have
		// some default settings for the grid printing, e.g. Print Landscape
	}

	CGXGridView::OnInitialUpdate();

	// Register all controls for the view
	SetupControls();

	EnableHints( FALSE );

	// Lock any drawing
	BOOL bOld = LockUpdate();

	// Initialize the grid data
	// Disable undo mechanism for the following commands
	GetParam()->EnableUndo( FALSE );

	// Floating cells mode
	// The other possible mode for floatcells is gxnFloatEvalOnDisplay 
	SetFloatCellsMode( gxnFloatDelayEval );

	// Reenable undo mechanism
	GetParam()->EnableUndo( TRUE );

	// Unlock drawing
	LockUpdate( bOld );

	// Register all controls for the grid

	// Just to be sure that everything is redrawn
	Invalidate();

	// Enable Objective Grid internal update-hint mechanism

	// You should put this line as last command into OnInitialUpdate,
	// becaus as long as EnableHints is not called, the modified flag
	// of the document will not be changed.
	EnableHints();
}

void ZVGridView::SetupUserAttributes()
{
	CGXStylesMap* stylesmap = GetParam()->GetStylesMap();

	// Register user attributes for the CGXStyleSheet-User Attributes page.
	// (control objects will be created on demand in CGXControlFactory).
	stylesmap->RegisterDefaultUserAttributes();
}

void ZVGridView::SetPopupMenu( UINT nIDRes )
{
	// If already allocated, destroy it first
	if ( m_PopupMenu.GetSafeHmenu() != NULL )
	{
		m_PopupMenu.DestroyMenu();
	}

	m_PopupMenu.LoadMenu( nIDRes );
}

BOOL ZVGridView::OnRButtonClickedRowCol( ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt )
{
	CMenu* pPopup = ( m_PopupMenu.GetSafeHmenu() != NULL ) ? m_PopupMenu.GetSubMenu( 0 ) : NULL;

	// We cannot proceed with the right button click
	if ( pPopup == NULL )
	{
		return FALSE;
	}

	CWnd* pWndPopupOwner = AfxGetMainWnd();

	// Display the menu
	ClientToScreen( &pt );
	pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, pWndPopupOwner );

	// We processed the message
	return TRUE;
}

void ZVGridView::ExportToTextFile()
{
	CString title;

	VERIFY( title.LoadString( IDS_EXPORTFILE_CHOOSETITLE ) );

	// Set the "*.txt" files filter
	CString strFilter;
	VERIFY( strFilter.LoadString( IDS_EXPORTFILE_FILTER ) );
	strFilter += (char)'\0';		// next string please
	strFilter += _T( "*.txt" );
	strFilter += (char)'\0';		// last string

	// append the "*.*" all files filter
	CString allFilter;
	VERIFY( allFilter.LoadString( AFX_IDS_ALLFILTER ) );
	strFilter += allFilter;
	strFilter += (char)'\0';		// next string please
	strFilter += _T( "*.*" );
	strFilter += (char)'\0';		// last string

	ZIFileDialog FileDialog( title, strFilter, 2, _T( "" ) );

	if ( FileDialog.DoModal() == IDCANCEL )
	{
		return;
	}

	if ( !ExportToTextFile( FileDialog.GetFilename() ) )
	{
		// In write mode no chance, file corruption
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_EXPORTFILE_FAIL );
		return;
	}
}

bool ZVGridView::ExportToTextFile( const CString Filename )
{
	CFile textFile;

	if ( !textFile.Open( Filename, CFile::modeCreate | CFile::modeWrite ) )
	{
		return false;
	}

	CopyTextToFile( textFile, CGXRange( 0, 1, GetRowCount(), GetColCount() ) );

	textFile.Close();

	return true;
}

void ZVGridView::ImportTextFile()
{ 
	CString title;
	VERIFY( title.LoadString( IDS_IMPORTFILE_CHOOSETITLE ) );

	// Set the "*.txt" files filter
	CString strFilter;
	VERIFY( strFilter.LoadString( IDS_EXPORTFILE_FILTER ) );
	strFilter += (char)'\0';		// Next string please
	strFilter += _T( "*.txt" );
	strFilter += (char)'\0';		// Last string

	// Append the "*.*" all files filter
	CString allFilter;
	VERIFY( allFilter.LoadString( AFX_IDS_ALLFILTER ) );
	strFilter += allFilter;
	strFilter += (char)'\0';		// Next string please
	strFilter += _T( "*.*" );
	strFilter += (char)'\0';		// Last string

	ZIFileDialog FileDialog( title, strFilter, 2, _T( "" ) );

	if ( FileDialog.DoModal() == IDCANCEL )
	{
		return;
	}

	if ( !ImportTextFile( FileDialog.GetFilename() ) )
	{
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_IMPORTFILE_FAIL );
		return;
	}
}

bool ZVGridView::ImportTextFile( const CString Filename )
{
	CFile textFile;

	if ( !textFile.Open( Filename, CFile::modeRead ) )
	{
		return false;
	}

	LPTSTR pszBuffer;
	DWORD dwSize = (DWORD)textFile.GetLength();
	pszBuffer = new TCHAR[dwSize];

	textFile.Read( pszBuffer, dwSize );

	PasteTextFromBuffer( pszBuffer, dwSize, CGXRange( 0, 1 ) );

	textFile.Close();

	delete pszBuffer;
	return true;
}

void ZVGridView::FreezeSplitter()
{
	ZDGridDocument* pDoc = GetDocument();

	if ( pDoc							&&
		 ( pDoc->GetFrozenRow() != 0	||
		 pDoc->GetFrozenHeaderRow() != 0 ) )
	{
		SetFrozenRows( pDoc->GetFrozenRow(), pDoc->GetFrozenHeaderRow() );
	}

	if ( pDoc							&&
		 ( pDoc->GetFrozenCol() != 0	||
		 pDoc->GetFrozenHeaderCol() != 0 ) )
	{
		SetFrozenCols( pDoc->GetFrozenCol(), pDoc->GetFrozenHeaderCol() );
	}
}

void ZVGridView::UnfreezeSplitter()
{
	SetFrozenRows( 0, 0 );
	SetFrozenCols( 0, 0 );
}

void ZVGridView::UnhideAll()
{
	HideRows( 0, GetRowCount(), FALSE );
	HideCols( 0, GetColCount(), FALSE );
}

/////////////////////////////////////////////////////////////////////////////
// ZVGridView printing

BOOL ZVGridView::OnPreparePrinting( CPrintInfo* pInfo )
{
	// default preparation
	return DoPreparePrinting( pInfo );
}

void ZVGridView::OnBeginPrinting( CDC* pDC, CPrintInfo* pInfo )
{
	CGXGridView::OnBeginPrinting( pDC, pInfo );
	// TODO: add extra initialization before printing
}

void ZVGridView::OnEndPrinting( CDC* pDC, CPrintInfo* pInfo )
{
	CGXGridView::OnEndPrinting( pDC, pInfo );

	// TODO: add cleanup after printing
}

void ZVGridView::OnPrint( CDC* pDC, CPrintInfo* pInfo )
{
	// add customized printing code here

	// Print the canvas
	CGXGridView::OnPrint( pDC, pInfo );
}

/////////////////////////////////////////////////////////////////////////////
// ZVGridView message handlers

void ZVGridView::OnViewZoomIn()
{
	if ( GetZoom() < 300 )
	{
		SetZoom( GetZoom() * 11 / 10 );
	}
}

void ZVGridView::OnViewZoomOut()
{
	if ( GetZoom() > 40 )
	{
		SetZoom( GetZoom() * 10 / 11 );
	}
}

void ZVGridView::OnUpdateViewZoomIn( CCmdUI* pCmdUI )
{
	pCmdUI->Enable( GetParam() && GetZoom() < 300 );
}

void ZVGridView::OnUpdateViewZoomOut( CCmdUI* pCmdUI )
{
	pCmdUI->Enable( GetParam() && GetZoom() > 40 );
}

void ZVGridView::OnClickedButtonRowCol( ROWCOL nRow, ROWCOL nCol )
{
	ZCGridGroup* pCtrl = FindGroupCtrl( nRow, nCol );

	// Toggle the group control
	if ( pCtrl )
	{
		pCtrl->SetCollapsed( !pCtrl->GetCollapsed() );
	}
}

void ZVGridView::OnExportToTextFile()
{
	ZVGridView::ExportToTextFile();
}

void ZVGridView::OnUpdateExportToTextFile( CCmdUI* pCmdUI )
{
}

void ZVGridView::OnImportFromTextFile()
{
	ZVGridView::ImportTextFile();
}

void ZVGridView::OnUpdateImportFromTextFile( CCmdUI* pCmdUI )
{
}

void ZVGridView::OnFreezeSplitter()
{
	FreezeSplitter();
}

void ZVGridView::OnUpdateFreezeSplitter( CCmdUI* pCmdUI )
{
	ROWCOL FrozenRow		= GetFrozenRows();
	ROWCOL FrozenCol		= GetFrozenCols();
	ROWCOL FrozenHeaderRow	= GetHeaderRows();
	ROWCOL FrozenHeaderCol	= GetHeaderCols();

	ZDGridDocument* pDoc = GetDocument();

	if ( pDoc )
	{
		pCmdUI->Enable( FrozenRow == 0					&&
						FrozenCol == 0					&&
						FrozenHeaderRow == 0			&&
						FrozenHeaderCol == 0			&&
						( pDoc->GetFrozenRow() != 0		||
						pDoc->GetFrozenCol() != 0		||
						pDoc->GetFrozenHeaderRow() != 0	||
						pDoc->GetFrozenHeaderCol() != 0 ) );
	}
	else
	{
		pCmdUI->Enable( FALSE );
	}
}

void ZVGridView::OnUnfreezeSplitter()
{
	UnfreezeSplitter();
}

void ZVGridView::OnUpdateUnfreezeSplitter( CCmdUI* pCmdUI )
{
	ROWCOL FrozenRow		= GetFrozenRows();
	ROWCOL FrozenCol		= GetFrozenCols();
	ROWCOL FrozenHeaderRow	= GetHeaderRows();
	ROWCOL FrozenHeaderCol	= GetHeaderCols();

	ZDGridDocument* pDoc = GetDocument();

	if ( pDoc )
	{
		pCmdUI->Enable( FrozenRow != 0			||
						FrozenCol != 0			||
						FrozenHeaderRow != 0	||
						FrozenHeaderCol != 0 );
	}
	else
	{
		pCmdUI->Enable( FALSE );
	}
}

void ZVGridView::OnUnhideAll()
{
	UnhideAll();
}

void ZVGridView::OnUpdateUnhideAll( CCmdUI* pCmdUI )
{
	pCmdUI->Enable( TRUE );
}

/////////////////////////////////////////////////////////////////////////////
// ZVGridView diagnostics

#ifdef _DEBUG
void ZVGridView::AssertValid() const
{
	CGXGridView::AssertValid();
}

void ZVGridView::Dump( CDumpContext& dc ) const
{
	CGXGridView::Dump( dc );
}

// Non-debug version is inline
ZDGridDocument* ZVGridView::GetDocument()
{
	ASSERT( m_pDocument->IsKindOf( RUNTIME_CLASS( ZDGridDocument ) ) );
	return (ZDGridDocument*)m_pDocument;
}

// Non-debug version is inline
ZDGridDocument* ZVGridView::GetMasterDocument()
{
	if ( m_pDocument && ISA( dynamic_cast<ZDGridDocument*>( m_pDocument )->GetPrimaryDocument(), ZDGridDocument ) )
	{
		return dynamic_cast<ZDGridDocument*>( dynamic_cast<ZDGridDocument*>( m_pDocument )->GetPrimaryDocument() );
	}

	return NULL;
}
#else
// Non-debug version is inline
ZDGridDocument* ZVGridView::GetMasterDocument()
{
	return ( GetDocument() ) ? (ZDGridDocument*)( GetDocument()->GetPrimaryDocument() ) : NULL;
}
#endif
