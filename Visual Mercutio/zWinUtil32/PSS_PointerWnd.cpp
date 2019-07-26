/****************************************************************************
 * ==> PSS_PointerWnd ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a pointer window                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PointerWnd.h"

// processsoft
#include "zBaseLib\Draw.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_PointerWnd, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PointerWnd, CWnd)
    //{{AFX_MSG_MAP(PSS_PointerWnd)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PointerWnd
//---------------------------------------------------------------------------
PSS_PointerWnd::PSS_PointerWnd() :
    CWnd(),
    m_pWndMessage(NULL),
    m_ID(IDB_POINTERWINDOW),
    m_StartPointer(FALSE)
{
    #ifndef _WIN32
        // 16 bit only
        m_hCurPointer = ::LoadCursor(g_zWinUtilDLL.hModule, MAKEINTRESOURCE(IDC_POINTER));
    #else
        // 32 bit only
        m_hCurPointer = ::LoadCursor(g_zWinUtil32DLL.hModule, MAKEINTRESOURCE(IDC_POINTER));
    #endif
}
//---------------------------------------------------------------------------
PSS_PointerWnd::~PSS_PointerWnd()
{}
//---------------------------------------------------------------------------
void PSS_PointerWnd::Create(CWnd* pWndMessage, CRect& rect, CWnd* pParent)
{
    m_pWndMessage = pWndMessage;

    CWnd::Create(NULL, "PointerWindow", WS_CHILD | WS_VISIBLE, rect, pParent, IDC_POINTER);
}
//---------------------------------------------------------------------------
void PSS_PointerWnd::AssignMessageWnd(CWnd* pWndMessage)
{
    m_pWndMessage = pWndMessage;
}
//---------------------------------------------------------------------------
void PSS_PointerWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
    SetCapture();

    m_ID           = IDB_POINTERWINDOWEMPTY;
    m_StartPointer = TRUE;

    SetCursor(m_hCurPointer);
    Invalidate();
    UpdateWindow();
}
//---------------------------------------------------------------------------
void PSS_PointerWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
    CWnd::OnLButtonUp(nFlags, point);

    ReleaseCapture();

    m_ID = IDB_POINTERWINDOW;

    Invalidate();
    UpdateWindow();

    TRACE(" On Mouse Button UP Pointer ");

    // to notify the view that a field has been selected. Pass the point object adress so can know which point is selected
    if (m_StartPointer && m_pWndMessage)
        m_pWndMessage->SendMessageToDescendants(ID_POINTERHASSELECTED);

    m_StartPointer = FALSE;
}
//---------------------------------------------------------------------------
void PSS_PointerWnd::OnMouseMove(UINT nFlags, CPoint point)
{
    if (!m_StartPointer)
        return;

    ClientToScreen(&point);
    
    SetCursor(m_hCurPointer);

    // to notify the view that a field can be selected. Pass the point object adress so can know which point is selected
    if (m_pWndMessage)
        m_pWndMessage->SendMessageToDescendants(ID_POINTERINSELECTION, 0, (LPARAM)&point);

    TRACE(" On Mouse Move Pointer ");
}
//---------------------------------------------------------------------------
void PSS_PointerWnd::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);

    // find the resource instance handle
    HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(m_ID), RT_BITMAP);
    
    DisplayBitmapFile(MAKEINTRESOURCE(m_ID), dc.m_hDC, hInst, 0, 0);
}
//---------------------------------------------------------------------------
