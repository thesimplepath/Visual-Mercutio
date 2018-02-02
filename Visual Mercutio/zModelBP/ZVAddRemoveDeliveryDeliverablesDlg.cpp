// **************************************************************************************************************
// *							   Classe ZVAddRemoveDeliveryDeliverablesDlg									*
// **************************************************************************************************************
// * JMR-MODIF - Le 13 février 2006 - Ajout de la classe ZVAddRemoveDeliveryDeliverablesDlg.					*
// **************************************************************************************************************
// * Cette classe représente la boîte de dialogue permettant de contrôler la gestion des livrables dans les		*
// * livraisons.																								*
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVAddRemoveDeliveryDeliverablesDlg.h"

#include "zBaseLib\ZBTokenizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVAddRemoveDeliveryDeliverablesDlg dialog

BEGIN_MESSAGE_MAP( ZVAddRemoveDeliveryDeliverablesDlg, CDialog )
	//{{AFX_MSG_MAP(ZVAddRemoveDeliveryDeliverablesDlg)
	ON_BN_CLICKED(IDC_ADD_DELIV, OnAddDeliv)
	ON_BN_CLICKED(IDC_DEL_DELIV, OnDelDeliv)
	ON_LBN_SELCHANGE(IDC_SELECTED_DELIV, OnSelchangeSelectedDeliv)
	ON_LBN_SELCHANGE(IDC_AVAILABLE_DELIV, OnSelchangeAvailableDeliv)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Constructeur par défaut de la classe ZVAddRemoveDeliveryDeliverablesDlg.
ZVAddRemoveDeliveryDeliverablesDlg::ZVAddRemoveDeliveryDeliverablesDlg( const CString	AvailableDeliverables	/*= _T( "" )*/,
																		const CString	SelectedDeliverables	/*= _T( "" )*/,
																		CWnd*			pParent					/*=NULL*/ )
	: CDialog					( ZVAddRemoveDeliveryDeliverablesDlg::IDD, pParent ),
	  m_AvailableDeliverables	( AvailableDeliverables ),
	  m_SelectedDeliverables	( SelectedDeliverables )
{
	//{{AFX_DATA_INIT(ZVAddRemoveDeliveryDeliverablesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

// Destructeur de la classe ZVAddRemoveDeliveryDeliverablesDlg.
ZVAddRemoveDeliveryDeliverablesDlg::~ZVAddRemoveDeliveryDeliverablesDlg()
{
}

// Fonction d'échange des données.
void ZVAddRemoveDeliveryDeliverablesDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP(ZVAddRemoveDeliveryDeliverablesDlg)
	DDX_Control(pDX, IDC_SELECTED_DELIV, m_SelectedDeliverablesLB);
	DDX_Control(pDX, IDC_AVAILABLE_DELIV, m_AvailableDeliverablesLB);
	//}}AFX_DATA_MAP
}

// Envoie une chaîne de caractères dans la liste donnée.
void ZVAddRemoveDeliveryDeliverablesDlg::StringToListBox( const CString Deliv, CListBox& LB )
{
	// Initialize the token with ; as separator
	ZBTokenizer token;

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

// Obtient une chaîne de caractères depuis la liste donnée.
void ZVAddRemoveDeliveryDeliverablesDlg::ListBoxToString( CListBox& LB, CString& Deliv )
{
	// Initialize the token with ; as separator
	ZBTokenizer token;
	CString str;

	// Run through the list box elements and build the string
	int Count = LB.GetCount();

	for ( int i = 0; i < Count; ++i )
	{
		LB.GetText( i, str );
		token.AddToken( str );
	}

	// Assign the return string
	Deliv = token.GetString();
}

// Ajoute une chaîne de caractères à la liste donnée.
void ZVAddRemoveDeliveryDeliverablesDlg::AddStringToListBox( const CString str, CListBox& LB )
{
	LB.AddString( str );
}

// Supprime une chaîne de caractères dans la liste donnée.
void ZVAddRemoveDeliveryDeliverablesDlg::RemoveStringToListBox( const CString str, CListBox& LB )
{
	int Index = LB.FindString( 0, str );

	if ( Index != LB_ERR )
	{
		LB.DeleteString( Index );
	}
}

// Mets à jour l'état des boutons, en fonction des sélections.
void ZVAddRemoveDeliveryDeliverablesDlg::CheckState()
{
	int CurSel = m_AvailableDeliverablesLB.GetCurSel();

	if ( GetDlgItem( IDC_ADD_DELIV ) )
	{
		GetDlgItem( IDC_ADD_DELIV )->EnableWindow( CurSel != LB_ERR );
	}

	CurSel = m_SelectedDeliverablesLB.GetCurSel();

	if ( GetDlgItem( IDC_DEL_DELIV ) )
	{
		GetDlgItem( IDC_DEL_DELIV )->EnableWindow( CurSel != LB_ERR );
	}
}

// Cette fonction teste si une entrée donnée existe déjà dans la liste de destination.
BOOL ZVAddRemoveDeliveryDeliverablesDlg::IsEntryAlreadyExist( CString EntryValue )
{
	for ( int i = 0; i < m_SelectedDeliverablesLB.GetCount(); i++ )
	{
		CString m_CompStr;
		m_SelectedDeliverablesLB.GetText( i, m_CompStr );

		if ( m_CompStr == EntryValue )
		{
			return TRUE;
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ZVAddRemoveDeliveryDeliverablesDlg message handlers

// Cette fonction est appelée lorsque la boîte de dialogue s'initialise.
BOOL ZVAddRemoveDeliveryDeliverablesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	StringToListBox( m_AvailableDeliverables, m_AvailableDeliverablesLB );
	StringToListBox( m_SelectedDeliverables, m_SelectedDeliverablesLB );

	// Sets the maximum horizontal scroll
	m_SelectedDeliverablesLB.SetHorizontalExtent( 1000 );
	m_AvailableDeliverablesLB.SetHorizontalExtent( 1000 );

	CheckState();

	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Ajouter".
void ZVAddRemoveDeliveryDeliverablesDlg::OnAddDeliv()
{
	int CurSel = m_AvailableDeliverablesLB.GetCurSel();

	if ( CurSel != LB_ERR )
	{
		CString str;
		m_AvailableDeliverablesLB.GetText( CurSel, str );

		if ( IsEntryAlreadyExist( str ) == FALSE )
		{
			AddStringToListBox( str, m_SelectedDeliverablesLB );
		}
	}

	CheckState();
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Supprimer".
void ZVAddRemoveDeliveryDeliverablesDlg::OnDelDeliv()
{
	int CurSel = m_SelectedDeliverablesLB.GetCurSel();

	if ( CurSel != LB_ERR )
	{
		CString str;
		m_SelectedDeliverablesLB.GetText( CurSel, str );
		RemoveStringToListBox( str, m_SelectedDeliverablesLB );
	}

	CheckState();
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Valider".
void ZVAddRemoveDeliveryDeliverablesDlg::OnOK()
{
	ListBoxToString( m_SelectedDeliverablesLB, m_SelectedDeliverables );

	CDialog::OnOK();
}

// Cette fonction est appelée lorsque la sélection de la liste "Livrables de la livraison" change.
void ZVAddRemoveDeliveryDeliverablesDlg::OnSelchangeSelectedDeliv()
{
	CheckState();
}

// Cette fonction est appelée lorsque la sélection de la liste "Livrables disponibles" change.
void ZVAddRemoveDeliveryDeliverablesDlg::OnSelchangeAvailableDeliv()
{
	CheckState();
}
