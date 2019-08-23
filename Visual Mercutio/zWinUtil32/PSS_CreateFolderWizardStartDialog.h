/****************************************************************************
 * ==> PSS_CreateFolderWizardStartDialog -----------------------------------*
 ****************************************************************************
 * Description : Provides a folder Wizard start dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CreateFolderWizardStartDialogH
#define PSS_CreateFolderWizardStartDialogH

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

// processsoft
#include "zBaseLib\PSS_WizardDialog.h"
#include "PSS_SearchEdit.h"

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
* Folder Wizard start dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_CreateFolderWizardStartDialog : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param useFolderNameAsFileName - if TRUE, folder names will be used as file names
        *@param folderDirectory - folder directory
        *@param folderName - folder name
        *@param folderDescription - folder description
        *@param initialFileName - initial file name
        *@param fileExtension - file extension
        *@param pParent - parent window, can be NULL
        */
        PSS_CreateFolderWizardStartDialog(BOOL           useFolderNameAsFileName = FALSE,
                                          const CString& folderDirectory         = "",
                                          const CString& folderName              = "",
                                          const CString& folderDescription       = "",
                                          const CString& initialFileName         = "",
                                          const CString& fileExtension           = "",
                                          CWnd*          pParent                 = NULL);

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

        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_CreateFolderWizardStartDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_CreateFolderWizardStartDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnChangeFolderName();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZCREATEFOLDERFILE_ST
        };

        PSS_SearchEdit m_CompleteFileName;
        CString        m_FolderComment;
        CString        m_FolderName;
        CString        m_FolderDirectory;
        CString        m_FileName;
        CString        m_InitialFileName;
        CString        m_FileExtension;
        BOOL           m_UseFolderNameAsFileName;
        char           m_Dir[_MAX_DIR];
};

//---------------------------------------------------------------------------
// PSS_CreateFolderWizardStartDialog
//---------------------------------------------------------------------------
CString PSS_CreateFolderWizardStartDialog::GetFolderName() const
{
    return m_FolderName;
}
//---------------------------------------------------------------------------
CString PSS_CreateFolderWizardStartDialog::GetFolderDescription() const
{
    return m_FolderComment;
}
//---------------------------------------------------------------------------
CString PSS_CreateFolderWizardStartDialog::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------

#endif
