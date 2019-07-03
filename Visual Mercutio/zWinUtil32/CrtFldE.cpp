// CrtFldE.cpp : implementation file
//

#include "stdafx.h"
#include "CrtFldE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZICreateFolderWizardExist dialog


ZICreateFolderWizardExist::ZICreateFolderWizardExist(CString FolderName, CString FileDirectory, CString InitialFilename, FldExistInitialChoice InitialChoice, CWnd* pParent /*=NULL*/)
    : ZIWizardDialog(ZICreateFolderWizardExist::IDD, // Dialog template
                     IDB_WZBMP1,    // Bitmap to display
                     0,            // Icon do display
                     0,                    // Window Title
                     IDS_CREATEFOLDEREXIST_S, // Wizard title
                     IDS_CREATEFOLDEREXIST_T    // Wizard text
                    ),
    m_FileDirectory(FileDirectory),
    m_InitialFilename(InitialFilename),
    m_InitialChoice(InitialChoice)
{
    //{{AFX_DATA_INIT(ZICreateFolderWizardExist)
    m_Folder = _T(FolderName);
    //}}AFX_DATA_INIT
    m_Filename.SetSearchType( ZSEARCHEDIT_FILE, IDS_CHOOSEFILENAMEFORFOLDER, FileDirectory, "", 0 );
    m_Directory.SetSearchType( ZSEARCHEDIT_DIRECTORY, IDS_CHOOSEDIRECTORYFORFOLDER, FileDirectory );

    switch (m_InitialChoice)
    {
        case DirectoryChoice:
        {
            m_Choice = 1;
            break;
        }
        case FilenameChoice:
        {
            m_Choice = 2;
            break;
        }
        case KeepChoice:
        {
            m_Choice = 3;
            break;
        }
        case FolderNameChoice:
        default:
        {
            m_Choice = 0;
            break;
        }
    }
}


void ZICreateFolderWizardExist::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZICreateFolderWizardExist)
    DDX_Control(pDX, IDC_OTHERFILENAME, m_Filename);
    DDX_Control(pDX, IDC_FOLDERDIRECTORY, m_Directory);
    DDX_Radio(pDX, IDC_FOLDERCHOICE, m_Choice);
    DDX_Text(pDX, IDC_FOLDERFILENAME, m_Folder);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZICreateFolderWizardExist, ZIWizardDialog)
    //{{AFX_MSG_MAP(ZICreateFolderWizardExist)
    ON_BN_CLICKED(IDC_FOLDERCHOICE, OnFolderChoice)
    ON_BN_CLICKED(IDC_FOLDERCHOICE2, OnFolderChoice)
    ON_BN_CLICKED(IDC_FOLDERCHOICE3, OnFolderChoice)
    ON_BN_CLICKED(IDC_FOLDERCHOICE4, OnFolderChoice)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ZICreateFolderWizardExist::CheckControlStates()
{
    UpdateData();
    switch (m_Choice)
    {
        case 0:    // Change folder name
        {
            // Hide controls
            m_Filename.ShowWindow( SW_HIDE );
            if (GetDlgItem(IDC_FILE_TEXT))
               GetDlgItem(IDC_FILE_TEXT)->ShowWindow( SW_HIDE );
            m_Directory.ShowWindow( SW_HIDE );
            if (GetDlgItem(IDC_DIRECTORY_TEXT))
               GetDlgItem(IDC_DIRECTORY_TEXT)->ShowWindow( SW_HIDE );

            // Show controls            
            if (GetDlgItem(IDC_FOLDERFILENAME))
               GetDlgItem(IDC_FOLDERFILENAME)->ShowWindow( SW_SHOW );
            if (GetDlgItem(IDC_FOLDER_TEXT))
               GetDlgItem(IDC_FOLDER_TEXT)->ShowWindow( SW_SHOW );
            break;
        }
        case 1:    // Change directory
        {
            // Hide controls
            m_Filename.ShowWindow( SW_HIDE );
            if (GetDlgItem(IDC_FILE_TEXT))
               GetDlgItem(IDC_FILE_TEXT)->ShowWindow( SW_HIDE );
            if (GetDlgItem(IDC_FOLDERFILENAME))
               GetDlgItem(IDC_FOLDERFILENAME)->ShowWindow( SW_HIDE );
            if (GetDlgItem(IDC_FOLDER_TEXT))
               GetDlgItem(IDC_FOLDER_TEXT)->ShowWindow( SW_HIDE );

            // Show controls            
            m_Directory.ShowWindow( SW_SHOW );
            if (GetDlgItem(IDC_DIRECTORY_TEXT))
               GetDlgItem(IDC_DIRECTORY_TEXT)->ShowWindow( SW_SHOW );
            break;
        }
        case 2:    // Change filename
        {
            // Hide controls
            if (GetDlgItem(IDC_FOLDERFILENAME))
               GetDlgItem(IDC_FOLDERFILENAME)->ShowWindow( SW_HIDE );
            if (GetDlgItem(IDC_FOLDER_TEXT))
               GetDlgItem(IDC_FOLDER_TEXT)->ShowWindow( SW_HIDE );
            m_Directory.ShowWindow( SW_HIDE );
            if (GetDlgItem(IDC_DIRECTORY_TEXT))
               GetDlgItem(IDC_DIRECTORY_TEXT)->ShowWindow( SW_HIDE );

            // Show controls            
            m_Filename.ShowWindow( SW_SHOW );
            if (GetDlgItem(IDC_FILE_TEXT))
               GetDlgItem(IDC_FILE_TEXT)->ShowWindow( SW_SHOW );
            break;
        }
        case 3:    // Keep as is and rewrite the file
        {
            // Hide all controls
            if (GetDlgItem(IDC_FOLDERFILENAME))
               GetDlgItem(IDC_FOLDERFILENAME)->ShowWindow( SW_HIDE );
            if (GetDlgItem(IDC_FOLDER_TEXT))
               GetDlgItem(IDC_FOLDER_TEXT)->ShowWindow( SW_HIDE );
            m_Directory.ShowWindow( SW_HIDE );
            if (GetDlgItem(IDC_DIRECTORY_TEXT))
               GetDlgItem(IDC_DIRECTORY_TEXT)->ShowWindow( SW_HIDE );
            m_Filename.ShowWindow( SW_HIDE );
            if (GetDlgItem(IDC_FILE_TEXT))
               GetDlgItem(IDC_FILE_TEXT)->ShowWindow( SW_HIDE );
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZICreateFolderWizardExist message handlers

void ZICreateFolderWizardExist::OnOK() 
{
    UpdateData();
    switch (m_Choice)
    {
        case 0:    // Change folder name
        {
            if (m_Folder.IsEmpty())
            {
                return;
            }
            // The new folder name is assigned
            break;
        }
        case 1:    // Change directory
        {
            CString Directory;
            m_Directory.GetWindowText( Directory );
            if (Directory.IsEmpty())
            {
                return;
            }
            // Assign the new directory
            m_FileDirectory = Directory;
            break;
        }
        case 2:    // Change filename
        {
            CString    Filename;
            m_Filename.GetWindowText( Filename );
            if (Filename.IsEmpty())
            {
                return;
            }
            // Assign the new filename
            m_CompleteFilename = Filename;
            break;
        }
        case 3:    // Keep as is and rewrite the file
        {
            break;
        }
    }
    ZIWizardDialog::OnOK();
}

void ZICreateFolderWizardExist::OnFolderChoice() 
{
    CheckControlStates();    
}

BOOL ZICreateFolderWizardExist::OnInitDialog() 
{
    ZIWizardDialog::OnInitDialog();
    
    m_Directory.SetWindowText( m_FileDirectory );
    m_Filename.SetWindowText( m_InitialFilename );

    CheckControlStates();    
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
