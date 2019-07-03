/****************************************************************************
 * ==> PSS_TipOfDayBar -----------------------------------------------------*
 ****************************************************************************
 * Description : Tip of the day bar component                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_TipOfDayBar.h"

// resources
#include "ZTipRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_TipOfDayBar, SECControlBar)
    //{{AFX_MSG_MAP(PSS_TipOfDayBar)
    ON_WM_CREATE()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_TipOfDayBar
//---------------------------------------------------------------------------
PSS_TipOfDayBar::PSS_TipOfDayBar() :
    SECControlBar(),
    m_pBrowser(NULL)
{}
//---------------------------------------------------------------------------
PSS_TipOfDayBar::~PSS_TipOfDayBar()
{
    if (m_pBrowser)
        delete m_pBrowser;
}
//---------------------------------------------------------------------------
int PSS_TipOfDayBar::OnCreate(LPCREATESTRUCT pCreateStruct)
{
    if (SECControlBar::OnCreate(pCreateStruct) == -1)
        return -1;

    CRect rect;
    GetClientRect (&rect);

    // create the control
    m_pBrowser = new ZWebBrowser;
    ASSERT (m_pBrowser);

    if (!m_pBrowser->Create(NULL, NULL, WS_VISIBLE, rect, this, NULL))
    {
        TRACE("failed to create ZTipOfDayBar\n");
        delete m_pBrowser;
        m_pBrowser = NULL;
        return -1;
    }

    return 0;
}
//---------------------------------------------------------------------------
void PSS_TipOfDayBar::OnSize(UINT type, int cx, int cy)
{
    if (m_pBrowser && ::IsWindow(m_pBrowser->GetSafeHwnd()))
    {
        CRect rectInside;
        GetInsideRect(rectInside);

        ::SetWindowPos(m_pBrowser->GetSafeHwnd(),
                       NULL,
                       rectInside.left,
                       rectInside.top,
                       rectInside.Width(),
                       rectInside.Height(),
                       SWP_NOZORDER | SWP_NOACTIVATE);
    }

    SECControlBar::OnSize(type, cx, cy);
}
//---------------------------------------------------------------------------
