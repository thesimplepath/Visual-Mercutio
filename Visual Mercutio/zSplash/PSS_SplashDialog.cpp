/****************************************************************************
 * ==> PSS_SplashDialog ----------------------------------------------------*
 ****************************************************************************
 * Description : Splash screen dialog                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SplashDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SplashDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_SplashDialog)
    ON_WM_LBUTTONDBLCLK()
    ON_WM_LBUTTONUP()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SplashDialog
//---------------------------------------------------------------------------
PSS_SplashDialog::PSS_SplashDialog(UINT resID, const CString& info, CWnd* pParent) :
    CDialog(PSS_SplashDialog::IDD, pParent),
    m_Info(info),
    m_BitmapResID(resID)
{}
//---------------------------------------------------------------------------
PSS_SplashDialog::PSS_SplashDialog(LPCTSTR pFileName, const CString& info, CWnd* pParent) :
    CDialog(PSS_SplashDialog::IDD, pParent),
    m_BitmapFileName(pFileName),
    m_Info(info),
    m_BitmapResID(0)
{}
//---------------------------------------------------------------------------
PSS_SplashDialog::~PSS_SplashDialog()
{}
//---------------------------------------------------------------------------
BOOL PSS_SplashDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // check if the constructor has been called correctly
    if (m_BitmapFileName.IsEmpty() && !m_BitmapResID)
        return false;

    // do load image from resources?
    if (m_BitmapResID)
    {
        // load image from resources
        if (!m_Bitmap.LoadBitmap(m_BitmapResID))
            return false;
    }
    else
    // load image from file
    if (!m_Bitmap.LoadBitmapFromFile(m_BitmapFileName))
        return false;

    if (m_Bitmap.IsValid())
        if (!SetWindowPos(&wndTopMost, 0, 0, m_Bitmap.GetSize().cx, m_Bitmap.GetSize().cy, SWP_NOMOVE | SWP_NOREDRAW))
            return false;

    CenterWindow();

    GetClientRect(&m_InfoRect);
    m_InfoRect.left = m_InfoRect.right  - 200;
    m_InfoRect.top  = m_InfoRect.bottom - 80;

    // get the log font
    NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));
    m_Font.CreateFontIndirect(&ncm.lfMessageFont);

    // set the font color
    m_FontColor = RGB(0, 0, 0);

    // set the background color
    m_BackgroundColor = ::GetSysColor(COLOR_BTNFACE);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should also return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SplashDialog::OnLButtonDblClk(UINT flags, CPoint point)
{
    CDialog::OnLButtonDblClk(flags, point);
    EndDialog(IDCANCEL);
}
//---------------------------------------------------------------------------
void PSS_SplashDialog::OnLButtonUp(UINT flags, CPoint point)
{
    CDialog::OnLButtonUp(flags, point);
    EndDialog(IDCANCEL);
}
//---------------------------------------------------------------------------
void PSS_SplashDialog::OnPaint()
{
    // get device context for painting
    CPaintDC dc(this);

    // draw the background bitmap
    if (m_Bitmap.IsValid())
        m_Bitmap.DrawBitmap(&dc);

    // draw the info text
    if (!m_Info.IsEmpty())
    {
        dc.SetTextColor(m_FontColor);
        dc.SetBkMode(TRANSPARENT);
        dc.SetTextAlign(0);

        CFont* pOldFont = NULL;

        try
        {
            pOldFont = dc.SelectObject(&m_Font);
            dc.DrawText(m_Info, m_InfoRect, DT_LEFT | DT_WORDBREAK | DT_TOP);
        }
        catch (...)
        {
            dc.SelectObject(pOldFont);
            throw;
        }

        dc.SelectObject(pOldFont);
    }

    // NOTE do not call CDialog::OnPaint() for painting messages
}
//---------------------------------------------------------------------------
void PSS_SplashDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}
//---------------------------------------------------------------------------
