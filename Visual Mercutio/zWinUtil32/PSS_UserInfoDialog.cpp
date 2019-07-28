/****************************************************************************
 * ==> PSS_UserInfoDialog --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user info dialog box                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UserInfoDialog.h"

// resources
#include "zRes32\ZRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UserInfoDialog, ZIDialog)
    //{{AFX_MSG_MAP(PSS_UserInfoDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UserInfoDialog
//---------------------------------------------------------------------------
PSS_UserInfoDialog::PSS_UserInfoDialog(ZUser& user, bool creationMode, CWnd* pParent) :
    ZIDialog(PSS_UserInfoDialog::IDD, TRUE, pParent),
    m_User(user),
    m_CreationMode(creationMode)
{
    m_UserName    = m_User.GetUserName();
    m_Description = m_User.GetDescription();
    m_EMail       = m_User.GetMailAddress();
    m_Departement = m_User.GetDepartement();
    m_DisplayName = m_User.GetDisplayName();
    m_Responsible = m_User.GetResponsible();
    m_Admin       = m_User.IsAdministrator();
}
//---------------------------------------------------------------------------
void PSS_UserInfoDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_UserInfoDialog)
    DDX_Text (pDX, IDC_USERNAME_USER,    m_UserName);
    DDX_Text (pDX, IDC_DESCRIPTION_USER, m_Description);
    DDX_Text (pDX, IDC_EMAIL_USER,       m_EMail);
    DDX_Text (pDX, IDC_DEPARTEMENT_USER, m_Departement);
    DDX_Text (pDX, IDC_DISPLAYNAME_USER, m_DisplayName);
    DDX_Text (pDX, IDC_RESPONSIBLE_USER, m_Responsible);
    DDX_Check(pDX, IDC_ADMIN_USER,       m_Admin);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_UserInfoDialog::OnInitDialog()
{
    ZIDialog::OnInitDialog();

    if (!m_CreationMode && GetDlgItem(IDOK))
    {
        CString title;
        title.LoadString(IDS_MODIFY_TEXT);
        GetDlgItem(IDOK)->SetWindowText(title);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_UserInfoDialog::OnOK()
{
    UpdateData();

    if (m_UserName.IsEmpty())
        return;

    // save values
    m_User.SetUserName(m_UserName);
    m_User.SetDescription(m_Description);
    m_User.SetMailAddress(m_EMail);
    m_User.SetDepartement(m_Departement);
    m_User.SetDisplayName(m_DisplayName);
    m_User.SetResponsible(m_Responsible);
    m_User.SetAdministrator(m_Admin);

    ZIDialog::OnOK();
}
//---------------------------------------------------------------------------
