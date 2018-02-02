// ZVWorkspaceRenameGroupNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVWorkspaceRenameGroupNameDlg.h"

#include "ZBWorkspaceGroupEntity.h"

#include "MsgBox.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceRenameGroupNameDlg dialog


ZVWorkspaceRenameGroupNameDlg::ZVWorkspaceRenameGroupNameDlg(const CString GroupName, ZBWorkspaceGroupEntity* pParentGroup /*= NULL*/, CWnd* pParent /*=NULL*/)
	: CDialog(ZVWorkspaceRenameGroupNameDlg::IDD, pParent),
	  m_pParentGroup(pParentGroup)
{
	//{{AFX_DATA_INIT(ZVWorkspaceRenameGroupNameDlg)
	m_GroupName = GroupName;
	//}}AFX_DATA_INIT
}


void ZVWorkspaceRenameGroupNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZVWorkspaceRenameGroupNameDlg)
	DDX_Text(pDX, IDC_WKS_GROUPNAME, m_GroupName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVWorkspaceRenameGroupNameDlg, CDialog)
	//{{AFX_MSG_MAP(ZVWorkspaceRenameGroupNameDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceRenameGroupNameDlg message handlers

void ZVWorkspaceRenameGroupNameDlg::OnOK() 
{
	UpdateData( TRUE );
	if (m_pParentGroup && m_pParentGroup->GroupExist( m_GroupName ))
	{
		// Already exists
		MsgBox		mbox;
		mbox.DisplayMsgBox( IDS_WKS_GROUP_ALREADYEXIST, MB_OK );
		return;
	}
	
	CDialog::OnOK();
}

BOOL ZVWorkspaceRenameGroupNameDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
