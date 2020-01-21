/****************************************************************************
 * ==> PSS_SelectUserGroupDlg ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a select user group dialog box                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectUserGroupDlgH
#define PSS_SelectUserGroupDlgH

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
#include "PSS_UserGroupTreeCtrl.h"

// resources
#include "zModelRes.h"

// class name mapping
#ifndef PSS_UserEntity
    #define PSS_UserEntity ZBUserEntity
#endif
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif

// forward class declaration
class PSS_UserEntity;
class PSS_UserGroupEntity;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Select user group dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SelectUserGroupDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param title - the title
        *@param pMainUserGroup - the main user group
        *@param allowGroupSelection - if true, the group selection is allowed
        *@param allowRoleSelection - if true, the role selection is allowed
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectUserGroupDlg(const CString&       title               = _T(""),
                               PSS_UserGroupEntity* pMainUserGroup      = NULL,
                               bool                 allowGroupSelection = true,
                               bool                 allowRoleSelection  = true,
                               CWnd*                pParent             = NULL);

        /**
        * Constructor
        *@param titleID - the title resources identifier
        *@param pMainUserGroup - the main user group
        *@param allowGroupSelection - if true, the group selection is allowed
        *@param allowRoleSelection - if true, the role selection is allowed
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectUserGroupDlg(UINT                 titleID,
                               PSS_UserGroupEntity* pMainUserGroup,
                               bool                 allowGroupSelection = true,
                               bool                 allowRoleSelection  = true,
                               CWnd*                pParent             = NULL);

        virtual ~PSS_SelectUserGroupDlg();

        /**
        * Release the dialog box content
        */
        void Release();

        /**
        * Gets the selected user entity
        *@return the selected user entity
        */
        virtual inline PSS_UserEntity* GetSelectedUserEntity() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectUserGroupDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SelectUserGroupDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelchangedUsergroupTree(NMHDR* pNMHDR, LRESULT* pResult);
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_USERGROUP_SELECTION
        };

        PSS_UserEntity*       m_pUserEntity;
        PSS_UserGroupEntity*  m_pMainUserGroup;
        PSS_UserGroupTreeCtrl m_Ctrl;
        CString               m_Title;
        bool                  m_AllowGroupSelection;
        bool                  m_AllowRoleSelection;
};

//---------------------------------------------------------------------------
// PSS_SelectUserGroupDlg
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_SelectUserGroupDlg::GetSelectedUserEntity() const
{
    return m_pUserEntity;
};
//---------------------------------------------------------------------------

#endif
