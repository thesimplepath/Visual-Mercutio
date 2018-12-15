#if !defined(AFX_ZVWorkspaceGroupNameDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_)
#define AFX_ZVWorkspaceGroupNameDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVWorkspaceGroupNameDlg.h : header file
//

#include "zBaseLibRes.h"

// forward class declaration
class ZBWorkspaceGroupEntity;


/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceGroupNameDlg dialog

class ZVWorkspaceGroupNameDlg : public CDialog
{
// Construction
public:
    ZVWorkspaceGroupNameDlg(ZBWorkspaceGroupEntity* pRootGroup = NULL, 
                            const CString GroupName = "", 
                            const CString ExtensionList = "", 
                            CWnd* pParent = NULL);   // standard constructor

    CString    GetExtensions() const
    {
        return m_Extensions;
    };
    CString    GetGroupName() const
    {
        return m_GroupName;
    };

private:
// Dialog Data
    //{{AFX_DATA(ZVWorkspaceGroupNameDlg)
    enum { IDD = IDD_WKS_NEWGROUP };
    CString    m_Extensions;
    CString    m_GroupName;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVWorkspaceGroupNameDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVWorkspaceGroupNameDlg)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ZBWorkspaceGroupEntity* m_pRootGroup;
    bool m_Modify;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVWorkspaceGroupNameDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_)
