/****************************************************************************
 * ==> PSS_CreateFolderWizardDialog ----------------------------------------*
 ****************************************************************************
 * Description : Provides a create folder Wizard dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CreateFolderWizardDialog.h"

// processsoft
#include "zBaseLib\File.h"
#include "PSS_CreateFolderWizardStartDialog.h"
#include "PSS_CreateFolderWizardExistDialog.h"
#include "opendird32.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_CreateFolderWizardDialog
//---------------------------------------------------------------------------
PSS_CreateFolderWizardDialog::PSS_CreateFolderWizardDialog(BOOL           useFolderNameAsFileName,
                                                           const CString& fileDirectory,
                                                           const CString& fileExtension,
                                                           const CString& folderName,
                                                           const CString& folderDescription) :
    m_FileDirectory(fileDirectory),
    m_FolderName(folderName),
    m_FolderDescription(folderDescription),
    m_FileExtension(fileExtension),
    m_UseFolderNameAsFileName(useFolderNameAsFileName)
{}
//---------------------------------------------------------------------------
PSS_CreateFolderWizardDialog::~PSS_CreateFolderWizardDialog()
{}
//---------------------------------------------------------------------------
BOOL PSS_CreateFolderWizardDialog::PlayWizard()
{
    PSS_CreateFolderWizardStartDialog createFolderWizardStart(m_UseFolderNameAsFileName,
                                                              m_FileDirectory,
                                                              m_FolderName,
                                                              m_FolderDescription,
                                                              "",
                                                              m_FileExtension);

    if (createFolderWizardStart.DoModal() == IDCANCEL)
        return FALSE;

    // if the file directory is empty, get it
    if (m_FileDirectory.IsEmpty())
    {
        ZIOpenDirDlg openDirDlg(IDS_CHOOSEDIRECTORYFORFOLDER);
        m_FileDirectory = openDirDlg.ProcessDirectory();

        if (m_FileDirectory.IsEmpty())
            return FALSE;
    }

    // check if the file name already exists
    m_FolderName = createFolderWizardStart.GetFolderName();

    // create empty file name
    CString fileName;

    if (!m_UseFolderNameAsFileName)
        fileName = createFolderWizardStart.GetFileName();

    PSS_CreateFolderWizardExistDialog::IEFolderExistInitialChoice initialChoice =
                PSS_CreateFolderWizardExistDialog::IE_FC_FolderName;

    while (CheckFolderExist(fileName))
        if (m_UseFolderNameAsFileName)
        {
            PSS_CreateFolderWizardExistDialog createFolderWizardExist(m_FolderName,
                                                                      m_FileDirectory,
                                                                      m_CompleteFileName,
                                                                      initialChoice);

            if (createFolderWizardExist.DoModal() == IDCANCEL)
                return FALSE;

            if (createFolderWizardExist.IsFolderNameSelected())
            {
                // assign the new folder name
                m_FolderName = createFolderWizardExist.GetFolderName();

                // empty the file name
                fileName.Empty();

                // keep choice for next use
                initialChoice = PSS_CreateFolderWizardExistDialog::IE_FC_FolderName;
            }
            else
            if (createFolderWizardExist.IsDirectorySelected())
            {
                // assign the new directory
                m_FileDirectory = createFolderWizardExist.GetFileDirectory();

                // empty the file name
                fileName.Empty();

                // keep choice for next use
                initialChoice = PSS_CreateFolderWizardExistDialog::IE_FC_Directory;
            }
            else
            if (createFolderWizardExist.IsFileNameSelected())
            {
                // assign the new file name
                fileName = createFolderWizardExist.GetFileName();

                // keep choice for next use
                initialChoice = PSS_CreateFolderWizardExistDialog::IE_FC_FileName;
            }
            else
            if (createFolderWizardExist.IsReWriteSelected())
                break;
        }
        else
        {
            PSS_CreateFolderWizardStartDialog correctCreateFolderWizardStart(m_UseFolderNameAsFileName,
                                                                             m_FileDirectory,
                                                                             m_FolderName,
                                                                             m_FolderDescription,
                                                                             fileName,
                                                                             m_FileExtension);

            if (correctCreateFolderWizardStart.DoModal() == IDCANCEL)
                return FALSE;

            // assign the new file name
            fileName = correctCreateFolderWizardStart.GetFileName();
        }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CreateFolderWizardDialog::CheckFolderExist(const CString& fileName)
{
    // build the complete file name
    if (fileName.IsEmpty())
        m_CompleteFileName = m_FileDirectory + "\\" + m_FolderName + "." + m_FileExtension;
    else
        m_CompleteFileName = fileName;

    ZFile file(m_CompleteFileName);
    return file.Exist();
}
//---------------------------------------------------------------------------
