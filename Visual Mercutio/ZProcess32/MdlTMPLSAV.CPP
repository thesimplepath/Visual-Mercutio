// MdlTmplSav.cpp : implementation file

#include "stdafx.h"
#include "MdlTmplSav.h"
#include "zBaseLib\MsgBox.h"

#include "zBaseLib\ZDirectory.h"
#include "zBaseLib\File.h"
#include "Resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 9 décembre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

BEGIN_MESSAGE_MAP( ZIModelTemplateCopyDlg, CDialog )
	//{{AFX_MSG_MAP(ZIModelTemplateCopyDlg)
	ON_EN_CHANGE(IDC_TITLE, OnChangeTitle)
	ON_BN_CLICKED(ID_DONTSAVE, OnDontSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIModelTemplateCopyDlg dialog

ZIModelTemplateCopyDlg::ZIModelTemplateCopyDlg( CString			FileExtension,
												const CString	Directory,
												ZDFolderStamp*	pFolderStamp,
												BOOL			AllowReplace	/*= FALSE*/,
												CWnd*			pParent			/*= NULL*/ )
	: ZIDialog			( ZIModelTemplateCopyDlg::IDD, TRUE, pParent ),
	  m_FileExtension	( FileExtension ),
	  m_Directory		( Directory ),
	  m_pFolderStamp	( pFolderStamp ),
	  m_AllowReplace	( AllowReplace ),
	  m_FileExist		( false )
{
	//{{AFX_DATA_INIT(ZIModelTemplateCopyDlg)
	m_sDescription	= _T( "" );
	m_sFilename		= _T( "" );
	m_sTitle		= _T( "" );
	//}}AFX_DATA_INIT

	if ( m_pFolderStamp )
	{
		m_sDescription = m_pFolderStamp->GetExplanation();

#ifdef _WIN32
		m_sFilename = m_pFolderStamp->GetTitle();
#endif
#ifndef _WIN32
		// In 16bit only 8 character for the filename
		m_sFilename = m_pFolderStamp->GetTitle().Left( 8 );
#endif

		m_sTitle = m_pFolderStamp->GetTitle();
	}

	m_ModelDirectory.SetSearchType( ZSEARCHEDIT_DIRECTORY, IDS_CHOOSEDIRECTORY, m_Directory );

	// If the directory is empty, use the current directory
	if ( m_Directory.IsEmpty() )
	{
		GetCurrentDirectory( 500, m_Directory.GetBuffer( 500 ) );
	}
}

void ZIModelTemplateCopyDlg::DoDataExchange( CDataExchange* pDX )
{
	ZIDialog::DoDataExchange( pDX );

	//{{AFX_DATA_MAP(ZIModelTemplateCopyDlg)
	DDX_Control(pDX, IDC_MODELDIR, m_ModelDirectory);
	DDX_Text(pDX, IDC_DESCRIPTION, m_sDescription);
	DDX_Text(pDX, IDC_FILENAME, m_sFilename);
	DDX_Text(pDX, IDC_TITLE, m_sTitle);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZIModelTemplateCopyDlg message handlers

void ZIModelTemplateCopyDlg::OnOK()
{
	UpdateData( TRUE );
	
	m_ModelDirectory.GetWindowText( m_Directory );
	m_Directory = ZDirectory::NormalizeDirectory( m_Directory );

	if ( m_Directory.IsEmpty() )
	{
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_DIRECTORY_MISSING, MB_OK );
		return;
	}

	if ( m_sFilename.IsEmpty() )
	{
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_FILENAMEMISSING, MB_OK );
		return;
	}

	if ( m_sTitle.IsEmpty() )
	{
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_TITLEMISSING, MB_OK );
		return;
	}

	// Check if normal template is specified
	if ( m_sFilename + _T( "." ) + m_FileExtension == sNormalModelTemplateFilename )
	{
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_NORMALTMPL_CANNOTBEUSED, MB_OK );
		return;
	}

#ifndef _WIN32
	if ( m_sFilename.GetLength() > 8 || m_sFilename.Find( '.' ) != -1 )
#endif
#ifdef _WIN32
	if ( m_sFilename.Find( '.' ) != -1 )
#endif
	{
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_TEMPLATEFILENAMEERROR, MB_OK );
		return;
	}

	// Build the complete filename to know if already exist
	CString sFile = m_Directory + _T( "\\" ) + m_sFilename + _T( "." ) + m_FileExtension;
	CFileStatus status;

	if ( CFile::GetStatus( sFile, status ) )
	{
		// If does not allow replacement of file
		// error message and return
		MsgBox mbox;

		if ( !m_AllowReplace )
		{
			mbox.DisplayMsgBox( IDS_FORMALREADYEXIST, MB_OK );
			return;
		}

		if ( mbox.DisplayMsgBox( IDS_FORMALREADYEXIST_CONTREPLACE, MB_YESNO ) == IDNO )
		{
			return;
		}

		// Set the flag for file chosen exists
		m_FileExist = true;
	}

	// Add the extension
	m_sFilename = sFile;
	UpdateData( FALSE );
	CDialog::OnOK();
}

BOOL ZIModelTemplateCopyDlg::OnInitDialog()
{
	ZIDialog::OnInitDialog();

	m_ModelDirectory.SetWindowText( m_Directory );

	// return TRUE unless you set the focus to a control
	return TRUE;
}

void ZIModelTemplateCopyDlg::OnChangeTitle()
{
	// If this is a RICHEDIT control, the control will not
	// send this notification unless you override the ZIDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// Trap input and change the filename
	UpdateData( TRUE );

#ifndef _WIN32
	// In 16bit only copy 8 character of the title
	m_sFilename = m_sTitle.Left( 8 );
#endif
#ifdef _WIN32
	m_sFilename = m_sTitle;
#endif

	UpdateData( FALSE );
}

void ZIModelTemplateCopyDlg::OnDontSave()
{
	ZIDialog::EndDialog( ID_DONTSAVE );
}
