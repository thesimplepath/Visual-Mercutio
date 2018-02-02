#if !defined(AFX_ZVLogicalSystemInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_)
#define AFX_ZVLogicalSystemInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelRes.h"

// JMR-MODIF - Le 11 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// forward class declaration
class ZBLogicalSystemEntity;

/////////////////////////////////////////////////////////////////////////////
// ZVLogicalSystemInfoDlg dialog

class ZVLogicalSystemInfoDlg : public CDialog
{
// Construction
public:

	// Standard constructor
	ZVLogicalSystemInfoDlg( UINT					nTitleID		= -1,
							ZBLogicalSystemEntity*	pLogicalSystem	= NULL,
							const CString			Name			= _T( "" ),
							const CString			Description		= _T( "" ),
							bool					ModifyMode		= false,
							CWnd*					pParent			= NULL );

	CString GetDescription() const
	{
		return m_Description;
	};

	CString GetName() const
	{
		return m_Name;
	};

// Dialog Data
private:

	//{{AFX_DATA(ZVLogicalSystemInfoDlg)
	enum { IDD = IDD_LOGICALSYSTEM_INFO };
	CString m_Description;
	CString m_Name;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVLogicalSystemInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVLogicalSystemInfoDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	ZBLogicalSystemEntity*	m_pLogicalSystem;
	CString					m_Title;
	bool					m_ModifyMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVLogicalSystemInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_)