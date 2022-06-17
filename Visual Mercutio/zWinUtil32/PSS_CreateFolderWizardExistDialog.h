/****************************************************************************
 * ==> PSS_CreateFolderWizardExistDialog -----------------------------------*
 ****************************************************************************
 * Description : Provides a check if folder exists and create folder Wizard *
 *               dialog box                                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CreateFolderWizardExistDialogH
#define PSS_CreateFolderWizardExistDialogH

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
* Check if folder exists and create folder Wizard dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_CreateFolderWizardExistDialog : public PSS_WizardDialog
{
    public:
        /**
        * Folder exists initial choice enumeration
        */
        enum class IEFolderExistInitialChoice
        {
            IE_FC_FolderName,
            IE_FC_Directory,
            IE_FC_FileName,
            IE_FC_Keep
        };

        /**
        * Constructor
        *@param folderName - folder name
        *@param fileDirectory - file directory
        *@param initialFileName - initial file name
        *@param initialChoice - initial choice
        *@param pParent - parent window, can be NULL
        */
        PSS_CreateFolderWizardExistDialog(const CString&             folderName,
                                          const CString&             fileDirectory,
                                          const CString&             initialFileName,
                                          IEFolderExistInitialChoice initialChoice = IEFolderExistInitialChoice::IE_FC_FolderName,
                                          CWnd*                      pParent       = NULL);

        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;

        /**
        * Gets the file directory
        *@return the file directory
        */
        virtual inline CString GetFileDirectory() const;

        /**
        * Gets the folder name
        *@return the folder name
        */
        virtual inline CString GetFolderName() const;

        /**
        * Checks if the folder name is selected
        *@return TRUE if the folder name is selected, otherwise FALSE
        */
        virtual inline BOOL IsFolderNameSelected() const;

        /**
        * Checks if the directory is selected
        *@return TRUE if the directory is selected, otherwise FALSE
        */
        virtual inline BOOL IsDirectorySelected() const;

        /**
        * Checks if the file name is selected
        *@return TRUE if the file name is selected, otherwise FALSE
        */
        virtual inline BOOL IsFileNameSelected() const;

        /**
        * Checks if the re-write option is selected
        *@return TRUE if the re-write option is selected, otherwise FALSE
        */
        virtual inline BOOL IsReWriteSelected() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_CreateFolderWizardExistDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_CreateFolderWizardExistDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnFolderChoice();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZCREATEFOLDERFILE_EXIST
        };

        PSS_SearchEdit             m_FileName;
        PSS_SearchEdit             m_Directory;
        CString                    m_Folder;
        CString                    m_FileDirectory;
        CString                    m_CompleteFileName;
        CString                    m_InitialFileName;
        IEFolderExistInitialChoice m_InitialChoice;
        int                        m_Choice;

        /**
        * Checks the control state
        */
        void CheckControlStates();
};

//---------------------------------------------------------------------------
// PSS_CreateFolderWizardExistDialog
//---------------------------------------------------------------------------
CString PSS_CreateFolderWizardExistDialog::GetFileName() const
{
    return m_CompleteFileName;
}
//---------------------------------------------------------------------------
CString PSS_CreateFolderWizardExistDialog::GetFileDirectory() const
{
    return m_FileDirectory;
}
//---------------------------------------------------------------------------
CString PSS_CreateFolderWizardExistDialog::GetFolderName() const
{
    return m_Folder;
}
//---------------------------------------------------------------------------
BOOL PSS_CreateFolderWizardExistDialog::IsFolderNameSelected() const
{
    return m_Choice == 0;
}
//---------------------------------------------------------------------------
BOOL PSS_CreateFolderWizardExistDialog::IsDirectorySelected() const
{
    return m_Choice == 1;
}
//---------------------------------------------------------------------------
BOOL PSS_CreateFolderWizardExistDialog::IsFileNameSelected() const
{
    return m_Choice == 2;
}
//---------------------------------------------------------------------------
BOOL PSS_CreateFolderWizardExistDialog::IsReWriteSelected() const
{
    return m_Choice == 3;
}
//---------------------------------------------------------------------------

#endif
