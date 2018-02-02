// **************************************************************************************************************
// *									   Classe ZVRiskCalculateParametersDlg									*
// **************************************************************************************************************
// * JMR-MODIF - Le 21 juillet 2007 - Ajout de la classe ZVRiskCalculateParametersDlg.							*
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de paramétrer les données pour calculer les risques dans le modèle.	*
// **************************************************************************************************************

#if !defined(AFX_ZVRISKCALCULATEPARAMETERSDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
#define AFX_ZVRISKCALCULATEPARAMETERSDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_

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
#include "afxcmn.h"

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
// ZVRiskCalculateParametersDlg dialog

class AFX_EXT_CLASS ZVRiskCalculateParametersDlg : public CDialog
{
// Construction / Destruction
public:

	ZVRiskCalculateParametersDlg( CString	IniFilename,
								  CString	CurrencySymbol,
								  CWnd*		pParent			= NULL );

public:

	int GetOrangeSeverityLevel();
	int GetRedSeverityLevel();

	float GetOrangeUE();
	float GetRedUE();
	float GetOrangePOA();
	float GetRedPOA();

	BOOL IsOrangeActionEnabled();
	BOOL IsOrangeNoActionEnabled();
	BOOL IsRedActionEnabled();
	BOOL IsRedNoActionEnabled();
	BOOL IsDefaultColorsEnabled();

private:

	void UpdateOrangeLevel();
	void UpdateRedLevel();
	void UpdateOKButton();

	bool LoadStateFromIniFile();
	bool SaveStateToIniFile();

private:

	// Dialog Data
	//{{AFX_DATA(ZVRiskCalculateParametersDlg)
	enum { IDD = IDD_RISK_CALCULATE_PARAMETERS };
	CSliderCtrl m_OrangeSeverityCtrl;
	CSliderCtrl m_RedSeverityCtrl;
	CStatic m_OrangeLevelCtrl;
	CStatic m_RedLevelCtrl;
	CStatic m_OrangeUEFrsLabelCtrl;
	CStatic m_OrangePOAFrsLabelCtrl;
	CStatic m_RedUEFrsLabelCtrl;
	CStatic m_RedPOAFrsLabelCtrl;
	CButton m_OrangeActionCtrl;
	CButton m_RedActionCtrl;
	CButton m_OrangeNoActionCtrl;
	CButton m_RedNoActionCtrl;
	CButton m_OKCtrl;
	float m_OrangeUE;
	float m_OrangePOA;
	float m_RedUE;
	float m_RedPOA;
	int m_OrangeSeverity;
	int m_RedSeverity;
	BOOL m_OrangeAction;
	BOOL m_OrangeNoAction;
	BOOL m_RedAction;
	BOOL m_RedNoAction;
	BOOL m_DefaultColors;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVRiskCalculateParametersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVRiskCalculateParametersDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNMReleasedcaptureOrangeSeverity(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureRedSeverity(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOrangeAction();
	afx_msg void OnBnClickedOrangeNoAction();
	afx_msg void OnBnClickedRedAction();
	afx_msg void OnBnClickedRedNoAction();
	afx_msg void OnBnClickedOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	BOOL	m_OrangeActionChecked;
	BOOL	m_OrangeNoActionChecked;

	CString	m_IniFilename;
	CString m_CurrencySymbol;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVRISKCALCULATEPARAMETERSDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
