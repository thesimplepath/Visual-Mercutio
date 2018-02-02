// foldinfo.cpp : implementation file
//

#include "stdafx.h"
#include "FoldInfo.h"

#include "zBaseLib\MsgBox.h"
#include "zRes32\Zres.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIFolderInformation dialog


ZIFolderInformation::ZIFolderInformation(ZDFolderStamp* pFolderStamp, BOOL ReadOnly, CWnd* pParent /*=NULL*/)
	: ZIDialog(ZIFolderInformation::IDD, TRUE, pParent), 
	  m_pFolderStamp(pFolderStamp), m_ReadOnly(ReadOnly)
{
	//{{AFX_DATA_INIT(ZIFolderInformation)
	//}}AFX_DATA_INIT
	if (m_pFolderStamp)
	{
		m_FolderDescription = m_pFolderStamp->GetFolderDescription();
		m_FolderName = m_pFolderStamp->GetFolderName();
	}
}

void ZIFolderInformation::DoDataExchange(CDataExchange* pDX)
{
	ZIDialog::DoDataExchange(pDX);
#ifdef _WIN32
	DDX_Control(pDX, IDC_LIST_INFORMATION, m_ListInformation);
#endif
	//{{AFX_DATA_MAP(ZIFolderInformation)
	DDX_Text(pDX, IDC_FOLDERDESCRIPTION, m_FolderDescription);
	DDX_Text(pDX, IDC_FOLDERNAME, m_FolderName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZIFolderInformation, ZIDialog)
	//{{AFX_MSG_MAP(ZIFolderInformation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIFolderInformation message handlers

void ZIFolderInformation::OnOK()
{
	UpdateData();
	
	if (!m_ReadOnly)
	{
//		if (m_FolderName.IsEmpty())
//		{
//			MsgBox		mbox;
//			mbox.DisplayMsgBox( IDS_NO_FOLDERNAME, MB_OK );
//			return;
//		}
		
		if (m_pFolderStamp)
		{
			m_pFolderStamp->SetFolderDescription( m_FolderDescription );
			m_pFolderStamp->SetFolderName( m_FolderName );
		}
	}	
	ZIDialog::OnOK();
}

BOOL ZIFolderInformation::OnInitDialog() 
{
	ZIDialog::OnInitDialog();
	
	if (m_ReadOnly)
	{
		if (GetDlgItem(IDC_FOLDERNAME))
			GetDlgItem(IDC_FOLDERNAME)->EnableWindow( FALSE );
		if (GetDlgItem(IDC_FOLDERDESCRIPTION))
			GetDlgItem(IDC_FOLDERDESCRIPTION)->EnableWindow( FALSE );
		if (GetDlgItem(IDCANCEL))
			GetDlgItem(IDCANCEL)->ShowWindow( SW_HIDE );
		if (GetDlgItem(IDOK))
		{
			CString	Title;
			Title.LoadString( IDS_CLOSE_TEXT );
			GetDlgItem(IDOK)->SetWindowText( Title );
		}
	}
#ifdef _WIN32
	 
	m_ListInformation.Initialize( m_pFolderStamp, FALSE, !m_ReadOnly );
#endif
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
