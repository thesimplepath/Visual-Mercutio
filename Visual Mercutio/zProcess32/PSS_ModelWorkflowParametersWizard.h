/****************************************************************************
 * ==> PSS_ModelWorkflowParametersWizard -----------------------------------*
 ****************************************************************************
 * Description : Provides a model workflow parameters wizard                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModelWorkflowParametersWizardH
#define PSS_ModelWorkflowParametersWizardH

// processsoft
#include "zBaseLib\PSS_FolderStamp.h"
#include "zBaseLib\PSS_WizardDialog.h"

// resources
#include "Resources.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_ProcessGraphModelDoc;
class PSS_TemplateManager;

/**
* Model workflow parameters wizard
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ModelWorkflowParametersWizard
{
    public:
        /**
        * Constructor
        *@param modify - if TRUE, existing values will be get and shown for modification, otherwise default values will be shown
        *@param pDoc - the document for which options should be shown
        *@param pTemplateManager - the template manager
        *@param fileExtension - the file extension
        *@param pParent - the parent window, can be NULL
        */
        PSS_ModelWorkflowParametersWizard(BOOL                      modify,
                                          PSS_ProcessGraphModelDoc* pDoc,
                                          PSS_TemplateManager*      pTemplateManager,
                                          const CString&            fileExtension,
                                          CWnd*                     pParent = NULL);

        virtual ~PSS_ModelWorkflowParametersWizard();

        /**
        * Gets the folder stamp
        *@return the folder stamp
        */
        virtual inline PSS_FolderStamp& GetFolderStamp();

        /**
        * Gets the check consistency state
        *@return the check consistency state
        */
        virtual inline bool GetCheckConsistency() const;

        /**
        * Gets the save model in workflow state
        *@return the save model in workflow state
        */
        virtual inline bool GetSaveModelInWorkflow() const;

        /**
        * Checks if the selected file exists
        *@return true if the selected file exists, otherwise false
        */
        virtual inline bool SelectedFileExists() const;

        /**
        * Shows the wizard in modal mode
        *@return the modal result
        */
        virtual int DoModal();

    private:
        PSS_ProcessGraphModelDoc* m_pDoc;
        PSS_TemplateManager*      m_pTemplateManager;
        PSS_FolderStamp           m_FolderStamp;
        CString                   m_FileExtension;
        BOOL                      m_Modify;
        bool                      m_CheckConsistency;
        bool                      m_SaveModelInWkfFile;
        bool                      m_FileExist;
};

//---------------------------------------------------------------------------
// PSS_ModelWorkflowParametersWizard
//---------------------------------------------------------------------------
PSS_FolderStamp& PSS_ModelWorkflowParametersWizard::GetFolderStamp()
{
    return m_FolderStamp;
}
//---------------------------------------------------------------------------
bool PSS_ModelWorkflowParametersWizard::GetCheckConsistency() const
{
    return m_CheckConsistency;
}
//---------------------------------------------------------------------------
bool PSS_ModelWorkflowParametersWizard::GetSaveModelInWorkflow() const
{
    return m_SaveModelInWkfFile;
}
//---------------------------------------------------------------------------
bool PSS_ModelWorkflowParametersWizard::SelectedFileExists() const
{
    return m_FileExist;
}
//---------------------------------------------------------------------------

/**
* Model workflow parameters welcome dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ModelWorkflowParamsWelcomeDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param pParent - the parent window, can be NULL
        */
        PSS_ModelWorkflowParamsWelcomeDlg(CWnd* pParent = NULL);

        virtual ~PSS_ModelWorkflowParamsWelcomeDlg();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ModelWorkflowParamsWelcomeDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        // Generated message map functions
        //{{AFX_MSG(PSS_ModelWorkflowParamsWelcomeDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnNext();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog data
        */
        enum
        {
            IDD = IDD_WZ_MODELWKF_START
        };
};

/**
* Model workflow parameters options dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ModelWorkflowParamsOptionsDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param modify - if TRUE, existing values will be get and shown for modification, otherwise default values will be shown
        *@param doc - the document for which options should be shown
        *@param pParent - the parent window, can be NULL
        */
        PSS_ModelWorkflowParamsOptionsDlg(BOOL modify, PSS_ProcessGraphModelDoc& doc, CWnd* pParent = NULL);

        virtual ~PSS_ModelWorkflowParamsOptionsDlg();

        /**
        * Gets the check consistency state
        *@return the check consistency state
        */
        virtual inline BOOL GetCheckConsistency() const;

        /**
        * Gets the save model in workflow state
        *@return the save model in workflow state
        */
        virtual inline BOOL GetSaveModelInWorkflow() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ModelWorkflowParamsOptionsDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ModelWorkflowParamsOptionsDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnNext();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog data
        */
        enum
        {
            IDD = IDD_WZ_MODELWKF_OPTIONS
        };

        PSS_ProcessGraphModelDoc& m_Doc;
        BOOL                      m_CheckConsistency;
        BOOL                      m_SaveModelInWkfFile;
        BOOL                      m_Modify;
};

//---------------------------------------------------------------------------
// PSS_ModelWorkflowParamsOptionsDlg
//---------------------------------------------------------------------------
BOOL PSS_ModelWorkflowParamsOptionsDlg::GetCheckConsistency() const
{
    return m_CheckConsistency;
}
//---------------------------------------------------------------------------
BOOL PSS_ModelWorkflowParamsOptionsDlg::GetSaveModelInWorkflow() const
{
    return m_SaveModelInWkfFile;
}
//---------------------------------------------------------------------------

#endif
