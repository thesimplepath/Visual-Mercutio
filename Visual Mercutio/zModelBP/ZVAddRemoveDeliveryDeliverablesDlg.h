// **************************************************************************************************************
// *							   Classe ZVAddRemoveDeliveryDeliverablesDlg									*
// **************************************************************************************************************
// * JMR-MODIF - Le 13 février 2006 - Ajout de la classe ZVAddRemoveDeliveryDeliverablesDlg.					*
// **************************************************************************************************************
// * Cette classe représente la boîte de dialogue permettant de contrôler la gestion des livrables dans les		*
// * livraisons.																								*
// **************************************************************************************************************

#if !defined(AFX_ZVADDREMOVEDELIVERYDELIVERABLESDLG_H__8C46ABB8_8662_492F_B0FB_3D90F851823A__INCLUDED_)
#define AFX_ZVADDREMOVEDELIVERYDELIVERABLESDLG_H__8C46ABB8_8662_492F_B0FB_3D90F851823A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelBPRes.h"

class ZVAddRemoveDeliveryDeliverablesDlg : public CDialog
{
// Construction
public:

	// Standard constructor
	ZVAddRemoveDeliveryDeliverablesDlg( const CString	AvailableDeliverables	= _T( "" ),
										const CString	SelectedDeliverables	= _T( "" ),
										CWnd*			pParent					= NULL);

	~ZVAddRemoveDeliveryDeliverablesDlg();

	CString GetDeliverables() const
	{
		return m_SelectedDeliverables;
	};

private:

	// Dialog Data
	//{{AFX_DATA(ZVAddRemoveDeliveryDeliverablesDlg)
	enum { IDD = IDD_ADD_DELIV_DELIVERY };
	CListBox	m_SelectedDeliverablesLB;
	CListBox	m_AvailableDeliverablesLB;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVAddRemoveDeliveryDeliverablesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVAddRemoveDeliveryDeliverablesDlg)
	afx_msg void OnAddDeliv();
	afx_msg void OnDelDeliv();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSelectedDeliv();
	afx_msg void OnSelchangeAvailableDeliv();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void StringToListBox( const CString Deliv, CListBox& LB );
	void ListBoxToString( CListBox& LB, CString& Deliv );
	void AddStringToListBox( const CString str, CListBox& LB );
	void RemoveStringToListBox( const CString str, CListBox& LB );
	void CheckState();

	BOOL IsEntryAlreadyExist( CString EntryValue );

private:

	CString m_SelectedDeliverables;
	CString m_AvailableDeliverables;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVADDREMOVEDELIVERYDELIVERABLESDLG_H__8C46ABB8_8662_492F_B0FB_3D90F851823A__INCLUDED_)
