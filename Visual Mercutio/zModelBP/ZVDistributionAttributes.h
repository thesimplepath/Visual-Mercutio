#if !defined(_ZVDistributionAttributes_H__)
#define _ZVDistributionAttributes_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVDistributionAttributes.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "ZCDistributionAttributesList.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_ProcessGraphModelDoc;


#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


/////////////////////////////////////////////////////////////////////////////
// _ZVFlatToolBarDistributionAttribs window

class _ZVFlatToolBarDistributionAttribs : public CStatic, public PSS_Subject
{
    // Construction
public:
    _ZVFlatToolBarDistributionAttribs();

    // Attributes
private:
    CCJFlatButton    m_RefreshButton;
    CCJFlatButton    m_AddDistributionAttribButton;
    CCJFlatButton    m_DeleteDistributionAttribButton;
    CCJFlatButton    m_ModifyDistributionAttribButton;

    CImageList        m_ImageList;
    CToolTipCtrl    m_tooltip;

    // Operations
public:

    // Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(_ZVFlatToolBarDistributionAttribs)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~_ZVFlatToolBarDistributionAttribs();

    // Generated message map functions
protected:
    //{{AFX_MSG(_ZVFlatToolBarDistributionAttribs)
    afx_msg void OnRefreshButton();
    afx_msg void OnAddDistributionAttribButton();
    afx_msg void OnDeleteDistributionAttribButton();
    afx_msg void OnModifyDistributionAttribButton();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// ZVDistributionAttributes view

class AFX_EXT_CLASS ZVDistributionAttributes : public CWnd, public PSS_Subject, public PSS_Observer
{

public:
    DECLARE_DYNCREATE(ZVDistributionAttributes)
    ZVDistributionAttributes();           // protected constructor used by dynamic creation
    virtual ~ZVDistributionAttributes();

    // Observer call back
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    // Operations
    void Initialize(PSS_DistributionAttributeManager* pDistributionManager,
                    ZBDynamicPropertiesManager* pPropManager,
                    PSS_UserGroupEntity* pMainUserGroup,
                    PSS_DistributionAttribute* pDistributionAttribute = NULL,
                    bool ShowAll = false, int SymbolRef = -1)
    {
        m_listctrl.Initialize(pDistributionManager, pPropManager,
                              pMainUserGroup, pDistributionAttribute,
                              ShowAll, SymbolRef);
    };
    void ShowAll(bool value = true, bool bRefresh = true)
    {
        m_listctrl.ShowAll(value, bRefresh);
    };
    void SetSymbolRef(int value, bool bRefresh = true)
    {
        m_listctrl.SetSymbolRef(value, bRefresh);
    };

    void Refresh();
    void Empty();

    PSS_DistributionAttribute* GetSelectedDistributionAttribute()
    {
        return m_listctrl.GetSelectedDistributionAttribute();
    };
    PSS_DistributionRulesForRole* GetSelectedDistributionRuleForRole()
    {
        return m_listctrl.GetSelectedDistributionRuleForRole();
    };
    PSS_DistributionRule* GetSelectedDistributionRule()
    {
        return m_listctrl.GetSelectedDistributionRule();
    };



    // Generated message map functions
protected:
    //{{AFX_MSG(ZVDistributionAttributes)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    void OnAddDistributionAttrib();
    void OnDeleteDistributionAttrib();
    void OnModifyDistributionAttrib();
    void OnRefresh();

    CString GetAndCheckUnitGUID() const;


private:
    _ZVFlatToolBarDistributionAttribs    m_FlatToolBar;
    ZCDistributionAttributesList        m_listctrl;
    PSS_ProcessGraphModelDoc*                m_pCurrentDoc;
    CODComponent*                        m_pSymbol;

};

#endif
