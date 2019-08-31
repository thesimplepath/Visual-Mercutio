/****************************************************************************
 * ==> PSS_SelectResourcesDialog -------------------------------------------*
 ****************************************************************************
 * Description : Provides a select resources dialog box                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectResourcesDialogH
#define PSS_SelectResourcesDialogH

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
#include "zBaseLib\ZIDialog.h"
#include "PSS_UserTreeCtrl.h"

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
* Select resources dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SelectResourcesDialog : public ZIDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_CHOOSE_RESOURCE
        };

        PSS_UserTreeCtrl m_ResourceTree;
        CListBox         m_ResourceList;

        /**
        * Constructor
        *@param userManager - user manager
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectResourcesDialog(PSS_UserManager& userManager, CWnd* pParent = NULL);

        /**
        * Gets the user list string
        *@return the user list string
        */
        virtual inline CString GetUserListString() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectResourcesDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SelectResourcesDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnAddResource();
        afx_msg void OnRemoveResource();
        afx_msg void OnSelchangedResourceTree(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnSelchangeResourceList();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_UserManager& m_UserManager;
        CString          m_UserListString;

        /**
        * Checks the control states
        */
        void CheckControlState();
};

//---------------------------------------------------------------------------
// PSS_SelectResourcesDialog
//---------------------------------------------------------------------------
CString PSS_SelectResourcesDialog::GetUserListString() const
{
    return m_UserListString;
}
//---------------------------------------------------------------------------

#endif
