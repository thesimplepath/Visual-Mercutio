// ZIProcessTemplateView.cpp : implementation file
//

#include "stdafx.h"
#include "ZIProcessTemplateView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIProcessTemplateView

IMPLEMENT_DYNCREATE(ZIProcessTemplateView, ZITemplateView)

ZIProcessTemplateView::ZIProcessTemplateView()
{
}

ZIProcessTemplateView::~ZIProcessTemplateView()
{
}



BEGIN_MESSAGE_MAP(ZIProcessTemplateView, ZITemplateView)
    //{{AFX_MSG_MAP(ZIProcessTemplateView)
    ON_MESSAGE(UM_INITIALIZE_PROCESSTEMPLATEMANAGER, OnInitializeTemplateManager)
    ON_MESSAGE(UM_RELOAD_PROCESSTEMPLATEMANAGER, OnReloadTemplateManager)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIProcessTemplateView message handlers



afx_msg LRESULT ZIProcessTemplateView::OnInitializeTemplateManager( WPARAM wParam, LPARAM lParam )
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (ZDTemplateManager*)lParam;
    m_IncludeFiles = (BOOL)wParam;

    if (m_pTemplateManager)
    {
        ZIProcessTemplateView::Initialize( m_pTemplateManager, m_IncludeFiles );
    }
    else
    {
//        m_TemplateTree.Empty();
    }
    return 1;
}


afx_msg LRESULT ZIProcessTemplateView::OnReloadTemplateManager( WPARAM wParam, LPARAM lParam )
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (ZDTemplateManager*)lParam;

    if (m_pTemplateManager)
    {
        ZIProcessTemplateView::ReInitialize( m_pTemplateManager, m_IncludeFiles );
    }
    else
    {
//        m_TemplateTree.Empty();
    }
    return 1;
}


