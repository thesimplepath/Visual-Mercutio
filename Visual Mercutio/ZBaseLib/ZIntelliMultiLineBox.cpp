// _ZCInternalMultiLineEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ZIntelliMultiLineBox.h"

// processsoft
#include "PSS_MultiLineEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(ZIntelliMultiLineBox, CWnd);

// static members
CString near     ZIntelliMultiLineBox::m_strClassName = "";

/////////////////////////////////////////////////////////////////////////////
// ZIntelliMultiLineBox

ZIntelliMultiLineBox::ZIntelliMultiLineBox(PSS_MultiLineEdit* pEditCtrl /*= NULL*/, CSize* pSize /*= NULL*/)
    : m_pEditCtrl(pEditCtrl),
    m_MultiLineEditBoxHeight(100),
    m_Size(0, 0)
{
    if (pSize)
        m_Size = *pSize;
}

ZIntelliMultiLineBox::~ZIntelliMultiLineBox()
{}


BOOL ZIntelliMultiLineBox::Create(PSS_MultiLineEdit* pEditCtrl, CSize* pSize /*= NULL*/)
{
    ASSERT(pEditCtrl);

    m_pEditCtrl = pEditCtrl;
    CWnd* pWndParent = m_pEditCtrl->GetParent();
    ASSERT_VALID(pWndParent);

    if (pSize)
        m_Size = *pSize;
    // create our bubble window but leave it invisible

    // do we need to register the class?
    if (m_strClassName == "")
    {
        // yes

        // register the class name
        m_strClassName = ::AfxRegisterWndClass(CS_BYTEALIGNCLIENT | CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW, 0, 0);

        // we're we successful?
        if (m_strClassName == "")
            return 0;  // return failed
    }

    CRect    rect;
    m_pEditCtrl->GetClientRect(&rect);

    // If no size, defines the default size
    if (m_Size.cx == 0)
        m_Size.cx = rect.Width();
    if (m_Size.cy == 0)
        m_Size.cy = m_MultiLineEditBoxHeight;

    //WS_EX_TRANSPARENT
    if (!CreateEx(0, m_strClassName, "", WS_BORDER | WS_POPUP | WS_THICKFRAME,
                  0, 0,
                  m_Size.cx,
                  m_Size.cy,
                  pWndParent->GetSafeHwnd(), (HMENU)NULL))
        return FALSE;


    // Create the edit class
    if (!m_Edit.Create(WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL,
                       CRect(0, 0, m_Size.cx, m_Size.cy),
                       this, GetNextID(this)))
    {
        return FALSE;
    }
    m_Edit.SetEditControl(m_pEditCtrl, this);

    return TRUE;
}

void ZIntelliMultiLineBox::SetEditControl(PSS_MultiLineEdit* pEditCtrl, CSize* pSize /*= NULL*/)
{
    m_pEditCtrl = pEditCtrl;
    m_Edit.SetEditControl(pEditCtrl, this);
    if (pSize)
        m_Size = *pSize;
}

UINT ZIntelliMultiLineBox::GetNextID(CWnd* pWnd) const
{
    for (UINT nID = 32767; nID != 1; --nID)
        if (!pWnd->GetDlgItem(nID))
            return nID;
    return -1;
}

void ZIntelliMultiLineBox::OnEnable(BOOL bEnable)
{
    CWnd::OnEnable(bEnable);
    if (::IsWindow(m_Edit.GetSafeHwnd()))
        m_Edit.EnableWindow(bEnable);
}

void ZIntelliMultiLineBox::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CWnd::OnShowWindow(bShow, nStatus);
    if (::IsWindow(m_Edit.GetSafeHwnd()))
        m_Edit.ShowWindow((bShow) ? SW_SHOW : SW_HIDE);
}


BEGIN_MESSAGE_MAP(ZIntelliMultiLineBox, CWnd)
    //{{AFX_MSG_MAP(ZIntelliMultiLineBox)
    ON_WM_KILLFOCUS()
    ON_WM_SIZE()
    ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIntelliMultiLineBox message handlers

void ZIntelliMultiLineBox::OnKillFocus(CWnd* pNewWnd)
{
    //    CWnd::OnKillFocus(pNewWnd);
}


void ZIntelliMultiLineBox::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_Edit.GetSafeHwnd()))
    {
        CRect rc;
        GetClientRect(&rc);

        m_Edit.MoveWindow(&rc);
    }
    if (m_pEditCtrl)
        m_pEditCtrl->OnExtendedSizeHasChanged(cx, cy);
}


/////////////////////////////////////////////////////////////////////////////
// _ZCInternalMultiLineEdit

_ZCInternalMultiLineEdit::_ZCInternalMultiLineEdit(PSS_MultiLineEdit* pEditCtrl /*= NULL*/, ZIntelliMultiLineBox* pParent /*= NULL*/)
    : m_pEditCtrl(pEditCtrl), m_pParent(pParent)
{}

_ZCInternalMultiLineEdit::~_ZCInternalMultiLineEdit()
{}

void _ZCInternalMultiLineEdit::SetEditControl(PSS_MultiLineEdit* pEditCtrl, ZIntelliMultiLineBox* pParent /*= NULL*/)
{
    m_pEditCtrl = pEditCtrl;
    if (pParent)
        m_pParent = pParent;
}

void _ZCInternalMultiLineEdit::TranslateSelectionToEditControl()
{
    if (m_pEditCtrl)
    {
        CString    Text;
        GetWindowText(Text);
        m_pEditCtrl->SetWindowText(Text);
        if (m_pParent)
            m_pParent->ShowWindow(SW_HIDE);
        m_pEditCtrl->SetFocus();
        // Call the notification call-back
        m_pEditCtrl->OnEditTextChanged();
    }
}

BEGIN_MESSAGE_MAP(_ZCInternalMultiLineEdit, CEdit)
    //{{AFX_MSG_MAP(_ZCInternalMultiLineEdit)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// _ZCInternalMultiLineEdit message handlers

BOOL _ZCInternalMultiLineEdit::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
        if (GetFocus() == this)
            switch (pMsg->wParam)
            {
                case VK_ESCAPE:
                    if (m_pParent)
                        m_pParent->ShowWindow(SW_HIDE);

                    if (m_pEditCtrl)
                        m_pEditCtrl->SetFocus();

                    return TRUE;

                case VK_RETURN:
                    TranslateSelectionToEditControl();
                    return TRUE;

                default:
                    break;
            }

    return CEdit::PreTranslateMessage(pMsg);
}
