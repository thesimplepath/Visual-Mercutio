/****************************************************************************
 * ==> PSS_HoverButton -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a hover button                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_HoverButton.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#endif
#ifdef _WIN32
    #include "zWinUtil32Res.h"
#endif

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_HoverButton, CBitmapButton)
    //{{AFX_MSG_MAP(PSS_HoverButton)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_HoverButton
//---------------------------------------------------------------------------
PSS_HoverButton::PSS_HoverButton() :
    CBitmapButton(),
    m_hWndOld(NULL),
    m_ButtonState(EHoverButtonState::E_HB_OFF),
    m_MouseTracking(FALSE)
{
    LoadBitmaps(IDB_RBU, IDB_RBD, IDB_RBF, IDB_RBX);
}
//---------------------------------------------------------------------------
PSS_HoverButton::~PSS_HoverButton()
{}
//---------------------------------------------------------------------------
EHoverButtonState PSS_HoverButton::SetButtonState(EHoverButtonState state)
{
    const EHoverButtonState oldState = EHoverButtonState(GetCheck());

    m_ButtonState = state;

    switch (m_ButtonState)
    {
        case EHoverButtonState::E_HB_ON:
            EnableWindow(TRUE);
            SetState(TRUE);
            break;

        case EHoverButtonState::E_HB_Greyed:
            EnableWindow(FALSE);
            SetState(TRUE);
            break;

        case EHoverButtonState::E_HB_Over:
            EnableWindow(TRUE);
            SetState(TRUE);
            break;

        default:
            EnableWindow(TRUE);
            SetState(FALSE);
            m_ButtonState = EHoverButtonState::E_HB_OFF;
            break;
    }

    return oldState;
}
//---------------------------------------------------------------------------
BOOL PSS_HoverButton::LoadBitmaps(UINT bitmapUp, UINT bitmapDown, UINT bitmapFocus, UINT bitmapDisabled)
{
    // delete old ones
    m_BmpButtonDown.DeleteObject();
    m_BmpButtonFocussed.DeleteObject();
    m_BmpButtonUp.DeleteObject();
    m_BmpButtonDisabled.DeleteObject();

    if (!m_BmpButtonUp.LoadBitmap(bitmapUp))
    {
        TRACE0("Failed to load up bitmap of bitmap button\n");
        return FALSE;
    }

    if (bitmapDown > 0 && !m_BmpButtonDown.LoadBitmap(bitmapDown))
    {
        TRACE0("Failed to load down bitmap of bitmap button\n");
        return FALSE;
    }

    if (bitmapFocus > 0 && !m_BmpButtonFocussed.LoadBitmap(bitmapFocus))
    {
        TRACE0("Failed to load focussed bitmap of bitmap button\n");
        return FALSE;
    }

    if (bitmapDisabled > 0 && !m_BmpButtonDisabled.LoadBitmap(bitmapDisabled))
    {
        TRACE0("Failed to load disabled bitmap of bitmap button\n");
        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_HoverButton::LoadBitmaps(LPCSTR pBitmapUp, LPCSTR pBitmapDown, LPCSTR pBitmapFocus, LPCSTR pBitmapDisabled)
{
    // delete old ones
    m_BmpButtonDown.DeleteObject();
    m_BmpButtonFocussed.DeleteObject();
    m_BmpButtonUp.DeleteObject();
    m_BmpButtonDisabled.DeleteObject();

    if (!pBitmapUp || !m_BmpButtonUp.LoadBitmap(pBitmapUp))
    {
        TRACE0("Failed to load up bitmap of bitmap button\n");
        return FALSE;
    }

    if (pBitmapDown && !m_BmpButtonDown.LoadBitmap(pBitmapDown))
    {
        TRACE0("Failed to load down bitmap of bitmap button\n");
        return FALSE;
    }

    if (pBitmapFocus && !m_BmpButtonFocussed.LoadBitmap(pBitmapFocus))
    {
        TRACE0("Failed to load focussed bitmap of bitmap button\n");
        return FALSE;
    }

    if (pBitmapDisabled && !m_BmpButtonDisabled.LoadBitmap(pBitmapDisabled))
    {
        TRACE0("Failed to load disabled bitmap of bitmap button\n");
        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_HoverButton::DrawItem(LPDRAWITEMSTRUCT pDrawItemStruct)
{
    if (!pDrawItemStruct)
        return;

    CString title;
    GetWindowText(title);

    CDC  memDC;
    CDC* pDC = CDC::FromHandle(pDrawItemStruct->hDC);
    memDC.CreateCompatibleDC(pDC);
    VERIFY(pDC);

    const int saveDC = pDC->SaveDC();

    try
    {
        CRect rc;
        rc.CopyRect(&pDrawItemStruct->rcItem);

        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(GetSysColor(COLOR_WINDOWFRAME));

        CBitmap* pBitmap = NULL;

        switch (m_ButtonState)
        {
            case EHoverButtonState::E_HB_ON:     pBitmap = &m_BmpButtonDown;     break;
            case EHoverButtonState::E_HB_Over:   pBitmap = &m_BmpButtonFocussed; break;
            case EHoverButtonState::E_HB_Greyed: pBitmap = &m_BmpButtonDisabled; break;
            default:                             pBitmap = &m_BmpButtonUp;       break;
        }

        if (pBitmap->m_hObject)
        {
            CRect  rcBitmap(rc);
            BITMAP bmpInfo;

            // measure text
            const CSize size = pDC->GetTextExtent(title);
            rcBitmap.OffsetRect(size.cx + 5, 0);

            // draw bitmap
            if (!pBitmap->GetBitmap(&bmpInfo))
                return;

            CBitmap* pOld = memDC.SelectObject((CBitmap*)pBitmap);

            // destructor will clean up
            if (!pOld)
                return;

            if (!pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY))
                return;

            memDC.SelectObject(pOld);

            if (!memDC.m_hDC)
                return;
        }

        const UINT format = DT_LEFT;

        CRect rcText(rc);
        rcText.left += 20;

        switch (m_ButtonState)
        {
            case EHoverButtonState::E_HB_Over:
                pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
                pDC->DrawText(title, rcText, format);
                break;

            case EHoverButtonState::E_HB_Greyed:
                rcText.OffsetRect(1, 1);
                pDC->SetTextColor(::GetSysColor(COLOR_BTNHIGHLIGHT));
                pDC->DrawText(title, rcText, format);
                rcText.OffsetRect(-1, -1);
                pDC->SetTextColor(::GetSysColor(COLOR_BTNSHADOW));
                pDC->DrawText(title, rcText, format);
                break;

            default:
                pDC->DrawText(title, rcText, format);
                break;
        }
    }
    catch (...)
    {
        if (pDC)
            pDC->RestoreDC(saveDC);

        throw;
    }

    pDC->RestoreDC(saveDC);
}
//---------------------------------------------------------------------------
void PSS_HoverButton::OnMouseMove(UINT flags, CPoint point)
{
    CBitmapButton::OnMouseMove(flags, point);

    // 1. Mouse has moved and we are not tracking this button, or
    // 2. mouse has moved and the cursor was not above this window
    // == Is equivalent to WM_MOUSEENTER (for which there is no message)
    if ((!m_MouseTracking || GetCapture() != this) && (m_ButtonState == EHoverButtonState::E_HB_OFF))
        OnMouseEnter();
    else
    if (m_ButtonState == EHoverButtonState::E_HB_Over)
    {
        CRect rc;
        GetClientRect(&rc);

        // if mouse isn't inside the rect surrounding the button, the cursor is no longer above this button
        if (!rc.PtInRect(point))
            OnMouseLeave();
    }
}
//---------------------------------------------------------------------------
void PSS_HoverButton::OnLButtonUp(UINT flags, CPoint point)
{
    // highlight button
    SetButtonState(EHoverButtonState::E_HB_ON);

    CBitmapButton::OnLButtonUp(flags, point);
}
//---------------------------------------------------------------------------
void PSS_HoverButton::OnMouseEnter(void)
{
    // track the mouse, set button to over state
    m_MouseTracking = TRUE;
    m_ButtonState   = EHoverButtonState::E_HB_Over;

    // ensure that mouse input is sent to the button
    SetCapture();
    Invalidate();
    UpdateWindow();
}
//---------------------------------------------------------------------------
void PSS_HoverButton::OnMouseLeave(void)
{
    // release the mouse tracking and set button to OFF state
    m_MouseTracking = FALSE;
    m_ButtonState   = EHoverButtonState::E_HB_OFF;

    // release mouse capture from the button and restore normal mouse input
    Invalidate();
    UpdateWindow();
    ReleaseCapture();
}
//---------------------------------------------------------------------------
