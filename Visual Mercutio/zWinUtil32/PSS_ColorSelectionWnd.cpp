/****************************************************************************
 * ==> PSS_ColorSelectionWnd -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a color selection window                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ColorSelectionWnd.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
#ifndef TBX_FONT_SIZE
    #define TBX_FONT_SIZE -8
#endif

const std::size_t g_SizeSquare     =  12;
const std::size_t g_NbSquare       =  4;
const std::size_t g_SizeBorder     =  3;
const std::size_t g_NbColor        =  24;
const int         g_ErrorSelection = -2;
//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
CString  near PSS_ColorSelectionWnd::m_ClassName = "";
CFont    near PSS_ColorSelectionWnd::m_Font;
COLORREF      PSS_ColorSelectionWnd::m_ColorTable[24] =
{
    RGB(0,   0,   0),
    RGB(255, 255, 255),
    RGB(0,   255, 255),
    RGB(255, 0,   255),
    RGB(255, 255, 0),
    RGB(0,   0,   255),
    RGB(0,   255, 0),
    RGB(255, 0,   0),
    RGB(128, 128, 128),
    RGB(0,   128, 128),
    RGB(128, 0,   128),
    RGB(128, 128, 0),
    RGB(0,   0,   128),
    RGB(0,   128, 0),
    RGB(128, 0,   0),
    RGB(192, 192, 192),
    RGB(0,   192, 192),
    RGB(192, 0,   192),
    RGB(192, 192, 0),
    RGB(0,   0,   192),
    RGB(0,   192, 0),
    RGB(192, 0,   0),
    RGB(128, 128, 192),
    RGB(255, 0,   128)
};
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ColorSelectionWnd, CWnd);
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ColorSelectionWnd, CWnd)
    //{{AFX_MSG_MAP(PSS_ColorSelectionWnd)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ColorSelectionWnd
//---------------------------------------------------------------------------
PSS_ColorSelectionWnd::PSS_ColorSelectionWnd(COLORREF color) :
    m_Col(color),
    m_OldCol(color),
    m_CurrentX(0),
    m_CurrentY(0),
    m_Selected(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ColorSelectionWnd::~PSS_ColorSelectionWnd()
{}
//---------------------------------------------------------------------------
BOOL PSS_ColorSelectionWnd::Create()
{
    // create a bubble window but leave it invisible
        
    // do register the class?
    if (m_ClassName == "")
    {
        // yes, register the class name
        m_ClassName = ::AfxRegisterWndClass(CS_BYTEALIGNCLIENT | CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW, 0 ,0);
            
        // successful?
        if (m_ClassName == "")
          return 0;
    }

    CPoint point;

    // calculate the position based on the current screen cursor position (in screen coorinates)
    ::GetCursorPos(&point);

    // move half the cursor size down
    point.y += GetSystemMetrics(SM_CYCURSOR) / 2;

    m_BlackPen.CreatePen(PS_SOLID, 1, defCOLOR_BLACK);
    m_WhitePen.CreatePen(PS_SOLID, 1, defCOLOR_WHITE);
    m_GrayPen.CreatePen (PS_SOLID, 1, defCOLOR_GRAY);
  
    // create the color selection window 
    const CRect rect(point.x, 
                     point.y, 
                    (g_SizeSquare * g_NbSquare) + (g_SizeBorder * (g_NbSquare + 1)),
                    (g_SizeSquare * ((g_NbColor / g_NbSquare)+1)) + (g_SizeBorder * ((g_NbColor / g_NbSquare) + 1)));

    // create the window
    if (!CreateEx(0, m_ClassName, "", WS_POPUP, rect.left, rect.top, rect.right, rect.bottom, NULL, (HMENU)NULL))
        return FALSE;

    // do we need to create the font?
    if (!m_Font.GetSafeHandle())
    {
        // used to calculate the font size
        CClientDC dc(this);

        // create the font
        TRY
        {
            LOGFONT lf;
            std::memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight         = -::MulDiv(TBX_FONT_SIZE, dc.GetDeviceCaps(LOGPIXELSY), 72);
            lf.lfCharSet        = ANSI_CHARSET;
            lf.lfQuality        = DEFAULT_QUALITY;
            lf.lfClipPrecision  = CLIP_LH_ANGLES | CLIP_STROKE_PRECIS;
            lf.lfPitchAndFamily = FF_SWISS;
            m_Font.CreateFontIndirect(&lf);
        }
        CATCH(CResourceException, e)
        {
            // font creation failed
            return FALSE;
        }
        END_CATCH
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ColorSelectionWnd::ChooseColor()
{
    if (!Create())
        return;

    ShowWindow(SW_SHOW);

    MSG msg;

    while (GetMessage(&msg, (HWND) NULL, 0, 0) && !m_Selected) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // call the base to destroy the window
    CWnd::DestroyWindow();
}
//---------------------------------------------------------------------------
void PSS_ColorSelectionWnd::OnLButtonDown(UINT flags, CPoint point)
{
    m_Selected = TRUE;

    CRect rect;

    const int index = FindColor(point, rect);

    if (index != g_ErrorSelection)
        m_Col = (index != -1 ? m_ColorTable[index] : -1);

    CWnd::OnLButtonDown(flags, point);
}
//---------------------------------------------------------------------------
void PSS_ColorSelectionWnd::OnMouseMove(UINT flags, CPoint point)
{
    CRect rectOld, rectNew;

    const int indexOld = FindColorRect(rectOld);
    const int indexNew = FindColor(point, rectNew);

    // if one color is selected, clear the area before
    if (indexOld != indexNew)
    {
        CDC* pDC = GetDC();
        PSS_Assert(pDC);

        if (indexOld != g_ErrorSelection)
            ShowHighlight(*pDC, rectOld, FALSE);

        if (indexNew != g_ErrorSelection)
            ShowHighlight(*pDC, rectNew, TRUE);

        m_Col = (indexNew != -1 ? m_ColorTable[indexNew] : -1);

        ReleaseDC(pDC);
    }

    CWnd::OnMouseMove(flags, point);
}
//---------------------------------------------------------------------------
void PSS_ColorSelectionWnd::OnKillFocus(CWnd* pNewWnd)
{
    CWnd::OnKillFocus(pNewWnd);

    m_Selected = TRUE;
}
//---------------------------------------------------------------------------
void PSS_ColorSelectionWnd::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);
    CRect    rect;
    GetClientRect(&rect);

    CPen* pOldPen = dc.SelectObject(&m_WhitePen);
    dc.MoveTo(rect.left, rect.bottom);
    dc.LineTo(rect.left, rect.top);
    dc.LineTo(rect.right, rect.top);

    dc.SelectObject(&m_BlackPen);
    dc.MoveTo(rect.right - 1, rect.top);
    dc.LineTo(rect.right - 1, rect.bottom - 1);
    dc.LineTo(rect.left, rect.bottom - 1);
    rect.InflateRect(-1, -1);
    
    dc.SelectObject(&m_GrayPen);
    CBrush  brush(defCOLOR_GRAY);
    CBrush* pOldBrush = dc.SelectObject(&brush);
    dc.Rectangle(&rect);
    
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);

    const int squareLines = g_NbColor / g_NbSquare;

    for (int y = 0; y < squareLines; ++y)
        for (int x = 0; x < g_NbSquare; ++x)
            DrawColor(dc, x, y, m_ColorTable[y * 4 + x], m_Col == m_ColorTable[y * 4 + x]);

    // draw the Automatic box
    rect.InflateRect(1, 1);
    rect.left   += g_SizeBorder;
    rect.right  -= g_SizeBorder;
    rect.top     = squareLines * g_SizeSquare + g_SizeBorder + squareLines * g_SizeBorder;
    rect.bottom -= g_SizeBorder;

    pOldPen = dc.SelectObject( &m_WhitePen );
    dc.MoveTo( rect.right-1, rect.top );
    dc.LineTo( rect.right-1, rect.bottom-1 );
    dc.LineTo( rect.left, rect.bottom-1 );

      dc.SelectObject( &m_BlackPen );
    dc.MoveTo( rect.left, rect.bottom );
    dc.LineTo( rect.left, rect.top );
    dc.LineTo( rect.right, rect.top );

    // select the font we're using
    CFont*  oldFont = dc.SelectObject(&m_Font);
    CString text;
    text.LoadString( IDS_AUTOMATIC_TEXT );
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(defCOLOR_BLACK);
    dc.DrawText(text, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    // select the old font
    dc.SelectObject(oldFont);
    dc.SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
void PSS_ColorSelectionWnd::DrawColor(CDC& dc, int x, int y, COLORREF color, BOOL highLight)
{
    CRect rect(x * g_SizeSquare + g_SizeBorder + x * g_SizeBorder,
               y * g_SizeSquare + g_SizeBorder + y * g_SizeBorder,
               x * g_SizeSquare + g_SizeBorder + x * g_SizeBorder + g_SizeSquare,
               y * g_SizeSquare + g_SizeBorder + y * g_SizeBorder + g_SizeSquare);

    CBrush  brush(color);
    CBrush* pOldBrush = dc.SelectObject(&brush);
    CPen*   pOldPen   = dc.SelectObject(&m_BlackPen);

    dc.Rectangle(&rect);
    dc.SelectObject(pOldBrush);

    dc.SelectObject(&m_WhitePen);
    dc.MoveTo(rect.right - 1, rect.top);
    dc.LineTo(rect.right - 1, rect.bottom - 1);
    dc.LineTo(rect.left, rect.bottom - 1);

    if (highLight)
        ShowHighlight(dc, rect, TRUE);

    dc.SelectObject( pOldPen );
}
//---------------------------------------------------------------------------
int PSS_ColorSelectionWnd::FindColor(const CPoint& point, CRect& rect)
{
    const int posY = g_NbColor / g_NbSquare;
    const int posX = g_NbSquare;

    rect.left   = g_SizeBorder;
    rect.top    = posY * g_SizeSquare + g_SizeBorder + posY * g_SizeBorder;
    rect.right  = posX * g_SizeSquare + g_SizeBorder + posX * g_SizeBorder + g_SizeSquare;
    rect.bottom = posY * g_SizeSquare + g_SizeBorder + posY * g_SizeBorder + g_SizeSquare;

    // automatic selection?
    if (rect.PtInRect(point))
        return -1;

    for (int y = 0; y < posY; ++y)
        for (int x = 0; x < g_NbSquare; ++x)
        {
            rect.left   = x * g_SizeSquare + g_SizeBorder + x * g_SizeBorder;
            rect.top    = y * g_SizeSquare + g_SizeBorder + y * g_SizeBorder;
            rect.right  = x * g_SizeSquare + g_SizeBorder + x * g_SizeBorder + g_SizeSquare;
            rect.bottom = y * g_SizeSquare + g_SizeBorder + y * g_SizeBorder + g_SizeSquare;

            if (rect.PtInRect(point))
                return y * 4 + x;
        }

    return g_ErrorSelection;
}
//---------------------------------------------------------------------------
int PSS_ColorSelectionWnd::FindColorRect(CRect& rect)
{
    const int lines = g_NbColor / g_NbSquare;

    if (m_Col == -1)
    {
        const int y = lines;
        const int x = g_NbSquare;
        rect.left   = g_SizeBorder;
        rect.top    = y * g_SizeSquare + g_SizeBorder + y * g_SizeBorder;
        rect.right  = x * g_SizeSquare + g_SizeBorder + x * g_SizeBorder + g_SizeSquare;
        rect.bottom = y * g_SizeSquare + g_SizeBorder + y * g_SizeBorder + g_SizeSquare;
        return -1;
    }

    for (int y = 0; y < lines; ++y)
        for (int x = 0; x < g_NbSquare; ++x)
            if (m_Col == m_ColorTable[y * 4 + x])
            {
                rect.left   = x * g_SizeSquare + g_SizeBorder + x * g_SizeBorder;
                rect.top    = y * g_SizeSquare + g_SizeBorder + y * g_SizeBorder;
                rect.right  = x * g_SizeSquare + g_SizeBorder + x * g_SizeBorder + g_SizeSquare;
                rect.bottom = y * g_SizeSquare + g_SizeBorder + y * g_SizeBorder + g_SizeSquare;
                return y * 4 + x;
            }

    return g_ErrorSelection;
}
//---------------------------------------------------------------------------
void PSS_ColorSelectionWnd::ShowHighlight(CDC& dc, CRect& rect, BOOL show)
{
    CPen* pOldPen = (show ? dc.SelectObject(&m_BlackPen) : dc.SelectObject(&m_GrayPen));
    
    rect.InflateRect(2, 2);
    dc.MoveTo(rect.left,      rect.bottom - 1);
    dc.LineTo(rect.left,      rect.top);
    dc.LineTo(rect.right - 1, rect.top);
    dc.LineTo(rect.right - 1, rect.bottom - 1);
    dc.LineTo(rect.left,      rect.bottom - 1);
    
    dc.SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
