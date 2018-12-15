#if !defined(AFX_ZVWORKSPACEFILEPROPERTIES_H__D235F6E1_AFAE_424F_A632_4E7DED827C8A__INCLUDED_)
#define AFX_ZVWORKSPACEFILEPROPERTIES_H__D235F6E1_AFAE_424F_A632_4E7DED827C8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVWorkspaceFileProperties.h : header file
//

#include "zBaseLibRes.h"

// forward class declaration
class ZBWorkspaceGroupEntity;


/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceFileProperties dialog

class ZVWorkspaceFileProperties : public CDialog
{
// Construction
public:
    ZVWorkspaceFileProperties(ZBWorkspaceGroupEntity* pRootGroup = NULL, 
                              const CString Title = "", 
                              const CString CompleteFilename = "", 
                              CWnd* pParent = NULL);   // standard constructor

    CString GetFilename() const
    {
        return m_Filename;
    };
    CString GetFileTitle() const
    {
        return m_FileTitle;
    };
private:
// Dialog Data
    //{{AFX_DATA(ZVWorkspaceFileProperties)
    enum { IDD = IDD_WKS_FILEPROP };
    CString    m_FileTitle;
    CString    m_Filename;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVWorkspaceFileProperties)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVWorkspaceFileProperties)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVWORKSPACEFILEPROPERTIES_H__D235F6E1_AFAE_424F_A632_4E7DED827C8A__INCLUDED_)
