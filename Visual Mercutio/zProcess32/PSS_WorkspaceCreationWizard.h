/****************************************************************************
 * ==> PSS_WorkspaceCreationWizard -----------------------------------------*
 ****************************************************************************
 * Description : Provides the workspace creation wizard                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceCreationWizardH
#define PSS_WorkspaceCreationWizardH

#if _MSC_VER > 1000
    #pragma once
#endif

// class name mapping
#ifndef PSS_WorkspaceWizardTemplateManager
    #define PSS_WorkspaceWizardTemplateManager ZBWorkspaceWizardTemplateMg
#endif

// processsoft
#include "zBaseLib\PSS_WizardDialog.h"
#include "zWinUtil32\PSS_SearchEdit.h"
#include "zWinUtil32\PSS_WorkspaceTemplateListCtrl.h"

// resources
#include "resource.h"

// forward class declaration
class PSS_WorkspaceWizardTemplateManager;

/**
* Workspace creation wizard
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_WorkspaceCreationWizard
{
    public:
        /**
        * Constructor
        *@param pWorkspaceTemplateManager - the workspace template manager
        *@param initialDirectory - the initial directory
        *@param workspaceExtension - the workspace extension
        *@param modify - if TRUE, the modification are allowed on the wizard
        */
        PSS_WorkspaceCreationWizard(PSS_WorkspaceWizardTemplateManager* pWorkspaceTemplateManager = NULL,
                                    const CString&                      initialDirectory          = _T(""),
                                    const CString&                      workspaceExtension        = _T(""),
                                    bool                                modify                    = false);

        virtual ~PSS_WorkspaceCreationWizard();

        /**
        * Gets the workspace name
        *@return the workspace name
        */
        virtual inline CString GetWorkspaceName() const;

        /**
        * Gets the workspace directory
        *@return the workspace directory
        */
        virtual inline CString GetDirectory() const;

        /**
        * Gets the workspace file name
        *@return the workspace file name
        */
        virtual inline CString GetWorkspaceFileName() const;

        /**
        * Show dialog in modal mode
        *@return modal result
        */
        virtual int DoModal();

    private:
        PSS_WorkspaceWizardTemplateManager* m_pWorkspaceTemplateManager;
        CString                             m_InitialDirectory;
        CString                             m_WorkspaceName;
        CString                             m_Directory;
        CString                             m_WorkspaceFileName;
        CString                             m_WorkspaceExtension;
        bool                                m_Modify;
};

//---------------------------------------------------------------------------
// PSS_WorkspaceCreationWizard
//---------------------------------------------------------------------------
CString PSS_WorkspaceCreationWizard::GetWorkspaceName() const
{
    return m_WorkspaceName;
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceCreationWizard::GetDirectory() const
{
    return m_Directory;
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceCreationWizard::GetWorkspaceFileName() const
{
    return m_WorkspaceFileName;
}
//---------------------------------------------------------------------------

/**
* Workspace creation wizard start dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_WorkspaceStartDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param initialDirectory - the initial directory
        *@param workspaceExtension - the workspace extension
        *@param modify - if TRUE, the modification are allowed on the wizard
        *@param pParent - parent window, can be NULL
        */
        PSS_WorkspaceStartDlg(const CString& initialDirectory   = _T(""),
                              const CString& workspaceExtension = _T(""),
                              bool           modify             = false,
                              CWnd*          pParent            = NULL);

        virtual ~PSS_WorkspaceStartDlg();

        /**
        * Gets the workspace name
        *@return the workspace name
        */
        virtual inline CString GetWorkspaceName() const;

        /**
        * Gets the workspace directory
        *@return the workspace directory
        */
        virtual inline CString GetDirectory() const;

        /**
        * Gets the workspace file name
        *@return the workspace file name
        */
        virtual inline CString GetWorkspaceFileName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_WorkspaceStartDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_WorkspaceStartDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnChangeWorkspaceName();
        afx_msg void OnChangeWorkspaceFolder();
        afx_msg void OnNext();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog Data
        */
        enum
        {
            IDD = IDD_WZ_WORKSPACE_START
        };

        PSS_SearchEdit m_Directory;
        CString        m_WorkspaceName;
        CString        m_InitialDirectory;
        CString        m_DirectoryStr;
        CString        m_WorkspaceExtension;
        CString        m_WorkspaceFileName;
        bool           m_Modify;
        bool           m_HasChanged;

        /**
        * Validates the dialog
        */
        bool Validate();
};
//---------------------------------------------------------------------------
// PSS_WorkspaceStartDlg
//---------------------------------------------------------------------------
CString PSS_WorkspaceStartDlg::GetWorkspaceName() const
{
    return m_WorkspaceName;
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceStartDlg::GetDirectory() const
{
    return m_DirectoryStr;
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceStartDlg::GetWorkspaceFileName() const
{
    return m_WorkspaceFileName;
}
//---------------------------------------------------------------------------

/**
* Workspace creation wizard template dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_WorkspaceTemplateDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param pWorkspaceTemplateManager - the workspace temlate manager
        *@param pParent - parent window, can be NULL
        */
        PSS_WorkspaceTemplateDlg(PSS_WorkspaceWizardTemplateManager* pWorkspaceTemplateManager = NULL, CWnd* pParent = NULL);

        virtual ~PSS_WorkspaceTemplateDlg();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_WorkspaceTemplateDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_WorkspaceTemplateDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnClickWksTemplatelist(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblclkWksTemplatelist(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnRclickWksTemplatelist(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnRdblclkWksTemplatelist(NMHDR* pNMHDR, LRESULT* pResult);
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZ_WORKSPACE_TEMPLATE
        };

        PSS_WorkspaceWizardTemplateManager* m_pWorkspaceTemplateManager;
        PSS_WorkspaceTemplateListCtrl       m_TemplateList;
        CString                             m_Comment;
        CString                             m_WorkspaceExtension;

        /**
        * Notify that selection has changed
        */
        void SelChanged();
};

#endif
