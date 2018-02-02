#if !defined(AFX_SELPROCS_H__B6801F53_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
#define AFX_SELPROCS_H__B6801F53_4E39_11D3_9604_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelProcS.h : header file
//

/*
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
*/
#include "zBaseLib\ZWizard.h"
#include "ZSearchEdit.h"

#include "zWinUtil32\ZWinUtil32.h"

/*
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
*/


/////////////////////////////////////////////////////////////////////////////
// ZISelectProcessWizardStart dialog

class ZISelectProcessWizardStart : public ZIWizardDialog
{
// Construction
public:
	ZISelectProcessWizardStart(CString ProcessName, CWnd* pParent = NULL);   // standard constructor

private:
// Dialog Data
	//{{AFX_DATA(ZISelectProcessWizardStart)
	enum { IDD = IDD_WZCHOOSEPROC_WELCOME };
	CString	m_ProcessName;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZISelectProcessWizardStart)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZISelectProcessWizardStart)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELPROCS_H__B6801F53_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
