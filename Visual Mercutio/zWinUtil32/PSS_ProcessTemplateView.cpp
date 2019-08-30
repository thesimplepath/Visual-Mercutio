/****************************************************************************
 * ==> PSS_ProcessTemplateView ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a process template view                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessTemplateView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_ProcessTemplateView, PSS_TemplateView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessTemplateView, PSS_TemplateView)
    //{{AFX_MSG_MAP(PSS_ProcessTemplateView)
    ON_MESSAGE(UM_INITIALIZE_PROCESSTEMPLATEMANAGER, OnInitializeTemplateManager)
    ON_MESSAGE(UM_RELOAD_PROCESSTEMPLATEMANAGER, OnReloadTemplateManager)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessTemplateView
//---------------------------------------------------------------------------
PSS_ProcessTemplateView::PSS_ProcessTemplateView() :
    PSS_TemplateView()
{}
//---------------------------------------------------------------------------
PSS_ProcessTemplateView::~PSS_ProcessTemplateView()
{}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessTemplateView::OnInitializeTemplateManager(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (PSS_TemplateManager*)lParam;
    m_IncludeFiles     = BOOL(wParam);

    if (m_pTemplateManager)
        Initialize(m_pTemplateManager, m_IncludeFiles);

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessTemplateView::OnReloadTemplateManager(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (PSS_TemplateManager*)lParam;

    if (m_pTemplateManager)
        ReInitialize(m_pTemplateManager, m_IncludeFiles);

    return 1;
}
//---------------------------------------------------------------------------
