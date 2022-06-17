/****************************************************************************
 * ==> PSS_PrestationsView -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a prestations view                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PrestationsViewH
#define PSS_PrestationsViewH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zModel\PSS_PrestationsTreeCtrl.h"

/**
* Prestations view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_PrestationsView : public CWnd,
                            public PSS_Subject,
                            public PSS_Observer
{
    DECLARE_DYNCREATE(PSS_PrestationsView)

    public:
        /**
        * Prestations flat toolbar
        */
        class IPrestationsFlatToolBar : public CStatic, public PSS_Subject
        {
            public:
                IPrestationsFlatToolBar();
                virtual ~IPrestationsFlatToolBar();

            protected:
                /// Generated virtual functions
                //{{AFX_VIRTUAL(IPrestationsFlatToolBar)
                virtual BOOL PreTranslateMessage(MSG* pMsg);
                virtual void PreSubclassWindow();
                //}}AFX_VIRTUAL

                /// Generated message map
                //{{AFX_MSG(IPrestationsFlatToolBar)
                afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
                afx_msg void OnAddPrestationButton();
                afx_msg void OnRenamePrestationButton();
                afx_msg void OnDeletePrestationButton();
                afx_msg void OnMovePrestationButton();
                afx_msg void OnPropertiesButton();
                afx_msg void OnRefreshButton();
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

            private:
                CToolTipCtrl  m_ToolTip;
                CCJFlatButton m_RefreshButton;
                CCJFlatButton m_AddPrestationButton;
                CCJFlatButton m_RenamePrestationButton;
                CCJFlatButton m_DeletePrestationButton;
                CCJFlatButton m_MovePrestationButton;
                CCJFlatButton m_PropertiesButton;
                CImageList    m_ImageList;
        };

        PSS_PrestationsView();
        virtual ~PSS_PrestationsView();

        /**
        * Releases the view content
        */
        virtual void Release();

        /**
        * Checks if a prestation may be added to the view
        *@return true if a prestation may be added to the view, otherwise false
        */
        virtual bool CanAddPrestation();

        /**
        * Checks if a prestation may be renamed in the view
        *@return true if a prestation may be renamed in the view, otherwise false
        */
        virtual bool CanRenamePrestation();

        /**
        * Checks if a prestation may be deleted from the view
        *@return true if a prestation may be deleted from the view, otherwise false
        */
        virtual bool CanDeletePrestation();

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
        * Called when a prestation is added to the view
        */
        virtual void OnAddPrestation();

        /**
        * Called when a prestation is renamed in the view
        */
        virtual void OnRenamePrestation();

        /**
        * Called when a prestation is deleted from the view
        */
        virtual void OnDeletePrestation();

        /**
        * Called when a prestation is moved in the view
        */
        virtual void OnMovePrestation();

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
        /// Generated message map functions
        //{{AFX_MSG(PSS_PrestationsView)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        IPrestationsFlatToolBar m_FlatToolBar;
        PSS_PrestationsTreeCtrl m_Ctrl;
        COLORREF                m_ClrBtnFace;
};

#endif
