// ZITreeView.cpp : implementation file
//

#include "stdafx.h"
#include "ZITreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "ZIDropView.h"
#include "ZIDropScrollView.h"

/////////////////////////////////////////////////////////////////////////////
// ZITreeView

IMPLEMENT_DYNCREATE(ZITreeView, CTreeView)

BEGIN_MESSAGE_MAP(ZITreeView, CTreeView)
    //{{AFX_MSG_MAP(ZITreeView)
    ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBeginDrag)
    ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndLabelEdit)
    ON_WM_RBUTTONUP()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
    ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBeginDrag)
END_MESSAGE_MAP()
//    ON_NOTIFY_REFLECT(TVN_BEGINRDRAG, OnBeginDrag)



ZITreeView::ZITreeView()
: m_bDragging(FALSE), m_pImageList(NULL), m_pDragImage(NULL), m_pDragObj(NULL)
{
}

ZITreeView::~ZITreeView()
{
}


void        ZITreeView::ExpandRoot( BOOL Deep )
{
    ExpandBranch( GetTreeCtrl().GetRootItem(), Deep );
}

void        ZITreeView::ExpandBranch( HTREEITEM hTreeItem, BOOL Deep )
{
    if (hTreeItem && GetTreeCtrl().ItemHasChildren( hTreeItem ))
    {
        GetTreeCtrl().Expand( hTreeItem, TVE_EXPAND );
        if (Deep)
        {
            hTreeItem = GetTreeCtrl().GetChildItem( hTreeItem );
            do
            {
                ExpandBranch( hTreeItem, Deep );
            }
            while( (hTreeItem = GetTreeCtrl().GetNextSiblingItem( hTreeItem )) != NULL );
        }
    }
    GetTreeCtrl().EnsureVisible( GetTreeCtrl().GetSelectedItem() );
}

void        ZITreeView::CollapseRoot( BOOL Deep )
{
    CollapseBranch( GetTreeCtrl().GetRootItem(), Deep );
}

void        ZITreeView::CollapseBranch( HTREEITEM hTreeItem, BOOL Deep )
{
    if (hTreeItem && GetTreeCtrl().ItemHasChildren( hTreeItem ))
    {
        GetTreeCtrl().Expand( hTreeItem, TVE_COLLAPSE );
        if (Deep)
        {
            hTreeItem = GetTreeCtrl().GetChildItem( hTreeItem );
            do
            {
                CollapseBranch( hTreeItem, Deep );
            }
            while( (hTreeItem = GetTreeCtrl().GetNextSiblingItem( hTreeItem )) != NULL );
        }
    }
    GetTreeCtrl().EnsureVisible( GetTreeCtrl().GetSelectedItem() );
}

void ZITreeView::LoadImageList( UINT nID, int cx, int Grow, COLORREF crMask )
{
    m_pImageList = new CImageList();
    m_pImageList->Create( nID, cx, Grow, crMask );

    GetTreeCtrl().SetImageList(m_pImageList, TVSIL_NORMAL);
}

void ZITreeView::LoadImageList( UINT nIDStart, UINT nIDEnd, UINT nFlags, int cx, int cy )
{
    CBitmap             bitmap;

    m_pImageList = new CImageList();
    m_pImageList->Create( cx, cy, nFlags, 2, 2 );

    // If nIDEnd is zero assigns to start
    if (!nIDEnd)
        nIDEnd = nIDStart;
    for (UINT nID = nIDStart; nID <= nIDEnd; ++nID)  // load bitmaps 
    {
        bitmap.LoadBitmap( nID );
        m_pImageList->Add( &bitmap, static_cast<COLORREF>(NULL) );
        bitmap.DeleteObject();
    }
    GetTreeCtrl().SetImageList(m_pImageList, TVSIL_NORMAL);
}

void ZITreeView::LoadImageListMasked( UINT nIDStart, UINT nIDEnd, int cx, int cy )
{
    CBitmap             bitmap;

    m_pImageList = new CImageList();
    m_pImageList->Create( cx, cy, ILC_MASK, 2, 2 );

    // If nIDEnd is zero assigns to start
    if (!nIDEnd)
        nIDEnd = nIDStart;
    for (UINT nID = nIDStart; nID <= nIDEnd; ++nID)  // load bitmaps 
    {
        bitmap.LoadBitmap( nID );
        m_pImageList->Add( &bitmap, static_cast<COLORREF>(0xFFFFFF) );
        bitmap.DeleteObject();
    }
    GetTreeCtrl().SetImageList(m_pImageList, TVSIL_NORMAL);
}

void ZITreeView::DeleteAllItems( BOOL DeleteImageList )
{
    if (DeleteImageList)
    {
        CImageList  *pimagelist;

        pimagelist = GetTreeCtrl().GetImageList(TVSIL_NORMAL);
        if (pimagelist)
        {
            pimagelist->DeleteImageList();
            delete pimagelist;
            pimagelist = NULL;
        }
    }
    // Therefore, call the base class DeleteAllItems function
    GetTreeCtrl().DeleteAllItems();
}

/////////////////////////////////////////////////////////////////////////////
// ZITreeView drawing

void ZITreeView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
}

/////////////////////////////////////////////////////////////////////////////
// ZITreeView diagnostics

#ifdef _DEBUG
void ZITreeView::AssertValid() const
{
    CTreeView::AssertValid();
}

void ZITreeView::Dump(CDumpContext& dc) const
{
    CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZITreeView message handlers


void ZITreeView::OnDestroy()
{
    DeleteAllItems( TRUE );
    CTreeView::OnDestroy();
}

void ZITreeView::SetNewStyle(long lStyleMask, BOOL bSetBits)
{
    long        lStyleOld;

    lStyleOld = GetWindowLong(m_hWnd, GWL_STYLE);
    lStyleOld &= ~lStyleMask;
    if (bSetBits)
        lStyleOld |= lStyleMask;

    SetWindowLong(m_hWnd, GWL_STYLE, lStyleOld);
    SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
}

void ZITreeView::OnEndLabelEdit(LPNMHDR pnmhdr, LRESULT *pLResult)
{
    TV_DISPINFO     *ptvinfo;

//    ((CTreeCtrlPage *)GetParent())->ShowNotification(pnmhdr, pLResult);
    ptvinfo = (TV_DISPINFO *)pnmhdr;
    if (ptvinfo->item.pszText != NULL)
    {
        ptvinfo->item.mask = TVIF_TEXT;
        GetTreeCtrl().SetItem(&ptvinfo->item);
    }
    *pLResult = TRUE;
}


BOOL ZITreeView::IsChildNodeOf(HTREEITEM hitemChild, HTREEITEM hitemSuspectedParent)
{
    do
    {
        if (hitemChild == hitemSuspectedParent)
            break;
    }
    while ((hitemChild = GetTreeCtrl().GetParentItem(hitemChild)) != NULL);

    return (hitemChild != NULL);
}


BOOL ZITreeView::TransferItem(HTREEITEM hitemDrag, HTREEITEM hitemDrop)
{
    TV_INSERTSTRUCT     tvstruct;
    TCHAR               sztBuffer[50];
    HTREEITEM           hNewItem, hFirstChild;

        // avoid an infinite recursion situation
    tvstruct.item.hItem = hitemDrag;
    tvstruct.item.cchTextMax = 49;
    tvstruct.item.pszText = sztBuffer;
    tvstruct.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
    GetTreeCtrl().GetItem(&tvstruct.item);  // get information of the dragged element
    tvstruct.hParent = hitemDrop;
    tvstruct.hInsertAfter = TVI_SORT;
    tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
    hNewItem = GetTreeCtrl().InsertItem(&tvstruct);

    while ((hFirstChild = GetTreeCtrl().GetChildItem(hitemDrag)) != NULL)
    {
        TransferItem(hFirstChild, hNewItem);  // recursively transfer all the items
        GetTreeCtrl().DeleteItem(hFirstChild);        // delete the first child and all its children
    }
    return TRUE;
}


void ZITreeView::OnButtonUp(CPoint point)
{
    if (m_bDragging)
    {
        // end dragging
        VERIFY (m_pDragImage->DragLeave (GetDesktopWindow ()));    
        m_pDragImage->EndDrag ();
        // Show the cursor again
        ShowCursor(TRUE);
        // stop intercepting all mouse messages
        VERIFY (::ReleaseCapture ());
        m_bDragging = FALSE;

        CPoint pt (point);
        ClientToScreen (&pt);
        // get the CWnd pointer of the window that is under the mouse cursor
        CWnd* pDropWnd = WindowFromPoint (pt);
        ASSERT (pDropWnd);
        // if window accepts drop of symbol
        if ((ISA(pDropWnd,ZIDropView) && ((ZIDropView*)pDropWnd)->AcceptDrop()) ||
            (ISA(pDropWnd,ZIDropScrollView) && ((ZIDropScrollView*)pDropWnd)->AcceptDrop()))
        {
            // convert from screen coordinates to drop target client coordinates
            pDropWnd->ScreenToClient (&pt);
            if (m_pDragObj)
            {
                if (ISA(pDropWnd,ZIDropView))
                    ((ZIDropView*)pDropWnd)->DropItem( m_pDragObj, pt );
                else
                    if (ISA(pDropWnd,ZIDropScrollView))
                        ((ZIDropScrollView*)pDropWnd)->DropItem( m_pDragObj, pt );
            }
        }
    }
}

void ZITreeView::OnRButtonUp(UINT nFlags, CPoint point)
{
    OnButtonUp(point);
    CTreeView::OnRButtonUp(nFlags, point);
}

void ZITreeView::OnBeginDrag(LPNMHDR pnmhdr, LRESULT *pLResult)
{
    m_hDragItem = ((NM_TREEVIEW *)pnmhdr)->itemNew.hItem;
    int nSelectedImage;
    GetTreeCtrl().GetItemImage( m_hDragItem, m_DragImageIndex, nSelectedImage );
    // create a drag image

    // Added 7/29/96
//    if(m_pDragImage)
//        delete m_pDragImage;

    m_pDragImage = GetTreeCtrl().GetImageList(LVSIL_NORMAL); //CreateDragImage (m_hDragItem);
    if (!m_pDragImage)
        m_pDragImage = GetTreeCtrl().GetImageList(LVSIL_SMALL); //CreateDragImage (m_hDragItem);
    ASSERT (m_pDragImage);
    // changes the cursor to the drag image (DragMove() is still required in 
    // OnMouseMove())
    VERIFY (m_pDragImage->BeginDrag (m_DragImageIndex, CPoint (0, 0)));
    VERIFY (m_pDragImage->DragEnter (GetDesktopWindow (), ((NM_TREEVIEW *)pnmhdr)->ptDrag));
    // set dragging flag
    m_bDragging = TRUE;
    m_pDropWnd = this;
    // Set the drag object
    m_pDragObj = GetDragObject( m_hDragItem );
    // Hide the cursor
    ShowCursor(FALSE);
    // capture all mouse messages
    SetCapture ();
}



void ZITreeView::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (m_bDragging)
    {
        CPoint pt (point);
        ClientToScreen (&pt);

        // move the drag image
        VERIFY (m_pDragImage->DragMove (pt));

        // unlock window updates
        VERIFY (m_pDragImage->DragShowNolock (FALSE));

        // get the CWnd pointer of the window that is under the mouse cursor
        CWnd* pDropWnd = WindowFromPoint (pt);
        ASSERT (pDropWnd);
        // if we drag outside current window
        if (pDropWnd != m_pDropWnd)
        {
        }

        // save current window pointer
        m_pDropWnd = pDropWnd;

        // convert from screen coordinates to drop target client coordinates
        pDropWnd->ScreenToClient (&pt);

        // if window accepts drop of symbol
        if ((ISA(pDropWnd,ZIDropView) && ((ZIDropView*)pDropWnd)->AcceptDrop()) ||
            (ISA(pDropWnd,ZIDropScrollView) && ((ZIDropScrollView*)pDropWnd)->AcceptDrop()))
        {            
            if (m_pDragObj)
            {
                // If do accept drop
                if ((ISA(pDropWnd,ZIDropView) && ((ZIDropView*)pDropWnd)->AcceptDropItem( m_pDragObj, pt )) ||
                    (ISA(pDropWnd,ZIDropScrollView) && ((ZIDropScrollView*)pDropWnd)->AcceptDropItem( m_pDragObj, pt )))
                {
                    // change the drag image
                    VERIFY (m_pDragImage->SetDragCursorImage (m_DragImageIndex, CPoint(0,0)));

                }
                else
                {
                    // change the drag image to impossible
                    VERIFY (m_pDragImage->SetDragCursorImage (GetIndexOfNoDropImage(), CPoint(0,0)));
                }
            }
//            UINT uFlags;
            // get the item that is below cursor
//            m_hDropItem = ((CTreeCtrl*)pDropWnd)->HitTest (pt, &uFlags);
            // highlight it
//            ((CTreeCtrl*)pDropWnd)->SelectDropTarget (m_hDropItem);
        }
        // lock window updates
        VERIFY (m_pDragImage->DragShowNolock (TRUE));
    }
    CTreeView::OnMouseMove(nFlags, point);
}


void ZITreeView::OnLButtonUp(UINT nFlags, CPoint point)
{
    OnButtonUp( point );
    CTreeView::OnLButtonUp(nFlags, point);
}


HTREEITEM    ZITreeView::FindItem( CString Label, HTREEITEM hStartItem )
{
    // If hItem is NULL, start search from root item.
    if (hStartItem == NULL)
        hStartItem = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_ROOT, 0 );

    while (hStartItem != NULL)
    {
        char szBuffer[_MAX_FNAME+1];
        TV_ITEM item;

        item.hItem = hStartItem;
        item.mask = TVIF_TEXT | TVIF_CHILDREN;
        item.pszText = szBuffer;
        item.cchTextMax = _MAX_FNAME;
        SendMessage( TVM_GETITEM, 0, (LPARAM)&item );

        // Did we find it?
        if (lstrcmp(szBuffer, (const char*)Label) == 0)
            return hStartItem;

        // Check whether we have child items.
        if (item.cChildren)
        {
            // Recursively traverse child items.
            HTREEITEM hItemFound, hItemChild;

            hItemChild = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hStartItem );
            hItemFound = FindItem( Label, hItemChild );

            // Did we find it?
            if (hItemFound != NULL)
                return hItemFound;
        }

        // Go to next sibling item.
        hStartItem = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hStartItem );
    }

    // Not found.
    return NULL;
}

HTREEITEM    ZITreeView::FindItemData(void* pData, HTREEITEM hStartItem)
{
    // If hItem is NULL, start search from root item.
    if (hStartItem == NULL)
        hStartItem = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_ROOT, 0 );

    while (hStartItem != NULL)
    {

        char szBuffer[_MAX_FNAME+1];
        TV_ITEM item;

        item.hItem = hStartItem;
        item.mask = TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN;
        item.pszText = szBuffer;
        item.cchTextMax = _MAX_FNAME;
        GetTreeCtrl().GetItem( &item );

        // Did we find it?
        if ((void*)item.lParam == pData)
            return hStartItem;

        // Check whether we have child items.
        if (item.cChildren)
        {
            // Recursively traverse child items.
            HTREEITEM hItemFound, hItemChild;

            hItemChild = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hStartItem );
            hItemFound = FindItemData( pData, hItemChild );

            // Did we find it?
            if (hItemFound != NULL)
                return hItemFound;
        }

        // Go to next sibling item.
        hStartItem = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hStartItem );
    }

    // Not found.
    return NULL;
}

int    ZITreeView::GetSelectItemPosition(HTREEITEM hParentItem)
{
    HTREEITEM hSelected = GetTreeCtrl().GetSelectedItem();
    if (hParentItem == NULL)
        hParentItem = GetTreeCtrl().GetRootItem();
    if (hSelected)
    {
        HTREEITEM    hPos;
        if (hParentItem)
        {
            hPos = GetTreeCtrl().GetChildItem( hParentItem );
            int            Index = 0;
            while (hPos)
            {
                if (hPos == hSelected)
                    return Index;
                ++Index;
                hPos = GetTreeCtrl().GetNextItem( hPos, TVGN_NEXT );
            }
        }
    }
    return -1;
}

BOOL ZITreeView::IsSelectedItemRootItem()
{
    HTREEITEM hSelected = GetTreeCtrl().GetSelectedItem();
    return hSelected && hSelected == GetTreeCtrl().GetRootItem();
}

BOOL ZITreeView::IsRootItemName (const CString Name)
{
    HTREEITEM    hRoot = GetTreeCtrl().GetRootItem();
    if (hRoot && GetTreeCtrl().GetItemText( hRoot ) == Name)
        return TRUE;
    return FALSE;
}

BOOL ZITreeView::IsLastItemName (const CString Name)
{
    return FALSE;
}

BOOL ZITreeView::ItemNameExist (const CString Name)
{
    return FindItem( Name, NULL ) != NULL;
}


CString ZITreeView::GetNameSelectedItem ()
{
    HTREEITEM hSelected = GetTreeCtrl().GetSelectedItem();
    if (hSelected)
    {
        return GetTreeCtrl().GetItemText( hSelected );
    }
    return "";
}

BOOL ZITreeView::SelectItemName (const CString Name)
{
    HTREEITEM hItemToSelect = FindItem( Name, NULL );
    if (hItemToSelect)
        return GetTreeCtrl().SelectItem( hItemToSelect );
    return FALSE;
}

// GetLastItem  - Gets last item in the branch
// Returns      - Last item
// hItem        - Node identifying the branch. NULL will 
//                return the last item in outine

HTREEITEM ZITreeView::GetLastItem( HTREEITEM hItem )
{
        // Last child of the last child of the last child ...
        HTREEITEM htiNext;

        if (hItem == NULL)
        {
            // Get the last item at the top level
            htiNext = GetTreeCtrl().GetRootItem();
            while (htiNext)
            {
                hItem = htiNext;
                htiNext = GetTreeCtrl().GetNextSiblingItem( htiNext );
            }
        }

        while (GetTreeCtrl().ItemHasChildren( hItem ))
        {
            htiNext = GetTreeCtrl().GetChildItem( hItem );
            while (htiNext)
            {
                hItem = htiNext;
                htiNext = GetTreeCtrl().GetNextSiblingItem( htiNext );
            }
        }

        return hItem;
}

// GetNextItem  - Get next item as if outline was completely expanded
// Returns      - The item immediately below the reference item
// hItem        - The reference item
HTREEITEM ZITreeView::GetNextItem( HTREEITEM hItem )
{
        HTREEITEM       hti;

        if (GetTreeCtrl().ItemHasChildren( hItem ) )
            return GetTreeCtrl().GetChildItem( hItem );           // return first child
        else
        {
            // return next sibling item
            // Go up the tree to find a parent's sibling if needed.
            while ((hti = GetTreeCtrl().GetNextSiblingItem( hItem )) == NULL)
            {
                if ((hItem = GetTreeCtrl().GetParentItem( hItem ) ) == NULL)
                    return NULL;
            }
        }
        return hti;
}

// GetNextItem  - Get previous item as if outline was completely expanded
// Returns              - The item immediately above the reference item
// hItem                - The reference item
HTREEITEM ZITreeView::GetPrevItem( HTREEITEM hItem )
{
        HTREEITEM       hti;

        hti = GetTreeCtrl().GetPrevSiblingItem(hItem);
        if (hti == NULL)
            hti = GetTreeCtrl().GetParentItem(hItem);
        else
            hti = GetLastItem(hti);
        return hti;
}

// FindItem        - Finds an item that contains the search string
// Returns        - Handle to the item or NULL
// str            - String to search for
// bCaseSensitive    - Should the search be case sensitive
// bDownDir        - Search direction - TRUE for down
// bWholeWord        - True if search should match whole words
// hItem        - Item to start searching from. NULL for
//            - currently selected item
HTREEITEM ZITreeView::FindItem(CString str, 
                BOOL bCaseSensitive /*= FALSE*/, 
                BOOL bDownDir /*= TRUE*/, 
                BOOL bWholeWord /*= FALSE*/, 
                HTREEITEM hItem /*= NULL*/)
{
    int lenSearchStr = str.GetLength();
    if (lenSearchStr == 0) 
        return NULL;

    HTREEITEM htiSel = hItem ? hItem : GetTreeCtrl().GetSelectedItem();
    HTREEITEM htiCur = bDownDir ?GetNextItem( htiSel ) : GetPrevItem( htiSel );

    CString sSearch = str;

    if (htiCur == NULL)
    {
        if (bDownDir)  
            htiCur = GetTreeCtrl().GetRootItem();
        else 
            htiCur = GetLastItem( NULL );
    }

    if( !bCaseSensitive )
        sSearch.MakeLower();

    while (htiCur && htiCur != htiSel)
    {
        CString sItemText = GetTreeCtrl().GetItemText( htiCur );
        if (!bCaseSensitive)
            sItemText.MakeLower();

        int n;
        while ((n = sItemText.Find( sSearch )) != -1)
        {
            // Search string found
            if (bWholeWord)
            {
                // Check preceding char
                if (n != 0)
                {
                    if (isalpha(sItemText[n-1]) || 
                        sItemText[n-1] == '_')
                    {
                        // Not whole word
                        sItemText = sItemText.Right( sItemText.GetLength() - n - 
                                                     lenSearchStr );
                        continue;
                    }
                }

                // Check succeeding char
                if (sItemText.GetLength() > n + lenSearchStr
                    && (isalpha(sItemText[n+lenSearchStr]) ||
                    sItemText[n+lenSearchStr] == '_' ))
                {
                    // Not whole word
                    sItemText = sItemText.Right( sItemText.GetLength() - 
                                                 n - sSearch.GetLength() );
                    continue;
                }
            }
            
            if (IsFindValid( htiCur ))
                return htiCur;
            else 
                break;
        }


        htiCur = bDownDir ? GetNextItem( htiCur ) : GetPrevItem( htiCur );
        if (htiCur == NULL)
        {
            if (bDownDir)  
                htiCur = GetTreeCtrl().GetRootItem();
            else 
                htiCur = GetLastItem( NULL );
        }
    }
    return NULL;
}

// IsFindValid    - Virtual function used by FindItem to allow this
//          function to filter the result of FindItem
// Returns    - True if item matches the criteria
// Arg        - Handle of the item
BOOL ZITreeView::IsFindValid( HTREEITEM )
{
    return TRUE;
}


