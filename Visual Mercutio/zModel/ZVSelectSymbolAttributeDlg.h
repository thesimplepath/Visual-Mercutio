#if !defined(AFX_ZVSELECTSYMBOLATTRIBUTEDLG_H__B04D936D_A2ED_4D7C_947E_00E0C77D04C9__INCLUDED_)
#define AFX_ZVSELECTSYMBOLATTRIBUTEDLG_H__B04D936D_A2ED_4D7C_947E_00E0C77D04C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVSelectSymbolAttributeDlg.h : header file
//

// ZCSymbolAttributesTreeCtrl
#include "ZCSymbolAttributesTreeCtrl.h"
// ZIProperties
#include "zProperty\ZIProperties.h"

#include "zModelRes.h"

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBPropertyAttributes;

/////////////////////////////////////////////////////////////////////////////
// ZVSelectSymbolAttributeDlg dialog

class ZVSelectSymbolAttributeDlg : public CDialog
{
// Construction
public:
	ZVSelectSymbolAttributeDlg(ZBPropertyAttributes* pPropAttributes = NULL, 
							   ZBPropertySet* pPropSet = NULL,
							   CWnd* pParent = NULL);   // standard constructor

	BOOL MustSetAsDefaultToAll() const
	{
		return m_SetAsDefaultToAll;
	};

private:
// Dialog Data
	//{{AFX_DATA(ZVSelectSymbolAttributeDlg)
	enum { IDD = IDD_SYMBOLATTRIBUTE_SELECTION };
	ZCSymbolAttributesTreeCtrl	m_AttributeTree;
	BOOL	m_SetAsDefaultToAll;
	BOOL	m_ShowLabel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVSelectSymbolAttributeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVSelectSymbolAttributeDlg)
	virtual void OnOK();
	afx_msg void OnApplyToAll();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	ZBPropertyAttributes* m_pPropAttributes;
	ZBPropertySet* m_pPropSet;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVSELECTSYMBOLATTRIBUTEDLG_H__B04D936D_A2ED_4D7C_947E_00E0C77D04C9__INCLUDED_)
