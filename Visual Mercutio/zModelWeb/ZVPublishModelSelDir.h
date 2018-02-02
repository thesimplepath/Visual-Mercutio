// ZVPublishModelSelDir.h : header file

#if !defined(AFX_ZVPublishModelSelDir_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
#define AFX_ZVPublishModelSelDir_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\ZWizard.h"
#include "zBaseLib\ZCIntelliEdit.h"
#include "zWinUtil32\DirTreeCtrl.h"

#include "zModelWebRes.h"

// JMR-MODIF - Le 8 août 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelSelectDirectory dialog

class ZVPublishModelSelectDirectory : public ZIWizardDialog
{
// Construction
public:

	// Standard constructor
	ZVPublishModelSelectDirectory( CString			LastPathName	= _T( "" ),
								   CStringArray*	pArrayOfAddress	= NULL,
								   CWnd*			pParent			= NULL);
	
	CString GetDirectory() const
	{
		return m_Directory;
	}

private:

	// Dialog Data
	//{{AFX_DATA(ZVPublishModelSelectDirectory)
	enum { IDD = IDD_WZPUBMODEL_SEL };
	ZIDirTreeCtrl	m_DirTreeCtrl;
	ZCIntelliEdit	m_cbDirectory;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVPublishModelSelectDirectory)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVPublishModelSelectDirectory)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnChangeServerChoosed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void CheckControlStates();
	void ReflectChangedDirectory();

private:

	CString			m_Directory;
	CStringArray*	m_pArrayOfAddress;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVPublishModelSelDir_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
