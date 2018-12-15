// ZIntelliListBox.cpp : implementation file
//

#include "stdafx.h"
#include "ZIntelliListBox.h"

#include "ZCIntelliEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIntelliListBox

ZIntelliListBox::ZIntelliListBox(ZCIntelliEdit* pEditCtrl /*= NULL*/)
: m_pEditCtrl(pEditCtrl), m_CurrentSelectionOnDown(-1)
{
}

ZIntelliListBox::~ZIntelliListBox()
{
}

void ZIntelliListBox::SetEditControl( ZCIntelliEdit* pEditCtrl )
{
    m_pEditCtrl = pEditCtrl;
}

void ZIntelliListBox::TranslateSelectionToEditControl()
{
    if (m_pEditCtrl)
    {
        INT    CurSel = GetCurSel();
        if (CurSel != LB_ERR)
        {
            CString    Text;
            GetText( CurSel, Text );
            m_pEditCtrl->SetWindowText( Text );
            m_pEditCtrl->SetSel( Text.GetLength(), Text.GetLength() );
            ShowWindow( SW_HIDE );
            m_pEditCtrl->SetFocus();
            // Call the notification call-back
            m_pEditCtrl->OnItemSelectedFromList();
        }
    }
}

BEGIN_MESSAGE_MAP(ZIntelliListBox, CListBox)
    //{{AFX_MSG_MAP(ZIntelliListBox)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIntelliListBox message handlers

BOOL ZIntelliListBox::PreTranslateMessage(MSG* pMsg) 
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
                    ShowWindow( SW_HIDE );
                    if (m_pEditCtrl)
                        m_pEditCtrl->SetFocus();
                    return TRUE;
                }
                case VK_RETURN:
                {
                    TranslateSelectionToEditControl();
                    return TRUE;
                }
                default:
                    break;
            }
        }
    }
    return CListBox::PreTranslateMessage(pMsg);
}


void ZIntelliListBox::OnMouseMove(UINT nFlags, CPoint point) 
{
    BOOL    bOutside;
    UINT    Index = ItemFromPoint( point, bOutside );

    CListBox::OnMouseMove(nFlags, point);

    if (bOutside == FALSE)
    {
        SetCurSel( Index );
    }
}

void ZIntelliListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
    m_CurrentSelectionOnDown = GetCurSel();    
    CListBox::OnLButtonDown(nFlags, point);
}

void ZIntelliListBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
    CListBox::OnLButtonUp(nFlags, point);
    // Check if the selection on the up is the same as on the down
    // if not, do not translate to edit control
    int    CurSel = GetCurSel();    
    if (CurSel != LB_ERR && CurSel == m_CurrentSelectionOnDown)
        TranslateSelectionToEditControl();
}

void ZIntelliListBox::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    CListBox::OnLButtonDblClk(nFlags, point);
    TranslateSelectionToEditControl();

}

void ZIntelliListBox::OnSize(UINT nType, int cx, int cy) 
{
    CListBox::OnSize(nType, cx, cy);

    if (m_pEditCtrl)
        m_pEditCtrl->OnExtendedSizeHasChanged( cx,cy );
    
}

