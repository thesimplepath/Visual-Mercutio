/****************************************************************************
 * ==> PSS_FormTemplateView ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a form template view                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FormTemplateView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_FormTemplateView, PSS_TemplateView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FormTemplateView, PSS_TemplateView)
    //{{AFX_MSG_MAP(PSS_FormTemplateView)
    ON_MESSAGE(UM_INITIALIZE_TEMPLATEMANAGER, OnInitializeTemplateManager)
    ON_MESSAGE(UM_RELOAD_TEMPLATEMANAGER, OnReloadTemplateManager)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FormTemplateView
//---------------------------------------------------------------------------
PSS_FormTemplateView::PSS_FormTemplateView() :
    PSS_TemplateView()
{}
//---------------------------------------------------------------------------
PSS_FormTemplateView::~PSS_FormTemplateView()
{}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_FormTemplateView::OnInitializeTemplateManager(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (ZDTemplateManager*)lParam;
    m_IncludeFiles     = BOOL(wParam);

    if (m_pTemplateManager)
        Initialize(m_pTemplateManager, m_IncludeFiles);

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_FormTemplateView::OnReloadTemplateManager(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (ZDTemplateManager*)lParam;

    if (m_pTemplateManager)
        ReInitialize(m_pTemplateManager, m_IncludeFiles);

    return 1;
}
//---------------------------------------------------------------------------
