// ZUFloatingToolbar.h: interface for the ZUFloatingToolbar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUFLOATINGTOOLBAR_H__4BAA50CE_E692_42F1_AEC1_4AA59689C308__INCLUDED_)
#define AFX_ZUFLOATINGTOOLBAR_H__4BAA50CE_E692_42F1_AEC1_4AA59689C308__INCLUDED_

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

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 18 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class _ToolbarData
{
	public:

	_ToolbarData( CString Name, UINT nIDToolBar, CFrameWnd* pFrame, ModelNotation Notation )
	{
		m_Name			= Name;
		m_nIDToolBar	= nIDToolBar;
		m_pBar			= NULL;
		m_pFrame		= pFrame;
		m_Notation		= Notation;
		m_bReloaded		= false;
	};

	_ToolbarData( CString Name, CControlBar* pBar, CFrameWnd* pFrame, ModelNotation Notation )
	{
		m_Name			= Name;
		m_nIDToolBar	= -1;
		m_pBar			= pBar;
		m_pFrame		= pFrame;
		m_Notation		= Notation;
		m_bReloaded		= false;
	};

	virtual ~_ToolbarData()
	{
	};

public:

	CString			m_Name;
	UINT			m_nIDToolBar;
	CControlBar*	m_pBar;
	CFrameWnd*		m_pFrame;
	ModelNotation	m_Notation;
	bool			m_bReloaded;
};

class _MenubarData
{
public:

	_MenubarData( CString Name, UINT nIDRes, CFrameWnd* pFrame, ModelNotation Notation )
	{
		m_Name			= Name;
		m_nIDRes		= nIDRes;
		m_pMenu			= NULL;
		m_pFrame		= pFrame;
		m_Notation		= Notation;
		m_bReloaded		= false;
	};

	_MenubarData( CString Name, CMenu* pMenu, CFrameWnd* pFrame, ModelNotation Notation )
	{
		m_Name			= Name;
		m_nIDRes		= -1;
		m_pMenu			= pMenu;
		m_pFrame		= pFrame;
		m_Notation		= Notation;
		m_bReloaded		= false;
	};

	virtual ~_MenubarData()
	{
	};

public:

	CString			m_Name;
	CMenu*			m_pMenu;
	UINT			m_nIDRes;
	CFrameWnd*		m_pFrame;
	ModelNotation	m_Notation;
	bool			m_bReloaded;
};

// Forward declaration
class ZAWindowConfiguration;

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

//@type ZBToolbarSet | An array of _ToolbarData pointers.
//@iex typedef CCArray_T<_ToolbarData*,_ToolbarData*> ZBToolbarSet;
typedef CCArray_T<_ToolbarData*, _ToolbarData*> ZBToolbarSet;

//@type ZBToolbarIterator | An iterator for ZBToolbarSet collections.
//@iex typedef Iterator_T<_ToolbarData*> ZBToolbarIterator;
typedef Iterator_T<_ToolbarData*> ZBToolbarIterator;


//@type ZBMenubarSet | An array of _ToolbarData pointers.
//@iex typedef CCArray_T<_MenubarData*,_MenubarData*> ZBMenubarSet;
typedef CCArray_T<_MenubarData*, _MenubarData*> ZBMenubarSet;

//@type ZBMenubarIterator | An iterator for ZBMenubarSet collections.
//@iex typedef Iterator_T<_MenubarData*> ZBMenubarIterator;
typedef Iterator_T<_MenubarData*> ZBMenubarIterator;

class AFX_EXT_CLASS ZUFloatingToolbar  
{
public:

	ZUFloatingToolbar();
	virtual ~ZUFloatingToolbar();

	static void Initialize( ZAWindowConfiguration*	pWndConf,
							SECToolBarManager*		pToolBarManager,
							SECMenuBar*				pMenuBarManager );

	// JMR-MODIF - Le 31 août 2005 - Ajout de la fonction Release.
	static void Release();

	static SECToolBarManager* GetToolBarManager()
	{
		return m_pToolBarManager;
	};

	static SECMenuBar* GetMenuBarManager()
	{
		return m_pMenuBarManager;
	};

	static bool RegisterToolbar( CString Name, UINT nIDToolBar, CFrameWnd* pFrame, ModelNotation Notation );
	static bool UnRegisterToolbar( UINT nIDToolBar );

	static bool RegisterToolbar( CString Name, CControlBar* pBar, CFrameWnd* pFrame, ModelNotation Notation );
	static bool UnRegisterToolbar( CControlBar* pBar );

	static bool RegisterMenubar( CString Name, UINT nIDRes, CFrameWnd* pFrame, ModelNotation Notation );
	static bool RegisterAndLoadMenubar( CString Name, UINT nIDRes, CFrameWnd* pFrame, ModelNotation Notation );
	static bool UnRegisterMenubar( UINT nIDRes );
	
	static bool RegisterMenubar( CString Name, CMenu* pMenu, CFrameWnd* pFrame, ModelNotation Notation );
	static bool UnRegisterMenubar( CMenu* pMenu );

	static bool SwitchContext( ModelNotation Notation );

	static void ReloadBarState();
	static void ReloadBarState(const CString Name);
	static void SaveBarState();

private:

	static bool HideToolbars( ModelNotation Notation );
	static bool ShowToolbars( ModelNotation Notation );
	static bool ToolbarExist( CString Name );
	static bool ToolbarExist( UINT nIDToolBar );
	static bool ToolbarExist( CControlBar* pBar );
	static bool MenubarExist( CString Name );
	static bool MenubarExist( UINT nIDRes );
	static bool MenubarExist( CMenu* pMenu );
	static bool HideMenubars( ModelNotation Notation );
	static bool ShowMenubars( ModelNotation Notation );

private:

	static ZBToolbarSet				m_ToolbarSet;
	static ZBMenubarSet				m_MenubarSet;
	static ModelNotation			m_CurrentNotation;
	static ZAWindowConfiguration*	m_pWndConf;
	static SECToolBarManager*		m_pToolBarManager;
	static SECMenuBar*				m_pMenuBarManager;
};

#endif // !defined(AFX_ZUFLOATINGTOOLBAR_H__4BAA50CE_E692_42F1_AEC1_4AA59689C308__INCLUDED_)