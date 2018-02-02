// ZFileVersionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ZFileVersionDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZFileVersionDialog dialog


ZFileVersionDialog::ZFileVersionDialog(long FileVersion, CWnd* pParent /*=NULL*/)
	: ZIDialog(ZFileVersionDialog::IDD, TRUE, pParent)
{
	//{{AFX_DATA_INIT(ZFileVersionDialog)
	m_FileVersion = FileVersion;
	//}}AFX_DATA_INIT
}


void ZFileVersionDialog::DoDataExchange(CDataExchange* pDX)
{
	ZIDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZFileVersionDialog)
	DDX_Control(pDX, IDC_FILEVERSION_SPIN, m_FileVersionSpin);
	DDX_Text(pDX, IDC_FILEVERSION, m_FileVersion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZFileVersionDialog, ZIDialog)
	//{{AFX_MSG_MAP(ZFileVersionDialog)
	ON_NOTIFY(UDN_DELTAPOS, IDC_FILEVERSION_SPIN, OnDeltaposFileversionSpin)
	ON_EN_CHANGE(IDC_FILEVERSION, OnChangeFileVersion)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZFileVersionDialog message handlers

BOOL ZFileVersionDialog::OnInitDialog() 
{
	ZIDialog::OnInitDialog();
	
	m_FileVersionSpin.SetRange( 0, UD_MAXVAL );
//	m_FileVersionSpin.SetRange32( 0, 32767 );
	m_FileVersionSpin.SetPos( m_FileVersion );
	if (GetDlgItem(IDC_FILEVERSION))
		m_FileVersionSpin.SetBuddy( GetDlgItem(IDC_FILEVERSION) );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ZFileVersionDialog::OnDeltaposFileversionSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_FileVersion = m_FileVersionSpin.GetPos() & 0x0000FFFF;
	UpdateData( FALSE );

	*pResult = 0;
}

void ZFileVersionDialog::OnChangeFileVersion() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the ZIDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData();
	m_FileVersionSpin.SetPos( m_FileVersion );
}
