/****************************************************************************
 * ==> PSS_CreateFolderWizardDialog ----------------------------------------*
 ****************************************************************************
 * Description : Provides a create folder Wizard dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CreateFolderWizardDialogH
#define PSS_CreateFolderWizardDialogH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// resources
#include "zWinUtil32\zWinUtil32Res.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Create folder Wizard dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CreateFolderWizardDialog
{
    public:
        /**
        * Constructor
        *@param useFolderNameAsFileName - if TRUE, folder names will be used as file names
        *@param fileDirectory - file directory
        *@param fileExtension - file extension
        *@param folderName - folder name
        *@param folderDescription - folder description
        */
        PSS_CreateFolderWizardDialog(BOOL           useFolderNameAsFileName,
                                     const CString& fileDirectory,
                                     const CString& fileExtension     = "",
                                     const CString& folderName        = "",
                                     const CString& folderDescription = "");

        virtual ~PSS_CreateFolderWizardDialog();

        /**
        * Starts the wizard
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PlayWizard();
    
        /**
        * Gets the folder file name
        *@return the folder file name
        */
        virtual inline CString GetFolderFileName() const;

        /**
        * Gets the folder name
        *@return the folder name
        */
        virtual inline CString GetFolderName() const;

        /**
        * Gets the folder description
        *@return the folder description
        */
        virtual inline CString GetFolderDescription() const;

    private:
        CString m_FileDirectory;
        CString m_FolderName;
        CString m_FolderDescription;
        CString m_FileExtension;
        CString m_CompleteFileName;
        BOOL    m_UseFolderNameAsFileName;

        /**
        * Checks if a folder exists
        *@param fileName - folder file name
        *@return TRUE if the folder exists, otherwise FALSE
        */
        BOOL CheckFolderExist(const CString& fileName = "");
};

//---------------------------------------------------------------------------
// PSS_CreateFolderWizardDialog
//---------------------------------------------------------------------------
CString PSS_CreateFolderWizardDialog::GetFolderFileName() const
{
    return m_CompleteFileName;
}
//---------------------------------------------------------------------------
CString PSS_CreateFolderWizardDialog::GetFolderName() const
{
    return m_FolderName;
}
//---------------------------------------------------------------------------
CString PSS_CreateFolderWizardDialog::GetFolderDescription() const
{
    return m_FolderDescription;
}
//---------------------------------------------------------------------------

#endif
