// msgbox.cpp : implementation file

#include "stdafx.h"
#include "msgbox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 12 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_DYNCREATE( MsgBox, CDialog )

BEGIN_MESSAGE_MAP( MsgBox, CDialog )
    //{{AFX_MSG_MAP(MsgBox)
    ON_WM_TIMER()
    ON_WM_CREATE()
    ON_WM_PAINT()
    ON_BN_CLICKED(IDYES, OnYes)
    ON_BN_CLICKED(IDNO, OnNo)
    ON_BN_CLICKED(IDCANCEL, OnCancelBtn)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MsgBox dialog

MsgBox::MsgBox( CWnd* pParent /*=NULL*/ )
    : CDialog( MsgBox::IDD, pParent )
{
    // Init the sequence
    m_iIcon = 0;

    // JMR-MODIF - Le 7 novembre 2006 - Initialise la variable bDoShowUnlockButton.
    bDoShowUnlockButton = FALSE;

    //{{AFX_DATA_INIT(MsgBox)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

MsgBox::~MsgBox()
{
}

void MsgBox::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(MsgBox)
    DDX_Control(pDX, IDC_DIALOGSAVE_ICON, m_icnApp);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// MsgBox publics functions

int MsgBox::DisplayMsgBox( LPCSTR prompt, UINT fuStyle )
{
    m_strText = prompt;
    m_fuStyle = fuStyle;

    return( DoModal() );
}

int MsgBox::DisplayMsgBox( UINT uIDRes, UINT fuStyle, HINSTANCE hInst )
{
    if ( hInst )
    {
        char szBuf[500];
        ::LoadString( hInst, uIDRes, szBuf, sizeof( szBuf ) );
        m_strText = szBuf;
    }
    else
    {
        m_strText.LoadString( uIDRes );
    }

    m_fuStyle = fuStyle;

    return( DoModal() );
}

// JMR-MODIF - Le 7 novembre 2006 - Permet de basculer entre le texte Cancel ou Déverrouiller pour le 3ème bouton.
void MsgBox::DoChangeCancelBtnToUnlockBtn( BOOL Value /*= TRUE*/ )
{
    bDoShowUnlockButton = Value;
}

/////////////////////////////////////////////////////////////////////////////
// MsgBox message handlers

int MsgBox::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
    if ( CDialog::OnCreate( lpCreateStruct ) == -1 )
    {
        return -1;
    }

    m_pIcon[0] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP1 ) );
    m_pIcon[1] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP2 ) ); 
    m_pIcon[2] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP3 ) );
    m_pIcon[3] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP4 ) );
    m_pIcon[4] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP5 ) );
    m_pIcon[5] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP6 ) );
    m_pIcon[6] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP7 ) );

    m_pIconAnimation2[0] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP_1 ) );
    m_pIconAnimation2[1] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP_2 ) ); 
    m_pIconAnimation2[2] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP_3 ) );
    m_pIconAnimation2[3] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP_4 ) );
    m_pIconAnimation2[4] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP_5 ) );
    m_pIconAnimation2[5] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP_6 ) );
    m_pIconAnimation2[6] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP_7 ) );
    m_pIconAnimation2[7] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP_8 ) );
    m_pIconAnimation2[8] = ::LoadIcon( ZBaseLibDLL.hModule, MAKEINTRESOURCE ( IDI_ICONAPP_9 ) );
    
    // Create the timer for the animation
    m_uTimerID = SetTimer( ID_TIMERABOUT, 80, NULL );

    return 0;
}

BOOL MsgBox::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Put the window in the center of the screen
    CRect    rect;
    GetClientRect( &rect );
    CRect    ClientRect;
    UINT    uiX;
    UINT    uiY;

    uiX = GetSystemMetrics( SM_CXFULLSCREEN );
    uiY = GetSystemMetrics( SM_CYFULLSCREEN );

    SetWindowPos( NULL, ( uiX - rect.right ) / 2, ( uiY - rect.bottom ) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
    
    AdjustSize();

    // Return TRUE  unless you set the focus to a control
    return TRUE;
}

void MsgBox::OnTimer( UINT nIDEvent )
{
    // Increment the icon for the next time
    if ( m_fuStyle == MB_OK )
    {
        m_icnApp.SetIcon( m_pIcon[m_iIcon] );

        if( ++m_iIcon >= NUMBER_OF_ICON )
        {
            m_iIcon = 0;
        }
    }
    else
    {
        m_icnApp.SetIcon( m_pIconAnimation2[m_iIcon] );

        if( ++m_iIcon >= ANIMATION2_NUMBER_OF_ICON )
        {
            m_iIcon = 0;
        }
    }
    
    CDialog::OnTimer( nIDEvent );
}

void MsgBox::OnPaint()
{
    // Device context for painting
    CPaintDC    dc( this );

    CRect        rect;
    CPoint        pt;

    GetClientRect( &rect );
    rect.InflateRect( -30, -25 );
    dc.DPtoLP( &rect );
    rect.OffsetRect( 10, 0 );

    dc.SetBkMode( TRANSPARENT );

    // Text color
    dc.SetTextColor( defCOLOR_DEFAULT_TEXT );

    dc.DrawText( m_strText, -1, &rect, DT_CENTER | DT_WORDBREAK );
}

void MsgBox::OnYes()
{
    ReleaseDialog();

    CDialog::EndDialog( IDYES );
}

void MsgBox::OnNo()
{
    ReleaseDialog();

    CDialog::EndDialog( IDNO );
}

void MsgBox::OnCancelBtn()
{
    ReleaseDialog();

    CDialog::EndDialog( IDCANCEL );
}

/////////////////////////////////////////////////////////////////////////////
// MsgBox privates functions

// JMR-MODIF - Le 6 novembre 2006 - Cette fonction nettoie les ressources utilisées par le dialog box.
void MsgBox::ReleaseDialog()
{
    // Remove the timer
    KillTimer( m_uTimerID );
    m_uTimerID = 0;

    for( int i = 0; i < NUMBER_OF_ICON ;i++ )
    {
        DestroyIcon( m_pIcon[i] );
    }

    for( i = 0; i < ANIMATION2_NUMBER_OF_ICON ;i++ )
    {
        DestroyIcon( m_pIconAnimation2[i] );
    }
}

void MsgBox::AdjustSize()
{
    // Device context for painting
    CDC* pDC = GetDC();

    // JMR-MODIF - Le 7 novembre 2006 - Teste le Device Context avant son utilisation.
    if ( pDC == NULL )
    {
        return;
    }

    CRect        rect;
    CPoint        pt;
    int            iSaveRight;

    GetWindowRect( &rect );
    rect.InflateRect( -30, -50 );
    pDC->DPtoLP( &rect );

    rect.bottom = rect.top;

    // Save the right coordinate because there is a bug in DrawText to calculate
    iSaveRight    = rect.right;

    pDC->DrawText( m_strText, -1, &rect, DT_CALCRECT | DT_CENTER | DT_WORDBREAK );

    // Restore the right coordinate
    rect.right = iSaveRight;

    pDC->LPtoDP( &rect );
    rect.InflateRect( 30, 50 );

    // Resize the window but without repainting the window
    MoveWindow( &rect, FALSE );

    // **********************************************************************************************
    // JMR-MODIF - Le 6 novembre 2006 - Nouvelle fonction pour la gestion et l'affichage des boutons.
/*
    // Move the buttons too.
    CRect    ButtonRect;
    int        iButtonHeight;
    CWnd*    pYes    = GetDlgItem( IDYES );
    CWnd*    pNo        = GetDlgItem( IDNO );
    CWnd*    pCancel    = GetDlgItem( IDCANCEL );

    if ( pNo )
    {
        pNo->GetWindowRect( &ButtonRect );
        iButtonHeight        = ButtonRect.Height();
        ButtonRect.bottom    = rect.bottom - 5;
        ButtonRect.top        = ButtonRect.bottom - iButtonHeight;
        ScreenToClient( &ButtonRect );

        if ( m_fuStyle & MB_YESNOCANCEL || m_fuStyle & MB_YESNO )
        {
            pNo->MoveWindow( &ButtonRect );
        }
        else
        {
            pNo->ShowWindow( SW_HIDE );
        }
    }

    if ( pYes )
    {
        if ( m_fuStyle == MB_OK )
        {
            // Take the place of the No button
            // because he is already centered
            // Thus do not calculate the position
            pYes->SetWindowText( _T( "OK" ) );
        }
        else
        {
            pYes->GetWindowRect( &ButtonRect );
            iButtonHeight        = ButtonRect.Height();
            ButtonRect.bottom    = rect.bottom - 5;
            ButtonRect.top        = ButtonRect.bottom - iButtonHeight;
            ScreenToClient( &ButtonRect );
        }

        pYes->MoveWindow( &ButtonRect );
    }

    if ( pCancel )
    {
        pCancel->GetWindowRect( &ButtonRect );
        iButtonHeight        = ButtonRect.Height();
        ButtonRect.bottom    = rect.bottom - 5;
        ButtonRect.top        = ButtonRect.bottom - iButtonHeight;
        ScreenToClient( &ButtonRect );

        if ( m_fuStyle & MB_YESNOCANCEL )
        {
            pCancel->MoveWindow( &ButtonRect );
        }
        else
        {
            pCancel->ShowWindow( SW_HIDE );
        }
    }
*/

    // Obtention des pointeurs sur les objets boutons.
    CWnd*    pYes    = GetDlgItem( IDYES );
    CWnd*    pNo        = GetDlgItem( IDNO );
    CWnd*    pCancel    = GetDlgItem( IDCANCEL );

    if ( pYes == NULL || pNo == NULL || pCancel == NULL )
    {
        ReleaseDC( pDC );
        return;
    }

    if ( bDoShowUnlockButton == TRUE )
    {
        pCancel->SetWindowText( _T( "Déverrouiller" ) );
    }

    switch ( m_fuStyle )
    {
        // Boîte de dialogue ne comprenant qu'un seul bouton OK.
        case MB_OK:
        {
            CRect ButtonRect;

            pYes->GetWindowRect( &ButtonRect );

            int iHeight            = ButtonRect.Height();
            int iWidth            = ButtonRect.Width();

            // Centrage du bouton par rapport à la fenêtre parent.
            ButtonRect.bottom    = rect.bottom - 6;
            ButtonRect.top        = ButtonRect.bottom - iHeight;
            ButtonRect.left        = rect.left + ( ( rect.Width() / 2 ) - ( iWidth / 2 ) );
            ButtonRect.right    = ButtonRect.left + iWidth;

            // Conversion des coordonnées.
            ScreenToClient( &ButtonRect );

            pYes->MoveWindow( &ButtonRect );

            // Corrige le texte du bouton, afin qu'il affiche le message OK plutôt que Yes.
            pYes->SetWindowText( _T( "OK" ) );

            // Masque les boutons No et Cancel.
            pNo->ShowWindow( SW_HIDE );
            pCancel->ShowWindow( SW_HIDE );

            break;
        }

        // Boîte de dialogue avec un bouton Yes et un bouton No.
        case MB_YESNO:
        {
            CRect ButtonRectYes;
            CRect ButtonRectNo;

            pYes->GetWindowRect( &ButtonRectYes );
            pNo->GetWindowRect( &ButtonRectNo );

            int iHeightYes            = ButtonRectYes.Height();
            int iWidthYes            = ButtonRectYes.Width();
            int iHeightNo            = ButtonRectNo.Height();
            int iWidthNo            = ButtonRectNo.Width();

            // Centrage et positionnement du bouton Yes.
            ButtonRectYes.bottom    = rect.bottom - 6;
            ButtonRectYes.top        = ButtonRectYes.bottom - iHeightYes;
            ButtonRectYes.left        = rect.left + ( ( rect.Width() / 2 ) - iWidthYes - 3 );
            ButtonRectYes.right        = ButtonRectYes.left + iWidthYes;

            // Centrage et positionnement du bouton No.
            ButtonRectNo.bottom        = rect.bottom - 6;
            ButtonRectNo.top        = ButtonRectNo.bottom - iHeightNo;
            ButtonRectNo.right        = rect.left + ( ( rect.Width() / 2 ) + iWidthNo + 3 );
            ButtonRectNo.left        = ButtonRectNo.right - iWidthNo;

            // Conversion des coordonnées.
            ScreenToClient( &ButtonRectYes );
            ScreenToClient( &ButtonRectNo );

            pYes->MoveWindow( &ButtonRectYes );
            pNo->MoveWindow( &ButtonRectNo );

            // Masque le bouton Cancel.
            pCancel->ShowWindow( SW_HIDE );

            break;
        }

        // Boîte de dialogue avec un bouton Yes, No et Cancel. C'est celle que l'on affiche aussi par défaut.
        default:
        case MB_YESNOCANCEL:
        {
            CRect ButtonRectYes;
            CRect ButtonRectNo;
            CRect ButtonRectCancel;

            pYes->GetWindowRect( &ButtonRectYes );
            pNo->GetWindowRect( &ButtonRectNo );
            pCancel->GetWindowRect( &ButtonRectCancel );

            int iHeightYes                = ButtonRectYes.Height();
            int iWidthYes                = ButtonRectYes.Width();
            int iHeightNo                = ButtonRectNo.Height();
            int iWidthNo                = ButtonRectNo.Width();
            int iHeightCancel            = ButtonRectCancel.Height();
            int iWidthCancel            = ButtonRectCancel.Width();

            // Centrage et positionnement du bouton No. On commence par celui-ci car il est au centre de la fenêtre.
            ButtonRectNo.bottom            = rect.bottom - 6;
            ButtonRectNo.top            = ButtonRectNo.bottom - iHeightNo;
            ButtonRectNo.left            = rect.left + ( ( rect.Width() / 2 ) - ( iWidthNo / 2 ) );
            ButtonRectNo.right            = ButtonRectNo.left + iWidthNo;

            // Centrage et positionnement du bouton Yes.
            ButtonRectYes.bottom        = rect.bottom - 6;
            ButtonRectYes.top            = ButtonRectYes.bottom - iHeightYes;
            ButtonRectYes.right            = ButtonRectNo.left - 6;
            ButtonRectYes.left            = ButtonRectYes.right - iWidthYes;

            // Centrage et positionnement du bouton Cancel.
            ButtonRectCancel.bottom        = rect.bottom - 6;
            ButtonRectCancel.top        = ButtonRectNo.bottom - iHeightNo;
            ButtonRectCancel.left        = ButtonRectNo.right + 6;
            ButtonRectCancel.right        = ButtonRectCancel.left + iWidthCancel;

            // Conversion des coordonnées.
            ScreenToClient( &ButtonRectYes );
            ScreenToClient( &ButtonRectNo );
            ScreenToClient( &ButtonRectCancel );

            pYes->MoveWindow( &ButtonRectYes );
            pNo->MoveWindow( &ButtonRectNo );
            pCancel->MoveWindow( &ButtonRectCancel );

            break;
        }
    }
    // **********************************************************************************************

    ReleaseDC( pDC );
}
