#if !defined(AFX_ZVMANAGEVALUEINTELLIEDIT_H__C6635087_7F55_439F_8F26_19B0ADA01219__INCLUDED_)
#define AFX_ZVMANAGEVALUEINTELLIEDIT_H__C6635087_7F55_439F_8F26_19B0ADA01219__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVManageValueIntelliEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ZVManageValueIntelliEdit dialog

class ZVManageValueIntelliEdit : public CDialog
{
// Construction
public:
	ZVManageValueIntelliEdit(CStringArray* pArrayOfValues, CWnd* pParent = NULL);   // standard constructor

private:
// Dialog Data
	//{{AFX_DATA(ZVManageValueIntelliEdit)
//	enum { IDD = IDD_MGVALUE_INTELLI };
	CListBox	m_Values;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVManageValueIntelliEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVManageValueIntelliEdit)
	afx_msg void OnAddvalue();
	afx_msg void OnDelvalue();
	afx_msg void OnSelchangeValues();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CStringArray* m_pArrayOfValues;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVMANAGEVALUEINTELLIEDIT_H__C6635087_7F55_439F_8F26_19B0ADA01219__INCLUDED_)
