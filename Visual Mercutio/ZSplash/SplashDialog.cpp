// SplashDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SplashDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZSplashDialog dialog


ZSplashDialog::ZSplashDialog(UINT nResID /*= 0*/, const CString Info /*= ""*/, CWnd* pParent /*=NULL*/)
: CDialog(ZSplashDialog::IDD, pParent),
  m_Info(Info), m_BitmapResID(nResID)
{
	//{{AFX_DATA_INIT(ZSplashDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

ZSplashDialog::ZSplashDialog(LPCTSTR szFilename, const CString Info /*= ""*/, CWnd* pParent /*=NULL*/)
: CDialog(ZSplashDialog::IDD, pParent),
  m_Info(Info), m_BitmapFilename(szFilename), m_BitmapResID(0)
{
	//{{AFX_DATA_INIT(ZSplashDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ZSplashDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZSplashDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZSplashDialog, CDialog)
	//{{AFX_MSG_MAP(ZSplashDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZSplashDialog message handlers

void ZSplashDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if (m_Bitmap.IsValid())
		m_Bitmap.DrawBitmap( &dc );

	if (!m_Info.IsEmpty())
	{
		dc.SetTextColor( m_clrFont );
		dc.SetBkMode( TRANSPARENT );
		dc.SetTextAlign( 0 );
		CFont* oldFont = dc.SelectObject( &m_Font );
		dc.DrawText( m_Info, m_InfoRect, DT_LEFT | DT_WORDBREAK | DT_TOP );
		
		dc.SelectObject(oldFont);
	}
	// Do not call CDialog::OnPaint() for painting messages
}

void ZSplashDialog::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonDblClk(nFlags, point);

	EndDialog( IDCANCEL );
}

void ZSplashDialog::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonUp(nFlags, point);

	EndDialog( IDCANCEL );
}

BOOL ZSplashDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Check if the constructor has been called correctly
	if (m_BitmapFilename.IsEmpty() && m_BitmapResID == 0)
		return false;

	// Check which resource must be loaded
	if (m_BitmapResID != 0)
	{
		if (!m_Bitmap.LoadBitmap( m_BitmapResID ))
			return false;
	}
	else
	{
		if (!m_Bitmap.LoadBitmapFromFile( m_BitmapFilename ))
			return false;
	}
	
	if (m_Bitmap.IsValid())
	{
		if (!SetWindowPos( &wndTopMost, 0, 0, m_Bitmap.GetSize().cx, m_Bitmap.GetSize().cy, SWP_NOMOVE | SWP_NOREDRAW ))
			return false;
	}

	CenterWindow();

	GetClientRect( &m_InfoRect );
	m_InfoRect.left = m_InfoRect.right - 200;
	m_InfoRect.top = m_InfoRect.bottom - 80;
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

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
