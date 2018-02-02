// ZVInputURLDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ZVInputURLDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVInputURLDialog dialog


ZVInputURLDialog::ZVInputURLDialog(const CString URL /*= ""*/, CWnd* pParent /*=NULL*/)
	: CDialog(ZVInputURLDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ZVInputURLDialog)
	m_URL = URL;
	//}}AFX_DATA_INIT
}


void ZVInputURLDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZVInputURLDialog)
	DDX_Text(pDX, IDC_URL, m_URL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVInputURLDialog, CDialog)
	//{{AFX_MSG_MAP(ZVInputURLDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVInputURLDialog message handlers
