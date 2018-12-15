// animate.cpp : implementation file
//

#include "stdafx.h"
#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif
#include "animate.h"
#include "zBaseLib\draw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

const    UINT uiLastID = IDB_BITMAP17;
const    UINT uiFirstID = IDB_BITMAP1;


/////////////////////////////////////////////////////////////////////////////
// ZIAnimateDlg dialog


ZIAnimateDlg::ZIAnimateDlg( CWnd* pParent /*=NULL*/ )
:     m_uID( uiFirstID ),
    m_bStop( FALSE )
{
    //{{AFX_DATA_INIT(ZIAnimateDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    // Calculate the rect
    // of the bitmap for the invalidate
    // rect.
    CPoint        pt;
#ifndef _WIN32
    GetSizeOfBitmapFile( MAKEINTRESOURCE (uiFirstID), extensionZWinUtilDLL.hModule, &pt );
#else // Only in 16bit
    GetSizeOfBitmapFile( MAKEINTRESOURCE (uiFirstID), extensionZWinUtil32DLL.hModule, &pt );
#endif // Only in 32bit

    m_ImageRect.left = 10;
    m_ImageRect.top = 10;
    m_ImageRect.right = m_ImageRect.left + pt.x;
    m_ImageRect.bottom = m_ImageRect.top + pt.y;
    Create( IDD_ANIMATEDLG, pParent );
    ShowWindow( SW_SHOW );
}

BOOL ZIAnimateDlg::DisplayNext()
{
    if (m_bStop)
    {
        CloseAnimation();
        return FALSE;
    }
    m_uID = ( m_uID > uiLastID ) ? uiFirstID : m_uID + 1;
    CDC*    pDC = GetDC();
    ASSERT( pDC );
#ifndef _WIN32
    DisplayBitmapFile/*Extent*/( MAKEINTRESOURCE (m_uID), 
                             pDC->m_hDC, extensionZWinUtilDLL.hModule, 
                             10, 10 ); 
//                             SRCAND );
#else // Only in 16bit
    DisplayBitmapFile/*Extent*/( MAKEINTRESOURCE (m_uID), 
                             pDC->m_hDC, extensionZWinUtil32DLL.hModule,
                             10, 10 ); 
//                             SRCAND );
#endif // Only in 32bit
    VERIFY( ReleaseDC( pDC ) );
    return TRUE;
}

void ZIAnimateDlg::CloseAnimation()
{
    DestroyWindow();
}

void ZIAnimateDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIAnimateDlg)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZIAnimateDlg, CDialog)
    //{{AFX_MSG_MAP(ZIAnimateDlg)
    ON_WM_ERASEBKGND()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIAnimateDlg message handlers

void ZIAnimateDlg::OnCancel()
{
    m_bStop = TRUE;
}

BOOL ZIAnimateDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    // Put the window in the center of the screen    
    CRect    rect;
    GetClientRect( &rect );
    CRect    ClientRect;
    UINT    uiX, uiY;
    uiX = GetSystemMetrics( SM_CXFULLSCREEN );
    uiY = GetSystemMetrics( SM_CYFULLSCREEN );
    SetWindowPos( NULL, (uiX - rect.right) / 2, (uiY - rect.bottom) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}


BOOL ZIAnimateDlg::OnEraseBkgnd(CDC* pDC)
{
    ASSERT_VALID(pDC);

    // Fill background with APPWORKSPACE
    CBrush backBrush( defCOLOR_LTGRAY );
    CBrush* pOldBrush = pDC->SelectObject(&backBrush);
    CRect rect;
    pDC->GetClipBox(&rect);     // Erase the area needed

    pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
    pDC->SelectObject(pOldBrush);

    return( TRUE );
}
