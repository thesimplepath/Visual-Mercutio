// ZVChooseMasterDeliverable.h : header file

#if !defined(AFX_ZVCHOOSEMASTERDELIVERABLE_H__A8527013_24E9_4873_B7ED_59144B21863A__INCLUDED_)
#define AFX_ZVCHOOSEMASTERDELIVERABLE_H__A8527013_24E9_4873_B7ED_59144B21863A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelBPRes.h"

// JMR-MODIF - Le 14 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVChooseMasterDeliverable dialog

class ZVChooseMasterDeliverable : public CDialog
{
// Construction
public:

	// Standard constructor
	ZVChooseMasterDeliverable( const CString Deliverables, const CString Master = _T( "" ), CWnd* pParent = NULL );

	CString GetMaster() const
	{
		return m_Master;
	};

private:

	// Dialog Data
	//{{AFX_DATA(ZVChooseMasterDeliverable)
	enum { IDD = IDD_CHOOSE_MASTERDELIV };
	CListBox	m_ListOfDeliverables;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVChooseMasterDeliverable)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVChooseMasterDeliverable)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeListOfDeliverable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void StringToListBox( const CString Deliv, CListBox& LB );
	void CheckState();

private:

	CString m_Deliverables;
	CString m_Master;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVCHOOSEMASTERDELIVERABLE_H__A8527013_24E9_4873_B7ED_59144B21863A__INCLUDED_)
