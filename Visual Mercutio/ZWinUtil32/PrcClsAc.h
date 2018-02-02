#if !defined(AFX_PRCCLSAC_H__9F9D8456_19E2_11D3_95A7_0000B45D7C6F__INCLUDED_)
#define AFX_PRCCLSAC_H__9F9D8456_19E2_11D3_95A7_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrcClsAc.h : header file
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

const UINT IDACCEPTCOMMAND = 10;
const UINT IDREJECTCOMMAND = 11;
const UINT IDSENDCOMMAND = 12;
const UINT IDSUSPENDCOMMAND = 13;
const UINT IDTRASHCOMMAND = 14;
const UINT IDCANCELCOMMAND = 15;
const UINT IDABORTCOMMAND = 16;


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
// ZIProcessCloseActions dialog

class AFX_EXT_CLASS ZIProcessCloseActions : public ZIDialog
{
// Construction
public:
	ZIProcessCloseActions(BOOL SendCommand = TRUE, BOOL AcceptRejectCommand = TRUE, BOOL SuspendCommand = TRUE, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ZIProcessCloseActions)
	enum { IDD = IDD_PROCESSCLOSE };
	ZUHoverButton	m_AbortCommand;
	ZUHoverButton	m_TrashCommandBtn;
	ZUHoverButton	m_SuspendCommandBtn;
	ZUHoverButton	m_SendCommandBtn;
	ZUHoverButton	m_RejectCommandBtn;
	ZUHoverButton	m_CancelCommandBtn;
	ZUHoverButton	m_AcceptCommandBtn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIProcessCloseActions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZIProcessCloseActions)
	afx_msg void OnAcceptCommand();
	afx_msg void OnRejectCommand();
	afx_msg void OnSendCommand();
	afx_msg void OnSuspendCommand();
	afx_msg void OnTrashCommand();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelCommand();
	afx_msg void OnAbortCommand();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL	m_SendCommand;
	BOOL	m_AcceptRejectCommand;
	BOOL	m_SuspendCommand;

};

//#undef  AFX_DATA
//#define AFX_DATA

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRCCLSAC_H__9F9D8456_19E2_11D3_95A7_0000B45D7C6F__INCLUDED_)
