/****************************************************************************
 * ==> PSS_RulesView -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a rules view                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RulesViewH
#define PSS_RulesViewH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zModel\PSS_RulesTreeCtrl.h"

/**
* Rules view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_RulesView : public CWnd,
                      public PSS_Subject,
                      public PSS_Observer
{
    DECLARE_DYNCREATE(PSS_RulesView)

    public:
        PSS_RulesView();
        virtual ~PSS_RulesView();

        /**
        * Releases the view content
        */
        virtual void Release();

        /**
        * Checks if a rule may be added to the view
        *@return true if a rule may be added to the view, otherwise false
        */
        virtual bool CanAddRule();

        /**
        * Checks if a rule may be renamed in the view
        *@return true if a rule may be renamed in the view, otherwise false
        */
        virtual bool CanRenameRule();

        /**
        * Checks if a rule may be deleted from the view
        *@return true if a rule may be deleted from the view, otherwise false
        */
        virtual bool CanDeleteRule();

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
        * Called when a rule is added to the view
        */
        virtual void OnAddRule();

        /**
        * Called when a rule is renamed in the view
        */
        virtual void OnRenameRule();

        /**
        * Called when a rule is deleted from the view
        */
        virtual void OnDeleteRule();

        /**
        * Called when a rule is moved in the view
        */
        virtual void OnMoveRule();

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
        class IRulesFlatToolBar : public CStatic, public PSS_Subject
        {
            public:
                IRulesFlatToolBar();
                virtual ~IRulesFlatToolBar();

            protected:
                /// ClassWizard generated virtual function overrides
                //{{AFX_VIRTUAL(IRulesFlatToolBar)
                virtual BOOL PreTranslateMessage(MSG* pMsg);
                virtual void PreSubclassWindow();
                //}}AFX_VIRTUAL

                /// Generated message map functions
                //{{AFX_MSG(IRulesFlatToolBar)
                afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
                afx_msg void OnAddRuleButton();
                afx_msg void OnRenameRuleButton();
                afx_msg void OnDeleteRuleButton();
                afx_msg void OnMoveRuleButton();
                afx_msg void OnPropertiesButton();
                afx_msg void OnRefreshButton();
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

            private:
                CCJFlatButton    m_RefreshButton;
                CCJFlatButton    m_AddRuleButton;
                CCJFlatButton    m_RenameRuleButton;
                CCJFlatButton    m_DeleteRuleButton;
                CCJFlatButton    m_MoveRuleButton;
                CCJFlatButton    m_PropertiesButton;
                CToolTipCtrl     m_ToolTip;
                CImageList       m_ImageList;
        };

        /// Generated message map functions
        //{{AFX_MSG(PSS_RulesView)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        IRulesFlatToolBar m_FlatToolBar;
        PSS_RulesTreeCtrl m_Ctrl;
        COLORREF          m_ClrBtnFace;
};

#endif
