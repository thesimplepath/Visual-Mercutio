// UserInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UserInfoDlg.h"

#include "zRes32\ZRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIUserInformationDialog dialog


ZIUserInformationDialog::ZIUserInformationDialog(ZUser& User, bool CreationMode, CWnd* pParent /*=NULL*/)
    : ZIDialog(ZIUserInformationDialog::IDD, TRUE, pParent),
      m_User(User), 
      m_CreationMode(CreationMode)
{
    //{{AFX_DATA_INIT(ZIUserInformationDialog)
    m_Admin = m_User.IsAdministrator();
    m_Departement = m_User.GetDepartement();
    m_Description = m_User.GetDescription();
    m_DisplayName = m_User.GetDisplayName();
    m_Responsible = m_User.GetResponsible();
    m_Username = m_User.GetUserName();
    m_EMail = m_User.GetMailAddress();
    //}}AFX_DATA_INIT
}


void ZIUserInformationDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIUserInformationDialog)
    DDX_Check(pDX, IDC_ADMIN_USER, m_Admin);
    DDX_Text(pDX, IDC_DEPARTEMENT_USER, m_Departement);
    DDX_Text(pDX, IDC_DESCRIPTION_USER, m_Description);
    DDX_Text(pDX, IDC_DISPLAYNAME_USER, m_DisplayName);
    DDX_Text(pDX, IDC_RESPONSIBLE_USER, m_Responsible);
    DDX_Text(pDX, IDC_USERNAME_USER, m_Username);
    DDX_Text(pDX, IDC_EMAIL_USER, m_EMail);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIUserInformationDialog, ZIDialog)
    //{{AFX_MSG_MAP(ZIUserInformationDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIUserInformationDialog message handlers

void ZIUserInformationDialog::OnOK() 
{
    UpdateData();
    
    if (m_Username.IsEmpty())
    {
        return;
    }

    // Save values
    m_User.SetAdministrator( m_Admin );
    m_User.SetDepartement( m_Departement );
    m_User.SetDescription( m_Description );
    m_User.SetDisplayName( m_DisplayName );
    m_User.SetResponsible( m_Responsible );
    m_User.SetUserName( m_Username );
    m_User.SetMailAddress( m_EMail );

    ZIDialog::OnOK();
}

BOOL ZIUserInformationDialog::OnInitDialog() 
{
    ZIDialog::OnInitDialog();
    
    if (m_CreationMode == false)
    {
        if (GetDlgItem(IDOK))
        {
            CString    Title;
            Title.LoadString( IDS_MODIFY_TEXT );
            GetDlgItem(IDOK)->SetWindowText( Title );
        }
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
