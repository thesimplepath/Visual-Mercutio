// ZIListCtrl.cpp : implementation file
// 
#include "stdafx.h"
#include "ZIListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIListCtrl

ZIListCtrl::ZIListCtrl()
{
    m_nSortedCol = -1;
    m_bEnableOver = FALSE;
    m_bFullRowSelect = FALSE;
    m_bSortAscending = TRUE;
    m_bSaveColumnState = FALSE;
    m_bEnableSort = FALSE;
    m_strSection.Empty();
    m_strControl.Empty();
    m_pImageList = NULL;
}

ZIListCtrl::~ZIListCtrl()
{
}

void ZIListCtrl::SetEnableOver( BOOL value /*= TRUE*/)
{
    DWORD    dwExtStyles;
    dwExtStyles = GetExtendedStyle();
    if (value)
        dwExtStyles = dwExtStyles | LVS_EX_TRACKSELECT | LVS_EX_ONECLICKACTIVATE;
    else
        dwExtStyles = dwExtStyles & (~LVS_EX_TRACKSELECT | ~LVS_EX_ONECLICKACTIVATE);
    SetExtendedStyle( dwExtStyles );
}

void ZIListCtrl::SetFullRowSelect( BOOL value /*= TRUE*/)
{
    DWORD    dwExtStyles;
    dwExtStyles = GetExtendedStyle();
    if (value)
        dwExtStyles |= LVS_EX_FULLROWSELECT;
    else
        dwExtStyles &= ~LVS_EX_FULLROWSELECT;
    SetExtendedStyle( dwExtStyles );
}

void ZIListCtrl::SetEnableEditLabel( BOOL value /*= TRUE*/)
{
    DWORD    dwExtStyles;
    dwExtStyles = GetExtendedStyle();
    if (value)
        dwExtStyles |= LVS_EDITLABELS;
    else
        dwExtStyles &= ~LVS_EDITLABELS;
    SetExtendedStyle( dwExtStyles );
}

void ZIListCtrl::SetHeaderBitmap(int nCol, int nBitmap, DWORD dwRemove)
{
    HD_ITEM hdi;
    hdi.mask = HDI_FORMAT;
    m_HeaderCtrl.GetItem (nCol, &hdi);
    hdi.mask = HDI_BITMAP | HDI_FORMAT;
    hdi.fmt  |= HDF_BITMAP;
    hdi.hbm = (HBITMAP)::LoadImage(AfxFindResourceHandle(MAKEINTRESOURCE(nBitmap), RT_BITMAP),
        MAKEINTRESOURCE(nBitmap),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);

    if (dwRemove)
        hdi.fmt &= ~dwRemove;

    m_HeaderCtrl.SetItem (nCol, &hdi);
}

BEGIN_MESSAGE_MAP(ZIListCtrl, CListCtrl)
    //{{AFX_MSG_MAP(ZIListCtrl)
    ON_NOTIFY(HDN_ITEMCLICKA, 0, OnItemclick) 
    ON_WM_DESTROY()
    ON_WM_CREATE()
    ON_NOTIFY(HDN_ITEMCLICKW, 0, OnItemclick)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void ZIListCtrl::LoadImageList( UINT nID, int cx, int Grow, COLORREF crMask )
{
    m_pImageList = new CImageList();
    m_pImageList->Create( nID, cx, Grow, crMask );

    SetImageList(m_pImageList, TVSIL_NORMAL);
}

void ZIListCtrl::LoadImageList( UINT nIDStart, UINT nIDEnd, UINT nFlags, int cx, int cy )
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
    SetImageList(m_pImageList, TVSIL_NORMAL);
    SetImageList(m_pImageList, LVSIL_SMALL);
}

void ZIListCtrl::LoadImageListMasked( UINT nIDStart, UINT nIDEnd, int cx, int cy )
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
    SetImageList(m_pImageList, TVSIL_NORMAL);
    SetImageList(m_pImageList, LVSIL_SMALL);
}

/////////////////////////////////////////////////////////////////////////////
// ZIListCtrl message handlers

void ZIListCtrl::OnItemclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if (!m_bEnableSort)
        return;
    HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;

    if( phdn->iButton == 0 )
    {
        // User clicked on header using left mouse button
        if( phdn->iItem == m_nSortedCol )
            m_bSortAscending = !m_bSortAscending;
        else
            m_bSortAscending = TRUE;

        m_nSortedCol = phdn->iItem;
        SortTextItems( m_nSortedCol, m_bSortAscending );
        m_HeaderCtrl.SetSortImage(m_nSortedCol, m_bSortAscending);
    }

    *pResult = 0;
}

// SortTextItems    - Sort the list based on column text
// Returns        - Returns true for success
// nCol            - column that contains the text to be sorted
// bAscending        - indicate sort order
// low            - row to start scanning from - default row is 0
// high            - row to end scan. -1 indicates last row

BOOL ZIListCtrl::SortTextItems( int nCol, BOOL bAscending, int low /*= 0*/, int high /*= -1*/ )
{
    if( nCol >= ((CHeaderCtrl*)GetDlgItem(0))->GetItemCount() )
        return FALSE;

    if( high == -1 ) high = GetItemCount() - 1;

    int lo = low;
    int hi = high;
    CString midItem;

    if( hi <= lo ) return FALSE;

    midItem = GetItemText( (lo+hi)/2, nCol );

    // loop through the list until indices cross
    while( lo <= hi )
    {
        // rowText will hold all column text for one row
        CStringArray rowText;

        // find the first element that is greater than or equal to
        // the partition element starting from the left Index.
        if( bAscending ) {
            while( ( lo < high ) && ( GetItemText(lo, nCol) < midItem ) )
                ++lo;
        }
        else {
            while( ( lo < high ) && ( GetItemText(lo, nCol) > midItem ) )
                ++lo;
        }

        // find an element that is smaller than or equal to
        // the partition element starting from the right Index.
        if( bAscending ) {
            while( ( hi > low ) && ( GetItemText(hi, nCol) > midItem ) )
                --hi;
        }

        else {
            while( ( hi > low ) && ( GetItemText(hi, nCol) < midItem ) )
                --hi;
        }

        // if the indexes have not crossed, swap
        // and if the items are not equal
        if( lo <= hi )
        {
            // swap only if the items are not equal
            if( GetItemText(lo, nCol) != GetItemText(hi, nCol))
            {
                // swap the rows
                LV_ITEM lvitemlo, lvitemhi;
                int nColCount =
                    ((CHeaderCtrl*)GetDlgItem(0))->GetItemCount();
                rowText.SetSize( nColCount );
                int i;
                for( i=0; i<nColCount; i++)
                    rowText[i] = GetItemText(lo, i);
                lvitemlo.mask = LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
                lvitemlo.iItem = lo;
                lvitemlo.iSubItem = 0;
                lvitemlo.stateMask = LVIS_CUT | LVIS_DROPHILITED |
                    LVIS_FOCUSED | LVIS_SELECTED |
                    LVIS_OVERLAYMASK | LVIS_STATEIMAGEMASK;
                
                lvitemhi = lvitemlo;
                lvitemhi.iItem = hi;
                
                GetItem( &lvitemlo );
                GetItem( &lvitemhi );
                
                for( i=0; i<nColCount; i++)
                    SetItemText(lo, i, GetItemText(hi, i));
                
                lvitemhi.iItem = lo;
                SetItem( &lvitemhi );
                
                for( i=0; i<nColCount; i++)
                    SetItemText(hi, i, rowText[i]);
                
                lvitemlo.iItem = hi;
                SetItem( &lvitemlo );
            }
            
            ++lo;
            --hi;
        }
    }
    
    // If the right index has not reached the left side of array
    // must now sort the left partition.
    if( low < hi )
        SortTextItems( nCol, bAscending , low, hi);
    
    // If the left index has not reached the right side of array
    // must now sort the right partition.
    if( lo < high )
        SortTextItems( nCol, bAscending , lo, high );
    
    return TRUE;
}


void ZIListCtrl::AutoSizeColumn(int iColumn)
{
    SetRedraw(TRUE);
    
    CListCtrl::SetColumnWidth(iColumn,LVSCW_AUTOSIZE);
    int wc1 = GetColumnWidth( iColumn );
    CListCtrl::SetColumnWidth(iColumn,LVSCW_AUTOSIZE_USEHEADER);
    int wc2 = GetColumnWidth( iColumn );
    int wc = __max(MINCOLWIDTH,__max( wc1,wc2 ));
    
    if( wc > MAXCOLWIDTH )
        wc = MAXCOLWIDTH;
    
    CListCtrl::SetColumnWidth( iColumn,wc );  
    SetRedraw(FALSE);
}

void ZIListCtrl::OnDestroy() 
{
    ZIListCtrl::DeleteAllItems( TRUE );
    CListCtrl::OnDestroy();
}

void ZIListCtrl::DeSelectAll()
{
    POSITION pos = GetFirstSelectedItemPosition();
    while (pos)
    {
        int nItem = GetNextSelectedItem(pos);
        SetItemState(nItem, 0, LVIS_SELECTED);
    }
}

BOOL ZIListCtrl::SetCurSel( size_t Index )
{
    if (Index < GetItemCount())
    {
        SetItemState(Index, LVIS_SELECTED, LVIS_SELECTED);
        return TRUE;
    }
    return FALSE;
}

BOOL ZIListCtrl::DeleteAllItems( BOOL DeleteImageList /*= FALSE*/ )
{
    if (DeleteImageList && ::IsWindow(GetSafeHwnd()))
    {
        CImageList  *pimagelist;

        pimagelist = GetImageList(TVSIL_NORMAL);
        if (pimagelist)
        {
            pimagelist->DeleteImageList();
            delete pimagelist;
            pimagelist = NULL;
        }
    }
    if (IsWindow(GetSafeHwnd()))
        return CListCtrl::DeleteAllItems();
    return FALSE;
}

BOOL ZIListCtrl::BuildColumns(int nCols, int * nWidth, int * nColString)
{
    //insert columns
    int i;
    LV_COLUMN lvc;

    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    CString    strTemp;
    for(i = 0; i < nCols; i++)
    {
        lvc.iSubItem = i;
        strTemp.LoadString(nColString[i]);
        lvc.pszText = strTemp.GetBuffer(0);
        strTemp.ReleaseBuffer(-1);
        lvc.cx = nWidth[i];
        lvc.fmt = LVCFMT_LEFT;
        InsertColumn(i,&lvc);
    }
    return TRUE;
}

// ie: LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP
void ZIListCtrl::SetExtendedStyle(DWORD dwNewStyle)
{
    // Returns the current extended style ( a DWORD ).
    DWORD dwStyle = ::SendMessage (m_hWnd, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);

    // Add the full row select and grid line style to the existing extended styles.
    dwStyle |= dwNewStyle;

    // Sets the current extended style ( a DWORD ).
    ::SendMessage (m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
}

int ZIListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CListCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    return InitializeFlatHeader();
}

void ZIListCtrl::PreSubclassWindow() 
{
    CListCtrl::PreSubclassWindow();
    InitializeFlatHeader();
}

int ZIListCtrl::InitializeFlatHeader()
{
    if (!m_HeaderCtrl.SubclassWindow(GetDlgItem(0)->GetSafeHwnd()))
        return -1;

    m_HeaderCtrl.FlatHeader();

    return 0;
}
