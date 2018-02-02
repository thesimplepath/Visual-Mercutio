// ZVProperties.h : header file

#if !defined(_ZVPROPERTIES_H__)
#define _ZVPROPERTIES_H__

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

#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"
#include "ZCPropertyListCtrl.h"
#include "ZCPropertyDescription.h"

#ifdef _ZPTYMGREXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 23 septembre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// _ZIFlatToolBar window

class _ZIFlatToolBar : public CStatic,
					   public ZISubject
{
// Construction / Destruction
public:

	_ZIFlatToolBar();
	virtual ~_ZIFlatToolBar();

// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(_ZIFlatToolBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Generated message map functions
protected:

	//{{AFX_MSG(_ZIFlatToolBar)
	afx_msg void OnRefreshButton();
	afx_msg void OnShowAllTypesButton();
	afx_msg void OnShowStaticTypeButton();
	afx_msg void OnShowDynamicTypeButton();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes
private:

	CCJFlatButton	m_RefreshButton;
	CCJFlatButton	m_ShowAllTypesButton;
	CCJFlatButton	m_ShowStaticTypeButton;
	CCJFlatButton	m_ShowDynamicTypeButton;

	CImageList		m_ImageList;
	CToolTipCtrl	m_tooltip;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ZVProperties view

class AFX_EXT_CLASS ZVProperties : public CWnd,
								   public ZISubject,
								   public ZIObserver
{
private:

	DECLARE_DYNCREATE( ZVProperties )

private:

	enum ZPropertiesView
	{
		AllTypes	= 0,
		StaticType	= 1,
		DynamicType	= 2,
		None		= 3
	};

public:

	ZVProperties();
	virtual ~ZVProperties();

public:

	// Observer call back
	virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

	// Attributes
	void SetPropertyItemManager( ZBPropertyItemManager* pPropertyItemManager )
	{
		m_listctrl.SetPropertyItemManager( pPropertyItemManager );
	}

	void LoadStateFromIniFile( const CString IniFile )
	{
		m_listctrl.LoadStateFromIniFile( IniFile );
	}

	ZBPropertyItem* GetPropertyItem( int nIndex )
	{
		return m_listctrl.GetPropertyItem( nIndex );
	}

	// Operations
	void InsertPropertyItem( ZBPropertyItem* pPropertyItem, int nIndex = 0 )
	{
		m_listctrl.InsertPropertyItem( pPropertyItem, nIndex );
	}

	void ResetContent()
	{
		m_listctrl.ResetContent();
	}

	void ShowInPlaceControl( bool bShow = true )
	{
		m_listctrl.ShowInPlaceControl( bShow );
	}

	void Refresh()
	{
		m_listctrl.Refresh();
	}

	void EmptyControl()
	{
		OnEmptyControl();
	}

// Generated message map functions
protected:

	//{{AFX_MSG(ZVProperties)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnShowAllTypes();
	void OnShowStaticType();
	void OnShowDynamicType();
	void OnRefresh();
	void OnEmptyControl();

	void SwitchToView( ZVProperties::ZPropertiesView View = AllTypes );
	void RefreshCurrentView();
	void ShowAllTypes();
	void ShowStaticType();
	void ShowDynamicType();

private:

	_ZIFlatToolBar			m_FlatToolBar;
	ZCPropertyListCtrl		m_listctrl;
	ZCPropertyDescription	m_PropDesc;

	ZPropertiesView			m_CurrentView;
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_ZVPROPERTIES_H__)
