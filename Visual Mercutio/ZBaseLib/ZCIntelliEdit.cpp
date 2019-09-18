// ZCIntelliEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ZCIntelliEdit.h"

#include "ZVManageValueIntelliEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static bool gInMoveOfListBox = false;
static bool gInOnClicked = false;

/////////////////////////////////////////////////////////////////////////////
// ZIntelliEditButton class
/////////////////////////////////////////////////////////////////////////////

ZIntelliEditButton::ZIntelliEditButton()
: m_pArrayOfValues(NULL),
  m_Size(0,0),
  m_ListBoxHeight(200)
{
    NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
        sizeof(NONCLIENTMETRICS), &ncm, 0));
    m_Font.CreateFontIndirect(&ncm.lfMessageFont);
}

ZIntelliEditButton::~ZIntelliEditButton()
{
}

BEGIN_MESSAGE_MAP(ZIntelliEditButton, CButton)
    //{{AFX_MSG_MAP(ZIntelliEditButton)
    ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
    ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL ZIntelliEditButton::Create(ZCIntelliEdit* pEdit, CStringArray* pArrayOfValues, CSize* pSize /*= NULL*/)
{
    ASSERT_VALID(pEdit);
    m_pArrayOfValues = pArrayOfValues;
    if (pSize)
        m_Size = *pSize;
    m_pEdit = pEdit;
    CWnd* pWndParent = m_pEdit->GetParent();
    ASSERT_VALID(pWndParent);
    
    CRect rc;
    m_pEdit->GetWindowRect(&rc);
    m_pEdit->SetWindowPos(NULL, 0, 0, rc.Width()-23,
                         rc.Height(), SWP_NOZORDER|SWP_NOMOVE);
    pWndParent->ScreenToClient(&rc);
    rc.left = rc.right-23;

    DWORD dwStyle = WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_CENTER|BS_VCENTER;
    if (CButton::Create(_T("..."), dwStyle|BS_ICON, rc,
        pWndParent, GetNextID(pWndParent)))
    {
        SetWindowPos(m_pEdit, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
        EnableWindow(m_pEdit->IsWindowEnabled());
        SetFont(&m_Font);

        CImageList imageList;
        CBitmap    bitmap;

        bitmap.LoadBitmap(IDB_BTNARROWDWN);
        imageList.Create(15, 17, ILC_COLORDDB|ILC_MASK, 1, 1);
        imageList.Add(&bitmap, RGB(255,0,255));

        SetIcon(imageList.ExtractIcon(0));

        imageList.Detach();
        bitmap.Detach();


        CRect    rect;
        m_pEdit->GetClientRect( &rect );

        // If no size, defines the default size
        if (m_Size.cx == 0)
            m_Size.cx = __min( rect.Width(), 300 );
        if (m_Size.cy == 0)
            m_Size.cy = m_ListBoxHeight;

        // WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE
        if (!m_ListBoxOfValues.CreateEx(WS_EX_CLIENTEDGE | WS_EX_RIGHTSCROLLBAR, _T("LISTBOX"), NULL, WS_POPUP | WS_BORDER | WS_VSCROLL | LBS_SORT | WS_SIZEBOX, 
                                        0, 0, 
                                        m_Size.cx, 
                                        m_Size.cy, 
                                        m_pEdit->GetSafeHwnd(), 
                                        (HMENU)NULL))
        {
            return FALSE;
        }
        m_ListBoxOfValues.SetEditControl( m_pEdit );

        // Fill the list box
        if (!m_pArrayOfValues)
            return TRUE;
        m_ListBoxOfValues.ResetContent();
        for (size_t i = 0; i < (size_t)m_pArrayOfValues->GetSize(); ++i)
            m_ListBoxOfValues.AddString( m_pArrayOfValues->GetAt(i) );

        return TRUE;
    }

    return FALSE;
}

void ZIntelliEditButton::SetArrayOfValues( CStringArray* pArrayOfValues, bool Reload /*= true*/ )
{
    m_pArrayOfValues = pArrayOfValues;
    if (Reload)
        ReloadListOfValues();
}

void ZIntelliEditButton::ReloadListOfValues()
{
    if (!m_pArrayOfValues)
        return;
    m_ListBoxOfValues.ResetContent();
    for (size_t i = 0; i < (size_t)m_pArrayOfValues->GetSize(); ++i)
        m_ListBoxOfValues.AddString( m_pArrayOfValues->GetAt(i) );
}

void ZIntelliEditButton::OnClicked()
{
    if (gInOnClicked)
        return;

    gInOnClicked = true;

    SetState(TRUE);

    CRect rc;
    GetWindowRect(&rc);
    CWnd* pParentWnd = m_pEdit->GetParent();

    // Hide the history list of the edit
    m_pEdit->HideListBox();

    if (GetKeyState(VK_SHIFT) & 0x8000) 
    { 
        // Display the dialog used to manage entries
        ManageEntries();
    }
    else
    {
        // Then, calculate the size and the position of the window
        CalculateSizeAndPosition();
        // Show the window
        m_ListBoxOfValues.ShowWindow( (m_ListBoxOfValues.IsWindowVisible()) ? SW_HIDE: SW_SHOW );
        m_pEdit->SetFocus();
    }
    // Return the button state to normal.
    SetState(FALSE);

    gInOnClicked = false;
}

UINT ZIntelliEditButton::GetNextID(CWnd* pWnd) const
{
    for (UINT nID = 32767; nID != 1; --nID)
        if(!pWnd->GetDlgItem(nID))
            return nID;
        return -1;
}

BOOL ZIntelliEditButton::PreTranslateMessage(MSG* pMsg) 
{
//    CWnd                    *pWnd;
//    int                     hittest;

    if (pMsg->message == WM_KEYDOWN)
    {
        if (GetFocus()==this)
        {
            switch (pMsg->wParam)
            {
                case VK_ESCAPE:
                {
                    if (IsFloatingListIsVisible())
                    {
                        m_ListBoxOfValues.ShowWindow( SW_HIDE );
                        m_pEdit->SetFocus();
                        return TRUE;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    return CButton::PreTranslateMessage(pMsg);
}

void ZIntelliEditButton::CalculateSizeAndPosition()
{
    if (!::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        return;

    CRect    EditRect;
    m_pEdit->GetWindowRect( &EditRect );

    CRect LBRect;

    CRect wndRect;
    ::GetWindowRect( ::GetDesktopWindow(), &wndRect );
    // If from the left, the final window is greater than the desktop,
    // Then align the window from the right of the control
    if ((EditRect.left + 5 + m_Size.cx) > wndRect.right)
    {
        LBRect.right = EditRect.right + 5;
        LBRect.left = LBRect.right - m_Size.cx;
        LBRect.top = EditRect.bottom + 2;
        LBRect.bottom = LBRect.top + m_Size.cy;
    }
    else
    {
        LBRect.left = EditRect.left + 5;
        LBRect.right = LBRect.left + m_Size.cx;
        LBRect.top = EditRect.bottom + 2;
        LBRect.bottom = LBRect.top + m_Size.cy;
    }

    // Sets the global variable in order to avoid double resizing
    gInMoveOfListBox = true;
    m_ListBoxOfValues.MoveWindow( &LBRect, FALSE );
    gInMoveOfListBox = false;
    
}


void ZIntelliEditButton::OnEnable(BOOL bEnable) 
{
    CButton::OnEnable(bEnable);
    if (::IsWindow( m_ListBoxOfValues.GetSafeHwnd() ))
        m_ListBoxOfValues.EnableWindow(bEnable);
}

void ZIntelliEditButton::OnShowWindow(BOOL bShow, UINT nStatus) 
{
    CButton::OnShowWindow(bShow, nStatus);
    if (::IsWindow( m_ListBoxOfValues.GetSafeHwnd() ))
        m_ListBoxOfValues.ShowWindow((bShow && IsFloatingListIsVisible())?SW_SHOW:SW_HIDE);
}


void ZIntelliEditButton::ManageEntries()
{
    if (!m_pArrayOfValues)
        return;

    ZVManageValueIntelliEdit Dlg(m_pArrayOfValues);
    Dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// ZCIntelliEdit

ZCIntelliEdit::ZCIntelliEdit( CStringArray* pArrayOfValues /*= NULL*/, CSize* pSize /*= NULL*/ )
: m_pArrayOfValues(pArrayOfValues),
  m_ListBoxHeight(200),
  m_HasFocus(false),
  m_BeingResized(false),
  m_Size(0,0)
{
    if (pSize)
        m_Size = *pSize;
}

ZCIntelliEdit::~ZCIntelliEdit()
{
}

void ZCIntelliEdit::DestroyEdit()
{
    // Hide the list box of value
    m_ListBoxOfValues.ShowWindow( SW_HIDE );
}

void ZCIntelliEdit::Initialize(    CStringArray* pArrayOfValues, CSize* pSize /*= NULL*/ )
{
    if (pSize)
        m_Size = *pSize;

    m_pArrayOfValues = pArrayOfValues;
    ZCIntelliEdit::Initialize();
}

void ZCIntelliEdit::SetArrayOfValues( CStringArray* pArrayOfValues, bool Reload /*= true*/ )
{
    m_pArrayOfValues = pArrayOfValues;
    m_Button.SetArrayOfValues( pArrayOfValues, Reload );
    if (Reload)
        ReloadListOfValues();
}

#define    IDC_INTELLI_LIST_CTRL    90000

void ZCIntelliEdit::Initialize()
{
    CRect    rect;
    GetClientRect( &rect );
    // If no size, defines the default size
    if (m_Size.cx == 0)
        m_Size.cx = __min( rect.Width(), 300 );
    if (m_Size.cy == 0)
        m_Size.cy = m_ListBoxHeight;

    // WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE
    if (!m_ListBoxOfValues.CreateEx(WS_EX_CLIENTEDGE | WS_EX_RIGHTSCROLLBAR, _T("LISTBOX"), NULL, WS_POPUP | WS_BORDER | WS_VSCROLL | LBS_SORT | WS_SIZEBOX, 
                                    0, 0, 
                                    m_Size.cx, 
                                    m_Size.cy, 
                                    this->GetSafeHwnd(), 
                                    (HMENU)NULL))
    {
        return;
    }
    if (!m_Button.Create(this, m_pArrayOfValues, &m_Size)) 
    {
        TRACE0(_T("Failed to create down button.\n"));
        return;
    }
    m_ListBoxOfValues.SetEditControl( this );
    // Initialize drag & drop facilities
    PSS_DragEdit::Init();
}

void ZCIntelliEdit::OnExtendedSizeHasChanged( int cx, int cy )
{
    if (gInMoveOfListBox == false &&
        cx != 0 && cy != 0)
    {
        m_Size.cx = cx;
        m_Size.cy = cy;
        m_Button.SetListBoxSize( m_Size );
//    CalculateSizeAndPosition();
    }
}

int    ZCIntelliEdit::BuildSimilarList( CString EditText )
{
    if (!m_pArrayOfValues)
        return 0;
    m_ListBoxOfValues.ResetContent();
    if (EditText.IsEmpty())
        return 0;
    for (size_t i = 0; i < (size_t)m_pArrayOfValues->GetSize(); ++i)
    {
        if (CompareSimilar( EditText, m_pArrayOfValues->GetAt(i)))
            m_ListBoxOfValues.AddString( m_pArrayOfValues->GetAt(i) );
    }
    return m_ListBoxOfValues.GetCount();
}


bool ZCIntelliEdit::CompareSimilar( CString PartialText, CString FullText )
{
    // Run through all caracters of the partial text and should match
    // the characters of the FullText
    char    Source;
    char    Destination;
    for (size_t i = 0; i < (size_t)PartialText.GetLength(); ++i)
    {
        Source = ::toupper( PartialText.GetAt(i) );
        if (i >= (size_t)FullText.GetLength())
            return false;
        Destination = ::toupper( FullText.GetAt(i) );
        if (Source != Destination)
            return false;
    }
    return true;
}


BEGIN_MESSAGE_MAP(ZCIntelliEdit, PSS_DragEdit)
    //{{AFX_MSG_MAP(ZCIntelliEdit)
    ON_WM_KILLFOCUS()
    ON_WM_CHAR()
    ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZCIntelliEdit message handlers

void ZCIntelliEdit::OnKillFocus(CWnd* pNewWnd)
{
    PSS_DragEdit::OnKillFocus(pNewWnd);
    if (GetFocus() == this ||
        GetFocus() == &m_ListBoxOfValues ||
        GetFocus() == &m_Button ||
        GetFocus() == m_Button.GetListBoxWnd())
        m_HasFocus = true;
    else
        m_HasFocus = false;

    if (m_HasFocus == false)
    {
        if (m_Button.IsFloatingListIsVisible())
            m_Button.HideListBox();
        if (IsFloatingListIsVisible())
            HideListBox();
    }
}

BOOL ZCIntelliEdit::PreTranslateMessage(MSG* pMsg) 
{
//    CWnd                    *pWnd;
//    int                     hittest;

    if (pMsg->message == WM_KEYDOWN)
    {
        if (GetFocus()==this)
        {
            switch (pMsg->wParam)
            {
                case VK_ESCAPE:
                {
                    if (IsFloatingListIsVisible())
                    {
                        HideListBox();
                        SetFocus();
                        return TRUE;
                    }
                    else
                        if (IsHistoryFloatingListIsVisible())
                        {
                            HideHistoryListBox();
                            SetFocus();
                            return TRUE;
                        }
                    // Call the virtual call-back function
                    OnEscape();
                    break;
                }
                case VK_RETURN:
                {
                    if (IsFloatingListIsVisible())
                    {
                        HideListBox();
                        SetFocus();
                    }
                    else
                        if (IsHistoryFloatingListIsVisible())
                        {
                            HideHistoryListBox();
                            SetFocus();
                        }
                    // Call the virtual call-back function
                    OnEnter();
                    break;
                }
                case VK_UP:
                {
                    if (IsFloatingListIsVisible())
                    {
                        int    CurSel = GetListBoxCurSel();
                        if (CurSel == LB_ERR)
                            SetListBoxCurSel(0);
                        else
                            SetListBoxCurSel( CurSel - 1 );
                        // Now get the text
                        CString Text;
                        GetListBoxTextCurSel( Text );
                        if (!Text.IsEmpty())
                            SetWindowText( Text );
                        SetSel( Text.GetLength(), Text.GetLength() );
                    }
                    else
                        if (IsHistoryFloatingListIsVisible())
                        {
                            int    CurSel = GetHistoryListBoxCurSel();
                            if (CurSel == LB_ERR)
                                SetHistoryListBoxCurSel(0);
                            else
                                SetHistoryListBoxCurSel( CurSel - 1 );
                            // Now get the text
                            CString Text;
                            GetHistoryListBoxTextCurSel( Text );
                            if (!Text.IsEmpty())
                                SetWindowText( Text );
                            SetSel( Text.GetLength(), Text.GetLength() );
                        }
                    return TRUE;
                }

                case VK_DOWN:
                {
                    if (IsFloatingListIsVisible())
                    {
                        int    CurSel = GetListBoxCurSel();
                        if (CurSel == LB_ERR)
                            SetListBoxCurSel(0);
                        else
                            SetListBoxCurSel( CurSel + 1 );
                        // Now get the text
                        CString Text;
                        GetListBoxTextCurSel( Text );
                        if (!Text.IsEmpty())
                            SetWindowText( Text );
                        SetSel( Text.GetLength(), Text.GetLength() );
                        return TRUE;
                    }
                    else
                        if (IsHistoryFloatingListIsVisible())
                        {
                            int    CurSel = GetHistoryListBoxCurSel();
                            if (CurSel == LB_ERR)
                                SetHistoryListBoxCurSel(0);
                            else
                                SetHistoryListBoxCurSel( CurSel + 1 );
                            // Now get the text
                            CString Text;
                            GetHistoryListBoxTextCurSel( Text );
                            if (!Text.IsEmpty())
                                SetWindowText( Text );
                            SetSel( Text.GetLength(), Text.GetLength() );
                            return TRUE;
                        }
                }

                default:
                    break;
            }
        }
    }
    return PSS_DragEdit::PreTranslateMessage(pMsg);
}

void ZCIntelliEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    // Get the edit text before the char is typed
    CString    EditText;
    GetWindowText( EditText );

    if (ValidateChar(nChar, EditText))
    {

        PSS_DragEdit::OnChar(nChar, nRepCnt, nFlags);

        // Get the edit text after the char is typed
        EditText;
        GetWindowText( EditText );
        // For each word, try to locate similar keywords
        int    count = BuildSimilarList( EditText );
        if (count > 0)
        {
            CalculateSizeAndPosition();
            HideHistoryListBox();
            ShowListBox();
            ListBoxSelectString( EditText );
            // Set the focus to the edit control
            SetFocus();
        }
        else
        {
            HideListBox();
        }
    }
}

void ZCIntelliEdit::CalculateSizeAndPosition()
{
    if (IsFloatingListIsVisible())
        return;

    CRect    EditRect;
    GetWindowRect( &EditRect );

    CRect LBRect;

    CRect wndRect;
    ::GetWindowRect( ::GetDesktopWindow(), &wndRect );
    // If from the left, the final window is greater than the desktop,
    // Then align the window from the right of the control
    if ((EditRect.left + 5 + m_Size.cx) > wndRect.right)
    {
        LBRect.right = EditRect.right + 5;
        LBRect.left = LBRect.right - m_Size.cx;
        LBRect.top = EditRect.bottom + 2;
        LBRect.bottom = LBRect.top + m_Size.cy;
    }
    else
    {
        LBRect.left = EditRect.left + 5;
        LBRect.right = LBRect.left + m_Size.cx;
        LBRect.top = EditRect.bottom + 2;
        LBRect.bottom = LBRect.top + m_Size.cy;
    }

    // Sets the global variable in order to avoid double resizing
    gInMoveOfListBox = true;
    m_ListBoxOfValues.MoveWindow( &LBRect, FALSE );
    gInMoveOfListBox = false;
    
}




void ZCIntelliEdit::OnEnable(BOOL bEnable) 
{
    PSS_DragEdit::OnEnable(bEnable);
    if (::IsWindow( m_Button.GetSafeHwnd() ))
        m_Button.EnableWindow(bEnable);
    if (::IsWindow( m_ListBoxOfValues.GetSafeHwnd() ))
        m_ListBoxOfValues.EnableWindow(bEnable);
}

void ZCIntelliEdit::OnShowWindow(BOOL bShow, UINT nStatus) 
{
    PSS_DragEdit::OnShowWindow(bShow, nStatus);
    if (::IsWindow( m_Button.GetSafeHwnd() ))
        m_Button.ShowWindow(bShow?SW_SHOW:SW_HIDE);
    if (::IsWindow( m_ListBoxOfValues.GetSafeHwnd() ))
        m_ListBoxOfValues.ShowWindow((bShow && IsFloatingListIsVisible())?SW_SHOW:SW_HIDE);
}

void ZCIntelliEdit::PreSubclassWindow() 
{
    PSS_DragEdit::PreSubclassWindow();
}


void ZCIntelliEdit::OnSize(UINT nType, int cx, int cy) 
{
    // To avoid recursion
    if (m_BeingResized)
        return;
    PSS_DragEdit::OnSize(nType, cx, cy);

    if (!::IsWindow( m_Button.GetSafeHwnd() ))
        return;

    // Start resize controls
    m_BeingResized = true;

    CRect rc;
    GetWindowRect(&rc);
    SetWindowPos(NULL, 0, 0, rc.Width()-23,
                 rc.Height(), SWP_NOZORDER|SWP_NOMOVE);
    
    CWnd* pWndParent = GetParent();
    ASSERT_VALID(pWndParent);

    pWndParent->ScreenToClient(&rc);
    rc.left = rc.right-23;

    m_Button.MoveWindow( &rc );

    // End resize controls
    m_BeingResized = false;
}
