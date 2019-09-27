#if !defined(_ZCPROPERTYLISTVIEW_H__)
#define _ZCPROPERTYLISTVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZCPropertyListView.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Observer.h"
#include "ZCPropertyListCtrl.h"

#ifdef _ZPTYMGREXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// ZCPropertyListView view

class AFX_EXT_CLASS ZCPropertyListView : public CView, public PSS_Observer
{
protected:
    ZCPropertyListView();           // protected constructor used by dynamic creation
    DECLARE_DYNCREATE(ZCPropertyListView)

    // Operations
public:

    // Observer call back
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    // Attributes
    void SetPropertyItemManager(ZBPropertyItemManager* pPropertyItemManager)
    {
        m_listctrl.SetPropertyItemManager(pPropertyItemManager);
    };
    ZBPropertyItem* GetPropertyItem(int nIndex)
    {
        return m_listctrl.GetPropertyItem(nIndex);
    };
    // Operations
    void InsertPropertyItem(ZBPropertyItem* pPropertyItem, int nIndex = 0)
    {
        m_listctrl.InsertPropertyItem(pPropertyItem, nIndex);
    };
    void ResetContent()
    {
        m_listctrl.ResetContent();
    };
    void ShowInPlaceControl(bool bShow = true)
    {
        m_listctrl.ShowInPlaceControl(bShow);
    };
    void Refresh()
    {
        m_listctrl.Refresh();
    };

    // Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ZCPropertyListView)
protected:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    //}}AFX_VIRTUAL

// Implementation
protected:
    virtual ~ZCPropertyListView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCPropertyListView)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
protected:
    ZCPropertyListCtrl m_listctrl;

};

#endif
