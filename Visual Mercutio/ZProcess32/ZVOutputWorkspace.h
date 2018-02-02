// ZVOutputWorkspace.h: interface for the ZVOutputWorkspace class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVOutputWorkspace_H__8CD08B10_53ED_438C_82AD_1E04FE3C6282__INCLUDED_)
#define AFX_ZVOutputWorkspace_H__8CD08B10_53ED_438C_82AD_1E04FE3C6282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"
#include "zModel\ZVOutputSymbolLogView.h"
#include "zModel\ZVOutputSearchView.h"
#include "zModel\ZVOutputAnalyzerLogView.h"
#include "zModel\ZVOutputWorkflowLogView.h"

// JMR-MODIF - Le 13 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

////////////////////////////////////////////////////////////////
// Tab Index constant definition
const int def_SymbolLogTabIndex		= 0;
const int def_SearchLogTabIndex		= 1;
const int def_AnalyzerLogTabIndex	= 2;
const int def_WkfLogTabIndex		= 3;

class ZVOutputWorkspace : public SECControlBar,
						  public ZISubject,
						  public ZIObserver
{
	DECLARE_DYNAMIC( ZVOutputWorkspace )

public:

	ZVOutputWorkspace();
	virtual ~ZVOutputWorkspace();

	void Initialize();

	// JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release.
	void Release();

	void LogClearOutput();
	void LogAddLine( const CString Line );

	///////////////////////////////////////////////////////////
	// Output Symbol log
	ZVOutputSymbolLogView* GetLogView()
	{
		return &m_OutputView;
	}

	void ActivateSymbolLogTab()
	{
		m_wndTab.ActivateTab( def_SymbolLogTabIndex );
	}

	void ShowSymbolLogTab()
	{
	}

	void HideSymbolLogTab()
	{
	}

	///////////////////////////////////////////////////////////
	// Output Search log

	ZVOutputSearchView* GetLogSearchView()
	{
		return &m_OutputSearchView;
	}

	void ActivateSearchLogTab()
	{
		m_wndTab.ActivateTab( def_SearchLogTabIndex );
	}

	void ShowSearchLogTab()
	{
	}

	void HideSearchLogTab()
	{
	}

	///////////////////////////////////////////////////////////
	// Output Analyzer log

	ZVOutputAnalyzerLogView* GetLogAnalyzerView()
	{
		return &m_OutputAnalyzerView;
	}

	void ActivateAnalyzerLogTab()
	{
		m_wndTab.ActivateTab( def_AnalyzerLogTabIndex );
	}

	void ShowAnalyzerLogTab()
	{
	}

	void HideAnalyzerLogTab()
	{
	}

	///////////////////////////////////////////////////////////
	// Output Workflow log

	ZVOutputWorkflowLogView* GetLogWorkflowView()
	{
		return &m_OutputWkfView;
	}

	void ActivateWorkflowLogTab()
	{
		m_wndTab.ActivateTab( def_WkfLogTabIndex );
	}

	void ShowWorkflowLogTab()
	{
	}

	void HideWorkflowLogTab()
	{
	}

	// Observer call back
	virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

public:

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVOutputWorkspace)
	public:
	//}}AFX_VIRTUAL

	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );
	virtual void OnExtendContextMenu( CMenu* pMenu );

// Generated message map functions
protected:

	//{{AFX_MSG(ZVOutputWorkspace)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnListGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClearWindow();
	afx_msg void OnSetDebugMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	ZVOutputSymbolLogView		m_OutputView;
	ZVOutputSearchView			m_OutputSearchView;
	ZVOutputAnalyzerLogView		m_OutputAnalyzerView;
	ZVOutputWorkflowLogView		m_OutputWkfView;
	// RS-MODIF 21.12.04
	SEC3DTabWnd					m_wndTab;
	//SECTabWnd					m_wndTab;
};

#endif // !defined(AFX_ZVOutputWorkspace_H__8CD08B10_53ED_438C_82AD_1E04FE3C6282__INCLUDED_)