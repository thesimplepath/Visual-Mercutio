/****************************************************************************
 * ==> PSS_StatusBar -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a status bar                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "aniload.h"

// processsoft
#include "draw.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
HBITMAP PSS_StatusBar::m_hBtmBack;
HBITMAP PSS_StatusBar::m_hBtmGreenLight;
HBITMAP PSS_StatusBar::m_hBtmRedLight;
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_StatusBar, SECStatusBar)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_StatusBar, SECStatusBar)
    //{{AFX_MSG_MAP(PSS_StatusBar)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_StatusBar
//---------------------------------------------------------------------------
PSS_StatusBar::PSS_StatusBar() :
    SECStatusBar(),
    m_TickCount(0),
    m_Percent(0),
    m_Image(0),
    m_BackWidth(0),
    m_LeftStart(0),
    m_Step(0),
    m_SwapLight(FALSE),
    m_IsStarted(FALSE)
{
    m_hBtmBack       = LoadBitmap (g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDB_ANILOADBACK));
    m_hBtmGreenLight = LoadBitmap (g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDB_GREENLIGHT));
    m_hBtmRedLight   = LoadBitmap (g_zBaseLibDLL.hModule, MAKEINTRESOURCE(IDB_REDLIGHT));

    BITMAP bm;
    GetObject(m_hBtmBack, sizeof(BITMAP), &bm);
    m_BackWidth = bm.bmWidth + 1;

    // calculate the step
    m_Step = m_BackWidth / 100;

    // create the font
    VERIFY(m_Font.CreateFont(10,                   // Height
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
                             _T("Courier")));

    m_LtBlueBrush.CreateSolidBrush(defCOLOR_LTBLUE);
    m_BlackPen.CreatePen(PS_SOLID, 1, defCOLOR_BLACK);
    m_WhitePen.CreatePen(PS_SOLID, 1, defCOLOR_WHITE);
}
//---------------------------------------------------------------------------
PSS_StatusBar::~PSS_StatusBar()
{
    VERIFY(DeleteObject(m_hBtmBack));
    VERIFY(DeleteObject(m_hBtmGreenLight));
    VERIFY(DeleteObject(m_hBtmRedLight));
}
//---------------------------------------------------------------------------
BOOL PSS_StatusBar::PreCreateWindow(CREATESTRUCT& cs)
{
    // add gripper
    cs.style |= SBARS_SIZEGRIP;
    return SECStatusBar::PreCreateWindow(cs);
}
//---------------------------------------------------------------------------
void PSS_StatusBar::SetCurrentPercentage(int value)
{
    // check if started
    if (!m_IsStarted)
        return;

    if (m_Percent != value)
    {
        m_Percent = __min(100, value);

        // calculate the left meter size
        m_LeftStart += m_Step;

        // to regulate the animation time, check the elapsed time between two
        // animation and change the image only if the time is greater than a
        // certain value
        BOOL  show = TRUE;
        DWORD temp = GetTickCount();

        if (m_TickCount)
        {
            if (temp - m_TickCount < 50)
                show = FALSE;
            else
                m_TickCount = temp;
        }
        else
            m_TickCount = temp;

        CDC* pDC = GetDC();
        ASSERT(pDC);

        if (m_LeftStart < m_BackWidth)
        {
            // show the meter
            CBrush* pOldBrush = pDC->SelectObject(&m_LtBlueBrush);
            CPen*   pOldPen   = pDC->SelectObject(&m_BlackPen);

            pDC->Rectangle(m_ItemRect.left   + 2,
                           m_ItemRect.top    + 2,
                           m_ItemRect.left   + m_LeftStart,
                           m_ItemRect.bottom - 1);

            pDC->SelectObject(&m_WhitePen);
            pDC->MoveTo(m_ItemRect.left + m_LeftStart - 2, m_ItemRect.bottom - 2);
            pDC->LineTo(m_ItemRect.left + 2,               m_ItemRect.bottom - 2);
            pDC->LineTo(m_ItemRect.left + 2,               m_ItemRect.top    + 2);
    
            pDC->SelectObject(pOldBrush);
            pDC->SelectObject(pOldPen);
        }

        if (show)
        {
            if (m_SwapLight)
            {
                DisplayBitmap(m_hBtmGreenLight,
                              pDC->m_hDC,
                              AfxGetInstanceHandle(),
                              m_ItemRect.left + m_BackWidth,
                              m_ItemRect.top);
            }
            else
                DisplayBitmap(m_hBtmRedLight,
                              pDC->m_hDC,
                              AfxGetInstanceHandle(),
                              m_ItemRect.left + m_BackWidth,
                              m_ItemRect.top );

            // switch the light
            m_SwapLight = (m_SwapLight ? FALSE : TRUE);
        }

        VERIFY(ReleaseDC(pDC));
    }
}
//---------------------------------------------------------------------------
void PSS_StatusBar::BeginAniPercentage()
{
    // create the animation timer
    m_IsStarted = TRUE;
    m_Image     = 0;
    m_Percent   = 0;
    m_TickCount = 0;

    // calculate the start position
    m_LeftStart = 5;
    GetItemRect(0, &m_ItemRect);

    CDC* pDC = GetDC();
    ASSERT(pDC);

    DisplayBitmap(m_hBtmBack,
                  pDC->m_hDC,
                  AfxGetInstanceHandle(),
                  m_ItemRect.left,
                  m_ItemRect.top);

    // show the first percentage
    CBrush* pOldBrush = pDC->SelectObject(&m_LtBlueBrush);
    CPen*   pOldPen   = pDC->SelectObject(&m_BlackPen);

    pDC->Rectangle(m_ItemRect.left   + 2,
                   m_ItemRect.top    + 2,
                   m_ItemRect.left   + m_LeftStart,
                   m_ItemRect.bottom - 1);

    pDC->SelectObject(&m_WhitePen);
    pDC->MoveTo(m_ItemRect.left + m_LeftStart - 2, m_ItemRect.bottom - 2);
    pDC->LineTo(m_ItemRect.left + 2,               m_ItemRect.bottom - 2);
    pDC->LineTo(m_ItemRect.left + 2,               m_ItemRect.top    + 2);

    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldPen);
    VERIFY(ReleaseDC(pDC));
}
//---------------------------------------------------------------------------
void PSS_StatusBar::EndAniPercentage()
{
    Invalidate(TRUE);
}
//---------------------------------------------------------------------------
