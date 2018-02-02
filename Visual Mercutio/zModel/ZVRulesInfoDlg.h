// ******************************************************************************************************************
// *										Classe ZVRulesInfoDlg													*
// ******************************************************************************************************************
// * JMR-MODIF - Le 15 novembre 2006 - Ajout de la classe ZVRulesInfoDlg.											*
// ******************************************************************************************************************
// * Cette classe représente une boîte de dialogue personnalisée pour les messages en provenance du gestionnaire de	*
// * données des règles.																							*
// ******************************************************************************************************************

#if !defined(AFX_ZVRulesInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_)
#define AFX_ZVRulesInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelRes.h"

// forward class declaration
class ZBLogicalRulesEntity;

/////////////////////////////////////////////////////////////////////////////
// ZVRulesInfoDlg dialog

class ZVRulesInfoDlg : public CDialog
{
// Construction
public:

	// Standard constructor
	ZVRulesInfoDlg( UINT					nTitleID		= -1,
					ZBLogicalRulesEntity*	pLogicalRule	= NULL,
					const CString			Name			= _T( "" ),
					const CString			Description		= _T( "" ),
					bool					ModifyMode		= false,
					CWnd*					pParent			= NULL );

	~ZVRulesInfoDlg();

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

	//{{AFX_DATA(ZVRulesInfoDlg)
	enum { IDD = IDD_RULES_INFO };
	CString m_Description;
	CString m_Name;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVRulesInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVRulesInfoDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	ZBLogicalRulesEntity*	m_pRule;
	CString					m_Title;
	bool					m_ModifyMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVRulesInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_)