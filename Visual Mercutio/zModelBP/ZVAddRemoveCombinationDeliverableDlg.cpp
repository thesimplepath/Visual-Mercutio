// **************************************************************************************************************
// *                               Classe ZVAddRemoveCombinationDeliverableDlg                                    *
// **************************************************************************************************************
// * Cette classe représente la boîte de dialogue permettant de contrôler la gestion des livrables dans les        *
// * combinaisons.                                                                                                *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVAddRemoveCombinationDeliverableDlg.h"

#include "zBaseLib\PSS_Tokenizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 13 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVAddRemoveCombinationDeliverableDlg dialog

BEGIN_MESSAGE_MAP( ZVAddRemoveCombinationDeliverableDlg, CDialog )
    //{{AFX_MSG_MAP(ZVAddRemoveCombinationDeliverableDlg)
    ON_BN_CLICKED(IDC_ADD_DELIV, OnAddDeliv)
    ON_BN_CLICKED(IDC_DEL_DELIV, OnDelDeliv)
    ON_LBN_SELCHANGE(IDC_COMB_DELIV, OnSelchangeCombDeliv)
    ON_LBN_SELCHANGE(IDC_REMAIN_DELIV, OnSelchangeRemainDeliv)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVAddRemoveCombinationDeliverableDlg::ZVAddRemoveCombinationDeliverableDlg( const CString    RemainingDeliverables    /*= _T( "" )*/,
                                                                            const CString    Deliverables            /*= _T( "" )*/,
                                                                            CWnd*            pParent                    /*=NULL*/ )
    : CDialog                    ( ZVAddRemoveCombinationDeliverableDlg::IDD, pParent ),
      m_RemainingDeliverables    ( RemainingDeliverables ),
      m_Deliverables            ( Deliverables )
{
    //{{AFX_DATA_INIT(ZVAddRemoveCombinationDeliverableDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

void ZVAddRemoveCombinationDeliverableDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVAddRemoveCombinationDeliverableDlg)
    DDX_Control(pDX, IDC_COMB_DELIV, m_CombinationDeliverablesLB);
    DDX_Control(pDX, IDC_REMAIN_DELIV, m_RemainingDeliverablesLB);
    //}}AFX_DATA_MAP
}

void ZVAddRemoveCombinationDeliverableDlg::StringToListBox( const CString Deliv, CListBox& LB )
{
    // Initialize the token with ; as separator
    PSS_Tokenizer token;

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

void ZVAddRemoveCombinationDeliverableDlg::ListBoxToString( CListBox& LB, CString& Deliv )
{
    // Initialize the token with ; as separator
    PSS_Tokenizer token;
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

void ZVAddRemoveCombinationDeliverableDlg::CheckState()
{
    int CurSel = m_RemainingDeliverablesLB.GetCurSel();

    if ( GetDlgItem( IDC_ADD_DELIV ) )
    {
        GetDlgItem( IDC_ADD_DELIV )->EnableWindow( CurSel != LB_ERR );
    }

    CurSel = m_CombinationDeliverablesLB.GetCurSel();

    if ( GetDlgItem( IDC_DEL_DELIV ) )
    {
        GetDlgItem( IDC_DEL_DELIV )->EnableWindow( CurSel != LB_ERR );
    }
}

void ZVAddRemoveCombinationDeliverableDlg::AddStringToListBox( const CString str, CListBox& LB )
{
    LB.AddString( str );
}

void ZVAddRemoveCombinationDeliverableDlg::RemoveStringToListBox( const CString str, CListBox& LB )
{
    int Index = LB.FindString( 0, str );

    if ( Index != LB_ERR )
    {
        LB.DeleteString( Index );
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZVAddRemoveCombinationDeliverableDlg message handlers

BOOL ZVAddRemoveCombinationDeliverableDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    StringToListBox( m_RemainingDeliverables, m_RemainingDeliverablesLB );
    StringToListBox( m_Deliverables, m_CombinationDeliverablesLB );

    // Sets the maximum horizontal scroll
    m_CombinationDeliverablesLB.SetHorizontalExtent( 1000 );
    m_RemainingDeliverablesLB.SetHorizontalExtent( 1000 );

    CheckState();

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVAddRemoveCombinationDeliverableDlg::OnAddDeliv()
{
    int CurSel = m_RemainingDeliverablesLB.GetCurSel();

    if ( CurSel != LB_ERR )
    {
        CString str;
        m_RemainingDeliverablesLB.GetText( CurSel, str );
        AddStringToListBox( str, m_CombinationDeliverablesLB );
        RemoveStringToListBox( str, m_RemainingDeliverablesLB );
    }

    CheckState();
}

void ZVAddRemoveCombinationDeliverableDlg::OnDelDeliv()
{
    int CurSel = m_CombinationDeliverablesLB.GetCurSel();

    if ( CurSel != LB_ERR )
    {
        CString str;
        m_CombinationDeliverablesLB.GetText( CurSel, str );
        AddStringToListBox( str, m_RemainingDeliverablesLB );
        RemoveStringToListBox( str, m_CombinationDeliverablesLB );
    }

    CheckState();
}

void ZVAddRemoveCombinationDeliverableDlg::OnSelchangeCombDeliv()
{
    CheckState();
}

void ZVAddRemoveCombinationDeliverableDlg::OnSelchangeRemainDeliv()
{
    CheckState();
}

void ZVAddRemoveCombinationDeliverableDlg::OnOK()
{
    ListBoxToString( m_CombinationDeliverablesLB, m_Deliverables );

    CDialog::OnOK();
}
