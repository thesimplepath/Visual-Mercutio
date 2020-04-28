/****************************************************************************
 * ==> PSS_IntelliEdit -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an intellisense edit box                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_IntelliEdit.h"

// processsoft
#include "PSS_ManageValueIntelliEditDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define IDC_INTELLI_LIST_CTRL 90000
//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static bool g_InMoveOfListBox = false;
static bool g_InOnClicked     = false;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_IntelliEditBtn, CButton)
    //{{AFX_MSG_MAP(PSS_IntelliEditBtn)
    ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
    ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_IntelliEditBtn
//---------------------------------------------------------------------------
PSS_IntelliEditBtn::PSS_IntelliEditBtn() :
    CButton(),
    m_pEdit(NULL),
    m_pArrayOfValues(NULL),
    m_Size(0, 0),
    m_ListBoxHeight(200)
{
    NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));
    m_Font.CreateFontIndirect(&ncm.lfMessageFont);
}
//---------------------------------------------------------------------------
PSS_IntelliEditBtn::~PSS_IntelliEditBtn()
{}
//---------------------------------------------------------------------------
BOOL PSS_IntelliEditBtn::Create(PSS_IntelliEdit* pEdit, CStringArray* pArrayOfValues, CSize* pSize)
{
    ASSERT_VALID(pEdit);
    m_pArrayOfValues = pArrayOfValues;

    if (pSize)
        m_Size = *pSize;

    m_pEdit = pEdit;

    CWnd* pWndParent = m_pEdit->GetParent();
    ASSERT_VALID(pWndParent);

    CRect editRect;
    m_pEdit->GetWindowRect(&editRect);
    m_pEdit->SetWindowPos(NULL, 0, 0, editRect.Width() - 23, editRect.Height(), SWP_NOZORDER | SWP_NOMOVE);
    pWndParent->ScreenToClient(&editRect);
    editRect.left = editRect.right - 23;

    const DWORD style = WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_CENTER | BS_VCENTER;

    if (CButton::Create(_T("..."), style | BS_ICON, editRect, pWndParent, GetNextID(pWndParent)))
    {
        SetWindowPos(m_pEdit, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        EnableWindow(m_pEdit->IsWindowEnabled());
        SetFont(&m_Font);

        CImageList imageList;
        CBitmap    bitmap;

        bitmap.LoadBitmap(IDB_BTNARROWDWN);
        imageList.Create(15, 17, ILC_COLORDDB | ILC_MASK, 1, 1);
        imageList.Add(&bitmap, RGB(255, 0, 255));

        SetIcon(imageList.ExtractIcon(0));

        imageList.Detach();
        bitmap.Detach();

        CRect rect;
        m_pEdit->GetClientRect(&rect);

        // if no size, define the default size
        if (!m_Size.cx)
            m_Size.cx = __min(rect.Width(), 300);

        if (!m_Size.cy)
            m_Size.cy = m_ListBoxHeight;

        if (!m_ListBoxOfValues.CreateEx(WS_EX_CLIENTEDGE | WS_EX_RIGHTSCROLLBAR,
                                        _T("LISTBOX"),
                                        NULL,
                                        WS_POPUP | WS_BORDER | WS_VSCROLL | LBS_SORT | WS_SIZEBOX,
                                        0, 0,
                                        m_Size.cx,
                                        m_Size.cy,
                                        m_pEdit->GetSafeHwnd(),
                                        HMENU(NULL)))
            return FALSE;

        m_ListBoxOfValues.SetEditControl(m_pEdit);

        // fill the list box
        if (!m_pArrayOfValues)
            return TRUE;

        m_ListBoxOfValues.ResetContent();

        const std::size_t valueCount = m_pArrayOfValues->GetSize();

        for (std::size_t i = 0; i < valueCount; ++i)
            m_ListBoxOfValues.AddString(m_pArrayOfValues->GetAt(i));

        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
UINT PSS_IntelliEditBtn::GetNextID(CWnd* pWnd) const
{
    for (UINT nID = 32767; nID != 1; --nID)
        if (!pWnd->GetDlgItem(nID))
            return nID;

    return -1;
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::SetArrayOfValues(CStringArray* pArrayOfValues, bool reload)
{
    m_pArrayOfValues = pArrayOfValues;

    if (reload)
        ReloadListOfValues();
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::ReloadListOfValues()
{
    if (!m_pArrayOfValues)
        return;

    m_ListBoxOfValues.ResetContent();

    const std::size_t valueCount = m_pArrayOfValues->GetSize();

    for (std::size_t i = 0; i < valueCount; ++i)
        m_ListBoxOfValues.AddString(m_pArrayOfValues->GetAt(i));
}
//---------------------------------------------------------------------------
BOOL PSS_IntelliEditBtn::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
        if (GetFocus() == this)
            switch (pMsg->wParam)
            {
                case VK_ESCAPE:
                    if (IsFloatingListVisible())
                    {
                        m_ListBoxOfValues.ShowWindow(SW_HIDE);
                        m_pEdit->SetFocus();
                        return TRUE;
                    }

                    break;

                default:
                    break;
            }

    return CButton::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::OnClicked()
{
    if (g_InOnClicked)
        return;

    g_InOnClicked = true;

    try
    {
        SetState(TRUE);

        CRect rect;
        GetWindowRect(&rect);

        CWnd* pParentWnd = m_pEdit->GetParent();

        // hide the edit history list
        m_pEdit->HideListBox();

        if (GetKeyState(VK_SHIFT) & 0x8000)
            // show the dialog used to manage entries
            ManageEntries();
        else
        {
            // calculate the window size and position
            CalculateSizeAndPosition();

            // show the window
            m_ListBoxOfValues.ShowWindow(m_ListBoxOfValues.IsWindowVisible() ? SW_HIDE : SW_SHOW);
            m_pEdit->SetFocus();
        }

        // return the button state to normal
        SetState(FALSE);
    }
    catch (...)
    {
        g_InOnClicked = false;
        throw;
    }

    g_InOnClicked = false;
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::OnEnable(BOOL bEnable)
{
    CButton::OnEnable(bEnable);

    if (::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        m_ListBoxOfValues.EnableWindow(bEnable);
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CButton::OnShowWindow(bShow, nStatus);

    if (::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        m_ListBoxOfValues.ShowWindow(bShow && IsFloatingListVisible() ? SW_SHOW : SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::CalculateSizeAndPosition()
{
    if (!::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        return;

    CRect editRect;
    m_pEdit->GetWindowRect(&editRect);

    CRect wndRect;
    ::GetWindowRect(::GetDesktopWindow(), &wndRect);

    CRect lbRect;

    // if the final window exceeds the desktop on the right, correct it
    if ((editRect.left + 5 + m_Size.cx) > wndRect.right)
    {
        lbRect.right  = editRect.right  + 5;
        lbRect.left   = lbRect.right    - m_Size.cx;
        lbRect.top    = editRect.bottom + 2;
        lbRect.bottom = lbRect.top      + m_Size.cy;
    }
    else
    {
        lbRect.left   = editRect.left   + 5;
        lbRect.right  = lbRect.left     + m_Size.cx;
        lbRect.top    = editRect.bottom + 2;
        lbRect.bottom = lbRect.top      + m_Size.cy;
    }

    // set the global variable in order to avoid double resizing
    g_InMoveOfListBox = true;

    try
    {
        m_ListBoxOfValues.MoveWindow(&lbRect, FALSE);
    }
    catch (...)
    {
        g_InMoveOfListBox = false;
        throw;
    }

    g_InMoveOfListBox = false;
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::ManageEntries()
{
    if (!m_pArrayOfValues)
        return;

    PSS_ManageValueIntelliEditDlg dlg(m_pArrayOfValues);
    dlg.DoModal();
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_IntelliEdit, PSS_DragEdit)
    //{{AFX_MSG_MAP(PSS_IntelliEdit)
    ON_WM_KILLFOCUS()
    ON_WM_CHAR()
    ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_IntelliEdit
//---------------------------------------------------------------------------
PSS_IntelliEdit::PSS_IntelliEdit(CStringArray* pArrayOfValues, CSize* pSize) :
    PSS_DragEdit(),
    m_pArrayOfValues(pArrayOfValues),
    m_Size(0, 0),
    m_ListBoxHeight(200),
    m_HasFocus(false),
    m_BeingResized(false)
{
    if (pSize)
        m_Size = *pSize;
}
//---------------------------------------------------------------------------
PSS_IntelliEdit::~PSS_IntelliEdit()
{}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::Initialize(CStringArray* pArrayOfValues, CSize* pSize)
{
    if (pSize)
        m_Size = *pSize;

    m_pArrayOfValues = pArrayOfValues;

    Initialize();
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::Initialize()
{
    CRect rect;
    GetClientRect(&rect);

    // if no size, defines the default size
    if (!m_Size.cx)
        m_Size.cx = __min(rect.Width(), 300);

    if (!m_Size.cy)
        m_Size.cy = m_ListBoxHeight;

    if (!m_ListBoxOfValues.CreateEx(WS_EX_CLIENTEDGE | WS_EX_RIGHTSCROLLBAR,
                                    _T("LISTBOX"),
                                    NULL,
                                    WS_POPUP | WS_BORDER | WS_VSCROLL | LBS_SORT | WS_SIZEBOX,
                                    0,
                                    0,
                                    m_Size.cx,
                                    m_Size.cy,
                                    GetSafeHwnd(),
                                    HMENU(NULL)))
        return;

    if (!m_Button.Create(this, m_pArrayOfValues, &m_Size))
    {
        TRACE0("Failed to create down button.\n");
        return;
    }

    m_ListBoxOfValues.SetEditControl(this);

    // initialize drag&drop facilities
    PSS_DragEdit::Init();
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::SetArrayOfValues(CStringArray* pArrayOfValues, bool reload)
{
    m_pArrayOfValues = pArrayOfValues;
    m_Button.SetArrayOfValues(pArrayOfValues, reload);

    if (reload)
        ReloadListOfValues();
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::OnExtendedSizeHasChanged(int cx, int cy)
{
    if (!g_InMoveOfListBox && cx && cy)
    {
        m_Size.cx = cx;
        m_Size.cy = cy;
        m_Button.SetListBoxSize(m_Size);
    }
}
//---------------------------------------------------------------------------
bool PSS_IntelliEdit::ValidateChar(UINT ch, const CString& editText) const
{
    return true;
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::OnItemSelectedFromList()
{}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::OnEnter()
{}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::OnEscape()
{}
//---------------------------------------------------------------------------
BOOL PSS_IntelliEdit::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
        if (GetFocus() == this)
            switch (pMsg->wParam)
            {
                case VK_ESCAPE:
                    if (IsFloatingListVisible())
                    {
                        HideListBox();
                        SetFocus();
                        return TRUE;
                    }
                    else
                    if (IsHistoryFloatingListVisible())
                    {
                        HideHistoryListBox();
                        SetFocus();
                        return TRUE;
                    }

                    // call the virtual call-back function
                    OnEscape();
                    break;

                case VK_RETURN:
                    if (IsFloatingListVisible())
                    {
                        HideListBox();
                        SetFocus();
                    }
                    else
                    if (IsHistoryFloatingListVisible())
                    {
                        HideHistoryListBox();
                        SetFocus();
                    }

                    // all the virtual call-back function
                    OnEnter();
                    break;

                case VK_UP:
                    if (IsFloatingListVisible())
                    {
                        const int selection = GetListBoxCurSel();

                        if (selection == LB_ERR)
                            SetListBoxCurSel(0);
                        else
                            SetListBoxCurSel(selection - 1);

                        CString text;

                        // get the text
                        GetListBoxTextCurSel(text);

                        if (!text.IsEmpty())
                            SetWindowText(text);

                        SetSel(text.GetLength(), text.GetLength());
                    }
                    else
                    if (IsHistoryFloatingListVisible())
                    {
                        const int selection = GetHistoryListBoxCurSel();

                        if (selection == LB_ERR)
                            SetHistoryListBoxCurSel(0);
                        else
                            SetHistoryListBoxCurSel(selection - 1);

                        CString text;

                        // get the text
                        GetHistoryListBoxTextCurSel(text);

                        if (!text.IsEmpty())
                            SetWindowText(text);

                        SetSel(text.GetLength(), text.GetLength());
                    }

                    return TRUE;

                case VK_DOWN:
                    if (IsFloatingListVisible())
                    {
                        const int selection = GetListBoxCurSel();

                        if (selection == LB_ERR)
                            SetListBoxCurSel(0);
                        else
                            SetListBoxCurSel(selection + 1);

                        CString text;

                        // get the text
                        GetListBoxTextCurSel(text);

                        if (!text.IsEmpty())
                            SetWindowText(text);

                        SetSel(text.GetLength(), text.GetLength());
                        return TRUE;
                    }
                    else
                    if (IsHistoryFloatingListVisible())
                    {
                        const int selection = GetHistoryListBoxCurSel();

                        if (selection == LB_ERR)
                            SetHistoryListBoxCurSel(0);
                        else
                            SetHistoryListBoxCurSel(selection + 1);

                        CString text;

                        // get the text
                        GetHistoryListBoxTextCurSel(text);

                        if (!text.IsEmpty())
                            SetWindowText(text);

                        SetSel(text.GetLength(), text.GetLength());
                        return TRUE;
                    }

                    break;

                default:
                    break;
            }

    return PSS_DragEdit::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::PreSubclassWindow()
{
    PSS_DragEdit::PreSubclassWindow();
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::OnShowWindow(BOOL bShow, UINT nStatus)
{
    PSS_DragEdit::OnShowWindow(bShow, nStatus);

    if (::IsWindow(m_Button.GetSafeHwnd()))
        m_Button.ShowWindow(bShow ? SW_SHOW : SW_HIDE);

    if (::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        m_ListBoxOfValues.ShowWindow(bShow && IsFloatingListVisible() ? SW_SHOW : SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::OnEnable(BOOL bEnable)
{
    PSS_DragEdit::OnEnable(bEnable);

    if (::IsWindow(m_Button.GetSafeHwnd()))
        m_Button.EnableWindow(bEnable);

    if (::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        m_ListBoxOfValues.EnableWindow(bEnable);
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::OnKillFocus(CWnd* pNewWnd)
{
    PSS_DragEdit::OnKillFocus(pNewWnd);

    m_HasFocus = (GetFocus() == this               ||
                  GetFocus() == &m_ListBoxOfValues ||
                  GetFocus() == &m_Button          ||
                  GetFocus() == m_Button.GetListBoxWnd());

    if (!m_HasFocus)
    {
        if (m_Button.IsFloatingListVisible())
            m_Button.HideListBox();

        if (IsFloatingListVisible())
            HideListBox();
    }
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // get the edit text before the char is typed
    CString editText;
    GetWindowText(editText);

    if (ValidateChar(nChar, editText))
    {
        PSS_DragEdit::OnChar(nChar, nRepCnt, nFlags);

        // get the edit text after the char is typed
        GetWindowText(editText);

        const int count = BuildSimilarList(editText);

        // for each word, try to locate similar keywords
        if (count > 0)
        {
            CalculateSizeAndPosition();
            HideHistoryListBox();
            ShowListBox();
            ListBoxSelectString(editText);

            // set the focus to the edit control
            SetFocus();
        }
        else
            HideListBox();
    }
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::OnSize(UINT nType, int cx, int cy)
{
    // to avoid recursion
    if (m_BeingResized)
        return;

    PSS_DragEdit::OnSize(nType, cx, cy);

    if (!::IsWindow(m_Button.GetSafeHwnd()))
        return;

    // start to resize controls
    m_BeingResized = true;

    try
    {
        CRect rect;
        GetWindowRect(&rect);
        SetWindowPos(NULL, 0, 0, rect.Width() - 23, rect.Height(), SWP_NOZORDER | SWP_NOMOVE);

        CWnd* pWndParent = GetParent();
        ASSERT_VALID(pWndParent);

        pWndParent->ScreenToClient(&rect);
        rect.left = rect.right - 23;

        m_Button.MoveWindow(&rect);
    }
    catch (...)
    {
        // end controls resize
        m_BeingResized = false;
        throw;
    }

    // end controls resize
    m_BeingResized = false;
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::DestroyEdit()
{
    // hide the value list box
    m_ListBoxOfValues.ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
int PSS_IntelliEdit::BuildSimilarList(const CString& editText)
{
    if (!m_pArrayOfValues)
        return 0;

    m_ListBoxOfValues.ResetContent();

    if (editText.IsEmpty())
        return 0;

    std::size_t valueCount = m_pArrayOfValues->GetSize();

    for (std::size_t i = 0; i < valueCount; ++i)
        if (CompareSimilar(editText, m_pArrayOfValues->GetAt(i)))
            m_ListBoxOfValues.AddString(m_pArrayOfValues->GetAt(i));

    return m_ListBoxOfValues.GetCount();
}
//---------------------------------------------------------------------------
bool PSS_IntelliEdit::CompareSimilar(const CString& partialText, const CString& fullText)
{
    char source;
    char destination;

    std::size_t strLen = partialText.GetLength();

    // iterate through all partial text chars and search if they are matching with the full text chars
    for (std::size_t i = 0; i < strLen; ++i)
    {
        source = ::toupper(partialText.GetAt(i));

        if (i >= std::size_t(fullText.GetLength()))
            return false;

        destination = ::toupper(fullText.GetAt(i));

        if (source != destination)
            return false;
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::CalculateSizeAndPosition()
{
    if (IsFloatingListVisible())
        return;

    CRect editRect;
    GetWindowRect(&editRect);

    CRect wndRect;
    ::GetWindowRect(::GetDesktopWindow(), &wndRect);

    CRect lbRect;

    // if the final window exceeds the desktop on the right, correct it
    if ((editRect.left + 5 + m_Size.cx) > wndRect.right)
    {
        lbRect.right  = editRect.right  + 5;
        lbRect.left   = lbRect.right    - m_Size.cx;
        lbRect.top    = editRect.bottom + 2;
        lbRect.bottom = lbRect.top      + m_Size.cy;
    }
    else
    {
        lbRect.left   = editRect.left   + 5;
        lbRect.right  = lbRect.left     + m_Size.cx;
        lbRect.top    = editRect.bottom + 2;
        lbRect.bottom = lbRect.top      + m_Size.cy;
    }

    // set the global variable in order to avoid double resizing
    g_InMoveOfListBox = true;

    try
    {
        m_ListBoxOfValues.MoveWindow(&lbRect, FALSE);
    }
    catch (...)
    {
        g_InMoveOfListBox = false;
        throw;
    }

    g_InMoveOfListBox = false;
}
//---------------------------------------------------------------------------
