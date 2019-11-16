/****************************************************************************
 * ==> PSS_TreeView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic tree view                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_TreeView.h"

// processsoft
#include "PSS_DropView.h"
#include "PSS_DropScrollView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_TreeView, CTreeView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_TreeView, CTreeView)
    //{{AFX_MSG_MAP(PSS_TreeView)
    ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBeginDrag)
    ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndLabelEdit)
    ON_WM_RBUTTONUP()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_DESTROY()
    ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBeginDrag)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_TreeView
//---------------------------------------------------------------------------
PSS_TreeView::PSS_TreeView() :
    m_pDropWnd(NULL),
    m_pDragObj(NULL),
    m_hItemDrag(NULL),
    m_hItemDrop(NULL),
    m_hDragItem(NULL),
    m_pImageList(NULL),
    m_pDragImage(NULL),
    m_DragImageIndex(0),
    m_Dragging(FALSE)
{}
//---------------------------------------------------------------------------
PSS_TreeView::~PSS_TreeView()
{}
//---------------------------------------------------------------------------
void PSS_TreeView::LoadImageList(UINT id, int size, int grow, COLORREF maskColor)
{
    m_pImageList = new CImageList();
    m_pImageList->Create(id, size, grow, maskColor);

    GetTreeCtrl().SetImageList(m_pImageList, TVSIL_NORMAL);
}
//---------------------------------------------------------------------------
void PSS_TreeView::LoadImageList(UINT startID, UINT endID, UINT flags, int cx, int cy)
{
    m_pImageList = new CImageList();
    m_pImageList->Create(cx, cy, flags, 2, 2);

    // if end index is set to zero, assign it to start
    if (!endID)
        endID = startID;

    // load bitmaps
    for (UINT id = startID; id <= endID; ++id)
    {
        CBitmap bitmap;
        bitmap.LoadBitmap(id);
        m_pImageList->Add(&bitmap, static_cast<COLORREF>(NULL));
        bitmap.DeleteObject();
    }

    GetTreeCtrl().SetImageList(m_pImageList, TVSIL_NORMAL);
}
//---------------------------------------------------------------------------
void PSS_TreeView::LoadImageListMasked(UINT startID, UINT endID, int cx, int cy)
{
    m_pImageList = new CImageList();
    m_pImageList->Create(cx, cy, ILC_MASK, 2, 2);

    // if end index is set to zero, assign it to start
    if (!endID)
        endID = startID;

    // load bitmaps
    for (UINT id = startID; id <= endID; ++id)
    {
        CBitmap bitmap;
        bitmap.LoadBitmap(id);
        m_pImageList->Add(&bitmap, static_cast<COLORREF>(0xFFFFFF));
        bitmap.DeleteObject();
    }

    GetTreeCtrl().SetImageList(m_pImageList, TVSIL_NORMAL);
}
//---------------------------------------------------------------------------
void PSS_TreeView::ExpandRoot(BOOL deep)
{
    ExpandBranch(GetTreeCtrl().GetRootItem(), deep);
}
//---------------------------------------------------------------------------
void PSS_TreeView::ExpandBranch(HTREEITEM hTreeItem, BOOL deep)
{
    if (hTreeItem && GetTreeCtrl().ItemHasChildren(hTreeItem))
    {
        GetTreeCtrl().Expand(hTreeItem, TVE_EXPAND);

        if (deep)
        {
            hTreeItem = GetTreeCtrl().GetChildItem(hTreeItem);

            do
            {
                ExpandBranch(hTreeItem, deep);
            }
            while ((hTreeItem = GetTreeCtrl().GetNextSiblingItem(hTreeItem)) != NULL);
        }
    }

    GetTreeCtrl().EnsureVisible(GetTreeCtrl().GetSelectedItem());
}
//---------------------------------------------------------------------------
void PSS_TreeView::CollapseRoot(BOOL deep)
{
    CollapseBranch(GetTreeCtrl().GetRootItem(), deep);
}
//---------------------------------------------------------------------------
void PSS_TreeView::CollapseBranch(HTREEITEM hTreeItem, BOOL deep)
{
    if (hTreeItem && GetTreeCtrl().ItemHasChildren(hTreeItem))
    {
        GetTreeCtrl().Expand(hTreeItem, TVE_COLLAPSE);

        if (deep)
        {
            hTreeItem = GetTreeCtrl().GetChildItem(hTreeItem);

            do
            {
                CollapseBranch(hTreeItem, deep);
            }
            while ((hTreeItem = GetTreeCtrl().GetNextSiblingItem(hTreeItem)) != NULL);
        }
    }

    GetTreeCtrl().EnsureVisible(GetTreeCtrl().GetSelectedItem());
}
//---------------------------------------------------------------------------
BOOL PSS_TreeView::SelectItemName(const CString& name)
{
    HTREEITEM hItemToSelect = FindItem(name, NULL);

    if (hItemToSelect)
        return GetTreeCtrl().SelectItem(hItemToSelect);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_TreeView::IsRootItemName(const CString& name)
{
    HTREEITEM hRoot = GetTreeCtrl().GetRootItem();

    if (hRoot && GetTreeCtrl().GetItemText(hRoot) == name)
        return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_TreeView::IsLastItemName(const CString& name)
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_TreeView::IsSelectedItemRootItem()
{
    HTREEITEM hSelected = GetTreeCtrl().GetSelectedItem();
    return hSelected && hSelected == GetTreeCtrl().GetRootItem();
}
//---------------------------------------------------------------------------
BOOL PSS_TreeView::ItemNameExist(const CString& name)
{
    return (FindItem(name, NULL) != NULL);
}
//---------------------------------------------------------------------------
int PSS_TreeView::GetSelectItemPosition(HTREEITEM hParentItem) const
{
    HTREEITEM hSelected = GetTreeCtrl().GetSelectedItem();

    if (!hParentItem)
        hParentItem = GetTreeCtrl().GetRootItem();

    if (hSelected)
    {
        HTREEITEM hPos;

        if (hParentItem)
        {
            hPos      = GetTreeCtrl().GetChildItem(hParentItem);
            int index = 0;

            while (hPos)
            {
                if (hPos == hSelected)
                    return index;

                ++index;
                hPos = GetTreeCtrl().GetNextItem(hPos, TVGN_NEXT);
            }
        }
    }

    return -1;
}
//---------------------------------------------------------------------------
CString PSS_TreeView::GetNameSelectedItem() const
{
    HTREEITEM hSelected = GetTreeCtrl().GetSelectedItem();

    if (hSelected)
        return GetTreeCtrl().GetItemText(hSelected);

    return "";
}
//---------------------------------------------------------------------------
void PSS_TreeView::DeleteAllItems(BOOL deleteImageList)
{
    if (deleteImageList)
    {
        CImageList* pImagelist = GetTreeCtrl().GetImageList(TVSIL_NORMAL);

        if (pImagelist)
        {
            pImagelist->DeleteImageList();
            delete pImagelist;
        }
    }

    // call the base class function
    GetTreeCtrl().DeleteAllItems();
}
//---------------------------------------------------------------------------
void PSS_TreeView::SetNewStyle(long flags, BOOL setBits)
{
    long styleFlags;

    styleFlags = GetWindowLong(m_hWnd, GWL_STYLE) & ~flags;

    if (setBits)
        styleFlags |= flags;

    ::SetWindowLong(m_hWnd, GWL_STYLE, styleFlags);
    SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
}
//---------------------------------------------------------------------------
BOOL PSS_TreeView::TransferItem(HTREEITEM hItem, HTREEITEM hNewParent)
{
    TV_INSERTSTRUCT     tvstruct;
    TCHAR               sztBuffer[50];
    HTREEITEM           hNewItem, hFirstChild;

    // to avoid an infinite recursion
    tvstruct.item.hItem      = hItem;
    tvstruct.item.cchTextMax = 49;
    tvstruct.item.pszText    = sztBuffer;
    tvstruct.item.mask       = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;

    // get information about the dragged element
    GetTreeCtrl().GetItem(&tvstruct.item);

    tvstruct.hParent      = hNewParent;
    tvstruct.hInsertAfter = TVI_SORT;
    tvstruct.item.mask    = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
    hNewItem              = GetTreeCtrl().InsertItem(&tvstruct);

    while ((hFirstChild = GetTreeCtrl().GetChildItem(hItem)) != NULL)
    {
        // recursively transfer all the items, then delete the first child and all its children
        TransferItem(hFirstChild, hNewItem);
        GetTreeCtrl().DeleteItem(hFirstChild);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TreeView::IsChildNodeOf(HTREEITEM hItemChild, HTREEITEM hItemSuspectedParent)
{
    do
    {
        if (hItemChild == hItemSuspectedParent)
            break;
    }
    while ((hItemChild = GetTreeCtrl().GetParentItem(hItemChild)) != NULL);

    return (hItemChild != NULL);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TreeView::GetPrevItem(HTREEITEM hItem)
{
    HTREEITEM hTreeItem = GetTreeCtrl().GetPrevSiblingItem(hItem);

    if (!hTreeItem)
        hTreeItem = GetTreeCtrl().GetParentItem(hItem);
    else
        hTreeItem = GetLastItem(hTreeItem);

    return hTreeItem;
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TreeView::GetNextItem(HTREEITEM hItem)
{
    HTREEITEM hTreeItem;

    if (GetTreeCtrl().ItemHasChildren(hItem))
        // return first child
        return GetTreeCtrl().GetChildItem(hItem);

    // return next sibling item. Move up in the tree to find a parent's sibling if needed
    while ((hTreeItem = GetTreeCtrl().GetNextSiblingItem(hItem)) == NULL)
        if ((hItem = GetTreeCtrl().GetParentItem(hItem)) == NULL)
            return NULL;

    return hTreeItem;
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TreeView::GetLastItem(HTREEITEM hItem)
{
    // last child of the last child of the last child ...
    HTREEITEM hNext;

    if (hItem == NULL)
    {
        // get the last item at the top level
        hNext = GetTreeCtrl().GetRootItem();

        while (hNext)
        {
            hItem = hNext;
            hNext = GetTreeCtrl().GetNextSiblingItem(hNext);
        }
    }

    while (GetTreeCtrl().ItemHasChildren(hItem))
    {
        hNext = GetTreeCtrl().GetChildItem(hItem);

        while (hNext)
        {
            hItem = hNext;
            hNext = GetTreeCtrl().GetNextSiblingItem(hNext);
        }
    }

    return hItem;
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TreeView::FindItem(const CString& str,
                                 BOOL           caseSensitive,
                                 BOOL           downDir,
                                 BOOL           wholeWord,
                                 HTREEITEM      hItem)
{
    const int lenSearchStr = str.GetLength();

    if (!lenSearchStr)
        return NULL;

    HTREEITEM hSelItem = hItem   ? hItem                 : GetTreeCtrl().GetSelectedItem();
    HTREEITEM hCurItem = downDir ? GetNextItem(hSelItem) : GetPrevItem(hSelItem);

    CString search = str;

    if (!hCurItem)
        if (downDir)
            hCurItem = GetTreeCtrl().GetRootItem();
        else
            hCurItem = GetLastItem(NULL);

    if (!caseSensitive)
        search.MakeLower();

    while (hCurItem && hCurItem != hSelItem)
    {
        CString itemText = GetTreeCtrl().GetItemText(hCurItem);

        if (!caseSensitive)
            itemText.MakeLower();

        int n;

        while ((n = itemText.Find(search)) != -1)
        {
            // search string found
            if (wholeWord)
            {
                // check preceding char
                if (n != 0)
                {
                    if (isalpha(itemText[n - 1]) || itemText[n - 1] == '_')
                    {
                        // not whole word
                        itemText = itemText.Right(itemText.GetLength() - n - lenSearchStr);
                        continue;
                    }
                }

                // check following char
                if (itemText.GetLength() > n + lenSearchStr &&
                   (isalpha(itemText[n + lenSearchStr]) || itemText[n + lenSearchStr] == '_'))
                {
                    // not whole word
                    itemText = itemText.Right(itemText.GetLength() - n - search.GetLength());
                    continue;
                }
            }

            if (IsFindValid(hCurItem))
                return hCurItem;

            break;
        }


        hCurItem = downDir ? GetNextItem(hCurItem) : GetPrevItem(hCurItem);

        if (!hCurItem)
            if (downDir)
                hCurItem = GetTreeCtrl().GetRootItem();
            else
                hCurItem = GetLastItem(NULL);
    }

    return NULL;
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TreeView::FindItem(const CString& label, HTREEITEM hStartItem)
{
    // if start item is NULL, start the search from the root item
    if (!hStartItem)
        hStartItem = HTREEITEM(SendMessage(TVM_GETNEXTITEM, TVGN_ROOT, 0));

    while (hStartItem)
    {
        char buffer[_MAX_FNAME + 1];

        TV_ITEM item;
        item.hItem      = hStartItem;
        item.mask       = TVIF_TEXT | TVIF_CHILDREN;
        item.pszText    = buffer;
        item.cchTextMax = _MAX_FNAME;
        SendMessage(TVM_GETITEM, 0, (LPARAM)&item);

        // found it?
        if (!lstrcmp(buffer, (const char*)label))
            return hStartItem;

        // check if child items exist
        if (item.cChildren)
        {
            // recursively iterate through child items
            HTREEITEM hItemChild = HTREEITEM(SendMessage(TVM_GETNEXTITEM, TVGN_CHILD, LPARAM(hStartItem)));
            HTREEITEM hItemFound = FindItem(label, hItemChild);

            // found it?
            if (hItemFound)
                return hItemFound;
        }

        // go to next sibling item
        hStartItem = HTREEITEM(SendMessage(TVM_GETNEXTITEM, TVGN_NEXT, LPARAM(hStartItem)));
    }

    // not found
    return NULL;
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TreeView::FindItemData(void* pData, HTREEITEM hStartItem)
{
    // if start item is NULL, start the search from the root item
    if (!hStartItem)
        hStartItem = HTREEITEM(SendMessage(TVM_GETNEXTITEM, TVGN_ROOT, 0));

    while (hStartItem)
    {
        char buffer[_MAX_FNAME + 1];

        TV_ITEM item;
        item.hItem      = hStartItem;
        item.mask       = TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN;
        item.pszText    = buffer;
        item.cchTextMax = _MAX_FNAME;
        GetTreeCtrl().GetItem(&item);

        // found it?
        if ((void*)item.lParam == pData)
            return hStartItem;

        // check if child items exist
        if (item.cChildren)
        {
            // recursively iterate through child items
            HTREEITEM hItemChild = HTREEITEM(SendMessage(TVM_GETNEXTITEM, TVGN_CHILD, LPARAM(hStartItem)));
            HTREEITEM hItemFound = FindItemData(pData, hItemChild);

            // found it?
            if (hItemFound)
                return hItemFound;
        }

        // go to next sibling item
        hStartItem = HTREEITEM(SendMessage(TVM_GETNEXTITEM, TVGN_NEXT, LPARAM(hStartItem)));
    }

    // not found
    return NULL;
}
//---------------------------------------------------------------------------
void PSS_TreeView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
}
//---------------------------------------------------------------------------
void PSS_TreeView::OnBeginDrag(LPNMHDR pnmhdr, LRESULT* pLResult)
{
    m_hDragItem = ((NM_TREEVIEW *)pnmhdr)->itemNew.hItem;

    int selectedImage;
    GetTreeCtrl().GetItemImage(m_hDragItem, m_DragImageIndex, selectedImage);

    // create a drag image
    m_pDragImage = GetTreeCtrl().GetImageList(LVSIL_NORMAL);

    if (!m_pDragImage)
        m_pDragImage = GetTreeCtrl().GetImageList(LVSIL_SMALL);

    ASSERT(m_pDragImage);

    // change the cursor to the drag image (DragMove() is still required in OnMouseMove())
    VERIFY(m_pDragImage->BeginDrag(m_DragImageIndex, CPoint(0, 0)));
    VERIFY(m_pDragImage->DragEnter(GetDesktopWindow(), ((NM_TREEVIEW *)pnmhdr)->ptDrag));

    // set dragging flag
    m_Dragging = TRUE;
    m_pDropWnd = this;

    // set the drag object
    m_pDragObj = GetDragObject(m_hDragItem);

    // hide the cursor
    ShowCursor(FALSE);

    // capture all mouse messages
    SetCapture();
}
//---------------------------------------------------------------------------
void PSS_TreeView::OnEndLabelEdit(LPNMHDR pnmhdr, LRESULT* pLResult)
{
    TV_DISPINFO* ptvinfo = (TV_DISPINFO *)pnmhdr;

    if (ptvinfo->item.pszText)
    {
        ptvinfo->item.mask = TVIF_TEXT;
        GetTreeCtrl().SetItem(&ptvinfo->item);
    }

    *pLResult = TRUE;
}
//---------------------------------------------------------------------------
void PSS_TreeView::OnRButtonUp(UINT nFlags, CPoint point)
{
    OnButtonUp(point);
    CTreeView::OnRButtonUp(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_TreeView::OnLButtonUp(UINT nFlags, CPoint point)
{
    OnButtonUp(point);
    CTreeView::OnLButtonUp(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_TreeView::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_Dragging)
    {
        CPoint pt(point);
        ClientToScreen(&pt);

        // move the drag image
        VERIFY(m_pDragImage->DragMove(pt));

        // unlock window updates
        VERIFY(m_pDragImage->DragShowNolock(FALSE));

        // get the window under the mouse cursor
        CWnd* pDropWnd = WindowFromPoint(pt);
        ASSERT(pDropWnd);

        // save current window
        m_pDropWnd = pDropWnd;

        // convert from screen coordinates to drop target client coordinates
        pDropWnd->ScreenToClient(&pt);

        // if window accepts drop of symbol
        if ((ISA(pDropWnd, PSS_DropView) && ((PSS_DropView*)pDropWnd)->AcceptDrop()) ||
            (ISA(pDropWnd, PSS_DropScrollView) && ((PSS_DropScrollView*)pDropWnd)->AcceptDrop()))
            if (m_pDragObj)
            {
                PSS_DropView*       pDropView       = dynamic_cast<PSS_DropView*>(pDropWnd);
                PSS_DropScrollView* pDropScrollView = dynamic_cast<PSS_DropScrollView*>(pDropWnd);

                // if do accept drop
                if ((pDropView       && pDropView->AcceptDropItem(m_pDragObj, pt)) ||
                    (pDropScrollView && pDropScrollView->AcceptDropItem(m_pDragObj, pt)))
                    // change the drag image
                    VERIFY(m_pDragImage->SetDragCursorImage(m_DragImageIndex, CPoint(0, 0)));
                else
                    // change the drag image to impossible
                    VERIFY(m_pDragImage->SetDragCursorImage(GetIndexOfNoDropImage(), CPoint(0, 0)));
            }

        // lock window updates
        VERIFY(m_pDragImage->DragShowNolock(TRUE));
    }

    CTreeView::OnMouseMove(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_TreeView::OnDestroy()
{
    DeleteAllItems(TRUE);
    CTreeView::OnDestroy();
}
//---------------------------------------------------------------------------
void PSS_TreeView::OnButtonUp(const CPoint& point)
{
    if (m_Dragging)
    {
        // end dragging
        VERIFY(m_pDragImage->DragLeave(GetDesktopWindow()));
        m_pDragImage->EndDrag();

        // show the cursor again
        ShowCursor(TRUE);

        // stop intercepting all mouse messages
        VERIFY(::ReleaseCapture());

        m_Dragging = FALSE;

        CPoint pt(point);
        ClientToScreen(&pt);

        // get the window under the mouse cursor
        CWnd* pDropWnd = WindowFromPoint(pt);
        ASSERT(pDropWnd);

        PSS_DropView*       pDropView       = dynamic_cast<PSS_DropView*>(pDropWnd);
        PSS_DropScrollView* pDropScrollView = dynamic_cast<PSS_DropScrollView*>(pDropWnd);

        // if window accepts drop of symbol
        if ((pDropView && pDropView->AcceptDrop()) || (pDropScrollView && pDropScrollView->AcceptDrop()))
        {
            // convert from screen coordinates to drop target client coordinates
            pDropWnd->ScreenToClient(&pt);

            if (m_pDragObj)
                if (pDropView)
                    pDropView->DropItem(m_pDragObj, pt);
                else
                if (pDropScrollView)
                    pDropScrollView->DropItem(m_pDragObj, pt);
        }
    }
}
//---------------------------------------------------------------------------
BOOL PSS_TreeView::IsFindValid(HTREEITEM hItem)
{
    return TRUE;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_TreeView::AssertValid() const
    {
        CTreeView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_TreeView::Dump(CDumpContext& dc) const
    {
        CTreeView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
