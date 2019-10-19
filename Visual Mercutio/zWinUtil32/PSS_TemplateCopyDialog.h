/****************************************************************************
 * ==> PSS_TemplateCopyDialog ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a template copy dialog box                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TemplateCopyDialogH
#define PSS_TemplateCopyDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_TemplateManager.h"
#include "zBaseLib\PSS_Dialog.h"
#include "PSS_TemplateTreeCtrl.h"

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
* Template copy dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TemplateCopyDialog : public PSS_Dialog
{
public:
    /**
    * Constructor
    *@param pTemplateManager - template manager
    *@param fileExtension - file extension
    *@param pFolderStamp - folder stamp
    *@param allowReplace - if TRUE, replace is allowed
    *@param pParent - parent window, can be NULL
    */
    PSS_TemplateCopyDialog(PSS_TemplateManager* pTemplateManager,
                           const CString&       fileExtension,
                           PSS_FolderStamp*     pFolderStamp = NULL,
                           BOOL                 allowReplace = FALSE,
                           CWnd*                pParent      = NULL);

    /**
    * Gets the title
    *@return the title
    */
    virtual inline CString GetTitle() const;

    /**
    * Gets the file name
    *@return the file name
    */
    virtual inline CString GetFileName() const;

    /**
    * Gets the description
    *@return the description
    */
    virtual inline CString GetDescription() const;

    /**
    * Gets if the selected file exists
    *@return true if the selected file exists, otherwise false
    */
    virtual inline bool SelectedFileExists() const;

protected:
    /**
    * DDX/DDV support
    *@param pDX - DDX/DDV data
    */
    virtual void DoDataExchange(CDataExchange* pDX);

    /// Generated message map functions
    //{{AFX_MSG(PSS_TemplateCopyDialog)
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeTitle();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    /**
    * Dialog resources
    */
    enum
    {
        IDD = IDD_TEMPLATESAVE
    };

    #ifdef _WIN32
    PSS_TemplateTreeCtrl m_TemplateDirList;
    #else
        CListBox         m_TemplateDirList;
    #endif
    PSS_TemplateManager* m_pTemplateManager;
    PSS_FolderStamp*     m_pFolderStamp;
    CString              m_Title;
    CString              m_Description;
    CString              m_FileName;
    CString              m_FileExtension;
    BOOL                 m_AllowReplace;
    bool                 m_FileExist;
};

//---------------------------------------------------------------------------
// PSS_TemplateCopyDialog
//---------------------------------------------------------------------------
CString PSS_TemplateCopyDialog::GetTitle() const
{
    return m_Title;
}
//---------------------------------------------------------------------------
CString PSS_TemplateCopyDialog::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
CString PSS_TemplateCopyDialog::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
bool PSS_TemplateCopyDialog::SelectedFileExists() const
{
    return m_FileExist;
}
//---------------------------------------------------------------------------

#endif
