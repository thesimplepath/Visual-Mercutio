// colorsel.cpp : implementation file
//

#include "stdafx.h"
#include "colorsel.h"
#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(ZIColorSelection, CWnd);

// static members
CString near     ZIColorSelection::m_strClassName = "";
CFont     near     ZIColorSelection::m_fntFont;
COLORREF        ZIColorSelection::m_ColorTable[24] = {     RGB(0,0,0),

                                                        RGB(255,255,255),
                                                        RGB(0,255,255),
                                                        RGB(255,0,255),
                                                        RGB(255,255,0),
                                                        RGB(0,0,255),
                                                        RGB(0,255,0),
                                                        RGB(255,0,0),
                                                        
                                                        RGB(128,128,128),
                                                        RGB(0,128,128),
                                                        RGB(128,0,128),
                                                        RGB(128,128,0),
                                                        RGB(0,0,128),
                                                        RGB(0,128,0),
                                                        RGB(128,0,0),
                                                        
                                                        RGB(192,192,192),
                                                        RGB(0,192,192),
                                                        RGB(192,0,192),
                                                        RGB(192,192,0),
                                                        RGB(0,0,192),
                                                        RGB(0,192,0),
                                                        RGB(192,0,0),

                                                        RGB(128,128,192),
                                                        RGB(255,0,128)
                                                    };

/////////////////////////////////////////////////////////////////////////////
// ZIColorSelection

ZIColorSelection::ZIColorSelection( COLORREF col )
 :     m_Col( col ), m_OldCol( col ), m_bChoosed( FALSE ),
    m_CurrentX( 0 ), m_CurrentY( 0 )
{
}

ZIColorSelection::~ZIColorSelection()
{
}


BOOL ZIColorSelection::Create()
{
    // create our bubble window but leave it invisible
        
    // do we need to register the class?
    if(m_strClassName == "")
    {
        // yes
        
        // register the class name
        m_strClassName = ::AfxRegisterWndClass(CS_BYTEALIGNCLIENT | CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW, 0 ,0);
            
        // we're we successful?
        if(m_strClassName == "")
          return 0;  // return failed
    }
    CPoint    point;
    // calc the position based on the current screen cursor position
    ::GetCursorPos(&point);  // in screen coorinates
    
    // move half the cursor size down
    point.y += GetSystemMetrics(SM_CYCURSOR)/2;

    m_BlackPen.CreatePen( PS_SOLID, 1, defCOLOR_BLACK );
    m_WhitePen.CreatePen( PS_SOLID, 1, defCOLOR_WHITE );
    m_GrayPen.CreatePen( PS_SOLID, 1, defCOLOR_GRAY );
  
    // create the color selection window 
    CRect rect( point.x, 
                point.y, 
                (m_SizeSquare * m_NbSquare) + (m_SizeBorder * (m_NbSquare+1)),
                (m_SizeSquare * ((m_NbColor/m_NbSquare)+1)) + (m_SizeBorder * ((m_NbColor/m_NbSquare)+1)) );
    //WS_EX_TRANSPARENT
    if (!CreateEx(0, m_strClassName, "", WS_POPUP,
                       rect.left, rect.top, rect.right, rect.bottom, 
                       NULL, (HMENU)NULL))
        return FALSE;

    // do we need to create the font?
    if(m_fntFont.GetSafeHandle() == NULL)
    {
        // create the font
        
        CClientDC dc(this);  // used to calculate the font size
        TRY 
        {
          LOGFONT        lf;
            
          memset(&lf, 0, sizeof(LOGFONT));
              
          lf.lfHeight = -::MulDiv(TBX_FONT_SIZE, dc.GetDeviceCaps(LOGPIXELSY), 72);
          lf.lfCharSet = ANSI_CHARSET;
          lf.lfQuality = DEFAULT_QUALITY;
          lf.lfClipPrecision = CLIP_LH_ANGLES | CLIP_STROKE_PRECIS;
          lf.lfPitchAndFamily = FF_SWISS;
        
          m_fntFont.CreateFontIndirect(&lf);
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

void    ZIColorSelection::ChooseColor()
{
    if (!Create())
        return;
    ShowWindow( SW_SHOW );

    MSG msg;
    while (GetMessage(&msg, (HWND) NULL, 0, 0) && m_bChoosed == FALSE) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // call the base to destroy the window
    CWnd::DestroyWindow();
}

BEGIN_MESSAGE_MAP(ZIColorSelection, CWnd)
    //{{AFX_MSG_MAP(ZIColorSelection)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIColorSelection message handlers


void ZIColorSelection::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    CRect    rect;
    GetClientRect( &rect );
      CPen*    pOldPen;

    pOldPen = dc.SelectObject( &m_WhitePen );
    dc.MoveTo( rect.left, rect.bottom );
    dc.LineTo( rect.left, rect.top );
    dc.LineTo( rect.right, rect.top );

    dc.SelectObject( &m_BlackPen );
    dc.MoveTo( rect.right-1, rect.top );
    dc.LineTo( rect.right-1, rect.bottom-1 );
    dc.LineTo( rect.left, rect.bottom-1 );
    rect.InflateRect( -1, -1 );
    
    dc.SelectObject( &m_GrayPen );
    CBrush    Brush( defCOLOR_GRAY );
    CBrush*    pOldBrush = dc.SelectObject( &Brush );
    dc.Rectangle( &rect );
    
    dc.SelectObject( pOldPen );
    dc.SelectObject( pOldBrush );
    
    for (int y = 0; y < m_NbColor/m_NbSquare; ++y)
        for (int x = 0; x < m_NbSquare; ++x)
            DrawColor( dc, x, y, m_ColorTable[y*4+x], m_Col == m_ColorTable[y*4+x] );
    // Draw the Automatic box
    rect.InflateRect( 1, 1 );
    rect.left += m_SizeBorder;
    rect.right -= m_SizeBorder;
    rect.top = ((m_NbColor/m_NbSquare))*m_SizeSquare + m_SizeBorder + ((m_NbColor/m_NbSquare))*m_SizeBorder;
    rect.bottom -= m_SizeBorder;

    pOldPen = dc.SelectObject( &m_WhitePen );
    dc.MoveTo( rect.right-1, rect.top );
    dc.LineTo( rect.right-1, rect.bottom-1 );
    dc.LineTo( rect.left, rect.bottom-1 );

      dc.SelectObject( &m_BlackPen );
    dc.MoveTo( rect.left, rect.bottom );
    dc.LineTo( rect.left, rect.top );
    dc.LineTo( rect.right, rect.top );

    // select the font we're using
    CFont* oldFont = dc.SelectObject( &m_fntFont );
    CString        sText;
    sText.LoadString( IDS_AUTOMATIC_TEXT );
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor( defCOLOR_BLACK );
    dc.DrawText( sText, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER );

    // select the old font
    dc.SelectObject( oldFont );
    dc.SelectObject( pOldPen );
}



void ZIColorSelection::DrawColor( CDC& dc, int x, int y, COLORREF col, BOOL bHighLight )
{
    CRect    rect( x*m_SizeSquare + m_SizeBorder + x*m_SizeBorder,
                  y*m_SizeSquare + m_SizeBorder + y*m_SizeBorder,
                  x*m_SizeSquare + m_SizeBorder + x*m_SizeBorder + m_SizeSquare,
                  y*m_SizeSquare + m_SizeBorder + y*m_SizeBorder + m_SizeSquare
                );
    CBrush    Brush( col );
    CBrush*    pOldBrush = dc.SelectObject( &Brush );
      CPen*    pOldPen = dc.SelectObject( &m_BlackPen );
    dc.Rectangle( &rect );
    dc.SelectObject( pOldBrush );

    dc.SelectObject( &m_WhitePen );
    dc.MoveTo( rect.right-1, rect.top );
    dc.LineTo( rect.right-1, rect.bottom-1 );
    dc.LineTo( rect.left, rect.bottom-1 );

    if (bHighLight)
        DisplayHighlight( dc, rect, TRUE );
    dc.SelectObject( pOldPen );
}

void ZIColorSelection::DisplayHighlight( CDC& dc, CRect& rect, BOOL bDisplay )
{
      CPen*    pOldPen;
    if (bDisplay)
          pOldPen = dc.SelectObject( &m_BlackPen );
      else
          pOldPen = dc.SelectObject( &m_GrayPen );
    
    rect.InflateRect( 2, 2 );
    dc.MoveTo( rect.left, rect.bottom-1 );
    dc.LineTo( rect.left, rect.top );
    dc.LineTo( rect.right-1, rect.top );
    dc.LineTo( rect.right-1, rect.bottom-1 );
    dc.LineTo( rect.left, rect.bottom-1 );
    
    dc.SelectObject( pOldPen );
}

int ZIColorSelection::FindColorRect( CRect& rect )
{
    if (m_Col == -1)
    {
        int y = m_NbColor/m_NbSquare;
        int    x = m_NbSquare;
        rect.left = m_SizeBorder;
        rect.top = y*m_SizeSquare + m_SizeBorder + y*m_SizeBorder;
        rect.right = x*m_SizeSquare + m_SizeBorder + x*m_SizeBorder + m_SizeSquare;
        rect.bottom = y*m_SizeSquare + m_SizeBorder + y*m_SizeBorder + m_SizeSquare;
        return -1;
    }
    for (int y = 0; y < m_NbColor/m_NbSquare; ++y)
        for (int x = 0; x < m_NbSquare; ++x)
        {
            if (m_Col == m_ColorTable[y*4+x])
            {
                rect.left = x*m_SizeSquare + m_SizeBorder + x*m_SizeBorder;
                rect.top = y*m_SizeSquare + m_SizeBorder + y*m_SizeBorder;
                rect.right = x*m_SizeSquare + m_SizeBorder + x*m_SizeBorder + m_SizeSquare;
                rect.bottom = y*m_SizeSquare + m_SizeBorder + y*m_SizeBorder + m_SizeSquare;
                return y*4+x;
            }
        }
    return ErrorSelection;
}

int ZIColorSelection::FindColor( CPoint point, CRect& rect )
{
    // Search if in the automatic selection
    int iY = m_NbColor/m_NbSquare;
    int    iX = m_NbSquare;
    rect.left = m_SizeBorder;
    rect.top = iY*m_SizeSquare + m_SizeBorder + iY*m_SizeBorder;
    rect.right = iX*m_SizeSquare + m_SizeBorder + iX*m_SizeBorder + m_SizeSquare;
    rect.bottom = iY*m_SizeSquare + m_SizeBorder + iY*m_SizeBorder + m_SizeSquare;
    if (rect.PtInRect( point ))
        return -1;
    for (int y = 0; y < m_NbColor/m_NbSquare; ++y)
        for (int x = 0; x < m_NbSquare; ++x)
        {
            rect.left = x*m_SizeSquare + m_SizeBorder + x*m_SizeBorder;
            rect.top = y*m_SizeSquare + m_SizeBorder + y*m_SizeBorder;
            rect.right = x*m_SizeSquare + m_SizeBorder + x*m_SizeBorder + m_SizeSquare;
            rect.bottom = y*m_SizeSquare + m_SizeBorder + y*m_SizeBorder + m_SizeSquare;

            if (rect.PtInRect( point ))
                return y*4+x;
        }
    return ErrorSelection;
}

void ZIColorSelection::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_bChoosed = TRUE;
    int        iIndex;
    CRect    rect;
    iIndex = FindColor( point, rect );
    if (iIndex != ErrorSelection)
    {
        if (iIndex != -1)
            m_Col = m_ColorTable[iIndex];
        else
            m_Col = -1;
    }
    CWnd::OnLButtonDown(nFlags, point);
}

void ZIColorSelection::OnMouseMove(UINT nFlags, CPoint point)
{
    CRect    rectOld, rectNew;
    int        iIndexOld, iIndexNew;
    // If one color is selected
    // clear the area before
    iIndexOld = FindColorRect( rectOld );
    iIndexNew = FindColor( point, rectNew );
    if (iIndexOld != iIndexNew)
    {
        CDC*    pDC = GetDC();
        ASSERT( pDC );
        if (iIndexOld != ErrorSelection)
            DisplayHighlight( *pDC, rectOld, FALSE );
        if (iIndexNew != ErrorSelection)
            DisplayHighlight( *pDC, rectNew, TRUE );
        if (iIndexNew != -1)
            m_Col = m_ColorTable[iIndexNew];
        else
            m_Col = -1;
        ReleaseDC( pDC );
    }
    CWnd::OnMouseMove(nFlags, point);
}

void ZIColorSelection::OnKillFocus(CWnd* pNewWnd)
{
    CWnd::OnKillFocus(pNewWnd);
    m_bChoosed = TRUE;
}
