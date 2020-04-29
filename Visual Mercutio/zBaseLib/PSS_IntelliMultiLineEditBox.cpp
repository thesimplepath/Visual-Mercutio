/****************************************************************************
 * ==> PSS_IntelliMultiLineEditBox -----------------------------------------*
 ****************************************************************************
 * Description : Provides an intellisense multiline edit box                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_IntelliMultiLineEditBox.h"

// processsoft
#include "PSS_MultiLineEdit.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_IntelliMultiLineEditBox::IMultiLineEdit, CEdit)
    //{{AFX_MSG_MAP(PSS_IntelliMultiLineEditBox::IMultiLineEdit)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_IntelliMultiLineEditBox::IMultiLineEdit
//---------------------------------------------------------------------------
PSS_IntelliMultiLineEditBox::IMultiLineEdit::IMultiLineEdit(PSS_MultiLineEdit* pEditCtrl, PSS_IntelliMultiLineEditBox* pParent) :
    CEdit(),
    m_pParent(pParent),
    m_pEditCtrl(pEditCtrl)
{}
//---------------------------------------------------------------------------
PSS_IntelliMultiLineEditBox::IMultiLineEdit::~IMultiLineEdit()
{}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::IMultiLineEdit::SetEditControl(PSS_MultiLineEdit* pEditCtrl, PSS_IntelliMultiLineEditBox* pParent)
{
    m_pEditCtrl = pEditCtrl;

    if (pParent)
        m_pParent = pParent;
}
//---------------------------------------------------------------------------
BOOL PSS_IntelliMultiLineEditBox::IMultiLineEdit::PreTranslateMessage(MSG* pMsg)
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
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::IMultiLineEdit::TranslateSelectionToEditControl()
{
    if (m_pEditCtrl)
    {
        CString text;
        GetWindowText(text);
        m_pEditCtrl->SetWindowText(text);

        if (m_pParent)
            m_pParent->ShowWindow(SW_HIDE);

        m_pEditCtrl->SetFocus();

        // call the notification callback
        m_pEditCtrl->OnEditTextChanged();
    }
}
//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
CString near PSS_IntelliMultiLineEditBox::m_ClassName = "";
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_IntelliMultiLineEditBox, CWnd);
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_IntelliMultiLineEditBox, CWnd)
    //{{AFX_MSG_MAP(PSS_IntelliMultiLineEditBox)
    ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
    ON_WM_SIZE()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_IntelliMultiLineEditBox
//---------------------------------------------------------------------------
PSS_IntelliMultiLineEditBox::PSS_IntelliMultiLineEditBox(PSS_MultiLineEdit* pEditCtrl, CSize* pSize) :
    CWnd(),
    m_pEditCtrl(pEditCtrl),
    m_MultiLineEditBoxHeight(100)
{
    if (pSize)
        m_Size = *pSize;
}
//---------------------------------------------------------------------------
PSS_IntelliMultiLineEditBox::~PSS_IntelliMultiLineEditBox()
{}
//---------------------------------------------------------------------------
BOOL PSS_IntelliMultiLineEditBox::Create(PSS_MultiLineEdit* pEditCtrl, CSize* pSize)
{
    PSS_Assert(pEditCtrl);

    // create the bubble window but leave it invisible
    m_pEditCtrl      = pEditCtrl;
    CWnd* pWndParent = m_pEditCtrl->GetParent();
    ASSERT_VALID(pWndParent);

    if (pSize)
        m_Size = *pSize;

    // do register the class?
    if (m_ClassName == "")
    {
        // yes, register the class name
        m_ClassName = ::AfxRegisterWndClass(CS_BYTEALIGNCLIENT | CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW, 0, 0);

        // succeeded?
        if (m_ClassName == "")
            // return failed
            return 0;
    }

    CRect rect;
    m_pEditCtrl->GetClientRect(&rect);

    // if no size, defines the default one
    if (!m_Size.cx)
        m_Size.cx = rect.Width();

    if (!m_Size.cy)
        m_Size.cy = m_MultiLineEditBoxHeight;

    if (!CreateEx(0,
                  m_ClassName,
                  "",
                  WS_BORDER | WS_POPUP | WS_THICKFRAME,
                  0,
                  0,
                  m_Size.cx,
                  m_Size.cy,
                  pWndParent->GetSafeHwnd(),
                  HMENU(NULL)))
        return FALSE;


    // create the edit class
    if (!m_Edit.Create(WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL,
                       CRect(0, 0, m_Size.cx, m_Size.cy),
                       this,
                       GetNextID(this)))
        return FALSE;

    m_Edit.SetEditControl(m_pEditCtrl, this);

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::SetEditControl(PSS_MultiLineEdit* pEditCtrl, CSize* pSize)
{
    m_pEditCtrl = pEditCtrl;
    m_Edit.SetEditControl(pEditCtrl, this);

    if (pSize)
        m_Size = *pSize;
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::OnEnable(BOOL bEnable)
{
    CWnd::OnEnable(bEnable);

    if (::IsWindow(m_Edit.GetSafeHwnd()))
        m_Edit.EnableWindow(bEnable);
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CWnd::OnShowWindow(bShow, nStatus);

    if (::IsWindow(m_Edit.GetSafeHwnd()))
        m_Edit.ShowWindow((bShow) ? SW_SHOW : SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::OnSize(UINT nType, int cx, int cy)
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
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::OnKillFocus(CWnd* pNewWnd)
{}
//---------------------------------------------------------------------------
UINT PSS_IntelliMultiLineEditBox::GetNextID(CWnd* pWnd) const
{
    for (UINT id = 32767; id != 1; --id)
        if (!pWnd->GetDlgItem(id))
            return id;

    return -1;
}
//---------------------------------------------------------------------------
