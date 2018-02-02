// **************************************************************************************************************
// *										  Classe ZVSelectUserGroupDlg										*
// **************************************************************************************************************
// * Cette classe repr�sente l'interface de s�lection d'un utilisateur, ou d'un groupe d'utilisateurs, dans la	*
// * liste.																										*
// **************************************************************************************************************

#if !defined(AFX_ZVSELECTUSERGROUPDLG_H__16B257AC_C5CD_4411_8750_F4510E61718B__INCLUDED_)
#define AFX_ZVSELECTUSERGROUPDLG_H__16B257AC_C5CD_4411_8750_F4510E61718B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ZCUserGroupTreeCtrl.h"
#include "zModelRes.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 27 f�vrier 2006 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Forward class declaration
class ZBUserEntity;
class ZBUserGroupEntity;

/////////////////////////////////////////////////////////////////////////////
// ZVSelectUserGroupDlg dialog

class AFX_EXT_CLASS ZVSelectUserGroupDlg : public CDialog
{
// Construction
public:

	// Standard constructor
	ZVSelectUserGroupDlg( const CString			Title				= _T( "" ),
						  ZBUserGroupEntity*	pMainUserGroup		= NULL,
						  bool					AllowGroupSelection	= true,
						  bool					AllowRoleSelection	= true,
						  CWnd*					pParent				= NULL);

	// Standard constructor
	ZVSelectUserGroupDlg( UINT					nTitle,
						  ZBUserGroupEntity*	pMainUserGroup,
						  bool					AllowGroupSelection	= true,
						  bool					AllowRoleSelection	= true,
						  CWnd*					pParent				= NULL);

	// JMR-MODIF - Le 27 f�vrier 2006 - Nettoyage des memory leaks, ajout du destructeur de l'objet.
	~ZVSelectUserGroupDlg();

	// JMR-MODIF - Le 27 f�vrier 2006 - Nettoyage des memory leaks, ajout de la fonction Release.
	void Release();

	ZBUserEntity* GetSelectedUserEntity() const
	{
		return m_pUserEntity;
	};

private:

	// Dialog Data
	//{{AFX_DATA(ZVSelectUserGroupDlg)
	enum { IDD = IDD_USERGROUP_SELECTION };
	ZCUserGroupTreeCtrl	m_Ctrl;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVSelectUserGroupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVSelectUserGroupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedUsergroupTree(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	CString				m_Title;
	ZBUserEntity*		m_pUserEntity;
	ZBUserGroupEntity*	m_pMainUserGroup;
	bool				m_AllowGroupSelection;
	bool				m_AllowRoleSelection;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVSELECTUSERGROUPDLG_H__16B257AC_C5CD_4411_8750_F4510E61718B__INCLUDED_)