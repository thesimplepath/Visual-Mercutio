#if !defined(AFX_SPLASHDIALOG_H__B84608BF_E2E9_43C6_B4C7_69D87153CAAF__INCLUDED_)
#define AFX_SPLASHDIALOG_H__B84608BF_E2E9_43C6_B4C7_69D87153CAAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplashDialog.h : header file
//

#include "zBaseLib\ZBitmap.h"
#include "ZSplashRes.h"


/////////////////////////////////////////////////////////////////////////////
// ZSplashDialog dialog

class ZSplashDialog : public CDialog
{
// Construction
public:
	ZSplashDialog(UINT nResID = 0, const CString Info = "", CWnd* pParent = NULL);   // standard constructor
	ZSplashDialog(LPCTSTR szFilename, const CString Info = "", CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(ZSplashDialog)
	enum { IDD = IDD_SPLASH_IMAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZSplashDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZSplashDialog)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString			m_BitmapFilename;
	UINT			m_BitmapResID;
	ZBitmap			m_Bitmap;
	CString			m_Info;
	CFont			m_Font;
	CRect			m_InfoRect;
	COLORREF		m_clrFont;
	COLORREF		m_clrBackground;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASHDIALOG_H__B84608BF_E2E9_43C6_B4C7_69D87153CAAF__INCLUDED_)
