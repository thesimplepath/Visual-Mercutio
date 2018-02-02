// actIattr.cpp : implementation file
//

#include "stdafx.h"
#include "actIattr.h"

#include "ZVChooseResources.h"
#include "zBaseLib\ZBTokenizer.h"

#include "zBaseLib\MsgBox.h"
#include "zBaseLib\InpVal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIActivityAttributionValueInput dialog


ZIActivityAttributionValueInput::ZIActivityAttributionValueInput(ZUUserManager& UserManager, ZUMail& Mail, ZActivity* pActivity, BOOL LastActivity, BOOL UserAttribution, BOOL TimeAttribution, BOOL VisibilityAttribution, CWnd* pParent)
	: 	ZIWizardDialog(ZIActivityAttributionValueInput::IDD, // Dialog template
					   IDB_WZBMP1,	// Bitmap to display
					   0,			// Icon do display
					   0,					// Window Title
					   IDS_ATTRIBUTIONTITLE_WZ, // Wizard title
					   IDS_ATTRIBUTIONTEXTE_WZ	// Wizard text
					   ), 
		m_UserManager(UserManager), m_Mail(Mail), m_pActivity(pActivity),
		m_LastActivity(LastActivity),
		m_UserAttribution(UserAttribution),
		m_TimeAttribution(TimeAttribution),
		m_VisibilityAttribution(VisibilityAttribution)
		
{
	ASSERT( m_pActivity );
	//{{AFX_DATA_INIT(ZIActivityAttributionValueInput)
	m_ActivityName = "";
	m_TimeOutDays = 0;
	m_VisibilityType = -1;
	//}}AFX_DATA_INIT
}


void ZIActivityAttributionValueInput::CheckControlState()
{
	UpdateData();
	if (GetDlgItem(IDC_REMOVEUSER))
	   GetDlgItem(IDC_REMOVEUSER)->EnableWindow( m_UserList.GetCurSel() != LB_ERR );

	// Fonction of what is to imput
	if (GetDlgItem(IDC_ADDUSER))
	   GetDlgItem(IDC_ADDUSER)->EnableWindow( m_UserAttribution && m_VisibilityType != 1 );
	if (GetDlgItem(IDC_ADDEMAIL))
	   GetDlgItem(IDC_ADDEMAIL)->EnableWindow( m_UserAttribution && m_VisibilityType != 1 );
	if (GetDlgItem(IDC_USERLIST))
	   GetDlgItem(IDC_USERLIST)->EnableWindow( m_UserAttribution && m_VisibilityType != 1 );
	if (GetDlgItem(IDC_REMOVEUSER))
	   GetDlgItem(IDC_REMOVEUSER)->EnableWindow( m_UserAttribution && m_VisibilityType != 1 );

	if (GetDlgItem(IDC_TIMEOUT))
	   GetDlgItem(IDC_TIMEOUT)->EnableWindow( m_TimeAttribution && m_VisibilityType != 1 );

	   
}

void ZIActivityAttributionValueInput::DoDataExchange(CDataExchange* pDX)
{
	ZIWizardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZIActivityAttributionValueInput)
	DDX_Control(pDX, IDC_USERLIST, m_UserList);
	DDX_Text(pDX, IDC_ACTIVITYNAME, m_ActivityName);
	DDX_Text(pDX, IDC_TIMEOUT, m_TimeOutDays);
	DDX_Radio(pDX, IDC_VISIBILITYTYPE, m_VisibilityType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZIActivityAttributionValueInput, ZIWizardDialog)
	//{{AFX_MSG_MAP(ZIActivityAttributionValueInput)
	ON_BN_CLICKED(IDNEXT, OnNext)
	ON_BN_CLICKED(IDC_ADDUSER, OnAddUser)
	ON_BN_CLICKED(IDC_REMOVEUSER, OnDeleteUser)
	ON_LBN_SELCHANGE(IDC_USERLIST, OnSelChangeUserList)
	ON_BN_CLICKED(IDC_ADDEMAIL, OnAddEmail)
	ON_BN_CLICKED(IDC_VISIBILITYTYPE, OnVisibilityType)
	ON_BN_CLICKED(IDC_VISIBILITYTYPE2, OnVisibilityType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIActivityAttributionValueInput message handlers

BOOL ZIActivityAttributionValueInput::OnInitDialog()
{
	ZIWizardDialog::OnInitDialog();
	
	ASSERT( m_pActivity );
	m_ActivityName = m_pActivity->GetName();

	for (size_t i = 0; i < m_pActivity->GetUserCount(); ++i)
		m_UserList.AddString( m_pActivity->GetUserAt(i) );
	m_TimeOutDays = m_pActivity->GetDurationDays();

	// Set the visibility type
	switch (m_pActivity->GetIsVisible())
	{
		case TrueState:
		{
			m_VisibilityType = 0;
			break;
		}
		case FalseState:
		{
			m_VisibilityType = 1;
			break;
		}
		default : m_VisibilityType = -1;
	}
	// Propagate changes
	UpdateData( FALSE );

	// Disable the posibility to change the name		
	if (GetDlgItem(IDC_ACTIVITYNAME))
	   GetDlgItem(IDC_ACTIVITYNAME)->EnableWindow( FALSE );
	if (GetDlgItem(IDOK))
	   GetDlgItem(IDOK)->EnableWindow( m_LastActivity );
	if (GetDlgItem(IDNEXT))
	   GetDlgItem(IDNEXT)->EnableWindow( !m_LastActivity );

	if (GetDlgItem(IDC_VISIBILITYTYPE))
	   GetDlgItem(IDC_VISIBILITYTYPE)->EnableWindow( m_VisibilityAttribution );
	if (GetDlgItem(IDC_VISIBILITYTYPE2))
	   GetDlgItem(IDC_VISIBILITYTYPE2)->EnableWindow( m_VisibilityAttribution );

	CheckControlState();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void ZIActivityAttributionValueInput::OnAddUser()
{
	ZVChooseResources	ChooseResources( m_UserManager );
	
	if (ChooseResources.DoModal() == IDOK && !ChooseResources.GetUserListString().IsEmpty())
	{
		// Parse the user delimiter string
		ZBTokenizer	Tokenizer( ';' );
		CString	Token = Tokenizer.GetFirstToken( ChooseResources.GetUserListString() );
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

void ZIActivityAttributionValueInput::OnAddEmail()
{
	CString	Title;
	Title.LoadString( IDS_ENTER_EMAILADRESS );
	ZIInputValue	InputValue( Title );
			
	if (InputValue.DoModal() == IDOK)
	{
		// Check if not null and not already in the list
		if (m_UserList.FindString( -1, InputValue.GetValue() ) == LB_ERR)
			m_UserList.AddString( InputValue.GetValue() );
	}	
}

void ZIActivityAttributionValueInput::OnDeleteUser()
{
	int	iCurSel = m_UserList.GetCurSel();
	if (iCurSel != LB_ERR)
	{
		m_UserList.DeleteString( iCurSel );
	}	
	CheckControlState();
}

void ZIActivityAttributionValueInput::OnSelChangeUserList()
{
	CheckControlState();
}

void ZIActivityAttributionValueInput::SaveState()
{
	UpdateData();

	ASSERT( m_pActivity );
	m_pActivity->SetDurationDays( m_TimeOutDays );
	// Save data
	m_pActivity->RemoveAllUsers();

	CString	Text;
	for (int i = 0; i < m_UserList.GetCount(); ++i)
	{
		m_UserList.GetText( i, Text );
		m_pActivity->AddUser( Text );
	}
	// Sets the real state of the activity
	m_pActivity->SetVisibility( (m_VisibilityType == 0) ? TrueState : FalseState );
}


BOOL ZIActivityAttributionValueInput::CheckData()
{
	UpdateData();
	// User must sets the visibility
	if (m_VisibilityAttribution && m_VisibilityType == -1)
	{
		MsgBox		mbox;
		mbox.DisplayMsgBox( IDS_VISIBILITY_REQUIRED, MB_OK );
		return FALSE;
	}
	// If the user must attribute the visibility and he
	// has attributed invisible, do not check the other fields
	if (m_VisibilityAttribution && m_VisibilityType == 1)
	{
		return TRUE;
	}

	// Time must be defined
	if (m_TimeAttribution && m_TimeOutDays <= 0)
	{
		MsgBox		mbox;
		mbox.DisplayMsgBox( IDS_TIMEOUT_REQUIRED, MB_OK );
		return FALSE;
	}
	
	// User must be in the list
	if (m_UserAttribution && m_UserList.GetCount() <= 0)
	{
		MsgBox		mbox;
		mbox.DisplayMsgBox( IDS_ONEPERSON_REQUIRED, MB_OK );
		return FALSE;
	}
	return TRUE;
}


void ZIActivityAttributionValueInput::OnOK()
{
	if (!CheckData())
		return;
	SaveState();
	ZIWizardDialog::OnOK();
}



void ZIActivityAttributionValueInput::OnNext()
{
	if (!CheckData())
		return;
	SaveState();
	EndDialog( IDNEXT );
}




void ZIActivityAttributionValueInput::OnVisibilityType() 
{
	CheckControlState();
}
