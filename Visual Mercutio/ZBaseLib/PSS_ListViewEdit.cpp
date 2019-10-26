/****************************************************************************
 * ==> PSS_ListViewEdit ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a list view edit                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ListViewEdit.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ListViewEdit, CEdit)
    //{{AFX_MSG_MAP(PSS_ListViewEdit)
    ON_WM_KILLFOCUS()
    ON_WM_NCDESTROY()
    ON_WM_CHAR()
    ON_WM_CREATE()
    ON_WM_WINDOWPOSCHANGING()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ListViewEdit
//---------------------------------------------------------------------------
PSS_ListViewEdit::PSS_ListViewEdit(int item, int subItem, const CString& initText) :
    CEdit(),
    m_InitText(initText),
    m_Item(item),
    m_SubItem(subItem),
    m_X(0),
    m_Y(0),
    m_Escape(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ListViewEdit::~PSS_ListViewEdit()
{}
//---------------------------------------------------------------------------
BOOL PSS_ListViewEdit::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
        if (pMsg->wParam == VK_RETURN ||
            pMsg->wParam == VK_DELETE ||
            pMsg->wParam == VK_ESCAPE ||
            ::GetKeyState(VK_CONTROL))
        {
            ::TranslateMessage(pMsg);
            ::DispatchMessage(pMsg);
            return 1;
        }

    return CEdit::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
int PSS_ListViewEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CEdit::OnCreate(lpCreateStruct) == -1)
        return -1;

    CFont* pFont = GetParent()->GetFont();
    SetFont(pFont);

    SetWindowText(m_InitText);

    SetFocus();
    SetSel(0, 0);
    return 0;
}
//---------------------------------------------------------------------------
void PSS_ListViewEdit::OnKillFocus(CWnd* pNewWnd)
{
    CEdit::OnKillFocus(pNewWnd);

    CString str;
    GetWindowText(str);

    // send notification to list view parent
    LV_DISPINFO lvDispInfo;
    lvDispInfo.hdr.hwndFrom    = GetParent()->m_hWnd;
    lvDispInfo.hdr.idFrom      = GetDlgCtrlID();
    lvDispInfo.hdr.code        = LVN_ENDLABELEDIT;
    lvDispInfo.item.mask       = LVIF_TEXT;
    lvDispInfo.item.iItem      = m_Item;
    lvDispInfo.item.iSubItem   = m_SubItem;
    lvDispInfo.item.pszText    = m_Escape ? NULL : LPTSTR(LPCTSTR(str));
    lvDispInfo.item.cchTextMax = str.GetLength();
    GetParent()->GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), LPARAM(&lvDispInfo));
    DestroyWindow();
}
//---------------------------------------------------------------------------
void PSS_ListViewEdit::OnNcDestroy()
{
    CEdit::OnNcDestroy();
    delete this;
}
//---------------------------------------------------------------------------
void PSS_ListViewEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar)
    {
        case VK_ESCAPE:
            m_Escape = TRUE;
            GetParent()->SetFocus();
            return;

        case VK_RETURN:
            GetParent()->SetFocus();
            return;
    }

    CEdit::OnChar(nChar, nRepCnt, nFlags);

    // resize edit control if needed. Get text extent
    CString str;
    GetWindowText(str);

    CWindowDC dc(this);
    CFont*    pFont   = GetParent()->GetFont();
    CFont*    pFontDC = dc.SelectObject(pFont);
    CSize     size    = dc.GetTextExtent(str);
    dc.SelectObject(pFontDC);

    // add some extra buffer
    size.cx += 5;

    // get client rect
    CRect rect, rcParent;
    GetClientRect(&rect);
    GetParent()->GetClientRect(&rcParent);

    // transform rect to parent coordinates
    ClientToScreen(&rect);
    GetParent()->ScreenToClient(&rect);

    // check whether control needs to be resized, and whether there is space to grow
    if (size.cx > rect.Width())
    {
        if (size.cx + rect.left < rcParent.right)
            rect.right = rect.left + size.cx;
        else
            rect.right = rcParent.right;

        MoveWindow(&rect);
    }
}
//---------------------------------------------------------------------------
void PSS_ListViewEdit::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
    lpwndpos->x = m_X;
    lpwndpos->y = m_Y;

    CEdit::OnWindowPosChanging(lpwndpos);
}
//---------------------------------------------------------------------------
