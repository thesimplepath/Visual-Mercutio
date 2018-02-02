#if !defined(AFX_ZVCHOOSEPROPERTYDLG_H__D54FCF65_CB5E_4A17_AFE2_651929FCCF12__INCLUDED_)
#define AFX_ZVCHOOSEPROPERTYDLG_H__D54FCF65_CB5E_4A17_AFE2_651929FCCF12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVChoosePropertyDlg.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZCPropertyListCtrl.h"
#include "zPtyMgr\zPtyMgrRes.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBDynamicPropertiesManager;
class ZDProcessGraphModelMdl;



#ifdef _ZPTYMGREXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


/////////////////////////////////////////////////////////////////////////////
// ZVChoosePropertyDlg dialog

class AFX_EXT_CLASS ZVChoosePropertyDlg : public CDialog
{
// Construction
public:
	ZVChoosePropertyDlg(ZIProperties* pProperties, int ShowType = 0, bool Selection = true, 
					    bool AllowItemSelection = true, bool AllowCategorySelection = false, 
						ZBDynamicPropertiesManager* pPropManager = NULL, 
						ZDProcessGraphModelMdl* pModel = NULL, 
						CWnd* pParent = NULL);   // standard constructor

	ZVChoosePropertyDlg(ZBPropertySet* pPropSet, int ShowType = 0, bool Selection = true,  
					    bool AllowItemSelection = true, bool AllowCategorySelection = false, 
						ZBDynamicPropertiesManager* pPropManager = NULL, 
						ZDProcessGraphModelMdl* pModel = NULL, 
						CWnd* pParent = NULL);   // standard constructor
	

	ZBProperty*	GetSelectedProperty()
	{
		if (m_pSelectedProperty)
			return m_PropertyList.GetCorrespondingProperty( m_pSelectedProperty );
		return NULL;
	};

	ZBPropertyItem* GetSelectedPropertyItem() const
	{
		return m_pSelectedProperty;
	};

private:
// Dialog Data
	//{{AFX_DATA(ZVChoosePropertyDlg)
	enum { IDD = IDD_ALL_PROPERTIES };
	ZCPropertyListCtrl	m_PropertyList;
	int		m_PropType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVChoosePropertyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVChoosePropertyDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnProptype();
	afx_msg void OnDeleteAttribute();
	afx_msg void OnRenameAttribute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void CheckControlStates();

private:
	ZIProperties* m_pProperties;
	ZBPropertySet* m_pPropSet;
	ZBPropertyItem* m_pSelectedProperty;
	bool m_AllowItemSelection;
	bool m_AllowCategorySelection;
	bool m_Selection;
	ZBDynamicPropertiesManager* m_pPropManager;
	ZDProcessGraphModelMdl* m_pModel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVCHOOSEPROPERTYDLG_H__D54FCF65_CB5E_4A17_AFE2_651929FCCF12__INCLUDED_)
