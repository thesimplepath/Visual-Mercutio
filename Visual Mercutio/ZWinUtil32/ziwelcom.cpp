// ZIWelcomeDialog.cpp : implementation file

#include "stdafx.h"
#include "ZIWelcom.h"
#include "zBaseLib\Draw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 17 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIWelcomeDialog dialog

BEGIN_MESSAGE_MAP( ZIWelcomeDialog, CDialog )
	//{{AFX_MSG_MAP(ZIWelcomeDialog)
	ON_BN_CLICKED(ID_WELCOME_LASTFILE, OnWelcomeLastFile)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZIWelcomeDialog::ZIWelcomeDialog( UINT					nID,
								  UINT					nIDBitmap,
								  ZAApplicationOption*	pApplicationOptions,
								  BOOL					EnableMoveToGeneral,
								  CWnd*					pParent /*=NULL*/ )
	: ZIDialog				( nID, TRUE, pParent ),
	  m_nIDBitmap			( nIDBitmap ),
	  m_pApplicationOptions	( pApplicationOptions ), 
	  m_EnableMoveToGeneral	( EnableMoveToGeneral )
{
	//{{AFX_DATA_INIT(ZIWelcomeDialog)
	//}}AFX_DATA_INIT

	m_DoNotStart = !m_pApplicationOptions->GetShowWelcomeScreen();
}

void ZIWelcomeDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP(ZIWelcomeDialog)
	DDX_Control(pDX, ID_WELCOME_LASTFILE, m_LastFile);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDC_HYPERLINK_HTTP, m_HyperLink);
	DDX_Check(pDX, IDC_DONOTSTART, m_DoNotStart);
	//}}AFX_DATA_MAP
}

void ZIWelcomeDialog::SaveState()
{
	UpdateData();

	// Save the flag
	m_pApplicationOptions->SetShowWelcomeScreen( !m_DoNotStart );
}

/////////////////////////////////////////////////////////////////////////////
// ZIWelcomeDialog message handlers

void ZIWelcomeDialog::OnCancel()
{
	SaveState();
	CDialog::OnCancel();
}

void ZIWelcomeDialog::OnWelcomeLastFile()
{
	SaveState();
	EndDialog( ID_WELCOME_LASTFILE );
}

void ZIWelcomeDialog::OnPaint()
{
	CPaintDC dc( this ); // device context for painting

	HINSTANCE hInst = AfxFindResourceHandle( MAKEINTRESOURCE( m_nIDBitmap ), RT_BITMAP );

	DisplayBitmapFile ( MAKEINTRESOURCE( m_nIDBitmap ),
						dc.m_hDC,
						hInst,
						3,
						3 );
}

BOOL ZIWelcomeDialog::OnInitDialog()
{
	ZIDialog::OnInitDialog();

	m_HyperLink.SetURL( _T( "http://www.processsoft.com" ) );
	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

// JMR-MODIF - Le 20 octobre 2005 - Ajout de la fonction OnCtlColor.
HBRUSH ZIWelcomeDialog::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
	HBRUSH hbr = ZIDialog::OnCtlColor( pDC, pWnd, nCtlColor );

	return hbr;
}
