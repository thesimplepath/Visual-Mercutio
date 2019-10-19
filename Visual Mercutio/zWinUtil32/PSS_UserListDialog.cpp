/****************************************************************************
 * ==> PSS_UserListDialog --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a user list dialog box                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UserListDialog.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UserListDialog, PSS_Dialog)
    //{{AFX_MSG_MAP(PSS_UserListDialog)
    ON_LBN_SELCHANGE(IDC_LIST_OF_USERS, OnSelChangeListOfUsers)
    ON_LBN_DBLCLK(IDC_LIST_OF_USERS, OnDblclkListOfUsers)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UserListDialog
//---------------------------------------------------------------------------
PSS_UserListDialog::PSS_UserListDialog(PSS_UserManager& userManager, CWnd* pParent) :
    PSS_Dialog(PSS_UserListDialog::IDD, TRUE, pParent),
    m_IsAdministrator(FALSE),
    m_UserManager(userManager),
    m_pUser(NULL)
{}
//---------------------------------------------------------------------------
void PSS_UserListDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_UserListDialog)
    DDX_Control(pDX, IDOK,                 m_InsertButton);
    DDX_Control(pDX, IDC_LIST_OF_USERS,    m_UserList);
    DDX_Text   (pDX, IDC_USER_DESCRIPTION, m_Description);
    DDX_Text   (pDX, IDC_RESPONSIBLE,      m_Responsible);
    DDX_Text   (pDX, IDC_EMAIL,            m_EMail);
    DDX_Text   (pDX, IDC_DEPARTEMENT,      m_Departement);
    DDX_Check  (pDX, IDC_ISADMINISTRATOR,  m_IsAdministrator);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_UserListDialog::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();
    
    LoadSource();
    CheckControlState();
    
    if (GetDlgItem(IDC_USER_DESCRIPTION))
       GetDlgItem(IDC_USER_DESCRIPTION)->EnableWindow(FALSE);

    if (GetDlgItem(IDC_RESPONSIBLE))
       GetDlgItem(IDC_RESPONSIBLE)->EnableWindow(FALSE);

    if (GetDlgItem(IDC_EMAIL))
       GetDlgItem(IDC_EMAIL)->EnableWindow(FALSE);

    if (GetDlgItem(IDC_DEPARTEMENT))
       GetDlgItem(IDC_DEPARTEMENT)->EnableWindow(FALSE);

    if (GetDlgItem(IDC_ISADMINISTRATOR))
       GetDlgItem(IDC_ISADMINISTRATOR)->EnableWindow(FALSE);

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_UserListDialog::OnSource()
{
    LoadSource();
}
//---------------------------------------------------------------------------
void PSS_UserListDialog::OnSelChangeListOfUsers()
{
    UpdateData();
    CheckControlState();

    const int curSel = m_UserList.GetCurSel();

    if (curSel != LB_ERR)
    {
        m_pUser = (ZUser*)m_UserList.GetItemDataPtr(curSel);

        if (m_pUser)
        {
            m_Description     = m_pUser->GetDescription();
            m_Responsible     = m_pUser->GetResponsible();
            m_EMail           = m_pUser->GetMailAddress();
            m_Departement     = m_pUser->GetDepartement();
            m_IsAdministrator = m_pUser->IsAdministrator();
        }
        else
        {
            m_Description     = "";
            m_Responsible     = "";
            m_EMail           = "";
            m_Departement     = "";
            m_IsAdministrator = FALSE;
        }

        UpdateData(FALSE);
    }
}
//---------------------------------------------------------------------------
void PSS_UserListDialog::OnDblclkListOfUsers()
{
    OnOK();
}
//---------------------------------------------------------------------------
void PSS_UserListDialog::LoadSource()
{
    UpdateData();
    m_UserList.ResetContent();

    for (std::size_t index = 0; index < m_UserManager.GetCount(); ++index)
    {
        ZUser* pObj = m_UserManager.GetAt(index);
        ASSERT(pObj);

        m_UserList.AddString((const char*)pObj->GetUserName());

        // find the user position
        const int userIndex = m_UserList.FindString(-1, pObj->GetUserName());

        if (userIndex == LB_ERR)
            m_UserList.SetItemDataPtr(userIndex, NULL);
        else
            m_UserList.SetItemDataPtr(userIndex, pObj);
    }

    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_UserListDialog::CheckControlState()
{
    m_InsertButton.EnableWindow(m_UserList.GetCurSel() != LB_ERR);
}
//---------------------------------------------------------------------------
