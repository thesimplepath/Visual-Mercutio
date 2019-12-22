/****************************************************************************
 * ==> PSS_UserGroupInfoDlg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user group info dialog                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserGroupInfoDlgH
#define PSS_UserGroupInfoDlgH

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

// resources
#include "zModelRes.h"

// forward class declaration
class ZBUserGroupEntity;

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
* User group info dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_UserGroupInfoDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param titleID - the title identifier
        *@param pGroup - the group
        *@param name - the name
        *@param description - the description
        *@param cost - the cost
        *@param isRole - if true, the user group is a role
        *@param modifyMode - if true, the modify mode will be enabled
        *@param pParent - parent window, can be NULL
        */
        PSS_UserGroupInfoDlg(UINT               titleID     = -1,
                             ZBUserGroupEntity* pGroup      = NULL,
                             const CString&     name        = "",
                             const CString&     description = "",
                             const float        cost        = 0,
                             bool               isRole      = false,
                             bool               modifyMode  = false,
                             CWnd*              pParent     = NULL);

        /**
        * Gets the name
        *@return the name
        */
        virtual inline CString GetName() const;

        /**
        * Gets the description
        *@return the description
        */
        virtual inline CString GetDescription() const;

        /**
        * Gets the cost
        *@return the cost
        */
        virtual inline float GetCost() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_UserGroupInfoDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL


        /// Generated message map functions
        //{{AFX_MSG(PSS_UserGroupInfoDlg)
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
            IDD = IDD_UGP_INFO
        };

        ZBUserGroupEntity* m_pGroup;
        CString            m_Title;
        CString            m_Name;
        CString            m_Description;
        CString            m_CostStr;
        float              m_Cost;
        bool               m_IsRole;
        bool               m_ModifyMode;
};

//---------------------------------------------------------------------------
// PSS_UserGroupInfoDlg
//---------------------------------------------------------------------------
CString PSS_UserGroupInfoDlg::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
CString PSS_UserGroupInfoDlg::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
float PSS_UserGroupInfoDlg::GetCost() const
{
    return m_Cost;
}
//---------------------------------------------------------------------------

#endif
