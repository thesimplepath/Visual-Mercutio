/****************************************************************************
 * ==> PSS_SelectUserGroupDlg ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a select user group dialog box                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectUserGroupDlg.h"

// processsoft
#include "PSS_UserGroupEntity.h"
#include "PSS_UserRoleEntity.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectUserGroupDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_SelectUserGroupDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_USERGROUP_TREE, OnSelchangedUsergroupTree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectUserGroupDlg
//---------------------------------------------------------------------------
PSS_SelectUserGroupDlg::PSS_SelectUserGroupDlg(const CString&       title,
                                               PSS_UserGroupEntity* pMainUserGroup,
                                               bool                 allowGroupSelection,
                                               bool                 allowRoleSelection,
                                               CWnd*                pParent) :
    CDialog(PSS_SelectUserGroupDlg::IDD, pParent),
    m_pUserEntity(NULL),
    m_pMainUserGroup(pMainUserGroup),
    m_Title(title),
    m_AllowGroupSelection(allowGroupSelection),
    m_AllowRoleSelection(allowRoleSelection)
{}
//---------------------------------------------------------------------------
PSS_SelectUserGroupDlg::PSS_SelectUserGroupDlg(UINT                 titleID,
                                               PSS_UserGroupEntity* pMainUserGroup,
                                               bool                 allowGroupSelection,
                                               bool                 allowRoleSelection,
                                               CWnd*                pParent) :
    CDialog(PSS_SelectUserGroupDlg::IDD, pParent),
    m_pUserEntity(NULL),
    m_pMainUserGroup(pMainUserGroup),
    m_AllowGroupSelection(allowGroupSelection),
    m_AllowRoleSelection(allowRoleSelection)
{
    m_Title.LoadString(titleID);
}
//---------------------------------------------------------------------------
PSS_SelectUserGroupDlg::~PSS_SelectUserGroupDlg()
{
    // NOTE the fully qualified name is used here to avoid to call a pure virtual function during the destruction
    PSS_SelectUserGroupDlg::Release();
}
//---------------------------------------------------------------------------
void PSS_SelectUserGroupDlg::Release()
{
    m_Title.Empty();
    m_Ctrl.Release();
}
//---------------------------------------------------------------------------
void PSS_SelectUserGroupDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectUserGroupDlg)
    DDX_Control(pDX, IDC_USERGROUP_TREE, m_Ctrl);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectUserGroupDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    CString text;
    text.LoadString(IDS_USERGROUP_ROOT_T);
    m_Ctrl.Initialize(text, m_pMainUserGroup);

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(FALSE);

    // return TRUE unless you set the focus to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectUserGroupDlg::OnSelchangedUsergroupTree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    PSS_UserEntity* pEntity = m_Ctrl.GetSelectedEntity();
    BOOL            enable  = FALSE;

    if (pEntity)
        if (m_AllowGroupSelection && ISA(pEntity, PSS_UserGroupEntity))
            enable = TRUE;
        else
        if (m_AllowRoleSelection && ISA(pEntity, PSS_UserRoleEntity))
            enable = TRUE;

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(enable);

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_SelectUserGroupDlg::OnOK()
{
    // Save the selected item
    m_pUserEntity = m_Ctrl.GetSelectedEntity();

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
