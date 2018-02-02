// ZVChooseMasterDeliverable.cpp : implementation file

#include "stdafx.h"
#include "ZVChooseMasterDeliverable.h"

#include "zBaseLib\ZBTokenizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 14 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVChooseMasterDeliverable dialog

BEGIN_MESSAGE_MAP( ZVChooseMasterDeliverable, CDialog )
	//{{AFX_MSG_MAP(ZVChooseMasterDeliverable)
	ON_LBN_SELCHANGE(IDC_LISTOFDELIVERABLE, OnSelchangeListOfDeliverable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVChooseMasterDeliverable::ZVChooseMasterDeliverable( const CString	Deliverables,
													  const CString	Master			/*= ""*/,
													  CWnd*			pParent			/*=NULL*/ )
	: CDialog			( ZVChooseMasterDeliverable::IDD, pParent ),
	  m_Deliverables	( Deliverables ),
	  m_Master			( Master )
{
	//{{AFX_DATA_INIT(ZVChooseMasterDeliverable)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void ZVChooseMasterDeliverable::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP(ZVChooseMasterDeliverable)
	DDX_Control(pDX, IDC_LISTOFDELIVERABLE, m_ListOfDeliverables);
	//}}AFX_DATA_MAP
}

void ZVChooseMasterDeliverable::StringToListBox( const CString Deliv, CListBox& LB )
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

void ZVChooseMasterDeliverable::CheckState()
{
	int CurSel = m_ListOfDeliverables.GetCurSel();

	if ( GetDlgItem( IDOK ) )
	{
		GetDlgItem( IDOK )->EnableWindow( CurSel != LB_ERR );
	}
}

/////////////////////////////////////////////////////////////////////////////
// ZVChooseMasterDeliverable message handlers

BOOL ZVChooseMasterDeliverable::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	StringToListBox( m_Deliverables, m_ListOfDeliverables );

	// Sets the maximum horizontal scroll
	m_ListOfDeliverables.SetHorizontalExtent( 1000 );

	CheckState();
	
	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}

void ZVChooseMasterDeliverable::OnOK()
{
	int CurSel = m_ListOfDeliverables.GetCurSel();

	if ( CurSel != LB_ERR )
	{
		m_ListOfDeliverables.GetText( CurSel, m_Master );
	}

	CDialog::OnOK();
}

void ZVChooseMasterDeliverable::OnSelchangeListOfDeliverable()
{
	CheckState();
}
