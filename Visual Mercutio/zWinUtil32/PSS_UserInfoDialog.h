/****************************************************************************
 * ==> PSS_UserInfoDialog --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user info dialog box                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserInfoDialogH
#define PSS_UserInfoDialogH

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
#include "zBaseLib\PSS_Dialog.h"
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

/**
* User info dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserInfoDialog : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param user - user
        *@param creationMode - if true, dialog will enter in creation mode
        *@param pParent - parent window, can be NULL
        */
        PSS_UserInfoDialog(ZUser& user, bool creationMode = false, CWnd* pParent = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ZIUserInformationDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(ZIUserInformationDialog)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_USERINFO
        };

        ZUser&  m_User;
        CString m_UserName;
        CString m_Description;
        CString m_EMail;
        CString m_Departement;
        CString m_DisplayName;
        CString m_Responsible;
        BOOL    m_Admin;
        bool    m_CreationMode;
};

#endif
