#if !defined(AFX_ZITreeView_H__BF391ECD_8805_4220_A368_C992B623A66E__INCLUDED_)
#define AFX_ZITreeView_H__BF391ECD_8805_4220_A368_C992B623A66E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZITreeView.h : header file
//

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

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


/////////////////////////////////////////////////////////////////////////////
// ZITreeView view

class AFX_EXT_CLASS ZITreeView : public CTreeView
{
protected:
	ZITreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ZITreeView)


// Operations
public:
	void		DisableDragDrop( bool value = true );
	void		EditLabels( bool value = true );
	void		HasButtons( bool value = true );
	void		HasLines( bool value = true );
	void		LinesAtRoot( bool value = true );
	void		ShowSelectionAlways( bool value = true );
	void		ShowCheckBoxes( bool value = true );
	void		TrackSelect( bool value = true );
	void		SingleExpand( bool value = true );
	void		FullRowSelect( bool value = true );

	void		LoadImageList( UINT nID, int cx, int Grow, COLORREF crMask );
	void		LoadImageList( UINT nIDStart, UINT nIDEnd = 0, UINT nFlags = ILC_COLOR, int cx = 16, int cy = 16 );
	void		LoadImageListMasked( UINT nIDStart, UINT nIDEnd = 0, int cx = 16, int cy = 16 );
	void		ExpandRoot( BOOL Deep = FALSE );
	void		ExpandBranch( HTREEITEM hTreeItem, BOOL Deep = FALSE );
	void		CollapseRoot( BOOL Deep = FALSE );
	void		CollapseBranch( HTREEITEM hTreeItem, BOOL Deep = FALSE );
    BOOL		SelectItemName (const CString Name);
    BOOL		IsLastItemName (const CString Name);
    BOOL		IsRootItemName (const CString Name);
	BOOL		IsSelectedItemRootItem();
    BOOL		ItemNameExist (const CString Name);
    int			GetSelectItemPosition(HTREEITEM hParentItem = NULL);
    CString		GetNameSelectedItem();
	void		DeleteAllItems( BOOL DeleteImageList = FALSE );

	void		SetNewStyle(long lStyleMask, BOOL bSetBits);
	BOOL		TransferItem(HTREEITEM hitem, HTREEITEM hNewParent);
	void		OnButtonUp(void);
	BOOL		IsChildNodeOf(HTREEITEM hitemChild, HTREEITEM hitemSuspectedParent);

	HTREEITEM	GetLastItem( HTREEITEM hItem );
	HTREEITEM	GetNextItem( HTREEITEM hItem );
	HTREEITEM	GetPrevItem( HTREEITEM hItem );
	HTREEITEM	FindItem(CString sSearch, 
				BOOL bCaseSensitive = FALSE, 
				BOOL bDownDir = TRUE, 
				BOOL bWholeWord = FALSE, 
				HTREEITEM hItem = NULL);
	HTREEITEM	FindItem(CString Label, HTREEITEM hStartItem = NULL);
	HTREEITEM	FindItemData(void* pData, HTREEITEM hStartItem = NULL);

protected:
	virtual BOOL IsFindValid( HTREEITEM );
	virtual int	 GetIndexOfNoDropImage() const;
	virtual CObject* GetDragObject( HTREEITEM DragItem );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZITreeView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~ZITreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(ZITreeView)
	afx_msg void OnBeginDrag (NMHDR* pnmhdr, LRESULT* pResult);
	afx_msg void OnEndLabelEdit(LPNMHDR pnmhdr, LRESULT *pLResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void OnButtonUp(CPoint point);

protected:
	HTREEITEM   m_hItemDrag;
	HTREEITEM   m_hItemDrop;
	CImageList*	m_pImageList;

	CImageList*	m_pDragImage;
	CWnd*		m_pDropWnd;
	HTREEITEM	m_hDragItem;
	int			m_DragImageIndex;

	CObject*	m_pDragObj;

private:
	BOOL        m_bDragging;



};

inline	void ZITreeView::DisableDragDrop( bool value )
{ 
	SetNewStyle( TVS_DISABLEDRAGDROP, value);
}

inline	void ZITreeView::EditLabels( bool value )
{
	SetNewStyle(TVS_EDITLABELS, value);
}

inline	void ZITreeView::HasButtons( bool value )
{
	SetNewStyle(TVS_HASBUTTONS, value);
}

inline	void ZITreeView::HasLines( bool value )
{
	SetNewStyle(TVS_HASLINES, value);
}

inline	void ZITreeView::LinesAtRoot( bool value )
{
	SetNewStyle(TVS_LINESATROOT, value);
}

inline void	ZITreeView::ShowSelectionAlways( bool value )
{
	SetNewStyle(TVS_SHOWSELALWAYS, value);
}

inline void	ZITreeView::ShowCheckBoxes( bool value )
{
	SetNewStyle(TVS_CHECKBOXES, value);
}

inline void	ZITreeView::TrackSelect( bool value )
{
	SetNewStyle(TVS_TRACKSELECT, value);
}

inline void	ZITreeView::SingleExpand( bool value )
{
	SetNewStyle(TVS_SINGLEEXPAND, value);
}

inline void	ZITreeView::FullRowSelect( bool value )
{
	SetNewStyle(TVS_FULLROWSELECT, value);
}


inline int ZITreeView::GetIndexOfNoDropImage() const
{
	return -1;
}

inline CObject* ZITreeView::GetDragObject( HTREEITEM DragItem )
{
	return (CObject*)GetTreeCtrl().GetItemData( DragItem );
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZITreeView_H__BF391ECD_8805_4220_A368_C992B623A66E__INCLUDED_)
