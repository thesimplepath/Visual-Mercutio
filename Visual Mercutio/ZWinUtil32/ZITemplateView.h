#if !defined(AFX_ZITEMPLATEVIEW_H__1D455413_ED45_11D3_96D8_0000B45D7C6F__INCLUDED_)
#define AFX_ZITEMPLATEVIEW_H__1D455413_ED45_11D3_96D8_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZITemplateView.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZITreeView.h"

// ZITmplTr
#include "ZITmplTr.h"


#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif


#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


/////////////////////////////////////////////////////////////////////////////
// ZITemplateView view

class AFX_EXT_CLASS ZITemplateView : public ZITreeView
{
protected:
	ZITemplateView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ZITemplateView)


// Operations
public:
	void				Initialize (ZDTemplateManager* pTemplateManager, BOOL IncludeFiles);
	void				ReInitialize (ZDTemplateManager* pTemplateManager, BOOL IncludeFiles);
	void				Refresh();
	CString				GetNameSelectedItem();
	ZDTemplateDir*		GetSelectedFolderItem();
	ZDTemplateFile*		GetSelectedFileItem();
	BOOL				SelectItemName (const CString Name);

	virtual	void		OnSelChangedEvent() {};
	virtual	void		OnClickEvent() {};
	virtual	void		OnDblClickEvent() {};
	virtual	void		OnRightClickEvent() {};
	virtual	void		OnRightDblClickEvent() {};

protected:
	virtual int			GetIndexOfNoDropImage() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZITemplateView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~ZITemplateView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(ZITemplateView)
	afx_msg LRESULT OnReloadTemplateManager( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnInitializeTemplateManager( WPARAM wParam, LPARAM lParam );
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRightClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRightDblClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
      ZITemplateTree		m_TemplateTree;
      ZDTemplateManager*	m_pTemplateManager;
      BOOL					m_IncludeFiles;
};



inline int ZITemplateView::GetIndexOfNoDropImage() const
{
	return 2;
}


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZITEMPLATEVIEW_H__1D455413_ED45_11D3_96D8_0000B45D7C6F__INCLUDED_)
