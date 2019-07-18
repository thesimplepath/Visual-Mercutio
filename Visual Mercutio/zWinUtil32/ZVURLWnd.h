// ZVURLWnd.h : header file

#if !defined(AFX_ZVURLWnd_H__267E06C6_44DC_11D4_9759_0000B45D7C6F__INCLUDED_)
#define AFX_ZVURLWnd_H__267E06C6_44DC_11D4_9759_0000B45D7C6F__INCLUDED_

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

// mfc
#ifndef __AFXEXT_H__
    #include <afxext.h>
#endif

// processsoft
#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"
#include "zBaseLib\FlatBtn.h"
#include "zBaseLib\ZCIntelliEdit.h"
#include "zWeb\PSS_WebBrowser.h"

// resources
#include "zWinUtil32\ZWinUtil32Res.h"
#include "zFormsRes\zFormsRes.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - LE 14 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

/////////////////////////////////////////////////////////////////////////////
// _ZCURLWndAddressIntelliEdit window

class _ZCURLWndAddressIntelliEdit : public ZCIntelliEdit, public ZISubject
{
// Construction / destruction
public:

    _ZCURLWndAddressIntelliEdit( CWnd* pParent = NULL, CStringArray* pArrayOfValues = NULL );
    virtual ~_ZCURLWndAddressIntelliEdit();

// Operations
public:

    virtual void OnEnter();
    void SetParent( CWnd* pParent );

// Generated message map functions
protected:

    //{{AFX_MSG(_ZCURLWndAddressIntelliEdit)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

private:

    CWnd* m_pParent;
};

/////////////////////////////////////////////////////////////////////////////
// _ZVURLWndButtonToolBar window

class _ZVURLWndButtonToolBar : public CStatic, public ZISubject
{
// Construction
public:

    // Default constructor
    _ZVURLWndButtonToolBar( CWnd* pParent = NULL );
    virtual ~_ZVURLWndButtonToolBar();

    void SetParent( CWnd* pParent );

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZVURLWndButtonToolBar)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

// Generated message map functions
protected:

    //{{AFX_MSG(_ZVURLWndButtonToolBar)
    afx_msg void OnStopWebButton();
    afx_msg void OnRefreshWebButton();
    afx_msg void OnPrevWebButton();
    afx_msg void OnNextWebButton();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG

// Attributes
private:

    CWnd*            m_pParent;
    CCJFlatButton    m_PrevWebButton;
    CCJFlatButton    m_NextWebButton;
    CCJFlatButton    m_StopWebButton;
    CCJFlatButton    m_RefreshWebButton;

    CImageList        m_ImageList;
    CToolTipCtrl    m_tooltip;

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// ZVURLWnd form view

class AFX_EXT_CLASS ZVURLWnd : public CWnd, public ZISubject, public ZIObserver
{
public:

    DECLARE_DYNCREATE( ZVURLWnd )

    ZVURLWnd();
    virtual ~ZVURLWnd();

    // Observer call back
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

private:

    void OnStopWebButton();
    void OnRefreshWebButton();
    void OnPrevWebButton();
    void OnNextWebButton();

    // Generated message map functions
    //{{AFX_MSG(ZVURLWnd)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnPaint();
    afx_msg void OnGo();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    _ZCURLWndAddressIntelliEdit m_URLEdit;
    ZCFlatButton                m_GoButton;
    _ZVURLWndButtonToolBar      m_FlatToolBar;
    PSS_WebBrowser*             m_pBrowser;
    COLORREF                    m_clrBtnFace;
    CStringArray                m_ValueArray;
    CString                     m_URL;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVURLWnd_H__267E06C6_44DC_11D4_9759_0000B45D7C6F__INCLUDED_)
