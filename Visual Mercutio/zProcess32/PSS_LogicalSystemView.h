/****************************************************************************
 * ==> PSS_LogicalSystemView -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a logical system view                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LogicalSystemViewH
#define PSS_LogicalSystemViewH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zModel\PSS_LogicalSystemTreeCtrl.h"

/**
* Logical system view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_LogicalSystemView : public CWnd,
                              public PSS_Subject,
                              public PSS_Observer
{
    DECLARE_DYNCREATE(PSS_LogicalSystemView)

    public:
        PSS_LogicalSystemView();
        virtual ~PSS_LogicalSystemView();

        /**
        * Releases the view content
        */
        virtual void Release();

        /**
        * Checks if a system may be added to the view
        *@return true if a system may be added to the view, otherwise false
        */
        virtual bool CanAddSystem();

        /**
        * Checks if a system may be renamed in the view
        *@return true if a system may be renamed in the view, otherwise false
        */
        virtual bool CanRenameSystem();

        /**
        * Checks if a system may be deleted from the view
        *@return true if a system may be deleted from the view, otherwise false
        */
        virtual bool CanDeleteSystem();

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
        * Called when a branch should be expanded
        */
        virtual void OnExpandBranch();

        /**
        * Called when a branch should be collapsed
        */
        virtual void OnCollapseBranch();

        /**
        * Called when a system is added to the view
        */
        virtual void OnAddSystem();

        /**
        * Called when a system is renamed in the view
        */
        virtual void OnRenameSystem();

        /**
        * Called when a system is deleted from the view
        */
        virtual void OnDeleteSystem();

        /**
        * Called when a system is moved in the view
        */
        virtual void OnMoveSystem();

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
        * Logical system flat toolbar
        */
        class ILogicalSystemFlatToolBar : public CStatic, public PSS_Subject
        {
            public:
                ILogicalSystemFlatToolBar();
                virtual ~ILogicalSystemFlatToolBar();

            protected:
                /// Generated virtual functions
                //{{AFX_VIRTUAL(ILogicalSystemFlatToolBar)
                virtual BOOL PreTranslateMessage(MSG* pMsg);
                virtual void PreSubclassWindow();
                //}}AFX_VIRTUAL

                /// Generated message map functions
                //{{AFX_MSG(ILogicalSystemFlatToolBar)
                afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
                afx_msg void OnAddSystemButton();
                afx_msg void OnRenameSystemButton();
                afx_msg void OnDeleteSystemButton();
                afx_msg void OnMoveSystemButton();
                afx_msg void OnPropertiesButton();
                afx_msg void OnRefreshButton();
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

            private:
                CCJFlatButton m_RefreshButton;
                CCJFlatButton m_AddSystemButton;
                CCJFlatButton m_RenameSystemButton;
                CCJFlatButton m_DeleteSystemButton;
                CCJFlatButton m_MoveSystemButton;
                CCJFlatButton m_PropertiesButton;
                CToolTipCtrl  m_ToolTip;
                CImageList    m_ImageList;
        };

        /// Generated message map functions
        //{{AFX_MSG(PSS_LogicalSystemView)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        ILogicalSystemFlatToolBar m_FlatToolBar;
        PSS_LogicalSystemTreeCtrl m_Ctrl;
        COLORREF                  m_ClrBtnFace;
};

#endif
