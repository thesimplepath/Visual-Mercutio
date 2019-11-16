/****************************************************************************
 * ==> PSS_MsgBox ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a message box                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_MsgBox.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_TimerAboutID 15
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_MsgBox, CDialog)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_MsgBox, CDialog)
    //{{AFX_MSG_MAP(PSS_MsgBox)
    ON_WM_TIMER()
    ON_WM_CREATE()
    ON_WM_PAINT()
    ON_BN_CLICKED(IDYES, OnYes)
    ON_BN_CLICKED(IDNO, OnNo)
    ON_BN_CLICKED(IDCANCEL, OnCancelBtn)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_MsgBox
//---------------------------------------------------------------------------
PSS_MsgBox::PSS_MsgBox(CWnd* pParent) :
    CDialog(PSS_MsgBox::IDD, pParent),
    m_TimerID(0),
    m_Style(0),
    m_IconIndex(0),
    m_DoShowUnlockButton(FALSE)
{}
//---------------------------------------------------------------------------
PSS_MsgBox::~PSS_MsgBox()
{}
//---------------------------------------------------------------------------
int PSS_MsgBox::Show(LPCSTR pMessage, UINT style)
{
    m_Text  = pMessage;
    m_Style = style;

    return DoModal();
}
//---------------------------------------------------------------------------
int PSS_MsgBox::Show(UINT messageID, UINT style, HINSTANCE hInstance)
{
    if (hInstance)
    {
        char buffer[500];
        ::LoadString(hInstance, messageID, buffer, sizeof(buffer));
        m_Text = buffer;
    }
    else
        m_Text.LoadString(messageID);

    m_Style = style;

    return DoModal();
}
//---------------------------------------------------------------------------
void PSS_MsgBox::DoChangeCancelBtnToUnlockBtn(BOOL value)
{
    m_DoShowUnlockButton = value;
}
//---------------------------------------------------------------------------
void PSS_MsgBox::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_MsgBox)
    DDX_Control(pDX, IDC_DIALOGSAVE_ICON, m_Icon);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
int PSS_MsgBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDialog::OnCreate(lpCreateStruct) == -1)
        return -1;

    m_pAnimIcons[0] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP1));
    m_pAnimIcons[1] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP2));
    m_pAnimIcons[2] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP3));
    m_pAnimIcons[3] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP4));
    m_pAnimIcons[4] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP5));
    m_pAnimIcons[5] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP6));
    m_pAnimIcons[6] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP7));

    m_pAnimIcons2[0] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP_1));
    m_pAnimIcons2[1] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP_2));
    m_pAnimIcons2[2] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP_3));
    m_pAnimIcons2[3] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP_4));
    m_pAnimIcons2[4] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP_5));
    m_pAnimIcons2[5] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP_6));
    m_pAnimIcons2[6] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP_7));
    m_pAnimIcons2[7] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP_8));
    m_pAnimIcons2[8] = ::LoadIcon(g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDI_ICONAPP_9));

    // create the timer for the animation
    m_TimerID = SetTimer(M_TimerAboutID, 80, NULL);

    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_MsgBox::OnInitDialog()
{
    CDialog::OnInitDialog();

    CRect rect;
    GetClientRect(&rect);

    const UINT uiX = ::GetSystemMetrics(SM_CXFULLSCREEN);
    const UINT uiY = ::GetSystemMetrics(SM_CYFULLSCREEN);

    // put the window in the center of the screen
    SetWindowPos(NULL, (uiX - rect.right) / 2, (uiY - rect.bottom) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

    AdjustSize();

    // Return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_MsgBox::OnTimer(UINT nIDEvent)
{
    // increment the icon for the next time
    if (m_Style == MB_OK)
    {
        m_Icon.SetIcon(m_pAnimIcons[m_IconIndex]);

        if (++m_IconIndex >= M_AnimIconNb)
            m_IconIndex = 0;
    }
    else
    {
        m_Icon.SetIcon(m_pAnimIcons2[m_IconIndex]);

        if (++m_IconIndex >= M_AnimIcon2Nb)
            m_IconIndex = 0;
    }

    CDialog::OnTimer(nIDEvent);
}
//---------------------------------------------------------------------------
void PSS_MsgBox::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);

    CRect rect;
    GetClientRect(&rect);
    rect.InflateRect(-30, -25);
    dc.DPtoLP(&rect);
    rect.OffsetRect(10, 0);

    // get the image rect
    CRect imageRect;
    m_Icon.GetWindowRect(imageRect);

    // keep the image aligned with the text
    m_Icon.SetWindowPos(NULL,
                        15,
                        rect.top,
                        0,
                        0,
                        SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);

    dc.SetBkMode(TRANSPARENT);

    // set text color
    dc.SetTextColor(defCOLOR_DEFAULT_TEXT);

    // draw the message text
    dc.DrawText(m_Text, -1, &rect, DT_CENTER | DT_WORDBREAK);
}
//---------------------------------------------------------------------------
void PSS_MsgBox::OnYes()
{
    ReleaseDialog();

    CDialog::EndDialog(IDYES);
}
//---------------------------------------------------------------------------
void PSS_MsgBox::OnNo()
{
    ReleaseDialog();

    CDialog::EndDialog(IDNO);
}
//---------------------------------------------------------------------------
void PSS_MsgBox::OnCancelBtn()
{
    ReleaseDialog();

    CDialog::EndDialog(IDCANCEL);
}
//---------------------------------------------------------------------------
void PSS_MsgBox::ReleaseDialog()
{
    // remove the timer
    KillTimer(m_TimerID);
    m_TimerID = 0;

    for (int i = 0; i < M_AnimIconNb; ++i)
        DestroyIcon(m_pAnimIcons[i]);

    for (int i = 0; i < M_AnimIcon2Nb; ++i)
        DestroyIcon(m_pAnimIcons2[i]);
}
//---------------------------------------------------------------------------
void PSS_MsgBox::AdjustSize()
{
    // device context for painting
    CDC* pDC = GetDC();

    if (!pDC)
        return;

    CRect rect;
    GetWindowRect(&rect);
    rect.InflateRect(-30, -50);
    pDC->DPtoLP(&rect);
    rect.bottom = rect.top;

    // save the right coordinate because there is a bug in DrawText to calculate
    const int saveRight = rect.right;

    // measure the message text
    pDC->DrawText(m_Text, -1, &rect, DT_CALCRECT | DT_CENTER | DT_WORDBREAK);

    // restore the right coordinate
    rect.right = saveRight;

    pDC->LPtoDP(&rect);
    rect.InflateRect(30, 60);

    // resize the window but without repainting it
    MoveWindow(&rect, FALSE);

    // get buttons
    CWnd* pYes    = GetDlgItem(IDYES);
    CWnd* pNo     = GetDlgItem(IDNO);
    CWnd* pCancel = GetDlgItem(IDCANCEL);

    if (!pYes || !pNo || !pCancel)
    {
        ReleaseDC(pDC);
        return;
    }

    if (m_DoShowUnlockButton)
        pCancel->SetWindowText(_T("Déverrouiller"));

    // todo -cImprovement -oJean: find a better way to calculate the button positions in a generic manner
    switch (m_Style)
    {
        case MB_OK:
        {
            CRect buttonRect;
            pYes->GetWindowRect(&buttonRect);

            const int width  = buttonRect.Width();
            const int height = buttonRect.Height();

            // center the button in the parent window
            buttonRect.bottom = rect.bottom       - 15;
            buttonRect.top    = buttonRect.bottom - height;
            buttonRect.left   = rect.left         + ((rect.Width() / 2) - (width / 2));
            buttonRect.right  = buttonRect.left   + width;

            // convert to client coordinates
            ScreenToClient(&buttonRect);

            // place the button
            pYes->MoveWindow(&buttonRect);

            // change the button text to show Ok instead of Yes
            pYes->SetWindowText(_T("Ok"));

            // hide the other buttons
            pNo->ShowWindow(SW_HIDE);
            pCancel->ShowWindow(SW_HIDE);

            break;
        }

        case MB_YESNO:
        {
            CRect buttonRectYes;
            pYes->GetWindowRect(&buttonRectYes);

            CRect buttonRectNo;
            pNo->GetWindowRect(&buttonRectNo);

            const int widthYes  = buttonRectYes.Width();
            const int heightYes = buttonRectYes.Height();
            const int widthNo   = buttonRectNo.Width();
            const int heightNo  = buttonRectNo.Height();

            // calculate the yes button position
            buttonRectYes.bottom = rect.bottom          - 15;
            buttonRectYes.top    = buttonRectYes.bottom - heightYes;
            buttonRectYes.left   = rect.left            + ((rect.Width() / 2) - widthYes - 3);
            buttonRectYes.right  = buttonRectYes.left   + widthYes;

            // calculate the no button position
            buttonRectNo.bottom = rect.bottom         - 15;
            buttonRectNo.top    = buttonRectNo.bottom - heightNo;
            buttonRectNo.right  = rect.left           + ((rect.Width() / 2) + widthNo + 3);
            buttonRectNo.left   = buttonRectNo.right  - widthNo;

            // convert to client coordinates
            ScreenToClient(&buttonRectYes);
            ScreenToClient(&buttonRectNo);

            // place the buttons
            pYes->MoveWindow(&buttonRectYes);
            pNo->MoveWindow(&buttonRectNo);

            // hide the remaining button
            pCancel->ShowWindow(SW_HIDE);

            break;
        }

        case MB_YESNOCANCEL:
        {
            CRect buttonRectYes;
            pYes->GetWindowRect(&buttonRectYes);

            CRect buttonRectNo;
            pNo->GetWindowRect(&buttonRectNo);

            CRect buttonRectCancel;
            pCancel->GetWindowRect(&buttonRectCancel);

            const int widthYes     = buttonRectYes.Width();
            const int heightYes    = buttonRectYes.Height();
            const int widthNo      = buttonRectNo.Width();
            const int heightNo     = buttonRectNo.Height();
            const int widthCancel  = buttonRectCancel.Width();
            const int heightCancel = buttonRectCancel.Height();

            // calculate the no button position. NOTE Begins with it because located on the parent center
            buttonRectNo.bottom = rect.bottom         - 15;
            buttonRectNo.top    = buttonRectNo.bottom - heightNo;
            buttonRectNo.left   = rect.left           + ((rect.Width() / 2) - (widthNo / 2));
            buttonRectNo.right  = buttonRectNo.left   + widthNo;

            // calculate the yes button position
            buttonRectYes.bottom = rect.bottom          - 15;
            buttonRectYes.top    = buttonRectYes.bottom - heightYes;
            buttonRectYes.right  = buttonRectNo.left    - 6;
            buttonRectYes.left   = buttonRectYes.right  - widthYes;

            // calculate the cancel button position
            buttonRectCancel.bottom = rect.bottom           - 15;
            buttonRectCancel.top    = buttonRectNo.bottom   - heightNo;
            buttonRectCancel.left   = buttonRectNo.right    + 6;
            buttonRectCancel.right  = buttonRectCancel.left + widthCancel;

            // convert to client coordinates
            ScreenToClient(&buttonRectYes);
            ScreenToClient(&buttonRectNo);
            ScreenToClient(&buttonRectCancel);

            // place the buttons
            pYes->MoveWindow(&buttonRectYes);
            pNo->MoveWindow(&buttonRectNo);
            pCancel->MoveWindow(&buttonRectCancel);

            break;
        }

        default:
            THROW(_T(L"Unknown button style"));
    }

    ReleaseDC(pDC);
}
//---------------------------------------------------------------------------
