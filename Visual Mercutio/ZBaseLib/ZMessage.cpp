//## begin module%36DEE3D90136.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36DEE3D90136.cm

//## begin module%36DEE3D90136.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%36DEE3D90136.cp

//## Module: ZMessage%36DEE3D90136; Package body
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\ZMessage.cpp

//## begin module%36DEE3D90136.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%36DEE3D90136.additionalIncludes

//## begin module%36DEE3D90136.includes preserve=yes
//## end module%36DEE3D90136.includes

// ZMessage
#include "ZMessage.h"
//## begin module%36DEE3D90136.declarations preserve=no
//## end module%36DEE3D90136.declarations

//## begin module%36DEE3D90136.additionalDeclarations preserve=yes
#include "PSS_DrawFunctions.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(ZIMessage, ZIDialog)
    //{{AFX_MSG_MAP(ZIMessage)
    ON_WM_TIMER()
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_CLOSEWINDOW, OnCloseWindow)
    ON_WM_CREATE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%36DEE3D90136.additionalDeclarations


// Class ZIMessage 







ZIMessage::ZIMessage (CWnd* pWnd)
  //## begin ZIMessage::ZIMessage%920577013.hasinit preserve=no
      : m_IDBitmap(0), m_hInst(0)
  //## end ZIMessage::ZIMessage%920577013.hasinit
  //## begin ZIMessage::ZIMessage%920577013.initialization preserve=yes
  , ZIDialog(ZIMessage::IDD)
  //## end ZIMessage::ZIMessage%920577013.initialization
{
  //## begin ZIMessage::ZIMessage%920577013.body preserve=yes
  
    //{{AFX_DATA_INIT(ZIMessage)
    //}}AFX_DATA_INIT

    m_iIcon = 0;    // Init the sequence

    HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE (IDC_CLICKTOCLOSE), RT_GROUP_CURSOR);
    m_Cursor = ::LoadCursor( hInst, MAKEINTRESOURCE(IDC_CLICKTOCLOSE) );

    // Create the text font
    VERIFY( m_TextFont.CreateFont( 10, 8,        // Size
                                0, 0,        // Escapment and Orientation
                                FW_NORMAL,  // Weight
                                0, 0, 0,    // Italic, Underline, StrikeOut
                                DEFAULT_CHARSET,
                                OUT_DEVICE_PRECIS,
                                CLIP_TT_ALWAYS,
                                PROOF_QUALITY,
                                DEFAULT_PITCH,
                                "System" ) );
    // Create the title font
    VERIFY( m_TitleFont.CreateFont( 20, 16,        // Size
                                0, 0,        // Escapment and Orientation
                                FW_BOLD,    // Weight
                                0, 0, 0,    // Italic, Underline, StrikeOut
                                DEFAULT_CHARSET,
                                OUT_DEVICE_PRECIS,
                                CLIP_TT_ALWAYS,
                                PROOF_QUALITY,
                                DEFAULT_PITCH,
                                "System" ) );
    
  //## end ZIMessage::ZIMessage%920577013.body
}


ZIMessage::~ZIMessage()
{
  //## begin ZIMessage::~ZIMessage%.body preserve=yes
  //## end ZIMessage::~ZIMessage%.body
}



//## Other Operations (implementation)
void ZIMessage::DisplayMessage (const CString Text, CString Title, UINT IDBitmap)
{
  //## begin ZIMessage::DisplayMessage%920577014.body preserve=yes
    m_IDBitmap = IDBitmap;
    m_Text = Text;
    m_Title = Title;
    if (m_IDBitmap)
        m_hInst = AfxFindResourceHandle( MAKEINTRESOURCE (m_IDBitmap), RT_BITMAP );
    DoModal();
  //## end ZIMessage::DisplayMessage%920577014.body
}

void ZIMessage::DisplayMessage (UINT IDText, UINT IDTitle, UINT IDBitmap)
{
  //## begin ZIMessage::DisplayMessage%920577015.body preserve=yes
      CString    Text;
      CString    Title;
      
    Text.LoadString( IDText );
      if (IDTitle)
          Title.LoadString( IDTitle );
      DisplayMessage( Text, Title, IDBitmap );
  //## end ZIMessage::DisplayMessage%920577015.body
}

// Additional Declarations
  //## begin ZIMessage%36DEE2420330.declarations preserve=yes
  //## end ZIMessage%36DEE2420330.declarations

//## begin module%36DEE3D90136.epilog preserve=yes
void ZIMessage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIMessage)
    DDX_Control(pDX, IDC_DIALOGMESSAGE_ICON, m_icnApp);
    DDX_Control(pDX, IDC_CLOSEWINDOW, m_CloseButton);
    //}}AFX_DATA_MAP
}


BOOL ZIMessage::OnInitDialog()
{
    ZIDialog::OnInitDialog();
    
    m_CloseButton.SetIcon(IDI_CLOSEWINDOW);
    m_CloseButton.SetBtnCursor( IDC_CLOSEWINDOW );
    m_CloseButton.SetAlign( ZCFlatButton::ST_ALIGN_HORIZ_RIGHT );
    m_CloseButton.DrawTransparent();
//    m_CloseButton.AutoLoad( IDC_CLOSEWINDOW, this );
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void ZIMessage::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    
    CRect    rect;
    CFont*    OldFont;
    CBrush*    OldBrush;
                 
    CBrush    NewBrush( defCOLOR_WHITE ); 
    GetClientRect( &rect );
    CRect    WhiteRect( rect.left+1, rect.top+1, rect.right-2, rect.top+40 );

    OldBrush = dc.SelectObject( &NewBrush );
    dc.FillRect( WhiteRect, &NewBrush );

      CPen*    pOldPen = NULL;
      CPen    PenBlack( PS_SOLID, 1, defCOLOR_GRAY );
    pOldPen = dc.SelectObject( &PenBlack );
    dc.MoveTo( rect.right, rect.top );
    dc.LineTo( rect.left, rect.top );
    dc.LineTo( rect.left, rect.top+40 );
    dc.SelectObject( pOldPen );

      CPen    PenGray( PS_SOLID, 1, defCOLOR_BLACK );
    pOldPen = dc.SelectObject( &PenGray );
    dc.MoveTo( rect.left, rect.top+40 );
    dc.LineTo( rect.right-1, rect.top+40 );
    dc.LineTo( rect.right-1, rect.top );
    dc.SelectObject( pOldPen );

    Draw3DLine( dc.m_hDC, 0, WhiteRect.left+2, WhiteRect.bottom+2, WhiteRect.right-2, WhiteRect.bottom+2 );

    // Display the title
    OldFont = dc.SelectObject( &m_TitleFont );
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor( defCOLOR_BLACK );
    dc.SetTextAlign( TA_LEFT | TA_BOTTOM );
    dc.TextOut( rect.left+20, rect.top+30, m_Title );
    dc.SelectObject( OldFont );

    // Display the text    
    CRect    TextRect( rect.left+40, rect.top+65, rect.right-20, rect.bottom-40 );
    DrawEngraveRect( dc.m_hDC, TextRect, defCOLOR_LTLTGRAY );
    
    OldFont = dc.SelectObject( &m_TextFont );
    dc.SetTextColor( defCOLOR_BLACK );
    dc.SetTextAlign( 0 );
    TextRect.InflateRect( -5, -5 );
    dc.DrawText( m_Text, -1, &TextRect, DT_LEFT | DT_BOTTOM | DT_WORDBREAK );


    Draw3DLine( dc.m_hDC, 0, WhiteRect.left+2, rect.bottom-30, WhiteRect.right-2, rect.bottom-30 );

    dc.SelectObject( OldFont );
    dc.SelectObject( OldBrush );

    if (m_IDBitmap && m_hInst)
        ShowBitmapFile(MAKEINTRESOURCE(m_IDBitmap),
                       dc.m_hDC,
                       m_hInst,
                       rect.right - 5,
                       rect.top   + 5);
}


void ZIMessage::OnCloseWindow()
{
    CloseWindow();
}


void ZIMessage::CloseWindow()
{
    // remove the timer
    KillTimer(m_uTimerID);
    m_uTimerID = 0;

    for(int i = 0; i < NUMBER_OF_MESSAGE_ICON; ++i)
        DestroyIcon(m_pIcon[i]);

    ReleaseCapture();
    EndDialog(IDOK);
}

void ZIMessage::OnLButtonDown(UINT nFlags, CPoint point)
{
    ZIDialog::OnLButtonDown(nFlags, point);
    CloseWindow();
}

void ZIMessage::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    ZIDialog::OnLButtonDblClk(nFlags, point);
    CloseWindow();
}

int ZIMessage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDialog::OnCreate(lpCreateStruct) == -1)
        return -1;

    m_pIcon[0]  = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS1));
    m_pIcon[1]  = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS2));
    m_pIcon[2]  = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS3));
    m_pIcon[3]  = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS4));
    m_pIcon[4]  = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS5));
    m_pIcon[5]  = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS6));
    m_pIcon[6]  = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS7));
    m_pIcon[7]  = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS8));
    m_pIcon[8]  = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS9));
    m_pIcon[9]  = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS10));
    m_pIcon[10] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS11));
    m_pIcon[11] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS12));
    m_pIcon[12] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS13));
    m_pIcon[13] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS14));
    m_pIcon[14] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS15));
    m_pIcon[15] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_TIPS16));

    // create the timer for the animation
    m_uTimerID = SetTimer(ID_TIMERMESSAGE, 120, NULL);

    return 0;
}

void ZIMessage::OnTimer(UINT nIDEvent)
{
    // Increment the icon for the next time
    m_icnApp.SetIcon( m_pIcon[m_iIcon] );
    if( ++m_iIcon >= NUMBER_OF_MESSAGE_ICON )
        m_iIcon = 0;
    CDialog::OnTimer(nIDEvent);
}


void ZIMessage::OnMouseMove(UINT nFlags, CPoint point) 
{
    ZIDialog::OnMouseMove(nFlags, point);
    return;    
    // Convert the cursor point
//    ScreenToClient(&point);

    // Retreive the client rect
    CRect ClientRect;
    GetClientRect(ClientRect);
    if (ClientRect.PtInRect(point))
    {
        m_CloseButton.GetClientRect( ClientRect );
        if (!ClientRect.PtInRect(point))
        {
            ZIDialog::OnMouseMove(nFlags, point);
            // Set the capture
            SetCapture();
            if (GetCursor() !=  m_Cursor)
                SetCursor( m_Cursor );
            return;
        }
    }
    ReleaseCapture();
}


//## end module%36DEE3D90136.epilog



