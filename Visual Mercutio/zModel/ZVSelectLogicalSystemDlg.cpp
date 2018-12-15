// **************************************************************************************************************
// *                                        Classe ZVSelectLogicalSystemDlg                                        *
// **************************************************************************************************************
// * Cette classe représente l'interface de sélection d'un système logique, ou d'un groupe de systèmes logiques    *
// * dans la liste.                                                                                                *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVSelectLogicalSystemDlg.h"

#include "ZBLogicalSystemEntity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 27 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVSelectLogicalSystemDlg dialog

BEGIN_MESSAGE_MAP( ZVSelectLogicalSystemDlg, CDialog )
    //{{AFX_MSG_MAP(ZVSelectLogicalSystemDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_LOGICALSYSTEM_TREE, OnSelchangedLogicalSystemTree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVSelectLogicalSystemDlg::ZVSelectLogicalSystemDlg( const CString            Title                        /*= ""*/,
                                                    ZBLogicalSystemEntity*    pMainLogicalSystemGroup        /*= NULL*/,
                                                    CWnd*                    pParent                        /*=NULL*/ )
    : CDialog                    ( ZVSelectLogicalSystemDlg::IDD, pParent ),
      m_pSystemEntity            ( NULL ),
      m_Title                    ( Title ),
      m_pMainLogicalSystemGroup    ( pMainLogicalSystemGroup )
{
    //{{AFX_DATA_INIT(ZVSelectLogicalSystemDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

ZVSelectLogicalSystemDlg::ZVSelectLogicalSystemDlg( UINT                    nTitle,
                                                    ZBLogicalSystemEntity*    pMainLogicalSystemGroup,
                                                    CWnd*                    pParent                    /*=NULL*/ )
    : CDialog                    ( ZVSelectLogicalSystemDlg::IDD, pParent ),
      m_pSystemEntity            ( NULL ),
      m_pMainLogicalSystemGroup    ( pMainLogicalSystemGroup )
{
    m_Title.LoadString( nTitle );
}

// JMR-MODIF - Le 27 février 2006 - Nettoyage des memory leaks, ajout du destructeur de l'objet.
ZVSelectLogicalSystemDlg::~ZVSelectLogicalSystemDlg()
{
    Release();
}

// JMR-MODIF - Le 27 février 2006 - Nettoyage des memory leaks, ajout de la fonction Release.
void ZVSelectLogicalSystemDlg::Release()
{
    m_Title.Empty();
    m_Ctrl.Release();
}

void ZVSelectLogicalSystemDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVSelectLogicalSystemDlg)
    DDX_Control(pDX, IDC_LOGICALSYSTEM_TREE, m_Ctrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVSelectLogicalSystemDlg message handlers

BOOL ZVSelectLogicalSystemDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    CString m_Text;
    m_Text.LoadString ( IDS_LOGICALSYSTEM_ROOT_T );
    m_Ctrl.Initialize( m_Text, m_pMainLogicalSystemGroup );
    
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

void ZVSelectLogicalSystemDlg::OnOK()
{
    // Save the selected item
    m_pSystemEntity = m_Ctrl.GetSelectedSystemEntity();

    CDialog::OnOK();
}

void ZVSelectLogicalSystemDlg::OnSelchangedLogicalSystemTree( NMHDR* pNMHDR, LRESULT* pResult )
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    BOOL Enable = FALSE;
    ZBSystemEntity* pEntity = m_Ctrl.GetSelectedSystemEntity();

    if ( pEntity )
    {
        Enable = TRUE;
    }

    if ( GetDlgItem( IDOK ) )
    {
        GetDlgItem( IDOK )->EnableWindow( Enable );
    }

    *pResult = 0;
}
