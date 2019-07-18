#if !defined(AFX_USERINFODLG_H__86779DB3_9804_11D3_966B_0000B45D7C6F__INCLUDED_)
#define AFX_USERINFODLG_H__86779DB3_9804_11D3_966B_0000B45D7C6F__INCLUDED_

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
#include "zBaseLib\ZUser.h"

// resources
#include "zWinUtil32Res.h"

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
// ZIUserInformationDialog dialog

class AFX_EXT_CLASS ZIUserInformationDialog : public ZIDialog
{
// Construction
public:
    ZIUserInformationDialog(ZUser& User, bool CreationMode = false, CWnd* pParent = NULL);   // standard constructor


private:
// Dialog Data
    //{{AFX_DATA(ZIUserInformationDialog)
    enum { IDD = IDD_USERINFO };
    BOOL    m_Admin;
    CString    m_Departement;
    CString    m_Description;
    CString    m_DisplayName;
    CString    m_Responsible;
    CString    m_Username;
    CString    m_EMail;
    //}}AFX_DATA

private:
    ZUser&    m_User;
    bool    m_CreationMode;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIUserInformationDialog)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZIUserInformationDialog)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERINFODLG_H__86779DB3_9804_11D3_966B_0000B45D7C6F__INCLUDED_)
