/****************************************************************************
 * ==> PSS_ColorBtn --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a color picker button and its associated dialog   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ColorBtn.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
/// The color table, initialized to windows' 20 static colors
COLORREF PSS_ColorBtnDialog::m_Colors[20] =
{
    RGB(0,   0,   0),
    RGB(128, 0,   0),
    RGB(0,   128, 0),
    RGB(128, 128, 0),
    RGB(0,   0,   128),
    RGB(128, 0,   128),
    RGB(0,   128, 128),
    RGB(192, 192, 192),
    RGB(192, 220, 192),
    RGB(166, 202, 240),
    RGB(255, 251, 240),
    RGB(160, 160, 164),
    RGB(128, 128, 128),
    RGB(255, 0,   0),
    RGB(0,   255, 0),
    RGB(255, 255, 0),
    RGB(0,   0,   255),
    RGB(255, 0,   255),
    RGB(0,   255, 255),
    RGB(255, 255, 255)
};

/// MRU table. See notes for Reset()
BYTE PSS_ColorBtnDialog::m_Used[20] =
{
    1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2
};
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ColorBtnDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_ColorBtnDialog)
    ON_BN_CLICKED(IDC_OTHER, OnOther)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_DRAWITEM()
    ON_COMMAND_RANGE(IDC_COLOR1, IDC_COLOR20, OnColor)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ColorBtnDialog
//---------------------------------------------------------------------------
PSS_ColorBtnDialog::PSS_ColorBtnDialog(CWnd* pParent) :
    CDialog(PSS_ColorBtnDialog::IDD, pParent),
    m_ColorIndex(-1)
{}
//---------------------------------------------------------------------------
void PSS_ColorBtnDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ColorBtnDialog)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ColorBtnDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (!m_pParentWnd)
        return TRUE;

    RECT r;
    m_pParentWnd->GetWindowRect(&r);

    // move the dialog below the button
    SetWindowPos(NULL, r.left, r.bottom, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    RECT r2;
    GetWindowRect(&r2);

    // check if the dialog has a portion outside the screen, if so, adjust
    if (r2.bottom > ::GetSystemMetrics(SM_CYSCREEN))
        r2.top = r.top - (r2.bottom - r2.top);

    if (r2.right > ::GetSystemMetrics(SM_CXSCREEN))
        r2.left = ::GetSystemMetrics(SM_CXSCREEN) - (r2.right - r2.left);

    SetWindowPos(NULL, r2.left, r2.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    // capture the mouse, this allows the dialog to close when the user clicks outside.
    // Remember that the dialog has no "close" button
    SetCapture();

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ColorBtnDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    RECT  r;
    POINT p;

    p.x = point.x;
    p.y = point.y;
    ClientToScreen(&p);

    GetWindowRect(&r);

    // the user clicked...
    if (!PtInRect(&r, p))
    {
        //  ...outside the dialog, close
        EndDialog(IDCANCEL);
    }
    else
    {
        // ...inside the dialog. Since this window has the mouse captured, its children
        // get no messages. So, check to see if the click was in one of its children and
        // tell him. If the user clicks inside the dialog but not on any of the controls,
        // ChildWindowFromPoint returns a pointer to the dialog. In this case we do not
        // resend the message (obviously) because it would cause a stack overflow
        CWnd* pChild = ChildWindowFromPoint(point);

        if (pChild && pChild != this)
            pChild->SendMessage(WM_LBUTTONDOWN, 0, 0l);
    }

    CDialog::OnLButtonDown(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_ColorBtnDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
    // see notes for OnLButtonDown
    CWnd* pChild = ChildWindowFromPoint(point, CWP_ALL);

    if (pChild && pChild != this)
        pChild->SendMessage(WM_LBUTTONDOWN, 0, 0l);

    CDialog::OnLButtonUp(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_ColorBtnDialog::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpd)
{
    CPen   nullPen;
    CBrush brush;

    // draw the color wheel using the current color table
    nullPen.CreateStockObject(NULL_PEN);
    brush.CreateSolidBrush(m_Colors[nIDCtl - IDC_COLOR1]);

    CPen*   pOldPen   = NULL;
    CBrush* pOldBrush = NULL;
    CDC     dc;

    try
    {
        dc.Attach(lpd->hDC);

        pOldPen   = dc.SelectObject(&nullPen);
        pOldBrush = dc.SelectObject(&brush);

        ++lpd->rcItem.right;
        ++lpd->rcItem.bottom;

        dc.Rectangle(&lpd->rcItem);
    }
    catch (...)
    {
        if (pOldPen)
            dc.SelectObject(pOldPen);

        if (pOldBrush)
            dc.SelectObject(pOldBrush);

        dc.Detach();

        throw;
    }

    if (pOldPen)
        dc.SelectObject(pOldPen);

    if (pOldBrush)
        dc.SelectObject(pOldBrush);

    dc.Detach();

    CDialog::OnDrawItem(nIDCtl, lpd);
}
//---------------------------------------------------------------------------
void PSS_ColorBtnDialog::OnOther()
{
    // the "Other" button
    ReleaseCapture();

    CColorDialog colorDlg;
    colorDlg.m_cc.Flags |= CC_FULLOPEN;

    if (colorDlg.DoModal() == IDOK)
    {
        // the user clicked OK, set the color and close
        const COLORREF newColor = colorDlg.GetColor();

        // check if the selected color is already in the table
        m_ColorIndex = -1;

        for (int i = 0; i < 20; ++i)
            if (m_Colors[i] == newColor)
            {
                m_ColorIndex = i;
                break;
            }

        // if the color was not found, replace the LRU with this color
        if (m_ColorIndex == -1)
            for (int i = 0; i < 20; ++i)
                if (m_Used[i] == 20)
                {
                    m_Colors[i]  = newColor;
                    m_ColorIndex = i;
                    break;
                }

        // this is the new MRU
        if (m_ColorIndex != -1)
        {
            for (int i = 0; i < 20; ++i)
                if (m_Used[m_ColorIndex] > m_Used[i])
                    ++m_Used[i];

            m_Used[m_ColorIndex] = 1;
        }

        EndDialog(IDOK);

        return;
    }

    // if the user clicked "Cancel", reclaim the mouse capture
    SetCapture();
}
//---------------------------------------------------------------------------
void PSS_ColorBtnDialog::OnColor(UINT id)
{
    // a color was clicked on the wheel, set the color index and close
    m_ColorIndex = id - IDC_COLOR1;

    // this color is now the MRU
    for (int i = 0; i < 20; ++i)
        if (m_Used[m_ColorIndex] > m_Used[i])
            ++m_Used[i];

    m_Used[m_ColorIndex] = 1;

    EndDialog(IDOK);
}
//---------------------------------------------------------------------------
void PSS_ColorBtnDialog::EndDialog(int nResult)
{
    ReleaseCapture();

    CDialog::EndDialog(nResult);
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ColorBtn, CButton)
    //{{AFX_MSG_MAP(PSS_ColorBtn)
    ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ColorBtn
//---------------------------------------------------------------------------
PSS_ColorBtn::PSS_ColorBtn() :
    CButton(),
    m_pColorDlg(NULL),
    m_pOldBrush(NULL),
    m_pOldPen(NULL),
    m_CurrentColor(RGB(255, 255, 255))
{
    // create the color dialog and allow it to position itself (by setting the parent)
    m_pColorDlg = new PSS_ColorBtnDialog(this);

    // create the brushes and pens that will be used to draw the button
    m_NullBrush.CreateStockObject(NULL_BRUSH);
    m_BackBrush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
    m_NullPen.CreateStockObject(NULL_PEN);
    m_BlackPen.CreateStockObject(BLACK_PEN);
    m_WhitePen.CreateStockObject(WHITE_PEN);
    m_DkGray.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
}
//---------------------------------------------------------------------------
PSS_ColorBtn::~PSS_ColorBtn()
{
    if (m_pColorDlg)
        delete m_pColorDlg;
}
//---------------------------------------------------------------------------
void PSS_ColorBtn::Reset()
{
    PSS_ColorBtnDialog::m_Colors[0]  = RGB(0,   0,   0);
    PSS_ColorBtnDialog::m_Colors[1]  = RGB(128, 0,   0);
    PSS_ColorBtnDialog::m_Colors[2]  = RGB(0,   128, 0);
    PSS_ColorBtnDialog::m_Colors[3]  = RGB(128, 128, 0);
    PSS_ColorBtnDialog::m_Colors[4]  = RGB(0,   0,   128);
    PSS_ColorBtnDialog::m_Colors[5]  = RGB(128, 0,   128);
    PSS_ColorBtnDialog::m_Colors[6]  = RGB(0,   128, 128);
    PSS_ColorBtnDialog::m_Colors[7]  = RGB(192, 192, 192);
    PSS_ColorBtnDialog::m_Colors[8]  = RGB(192, 220, 192);
    PSS_ColorBtnDialog::m_Colors[9]  = RGB(166, 202, 240);
    PSS_ColorBtnDialog::m_Colors[10] = RGB(255, 251, 240);
    PSS_ColorBtnDialog::m_Colors[11] = RGB(160, 160, 164);
    PSS_ColorBtnDialog::m_Colors[12] = RGB(128, 128, 128);
    PSS_ColorBtnDialog::m_Colors[13] = RGB(255, 0,   0);
    PSS_ColorBtnDialog::m_Colors[14] = RGB(0,   255, 0);
    PSS_ColorBtnDialog::m_Colors[15] = RGB(255, 255, 0);
    PSS_ColorBtnDialog::m_Colors[16] = RGB(0,   0,   255);
    PSS_ColorBtnDialog::m_Colors[17] = RGB(255, 0,   255);
    PSS_ColorBtnDialog::m_Colors[18] = RGB(0,   255, 255);
    PSS_ColorBtnDialog::m_Colors[19] = RGB(255, 255, 255);

    // This "colorful" (no pun intended) order ensures that the colors at the center of the color table
    // will get replaced first. This preserves the white and black colors even if they're not used
    // (They'll get replaced last)
    PSS_ColorBtnDialog::m_Used[0]  = 1;
    PSS_ColorBtnDialog::m_Used[1]  = 3;
    PSS_ColorBtnDialog::m_Used[2]  = 5;
    PSS_ColorBtnDialog::m_Used[3]  = 7;
    PSS_ColorBtnDialog::m_Used[4]  = 9;
    PSS_ColorBtnDialog::m_Used[5]  = 11;
    PSS_ColorBtnDialog::m_Used[6]  = 13;
    PSS_ColorBtnDialog::m_Used[7]  = 15;
    PSS_ColorBtnDialog::m_Used[8]  = 17;
    PSS_ColorBtnDialog::m_Used[9]  = 19;
    PSS_ColorBtnDialog::m_Used[10] = 20;
    PSS_ColorBtnDialog::m_Used[11] = 18;
    PSS_ColorBtnDialog::m_Used[12] = 16;
    PSS_ColorBtnDialog::m_Used[13] = 14;
    PSS_ColorBtnDialog::m_Used[14] = 12;
    PSS_ColorBtnDialog::m_Used[15] = 10;
    PSS_ColorBtnDialog::m_Used[16] = 8;
    PSS_ColorBtnDialog::m_Used[17] = 6;
    PSS_ColorBtnDialog::m_Used[18] = 4;
    PSS_ColorBtnDialog::m_Used[19] = 2;
}
//---------------------------------------------------------------------------
BOOL PSS_ColorBtn::Load()
{
    BYTE* pData = NULL;
    UINT  size;

    // allocate the memory
    AfxGetApp()->GetProfileBinary(_T("ColorData"), _T("ColorTable"), &pData, &size);

    if (pData)
    {
        // copy the data in the table and get rid of the buffer
        std::memcpy((void*)PSS_ColorBtnDialog::m_Colors, (void*)pData, size);
        std::free((void*)pData);

        AfxGetApp()->GetProfileBinary(_T("ColorData"), _T("MRU"), &pData, &size);

        if (pData)
        {
            std::memcpy((void*)PSS_ColorBtnDialog::m_Used, (void*)pData, size);
            std::free((void*)pData);

            return TRUE;
        }
    }

    // if the loading fails, back to the default
    Reset();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_ColorBtn::Store()
{
    return (AfxGetApp()->WriteProfileBinary(_T("ColorData"), _T("ColorTable"), LPBYTE(PSS_ColorBtnDialog::m_Colors), sizeof(COLORREF) * 20) &&
            AfxGetApp()->WriteProfileBinary(_T("ColorData"), _T("MRU"),        LPBYTE(PSS_ColorBtnDialog::m_Used),   sizeof(BYTE)     * 20));
}
//---------------------------------------------------------------------------
void PSS_ColorBtn::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar.Write((void*)PSS_ColorBtnDialog::m_Colors, sizeof(COLORREF) * 20);
        ar.Write((void*)PSS_ColorBtnDialog::m_Used,   sizeof(BYTE)     * 20);
    }
    else
    {
        ar.Read((void*)PSS_ColorBtnDialog::m_Colors, sizeof(COLORREF) * 20);
        ar.Read((void*)PSS_ColorBtnDialog::m_Used,   sizeof(BYTE)     * 20);
    }
}
//---------------------------------------------------------------------------
void PSS_ColorBtn::OnClicked()
{
    // when the button is clicked, show the dialog
    if (m_pColorDlg->DoModal() == IDOK)
    {
        m_CurrentColor = PSS_ColorBtnDialog::m_Colors[m_pColorDlg->m_ColorIndex];
        InvalidateRect(NULL);
        GetParent()->SendMessage(WM_COLOR_CHANGED);
    }
}
//---------------------------------------------------------------------------
void PSS_ColorBtn::DrawItem(LPDRAWITEMSTRUCT lpd)
{
    CDC dc;
    dc.Attach(lpd->hDC);

    // store that for convinience
    int top    = lpd->rcItem.top;
    int left   = lpd->rcItem.left;
    int bottom = lpd->rcItem.bottom;
    int right  = lpd->rcItem.right;

    CBrush colorBrush;
    colorBrush.CreateSolidBrush(m_CurrentColor);

    try
    {
        m_pOldPen   = dc.SelectObject(&m_NullPen);
        m_pOldBrush = dc.SelectObject(&m_BackBrush);

        // clear the background using the back brush color
        dc.Rectangle(&lpd->rcItem);

        // draw the border
        if (!(lpd->itemState & ODS_SELECTED))
        {
            // button is up
            dc.SelectObject(&m_BlackPen);
            dc.MoveTo(left,      bottom - 1);
            dc.LineTo(right - 1, bottom - 1);
            dc.LineTo(right - 1, top);

            dc.SelectObject(&m_DkGray);
            dc.MoveTo(left  + 1, bottom - 2);
            dc.LineTo(right - 2, bottom - 2);
            dc.LineTo(right - 2, top    + 1);

            dc.SelectObject(&m_WhitePen);
            dc.LineTo(left + 1, top    + 1);
            dc.LineTo(left + 1, bottom - 2);
        }
        else
        {
            // button is down
            dc.SelectObject(&m_DkGray);
            dc.MoveTo(left,      bottom - 1);
            dc.LineTo(left,      top);
            dc.LineTo(right - 1, top);

            dc.SelectObject(&m_WhitePen);
            dc.MoveTo(right - 1, top    - 1);
            dc.LineTo(right - 1, bottom - 1);
            dc.LineTo(left  + 1, bottom - 1);

            dc.SelectObject(&m_BlackPen);
            dc.MoveTo(left  + 1, bottom - 2);
            dc.LineTo(left  + 1, top    + 1);
            dc.LineTo(right - 2, top    + 1);

            // by moving the borders, we get the things inside the button to draw themselves
            // one pixel down and one to the right. This completes the "pushed" effect
            ++left;
            ++right;
            ++bottom;
            ++top;
        }

        // the division
        dc.SelectObject(&m_WhitePen);
        dc.MoveTo(right - 10, top    + 4);
        dc.LineTo(right - 10, bottom - 4);

        dc.SelectObject(m_DkGray);
        dc.MoveTo(right - 11, top    + 4);
        dc.LineTo(right - 11, bottom - 4);

        // the triangle
        if (lpd->itemState & ODS_DISABLED)
            dc.SelectObject(m_DkGray);
        else
            dc.SelectObject(m_BlackPen);

        dc.MoveTo(right - 4, (bottom / 2) - 1);
        dc.LineTo(right - 9, (bottom / 2) - 1);

        dc.MoveTo(right - 5, (bottom / 2));
        dc.LineTo(right - 8, (bottom / 2));

        if (lpd->itemState & ODS_DISABLED)
        {
            dc.SetPixel(right - 4, (bottom / 2) - 1, RGB(255, 255, 255));
            dc.SetPixel(right - 5, (bottom / 2),     RGB(255, 255, 255));
            dc.SetPixel(right - 6, (bottom / 2) + 1, RGB(255, 255, 255));
        }
        else
            dc.SetPixel(right - 6, (bottom / 2) + 1, RGB(0, 0, 0));

        // the color rectangle, only if enabled
        if (!(lpd->itemState & ODS_DISABLED))
        {
            dc.SelectObject(&colorBrush);
            dc.Rectangle(left + 5, top + 4, right - 15, bottom - 4);
        }

        if (lpd->itemState & ODS_FOCUS)
        {
            // draw the focus. It would have been nice just to draw a rectangle using a pen created
            // with the PS_ALTERNATE style, but this is not supported by WIN95
            for (int i = left + 3; i < right - 4; i += 2)
            {
                dc.SetPixel(i, top    + 3, RGB(0, 0, 0));
                dc.SetPixel(i, bottom - 4, RGB(0, 0, 0));
            }

            for (int i = top + 3; i < bottom - 4; i += 2)
            {
                dc.SetPixel(left  + 3, i, RGB(0, 0, 0));
                dc.SetPixel(right - 4, i, RGB(0, 0, 0));
            }
        }
    }
    catch (...)
    {
        if (m_pOldPen)
        {
            dc.SelectObject(m_pOldPen);
            m_pOldPen = NULL;
        }

        if (m_pOldBrush)
        {
            dc.SelectObject(m_pOldBrush);
            m_pOldBrush = NULL;
        }

        dc.Detach();

        throw;
    }

    if (m_pOldPen)
    {
        dc.SelectObject(m_pOldPen);
        m_pOldPen = NULL;
    }

    if (m_pOldBrush)
    {
        dc.SelectObject(m_pOldBrush);
        m_pOldBrush = NULL;
    }

    dc.Detach();
}
//---------------------------------------------------------------------------
