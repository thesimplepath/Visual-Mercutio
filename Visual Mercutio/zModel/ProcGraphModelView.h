// ProcGraphModelView.h : interface of the ZIProcessGraphModelView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTIVVIEW_H__BA14FA99_F1F8_4526_8B0F_A212865D7399__INCLUDED_)
#define AFX_OBJECTIVVIEW_H__BA14FA99_F1F8_4526_8B0F_A212865D7399__INCLUDED_

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

#include "ProcGraphModelVp.h"
#include "zBaseLib\ZIDropScrollView.h"
#include "ZTMvcScrollView.h"

#include "zBaseLib\ZVDocumentPageSetup.h"

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 29 septembre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZDProcessGraphModelMdl;
class ZDProcessGraphModelController;

class AFX_EXT_CLASS ZIProcessGraphModelView : public ZTMvcScrollView<ZIProcessGraphModelViewport>
{
protected: // create from serialization only

	DECLARE_DYNCREATE( ZIProcessGraphModelView )

	ZIProcessGraphModelView();

// Attributes
public:

	virtual ZDProcessGraphModelController* GetModelController();

	void	SetModel( ZDProcessGraphModelMdl* pModel, bool SizeViewport = true );
	virtual ZDProcessGraphModelMdl* GetModel();

	// Size the viewport to model
	void	SizeVpToModel();

	// Implement the drop of a symbol
	virtual bool AcceptDrop() const { return true; };
	virtual bool DropItem( CObject* pObj, CPoint pt );
	virtual bool AcceptDropItem( CObject* pObj, CPoint pt );

	virtual const CString GetViewName();

	// Image utility methods
	bool ChooseExportModelToImageFile();

	//	The tooltip class member. Used to display tooltip for
	//	fields.
	CToolTipCtrl& GetToolTip();

// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIProcessGraphModelView)
	public:
	virtual void OnDrawPan(CDC* pDC);	// overridden to draw this view in the pan window
	virtual void OnInitialUpdate();		// called first time after construct
	virtual void OnDraw(CDC* pDC);		// overridden to draw this view
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~ZIProcessGraphModelView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

// Generated message map functions
protected:

	//{{AFX_MSG(ZIProcessGraphModelView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnExportModelToImageFile();
	afx_msg LRESULT OnRefreshSymbol( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRefreshSymbolSet( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnBrowseSymbol( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnOpenModelPage( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnEnsureVisibleSymbol( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnModelDocumentHasChanged( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnAdviseStartPropertyEdition( WPARAM wParam, LPARAM lParam );
	afx_msg BOOL OnToolTipNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Pre translates key message.
	virtual BOOL PreTranslateMessage ( MSG* pMsg );

	// ZVSpanView virtual functions
	virtual void UpdateOverviewRect();
	virtual void PreOverview();
	virtual void PostOverview();

	void InitializePanViewport();
	void SetRatio();

// Attributes
protected:

	CString											m_StrToolTip;
	CToolTipCtrl									m_ToolTip;

	// Used in conjonction with the pan window
	CPoint											m_orig_ptVirtualOrigin;
	CSize											m_orig_szVirtualSize;
	CSize											m_orig_szMag;
	double											m_CurrentRatio;

	bool											m_PanInitialized;

	MvcScrollWrapper_T<ZIProcessGraphModelViewport>	m_vpPan;

private:

	ZDProcessGraphModelMdl*							m_pModelOfView;
};

inline CToolTipCtrl& ZIProcessGraphModelView::GetToolTip()
{
	return m_ToolTip;
}

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTIVVIEW_H__BA14FA99_F1F8_4526_8B0F_A212865D7399__INCLUDED_)
