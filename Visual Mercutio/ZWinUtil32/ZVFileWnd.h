// ZVFileWnd.h : header file

#if !defined(AFX_ZVFileWnd_H__267E06C6_44DC_11D4_9759_0000B45D7C6F__INCLUDED_)
#define AFX_ZVFileWnd_H__267E06C6_44DC_11D4_9759_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zWinUtil32\ZWinUtil32.h"

#include "zFormsRes\zFormsRes.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"
#include "zBaseLib\FlatBtn.h"
#include "DirTreeCtrl.h"
#include "ZSearchEdit.h"

#ifdef _ZWINUTIL32EXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 14 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

/////////////////////////////////////////////////////////////////////////////
// _ZVFileWndButtonToolBar window

class _ZVFileWndButtonToolBar : public CStatic, public ZISubject
{
// Construction / destruction
public:

    // Default constructor
    _ZVFileWndButtonToolBar( CWnd* pParent = NULL );
    virtual ~_ZVFileWndButtonToolBar();

    void SetParent( CWnd* pParent );

// Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZVFileWndButtonToolBar)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

// Generated message map functions
protected:

    //{{AFX_MSG(_ZVFileWndButtonToolBar)
    afx_msg void OnStopFileButton();
    afx_msg void OnRefreshFileButton();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG

// Attributes
private:

    CWnd*            m_pParent;
    CCJFlatButton    m_StopWebButton;
    CCJFlatButton    m_RefreshWebButton;

    CImageList        m_ImageList;
    CToolTipCtrl    m_tooltip;

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// ZVFileWnd form view

class AFX_EXT_CLASS ZVFileWnd : public CWnd, public ZISubject, public ZIObserver
{
public:

    DECLARE_DYNCREATE( ZVFileWnd )

    ZVFileWnd();
    virtual ~ZVFileWnd();

    // Observer call back
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

private:

    void ReflectChangedDirectory();

    void OnStopFileButton();
    void OnRefreshButton();

    // Generated message map functions
    //{{AFX_MSG(ZVFileWnd)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    ZCSearchEdit            m_Filename;
    ZIDirTreeCtrl            m_DirTreeCtrl;
    _ZVFileWndButtonToolBar    m_FlatToolBar;

    COLORREF                m_clrBtnFace;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVFileWnd_H__267E06C6_44DC_11D4_9759_0000B45D7C6F__INCLUDED_)
