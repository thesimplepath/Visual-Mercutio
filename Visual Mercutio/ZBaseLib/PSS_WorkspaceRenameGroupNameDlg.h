/****************************************************************************
 * ==> PSS_WorkspaceRenameGroupNameDlg -------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace rename group name dialog box          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceRenameGroupNameDlgH
#define PSS_WorkspaceRenameGroupNameDlgH

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
* Workspace rename group name dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_WorkspaceRenameGroupNameDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param groupName - group name
        *@param pParentGroup - parent group, can be NULL
        *@param pParent - parent window, can be NULL
        */
        PSS_WorkspaceRenameGroupNameDlg(const CString& groupName, ZBWorkspaceGroupEntity* pParentGroup = NULL, CWnd* pParent = NULL);

        /**
        * Gets the group name
        *@return the group name
        */
        virtual inline CString GetGroupName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_WorkspaceRenameGroupNameDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_WorkspaceRenameGroupNameDlg)
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
            IDD = IDD_WKS_RENAMEGROUP
        };

        ZBWorkspaceGroupEntity* m_pParentGroup;
        CString                 m_GroupName;
};

//---------------------------------------------------------------------------
// PSS_WorkspaceRenameGroupNameDlg
//---------------------------------------------------------------------------
CString PSS_WorkspaceRenameGroupNameDlg::GetGroupName() const
{
    return m_GroupName;
}
//---------------------------------------------------------------------------

#endif
