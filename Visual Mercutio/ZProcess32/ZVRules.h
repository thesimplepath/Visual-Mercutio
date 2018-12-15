// ******************************************************************************************************************
// *                                  Classes _ZIRulesFlatToolBar et ZVRules                                        *
// ******************************************************************************************************************
// * JMR-MODIF - Le 14 novembre 2006 - Ajout des classes _ZIRulesFlatToolBar et ZVRules.                            *
// ******************************************************************************************************************
// * Ces classes représentent la vue et les boutons utilisés pour représenter l'affichage des règles.                *
// ******************************************************************************************************************

#if !defined(AFX_ZVRules_H__B9410245_8299_4908_8E68_3CF603C57BE0__INCLUDED_)
#define AFX_ZVRules_H__B9410245_8299_4908_8E68_3CF603C57BE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"

#include "zModel\ZCRulesTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// _ZIRulesFlatToolBar window

class _ZIRulesFlatToolBar : public CStatic,
                            public ZISubject
{
// Construction / Destruction
public:

    _ZIRulesFlatToolBar();
    virtual ~_ZIRulesFlatToolBar();

// Attributes
private:

    CCJFlatButton    m_RefreshButton;
    CCJFlatButton    m_AddRuleButton;
    CCJFlatButton    m_RenameRuleButton;
    CCJFlatButton    m_DeleteRuleButton;
    CCJFlatButton    m_MoveRuleButton;
    CCJFlatButton    m_PropertiesButton;

    CImageList        m_ImageList;
    CToolTipCtrl    m_tooltip;

// Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZIRulesFlatToolBar)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Generated message map functions
protected:

    //{{AFX_MSG(_ZIRulesFlatToolBar)
    afx_msg void OnAddRuleButton();
    afx_msg void OnRenameRuleButton();
    afx_msg void OnDeleteRuleButton();
    afx_msg void OnMoveRuleButton();
    afx_msg void OnPropertiesButton();
    afx_msg void OnRefreshButton();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// ZVRules view

class ZVRules : public CWnd,
                public ZISubject,
                public ZIObserver
{
public:

    DECLARE_DYNCREATE( ZVRules )

    ZVRules();
    virtual ~ZVRules();

    void Release();

    // Observer call back
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

    ////////////////////////////////////////////////////////////////////
    // Context menu function
    int HasContextMenu( CWnd* pWnd, CPoint point );
    void DisplayContextMenu( CWnd* pWnd, CPoint point );

    ////////////////////////////////////////////////////////////////////
    // Group functions
    void OnRefresh();
    void OnAddRule();
    void OnRenameRule();
    void OnDeleteRule();
    void OnMoveRule();
    void OnProperties();

    bool CanAddRule();
    bool CanRenameRule();
    bool CanDeleteRule();
    bool CanProperties();

// Generated message map functions
protected:

    //{{AFX_MSG(ZVRules)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    _ZIRulesFlatToolBar    m_FlatToolBar;
    ZCRulesTreeCtrl        m_Ctrl;
    COLORREF            m_clrBtnFace;
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVRules_H__B9410245_8299_4908_8E68_3CF603C57BE0__INCLUDED_)