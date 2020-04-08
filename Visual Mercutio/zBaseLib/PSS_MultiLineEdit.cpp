/****************************************************************************
 * ==> PSS_MultiLineEdit ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a multiline edit box                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_MultiLineEdit.h"

// resources
#include "zBaseLibRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define IDC_MULTILINE_EDITBOX_CTRL 90001
//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static int  g_ButtonOffsetFromBorder   = 23;
static bool g_InMoveOfMultiLineEditBox = false;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_MultiLineEditBtn, CButton)
    //{{AFX_MSG_MAP(PSS_MultiLineEditBtn)
    ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
    ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_MultiLineEditBtn
//---------------------------------------------------------------------------
PSS_MultiLineEditBtn::PSS_MultiLineEditBtn() :
    CButton(),
    m_pEdit(NULL)
{
    NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));
    m_Font.CreateFontIndirect(&ncm.lfMessageFont);
}
//---------------------------------------------------------------------------
PSS_MultiLineEditBtn::~PSS_MultiLineEditBtn()
{}
//---------------------------------------------------------------------------
BOOL PSS_MultiLineEditBtn::Create(PSS_MultiLineEdit* pEdit, CSize* pSize, bool expanded, bool resizeParent)
{
    ASSERT_VALID(pEdit);

    if (pSize)
        m_Size = *pSize;

    m_pEdit = pEdit;

    CWnd* pWndParent = m_pEdit->GetParent();
    ASSERT_VALID(pWndParent);

    CRect rect;
    m_pEdit->GetWindowRect(&rect);

    if (resizeParent)
    {
        m_pEdit->SetWindowPos(NULL, 0, 0, rect.Width() - g_ButtonOffsetFromBorder, rect.Height(), SWP_NOZORDER | SWP_NOMOVE);

        pWndParent->ScreenToClient(&rect);
        rect.left = rect.right - g_ButtonOffsetFromBorder;
    }
    else
    {
        rect.right += g_ButtonOffsetFromBorder;
        pWndParent->ScreenToClient(&rect);
        rect.left = rect.right - g_ButtonOffsetFromBorder;
    }

    const DWORD style = WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_CENTER | BS_VCENTER;

    if (CButton::Create(_T("..."), style | BS_ICON, rect, pWndParent, GetNextID(pWndParent)))
    {
        SetWindowPos(m_pEdit, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        EnableWindow(m_pEdit->IsWindowEnabled());
        SetFont(&m_Font);

        CImageList imageList;
        CBitmap    bitmap;

        if (expanded)
            bitmap.LoadBitmap(IDB_BTNSPEDITARROWDWN);
        else
            bitmap.LoadBitmap(IDB_BTNSPEDITARROWDWN1);

        imageList.Create(15, 17, ILC_COLORDDB | ILC_MASK, 1, 1);
        imageList.Add(&bitmap, RGB(255, 0, 255));

        SetIcon(imageList.ExtractIcon(0));

        imageList.Detach();
        bitmap.Detach();

        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
UINT PSS_MultiLineEditBtn::GetNextID(CWnd* pWnd) const
{
    for (UINT nID = 32767; nID != 1; --nID)
        if (!pWnd->GetDlgItem(nID))
            return nID;

    return -1;
}
//---------------------------------------------------------------------------
BOOL PSS_MultiLineEditBtn::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
        if (GetFocus() == this)
            switch (pMsg->wParam)
            {
                case VK_ESCAPE:
                    m_pEdit->HideMultiLineEditBox();
                    m_pEdit->SetFocus();
                    return TRUE;

                default:
                    break;
            }

    return CButton::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_MultiLineEditBtn::OnClicked()
{
    SetState(TRUE);

    CRect rect;
    GetWindowRect(&rect);

    CWnd* pParentWnd = m_pEdit->GetParent();

    // check the edit state and do what necessary
    if (m_pEdit->EditIsExpanded())
        m_pEdit->CollapseBaseEdit();
    else
        m_pEdit->ExpandBaseEdit();

    // reset the button state to normal
    SetState(FALSE);
}
//---------------------------------------------------------------------------
void PSS_MultiLineEditBtn::OnEnable(BOOL bEnable)
{
    CButton::OnEnable(bEnable);
}
//---------------------------------------------------------------------------
void PSS_MultiLineEditBtn::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CButton::OnShowWindow(bShow, nStatus);
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ExpandedMultiLineEdit, PSS_DragEdit)
    //{{AFX_MSG_MAP(PSS_ExpandedMultiLineEdit)
    ON_WM_KILLFOCUS()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ExpandedMultiLineEdit
//---------------------------------------------------------------------------
PSS_ExpandedMultiLineEdit::PSS_ExpandedMultiLineEdit(PSS_MultiLineEdit* pEditCtrl, const CSize& size) :
    PSS_DragEdit(),
    m_pEditCtrl(pEditCtrl),
    m_Size(0, 0),
    m_MultiLineEditBoxHeight(200),
    m_BeingResized(false)
{
    if (size.cx && size.cy)
        m_Size = size;
}
//---------------------------------------------------------------------------
PSS_ExpandedMultiLineEdit::~PSS_ExpandedMultiLineEdit()
{}
//---------------------------------------------------------------------------
BOOL PSS_ExpandedMultiLineEdit::Create(PSS_MultiLineEdit* pEditCtrl, const CSize& size)
{
    ASSERT(pEditCtrl);

    m_pEditCtrl = pEditCtrl;

    CWnd* pWndParent = m_pEditCtrl->GetParent();
    ASSERT_VALID(pWndParent);

    if (size.cx && size.cy)
        m_Size = size;

    CRect rect;
    m_pEditCtrl->GetClientRect(&rect);

    // if no size, defines a default one
    if (!m_Size.cx)
        m_Size.cx = __min(rect.Width(), 300);

    if (!m_Size.cy)
        m_Size.cy = m_MultiLineEditBoxHeight;

    if (!PSS_DragEdit::Create(WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_THICKFRAME | ES_LEFT, rect, pWndParent, 0))
    {
        TRACE0(_T("Failed to create the second edit box.\n"));
        return FALSE;
    }

    // initialize drag&drop facilities
    PSS_DragEdit::Init();

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ExpandedMultiLineEdit::SetEditControl(PSS_MultiLineEdit* pEditCtrl, const CSize& size)
{
    m_pEditCtrl = pEditCtrl;

    if (size.cx && size.cy)
        m_Size = size;
}
//---------------------------------------------------------------------------
BOOL PSS_ExpandedMultiLineEdit::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
        if (GetFocus() == this)
            switch (pMsg->wParam)
            {
                case VK_ESCAPE:
                    // call the virtual callback function
                    if (m_pEditCtrl)
                        m_pEditCtrl->OnMultiLineEditBoxEscape();

                    return TRUE;

                case VK_RETURN:
                    // call the virtual callback function
                    if (m_pEditCtrl)
                        m_pEditCtrl->OnMultiLineEditBoxEnter();

                    return TRUE;

                default:
                    break;
            }

    return PSS_DragEdit::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_ExpandedMultiLineEdit::OnKillFocus(CWnd* pNewWnd)
{
    PSS_DragEdit::OnKillFocus(pNewWnd);
}
//---------------------------------------------------------------------------
void PSS_ExpandedMultiLineEdit::OnSize(UINT nType, int cx, int cy)
{
    PSS_DragEdit::OnSize(nType, cx, cy);

    if (m_pEditCtrl)
        m_pEditCtrl->OnExtendedSizeHasChanged(cx, cy);
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_MultiLineEdit, PSS_DragEdit)
    //{{AFX_MSG_MAP(PSS_MultiLineEdit)
    ON_WM_KILLFOCUS()
    ON_WM_CHAR()
    ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_MultiLineEdit
//---------------------------------------------------------------------------
PSS_MultiLineEdit::PSS_MultiLineEdit(const CString& editValue, CSize* pSize) :
    PSS_DragEdit(),
    m_EditValue(editValue),
    m_Size(0, 0),
    m_MultiLineEditBoxHeight(200),
    m_HasFocus(false),
    m_BeingResized(false),
    m_InCreationProcess(false),
    m_EditIsExpanded(false)
{
    if (pSize)
        m_Size = *pSize;
}
//---------------------------------------------------------------------------
PSS_MultiLineEdit::~PSS_MultiLineEdit()
{}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::Initialize(const CString& editValue, CSize* pSize)
{
    if (pSize)
        m_Size = *pSize;

    m_EditValue = editValue;

    PSS_MultiLineEdit::Initialize();
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::Initialize(const CSize& size)
{
    m_Size = size;

    PSS_MultiLineEdit::Initialize();
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::Initialize()
{
    CRect rect;
    GetClientRect(&rect);

    m_InitialRect = rect;

    // if no size, defines a default one
    if (!m_Size.cx)
        m_Size.cx = __min(rect.Width(), 300);

    if (!m_Size.cy)
        m_Size.cy = m_MultiLineEditBoxHeight;

    CWnd* pParentWnd = GetParent();

    if (!pParentWnd)
        return;

    // set the flag for creation process
    m_InCreationProcess = true;

    // check if it's a child style. If yes, restrict the control size to the max parent width
    CRect parentRect;
    pParentWnd->GetClientRect(&parentRect);
    m_Size.cx = __min(parentRect.Width() - g_ButtonOffsetFromBorder, m_Size.cx);
    m_Size.cy = __min(parentRect.Height(),                           m_Size.cy);

    if (!m_ExpandedEditBox.Create(this, m_Size))
    {
        TRACE0(_T("Failed to create the second edit box.\n"));
        return;
    }

    if (!m_ExpandedButton.Create(this, &m_Size, true, true))
    {
        TRACE0(_T("Failed to create down button.\n"));
        return;
    }

    if (!m_CollapsedButton.Create(this, &m_Size, false, false))
    {
        TRACE0(_T("Failed to create down button.\n"));
        return;
    }

    m_CollapsedButton.ShowWindow(SW_HIDE);

    // initialize drag & drop facilities
    PSS_DragEdit::Init();

    // clear the flag for creation process
    m_InCreationProcess = false;
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::SetEditText(const CString& editValue, bool reload)
{
    m_EditValue = editValue;
    SetWindowText(m_EditValue);
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::ExpandBaseEdit()
{
    if (m_EditIsExpanded)
        return;

    CString text;

    // copy the text from an edit to the other
    GetWindowText(text);
    m_ExpandedEditBox.SetWindowText(text);

    int startChar;
    int endChar;

    // get the cursor position
    GetSel(startChar, endChar);

    // swap the edit control
    m_ExpandedEditBox.ShowWindow(SW_SHOW);
    m_CollapsedButton.ShowWindow(SW_SHOW);
    m_ExpandedEditBox.SetFocus();

    // set the same selection
    m_ExpandedEditBox.SetSel(startChar, endChar, TRUE);

    // resize the edit
    CalculateSizeAndPosition();

    // hide the current edit
    ShowWindow(SW_HIDE);
    m_ExpandedButton.ShowWindow(SW_HIDE);

    m_EditIsExpanded = true;
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::CollapseBaseEdit(bool copyTextBack)
{
    if (!m_EditIsExpanded)
        return;

    int startChar;
    int endChar;

    if (copyTextBack)
    {
        CString previousText;

        // get the previous text
        GetWindowText(previousText);

        CString text;

        // copy the text from an edit to the other
        m_ExpandedEditBox.GetWindowText(text);
        SetWindowText(text);

        // get the cursor position
        m_ExpandedEditBox.GetSel(startChar, endChar);

        // if the new text is different
        if (previousText != text)
            // callback to notify the text change
            OnEditTextChanged();
    }

    // swap the edit control
    m_ExpandedEditBox.ShowWindow(SW_HIDE);
    m_CollapsedButton.ShowWindow(SW_HIDE);

    ShowWindow(SW_SHOW);
    m_ExpandedButton.ShowWindow(SW_SHOW);
    SetFocus();

    m_EditIsExpanded = false;

    if (copyTextBack)
        // set the same selection
        SetSel(startChar, endChar, TRUE);
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::OnExtendedSizeHasChanged(int cx, int cy)
{
    // check if not in the creation process
    if (m_InCreationProcess == false && cx && cy)
    {
        m_Size.cx = cx;
        m_Size.cy = cy;
    }
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::OnMultiLineEditBoxEnter()
{
    CollapseBaseEdit();
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::OnMultiLineEditBoxEscape()
{
    // don't copy the text
    CollapseBaseEdit(false);
}
//---------------------------------------------------------------------------
bool PSS_MultiLineEdit::ValidateChar(UINT ch, const CString& editText) const
{
    return true;
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::OnEditTextChanged()
{}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::OnEnter()
{}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::OnEscape()
{}
//---------------------------------------------------------------------------
BOOL PSS_MultiLineEdit::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
        if (GetFocus() == this)
            switch (pMsg->wParam)
            {
                case VK_ESCAPE: OnEscape(); break;
                case VK_RETURN: OnEnter();  break;
                default:                    break;
            }

    return PSS_DragEdit::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::PreSubclassWindow()
{
    PSS_DragEdit::PreSubclassWindow();
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::OnShowWindow(BOOL bShow, UINT nStatus)
{
    PSS_DragEdit::OnShowWindow(bShow, nStatus);
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::OnEnable(BOOL bEnable)
{
    PSS_DragEdit::OnEnable(bEnable);

    if (EditIsExpanded())
    {
        if (::IsWindow(m_CollapsedButton.GetSafeHwnd()))
            m_CollapsedButton.EnableWindow(bEnable);
    }
    else
    if (::IsWindow(m_ExpandedButton.GetSafeHwnd()))
        m_ExpandedButton.EnableWindow(bEnable);
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::OnKillFocus(CWnd* pNewWnd)
{
    PSS_DragEdit::OnKillFocus(pNewWnd);
 
    m_HasFocus = (GetFocus() == this               ||
                  GetFocus() == &m_ExpandedEditBox ||
                  GetFocus() == &m_ExpandedButton  ||
                  GetFocus() == &m_CollapsedButton);

    if (!m_HasFocus)
        HideMultiLineEditBox();
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    CString editText;

    // get the edit text before the char is typed
    GetWindowText(editText);

    if (ValidateChar(nChar, editText))
        PSS_DragEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::OnSize(UINT nType, int cx, int cy)
{
    // to avoid recursion
    if (m_BeingResized)
        return;

    PSS_DragEdit::OnSize(nType, cx, cy);

    if (EditIsExpanded())
    {
        if (!::IsWindow(m_CollapsedButton.GetSafeHwnd()))
            return;
    }
    else
    if (!::IsWindow(m_ExpandedButton.GetSafeHwnd()))
        return;

    // start to resize controls
    m_BeingResized = true;

    try
    {
        CRect rect;
        GetWindowRect(&rect);

        CWnd* pWndParent = GetParent();
        ASSERT_VALID(pWndParent);

        pWndParent->ScreenToClient(&rect);
        rect.left = rect.right - 23;

        if (EditIsExpanded())
            m_CollapsedButton.MoveWindow(&rect);
        else
            m_ExpandedButton.MoveWindow(&rect);
    }
    catch (...)
    {
        // resize control end
        m_BeingResized = false;
        throw;
    }

    // resize control end
    m_BeingResized = false;
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::SetNewStyle(long lStyleMask, BOOL bSetBits)
{
    long oldStyle = GetWindowLong(m_hWnd, GWL_STYLE) & ~lStyleMask;

    if (bSetBits)
        oldStyle |= lStyleMask;

    ::SetWindowLong(m_hWnd, GWL_STYLE, oldStyle);
    SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::DestroyEdit()
{
    // hide the value listbox
    HideMultiLineEditBox();
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::CalculateSizeAndPosition()
{
    CWnd* pParentWnd = GetParent();

    if (!pParentWnd)
        return;

    CRect editRect;
    GetWindowRect(&editRect);

    CRect wndRect;
    pParentWnd->GetWindowRect(&wndRect);

    CRect lbRect;

    // if the final window exceeds the desktop on the right, correct it
    if ((editRect.left + 8 + m_Size.cx) > wndRect.right)
    {
        editRect.right -= 8;
        editRect.left   = editRect.right - m_Size.cx;
        editRect.bottom = editRect.top   + m_Size.cy;
    }
    else
    {
        editRect.left  -= 8;
        editRect.right  = editRect.left + m_Size.cx;
        editRect.bottom = editRect.top  + m_Size.cy;
    }

    // set the global variable in order to avoid double resizing
    g_InMoveOfMultiLineEditBox = true;

    try
    {
        pParentWnd->ScreenToClient(&editRect);
        m_ExpandedEditBox.SetWindowPos(NULL, editRect.left, editRect.top, editRect.Width(), editRect.Height(), SWP_NOZORDER);
    }
    catch (...)
    {
        g_InMoveOfMultiLineEditBox = false;
        throw;
    }

    g_InMoveOfMultiLineEditBox = false;
}
//---------------------------------------------------------------------------
