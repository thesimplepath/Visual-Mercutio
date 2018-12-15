// **************************************************************************************************************
// *                                       Classe ZVSelectRuleDlg                                                *
// **************************************************************************************************************
// * JMR-MODIF - Le 15 novembre 2006 - Ajout de la classe ZVSelectRuleDlg.                                        *
// **************************************************************************************************************
// * Cette classe représente l'interface de sélection d'une règle, ou d'un groupe de règles, dans la liste.        *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVSelectRuleDlg.h"

#include "ZBLogicalRulesEntity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVSelectRuleDlg dialog

BEGIN_MESSAGE_MAP( ZVSelectRuleDlg, CDialog )
    //{{AFX_MSG_MAP(ZVSelectRuleDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_RULES_TREE, OnSelchangedRulesTree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVSelectRuleDlg::ZVSelectRuleDlg( const CString            Title                /*= ""*/,
                                  ZBLogicalRulesEntity*    pMainRule            /*= NULL*/,
                                  bool                    AllowRuleSelection    /*= true*/,
                                  CWnd*                    pParent                /*=NULL*/ )
    : CDialog                ( ZVSelectRuleDlg::IDD, pParent ),
      m_pRuleEntity            ( NULL ),
      m_Title                ( Title ),
      m_pMainRule            ( pMainRule ),
      m_AllowRuleSelection    ( AllowRuleSelection )
{
    //{{AFX_DATA_INIT(ZVSelectRuleDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

ZVSelectRuleDlg::ZVSelectRuleDlg( UINT                    nTitle,
                                  ZBLogicalRulesEntity*    pMainRule,
                                  bool                    AllowRuleSelection    /*= true*/,
                                  CWnd*                    pParent                /*=NULL*/ )
    : CDialog                ( ZVSelectRuleDlg::IDD, pParent ),
      m_pRuleEntity            ( NULL ),
      m_pMainRule            ( pMainRule ),
      m_AllowRuleSelection    ( AllowRuleSelection )
{
    m_Title.LoadString( nTitle );
}

ZVSelectRuleDlg::~ZVSelectRuleDlg()
{
    Release();
}

void ZVSelectRuleDlg::Release()
{
    m_Title.Empty();
    m_Ctrl.Release();
}

void ZVSelectRuleDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVSelectRuleDlg)
    DDX_Control(pDX, IDC_RULES_TREE, m_Ctrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVSelectRuleDlg message handlers

BOOL ZVSelectRuleDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    CString m_Text;
    m_Text.LoadString ( IDS_RULE_ROOT_T );
    m_Ctrl.Initialize( m_Text, m_pMainRule );

    if ( !m_Title.IsEmpty() )
    {
        SetWindowText( m_Title );
    }

    if ( GetDlgItem( IDOK ) )
    {
        GetDlgItem( IDOK )->EnableWindow( FALSE );
    }

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVSelectRuleDlg::OnOK()
{
    // Save the selected item
    m_pRuleEntity = m_Ctrl.GetSelectedRuleEntity();

    CDialog::OnOK();
}

void ZVSelectRuleDlg::OnSelchangedRulesTree( NMHDR* pNMHDR, LRESULT* pResult )
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    BOOL Enable = FALSE;
    ZBRulesEntity* pEntity = m_Ctrl.GetSelectedRuleEntity();

    if ( pEntity )
    {
        if ( m_AllowRuleSelection && ISA( pEntity, ZBLogicalRulesEntity ) )
        {
            Enable = TRUE;
        }
    }

    if ( GetDlgItem( IDOK ) )
    {
        GetDlgItem( IDOK )->EnableWindow( Enable );
    }

    *pResult = 0;
}
