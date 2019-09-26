/****************************************************************************
 * ==> PSS_TreeListCtrl ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a tree list controller                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_TreeListCtrl.h"

// resources
#include "zBaseLibRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_TreeListCtrl, ZIListCtrl)
    //{{AFX_MSG_MAP(PSS_TreeListCtrl)
    ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
    ON_WM_KEYDOWN()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_TreeListCtrl::IInfo
//---------------------------------------------------------------------------
PSS_TreeListCtrl::IInfo::IInfo() :
    m_LParam(NULL),
    m_Level(0),
    m_Image(0),
    m_Item(0),
    m_Collapsed(false)
{}
//---------------------------------------------------------------------------
PSS_TreeListCtrl::IInfo::~IInfo()
{}
//---------------------------------------------------------------------------
// PSS_TreeListCtrl
//---------------------------------------------------------------------------
PSS_TreeListCtrl::PSS_TreeListCtrl() :
    ZIListCtrl()
{}
//---------------------------------------------------------------------------
PSS_TreeListCtrl::~PSS_TreeListCtrl()
{}
//---------------------------------------------------------------------------
BOOL PSS_TreeListCtrl::Create(DWORD style, const RECT& rect, CWnd* pParentWnd, UINT id)
{
    if (!ZIListCtrl::Create(style, rect, pParentWnd, id))
        return FALSE;

    SetExtendedStyle(LVS_EX_FULLROWSELECT);

    if (!m_ILState.GetSafeHandle())
        m_ILState.Create(IDB_PLUSMINUS, 16, 1, RGB(255, 0, 0));

    SetImageList(&m_ILState, LVSIL_STATE);

    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_TreeListCtrl::AddItem(LPCTSTR pItem, int imageIndex, int level, LPARAM lParam)
{
    LVITEM item;
    IInfo  info;

    info.m_Columns.resize(GetHeaderCtrl()->GetItemCount());
    info.m_Columns[0] = pItem;
    info.m_Item       = m_TreeCtrl.size();
    info.m_Level      = level;
    info.m_Image      = imageIndex;
    info.m_Collapsed  = true;
    info.m_LParam     = lParam;
    m_TreeCtrl.push_back(info);

    item.mask      = LVIF_TEXT | LVIF_IMAGE | LVIF_INDENT | LVIF_STATE | LVIF_PARAM;
    item.iItem     = info.m_Item;
    item.iSubItem  = 0;
    item.pszText   = LPTSTR(LPCTSTR(info.m_Columns[0]));
    item.iImage    = info.m_Image;
    item.iIndent   = info.m_Level;
    item.state     = INDEXTOSTATEIMAGEMASK(info.m_Collapsed ? 1 : 2);
    item.stateMask = LVIS_STATEIMAGEMASK;
    item.lParam    = info.m_Item;

    if (!info.m_Level)
        ZIListCtrl::InsertItem(&item);

    return info.m_Item;
}
//---------------------------------------------------------------------------
BOOL PSS_TreeListCtrl::SetItemText(int itemIndex, int subItemIndex, LPCTSTR pText)
{
    IInfo& info = m_TreeCtrl.at(itemIndex);

    if (subItemIndex >= info.m_Columns.size())
        THROW("Sub-item index is out of bounds");

    info.m_Columns[subItemIndex] = pText;

    return ZIListCtrl::SetItemText(itemIndex, subItemIndex, pText);
}
//---------------------------------------------------------------------------
LPARAM PSS_TreeListCtrl::GetParam(int itemIndex)
{
    const int count = m_TreeCtrl.size();

    for (int i = 0; i < count; ++i)
        if (m_TreeCtrl[i].m_Item == itemIndex)
            return m_TreeCtrl[i].m_LParam;

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_TreeListCtrl::DeleteAllItems(BOOL deleteImageList)
{
    m_TreeCtrl.clear();
    return ZIListCtrl::DeleteAllItems(deleteImageList);
}
//---------------------------------------------------------------------------
void PSS_TreeListCtrl::PreSubclassWindow()
{
    SetExtendedStyle(LVS_EX_FULLROWSELECT);

    if (!m_ILState.GetSafeHandle())
        m_ILState.Create(IDB_PLUSMINUS, 16, 1, RGB(255, 0, 0));

    SetImageList(&m_ILState, LVSIL_STATE);

    ZIListCtrl::PreSubclassWindow();
}
//---------------------------------------------------------------------------
void PSS_TreeListCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMITEMACTIVATE pItemActivate = LPNMITEMACTIVATE(pNMHDR);
    CRect            rect;

    GetItemRect(pItemActivate->iItem, rect, LVIR_ICON);

    if (pItemActivate->ptAction.x < rect.left)
    {
        LVITEM item;
        item.mask     = LVIF_INDENT | LVIF_PARAM;
        item.iItem    = pItemActivate->iItem;
        item.iSubItem = 0;
        GetItem(&item);

        if (pItemActivate->ptAction.x > item.iIndent * 16)
            if (m_TreeCtrl[item.lParam].m_Collapsed)
            {
                int insert = pItemActivate->iItem;
                SetRedraw(0);
                Expand(item.lParam, false, insert);
                SetRedraw(1);
                SetItemState(pItemActivate->iItem, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
            }
            else
            {
                SetRedraw(0);
                Collapse(item.lParam, pItemActivate->iItem);
                SetRedraw(1);
                SetItemState(pItemActivate->iItem, INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK);
            }
    }

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_TreeListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const int itemIndex = GetNextItem(-1, LVNI_SELECTED);

    if (itemIndex == -1)
    {
        ZIListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
        return;
    }

    LVITEM item;
    item.mask     = LVIF_INDENT | LVIF_PARAM;
    item.iItem    = itemIndex;
    item.iSubItem = 0;
    GetItem(&item);

    switch (nChar)
    {
        case VK_ADD:
            if (m_TreeCtrl[item.lParam].m_Collapsed)
            {
                int insert = itemIndex;
                SetRedraw(0);
                Expand(item.lParam, false, insert);
                SetRedraw(1);
                SetItemState(itemIndex, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
            }

            break;

        case VK_SUBTRACT:
            if (!m_TreeCtrl[item.lParam].m_Collapsed)
            {
                SetRedraw(0);
                Collapse(item.lParam, itemIndex);
                SetRedraw(1);
                SetItemState(itemIndex, INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK);
            }

            break;

        case VK_RIGHT:
            if (m_TreeCtrl[item.lParam].m_Collapsed)
            {
                int insert = itemIndex;
                SetRedraw(0);
                Expand(item.lParam, false, insert);
                SetRedraw(1);
                SetItemState(itemIndex, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
            }
            else
            {
                // if any child, move to the first one
                const int nextItem = item.lParam + 1;

                if (nextItem < m_TreeCtrl.size() && m_TreeCtrl[nextItem].m_Level > m_TreeCtrl[item.lParam].m_Level)
                    SetItemState(itemIndex + 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
            }

            break;

        case VK_LEFT:
            if (!m_TreeCtrl[item.lParam].m_Collapsed)
            {
                SetRedraw(0);
                Collapse(item.lParam, itemIndex);
                SetRedraw(1);
                SetItemState(itemIndex, INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK);
            }
            else
            {
                // move to our parent
                int prevItem = item.lParam - 1;
                int level    = m_TreeCtrl[item.lParam].m_Level;

                while (prevItem >= 0 && level <= m_TreeCtrl[prevItem].m_Level)
                    --prevItem;

                if (prevItem >= 0)
                {
                    LVFINDINFO info;
                    info.flags  = LVFI_PARAM;
                    info.lParam = prevItem;

                    SetItemState(FindItem(&info), LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
                }
            }

            break;

        default:
            ZIListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
            break;
    }
}
//---------------------------------------------------------------------------
void PSS_TreeListCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const int itemIndex = GetNextItem(-1, LVNI_SELECTED);

    if (itemIndex != -1)
    {
        LVITEM item;
        item.mask     = LVIF_INDENT | LVIF_PARAM;
        item.iItem    = itemIndex;
        item.iSubItem = 0;
        GetItem(&item);

        if (nChar == '*')
        {
            // TODO: Recursively expands items 
            if (m_TreeCtrl[item.lParam].m_Collapsed)
            {
                int insert = itemIndex;
                SetRedraw(0);
                Expand(item.lParam, true, insert);
                SetRedraw(1);
                SetItemState(itemIndex, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
            }
        }
    }

    ZIListCtrl::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
int PSS_TreeListCtrl::InsertItem(int itemIndex, int posArray, IInfo& info)
{
    LVITEM item;
    item.mask      = LVIF_TEXT | LVIF_IMAGE | LVIF_INDENT | LVIF_STATE | LVIF_PARAM;
    item.iItem     = itemIndex;
    item.iSubItem  = 0;
    item.pszText   = LPTSTR(LPCTSTR(info.m_Columns[0]));
    item.iImage    = info.m_Image;
    item.iIndent   = info.m_Level;
    item.state     = INDEXTOSTATEIMAGEMASK(info.m_Collapsed ? 1 : 2);
    item.stateMask = LVIS_STATEIMAGEMASK;
    item.lParam    = posArray;

    const int itemRes = ZIListCtrl::InsertItem(&item);
    const int count   = info.m_Columns.size();

    for (int i = 1; i < count; ++i)
        ZIListCtrl::SetItemText(itemRes, i, info.m_Columns[i]);

    return itemRes;
}
//---------------------------------------------------------------------------
void PSS_TreeListCtrl::Collapse(int pos, int itemIndex)
{
    IInfo& info      = m_TreeCtrl[pos];
    info.m_Collapsed = true;

    SetRedraw(0);

    const int level = info.m_Level;
    const int last  = GetItemCount();

    LVITEM item;
    item.mask     = LVIF_PARAM;
    item.iSubItem = 0;

    const int counter = itemIndex + 1;

    if (counter < last)
        do
        {
            item.iItem = counter;

            GetItem(&item);

            if (m_TreeCtrl[item.lParam].m_Level > level)
                DeleteItem(itemIndex + 1);
        }
        while (m_TreeCtrl[item.lParam].m_Level > level && GetItemCount() > counter);

    SetRedraw(1);
}
//---------------------------------------------------------------------------
int PSS_TreeListCtrl::Expand(int itemIndex, bool recursive, int& counterInsert)
{
    IInfo& info      = m_TreeCtrl[itemIndex];
    info.m_Collapsed = false;

    const int level   = info.m_Level;
          int counter = itemIndex     + 1;
    counterInsert     = counterInsert + 1;

    while (counter < m_TreeCtrl.size() && m_TreeCtrl[counter].m_Level > level)
    {
        if (m_TreeCtrl[counter].m_Level > level)
        {
            if (recursive)
                m_TreeCtrl[counter].m_Collapsed = false;

            InsertItem(counterInsert, counter, m_TreeCtrl[counter]);
        }

        if (recursive || !m_TreeCtrl[counter].m_Collapsed)
            counter = Expand(counter, recursive, counterInsert);
        else
        {
            const int childLevel = m_TreeCtrl[counter].m_Level;

            while (++counter < m_TreeCtrl.size() && m_TreeCtrl[counter].m_Level > childLevel)
            {}

            ++counterInsert;
        }
    }

    return counter;
}
//---------------------------------------------------------------------------
