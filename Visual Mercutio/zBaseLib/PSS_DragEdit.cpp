/****************************************************************************
 * ==> PSS_DragEdit --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a base class for drag edit operations             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DragEdit.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_MaxLineLen 2048
//---------------------------------------------------------------------------
// Global enums
//---------------------------------------------------------------------------
enum
{
    E_DE_INSEL,
    E_DE_BEFORESEL,
    E_DE_AFTERSEL
};
//---------------------------------------------------------------------------
// Global functions
//---------------------------------------------------------------------------
/**
* Checks if (line, pos) is within (line1, pos1) ~ (line2, pos2)
*@param line - line to check
*@param pos - position to check
*@param line1 - range start line
*@param pos1 - range start position
*@param line2 - range end line
*@param pos2 - range end position
*@return selection type
*/
static int LinePosInRange(int line, int pos, int line1, int pos1, int line2, int pos2)
{
    // single or multi line selection mark?
    if (line1 == line2)
    {
        // single line selection mark
        if (line < line1)
            return E_DE_BEFORESEL;

        if (line > line1)
            return E_DE_AFTERSEL;

        // nLine == nLine1
        if (pos < pos1)
            return E_DE_BEFORESEL;

        if (pos > pos2)
            return E_DE_AFTERSEL;
    }
    else
    {
        // multi-line selection mark
        if (line < line1)
            return E_DE_BEFORESEL;

        if (line > line2)
            return E_DE_AFTERSEL;

        if (line == line1 && pos < pos1)
            return E_DE_BEFORESEL;

        if (line == line2 && pos > pos2)
            return E_DE_AFTERSEL;
    }

    return E_DE_INSEL;
}
//---------------------------------------------------------------------------
// PSS_EditDropTarget
//---------------------------------------------------------------------------
BOOL PSS_EditDropTarget::Register(PSS_DragEdit* pEdit)
{
    m_pEditCtl = pEdit;
    return COleDropTarget::Register(pEdit);
}
//---------------------------------------------------------------------------
DROPEFFECT PSS_EditDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD keyState, CPoint point)
{
    PSS_Assert(m_pEditCtl);

    if (!m_pEditCtl->EnableDrop() || !pDataObject->IsDataAvailable(CF_TEXT))
        return DROPEFFECT_NONE;

    DROPEFFECT dwEffect;

    if (keyState & MK_CONTROL)
        dwEffect = DROPEFFECT_COPY;
    else
        dwEffect = DROPEFFECT_MOVE;

    m_BeginDrop = TRUE;

    // set focus to current window, so the caret will be shown
    m_pEditCtl->SetFocus();

    return dwEffect;
}
//---------------------------------------------------------------------------
void PSS_EditDropTarget::OnDragLeave(CWnd* pWnd)
{
    PSS_Assert(m_pEditCtl);

    m_BeginDrop = FALSE;
}
//---------------------------------------------------------------------------
DROPEFFECT PSS_EditDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD keyState, CPoint point)
{
    PSS_Assert(m_pEditCtl);

    if (!m_BeginDrop)
        return DROPEFFECT_NONE;

    DROPEFFECT dwEffect;

    if (keyState & MK_CONTROL)
        dwEffect = DROPEFFECT_COPY;
    else
        dwEffect = DROPEFFECT_MOVE;

    m_pEditCtl->DrawCaretByCursor();

    return dwEffect;
}
//---------------------------------------------------------------------------
DROPEFFECT PSS_EditDropTarget::OnDragScroll(CWnd* pWnd, DWORD keyState, CPoint point)
{
    PSS_Assert(m_pEditCtl);

    // if pWnd is kind of CView, let COleDropTarget handle it
    if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))
        return COleDropTarget::OnDragScroll(pWnd, keyState, point);

    if (!m_BeginDrop)
        return DROPEFFECT_NONE;

    CRect rectClient;
    m_pEditCtl->GetClientRect(&rectClient);

    CRect rect = rectClient;

    // nScrollInset is a COleDropTarget's static member variable
    rect.InflateRect(-nScrollInset, -nScrollInset);

    // hit-test against insert region
    if (rectClient.PtInRect(point) && !rect.PtInRect(point))
    {
        UINT        msg        = 0;
        int         code       = 0;
        CScrollBar* pScrollBar = NULL;

        // determine which way to scroll along both x and y axis
        if (point.x < rect.left)
        {
            pScrollBar = m_pEditCtl->GetScrollBarCtrl(SB_HORZ);
            msg        = WM_HSCROLL;
            code       = SB_LINELEFT;
        }
        else
        if (point.x >= rect.right)
        {
            pScrollBar = m_pEditCtl->GetScrollBarCtrl(SB_HORZ);
            msg        = WM_HSCROLL;
            code       = SB_LINERIGHT;
        }

        if (point.y < rect.top)
        {
            pScrollBar = m_pEditCtl->GetScrollBarCtrl(SB_VERT);
            msg        = WM_VSCROLL;
            code       = SB_LINEUP;
        }
        else
        if (point.y >= rect.bottom)
        {
            pScrollBar = m_pEditCtl->GetScrollBarCtrl(SB_VERT);
            msg        = WM_VSCROLL;
            code       = SB_LINEDOWN;
        }

        if (msg)
            m_pEditCtl->SendMessage(msg, MAKEWPARAM(code, 0), LPARAM(pScrollBar ? pScrollBar->GetSafeHwnd() : NULL));

        m_pEditCtl->DrawCaretByCursor();

        if (keyState & MK_CONTROL)
            return (DROPEFFECT_SCROLL | DROPEFFECT_COPY);
        else
            return (DROPEFFECT_SCROLL | DROPEFFECT_MOVE);
    }

    return DROPEFFECT_NONE;
}
//---------------------------------------------------------------------------
BOOL PSS_EditDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
    PSS_Assert(m_pEditCtl);

    if (!m_BeginDrop)
        return FALSE;

    if (m_pEditCtl->IsInDragging() && m_pEditCtl->IsInSelRange())
        return DROPEFFECT_NONE;

    if ((dropEffect & DROPEFFECT_MOVE) && m_pEditCtl->IsInDragging())
    {
        // if the drag window is equal to drop window and user want to move string, let drag source
        // to move string by itself
        m_pEditCtl->SetDropEqualDrag(TRUE);

        int line, pos;
        m_pEditCtl->GetLinePosByCursor(line, pos);
        m_pEditCtl->SetDropPos(line, pos);
    }
    else
    {
        HGLOBAL hData = pDataObject->GetGlobalData(CF_TEXT);

        if (!hData)
        {
            TRACE("PSS_EditDropTarget - OnDrop - Could not get data\n");
            return FALSE;
        }

        LPCSTR pData = LPCSTR(::GlobalLock(hData));

        if (!pData)
        {
            TRACE("PSS_EditDropTarget - OnDrop - Failed to lock the data\n");
            return FALSE;
        }

        try
        {
            // set dropped point
            m_pEditCtl->SetCaretByCursor();

            int begin, end;

            // insert string and select the inserted string
            m_pEditCtl->GetSel(begin, end);
            end += std::strlen(pData);
            m_pEditCtl->ReplaceSel(pData, TRUE);
            m_pEditCtl->SetSel(begin, end);
        }
        catch (...)
        {
            ::GlobalUnlock(hData);
            throw;
        }

        ::GlobalUnlock(hData);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::m_OleInit = FALSE;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DragEdit, PSS_DragEditBase)
    //{{AFX_MSG_MAP(PSS_DragEdit)
    ON_WM_LBUTTONDOWN()
    ON_WM_SETCURSOR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DragEdit
//---------------------------------------------------------------------------
PSS_DragEdit::PSS_DragEdit() :
    PSS_DragEditBase(),
    m_EnableFlags(0),
    m_DropPtLine(0),
    m_DropPtPos(0),
    m_DragInit(FALSE),
    m_InDragging(FALSE),
    m_DropEqualDrag(FALSE)
{}
//---------------------------------------------------------------------------
PSS_DragEdit::~PSS_DragEdit()
{}
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::Init(int flags)
{
    if (m_DragInit)
        return FALSE;

    m_EnableFlags = flags;

    if (!GetSafeHwnd())
    {
        TRACE("You should create ZBDragEdit first, before this function is called\n");
        return FALSE;
    }

    if (!m_DropTarget.Register(this))
    {
        TRACE("Fail in registing drop target\n");
        return FALSE;
    }

    m_DragInit = TRUE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::GetCurRange(int& line1, int& pos1, int& line2, int& pos2) const
{
    // get current selection range
    GetSel(pos1, pos2);

    // transpose to line and pos
    CharToLinePos(pos1, &line1, &pos1);
    CharToLinePos(pos2, &line2, &pos2);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::GetLinePosByCursor(int& line, int& pos) const
{
    CPoint ptCursor;
    ::GetCursorPos(&ptCursor);
    ScreenToClient(&ptCursor);

    pos = int(short(LOWORD(DWORD(CharFromPos(ptCursor)))));

    if (pos < 0)
        pos = 0;

    CharToLinePos(pos, &line, &pos);

    // check if cusor is on white space area and get the maximum x of line
    const CPoint ptChar = PosFromChar(LineIndex(line) + LineLength(LineIndex(line)));

    if (ptChar.x < ptCursor.x || ptCursor.x < 0)
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::SetCaretByCursor()
{
    // get cursor position and translate it to client coordinate
    CPoint ptCursor;
    ::GetCursorPos(&ptCursor);
    ScreenToClient(&ptCursor);

    // set caret position
    const int ch = int(LOWORD(DWORD(CharFromPos(ptCursor))));
    SetSel(ch, ch);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::SetCaret(int line, int pos)
{
    const int ch = LinePosToChar(line, pos);
    SetSel(ch, ch);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::DrawCaretByCursor() const
{
    int line, pos;
    GetLinePosByCursor(line, pos);
    SetCaretPos(GetPosFromLinePos(line, pos));
    return TRUE;
}
//---------------------------------------------------------------------------
CPoint PSS_DragEdit::PosFromChar(UINT ch) const
{
    if (0 == ch)
        return CPoint(0, 0);

    CPoint pt = PSS_DragEditBase::PosFromChar(ch);

    if (pt.x < 0 && pt.y < 0)
    {
        int line, pos;
        CharToLinePos(int(ch), &line, &pos);

        // get dc and select current using font
        CClientDC dc(const_cast<PSS_DragEdit*>(this));
        dc.SelectObject(GetFont());

        // get previous char position
        pt = PSS_DragEditBase::PosFromChar(ch - 1);

        if (!pos)
        {
            // if current char is the first char, get the current y from previous y plus font height
            const CSize fontSize = dc.GetTextExtent("A", 1);
            pt.y                += fontSize.cy;
            pt.x                 = 0;
        }
        else
        {
            char buffer[M_MaxLineLen];
            GetLine(line, buffer, sizeof(buffer));
            const CSize fontSize = dc.GetTextExtent(&buffer[pos - 1], 1);
            pt.x                += fontSize.cx;
        }

        dc.SelectStockObject(SYSTEM_FONT);
    }

    return pt;
}
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::IsInSelRange() const
{
    int line1, pos1, line2, pos2;
    GetCurRange(line1, pos1, line2, pos2);

    // no selection mark?
    if (line1 == line2 && pos1 == pos2)
        return FALSE;

    int line, pos;

    // out of selection mark?
    if (!GetLinePosByCursor(line, pos))
        return FALSE;

    return (LinePosInRange(line, pos, line1, pos1, line2, pos2) == E_DE_INSEL);
}
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        const WPARAM ch = pMsg->wParam;

        switch (ch)
        {
            case VK_DELETE:
                DoDelete();
                return TRUE;

            default:
                break;
        }
    }

    return PSS_DragEditBase::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_DragEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (!EnableDrag())
    {
        PSS_DragEditBase::OnLButtonDown(nFlags, point);
        return;
    }

    if (IsInSelRange())
    {
        CString str;

        // get selected text
        if (!GetSelText(str))
        {
            PSS_DragEditBase::OnLButtonDown(nFlags, point);
            return;
        }

        int line1, pos1, line2, pos2;
        GetCurRange(line1, pos1, line2, pos2);

        // make a copy of selected text to a global memory
        HGLOBAL hData = ::GlobalAlloc(GHND | GMEM_SHARE, std::strlen(str) + 1);

        if (!hData)
            return;

        LPSTR pData = LPSTR(::GlobalLock(hData));

        if (!pData)
            return;

        try
        {
            std::strcpy(pData, str);
            m_DropSource.CacheGlobalData(CF_TEXT, hData);
        }
        catch (...)
        {
            ::GlobalUnlock(hData);
            throw;
        }

        ::GlobalUnlock(hData);

        // defined dragging area
        CRect rc(point.x - 5, point.y - 5, point.x + 5, point.y + 5);

        // it seems it's a MFC's bug that MFC will set capture to ::AfxGetMainWnd() and use its coordinates
        // to test the lpRectStartDrag. So, we need to first translate the rc's coordinate
        MapWindowPoints(::AfxGetMainWnd(), &rc);

        // start dragging
        const DROPEFFECT effect = m_DropSource.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, &rc);
        m_DropEqualDrag         = FALSE;
        m_InDragging            = TRUE;
        m_InDragging            = FALSE;

        if (effect & (DROPEFFECT_MOVE | DROPEFFECT_COPY))
        {
            if (effect & DROPEFFECT_MOVE)
            {
                if (m_DropEqualDrag)
                {
                    // if drag source equal to drop target and user want to move string
                    m_DropEqualDrag = FALSE;
                    const int sel   = LinePosInRange(m_DropPtLine, m_DropPtPos, line1, pos1, line2, pos2);

                    // don't allow the string to be moved into selection area
                    if (sel == E_DE_INSEL)
                        return;
                    else
                    {
                        if (sel == E_DE_AFTERSEL)
                        {
                            // if user want to move the string back, need to adjust the m_DropPtLine
                            // and m_DropPtPos
                            int ch = LinePosToChar(m_DropPtLine, m_DropPtPos);
                            ch    -= str.GetLength();

                            // delete selected string first
                            ReplaceSel("", TRUE);
                            CharToLinePos(ch, &m_DropPtLine, &m_DropPtPos);

                            // set the new insert point
                            SetCaret(m_DropPtLine, m_DropPtPos);
                        }
                        else
                        {
                            // delete selected string first
                            ReplaceSel("", TRUE);

                            // set new insert point
                            SetCaret(m_DropPtLine, m_DropPtPos);
                        }

                        // insert dragged string and select it
                        int begin, end;
                        GetSel(begin, end);
                        end += str.GetLength();
                        ReplaceSel(str, TRUE);
                        SetSel(begin, end);
                    }
                }
                else
                    ReplaceSel("", TRUE);
            }

            m_DropEqualDrag = FALSE;
            return;
        }

        m_DropEqualDrag = FALSE;

        // if user does not want to drag string, reset the caret pos
        SetCaretByCursor();

        return;
    }

    PSS_DragEditBase::OnLButtonDown(nFlags, point);
}
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    if (EnableDrag() && IsInSelRange())
    {
        // if the cursor is over a selection mark, will change the cursor shape to a arrow type,
        // it means user can drag it
        ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
        return FALSE;
    }

    // otherwise keep the cursor shape as its original type
    return PSS_DragEditBase::OnSetCursor(pWnd, nHitTest, message);
}
//---------------------------------------------------------------------------
void PSS_DragEdit::DoDelete()
{

    int line1, pos1, line2, pos2;
    GetCurRange(line1, pos1, line2, pos2);

    // no selection mark
    const BOOL hasSel = (line1 == line2 && pos1 == pos2) ? FALSE : TRUE;

    if (pos2 >= GetWindowTextLength() && !hasSel)
        return;

    CString s;
    GetWindowText(s);
    const int length = s.GetLength();

    if ((length > 0 && pos1 < length))
    {
        // if no selection, selects the char on the right
        if (!hasSel)
            pos2 = pos1 + 1;

        CString strNew;
        ReplaceSelString(NULL, pos1, pos2, strNew);

        SetWindowText(strNew);
        SetSel(pos1, pos1);
        NotifyParent(EN_UPDATE);
        NotifyParent(EN_CHANGE);
    }
}
//---------------------------------------------------------------------------
void PSS_DragEdit::NotifyParent(UINT msg)
{
    CWnd* pWndParent = GetParent();

    if (pWndParent)
    {
        WPARAM w = MAKELONG(GetDlgCtrlID(), msg);
        LPARAM l = reinterpret_cast<LPARAM>(GetSafeHwnd());
        pWndParent->SendMessage(WM_COMMAND, w, l);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::GetSelText(CString& str)
{
    int line1, pos1, line2, pos2;
    GetCurRange(line1, pos1, line2, pos2);
    PSS_Assert(line1 >= 0 && pos1 >= 0 && line2 >= 0 && pos2 >= 0);

    char buffer[M_MaxLineLen];
    int  len;

    // single-line selection
    if (line1 == line2)
    {
        len          = GetLine(line1, buffer, sizeof(buffer));
        buffer[len]  = '\0';
        buffer[pos2] = '\0';
        str          = buffer + pos1;
        return TRUE;
    }

    // multi-line section
    len         = GetLine(line1, buffer, sizeof(buffer));
    buffer[len] = '\0';
    str         = buffer + pos1;

    for (int i = line1 + 1; i < line2; ++i)
    {
        str         += "\r\n";
        len          = GetLine(i, buffer, sizeof(buffer));
        buffer[len]  = '\0';
        str         += buffer;
    }

    str          += "\r\n";
    len           = GetLine(line2, buffer, sizeof(buffer));
    buffer[len]   = '\0';
    buffer[pos2]  = '\0';
    str          += buffer;

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DragEdit::ReplaceSelString(LPCTSTR pNew, int start, int stop, CString& str) const
{
    // if all is selected, return the new string
    if (start && stop == -1)
        str = (pNew ? pNew : _T(""));
    else
    {
        CString s;
        GetWindowText(s);
        const int length = s.GetLength();

        str.Empty();

        if (start > 0)
            str += s.Left(start);

        if (pNew)
            str += pNew;

        if (stop < length)
            str += s.Right(length - stop);
    }
}
//---------------------------------------------------------------------------
