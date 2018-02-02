#if !defined(AFX_ZVINPUTATTRIBUTESSELECTIONDLG_H__B7A96F15_086F_49FF_B844_8C441C3CB68A__INCLUDED_)
#define AFX_ZVINPUTATTRIBUTESSELECTIONDLG_H__B7A96F15_086F_49FF_B844_8C441C3CB68A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVInputAttributesSelectionDlg.h : header file
//


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZCInputAttributesList.h"
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
// ZVInputAttributesSelectionDlg dialog

class AFX_EXT_CLASS ZVInputAttributesSelectionDlg : public CDialog
{
// Construction
public:
	ZVInputAttributesSelectionDlg(ZBInputAttributeManager* pInputManager, ZBDynamicPropertiesManager* pPropManager, CWnd* pParent = NULL);   // standard constructor

	ZBInputAttribute* GetSelectedInputAttribute()
	{
		return m_List.GetSelectedInputAttribute();
	};

private:
// Dialog Data
	//{{AFX_DATA(ZVInputAttributesSelectionDlg)
	enum { IDD = IDD_INPUTATTRIBUTES };
	ZCInputAttributesList	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVInputAttributesSelectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVInputAttributesSelectionDlg)
	afx_msg void OnClickInputattributeList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkInputattributeList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void CheckControlState();

private:
	ZBInputAttributeManager* m_pInputManager;
	ZBDynamicPropertiesManager* m_pPropManager;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVINPUTATTRIBUTESSELECTIONDLG_H__B7A96F15_086F_49FF_B844_8C441C3CB68A__INCLUDED_)
