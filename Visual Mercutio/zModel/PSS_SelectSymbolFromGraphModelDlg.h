/****************************************************************************
 * ==> PSS_SelectSymbolFromGraphModelDlg -----------------------------------*
 ****************************************************************************
 * Description : Provides a symbol selector from graphic model dialog box   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectSymbolFromGraphModelDlgH
#define PSS_SelectSymbolFromGraphModelDlgH

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

// stingray studio
#include "Views\OdRulerWrapper.h"

// processsoft
#include "zBaseLib\PSS_Dialog.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_ObserverMsg.h"
#include "PSS_SelectableDefs.h"

// class name mapping
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_ProcessGraphModelMdl;

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
* Symbol selector from graphic model dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SelectSymbolFromGraphModelDlg : public PSS_Dialog, public PSS_Observer
{
    public:
        /**
        * Graphic model viewport
        */
        class IGraphModelViewport : public CODBufferedRulerViewport, public PSS_Observer
        {
            public:
                IGraphModelViewport();
                virtual ~IGraphModelViewport();

                /**
                * Creates the controller
                *@return TRUE on success, otherwise FALSE
                */
                virtual BOOL CreateController();

                /**
                * Resizes the viewport to the window
                *@param wnd - the window to resize to
                */
                virtual void ResizeToWnd(const CWnd& wnd);

                /**
                * Called when the observer receives a message from the subject
                *@param pSubject - subject which sent the message
                *@param pMsg - the message
                */
                virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);
        };

        /**
        * Graphic model controller
        */
        class IGraphModelController : public CODController, public PSS_Observer
        {
            public:
                /**
                * Constructor
                *@param pViewport - the viewport
                */
                IGraphModelController(CODViewport* pViewport);

                virtual ~IGraphModelController();

                /**
                * Gets the selected symbol
                *@return the selected symbol, NULL if not found or on error
                */
                virtual inline CODSymbolComponent* GetSelectedSymbol();

                /**
                * Called when the selection changes
                *@param pChangedSet - the changed component set
                */
                virtual void OnSelectionChange(CODComponentSet* pChangedSet);

                /**
                * Called when the observer receives a message from the subject
                *@param pSubject - subject which sent the message
                *@param pMsg - the message
                */
                virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

            protected:
                /// Generated message map functions
                //{{AFX_MSG(IGraphModelController)
                afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

                /**
                * Called when the controller is refreshed
                */
                virtual void OnRefresh();

                /**
                * Called when the controller navigates to the up
                */
                virtual void OnGoUp();

            private:
                CODSymbolComponent* m_pSelectedSymbol;

                /**
                * Finds the selected symbol
                *@return the selected symbol, NULL if not found or on error
                */
                CODSymbolComponent* FindSelectedSymbol();
        };

        /**
        * Graphic model window
        */
        class IGraphModelWnd : public CWnd, public PSS_Subject, public PSS_Observer
        {
            public:
                IGraphModelWnd();
                virtual ~IGraphModelWnd();

                /**
                * Initializes the class
                */
                virtual void Initialize();

                /**
                * Gets if the navigation is enabled
                *@return true if the navigation is enabled, otherwise false
                */
                virtual inline bool GetEnableNavigate() const;

                /**
                * Sets if the navigation is enabled
                *@param value - if true, the navigation is enabled
                */
                virtual inline void SetEnableNavigate(bool value);

                /**
                * Gets the window
                *@return the window
                */
                virtual CWnd* GetWnd() const;

                /**
                * Gets the model
                *@return the model
                */
                virtual CODModel* GetModel();

                /**
                * Sets the model
                *@param pModel - the model
                */
                virtual void SetModel(CODModel* pModel);

                /**
                * Sets the current symbol
                *@param pComp - the current symbol component
                */
                virtual void SetCurrentSymbol(CODSymbolComponent* pComp);

                /**
                * Called when the observer receives a message from the subject
                *@param pSubject - subject which sent the message
                *@param pMsg - the message
                */
                virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

            protected:
                stingray::foundation::MvcScrollWrapper_T<IGraphModelViewport> m_DialogViewport;
                CODModel*                                                     m_pModel;

                /// Generated message map functions
                //{{AFX_MSG(_ZVGraphModelWnd)
                afx_msg void OnPaint();
                afx_msg void OnSize(UINT nType, int cx, int cy);
                virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
                virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

            private:
                bool m_EnableNavigate;
        };

        /**
        * Select symbol observer message
        */
        class ISelectSymbolObserverMsg : public PSS_ObserverMsg
        {
            DECLARE_DYNAMIC(ISelectSymbolObserverMsg)

            public:
                /**
                * Constructor
                *@param pComp - the symbol component
                */
                ISelectSymbolObserverMsg(CODSymbolComponent* pComp = NULL);

                virtual ~ISelectSymbolObserverMsg();

                /**
                * Gets the symbol component
                *@return the symbol component
                */
                virtual inline CODSymbolComponent* GetComponent() const;

                /**
                * Sets the symbol component
                *@param pComp - the symbol component
                */
                virtual inline void SetComponent(CODSymbolComponent* pComp);

            private:
                CODSymbolComponent* m_pComp;
        };

        /**
        * Select symbol flat toolbar
        */
        class ISelectSymbolFlatToolBar : public CStatic, public PSS_Subject
        {
            public:
                ISelectSymbolFlatToolBar();
                virtual ~ISelectSymbolFlatToolBar();

                /**
                * Enables or disables the navigation
                *@param enabled - if true, the navigation is enabled
                */
                virtual void EnableNavigate(bool enabled = true);

            protected:
                /// ClassWizard generated virtual function overrides
                //{{AFX_VIRTUAL(ISelectSymbolFlatToolBar)
                virtual BOOL PreTranslateMessage(MSG* pMsg);
                virtual void PreSubclassWindow();
                //}}AFX_VIRTUAL

                /// Generated message map functions
                //{{AFX_MSG(ISelectSymbolFlatToolBar)
                afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
                afx_msg void OnRefreshButton();
                afx_msg void OnGoUpButton();
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

            private:
                CCJFlatButton m_RefreshButton;
                CCJFlatButton m_GoUpButton;
                CImageList    m_ImageList;
                CToolTipCtrl  m_Tooltip;
                bool          m_EnableNavigate;
        };

        /**
        * Constructor
        *@param pModel - the model
        *@param title - the title
        *@param selectableItem - the selectable item type
        *@param enableNavigate - if true, the navigation will be enabled
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectSymbolFromGraphModelDlg(PSS_ProcessGraphModelMdl* pModel,
                                          const CString&            title          = _T(""),
                                          int                       selectableItem = g_Selectable_All,
                                          bool                      enableNavigate = true,
                                          CWnd*                     pParent        = NULL);

        /**
        * Constructor
        *@param pModel - the model
        *@param title - the title
        *@param pSelectableClass - the selectable class type
        *@param enableNavigate - if true, the navigation will be enabled
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectSymbolFromGraphModelDlg(PSS_ProcessGraphModelMdl* pModel,
                                          const CString&            title,
                                          CRuntimeClass*            pSelectableClass,
                                          bool                      enableNavigate = true,
                                          CWnd*                     pParent        = NULL);

        /**
        * Constructor
        *@param pModel - the model
        *@param titleID - the title resources identifier
        *@param selectableItem - the selectable item type
        *@param enableNavigate - if true, the navigation will be enabled
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectSymbolFromGraphModelDlg(PSS_ProcessGraphModelMdl* pModel,
                                          UINT                      titleID,
                                          int                       selectableItem = g_Selectable_All,
                                          bool                      enableNavigate = true,
                                          CWnd*                     pParent        = NULL);

        /**
        * Constructor
        *@param pModel - the model
        *@param titleID - the title resources identifier
        *@param pSelectableClass - the selectable class type
        *@param enableNavigate - if true, the navigation will be enabled
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectSymbolFromGraphModelDlg(PSS_ProcessGraphModelMdl* pModel,
                                          UINT                      titleID,
                                          CRuntimeClass*            pSelectableClass,
                                          bool                      enableNavigate = true,
                                          CWnd*                     pParent        = NULL);

        virtual ~PSS_SelectSymbolFromGraphModelDlg();

        /**
        * Gets the selected symbol
        *@return the selected symbol
        */
        virtual inline CODSymbolComponent* GetSelectedSymbol();

        /**
        * Gets the symbol name
        *@return the symbol name
        */
        virtual inline CString GetSymbolName() const;

        /**
        * Gets the symbol path
        *@return the symbol path
        */
        virtual inline CString GetSymbolPath() const;

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectSymbolFromGraphModelDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SelectSymbolFromGraphModelDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSize(UINT nType, int cx, int cy);
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_ProcessGraphModelMdl* m_pModel;
        CODSymbolComponent*       m_pSelectedSymbol;
        CRuntimeClass*            m_pSelectableClass;
        ISelectSymbolFlatToolBar  m_FlatToolBar;
        IGraphModelWnd            m_WndModelGraph;
        CString                   m_Title;
        CString                   m_SymbolName;
        CString                   m_SymbolPath;
        int                       m_SelectableItem;
        bool                      m_EnableNavigate;

        /**
        * Move the controls to a position
        *@param cx - the x position in pixels
        *@param cy - the y position in pixels
        */
        void MoveControls(int cx, int cy);

        /**
        * Checks the symbol
        *@param pComp - the symbol component to check
        */
        void CheckSymbol(CODSymbolComponent* pComp);
};

//---------------------------------------------------------------------------
// PSS_SelectSymbolFromGraphModelDlg::IGraphModelController
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_SelectSymbolFromGraphModelDlg::IGraphModelController::GetSelectedSymbol()
{
    return m_pSelectedSymbol;
};
//---------------------------------------------------------------------------
// PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd
//---------------------------------------------------------------------------
bool PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::GetEnableNavigate() const
{
    return m_EnableNavigate;
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::SetEnableNavigate(bool value)
{
    m_EnableNavigate = value;
}
//---------------------------------------------------------------------------
// PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolObserverMsg
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolObserverMsg::GetComponent() const
{
    return m_pComp;
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolObserverMsg::SetComponent(CODSymbolComponent* pComp)
{
    m_pComp = pComp;
}
//---------------------------------------------------------------------------
// PSS_SelectSymbolFromGraphModelDlg
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_SelectSymbolFromGraphModelDlg::GetSelectedSymbol()
{
    return m_pSelectedSymbol;
}
//---------------------------------------------------------------------------
CString PSS_SelectSymbolFromGraphModelDlg::GetSymbolName() const
{
    return m_SymbolName;
}
//---------------------------------------------------------------------------
CString PSS_SelectSymbolFromGraphModelDlg::GetSymbolPath() const
{
    return m_SymbolPath;
}
//---------------------------------------------------------------------------

#endif
