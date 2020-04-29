/****************************************************************************
 * ==> PSS_HelpContextBar --------------------------------------------------*
 ****************************************************************************
 * Description : Contextual help bar component                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_HelpContextBar.h"

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
BEGIN_MESSAGE_MAP(PSS_HelpContextBar, SECControlBar)
    //{{AFX_MSG_MAP(PSS_HelpContextBar)
    ON_WM_CREATE()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_HelpContextBar
//---------------------------------------------------------------------------
PSS_HelpContextBar::PSS_HelpContextBar() :
    m_pBrowser(NULL)
{}
//---------------------------------------------------------------------------
PSS_HelpContextBar::~PSS_HelpContextBar()
{
    if (m_pBrowser)
        delete m_pBrowser;
}
//---------------------------------------------------------------------------
int PSS_HelpContextBar::OnCreate(LPCREATESTRUCT pCreateStruct)
{
    if (SECControlBar::OnCreate(pCreateStruct) == -1)
        return -1;

    CRect rect;
    GetClientRect(&rect);

    if (m_pBrowser)
        delete m_pBrowser;

    // create the control
    m_pBrowser = new PSS_WebBrowser();

    if (!m_pBrowser->Create(NULL, NULL, WS_VISIBLE, rect, this, NULL))
    {
        TRACE("failed to create ZHelpContextBar\n");
        delete m_pBrowser;
        m_pBrowser = NULL;
        return -1;
    }

    return 0;
}
//---------------------------------------------------------------------------
void PSS_HelpContextBar::OnSize(UINT type, int cx, int cy)
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
