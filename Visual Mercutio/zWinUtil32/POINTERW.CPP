// pointerw.cpp : implementation file
//

#include "stdafx.h"
#include "PointerW.h"
#include "zBaseLib\Draw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// ZIPointerWnd

IMPLEMENT_DYNAMIC(ZIPointerWnd, CWnd)

ZIPointerWnd::ZIPointerWnd()
 :     m_uID( IDB_POINTERWINDOW ),
     m_bStartPointer( FALSE ),
     m_pWndMessage( NULL )
{
#ifndef _WIN32
    // 16 bit only
    m_hcurPointer = ::LoadCursor(g_zWinUtilDLL.hModule, MAKEINTRESOURCE(IDC_POINTER));
#else
    // 32 bit only
    m_hcurPointer = ::LoadCursor(g_zWinUtil32DLL.hModule, MAKEINTRESOURCE(IDC_POINTER));
#endif
}

ZIPointerWnd::~ZIPointerWnd()
{
}

void    ZIPointerWnd::Create(CWnd *pWndMessage, CRect& Rect, CWnd* pParent)
{
    m_pWndMessage = pWndMessage;
    CWnd::Create( NULL, "PointerWindow",
                    WS_CHILD | WS_VISIBLE,
                  Rect,
                  pParent,
                  IDC_POINTER );
}

void    ZIPointerWnd::AssignMessageWnd(CWnd *pWndMessage)
{
    m_pWndMessage = pWndMessage;
}


BEGIN_MESSAGE_MAP(ZIPointerWnd, CWnd)
    //{{AFX_MSG_MAP(ZIPointerWnd)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIPointerWnd message handlers


void ZIPointerWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
    SetCapture();
    m_uID = IDB_POINTERWINDOWEMPTY;
    m_bStartPointer = TRUE;
    SetCursor( m_hcurPointer );
    Invalidate();
    UpdateWindow();
}

void ZIPointerWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
    CWnd::OnLButtonUp(nFlags, point);
    ReleaseCapture();
    m_uID = IDB_POINTERWINDOW;
    Invalidate();
    UpdateWindow();
    TRACE(" On Mouse Button UP Pointer " );

    if (m_bStartPointer && m_pWndMessage)
        // To notify the view that a field has been selected
        // Pass the adress of the object.
        m_pWndMessage->SendMessageToDescendants( ID_POINTERHASSELECTED );
    m_bStartPointer = FALSE;
}

void ZIPointerWnd::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_bStartPointer)
    {
        ClientToScreen( &point );
    
        SetCursor( m_hcurPointer );
        // To notify the view that a field can be selected
        // Pass the adress of the point object
        // can know which point is selected
        if (m_pWndMessage)
            m_pWndMessage->SendMessageToDescendants( ID_POINTERINSELECTION, 0, (LPARAM)&point );
        TRACE(" On Mouse Move Pointer " );
    }
}


void ZIPointerWnd::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    // Find the resource instance handle
    HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE (m_uID), RT_BITMAP);
    
    DisplayBitmapFile( MAKEINTRESOURCE (m_uID), dc.m_hDC, hInst, 0, 0 );
}




