// actIattr.h : header file
//

#ifndef ActIAttr_h
#define ActIAttr_h 1

// processsoft
#include "zBaseLib\ZWizard.h"
#include "zBaseLib\ZUMail.h"
#include "zBaseLib\UserMng.h"
#include "zEvent\Activity.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIActivityAttributionValueInput dialog

class ZIActivityAttributionValueInput : public ZIWizardDialog
{
// Construction
public:
    ZIActivityAttributionValueInput(    ZUUserManager& UserManager, ZUMail& Mail, ZActivity* pActivity, 
                                BOOL LastActivity, 
                                BOOL UserAttribution = TRUE, 
                                BOOL TimeAttribution = TRUE, 
                                BOOL VisibilityAttribution = TRUE, CWnd* pParent = NULL);    // standard constructor
    ZActivity*         GetActivity() { return m_pActivity; };

// Dialog Data
    //{{AFX_DATA(ZIActivityAttributionValueInput)
    enum { IDD = IDD_WZTIMERESOURCE_ATTR };
    CListBox    m_UserList;
    CString    m_ActivityName;
    UINT    m_TimeOutDays;
    int        m_VisibilityType;
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(ZIActivityAttributionValueInput)
    virtual BOOL OnInitDialog();
    afx_msg void OnNext();
    afx_msg void OnAddUser();
    afx_msg void OnDeleteUser();
    afx_msg void OnSelChangeUserList();
    virtual void OnOK();
    afx_msg void OnAddEmail();
    afx_msg void OnVisibilityType();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    
private:
    ZUUserManager&    m_UserManager;
    ZUMail&         m_Mail;
    ZActivity*         m_pActivity;
    BOOL             m_LastActivity;
    BOOL             m_UserAttribution;
    BOOL             m_TimeAttribution;     
    BOOL             m_VisibilityAttribution;
private:
    void    CheckControlState();
    void     SaveState();
    BOOL     CheckData();
};



#endif
