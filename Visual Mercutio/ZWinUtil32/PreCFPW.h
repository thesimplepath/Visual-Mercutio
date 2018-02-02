#if !defined(AFX_PRECFPW_H__DAECC7A5_4817_11D3_95FB_0000B45D7C6F__INCLUDED_)
#define AFX_PRECFPW_H__DAECC7A5_4817_11D3_95FB_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreCFPW.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\ZWizard.h"

#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif



/////////////////////////////////////////////////////////////////////////////
// ZIActivityAttributionWelcome dialog

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
// ZIPreConditionFormProcWelcome dialog

class AFX_EXT_CLASS ZIPreConditionFormProcWelcome : public ZIWizardDialog
{
// Construction
public:
	ZIPreConditionFormProcWelcome(CString ActivityName = "", CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ZIPreConditionFormProcWelcome)
	enum { IDD = IDD_WZPREACTST_FORMPROC };
	CString	m_ActivityName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIPreConditionFormProcWelcome)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZIPreConditionFormProcWelcome)
	afx_msg void OnNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRECFPW_H__DAECC7A5_4817_11D3_95FB_0000B45D7C6F__INCLUDED_)
