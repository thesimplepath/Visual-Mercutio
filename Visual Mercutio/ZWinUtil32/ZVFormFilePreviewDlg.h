#if !defined(AFX_ZVFORMFILEPREVIEWDLG_H__803DD553_2E0D_11D4_9736_0000B45D7C6F__INCLUDED_)
#define AFX_ZVFORMFILEPREVIEWDLG_H__803DD553_2E0D_11D4_9736_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVFormFilePreviewDlg.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zwinutil32.h"

// ViewRead
#include "zBaseLib\ViewRead.h"
// ZDDocument
#include "zBaseLib\ZDDoc.h"
// ZDDocTemplateEx
#include "zBaseLib\DocTmplEx.h"


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
// ZIButtonToolBarFormFilePreview window

class ZIButtonToolBarFormFilePreview : public CStatic
{
public:
// Construction
public:
	ZIButtonToolBarFormFilePreview();
	void SetParent(CWnd* pParent);

// Attributes
private:
	CCJFlatButton	m_NextPageButton;
	CCJFlatButton	m_PreviousPageButton;
	CCJFlatButton	m_RefreshButton;
	CCJFlatButton	m_ZoomOutButton;
	CCJFlatButton	m_ZoomInButton;
	CCJFlatButton	m_NextFileButton;
	CCJFlatButton	m_PreviousFileButton;
	CCJFlatButton	m_CloseFileButton;

	CImageList		m_ImageList;
	CToolTipCtrl	m_tooltip;
	CWnd*			m_pParent;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIButtonToolBarFormFilePreview)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ZIButtonToolBarFormFilePreview();

	// Generated message map functions
protected:
	//{{AFX_MSG(ZIButtonToolBarFormFilePreview)
	afx_msg void OnNextPageButton();
	afx_msg void OnPreviousPageButton();
	afx_msg void OnRefreshButton();
	afx_msg void OnZoomOutButton();
	afx_msg void OnZoomInButton();
	afx_msg void OnNextFileButton();
	afx_msg void OnPrevFileButton();
	afx_msg void OnCloseButton();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// ZVFormFilePreviewDlg dialog

class AFX_EXT_CLASS ZVFormFilePreviewDlg : public CDialog
{
// Construction
public:
	ZVFormFilePreviewDlg(const CString Filename, ZDDocTemplateEx* pDocTemplate, CWnd* pParent = NULL);   // standard constructor
	virtual ~ZVFormFilePreviewDlg();

// Dialog Data
	//{{AFX_DATA(ZVFormFilePreviewDlg)
	enum { IDD = IDD_FORM_FILEPREVIEW };
	ZIButtonToolBarFormFilePreview		m_FlatToolBar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVFormFilePreviewDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVFormFilePreviewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnOK();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	void SizeControl();
	void CloseDocument();

private:
	CCreateContext		m_Context; 
	CString				m_Filename;
	ZIViewRead*			m_pView;
	CFrameWnd*			m_pFrameWindow;
	ZDDocument*			m_pDocument;
	ZDDocTemplateEx*	m_pDocTemplate;

};




/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVFORMFILEPREVIEWDLG_H__803DD553_2E0D_11D4_9736_0000B45D7C6F__INCLUDED_)
