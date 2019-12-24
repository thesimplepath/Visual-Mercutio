/****************************************************************************
 * ==> PSS_UserGroupInfoDlg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user group info dialog                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UserGroupInfoDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "ZBUserGroupEntity.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UserGroupInfoDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_UserGroupInfoDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UserGroupInfoDlg
//---------------------------------------------------------------------------
PSS_UserGroupInfoDlg::PSS_UserGroupInfoDlg(UINT               titleID,
                                           ZBUserGroupEntity* pGroup,
                                           const CString&     name,
                                           const CString&     description,
                                           const float        cost,
                                           bool               isRole,
                                           bool               modifyMode,
                                           CWnd*              pParent) :
    CDialog(PSS_UserGroupInfoDlg::IDD, pParent),
    m_pGroup(pGroup),
    m_Name(name),
    m_Description(description),
    m_Cost(cost),
    m_IsRole(isRole),
    m_ModifyMode(modifyMode)
{
    if (m_IsRole)
        m_CostStr = _T("");
    else
        m_CostStr.Format("%3.2f", cost);

    if (titleID != -1)
        m_Title.LoadString(titleID);
}
//---------------------------------------------------------------------------
void PSS_UserGroupInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_UserGroupInfoDlg)
    DDX_Text(pDX, IDC_UGP_NAME,        m_Name);
    DDX_Text(pDX, IDC_UGP_DESCRIPTION, m_Description);
    DDX_Text(pDX, IDC_UGP_COST,        m_CostStr);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_UserGroupInfoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    // the cost is not allowed for a role
    if (m_IsRole)
    {
        if (GetDlgItem(IDC_COST_STATIC))
            GetDlgItem(IDC_COST_STATIC)->EnableWindow(FALSE);

        if (GetDlgItem(IDC_UGP_COST))
            GetDlgItem(IDC_UGP_COST)->EnableWindow(FALSE);
    }
    if (m_ModifyMode)
        if (GetDlgItem(IDC_UGP_NAME))
            GetDlgItem(IDC_UGP_NAME)->EnableWindow(FALSE);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_UserGroupInfoDlg::OnOK()
{
    UpdateData(TRUE);

    if (!m_ModifyMode)
        if (m_pGroup && m_pGroup->GroupExist(m_Name))
        {
            // already exists
            PSS_MsgBox mBox;
            mBox.Show(IDS_UGP_GROUP_ALREADYEXIST, MB_OK);
            return;
        }

    // if not a role, converts the entered cost
    if (!m_IsRole)
        m_Cost = static_cast<float>(std::atof(m_CostStr));

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
