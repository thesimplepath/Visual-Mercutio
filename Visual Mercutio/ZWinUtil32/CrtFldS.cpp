// CrtFldS.cpp : implementation file
//

#include "stdafx.h"
#include "CrtFldS.h"
#include "zBaseLib\MsgBox.h"
#include "zRes32\Zres.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZICreateFolderWizardStart dialog


ZICreateFolderWizardStart::ZICreateFolderWizardStart(BOOL UseFolderNameAsFilename, CString FolderDirectory, CString FolderName, CString FolderDescription, CString InitialFilename, CString FileExtension, CWnd* pParent /*=NULL*/)
    : ZIWizardDialog(ZICreateFolderWizardStart::IDD, // Dialog template
                     IDB_WZBMP1,    // Bitmap to display
                     0,            // Icon do display
                     0,                    // Window Title
                     IDS_CREATEFOLDERST_S, // Wizard title
                     IDS_CREATEFOLDERST_T    // Wizard text
                    ),
    m_UseFolderNameAsFilename(UseFolderNameAsFilename),
    m_FolderDirectory(FolderDirectory),
    m_InitialFilename(InitialFilename),
    m_FileExtension(FileExtension)
{
    //{{AFX_DATA_INIT(ZICreateFolderWizardStart)
    m_FolderComment = _T(FolderDescription);
    m_FolderName = _T(FolderName);
    //}}AFX_DATA_INIT
    m_CompleteFilename.SetSearchType( ZSEARCHEDIT_FILE, IDS_CHOOSEFILENAMEFORFOLDER, m_FolderDirectory, "", 0 );
    GetCurrentDirectory( _MAX_DIR - 1, m_szDir );
    // If the last char of the directory is not a backslash, add one
    if (m_FolderDirectory.GetAt( m_FolderDirectory.GetLength()-1 ) != '\\')
        m_FolderDirectory += '\\';
}


void ZICreateFolderWizardStart::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZICreateFolderWizardStart)
    DDX_Control(pDX, IDC_COMPLETEFILENAME, m_CompleteFilename);
    DDX_Text(pDX, IDC_FOLDERCOMMENT, m_FolderComment);
    DDX_Text(pDX, IDC_FOLDERFILENAME, m_FolderName);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZICreateFolderWizardStart, ZIWizardDialog)
    //{{AFX_MSG_MAP(ZICreateFolderWizardStart)
    ON_EN_CHANGE(IDC_FOLDERFILENAME, OnChangeFolderName)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZICreateFolderWizardStart message handlers

void ZICreateFolderWizardStart::OnOK() 
{
    UpdateData();
    // Folder name required
    if (m_FolderName.IsEmpty())
    {
        MsgBox        mbox;
        mbox.DisplayMsgBox( IDS_NO_FOLDERNAME, MB_OK );
        return;
    }

    // If not automatic foldername, a filename is necessary
    if (!m_UseFolderNameAsFilename && m_Filename.IsEmpty())
    {
        m_CompleteFilename.GetWindowText( m_Filename );
        if (m_Filename.IsEmpty())
        {
            MsgBox        mbox;
            mbox.DisplayMsgBox( IDS_FILENAMEMISSING, MB_OK );
            return;
        }
    }

    ZIWizardDialog::OnOK();
}

BOOL ZICreateFolderWizardStart::OnInitDialog() 
{
    ZIWizardDialog::OnInitDialog();
    
    // show or hide file control. Depends on use foldername as file
    m_CompleteFilename.ShowWindow( (m_UseFolderNameAsFilename) ? SW_HIDE : SW_SHOW );
    if (GetDlgItem(IDC_FILE_TEXT))
       GetDlgItem(IDC_FILE_TEXT)->ShowWindow( (m_UseFolderNameAsFilename) ? SW_HIDE : SW_SHOW );

    if (m_InitialFilename.IsEmpty())
    {
        if (m_FolderDirectory.IsEmpty())
            m_CompleteFilename.SetWindowText( m_szDir );
        else
            m_CompleteFilename.SetWindowText( m_FolderDirectory );
    }
    else
        m_CompleteFilename.SetWindowText( m_InitialFilename );
        

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void ZICreateFolderWizardStart::OnChangeFolderName() 
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the ZIWizardDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.
    
    UpdateData();

    // Not automatic
    if (!m_UseFolderNameAsFilename)    
    {
        CString    Filename;
        m_CompleteFilename.GetWindowText( Filename );

        char         drive[_MAX_DRIVE];
        char         dir[_MAX_DIR];
        char         fname[_MAX_FNAME];
        char         ext[_MAX_EXT];
        _splitpath( (const char*)Filename, drive, dir, fname, ext );

        if (m_FolderName.IsEmpty())
        {
            m_CompleteFilename.SetWindowText( CString(drive) + dir );
        }
        else
        {
            CString CompleteFilename = CString(drive) + dir + m_FolderName + "." + m_FileExtension;
            m_CompleteFilename.SetWindowText( CompleteFilename );
        }

    }
}

