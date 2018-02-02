// ZIListCtrl.h : header file
// 

#ifndef __CZILISTCTRL_H__
#define __CZILISTCTRL_H__

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


#define MINCOLWIDTH	       70
#define MAXCOLWIDTH	       70

/////////////////////////////////////////////////////////////////////////////
// ZIListCtrl window

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


class AFX_EXT_CLASS ZIListCtrl : public CListCtrl
{
// Construction
public:
	ZIListCtrl();

// Attributes
public:

protected:
	int					m_nSortedCol; 
	BOOL				m_bEnableOver;
	BOOL				m_bFullRowSelect;
	BOOL				m_bSortAscending; 
	BOOL				m_bSaveColumnState;
	BOOL				m_bEnableSort;
	CString				m_strSection;
	CString				m_strControl;
	CCJFlatHeaderCtrl	m_HeaderCtrl;
	CImageList*			m_pImageList;

// Operations
public:
	int InitializeFlatHeader();
	BOOL SortTextItems( int nCol, BOOL bAscending, int low = 0, int high = -1 );
	void SetExtendedStyle(DWORD dwNewStyle);
	BOOL BuildColumns(int nCols, int* nWidth, int* nColString);
	void AutoSizeColumn( int iColumn );
	void EnableSort( BOOL value = TRUE );
	void LoadImageList( UINT nID, int cx, int Grow, COLORREF crMask );
	void LoadImageList( UINT nIDStart, UINT nIDEnd = 0, UINT nFlags = ILC_COLOR, int cx = 16, int cy = 16 );
	void LoadImageListMasked( UINT nIDStart, UINT nIDEnd = 0, int cx = 16, int cy = 16 );
	void SetHeaderBitmap(int nCol, int nBitmap, DWORD dwRemove);
	void SetEnableOver( BOOL value = TRUE);
	void SetEnableEditLabel( BOOL value = TRUE);
	void SetFullRowSelect( BOOL value = TRUE);
	void SetHotCursor( HCURSOR hc );
	BOOL DeleteAllItems( BOOL DeleteImageList = FALSE );
	
	void DeSelectAll();
	BOOL SetCurSel( size_t Index );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIListCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ZIListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(ZIListCtrl)
	afx_msg void OnItemclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


//#undef  AFX_DATA
//#define AFX_DATA



inline	void ZIListCtrl::EnableSort( BOOL value )
{ 
	m_bEnableSort = value; 
}

inline	void ZIListCtrl::SetHotCursor( HCURSOR hc )
{
	CListCtrl::SetHotCursor( hc );
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __ZILISTCTRL_H__
