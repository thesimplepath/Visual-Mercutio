#if !defined(AFX_PrcTkOwner_H__9F9D8456_19E2_11D3_95A7_0000B45D7C6F__INCLUDED_)
#define AFX_PrcTkOwner_H__9F9D8456_19E2_11D3_95A7_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrcTkOwner.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZIDialog.h"
#include "HoverButton.h"

#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif



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
// ZVTakeOwnerShipActions dialog

class AFX_EXT_CLASS ZVTakeOwnerShipActions : public ZIDialog
{
// Construction
public:
	ZVTakeOwnerShipActions(const CString Filename, const CString ActivityName, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ZVTakeOwnerShipActions)
	enum { IDD = IDD_PROCESS_TAKEOWNERSHIP };
	ZUHoverButton	m_ViewCommandBtn;
	ZUHoverButton	m_CancelCommandBtn;
	ZUHoverButton	m_AcceptCommandBtn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVTakeOwnerShipActions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVTakeOwnerShipActions)
	afx_msg void OnViewCommand();
	afx_msg void OnAcceptCommand();
	afx_msg void OnCancelCommand();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString m_Filename;
	CString m_ActivityName;
};

//#undef  AFX_DATA
//#define AFX_DATA

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PrcTkOwner_H__9F9D8456_19E2_11D3_95A7_0000B45D7C6F__INCLUDED_)
