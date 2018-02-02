#if !defined(AFX_ZVINPUTURLDIALOG_H__54224FB6_443D_11D4_9758_0000B45D7C6F__INCLUDED_)
#define AFX_ZVINPUTURLDIALOG_H__54224FB6_443D_11D4_9758_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVInputURLDialog.h : header file
//


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zWinUtil32\ZWinUtil32.h"


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
// ZVInputURLDialog dialog

class AFX_EXT_CLASS ZVInputURLDialog : public CDialog
{
// Construction
public:
	ZVInputURLDialog(const CString URL = "", CWnd* pParent = NULL);   // standard constructor

	CString	GetURL() const { return m_URL; };

private:
// Dialog Data
	//{{AFX_DATA(ZVInputURLDialog)
	enum { IDD = IDD_INPUT_URL };
	CString	m_URL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVInputURLDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVInputURLDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#undef  AFX_DATA
//#define AFX_DATA

#endif // !defined(AFX_ZVINPUTURLDIALOG_H__54224FB6_443D_11D4_9758_0000B45D7C6F__INCLUDED_)
