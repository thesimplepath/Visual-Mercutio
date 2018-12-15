// lstuser.cpp : implementation file
//

#include "stdafx.h"

#include "LstUser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIListUserDlg dialog


ZIListUserDlg::ZIListUserDlg(ZUUserManager& UserManager, CWnd* pParent /*=NULL*/)
    : ZIDialog(ZIListUserDlg::IDD, TRUE, pParent), m_UserManager(UserManager), m_pUser(NULL)
{
    //{{AFX_DATA_INIT(ZIListUserDlg)
    m_sDescription = "";
    m_Responsible = "";
    m_EMail = "";
    m_Departement = _T("");
    m_IsAdministrator = FALSE;
    //}}AFX_DATA_INIT
}

void ZIListUserDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIListUserDlg)
    DDX_Control(pDX, IDOK, m_InsertButton);
    DDX_Control(pDX, IDC_LIST_OF_USERS, m_ListOfUsers);
    DDX_Text(pDX, IDC_USER_DESCRIPTION, m_sDescription);
    DDX_Text(pDX, IDC_RESPONSIBLE, m_Responsible);
    DDX_Text(pDX, IDC_EMAIL, m_EMail);
    DDX_Text(pDX, IDC_DEPARTEMENT, m_Departement);
    DDX_Check(pDX, IDC_ISADMINISTRATOR, m_IsAdministrator);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZIListUserDlg, CDialog)
    //{{AFX_MSG_MAP(ZIListUserDlg)
    ON_LBN_SELCHANGE(IDC_LIST_OF_USERS, OnSelChangeListOfUsers)
    ON_LBN_DBLCLK(IDC_LIST_OF_USERS, OnDblclkListOfUsers)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// ZIListUserDlg message handlers

BOOL ZIListUserDlg::OnInitDialog()
{
    ZIDialog::OnInitDialog();
    
    LoadSource();
    CheckControlState();
    
    if (GetDlgItem(IDC_USER_DESCRIPTION))
       GetDlgItem(IDC_USER_DESCRIPTION)->EnableWindow( FALSE );
    if (GetDlgItem(IDC_RESPONSIBLE))
       GetDlgItem(IDC_RESPONSIBLE)->EnableWindow( FALSE );
    if (GetDlgItem(IDC_EMAIL))
       GetDlgItem(IDC_EMAIL)->EnableWindow( FALSE );
    if (GetDlgItem(IDC_DEPARTEMENT))
       GetDlgItem(IDC_DEPARTEMENT)->EnableWindow( FALSE );
    if (GetDlgItem(IDC_ISADMINISTRATOR))
       GetDlgItem(IDC_ISADMINISTRATOR)->EnableWindow( FALSE );
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void ZIListUserDlg::OnSelChangeListOfUsers()
{
    UpdateData();
    CheckControlState();
    int    iCurSel = m_ListOfUsers.GetCurSel();
    if (iCurSel != LB_ERR)
    {
        m_pUser = (ZUser*)m_ListOfUsers.GetItemDataPtr( iCurSel );
        if (m_pUser)
        {
            m_sDescription = m_pUser->GetDescription();
            m_Responsible = m_pUser->GetResponsible();
            m_EMail = m_pUser->GetMailAddress();
            m_Departement = m_pUser->GetDepartement();
            m_IsAdministrator = m_pUser->IsAdministrator();
        }
        else
        {
            m_sDescription = "";
            m_Responsible = "";
            m_EMail = "";
            m_Departement = "";
            m_IsAdministrator = FALSE;
        }
        UpdateData( FALSE );
        
    }
}


void ZIListUserDlg::CheckControlState()
{
    m_InsertButton.EnableWindow( m_ListOfUsers.GetCurSel() != LB_ERR );
}


void ZIListUserDlg::OnSource()
{
    LoadSource();
}

void ZIListUserDlg::LoadSource()
{
    UpdateData();
    m_ListOfUsers.ResetContent();
    
    ZUser*     pObj;
    int        UserIndex;
    for (size_t Index = 0 ; Index < m_UserManager.GetCount(); ++Index)
    {
          pObj = m_UserManager.GetAt( Index );
        m_ListOfUsers.AddString( (const char*)pObj->GetUserName() );
        // Find the user position
        UserIndex = m_ListOfUsers.FindString( -1, pObj->GetUserName() );
        if (UserIndex == LB_ERR)
            m_ListOfUsers.SetItemDataPtr( UserIndex, NULL );
        else
            m_ListOfUsers.SetItemDataPtr( UserIndex, pObj );
    }
    CheckControlState();
}



void ZIListUserDlg::OnDblclkListOfUsers()
{
    OnOK();
}
