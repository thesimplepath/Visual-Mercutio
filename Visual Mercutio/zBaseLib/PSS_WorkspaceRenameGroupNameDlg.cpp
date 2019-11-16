/****************************************************************************
 * ==> PSS_WorkspaceRenameGroupNameDlg -------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace rename group name dialog box          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceRenameGroupNameDlg.h"

// processsoft
#include "PSS_WorkspaceGroupEntity.h"
#include "PSS_MsgBox.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WorkspaceRenameGroupNameDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_WorkspaceRenameGroupNameDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WorkspaceRenameGroupNameDlg
//---------------------------------------------------------------------------
PSS_WorkspaceRenameGroupNameDlg::PSS_WorkspaceRenameGroupNameDlg(const CString&            groupName,
                                                                 PSS_WorkspaceGroupEntity* pParentGroup,
                                                                 CWnd*                     pParent) :
    CDialog(PSS_WorkspaceRenameGroupNameDlg::IDD, pParent),
    m_pParentGroup(pParentGroup),
    m_GroupName(groupName)
{}
//---------------------------------------------------------------------------
void PSS_WorkspaceRenameGroupNameDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_WorkspaceRenameGroupNameDlg)
    DDX_Text(pDX, IDC_WKS_GROUPNAME, m_GroupName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceRenameGroupNameDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceRenameGroupNameDlg::OnOK()
{
    UpdateData(TRUE);

    if (m_pParentGroup && m_pParentGroup->GroupExist(m_GroupName))
    {
        // already exists
        PSS_MsgBox mBox;
        mBox.Show(IDS_WKS_GROUP_ALREADYEXIST, MB_OK);
        return;
    }

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
