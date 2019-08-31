/****************************************************************************
 * ==> PSS_WorkspaceGroupNameDlg -------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace group name dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceGroupNameDlgH
#define PSS_WorkspaceGroupNameDlgH

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
#include "zBaseLibRes.h"

// forward class declaration
class ZBWorkspaceGroupEntity;

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Workspace group name dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_WorkspaceGroupNameDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param pRootGroup - root group, can be NULL
        *@param groupName - group name
        *@param extensionList - extension list
        *@param pParent - parent window, can be NULL
        */
        PSS_WorkspaceGroupNameDlg(ZBWorkspaceGroupEntity* pRootGroup    = NULL,
                                  const CString&          groupName     = "",
                                  const CString&          extensionList = "",
                                  CWnd*                   pParent       = NULL);

        /**
        * Gets the extensions
        *@return the extensions
        */
        virtual inline CString GetExtensions() const;

        /**
        * Gets the group name
        *@return the group name
        */
        virtual inline CString GetGroupName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_WorkspaceGroupNameDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_WorkspaceGroupNameDlg)
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
            IDD = IDD_WKS_NEWGROUP
        };

        ZBWorkspaceGroupEntity* m_pRootGroup;
        CString                 m_Extensions;
        CString                 m_GroupName;
        bool                    m_Modify;
};

//---------------------------------------------------------------------------
// PSS_WorkspaceGroupNameDlg
//---------------------------------------------------------------------------
CString PSS_WorkspaceGroupNameDlg::GetExtensions() const
{
    return m_Extensions;
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceGroupNameDlg::GetGroupName() const
{
    return m_GroupName;
}
//---------------------------------------------------------------------------

#endif
