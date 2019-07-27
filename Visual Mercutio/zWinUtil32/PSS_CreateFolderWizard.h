/****************************************************************************
 * ==> PSS_CreateFolderWizard ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a create folder Wizard                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CreateFolderWizardH
#define PSS_CreateFolderWizardH

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
* Create folder Wizard
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CreateFolderWizard
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
        PSS_CreateFolderWizard(BOOL           useFolderNameAsFileName,
                               const CString& fileDirectory,
                               const CString& fileExtension     = "",
                               const CString& folderName        = "",
                               const CString& folderDescription = "");

        virtual ~PSS_CreateFolderWizard();

        /**
        * Executes the wizard
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Execute();
    
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
// PSS_CreateFolderWizard
//---------------------------------------------------------------------------
CString PSS_CreateFolderWizard::GetFolderFileName() const
{
    return m_CompleteFileName;
}
//---------------------------------------------------------------------------
CString PSS_CreateFolderWizard::GetFolderName() const
{
    return m_FolderName;
}
//---------------------------------------------------------------------------
CString PSS_CreateFolderWizard::GetFolderDescription() const
{
    return m_FolderDescription;
}
//---------------------------------------------------------------------------

#endif
