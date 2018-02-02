// ZITreeCtl.h : header file

#ifndef INC_ZITREECTL_H
#define INC_ZITREECTL_H

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

/////////////////////////////////////////////////////////////////////////////
// ZITreeCtrl window

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 31 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Encapsulate information for the modeltree
class _ZTreeData : public CObject
{
public:

	_ZTreeData();
	_ZTreeData( CString Str );
	~_ZTreeData();

	// Collapsed method. Used to keep the current state of an item
	bool IsCollapsed() const
	{
		return m_Collapsed;
	};

	void SetCollapsed( bool value = true )
	{
		m_Collapsed = value;
	};

	// Data member
	CString	m_Str;
	bool	m_Collapsed;
};

class AFX_EXT_CLASS ZITreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC( ZITreeCtrl )

// Construction
public:

	ZITreeCtrl();

	virtual		~ZITreeCtrl();

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
	void		ExpandRoot( BOOL Deep = FALSE );
	void		ExpandBranch( HTREEITEM hTreeItem, BOOL Deep = FALSE );
	void		CollapseRoot( BOOL Deep = FALSE );
	void		CollapseBranch( HTREEITEM hTreeItem, BOOL Deep = FALSE );

	void		LoadImageListMasked( UINT		nIDStart,
									 UINT		nIDEnd	= 0,
									 int		cx		= 16,
									 int		cy		= 16,
									 COLORREF	crMask	= RGB( 255, 255, 255 ) );

	BOOL		SelectItemName ( const CString Name );
	BOOL		IsLastItemName ( const CString Name );
	BOOL		IsRootItemName ( const CString Name );
	BOOL		IsSelectedItemRootItem();
	BOOL		ItemNameExist ( const CString Name );
	int			GetSelectItemPosition( HTREEITEM hParentItem = NULL );
	CString		GetNameSelectedItem();
	void		DeleteAllItems( BOOL DeleteImageList = FALSE );

	void		SaveCollapsedState();
	void		RestoreCollapsedStateToTreeCtrl();

	void		SetNewStyle( long lStyleMask, BOOL bSetBits );
	BOOL		TransferItem( HTREEITEM hitem, HTREEITEM hNewParent );
	void		OnButtonUp();
	BOOL		IsChildNodeOf( HTREEITEM hitemChild, HTREEITEM hitemSuspectedParent );

	HTREEITEM	GetLastItem( HTREEITEM hItem );
	HTREEITEM	GetNextItem( HTREEITEM hItem );
	HTREEITEM	GetPrevItem( HTREEITEM hItem );

	HTREEITEM	FindItem( CString sSearch, 
						  BOOL bCaseSensitive	= FALSE, 
						  BOOL bDownDir			= TRUE, 
						  BOOL bWholeWord		= FALSE, 
						  HTREEITEM hItem		= NULL);

	HTREEITEM	FindItem( CString Label, HTREEITEM hStartItem = NULL );
	HTREEITEM	FindItemData( void* pData, HTREEITEM hStartItem = NULL );

// Generated message map functions
public:

	DECLARE_MESSAGE_MAP()

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZITreeCtrl)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(ZITreeCtrl)
	afx_msg void OnEndLabelEdit(LPNMHDR pnmhdr, LRESULT *pLResult);
	afx_msg void OnBeginDrag(LPNMHDR pnmhdr, LRESULT *pLResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	void OnButtonUp( CPoint point );

protected:

	virtual BOOL IsFindValid( HTREEITEM );
	virtual int GetIndexOfNoDropImage() const;
	virtual CObject* GetDragObject( HTREEITEM DragItem );

private:

	void		_SaveCollapsedState( HTREEITEM hTreeItem );
	void		_RestoreCollapsedStateToTreeCtrl( HTREEITEM hTreeItem );
	void		_EmptySaveStateDataSet();

	_ZTreeData* _FindElementFromSaveStateDataSet( CString Str );
	_ZTreeData* _AddSaveStateDataToSet( CString Str );

	bool		_DeleteElementFromSaveStateDataSet( CString Str );

// Attributes
protected:

	HTREEITEM		m_hItemDrag;
	HTREEITEM		m_hItemDrop;
	CImageList*		m_pImageList;

	CImageList*		m_pDragImage;
	CWnd*			m_pDropWnd;
	HTREEITEM		m_hDragItem;
	int				m_DragImageIndex;

	CObject*		m_pDragObj;

private:

	//@type _ZTreeDataSet | An array of _ZTreeData pointers.
	//@iex typedef CCArray_T<_ZTreeData*,_ZTreeData*> _ZTreeDataSet;
	typedef sfl::CCArray_T<_ZTreeData*,_ZTreeData*> _ZTreeDataSet;

	//@type _ZTreeDataIterator | An iterator for _ZTreeDataSet collections.
	//@iex typedef Iterator_T<_ZTreeData*> _ZTreeDataIterator;
	typedef sfl::Iterator_T<_ZTreeData*> _ZTreeDataIterator;

	_ZTreeDataSet	m_TreeDataSet;

	BOOL			m_bDragging;
};

/////////////////////////////////////////////////////////////////////////////

inline	void ZITreeCtrl::DisableDragDrop( bool value )
{
	SetNewStyle( TVS_DISABLEDRAGDROP, value );
}

inline	void ZITreeCtrl::EditLabels( bool value )
{
	SetNewStyle( TVS_EDITLABELS, value );
}

inline	void ZITreeCtrl::HasButtons( bool value )
{
	SetNewStyle( TVS_HASBUTTONS, value );
}

inline	void ZITreeCtrl::HasLines( bool value )
{
	SetNewStyle( TVS_HASLINES, value );
}

inline	void ZITreeCtrl::LinesAtRoot( bool value )
{
	SetNewStyle( TVS_LINESATROOT, value );
}

inline void	ZITreeCtrl::ShowSelectionAlways( bool value )
{
	SetNewStyle( TVS_SHOWSELALWAYS, value );
}

inline void	ZITreeCtrl::ShowCheckBoxes( bool value )
{
	SetNewStyle( TVS_CHECKBOXES, value );
}

inline void	ZITreeCtrl::TrackSelect( bool value )
{
	SetNewStyle( TVS_TRACKSELECT, value );
}

inline void	ZITreeCtrl::SingleExpand( bool value )
{
	SetNewStyle( TVS_SINGLEEXPAND, value );
}

inline void	ZITreeCtrl::FullRowSelect( bool value )
{
	SetNewStyle( TVS_FULLROWSELECT, value );
}

inline int ZITreeCtrl::GetIndexOfNoDropImage() const
{
	return -1;
}

inline CObject* ZITreeCtrl::GetDragObject( HTREEITEM DragItem )
{
	return (CObject*)GetItemData( DragItem );
}

#endif