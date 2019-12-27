// **************************************************************************************************************
// *                                          Classe ZVSelectUserGroupDlg                                        *
// **************************************************************************************************************
// * Cette classe représente l'interface de sélection d'un utilisateur, ou d'un groupe d'utilisateurs, dans la    *
// * liste.                                                                                                        *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVSelectUserGroupDlg.h"

#include "ZBUserGroupEntity.h"
#include "ZBUserRoleEntity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 27 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVSelectUserGroupDlg dialog

BEGIN_MESSAGE_MAP( ZVSelectUserGroupDlg, CDialog )
    //{{AFX_MSG_MAP(ZVSelectUserGroupDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_USERGROUP_TREE, OnSelchangedUsergroupTree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVSelectUserGroupDlg::ZVSelectUserGroupDlg( const CString        Title                /*= ""*/,
                                            ZBUserGroupEntity*    pMainUserGroup        /*= NULL*/,
                                            bool                AllowGroupSelection    /*= true*/,
                                            bool                AllowRoleSelection    /*= true*/,
                                            CWnd*                pParent                /*=NULL*/ )
    : CDialog                ( ZVSelectUserGroupDlg::IDD, pParent ),
      m_pUserEntity            ( NULL ),
      m_Title                ( Title ),
      m_pMainUserGroup        ( pMainUserGroup ),
      m_AllowGroupSelection    ( AllowGroupSelection ),
      m_AllowRoleSelection    ( AllowRoleSelection )
{
    //{{AFX_DATA_INIT(ZVSelectUserGroupDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

ZVSelectUserGroupDlg::ZVSelectUserGroupDlg( UINT                nTitle,
                                            ZBUserGroupEntity*    pMainUserGroup,
                                            bool                AllowGroupSelection    /*= true*/,
                                            bool                AllowRoleSelection    /*= true*/,
                                            CWnd*                pParent                /*=NULL*/ )
    : CDialog                ( ZVSelectUserGroupDlg::IDD, pParent ),
      m_pUserEntity            ( NULL ),
      m_pMainUserGroup        ( pMainUserGroup ),
      m_AllowGroupSelection    ( AllowGroupSelection ),
      m_AllowRoleSelection    ( AllowRoleSelection )
{
    m_Title.LoadString( nTitle );
}

// JMR-MODIF - Le 27 février 2006 - Nettoyage des Memory Leaks, ajout du destructeur pour l'objet.
ZVSelectUserGroupDlg::~ZVSelectUserGroupDlg()
{
    Release();
}

// JMR-MODIF - Le 27 février 2006 - Nettoyage des memory leaks, ajout de la fonction Release.
void ZVSelectUserGroupDlg::Release()
{
    m_Title.Empty();
    m_Ctrl.Release();
}

void ZVSelectUserGroupDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVSelectUserGroupDlg)
    DDX_Control(pDX, IDC_USERGROUP_TREE, m_Ctrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVSelectUserGroupDlg message handlers

BOOL ZVSelectUserGroupDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    CString m_Text;
    m_Text.LoadString ( IDS_USERGROUP_ROOT_T );
    m_Ctrl.Initialize( m_Text, m_pMainUserGroup );

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

void ZVSelectUserGroupDlg::OnOK()
{
    // Save the selected item
    m_pUserEntity = m_Ctrl.GetSelectedEntity();

    CDialog::OnOK();
}

void ZVSelectUserGroupDlg::OnSelchangedUsergroupTree( NMHDR* pNMHDR, LRESULT* pResult )
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    BOOL Enable = FALSE;
    PSS_UserEntity* pEntity = m_Ctrl.GetSelectedEntity();

    if ( pEntity )
    {
        if ( m_AllowGroupSelection && ISA( pEntity, ZBUserGroupEntity ) )
        {
            Enable = TRUE;
        }
        else if ( m_AllowRoleSelection && ISA( pEntity, ZBUserRoleEntity ) )
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
