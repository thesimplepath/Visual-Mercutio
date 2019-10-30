/****************************************************************************
 * ==> PSS_ActivityAttributionInputBackupDialog ----------------------------*
 ****************************************************************************
 * Description : Provides an activity attribution input backup dialog box   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityAttributionInputBackupDialogH
#define PSS_ActivityAttributionInputBackupDialogH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_WizardDialog.h"
#include "zBaseLib\PSS_Mail.h"
#include "zBaseLib\PSS_UserManager.h"
#include "zEvent\Activity.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

/**
* Activity attribution input backup dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ActivityAttributionInputBackupDialog : public PSS_WizardDialog
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
        PSS_ActivityAttributionInputBackupDialog(PSS_UserManager& userManager,
                                                 PSS_Mail&        mail,
                                                 ZActivity*       pActivity,
                                                 BOOL             lastActivity,
                                                 CWnd*            pParent = NULL);

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
        //{{AFX_MSG(PSS_ActivityAttributionInputBackupDialog)
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
        PSS_UserManager& m_UserManager;
        PSS_Mail&        m_Mail;
        ZActivity*       m_pActivity;
        CListBox         m_UserList;
        CString          m_ActivityName;
        BOOL             m_LastActivity;

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
// PSS_ActivityAttributionInputBackupDialog
//---------------------------------------------------------------------------
ZActivity* PSS_ActivityAttributionInputBackupDialog::GetActivity()
{
    return m_pActivity;
}
//---------------------------------------------------------------------------

#endif
