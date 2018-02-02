// **************************************************************************************************************
// *									Classe ZVChooseMainDeliverable											*
// **************************************************************************************************************
// * JMR-MODIF - Le 14 février 2006 - Ajout de la classe ZVChooseMainDeliverable.								*
// **************************************************************************************************************
// * Cette classe représente la boîte de dialogue permettant la sélection d'un nouveau livrable principal.		*
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVChooseMainDeliverable.h"

#include "zBaseLib\ZBTokenizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVChooseMainDeliverable dialog

BEGIN_MESSAGE_MAP( ZVChooseMainDeliverable, CDialog )
	//{{AFX_MSG_MAP(ZVChooseMainDeliverable)
	ON_LBN_SELCHANGE(IDC_LISTOFDELIVERABLE, OnSelchangeListOfDeliverable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVChooseMainDeliverable::ZVChooseMainDeliverable( const CString	Deliverables,
												  const CString	Main			/*= ""*/,
												  CWnd*			pParent			/*=NULL*/ )
	: CDialog			( ZVChooseMainDeliverable::IDD, pParent ),
	  m_Deliverables	( Deliverables ),
	  m_Main			( Main )
{
	//{{AFX_DATA_INIT(ZVChooseMainDeliverable)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

ZVChooseMainDeliverable::~ZVChooseMainDeliverable()
{
}

void ZVChooseMainDeliverable::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP(ZVChooseMainDeliverable)
	DDX_Control(pDX, IDC_LISTOFDELIVERABLE, m_ListOfDeliverables);
	//}}AFX_DATA_MAP
}

void ZVChooseMainDeliverable::StringToListBox( const CString Deliv, CListBox& LB )
{
	ZBTokenizer token;	// Initialize the token with ; as separator

	CString str = token.GetFirstToken( Deliv );

	// Run through all tokens
	while ( !str.IsEmpty() )
	{
		// Add the string to the list
		LB.AddString( str );

		// Get the next token
		str = token.GetNextToken();
	}
}

void ZVChooseMainDeliverable::CheckState()
{
	int CurSel = m_ListOfDeliverables.GetCurSel();

	if ( GetDlgItem( IDOK ) )
	{
		GetDlgItem( IDOK )->EnableWindow( CurSel != LB_ERR );
	}
}

/////////////////////////////////////////////////////////////////////////////
// ZVChooseMainDeliverable message handlers

BOOL ZVChooseMainDeliverable::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	StringToListBox( m_Deliverables, m_ListOfDeliverables );

	// Sets the maximum horizontal scroll
	m_ListOfDeliverables.SetHorizontalExtent( 1000 );

	CheckState();
	
	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}

void ZVChooseMainDeliverable::OnOK()
{
	int CurSel = m_ListOfDeliverables.GetCurSel();

	if ( CurSel != LB_ERR )
	{
		m_ListOfDeliverables.GetText( CurSel, m_Main );
	}

	CDialog::OnOK();
}

void ZVChooseMainDeliverable::OnSelchangeListOfDeliverable()
{
	CheckState();
}
