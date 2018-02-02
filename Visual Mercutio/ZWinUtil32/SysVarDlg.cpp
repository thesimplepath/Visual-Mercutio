// SysVarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SysVarDlg.h"
#include "SysVar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const	char*	Symbol[] =
{
	szToday,
	szFilename,
	szExchFilename,
	szProcExchFilename,
	szAuthor,
	szModifier,
	szCreationDate,
	szModificationDate,
	szPublishDate,
	szFileVer,
	NULL
};

const	UINT	SymbolID[] =
{
	IDS_TODAY_SYSVAR,
	IDS_FILENAME_SYSVAR,
	IDS_EXCHFILENAME_SYSVAR,
	IDS_PROCEXCHFILENAME_SYSVAR,
	IDS_AUTHOR_SYSVAR,
	IDS_MODIFIER_SYSVAR,
	IDS_CREATIONDATE_SYSVAR,
	IDS_MODIFICATIONDATE_SYSVAR,
	IDS_PUBLISHDATE_SYSVAR,
	IDS_FILEVER_SYSVAR,
	0
};

/////////////////////////////////////////////////////////////////////////////
// ZISysVarDlg dialog


ZISysVarDlg::ZISysVarDlg(CWnd* pParent /*=NULL*/)
	: ZIDialog(ZISysVarDlg::IDD, TRUE, pParent)
{
	//{{AFX_DATA_INIT(ZISysVarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ZISysVarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZISysVarDlg)
	DDX_Control(pDX, IDC_SYSTEMVARLIST, m_SysVarList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZISysVarDlg, ZIDialog)
	//{{AFX_MSG_MAP(ZISysVarDlg)
	ON_LBN_SELCHANGE(IDC_SYSTEMVARLIST, OnSelchangeSystemVarlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZISysVarDlg message handlers

BOOL ZISysVarDlg::OnInitDialog() 
{
	ZIDialog::OnInitDialog();
	
	size_t	Index = 0;
	while (SymbolID[Index] != 0)
	{
		CString	Text;
		Text.LoadString( SymbolID[Index++] );
		m_SysVarList.AddString( Text );
	}
	if (GetDlgItem(IDOK))
		GetDlgItem(IDOK)->EnableWindow( FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ZISysVarDlg::OnOK() 
{
	int	CurSel = m_SysVarList.GetCurSel();
	if (CurSel != LB_ERR)
	{
		m_Keyword = Symbol[CurSel];
	}
	ZIDialog::OnOK();
}

void ZISysVarDlg::OnSelchangeSystemVarlist() 
{
	if (GetDlgItem(IDOK))
		GetDlgItem(IDOK)->EnableWindow( m_SysVarList.GetCurSel() != LB_ERR );
	
}
