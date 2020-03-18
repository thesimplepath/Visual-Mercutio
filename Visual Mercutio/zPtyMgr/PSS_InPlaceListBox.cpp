/****************************************************************************
 * ==> PSS_InPlaceListBox --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place list box                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InPlaceListBox.h"

// processsoft
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_KeyboardObserverMsg.h"
#include "zProperty\PSS_PropertyItem.h"
#include "ZCPropertyListCtrl.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Default_Listbox_Height 128 // 16 * 8
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InPlaceListBox::IEdit, CEdit)
    //{{AFX_MSG_MAP(PSS_InPlaceListBox::IEdit)
    ON_WM_ERASEBKGND()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InPlaceListBox::IEdit
//---------------------------------------------------------------------------
PSS_InPlaceListBox::IEdit::IEdit() :
    CEdit(),
    m_pOwnerList(NULL)
{}
//---------------------------------------------------------------------------
PSS_InPlaceListBox::IEdit::IEdit(const IEdit& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_InPlaceListBox::IEdit::~IEdit()
{}
//---------------------------------------------------------------------------
PSS_InPlaceListBox::IEdit& PSS_InPlaceListBox::IEdit::operator = (const IEdit& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceListBox::IEdit::PreTranslateMessage(MSG* pMsg)
{
    if (!pMsg)
        return CEdit::PreTranslateMessage(pMsg);

    if (pMsg->message == WM_KEYDOWN)
        switch (pMsg->wParam)
        {
            case VK_ESCAPE:
            case VK_RETURN:
            case VK_TAB:
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);

                // notify the owner list
                if (m_pOwnerList)
                    m_pOwnerList->NotifyEditKeyPressed
                            ((::GetKeyState(VK_SHIFT) & 0x80000000) ? (VK_SHIFT | pMsg->wParam) : pMsg->wParam);

                return TRUE;

            default:
                break;
        }

    return CEdit::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceListBox::IEdit::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InPlaceListBox::IListBox, CListBox)
    //{{AFX_MSG_MAP(PSS_InPlaceListBox::IListBox)
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InPlaceListBox::IListBox
//---------------------------------------------------------------------------
PSS_InPlaceListBox::IListBox::IListBox() :
    CListBox(),
    m_pOwnerList(NULL)
{}
//---------------------------------------------------------------------------
PSS_InPlaceListBox::IListBox::IListBox(const IListBox& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_InPlaceListBox::IListBox::~IListBox()
{}
//---------------------------------------------------------------------------
PSS_InPlaceListBox::IListBox& PSS_InPlaceListBox::IListBox::operator = (const IListBox& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceListBox::IListBox::PreTranslateMessage(MSG* pMsg)
{
    if (!pMsg)
        return CListBox::PreTranslateMessage(pMsg);

    if (pMsg->message == WM_KEYDOWN)
        switch (pMsg->wParam)
        {
            case VK_RETURN:
            case VK_TAB:
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);
                ProcessSelected();
                return TRUE;

            case VK_ESCAPE:
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);
                ProcessSelected(false);
                return TRUE;

            default:
                break;
        }

    return CListBox::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::IListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
    CListBox::OnLButtonDown(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::IListBox::OnLButtonUp(UINT nFlags, CPoint point)
{
    CListBox::OnLButtonUp(nFlags, point);

    CRect rect;
    GetClientRect(rect);

    if (rect.PtInRect(point))
        ProcessSelected();
    else
    {
        // check if the clicked point is above the owner
        PSS_InPlaceListBox* pOwner = dynamic_cast<PSS_InPlaceListBox*>(GetOwner());

        if (pOwner)
        {
            ClientToScreen(&point);

            if (pOwner->IsEditButtonCtrlHit(point))
            {
                // do nothing
            }
            else
            if (pOwner->IsEditCtrlHit(point))
            {
                // set the focus to the edit
                if (m_pOwnerList)
                    m_pOwnerList->NotifiyListBoxAction(WM_HIDE_LISTBOX_SETFOCUS_EDIT);
            }
            else
                // process nothing
                ProcessSelected(false);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::IListBox::ProcessSelected(bool process)
{
    ReleaseCapture();

    if (process)
    {
        // hide the listbox and apply the selection
        if (m_pOwnerList)
            m_pOwnerList->NotifiyListBoxAction(WM_HIDE_LISTBOX_APPLYSELECTION);
    }
    else
    if (m_pOwnerList)
        // hide the listbox and set the focus to the edit
        m_pOwnerList->NotifiyListBoxAction(WM_HIDE_LISTBOX_SETFOCUS_EDIT);
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_InPlaceListBox, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InPlaceListBox, CWnd)
    //{{AFX_MSG_MAP(PSS_InPlaceListBox)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
    ON_WM_SETFOCUS()
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InPlaceListBox
//---------------------------------------------------------------------------
int PSS_InPlaceListBox::m_ButtonDx = ::GetSystemMetrics(SM_CXHSCROLL);
//---------------------------------------------------------------------------
PSS_InPlaceListBox::PSS_InPlaceListBox(bool isReadOnly) :
    PSS_InPlaceEdit(CString(_T("")), isReadOnly),
    CWnd(),
    m_CurrentSelection(-1)
{}
//---------------------------------------------------------------------------
PSS_InPlaceListBox::PSS_InPlaceListBox(const PSS_InPlaceListBox& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_InPlaceListBox& PSS_InPlaceListBox::operator = (const PSS_InPlaceListBox& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceListBox::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                   const CString&    initText,
                                                   CWnd*             pWndParent,
                                                   const CRect&      rect,
                                                   DWORD             exStyle)
{
    m_pItem = pItem;

    const BOOL result = Create(NULL, _T(""), WS_VISIBLE | WS_CHILD, rect, pWndParent, 1);

    SetEditText(initText);

    // save the initial value
    m_InitialValueText = initText;

    return result;
}
//---------------------------------------------------------------------------
CString PSS_InPlaceListBox::GetEditText() const
{
    CString text;

    if (::IsWindow(m_Edit.GetSafeHwnd()))
        m_Edit.GetWindowText(text);

    return text;
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::SetEditText(const CString& strText)
{
    if (::IsWindow(m_Edit.GetSafeHwnd()))
        m_Edit.SetWindowText(strText);
}
//---------------------------------------------------------------------------
int PSS_InPlaceListBox::SetCurSel(const CString& value, bool sendSetData)
{
    const int select = m_Listbox.FindStringExact(0, value);
    return SetCurSel(select, sendSetData);
}
//---------------------------------------------------------------------------
int PSS_InPlaceListBox::SetCurSel(int select, bool sendSetData)
{
    if (select >= m_Listbox.GetCount())
        return CB_ERR;

    const int index = m_Listbox.SetCurSel(select);

    if (index != -1)
    {
        SetCurSelToEdit(select);
        m_CurrentSelection = select;

        if (sendSetData)
        {
            // notify observers about changed value
            PSS_ToolbarObserverMsg msg(WM_VALUESAVED_EDIT);
            NotifyAllObservers(&msg);
        }
    }

    return index;
}
//---------------------------------------------------------------------------
CString PSS_InPlaceListBox::GetTextData() const
{
    CString text;

    if (m_CurrentSelection != -1)
        m_Listbox.GetText(m_CurrentSelection, text);

    return text;
}
//---------------------------------------------------------------------------
int PSS_InPlaceListBox::AddString(LPCTSTR pStrText, DWORD data)
{
    const int index = m_Listbox.AddString(pStrText);

    return m_Listbox.SetItemData(index, data);
}
//---------------------------------------------------------------------------
bool PSS_InPlaceListBox::IsEditCtrlHit(const CPoint& point) const
{
    CRect rect;
    GetClientRect(rect);

    ClientToScreen(&rect);

    return rect.PtInRect(point);
}
//---------------------------------------------------------------------------
bool PSS_InPlaceListBox::IsEditButtonCtrlHit(const CPoint& point) const
{
    CRect rect;
    GetClientRect(rect);
    rect.left = rect.right - m_ButtonDx;

    ClientToScreen(&rect);

    return rect.PtInRect(point);
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::ResetListBoxHeight()
{
    CRect rect;

    GetClientRect(rect);
    rect.right -= 1;

    const int items         = m_Listbox.GetCount();
    int       listBoxHeight = items > 0 ? (items + 1) * m_ButtonDx : M_Default_Listbox_Height;

    if (listBoxHeight > M_Default_Listbox_Height)
        listBoxHeight = M_Default_Listbox_Height;

    m_Listbox.SetWindowPos(NULL, 0, 0, rect.Width(), listBoxHeight, SWP_NOZORDER | SWP_NOMOVE);
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::ResetContent()
{
    m_Listbox.ResetContent();

    m_CurrentSelection = -1;
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::CancelEdit()
{
    HideListBox();

    // restore the initial value
    SetEditText(m_InitialValueText);

    // set the focus to properties control
    SetFocus();
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::SaveValue()
{
    ApplyListBoxValueToEdit();

    ZCPropertyListCtrl* pParent = dynamic_cast<ZCPropertyListCtrl*>(GetParent());

    if (pParent)
    {
        CString proposedValue = GetEditText();

        // process the data
        if (m_pItem && pParent->CheckCurrentPropertyData(m_pItem, proposedValue))
        {
            // set the property item changed flag
            m_pItem->SetHasChanged();

            // notify the observers about the changed value
            PSS_ToolbarObserverMsg msg(WM_VALUESAVED_EDIT);
            NotifyAllObservers(&msg);
        }
        else
            // change the window text to the proposed value
            SetEditText(proposedValue);
    }

    // set the focus to properties control
    SetFocus();
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::NotifyEditKeyPressed(UINT key)
{
    switch (key)
    {
        case VK_ESCAPE:
        {
            // cancel the edit
            CancelEdit();

            // notify the observers
            PSS_KeyboardObserverMsg msg(WM_KEYPRESSED_EDIT, key);
            NotifyAllObservers(&msg);

            return;
        }

        case VK_RETURN:
        case VK_TAB:
        case (VK_SHIFT | VK_TAB):
        {
            // save the value
            SaveValue();

            // notify the observers
            PSS_KeyboardObserverMsg msg(WM_KEYPRESSED_EDIT, key);
            NotifyAllObservers(&msg);

            return;
        }

        default:
            break;
    }
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::NotifiyListBoxAction(UINT action)
{
    switch (action)
    {
        case WM_SETFOCUS_EDIT:
            SetFocusToEdit();
            break;

        case WM_HIDE_LISTBOX:
            HideListBox();
            break;

        case WM_HIDE_LISTBOX_SETFOCUS_EDIT:
            HideListBox();
            SetFocusToEdit();
            break;

        case WM_HIDE_LISTBOX_APPLYSELECTION:
            ApplyListBoxValueToEdit();
            SetFocusToEdit();
            break;
    }
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
int PSS_InPlaceListBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rect;
    GetClientRect(rect);
    rect.DeflateRect(0, 1);
    rect.right -= m_ButtonDx;

    CWnd* pParent = GetParent();
    ASSERT(pParent);

    CFont* pFont = pParent->GetFont();
    DWORD  style = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;

    if (m_IsReadOnly)
        style |= ES_READONLY;

    m_Edit.Create(style, rect, this, 2);
    m_Edit.SetOwnerListBox(this);
    m_Edit.SetFont(pFont);

    rect.right  += m_ButtonDx  - 1;
    rect.top     = rect.bottom + 2;
    rect.bottom += 100;

    ClientToScreen(rect);
    pParent = pParent->GetParent();
    pParent->ScreenToClient(rect);

    m_Listbox.Create(WS_BORDER | WS_CHILD | WS_VSCROLL, rect, pParent, 3);
    m_Listbox.SetOwnerListBox(this);
    m_Listbox.SetFont(pFont);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::OnPaint()
{
    CPaintDC dc(this);
    CRect    rect;

    GetClientRect(rect);
    rect.left = rect.right - m_ButtonDx;

    #if 1
        dc.DrawFrameControl(rect, DFC_SCROLL, m_Listbox.IsWindowVisible() ? DFCS_SCROLLDOWN | DFCS_PUSHED : DFCS_SCROLLDOWN);
    #else
        dc.DrawFrameControl(rect, DFC_SCROLL, m_Listbox.IsWindowVisible() ? DFCS_SCROLLDOWN | DFCS_PUSHED | DFCS_FLAT : DFCS_SCROLLDOWN | DFCS_FLAT);
    #endif
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceListBox::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
    CWnd::OnLButtonDown(nFlags, point);

    CRect rect;
    GetClientRect(rect);

    CRect rectButton(rect);
    rectButton.left = rectButton.right - m_ButtonDx;

    if (rectButton.PtInRect(point))
    {
        const int doAction = m_Listbox.IsWindowVisible() ? SW_HIDE : SW_SHOW;

        m_Listbox.ShowWindow(doAction);
        InvalidateRect(rectButton, FALSE);

        if (doAction == SW_SHOW)
        {
            m_Listbox.SetFocus();
            m_Listbox.SetCapture();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::OnSetFocus(CWnd* pOldWnd)
{
    CWnd::OnSetFocus(pOldWnd);

    SetFocusToEdit();
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    m_Edit.SetWindowPos(NULL, 0, 0, cx - m_ButtonDx, cy, SWP_NOZORDER | SWP_NOMOVE);
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::HideListBox()
{
    m_Listbox.ShowWindow(SW_HIDE);

    CRect rectButton;
    GetClientRect(rectButton);
    rectButton.left = rectButton.right - m_ButtonDx;

    InvalidateRect(rectButton, FALSE);

    m_Edit.SetFocus();
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::SetFocusToEdit()
{
    m_Edit.SetFocus();
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::MoveSelection(UINT key)
{
    const int items = m_Listbox.GetCount();

    if (items > 0)
    {
        switch (key)
        {
            case VK_UP:
            case (VK_SHIFT | VK_TAB):
                if (m_CurrentSelection > 0)
                    SetCurSel(m_CurrentSelection - 1);
                else
                    // revert to last element
                    SetCurSel(items - 1);

                break;

            case VK_DOWN:
            case VK_RETURN:
            case VK_TAB:
                if (m_CurrentSelection < items - 1)
                    SetCurSel(m_CurrentSelection + 1);
                else
                    // revert to first element
                    SetCurSel(0);

                break;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::SetCurSelToEdit(int select)
{
    CString text;

    if (select != -1)
        m_Listbox.GetText(select, text);

    m_Edit.SetWindowText(text);
    m_Edit.SetSel(0, -1);
}
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::ApplyListBoxValueToEdit()
{
    const int selectedItem = m_Listbox.GetCurSel();

    HideListBox();

    SetCurSelToEdit(m_CurrentSelection = selectedItem);
}
//---------------------------------------------------------------------------
