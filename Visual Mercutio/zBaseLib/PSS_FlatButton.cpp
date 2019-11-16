/****************************************************************************
 * ==> PSS_FlatButton ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a flat button                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FlatButton.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_MemoryDC
//---------------------------------------------------------------------------
#ifdef ST_USE_MEMDC
    PSS_MemoryDC::PSS_MemoryDC(CDC* pDC) :
        CDC(),
        m_pOldBitmap(NULL),
        m_pDC(pDC),
        m_MemDC(FALSE),
        m_Printing(FALSE)
    {
        ASSERT(pDC);

        m_MemDC = !pDC->IsPrinting();

        // create a memory DC
        if (m_MemDC)
        {
            pDC->GetClipBox(&m_Rect);
            CreateCompatibleDC(pDC);
            m_Bitmap.CreateCompatibleBitmap(pDC, m_Rect.Width(), m_Rect.Height());
            m_pOldBitmap = SelectObject(&m_Bitmap);
            SetWindowOrg(m_Rect.left, m_Rect.top);
        }
        else
        {
            // make a copy of the relevant parts of the current DC for printing
            m_Printing  = pDC->m_bPrinting;
            m_hDC       = pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }
    }
#endif
//---------------------------------------------------------------------------
#ifdef ST_USE_MEMDC
    PSS_MemoryDC::~PSS_MemoryDC()
    {
        // copy the contents of the mem DC to the original DC
        if (m_MemDC)
        {
            // copy the offscreen bitmap onto the screen.
            m_pDC->BitBlt(m_Rect.left,
                          m_Rect.top,
                          m_Rect.Width(),
                          m_Rect.Height(),
                          this,
                          m_Rect.left,
                          m_Rect.top,
                          SRCCOPY);

            // swap back the original bitmap
            SelectObject(m_pOldBitmap);
        }
        else
            // replace the DC with an illegal value, this will prevent from accidently deleting
            // the handles associated with the CDC that was passed to the constructor
            m_hDC = m_hAttribDC = NULL;
    }
#endif
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FlatButton, CButton)
    //{{AFX_MSG_MAP(PSS_FlatButton)
    ON_WM_CAPTURECHANGED()
    ON_WM_SETCURSOR()
    ON_WM_KILLFOCUS()
    ON_WM_MOUSEMOVE()
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_SYSCOLORCHANGE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FlatButton
//---------------------------------------------------------------------------
PSS_FlatButton::PSS_FlatButton() :
    CButton(),
    m_pBmpOldBk(NULL),
    m_InactiveBg(0),
    m_InactiveFg(0),
    m_ActiveBg(0),
    m_ActiveFg(0),
    m_hCursor(NULL),
    m_hIconIn(NULL),
    m_hIconOut(NULL),
    m_Align(IE_ST_ALIGN_HORZ),
    m_CxIcon(0),
    m_CyIcon(0),
    m_ShowText(TRUE),
    m_DrawBorder(TRUE),
    m_IsFlat(TRUE),
    m_MouseOnButton(FALSE),
    m_DrawFlatFocus(FALSE),
    m_DrawTransparent(FALSE),
    m_IsDefault(FALSE)
{
    SetDefaultInactiveBgColor();
    SetDefaultInactiveFgColor();
    SetDefaultActiveBgColor();
    SetDefaultActiveFgColor();

    // no tooltip created
    m_ToolTip.m_hWnd = NULL;
}
//---------------------------------------------------------------------------
PSS_FlatButton::~PSS_FlatButton()
{
    // restore the old bitmap (if any)
    if (m_DcBk.m_hDC && m_pBmpOldBk)
        m_DcBk.SelectObject(m_pBmpOldBk);

    // destroy the icons (if any). NOTE the following two lines MUST be here, even if the bound checker
    // says they are unnecessary
    if (m_hIconIn)
        ::DestroyIcon(m_hIconIn);

    if (m_hIconOut)
        ::DestroyIcon(m_hIconOut);

    // destroy the cursor (if any)
    if (m_hCursor)
        ::DestroyCursor(m_hCursor);
}
//---------------------------------------------------------------------------
BOOL PSS_FlatButton::GetDefault() const
{
    return m_IsDefault;
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetTooltipText(int id, BOOL activate)
{
    CString text;

    // load string resource
    text.LoadString(id);

    // if string resource is not empty
    if (!text.IsEmpty())
        SetTooltipText(&text, activate);
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetTooltipText(CString* pText, BOOL activate)
{
    // cannot accept a NULL pointer
    if (!pText)
        return;

    // initialize tooltip
    InitToolTip();

    // if there is no tooltip defined, add it
    if (!m_ToolTip.GetToolCount())
    {
        CRect rectBtn;
        GetClientRect(rectBtn);
        m_ToolTip.AddTool(this, LPCTSTR(*pText), rectBtn, 1);
    }

    // set text for tooltip
    m_ToolTip.UpdateTipText(LPCTSTR(*pText), this, 1);
    m_ToolTip.Activate(activate);
}
//---------------------------------------------------------------------------
void PSS_FlatButton::ActivateTooltip(BOOL activate)
{
    // if there is no tooltip, do nothing
    if (!m_ToolTip.GetToolCount())
        return;

    // activate tooltip
    m_ToolTip.Activate(activate);
}
//---------------------------------------------------------------------------
BOOL PSS_FlatButton::SetBtnCursor(int cursorId)
{
    HINSTANCE hInstResource;

    // destroy any previous cursor
    if (m_hCursor)
        ::DestroyCursor(m_hCursor);

    m_hCursor = NULL;

    // cursor wanted?
    if (cursorId != -1)
    {
        hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(cursorId), RT_GROUP_CURSOR);

        // load icon resource
        m_hCursor = (HCURSOR)::LoadImage(hInstResource, MAKEINTRESOURCE(cursorId), IMAGE_CURSOR, 0, 0, 0);

        // something wrong?
        if (!m_hCursor)
            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_FlatButton::GetFlatFocus() const
{
    return m_DrawFlatFocus;
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetFlatFocus(BOOL drawFlatFocus, BOOL repaint)
{
    m_DrawFlatFocus = drawFlatFocus;

    // repaint the button
    if (repaint)
        Invalidate();
}
//---------------------------------------------------------------------------
const COLORREF PSS_FlatButton::GetActiveFgColor() const
{
    return m_ActiveFg;
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetActiveFgColor(COLORREF color, BOOL repaint)
{
    m_ActiveFg = color;

    if (repaint)
        Invalidate();
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetDefaultActiveFgColor(BOOL repaint)
{
    m_ActiveFg = ::GetSysColor(COLOR_BTNTEXT);

    if (repaint)
        Invalidate();
}
//---------------------------------------------------------------------------
const COLORREF PSS_FlatButton::GetActiveBgColor() const
{
    return m_ActiveBg;
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetActiveBgColor(COLORREF color, BOOL repaint)
{
    m_ActiveBg = color;

    if (repaint)
        Invalidate();
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetDefaultActiveBgColor(BOOL repaint)
{
    m_ActiveBg = ::GetSysColor(COLOR_BTNFACE);

    if (repaint)
        Invalidate();
}
//---------------------------------------------------------------------------
const COLORREF PSS_FlatButton::GetInactiveFgColor() const
{
    return m_InactiveFg;
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetInactiveFgColor(COLORREF color, BOOL repaint)
{
    m_InactiveFg = color;

    if (repaint)
        Invalidate();
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetDefaultInactiveFgColor(BOOL repaint)
{
    m_InactiveFg = ::GetSysColor(COLOR_BTNTEXT);

    if (repaint)
        Invalidate();
}
//---------------------------------------------------------------------------
const COLORREF PSS_FlatButton::GetInactiveBgColor() const
{
    return m_InactiveBg;
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetInactiveBgColor(COLORREF color, BOOL repaint)
{
    m_InactiveBg = color;

    if (repaint)
        Invalidate();
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetDefaultInactiveBgColor(BOOL repaint)
{
    m_InactiveBg = ::GetSysColor(COLOR_BTNFACE);

    if (repaint)
        Invalidate();
}
//---------------------------------------------------------------------------
BOOL PSS_FlatButton::GetShowText() const
{
    return m_ShowText;
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetShowText(BOOL show)
{
    m_ShowText = show;
    Invalidate();
}
//---------------------------------------------------------------------------
int PSS_FlatButton::GetAlign() const
{
    return m_Align;
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetAlign(int align)
{
    switch (align)
    {
        case IE_ST_ALIGN_HORZ:       m_Align = IE_ST_ALIGN_HORZ;       break;
        case IE_ST_ALIGN_HORZ_RIGHT: m_Align = IE_ST_ALIGN_HORZ_RIGHT; break;
        case IE_ST_ALIGN_VERT:       m_Align = IE_ST_ALIGN_VERT;       break;
    }

    Invalidate();
}
//---------------------------------------------------------------------------
BOOL PSS_FlatButton::GetFlat() const
{
    return m_IsFlat;
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetFlat(BOOL state)
{
    m_IsFlat = state;
    Invalidate();
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetIcon(int iconInId, int iconOutId)
{
    HINSTANCE hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(iconInId), RT_GROUP_ICON);

    // set icon when the mouse is IN the button
    HICON hIconIn = HICON(::LoadImage(hInstResource, MAKEINTRESOURCE(iconInId), IMAGE_ICON, 0, 0, 0));

    // set icon when the mouse is OUT the button
    HICON hIconOut = (!iconOutId ? NULL : HICON(::LoadImage(hInstResource, MAKEINTRESOURCE(iconOutId), IMAGE_ICON, 0, 0, 0)));

    SetIcon(hIconIn, hIconOut);
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetIcon(HICON hIconIn, HICON hIconOut)
{
    // NOTE the following two lines MUST be here, even if the bound checker says they are unnecessary
    if (m_hIconIn)
        ::DestroyIcon(m_hIconIn);

    if (m_hIconOut)
        ::DestroyIcon(m_hIconOut);

    // set icon when the mouse is IN the button
    m_hIconIn = hIconIn;

    // set icon when the mouse is OUT the button
    m_hIconOut = (hIconOut == NULL) ? m_hIconIn : hIconOut;

    ICONINFO iconInfo;

    // get icon dimension
    ZeroMemory(&iconInfo, sizeof(ICONINFO));
    ::GetIconInfo(m_hIconIn, &iconInfo);

    m_CxIcon = BYTE(iconInfo.xHotspot * 2);
    m_CyIcon = BYTE(iconInfo.yHotspot * 2);

    ::DeleteObject(iconInfo.hbmMask);
    ::DeleteObject(iconInfo.hbmColor);

    RedrawWindow();
}
//---------------------------------------------------------------------------
void PSS_FlatButton::SetDrawBorder(BOOL value)
{
    m_DrawBorder = value;
}
//---------------------------------------------------------------------------
void PSS_FlatButton::DrawTransparent(BOOL repaint)
{
    m_DrawTransparent = TRUE;

    // restore old bitmap (if any)
    if (m_DcBk.m_hDC && m_pBmpOldBk)
        m_DcBk.SelectObject(m_pBmpOldBk);

    m_BmpBk.Detach();
    m_DcBk.Detach();

    // repaint the button
    if (repaint)
        Invalidate();
}
//---------------------------------------------------------------------------
const short PSS_FlatButton::GetVersionI()
{
    // divide by 10 to get actual version
    return 26;
}
//---------------------------------------------------------------------------
const char* PSS_FlatButton::GetVersionC()
{
    return "2.6";
}
//---------------------------------------------------------------------------
void PSS_FlatButton::PreSubclassWindow()
{
    UINT style = GetButtonStyle();

    // check if this is the default button
    if (style & BS_DEFPUSHBUTTON)
        m_IsDefault = TRUE;

    // add BS_OWNERDRAW style
    SetButtonStyle(style | BS_OWNERDRAW);

    CButton::PreSubclassWindow();
}
//---------------------------------------------------------------------------
void PSS_FlatButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    #ifdef ST_USE_MEMDC
        CDC*         pDrawDC = CDC::FromHandle(lpDIS->hDC);
        PSS_MemoryDC memDC(pDrawDC);
        CDC*         pDC = &memDC;
    #else    
        CDC* pDC = CDC::FromHandle(lpDIS->hDC);
    #endif

    const BOOL  isPressed  = (lpDIS->itemState & ODS_SELECTED);
    const BOOL  isFocused  = (lpDIS->itemState & ODS_FOCUS);
    const BOOL  isDisabled = (lpDIS->itemState & ODS_DISABLED);
          CRect itemRect   = lpDIS->rcItem;

    pDC->SetBkMode(TRANSPARENT);

    if (m_IsFlat == FALSE)
        if (isFocused || GetDefault())
        {
            CBrush br(RGB(0, 0, 0));
            pDC->FrameRect(&itemRect, &br);
            itemRect.DeflateRect(1, 1);
        }

    COLORREF bgColor;

    // prepare draw... paint button's area with background color
    if (m_MouseOnButton || isPressed)
        bgColor = GetActiveBgColor();
    else
        bgColor = GetInactiveBgColor();

    CBrush br(bgColor);

    // do draw transparent?
    if (m_DrawTransparent)
        PaintBk(pDC);
    else
        pDC->FillRect(&itemRect, &br);

    // draw the pressed button
    if (isPressed)
    {
        if (m_IsFlat)
        {
            if (m_DrawBorder)
                pDC->Draw3dRect(itemRect, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHILIGHT));
        }
        else
        {
            CBrush brBtnShadow(GetSysColor(COLOR_BTNSHADOW));
            pDC->FrameRect(&itemRect, &brBtnShadow);
        }
    }
    else
    {
        // ...else draw non pressed button
        CPen penBtnHiLight(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // white
        CPen pen3DLight   (PS_SOLID, 0, GetSysColor(COLOR_3DLIGHT));    // light gray
        CPen penBtnShadow (PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));  // dark gray
        CPen pen3DDKShadow(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)); // black

        if (m_IsFlat)
        {
            if (m_MouseOnButton && m_DrawBorder)
                pDC->Draw3dRect(itemRect, ::GetSysColor(COLOR_BTNHILIGHT), ::GetSysColor(COLOR_BTNSHADOW));
        }
        else
        {
            // draw the border on the left top
            CPen* pOldPen = pDC->SelectObject(&penBtnHiLight);

            // white line
            pDC->MoveTo(itemRect.left,  itemRect.bottom - 1);
            pDC->LineTo(itemRect.left,  itemRect.top);
            pDC->LineTo(itemRect.right, itemRect.top);

            // light gray line
            pDC->SelectObject(pen3DLight);
            pDC->MoveTo(itemRect.left + 1, itemRect.bottom - 1);
            pDC->LineTo(itemRect.left + 1, itemRect.top    + 1);
            pDC->LineTo(itemRect.right,    itemRect.top    + 1);

            // draw the border on the right bottom
            pDC->SelectObject(pen3DDKShadow);

            // black line
            pDC->MoveTo(itemRect.left,      itemRect.bottom - 1);
            pDC->LineTo(itemRect.right - 1, itemRect.bottom - 1);
            pDC->LineTo(itemRect.right - 1, itemRect.top    - 1);

            // dark gray line
            pDC->SelectObject(penBtnShadow);
            pDC->MoveTo(itemRect.left  + 1, itemRect.bottom - 2);
            pDC->LineTo(itemRect.right - 2, itemRect.bottom - 2);
            pDC->LineTo(itemRect.right - 2, itemRect.top);

            pDC->SelectObject(pOldPen);
        }
    }

    CString title;

    // do show the title?
    if (m_ShowText)
        // read the button's title
        GetWindowText(title);

    CRect captionRect = lpDIS->rcItem;

    // draw the icon
    if (m_hIconIn)
        DrawIcon(pDC, &title, &lpDIS->rcItem, &captionRect, isPressed, isDisabled);

    // write the button title (if any)
    if (!title.IsEmpty())
    {
        // draw the caption rect. If the button is pressed, move the caption rect accordingly
        if (isPressed)
            captionRect.OffsetRect(1, 1);

        #ifdef ST_USE_MEMDC
            // get dialog's font
            CFont *pCurrentFont = GetFont();
            CFont *pOldFont = pDC->SelectObject(pCurrentFont);
        #endif

        if (m_MouseOnButton || isPressed)
        {
            pDC->SetTextColor(GetActiveFgColor());
            pDC->SetBkColor(GetActiveBgColor());
        }
        else
        {
            pDC->SetTextColor(GetInactiveFgColor());
            pDC->SetBkColor(GetInactiveBgColor());
        }

        // center text
        CRect centerRect = captionRect;
        pDC->DrawText(title, -1, captionRect, DT_SINGLELINE | DT_CALCRECT);
        captionRect.OffsetRect((centerRect.Width() - captionRect.Width()) / 2, (centerRect.Height() - captionRect.Height()) / 2);

        pDC->SetBkMode(TRANSPARENT);
        pDC->DrawState(captionRect.TopLeft(),
                       captionRect.Size(),
                       LPCTSTR(title),
                       isDisabled ? DSS_DISABLED : DSS_NORMAL,
                       TRUE,
                       0,
                       (CBrush*)NULL);

        #ifdef ST_USE_MEMDC
            pDC->SelectObject(pOldFont);
        #endif
    }

    if (!m_IsFlat || (m_IsFlat && m_DrawFlatFocus))
        // draw the focus rect
        if (isFocused)
        {
            CRect focusRect = itemRect;
            focusRect.DeflateRect(3, 3);
            pDC->DrawFocusRect(&focusRect);
        }
}
//---------------------------------------------------------------------------
BOOL PSS_FlatButton::PreTranslateMessage(MSG* pMsg)
{
    InitToolTip();
    m_ToolTip.RelayEvent(pMsg);

    return CButton::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
LRESULT PSS_FlatButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_LBUTTONDBLCLK)
        message = WM_LBUTTONDOWN;

    return CButton::DefWindowProc(message, wParam, lParam);
}
//---------------------------------------------------------------------------
void PSS_FlatButton::OnCaptureChanged(CWnd *pWnd)
{
    if (m_MouseOnButton)
    {
        ReleaseCapture();
        Invalidate();
    }

    // call base message handler
    CButton::OnCaptureChanged(pWnd);
}
//---------------------------------------------------------------------------
BOOL PSS_FlatButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    // if a cursor was specified then use it!
    if (!m_hCursor)
    {
        ::SetCursor(m_hCursor);
        return TRUE;
    }

    return CButton::OnSetCursor(pWnd, nHitTest, message);
}
//---------------------------------------------------------------------------
void PSS_FlatButton::OnKillFocus(CWnd * pNewWnd)
{
    CButton::OnKillFocus(pNewWnd);

    // if button is not flat, do nothing
    if (!m_IsFlat)
        return;

    if (m_MouseOnButton)
    {
        m_MouseOnButton = FALSE;
        Invalidate();
    }
}
//---------------------------------------------------------------------------
void PSS_FlatButton::OnMouseMove(UINT nFlags, CPoint point)
{
    CWnd* pWnd;
    CWnd* pParent;

    CButton::OnMouseMove(nFlags, point);

    // if the mouse enter the button with the left button pressed, do nothing
    if (nFlags & MK_LBUTTON && !m_MouseOnButton)
        return;

    // if our button is not flat then do nothing
    if (!m_IsFlat)
        return;

    pWnd    = GetActiveWindow();
    pParent = GetOwner();

    if ((GetCapture() != this) &&
        #ifndef ST_LIKEIE
            pWnd &&
        #endif
            pParent)
    {
        m_MouseOnButton = TRUE;
        SetCapture();
        Invalidate();
    }
    else
    {
        POINT p2 = point;
        ClientToScreen(&p2);

        CWnd* wndUnderMouse = WindowFromPoint(p2);

        if (wndUnderMouse && wndUnderMouse->m_hWnd != this->m_hWnd)
        {
            // redraw only if mouse goes out
            if (m_MouseOnButton)
            {
                m_MouseOnButton = FALSE;
                Invalidate();
            }

            // if user is NOT pressing left button then release capture
            if (!(nFlags & MK_LBUTTON))
                ReleaseCapture();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_FlatButton::OnSysColorChange()
{
    CButton::OnSysColorChange();

    m_DcBk.DeleteDC();
    m_BmpBk.DeleteObject();
}
//---------------------------------------------------------------------------
HBRUSH PSS_FlatButton::CtlColor(CDC* pDC, UINT nCtlColor)
{
    return (HBRUSH)::GetStockObject(NULL_BRUSH);
}
//---------------------------------------------------------------------------
void PSS_FlatButton::InitToolTip()
{
    if (!m_ToolTip.m_hWnd)
    {
        // create tooltip control
        m_ToolTip.Create(this);

        // create inactive
        m_ToolTip.Activate(FALSE);
    }
}
//---------------------------------------------------------------------------
void PSS_FlatButton::DrawIcon(CDC* pDC, CString* pTitle, RECT* pItemRect, CRect* pCaptionRect, BOOL isPressed, BOOL isDisabled)
{
    CRect iconRect = pItemRect;
    CRect btnRect;

    switch (m_Align)
    {
        case IE_ST_ALIGN_HORZ:
            if (pTitle->IsEmpty())
                // center the icon horizontally
                iconRect.left += ((iconRect.Width() - m_CxIcon) / 2);
            else
            {
                // the icon must appear immediately inside the focus rect
                iconRect.left      += 3;
                pCaptionRect->left += m_CxIcon + 3;
            }

            // center the icon vertically
            iconRect.top += ((iconRect.Height() - m_CyIcon) / 2);
            break;

        case IE_ST_ALIGN_HORZ_RIGHT:
            GetClientRect(&btnRect);

            if (pTitle->IsEmpty())
                // center the icon horizontally
                iconRect.left += ((iconRect.Width() - m_CxIcon) / 2);
            else
            {
                // the icon must appear immediately inside the focus rect
                pCaptionRect->right = pCaptionRect->Width() - m_CxIcon - 3;
                pCaptionRect->left  = 3;
                iconRect.left       = btnRect.right - m_CxIcon - 3;

                // center the icon vertically
                iconRect.top += ((iconRect.Height() - m_CyIcon) / 2);
            }

            break;

        case IE_ST_ALIGN_VERT:
            // center the icon horizontally
            iconRect.left += ((iconRect.Width() - m_CxIcon) / 2);

            if (pTitle->IsEmpty())
                // center the icon vertically
                iconRect.top += ((iconRect.Height() - m_CyIcon) / 2);
            else
                pCaptionRect->top += m_CyIcon;

            break;
    }

    // if button is pressed then press the icon also
    if (isPressed)
        iconRect.OffsetRect(1, 1);

    pDC->DrawState(iconRect.TopLeft(),
                   iconRect.Size(),
                   (m_MouseOnButton || isPressed) ? m_hIconIn : m_hIconOut,
                   (isDisabled ? DSS_DISABLED : DSS_NORMAL),
                   (CBrush*)NULL);
}
//---------------------------------------------------------------------------
void PSS_FlatButton::PaintBk(CDC * pDC)
{
    CClientDC clDC(GetParent());

    CRect rect;
    GetClientRect(rect);

    CRect rect1;
    GetWindowRect(rect1);

    GetParent()->ScreenToClient(rect1);

    if (!m_DcBk.m_hDC)
    {
        m_DcBk.CreateCompatibleDC(&clDC);
        m_BmpBk.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
        m_pBmpOldBk = m_DcBk.SelectObject(&m_BmpBk);
        m_DcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
    }

    pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_DcBk, 0, 0, SRCCOPY);
}
//---------------------------------------------------------------------------
