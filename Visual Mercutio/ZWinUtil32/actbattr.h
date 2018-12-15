// ActBAttr.h : header file
//

#ifndef ActBAttr_h
#define ActBAttr_h 1


#include "zBaseLib\ZWizard.h"

#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif


// ZUMail
#include "zBaseLib\ZUMail.h"

#include "zBaseLib\UserMng.h"

#include "zEvent\Activity.h"



/////////////////////////////////////////////////////////////////////////////
// ZIActivityAttributionBackupInput dialog

class ZIActivityAttributionBackupInput : public ZIWizardDialog
{
// Construction
public:
    ZIActivityAttributionBackupInput(    ZUUserManager& UserManager, ZUMail& Mail, ZActivity* pActivity, 
                                        BOOL LastActivity, 
                                        CWnd* pParent = NULL);    // standard constructor
    ZActivity*         GetActivity() { return m_pActivity; };

// Dialog Data
    //{{AFX_DATA(ZIActivityAttributionBackupInput)
    enum { IDD = IDD_WZBACKRESOURCE_ATTR };
    CListBox    m_UserList;
    CString    m_ActivityName;
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(ZIActivityAttributionBackupInput)
    virtual BOOL OnInitDialog();
    afx_msg void OnNext();
    afx_msg void OnAddUser();
    afx_msg void OnDeleteUser();
    afx_msg void OnSelChangeUserList();
    virtual void OnOK();
    afx_msg void OnAddEmail();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    
private:
    ZUUserManager&    m_UserManager;
    ZUMail&         m_Mail;
    ZActivity*         m_pActivity;
    BOOL             m_LastActivity;

private:
    void    CheckControlState();
    void     SaveState();
    BOOL     CheckData();
};



#endif
