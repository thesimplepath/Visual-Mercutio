// ZCFormTemplateTree.cpp : implementation file
//

#include "stdafx.h"
#include "ZCFormTemplateTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZCFormTemplateTree

IMPLEMENT_DYNCREATE(ZCFormTemplateTree, ZCTemplateTreeCtrl)

ZCFormTemplateTree::ZCFormTemplateTree()
{
}

ZCFormTemplateTree::~ZCFormTemplateTree()
{
}



BEGIN_MESSAGE_MAP(ZCFormTemplateTree, ZCTemplateTreeCtrl)
    //{{AFX_MSG_MAP(ZCFormTemplateTree)
    ON_MESSAGE(UM_INITIALIZE_TEMPLATEMANAGER, OnInitializeTemplateManager)
    ON_MESSAGE(UM_RELOAD_TEMPLATEMANAGER, OnReloadTemplateManager)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZCFormTemplateTree message handlers



afx_msg LRESULT ZCFormTemplateTree::OnInitializeTemplateManager( WPARAM wParam, LPARAM lParam )
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (ZDTemplateManager*)lParam;
    m_IncludeFiles = (BOOL)wParam;

    if (m_pTemplateManager)
    {
        ZCFormTemplateTree::Initialize( m_pTemplateManager, m_IncludeFiles );
    }
    else
    {
//        m_TemplateTree.Empty();
    }
    return 1;
}


afx_msg LRESULT ZCFormTemplateTree::OnReloadTemplateManager( WPARAM wParam, LPARAM lParam )
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (ZDTemplateManager*)lParam;

    if (m_pTemplateManager)
    {
        ZCFormTemplateTree::ReInitialize( m_pTemplateManager, m_IncludeFiles );
    }
    else
    {
//        m_TemplateTree.Empty();
    }
    return 1;
}


