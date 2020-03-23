/****************************************************************************
 * ==> PSS_PropertiesView --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a properties view                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertiesViewH
#define PSS_PropertiesViewH

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
#include "PSS_PropertyListCtrl.h"
#include "PSS_PropertyDescription.h"

#ifdef _ZPTYMGREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Properties view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PropertiesView : public CWnd,
                                         public PSS_Subject,
                                         public PSS_Observer
{
    DECLARE_DYNCREATE(PSS_PropertiesView)

    public:
        /**
        * Flat toolbar
        */
        class IFlatToolBar : public CStatic, public PSS_Subject
        {
            public:
                IFlatToolBar();
                virtual ~IFlatToolBar();

            protected:
                /// ClassWizard generated virtual function overrides
                //{{AFX_VIRTUAL(IFlatToolBar)
                virtual BOOL PreTranslateMessage(MSG* pMsg);
                virtual void PreSubclassWindow();
                //}}AFX_VIRTUAL

                /// Generated message map functions
                //{{AFX_MSG(IFlatToolBar)
                afx_msg void OnRefreshButton();
                afx_msg void OnShowAllTypesButton();
                afx_msg void OnShowStaticTypeButton();
                afx_msg void OnShowDynamicTypeButton();
                afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

            private:
                CCJFlatButton m_RefreshButton;
                CCJFlatButton m_ShowAllTypesButton;
                CCJFlatButton m_ShowStaticTypeButton;
                CCJFlatButton m_ShowDynamicTypeButton;
                CImageList    m_ImageList;
                CToolTipCtrl  m_ToolTip;
        };

        PSS_PropertiesView();
        virtual ~PSS_PropertiesView();

        /**
        * Loads the state from the initialization file
        *@param iniFile - the initialization file name
        */
        virtual inline void LoadStateFromIniFile(const CString& iniFile);

        /**
        * Gets the property item at index
        *@param index - the index
        *@return the property item, NULL if not found or on error
        */
        virtual inline PSS_PropertyItem* GetPropertyItem(int index);

        /**
        * Inserts a property item at index
        *@param pPropItem - the property item to insert
        *@param index - the index
        *@return the property item, NULL if not found or on error
        */
        virtual inline void InsertPropertyItem(PSS_PropertyItem* pPropItem, int index = 0);

        /**
        * Sets the property item manager
        *@param pPropItemManager - the property item manager
        */
        virtual inline void SetPropertyItemManager(PSS_PropertyItemManager* pPropItemManager);

        /**
        * Shows the in-place control
        *@param show - if true, the in-place control may be shown
        */
        virtual inline void ShowInPlaceControl(bool show = true);

        /**
        * Resets the view content
        */
        virtual inline void ResetContent();

        /**
        * Refreshes the view content
        */
        virtual inline void Refresh();

        /**
        * Empties the view
        */
        virtual inline void EmptyControl();

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /**
        * Properties view enumeration
        */
        enum IEPropertiesView
        {
            IE_PV_AllTypes    = 0,
            IE_PV_StaticType  = 1,
            IE_PV_DynamicType = 2,
            IE_PV_None        = 3
        };

        /// Generated message map functions
        //{{AFX_MSG(PSS_PropertiesView)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Switches to a view
        *@param view - the view to switch to
        */
        virtual void SwitchToView(IEPropertiesView view = IE_PV_AllTypes);

        /**
        * Refreshes the current view
        */
        virtual void RefreshCurrentView();

        /**
        * Shows all the types
        */
        virtual void ShowAllTypes();

        /**
        * Shows the static type
        */
        virtual void ShowStaticType();

        /**
        * Shows the dynamic type
        */
        virtual void ShowDynamicType();

        /**
        * Called when all types are shown
        */
        virtual void OnShowAllTypes();

        /**
        * Called when the static type is shown
        */
        virtual void OnShowStaticType();

        /**
        * Called when the dynamic type is shown
        */
        virtual void OnShowDynamicType();

        /**
        * Called when the view is refreshed
        */
        virtual void OnRefresh();

        /**
        * Called when the view is emptied
        */
        virtual void OnEmptyControl();

    private:
        IFlatToolBar            m_FlatToolBar;
        IEPropertiesView        m_CurrentView;
        PSS_PropertyListCtrl    m_ListCtrl;
        PSS_PropertyDescription m_PropDesc;
};

//---------------------------------------------------------------------------
// PSS_PropertiesView
//---------------------------------------------------------------------------
void PSS_PropertiesView::LoadStateFromIniFile(const CString& iniFile)
{
    m_ListCtrl.LoadStateFromIniFile(iniFile);
}
//---------------------------------------------------------------------------
PSS_PropertyItem* PSS_PropertiesView::GetPropertyItem(int index)
{
    return m_ListCtrl.GetPropertyItem(index);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::InsertPropertyItem(PSS_PropertyItem* pPropItem, int index)
{
    m_ListCtrl.InsertPropertyItem(pPropItem, index);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::SetPropertyItemManager(PSS_PropertyItemManager* pPropItemManager)
{
    m_ListCtrl.SetPropertyItemManager(pPropItemManager);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::ShowInPlaceControl(bool show)
{
    m_ListCtrl.ShowInPlaceControl(show);
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::ResetContent()
{
    m_ListCtrl.ResetContent();
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::Refresh()
{
    m_ListCtrl.Refresh();
}
//---------------------------------------------------------------------------
void PSS_PropertiesView::EmptyControl()
{
    OnEmptyControl();
}
//---------------------------------------------------------------------------

#endif
