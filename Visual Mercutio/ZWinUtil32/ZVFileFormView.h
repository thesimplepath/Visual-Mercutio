#if !defined(AFX_ZVFileFormView_H__267E06C6_44DC_11D4_9759_0000B45D7C6F__INCLUDED_)
#define AFX_ZVFileFormView_H__267E06C6_44DC_11D4_9759_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVFileFormView.h : header file
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
#include "DirTreeCtrl.h"
#include "ZSearchEdit.h"


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
// _ZVFileFormViewButtonToolBar window

class _ZVFileFormViewButtonToolBar : public CStatic
{
public:
// Construction
public:
	_ZVFileFormViewButtonToolBar(CWnd* pParent = NULL); // Default constructor
	void	SetParent(CWnd* pParent);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(_ZVFileFormViewButtonToolBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~_ZVFileFormViewButtonToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(_ZVFileFormViewButtonToolBar)
	afx_msg void OnStopFileButton();
	afx_msg void OnRefreshFileButton();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG


// Attributes
private:
	CWnd*			m_pParent;
	CCJFlatButton	m_StopWebButton;
	CCJFlatButton	m_RefreshWebButton;

	CImageList		m_ImageList;
	CToolTipCtrl	m_tooltip;


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////
// ZVFileFormView form view

class AFX_EXT_CLASS ZVFileFormView : public CFormView
{
public:
	DECLARE_DYNCREATE(ZVFileFormView)
	ZVFileFormView();           
	virtual ~ZVFileFormView();

// Form Data
private:
	//{{AFX_DATA(ZVFileFormView)
	enum { IDD = IDD_FILEWINDOW };
	ZCSearchEdit					m_Filename;
	ZIDirTreeCtrl					m_DirTreeCtrl;
	_ZVFileFormViewButtonToolBar	m_FlatToolBar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVFileFormView)
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
	void ReflectChangedDirectory();


	// Generated message map functions
	//{{AFX_MSG(ZVFileFormView)
	afx_msg void OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnStopFileButton( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRefreshWebButton( WPARAM wParam, LPARAM lParam );

	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVFileFormView_H__267E06C6_44DC_11D4_9759_0000B45D7C6F__INCLUDED_)
