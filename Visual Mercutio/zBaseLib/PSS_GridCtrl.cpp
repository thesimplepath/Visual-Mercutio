/****************************************************************************
 * ==> PSS_GridCtrl --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid controller                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridCtrl.h"
#include "PSS_ListViewEdit.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Offset_First 2
#define M_Offset_Other 6
#define M_Timer_ID     1
#define IDC_EDITCTRL   0x1234
//---------------------------------------------------------------------------
// Global functions
//---------------------------------------------------------------------------
inline int StrComp(const CString* pFirstItem, const CString* pSecondItem)
{
    return pFirstItem->Compare(*pSecondItem);
}
//---------------------------------------------------------------------------
// PSS_GridCtrl::IRectangle
//---------------------------------------------------------------------------
PSS_GridCtrl::IRectangle::IRectangle(PSS_GridCtrl* pCtrl, CDC* pDC, int indent, const CRect& rect) :
    m_pDC(pDC),
    m_TopDown(0),
    m_Left(0),
    m_Top(0)
{
    const int halfImage  = (pCtrl->m_CxImage >> 1);
    const int bottomDown = rect.top + halfImage + ((rect.Height() - pCtrl->m_CyImage) >> 1);

    m_RightBottom.cx = (pCtrl->m_CxImage >> 1) + 3;
    m_RightBottom.cy = (pCtrl->m_CyImage >> 1) + 3;
    m_Left           = rect.left + indent * pCtrl->m_CxImage - halfImage;
    m_Top            = bottomDown - (m_RightBottom.cy >> 1);
    m_LeftTop.x      = m_Left     - (m_RightBottom.cx >> 1);
    m_LeftTop.y      = m_Top;
    m_TopDown        = bottomDown;
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IRectangle::~IRectangle()
{}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IRectangle::DrawRectangle(PSS_GridCtrl* pCtrl)
{
    // erase background
    const CRect rc(m_LeftTop, m_RightBottom);
    m_pDC->FillRect(rc, &pCtrl->m_BrushErase);

    // draw rectangle
    CPen* pPenRectangle = m_pDC->SelectObject(&pCtrl->m_PenRectangle);
    m_pDC->Rectangle(rc);
    m_pDC->SelectObject(pPenRectangle);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IRectangle::DrawPlus()
{
    m_pDC->MoveTo(m_Left, m_TopDown - 2);
    m_pDC->LineTo(m_Left, m_TopDown + 3);

    m_pDC->MoveTo(m_Left - 2, m_TopDown);
    m_pDC->LineTo(m_Left + 3, m_TopDown);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IRectangle::DrawMinus()
{
    m_pDC->MoveTo(m_Left - 2, m_TopDown);
    m_pDC->LineTo(m_Left + 3, m_TopDown);
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::IRectangle::HitTest(const CPoint& pt) const
{
    const CRect rc = GetHitTestRect();
    return rc.PtInRect(pt);
}
//---------------------------------------------------------------------------
// PSS_GridCtrl::IItemInfo
//---------------------------------------------------------------------------
PSS_GridCtrl::IItemInfo::IItemInfo() :
    m_EnumCtrlType(IE_CT_Edit),
    m_LParam(NULL),
    m_Color(COLORREF(-1)),
    m_Image(-1),
    m_Check(0)
{}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItemInfo::~IItemInfo()
{
    POSITION pPos = m_ListData.GetStartPosition();

    while (pPos)
    {
        int          key;
        CStringList* pStringList;

        m_ListData.GetNextAssoc(pPos, key, pStringList);

        if (pStringList)
        {
            pStringList->RemoveAll();
            delete pStringList;
        }
    }

    m_ListData.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::CopyObjects(IItemInfo* pItemInfo)
{
    SetItemText(pItemInfo->GetItemText());
    m_SubItems.Copy(pItemInfo->m_SubItems);
    CopyControls(pItemInfo);
    CopyColors(pItemInfo);
    SetCheck(pItemInfo->GetCheck());
    SetImage(pItemInfo->GetImage());
    m_LParam = pItemInfo->m_LParam;
    m_Color = pItemInfo->m_Color;
    CopySubItemImageList(pItemInfo);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::CopySubItemImageList(IItemInfo* pItemInfo)
{
    POSITION pPos = pItemInfo->m_ImageSubItems.GetStartPosition();

    while (pPos)
    {
        int key;
        int image = -1;

        pItemInfo->m_ImageSubItems.GetNextAssoc(pPos, key, image);

        if (image != -1)
            m_ImageSubItems.SetAt(key, image);
    }
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::CopyControls(IItemInfo* pItemInfo)
{
    const int colCount = pItemInfo->GetItemCount();

    for (int col = 0; col < colCount; ++col)
    {
        IEControlType ctrlType;

        // the function will return true if other than edit control
        if (pItemInfo->GetControlType(col, ctrlType))
        {
            SetControlType(ctrlType, col);

            CStringList* pList = NULL;
            pItemInfo->GetListData(col, pList);

            // should test if this is data list material
            if (pList)
                SetListData(col, pList);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::CopyColors(IItemInfo* pItemInfo)
{
    POSITION pPos = pItemInfo->m_Colors.GetStartPosition();

    while (pPos)
    {
        int      key;
        COLORREF color;

        pItemInfo->m_Colors.GetNextAssoc(pPos, key, color);
        m_Colors.SetAt(key, color);
    }
}
//---------------------------------------------------------------------------
// PSS_GridCtrl::IItem
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem::IItem() :
    m_pParent(NULL),
    m_pNodeInfo(NULL),
    m_Index(-1),
    m_Indent(-1),
    m_SetChildFlag(-1),
    m_HideChildren(FALSE)
{}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem::~IItem()
{
    POSITION pPos = m_ListChild.GetHeadPosition();

    // delete child nodes
    while (pPos)
    {
        IItem* pItem = (IItem*)m_ListChild.GetNext(pPos);

        if (pItem)
        {
            if (pItem->m_pNodeInfo)
                delete pItem->m_pNodeInfo;

            delete pItem;
        }
    }

    m_ListChild.RemoveAll();
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_GridCtrl, CListCtrl)
    //{{AFX_MSG_MAP(PSS_GridCtrl)
    ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
    ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
    ON_WM_CREATE()
    ON_WM_HSCROLL()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()
    ON_WM_VSCROLL()
    ON_WM_LBUTTONUP()
    ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
    ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBegindrag)
    ON_WM_MEASUREITEM_REFLECT()
    ON_WM_DRAWITEM_REFLECT()
    ON_WM_SYSCOLORCHANGE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_GridCtrl
//---------------------------------------------------------------------------
PSS_GridCtrl::PSS_GridCtrl() :
    m_CxImage(0),
    m_CyImage(0),
    m_hImageList(NULL),
    m_CurSubItem(0),
    m_DragItem(-1),
    m_DragTarget(-1),
    m_IsDragging(FALSE)
{
    m_BrushErase.CreateSolidBrush(RGB(255, 255, 255));
    m_PenTreeLine.CreatePen(PS_SOLID, 1, RGB(192, 192, 192));
    m_PenRectangle.CreatePen(PS_SOLID, 1, RGB(198, 198, 198));
    m_PenPlusMinus.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
}
//---------------------------------------------------------------------------
PSS_GridCtrl::~PSS_GridCtrl()
{
    m_BrushErase.DeleteObject();
    m_PenPlusMinus.DeleteObject();
    m_PenRectangle.DeleteObject();
    m_PenTreeLine.DeleteObject();

    while (m_RootItems.GetCount())
    {
        IItem* pRoot = (IItem*)m_RootItems.RemoveHead();

        if (pRoot && GetData(pRoot))
            delete GetData(pRoot);

        delete pRoot;
    }

    m_RootItems.RemoveAll();
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItemInfo* PSS_GridCtrl::CopyData(IItemInfo* lpSrc)
{
    // debug
    ASSERT(FALSE);

    // release
    return NULL;
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::GetIcon(const IItem* pItem) const
{
    // get the first item in image list, what ever that is
    return 0;
}
//---------------------------------------------------------------------------
COLORREF PSS_GridCtrl::GetCellRGB() const
{
    return RGB(192, 0, 0);
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem* PSS_GridCtrl::InsertRootItem(IItemInfo* pInfo)
{
    std::unique_ptr<IItemInfo> pDefaultItemInfo;

    if (!pInfo)
    {
        pDefaultItemInfo.reset(new IItemInfo());
        pInfo = pDefaultItemInfo.get();
    }

    std::unique_ptr<IItem> pRoot(new IItem());

    Clear(pRoot.get());
    UpdateData(pRoot.get(), pInfo);
    SetIndent(pRoot.get(), 1);
    SetCurIndex(pRoot.get(), GetItemCount());
    SetParentItem(pRoot.get(), NULL);

    IItemInfo* pItemInfo = GetData(pRoot.get());
    CString    strItem   = pItemInfo->GetItemText();

    LV_ITEM lvItem;
    lvItem.mask     = LVIF_TEXT | LVIF_INDENT | LVIF_PARAM;
    lvItem.pszText  = strItem.GetBuffer(1);
    lvItem.iItem    = GetItemCount();
    lvItem.lParam   = LPARAM(pRoot.get());
    lvItem.iIndent  = 1;
    lvItem.iSubItem = 0;
    CListCtrl::InsertItem(&lvItem);

    const int size = pItemInfo->GetItemCount();

    for (int i = 0; i < size; ++i)
    {
        CString str     = pItemInfo->GetSubItem(i);
        lvItem.mask     = LVIF_TEXT;
        lvItem.iSubItem = i + 1;
        lvItem.pszText  = str.GetBuffer(1);
        SetItem(&lvItem);
    }

    m_RootItems.AddTail(pRoot.get());

    if (pDefaultItemInfo.get())
        pDefaultItemInfo.release();

    return pRoot.release();
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::DeleteRootItem(IItem* pRoot)
{
    POSITION pPos = m_RootItems.Find(pRoot);

    if (pPos)
    {
        IItem* pRootToDel = (IItem*)m_RootItems.GetAt(pPos);

        if (pRootToDel->m_pNodeInfo)
            delete pRootToDel->m_pNodeInfo;

        delete pRootToDel;

        m_RootItems.RemoveAt(pPos);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::IsRoot(IItem* pItem) const
{
    return (m_RootItems.Find(pItem) != NULL);
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem* PSS_GridCtrl::GetRootItem(int index)
{
    POSITION pPos = m_RootItems.FindIndex(index);

    if (!pPos)
        return NULL;

    return (IItem*)m_RootItems.GetAt(pPos);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::DeleteAll()
{
    SetRedraw(false);
    DeleteAllItems();

    POSITION pPos = m_RootItems.GetHeadPosition();

    while (pPos)
    {
        IItem* pRoot = (IItem*)m_RootItems.GetNext(pPos);

        if (pRoot)
            // if root, must delete from m_rootData
            if (!GetParentItem(pRoot))
                DeleteRootItem(pRoot);
            else
                Delete(pRoot);
    }

    SetRedraw(true);
    InvalidateRect(NULL);
    UpdateWindow();
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem* PSS_GridCtrl::GetPrev(IItem* pStartAt, IItem* pNode, BOOL init, BOOL dontIncludeHidden)
{
    static IItem* pPrev;

    if (init)
        pPrev = pStartAt;

    if (pNode == pStartAt)
        return pPrev;

    pPrev = pStartAt;

    if (dontIncludeHidden)
    {
        if (!IsCollapsed(pStartAt))
        {
            POSITION pPos = pStartAt->m_ListChild.GetHeadPosition();

            while (pPos)
            {
                IItem* pCur   = (IItem*)pStartAt->m_ListChild.GetNext(pPos);
                IItem* pChild = GetPrev(pCur, pNode, FALSE, TRUE);

                if (pChild)
                    return pChild;
            }
        }
    }
    else
    {
        POSITION pPos = pStartAt->m_ListChild.GetHeadPosition();

        while (pPos)
        {
            IItem* pCur   = (IItem*)pStartAt->m_ListChild.GetNext(pPos);
            IItem* pChild = GetPrev(pCur, pNode, FALSE, FALSE);

            if (pChild)
                return pChild;
        }
    }

    if (init)
        return pPrev;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem* PSS_GridCtrl::GetNext(IItem* pStartAt, IItem* pNode, BOOL init, BOOL dontIncludeHidden)
{
    static BOOL found;

    if (init)
        found = FALSE;

    if (pNode == pStartAt)
        found = TRUE;

    if (dontIncludeHidden)
    {
        if (!IsCollapsed(pStartAt))
        {
            POSITION pPos = pStartAt->m_ListChild.GetHeadPosition();

            while (pPos)
            {
                IItem* pChild = (IItem*)pStartAt->m_ListChild.GetNext(pPos);

                if (found)
                    return pChild;

                pChild = GetNext(pChild, pNode, FALSE, TRUE);

                if (pChild)
                    return pChild;
            }
        }
    }
    else
    {
        POSITION pPos = pStartAt->m_ListChild.GetHeadPosition();

        while (pPos)
        {
            IItem* pChild = (IItem*)pStartAt->m_ListChild.GetNext(pPos);

            if (found)
                return pChild;

            pChild = GetNext(pChild, pNode, FALSE, FALSE);

            if (pChild)
                return pChild;
        }
    }

    // if reached top and last level, return original
    if (init)
        return pNode;

    return NULL;
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::GetSelectedItem() const
{
    return GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem* PSS_GridCtrl::GetTreeItem(int index)
{
    return reinterpret_cast<IItem*>(GetItemData(index));
}
//---------------------------------------------------------------------------
UINT PSS_GridCtrl::GetCount() const
{
    UINT     count    = 0;
    UINT     subCount = 0;
    POSITION pPos     = m_RootItems.GetHeadPosition();

    while (pPos)
    {
        IItem* pRoot  = (IItem*)m_RootItems.GetNext(pPos);
        count        += GetCount(pRoot, subCount) + 1;
    }

    return count;
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::GetChildrenCount(const IItem* pItem) const
{
    return pItem->m_ListChild.GetCount();
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::IsChildOf(const IItem* pParent, const IItem* pChild) const
{
    if (pChild == pParent)
        return TRUE;

    POSITION pPos = pParent->m_ListChild.GetHeadPosition();

    while (pPos)
    {
        IItem* pNode = (IItem*)pParent->m_ListChild.GetNext(pPos);

        if (IsChildOf(pNode, pChild))
            return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::ItemHasChildren(const IItem* pItem) const
{
    // check if the item can contain children
    const int flag = pItem->m_SetChildFlag;

    if (flag != -1)
        return 1;

    return pItem->m_ListChild.GetCount();
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::SetChildrenFlag(IItem *pItem, int flag) const
{
    pItem->m_SetChildFlag = flag;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::IsCollapsed(const IItem* pItem) const
{
    // i.e not visible
    return pItem->m_HideChildren;
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::GetIndent(const IItem* pItem) const
{
    return pItem->m_Indent;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::SetIndent(IItem *pItem, int indent)
{
    pItem->m_Indent = indent;
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::GetCurIndex(const IItem *pItem) const
{
    return pItem->m_Index;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::SetCurIndex(IItem* pItem, int index)
{
    pItem->m_Index = index;
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem* PSS_GridCtrl::GetParentItem(const IItem* pItem)
{
    return pItem->m_pParent;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::SetParentItem(IItem* pItem, IItem* pParent)
{
    pItem->m_pParent = pParent;

}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItemInfo* PSS_GridCtrl::GetData(const IItem* pItem)
{
    return pItem->m_pNodeInfo;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::UpdateData(IItem* pItem, IItemInfo* pInfo, BOOL updateRow)
{
    pItem->m_pNodeInfo = pInfo;

    // update list view item and sub-items
    if (updateRow)
        InvalidateItem(pItem);
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem* PSS_GridCtrl::InsertItem(IItem* pParent, IItemInfo* pInfo, BOOL update)
{
    if (!pParent)
        return NULL;

    std::unique_ptr<IItem>     pItem(new IItem());
    std::unique_ptr<IItemInfo> pDefaultItemInfo;

    if (!pInfo)
    {
        pDefaultItemInfo.reset(new IItemInfo());
        pInfo = pDefaultItemInfo.get();
    }

    UpdateData(pItem.get(), pInfo);
    SetIndent(pItem.get(), GetIndent(pParent) + 1);
    SetParentItem(pItem.get(), pParent);

    // add as the last child 
    pParent->m_ListChild.AddTail(pItem.get());

    if (!update)
        Hide(pParent, TRUE);
    else
    {
        // calculate the list view index for the new node
        const int index = NodeToIndex(pItem.get());
        CString   str   = GetData(pItem.get())->GetItemText();

        // insert item
        LV_ITEM lvItem;
        lvItem.mask     = LVIF_TEXT | LVIF_INDENT | LVIF_PARAM;
        lvItem.pszText  = str.GetBuffer(1);
        lvItem.iItem    = index;
        lvItem.iSubItem = 0;
        lvItem.lParam   = LPARAM(pItem.get());
        lvItem.iIndent  = GetIndent(pItem.get());
        CListCtrl::InsertItem(&lvItem);

        if (pInfo->GetCheck())
            SetCheck(index);

        const int size = GetData(pItem.get())->GetItemCount();

        // get sub-items
        for (int i = 0; i < size; ++i)
        {
            CString str     = GetData(pItem.get())->GetSubItem(i);
            lvItem.mask     = LVIF_TEXT;
            lvItem.iSubItem = i + 1;
            lvItem.pszText  = str.GetBuffer(1);
            SetItem(&lvItem);
        }

        // better do this
        InternalUpdateTree();
    }

    if (pDefaultItemInfo.get())
        pDefaultItemInfo.release();

    return pItem.release();
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::Collapse(IItem* pItem)
{
    if (pItem && ItemHasChildren(pItem))
    {
        SetRedraw(FALSE);

        try
        {
            const int index = NodeToIndex(pItem);
            HideChildren(pItem, TRUE, index + 1);
            InternalUpdateTree();
        }
        catch (...)
        {
            SetRedraw(TRUE);
            throw;
        }

        SetRedraw(TRUE);
    }
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::Expand(IItem* pItem, int index)
{
    if (ItemHasChildren(pItem) && IsCollapsed(pItem))
    {
        LV_ITEM lvItem;
        lvItem.mask     = LVIF_INDENT;
        lvItem.iItem    = index;
        lvItem.iSubItem = 0;
        lvItem.lParam   = LPARAM(pItem);
        lvItem.iIndent  = GetIndent(pItem);
        SetItem(&lvItem);

        Hide(pItem, FALSE);

        // expand children
        POSITION pPos = pItem->m_ListChild.GetHeadPosition();

        while (pPos)
        {
            IItem*  pNextNode = (IItem*)pItem->m_ListChild.GetNext(pPos);
            CString str       = GetData(pNextNode)->GetItemText();

            LV_ITEM lvItem;
            lvItem.mask     = LVIF_TEXT | LVIF_INDENT | LVIF_PARAM;
            lvItem.pszText  = str.GetBuffer(1);
            lvItem.iItem    = index + 1;
            lvItem.iSubItem = 0;
            lvItem.lParam   = LPARAM(pNextNode);
            lvItem.iIndent  = GetIndent(pItem) + 1;
            CListCtrl::InsertItem(&lvItem);

            if (GetData(pNextNode)->GetCheck())
                SetCheck(index + 1);

            // get sub-items
            const int size = GetData(pNextNode)->GetItemCount();

            for (int i = 0; i < size; ++i)
            {
                CString str     = GetData(pNextNode)->GetSubItem(i);
                lvItem.mask     = LVIF_TEXT;
                lvItem.iSubItem = i + 1;
                lvItem.pszText  = str.GetBuffer(1);
                SetItem(&lvItem);
            }

            ++index;
        }
    }

    InternalUpdateTree();
    return index;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::ExpandAll(IItem* pItem, int& scroll)
{
    const int children = pItem->m_ListChild.GetCount();

    if (children > 0)
    {
        const int index = NodeToIndex(pItem);
        scroll          = Expand(pItem, index);
    }

    POSITION pPos = pItem->m_ListChild.GetHeadPosition();

    while (pPos)
    {
        IItem* pChild = (IItem*)pItem->m_ListChild.GetNext(pPos);
        ExpandAll(pChild, scroll);
    }
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::ExpandUntil(IItem* pItem, IItem* pStopAt)
{
    const int children = pItem->m_ListChild.GetCount();

    if (children > 0)
    {
        POSITION pPos = pItem->m_ListChild.GetHeadPosition();

        while (pPos)
        {
            IItem* pChild = (IItem*)pItem->m_ListChild.GetNext(pPos);

            if (pChild == pStopAt)
            {
                const int size          = GetIndent(pChild);
                IItem**   ppParentArray = NULL;
                int       i             = 0;

                try
                {
                    ppParentArray = new IItem*[size];

                    while (1)
                    {
                        IItem* pParent = GetParentItem(pChild);

                        if (IsRoot(pParent))
                            break;

                        pChild           = pParent;
                        ppParentArray[i] = pChild;
                        ++i;
                    }

                    for (int x = i; x > 0; --x)
                    {
                        IItem* pParent = ppParentArray[x - 1];
                        Expand(pParent, NodeToIndex(pParent));
                    }
                }
                catch (...)
                {
                    delete[] ppParentArray;
                    throw;
                }

                delete[] ppParentArray;
                return;
            }
        }
    }

    POSITION pPos = pItem->m_ListChild.GetHeadPosition();

    while (pPos)
    {
        IItem* pChild = (IItem*)pItem->m_ListChild.GetNext(pPos);
        ExpandUntil(pChild, pStopAt);
    }
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::SelectNode(IItem* pLocateNode)
{
    if (IsRoot(pLocateNode))
    {
        const UINT flags = LVIS_SELECTED | LVIS_FOCUSED;
        SetItemState(0, flags, flags);
        return 0;
    }

    int    selectedItem    = -1;
    IItem* pNode           =  pLocateNode;
    IItem* pTopLevelParent =  NULL;

    // get top parent
    while (1)
    {
        IItem* pParent = GetParentItem(pLocateNode);

        if (IsRoot(pParent))
            break;

        pLocateNode = pParent;
    }

    // on top of all
    pTopLevelParent = pLocateNode;

    // expand the folder
    if (pTopLevelParent)
    {
        SetRedraw(FALSE);

        try
        {
            CWaitCursor wait;
            IItem*      pRoot = GetParentItem(pTopLevelParent);

            if (IsCollapsed(pRoot))
                Expand(pRoot, 0);

            ExpandUntil(pTopLevelParent, pNode);

            const UINT flags = LVIS_SELECTED | LVIS_FOCUSED;
            selectedItem = NodeToIndex(pNode);

            SetItemState(selectedItem, flags, flags);
        }
        catch (...)
        {
            SetRedraw(TRUE);
            throw;
        }

        SetRedraw(TRUE);
        EnsureVisible(selectedItem, TRUE);
    }

    return selectedItem;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::DeleteItemEx(IItem* pSelItem, int item)
{
    SetRedraw(FALSE);

    try
    {
        // delete cur item in listview
        DeleteItem(item);

        // delete/hide all item children
        HideChildren(pSelItem, TRUE, item);

        // delete all internal nodes. If root, must delete from root data
        if (!GetParentItem(pSelItem))
            DeleteRootItem(pSelItem);
        else
            Delete(pSelItem);

        InternalUpdateTree();

        // no more items in list
        if (item - 1 < 0)
        {
            SetRedraw(TRUE);
            InvalidateRect(NULL);
            UpdateWindow();

            return;
        }

        const UINT flags = LVIS_SELECTED | LVIS_FOCUSED;

        // ...just to get the documention right :)
        CRect rcTestIfItemIsValidToSelectOtherWiseSubtrackOneFromItem;

        GetItemRect(item, rcTestIfItemIsValidToSelectOtherWiseSubtrackOneFromItem, LVIR_LABEL) ?
                SetItemState(item, flags, flags) : SetItemState(item - 1, flags, flags);
    }
    catch (...)
    {
        SetRedraw(TRUE);
        throw;
    }

    SetRedraw(TRUE);
    InvalidateRect(NULL);
    UpdateWindow();
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::GetColCount() const
{
    CHeaderCtrl* pHeader = GetHeaderCtrl();
    return pHeader ? pHeader->GetItemCount() : 0;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::SortEx(BOOL sortChildren)
{
    const int items = m_RootItems.GetCount();

    if (items <= 0)
        return;

    if (sortChildren)
    {
        POSITION pPosSortChildren = GetRootHeadPosition();

        while (pPosSortChildren)
        {
            IItem* pParent = (IItem*)GetNextRoot(pPosSortChildren);

            // sort children
            Sort(pParent, TRUE);
        }
    }

    // set the hide flag for the root items
    POSITION pPosHide = GetRootHeadPosition();

    while (pPosHide)
    {
        IItem* pParent = (IItem*)GetNextRoot(pPosHide);
        Collapse(pParent);
    }

    // this is quite okay, don't delete the internal state
    DeleteAllItems();

    // sort root items
    IItem** ppSortArray = new IItem*[items];

    POSITION pPosCur = m_RootItems.GetHeadPosition();

    // fill array with children
    for (int i = 0; pPosCur; ++i)
    {
        ppSortArray[i] = (IItem*)m_RootItems.GetAt(pPosCur);
        m_RootItems.GetNext(pPosCur);
    }

    std::qsort(ppSortArray, items, sizeof(IItem*), CompareChildren);

    // reorganize the root items with new sorted list
    pPosCur = m_RootItems.GetHeadPosition();

    for (int i = 0; pPosCur; ++i)
    {
        m_RootItems.SetAt(pPosCur, ppSortArray[i]);
        m_RootItems.GetNext(pPosCur);
    }

    delete[] ppSortArray;

    // do a "repaint" of the root items... the children may be "refreshed" with an expand of the children
    int      index = 0;
    POSITION pPos  = GetRootHeadPosition();

    while (pPos)
    {
        IItem* pParent = (IItem*)GetNextRoot(pPos);

        if (pParent)
        {
            IItemInfo* pItemInfo = GetData(pParent);
            CString    str       = pItemInfo->GetItemText();

            LV_ITEM lvItem;
            lvItem.mask     = LVIF_TEXT | LVIF_INDENT | LVIF_PARAM;
            lvItem.pszText  = str.GetBuffer(1);
            lvItem.iItem    = index;
            lvItem.iSubItem = 0;

            // associate the root and all its children with this list view item
            lvItem.lParam  = LPARAM(pParent);
            lvItem.iIndent = GetIndent(pParent);
            CListCtrl::InsertItem(&lvItem);

            const int size = pItemInfo->GetItemCount();

            for (int i = 0; i < size; ++i)
            {
                CString strSubItems = pItemInfo->GetSubItem(i);
                lvItem.mask         = LVIF_TEXT;
                lvItem.iSubItem     = i + 1;
                lvItem.pszText      = strSubItems.GetBuffer(1);
                SetItem(&lvItem);
            }

            ++index;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::Sort(IItem* pParent, BOOL sortChildren)
{
    const int children = GetChildrenCount(pParent);

    if (children > 1)
    {
        IItem**  ppSortArray = NULL;
        POSITION pPos        = pParent->m_ListChild.GetHeadPosition();

        try
        {
            ppSortArray = new IItem*[children];

            // fill children array
            for (int i = 0; pPos; ++i)
            {
                ASSERT(i < children);
                ppSortArray[i] = (IItem*)pParent->m_ListChild.GetAt(pPos);
                pParent->m_ListChild.GetNext(pPos);
            }

            std::qsort(ppSortArray, children, sizeof(IItem*), CompareChildren);

            // reorganize children with the new sorted list
            pPos = pParent->m_ListChild.GetHeadPosition();

            for (int i = 0; pPos; ++i)
            {
                ASSERT(i < children);
                pParent->m_ListChild.SetAt(pPos, ppSortArray[i]);
                pParent->m_ListChild.GetNext(pPos);
            }
        }
        catch (...)
        {
            delete[] ppSortArray;
            throw;
        }

        delete[] ppSortArray;
    }

    if (sortChildren)
    {
        POSITION pPos = pParent->m_ListChild.GetHeadPosition();

        while (pPos)
        {
            IItem* pChild = (IItem*)pParent->m_ListChild.GetNext(pPos);
            Sort(pChild, TRUE);
        }
    }
}
//---------------------------------------------------------------------------
POSITION PSS_GridCtrl::GetHeadPosition(IItem* pItem) const
{
    return pItem->m_ListChild.GetHeadPosition();
}
//---------------------------------------------------------------------------
POSITION PSS_GridCtrl::GetTailPosition(IItem *pItem) const
{
    return pItem->m_ListChild.GetTailPosition();
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem* PSS_GridCtrl::GetPrevChild(IItem *pItem, POSITION& pPos) const
{
    return (IItem*)pItem->m_ListChild.GetPrev(pPos);
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem* PSS_GridCtrl::GetNextChild(IItem* pItem, POSITION& pPos) const
{
    return (IItem*)pItem->m_ListChild.GetNext(pPos);
}
//---------------------------------------------------------------------------
POSITION PSS_GridCtrl::GetRootHeadPosition() const
{
    return m_RootItems.GetHeadPosition();
}
//---------------------------------------------------------------------------
POSITION PSS_GridCtrl::GetRootTailPosition() const
{
    return m_RootItems.GetTailPosition();
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem* PSS_GridCtrl::GetPrevRoot(POSITION& pPos) const
{
    return (IItem*)m_RootItems.GetNext(pPos);
}
//---------------------------------------------------------------------------
PSS_GridCtrl::IItem* PSS_GridCtrl::GetNextRoot(POSITION& pPos) const
{
    return (IItem*)m_RootItems.GetNext(pPos);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::AddTail(IItem* pParent, IItem* pChild)
{
    pParent->m_ListChild.AddTail(pChild);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::InvalidateItemRect(int item)
{
    if (item != -1)
    {
        CRect rc;
        GetItemRect(item, rc, LVIR_BOUNDS);
        InvalidateRect(rc);
        UpdateWindow();
    }
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::InvalidateItemRect(IItem* pItem)
{
    if (!pItem)
        return;

    const int item = GetCurIndex(pItem);

    if (item != -1)
        InvalidateItemRect(item);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::InvalidateItem(IItem* pItem)
{
    if (!pItem)
        return;

    const int item = GetCurIndex(pItem);

    // should be visible
    if (item == -1)
        return;

    IItemInfo* pItemInfo = GetData(pItem);
    const int  size      = pItemInfo->GetItemCount();

    SetRedraw(false);
    SetItemText(item, 0, pItemInfo->GetItemText());

    for (int i = 0; i < size; ++i)
    {
        CString str = pItemInfo->GetSubItem(i);
        SetItemText(item, i + 1, str.GetBuffer(1));
    }

    SetRedraw(true);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnUpdateListViewItem(IItem* pItem, LV_ITEM* pLvItem)
{
    if (!pItem)
        return;
    
    if (!pLvItem)
        return;

    // default implementation you would go for this 9 out of 10 times
    IItemInfo*    pItemInfo = GetData(pItem);
    const CString str       = (CString)pLvItem->pszText;

    if (pItemInfo)
    {
        if (!pLvItem->iSubItem)
            pItemInfo->SetItemText(str);
        else
            // sub-item data
            pItemInfo->SetSubItemText(pLvItem->iSubItem - 1, str);

        // do not use updateRow here, hence a specific item or sub-item, not all items, should be updated
        UpdateData(pItem, pItemInfo);
    }

    SetItemText(pLvItem->iItem, pLvItem->iSubItem, pLvItem->pszText);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnControlLButtonDown(UINT flags, const CPoint& point, LVHITTESTINFO& hitTest)
{
    // call the derived class to advise the start edit
    OnBeginLabelEdit(hitTest.iItem, hitTest.iSubItem);

    if (!hitTest.iSubItem)
    {
        CRect rcItem;
        GetItemRect(hitTest.iItem, rcItem, LVIR_LABEL);

        const DWORD style = WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT;

        std::unique_ptr<CEdit> pEdit(new PSS_ListViewEdit(hitTest.iItem,
                                                          hitTest.iSubItem,
                                                          GetItemText(hitTest.iItem, hitTest.iSubItem)));
        pEdit->Create(style, rcItem, this, 0x1233);
        pEdit.release();
        return;
    }

    EditLabelEx(hitTest.iItem, hitTest.iSubItem);
}
//---------------------------------------------------------------------------
CImageList* PSS_GridCtrl::CreateDragImageEx(int index)
{
    std::unique_ptr<CImageList> pList(new CImageList());

    // get image index
    LV_ITEM lvItem;
    lvItem.mask     = LVIF_IMAGE;
    lvItem.iItem    = index;
    lvItem.iSubItem = 0;
    GetItem(&lvItem);

    CRect rc;
    GetItemRect(index, &rc, LVIR_BOUNDS);

    const CString str   = GetItemText(index, 0);
    CFont*        pFont = GetFont();

    rc.OffsetRect(-rc.left, -rc.top);
    rc.right = GetColumnWidth(0);

    pList->Create(rc.Width(), rc.Height(), ILC_COLOR24 | ILC_MASK, 1, 1);
    CDC* pDC = GetDC();

    if (pDC)
    {
        CDC dc;
        dc.CreateCompatibleDC(pDC);

        CBitmap bmp;
        bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());

        CBitmap* pOldBmp  = dc.SelectObject(&bmp);
        CFont*   pOldFont = dc.SelectObject(pFont);

        dc.FillSolidRect(rc, GetSysColor(COLOR_WINDOW));

        CImageList* pImgList = GetImageList(LVSIL_SMALL);

        if (pImgList)
            pImgList->Draw(&dc, lvItem.iImage, CPoint(0, 0), ILD_TRANSPARENT);

        dc.TextOut(m_CxImage + 4, 0, str);
        dc.SelectObject(pOldFont);
        dc.SelectObject(pOldBmp);

        // cause an error if the 1st column is hidden, so must check the image list
        if (pList->m_hImageList)
            pList->Add(&bmp, RGB(255, 255, 255));
        else
            pList.reset();

        ReleaseDC(pDC);
    }

    if (pList.get())
        return pList.release();

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::OnItemExpanding(IItem* pItem, int index)
{
    return 1;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::OnItemExpanded(IItem* pItem, int index)
{
    return 1;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::OnItemCollapsing(IItem* pItem)
{
    return 1;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::OnItemCollapsed(IItem* pItem)
{
    return 1;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::OnDeleteItem(IItem* pItem, int index)
{
    return 1;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::OnVKAdd(IItem* pItem, int index)
{
    return 1;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::OnVkSubtract(IItem* pItem, int index)
{
    return 1;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::OnVKMultiply(IItem* pItem, int index)
{
    return 1;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::OnVkReturn()
{
    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::OnItemLButtonDown(LVHITTESTINFO& hitTest)
{
    return 1;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnBeginLabelEdit(int item, int subItem)
{}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnEndLabelEdit(LPCSTR pText, int item, int subItem)
{}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
        if (GetFocus() == this)
            switch (pMsg->wParam)
            {
                case VK_LEFT:
                    // decrement the order number
                    --m_CurSubItem;

                    if (m_CurSubItem < 0)
                        m_CurSubItem = 0;
                    else
                    {
                        CHeaderCtrl* pHeader = GetHeaderCtrl();

                        // make the column visible, take into account that the header may be reordered
                        MakeColumnVisible(Header_OrderToIndex(pHeader->m_hWnd, m_CurSubItem));

                        // invalidate the item
                        const int item = GetSelectedItem();

                        if (item != -1)
                            InvalidateItemRect(item);
                    }

                    return TRUE;

                case VK_RIGHT:
                {
                    // increment the order number
                    ++m_CurSubItem;

                    CHeaderCtrl* pHeader = GetHeaderCtrl();
                    const int    columnCount = pHeader->GetItemCount();

                    // don't go beyond the last column
                    if (m_CurSubItem > columnCount - 1)
                        m_CurSubItem = columnCount - 1;
                    else
                    {
                        MakeColumnVisible(Header_OrderToIndex(pHeader->m_hWnd, m_CurSubItem));

                        const int item = GetSelectedItem();

                        // invalidate the item
                        if (item != -1)
                            InvalidateItemRect(item);
                    }

                    return TRUE;
                }

                case VK_RETURN:
                case VK_F2:
                    // edit item data
                    if (!OnVkReturn())
                    {
                        const int item = GetSelectedItem();

                        if (m_CurSubItem != -1 && item != -1)
                        {
                            CHeaderCtrl* pHeader = GetHeaderCtrl();
                            const int    subItem = Header_OrderToIndex(pHeader->m_hWnd, m_CurSubItem);

                            // call the derived class to notify the start edit
                            OnBeginLabelEdit(item, subItem);

                            // all nodes in col 0 are edit controls, they may be modifed
                            if (!subItem)
                            {
                                CRect rcItem;
                                GetItemRect(item, rcItem, LVIR_LABEL);

                                const DWORD style = WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT;

                                std::unique_ptr<CEdit> pEdit(new PSS_ListViewEdit(item, subItem, GetItemText(item, subItem)));
                                pEdit->Create(style, rcItem, this, 0x1233);
                                pEdit.release();
                            }
                            else
                                EditLabelEx(item, subItem);

                            return 1;
                        }
                    }

                    break;

                default:
                    break;
            }

    return CListCtrl::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= LVS_REPORT | LVS_SINGLESEL | LVS_SHAREIMAGELISTS | LVS_OWNERDRAWFIXED | LVS_SHOWSELALWAYS;
    return CListCtrl::PreCreateWindow(cs);
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CListCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
    if (GetFocus() != this)
        SetFocus();

    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    LVHITTESTINFO hitTest;
    hitTest.pt = pNMListView->ptAction;
    SubItemHitTest(&hitTest);

    if (OnItemLButtonDown(hitTest))
    {
        const BOOL select = HitTestOnSign(pNMListView->ptAction, hitTest);

        // normal selection
        if (select && hitTest.iItem != -1)
        {
            const int index = GetSelectedItem();

            if (index != -1)
            {
                IItem* pSelItem = GetTreeItem(index);

                if (pSelItem)
                {
                    BOOL redraw = 0;

                    if (ItemHasChildren(pSelItem))
                    {
                        int scrollIndex = 0;

                        SetRedraw(FALSE);

                        try
                        {
                            if (IsCollapsed(pSelItem))
                            {
                                if (OnItemExpanding(pSelItem, index))
                                {
                                    scrollIndex = Expand(pSelItem, index);
                                    OnItemExpanded(pSelItem, index);
                                    redraw = 1;
                                }
                            }
                            else
                            if (OnItemCollapsing(pSelItem))
                            {
                                Collapse(pSelItem);
                                OnItemCollapsed(pSelItem);
                                redraw = 1;
                            }
                        }
                        catch (...)
                        {
                            SetRedraw(TRUE);
                            throw;
                        }

                        SetRedraw(TRUE);

                        if (redraw)
                        {
                            InvalidateItemRect(index);
                            EnsureVisible(scrollIndex, 1);
                        }
                    }
                }
            }
        }
    }

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_DISPINFO* plvDispInfo = (LV_DISPINFO*)pNMHDR;
    LV_ITEM*     plvItem     = &plvDispInfo->item;

    // valid text
    if (plvItem->pszText)
    {
        // valid item
        if (plvItem->iItem != -1)
        {
            IItem* pSelItem = GetTreeItem(plvItem->iItem);

            if (pSelItem)
                OnUpdateListViewItem(pSelItem, plvItem);
        }

        OnEndLabelEdit(plvItem->pszText, plvItem->iItem, plvItem->iSubItem);
    }

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if (GetFocus() != this)
        SetFocus();

    CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if (GetFocus() != this)
        SetFocus();

    CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (GetFocus() != this)
        SetFocus();

    LVHITTESTINFO hitTest;
    hitTest.pt = point;
    SubItemHitTest(&hitTest);

    if (!OnItemLButtonDown(hitTest))
        return;

    const BOOL selected = HitTestOnSign(point, hitTest);

    if (selected && hitTest.iItem != -1)
    {
        m_CurSubItem         = IndexToOrder(hitTest.iSubItem);
        CHeaderCtrl* pHeader = GetHeaderCtrl();

        // make the column fully visible
        MakeColumnVisible(Header_OrderToIndex(pHeader->m_hWnd, m_CurSubItem));
        CListCtrl::OnLButtonDown(nFlags, point);
        OnControlLButtonDown(nFlags, point, hitTest);

        // update row anyway for selection bar
        InvalidateItemRect(hitTest.iItem);
    }
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_IsDragging)
    {
        KillTimer(M_Timer_ID);

        if (CWnd::GetCapture() != this)
            m_IsDragging = 0;

        if (nFlags == MK_RBUTTON || nFlags == MK_MBUTTON)
            m_IsDragging = 0;

        if (::GetKeyState(VK_ESCAPE) < 0)
            m_IsDragging = 0;

        // todo -cFeature -oJean: why not put this in a funtion :)
        if (!m_IsDragging)
        {
            SetItemState(m_DragTarget, 0, LVIS_DROPHILITED);
            CImageList::DragLeave(this);
            CImageList::EndDrag();
            ReleaseCapture();
            InvalidateRect(NULL);
            UpdateWindow();
        }
        else
        {
            CPoint ptList(point);
            MapWindowPoints(this, &ptList, 1);
            CImageList::DragMove(ptList);
            UINT hitTest = LVHT_ONITEM;
            m_DragTarget = HitTest(ptList, &hitTest);

            // turn off highlight for previous DROPHILITED state
            const int prev = GetNextItem(-1, LVNI_DROPHILITED);

            // Prevents flicker
            if (prev != m_DragTarget)
                SetItemState(prev, 0, LVIS_DROPHILITED);

            CRect rect;
            GetClientRect(rect);

            if (m_DragTarget != -1)
            {
                SetItemState(m_DragTarget, LVIS_DROPHILITED, LVIS_DROPHILITED);
                IItem*    pTarget = GetTreeItem(m_DragTarget);
                const int cy      = rect.Height();

                if ((point.y >= 0              && point.y <= m_CyImage) ||
                    (point.y >= cy - m_CyImage && point.y <= cy)        ||
                    (pTarget && ItemHasChildren(pTarget) && IsCollapsed(pTarget)))
                    SetTimer(M_Timer_ID, 300, NULL);
            }
        }
    }

    CListCtrl::OnMouseMove(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnTimer(UINT nIDEvent)
{
    CListCtrl::OnTimer(nIDEvent);

    if (nIDEvent != M_Timer_ID)
        return;

    if (CWnd::GetCapture() != this)
    {
        SetItemState(m_DragTarget, 0, LVIS_DROPHILITED);
        m_IsDragging = 0;
        CImageList::DragLeave(this);
        CImageList::EndDrag();
        ReleaseCapture();
        InvalidateRect(NULL);
        UpdateWindow();
        KillTimer(M_Timer_ID);
        return;
    }

    // reset timer
    SetTimer(M_Timer_ID, 300, NULL);

    DWORD  pos = ::GetMessagePos();
    CPoint ptList(LOWORD(pos), HIWORD(pos));
    ScreenToClient(&ptList);

    CRect rect;
    GetClientRect(rect);

    const int n  = GetTopIndex();
    const int cy = rect.Height();

    // perform autoscroll if the cursor is near the top or bottom.
    if (ptList.y >= 0 && ptList.y <= m_CyImage)
    {
        CImageList::DragShowNolock(0);
        SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEUP, 0), NULL);
        CImageList::DragShowNolock(1);

        if (GetTopIndex() == n)
            KillTimer(M_Timer_ID);
        else
        {
            CImageList::DragShowNolock(0);
            CImageList::DragMove(ptList);
            CImageList::DragShowNolock(1);

            return;
        }
    }
    else
    if (ptList.y >= cy - m_CyImage && ptList.y <= cy)
    {
        CImageList::DragShowNolock(0);
        SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, 0), NULL);
        CImageList::DragShowNolock(1);

        if (GetTopIndex() == n)
            KillTimer(M_Timer_ID);
        else
        {
            CImageList::DragShowNolock(0);
            CImageList::DragMove(ptList);
            CImageList::DragShowNolock(1);

            return;
        }
    }

    // hover test
    CImageList::DragMove(ptList);
    UINT hitTest = LVHT_ONITEM;
    m_DragTarget = HitTest(ptList, &hitTest);

    if (m_DragTarget != -1)
    {
        // if the target has children expand them
        IItem* pTarget = GetTreeItem(m_DragTarget);

        if (pTarget != NULL && ItemHasChildren(pTarget) && IsCollapsed(pTarget) && (m_DragItem != -1))
        {
            CImageList::DragShowNolock(0);
            IItem* pSource = GetTreeItem(m_DragItem);

            int scrollIndex = 0;

            SetRedraw(FALSE);

            try
            {
                if (ItemHasChildren(pTarget) && IsCollapsed(pTarget))
                    if (OnItemExpanding(pTarget, m_DragTarget))
                    {
                        scrollIndex = Expand(pTarget, m_DragTarget);
                        OnItemExpanded(pTarget, m_DragTarget);
                    }

                m_DragItem = NodeToIndex(pSource);
            }
            catch (...)
            {
                SetRedraw(TRUE);
                throw;
            }

            SetRedraw(TRUE);

            EnsureVisible(scrollIndex, 1);
            InvalidateRect(NULL);
            UpdateWindow();
            CImageList::DragShowNolock(1);
            KillTimer(M_Timer_ID);
            return;
        }
    }

    KillTimer(M_Timer_ID);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_IsDragging)
    {
        KillTimer(M_Timer_ID);
        CImageList::DragLeave(this);
        CImageList::EndDrag();
        ReleaseCapture();
        m_IsDragging = FALSE;
        SetItemState(m_DragTarget, 0, LVIS_DROPHILITED);

        // don't drop on itself
        if ((m_DragTarget != -1) && (m_DragTarget != m_DragItem) && (m_DragItem != -1))
        {
            IItem* pSource = GetTreeItem(m_DragItem);
            IItem* pTarget = GetTreeItem(m_DragTarget);

            if (IsRoot(pSource))
                return;

            IItem* pParent = GetParentItem(pSource);

            // can't drag child to parent
            if (pParent == pTarget)
                return;

            // can't drag parent to child
            if (!IsChildOf(pSource, pTarget))
            {
                CWaitCursor wait;
                SetRedraw(FALSE);

                try
                {
                    if (DoDragDrop(pTarget, pSource))
                    {
                        const UINT flags = LVIS_SELECTED | LVIS_FOCUSED;
                        SetItemState(m_DragTarget, flags, flags);
                        m_DragItem = -1;

                        // delete source
                        const int index = NodeToIndex(pSource);
                        DeleteItem(index);
                        HideChildren(pSource, TRUE, index);
                        Delete(pSource);
                        InternalUpdateTree();
                        SetRedraw(TRUE);
                        InvalidateRect(NULL);
                        UpdateWindow();
                    }
                    else
                        SetRedraw(TRUE);
                }
                catch (...)
                {
                    SetRedraw(TRUE);
                    throw;
                }
            }
        }

        return;
    }

    CListCtrl::OnLButtonUp(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

    switch (pLVKeyDow->wVKey)
    {
        case VK_SPACE:
            if (GetExtendedStyle() & LVS_EX_CHECKBOXES)
            {
                const int index = GetSelectedItem();

                if (index != -1)
                {
                    IItem* pItem = GetTreeItem(index);

                    if (pItem)
                    {
                        IItemInfo* pInfo = GetData(pItem);
                        pInfo->SetCheck(!pInfo->GetCheck());
                    }
                }
            }

            break;

        case VK_DELETE:
        {
            const int item = GetSelectedItem();

            if (item != -1)
            {
                IItem* pSelItem = GetTreeItem(item);

                if (pSelItem)
                    if (OnDeleteItem(pSelItem, item))
                        DeleteItemEx(pSelItem, item);
            }

            break;
        }

        case VK_MULTIPLY:
        {
            const int index = GetSelectedItem();

            if (index != -1)
            {
                CWaitCursor wait;
                int         scroll = 0;

                SetRedraw(FALSE);

                try
                {
                    IItem* pParent = GetTreeItem(index);

                    if (OnVKMultiply(pParent, index))
                        ExpandAll(pParent, scroll);
                }
                catch (...)
                {
                    SetRedraw(TRUE);
                    throw;
                }

                SetRedraw(TRUE);
                RedrawItems(index, scroll);
                EnsureVisible(scroll, TRUE);
            }

            break;
        }

        case VK_ADD:
        {
            const int index = GetSelectedItem();

            if (index != -1)
            {
                CWaitCursor wait;
                IItem*      pSelItem    = GetTreeItem(index);
                int         scrollIndex = 0;

                if (OnVKAdd(pSelItem, index))
                    scrollIndex = Expand(pSelItem, index);

                InvalidateItemRect(index);
                EnsureVisible(scrollIndex, 1);
            }

            break;
        }

        case VK_SUBTRACT:
        {
            const int index = GetSelectedItem();

            if (index != -1)
            {
                CWaitCursor wait;
                IItem*      pSelItem = GetTreeItem(index);

                if (OnVkSubtract(pSelItem, index))
                    Collapse(pSelItem);

                InvalidateItemRect(index);
            }

            break;
        }

        default:
            break;
    }

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    if (pNMListView->iItem != -1)
    {
        m_DragItem = pNMListView->iItem;

        // override this if another drag image is wanted, or none at all
        std::unique_ptr<CImageList> pDragImage(CreateDragImageEx(m_DragItem));

        if (pDragImage.get())
        {
            pDragImage->BeginDrag(0, CPoint(0, 0));
            pDragImage->DragEnter(this, pNMListView->ptAction);
            SetCapture();
            m_IsDragging = TRUE;
        }
    }

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    // this piece of code is borrowed from the wndproc.c file in the odlistvw.exe example from MSDN
    // and was converted to mfc style
    if (lpMeasureItemStruct->CtlType != ODT_LISTVIEW)
        return;

    CClientDC dc(this);
    CFont*    pFont    = GetFont();
    CFont*    pOldFont = dc.SelectObject(pFont);

    TEXTMETRIC tm;
    dc.GetTextMetrics(&tm);

    lpMeasureItemStruct->itemHeight = tm.tmHeight + tm.tmExternalLeading + 4;
    dc.SelectObject(pOldFont);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    if (lpDrawItemStruct->CtlType != ODT_LISTVIEW)
        return;

    if (lpDrawItemStruct->itemAction == ODA_DRAWENTIRE)
    {
        if (!m_hImageList)
            m_hImageList = (HIMAGELIST)::SendMessage(m_hWnd, LVM_GETIMAGELIST, WPARAM(int(LVSIL_SMALL)), 0L);

        static _TCHAR buffer[MAX_PATH];
        const int     item = lpDrawItemStruct->itemID;
        CRect         itemRect(lpDrawItemStruct->rcItem);

        LV_ITEM lvi;
        lvi.mask       = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_INDENT | LVIF_PARAM;
        lvi.iItem      = item;
        lvi.iSubItem   = 0;
        lvi.pszText    = buffer;
        lvi.cchTextMax = sizeof(buffer);
        lvi.stateMask  = 0xFFFF;
        GetItem(&lvi);

        IItem* pSelItem = (IItem*)lpDrawItemStruct->itemData;

        CRect labelRect;
        GetItemRect(item, labelRect, LVIR_LABEL);

        CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        ASSERT(pDC);

        CRect clipboxRect;
        pDC->GetClipBox(clipboxRect);

        COLORREF bgColor, textColor;

        if (lpDrawItemStruct->itemState & ODS_SELECTED)
        {
            // set the text background and foreground colors
            bgColor   = ::GetSysColor(COLOR_HIGHLIGHT);
            textColor = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
        }
        else
        {
            // set the text background and foreground colors to the standard window colors
            bgColor   = ::GetSysColor(COLOR_WINDOW);
            textColor = ::GetSysColor(COLOR_WINDOWTEXT);
        }

        // get current Icon, you have overridden this I hope :-)
        const int image = GetIcon(pSelItem);

        if (image != -1)
            if (lvi.iImage != image)
            {
                LV_ITEM lvItem;
                lvItem.mask     = LVIF_IMAGE;
                lvItem.iImage   = image;
                lvItem.iItem    = item;
                lvItem.iSubItem = 0;
                SetItem(&lvItem);

                lvi.iImage = image;
            }

        CRect rect;
        GetItemRect(item, rect, LVIR_BOUNDS);

        CRect iconRect;
        GetItemRect(item, iconRect, LVIR_ICON);

        int offset;
        int width;
        int y;

        // draw Current image
        if (m_hImageList == NULL)
        {
            width  = 0;
            offset = itemRect.Height() / 2;
            y      = itemRect.bottom   - offset;
        }
        else
        {
            width  = m_CxImage;
            offset = (itemRect.Height() - m_CyImage) / 2;
            y      =  itemRect.bottom   - m_CyImage  - offset;
        }

        // do not draw icon outside the 1st column
        const int indent = GetIndent(pSelItem) * m_CxImage + m_CxImage;

        if (rect.left + indent > GetColumnWidth(0) - 2)
            width = (rect.left + indent) - GetColumnWidth(0);

        UINT flags = ILD_TRANSPARENT;

        // if dragging, show a SelectDropTarget alike effect :)
        if (GetItemState(item, LVIF_STATE) & LVIS_DROPHILITED)
            flags |= ILD_BLEND50;

        // calculate icon width
        if ((width = m_CxImage - width) > -1)
        {
            if (m_hImageList)
            {
                ImageList_DrawEx(m_hImageList,
                                 lvi.iImage,
                                 pDC->m_hDC,
                                 rect.left + (GetIndent(pSelItem) * m_CxImage),
                                 y,
                                 width,
                                 m_CyImage,
                                 CLR_DEFAULT,
                                 CLR_DEFAULT,
                                 flags);
            }

            DrawTreeItem(pDC, pSelItem, item, rect);
        }

        // draw selection bar (also erase old selection)
        pDC->SetBkColor(bgColor);

        CRect clipRect  = lpDrawItemStruct->rcItem;
        clipRect.left  += GetIndent(pSelItem) * m_CxImage + m_CxImage + 2;

        if (clipRect.left > GetColumnWidth(0))
            clipRect.left = GetColumnWidth(0);

        // fill background color
        ::ExtTextOut(pDC->GetSafeHdc(), 0, 0, ETO_OPAQUE, clipRect, NULL, 0, NULL);

        // draw color in first column if any
        clipRect.right           = labelRect.right;
        IItemInfo*     pItemInfo = GetData(pSelItem);
        const COLORREF color     = pItemInfo->GetBkColor();

        if (color != -1)
        {
            CBrush brush(color);
            pDC->FillRect(clipRect, &brush);
        }

        // draw selection rect in 1st column if selected
        if ((lpDrawItemStruct->itemState & ODS_SELECTED) && (m_CurSubItem == 0))
        {
            CBrush brush(GetCellRGB());
            pDC->FillRect(clipRect, &brush);
            pDC->DrawFocusRect(clipRect);
        }

        // if checkbox style
        const UINT stateImageMask = lvi.state & LVIS_STATEIMAGEMASK;

        if (stateImageMask)
        {
            const int   imageMask = (stateImageMask >> 12) - 1;
            CImageList* pImageList = GetImageList(LVSIL_STATE);

            if (pImageList)
            {
                int cxIcon = 0;
                int cyIcon = 0;
                ImageList_GetIconSize(pImageList->m_hImageList, &cxIcon, &cyIcon);

                if (rect.left + (GetIndent(pSelItem) * m_CxImage) + m_CxImage + cxIcon < GetColumnWidth(0))
                    pImageList->Draw(pDC,
                                     imageMask,
                                     CPoint(rect.left + (GetIndent(pSelItem) * m_CxImage) + cxIcon, y),
                                     ILD_TRANSPARENT);
            }
        }

        // that's new
        CString strItemText = GetData(pSelItem)->GetItemText();

        // draw first item
        GetItemRect(item, itemRect, LVIR_LABEL);

        labelRect        = itemRect;
        labelRect.left  += M_Offset_First;
        labelRect.right -= M_Offset_First;

        pDC->SetBkColor(bgColor);
        pDC->SetTextColor(textColor);

        LPCTSTR pText = MakeShortString(pDC, strItemText.GetBuffer(1), itemRect.right - itemRect.left, M_Offset_First);

        pDC->DrawText(pText, -1, labelRect, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER | DT_EXTERNALLEADING);

        LV_COLUMN lvc;
        lvc.mask = LVCF_FMT | LVCF_WIDTH;

        // draw sub-items
        for (int column = 1; GetColumn(column, &lvc); ++column)
        {
            int subItemWidth = 0;

            itemRect.left   = itemRect.right;
            itemRect.right += lvc.cx;

            if (itemRect.left < clipboxRect.right && itemRect.right > clipboxRect.left && itemRect.right > itemRect.left)
            {
                // support for colors in each cell
                const COLORREF subItemColor = pItemInfo->GetBkColor(column - 1);

                if (subItemColor != -1)
                {
                    CBrush brush(subItemColor);
                    pDC->FillRect(itemRect, &brush);
                }

                // check for sub-items who has an image associated
                const int subImage = pItemInfo->GetSubItemImage(column - 1);

                if (subImage != -1)
                {
                    // m_CxImage is actually the width of the "tree" image list, not the sub-item image list.
                    // Remember that when the bitmap is created, because the sub-item icon size isn't get instead
                    subItemWidth = m_CxImage;

                    CRect subItemRect;
                    GetSubItemRect(item, column, LVIR_BOUNDS, subItemRect);

                    HIMAGELIST hImageList = m_SubItemImages.GetSafeHandle();

                    ImageList_DrawEx(m_hImageList,
                                     subImage,
                                     pDC->m_hDC,
                                     subItemRect.left,
                                     y,
                                     subItemWidth,
                                     m_CyImage,
                                     CLR_DEFAULT,
                                     CLR_DEFAULT,
                                     flags);

                    subItemWidth += 2;
                }

                CString str = GetData(pSelItem)->GetSubItem(column - 1);
                pText       = MakeShortString(pDC, str.GetBuffer(1), (itemRect.right - itemRect.left) - subItemWidth, M_Offset_Other);

                UINT justify = DT_LEFT;

                if (pText == str.GetBuffer(1))
                    switch (lvc.fmt & LVCFMT_JUSTIFYMASK)
                    {
                        case LVCFMT_RIGHT:  justify = DT_RIGHT;  break;
                        case LVCFMT_CENTER: justify = DT_CENTER; break;
                        default:                                 break;
                    }

                labelRect        = itemRect;
                labelRect.left  += M_Offset_Other + subItemWidth;
                labelRect.right -= M_Offset_Other;

                if (lpDrawItemStruct->itemState & ODS_SELECTED && !m_IsDragging)
                    DrawFocusCell(pDC, lpDrawItemStruct->itemID, column, subItemWidth);

                if (pText)
                    pDC->DrawText(pText, -1, labelRect, justify | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER | DT_EXTERNALLEADING);
            }

            // draw combobox down arrow regardless of clipboxRect region
            if (lpDrawItemStruct->itemState & ODS_SELECTED)
                DrawComboBox(pDC, pSelItem, item, column, subItemWidth);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::OnSysColorChange()
{
    CListCtrl::OnSysColorChange();
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::GetRootIndex(IItem* pRoot)
{
    int      index = 0;
    POSITION pPos  = m_RootItems.GetHeadPosition();

    while (pPos)
    {
        IItem* pItem = (IItem*)m_RootItems.GetNext(pPos);

        if (pItem == pRoot)
            return index;

        ++index;
    }

    return -1;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::Delete(IItem* pNode, BOOL clean)
{
    POSITION pPos = m_RootItems.GetHeadPosition();

    while (pPos)
    {
        IItem* pRoot = (IItem*)m_RootItems.GetNext(pPos);

        if (Delete(pRoot, pNode, clean))
            return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::CopyChildren(IItem* pDest, IItem* pSrc)
{
    if (ItemHasChildren(pSrc))
    {
        POSITION pPos = pSrc->m_ListChild.GetHeadPosition();

        while (pPos)
        {
            IItem*     pItem     = (IItem*)pSrc->m_ListChild.GetNext(pPos);
            IItemInfo* pItemInfo = CopyData(GetData(pItem));
            IItem*     pNewItem  = InsertItem(pDest, pItemInfo);

            CopyChildren(pNewItem, pItem);
        }
    }
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::DoDragDrop(IItem* pTarget, IItem* pSource)
{
    if (!pTarget)
        return 0;

    BOOL update = FALSE;

    if (!IsCollapsed(pTarget))
        // children are expanded, want to see update right away
        update = TRUE;

    // make a copy of the source data
    IItemInfo* pItemInfo = CopyData(GetData(pSource));

    // create new node with the source data and make pTarget the parent
    IItem* pNewParent = InsertItem(pTarget, pItemInfo, update);

    // if the source has children, copy all source data and make the newly created item the parent
    if (ItemHasChildren(pSource))
        CopyChildren(pNewParent, pSource);

    return 1;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::InternalUpdateTree()
{
    const int items = GetItemCount();

    for (int item = 0; item < items; ++item)
    {
        IItem* pItem = GetTreeItem(item);
        SetCurIndex(pItem, item);
    }
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::NodeToIndex(IItem *pNode)
{
    int      startIndex = 0;
    POSITION pPos       = m_RootItems.GetHeadPosition();

    while (pPos)
    {
        IItem* pRoot = (IItem*)m_RootItems.GetNext(pPos);
        int    ret   = NodeToIndex(pRoot, pNode, startIndex);

        if (ret != -1)
            return ret;
    }

    return -1;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::HitTestOnSign(const CPoint& point, LVHITTESTINFO& hitTest)
{
    hitTest.pt = point;

    // check which subitem was clicked
    SubItemHitTest(&hitTest);

    if (hitTest.iItem != -1)
    {
        // first hit test on checkbox
        BOOL hit = FALSE;

        if (GetExtendedStyle() & LVS_EX_CHECKBOXES)
        {
            // isn't this always owner draw fixed :-)
            if (hitTest.flags == LVHT_ONITEM && (GetStyle() & LVS_OWNERDRAWFIXED))
            {
                CRect iconRect, labelRect;

                // has to be between these two ....right :)
                GetItemRect(hitTest.iItem, iconRect,  LVIR_ICON);
                GetItemRect(hitTest.iItem, labelRect, LVIR_LABEL);

                // check if hit was on a state icon
                if (point.x > iconRect.left && point.x < labelRect.left)
                    hit = TRUE;
            }
            else
            if (hitTest.flags & LVHT_ONITEMSTATEICON)
                hit = TRUE;
        }

        IItem* pItem = GetTreeItem(hitTest.iItem);

        if (pItem)
        {
            // if checkbox
            if (hit)
            {
                // normally sets of check states should be maintained, one for listview state mask
                // and one for IItem, but it's located here, so no harm done
                SetCheck(hitTest.iItem, !GetCheck(hitTest.iItem));
                IItemInfo* pInfo = GetData(pItem);
                pInfo->SetCheck(!pInfo->GetCheck());
            }

            // if has children and clicked on [+] or [-] then expand/collapse
            if (ItemHasChildren(pItem))
            {
                // hit test on the plus/sign "button" 
                CRect rcBounds;
                GetItemRect(hitTest.iItem, rcBounds, LVIR_BOUNDS);

                IRectangle rect(this, NULL, GetIndent(pItem), rcBounds);

                // if OnItemExpanding() or OnItemCollapsing() returns false, don't redraw
                BOOL redraw = 0;

                if (rect.HitTest(point))
                {
                    int scrollIndex = GetCurIndex(pItem);

                    SetRedraw(FALSE);

                    try
                    {
                        if (IsCollapsed(pItem))
                        {
                            if (OnItemExpanding(pItem, hitTest.iItem))
                            {
                                scrollIndex = Expand(pItem, hitTest.iItem);
                                OnItemExpanded(pItem, hitTest.iItem);
                                redraw = 1;
                            }
                        }
                        else
                        if (OnItemCollapsing(pItem))
                        {
                            Collapse(pItem);
                            OnItemCollapsed(pItem);
                            redraw = 1;
                        }
                    }
                    catch (...)
                    {
                        SetRedraw(TRUE);
                        throw;
                    }

                    SetRedraw(TRUE);

                    if (redraw)
                    {
                        InvalidateItemRect(hitTest.iItem);
                        EnsureVisible(scrollIndex, 1);

                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}
//---------------------------------------------------------------------------
CEdit* PSS_GridCtrl::EditLabelEx(int item, int col)
{
    CRect rect;
    int   offset = 0;

    if (!EnsureVisible(item, TRUE))
        return NULL;

    GetSubItemRect(item, col, LVIR_BOUNDS, rect);

    // now scroll if we need to expose the column
    CRect clientRect;
    GetClientRect(clientRect);

    if (offset + rect.left < 0 || offset + rect.left > clientRect.right)
    {
        CSize size(offset + rect.left, 0);
        Scroll(size);
        rect.left -= size.cx;
    }

    rect.left  += offset;
    rect.right  = rect.left + GetColumnWidth(col);

    if (rect.right > clientRect.right)
        rect.right = clientRect.right;

    // get column alignment
    LV_COLUMN lvcol;
    lvcol.mask = LVCF_FMT;
    GetColumn(col, &lvcol);

    DWORD style;

    if ((lvcol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
        style = ES_LEFT;
    else
    if ((lvcol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
        style = ES_RIGHT;
    else
        style = ES_CENTER;

    IItem* pItem = GetTreeItem(item);

    if (pItem)
    {
        IItemInfo* pInfo = GetData(pItem);

        if (pInfo)
        {
            const int subImage = pInfo->GetSubItemImage(col - 1);

            if (subImage != -1)
            {
                // m_CxImage is actually the width of the "tree" image list, not the sub-item image list.
                // Remember that the bitmap is created, because the sub-item icon image list size will not
                // be get
                rect.left += m_CxImage;
            }
        }
    }

    style |= WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;
    std::unique_ptr<CEdit> pEdit(new PSS_ListViewEdit(item, col, GetItemText(item, col)));
    pEdit->Create(style, rect, this, IDC_EDITCTRL);

    return pEdit.release();
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::IndexToOrder(int index)
{
    CHeaderCtrl* pHeader     = GetHeaderCtrl();
    int          colCount    = pHeader->GetItemCount();
    int*         pOrderarray = new int[colCount];

    try
    {
        // this translates a column index value to a column order value
        Header_GetOrderArray(pHeader->m_hWnd, colCount, pOrderarray);

        for (int i = 0; i < colCount; ++i)
            if (pOrderarray[i] == index)
            {
                delete[] pOrderarray;
                return i;
            }
    }
    catch (...)
    {
        delete[] pOrderarray;
        throw;
    }

    delete[] pOrderarray;

    return -1;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::Hide(IItem* pItem, BOOL flag)
{
    pItem->m_HideChildren = flag;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::SetSubItemImageList(CImageList* pImageList)
{
    if (pImageList)
    {
        m_SubItemImages.Create(pImageList);

        const int count = pImageList->GetImageCount();

        for (int i = 0; i < count; ++i)
            m_SubItemImages.Copy(i, pImageList, i);

        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::Delete(IItem* pStartAt, IItem* pNode, BOOL clean)
{
    POSITION pPos = pStartAt->m_ListChild.GetHeadPosition();

    while (pPos)
    {
        POSITION pPosPrev = pPos;
        IItem*   pChild   = (IItem*)pStartAt->m_ListChild.GetNext(pPos);

        if (pChild == pNode)
        {
            pStartAt->m_ListChild.RemoveAt(pPosPrev);

            if (clean)
            {
                PSS_GridCtrl::IItemInfo* pData = GetData(pNode);

                if (pData)
                    delete pData;

                delete pNode;
            }

            return TRUE;
        }

        if (Delete(pChild, pNode))
            return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
UINT PSS_GridCtrl::GetCount(IItem* pItem, UINT& count) const
{
    POSITION pPos = pItem->m_ListChild.GetHeadPosition();

    while (pPos)
    {
        IItem* pChild = (IItem*)pItem->m_ListChild.GetNext(pPos);
        count = GetCount(pChild, count);
        ++count;
    }

    return count;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::DrawTreeItem(CDC* pDC, IItem* pSelItem, int listItem, const CRect& rect)
{
    const int colWidth     = GetColumnWidth(0);
    const int yDown        = rect.top;
    const int indent       = GetIndent(pSelItem);
    const int halfImage    = (m_CxImage >> 1);
    const int bottomDown   = yDown + halfImage + ((rect.Height() - m_CyImage) >> 1);
    CPen*     pPenTreeLine = pDC->SelectObject(&m_PenTreeLine);

    BOOL child     = ItemHasChildren(pSelItem);
    BOOL collapsed = IsCollapsed(pSelItem);

    // draw outline
    while (1)
    {
        IItem* pParent = GetParentItem(pSelItem);

        // no more parents, stop
        if (!pParent)
            break;

        POSITION pPos = pParent->m_ListChild.GetTailPosition();

        while (pPos)
        {
            IItem*    pLastChild = (IItem*)pParent->m_ListChild.GetPrev(pPos);
            const int index      = GetCurIndex(pLastChild);
            const int curIndent  = GetIndent(pLastChild);

            // don't need to go further in this loop
            if (listItem > index && indent > curIndent)
                break;

            int xLine = rect.left + curIndent * m_CxImage - halfImage;

            // don't draw outside the 1st columns right
            if (index == listItem && curIndent == indent)
            {
                int x;

                // draw
                pDC->MoveTo(xLine, yDown);
                pDC->LineTo(xLine, bottomDown);

                xLine + halfImage > colWidth ? x = colWidth : x = xLine + halfImage;

                pDC->MoveTo(xLine, bottomDown);
                pDC->LineTo(x,     bottomDown);
                break;
            }
            else
            if (index > listItem && curIndent == indent)
            {
                int x;
                xLine + halfImage > colWidth ? x = colWidth : x = xLine + halfImage;

                // draw
                pDC->MoveTo(xLine, bottomDown);
                pDC->LineTo(x,     bottomDown);

                pDC->MoveTo(xLine, yDown);
                pDC->LineTo(xLine, rect.bottom);
                break;
            }
            else
            if (index > listItem && curIndent < indent)
            {
                // draw
                pDC->MoveTo(xLine, yDown);
                pDC->LineTo(xLine, rect.bottom);
                break;
            }
        }

        // the next
        pSelItem = pParent;
    }

    // draw plus/minus sign
    if (child)
    {
        IRectangle childRect(this, pDC, indent, rect);

        childRect.DrawRectangle(this);
        CPen* pPenPlusMinus = pDC->SelectObject(&m_PenPlusMinus);

        if (collapsed)
            childRect.DrawPlus();
        else
        {
            childRect.DrawMinus();

            // draw line up to parent folder
            CPen*     pLine  = pDC->SelectObject(&m_PenTreeLine);
            const int offset = (rect.Height() - m_CyImage) / 2;

            pDC->MoveTo(childRect.GetLeft() + m_CxImage, rect.top + m_CyImage + offset);
            pDC->LineTo(childRect.GetLeft() + m_CxImage, rect.bottom);
            pDC->SelectObject(pLine);
        }

        pDC->SelectObject(pPenPlusMinus);
    }

    pDC->SelectObject(pPenTreeLine);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::DrawFocusCell(CDC* pDC, int item, int subItem, int iconOffset)
{
    if (subItem == m_CurSubItem)
    {
        CRect rect;
        GetSubItemRect(item, subItem, LVIR_BOUNDS, rect);

        if (!subItem)
            GetItemRect(subItem, rect, LVIR_LABEL);

        rect.left += iconOffset;

        CBrush brush(GetCellRGB());
        pDC->FillRect(rect, &brush);
        pDC->DrawFocusRect(rect);
    }
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::DrawComboBox(CDC* pDC, IItem* pSelItem, int item, int column, int subIconOffset)
{
    IItemInfo*               pInfo = GetData(pSelItem);
    IItemInfo::IEControlType ctrlType;

    if (pInfo->GetControlType(column - 1, ctrlType))
        if (ctrlType == IItemInfo::IE_CT_ComboBox)
        {
            CRect rect;
            GetSubItemRect(item, column, LVIR_BOUNDS, rect);
            rect.left = rect.right - ::GetSystemMetrics(SM_CYVSCROLL);
            pDC->DrawFrameControl(rect, DFC_SCROLL, DFCS_SCROLLDOWN);
        }
}
//---------------------------------------------------------------------------
LPCTSTR PSS_GridCtrl::MakeShortString(CDC* pDC, LPCTSTR pLong, int columnLen, int offset)
{
    static const _TCHAR  threeDots[] = _T("...");
    static       CString shortStr;
    const int    stringLen = lstrlen(pLong);

    if (!stringLen || pDC->GetTextExtent(pLong, stringLen).cx + offset < columnLen + 1)
        return(pLong);

    const int addLen = pDC->GetTextExtent(threeDots, sizeof(threeDots)).cx;

    shortStr = pLong;

    for (int i = stringLen - 1; i > 0; --i)
    {
        shortStr = shortStr.Left(shortStr.GetLength() - 1);

        if (pDC->GetTextExtent(shortStr, i).cx + offset + addLen < columnLen)
            break;
    }

    shortStr += threeDots;
    return shortStr;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::HideChildren(IItem* pItem, BOOL hide, int item)
{
    if (!IsCollapsed(pItem))
        if (ItemHasChildren(pItem))
        {
            Hide(pItem, hide);

            POSITION pPos = pItem->m_ListChild.GetHeadPosition();

            while (pPos)
            {
                HideChildren((IItem *)pItem->m_ListChild.GetNext(pPos), hide, item + 1);
                DeleteItem(item);
            }
        }
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::MakeColumnVisible(int col)
{
    if (col < 0)
        return;

    // get the order array to compute the column offset
    CHeaderCtrl* pHeader = GetHeaderCtrl();

    const int colCount = pHeader->GetItemCount();
    ASSERT(col < colCount);

    int  offset      = 0;
    int  colWidth    = 0;
    int* pOrderarray = new int[colCount];

    try
    {
        Header_GetOrderArray(pHeader->m_hWnd, colCount, pOrderarray);

        // get the column offset
        for (int i = 0; pOrderarray[i] != col; ++i)
            offset += GetColumnWidth(pOrderarray[i]);

        colWidth = GetColumnWidth(col);
    }
    catch (...)
    {
        delete[] pOrderarray;
        throw;
    }

    delete[] pOrderarray;

    CRect rect;
    GetItemRect(0, &rect, LVIR_BOUNDS);

    CRect clientRect;
    GetClientRect(&clientRect);

    // scroll to the column
    if (offset + rect.left < 0 || offset + colWidth + rect.left > clientRect.right)
    {
        CSize size(offset + rect.left, 0);
        Scroll(size);
        InvalidateRect(NULL);
        UpdateWindow();
    }
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::CompareChildren(const void* pItem1, const void* pItem2)
{
    IItem*     pChild1    = *(IItem**)pItem1;
    IItem*     pChild2    = *(IItem**)pItem2;
    IItemInfo* pItemInfo1 = (*pChild1).m_pNodeInfo;
    IItemInfo* pItemInfo2 = (*pChild2).m_pNodeInfo;

    return StrComp(&(pItemInfo1->GetItemText()), &(pItemInfo2->GetItemText()));
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::Clear(IItem* pItem)
{
    // delete child nodes
    POSITION pPos = pItem->m_ListChild.GetHeadPosition();

    while (pPos)
    {
        IItem* pItemData = (IItem*)pItem->m_ListChild.GetNext(pPos);

        if (pItemData)
        {
            if (pItemData->m_pNodeInfo)
                delete pItemData->m_pNodeInfo;

            pItemData->m_ListChild.RemoveAll();

            delete pItemData;
        }
    }

    pItem->m_ListChild.RemoveAll();
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::NodeToIndex(IItem* pStartpos, IItem* pNode, int& index, BOOL init)
{
    static BOOL found;

    // account for other root nodes
    if (!GetParentItem(pStartpos) && GetRootIndex(pStartpos))
        ++index;

    if (init)
        found = FALSE;

    if (pStartpos == pNode)
        found = TRUE;

    if (!IsCollapsed(pStartpos))
    {
        POSITION pPos = GetHeadPosition(pStartpos);

        while (pPos)
        {
            IItem* pChild = GetNextChild(pStartpos, pPos);

            if (found)
                return index;

            NodeToIndex(pChild, pNode, index, init);
            ++index;
        }
    }

    if (init && found)
        return index;

    return -1;
}
//---------------------------------------------------------------------------
