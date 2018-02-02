#if !defined(AFX_ZFILEVERSIONDIALOG_H__0B49E123_8FCC_11D3_965F_0000B45D7C6F__INCLUDED_)
#define AFX_ZFILEVERSIONDIALOG_H__0B49E123_8FCC_11D3_965F_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZFileVersionDialog.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZIDialog.h"
#include "zWinUtil32\zwinutil32.h"



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
// ZFileVersionDialog dialog

class AFX_EXT_CLASS ZFileVersionDialog : public ZIDialog
{
// Construction
public:
	ZFileVersionDialog(long FileVersion = 0, CWnd* pParent = NULL);   // standard constructor
	long	GetFileVersion() const { return m_FileVersion; };

// Dialog Data
	//{{AFX_DATA(ZFileVersionDialog)
	enum { IDD = IDD_FILEVERSION };
	CSpinButtonCtrl	m_FileVersionSpin;
	long	m_FileVersion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZFileVersionDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZFileVersionDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposFileversionSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeFileVersion();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZFILEVERSIONDIALOG_H__0B49E123_8FCC_11D3_965F_0000B45D7C6F__INCLUDED_)
