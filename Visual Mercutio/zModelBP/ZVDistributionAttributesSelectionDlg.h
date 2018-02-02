#if !defined(AFX_ZVINPUTATTRIBUTESSELECTIONDLG_H__B7A96F15_086F_49FF_B844_8C441C3CB68A__INCLUDED_)
#define AFX_ZVINPUTATTRIBUTESSELECTIONDLG_H__B7A96F15_086F_49FF_B844_8C441C3CB68A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVDistributionAttributesSelectionDlg.h : header file
//


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zModelBP\ZCDistributionAttributesList.h"
#include "zModelBP\zModelBPRes.h"

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
// ZVDistributionAttributesSelectionDlg dialog

class AFX_EXT_CLASS ZVDistributionAttributesSelectionDlg : public CDialog
{
// Construction
public:
	ZVDistributionAttributesSelectionDlg(ZBDistributionAttributeManager* pDistribManager, 
										 ZBDynamicPropertiesManager* pPropManager, 
										 ZBUserGroupEntity* pMainUserGroup,
										 CWnd* pParent = NULL);   // standard constructor

	ZBDistributionAttribute* GetSelectedDistributionAttribute()
	{
		return m_List.GetSelectedDistributionAttribute();
	};
	ZBDistributionRule*	GetSelectedDistributionRule()
	{
		return m_List.GetSelectedDistributionRule();
	};


private:
// Dialog Data
	//{{AFX_DATA(ZVDistributionAttributesSelectionDlg)
	enum { IDD = IDD_DISTRIBUTIONATTRIBUTES };
	ZCDistributionAttributesList	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVDistributionAttributesSelectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVDistributionAttributesSelectionDlg)
	afx_msg void OnClickDistribattributeList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkDistribattributeList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void CheckControlState();

private:
	ZBDistributionAttributeManager* m_pDistribManager;
	ZBDynamicPropertiesManager* m_pPropManager;
	ZBUserGroupEntity* m_pMainUserGroup;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVINPUTATTRIBUTESSELECTIONDLG_H__B7A96F15_086F_49FF_B844_8C441C3CB68A__INCLUDED_)
