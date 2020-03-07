/****************************************************************************
 * ==> PSS_InputAttributesView ---------------------------------------------*
 ****************************************************************************
 * Description : Provides an input attributes view                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InputAttributesViewH
#define PSS_InputAttributesViewH

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
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "PSS_InputAttributesList.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_ProcessGraphModelDoc;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Input attributes view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InputAttributesView : public CWnd,
                                              public PSS_Subject,
                                              public PSS_Observer
{
    DECLARE_DYNCREATE(PSS_InputAttributesView)

    public:
        /**
        * Flat toolbar
        *@author Dominique Aigroz, Jean-Milost Reymond
        */
        class IFlatToolbar : public CStatic,
                             public PSS_Subject
        {
            public:
                IFlatToolbar();
                virtual ~IFlatToolbar();

            protected:
                /// ClassWizard generated virtual function overrides
                //{{AFX_VIRTUAL(IFlatToolbar)
                virtual BOOL PreTranslateMessage(MSG* pMsg);
                virtual void PreSubclassWindow();
                //}}AFX_VIRTUAL

                /// Generated message map functions
                //{{AFX_MSG(IFlatToolbar)
                afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
                afx_msg void OnRefreshButton();
                afx_msg void OnAddInputAttributeButton();
                afx_msg void OnDeleteInputAttributeButton();
                afx_msg void OnModifyInputAttributeButton();
                afx_msg void OnShowSymbolAttributeButton();
                afx_msg void OnShowAllAttributeButton();
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

            private:
                CCJFlatButton m_RefreshButton;
                CCJFlatButton m_AddInputAttributeButton;
                CCJFlatButton m_DeleteInputAttributeButton;
                CCJFlatButton m_ModifyInputAttributeButton;
                CCJFlatButton m_ShowSymbolAttributeButton;
                CCJFlatButton m_ShowAllAttributeButton;
                CImageList    m_ImageList;
                CToolTipCtrl  m_Tooltip;
        };

        PSS_InputAttributesView();
        virtual ~PSS_InputAttributesView();

        /**
        * Initializes the view
        *@param pInputManager - the distribution manager
        *@param pPropManager - the properties manager
        */
        virtual inline void Initialize(PSS_InputAttributeManager* pInputManager, ZBDynamicPropertiesManager* pPropManager);

        /**
        * Sets the symbol reference
        *@param value - the symbol reference
        *@param refresh - if true, the window will be refreshed immediately
        */
        virtual inline void SetSymbolRef(int value, bool refresh = true);

        /**
        * Gets the selected input attribute
        *@return the selected input attribute, NULL if no selection or on error
        */
        virtual inline PSS_InputAttribute* GetSelectedInputAttribute();

        /**
        * Shows all the items
        *@param value - if true, all the items will be shown
        *@param refresh - if true, the window will be refreshed immediately
        */
        virtual inline void ShowAll(bool value = true, bool refresh = true);

        /**
        * Refreshes the view
        */
        virtual void Refresh();

        /**
        * Empties the window content
        */
        virtual void Empty();

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        // Generated message map functions
        //{{AFX_MSG(PSS_InputAttributesView)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Called when an input attribute is added
        */
        virtual void OnAddInputAttribute();

        /**
        * Called when an input attribute is deleted
        */
        virtual void OnDeleteInputAttribute();

        /**
        * Called when an input attribute is modified
        */
        virtual void OnModifyInputAttribute();

        /**
        * Called when the view is refreshed
        */
        virtual void OnRefresh();

    private:
        IFlatToolbar              m_FlatToolBar;
        PSS_InputAttributesList   m_ListCtrl;
        PSS_ProcessGraphModelDoc* m_pCurrentDoc;
        int                       m_SymbolRef;
};

//---------------------------------------------------------------------------
// PSS_InputAttributesView
//---------------------------------------------------------------------------
void PSS_InputAttributesView::Initialize(PSS_InputAttributeManager* pInputManager, ZBDynamicPropertiesManager* pPropManager)
{
    m_ListCtrl.Initialize(pInputManager, pPropManager);
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::SetSymbolRef(int value, bool refresh)
{
    if (::IsWindow(m_ListCtrl.GetSafeHwnd()))
        m_ListCtrl.SetSymbolRef(value, refresh);
}
//---------------------------------------------------------------------------
PSS_InputAttribute* PSS_InputAttributesView::GetSelectedInputAttribute()
{
    return m_ListCtrl.GetSelectedInputAttribute();
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::ShowAll(bool value, bool refresh)
{
    CWaitCursor cursor;

    if (::IsWindow(m_ListCtrl.GetSafeHwnd()))
        m_ListCtrl.ShowAll(value, refresh);
}
//---------------------------------------------------------------------------

#endif
