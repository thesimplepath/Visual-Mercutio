// ZIFormTemplateView.cpp : implementation file
//

#include "stdafx.h"
#include "ZIFormTemplateView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIFormTemplateView

IMPLEMENT_DYNCREATE(ZIFormTemplateView, ZITemplateView)

ZIFormTemplateView::ZIFormTemplateView()
{
}

ZIFormTemplateView::~ZIFormTemplateView()
{
}



BEGIN_MESSAGE_MAP(ZIFormTemplateView, ZITemplateView)
    //{{AFX_MSG_MAP(ZIFormTemplateView)
    ON_MESSAGE(UM_INITIALIZE_TEMPLATEMANAGER, OnInitializeTemplateManager)
    ON_MESSAGE(UM_RELOAD_TEMPLATEMANAGER, OnReloadTemplateManager)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIFormTemplateView message handlers



afx_msg LRESULT ZIFormTemplateView::OnInitializeTemplateManager( WPARAM wParam, LPARAM lParam )
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (ZDTemplateManager*)lParam;
    m_IncludeFiles = (BOOL)wParam;

    if (m_pTemplateManager)
    {
        ZIFormTemplateView::Initialize( m_pTemplateManager, m_IncludeFiles );
    }
    else
    {
//        m_TemplateTree.Empty();
    }
    return 1;
}


afx_msg LRESULT ZIFormTemplateView::OnReloadTemplateManager( WPARAM wParam, LPARAM lParam )
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (ZDTemplateManager*)lParam;

    if (m_pTemplateManager)
    {
        ZIFormTemplateView::ReInitialize( m_pTemplateManager, m_IncludeFiles );
    }
    else
    {
//        m_TemplateTree.Empty();
    }
    return 1;
}


