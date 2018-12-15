// SplashWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SplashWnd.h"

#include "ZSplashRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// ZSplashWnd

ZSplashWnd::ZSplashWnd()
{
}

ZSplashWnd::~ZSplashWnd()
{
}

bool ZSplashWnd::LoadBitmapImage( LPCTSTR szFilename ) 
{
    return m_Bitmap.LoadBitmapFromFile( szFilename );
}


bool ZSplashWnd::LoadBitmapImage( UINT nResID ) 
{
    return m_Bitmap.LoadBitmap( nResID );
}

bool ZSplashWnd::Display() 
{
    if (!m_Bitmap.IsValid())
        return false;
    // Show the Window
    ShowWindow( SW_SHOW );
    
    if (m_IncludeProgress == true)
    {
        m_ProgressControl.ShowWindow( SW_SHOW );
    }

    UpdateWindow();

    return true;
}


void ZSplashWnd::Process()
{
    UpdateWindow();
}

void ZSplashWnd::SetProgress(size_t value)
{
    if (m_IncludeProgress == true && ::IsWindow(m_ProgressControl.GetSafeHwnd()))
    {
        m_ProgressControl.SetPos( value );
    }
}

void ZSplashWnd::SetText(const CString value)
{
    if (m_IncludeProgress == true && ::IsWindow(GetSafeHwnd()))
    {
        m_Text = value;
        InvalidateRect( &m_TextRect );
    }
}

void ZSplashWnd::SetText(UINT nResID)
{
    if (m_IncludeProgress == true && ::IsWindow(GetSafeHwnd()))
    {
        CString    value;
        value.LoadString( nResID );
        m_Text = value;
        InvalidateRect( &m_TextRect );
    }
}

void ZSplashWnd::AssignParentWindow(CWnd* pParentWnd)
{
    if (pParentWnd)
        SetParent( pParentWnd );
}

bool ZSplashWnd::EndDisplay() 
{
    DestroyWindow();
    return true;
}


bool ZSplashWnd::CreateSplashWindow( bool IncludeProgress, CWnd* pParentWnd ) 
{
    // Save the Include progress flag
    m_IncludeProgress = IncludeProgress;
    CString    WindowClass;
    try
    {
       WindowClass = AfxRegisterWndClass( CS_VREDRAW | CS_HREDRAW,
                                          ::LoadCursor(NULL, IDC_ARROW),
                                          (HBRUSH)::GetStockObject(WHITE_BRUSH),
                                          ::LoadIcon(NULL, MAKEINTRESOURCE(IDI_ZSPLASH_APP)));
    }
    catch (CResourceException* pEx)
    {
          AfxMessageBox(
             _T("Couldn't register class! (Already registered?)"));
          pEx->Delete();
    }

    int        Height = m_Bitmap.GetSize().cy;
    if (m_IncludeProgress == true)
        Height += 32;
    DWORD dwStyle = WS_POPUP | WS_BORDER;
    DWORD dwExStyle = WS_EX_TOPMOST; // | WS_EX_TRANSPARENT;
    if (!CWnd::CreateEx(dwExStyle, 
                        WindowClass, "zSplashWindow",
                        dwStyle, 
                        0, 0, 
                        m_Bitmap.GetSize().cx, Height, 
                        pParentWnd->GetSafeHwnd(), NULL))
        return false;
    CenterWindow();

    // Create progress control and text area
    // only if the flag has been set to true
    if (m_IncludeProgress == true)
    {
        GetClientRect( &m_TextRect );
        m_ProgressRect = m_TextRect;

        // Assigns text coordinates
        m_TextRect.top = m_TextRect.bottom - 10;

        // Assigns progress control coordinates
        m_ProgressRect.bottom = m_TextRect.top - 1;
        m_ProgressRect.top = m_ProgressRect.bottom - 21;

        // Create the progress bar
        if (!m_ProgressControl.Create( WS_CHILD, m_ProgressRect, this, ID_SPLASH_PROGRESSCONTROL ))
            return false;
        m_ProgressControl.SetRange( 0, 100 );
        m_ProgressControl.SetPos( 0 );


        // Get the log font.
        NONCLIENTMETRICS ncm;
        ncm.cbSize = sizeof(NONCLIENTMETRICS);
        VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
            sizeof(NONCLIENTMETRICS), &ncm, 0));
        m_Font.CreateFontIndirect(&ncm.lfMessageFont);
        // Set the font color
        m_clrFont = RGB(0,0,0);
        // Set the background color
        m_clrBackground = ::GetSysColor(COLOR_BTNFACE);
    }
    return true;
}

BEGIN_MESSAGE_MAP(ZSplashWnd, CWnd)
    //{{AFX_MSG_MAP(ZSplashWnd)
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZSplashWnd message handlers


void ZSplashWnd::OnPaint() 
{
    CPaintDC dc(this); // device context for painting
    
    if (m_Bitmap.IsValid())
        m_Bitmap.DrawBitmap( &dc );

    if (m_IncludeProgress == true)
    {
        dc.FillSolidRect( &m_TextRect, m_clrBackground );
        dc.SetTextColor( m_clrFont );
        dc.SetBkMode( TRANSPARENT );
        dc.SetTextAlign( TA_BOTTOM );
        CFont* oldFont = dc.SelectObject( &m_Font );
        dc.TextOut( m_TextRect.left, m_TextRect.bottom, m_Text );
        
        dc.SelectObject(oldFont);
    }
    // Do not call CWnd::OnPaint() for painting messages
}
