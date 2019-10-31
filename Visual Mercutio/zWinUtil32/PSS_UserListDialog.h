/****************************************************************************
 * ==> PSS_UserListDialog --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a user list dialog box                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ListUserDialogH
#define PSS_ListUserDialogH

#if _MSC_VER >= 1000
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
#include "zBaseLib\PSS_Dialog.h"
#include "zBaseLib\PSS_UserManager.h"

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
* User list dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserListDialog : public PSS_Dialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_LIST_OF_USERS
        };

        CButton  m_InsertButton;
        CListBox m_UserList;
        CString  m_Description;
        CString  m_Responsible;
        CString  m_EMail;
        CString  m_Departement;
        BOOL     m_IsAdministrator;

        /**
        * Constructor
        *@param userManager - user manager
        *@param pParent - parent window, can be NULL
        */
        PSS_UserListDialog(PSS_UserManager& userManager, CWnd* pParent = NULL);

        /**
        * Gets the selected user
        *@return selected user, NULL if no user selected or on error
        */
        virtual inline PSS_User* GetUser() const;

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_UserListDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnSource();
        afx_msg void OnSelChangeListOfUsers();
        afx_msg void OnDblclkListOfUsers();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_UserManager& m_UserManager;
        PSS_User*        m_pUser;

        /**
        * Loads the source
        */
        void LoadSource();

        /**
        * Checks the control state
        */
        void CheckControlState();
};

//---------------------------------------------------------------------------
// PSS_UserListDialog
//---------------------------------------------------------------------------
PSS_User* PSS_UserListDialog::GetUser() const
{
    return m_pUser;
}
//---------------------------------------------------------------------------

#endif
