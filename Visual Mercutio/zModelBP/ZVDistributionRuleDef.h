#if !defined(AFX_ZVDISTRIBUTIONRULEDEF_H__08A33813_7FB6_46AE_9D2D_F03EE457AFFA__INCLUDED_)
#define AFX_ZVDISTRIBUTIONRULEDEF_H__08A33813_7FB6_46AE_9D2D_F03EE457AFFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVDistributionRuleDef.h : header file
//


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zModelBP\zModelBPRes.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBDistributionRule;


#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


/////////////////////////////////////////////////////////////////////////////
// ZVDistributionRuleDef dialog

class AFX_EXT_CLASS ZVDistributionRuleDef : public CDialog
{
// Construction
public:
	ZVDistributionRuleDef(ZBDistributionRule* pRule = NULL, CWnd* pParent = NULL);   // standard constructor

	int		GetOperator() const
	{
		return m_Operator;
	};
	CString	GetValue() const
	{
		return m_Value;
	};
	int		GetLogicalOperator() const
	{
		return m_LogicalOperator;
	};


private:
// Dialog Data
	//{{AFX_DATA(ZVDistributionRuleDef)
	enum { IDD = IDD_DISTRIBUTIONRULE_DEF };
	int		m_Operator;
	CString	m_Value;
	int		m_LogicalOperator;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVDistributionRuleDef)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVDistributionRuleDef)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	ZBDistributionRule* m_pRule;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVDISTRIBUTIONRULEDEF_H__08A33813_7FB6_46AE_9D2D_F03EE457AFFA__INCLUDED_)
