/****************************************************************************
 * ==> PSS_SplashWnd -------------------------------------------------------*
 ****************************************************************************
 * Description : Splash screen window                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SplashWnd.h"

// resources
#include "ZSplashRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SplashWnd, CWnd)
    //{{AFX_MSG_MAP(PSS_SplashWnd)
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SplashWnd
//---------------------------------------------------------------------------
PSS_SplashWnd::PSS_SplashWnd() :
    CWnd(),
    m_FontColor(RGB(20, 20, 20)),
    m_BackgroundColor(RGB(255, 255, 255)),
    m_IncludeProgress(false)
{}
//---------------------------------------------------------------------------
PSS_SplashWnd::~PSS_SplashWnd()
{}
//---------------------------------------------------------------------------
bool PSS_SplashWnd::CreateSplashWindow(bool includeProgress, CWnd* pParent)
{
    m_IncludeProgress = includeProgress;

    CString windowClass;

    try
    {
        windowClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW,
                                          ::LoadCursor(NULL, IDC_ARROW),
                                          HBRUSH(::GetStockObject(WHITE_BRUSH)),
                                          ::LoadIcon(NULL, MAKEINTRESOURCE(IDI_ZSPLASH_APP)));
    }
    catch (CResourceException* pEx)
    {
        AfxMessageBox(_T("Couldn't register class! (Already registered?)"));
        pEx->Delete();
        return false;
    }

    int height = m_Bitmap.GetSize().cy;

    if (m_IncludeProgress)
        height += 32;

    const DWORD dwStyle   = WS_POPUP | WS_BORDER;
    const DWORD dwExStyle = WS_EX_TOPMOST;

    if (!CWnd::CreateEx(dwExStyle,
                        windowClass,
                        "zSplashWindow",
                        dwStyle,
                        0,
                        0,
                        m_Bitmap.GetSize().cx,
                        height,
                        pParent->GetSafeHwnd(),
                        NULL))
        return false;

    CenterWindow();

    // only create progress control and text area if the flag has been set to true
    if (m_IncludeProgress)
    {
        GetClientRect(&m_TextRect);
        m_ProgressRect = m_TextRect;

        // assigns text coordinates
        m_TextRect.top = m_TextRect.bottom - 10;

        // assigns progress control coordinates
        m_ProgressRect.bottom = m_TextRect.top        - 1;
        m_ProgressRect.top    = m_ProgressRect.bottom - 21;

        // create the progress bar
        if (!m_ProgressControl.Create(WS_CHILD, m_ProgressRect, this, ID_SPLASH_PROGRESSCONTROL))
            return false;

        m_ProgressControl.SetRange(0, 100);
        m_ProgressControl.SetPos(0);

        // get the log font
        NONCLIENTMETRICS ncm;
        ncm.cbSize = sizeof(NONCLIENTMETRICS);
        VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));
        m_Font.CreateFontIndirect(&ncm.lfMessageFont);

        // set the font color
        m_FontColor = RGB(0, 0, 0);

        // set the background color
        m_BackgroundColor = ::GetSysColor(COLOR_BTNFACE);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SplashWnd::Show()
{
    if (!m_Bitmap.IsValid())
        return false;

    // show the Window
    ShowWindow(SW_SHOW);

    if (m_IncludeProgress)
        m_ProgressControl.ShowWindow(SW_SHOW);

    UpdateWindow();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SplashWnd::Hide()
{
    DestroyWindow();
    return true;
}
//---------------------------------------------------------------------------
void PSS_SplashWnd::Update()
{
    UpdateWindow();
}
//---------------------------------------------------------------------------
void PSS_SplashWnd::SetParent(CWnd* pParent)
{
    if (pParent)
        CWnd::SetParent(pParent);
}
//---------------------------------------------------------------------------
void PSS_SplashWnd::SetText(const CString& value)
{
    if (m_IncludeProgress && ::IsWindow(GetSafeHwnd()))
    {
        m_Text = value;
        InvalidateRect(&m_TextRect);
    }
}
//---------------------------------------------------------------------------
void PSS_SplashWnd::SetText(UINT resID)
{
    if (m_IncludeProgress && ::IsWindow(GetSafeHwnd()))
    {
        CString value;
        value.LoadString(resID);
        m_Text = value;
        InvalidateRect(&m_TextRect);
    }
}
//---------------------------------------------------------------------------
void PSS_SplashWnd::SetProgress(std::size_t value)
{
    if (m_IncludeProgress && ::IsWindow(m_ProgressControl.GetSafeHwnd()))
        m_ProgressControl.SetPos(value);
}
//---------------------------------------------------------------------------
bool PSS_SplashWnd::LoadBitmapImage(LPCTSTR pFileName)
{
    return m_Bitmap.LoadBitmapFromFile(pFileName);
}
//---------------------------------------------------------------------------
bool PSS_SplashWnd::LoadBitmapImage(UINT resID)
{
    return m_Bitmap.LoadBitmap(resID);
}
//---------------------------------------------------------------------------
void PSS_SplashWnd::OnPaint()
{
    // get device context for painting
    CPaintDC dc(this);
    
    if (m_Bitmap.IsValid())
        m_Bitmap.DrawBitmap(&dc);

    if (m_IncludeProgress)
    {
        dc.FillSolidRect(&m_TextRect, m_BackgroundColor);
        dc.SetTextColor(m_FontColor);
        dc.SetBkMode(TRANSPARENT);
        dc.SetTextAlign(TA_BOTTOM);

        CFont* pOldFont = dc.SelectObject(&m_Font);
        dc.TextOut(m_TextRect.left, m_TextRect.bottom, m_Text);
        
        dc.SelectObject(pOldFont);
    }

    // NOTE do not call CWnd::OnPaint() for painting messages
}
//---------------------------------------------------------------------------
