// ******************************************************************************************************************
// *										Classe ZVRulesInfoDlg													*
// ******************************************************************************************************************
// * JMR-MODIF - Le 15 novembre 2006 - Ajout de la classe ZVRulesInfoDlg.											*
// ******************************************************************************************************************
// * Cette classe représente une boîte de dialogue personnalisée pour les messages en provenance du gestionnaire de	*
// * données des règles.																							*
// ******************************************************************************************************************

#include "stdafx.h"
#include "ZVRulesInfoDlg.h"

#include "ZBLogicalRulesEntity.h"

#include "zBaseLib\MsgBox.h"

#include "zBaseLib\zBaseLibRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVRulesInfoDlg dialog

BEGIN_MESSAGE_MAP( ZVRulesInfoDlg, CDialog )
	//{{AFX_MSG_MAP(ZVRulesInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVRulesInfoDlg::ZVRulesInfoDlg( UINT					nTitleID		/*= -1*/,
								ZBLogicalRulesEntity*	pLogicalRule	/*= NULL*/,
								const CString			Name			/*= _T( "" )*/,
								const CString			Description		/*= _T( "" )*/,
								bool					ModifyMode		/*= false*/,
								CWnd*					pParent			/*=NULL*/ )
	: CDialog		( ZVRulesInfoDlg::IDD, pParent ),
	  m_pRule		( pLogicalRule ),
	  m_ModifyMode	( ModifyMode )
{
	//{{AFX_DATA_INIT(ZVRulesInfoDlg)
	m_Description = Description;
	m_Name = Name;
	//}}AFX_DATA_INIT

	// Assigns also the initial cost
	if ( nTitleID != -1 )
	{
		m_Title.LoadString( nTitleID );
	}
}

ZVRulesInfoDlg::~ZVRulesInfoDlg()
{
}

void ZVRulesInfoDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );

	//{{AFX_DATA_MAP(ZVRulesInfoDlg)
	DDX_Text(pDX, IDC_RULE_DESCRIPTION, m_Description);
	DDX_Text(pDX, IDC_RULE_NAME, m_Name);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVRulesInfoDlg message handlers

void ZVRulesInfoDlg::OnOK()
{
	UpdateData( TRUE );

	if ( !m_ModifyMode )
	{
		if ( m_pRule && m_pRule->RuleExist( m_Name ) )
		{
			// Already exists
			MsgBox mbox;
			mbox.DisplayMsgBox( IDS_RULE_ALREADYEXIST, MB_OK );
			return;
		}
	}

	CDialog::OnOK();
}

BOOL ZVRulesInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	if ( !m_Title.IsEmpty() )
	{
		SetWindowText( m_Title );
	}

	if ( m_ModifyMode )
	{
		if ( GetDlgItem( IDC_RULE_NAME ) )
		{
			GetDlgItem( IDC_RULE_NAME )->EnableWindow( FALSE );
		}
	}

	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}
