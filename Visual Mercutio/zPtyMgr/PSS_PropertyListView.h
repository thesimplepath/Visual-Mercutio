/****************************************************************************
 * ==> PSS_PropertyListView ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a property list view                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertyListViewH
#define PSS_PropertyListViewH

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
#include "zBaseLib\PSS_Observer.h"
#include "PSS_PropertyListCtrl.h"

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
* Property list controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PropertyListView : public CView,
                                           public PSS_Observer
{
    DECLARE_DYNCREATE(PSS_PropertyListView)

    public:
        /**
        * Sets the property item manager
        *@param pPropItemManager - the property item manager
        */
        virtual inline void SetPropertyItemManager(PSS_PropertyItemManager* pPropItemManager);

        /**
        * Gets a property item at index
        *@param index - the index
        *@return the property item at index, NULL if not found or on error
        */
        virtual inline PSS_PropertyItem* GetPropertyItem(int index);

        /**
        * Inserts a property item at index
        *@param pPropItem - the property item to insert
        *@param index - the index
        */
        virtual inline void InsertPropertyItem(PSS_PropertyItem* pPropItem, int index = 0);

        /**
        * Resets the view content
        */
        virtual inline void ResetContent();

        /**
        * Shows the in-place control
        *@param show - if true, the in-place control may be shown
        */
        virtual inline void ShowInPlaceControl(bool show = true);

        /**
        * Refreshes the view
        */
        virtual inline void Refresh();

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        PSS_PropertyListCtrl m_ListCtrl;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PropertyListView)
        virtual void OnDraw(CDC* pDC);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_PropertyListView)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        PSS_PropertyListView();
        virtual ~PSS_PropertyListView();

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
// PSS_PropertyListView
//---------------------------------------------------------------------------
void PSS_PropertyListView::SetPropertyItemManager(PSS_PropertyItemManager* pPropItemManager)
{
    m_ListCtrl.SetPropertyItemManager(pPropItemManager);
}
//---------------------------------------------------------------------------
PSS_PropertyItem* PSS_PropertyListView::GetPropertyItem(int index)
{
    return m_ListCtrl.GetPropertyItem(index);
}
//---------------------------------------------------------------------------
void PSS_PropertyListView::InsertPropertyItem(PSS_PropertyItem* pPropItem, int index)
{
    m_ListCtrl.InsertPropertyItem(pPropItem, index);
}
//---------------------------------------------------------------------------
void PSS_PropertyListView::ResetContent()
{
    m_ListCtrl.ResetContent();
}
//---------------------------------------------------------------------------
void PSS_PropertyListView::ShowInPlaceControl(bool show)
{
    m_ListCtrl.ShowInPlaceControl(show);
}
//---------------------------------------------------------------------------
void PSS_PropertyListView::Refresh()
{
    m_ListCtrl.Refresh();
}
//---------------------------------------------------------------------------

#endif
