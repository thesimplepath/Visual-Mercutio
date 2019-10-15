/****************************************************************************
 * ==> PSS_ListViewCombo ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a list view combobox                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ListViewCombo.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ListViewCombo, CComboBox)
    //{{AFX_MSG_MAP(PSS_ListViewCombo)
    ON_WM_CREATE()
    ON_WM_KILLFOCUS()
    ON_WM_CHAR()
    ON_WM_NCDESTROY()
    ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ListViewCombo
//---------------------------------------------------------------------------
PSS_ListViewCombo::PSS_ListViewCombo(int item, int subItem, CStringList* pItems) :
    CComboBox(),
    m_Item(item),
    m_SubItem(subItem),
    m_Escape(0)
{
    m_Items.AddTail(pItems);
}
//---------------------------------------------------------------------------
PSS_ListViewCombo::~PSS_ListViewCombo()
{}
//---------------------------------------------------------------------------
BOOL PSS_ListViewCombo::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
        if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
        {
            ::TranslateMessage(pMsg);
            ::DispatchMessage(pMsg);
            return 1;
        }

    return CComboBox::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
int PSS_ListViewCombo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CComboBox::OnCreate(lpCreateStruct) == -1)
        return -1;

    CFont* pFont = GetParent()->GetFont();
    SetFont(pFont);

    // add the items from CStringlist
    POSITION pPos = m_Items.GetHeadPosition();

    while (pPos)
        AddString(LPCTSTR(m_Items.GetNext(pPos)));

    SetFocus();
    return 0;
}
//---------------------------------------------------------------------------
void PSS_ListViewCombo::OnNcDestroy()
{
    // doing this hence it's a "modaless" component and need to cleanup itself
    CComboBox::OnNcDestroy();
    delete this;
}
//---------------------------------------------------------------------------
void PSS_ListViewCombo::OnCloseup()
{
    GetParent()->SetFocus();
}
//---------------------------------------------------------------------------
void PSS_ListViewCombo::OnKillFocus(CWnd* pNewWnd)
{
    const int index = GetCurSel();

    CComboBox::OnKillFocus(pNewWnd);

    CString str;
    GetWindowText(str);

    // send a notification to parent list view ctrl
    LV_DISPINFO lvDispinfo;
    lvDispinfo.hdr.hwndFrom    = GetParent()->m_hWnd;
    lvDispinfo.hdr.idFrom      = GetDlgCtrlID();
    lvDispinfo.hdr.code        = LVN_ENDLABELEDIT;
    lvDispinfo.item.mask       = LVIF_TEXT | LVIF_PARAM;
    lvDispinfo.item.iItem      = m_Item;
    lvDispinfo.item.iSubItem   = m_SubItem;
    lvDispinfo.item.pszText    = m_Escape ? NULL : LPTSTR(LPCTSTR(str));
    lvDispinfo.item.cchTextMax = str.GetLength();
    lvDispinfo.item.lParam     = GetItemData(GetCurSel());

    if (index != CB_ERR)
        GetParent()->GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), LPARAM(&lvDispinfo));

    PostMessage(WM_CLOSE);
}
//---------------------------------------------------------------------------
void PSS_ListViewCombo::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // need to catch the VK_ESCAPE for the notification msg
    if (nChar == VK_ESCAPE || nChar == VK_RETURN)
    {
        if (nChar == VK_ESCAPE)
            m_Escape = 1;

        GetParent()->SetFocus();
        return;
    }

    CComboBox::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_ListViewCombo::OnSize(UINT nType, int cx, int cy)
{
    CComboBox::OnSize(nType, cx, cy);
}
//---------------------------------------------------------------------------
