// ZCInPlaceListBox.cpp : implementation file

#include "stdafx.h"
#include "ZCInPlaceListBox.h"
#include "ZCPropertyListCtrl.h"

#include "zProperty\ZBPropertyItem.h"

#include "zBaseLib\ZBToolbarObserverMsg.h"
#include "zBaseLib\PSS_KeyboardObserverMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 5 septembre 2006 - Ajout des décorations unicode _T(), nettoyage du code inutile. (En commentaires)

#define DEFAULT_IPLISTBOX_HEIGHT 16 * 8

BEGIN_MESSAGE_MAP(_ZCInPlaceEdit, CEdit)
    //{{AFX_MSG_MAP(_ZCInPlaceEdit)
    ON_WM_ERASEBKGND()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZCInPlaceEdit::_ZCInPlaceEdit()
    : m_pOwnerList(NULL)
{}

_ZCInPlaceEdit::~_ZCInPlaceEdit()
{}

/////////////////////////////////////////////////////////////////////////////
// _ZCInPlaceEdit

BOOL _ZCInPlaceEdit::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        WPARAM nChar = pMsg->wParam;

        switch (nChar)
        {
            case VK_ESCAPE:
            case VK_RETURN:
            case VK_TAB:
            {
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);

                // Advise the owner list
                if (m_pOwnerList)
                {
                    m_pOwnerList->NotifyEditKeyPressed((GetKeyState(VK_SHIFT) & 0x80000000) ? (VK_SHIFT | nChar) : nChar);
                }

                return TRUE;
            }

            default:
            {
                break;
            }
        }
    }

    return CEdit::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// _ZCInPlaceEdit message handlers

BOOL _ZCInPlaceEdit::OnEraseBkgnd(CDC* /*pDC*/)
{
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// _ZCInPlaceListBox

BEGIN_MESSAGE_MAP(_ZCInPlaceListBox, CListBox)
    //{{AFX_MSG_MAP(_ZCInPlaceListBox)
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZCInPlaceListBox::_ZCInPlaceListBox()
    : m_pOwnerList(NULL)
{}

_ZCInPlaceListBox::~_ZCInPlaceListBox()
{}

/////////////////////////////////////////////////////////////////////////////
// _ZCInPlaceListBox message handlers

void _ZCInPlaceListBox::ProcessSelected(bool bProcess)
{
    ReleaseCapture();

    if (bProcess)
    {
        // hide the listbox and apply the selection
        if (m_pOwnerList)
        {
            m_pOwnerList->NotifiyListBoxAction(WM_HIDE_LISTBOX_APPLYSELECTION);
        }
    }
    else
    {
        // just hide the listbox and set the focus to the edit
        if (m_pOwnerList)
        {
            m_pOwnerList->NotifiyListBoxAction(WM_HIDE_LISTBOX_SETFOCUS_EDIT);
        }
    }
}

void _ZCInPlaceListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
    CListBox::OnLButtonDown(nFlags, point);
}

void _ZCInPlaceListBox::OnLButtonUp(UINT nFlags, CPoint point)
{
    CListBox::OnLButtonUp(nFlags, point);

    CRect rect;
    GetClientRect(rect);

    if (rect.PtInRect(point))
    {
        ProcessSelected();
    }
    else
    {
        // Now check if the point clicked
        // is on the owner
        CWnd* pWnd = GetOwner();

        if (pWnd && ISA(pWnd, ZCInPlaceListBox))
        {
            ClientToScreen(&point);

            if (dynamic_cast<ZCInPlaceListBox*>(pWnd)->IsEditButtonCtrlHit(point))
            {
                // Do nothing
            }
            else if (dynamic_cast<ZCInPlaceListBox*>(pWnd)->IsEditCtrlHit(point))
            {
                // set the focus to the edit
                if (m_pOwnerList)
                {
                    m_pOwnerList->NotifiyListBoxAction(WM_HIDE_LISTBOX_SETFOCUS_EDIT);
                }
            }
            else
            {
                // If not, processe nothing
                ProcessSelected(false);
            }
        }
    }
}

BOOL _ZCInPlaceListBox::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        switch (pMsg->wParam)
        {
            case VK_RETURN:
            case VK_TAB:
            {
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);
                ProcessSelected();
                return TRUE;
            }

            case VK_ESCAPE:
            {
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);
                ProcessSelected(false);
                return TRUE;
            }

            default:
            {
                break;
            }
        }
    }

    return CListBox::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceListBox

int ZCInPlaceListBox::m_nButtonDx = ::GetSystemMetrics(SM_CXHSCROLL);

IMPLEMENT_DYNAMIC(ZCInPlaceListBox, CWnd)

BEGIN_MESSAGE_MAP(ZCInPlaceListBox, CWnd)
    //{{AFX_MSG_MAP(ZCInPlaceListBox)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
    ON_WM_SETFOCUS()
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZCInPlaceListBox::ZCInPlaceListBox(bool IsReadOnly /*= false*/)
    : ZIInPlaceEdit(_T(""), IsReadOnly),
    m_nCurrentSelection(-1)
{}

void ZCInPlaceListBox::SetEditText(const CString& strText)
{
    if (::IsWindow(m_wndEdit.GetSafeHwnd()))
    {
        m_wndEdit.SetWindowText(strText);
    }
}

CString ZCInPlaceListBox::GetEditText() const
{
    CString strText;

    if (::IsWindow(m_wndEdit.GetSafeHwnd()))
    {
        m_wndEdit.GetWindowText(strText);
    }

    return strText;
}

BOOL ZCInPlaceListBox::InitializeInPlaceEditCtrl(ZBPropertyItem*    pItem,
                                                 const CString&    strInitText,
                                                 CWnd*                pWndParent,
                                                 CRect&            rect,
                                                 DWORD                exDwStyle    /*= 0"*/)
{
    m_pItem = pItem;

    BOOL rValue = Create(NULL, _T(""), WS_VISIBLE | WS_CHILD, rect, pWndParent, 1);
    SetEditText(strInitText);

    // Saves the initial value
    m_strInitialValueText = strInitText;

    return rValue;
}

bool ZCInPlaceListBox::IsEditCtrlHit(CPoint point) const
{
    CRect rect;
    GetClientRect(rect);

    ClientToScreen(&rect);

    return (rect.PtInRect(point)) ? true : false;
}

bool ZCInPlaceListBox::IsEditButtonCtrlHit(CPoint point) const
{
    CRect rect;
    GetClientRect(rect);
    rect.left = rect.right - m_nButtonDx;

    ClientToScreen(&rect);

    return (rect.PtInRect(point)) ? true : false;
}

void ZCInPlaceListBox::NotifyEditKeyPressed(UINT nChar)
{
    switch (nChar)
    {
        case VK_ESCAPE:
        {
            // First, cancel the edit
            CancelEdit();

            // Notify observers
            PSS_KeyboardObserverMsg Msg(WM_KEYPRESSED_EDIT, nChar);
            NotifyAllObservers(&Msg);

            return;
        }

        case VK_RETURN:
        case VK_TAB:
        case (VK_SHIFT | VK_TAB):
        {
            // First, save the value
            SaveValue();

            // Notify observers
            PSS_KeyboardObserverMsg Msg(WM_KEYPRESSED_EDIT, nChar);
            NotifyAllObservers(&Msg);

            return;
        }

        default:
        {
            break;
        }
    }
}

void ZCInPlaceListBox::NotifiyListBoxAction(UINT nAction)
{
    switch (nAction)
    {
        case WM_SETFOCUS_EDIT:
        {
            SetFocusToEdit();
            break;
        }

        case WM_HIDE_LISTBOX:
        {
            HideListBox();
            break;
        }

        case WM_HIDE_LISTBOX_SETFOCUS_EDIT:
        {
            HideListBox();
            SetFocusToEdit();
            break;
        }

        case WM_HIDE_LISTBOX_APPLYSELECTION:
        {
            ApplyListBoxValueToEdit();
            SetFocusToEdit();
            break;
        }
    }
}

void ZCInPlaceListBox::OnUpdate(ZISubject* pSubject, ZIObserverMsg* pMsg)
{}

/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceListBox message handlers

int ZCInPlaceListBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    CRect rect;
    GetClientRect(rect);
    rect.DeflateRect(0, 1);
    rect.right -= m_nButtonDx;

    CWnd* pParent = GetParent();
    ASSERT(pParent != NULL);

    CFont* pFont = pParent->GetFont();
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;

    if (m_IsReadOnly)
    {
        dwStyle |= ES_READONLY;
    }

    m_wndEdit.Create(dwStyle, rect, this, 2);
    m_wndEdit.SetOwnerListBox(this);
    m_wndEdit.SetFont(pFont);

    rect.right += m_nButtonDx - 1;
    rect.top = rect.bottom + 2;
    rect.bottom += 100;

    ClientToScreen(rect);
    pParent = pParent->GetParent();
    pParent->ScreenToClient(rect);

    m_wndList.Create(WS_BORDER | WS_CHILD | WS_VSCROLL, rect, pParent, 3);
    m_wndList.SetOwnerListBox(this);
    m_wndList.SetFont(pFont);

    return 0;
}

void ZCInPlaceListBox::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    m_wndEdit.SetWindowPos(NULL, 0, 0, cx - m_nButtonDx, cy, SWP_NOZORDER | SWP_NOMOVE);
}

void ZCInPlaceListBox::ResetListBoxHeight()
{
    CRect rect;

    GetClientRect(rect);
    rect.right -= 1;

    int nItems = m_wndList.GetCount();
    int nListBoxHeight = nItems > 0 ? (nItems + 1) * m_nButtonDx : DEFAULT_IPLISTBOX_HEIGHT;

    if (nListBoxHeight > DEFAULT_IPLISTBOX_HEIGHT)
    {
        nListBoxHeight = DEFAULT_IPLISTBOX_HEIGHT;
    }

    m_wndList.SetWindowPos(NULL, 0, 0, rect.Width(), nListBoxHeight, SWP_NOZORDER | SWP_NOMOVE);
}

void ZCInPlaceListBox::OnPaint()
{
    CPaintDC dc(this);

    CRect rect;

    GetClientRect(rect);
    rect.left = rect.right - m_nButtonDx;

#if 1
    dc.DrawFrameControl(rect, DFC_SCROLL, m_wndList.IsWindowVisible() ? DFCS_SCROLLDOWN | DFCS_PUSHED : DFCS_SCROLLDOWN);
#else
    dc.DrawFrameControl(rect, DFC_SCROLL, m_wndList.IsWindowVisible() ? DFCS_SCROLLDOWN | DFCS_PUSHED | DFCS_FLAT : DFCS_SCROLLDOWN | DFCS_FLAT);
#endif
}

BOOL ZCInPlaceListBox::OnEraseBkgnd(CDC* /*pDC*/)
{
    return TRUE;
}

void ZCInPlaceListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
    CWnd::OnLButtonDown(nFlags, point);

    CRect rect;
    GetClientRect(rect);

    CRect rectButton(rect);
    rectButton.left = rectButton.right - m_nButtonDx;

    if (rectButton.PtInRect(point))
    {
        int nDoAction = m_wndList.IsWindowVisible() ? SW_HIDE : SW_SHOW;

        m_wndList.ShowWindow(nDoAction);
        InvalidateRect(rectButton, FALSE);

        if (nDoAction == SW_SHOW)
        {
            m_wndList.SetFocus();
            m_wndList.SetCapture();
        }
    }
}

void ZCInPlaceListBox::OnSetFocus(CWnd* pOldWnd)
{
    CWnd::OnSetFocus(pOldWnd);

    SetFocusToEdit();
}

void ZCInPlaceListBox::SetFocusToEdit()
{
    m_wndEdit.SetFocus();
}

void ZCInPlaceListBox::ApplyListBoxValueToEdit()
{
    int nSelectedItem = m_wndList.GetCurSel();

    HideListBox();

    SetCurSelToEdit(m_nCurrentSelection = nSelectedItem);
}

void ZCInPlaceListBox::SaveValue()
{
    ApplyListBoxValueToEdit();

    if (GetParent() && ISA(GetParent(), ZCPropertyListCtrl))
    {
        CString ProposedValue = GetEditText();

        // If correct, process the data
        if (m_pItem &&
            dynamic_cast<ZCPropertyListCtrl*>(GetParent())->CheckCurrentPropertyData(m_pItem, ProposedValue))
        {
            // Set the has changed flag for the property item
            m_pItem->SetHasChanged();

            // Notify observers for value changed
            ZBToolbarObserverMsg Msg(WM_VALUESAVED_EDIT);
            NotifyAllObservers(&Msg);
        }
        else
        {
            // Change the window text to the proposed value
            SetEditText(ProposedValue);
        }
    }

    // Set the focus to properties control
    SetFocus();
}

void ZCInPlaceListBox::CancelEdit()
{
    HideListBox();

    // Set back the initial value
    SetEditText(m_strInitialValueText);

    // Set the focus to properties control
    SetFocus();
}

void ZCInPlaceListBox::MoveSelection(UINT Key)
{
    int nItems = m_wndList.GetCount();

    if (nItems > 0)
    {
        switch (Key)
        {
            case VK_UP:
            case (VK_SHIFT | VK_TAB):
            {
                if (m_nCurrentSelection > 0)
                {
                    SetCurSel(m_nCurrentSelection - 1);
                }
                else
                {
                    // Go back last element
                    SetCurSel(nItems - 1);
                }

                break;
            }

            case VK_DOWN:
            case VK_RETURN:
            case VK_TAB:
            {
                if (m_nCurrentSelection < nItems - 1)
                {
                    SetCurSel(m_nCurrentSelection + 1);
                }
                else
                {
                    // Go back first element
                    SetCurSel(0);
                }

                break;
            }
        }
    }
}

void ZCInPlaceListBox::HideListBox()
{
    m_wndList.ShowWindow(SW_HIDE);

    CRect rectButton;

    GetClientRect(rectButton);
    rectButton.left = rectButton.right - m_nButtonDx;

    InvalidateRect(rectButton, FALSE);

    m_wndEdit.SetFocus();
}

void ZCInPlaceListBox::SetCurSelToEdit(int nSelect)
{
    CString strText;

    if (nSelect != -1)
    {
        m_wndList.GetText(nSelect, strText);
    }

    m_wndEdit.SetWindowText(strText);
    m_wndEdit.SetSel(0, -1);
}

int ZCInPlaceListBox::SetCurSel(const CString Value, bool bSendSetData /*= true*/)
{
    int nSelect = m_wndList.FindStringExact(0, Value);
    return ZCInPlaceListBox::SetCurSel(nSelect, bSendSetData);
}

int ZCInPlaceListBox::SetCurSel(int nSelect, bool bSendSetData /*= true*/)
{
    if (nSelect >= m_wndList.GetCount())
    {
        return CB_ERR;
    }

    int nRet = m_wndList.SetCurSel(nSelect);

    if (nRet != -1)
    {
        SetCurSelToEdit(nSelect);
        m_nCurrentSelection = nSelect;

        if (bSendSetData)
        {
            // Notify observers for value changed
            ZBToolbarObserverMsg Msg(WM_VALUESAVED_EDIT);
            NotifyAllObservers(&Msg);
        }
    }

    return nRet;
}

CString ZCInPlaceListBox::GetTextData() const
{
    CString strText;

    if (m_nCurrentSelection != -1)
    {
        m_wndList.GetText(m_nCurrentSelection, strText);
    }

    return strText;
}

int ZCInPlaceListBox::AddString(LPCTSTR pStrText, DWORD nData)
{
    int nIndex = m_wndList.AddString(pStrText);

    return m_wndList.SetItemData(nIndex, nData);
}

void ZCInPlaceListBox::ResetContent()
{
    m_wndList.ResetContent();

    m_nCurrentSelection = -1;
}
