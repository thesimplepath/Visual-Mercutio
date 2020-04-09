/****************************************************************************
 * ==> PSS_ModelTemplateCopyDlg --------------------------------------------*
 ****************************************************************************
 * Description : Provides a model template copy dialog                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModelTemplateCopyDlgH
#define PSS_ModelTemplateCopyDlgH

// processsoft
#include "zBaseLib\PSS_Dialog.h"
#include "zBaseLib\PSS_FolderStamp.h"
#include "zWinUtil32\PSS_SearchEdit.h"

// resources
#include "Resources.h"

/**
* Model template copy dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ModelTemplateCopyDlg : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param fileExtension - the template file extension
        *@param dir - the template file dir
        *@param pFolderStamp - the folder stamp
        *@param allowReplace - if TRUE, any existing file is allowed to be replaced by the new one
        *@param pParent - the parent window, can be NULL
        */
        PSS_ModelTemplateCopyDlg(const CString&   fileExtension,
                                 const CString&   dir,
                                 PSS_FolderStamp* pFolderStamp = NULL,
                                 BOOL             allowReplace = FALSE,
                                 CWnd*            pParent      = NULL);

        virtual ~PSS_ModelTemplateCopyDlg();

        /**
        * Gets the title
        *@return the title
        */
        virtual inline CString GetTitle() const;

        /**
        * Gets the description
        *@return the description
        */
        virtual inline CString GetDescription() const;

        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;

        /**
        * Gets the directory
        *@return the directory
        */
        virtual inline CString GetDirectory() const;

        /**
        * Checks if the selected file exists
        *@return true if the selected file exists, otherwise false
        */
        virtual inline bool SelectedFileExists() const;

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        // Generated message map functions
        //{{AFX_MSG(ZIModelTemplateCopyDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnChangeTitle();
        afx_msg void OnDontSave();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_MODELTEMPLATESAVE
        };

        PSS_SearchEdit   m_ModelDirectory;
        PSS_FolderStamp* m_pFolderStamp;
        CString          m_Title;
        CString          m_Description;
        CString          m_FileName;
        CString          m_FileExtension;
        CString          m_Directory;
        BOOL             m_AllowReplace;
        bool             m_FileExist;
};

//---------------------------------------------------------------------------
// PSS_ModelTemplateCopyDlg
//---------------------------------------------------------------------------
CString PSS_ModelTemplateCopyDlg::GetTitle() const
{
    return m_Title;
}
//---------------------------------------------------------------------------
CString PSS_ModelTemplateCopyDlg::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
CString PSS_ModelTemplateCopyDlg::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
CString PSS_ModelTemplateCopyDlg::GetDirectory() const
{
    return m_Directory;
}
//---------------------------------------------------------------------------
bool PSS_ModelTemplateCopyDlg::SelectedFileExists() const
{
    return m_FileExist;
}
//---------------------------------------------------------------------------

#endif
