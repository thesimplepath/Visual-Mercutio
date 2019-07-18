#if !defined(AFX_ZVCHOOSERESOURCES_H__A4AEEEA3_2508_11D4_972C_0000B45D7C6F__INCLUDED_)
#define AFX_ZVCHOOSERESOURCES_H__A4AEEEA3_2508_11D4_972C_0000B45D7C6F__INCLUDED_

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
#include "zBaseLib\ZIDialog.h"
#include "UserTreeC.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVChooseResources dialog

class AFX_EXT_CLASS ZVChooseResources : public ZIDialog
{
// Construction
public:
    ZVChooseResources(ZUUserManager& UserManager, CWnd* pParent = NULL);   // standard constructor

    CString    GetUserListString() const { return m_UserListString; };

// Dialog Data
    //{{AFX_DATA(ZVChooseResources)
    enum { IDD = IDD_CHOOSE_RESOURCE };
    ZCUserTree    m_ResourceTree;
    CListBox    m_ResourceList;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVChooseResources)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVChooseResources)
    afx_msg void OnAddResource();
    afx_msg void OnRemoveResource();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedResourceTree(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnSelchangeResourceList();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ZUUserManager&        m_UserManager;
    CString                m_UserListString;
private:
    void CheckControlState();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVCHOOSERESOURCES_H__A4AEEEA3_2508_11D4_972C_0000B45D7C6F__INCLUDED_)
