// ActBAttr.cpp : implementation file
//

#include "stdafx.h"
#include "ActBAttr.h"

#include "ZVChooseResources.h"
#include "zBaseLib\ZBTokenizer.h"

#include "zBaseLib\MsgBox.h"
#include "zBaseLib\InpVal.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIActivityAttributionBackupInput dialog


ZIActivityAttributionBackupInput::ZIActivityAttributionBackupInput(ZUUserManager& UserManager, ZUMail& Mail, ZActivity* pActivity, BOOL LastActivity, CWnd* pParent)
    :     ZIWizardDialog(ZIActivityAttributionBackupInput::IDD, // Dialog template
                       IDB_WZBMP1,    // Bitmap to display
                       0,            // Icon do display
                       0,                    // Window Title
                       IDS_ATTRIBUTIONTITLE_WZ, // Wizard title
                       IDS_ATTRIBUTIONBACKUPTEXTE_WZ    // Wizard text
                       ), 
        m_UserManager(UserManager), m_Mail(Mail), m_pActivity(pActivity),
        m_LastActivity(LastActivity)
        
{
    ASSERT( m_pActivity );
    //{{AFX_DATA_INIT(ZIActivityAttributionBackupInput)
    m_ActivityName = "";
    //}}AFX_DATA_INIT
}


void ZIActivityAttributionBackupInput::CheckControlState()
{
//    UpdateData();
    if (GetDlgItem(IDC_REMOVEUSER))
       GetDlgItem(IDC_REMOVEUSER)->EnableWindow( m_UserList.GetCurSel() != LB_ERR );
       
}

void ZIActivityAttributionBackupInput::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIActivityAttributionBackupInput)
    DDX_Control(pDX, IDC_USERLIST, m_UserList);
    DDX_Text(pDX, IDC_ACTIVITYNAME, m_ActivityName);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZIActivityAttributionBackupInput, ZIWizardDialog)
    //{{AFX_MSG_MAP(ZIActivityAttributionBackupInput)
    ON_BN_CLICKED(IDNEXT, OnNext)
    ON_BN_CLICKED(IDC_ADDUSER, OnAddUser)
    ON_BN_CLICKED(IDC_REMOVEUSER, OnDeleteUser)
    ON_LBN_SELCHANGE(IDC_USERLIST, OnSelChangeUserList)
    ON_BN_CLICKED(IDC_ADDEMAIL, OnAddEmail)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIActivityAttributionBackupInput message handlers

BOOL ZIActivityAttributionBackupInput::OnInitDialog()
{
    ASSERT( m_pActivity );
    m_ActivityName = m_pActivity->GetName();

    ZIWizardDialog::OnInitDialog();
    

    for (size_t i = 0; i < m_pActivity->GetBackupUserCount(); ++i)
        m_UserList.AddString( m_pActivity->GetBackupUserAt(i) );

    CheckControlState();

    // Disable the posibility to change the name        
    if (GetDlgItem(IDC_ACTIVITYNAME))
       GetDlgItem(IDC_ACTIVITYNAME)->EnableWindow( FALSE );
    if (GetDlgItem(IDOK))
       GetDlgItem(IDOK)->EnableWindow( m_LastActivity );
    if (GetDlgItem(IDNEXT))
       GetDlgItem(IDNEXT)->EnableWindow( !m_LastActivity );

    return TRUE;  // return TRUE  unless you set the focus to a control
}


void ZIActivityAttributionBackupInput::OnAddUser()
{
    ZVChooseResources    ChooseResources( m_UserManager );
    
    if (ChooseResources.DoModal() == IDOK && !ChooseResources.GetUserListString().IsEmpty())
    {
        // Parse the user delimiter string
        ZBTokenizer    Tokenizer( ';' );
        CString    Token = Tokenizer.GetFirstToken( ChooseResources.GetUserListString() );
        while (!Token.IsEmpty())
        {
            // Check if not already in the list
            if (m_UserList.FindString( -1, Token ) == LB_ERR)
                m_UserList.AddString( Token );
            Token = Tokenizer.GetNextToken();
        }
    }
    CheckControlState();
}

void ZIActivityAttributionBackupInput::OnAddEmail()
{
    CString    Title;
    Title.LoadString( IDS_ENTER_EMAILADRESS );
    ZIInputValue    InputValue( Title );
            
    if (InputValue.DoModal() == IDOK)
    {
        // Check if not null and not already in the list
        if (m_UserList.FindString( -1, InputValue.GetValue() ) == LB_ERR)
            m_UserList.AddString( InputValue.GetValue() );
    }    
}

void ZIActivityAttributionBackupInput::OnDeleteUser()
{
    int    iCurSel = m_UserList.GetCurSel();
    if (iCurSel != LB_ERR)
    {
        m_UserList.DeleteString( iCurSel );
    }    
    CheckControlState();
}

void ZIActivityAttributionBackupInput::OnSelChangeUserList()
{
    CheckControlState();
}

void ZIActivityAttributionBackupInput::SaveState()
{
    UpdateData();

    ASSERT( m_pActivity );
    
    // Save data
    m_pActivity->RemoveAllBackupUsers();

    CString    Text;
    for (int i = 0; i < m_UserList.GetCount(); ++i)
    {
        m_UserList.GetText( i, Text );
        m_pActivity->AddBackupUser( Text );
    }
}


BOOL ZIActivityAttributionBackupInput::CheckData()
{
    UpdateData();
    // User must be in the list
    if (m_UserList.GetCount() <= 0)
    {
        MsgBox        mbox;
        mbox.DisplayMsgBox( IDS_ONEPERSON_REQUIRED, MB_OK );
        return FALSE;
    }
    return TRUE;
}

void ZIActivityAttributionBackupInput::OnOK()
{
    if (!CheckData())
        return;
    SaveState();
    ZIWizardDialog::OnOK();
}



void ZIActivityAttributionBackupInput::OnNext()
{
    if (!CheckData())
        return;
    SaveState();
    EndDialog( IDNEXT );
}



