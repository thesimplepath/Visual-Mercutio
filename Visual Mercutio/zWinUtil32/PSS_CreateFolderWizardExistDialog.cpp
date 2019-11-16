/****************************************************************************
 * ==> PSS_CreateFolderWizardExistDialog -----------------------------------*
 ****************************************************************************
 * Description : Provides a check if folder exists and create folder Wizard *
 *               dialog box                                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_CreateFolderWizardExistDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_CreateFolderWizardExistDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_CreateFolderWizardExistDialog)
    ON_BN_CLICKED(IDC_FOLDERCHOICE, OnFolderChoice)
    ON_BN_CLICKED(IDC_FOLDERCHOICE2, OnFolderChoice)
    ON_BN_CLICKED(IDC_FOLDERCHOICE3, OnFolderChoice)
    ON_BN_CLICKED(IDC_FOLDERCHOICE4, OnFolderChoice)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_CreateFolderWizardExistDialog
//---------------------------------------------------------------------------
PSS_CreateFolderWizardExistDialog::PSS_CreateFolderWizardExistDialog(const CString&             folderName,
                                                                     const CString&             fileDirectory,
                                                                     const CString&             initialFileName,
                                                                     IEFolderExistInitialChoice initialChoice,
                                                                     CWnd*                      pParent) :
    PSS_WizardDialog(PSS_CreateFolderWizardExistDialog::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_CREATEFOLDEREXIST_S,
                     IDS_CREATEFOLDEREXIST_T),
    m_Folder(_T(folderName)),
    m_FileDirectory(fileDirectory),
    m_InitialFileName(initialFileName),
    m_InitialChoice(initialChoice)
{
    m_FileName.SetSearchType(PSS_SearchEditButton::IE_T_File, IDS_CHOOSEFILENAMEFORFOLDER, fileDirectory, "", 0);
    m_Directory.SetSearchType(PSS_SearchEditButton::IE_T_Directory, IDS_CHOOSEDIRECTORYFORFOLDER, fileDirectory);

    switch (m_InitialChoice)
    {
        case IE_FC_Directory: m_Choice = 1; break;
        case IE_FC_FileName:  m_Choice = 2; break;
        case IE_FC_Keep:      m_Choice = 3; break;
        default:              m_Choice = 0; break;
    }
}
//---------------------------------------------------------------------------
void PSS_CreateFolderWizardExistDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_CreateFolderWizardExistDialog)
    DDX_Control(pDX, IDC_OTHERFILENAME,   m_FileName);
    DDX_Control(pDX, IDC_FOLDERDIRECTORY, m_Directory);
    DDX_Radio  (pDX, IDC_FOLDERCHOICE,    m_Choice);
    DDX_Text   (pDX, IDC_FOLDERFILENAME,  m_Folder);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_CreateFolderWizardExistDialog::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    m_Directory.SetWindowText(m_FileDirectory);
    m_FileName.SetWindowText(m_InitialFileName);

    CheckControlStates();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CreateFolderWizardExistDialog::OnFolderChoice()
{
    CheckControlStates();
}
//---------------------------------------------------------------------------
void PSS_CreateFolderWizardExistDialog::OnOK()
{
    UpdateData();
    switch (m_Choice)
    {
        // change folder name
        case 0:
            if (m_Folder.IsEmpty())
                return;

            // the new folder name is assigned
            break;

        // change directory
        case 1:
        {
            CString directory;
            m_Directory.GetWindowText(directory);

            if (directory.IsEmpty())
                return;

            // assign the new directory
            m_FileDirectory = directory;
            break;
        }

        // change file name
        case 2:
        {
            CString fileName;
            m_FileName.GetWindowText(fileName);

            if (fileName.IsEmpty())
                return;

            // assign the new file name
            m_CompleteFileName = fileName;
            break;
        }

        // Keep as is and rewrite the file
        case 3:
            break;
    }

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_CreateFolderWizardExistDialog::CheckControlStates()
{
    UpdateData();

    switch (m_Choice)
    {
        // change folder name
        case 0:
            // hide controls
            m_FileName.ShowWindow(SW_HIDE);

            if (GetDlgItem(IDC_FILE_TEXT))
               GetDlgItem(IDC_FILE_TEXT)->ShowWindow(SW_HIDE);

            m_Directory.ShowWindow(SW_HIDE);

            if (GetDlgItem(IDC_DIRECTORY_TEXT))
               GetDlgItem(IDC_DIRECTORY_TEXT)->ShowWindow(SW_HIDE);

            // show controls
            if (GetDlgItem(IDC_FOLDERFILENAME))
               GetDlgItem(IDC_FOLDERFILENAME)->ShowWindow(SW_SHOW);

            if (GetDlgItem(IDC_FOLDER_TEXT))
               GetDlgItem(IDC_FOLDER_TEXT)->ShowWindow(SW_SHOW);

            break;

        // change directory
        case 1:
            // hide controls
            m_FileName.ShowWindow(SW_HIDE);

            if (GetDlgItem(IDC_FILE_TEXT))
               GetDlgItem(IDC_FILE_TEXT)->ShowWindow(SW_HIDE);

            if (GetDlgItem(IDC_FOLDERFILENAME))
               GetDlgItem(IDC_FOLDERFILENAME)->ShowWindow(SW_HIDE);

            if (GetDlgItem(IDC_FOLDER_TEXT))
               GetDlgItem(IDC_FOLDER_TEXT)->ShowWindow(SW_HIDE);

            // show controls
            m_Directory.ShowWindow(SW_SHOW);

            if (GetDlgItem(IDC_DIRECTORY_TEXT))
               GetDlgItem(IDC_DIRECTORY_TEXT)->ShowWindow(SW_SHOW);

            break;

        // change file name
        case 2:
            // hide controls
            if (GetDlgItem(IDC_FOLDERFILENAME))
               GetDlgItem(IDC_FOLDERFILENAME)->ShowWindow(SW_HIDE);

            if (GetDlgItem(IDC_FOLDER_TEXT))
               GetDlgItem(IDC_FOLDER_TEXT)->ShowWindow(SW_HIDE);

            m_Directory.ShowWindow(SW_HIDE);

            if (GetDlgItem(IDC_DIRECTORY_TEXT))
               GetDlgItem(IDC_DIRECTORY_TEXT)->ShowWindow(SW_HIDE);

            // show controls
            m_FileName.ShowWindow(SW_SHOW);

            if (GetDlgItem(IDC_FILE_TEXT))
               GetDlgItem(IDC_FILE_TEXT)->ShowWindow(SW_SHOW);

            break;

        // keep as is and rewrite the file
        case 3:
            // hide all controls
            if (GetDlgItem(IDC_FOLDERFILENAME))
               GetDlgItem(IDC_FOLDERFILENAME)->ShowWindow(SW_HIDE);

            if (GetDlgItem(IDC_FOLDER_TEXT))
               GetDlgItem(IDC_FOLDER_TEXT)->ShowWindow(SW_HIDE);

            m_Directory.ShowWindow(SW_HIDE);

            if (GetDlgItem(IDC_DIRECTORY_TEXT))
               GetDlgItem(IDC_DIRECTORY_TEXT)->ShowWindow(SW_HIDE);

            m_FileName.ShowWindow(SW_HIDE);

            if (GetDlgItem(IDC_FILE_TEXT))
               GetDlgItem(IDC_FILE_TEXT)->ShowWindow(SW_HIDE);

            break;
    }
}
//---------------------------------------------------------------------------
