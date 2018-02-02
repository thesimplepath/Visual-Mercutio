// **************************************************************************************************************
// *							   Classe ZVAddRemoveCombinationDeliverableDlg									*
// **************************************************************************************************************
// * Cette classe représente la boîte de dialogue permettant de contrôler la gestion des livrables dans les		*
// * combinaisons.																								*
// **************************************************************************************************************

#if !defined(AFX_ZVADDREMOVECOMBINATIONDELIVERABLEDLG_H__8C46ABB8_8662_492F_B0FB_3D90F851823A__INCLUDED_)
#define AFX_ZVADDREMOVECOMBINATIONDELIVERABLEDLG_H__8C46ABB8_8662_492F_B0FB_3D90F851823A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ZVAddRemoveCombinationDeliverableDlg.h : header file

#include "zModelBPRes.h"

// JMR-MODIF - Le 13 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVAddRemoveCombinationDeliverableDlg dialog

class ZVAddRemoveCombinationDeliverableDlg : public CDialog
{
// Construction
public:

	// Standard constructor
	ZVAddRemoveCombinationDeliverableDlg( const CString	RemainingDeliverables	= _T( "" ),
										  const CString	Deliverables			= _T( "" ),
										  CWnd*			pParent					= NULL);

	CString GetDeliverables() const
	{
		return m_Deliverables;
	};

private:

	// Dialog Data
	//{{AFX_DATA(ZVAddRemoveCombinationDeliverableDlg)
	enum { IDD = IDD_ADD_DELIV_COMBINATION };
	CListBox	m_CombinationDeliverablesLB;
	CListBox	m_RemainingDeliverablesLB;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVAddRemoveCombinationDeliverableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVAddRemoveCombinationDeliverableDlg)
	afx_msg void OnAddDeliv();
	afx_msg void OnDelDeliv();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombDeliv();
	afx_msg void OnSelchangeRemainDeliv();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void StringToListBox( const CString Deliv, CListBox& LB );
	void ListBoxToString( CListBox& LB, CString& Deliv );
	void AddStringToListBox( const CString str, CListBox& LB );
	void RemoveStringToListBox( const CString str, CListBox& LB );
	void CheckState();

private:

	CString m_Deliverables;
	CString m_RemainingDeliverables;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVADDREMOVECOMBINATIONDELIVERABLEDLG_H__8C46ABB8_8662_492F_B0FB_3D90F851823A__INCLUDED_)
