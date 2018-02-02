// HoverButton.cpp : implementation file
//

#include "stdafx.h"
#include "HoverButton.h"

#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZUHoverButton

BEGIN_MESSAGE_MAP(ZUHoverButton, CBitmapButton)
	//{{AFX_MSG_MAP(ZUHoverButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZUHoverButton construction / destruction

ZUHoverButton::ZUHoverButton()
{
	// To start with, the button is switched off and we are NOT tracking the mouse
	m_ButtonState		= BUTTON_OFF;
	m_bMouseTracking	= FALSE;
	LoadBitmaps( IDB_RBU, IDB_RBD, IDB_RBF, IDB_RBX );
}

ZUHoverButton::~ZUHoverButton()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZUHoverButton message handlers

void ZUHoverButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	CBitmapButton::OnMouseMove(nFlags, point);

	// 1. Mouse has moved and we are not tracking this button, or 
	// 2. mouse has moved and the cursor was not above this window
	// == Is equivalent to WM_MOUSEENTER (for which there is no message)
	if ((!m_bMouseTracking || GetCapture()!=this) && (m_ButtonState == BUTTON_OFF))
	{
		OnMouseEnter();
	}
	else 
	{
		if (m_ButtonState == BUTTON_OVER)
		{
			CRect rc;
			GetClientRect(&rc);
			if(!rc.PtInRect(point))	// The mouse cursor is no longer above this button
				OnMouseLeave();
		}
	}
}

void ZUHoverButton::OnMouseEnter(void)
{
	// We are now tracking the mouse, OVER this button
	m_bMouseTracking = TRUE;
	m_ButtonState = BUTTON_OVER;

	// Ensure that mouse input is sent to the button
	SetCapture();
	Invalidate();
	UpdateWindow();
}

void ZUHoverButton::OnMouseLeave(void)
{
	// We are not tracking the mouse, this button is OFF.
	m_ButtonState = BUTTON_OFF;
	m_bMouseTracking = FALSE;

	// Release mouse capture from the button and restore normal mouse input
	Invalidate();
	UpdateWindow();
	ReleaseCapture();
}


void ZUHoverButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	SetButtonState( BUTTON_ON );			// Highlight button
	CBitmapButton::OnLButtonUp( nFlags, point );
}

// Purpose:		Set the new state of the button 
// Return:		Returns the old state of the button
// Parameters:	nState = Either ON or OFF. The default is OFF. This is NOT tri-state button!
BUTTON_STATE ZUHoverButton::SetButtonState(BUTTON_STATE nState) 
{
	BUTTON_STATE nOldState = (BUTTON_STATE)GetCheck();
	
	m_ButtonState = nState;
	switch (m_ButtonState)
	{
		case BUTTON_ON:
		{
			EnableWindow(TRUE);
			SetState(BUTTON_ON);
			break;
		}
		case BUTTON_GREYED:
		{
			EnableWindow(FALSE);
			break;
		}
		case BUTTON_OVER:
		{
			EnableWindow(TRUE);
			SetState(BUTTON_OVER);
			break;
		}
		default:
		{
			EnableWindow(TRUE);
			SetState(BUTTON_OFF);
			m_ButtonState = BUTTON_OFF;
			break;
		}
	}
	return(nOldState);
}

// Draws the buttons in their relevant state, and text labels
void ZUHoverButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC			memDC;
	CBitmap*	pOld=NULL;
	CBitmap*	pBitmap=NULL;
	CDC*		pDC;
	CRect		rc;
	int			iSaveDC;

	CString		strTitle;
	GetWindowText(strTitle);

	pDC= CDC::FromHandle(lpDrawItemStruct->hDC);
	memDC.CreateCompatibleDC(pDC);
	VERIFY(pDC);
	iSaveDC=pDC->SaveDC();
	rc.CopyRect(&lpDrawItemStruct->rcItem);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(GetSysColor(COLOR_WINDOWFRAME));// Black text color


	switch (m_ButtonState)
	{
		case BUTTON_ON:
		{
			pBitmap=&m_bmpButtonDown;
			break;
		}
		case BUTTON_OVER:
		{
			pBitmap=&m_bmpButtonFocussed;
			break;
		}
		case BUTTON_GREYED:
		{
			pBitmap=&m_bmpButtonDisabled;
			break;
		}
		default:
		{
			pBitmap=&m_bmpButtonUp;
			break;
		}
	}

	if (pBitmap->m_hObject)
	{
		CRect	rcBitmap(rc);
		BITMAP	bmpInfo;			
		CSize	size;

		// Text
		size = pDC->GetTextExtent(strTitle);
		rcBitmap.OffsetRect(size.cx+5,0);

		// Draw bitmap
		if (!pBitmap->GetBitmap(&bmpInfo))
			return;
		pOld=memDC.SelectObject((CBitmap*) pBitmap);
		if (pOld==NULL) 
			return; //Destructors will clean up

		if (!pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY))
			return;
		memDC.SelectObject(pOld);	
		if (memDC==NULL)
			return;
	}

	CRect	rcText(rc);
	UINT nFormat = DT_LEFT;
	rcText.left += 20;

	switch (m_ButtonState)
	{
		case BUTTON_OVER:
		{
			pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
			pDC->DrawText(strTitle,rcText,nFormat);
			break;
		}
		case BUTTON_GREYED:
		{
			rcText.OffsetRect(1,1);
			pDC->SetTextColor(GetSysColor(COLOR_BTNHIGHLIGHT));
			pDC->DrawText(strTitle,rcText,nFormat);
			rcText.OffsetRect(-1,-1);
			pDC->SetTextColor(GetSysColor(COLOR_BTNSHADOW));
			pDC->DrawText(strTitle,rcText,nFormat);
			break;
		}
		case BUTTON_ON:
		default:
		{
			pDC->DrawText(strTitle,rcText,nFormat);
			break;
		}
	}

	pDC->RestoreDC(iSaveDC);
}

BOOL ZUHoverButton::LoadBitmaps(UINT nBitmapUp, UINT nBitmapDown, 
							   UINT nBitmapFocus, UINT nBitmapDisabled)
{
	BOOL bAllLoaded=TRUE;

	//Delete old ones
	m_bmpButtonDown.DeleteObject();
	m_bmpButtonFocussed.DeleteObject();
	m_bmpButtonUp.DeleteObject();
	m_bmpButtonDisabled.DeleteObject();
	
	if (!m_bmpButtonUp.LoadBitmap(nBitmapUp))
	{
		TRACE0("Failed to load up bitmap of bitmap button\n");
		return FALSE;
	}

	if (nBitmapDown > 0)
	{
		if (!m_bmpButtonDown.LoadBitmap(nBitmapDown))
		{
			TRACE0("Failed to load down bitmap of bitmap button\n");
			return bAllLoaded=FALSE;
		}
	}
	
	if (nBitmapFocus > 0)
	{
		if (!m_bmpButtonFocussed.LoadBitmap(nBitmapFocus))
		{
			TRACE0("Failed to load focussed bitmap of bitmap button\n");
			return bAllLoaded=FALSE;
		}
	}
	
	if (nBitmapDisabled > 0)
	{
		if (!m_bmpButtonDisabled.LoadBitmap(nBitmapDisabled))
		{
			TRACE0("Failed to load disabled bitmap of bitmap button\n");
			return bAllLoaded=FALSE;
		}
	}
	return bAllLoaded;
/*
	return LoadBitmaps(MAKEINTRESOURCE(nBitmapUp),
						MAKEINTRESOURCE(nBitmapDown),
						MAKEINTRESOURCE(nBitmapFocus),
						MAKEINTRESOURCE(nBitmapDisabled));
*/
}

BOOL ZUHoverButton::LoadBitmaps(LPCSTR lpszBitmapUp, LPCSTR lpszBitmapDown, 
							   LPCSTR lpszBitmapFocus, LPCSTR lpszBitmapDisabled)
{
	BOOL bAllLoaded=TRUE;

	//Delete old ones
	m_bmpButtonDown.DeleteObject();
	m_bmpButtonFocussed.DeleteObject();
	m_bmpButtonUp.DeleteObject();
	m_bmpButtonDisabled.DeleteObject();
	
	if (!m_bmpButtonUp.LoadBitmap(lpszBitmapUp))
	{
		TRACE0("Failed to load up bitmap of bitmap button\n");
		return FALSE;
	}

	if (lpszBitmapDown!=NULL)
	{
		if (!m_bmpButtonDown.LoadBitmap(lpszBitmapDown))
		{
			TRACE0("Failed to load down bitmap of bitmap button\n");
			return bAllLoaded=FALSE;
		}
	}
	
	if (lpszBitmapFocus!=NULL)
	{
		if (!m_bmpButtonFocussed.LoadBitmap(lpszBitmapFocus))
		{
			TRACE0("Failed to load focussed bitmap of bitmap button\n");
			return bAllLoaded=FALSE;
		}
	}
	
	if (lpszBitmapDisabled!=NULL)
	{
		if (!m_bmpButtonDisabled.LoadBitmap(lpszBitmapDisabled))
		{
			TRACE0("Failed to load disabled bitmap of bitmap button\n");
			return bAllLoaded=FALSE;
		}
	}
	return bAllLoaded;
}
