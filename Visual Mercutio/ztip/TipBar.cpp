// TipBar.cpp : implementation file
//  

#include "stdafx.h"
#include "TipBar.h"
#include "ZTipRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZTipOfDayBar

ZTipOfDayBar::ZTipOfDayBar()
: SECControlBar(),
  m_pBrowser(NULL)
{
    // TODO: add construction code here.
}

ZTipOfDayBar::~ZTipOfDayBar()
{
    if (m_pBrowser)
        delete m_pBrowser;
    m_pBrowser = NULL;
}

BEGIN_MESSAGE_MAP(ZTipOfDayBar, SECControlBar)
    //{{AFX_MSG_MAP(ZTipOfDayBar)
    ON_WM_CREATE()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZTipOfDayBar message handlers

int ZTipOfDayBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (SECControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rect;
    GetClientRect (&rect);

    // Create the control.
    m_pBrowser = new ZWebBrowser;
    ASSERT (m_pBrowser);
    if (!m_pBrowser->Create(NULL,NULL,WS_VISIBLE,rect,this,NULL))
    {
        TRACE("failed to create ZTipOfDayBar\n");
        delete m_pBrowser;
        m_pBrowser = NULL;
        return -1;
    }


//    SetChild(m_pBrowser);

    return 0;
}

void ZTipOfDayBar::OnSize(UINT nType, int cx, int cy) 
{
    if (m_pBrowser && ::IsWindow(m_pBrowser->GetSafeHwnd()))
    {
        CRect rectInside;
        GetInsideRect(rectInside);
        ::SetWindowPos(m_pBrowser->GetSafeHwnd(), NULL, rectInside.left, rectInside.top,
            rectInside.Width(), rectInside.Height(),
            SWP_NOZORDER|SWP_NOACTIVATE);
    }
    SECControlBar::OnSize(nType, cx, cy);
}
