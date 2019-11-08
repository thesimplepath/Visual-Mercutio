/****************************************************************************
 * ==> PSS_ActivityAttributionInputValueDialog -----------------------------*
 ****************************************************************************
 * Description : Provides the activity attribution input value dialog box   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityAttributionInputValueDialogH
#define PSS_ActivityAttributionInputValueDialogH

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
#include "zBaseLib\PSS_WizardDialog.h"
#include "zBaseLib\PSS_Mail.h"
#include "zBaseLib\PSS_UserManager.h"
#include "zEvent\PSS_Activity.h"

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

/**
* Activity attribution input value dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ActivityAttributionInputValueDialog : public PSS_WizardDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZTIMERESOURCE_ATTR
        };

        CListBox m_UserList;
        CString  m_ActivityName;
        UINT     m_TimeOutDays;
        int      m_VisibilityType;

        /**
        * Constructor
        *@param userManager - user manager
        *@param pParent - parent window, can be NULL
        */
        PSS_ActivityAttributionInputValueDialog(PSS_UserManager& userManager,
                                                PSS_Mail&        mail,
                                                PSS_Activity*    pActivity,
                                                BOOL             lastActivity,
                                                BOOL             userAttribution       = TRUE,
                                                BOOL             timeAttribution       = TRUE,
                                                BOOL             visibilityAttribution = TRUE,
                                                CWnd*            pParent               = NULL);

        virtual inline PSS_Activity* GetActivity() const;

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_ActivityAttributionInputValueDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnAddUser();
        afx_msg void OnDeleteUser();
        afx_msg void OnSelChangeUserList();
        virtual void OnOK();
        afx_msg void OnNext();
        afx_msg void OnAddEmail();
        afx_msg void OnVisibilityType();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
    
    private:
        PSS_UserManager& m_UserManager;
        PSS_Mail&        m_Mail;
        PSS_Activity*    m_pActivity;
        BOOL             m_LastActivity;
        BOOL             m_UserAttribution;
        BOOL             m_TimeAttribution;
        BOOL             m_VisibilityAttribution;

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
// PSS_ActivityAttributionInputValueDialog
//---------------------------------------------------------------------------
PSS_Activity* PSS_ActivityAttributionInputValueDialog::GetActivity() const
{
    return m_pActivity;
}
//---------------------------------------------------------------------------

#endif
