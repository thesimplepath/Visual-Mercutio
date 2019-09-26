/****************************************************************************
 * ==> PSS_ActivityAttributionInputValueDialog -----------------------------*
 ****************************************************************************
 * Description : Provides the activity attribution input value dialog box   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ActivityAttributionInputValueDialog.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_InputValue.h"
#include "PSS_SelectResourcesDialog.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ActivityAttributionInputValueDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_ActivityAttributionInputValueDialog)
    ON_BN_CLICKED(IDNEXT, OnNext)
    ON_BN_CLICKED(IDC_ADDUSER, OnAddUser)
    ON_BN_CLICKED(IDC_REMOVEUSER, OnDeleteUser)
    ON_LBN_SELCHANGE(IDC_USERLIST, OnSelChangeUserList)
    ON_BN_CLICKED(IDC_ADDEMAIL, OnAddEmail)
    ON_BN_CLICKED(IDC_VISIBILITYTYPE, OnVisibilityType)
    ON_BN_CLICKED(IDC_VISIBILITYTYPE2, OnVisibilityType)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ActivityAttributionInputValueDialog
//---------------------------------------------------------------------------
PSS_ActivityAttributionInputValueDialog::PSS_ActivityAttributionInputValueDialog(PSS_UserManager& userManager,
                                                                                 ZUMail&          mail,
                                                                                 ZActivity*       pActivity,
                                                                                 BOOL             lastActivity,
                                                                                 BOOL             userAttribution,
                                                                                 BOOL             timeAttribution,
                                                                                 BOOL             visibilityAttribution,
                                                                                 CWnd*            pParent) :
    PSS_WizardDialog(PSS_ActivityAttributionInputValueDialog::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_ATTRIBUTIONTITLE_WZ,
                     IDS_ATTRIBUTIONTEXTE_WZ),
    m_ActivityName(""),
    m_TimeOutDays(0),
    m_VisibilityType(-1),
    m_UserManager(userManager),
    m_Mail(mail),
    m_pActivity(pActivity),
    m_LastActivity(lastActivity),
    m_UserAttribution(userAttribution),
    m_TimeAttribution(timeAttribution),
    m_VisibilityAttribution(visibilityAttribution)
{
    ASSERT(m_pActivity);
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionInputValueDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ActivityAttributionValueInputDialog)
    DDX_Control(pDX, IDC_USERLIST,       m_UserList);
    DDX_Text   (pDX, IDC_ACTIVITYNAME,   m_ActivityName);
    DDX_Text   (pDX, IDC_TIMEOUT,        m_TimeOutDays);
    DDX_Radio  (pDX, IDC_VISIBILITYTYPE, m_VisibilityType);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityAttributionInputValueDialog::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    ASSERT(m_pActivity);
    m_ActivityName = m_pActivity->GetName();

    const std::size_t userCount = m_pActivity->GetUserCount();

    for (std::size_t i = 0; i < userCount; ++i)
        m_UserList.AddString(m_pActivity->GetUserAt(i));

    m_TimeOutDays = m_pActivity->GetDurationDays();

    // set the visibility type
    switch (m_pActivity->GetIsVisible())
    {
        case E_TS_True:  m_VisibilityType =  0; break;
        case E_TS_False: m_VisibilityType =  1; break;
        default:         m_VisibilityType = -1;
    }

    // propagate changes
    UpdateData(FALSE);

    // disable the posibility to change the name
    if (GetDlgItem(IDC_ACTIVITYNAME))
        GetDlgItem(IDC_ACTIVITYNAME)->EnableWindow(FALSE);

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(m_LastActivity);

    if (GetDlgItem(IDNEXT))
        GetDlgItem(IDNEXT)->EnableWindow(!m_LastActivity);

    if (GetDlgItem(IDC_VISIBILITYTYPE))
        GetDlgItem(IDC_VISIBILITYTYPE)->EnableWindow(m_VisibilityAttribution);

    if (GetDlgItem(IDC_VISIBILITYTYPE2))
        GetDlgItem(IDC_VISIBILITYTYPE2)->EnableWindow(m_VisibilityAttribution);

    CheckControlState();

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionInputValueDialog::OnAddUser()
{
    PSS_SelectResourcesDialog selectResourcesDialog(m_UserManager);

    if (selectResourcesDialog.DoModal() == IDOK && !selectResourcesDialog.GetUserListString().IsEmpty())
    {
        PSS_Tokenizer tokenizer(';');
        CString       token = tokenizer.GetFirstToken(selectResourcesDialog.GetUserListString());

        // parse the user delimiter string
        while (!token.IsEmpty())
        {
            // check if not already in the list
            if (m_UserList.FindString(-1, token) == LB_ERR)
                m_UserList.AddString(token);

            token = tokenizer.GetNextToken();
        }
    }

    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionInputValueDialog::OnDeleteUser()
{
    const int curSel = m_UserList.GetCurSel();

    if (curSel != LB_ERR)
        m_UserList.DeleteString(curSel);

    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionInputValueDialog::OnSelChangeUserList()
{
    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionInputValueDialog::OnOK()
{
    if (!CheckData())
        return;

    SaveState();

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionInputValueDialog::OnNext()
{
    if (!CheckData())
        return;

    SaveState();
    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionInputValueDialog::OnAddEmail()
{
    CString title;
    title.LoadString(IDS_ENTER_EMAILADRESS);

    PSS_InputValue inputValue(title);

    if (inputValue.DoModal() == IDOK)
    {
        const CString value = inputValue.GetValue();

        // check if not null and not already in the list
        if (m_UserList.FindString(-1, value) == LB_ERR)
            m_UserList.AddString(value);
    }
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionInputValueDialog::OnVisibilityType()
{
    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionInputValueDialog::CheckControlState()
{
    UpdateData();

    if (GetDlgItem(IDC_REMOVEUSER))
       GetDlgItem(IDC_REMOVEUSER)->EnableWindow(m_UserList.GetCurSel() != LB_ERR);

    if (GetDlgItem(IDC_ADDUSER))
       GetDlgItem(IDC_ADDUSER)->EnableWindow(m_UserAttribution && m_VisibilityType != 1);

    if (GetDlgItem(IDC_ADDEMAIL))
       GetDlgItem(IDC_ADDEMAIL)->EnableWindow(m_UserAttribution && m_VisibilityType != 1);

    if (GetDlgItem(IDC_USERLIST))
       GetDlgItem(IDC_USERLIST)->EnableWindow(m_UserAttribution && m_VisibilityType != 1);

    if (GetDlgItem(IDC_REMOVEUSER))
       GetDlgItem(IDC_REMOVEUSER)->EnableWindow(m_UserAttribution && m_VisibilityType != 1);

    if (GetDlgItem(IDC_TIMEOUT))
       GetDlgItem(IDC_TIMEOUT)->EnableWindow(m_TimeAttribution && m_VisibilityType != 1);
}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionInputValueDialog::SaveState()
{
    UpdateData();

    ASSERT(m_pActivity);

    m_pActivity->SetDurationDays( m_TimeOutDays );

    // save data
    m_pActivity->RemoveAllUsers();

    CString text;

    for (int i = 0; i < m_UserList.GetCount(); ++i)
    {
        m_UserList.GetText(i, text);
        m_pActivity->AddUser(text);
    }

    // set the real state of the activity
    m_pActivity->SetVisibility(!m_VisibilityType ? E_TS_True : E_TS_False);
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityAttributionInputValueDialog::CheckData()
{
    UpdateData();

    // user must sets the visibility
    if (m_VisibilityAttribution && m_VisibilityType == -1)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_VISIBILITY_REQUIRED, MB_OK);
        return FALSE;
    }

    // if the user must attribute the visibility and he has attributed invisible,
    // do not check the other fields
    if (m_VisibilityAttribution && m_VisibilityType == 1)
        return TRUE;

    // time must be defined
    if (m_TimeAttribution && m_TimeOutDays <= 0)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_TIMEOUT_REQUIRED, MB_OK);
        return FALSE;
    }

    // user must be in the list
    if (m_UserAttribution && m_UserList.GetCount() <= 0)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_ONEPERSON_REQUIRED, MB_OK);
        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
