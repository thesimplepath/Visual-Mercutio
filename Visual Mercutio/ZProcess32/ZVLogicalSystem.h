/////////////////////////////////////////////////////////////////////////////
//@doc ZVLogicalSystem
//@module ZVLogicalSystem.h | Interface of the <c ZVLogicalSystem> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         05/2001
// <nl>Description:  ZVLogicalSystem user and group window support
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVLogicalSystem_H__B9410245_8299_4908_8E68_3CF603C57BE0__INCLUDED_)
#define AFX_ZVLogicalSystem_H__B9410245_8299_4908_8E68_3CF603C57BE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"

#include "zModel\ZCLogicalSystemTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// _ZILogicalSystemFlatToolBar window

class _ZILogicalSystemFlatToolBar : public CStatic,
    public PSS_Subject
{
    // Construction / Destruction
public:

    _ZILogicalSystemFlatToolBar();
    virtual ~_ZILogicalSystemFlatToolBar();

    // Attributes
private:

    CCJFlatButton    m_RefreshButton;
    CCJFlatButton    m_AddSystemButton;
    CCJFlatButton    m_RenameSystemButton;
    CCJFlatButton    m_DeleteSystemButton;
    // JMR-MODIF - Le 27 février 2006 - Ajout du bouton Move dans la barre.
    CCJFlatButton    m_MoveSystemButton;
    CCJFlatButton    m_PropertiesButton;

    CImageList        m_ImageList;
    CToolTipCtrl    m_tooltip;

    // Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZILogicalSystemFlatToolBar)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Generated message map functions
protected:

    //{{AFX_MSG(_ZILogicalSystemFlatToolBar)
    afx_msg void OnAddSystemButton();
    afx_msg void OnRenameSystemButton();
    afx_msg void OnDeleteSystemButton();
    afx_msg void OnMoveSystemButton();
    afx_msg void OnPropertiesButton();
    afx_msg void OnRefreshButton();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// ZVLogicalSystem view

class ZVLogicalSystem : public CWnd,
    public PSS_Subject,
    public PSS_Observer
{
public:

    DECLARE_DYNCREATE(ZVLogicalSystem)

    // Protected constructor used by dynamic creation
    ZVLogicalSystem();
    virtual ~ZVLogicalSystem();

    // JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release.
    void Release();

    // Observer call back
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    ////////////////////////////////////////////////////////////////////
    // Context menu function
    int HasContextMenu(CWnd* pWnd, CPoint point);
    void DisplayContextMenu(CWnd* pWnd, CPoint point);

    ////////////////////////////////////////////////////////////////////
    // Group functions
    void OnRefresh();
    void OnAddSystem();
    void OnRenameSystem();
    void OnDeleteSystem();
    // JMR-MODIF - Le 27 février 2006 - Ajout de la fonction OnMoveSystem.
    void OnMoveSystem();
    void OnProperties();

    bool CanAddSystem();
    bool CanRenameSystem();
    bool CanDeleteSystem();
    bool CanProperties();

    // Generated message map functions
protected:

    //{{AFX_MSG(ZVLogicalSystem)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    _ZILogicalSystemFlatToolBar        m_FlatToolBar;
    ZCLogicalSystemTreeCtrl            m_Ctrl;
    COLORREF                        m_clrBtnFace;
};

#endif
