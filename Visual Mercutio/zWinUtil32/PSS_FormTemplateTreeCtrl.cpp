/****************************************************************************
 * ==> PSS_FormTemplateTreeCtrl --------------------------------------------*
 ****************************************************************************
 * Description : Provides a form template tree control                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FormTemplateTreeCtrl.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_FormTemplateTreeCtrl, PSS_TemplateTreeCtrl)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FormTemplateTreeCtrl, PSS_TemplateTreeCtrl)
    //{{AFX_MSG_MAP(ZCFormTemplateTree)
    ON_MESSAGE(UM_INITIALIZE_TEMPLATEMANAGER, OnInitializeTemplateManager)
    ON_MESSAGE(UM_RELOAD_TEMPLATEMANAGER, OnReloadTemplateManager)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FormTemplateTreeCtrl
//---------------------------------------------------------------------------
PSS_FormTemplateTreeCtrl::PSS_FormTemplateTreeCtrl() :
    PSS_TemplateTreeCtrl()
{}
//---------------------------------------------------------------------------
PSS_FormTemplateTreeCtrl::~PSS_FormTemplateTreeCtrl()
{}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_FormTemplateTreeCtrl::OnInitializeTemplateManager(WPARAM wParam, LPARAM lParam)
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
afx_msg LRESULT PSS_FormTemplateTreeCtrl::OnReloadTemplateManager(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (ZDTemplateManager*)lParam;

    if (m_pTemplateManager)
        ReInitialize( m_pTemplateManager, m_IncludeFiles );

    return 1;
}
//---------------------------------------------------------------------------
