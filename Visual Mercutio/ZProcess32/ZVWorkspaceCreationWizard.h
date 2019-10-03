// ZVWorkspaceCreationWizard.h: interface for the ZVWorkspaceCreationWizard class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVWORKSPACECREATIONWIZARD_H__5DA4C599_18FB_4411_B32C_FA6E5C4462DB__INCLUDED_)
#define AFX_ZVWORKSPACECREATIONWIZARD_H__5DA4C599_18FB_4411_B32C_FA6E5C4462DB__INCLUDED_

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
#include "Resource.h"

// forward class declaration
class PSS_WorkspaceWizardTemplateManager;

class ZVWorkspaceCreationWizard
{
public:

    ZVWorkspaceCreationWizard(PSS_WorkspaceWizardTemplateManager* pWorkspaceTemplateManager = NULL,
                              const CString                InitialDirectory = _T(""),
                              const CString                WorkspaceExtension = _T(""),
                              bool                            Modify = false);

    virtual ~ZVWorkspaceCreationWizard();

    CString GetWorkspaceName() const
    {
        return m_WorkspaceName;
    };

    CString GetDirectory() const
    {
        return m_Directory;
    };

    CString GetWorkspaceFilename() const
    {
        return m_WorkspaceFilename;
    };

    int DoModal();

private:

    CString                             m_InitialDirectory;
    bool                                m_Modify;
    CString                             m_WorkspaceName;
    CString                             m_Directory;
    CString                             m_WorkspaceFilename;
    CString                             m_WorkspaceExtension;
    PSS_WorkspaceWizardTemplateManager* m_pWorkspaceTemplateManager;
};

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceStart dialog

class ZVWorkspaceStart : public PSS_WizardDialog
{
    // Construction
public:

    // Standard constructor
    ZVWorkspaceStart(const CString    InitialDirectory = _T(""),
                     const CString    WorkspaceExtension = _T(""),
                     bool            Modify = false,
                     CWnd*            pParent = NULL);

    CString GetWorkspaceName() const
    {
        return m_WorkspaceName;
    };

    CString GetDirectory() const
    {
        return m_DirectoryStr;
    };

    CString GetWorkspaceFilename() const
    {
        return m_WorkspaceFilename;
    };

private:

    // Dialog Data
    //{{AFX_DATA(ZVWorkspaceStart)
    enum
    {
        IDD = IDD_WZ_WORKSPACE_START
    };
    PSS_SearchEdit m_Directory;
    CString        m_WorkspaceName;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVWorkspaceStart)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVWorkspaceStart)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnNext();
    afx_msg void OnChangeWorkspaceName();
    afx_msg void OnChangeWorkspaceFolder();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    bool Validate();

private:

    CString    m_InitialDirectory;
    CString    m_DirectoryStr;
    bool    m_Modify;
    bool    m_HasChanged;
    CString    m_WorkspaceExtension;
    CString    m_WorkspaceFilename;
};

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceTemplate dialog

class ZVWorkspaceTemplate : public PSS_WizardDialog
{
    // Construction
public:

    // Standard constructor
    ZVWorkspaceTemplate(PSS_WorkspaceWizardTemplateManager* pWorkspaceTemplateManager = NULL,
                        CWnd*                               pParent = NULL);

    /**
    * Dialog resources
    */
    enum
    {
        IDD = IDD_WZ_WORKSPACE_TEMPLATE
    };

    PSS_WorkspaceTemplateListCtrl m_TemplateList;
    CString                       m_Comment;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVWorkspaceTemplate)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVWorkspaceTemplate)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnClickWksTemplatelist(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkWksTemplatelist(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRclickWksTemplatelist(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRdblclkWksTemplatelist(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    void SelChanged();

private:

    PSS_WorkspaceWizardTemplateManager* m_pWorkspaceTemplateManager;
    CString                             m_WorkspaceExtension;
};

#endif
