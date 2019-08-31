/****************************************************************************
 * ==> PSS_WorkspaceGroupNameDlg -------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace group name dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceGroupNameDlg.h"

// processsoft
#include "ZBWorkspaceGroupEntity.h"
#include "PSS_MsgBox.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WorkspaceGroupNameDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_WorkspaceGroupNameDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WorkspaceGroupNameDlg
//---------------------------------------------------------------------------
PSS_WorkspaceGroupNameDlg::PSS_WorkspaceGroupNameDlg(ZBWorkspaceGroupEntity* pRootGroup,
                                                     const CString&          groupName,
                                                     const CString&          extensionList,
                                                     CWnd*                   pParent) :
    CDialog(PSS_WorkspaceGroupNameDlg::IDD, pParent),
    m_pRootGroup(pRootGroup),
    m_Extensions(extensionList),
    m_GroupName(groupName),
    m_Modify(false)
{
    m_Modify = !m_GroupName.IsEmpty();
}
//---------------------------------------------------------------------------
void PSS_WorkspaceGroupNameDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_WorkspaceGroupNameDlg)
    DDX_Text(pDX, IDC_WKS_EXTENSIONS, m_Extensions);
    DDX_Text(pDX, IDC_WKS_GROUPNAME,  m_GroupName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceGroupNameDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (m_Modify)
    {
        if (GetDlgItem(IDC_WKS_GROUPNAME))
            GetDlgItem(IDC_WKS_GROUPNAME)->EnableWindow(FALSE);

        // change the title for properties
        CString s;
        s.LoadString(IDS_WKS_PROPGROUP_T);

        SetWindowText(s);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceGroupNameDlg::OnOK()
{
    UpdateData(TRUE);

    if (!m_Modify && m_pRootGroup && m_pRootGroup->GroupExist(m_GroupName))
    {
        // already exists
        PSS_MsgBox mBox;
        mBox.Show(IDS_WKS_GROUP_ALREADYEXIST, MB_OK);
        return;
    }

    // illegal char in extension set
    if (m_Extensions.FindOneOf(",.-/") != -1)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_WKS_ILLEGAL_EXTENSION_LIST, MB_OK);
        return;
    }

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
