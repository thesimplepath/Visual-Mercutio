// ColorBtn.cpp : implementation file

#include "stdafx.h"
#include "ColorBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 21 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// The color table, initialized to windows' 20 static colors
COLORREF _ZVColorBtnDlg::colors[20] =
{
    RGB( 0, 0, 0 ),
    RGB( 128, 0, 0 ),
    RGB( 0, 128, 0 ),
    RGB( 128, 128, 0 ),
    RGB( 0, 0, 128 ),
    RGB( 128, 0, 128 ),
    RGB( 0, 128, 128 ),
    RGB( 192, 192, 192 ),
    RGB( 192, 220, 192 ),
    RGB( 166, 202, 240 ),
    RGB( 255, 251, 240 ),
    RGB( 160, 160, 164 ),
    RGB( 128, 128, 128 ),
    RGB( 255, 0, 0 ),
    RGB( 0, 255, 0 ),
    RGB( 255, 255, 0 ),
    RGB( 0, 0, 255 ),
    RGB( 255, 0, 255 ),
    RGB( 0, 255, 255 ),
    RGB( 255, 255, 255 )
};

// MRU table. See notes for Reset()
BYTE _ZVColorBtnDlg::used[20] =
{
    1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2    
};

/////////////////////////////////////////////////////////////////////////////
// _ZVColorBtnDlg dialog

BEGIN_MESSAGE_MAP( _ZVColorBtnDlg, CDialog )
    //{{AFX_MSG_MAP(_ZVColorBtnDlg)
    ON_BN_CLICKED(IDC_OTHER, OnOther)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_DRAWITEM()
    ON_COMMAND_RANGE(IDC_COLOR1,IDC_COLOR20,OnColor)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZVColorBtnDlg::_ZVColorBtnDlg( CWnd* pParent /*=NULL*/ )
    : CDialog( _ZVColorBtnDlg::IDD, pParent )
{
    //{{AFX_DATA_INIT(_ZVColorBtnDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

void _ZVColorBtnDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(_ZVColorBtnDlg)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// _ZVColorBtnDlg message handlers

BOOL _ZVColorBtnDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    RECT r,r2;
    
    parent->GetWindowRect( &r );

    // Move the dialog to be below the button
    SetWindowPos( NULL, r.left, r.bottom, 0, 0, SWP_NOSIZE | SWP_NOZORDER );

    GetWindowRect( &r2 );

    // Check to see if the dialog has a portion outside the
    // screen, if so, adjust.
    if ( r2.bottom > GetSystemMetrics( SM_CYSCREEN ) )
    {
        r2.top = r.top-(r2.bottom-r2.top);
    }

    if ( r2.right > GetSystemMetrics( SM_CXSCREEN ) )
    {
        r2.left = GetSystemMetrics( SM_CXSCREEN ) - ( r2.right - r2.left );
    }

    SetWindowPos( NULL, r2.left, r2.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER );

    // Capture the mouse, this allows the dialog to close when
    // the user clicks outside.
    // Remember that the dialog has no "close" button.
    SetCapture();

    return TRUE; 
}

void _ZVColorBtnDlg::EndDialog( int nResult )
{
    ReleaseCapture();

    CDialog::EndDialog( nResult );
}

void _ZVColorBtnDlg::OnLButtonDown( UINT nFlags, CPoint point )
{
    RECT r;

    POINT p;
    p.x = point.x;
    p.y = point.y;

    ClientToScreen( &p );

    GetWindowRect( &r );

    // The user clicked...
    if ( !PtInRect( &r, p ) )
    {
        //  ...outside the dialog, close.
        EndDialog( IDCANCEL );
    }
    else
    {
        // inside the dialog. Since this window
        // has the mouse captured, its children
        // get no messages. So, check to see
        // if the click was in one of its children
        // and tell him.

        // If the user clicks inside the dialog
        // but not on any of the controls,
        // ChildWindowFromPoint returns a
        // pointer to the dialog. In this
        // case we do not resend the message
        // (obviously) because it would cause
        // a stack overflow.

        CWnd *child = ChildWindowFromPoint( point );

        if ( child && child != this )
        {
            child->SendMessage( WM_LBUTTONDOWN, 0, 0l );
        }
    }

    CDialog::OnLButtonDown( nFlags, point );
}

void _ZVColorBtnDlg::OnDrawItem( int nIDCtl, LPDRAWITEMSTRUCT lpd )
{
    CDC        dc;
    CPen    nullpen;
    CBrush    brush;
    CPen*    oldpen;
    CBrush*    oldbrush;

    // Draw the wells using the current color table

    nullpen.CreateStockObject( NULL_PEN );
    brush.CreateSolidBrush( colors[nIDCtl - IDC_COLOR1] );

    dc.Attach( lpd->hDC );

    oldpen        = dc.SelectObject( &nullpen );
    oldbrush    = dc.SelectObject( &brush );

    lpd->rcItem.right++;
    lpd->rcItem.bottom++;

    dc.Rectangle( &lpd->rcItem );

    dc.SelectObject( oldpen );
    dc.SelectObject( oldbrush );

    dc.Detach();

    CDialog::OnDrawItem( nIDCtl, lpd );
}

void _ZVColorBtnDlg::OnColor( UINT id )
{
    // A well has been clicked, set the color index
    // and close.
    colorindex = id - IDC_COLOR1;

    int i;

    // This color is now the MRU
    for ( i = 0; i < 20; i++ )
    {
        if ( used[colorindex] > used[i] )
        {
            used[i]++;
        }
    }

    used[colorindex] = 1;

    EndDialog( IDOK );
}

void _ZVColorBtnDlg::OnOther()
{
    int i;
    COLORREF newcolor;

    // The "Other" button.
    ReleaseCapture();

    CColorDialog dlg;

    dlg.m_cc.Flags |= CC_FULLOPEN;

    if ( dlg.DoModal() == IDOK )
    {
        // The user clicked OK.
        // set the color and close
        newcolor = dlg.GetColor();

        // Check to see if the selected color is
        // already in the table.
        colorindex = -1;

        for ( i = 0; i < 20; i++ )
        {
            if ( colors[i] == newcolor )
            {
                colorindex = i;
                break;
            }
        }

        // If the color was not found,
        // replace the LRU with this color
        if ( colorindex == -1 )
        {
            for ( i = 0; i < 20; i++ )
            {
                if ( used[i] == 20 )
                {
                    colors[i]    = newcolor;
                    colorindex    = i;
                    break;
                }
            }
        }

        // This is the new MRU
        for ( i = 0; i < 20; i++ )
        {
            if ( used[colorindex] > used[i] )
            {
                used[i]++;
            }
        }

        used[colorindex] = 1;
        EndDialog( IDOK );

        return;
    }

    // If the user clicked "Cancel" reclaim the mouse capture.
    SetCapture();
}

void _ZVColorBtnDlg::OnLButtonUp( UINT nFlags, CPoint point )
{
    // See notes for OnLButtonDown.
    CWnd *child = ChildWindowFromPoint( point, CWP_ALL );

    if ( child && child != this )
    {
        child->SendMessage( WM_LBUTTONDOWN, 0, 0l );
    }

    CDialog::OnLButtonUp( nFlags, point );
}

/////////////////////////////////////////////////////////////////////////////
// ZCColorBtn

BEGIN_MESSAGE_MAP( ZCColorBtn, CButton )
    //{{AFX_MSG_MAP(ZCColorBtn)
    ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZCColorBtn::ZCColorBtn()
{
    currentcolor = RGB( 255, 255, 255 );

    // This will allow the dialog to position itself
    dlg.parent = this;

    // Create the pens and brushes that we'll need to draw the button
    nullpen.CreateStockObject ( NULL_PEN );
    blackpen.CreateStockObject( BLACK_PEN );
    whitepen.CreateStockObject( WHITE_PEN );

    nullbrush.CreateStockObject( NULL_BRUSH );
    backbrush.CreateSolidBrush( GetSysColor( COLOR_3DFACE ) );
    dkgray.CreatePen( PS_SOLID, 1, RGB( 128, 128, 128 ) );
}

ZCColorBtn::~ZCColorBtn()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZCColorBtn message handlers

// Draw the button
void ZCColorBtn::DrawItem( LPDRAWITEMSTRUCT lpd )
{
    int        top;
    int        left;
    int        bottom;
    int        right;
    CBrush    colorbrush;
    CDC        DC;

    DC.Attach( lpd->hDC );

    // Store this for convinience
    top            = lpd->rcItem.top;
    left        = lpd->rcItem.left;
    bottom        = lpd->rcItem.bottom;
    right        = lpd->rcItem.right;

    colorbrush.CreateSolidBrush( currentcolor );

    oldpen        = DC.SelectObject( &nullpen );
    oldbrush    = DC.SelectObject( &backbrush );

    // Clear the background using the 3DFACE color.
    DC.Rectangle( &lpd->rcItem );

    // Draw the border
    if ( !( lpd->itemState & ODS_SELECTED ) )
    {
        // Button is up
        DC.SelectObject( &blackpen );

        DC.MoveTo( left, bottom - 1 );
        DC.LineTo( right - 1, bottom - 1 );
        DC.LineTo( right - 1, top );

        DC.SelectObject( &dkgray );

        DC.MoveTo( left + 1, bottom - 2 );
        DC.LineTo( right - 2, bottom - 2 );
        DC.LineTo( right - 2, top + 1 );

        DC.SelectObject( &whitepen );

        DC.LineTo( left + 1, top + 1);
        DC.LineTo( left + 1, bottom - 2);
    }
    else
    {
        // Button is down
        DC.SelectObject( &dkgray );

        DC.MoveTo( left, bottom - 1 );

        DC.LineTo( left, top );
        DC.LineTo( right - 1, top );

        DC.SelectObject( &whitepen );

        DC.MoveTo( right - 1, top - 1 );

        DC.LineTo( right - 1, bottom - 1 );
        DC.LineTo( left + 1, bottom - 1 );

        DC.SelectObject( &blackpen );

        DC.MoveTo( left + 1, bottom - 2 );
        DC.LineTo( left + 1, top + 1 );
        DC.LineTo( right - 2, top + 1 );

        // by moving this, we get the things inside the button
        // to draw themselves one pixel down and one to the right.
        // This completes the "pushed" effect
        left++;
        right++;
        bottom++;
        top++;
    }

    // The division
    DC.SelectObject( &whitepen );

    DC.MoveTo( right - 10, top + 4 );
    DC.LineTo( right - 10, bottom - 4 );

    DC.SelectObject( dkgray );

    DC.MoveTo( right - 11, top + 4 );
    DC.LineTo( right - 11, bottom - 4 );

    // The triangle
    if ( lpd->itemState & ODS_DISABLED )
    {
        DC.SelectObject( dkgray );
    }
    else
    {
        DC.SelectObject( blackpen );
    }

    DC.MoveTo( right - 4, ( bottom / 2 ) - 1 );
    DC.LineTo( right - 9, ( bottom / 2 ) - 1 );

    DC.MoveTo( right - 5, ( bottom / 2 ) );
    DC.LineTo( right - 8, ( bottom / 2 ) );

    if ( lpd->itemState & ODS_DISABLED )
    {
        DC.SetPixel( right - 4, ( bottom / 2 ) - 1, RGB( 255, 255, 255 ) );
        DC.SetPixel( right - 5, ( bottom / 2 ), RGB( 255, 255, 255 ) );
        DC.SetPixel( right - 6, ( bottom / 2 ) + 1, RGB( 255, 255, 255 ) );
    }
    else
    {
        DC.SetPixel( right - 6, ( bottom / 2 ) + 1, RGB( 0, 0, 0 ) );
    }

    if ( !( lpd->itemState & ODS_DISABLED ) )
    {
        // The color rectangle, only if enabled
        DC.SelectObject( &colorbrush );
        DC.Rectangle( left + 5, top + 4, right - 15, bottom - 4 );
    }

    if ( lpd->itemState & ODS_FOCUS )
    {
        // Draw the focus
        //
        // It would have been nice just to
        // draw a rectangle using a pen created
        // with the PS_ALTERNATE style, but
        // this is not supported by WIN95
        int i;

        for ( i = left + 3; i < right - 4; i += 2 )
        {
            DC.SetPixel( i, top + 3, RGB( 0, 0, 0 ) );
            DC.SetPixel( i, bottom - 4, RGB( 0, 0, 0 ) );
        }

        for ( i = top + 3; i < bottom - 4; i += 2 )
        {
            DC.SetPixel( left + 3, i, RGB( 0, 0, 0 ) );
            DC.SetPixel( right - 4, i, RGB( 0, 0, 0 ) );
        }
    }

    DC.SelectObject( oldpen );
    DC.SelectObject( oldbrush );

    DC.Detach();
}

void ZCColorBtn::OnClicked()
{
    // When the button is clicked, show the dialog.

    if ( dlg.DoModal() == IDOK )
    {
        currentcolor = _ZVColorBtnDlg::colors[dlg.colorindex];
        InvalidateRect( NULL );
        GetParent()->SendMessage( MESSAGE_COLOR_CHANGED );
    }
}

// Store and Load use an undocumented CWinApp function
BOOL ZCColorBtn::Store()
{
    return ( AfxGetApp()->WriteProfileBinary( _T( "ColorData" ), _T( "ColorTable" ), (LPBYTE)_ZVColorBtnDlg::colors, sizeof( COLORREF ) * 20 ) &&
             AfxGetApp()->WriteProfileBinary( _T( "ColorData" ), _T( "MRU" ), (LPBYTE)_ZVColorBtnDlg::used, sizeof( BYTE ) * 20 ) );
}

BOOL ZCColorBtn::Load()
{
    BYTE *data = NULL;
    UINT size;

    // This function allocates the memory it needs
    AfxGetApp()->GetProfileBinary( _T( "ColorData" ), _T( "ColorTable" ), &data, &size );

    if ( data )
    {
        // Copy the data into our table and get rid of the buffer
        memcpy( (void *)_ZVColorBtnDlg::colors, (void *)data, size );
        free( (void *)data );

        AfxGetApp()->GetProfileBinary( _T( "ColorData" ), _T( "MRU" ), &data, &size );

        if ( data )
        {
            memcpy( (void *)_ZVColorBtnDlg::used, (void *)data, size );
            free( (void *)data );

            return TRUE;
        }
    }

    // If the loading fails, back to the defaults    
    Reset();

    return FALSE;
}

void ZCColorBtn::Reset()
{
    _ZVColorBtnDlg::colors[0]    = RGB( 0, 0, 0 );
    _ZVColorBtnDlg::colors[1]    = RGB( 128, 0, 0 );
    _ZVColorBtnDlg::colors[2]    = RGB( 0, 128, 0 );
    _ZVColorBtnDlg::colors[3]    = RGB( 128, 128, 0 );
    _ZVColorBtnDlg::colors[4]    = RGB( 0, 0, 128 );
    _ZVColorBtnDlg::colors[5]    = RGB( 128, 0, 128 );
    _ZVColorBtnDlg::colors[6]    = RGB( 0, 128, 128 );
    _ZVColorBtnDlg::colors[7]    = RGB( 192, 192, 192 );
    _ZVColorBtnDlg::colors[8]    = RGB( 192, 220, 192 );
    _ZVColorBtnDlg::colors[9]    = RGB( 166, 202, 240 );
    _ZVColorBtnDlg::colors[10]    = RGB( 255, 251, 240 );
    _ZVColorBtnDlg::colors[11]    = RGB( 160, 160, 164 );
    _ZVColorBtnDlg::colors[12]    = RGB( 128, 128, 128 );
    _ZVColorBtnDlg::colors[13]    = RGB( 255, 0, 0 );
    _ZVColorBtnDlg::colors[14]    = RGB( 0, 255, 0 );
    _ZVColorBtnDlg::colors[15]    = RGB( 255, 255, 0 );
    _ZVColorBtnDlg::colors[16]    = RGB( 0, 0, 255 );
    _ZVColorBtnDlg::colors[17]    = RGB( 255, 0, 255 );
    _ZVColorBtnDlg::colors[18]    = RGB( 0, 255, 255 );
    _ZVColorBtnDlg::colors[19]    = RGB( 255, 255, 255 );

    // This "colorful" (no pun intended) order ensures
    // that the colors at the center of the color table
    // will get replaced first. This preserves the white
    // and black colors even if they're not used (They'll
    // get replaced last).

    _ZVColorBtnDlg::used[0]        = 1;
    _ZVColorBtnDlg::used[1]        = 3;
    _ZVColorBtnDlg::used[2]        = 5;
    _ZVColorBtnDlg::used[3]        = 7;
    _ZVColorBtnDlg::used[4]        = 9;
    _ZVColorBtnDlg::used[5]        = 11;
    _ZVColorBtnDlg::used[6]        = 13;
    _ZVColorBtnDlg::used[7]        = 15;
    _ZVColorBtnDlg::used[8]        = 17;
    _ZVColorBtnDlg::used[9]        = 19;
    _ZVColorBtnDlg::used[10]    = 20;
    _ZVColorBtnDlg::used[11]    = 18;
    _ZVColorBtnDlg::used[12]    = 16;
    _ZVColorBtnDlg::used[13]    = 14;
    _ZVColorBtnDlg::used[14]    = 12;
    _ZVColorBtnDlg::used[15]    = 10;
    _ZVColorBtnDlg::used[16]    = 8;
    _ZVColorBtnDlg::used[17]    = 6;
    _ZVColorBtnDlg::used[18]    = 4;
    _ZVColorBtnDlg::used[19]    = 2;
}

void ZCColorBtn::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        ar.Write( (void *)_ZVColorBtnDlg::colors, sizeof( COLORREF ) * 20 );
        ar.Write( (void *)_ZVColorBtnDlg::used, sizeof( BYTE ) * 20 );
    }
    else
    {
        ar.Read( (void *)_ZVColorBtnDlg::colors, sizeof( COLORREF ) * 20 );
        ar.Read( (void *)_ZVColorBtnDlg::used, sizeof( BYTE ) * 20 );
    }
}
