// ZCMultiLineEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ZCMultiLineEdit.h"

#include "zBaseLibRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	IDC_MULTILINE_EDITBOX_CTRL	90001

static bool gInMoveOfMultiLineEditBox = false;
static int gButtonOffsetFromBorder = 23;



/////////////////////////////////////////////////////////////////////////////
// ZMultiLineEditButton class
/////////////////////////////////////////////////////////////////////////////

ZMultiLineEditButton::ZMultiLineEditButton()
: m_Size(0,0)
{
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
		sizeof(NONCLIENTMETRICS), &ncm, 0));
	m_Font.CreateFontIndirect(&ncm.lfMessageFont);
}

ZMultiLineEditButton::~ZMultiLineEditButton()
{
}

BEGIN_MESSAGE_MAP(ZMultiLineEditButton, CButton)
	//{{AFX_MSG_MAP(ZMultiLineEditButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_ENABLE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL ZMultiLineEditButton::Create(ZCMultiLineEdit* pEdit, CSize* pSize /*= NULL*/, bool Expanded /*= true*/, bool ResizeParent /*= true*/)
{
	ASSERT_VALID(pEdit);
	if (pSize)
		m_Size = *pSize;
	m_pEdit = pEdit;
	CWnd* pWndParent = m_pEdit->GetParent();
	ASSERT_VALID(pWndParent);
	
	CRect rc;
	m_pEdit->GetWindowRect(&rc);
	if (ResizeParent)
	{
		m_pEdit->SetWindowPos(NULL, 0, 0, rc.Width()-gButtonOffsetFromBorder,
							  rc.Height(), SWP_NOZORDER|SWP_NOMOVE);

		pWndParent->ScreenToClient(&rc);
		rc.left = rc.right-gButtonOffsetFromBorder;
	}
	else
	{
		rc.right += gButtonOffsetFromBorder;
		pWndParent->ScreenToClient(&rc);
		rc.left = rc.right-gButtonOffsetFromBorder;
	}
	DWORD dwStyle = WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_CENTER|BS_VCENTER;
	if (CButton::Create(_T("..."), dwStyle|BS_ICON, rc,
		pWndParent, GetNextID(pWndParent)))
	{
		SetWindowPos(m_pEdit, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
		EnableWindow(m_pEdit->IsWindowEnabled());
		SetFont(&m_Font);

		CImageList imageList;
		CBitmap    bitmap;

		if (Expanded)
			bitmap.LoadBitmap(IDB_BTNSPEDITARROWDWN);
		else
			bitmap.LoadBitmap(IDB_BTNSPEDITARROWDWN1);
		imageList.Create(15, 17, ILC_COLORDDB|ILC_MASK, 1, 1);
		imageList.Add(&bitmap, RGB(255,0,255));

		SetIcon(imageList.ExtractIcon(0));

		imageList.Detach();
		bitmap.Detach();


		CRect	rect;
		m_pEdit->GetClientRect( &rect );



		return TRUE;
	}

	return FALSE;
}

void ZMultiLineEditButton::OnClicked()
{
	SetState(TRUE);

	CRect rc;
	GetWindowRect(&rc);
	CWnd* pParentWnd = m_pEdit->GetParent();

	// Test the edit state and do what necessary
	if (m_pEdit->EditIsExpanded())
		m_pEdit->CollapseBaseEdit();
	else
		m_pEdit->ExpandBaseEdit();
	// Return the button state to normal.
	SetState(FALSE);
}

UINT ZMultiLineEditButton::GetNextID(CWnd* pWnd) const
{
	for (UINT nID = 32767; nID != 1; --nID)
		if(!pWnd->GetDlgItem(nID))
			return nID;
		return -1;
}

BOOL ZMultiLineEditButton::PreTranslateMessage(MSG* pMsg) 
{
//	CWnd                    *pWnd;
//	int                     hittest;

	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetFocus()==this)
		{
			switch (pMsg->wParam)
			{
				case VK_ESCAPE:
				{
					m_pEdit->HideMultiLineEditBox();
					m_pEdit->SetFocus();
					return TRUE;
					break;
				}
				default:
					break;
			}
		}
	}
	return CButton::PreTranslateMessage(pMsg);
}



void ZMultiLineEditButton::OnEnable(BOOL bEnable) 
{
	CButton::OnEnable(bEnable);
}

void ZMultiLineEditButton::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CButton::OnShowWindow(bShow, nStatus);
}


/////////////////////////////////////////////////////////////////////////////
// _ZCExpandedMultiLineEdit window

_ZCExpandedMultiLineEdit::_ZCExpandedMultiLineEdit( ZCMultiLineEdit* pEditCtrl /*= NULL*/, CSize Size /*= CSize(0,0)*/ )
: m_pEditCtrl(pEditCtrl),
  m_MultiLineEditBoxHeight(200),
  m_Size(0,0)
{
	if (Size.cx != 0 && Size.cy != 0)
		m_Size = Size;
}

_ZCExpandedMultiLineEdit::~_ZCExpandedMultiLineEdit()
{
}

BOOL _ZCExpandedMultiLineEdit::Create( ZCMultiLineEdit* pEditCtrl, CSize Size /*= CSize(0,0)*/ )
{
	ASSERT( pEditCtrl );

	m_pEditCtrl = pEditCtrl;
	CWnd* pWndParent = m_pEditCtrl->GetParent();
	ASSERT_VALID(pWndParent);

	if (Size.cx != 0 && Size.cy != 0)
		m_Size = Size;

	CRect	rect;
	m_pEditCtrl->GetClientRect( &rect );

	// If no size, defines the default size
	if (m_Size.cx == 0)
		m_Size.cx = __min( rect.Width(), 300 );
	if (m_Size.cy == 0)
		m_Size.cy = m_MultiLineEditBoxHeight;

	if (!ZBDragEdit::Create(WS_CHILD|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL|WS_THICKFRAME|ES_LEFT, rect, pWndParent, 0))
	{
		TRACE0(_T("Failed to create the second edit box.\n"));
		return FALSE;
	}
	// Initialize drag & drop facilities
	ZBDragEdit::Init();

	return TRUE;
}

void _ZCExpandedMultiLineEdit::SetEditControl( ZCMultiLineEdit* pEditCtrl, CSize Size /*= CSize(0,0)*/ )
{
	m_pEditCtrl = pEditCtrl;
	if (Size.cx != 0 && Size.cy != 0)
		m_Size = Size;
}

BEGIN_MESSAGE_MAP(_ZCExpandedMultiLineEdit, ZBDragEdit)
	//{{AFX_MSG_MAP(_ZCExpandedMultiLineEdit)
	ON_WM_KILLFOCUS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZCMultiLineEdit message handlers

void _ZCExpandedMultiLineEdit::OnKillFocus(CWnd* pNewWnd)
{
	ZBDragEdit::OnKillFocus(pNewWnd);
}

void _ZCExpandedMultiLineEdit::OnSize(UINT nType, int cx, int cy) 
{
	ZBDragEdit::OnSize(nType, cx, cy);

	if (m_pEditCtrl)
		m_pEditCtrl->OnExtendedSizeHasChanged( cx,cy );
}

BOOL _ZCExpandedMultiLineEdit::PreTranslateMessage(MSG* pMsg) 
{
//	CWnd                    *pWnd;
//	int                     hittest;

	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetFocus()==this)
		{
			switch (pMsg->wParam)
			{
				case VK_ESCAPE:
				{
					// Call the virtual call-back function
					if (m_pEditCtrl)
						m_pEditCtrl->OnMultiLineEditBoxEscape();
					return TRUE;
				}
				case VK_RETURN:
				{
					// Call the virtual call-back function
					if (m_pEditCtrl)
						m_pEditCtrl->OnMultiLineEditBoxEnter();
					return TRUE;
				}
				default:
					break;
			}
		}
	}
	return ZBDragEdit::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// ZCMultiLineEdit

ZCMultiLineEdit::ZCMultiLineEdit( CString EditValue /*= ""*/, CSize* pSize /*= NULL*/ )
: m_EditValue(EditValue),
  m_MultiLineEditBoxHeight(200),
  m_HasFocus(false),
  m_BeingResized(false),
  m_InCreationProcess(false),
  m_EditIsExpanded(false),
  m_Size(0,0)
{
	if (pSize)
		m_Size = *pSize;
}

ZCMultiLineEdit::~ZCMultiLineEdit()
{
}

void ZCMultiLineEdit::DestroyEdit()
{
	// Hide the list box of value
	HideMultiLineEditBox();
}

void ZCMultiLineEdit::Initialize( CString EditValue, CSize* pSize /*= NULL*/ )
{
	if (pSize)
		m_Size = *pSize;

	m_EditValue = EditValue;
	ZCMultiLineEdit::Initialize();
}

void ZCMultiLineEdit::Initialize( CSize Size )
{
	m_Size = Size;

	ZCMultiLineEdit::Initialize();
}

void ZCMultiLineEdit::SetEditText( CString EditValue, bool Reload /*= true*/ )
{
	m_EditValue = EditValue;
	SetWindowText( m_EditValue );
/*
	if (Reload)
		SetMultiLineEditBoxText( EditValue );
*/
}


void ZCMultiLineEdit::Initialize()
{
	CRect	rect;
	GetClientRect( &rect );
	m_InitialRect = rect;

	// If no size, defines the default size
	if (m_Size.cx == 0)
		m_Size.cx = __min( rect.Width(), 300 );
	if (m_Size.cy == 0)
		m_Size.cy = m_MultiLineEditBoxHeight;

	CWnd* pParentWnd = GetParent();
	if (!pParentWnd)
		return;

	// Sets the flag for creation process
	m_InCreationProcess = true;

	// Check if the style is child. If it is the case,
	// Restrict the size of the crontrol to the max	width of the parent
	CRect	ParentRect;
	pParentWnd->GetClientRect( &ParentRect );
	m_Size.cx = __min ((ParentRect.Width()-gButtonOffsetFromBorder), m_Size.cx);
	m_Size.cy = __min (ParentRect.Height(), m_Size.cy);

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
	m_CollapsedButton.ShowWindow( SW_HIDE );
	// Initialize drag & drop facilities
	ZBDragEdit::Init();

	// Clear the flag for creation process
	m_InCreationProcess = false;

}

void ZCMultiLineEdit::OnExtendedSizeHasChanged( int cx, int cy )
{
	// Check if we are not in the creation process.
	if (m_InCreationProcess == false && 
		cx != 0 && cy != 0)
	{
		m_Size.cx = cx;
		m_Size.cy = cy;
	}
}

void ZCMultiLineEdit::OnMultiLineEditBoxEnter()
{
	CollapseBaseEdit();
}

void ZCMultiLineEdit::OnMultiLineEditBoxEscape()
{
	// Don't copy the text
	CollapseBaseEdit( false );
}

BEGIN_MESSAGE_MAP(ZCMultiLineEdit, ZBDragEdit)
	//{{AFX_MSG_MAP(ZCMultiLineEdit)
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_WM_ENABLE()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZCMultiLineEdit message handlers

void ZCMultiLineEdit::OnKillFocus(CWnd* pNewWnd)
{
	ZBDragEdit::OnKillFocus(pNewWnd);
	if (GetFocus() == this ||
		GetFocus() == &m_ExpandedEditBox ||
		GetFocus() == &m_ExpandedButton ||
		GetFocus() == &m_CollapsedButton)
		m_HasFocus = true;
	else
		m_HasFocus = false;

	if (m_HasFocus == false)
	{
		HideMultiLineEditBox();
	}
}

BOOL ZCMultiLineEdit::PreTranslateMessage(MSG* pMsg) 
{
//	CWnd                    *pWnd;
//	int                     hittest;

	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetFocus()==this)
		{
			switch (pMsg->wParam)
			{
				case VK_ESCAPE:
				{
					// Call the virtual call-back function
					OnEscape();
					break;
				}
				case VK_RETURN:
				{
					// Call the virtual call-back function
					OnEnter();
					break;
				}
				default:
					break;
			}
		}
	}
	return ZBDragEdit::PreTranslateMessage(pMsg);
}

void ZCMultiLineEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// Get the edit text before the char is typed
	CString	EditText;
	GetWindowText( EditText );

	if (ValidateChar(nChar, EditText))
	{

		ZBDragEdit::OnChar(nChar, nRepCnt, nFlags);

	}
}

void ZCMultiLineEdit::SetNewStyle(long lStyleMask, BOOL bSetBits)
{
	long        lStyleOld;

	lStyleOld = GetWindowLong(m_hWnd, GWL_STYLE);
	lStyleOld &= ~lStyleMask;
	if (bSetBits)
		lStyleOld |= lStyleMask;

	SetWindowLong(m_hWnd, GWL_STYLE, lStyleOld);
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
}


void ZCMultiLineEdit::ExpandBaseEdit()
{
	if (m_EditIsExpanded)
		return;

	// Copy the text from one edit to the other
	CString Text;
	GetWindowText( Text );
	m_ExpandedEditBox.SetWindowText( Text );
	// Retreive the cursor position
	int nStartChar;
	int nEndChar;
	GetSel( nStartChar, nEndChar );
	// Swap the edit control
	m_ExpandedEditBox.ShowWindow( SW_SHOW );
	m_CollapsedButton.ShowWindow( SW_SHOW );
	m_ExpandedEditBox.SetFocus();
	// Set the same selection
	m_ExpandedEditBox.SetSel( nStartChar, nEndChar, TRUE );
	// Resize the edit to the 
	CalculateSizeAndPosition();
	
	// Now hide the current edit
	ShowWindow( SW_HIDE );
	m_ExpandedButton.ShowWindow( SW_HIDE );

	m_EditIsExpanded = true;
}

void ZCMultiLineEdit::CollapseBaseEdit( bool CopyTextBack /*= true*/ )
{
	if (!m_EditIsExpanded)
		return;

	int nStartChar;
	int nEndChar;
	if (CopyTextBack)
	{
		CString PreviousText;
		// Retreive the previous text
		GetWindowText( PreviousText );
		// Copy the text from one edit to the other
		CString Text;
		m_ExpandedEditBox.GetWindowText( Text );
		SetWindowText( Text );

		// Retreive the cursor position
		m_ExpandedEditBox.GetSel( nStartChar, nEndChar );

		// If the new text is different
		if (PreviousText != Text)
			// Call-back to notify on text change
			OnEditTextChanged();
	}
	// Swap the edit control
	m_ExpandedEditBox.ShowWindow( SW_HIDE );
	m_CollapsedButton.ShowWindow( SW_HIDE );

	ShowWindow( SW_SHOW );
	m_ExpandedButton.ShowWindow( SW_SHOW );
	SetFocus();

	m_EditIsExpanded = false;

	if (CopyTextBack)
	{
		// Set the same selection
		SetSel( nStartChar, nEndChar, TRUE );
	}
}


void ZCMultiLineEdit::CalculateSizeAndPosition()
{
//	if (IsMultiLineEditBoxVisible())
//		return;

	CWnd* pParentWnd = GetParent();
	if (!pParentWnd)
		return;

	CRect	EditRect;
	GetWindowRect( &EditRect );

	CRect LBRect;

	CRect wndRect;
	pParentWnd->GetWindowRect( &wndRect );
	// If from the left, the final window is greater than the desktop,
	// Then align the window from the right of the control
	if ((EditRect.left + 8 + m_Size.cx) > wndRect.right)
	{
		EditRect.right -= 8;
		EditRect.left = EditRect.right - m_Size.cx;
//		LBRect.top = EditRect.bottom + 2;
		EditRect.bottom = EditRect.top + m_Size.cy;
	}
	else
	{
		EditRect.left -= 8;
		EditRect.right = EditRect.left + m_Size.cx;
//		LBRect.top = EditRect.bottom + 2;
		EditRect.bottom = EditRect.top + m_Size.cy;
	}

	// Sets the global variable in order to avoid double resizing
	gInMoveOfMultiLineEditBox = true;
	//m_MultiLineEditBox.
	pParentWnd->ScreenToClient( &EditRect );
//	pParentWnd->MapWindowPoints( this, &EditRect );
	m_ExpandedEditBox.SetWindowPos(	NULL, EditRect.left, EditRect.top, 
									EditRect.Width(), EditRect.Height(), 
									SWP_NOZORDER );
	gInMoveOfMultiLineEditBox = false;
	
}




void ZCMultiLineEdit::OnEnable(BOOL bEnable) 
{
	ZBDragEdit::OnEnable(bEnable);
	if (EditIsExpanded())
	{
		if (::IsWindow( m_CollapsedButton.GetSafeHwnd() ))
			m_CollapsedButton.EnableWindow(bEnable);
	}
	else
	{
		if (::IsWindow( m_ExpandedButton.GetSafeHwnd() ))
			m_ExpandedButton.EnableWindow(bEnable);
	}
}

void ZCMultiLineEdit::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	ZBDragEdit::OnShowWindow(bShow, nStatus);
/*
	if (EditIsExpanded())
	{
		if (::IsWindow( m_ExpandedButton.GetSafeHwnd() ))
			m_ExpandedButton.ShowWindow(bShow?SW_SHOW:SW_HIDE);
	}
	else
	{
		if (::IsWindow( m_CollapsedButton.GetSafeHwnd() ))
			m_CollapsedButton.ShowWindow(bShow?SW_SHOW:SW_HIDE);
	}
*/
}

void ZCMultiLineEdit::PreSubclassWindow() 
{
	ZBDragEdit::PreSubclassWindow();
}


void ZCMultiLineEdit::OnSize(UINT nType, int cx, int cy) 
{
	// To avoid recursion
	if (m_BeingResized)
		return;
	ZBDragEdit::OnSize(nType, cx, cy);

	if (EditIsExpanded())
	{
		if (!::IsWindow( m_CollapsedButton.GetSafeHwnd() ))
			return;
	}
	else
	{
		if (!::IsWindow( m_ExpandedButton.GetSafeHwnd() ))
			return;
	}
	// Start resize controls
	m_BeingResized = true;

	CRect rc;
	GetWindowRect(&rc);
//	SetWindowPos(NULL, 0, 0, rc.Width()-23,
//				 rc.Height(), SWP_NOZORDER|SWP_NOMOVE);
	
	CWnd* pWndParent = GetParent();
	ASSERT_VALID(pWndParent);

	pWndParent->ScreenToClient(&rc);
	rc.left = rc.right-23;

	if (EditIsExpanded())
		m_CollapsedButton.MoveWindow( &rc );
	else
		m_ExpandedButton.MoveWindow( &rc );
	// End resize controls
	m_BeingResized = false;
}
