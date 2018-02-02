// CJCJSearchEdit.h : header file
// 
/////////////////////////////////////////////////////////////////////////////

#ifndef __ZSEARCHEDIT_H__
#define __ZSEARCHEDIT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\ZBDragEdit.h"

// Forward class declaration
class ZCSearchEdit;

#ifdef _ZWINUTIL32EXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 4 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

typedef enum ZSEARCHEDIT_TYPE
{
	ZSEARCHEDIT_DIRECTORY = 0,
	ZSEARCHEDIT_FILE,
	ZSEARCHEDIT_POPUP,
	ZSEARCHEDIT_EXTENDED,
};

class ZEditButton : public CButton
{
public:

	ZEditButton();

public:

	UINT GetNextID( CWnd* pWnd ) const;

	virtual BOOL Create( ZCSearchEdit*		pWnd,
						 ZSEARCHEDIT_TYPE	eType,
						 UINT				nMenu,
						 CString			Title,
						 CString			InitialDirectory,
						 CString			Filters,
						 size_t				FilterCount,
						 bool				EnableMenuItems,
						 bool				NoNotify,
						 bool				Resize );

	virtual BOOL Create( ZCSearchEdit*		pWnd,
						 ZSEARCHEDIT_TYPE	eType,
						 CMenu*				pMenu,
						 CString			Title,
						 CString			InitialDirectory,
						 CString			Filters,
						 size_t				FilterCount,
						 bool				EnableMenuItems,
						 bool				NoNotify,
						 bool				Resize );

	virtual ~ZEditButton();

protected:

	afx_msg void OnClicked();
	DECLARE_MESSAGE_MAP()

private:

	BOOL CreateButton( CWnd* pWnd, ZSEARCHEDIT_TYPE eType, bool Resize );

protected:

	UINT				m_nID;
	CWnd*				m_pWnd;
	CFont				m_Font;
	ZSEARCHEDIT_TYPE	m_eType;
	UINT				m_nMenu;
	CMenu*				m_pMenu;
	CString				m_Title;
	CString				m_InitialDirectory;
	CString				m_Filters;
	size_t				m_FilterCount;
	ZCSearchEdit*		m_pEdit;
	bool				m_EnableMenuItems;
	bool 				m_NoNotify;

private:

	bool m_IsProcessingMenuItems;
};

/////////////////////////////////////////////////////////////////////////////
// ZCSearchEdit window
/////////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS ZCSearchEdit : public ZBDragEdit
{
// Construction
public:

	ZCSearchEdit();

// Operations
public:

	BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );

	void SetSearchType( ZSEARCHEDIT_TYPE eType );
	void SetSearchType( ZSEARCHEDIT_TYPE eType, UINT nMenu, bool EnableMenuItems = false, bool NoNotify = false );
	void SetSearchType( ZSEARCHEDIT_TYPE eType, CMenu* pMenu, bool EnableMenuItems = false, bool NoNotify = false );
	void SetSearchType( ZSEARCHEDIT_TYPE eType, CString Title, CString InitialDirectory = _T( "" ) );
	void SetSearchType( ZSEARCHEDIT_TYPE eType, UINT nID, CString InitialDirectory );

	void SetSearchType( ZSEARCHEDIT_TYPE	eType,
						CString				Title,
						CString				InitialDirectory,
						CString				Filters,
						size_t				FilterCount );

	void SetSearchType( ZSEARCHEDIT_TYPE	eType,
						UINT				nID,
						CString				InitialDirectory,
						CString				Filters,
						size_t				FilterCount );

	virtual void OnMenuCommand( int MenuCommand )
	{
		// Do nothing in the base class
	};

	virtual void OnExtendedCommand()
	{
		// Do nothing in the base class
	};

	// JMR-MODIF - Le 11 août 2005 - Ajout de la fonction DoCreateButton.
	void ZCSearchEdit::DoCreateButton( BOOL Value )
	{
		m_bDoCreateButton = Value;
	};

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZCSearchEdit)
	public:
	virtual BOOL Create( LPCTSTR			lpszClassName,
						 LPCTSTR			lpszWindowName,
						 DWORD				dwStyle,
						 const RECT&		rect,
						 CWnd*				pParentWnd,
						 UINT				nID,
						 CCreateContext*	pContext			= NULL);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~ZCSearchEdit();

// Generated message map functions
protected:

	//{{AFX_MSG(ZCSearchEdit)
	afx_msg void OnEnable( BOOL bEnable );
	afx_msg void OnShowWindow( BOOL bShow, UINT nStatus );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:

	void CreateButton( bool Resize );

// Attributes
private:

	ZEditButton			m_button;
	ZSEARCHEDIT_TYPE	m_eType;
	UINT				m_nMenu;
	CMenu*				m_pMenu;
	CWnd*				m_pParentWnd;
	CString				m_Title;
	CString				m_InitialDirectory;
	CString				m_Filters;
	size_t				m_FilterCount;
	bool				m_BeingResized;
	bool				m_BeingCreated;
	bool				m_EnableMenuItems;
	bool 				m_NoNotify;

	// JMR-MODIF - Le 11 août 2005 - Ajout de la variable m_bDoCreateButton.
	BOOL				m_bDoCreateButton;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __ZSEARCHEDIT_H__
