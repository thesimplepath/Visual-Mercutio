// ZVChooseResources.cpp : implementation file
//

#include "stdafx.h"
#include "ZVChooseResources.h"
#include "zBaseLib\MsgBox.h"

#include "zBaseLib\ZBTokenizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVChooseResources dialog


ZVChooseResources::ZVChooseResources(ZUUserManager& UserManager, CWnd* pParent /*=NULL*/)
	: ZIDialog(ZVChooseResources::IDD, TRUE, pParent), 
	m_UserManager(UserManager)
{
	//{{AFX_DATA_INIT(ZVChooseResources)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ZVChooseResources::DoDataExchange(CDataExchange* pDX)
{
	ZIDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZVChooseResources)
	DDX_Control(pDX, IDC_RESOURCE_TREE, m_ResourceTree);
	DDX_Control(pDX, IDC_RESOURCE_LIST, m_ResourceList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVChooseResources, ZIDialog)
	//{{AFX_MSG_MAP(ZVChooseResources)
	ON_BN_CLICKED(IDC_ADDRESOURCE, OnAddResource)
	ON_BN_CLICKED(IDC_REMOVERESOURCE, OnRemoveResource)
	ON_NOTIFY(TVN_SELCHANGED, IDC_RESOURCE_TREE, OnSelchangedResourceTree)
	ON_LBN_SELCHANGE(IDC_RESOURCE_LIST, OnSelchangeResourceList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ZVChooseResources::CheckControlState()
{
	if (GetDlgItem(IDC_ADDRESOURCE))
	   GetDlgItem(IDC_ADDRESOURCE)->EnableWindow( m_ResourceTree.GetSelectedUser() != NULL );
	if (GetDlgItem(IDC_REMOVERESOURCE))
	   GetDlgItem(IDC_REMOVERESOURCE)->EnableWindow( m_ResourceList.GetCurSel() != LB_ERR );
}



/////////////////////////////////////////////////////////////////////////////
// ZVChooseResources message handlers

void ZVChooseResources::OnAddResource() 
{
	// Check if not null and not already in the list
	if (m_ResourceTree.GetSelectedUser() && m_ResourceList.FindString( -1, m_ResourceTree.GetSelectedUser()->GetUserName() ) == LB_ERR)
		m_ResourceList.AddString( m_ResourceTree.GetSelectedUser()->GetUserName() );

	CheckControlState();
}

void ZVChooseResources::OnRemoveResource() 
{
	int	CurSel = m_ResourceList.GetCurSel();
	if (CurSel != LB_ERR)
	{
		m_ResourceList.DeleteString( CurSel );
	}
	CheckControlState();
	
}

void ZVChooseResources::OnOK() 
{
	int	Count = m_ResourceList.GetCount();
	if (Count <= 0)
	{
		// Display warning message
		MsgBox		mbox;
		if (mbox.DisplayMsgBox( IDS_LISTOFUSEREMPTY_CONTINUE, MB_YESNO ) == IDNO)
			return;
	}

	CString Text;
	m_UserListString.Empty();

	// Build the string of users
	ZBTokenizer	Tokenizer( ';' );
	for (int Index = 0; Index < Count; ++Index)
	{
		m_ResourceList.GetText( Index, Text );
		Tokenizer.AddToken( Text );
	}
	m_UserListString = Tokenizer.GetString();

	ZIDialog::OnOK();
}

BOOL ZVChooseResources::OnInitDialog() 
{
	ZIDialog::OnInitDialog();
	
	m_ResourceTree.Initialize( &m_UserManager );
	CheckControlState();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVChooseResources::OnSelchangedResourceTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	CheckControlState();
	
	*pResult = 0;
}

void ZVChooseResources::OnSelchangeResourceList() 
{
	CheckControlState();
}
