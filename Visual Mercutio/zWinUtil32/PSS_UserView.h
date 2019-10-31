/****************************************************************************
 * ==> PSS_UserView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user view                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_ZIUserView_H__1D455413_ED45_11D3_96D8_0000B45D7C6F__INCLUDED_)
#define AFX_ZIUserView_H__1D455413_ED45_11D3_96D8_0000B45D7C6F__INCLUDED_

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
#include "zBaseLib\PSS_TreeView.h"
#include "PSS_UserTree.h"

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
* User view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserView : public PSS_TreeView
{
    DECLARE_DYNCREATE(PSS_UserView)

    public:
        PSS_UserView();
        virtual ~PSS_UserView();

        /**
        * Initializes the user view
        *@param pUserManager - user manager
        */
        virtual void Initialize(PSS_UserManager* pUserManager);

        /**
        * Re-initializes the user view
        *@param pUserManager - user manager
        */
        virtual void ReInitialize(PSS_UserManager* pUserManager);

        /**
        * Refreshes the user view
        */
        virtual void Refresh();

        /**
        * Gets the selected user
        *@param the selected user, NULL if no selection or on error
        */
        virtual PSS_User* GetSelectedUser();

        /**
        * Gets the selected departement
        *@param the selected departement, empty string if no selection or on error
        */
        virtual CString GetSelectedDepartement();

        /**
        * Called when selection changed
        */
        virtual void OnSelChangedEvent();

        /**
        * Called when view is clicked
        */
        virtual void OnClickEvent();

        /**
        * Called when view is double-clicked
        */
        virtual void OnDblClickEvent();

        /**
        * Called when view is right clicked
        */
        virtual void OnRightClickEvent();

        /**
        * Called when view is right double-clicked
        */
        virtual void OnRightDblClickEvent();

    protected:
        PSS_UserManager* m_pUserManager;
        PSS_UserTree     m_UserTree;

        /**
        * Gets the no-drop image index
        *@return the no-drop image index
        */
        virtual inline int GetIndexOfNoDropImage() const;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ZIUserView)
        virtual void OnDraw(CDC* pDC);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(ZIUserView)
        afx_msg LRESULT OnInitializeUserManager(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnReloadUserManager(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnRefreshUserManager(WPARAM wParam, LPARAM lParam);
        afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnRightClick(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnRightDblClick(NMHDR* pNMHDR, LRESULT* pResult);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif
};

//---------------------------------------------------------------------------
// PSS_UserView
//---------------------------------------------------------------------------
int PSS_UserView::GetIndexOfNoDropImage() const
{
    return 4;
}
//---------------------------------------------------------------------------

#endif
