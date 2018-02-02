// SelProcC.cpp : implementation file
//

#include "stdafx.h"
#include "SelProcC.h"
#include "zBaseLib\MsgBox.h"
#include "zRes32\Zres.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZISelectProcessWizardChoose dialog


ZISelectProcessWizardChoose::ZISelectProcessWizardChoose(ZProcess& Process, CWnd* pParent /*=NULL*/)
	: ZIWizardDialog(ZISelectProcessWizardChoose::IDD, // Dialog template
					 IDB_WZBMP1,	// Bitmap to display
					 0,			// Icon do display
					 0,					// Window Title
					 IDS_SELECTIONPROCESSCS_S, // Wizard title
					 IDS_SELECTIONPROCESSCS_T	// Wizard text
					),
	  m_Process(Process)
{
	//{{AFX_DATA_INIT(ZISelectProcessWizardChoose)
	m_ProcessName = _T(m_Process.GetName());
	//}}AFX_DATA_INIT
}


void ZISelectProcessWizardChoose::DoDataExchange(CDataExchange* pDX)
{
	ZIWizardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZISelectProcessWizardChoose)
	DDX_Control(pDX, IDC_ACTIVITYPROC_LIST, m_ActivityProcList);
	DDX_Text(pDX, IDC_PROCESSNAME, m_ProcessName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZISelectProcessWizardChoose, ZIWizardDialog)
	//{{AFX_MSG_MAP(ZISelectProcessWizardChoose)
	ON_NOTIFY(NM_CLICK, IDC_ACTIVITYPROC_LIST, OnClickActivityProcList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ZISelectProcessWizardChoose::CheckControlStates()
{
	if (GetDlgItem(IDOK))
	   GetDlgItem(IDOK)->EnableWindow( !m_ActivityProcList.GetSelectedActivity().IsEmpty() );
}

/////////////////////////////////////////////////////////////////////////////
// ZISelectProcessWizardChoose message handlers

void ZISelectProcessWizardChoose::OnOK() 
{
	UpdateData();

	// Assign the activity name selected
	m_BaseActivityName = m_ActivityProcList.GetSelectedActivity();

	ZIWizardDialog::OnOK();
}

BOOL ZISelectProcessWizardChoose::OnInitDialog() 
{
	ZIWizardDialog::OnInitDialog();
	
	m_ActivityProcList.Initialize( &m_Process );

	CheckControlStates();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void ZISelectProcessWizardChoose::OnClickActivityProcList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CheckControlStates();
	
	*pResult = 0;
}
