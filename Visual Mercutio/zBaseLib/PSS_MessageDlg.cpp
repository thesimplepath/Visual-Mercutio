/****************************************************************************
 * ==> PSS_MessageDlg ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a message dialog box                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_MessageDlg.h"

#include "PSS_DrawFunctions.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_MessageDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(PSS_MessageDlg)
    ON_WM_TIMER()
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_CLOSEWINDOW, OnCloseWindow)
    ON_WM_CREATE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_MessageDlg
//---------------------------------------------------------------------------
PSS_MessageDlg::PSS_MessageDlg(CWnd* pWnd) :
    PSS_Dialog(PSS_MessageDlg::IDD),
    m_hInst(NULL),
    m_Cursor(NULL),
    m_Icon(0),
    m_BitmapID(0),
    m_TimerID(0)
{
    std::memset(&m_pIcon, 0x0, M_Message_Icon_Count);

    HINSTANCE hInst = ::AfxFindResourceHandle(MAKEINTRESOURCE(IDC_CLICKTOCLOSE), RT_GROUP_CURSOR);
    m_Cursor        = ::LoadCursor(hInst, MAKEINTRESOURCE(IDC_CLICKTOCLOSE));

    // create the text font
    VERIFY(m_TextFont.CreateFont(10,
                                 8,
                                 0,
                                 0,
                                 FW_NORMAL,
                                 0,
                                 0,
                                 0,
                                 DEFAULT_CHARSET,
                                 OUT_DEVICE_PRECIS,
                                 CLIP_TT_ALWAYS,
                                 PROOF_QUALITY,
                                 DEFAULT_PITCH,
                                 "System"));

    // create the title font
    VERIFY(m_TitleFont.CreateFont(20,
                                  16,
                                  0,
                                  0,
                                  FW_BOLD,
                                  0,
                                  0,
                                  0,
                                  DEFAULT_CHARSET,
                                  OUT_DEVICE_PRECIS,
                                  CLIP_TT_ALWAYS,
                                  PROOF_QUALITY,
                                  DEFAULT_PITCH,
                                  "System"));
}
//---------------------------------------------------------------------------
PSS_MessageDlg::PSS_MessageDlg(const PSS_MessageDlg& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_MessageDlg::~PSS_MessageDlg()
{}
//---------------------------------------------------------------------------
const PSS_MessageDlg& PSS_MessageDlg::operator = (const PSS_MessageDlg& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_MessageDlg::ShowMessage(const CString& text, const CString& title, UINT bitmapID)
{
    m_Title    = title;
    m_Text     = text;
    m_BitmapID = bitmapID;

    if (m_BitmapID)
        m_hInst = ::AfxFindResourceHandle(MAKEINTRESOURCE(m_BitmapID), RT_BITMAP);

    DoModal();
}
//---------------------------------------------------------------------------
void PSS_MessageDlg::ShowMessage(UINT textID, UINT titleID, UINT bitmapID)
{
    CString text;
    text.LoadString(textID);

    CString title;

    if (titleID)
        title.LoadString(titleID);

    ShowMessage(text, title, bitmapID);
}
//---------------------------------------------------------------------------
void PSS_MessageDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_MessageDlg)
    DDX_Control(pDX, IDC_DIALOGMESSAGE_ICON, m_AppIcon);
    DDX_Control(pDX, IDC_CLOSEWINDOW, m_CloseButton);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_MessageDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    m_CloseButton.SetIcon(IDI_CLOSEWINDOW);
    m_CloseButton.SetBtnCursor(IDC_CLOSEWINDOW);
    m_CloseButton.SetAlign(PSS_FlatButton::IE_ST_ALIGN_HORZ_RIGHT);
    m_CloseButton.DrawTransparent();

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_MessageDlg::OnTimer(UINT nIDEvent)
{
    // increment the icon for the next time
    m_AppIcon.SetIcon(m_pIcon[m_Icon]);

    if (++m_Icon >= M_Message_Icon_Count)
        m_Icon = 0;

    CDialog::OnTimer(nIDEvent);
}
//---------------------------------------------------------------------------
void PSS_MessageDlg::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);

    CBrush newBrush(defCOLOR_WHITE);

    CRect rect;
    GetClientRect(&rect);

    CRect whiteRect(rect.left + 1, rect.top + 1, rect.right - 2, rect.top + 40);

    CBrush* pOldBrush = dc.SelectObject(&newBrush);
    dc.FillRect(whiteRect, &newBrush);

    CPen  blackPen(PS_SOLID, 1, defCOLOR_GRAY);
    CPen* pOldPen = dc.SelectObject(&blackPen);
    dc.MoveTo(rect.right, rect.top);
    dc.LineTo(rect.left,  rect.top);
    dc.LineTo(rect.left,  rect.top + 40);
    dc.SelectObject(pOldPen);

    CPen grayPen(PS_SOLID, 1, defCOLOR_BLACK);
    pOldPen = dc.SelectObject(&grayPen);
    dc.MoveTo(rect.left,      rect.top + 40);
    dc.LineTo(rect.right - 1, rect.top + 40);
    dc.LineTo(rect.right - 1, rect.top);
    dc.SelectObject(pOldPen);

    Draw3DLine(dc.m_hDC, 0, whiteRect.left + 2, whiteRect.bottom + 2, whiteRect.right - 2, whiteRect.bottom + 2);

    // draw the title
    CFont* pOldFont = dc.SelectObject(&m_TitleFont);
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(defCOLOR_BLACK);
    dc.SetTextAlign(TA_LEFT | TA_BOTTOM);
    dc.TextOut(rect.left + 20, rect.top + 30, m_Title);
    dc.SelectObject(pOldFont);

    // draw the text 
    CRect textRect(rect.left + 40, rect.top + 65, rect.right - 20, rect.bottom - 40);
    DrawEngraveRect(dc.m_hDC, textRect, defCOLOR_LTLTGRAY);

    pOldFont = dc.SelectObject(&m_TextFont);
    dc.SetTextColor(defCOLOR_BLACK);
    dc.SetTextAlign(0);
    textRect.InflateRect(-5, -5);
    dc.DrawText(m_Text, -1, &textRect, DT_LEFT | DT_BOTTOM | DT_WORDBREAK);

    Draw3DLine(dc.m_hDC, 0, whiteRect.left + 2, rect.bottom - 30, whiteRect.right - 2, rect.bottom - 30);

    dc.SelectObject(pOldFont);
    dc.SelectObject(pOldBrush);

    // draw the bitmap
    if (m_BitmapID && m_hInst)
        ShowBitmapFile(MAKEINTRESOURCE(m_BitmapID),
                       dc.m_hDC,
                       m_hInst,
                       rect.right - 5,
                       rect.top   + 5);
}
//---------------------------------------------------------------------------
void PSS_MessageDlg::OnCloseWindow()
{
    CloseWindow();
}
//---------------------------------------------------------------------------
int PSS_MessageDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

    // create the animation timer
    m_TimerID = SetTimer(ID_TIMERMESSAGE, 120, NULL);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_MessageDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    PSS_Dialog::OnLButtonDown(nFlags, point);
    CloseWindow();
}
//---------------------------------------------------------------------------
void PSS_MessageDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    PSS_Dialog::OnLButtonDblClk(nFlags, point);
    CloseWindow();
}
//---------------------------------------------------------------------------
void PSS_MessageDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    PSS_Dialog::OnMouseMove(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_MessageDlg::CloseWindow()
{
    // remove the timer
    KillTimer(m_TimerID);
    m_TimerID = 0;

    for (int i = 0; i < M_Message_Icon_Count; ++i)
        DestroyIcon(m_pIcon[i]);

    ReleaseCapture();
    EndDialog(IDOK);
}
//---------------------------------------------------------------------------
