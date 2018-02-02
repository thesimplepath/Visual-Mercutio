#if !defined(AFX_ACTATRW_H__DAECC7A3_4817_11D3_95FB_0000B45D7C6F__INCLUDED_)
#define AFX_ACTATRW_H__DAECC7A3_4817_11D3_95FB_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ActAtrW.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\ZWizard.h"
#include "zEvent\Activity.h"

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


class AFX_EXT_CLASS ZIActivityAttributionWelcome : public ZIWizardDialog
{
// Construction
public:
	ZIActivityAttributionWelcome(ZActivity* pActivity, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ZIActivityAttributionWelcome)
	enum { IDD = IDD_WZTIMERESOURCE_ATTRST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIActivityAttributionWelcome)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZIActivityAttributionWelcome)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	ZActivity* 		m_pActivity;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


//#undef  AFX_DATA
//#define AFX_DATA

#endif // !defined(AFX_ACTATRW_H__DAECC7A3_4817_11D3_95FB_0000B45D7C6F__INCLUDED_)
