/****************************************************************************
 * ==> PSS_ListCtrl --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic list controller                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ListCtrl.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_MinColWidth 70
#define M_MaxColWidth 70
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ListCtrl, CListCtrl)
    //{{AFX_MSG_MAP(PSS_ListCtrl)
    ON_NOTIFY(HDN_ITEMCLICKA, 0, OnItemclick)
    ON_WM_DESTROY()
    ON_WM_CREATE()
    ON_NOTIFY(HDN_ITEMCLICKW, 0, OnItemclick)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ListCtrl
//---------------------------------------------------------------------------
PSS_ListCtrl::PSS_ListCtrl() :
    CListCtrl(),
    m_pImageList(NULL),
    m_SortedCol(-1),
    m_EnableOver(FALSE),
    m_FullRowSelect(FALSE),
    m_SortAscending(TRUE),
    m_SaveColumnState(FALSE),
    m_EnableSort(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ListCtrl::~PSS_ListCtrl()
{}
//---------------------------------------------------------------------------
int PSS_ListCtrl::InitializeFlatHeader()
{
    if (!m_HeaderCtrl.SubclassWindow(GetDlgItem(0)->GetSafeHwnd()))
        return -1;

    m_HeaderCtrl.FlatHeader();

    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_ListCtrl::SortTextItems(int col, BOOL ascending, int low, int high)
{
    if (col >= ((CHeaderCtrl*)GetDlgItem(0))->GetItemCount())
        return FALSE;

    if (high == -1)
        high = GetItemCount() - 1;

    int lo = low;
    int hi = high;

    if (hi <= lo)
        return FALSE;

    CString midItem = GetItemText((lo + hi) / 2, col);

    // iterate through the list until all items are sorted
    while (lo <= hi)
    {
        // row text will hold all column text for one row
        CStringArray rowText;

        // find the first element that is greater than or equal to the element to swap, starting
        // from the left index
        if (ascending)
        {
            while ((lo < high) && (GetItemText(lo, col) < midItem))
                ++lo;
        }
        else
            while ((lo < high) && (GetItemText(lo, col) > midItem))
                ++lo;

        // find an element that is smaller than or equal to the element to swap, starting from the
        // right index
        if (ascending)
        {
            while ((hi > low) && (GetItemText(hi, col) > midItem))
                --hi;
        }
        else
            while ((hi > low) && (GetItemText(hi, col) < midItem))
                --hi;

        // if the indexes were not swapped and are not equal, swap them
        if (lo <= hi)
        {
            // swap only if the items are not equal
            if (GetItemText(lo, col) != GetItemText(hi, col))
            {
                // swap the rows
                const int colCount = ((CHeaderCtrl*)GetDlgItem(0))->GetItemCount();
                rowText.SetSize(colCount);

                for (int i = 0; i < colCount; ++i)
                    rowText[i] = GetItemText(lo, i);

                LV_ITEM lvitemlo;
                lvitemlo.mask      = LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
                lvitemlo.iItem     = lo;
                lvitemlo.iSubItem  = 0;
                lvitemlo.stateMask = LVIS_CUT         |
                                     LVIS_DROPHILITED |
                                     LVIS_FOCUSED     |
                                     LVIS_SELECTED    |
                                     LVIS_OVERLAYMASK |
                                     LVIS_STATEIMAGEMASK;

                LV_ITEM lvitemhi;
                lvitemhi       = lvitemlo;
                lvitemhi.iItem = hi;

                GetItem(&lvitemlo);
                GetItem(&lvitemhi);

                for (int i = 0; i < colCount; ++i)
                    SetItemText(lo, i, GetItemText(hi, i));

                lvitemhi.iItem = lo;
                SetItem(&lvitemhi);

                for (int i = 0; i < colCount; ++i)
                    SetItemText(hi, i, rowText[i]);

                lvitemlo.iItem = hi;
                SetItem(&lvitemlo);
            }

            ++lo;
            --hi;
        }
    }

    // if the right index has not reached the left array side, the left partition should be sorted
    if (low < hi)
        SortTextItems(col, ascending, low, hi);

    // if the left index has not reached the right array side, the right partition should be sorted
    if (lo < high)
        SortTextItems(col, ascending, lo, high);

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::SetExtendedStyle(DWORD newStyle)
{
    // get the current extended style
    DWORD style = ::SendMessage(m_hWnd, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);

    // add the full row select and grid line style to the existing extended styles
    style |= newStyle;

    // set the current extended style
    ::SendMessage(m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, style);
}
//---------------------------------------------------------------------------
BOOL PSS_ListCtrl::BuildColumns(int cols, int* pWidth, int* pColString)
{
    if (!pWidth)
        return FALSE;

    if (!pColString)
        return FALSE;

    LV_COLUMN lvc = {0};
    lvc.mask      = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

    CString str;

    // insert columns
    for (int i = 0; i < cols; ++i)
    {
        lvc.iSubItem = i;
        lvc.cx       = pWidth[i];
        lvc.fmt      = LVCFMT_LEFT;

        str.LoadString(pColString[i]);
        lvc.pszText = str.GetBuffer(0);
        str.ReleaseBuffer(-1);

        InsertColumn(i, &lvc);
    }
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::AutoSizeColumn(int column)
{
    SetRedraw(TRUE);

    CListCtrl::SetColumnWidth(column, LVSCW_AUTOSIZE);
    const int cw1 = GetColumnWidth(column);

    CListCtrl::SetColumnWidth(column, LVSCW_AUTOSIZE_USEHEADER);
    const int cw2 = GetColumnWidth(column);

    int cw = __max(MINCOLWIDTH, __max(cw1, cw2));

    if (cw > MAXCOLWIDTH)
        cw = MAXCOLWIDTH;

    CListCtrl::SetColumnWidth(column, cw);
    SetRedraw(FALSE);
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::LoadImageList(UINT id, int size, int grow, COLORREF maskColor)
{
    m_pImageList = new CImageList();
    m_pImageList->Create(id, size, grow, maskColor);

    SetImageList(m_pImageList, TVSIL_NORMAL);
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::LoadImageList(UINT startID, UINT endID, UINT flags, int cx, int cy)
{
    CBitmap bitmap;

    m_pImageList = new CImageList();
    m_pImageList->Create(cx, cy, flags, 2, 2);

    // if end index is zero, assign it to start
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
    SetImageList(m_pImageList, LVSIL_SMALL);
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::LoadImageListMasked(UINT startID, UINT endID, int cx, int cy)
{
    CBitmap bitmap;

    m_pImageList = new CImageList();
    m_pImageList->Create(cx, cy, ILC_MASK, 2, 2);

    // if end index is zero, assign it to start
    if (!endID)
        endID = startID;

    // load bitmaps
    for (UINT id = startID; id <= endID; ++id)
    {
        bitmap.LoadBitmap(id);
        m_pImageList->Add(&bitmap, static_cast<COLORREF>(0xFFFFFF));
        bitmap.DeleteObject();
    }

    SetImageList(m_pImageList, TVSIL_NORMAL);
    SetImageList(m_pImageList, LVSIL_SMALL);
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::SetHeaderBitmap(int col, int bitmapID, DWORD remove)
{
    HD_ITEM hdi;
    hdi.mask = HDI_FORMAT;
    m_HeaderCtrl.GetItem(col, &hdi);

    hdi.mask = HDI_BITMAP | HDI_FORMAT;
    hdi.fmt |= HDF_BITMAP;
    hdi.hbm  = (HBITMAP)::LoadImage(::AfxFindResourceHandle(MAKEINTRESOURCE(bitmapID), RT_BITMAP),
                                    MAKEINTRESOURCE(bitmapID),
                                    IMAGE_BITMAP,
                                    0,
                                    0,
                                    LR_LOADMAP3DCOLORS);

    if (remove)
        hdi.fmt &= ~remove;

    m_HeaderCtrl.SetItem(col, &hdi);
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::SetEnableOver(BOOL value)
{
    DWORD extStyles = GetExtendedStyle();

    if (value)
        extStyles = extStyles | LVS_EX_TRACKSELECT | LVS_EX_ONECLICKACTIVATE;
    else
        extStyles = extStyles & (~LVS_EX_TRACKSELECT | ~LVS_EX_ONECLICKACTIVATE);

    SetExtendedStyle(extStyles);
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::SetEnableEditLabel(BOOL value)
{
    DWORD extStyles = GetExtendedStyle();

    if (value)
        extStyles |= LVS_EDITLABELS;
    else
        extStyles &= ~LVS_EDITLABELS;

    SetExtendedStyle(extStyles);
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::SetFullRowSelect(BOOL value)
{
    DWORD extStyles = GetExtendedStyle();

    if (value)
        extStyles |= LVS_EX_FULLROWSELECT;
    else
        extStyles &= ~LVS_EX_FULLROWSELECT;

    SetExtendedStyle(extStyles);
}
//---------------------------------------------------------------------------
BOOL PSS_ListCtrl::DeleteAllItems(BOOL deleteImageList)
{
    if (deleteImageList && ::IsWindow(GetSafeHwnd()))
    {
        CImageList* pImageList = GetImageList(TVSIL_NORMAL);

        if (pImageList)
        {
            pImageList->DeleteImageList();
            delete pImageList;
            pImageList = NULL;
        }
    }

    if (IsWindow(GetSafeHwnd()))
        return CListCtrl::DeleteAllItems();

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::DeSelectAll()
{
    POSITION pPos = GetFirstSelectedItemPosition();

    while (pPos)
    {
        int item = GetNextSelectedItem(pPos);
        SetItemState(item, 0, LVIS_SELECTED);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ListCtrl::SetCurSel(std::size_t index)
{
    if (index < GetItemCount())
    {
        SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::PreSubclassWindow()
{
    CListCtrl::PreSubclassWindow();
    InitializeFlatHeader();
}
//---------------------------------------------------------------------------
int PSS_ListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CListCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    return InitializeFlatHeader();
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::OnItemclick(NMHDR* pNMHDR, LRESULT* pResult)
{
    if (!m_EnableSort)
        return;

    HD_NOTIFY* pHdn = (HD_NOTIFY*)pNMHDR;

    if (pHdn->iButton == 0)
    {
        // user clicked on header using left mouse button
        if (pHdn->iItem == m_SortedCol)
            m_SortAscending = !m_SortAscending;
        else
            m_SortAscending = TRUE;

        m_SortedCol = pHdn->iItem;
        SortTextItems(m_SortedCol, m_SortAscending);
        m_HeaderCtrl.SetSortImage(m_SortedCol, m_SortAscending);
    }

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::OnDestroy()
{
    PSS_ListCtrl::DeleteAllItems(TRUE);
    CListCtrl::OnDestroy();
}
//---------------------------------------------------------------------------
