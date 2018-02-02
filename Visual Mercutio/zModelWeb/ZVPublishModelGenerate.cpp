// ZVPublishModelGenerate.cpp : implementation file

#include "stdafx.h"
#include "ZVPublishModelGenerate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 1er mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelGenerate dialog

BEGIN_MESSAGE_MAP( ZVPublishModelGenerate, ZIWizardDialog )
	//{{AFX_MSG_MAP(ZVPublishModelGenerate)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVPublishModelGenerate::ZVPublishModelGenerate()
	: m_RequestCancel( false )
{
	//{{AFX_DATA_INIT(ZVPublishModelGenerate)
	m_Destination = _T("");
	//}}AFX_DATA_INIT
}

bool ZVPublishModelGenerate::Create( CWnd* pParent /*= NULL*/ )
{
	BOOL myResult = ZIWizardDialog::Create( ZVPublishModelGenerate::IDD,
											IDB_WZBMP1,
											0,
											0,							// Title Window
											IDS_PUBLISHMODELGENERATE_S,	// Title Wizard
											IDS_PUBLISHMODELGENERATE_T,	// Text Wizard
											TRUE,						// Auto center
											FALSE,						// Stand Alone
											pParent );

	if ( myResult == TRUE )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ZVPublishModelGenerate::DoDataExchange( CDataExchange* pDX )
{
	ZIWizardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZVPublishModelGenerate)
	DDX_Control(pDX, IDC_AVIFILEMOVE, m_FileMoveAnimation);
	DDX_Text(pDX, IDC_FILEDESTINATION, m_Destination);
	//}}AFX_DATA_MAP
}

void ZVPublishModelGenerate::SetDestination( const CString Destination )
{
	m_Destination = Destination;
	UpdateData( FALSE );
	MSG msg;

	if ( PeekMessage( &msg, NULL, NULL, NULL, PM_NOREMOVE ) )
	{
		GetMessage( &msg, NULL, NULL, NULL );
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
}

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelGenerate message handlers

BOOL ZVPublishModelGenerate::OnInitDialog()
{
	ZIWizardDialog::OnInitDialog();

	m_FileMoveAnimation.Open( IDR_FILEMOVE );
	m_FileMoveAnimation.ShowWindow( SW_SHOW );
	m_FileMoveAnimation.Play( 0, -1, -1 );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void ZVPublishModelGenerate::OnCancel()
{
	m_RequestCancel = true;
}

// JMR-MODIF - Le 1er mars 2006 - Ajout de la fonction surchargée OnCtlColor.
HBRUSH ZVPublishModelGenerate::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
	// Mets à jour la couleur de fond de l'objet animé.
	if ( pWnd->GetDlgCtrlID() == IDC_AVIFILEMOVE )
	{
		pDC->SetBkColor( RGB( 192, 192, 192 ) );
		return (HBRUSH)GetStockObject( NULL_BRUSH );
	}

	return ZIWizardDialog::OnCtlColor( pDC, pWnd, nCtlColor );
}
