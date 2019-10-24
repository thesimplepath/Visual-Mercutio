/****************************************************************************
 * ==> PSS_IntelliListBox --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an intellisense list box                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_IntelliListBox.h"

// processsoft
#include "PSS_IntelliEdit.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_IntelliListBox, CListBox)
    //{{AFX_MSG_MAP(PSS_IntelliListBox)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_IntelliListBox
//---------------------------------------------------------------------------
PSS_IntelliListBox::PSS_IntelliListBox(PSS_IntelliEdit* pEditCtrl) :
    m_pEditCtrl(pEditCtrl),
    m_CurrentSelectionOnDown(-1)
{}
//---------------------------------------------------------------------------
PSS_IntelliListBox::~PSS_IntelliListBox()
{}
//---------------------------------------------------------------------------
void PSS_IntelliListBox::SetEditControl(PSS_IntelliEdit* pEditCtrl)
{
    m_pEditCtrl = pEditCtrl;
}
//---------------------------------------------------------------------------
BOOL PSS_IntelliListBox::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
        if (GetFocus() == this)
            switch (pMsg->wParam)
            {
                case VK_ESCAPE:
                    ShowWindow(SW_HIDE);

                    if (m_pEditCtrl)
                        m_pEditCtrl->SetFocus();

                    return TRUE;

                case VK_RETURN:
                    TranslateSelectionToEditControl();
                    return TRUE;

                default:
                    break;
            }

    return CListBox::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_IntelliListBox::OnMouseMove(UINT nFlags, CPoint point)
{
    BOOL outside;
    UINT index = ItemFromPoint(point, outside);

    CListBox::OnMouseMove(nFlags, point);

    if (!outside)
        SetCurSel(index);
}
//---------------------------------------------------------------------------
void PSS_IntelliListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_CurrentSelectionOnDown = GetCurSel();
    CListBox::OnLButtonDown(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_IntelliListBox::OnLButtonUp(UINT nFlags, CPoint point)
{
    CListBox::OnLButtonUp(nFlags, point);

    const int curSel = GetCurSel();

    // check if the selection on the top is the same as on the bottom. If not, don't translate to edit control
    if (curSel != LB_ERR && curSel == m_CurrentSelectionOnDown)
        TranslateSelectionToEditControl();
}
//---------------------------------------------------------------------------
void PSS_IntelliListBox::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CListBox::OnLButtonDblClk(nFlags, point);
    TranslateSelectionToEditControl();

}
//---------------------------------------------------------------------------
void PSS_IntelliListBox::OnSize(UINT nType, int cx, int cy)
{
    CListBox::OnSize(nType, cx, cy);

    if (m_pEditCtrl)
        m_pEditCtrl->OnExtendedSizeHasChanged(cx, cy);

}
//---------------------------------------------------------------------------
void PSS_IntelliListBox::TranslateSelectionToEditControl()
{
    if (m_pEditCtrl)
    {
        const INT curSel = GetCurSel();

        if (curSel != LB_ERR)
        {
            CString text;
            GetText(curSel, text);

            m_pEditCtrl->SetWindowText(text);
            m_pEditCtrl->SetSel(text.GetLength(), text.GetLength());

            ShowWindow(SW_HIDE);

            m_pEditCtrl->SetFocus();

            // call the notification callback
            m_pEditCtrl->OnItemSelectedFromList();
        }
    }
}
//---------------------------------------------------------------------------
