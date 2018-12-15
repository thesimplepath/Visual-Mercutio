// ZVFilePreviewDlg.cpp : implementation file

#include "stdafx.h"
#include "ZVFilePreviewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 26 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

/////////////////////////////////////////////////////////////////////////////
// ZVFilePreviewDlg dialog

BEGIN_MESSAGE_MAP( ZVFilePreviewDlg, CDialog )
    //{{AFX_MSG_MAP(ZVFilePreviewDlg)
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVFilePreviewDlg::ZVFilePreviewDlg( UINT nResID, CWnd* pParent /*=NULL*/ )
    : CDialog    ( ZVFilePreviewDlg::IDD, pParent ),
      m_pBrowser( NULL )
{
    //{{AFX_DATA_INIT(ZVFilePreviewDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

    CString strTemp;
    strTemp.Format( _T( "%d" ), nResID );
    
    m_strURL = ZWebBrowser::BuildResourceToURL( strTemp );
}

ZVFilePreviewDlg::ZVFilePreviewDlg( LPCTSTR lpszURL, BOOL bRes, CWnd* pParent /*=NULL*/ )
    : CDialog    ( ZVFilePreviewDlg::IDD, pParent ),
      m_pBrowser( NULL )
{
    if ( bRes )
    {
        m_strURL = ZWebBrowser::BuildResourceToURL( lpszURL );
    }
    else
    {
        m_strURL = lpszURL;
    }
}

ZVFilePreviewDlg::~ZVFilePreviewDlg()
{
    if ( m_pBrowser )
    {
        delete m_pBrowser;
        m_pBrowser = NULL;
    }
}

void ZVFilePreviewDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVFilePreviewDlg)
    //}}AFX_DATA_MAP
}

void ZVFilePreviewDlg::SizeControl()
{
    if ( GetDlgItem( IDC_WEBBROWSER_CONTROL ) && ::IsWindow( GetDlgItem( IDC_WEBBROWSER_CONTROL )->GetSafeHwnd() ) )
    {
        CRect rect;
        GetClientRect( &rect );

        if ( GetDlgItem( IDOK ) )
        {
            CRect ButtonRect;
            GetDlgItem( IDOK )->GetClientRect( &ButtonRect );

            int cx = ButtonRect.Width();
            int cy = ButtonRect.Height();

            ButtonRect.bottom    = rect.bottom - 5;
            ButtonRect.right    = rect.right - 5;
            ButtonRect.top        = ButtonRect.bottom - cy;
            ButtonRect.left        = ButtonRect.right - cx;

            GetDlgItem( IDOK )->MoveWindow( &ButtonRect );
        }

        if ( m_pBrowser )
        {
            CRect BrowserRect;
            m_pBrowser->GetClientRect( &BrowserRect );

            int cx = BrowserRect.Width();
            int cy = BrowserRect.Height();

            BrowserRect.bottom    = rect.bottom - 23;
            BrowserRect.right    = rect.right - 5;
            BrowserRect.top        = 5;
            BrowserRect.left    = 5;

            m_pBrowser->MoveWindow( &BrowserRect );
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZVFilePreviewDlg message handlers

BOOL ZVFilePreviewDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    if ( GetDlgItem( IDC_WEBBROWSER_CONTROL ) )
    {
        CRect rect;
        GetDlgItem( IDC_WEBBROWSER_CONTROL )->GetClientRect ( &rect );
        GetDlgItem( IDC_WEBBROWSER_CONTROL )->MapWindowPoints( this, &rect );

        // Create the control.
        m_pBrowser = new ZWebBrowser;
        ASSERT ( m_pBrowser );

        if ( !m_pBrowser->Create( NULL, NULL, WS_VISIBLE, rect, this, NULL ) )
        {
            TRACE( _T( "failed to create browser\n" ) );
            delete m_pBrowser;
            m_pBrowser = NULL;

            return FALSE;
        }

        // Initialize the first URL.
        m_pBrowser->Navigate( m_strURL );

        CString Title;
        GetWindowText( Title );
        Title += _T( " " ) + m_strURL;
        SetWindowText( Title );

        // Resize all controls
        SizeControl();
    }

    // Activate the application window
    SetActiveWindow();
    SetForegroundWindow();
    
    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVFilePreviewDlg::OnSize( UINT nType, int cx, int cy )
{
    CDialog::OnSize( nType, cx, cy );

    SizeControl();
}
