// ZVWorkspaceCreationWizard.h: interface for the ZVWorkspaceCreationWizard class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVWORKSPACECREATIONWIZARD_H__5DA4C599_18FB_4411_B32C_FA6E5C4462DB__INCLUDED_)
#define AFX_ZVWORKSPACECREATIONWIZARD_H__5DA4C599_18FB_4411_B32C_FA6E5C4462DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\ZWizard.h"
#include "Resource.h"
#include "zWinUtil32\ZSearchEdit.h"
#include "zWinUtil32\ZCWorkspaceTemplateList.h"

// JMR-MODIF - Le 14 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Forward class declaration
class ZBWorkspaceWizardTemplateMg;

class ZVWorkspaceCreationWizard
{
public:

    ZVWorkspaceCreationWizard( ZBWorkspaceWizardTemplateMg*    pWorkspaceTemplateManager    = NULL,
                               const CString                InitialDirectory            = _T( "" ),
                               const CString                WorkspaceExtension            = _T( "" ),
                               bool                            Modify                        = false );

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

    CString                            m_InitialDirectory;
    bool                            m_Modify;
    CString                            m_WorkspaceName;
    CString                            m_Directory;
    CString                            m_WorkspaceFilename;
    CString                            m_WorkspaceExtension;
    ZBWorkspaceWizardTemplateMg*    m_pWorkspaceTemplateManager;
};

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceStart dialog

class ZVWorkspaceStart : public ZIWizardDialog
{
// Construction
public:

    // Standard constructor
    ZVWorkspaceStart( const CString    InitialDirectory    = _T( "" ),
                      const CString    WorkspaceExtension    = _T( "" ),
                      bool            Modify                = false,
                      CWnd*            pParent                = NULL);

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
    enum { IDD = IDD_WZ_WORKSPACE_START };
    ZCSearchEdit    m_Directory;
    CString    m_WorkspaceName;
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

class ZVWorkspaceTemplate : public ZIWizardDialog
{
// Construction
public:

    // Standard constructor
    ZVWorkspaceTemplate( ZBWorkspaceWizardTemplateMg*    pWorkspaceTemplateManager    = NULL,
                         CWnd*                            pParent                        = NULL);

    // Dialog Data
    //{{AFX_DATA(ZVWorkspaceTemplate)
    enum { IDD = IDD_WZ_WORKSPACE_TEMPLATE };
    ZCWorkspaceTemplateList    m_TemplateList;
    CString    m_Comment;
    //}}AFX_DATA

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

    CString                            m_WorkspaceExtension;
    ZBWorkspaceWizardTemplateMg*    m_pWorkspaceTemplateManager;
};

#endif // !defined(AFX_ZVWORKSPACECREATIONWIZARD_H__5DA4C599_18FB_4411_B32C_FA6E5C4462DB__INCLUDED_)