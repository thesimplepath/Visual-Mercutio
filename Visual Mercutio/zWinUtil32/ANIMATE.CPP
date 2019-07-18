// animate.cpp : implementation file
//

#include "StdAfx.h"
#include "animate.h"

// processsoft
#include "zBaseLib\draw.h"

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

const UINT uiLastID = IDB_BITMAP17;
const UINT uiFirstID = IDB_BITMAP1;

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
    // 16 bit only
    GetSizeOfBitmapFile(MAKEINTRESOURCE(uiFirstID), g_zWinUtilDLL.hModule, &pt);
#else
    // 32 bit only
    GetSizeOfBitmapFile(MAKEINTRESOURCE(uiFirstID), g_zWinUtil32DLL.hModule, &pt);
#endif

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
    // 16 bit only
    DisplayBitmapFile/*Extent*/( MAKEINTRESOURCE (m_uID), 
                             pDC->m_hDC, g_zWinUtilDLL.hModule, 
                             10, 10 ); 
//                             SRCAND );
#else
    // 32 bit only
    DisplayBitmapFile/*Extent*/( MAKEINTRESOURCE (m_uID), 
                             pDC->m_hDC, g_zWinUtil32DLL.hModule,
                             10, 10 ); 
//                             SRCAND );
#endif
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
