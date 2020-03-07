/****************************************************************************
 * ==> PSS_DistributionAttributesView --------------------------------------*
 ****************************************************************************
 * Description : Provides the distribution attributes view                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DistributionAttributesViewH
#define PSS_DistributionAttributesViewH

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
#include "PSS_DistributionAttributesList.h"

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
* Distribution attributes view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DistributionAttributesView : public CWnd,
                                                     public PSS_Subject,
                                                     public PSS_Observer
{
    DECLARE_DYNCREATE(PSS_DistributionAttributesView)

    public:
        /**
        * Flat toolbar
        */
        class IFlatToolbar : public CStatic,
                             public PSS_Subject
        {
            public:
                IFlatToolbar();
                virtual ~IFlatToolbar();

            protected:
                /// ClassWizard generated virtual function overrides
                //{{AFX_VIRTUAL(IFlatToolBar)
                virtual BOOL PreTranslateMessage(MSG* pMsg);
                virtual void PreSubclassWindow();
                //}}AFX_VIRTUAL

                /// Generated message map functions
                //{{AFX_MSG(IFlatToolbar)
                afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
                afx_msg void OnRefreshButton();
                afx_msg void OnAddDistributionAttribButton();
                afx_msg void OnDeleteDistributionAttribButton();
                afx_msg void OnModifyDistributionAttribButton();
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

            private:
                CCJFlatButton m_RefreshButton;
                CCJFlatButton m_AddDistributionAttribButton;
                CCJFlatButton m_DeleteDistributionAttribButton;
                CCJFlatButton m_ModifyDistributionAttribButton;
                CToolTipCtrl  m_Tooltip;
                CImageList    m_ImageList;
        };

        PSS_DistributionAttributesView();
        virtual ~PSS_DistributionAttributesView();

        /**
        * Initializes the view
        *@param pDistributionManager - the distribution manager
        *@param pPropManager - the properties manager
        *@param pMainUserGroup - the main user group
        *@param pDistributionAttribute - the distribution attribute
        *@param showAll - if true, all the items will be shown
        *@param symbolRef - the symbol reference
        */
        virtual inline void Initialize(PSS_DistributionAttributeManager* pDistributionManager,
                                       ZBDynamicPropertiesManager*       pPropManager,
                                       PSS_UserGroupEntity*              pMainUserGroup,
                                       PSS_DistributionAttribute*        pDistributionAttribute =  NULL,
                                       bool                              showAll                =  false,
                                       int                               symbolRef              = -1);

        /**
        * Sets the symbol reference
        *@param value - the symbol reference
        *@param refresh - if true, the window will be refreshed immediately
        */
        virtual inline void SetSymbolRef(int value, bool refresh = true);

        /**
        * Gets the selected distribution attribute
        *@return the selected distribution attribute, NULL if no selection or on error
        */
        virtual inline PSS_DistributionAttribute* GetSelectedDistributionAttribute();

        /**
        * Gets the selected distribution rule for role
        *@return the selected distribution rule for role, NULL if no selection or on error
        */
        virtual inline PSS_DistributionRulesForRole* GetSelectedDistributionRuleForRole();

        /**
        * Gets the selected distribution rule
        *@return the selected distribution rule, NULL if no selection or on error
        */
        virtual inline PSS_DistributionRule* GetSelectedDistributionRule();

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
        /// Generated message map functions
        //{{AFX_MSG(PSS_DistributionAttributesView)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Gets and checks the unit GUID
        *@return the unit GUID
        */
        virtual CString GetAndCheckUnitGUID() const;

        /**
        * Called when a distribution attribute is added
        */
        virtual void OnAddDistributionAttrib();

        /**
        * Called when a distribution attribute is deleted
        */
        virtual void OnDeleteDistributionAttrib();

        /**
        * Called when a distribution attribute is modified
        */
        virtual void OnModifyDistributionAttrib();

        /**
        * Called when the view is refreshed
        */
        virtual void OnRefresh();

    private:
        IFlatToolbar                   m_FlatToolbar;
        PSS_DistributionAttributesList m_ListCtrl;
        PSS_ProcessGraphModelDoc*      m_pCurrentDoc;
        CODComponent*                  m_pSymbol;
};

//---------------------------------------------------------------------------
// PSS_DistributionAttributesView
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::Initialize(PSS_DistributionAttributeManager* pDistributionManager,
                                                ZBDynamicPropertiesManager*       pPropManager,
                                                PSS_UserGroupEntity*              pMainUserGroup,
                                                PSS_DistributionAttribute*        pDistributionAttribute,
                                                bool                              showAll,
                                                int                               symbolRef)
{
    m_ListCtrl.Initialize(pDistributionManager,
                          pPropManager,
                          pMainUserGroup,
                          pDistributionAttribute,
                          showAll,
                          symbolRef);
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::SetSymbolRef(int value, bool refresh)
{
    m_ListCtrl.SetSymbolRef(value, refresh);
}
//---------------------------------------------------------------------------
PSS_DistributionAttribute* PSS_DistributionAttributesView::GetSelectedDistributionAttribute()
{
    return m_ListCtrl.GetSelectedDistributionAttribute();
}
//---------------------------------------------------------------------------
PSS_DistributionRulesForRole* PSS_DistributionAttributesView::GetSelectedDistributionRuleForRole()
{
    return m_ListCtrl.GetSelectedDistributionRuleForRole();
}
//---------------------------------------------------------------------------
PSS_DistributionRule* PSS_DistributionAttributesView::GetSelectedDistributionRule()
{
    return m_ListCtrl.GetSelectedDistributionRule();
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::ShowAll(bool value, bool refresh)
{
    m_ListCtrl.ShowAll(value, refresh);
}
//---------------------------------------------------------------------------

#endif
