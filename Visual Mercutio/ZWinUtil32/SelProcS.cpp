// SelProcS.cpp : implementation file
//

#include "stdafx.h"
#include "SelProcS.h"
#include "zBaseLib\MsgBox.h"
#include "zRes32\Zres.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZISelectProcessWizardStart dialog


ZISelectProcessWizardStart::ZISelectProcessWizardStart(CString ProcessName, CWnd* pParent /*=NULL*/)
	: ZIWizardDialog(ZISelectProcessWizardStart::IDD, // Dialog template
					 IDB_WZBMP1,	// Bitmap to display
					 0,			// Icon do display
					 0,					// Window Title
					 IDS_SELECTIONPROCESSST_S,	// Wizard title
					 IDS_SELECTIONPROCESSST_T	// Wizard text
					)
{
	//{{AFX_DATA_INIT(ZISelectProcessWizardStart)
	m_ProcessName = _T(ProcessName);
	//}}AFX_DATA_INIT
}


void ZISelectProcessWizardStart::DoDataExchange(CDataExchange* pDX)
{
	ZIWizardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZISelectProcessWizardStart)
	DDX_Text(pDX, IDC_PROCESSNAME, m_ProcessName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZISelectProcessWizardStart, ZIWizardDialog)
	//{{AFX_MSG_MAP(ZISelectProcessWizardStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZISelectProcessWizardStart message handlers

