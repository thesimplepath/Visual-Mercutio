/****************************************************************************
 * ==> PSS_TreeCtrl --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic tree controller                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_TreeCtrl.h"

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
IMPLEMENT_DYNAMIC(PSS_TreeCtrl, CTreeCtrl)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_TreeCtrl, CTreeCtrl)
    //{{AFX_MSG_MAP(PSS_TreeCtrl)
    ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndLabelEdit)
    ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBeginDrag)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
    ON_WM_RBUTTONUP()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_TreeCtrl::IData
//---------------------------------------------------------------------------
PSS_TreeCtrl::IData::IData(const CString& str) :
    CObject(),
    m_Str(str),
    m_Collapsed(false)
{}
//---------------------------------------------------------------------------
PSS_TreeCtrl::IData::~IData()
{
    // reset all values
    m_Str.Empty();
    m_Collapsed = false;
}
//---------------------------------------------------------------------------
// PSS_TreeCtrl
//---------------------------------------------------------------------------
PSS_TreeCtrl::PSS_TreeCtrl() :
    CTreeCtrl(),
    m_hItemDrag(NULL),
    m_hItemDrop(NULL),
    m_hDragItem(NULL),
    m_pDropWnd(NULL),
    m_pDragObj(NULL),
    m_pImageList(NULL),
    m_pDragImage(NULL),
    m_DragImageIndex(-1),
    m_Dragging(FALSE)
{}
//---------------------------------------------------------------------------
PSS_TreeCtrl::~PSS_TreeCtrl()
{
    if (m_pImageList)
    {
        m_pImageList->DeleteImageList();
        delete m_pImageList;
    }

    // NOTE use fully qualified name to ensure to never call a pure virtual function during the destruction
    PSS_TreeCtrl::EmptySaveStateDataSet();
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::LoadImageList(UINT id, int size, int grow, COLORREF maskColor)
{
    if (m_pImageList)
    {
        m_pImageList->DeleteImageList();
        delete m_pImageList;
        m_pImageList = NULL;
    }

    m_pImageList = new CImageList();
    m_pImageList->Create(id, size, grow, maskColor);

    SetImageList(m_pImageList, TVSIL_NORMAL);
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::LoadImageList(UINT startID, UINT endID, UINT flags, int cx, int cy)
{
    CBitmap bitmap;

    m_pImageList = new CImageList();
    m_pImageList->Create(cx, cy, flags, 2, 2);

    // if end index is set to zero, assign it to start
    if (!endID)
        endID = startID;

    // load bitmaps
    for (UINT id = startID; id <= endID; ++id)
    {
        bitmap.LoadBitmap(id);
        m_pImageList->Add(&bitmap, static_cast<COLORREF>(NULL));
        bitmap.DeleteObject();
    }

    SetImageList(m_pImageList, TVSIL_NORMAL);
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::LoadImageListMasked(UINT startID, UINT endID, int cx, int cy, COLORREF maskColor)
{
    CBitmap bitmap;

    m_pImageList = new CImageList();
    m_pImageList->Create(cx, cy, ILC_MASK, 2, 2);

    // if end index is set to zero, assign it to start
    if (!endID)
        endID = startID;

    // load bitmaps
    for (UINT id = startID; id <= endID; ++id)
    {
        bitmap.LoadBitmap(id);
        m_pImageList->Add(&bitmap, maskColor);
        bitmap.DeleteObject();
    }

    SetImageList(m_pImageList, TVSIL_NORMAL);
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::ExpandRoot(BOOL deep)
{
    ExpandBranch(GetRootItem(), deep);
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::ExpandBranch(HTREEITEM hTreeItem, BOOL deep)
{
    if (hTreeItem && ItemHasChildren(hTreeItem))
    {
        Expand(hTreeItem, TVE_EXPAND);

        if (deep)
        {
            hTreeItem = GetChildItem(hTreeItem);

            do
            {
                ExpandBranch(hTreeItem, deep);
            }
            while ((hTreeItem = GetNextSiblingItem(hTreeItem)) != NULL);
        }
    }

    EnsureVisible(GetSelectedItem());
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::CollapseRoot(BOOL deep)
{
    CollapseBranch(GetRootItem(), deep);
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::CollapseBranch(HTREEITEM hTreeItem, BOOL deep)
{
    if (hTreeItem && ItemHasChildren(hTreeItem))
    {
        Expand(hTreeItem, TVE_COLLAPSE);

        if (deep)
        {
            hTreeItem = GetChildItem(hTreeItem);

            do
            {
                CollapseBranch(hTreeItem, deep);
            }
            while ((hTreeItem = GetNextSiblingItem(hTreeItem)) != NULL);
        }
    }
}
//---------------------------------------------------------------------------
BOOL PSS_TreeCtrl::SelectItemName(const CString& name)
{
    HTREEITEM hItemToSelect = FindItem(name, HTREEITEM(NULL));

    if (hItemToSelect)
        return SelectItem(hItemToSelect);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_TreeCtrl::IsRootItemName(const CString& name)
{
    HTREEITEM hRoot = GetRootItem();

    return (hRoot && GetItemText(hRoot) == name);
}
//---------------------------------------------------------------------------
BOOL PSS_TreeCtrl::IsLastItemName(const CString& name)
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_TreeCtrl::IsSelectedItemRootItem()
{
    HTREEITEM hSelected = GetSelectedItem();
    return (hSelected && hSelected == GetRootItem());
}
//---------------------------------------------------------------------------
BOOL PSS_TreeCtrl::ItemNameExist(const CString& name)
{
    return FindItem(name, NULL) != NULL;
}
//---------------------------------------------------------------------------
int PSS_TreeCtrl::GetSelectItemPosition(HTREEITEM hParentItem) const
{
    HTREEITEM hSelected = GetSelectedItem();

    if (!hParentItem)
        hParentItem = GetRootItem();

    if (hSelected)
    {
        HTREEITEM hPos;

        if (hParentItem)
        {
            hPos      = GetChildItem(hParentItem);
            int index = 0;

            while (hPos)
            {
                if (hPos == hSelected)
                    return index;

                ++index;
                hPos = CTreeCtrl::GetNextItem(hPos, TVGN_NEXT);
            }
        }
    }

    return -1;
}
//---------------------------------------------------------------------------
CString PSS_TreeCtrl::GetNameSelectedItem() const
{
    HTREEITEM hSelected = GetSelectedItem();

    if (hSelected)
        return GetItemText(hSelected);

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::DeleteAllItems(BOOL deleteImageList)
{
    if (deleteImageList)
        if (m_pImageList)
        {
            m_pImageList->DeleteImageList();
            delete m_pImageList;
            m_pImageList = NULL;
        }

    // call the base class function
    CTreeCtrl::DeleteAllItems();
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::SaveCollapsedState()
{
    EmptySaveStateDataSet();
    SaveCollapsedState(GetRootItem());
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::RestoreCollapsedStateToTreeCtrl()
{
    RestoreCollapsedStateToTreeCtrl(GetRootItem());
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::SetNewStyle(long flags, BOOL setBits)
{
    long styleFlags = ::GetWindowLong(m_hWnd, GWL_STYLE) & ~flags;

    if (setBits)
        styleFlags |= flags;

    ::SetWindowLong(m_hWnd, GWL_STYLE, styleFlags);
    SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
}
//---------------------------------------------------------------------------
BOOL PSS_TreeCtrl::TransferItem(HTREEITEM hItemDrag, HTREEITEM hItemDrop)
{
    TCHAR buffer[50];

    // to avoid an infinite recursion
    TV_INSERTSTRUCT tvstruct;
    tvstruct.item.hItem      = hItemDrag;
    tvstruct.item.cchTextMax = 49;
    tvstruct.item.pszText    = buffer;
    tvstruct.item.mask       = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;

    // get information about the dragged element
    GetItem(&tvstruct.item);

    tvstruct.hParent      = hItemDrop;
    tvstruct.hInsertAfter = TVI_SORT;
    tvstruct.item.mask    = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
    
    HTREEITEM hFirstChild;
    HTREEITEM hNewItem = InsertItem(&tvstruct);

    while ((hFirstChild = GetChildItem(hItemDrag)) != NULL)
    {
        // recursively transfer all the items, then delete the first child and all its children
        TransferItem(hFirstChild, hNewItem);
        DeleteItem(hFirstChild);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TreeCtrl::IsChildNodeOf(HTREEITEM hItemChild, HTREEITEM hItemSuspectedParent)
{
    do
    {
        if (hItemChild == hItemSuspectedParent)
            break;
    }
    while ((hItemChild = GetParentItem(hItemChild)) != NULL);

    return (hItemChild != NULL);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TreeCtrl::GetPrevItem(HTREEITEM hItem)
{
    HTREEITEM hTreeItem = CTreeCtrl::GetPrevSiblingItem(hItem);

    if (!hTreeItem)
        hTreeItem = CTreeCtrl::GetParentItem(hItem);
    else
        hTreeItem = GetLastItem(hTreeItem);

    return hTreeItem;
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TreeCtrl::GetNextItem(HTREEITEM hItem)
{
    HTREEITEM hTreeItem;

    if (CTreeCtrl::ItemHasChildren(hItem))
        // return first child
        return CTreeCtrl::GetChildItem(hItem);

    // return next sibling item. Move up in the tree to find a parent's sibling if needed
    while ((hTreeItem = CTreeCtrl::GetNextSiblingItem(hItem)) == NULL)
        if ((hItem = CTreeCtrl::GetParentItem(hItem)) == NULL)
            return NULL;

    return hTreeItem;
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TreeCtrl::GetLastItem(HTREEITEM hItem)
{
    // last child of the last child of the last child ...
    HTREEITEM hNext;

    if (!hItem)
    {
        // get the last item at the top level
        hNext = CTreeCtrl::GetRootItem();

        while (hNext)
        {
            hItem = hNext;
            hNext = CTreeCtrl::GetNextSiblingItem(hNext);
        }
    }

    while (CTreeCtrl::ItemHasChildren(hItem))
    {
        hNext = CTreeCtrl::GetChildItem(hItem);

        while (hNext)
        {
            hItem = hNext;
            hNext = CTreeCtrl::GetNextSiblingItem(hNext);
        }
    }

    return hItem;
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TreeCtrl::FindItem(const CString& str,
                                 BOOL           caseSensitive,
                                 BOOL           downDir,
                                 BOOL           wholeWord,
                                 HTREEITEM      hItem)
{
    const int lenSearchStr = str.GetLength();

    if (!lenSearchStr)
        return NULL;

    HTREEITEM hSelItem = hItem   ? hItem                 : CTreeCtrl::GetSelectedItem();
    HTREEITEM hCurItem = downDir ? GetNextItem(hSelItem) : GetPrevItem(hSelItem);

    if (!hCurItem)
        if (downDir)
            hCurItem = CTreeCtrl::GetRootItem();
        else
            hCurItem = GetLastItem(NULL);

    CString search = str;

    if (!caseSensitive)
        search.MakeLower();

    while (hCurItem && hCurItem != hSelItem)
    {
        CString itemText = CTreeCtrl::GetItemText(hCurItem);

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
                    if (isalpha(itemText[n - 1]) || itemText[n - 1] == '_')
                    {
                        // not whole word
                        itemText = itemText.Right(itemText.GetLength() - n - lenSearchStr);
                        continue;
                    }

                // check succeeding char
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
                hCurItem = CTreeCtrl::GetRootItem();
            else
                hCurItem = GetLastItem(NULL);
    }

    return NULL;
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TreeCtrl::FindItem(const CString& label, HTREEITEM hStartItem)
{
    // if item is NULL, start search from root item
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
HTREEITEM PSS_TreeCtrl::FindItemData(void* pData, HTREEITEM hStartItem)
{
    // if item is NULL, start search from root item
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
        GetItem(&item);

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
void PSS_TreeCtrl::OnEndLabelEdit(LPNMHDR pnmhdr, LRESULT* pLResult)
{
    TV_DISPINFO* ptvinfo = (TV_DISPINFO*)pnmhdr;

    if (ptvinfo->item.pszText)
    {
        ptvinfo->item.mask = TVIF_TEXT;
        SetItem(&ptvinfo->item);
    }

    *pLResult = TRUE;
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::OnBeginDrag(LPNMHDR pnmhdr, LRESULT* pLResult)
{
    m_hDragItem = ((NM_TREEVIEW *)pnmhdr)->itemNew.hItem;

    int selectedImage;
    GetItemImage(m_hDragItem, m_DragImageIndex, selectedImage);

    // create a drag image
    m_pDragImage = GetImageList(LVSIL_NORMAL);

    if (!m_pDragImage)
        m_pDragImage = GetImageList(LVSIL_SMALL);

    PSS_Assert(m_pDragImage);

    // change the cursor to the drag image (DragMove() is still required in OnMouseMove())
    VERIFY(m_pDragImage->BeginDrag(m_DragImageIndex, CPoint(0, 0)));
    VERIFY(m_pDragImage->DragEnter(GetDesktopWindow(), ((NM_TREEVIEW*)pnmhdr)->ptDrag));

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
void PSS_TreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
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
        PSS_Assert(pDropWnd);

        // save current window pointer
        m_pDropWnd = pDropWnd;

        // convert from screen coordinates to drop target client coordinates
        pDropWnd->ScreenToClient(&pt);

        PSS_DropView*       pDropView       = dynamic_cast<PSS_DropView*>(pDropWnd);
        PSS_DropScrollView* pDropScrollView = dynamic_cast<PSS_DropScrollView*>(pDropWnd);

        // if window accepts symbols drop
        if ((pDropView && pDropView->AcceptDrop()) || (pDropScrollView && pDropScrollView->AcceptDrop()))
            if (m_pDragObj)
                // if do accept drop
                if ((pDropView       && pDropView->AcceptDropItem(m_pDragObj, pt)) ||
                    (pDropScrollView && pDropScrollView->AcceptDropItem(m_pDragObj, pt)))
                    // change the drag image
                    m_pDragImage->SetDragCursorImage(m_DragImageIndex, CPoint(0, 0));
                else
                    // change the drag image to no-drop
                    m_pDragImage->SetDragCursorImage(GetIndexOfNoDropImage(), CPoint(0, 0));

        // lock window updates
        VERIFY(m_pDragImage->DragShowNolock(TRUE));
    }

    CTreeCtrl::OnMouseMove(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
    OnButtonUp(point);
    CTreeCtrl::OnLButtonUp(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::OnRButtonUp(UINT nFlags, CPoint point)
{
    OnButtonUp(point);
    CTreeCtrl::OnRButtonUp(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::OnDestroy()
{
    DeleteAllItems(TRUE);
    CTreeCtrl::OnDestroy();
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::OnButtonUp(const CPoint& point)
{
    if (m_Dragging)
    {
        // end dragging
        VERIFY(m_pDragImage->DragLeave(GetDesktopWindow()));
        m_pDragImage->EndDrag();

        // show the cursor again
        ShowCursor(TRUE);

        // stop capturing all mouse messages
        VERIFY(::ReleaseCapture());
        m_Dragging = FALSE;

        CPoint pt(point);
        ClientToScreen(&pt);

        // get the window under the mouse cursor
        CWnd* pDropWnd = WindowFromPoint(pt);
        PSS_Assert(pDropWnd);

        PSS_DropView*       pDropView       = dynamic_cast<PSS_DropView*>(pDropWnd);
        PSS_DropScrollView* pDropScrollView = dynamic_cast<PSS_DropScrollView*>(pDropWnd);

        // if window accepts symbols drop
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
BOOL PSS_TreeCtrl::IsFindValid(HTREEITEM hItem)
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::SaveCollapsedState(HTREEITEM hTreeItem)
{
    if (hTreeItem && ItemHasChildren(hTreeItem))
    {
        // get the item text
        const CString itemText = CTreeCtrl::GetItemText(hTreeItem);
        IData*        pObj     = AddSaveStateDataToSet(itemText);

        // if exists, set the collapsed state
        if (pObj)
            pObj->SetCollapsed((GetItemState(hTreeItem, TVIS_EXPANDED) & TVIS_EXPANDED) ? false : true);

        hTreeItem = GetChildItem(hTreeItem);

        do
        {
            SaveCollapsedState(hTreeItem);
        }
        while ((hTreeItem = GetNextSiblingItem(hTreeItem)) != NULL);
    }
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::RestoreCollapsedStateToTreeCtrl(HTREEITEM hTreeItem)
{
    if (hTreeItem && ItemHasChildren(hTreeItem))
    {
        // get the item text
        const CString itemText = CTreeCtrl::GetItemText(hTreeItem);

        // get the data object
        IData* pObj = FindElementFromSaveStateDataSet(itemText);

        // if exists, set the previously saved state
        if (pObj)
            Expand(hTreeItem, pObj->IsCollapsed() ? TVE_COLLAPSE : TVE_EXPAND);

        hTreeItem = GetChildItem(hTreeItem);

        do
        {
            RestoreCollapsedStateToTreeCtrl(hTreeItem);
        }
        while ((hTreeItem = GetNextSiblingItem(hTreeItem)) != NULL);
    }
}
//---------------------------------------------------------------------------
void PSS_TreeCtrl::EmptySaveStateDataSet()
{
    IDataIterator i(&m_DataSet);

    for (IData* pElement = i.GetFirst(); pElement; pElement = i.GetNext())
        delete pElement;

    m_DataSet.RemoveAll();
}
//---------------------------------------------------------------------------
PSS_TreeCtrl::IData* PSS_TreeCtrl::AddSaveStateDataToSet(const CString& str)
{
    std::unique_ptr<IData> pData(new IData(str));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
bool PSS_TreeCtrl::DeleteElementFromSaveStateDataSet(const CString& str)
{
    IDataIterator it(&m_DataSet);

    for (IData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Str == str)
        {
            delete pElement;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
PSS_TreeCtrl::IData* PSS_TreeCtrl::FindElementFromSaveStateDataSet(const CString& str)
{
    IDataIterator i(&m_DataSet);

    for (IData* pElement = i.GetFirst(); pElement; pElement = i.GetNext())
        if (pElement->m_Str == str)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
