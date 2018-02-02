// rejact.cpp : implementation file
//

#include "stdafx.h"
#include "RejAct.h"
#include "zBaseLib\MsgBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIRejectActivityInput dialog


ZIRejectActivityInput::ZIRejectActivityInput(CStringArray* pArray, CWnd* pParent /*=NULL*/)
	: ZIDialog(ZIRejectActivityInput::IDD, TRUE, pParent), m_pArray(pArray)
{
	//{{AFX_DATA_INIT(ZIRejectActivityInput)
	m_RejectText = "";
	//}}AFX_DATA_INIT
}

void ZIRejectActivityInput::DoDataExchange(CDataExchange* pDX)
{
	ZIDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZIRejectActivityInput)
	DDX_Control(pDX, IDC_REJECTCATEGORY, m_RejectCategory);
	DDX_Text(pDX, IDC_REJECT_TEXT, m_RejectText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZIRejectActivityInput, ZIDialog)
	//{{AFX_MSG_MAP(ZIRejectActivityInput)
	ON_CBN_SELCHANGE(IDC_REJECTCATEGORY, OnSelChangeRejectCategory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIRejectActivityInput message handlers

void ZIRejectActivityInput::OnSelChangeRejectCategory() 
{
	CheckControlStates();
}

void ZIRejectActivityInput::CheckControlStates() 
{
	CString	SelectedText;
	int	CurSel = m_RejectCategory.GetCurSel();
	if (CurSel != CB_ERR)
	{
		m_RejectCategory.GetLBText( CurSel, SelectedText );
		if (m_OwnerText == SelectedText)
		{
			if (GetDlgItem(IDC_REJECT_TEXT))
			   GetDlgItem(IDC_REJECT_TEXT)->ShowWindow( SW_SHOW );
		}
		else
		{
			if (GetDlgItem(IDC_REJECT_TEXT))
			   GetDlgItem(IDC_REJECT_TEXT)->ShowWindow( SW_HIDE );
		}
	}
}

BOOL ZIRejectActivityInput::OnInitDialog() 
{
	ZIDialog::OnInitDialog();
	if (m_pArray)
	{
		for (int i = 0; i < m_pArray->GetSize(); ++i)
			m_RejectCategory.AddString( m_pArray->GetAt(i) );
	}
	// Add the owner user text at the last position
	m_OwnerText.LoadString( IDS_SELFTEXT_REJECTCATEGORY );
	m_RejectCategory.AddString( m_OwnerText );

	m_RejectCategory.SetCurSel( 0 );
	CheckControlStates();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void ZIRejectActivityInput::OnOK()
{
	UpdateData( TRUE );

	// First, save text if necessary
	CString	SelectedText;
	int		CurSel = m_RejectCategory.GetCurSel();

	if (CurSel != CB_ERR)
	{
		m_RejectCategory.GetLBText( CurSel, SelectedText );
		// If different of owner user text, assigns the 
		if (SelectedText != m_OwnerText)
			m_RejectText = SelectedText;
	}

	if (m_RejectText.IsEmpty())
	{
		// Asks the user if he wants to insert it from the central repository.
		MsgBox		mbox;
		if (mbox.DisplayMsgBox( IDS_REJECTTEXTEMPTY, MB_YESNO ) == IDNO)
			return;
	}
	// And now assigns value back, otherwise, OnOK from CDialog will scrap changes
	UpdateData( FALSE );

	CDialog::OnOK();
}