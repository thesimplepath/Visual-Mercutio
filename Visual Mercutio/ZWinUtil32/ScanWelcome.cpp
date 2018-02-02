// ScanWelcome.cpp : implementation file
//

#include "stdafx.h"
#include "ScanWelcome.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIScanWelcome dialog


ZIScanWelcome::ZIScanWelcome(CWnd* pParent /*=NULL*/)
	: ZIWizardDialog(ZIScanWelcome::IDD, // Dialog template
					 IDB_WZBMP3,	// Bitmap to display
					 0,			// Icon do display
					 0,					// Window Title
					 IDS_SCANNINGWLC_S,	// Wizard title
					 IDS_SCANNINGWLC_T	// Wizard text
					)
{
	//{{AFX_DATA_INIT(ZIScanWelcome)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ZIScanWelcome::DoDataExchange(CDataExchange* pDX)
{
	ZIWizardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZIScanWelcome)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIScanWelcome, ZIWizardDialog)
	//{{AFX_MSG_MAP(ZIScanWelcome)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIScanWelcome message handlers

BOOL ZIScanWelcome::OnInitDialog() 
{
	ZIWizardDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

