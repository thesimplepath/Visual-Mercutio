// **************************************************************************************************************
// *										   Classe ZVRiskOptionsDlg											*
// **************************************************************************************************************
// * JMR-MODIF - Le 25 juin 2007 - Ajout de la classe ZVRiskOptionsDlg.											*
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de paramétrer les différentes données d'un risque.						*
// **************************************************************************************************************

#if !defined(AFX_ZVRISKOPTIONSDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
#define AFX_ZVRISKOPTIONSDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zModelBPRes.h"
#include "afxwin.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVRiskOptionsDlg dialog

class AFX_EXT_CLASS ZVRiskOptionsDlg : public CDialog
{
// Construction / Destruction
public:

	// Standard constructor
	ZVRiskOptionsDlg( CString	RiskName,
					  CString	RiskDesc,
					  CString	RiskType,
					  int		RiskImpact,
					  int		RiskProbability,
					  float		RiskUE,
					  float		RiskPOA,
					  bool		RiskAction,
					  CString	CurrencySymbol,
					  CWnd*		pParent			= NULL );

public:

	CString GetRiskTitle();
	CString GetRiskDescription();
	CString GetRiskType();

	int GetRiskImpact();
	int GetRiskProbability();
	int GetRiskSeverity();

	float GetRiskUE();
	float GetRiskPOA();

	bool GetRiskAction();

private:

	int GetImpactIndex();
	int GetProbabilityIndex();

	void LoadTypeList();
	void LoadImpactList();
	void LoadProbabilityList();
	void UpdateSeverity();
	void SelectFileToOpen( CString Directory, CString Caption, CString Extension, CString& Filename );

	BOOL ReloadTypeFile( CString Filename );
	BOOL ReloadImpactFile( CString Filename );
	BOOL ReloadProbabilityFile( CString Filename );

private:

	// Dialog Data
	//{{AFX_DATA(ZVRiskOptionsDlg)
	enum { IDD = IDD_RISK_OPTIONS };
	CString		m_RiskName;
	CString		m_RiskDesc;
	CString		m_RiskType;
	float		m_RiskUE;
	float		m_RiskPOA;
	BOOL		m_RiskAction;
	CComboBox	m_RiskImpactCtrl;
	CComboBox	m_RiskProbabilityCtrl;
	CComboBox	m_RiskTypeCtrl;
	CStatic		m_RiskSeverityCtrl;
	CStatic		m_UEFrsLabelCtrl;
	CStatic		m_POAFrsLabelCtrl;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVRiskOptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVRiskOptionsDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeRiskImpact();
	afx_msg void OnCbnSelchangeRiskProbability();
	afx_msg void OnBnClickedModifyRiskType();
	afx_msg void OnBnClickedOpenRiskType();
	afx_msg void OnBnClickedModifyRiskImpact();
	afx_msg void OnBnClickedModifyRiskProbability();
	afx_msg void OnBnClickedOpenRiskImpact();
	afx_msg void OnBnClickedOpenRiskProbability();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	int		m_RiskImpact;
	int		m_RiskProbability;

	CString	m_CurrencySymbol;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVRISKOPTIONSDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
