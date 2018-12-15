#if !defined(AFX_ZVURLFORMVIEW_H__267E06C6_44DC_11D4_9759_0000B45D7C6F__INCLUDED_)
#define AFX_ZVURLFORMVIEW_H__267E06C6_44DC_11D4_9759_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVURLFormView.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif

#include "zFormsRes\zFormsRes.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "zBaseLib\FlatBtn.h"
#include "zWeb\ZWebBrowser.h"
#include "zBaseLib\ZCIntelliEdit.h"


#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


/////////////////////////////////////////////////////////////////////////////
// _ZCAddressIntelliEdit window

class _ZCAddressIntelliEdit : public ZCIntelliEdit
{
// Construction
public:
    _ZCAddressIntelliEdit( CWnd* pParent = NULL, CStringArray* pArrayOfValues = NULL );

// Operations
public:
    virtual void    OnEnter();
    void    SetParent(CWnd* pParent);

// Implementation
public:
    virtual ~_ZCAddressIntelliEdit();

    // Generated message map functions
protected:
    //{{AFX_MSG(_ZCAddressIntelliEdit)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

private:
    CWnd*            m_pParent;

};


////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// _ZVURLFormViewButtonToolBar window

class _ZVURLFormViewButtonToolBar : public CStatic
{
public:
// Construction
public:
    _ZVURLFormViewButtonToolBar(CWnd* pParent = NULL); // Default constructor
    void    SetParent(CWnd* pParent);
// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZVURLFormViewButtonToolBar)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~_ZVURLFormViewButtonToolBar();

    // Generated message map functions
protected:
    //{{AFX_MSG(_ZVURLFormViewButtonToolBar)
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




/////////////////////////////////////////////////////////////////////////////
// ZVURLFormView form view

class AFX_EXT_CLASS ZVURLFormView : public CFormView
{
public:
    DECLARE_DYNCREATE(ZVURLFormView)
    ZVURLFormView();           
    virtual ~ZVURLFormView();

// Form Data
private:
    //{{AFX_DATA(ZVURLFormView)
    enum { IDD = IDD_URLWINDOW };
    _ZCAddressIntelliEdit    m_URLEdit;
    ZCFlatButton    m_GoButton;
    _ZVURLFormViewButtonToolBar    m_FlatToolBar;
    CString    m_URL;
    //}}AFX_DATA

    ZWebBrowser*    m_pBrowser;
    CStringArray    m_ValueArray;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVURLFormView)
    protected:
    virtual void OnInitialUpdate( );
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
    void SizeControl();


    // Generated message map functions
    //{{AFX_MSG(ZVURLFormView)
    afx_msg LRESULT OnStopWebButton( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnRefreshWebButton( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnPrevWebButton( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnNextWebButton( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnGoMessage( WPARAM wParam, LPARAM lParam );

    afx_msg void OnGo();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVURLFORMVIEW_H__267E06C6_44DC_11D4_9759_0000B45D7C6F__INCLUDED_)
