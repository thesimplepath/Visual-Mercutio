/****************************************************************************
 * ==> PSS_ActivityAttributionBackupInputDialog ----------------------------*
 ****************************************************************************
 * Description : Provides an activity attribution backup input dialog box   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityAttributionBackupInputDialogH
#define PSS_ActivityAttributionBackupInputDialogH

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

/**
* Activity attribution backup input dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ActivityAttributionBackupInputDialog : public ZIWizardDialog
{
    public:
        /**
        * Dialog data
        */
        enum
        {
            IDD = IDD_WZBACKRESOURCE_ATTR
        };

        /**
        * Constructor
        *@param userManager - user manager
        *@param mail - mail
        *@param pActivity - activity
        *@param lastActivity - if TRUE, activity is the last activity
        *@param pParent - parent window, can be NULL
        */
        PSS_ActivityAttributionBackupInputDialog(ZUUserManager& userManager,
                                                 ZUMail&        mail,
                                                 ZActivity*     pActivity,
                                                 BOOL           lastActivity,
                                                 CWnd*          pParent = NULL);

        /**
        * Gets the activity
        *@return the activity
        */
        virtual inline ZActivity* GetActivity();

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_ActivityAttributionBackupInputDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnAddUser();
        afx_msg void OnDeleteUser();
        afx_msg void OnSelChangeUserList();
        afx_msg void OnAddEmail();
        virtual void OnOK();
        afx_msg void OnNext();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
    
    private:
        ZUUserManager& m_UserManager;
        ZUMail&        m_Mail;
        ZActivity*     m_pActivity;
        CListBox       m_UserList;
        CString        m_ActivityName;
        BOOL           m_LastActivity;

        /**
        * Checks the control state
        */
        void CheckControlState();

        /**
        * Saves the state
        */
        void SaveState();

        /**
        * Checks the data
        *@return TRUE on success, otherwise FALSE
        */
        BOOL CheckData();
};

//---------------------------------------------------------------------------
// PSS_ActivityAttributionBackupInputDialog
//---------------------------------------------------------------------------
ZActivity* PSS_ActivityAttributionBackupInputDialog::GetActivity()
{
    return m_pActivity;
}
//---------------------------------------------------------------------------

#endif
