// **************************************************************************************************************
// *										Classe ZVSelectLogicalSystemDlg										*
// **************************************************************************************************************
// * Cette classe représente l'interface de sélection d'un système logique, ou d'un groupe de systèmes logiques	*
// * dans la liste.																								*
// **************************************************************************************************************

#if !defined(AFX_ZVSelectLogicalSystemDlg_H__16B257AC_C5CD_4411_8750_F4510E61718B__INCLUDED_)
#define AFX_ZVSelectLogicalSystemDlg_H__16B257AC_C5CD_4411_8750_F4510E61718B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ZCLogicalSystemTreeCtrl.h"
#include "zModelRes.h"

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 27 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Forward class declaration
class ZBSystemEntity;
class ZBLogicalSystemEntity;

/////////////////////////////////////////////////////////////////////////////
// ZVSelectLogicalSystemDlg dialog

class AFX_EXT_CLASS ZVSelectLogicalSystemDlg : public CDialog
{
// Construction
public:

	// Standard constructor
	ZVSelectLogicalSystemDlg( const CString				Title					= _T( "" ),
							  ZBLogicalSystemEntity*	pMainLogicalSystemGroup	= NULL,
							  CWnd*						pParent					= NULL );

	// Standard constructor
	ZVSelectLogicalSystemDlg( UINT						nTitle,
							  ZBLogicalSystemEntity*	pMainLogicalSystemGroup,
							  CWnd*						pParent					= NULL );

	// JMR-MODIF - Le 27 février 2006 - Nettoyage des memory leaks, ajout du destructeur de l'objet.
	~ZVSelectLogicalSystemDlg();

	// JMR-MODIF - Le 27 février 2006 - Nettoyage des memory leaks, ajout de la fonction Release.
	void Release();

	ZBSystemEntity* GetSelectedSystemEntity() const
	{
		return m_pSystemEntity;
	};

private:

	// Dialog Data
	//{{AFX_DATA(ZVSelectLogicalSystemDlg)
	enum { IDD = IDD_LOGICALSYSTEM_SELECTION };
	ZCLogicalSystemTreeCtrl	m_Ctrl;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVSelectLogicalSystemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVSelectLogicalSystemDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedLogicalSystemTree(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	CString					m_Title;
	ZBSystemEntity*			m_pSystemEntity;
	ZBLogicalSystemEntity*	m_pMainLogicalSystemGroup;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVSelectLogicalSystemDlg_H__16B257AC_C5CD_4411_8750_F4510E61718B__INCLUDED_)