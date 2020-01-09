/////////////////////////////////////////////////////////////////////////////
//@doc ZVUserGroup
//@module ZVUserGroup.h | Interface of the <c ZVUserGroup> class.
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
// <nl>Description:  ZVUserGroup user and group window support
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVUserGroup_H__B9410245_8299_4908_8E68_3CF603C57BE0__INCLUDED_)
#define AFX_ZVUserGroup_H__B9410245_8299_4908_8E68_3CF603C57BE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zModel\PSS_UserGroupTreeCtrl.h"

// JMR-MODIF - Le 14 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// _ZIUserGroupFlatToolBar window

class _ZIUserGroupFlatToolBar : public CStatic, public PSS_Subject
{
    // Construction / destruction
public:

    _ZIUserGroupFlatToolBar();
    virtual ~_ZIUserGroupFlatToolBar();

    virtual void RefreshButtonNow();

    // Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZIUserGroupFlatToolBar)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Generated message map functions
protected:

    //{{AFX_MSG(_ZIUserGroupFlatToolBar)
    afx_msg void OnAddGroupButton();
    afx_msg void OnRenameGroupButton();
    afx_msg void OnDeleteGroupButton();
    afx_msg void OnAddRoleButton();
    afx_msg void OnRenameRoleButton();
    afx_msg void OnDeleteRoleButton();
    afx_msg void OnPropertiesButton();
    afx_msg void OnRefreshButton();
    afx_msg void OnMoveButton();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    // Attributes
private:

    CCJFlatButton    m_RefreshButton;
    CCJFlatButton    m_AddGroupButton;
    CCJFlatButton    m_RenameGroupButton;
    CCJFlatButton    m_DeleteGroupButton;
    CCJFlatButton    m_AddRoleButton;
    CCJFlatButton    m_RenameRoleButton;
    CCJFlatButton    m_DeleteRoleButton;
    CCJFlatButton    m_PropertiesButton;
    CCJFlatButton    m_MoveButton;

    CImageList        m_ImageList;
    CToolTipCtrl    m_tooltip;
};

/////////////////////////////////////////////////////////////////////////////
// ZVUserGroup view

class ZVUserGroup : public CWnd, public PSS_Subject, public PSS_Observer
{
public:

    DECLARE_DYNCREATE(ZVUserGroup)

    // Protected constructor used by dynamic creation
    ZVUserGroup();

    virtual ~ZVUserGroup();

    // Observer call back
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    ////////////////////////////////////////////////////////////////////
    // Context menu function
    int HasContextMenu(CWnd* pWnd, CPoint point);
    void DisplayContextMenu(CWnd* pWnd, CPoint point);

    ////////////////////////////////////////////////////////////////////
    // Group functions
    void OnRefresh();
    void OnAddGroup();
    void OnRenameGroup();
    void OnDeleteGroup();
    void OnAddRole();
    void OnRenameRole();
    void OnDeleteRole();
    void OnMove();
    void OnProperties();

    bool CanAddGroup();
    bool CanRenameGroup();
    bool CanDeleteGroup();
    bool CanAddRole();
    bool CanRenameRole();
    bool CanDeleteRole();
    bool CanMove();
    bool CanProperties();


    // Generated message map functions
protected:
    //{{AFX_MSG(ZVUserGroup)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()



private:
    _ZIUserGroupFlatToolBar        m_FlatToolBar;
    PSS_UserGroupTreeCtrl            m_Ctrl;
    COLORREF                    m_clrBtnFace;
};

#endif
