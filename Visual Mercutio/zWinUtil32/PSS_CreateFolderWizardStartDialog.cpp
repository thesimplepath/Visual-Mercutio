/****************************************************************************
 * ==> PSS_CreateFolderWizardStartDialog -----------------------------------*
 ****************************************************************************
 * Description : Provides a folder Wizard start dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_CreateFolderWizardStartDialog.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zRes32\Zres.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_CreateFolderWizardStartDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_CreateFolderWizardStartDialog)
    ON_EN_CHANGE(IDC_FOLDERFILENAME, OnChangeFolderName)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_CreateFolderWizardStartDialog
//---------------------------------------------------------------------------
PSS_CreateFolderWizardStartDialog::PSS_CreateFolderWizardStartDialog(BOOL           useFolderNameAsFileName,
                                                                     const CString& folderDirectory,
                                                                     const CString& folderName,
                                                                     const CString& folderDescription,
                                                                     const CString& initialFileName,
                                                                     const CString& fileExtension,
                                                                     CWnd*          pParent) :
    PSS_WizardDialog(PSS_CreateFolderWizardStartDialog::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_CREATEFOLDERST_S,
                     IDS_CREATEFOLDERST_T),
    m_FolderComment(_T(folderDescription)),
    m_FolderName(_T(folderName)),
    m_FolderDirectory(folderDirectory),
    m_InitialFileName(initialFileName),
    m_FileExtension(fileExtension),
    m_UseFolderNameAsFileName(useFolderNameAsFileName)
{
    m_CompleteFileName.SetSearchType(PSS_SearchEditButton::IEType::IE_T_File, IDS_CHOOSEFILENAMEFORFOLDER, m_FolderDirectory, "", 0);
    GetCurrentDirectory(_MAX_DIR - 1, m_Dir);

    // if the last char of the directory is not a backslash, add one
    if (m_FolderDirectory.GetAt(m_FolderDirectory.GetLength() - 1) != '\\')
        m_FolderDirectory += '\\';
}
//---------------------------------------------------------------------------
void PSS_CreateFolderWizardStartDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_CreateFolderWizardStartDialog)
    DDX_Control(pDX, IDC_COMPLETEFILENAME, m_CompleteFileName);
    DDX_Text   (pDX, IDC_FOLDERCOMMENT,    m_FolderComment);
    DDX_Text   (pDX, IDC_FOLDERFILENAME,   m_FolderName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_CreateFolderWizardStartDialog::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    // show or hide file control. Depends on use foldername as file
    m_CompleteFileName.ShowWindow((m_UseFolderNameAsFileName) ? SW_HIDE : SW_SHOW);

    if (GetDlgItem(IDC_FILE_TEXT))
       GetDlgItem(IDC_FILE_TEXT)->ShowWindow((m_UseFolderNameAsFileName) ? SW_HIDE : SW_SHOW);

    if (m_InitialFileName.IsEmpty())
    {
        if (m_FolderDirectory.IsEmpty())
            m_CompleteFileName.SetWindowText(m_Dir);
        else
            m_CompleteFileName.SetWindowText(m_FolderDirectory);
    }
    else
        m_CompleteFileName.SetWindowText(m_InitialFileName);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CreateFolderWizardStartDialog::OnChangeFolderName()
{
    // todo -cFeature -oJean: If this is a RICHEDIT control, the control will not send this notification
    //                        unless the ZIWizardDialog::OnInitDialog() function is overriden, and the
    //                        CRichEditCtrl().SetEventMask() function is called with the ENM_CHANGE flag
    //                        set in the mask
    UpdateData();

    // not automatic
    if (!m_UseFolderNameAsFileName)
    {
        CString fileName;
        m_CompleteFileName.GetWindowText(fileName);

        char drive[_MAX_DRIVE];
        char dir  [_MAX_DIR];
        char fName[_MAX_FNAME];
        char ext  [_MAX_EXT];

        ::_splitpath_s((const char*)fileName,
                       drive,
                       ::_tcslen(drive),
                       dir,
                       ::_tcslen(dir),
                       fName,
                       ::_tcslen(fName),
                       ext,
                       ::_tcslen(ext));

        if (m_FolderName.IsEmpty())
            m_CompleteFileName.SetWindowText(CString(drive) + dir);
        else
        {
            CString completeFileName = CString(drive) + dir + m_FolderName + "." + m_FileExtension;
            m_CompleteFileName.SetWindowText(completeFileName);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_CreateFolderWizardStartDialog::OnOK()
{
    UpdateData();

    // folder name required
    if (m_FolderName.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_NO_FOLDERNAME, MB_OK);
        return;
    }

    // if not automatic folder name, a file name is necessary
    if (!m_UseFolderNameAsFileName && m_FileName.IsEmpty())
    {
        m_CompleteFileName.GetWindowText(m_FileName);

        if (m_FileName.IsEmpty())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_FILENAMEMISSING, MB_OK);
            return;
        }
    }

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
