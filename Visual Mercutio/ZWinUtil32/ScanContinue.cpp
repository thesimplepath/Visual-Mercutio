// ScanContinue.cpp : implementation file
//

#include "stdafx.h"
#include "ScanContinue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIScanContinueSelect dialog


ZIScanContinueSelect::ZIScanContinueSelect(bool FirstTime, CWnd* pParent /*=NULL*/)
	: ZIWizardDialog(ZIScanContinueSelect::IDD, // Dialog template
					 IDB_WZBMP3,	// Bitmap to display
					 0,			// Icon do display
					 0,					// Window Title
					 IDS_SCANNINGSELECT_S,	// Wizard title
					 IDS_SCANNINGSELECT_T	// Wizard text
					),
	m_FirstTime(FirstTime)
{
	//{{AFX_DATA_INIT(ZIScanContinueSelect)
	m_ScanType = 1;
	//}}AFX_DATA_INIT
	m_File.SetSearchType( ZSEARCHEDIT_FILE, _T("") );
}


void ZIScanContinueSelect::DoDataExchange(CDataExchange* pDX)
{
	ZIWizardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZIScanContinueSelect)
	DDX_Control(pDX, IDC_FILE_SCAN, m_File);
	DDX_Radio(pDX, IDC_SCAN_TYPE, m_ScanType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIScanContinueSelect, ZIWizardDialog)
	//{{AFX_MSG_MAP(ZIScanContinueSelect)
	ON_BN_CLICKED(IDCONTINUE, OnContinue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIScanContinueSelect message handlers

BOOL ZIScanContinueSelect::OnInitDialog() 
{
	ZIWizardDialog::OnInitDialog();
	
	if (m_FirstTime)
	{
		if (GetDlgItem(IDOK))
			GetDlgItem(IDOK)->ShowWindow( SW_HIDE );
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ZIScanContinueSelect::OnContinue() 
{
	CString	Filename;
	m_File.GetWindowText( Filename );
	if (Filename.IsEmpty())
	{
		return;
	}
	// Assign the new filename
	m_CompleteFilename = Filename;
	// Ok to continue
	EndDialog( IDCONTINUE );	
}
