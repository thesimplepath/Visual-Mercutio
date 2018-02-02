#if !defined(AFX_ZIScanInformation_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
#define AFX_ZIScanInformation_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanInfo.h : header file
//

#include "zBaseLib\ZWizard.h"

#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIScanInformation dialog

class ZIScanInformation : public ZIWizardDialog
{
// Construction
public:
	ZIScanInformation(const CString Name = "", const CString Description = "", CWnd* pParent = NULL);   // standard constructor
	CString	GetDescription() const { return m_Description; };
	CString	GetName() const { return m_Name; };

private:
// Dialog Data
	//{{AFX_DATA(ZIScanInformation)
	enum { IDD = IDD_WZSCANNING_INFODOC };
	CString	m_Description;
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIScanInformation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZIScanInformation)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIScanInformation_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
