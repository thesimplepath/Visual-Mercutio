
#include "stdafx.h"
#include "ZVTreeListCtrl.h"

#include "zBaseLibRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZVTreeListCtrl, ZIListCtrl)
    //{{AFX_MSG_MAP(ZVTreeListCtrl)
    ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
    ON_WM_KEYDOWN()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVTreeListCtrl

ZVTreeListCtrl::ZVTreeListCtrl()
{
}

ZVTreeListCtrl::~ZVTreeListCtrl()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZVTreeListCtrl overrides

void ZVTreeListCtrl::PreSubclassWindow() 
{
    // LVS_EX_GRIDLINES // 5.0: LVS_EX_LABELTIP 
    SetExtendedStyle(LVS_EX_FULLROWSELECT);

    if (NULL == m_ilState.GetSafeHandle())
    {
        m_ilState.Create(IDB_PLUSMINUS, 16, 1, RGB(255, 0, 0));
    }
    SetImageList(&m_ilState, LVSIL_STATE);
    
    ZIListCtrl::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// ZVTreeListCtrl operations

BOOL ZVTreeListCtrl::Create( DWORD dwStyle,
                             const RECT& rect,
                             CWnd* pParentWnd,
                             UINT nID )
{
    if (!ZIListCtrl::Create(dwStyle, rect, pParentWnd, nID))
        return FALSE;

    // LVS_EX_GRIDLINES // 5.0: LVS_EX_LABELTIP 
    SetExtendedStyle(LVS_EX_FULLROWSELECT);

    if (NULL == m_ilState.GetSafeHandle())
    {
        m_ilState.Create(IDB_PLUSMINUS, 16, 1, RGB(255, 0, 0));
    }
    SetImageList(&m_ilState, LVSIL_STATE);

    return TRUE;
}

int ZVTreeListCtrl::AddItem( LPCTSTR lpszItem, int nImage, int nLevel, LPARAM pParam /*= NULL*/ )
{
    LVITEM            item;
    _TreeListInfo    info;
    
    info.m_nItem = m_TreeCtrl.size();
    info.m_nLevel    = nLevel;
    info.m_nImage    = nImage;
    info.m_lstCols.resize(GetHeaderCtrl()->GetItemCount());
    info.m_lstCols[0] = lpszItem;
    info.m_bCollapsed = true;
    info.m_pParam = pParam;
    m_TreeCtrl.push_back(info);

    item.mask        = LVIF_TEXT | LVIF_IMAGE | LVIF_INDENT | LVIF_STATE | LVIF_PARAM;
    item.iItem        = info.m_nItem;
    item.iSubItem    = 0;
    item.pszText    = (LPTSTR)(LPCTSTR)info.m_lstCols[0];
    item.iImage        = info.m_nImage;
    item.iIndent    = info.m_nLevel;
    item.state        = INDEXTOSTATEIMAGEMASK(info.m_bCollapsed ? 1 : 2);
    item.stateMask    = LVIS_STATEIMAGEMASK;
    item.lParam        = info.m_nItem;

    if (info.m_nLevel == 0)
    {
        ZIListCtrl::InsertItem(&item);
    }

    return info.m_nItem;
}

BOOL  ZVTreeListCtrl::SetItemText( int nItem, int nSubItem, LPCTSTR lpszText )
{
    m_TreeCtrl.at(nItem).m_lstCols[nSubItem] = lpszText;
    return ZIListCtrl::SetItemText(nItem, nSubItem, lpszText);
}

/////////////////////////////////////////////////////////////////////////////
// ZVTreeListCtrl protected functions

int ZVTreeListCtrl::InsertItem( int nItem, int nPosArray, _TreeListInfo& info )
{
    LVITEM            item;

    item.mask        = LVIF_TEXT | LVIF_IMAGE | LVIF_INDENT | LVIF_STATE | LVIF_PARAM;
    item.iItem        = nItem;
    item.iSubItem    = 0;
    item.pszText    = (LPTSTR)(LPCTSTR)info.m_lstCols[0];
    item.iImage        = info.m_nImage;
    item.iIndent    = info.m_nLevel;
    item.state        = INDEXTOSTATEIMAGEMASK(info.m_bCollapsed ? 1 : 2);
    item.stateMask    = LVIS_STATEIMAGEMASK;
    item.lParam        = nPosArray;

    int    nItemRes = ZIListCtrl::InsertItem(&item);

    for (int i = 1; i < info.m_lstCols.size(); i++)
    {
        ZIListCtrl::SetItemText(nItemRes, i, info.m_lstCols[i]);
    }
    return nItemRes;
}

LPARAM    ZVTreeListCtrl::GetParam( int nItem )
{
    for (int i = 0; i < m_TreeCtrl.size(); ++i)
    {
        if (m_TreeCtrl[i].m_nItem == nItem)
            return m_TreeCtrl[i].m_pParam;
    }
    return NULL;
}

BOOL ZVTreeListCtrl::DeleteAllItems( BOOL DeleteImageList /*= FALSE*/ )
{
    m_TreeCtrl.clear();
    return ZIListCtrl::DeleteAllItems(DeleteImageList);
}

void ZVTreeListCtrl::Collapse( int nPos, int nItem )
{
    int                nLevel;
    int                nLast;
    LVITEM            item;
    
    _TreeListInfo&    info = m_TreeCtrl[nPos];
    info.m_bCollapsed = true;

    SetRedraw(0);
    nLevel    = info.m_nLevel;
    nLast    = GetItemCount();
    item.mask        = LVIF_PARAM;
    item.iSubItem    = 0;

    int nCounter = nItem + 1;
    if (nCounter < nLast)
    {
        do
        {
            item.iItem        = nCounter;
            GetItem(&item);
            if (m_TreeCtrl[item.lParam].m_nLevel > nLevel)
                DeleteItem(nItem + 1);
        }
        while (m_TreeCtrl[item.lParam].m_nLevel > nLevel && GetItemCount() > nCounter);
    }

    SetRedraw(1);
}

int ZVTreeListCtrl::Expand( int nItem, bool bRecursive, int& nCounterInsert )
{
    _TreeListInfo&    info    = m_TreeCtrl[nItem];
    info.m_bCollapsed        = false;

    int                nCounter;
    int                nLevel;
    
    nCounter        = nItem + 1;
    nCounterInsert    = nCounterInsert + 1;
    nLevel            = info.m_nLevel;
    while (nCounter < m_TreeCtrl.size() && m_TreeCtrl[nCounter].m_nLevel > nLevel)
    {
        if (m_TreeCtrl[nCounter].m_nLevel > nLevel)
        {
            if (bRecursive)
            {
                m_TreeCtrl[nCounter].m_bCollapsed = false;
            }
            InsertItem(nCounterInsert, nCounter, m_TreeCtrl[nCounter]);
        }

        if (bRecursive || !m_TreeCtrl[nCounter].m_bCollapsed)
        {
            nCounter = Expand(nCounter, bRecursive, nCounterInsert);
        }
        else
        {
            int    nSonLevel;

            nSonLevel = m_TreeCtrl[nCounter].m_nLevel;
            while (++nCounter < m_TreeCtrl.size() && m_TreeCtrl[nCounter].m_nLevel > nSonLevel)
            {
            }

            nCounterInsert++;
        }        
    }
    
    return nCounter;
}

/////////////////////////////////////////////////////////////////////////////
// ZVTreeListCtrl message handlers

void ZVTreeListCtrl::OnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
    LPNMITEMACTIVATE    pItemActivate = (LPNMITEMACTIVATE)pNMHDR;

    CRect                rect;

    GetItemRect(pItemActivate->iItem, rect, LVIR_ICON);
        
    if (pItemActivate->ptAction.x < rect.left)
    {
        LVITEM    item;

        item.mask        = LVIF_INDENT | LVIF_PARAM;
        item.iItem        = pItemActivate->iItem;
        item.iSubItem    = 0;
        GetItem(&item);

        if (pItemActivate->ptAction.x > item.iIndent * 16)
        {
            if (m_TreeCtrl[item.lParam].m_bCollapsed)
            {    
                int    nInsert = pItemActivate->iItem;
                SetRedraw(0);
                Expand(item.lParam, false, nInsert);
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
    }
    
    *pResult = 0;
}

void ZVTreeListCtrl::OnKeyDown( UINT nChar, UINT nRepCnt,UINT nFlags )
{
    int        nItem    =    GetNextItem(-1, LVNI_SELECTED);    

    if (nItem == -1)
    {
        ZIListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
        return;
    }
    
    LVITEM        item;

    item.mask        = LVIF_INDENT | LVIF_PARAM;
    item.iItem        = nItem;
    item.iSubItem    = 0;
    GetItem(&item);

    switch (nChar)
    {
        case VK_ADD:
        {
            if (m_TreeCtrl[item.lParam].m_bCollapsed)
            {    
                int    nInsert = nItem;
                SetRedraw(0);
                Expand(item.lParam, false, nInsert);
                SetRedraw(1);
                SetItemState(nItem, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
            }
            break;
        }
        case VK_SUBTRACT:
        {
            if (!m_TreeCtrl[item.lParam].m_bCollapsed)
            {                
                SetRedraw(0);
                Collapse(item.lParam, nItem);
                SetRedraw(1);
                SetItemState(nItem, INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK);
            }
            break;
        }
        case VK_RIGHT:
        {
            if (m_TreeCtrl[item.lParam].m_bCollapsed)
            {    
                int    nInsert = nItem;
                SetRedraw(0);
                Expand(item.lParam, false, nInsert);
                SetRedraw(1);
                SetItemState(nItem, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
            }
            else
            {
                // If any child, move to the first one
                int nNextItem    = item.lParam + 1;
                if (nNextItem < m_TreeCtrl.size() && m_TreeCtrl[nNextItem].m_nLevel > m_TreeCtrl[item.lParam].m_nLevel)
                {
                    SetItemState(nItem + 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
                }
            }
            break;
        }
        case VK_LEFT:
        {
            if (!m_TreeCtrl[item.lParam].m_bCollapsed)
            {                
                SetRedraw(0);
                Collapse(item.lParam, nItem);
                SetRedraw(1);
                SetItemState(nItem, INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK);
            }
            else
            {
                // Move to our parent
                int nPrevItem    = item.lParam - 1;
                int    nLevel        = m_TreeCtrl[item.lParam].m_nLevel;

                while (nPrevItem >= 0 && nLevel <= m_TreeCtrl[nPrevItem].m_nLevel)
                {
                    --nPrevItem;
                }

                if (nPrevItem >= 0)
                {
                    LVFINDINFO        info;
                    
                    info.flags        = LVFI_PARAM;
                    info.lParam        = nPrevItem;
            
                    SetItemState(FindItem(&info), LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
                }
            }
            break;
        }
        default:
        {
            ZIListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
            break;
        }
    }
}

void ZVTreeListCtrl::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags ) 
{
    int    nItem = GetNextItem(-1, LVNI_SELECTED);    

    if (nItem != -1)
    {
        LVITEM        item;

        item.mask        = LVIF_INDENT | LVIF_PARAM;
        item.iItem        = nItem;
        item.iSubItem    = 0;
        GetItem(&item);

        if (nChar == '*')
        {
            // TODO: Recursively expands items 
            if (m_TreeCtrl[item.lParam].m_bCollapsed)
            {    
                int    nInsert = nItem;
                SetRedraw(0);
                Expand(item.lParam, true, nInsert);
                SetRedraw(1);
                SetItemState(nItem, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
            }
        }    
    }

    ZIListCtrl::OnChar(nChar, nRepCnt, nFlags);
}
