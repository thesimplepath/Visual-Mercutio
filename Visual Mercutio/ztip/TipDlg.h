#if !defined(AFX_TIPOFDAYDLG_H__26894FA8_7408_4D6C_9255_01A8957E4755__INCLUDED_)
#define AFX_TIPOFDAYDLG_H__26894FA8_7408_4D6C_9255_01A8957E4755__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// TipDlg.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zWeb\ZWebBrowser.h"
#include "ZTipRes.h"



#ifdef _ZTIPEXPORT
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
// ZTipOfDayDlg dialog

class AFX_EXT_CLASS ZTipOfDayDlg : public CDialog
{
// Construction
public:
	ZTipOfDayDlg(CWnd* pParent = NULL);   // standard constructor
	ZTipOfDayDlg(UINT nResID, CWnd* pParent = NULL);
	ZTipOfDayDlg(LPCTSTR lpszURL, BOOL bRes, CWnd* pParent = NULL);   
	~ZTipOfDayDlg();

	BOOL	DoNotShowOnStartup() const { return m_DontShowOnStartup; };

// Dialog Data
	//{{AFX_DATA(ZTipOfDayDlg)
	enum { IDD = IDD_TIP };
	BOOL	m_DontShowOnStartup;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZTipOfDayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZTipOfDayDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	ZWebBrowser*	m_pBrowser;
	CString			m_strURL;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPOFDAYDLG_H__26894FA8_7408_4D6C_9255_01A8957E4755__INCLUDED_)
