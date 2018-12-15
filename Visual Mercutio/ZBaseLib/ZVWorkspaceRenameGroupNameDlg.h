#if !defined(AFX_ZVWorkspaceRenameGroupNameDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_)
#define AFX_ZVWorkspaceRenameGroupNameDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVWorkspaceRenameGroupNameDlg.h : header file
//

#include "zBaseLibRes.h"

// forward class declaration
class ZBWorkspaceGroupEntity;


/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceRenameGroupNameDlg dialog

class ZVWorkspaceRenameGroupNameDlg : public CDialog
{
// Construction
public:
    ZVWorkspaceRenameGroupNameDlg(const CString GroupName, ZBWorkspaceGroupEntity* pParentGroup = NULL, CWnd* pParent = NULL);   // standard constructor

    CString    GetGroupName() const
    {
        return m_GroupName;
    };

private:
// Dialog Data
    //{{AFX_DATA(ZVWorkspaceRenameGroupNameDlg)
    enum { IDD = IDD_WKS_RENAMEGROUP };
    CString    m_GroupName;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVWorkspaceRenameGroupNameDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVWorkspaceRenameGroupNameDlg)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ZBWorkspaceGroupEntity* m_pParentGroup;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVWorkspaceRenameGroupNameDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_)
