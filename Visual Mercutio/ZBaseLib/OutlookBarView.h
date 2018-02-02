#if !defined(AFX_OUTLOOKBARVIEW_H__FC539904_AE66_11D2_AB9F_A08556C10000__INCLUDED_)
#define AFX_OUTLOOKBARVIEW_H__FC539904_AE66_11D2_AB9F_A08556C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutlookBarView.h : header file
//

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

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

/////////////////////////////////////////////////////////////////////////////
// ZIOutlookBarView view

class AFX_EXT_CLASS ZIOutlookBarView : public CView
{
protected:
	ZIOutlookBarView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ZIOutlookBarView)

// Operations
public:
	void			InitializeMenuControl(CContentItems* pContents, size_t ContentSize, CImageList* pImageListSmall=NULL, CImageList* pImageListLarge=NULL);
	virtual BOOL	ChangeContext( size_t Context );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIOutlookBarView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~ZIOutlookBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(ZIOutlookBarView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg BOOL OnOutbarNotify(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()

// Attributes
protected:
	CCJOutlookBar	m_OutBar;
	CCJPagerCtrl	m_Pager;
	CFont			m_Font;
	CRect			m_pRect;
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKBARVIEW_H__FC539904_AE66_11D2_AB9F_A08556C10000__INCLUDED_)
