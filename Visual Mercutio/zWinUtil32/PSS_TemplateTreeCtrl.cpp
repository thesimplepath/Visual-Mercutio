/****************************************************************************
 * ==> PSS_TemplateTreeCtrl ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template tree control, which is automatically   *
 *               filled with a template manager object                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_TemplateTreeCtrl.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_TemplateTreeCtrl, ZITreeCtrl)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_TemplateTreeCtrl, ZITreeCtrl)
    //{{AFX_MSG_MAP(PSS_TemplateTreeCtrl)
    ON_MESSAGE(UM_INITIALIZE_TEMPLATEMANAGER, OnInitializeTemplateManager)
    ON_MESSAGE(UM_INITIALIZE_PROCESSTEMPLATEMANAGER, OnInitializeTemplateManager)
    ON_MESSAGE(UM_RELOAD_TEMPLATEMANAGER, OnReloadTemplateManager)
    ON_MESSAGE(UM_RELOAD_PROCESSTEMPLATEMANAGER, OnReloadTemplateManager)
    ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
    ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblClick)
    ON_NOTIFY_REFLECT(NM_RCLICK, OnRightClick)
    ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRightDblClick)
    ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_TemplateTreeCtrl
//---------------------------------------------------------------------------
PSS_TemplateTreeCtrl::PSS_TemplateTreeCtrl(ZDTemplateManager* pTemplateManager, BOOL includeFiles) :
    m_pTemplateManager(pTemplateManager),
    m_IncludeFiles(includeFiles)
{}
//---------------------------------------------------------------------------
PSS_TemplateTreeCtrl::PSS_TemplateTreeCtrl(const PSS_TemplateTreeCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_TemplateTreeCtrl::~PSS_TemplateTreeCtrl()
{}
//---------------------------------------------------------------------------
const PSS_TemplateTreeCtrl& PSS_TemplateTreeCtrl::operator = (const PSS_TemplateTreeCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::Initialize(ZDTemplateManager* pTemplateManager, BOOL includeFiles)
{
    m_pTemplateManager = pTemplateManager;
    m_IncludeFiles     = includeFiles;

    m_TemplateTree.Initialize(this, m_pTemplateManager, m_IncludeFiles);
}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::ReInitialize(ZDTemplateManager* pTemplateManager, BOOL includeFiles)
{
    m_pTemplateManager = pTemplateManager;
    m_IncludeFiles     = includeFiles;

    m_TemplateTree.ReInitialize(m_pTemplateManager, m_IncludeFiles);
}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::Refresh()
{
    m_TemplateTree.Refresh();
}
//---------------------------------------------------------------------------
CString PSS_TemplateTreeCtrl::GetNameSelectedItem()
{
    return m_TemplateTree.GetSelectedItemName();
}
//---------------------------------------------------------------------------
ZDTemplateDir* PSS_TemplateTreeCtrl::GetSelectedFolderItem()
{
    return m_TemplateTree.GetSelectedItemFolder();
}
//---------------------------------------------------------------------------
ZDTemplateFile* PSS_TemplateTreeCtrl::GetSelectedFileItem()
{
    return m_TemplateTree.GetSelectedItemFile();
}
//---------------------------------------------------------------------------
BOOL PSS_TemplateTreeCtrl::SelectItemName(const CString& name)
{
    return m_TemplateTree.SelectItemName(name);
}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::OnSelChangedEvent()
{}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::OnClickEvent()
{}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::OnDblClickEvent()
{}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::OnRightClickEvent()
{}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::OnRightDblClickEvent()
{}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_TemplateTreeCtrl::OnInitializeTemplateManager(WPARAM wParam, LPARAM lParam)
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
afx_msg LRESULT PSS_TemplateTreeCtrl::OnReloadTemplateManager(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (ZDTemplateManager*)lParam;

    if (m_pTemplateManager)
        ReInitialize(m_pTemplateManager, m_IncludeFiles);

    return 1;
}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the virtual method
    OnSelChangedEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the virtual method
    OnClickEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // something selected?
    if (GetSelectedFileItem())
        AfxGetMainWnd()->SendMessage(UM_FORM_OPEN, 1, (LPARAM)(const char*)GetSelectedFileItem()->GetFilename());

    // call the virtual method
    OnDblClickEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::OnRightClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the virtual method
    OnRightClickEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_TemplateTreeCtrl::OnRightDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the virtual method
    OnRightDblClickEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
