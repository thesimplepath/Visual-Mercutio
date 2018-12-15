// aniload.cpp : implementation file

#include "StdAfx.h"
#include "aniload.h"
#include "draw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 21 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIStatusBar

IMPLEMENT_DYNCREATE( ZIStatusBar, SECStatusBar )

HBITMAP    ZIStatusBar::m_hBtmBack;
HBITMAP    ZIStatusBar::m_hBtmGreenLight;
HBITMAP    ZIStatusBar::m_hBtmRedLight;

BEGIN_MESSAGE_MAP( ZIStatusBar, SECStatusBar )
    //{{AFX_MSG_MAP(ZIStatusBar)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZIStatusBar::ZIStatusBar()
    : m_SwapLight( FALSE )
{
    m_iPerc                = 0;
    m_hBtmBack            = LoadBitmap ( ZBaseLibDLL.hModule, MAKEINTRESOURCE( IDB_ANILOADBACK ) );
    m_hBtmGreenLight    = LoadBitmap ( ZBaseLibDLL.hModule, MAKEINTRESOURCE( IDB_GREENLIGHT ) );
    m_hBtmRedLight        = LoadBitmap ( ZBaseLibDLL.hModule, MAKEINTRESOURCE( IDB_REDLIGHT ) );

    BITMAP bm;
    GetObject ( m_hBtmBack, sizeof ( BITMAP ), &bm );
    m_iBackWidth = bm.bmWidth + 1;

    // Calculate the step
    m_iStep = m_iBackWidth / 100;

    // Create the font
    VERIFY( m_Font.CreateFont( 10,                    // Height
                               8,                    // Width
                               0,                    // Escapment
                               0,                    // Orientation
                               FW_MEDIUM,            // Weight
                               0,                    // Italic
                               0,                    // Underline
                               0,                    // StrikeOut
                               DEFAULT_CHARSET,
                               OUT_DEVICE_PRECIS,
                               CLIP_TT_ALWAYS,
                               PROOF_QUALITY,
                               DEFAULT_PITCH,
                               _T( "Courier" ) ) );

    m_LtBlueBrush.CreateSolidBrush( defCOLOR_LTBLUE );
    m_BlackPen.CreatePen( PS_SOLID, 1, defCOLOR_BLACK );
    m_WhitePen.CreatePen( PS_SOLID, 1, defCOLOR_WHITE );
}

ZIStatusBar::~ZIStatusBar()
{
    VERIFY( DeleteObject( m_hBtmBack ) );
    VERIFY( DeleteObject( m_hBtmGreenLight ) );
    VERIFY( DeleteObject( m_hBtmRedLight ) );
}

BOOL ZIStatusBar::PreCreateWindow( CREATESTRUCT& cs )
{
    // Add gripper
    cs.style |= SBARS_SIZEGRIP;
    return SECStatusBar::PreCreateWindow( cs );
}

void ZIStatusBar::SetCurrentPercentage( int iPerc )
{
    // Check if started
    if( !m_bIsStarted )
    {
        return;
    }

    if( m_iPerc != iPerc )
    {
        m_iPerc = __min( 100, iPerc );

        // Calculate the size of the left meter
        m_iLeftStart += m_iStep;

        // To regulate the animation time
        // Check the elapsed time between two
        // animation and change the image only
        // if the time is greater than a certain
        // value.
        BOOL    bDisplay = TRUE;
        DWORD    dwTemp = GetTickCount();

        if( m_dwTickCount )
        {
            if( dwTemp - m_dwTickCount < 50 )
            {
                bDisplay = FALSE;
            }
            else
            {
                m_dwTickCount = dwTemp;
            }
        }
        else
        {
            m_dwTickCount = dwTemp;
        }

        CDC* pDC = GetDC();
        ASSERT( pDC );

        if ( m_iLeftStart < m_iBackWidth )
        {
            // Display the meter
            CPen*    pOldPen;
            CBrush*    pOldBrush;

            pOldBrush = pDC->SelectObject( &m_LtBlueBrush );
            pOldPen = pDC->SelectObject( &m_BlackPen );

            pDC->Rectangle( m_ItemRect.left + 2,
                            m_ItemRect.top + 2,
                            m_ItemRect.left + m_iLeftStart,
                            m_ItemRect.bottom - 1 );

            pDC->SelectObject( &m_WhitePen );
            pDC->MoveTo( m_ItemRect.left + m_iLeftStart - 2, m_ItemRect.bottom - 2 );
            pDC->LineTo( m_ItemRect.left + 2, m_ItemRect.bottom - 2 );
            pDC->LineTo( m_ItemRect.left + 2, m_ItemRect.top + 2 );
    
            pDC->SelectObject( pOldBrush );
            pDC->SelectObject( pOldPen );
        }

        if( bDisplay )
        {
            if ( m_SwapLight )
            {
                DisplayBitmap ( m_hBtmGreenLight,
                                pDC->m_hDC,
                                AfxGetInstanceHandle(),
                                m_ItemRect.left + m_iBackWidth,
                                m_ItemRect.top );
            }
            else
            {
                DisplayBitmap ( m_hBtmRedLight,
                                pDC->m_hDC,
                                AfxGetInstanceHandle(),
                                m_ItemRect.left + m_iBackWidth,
                                m_ItemRect.top );
            }

            // Switch the light
            m_SwapLight = ( m_SwapLight ) ? FALSE : TRUE;
        }

        VERIFY( ReleaseDC( pDC ) );
    }
}

void ZIStatusBar::BeginAniPercentage()
{
    // Create the timer for the animation
    m_bIsStarted    = TRUE;
    m_iImage        = 0;
    m_iPerc            = 0;
    m_dwTickCount    = 0;

    // Calculate the start position
    m_iLeftStart = 5;
    GetItemRect( 0, &m_ItemRect );

    CDC* pDC = GetDC();
    ASSERT( pDC );

    DisplayBitmap ( m_hBtmBack,
                    pDC->m_hDC,
                    AfxGetInstanceHandle(),
                    m_ItemRect.left,
                    m_ItemRect.top );

    // Displays the first percentage
    CPen*    pOldPen;
    CBrush*    pOldBrush;
    pOldBrush = pDC->SelectObject( &m_LtBlueBrush );
    pOldPen = pDC->SelectObject( &m_BlackPen );

    pDC->Rectangle( m_ItemRect.left + 2,
                    m_ItemRect.top + 2,
                    m_ItemRect.left + m_iLeftStart,
                    m_ItemRect.bottom - 1 );

    pDC->SelectObject( &m_WhitePen );
    pDC->MoveTo( m_ItemRect.left + m_iLeftStart - 2, m_ItemRect.bottom - 2 );
    pDC->LineTo( m_ItemRect.left + 2, m_ItemRect.bottom - 2 );
    pDC->LineTo( m_ItemRect.left + 2, m_ItemRect.top + 2 );

    pDC->SelectObject( pOldBrush );
    pDC->SelectObject( pOldPen );
    VERIFY( ReleaseDC( pDC ) );
}

void ZIStatusBar::EndAniPercentage()
{
    Invalidate( TRUE );
}
