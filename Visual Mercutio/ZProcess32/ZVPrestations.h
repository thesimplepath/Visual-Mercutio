// ******************************************************************************************************************
// *							  Classes _ZIPrestationsFlatToolBar et ZVPrestations								*
// ******************************************************************************************************************
// * JMR-MODIF - Le 11 octobre 2005 - Ajout des classes _ZIPrestationsFlatToolBar et ZVPrestations.					*
// ******************************************************************************************************************
// * Ces classes représentent la vue et les boutons utilisés pour représenter l'affichage des prestations.			*
// ******************************************************************************************************************

#if !defined(AFX_ZVPrestations_H__B9410245_8299_4908_8E68_3CF603C57BE0__INCLUDED_)
#define AFX_ZVPrestations_H__B9410245_8299_4908_8E68_3CF603C57BE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"

#include "zModel\ZCPrestationsTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// _ZIPrestationsFlatToolBar window

class _ZIPrestationsFlatToolBar : public CStatic,
								  public ZISubject
{
// Construction / Destruction
public:

	_ZIPrestationsFlatToolBar();
	virtual ~_ZIPrestationsFlatToolBar();

// Attributes
private:

	CCJFlatButton	m_RefreshButton;
	CCJFlatButton	m_AddPrestationButton;
	CCJFlatButton	m_RenamePrestationButton;
	CCJFlatButton	m_DeletePrestationButton;
	CCJFlatButton	m_MovePrestationButton;
	CCJFlatButton	m_PropertiesButton;

	CImageList		m_ImageList;
	CToolTipCtrl	m_tooltip;

// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(_ZIPrestationsFlatToolBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Generated message map functions
protected:

	//{{AFX_MSG(_ZIPrestationsFlatToolBar)
	afx_msg void OnAddPrestationButton();
	afx_msg void OnRenamePrestationButton();
	afx_msg void OnDeletePrestationButton();
	afx_msg void OnMovePrestationButton();
	afx_msg void OnPropertiesButton();
	afx_msg void OnRefreshButton();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// ZVPrestations view

class ZVPrestations : public CWnd,
					  public ZISubject,
					  public ZIObserver
{
public:

	DECLARE_DYNCREATE( ZVPrestations )

	ZVPrestations();
	virtual ~ZVPrestations();

	// JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release.
	void Release();

	// Observer call back
	virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

	////////////////////////////////////////////////////////////////////
	// Context menu function
	int HasContextMenu( CWnd* pWnd, CPoint point );
	void DisplayContextMenu( CWnd* pWnd, CPoint point );

	////////////////////////////////////////////////////////////////////
	// Group functions
	void OnRefresh();
	void OnAddPrestation();
	void OnRenamePrestation();
	void OnDeletePrestation();
	void OnMovePrestation();
	void OnProperties();

	bool CanAddPrestation();
	bool CanRenamePrestation();
	bool CanDeletePrestation();
	bool CanProperties();

// Generated message map functions
protected:

	//{{AFX_MSG(ZVPrestations)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	_ZIPrestationsFlatToolBar		m_FlatToolBar;
	ZCPrestationsTreeCtrl			m_Ctrl;
	COLORREF						m_clrBtnFace;
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVPrestations_H__B9410245_8299_4908_8E68_3CF603C57BE0__INCLUDED_)