/****************************************************************************
 * ==> PSS_ActivityAttributionBackupInputDialog ----------------------------*
 ****************************************************************************
 * Description : Provides an activity attribution backup input dialog box   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ActivityAttributionBackupInputDialog.h"

// processsoft
#include "zBaseLib\ZBTokenizer.h"
#include "zBaseLib\MsgBox.h"
#include "zBaseLib\InpVal.h"
#include "ZVChooseResources.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ActivityAttributionBackupInputDialog, ZIWizardDialog)
    //{{AFX_MSG_MAP(PSS_ActivityAttributionBackupInputDialog)
    ON_BN_CLICKED(IDNEXT, OnNext)
    ON_BN_CLICKED(IDC_ADDUSER, OnAddUser)
    ON_BN_CLICKED(IDC_REMOVEUSER, OnDeleteUser)
    ON_LBN_SELCHANGE(IDC_USERLIST, OnSelChangeUserList)
    ON_BN_CLICKED(IDC_ADDEMAIL, OnAddEmail)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ActivityAttributionBackupInputDialog
//---------------------------------------------------------------------------
PSS_ActivityAttributionBackupInputDialog::PSS_ActivityAttributionBackupInputDialog(ZUUserManager& userManager,
                                                                                   ZUMail&        mail,
                                                                                   ZActivity*     pActivity,
                                                                                   BOOL           lastActivity,
                                                                                   CWnd*          pParent) :
    ZIWizardDialog(PSS_ActivityAttributionBackupInputDialog::IDD,
                   IDB_WZBMP1,
                   0,
                   0,
                   IDS_ATTRIBUTIONTITLE_WZ,
                   IDS_ATTRIBUTIONBACKUPTEXTE_WZ),
    m_UserManager(userManager),
    m_Mail(mail),
    m_pActivity(pActivity),
    m_LastActivity(lastActivity)
{
    ASSERT(m_pActivity);
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionBackupInputDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ActivityAttributionBackupInputDialog)
    DDX_Control(pDX, IDC_USERLIST,     m_UserList);
    DDX_Text   (pDX, IDC_ACTIVITYNAME, m_ActivityName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityAttributionBackupInputDialog::OnInitDialog()
{
    ASSERT(m_pActivity);
    m_ActivityName = m_pActivity->GetName();

    ZIWizardDialog::OnInitDialog();

    const std::size_t count = m_pActivity->GetBackupUserCount();

    for (std::size_t i = 0; i < count; ++i)
        m_UserList.AddString(m_pActivity->GetBackupUserAt(i));

    CheckControlState();

    // disable the posibility to change the name
    if (GetDlgItem(IDC_ACTIVITYNAME))
       GetDlgItem(IDC_ACTIVITYNAME)->EnableWindow( FALSE );

    if (GetDlgItem(IDOK))
       GetDlgItem(IDOK)->EnableWindow(m_LastActivity);

    if (GetDlgItem(IDNEXT))
       GetDlgItem(IDNEXT)->EnableWindow(!m_LastActivity);

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionBackupInputDialog::OnAddUser()
{
    ZVChooseResources chooseResources(m_UserManager);

    if (chooseResources.DoModal() == IDOK && !chooseResources.GetUserListString().IsEmpty())
    {
        ZBTokenizer tokenizer(';');
        CString     token = tokenizer.GetFirstToken(chooseResources.GetUserListString());

        // parse the user delimiter string
        while (!token.IsEmpty())
        {
            // check if not already in the list
            if (m_UserList.FindString(-1, token ) == LB_ERR)
                m_UserList.AddString(token);

            token = tokenizer.GetNextToken();
        }
    }

    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionBackupInputDialog::OnDeleteUser()
{
    const int curSel = m_UserList.GetCurSel();

    if (curSel != LB_ERR)
        m_UserList.DeleteString(curSel);

    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionBackupInputDialog::OnSelChangeUserList()
{
    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionBackupInputDialog::OnAddEmail()
{
    CString title;
    title.LoadString(IDS_ENTER_EMAILADRESS);

    ZIInputValue inputValue(title);
            
    if (inputValue.DoModal() == IDOK)
        // check if not null and not already in the list
        if (m_UserList.FindString(-1, inputValue.GetValue()) == LB_ERR)
            m_UserList.AddString(inputValue.GetValue());
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionBackupInputDialog::OnOK()
{
    if (!CheckData())
        return;

    SaveState();

    ZIWizardDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionBackupInputDialog::OnNext()
{
    if (!CheckData())
        return;

    SaveState();

    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionBackupInputDialog::CheckControlState()
{
    if (GetDlgItem(IDC_REMOVEUSER))
        GetDlgItem(IDC_REMOVEUSER)->EnableWindow(m_UserList.GetCurSel() != LB_ERR);
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionBackupInputDialog::SaveState()
{
    UpdateData();

    ASSERT(m_pActivity);

    // save data
    m_pActivity->RemoveAllBackupUsers();

    const int     count = m_UserList.GetCount();
          CString text;

    for (int i = 0; i < count; ++i)
    {
        m_UserList.GetText(i, text);
        m_pActivity->AddBackupUser(text);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityAttributionBackupInputDialog::CheckData()
{
    UpdateData();

    // user must be in the list
    if (m_UserList.GetCount() <= 0)
    {
        MsgBox mbox;
        mbox.DisplayMsgBox(IDS_ONEPERSON_REQUIRED, MB_OK);
        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
