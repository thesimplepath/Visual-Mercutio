#if !defined(AFX_CNFDELMSG_H__D94A62A3_2BA3_11D3_95C9_0000B45D7C6F__INCLUDED_)
#define AFX_CNFDELMSG_H__D94A62A3_2BA3_11D3_95C9_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CnfDelMsg.h : header file
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
#include "zEvent\ActEvent.h"
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif
#ifndef _WIN32
	#include "ZWinUtil.h"
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
// ZIConfirmDeleteMessage dialog


class AFX_EXT_CLASS ZIConfirmDeleteMessage : public ZIDialog
{
// Construction
public:
	ZIConfirmDeleteMessage(ZBEventActivity& EventActivity, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ZIConfirmDeleteMessage)
	enum { IDD = IDD_CONFIRM_DELETE_MSGEVT };
	ZUHoverButton	m_Delete;
	ZUHoverButton	m_DoNotDelete;
	CString	m_ActivityName;
	CString	m_Message;
	CString	m_ProcessName;
	CString	m_Status;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIConfirmDeleteMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZIConfirmDeleteMessage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//#undef  AFX_DATA
//#define AFX_DATA


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNFDELMSG_H__D94A62A3_2BA3_11D3_95C9_0000B45D7C6F__INCLUDED_)
