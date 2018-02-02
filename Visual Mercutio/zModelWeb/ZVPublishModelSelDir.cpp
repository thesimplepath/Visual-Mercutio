// ZVPublishModelSelDir.cpp : implementation file

#include "stdafx.h"
#include "ZVPublishModelSelDir.h"

#include "zBaseLib\ZDirectory.h"
#include "zRes32\zRes.h"
#include "zBaseLib\MsgBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 8 août 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelSelectDirectory dialog

BEGIN_MESSAGE_MAP( ZVPublishModelSelectDirectory, ZIWizardDialog )
	//{{AFX_MSG_MAP(ZVPublishModelSelectDirectory)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEOFDIRECTORY, OnSelchangedDirectory)
	ON_NOTIFY(NM_DBLCLK, IDC_TREEOFDIRECTORY, OnDblclkDirectory)
	ON_NOTIFY(NM_CLICK, IDC_TREEOFDIRECTORY, OnClickDirectory)
	ON_EN_CHANGE(IDC_DIRECTORYCHOOSED, OnChangeServerChoosed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVPublishModelSelectDirectory::ZVPublishModelSelectDirectory( CString		LastPathName	/*= _T( "" )*/,
															  CStringArray*	pArrayOfAddress	/*= NULL*/,
															  CWnd*			pParent			/*= NULL*/ )
	: ZIWizardDialog	( ZVPublishModelSelectDirectory::IDD, // Dialog template
						  IDB_WZBMP1,					// Bitmap to display
						  0,							// Icon do display
						  0,							// Window Title
						  IDS_PUBLISHMODELSELDIR_S,		// Wizard title
						  IDS_PUBLISHMODELSELDIR_T ),	// Wizard text
	m_Directory			( LastPathName ),
	m_pArrayOfAddress	( pArrayOfAddress )
{
	//{{AFX_DATA_INIT(ZVPublishModelSelectDirectory)
	//}}AFX_DATA_INIT
}

void ZVPublishModelSelectDirectory::DoDataExchange( CDataExchange* pDX )
{
	ZIWizardDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP(ZVPublishModelSelectDirectory)
	DDX_Control(pDX, IDC_TREEOFDIRECTORY, m_DirTreeCtrl);
	DDX_Control(pDX, IDC_DIRECTORYCHOOSED, m_cbDirectory);
	//}}AFX_DATA_MAP
}

void ZVPublishModelSelectDirectory::CheckControlStates()
{
	UpdateData();

	if ( GetDlgItem( IDOK ) )
	{
		m_cbDirectory.GetWindowText( m_Directory );
		GetDlgItem( IDOK )->EnableWindow( !m_DirTreeCtrl.GetSelectedDirectory().IsEmpty() || !m_Directory.IsEmpty() );
	}
}

void ZVPublishModelSelectDirectory::ReflectChangedDirectory()
{
	CheckControlStates();

	if ( m_DirTreeCtrl.IsValid() )
	{
		m_Directory = m_DirTreeCtrl.GetSelectedDirectory();
		m_cbDirectory.SetWindowText( m_Directory );
	}
}

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelSelectDirectory message handlers

BOOL ZVPublishModelSelectDirectory::OnInitDialog()
{
	ZIWizardDialog::OnInitDialog();
	
	// Initialize the directory tree control
	m_DirTreeCtrl.Initialize();

	// Load the address edit
	m_cbDirectory.Initialize( m_pArrayOfAddress );
	m_cbDirectory.SetWindowText( m_Directory );

	CheckControlStates();
	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}

void ZVPublishModelSelectDirectory::OnSelchangedDirectory( NMHDR* pNMHDR, LRESULT* pResult )
{
	ReflectChangedDirectory();
	*pResult = 0;
}

void ZVPublishModelSelectDirectory::OnDblclkDirectory( NMHDR* pNMHDR, LRESULT* pResult )
{
	ReflectChangedDirectory();
	*pResult = 0;
}

void ZVPublishModelSelectDirectory::OnClickDirectory( NMHDR* pNMHDR, LRESULT* pResult )
{
	ReflectChangedDirectory();
	*pResult = 0;
}

void ZVPublishModelSelectDirectory::OnChangeServerChoosed()
{
	CheckControlStates();
}

void ZVPublishModelSelectDirectory::OnOK()
{
	UpdateData( TRUE );
	m_cbDirectory.GetWindowText( m_Directory );

	if ( !ZDirectory::Exist( m_Directory ) )
	{
		// Asks the user to create the directory
		MsgBox mbox;

		if ( mbox.DisplayMsgBox( IDS_DIR_NEEDCREATE, MB_YESNO ) == IDNO )
		{
			return;
		}

		// Then, try to create it
		ZDirectory::CreateDirectory( m_Directory );

		// If is still not created, error message
		if ( !ZDirectory::Exist( m_Directory ) )
		{
			MsgBox mbox;
			mbox.DisplayMsgBox( IDS_DIR_FAILCREATE, MB_OK );
			return;
		}
	}

	ZIWizardDialog::OnOK();
}
