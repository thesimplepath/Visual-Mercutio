/****************************************************************************
 * ==> PSS_UserGroupView ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user group view                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserGroupViewH
#define PSS_UserGroupViewH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zModel\PSS_UserGroupTreeCtrl.h"

/**
* User group view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_UserGroupView : public CWnd, public PSS_Subject, public PSS_Observer
{
    DECLARE_DYNCREATE(PSS_UserGroupView)

    public:
        PSS_UserGroupView();
        virtual ~PSS_UserGroupView();

        /**
        * Checks if a group may be added to the view
        *@return true if a group may be added to the view, otherwise false
        */
        virtual bool CanAddGroup();

        /**
        * Checks if a group may be renamed in the view
        *@return true if a group may be renamed in the view, otherwise false
        */
        virtual bool CanRenameGroup();

        /**
        * Checks if a group may be deleted from the view
        *@return true if a group may be deleted from the view, otherwise false
        */
        virtual bool CanDeleteGroup();

        /**
        * Checks if a role may be added to the view
        *@return true if a role may be added to the view, otherwise false
        */
        virtual bool CanAddRole();

        /**
        * Checks if a role may be renamed in the view
        *@return true if a role may be renamed in the view, otherwise false
        */
        virtual bool CanRenameRole();

        /**
        * Checks if a role may be deleted from the view
        *@return true if a role may be deleted from the view, otherwise false
        */
        virtual bool CanDeleteRole();

        /**
        * Checks if the items may be moved
        *@return true if the items may be moved, otherwise false
        */
        virtual bool CanMove();

        /**
        * Checks if the properties may be shown
        *@return true if the properties may be shown, otherwise false
        */
        virtual bool CanProperties();

        /**
        * Checks if the workspace has a context menu
        *@param pWnd - window
        *@param point - hit point
        *@return the context menu identifier
        */
        virtual int HasContextMenu(CWnd* pWnd, const CPoint& point);

        /**
        * Shows the context menu
        *@param pWnd - window
        *@param point - hit point
        *@return the context menu identifier
        */
        virtual void ShowContextMenu(CWnd* pWnd, const CPoint& point);

        /**
        * Called when the view is refreshed
        */
        virtual void OnRefresh();

        /**
        * Called when a group is added to the view
        */
        virtual void OnAddGroup();

        /**
        * Called when a group is renamed in the view
        */
        virtual void OnRenameGroup();

        /**
        * Called when a group is deleted from the view
        */
        virtual void OnDeleteGroup();

        /**
        * Called when a role is added to the view
        */
        virtual void OnAddRole();

        /**
        * Called when a role is renamed in the view
        */
        virtual void OnRenameRole();

        /**
        * Called when a role is deleted from the view
        */
        virtual void OnDeleteRole();

        /**
        * Called when an item is moved in the view
        */
        virtual void OnMove();

        /**
        * Called when the properties are shown
        */
        virtual void OnProperties();

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /**
        * Rules flat toolbar
        */
        class IUserGroupFlatToolBar : public CStatic, public PSS_Subject
        {
            public:
                IUserGroupFlatToolBar();
                virtual ~IUserGroupFlatToolBar();

                /**
                * Refreshes the button immediately
                */
                virtual void RefreshButtonNow();

            protected:
                /// ClassWizard generated virtual function overrides
                //{{AFX_VIRTUAL(IUserGroupFlatToolBar)
                virtual BOOL PreTranslateMessage(MSG* pMsg);
                virtual void PreSubclassWindow();
                //}}AFX_VIRTUAL

                /// Generated message map functions
                //{{AFX_MSG(IUserGroupFlatToolBar)
                afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
                afx_msg void OnAddGroupButton();
                afx_msg void OnRenameGroupButton();
                afx_msg void OnDeleteGroupButton();
                afx_msg void OnAddRoleButton();
                afx_msg void OnRenameRoleButton();
                afx_msg void OnDeleteRoleButton();
                afx_msg void OnMoveButton();
                afx_msg void OnPropertiesButton();
                afx_msg void OnRefreshButton();
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

            private:
                CToolTipCtrl  m_ToolTip;
                CCJFlatButton m_RefreshButton;
                CCJFlatButton m_AddGroupButton;
                CCJFlatButton m_RenameGroupButton;
                CCJFlatButton m_DeleteGroupButton;
                CCJFlatButton m_AddRoleButton;
                CCJFlatButton m_RenameRoleButton;
                CCJFlatButton m_DeleteRoleButton;
                CCJFlatButton m_PropertiesButton;
                CCJFlatButton m_MoveButton;
                CImageList    m_ImageList;
        };

        /// Generated message map functions
        //{{AFX_MSG(PSS_UserGroupView)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        IUserGroupFlatToolBar m_FlatToolBar;
        PSS_UserGroupTreeCtrl m_Ctrl;
        COLORREF              m_ClrBtnFace;
};

#endif
