/****************************************************************************
 * ==> PSS_TemplateView ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template view                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_TemplateView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_TemplateView, PSS_TreeView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_TemplateView, PSS_TreeView)
    //{{AFX_MSG_MAP(PSS_TemplateView)
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
// PSS_TemplateView
//---------------------------------------------------------------------------
PSS_TemplateView::PSS_TemplateView() :
    PSS_TreeView(),
    m_pTemplateManager(NULL),
    m_IncludeFiles(TRUE)
{}
//---------------------------------------------------------------------------
PSS_TemplateView::~PSS_TemplateView()
{}
//---------------------------------------------------------------------------
void PSS_TemplateView::Initialize(PSS_TemplateManager* pTemplateManager, BOOL includeFiles)
{
    m_pTemplateManager = pTemplateManager;
    m_IncludeFiles     = includeFiles;

    // enable drag and drop
    ((PSS_TreeCtrl*)&GetTreeCtrl())->DisableDragDrop(false);

    m_TemplateTree.Initialize((PSS_TreeCtrl*)&GetTreeCtrl(), m_pTemplateManager, m_IncludeFiles);
}
//---------------------------------------------------------------------------
void PSS_TemplateView::ReInitialize(PSS_TemplateManager* pTemplateManager, BOOL includeFiles)
{
    m_pTemplateManager = pTemplateManager;
    m_IncludeFiles     = includeFiles;
    m_TemplateTree.ReInitialize(m_pTemplateManager, m_IncludeFiles);
}
//---------------------------------------------------------------------------
void PSS_TemplateView::Refresh()
{
    m_TemplateTree.Refresh();
}
//---------------------------------------------------------------------------
CString PSS_TemplateView::GetSelectedItemName()
{
    return m_TemplateTree.GetSelectedItemName();
}
//---------------------------------------------------------------------------
PSS_TemplateDir* PSS_TemplateView::GetSelectedItemFolder()
{
    return m_TemplateTree.GetSelectedItemFolder();
}
//---------------------------------------------------------------------------
PSS_TemplateFile* PSS_TemplateView::GetSelectedItemFile()
{
    return m_TemplateTree.GetSelectedItemFile();
}
//---------------------------------------------------------------------------
BOOL PSS_TemplateView::SelectItemName(const CString& name)
{
    return m_TemplateTree.SelectItemName(name);
}
//---------------------------------------------------------------------------
void PSS_TemplateView::OnSelChangedEvent()
{}
//---------------------------------------------------------------------------
void PSS_TemplateView::OnClickEvent()
{}
//---------------------------------------------------------------------------
void PSS_TemplateView::OnDblClickEvent()
{}
//---------------------------------------------------------------------------
void PSS_TemplateView::OnRightClickEvent()
{}
//---------------------------------------------------------------------------
void PSS_TemplateView::OnRightDblClickEvent()
{}
//---------------------------------------------------------------------------
void PSS_TemplateView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();

    // todo -cFeature -oJean: add draw code here
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_TemplateView::OnInitializeTemplateManager(WPARAM wParam, LPARAM lParam)
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
afx_msg LRESULT PSS_TemplateView::OnReloadTemplateManager(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (PSS_TemplateManager*)lParam;

    if (m_pTemplateManager)
        ReInitialize(m_pTemplateManager, m_IncludeFiles);

    return 1;
}
//---------------------------------------------------------------------------
void PSS_TemplateView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the virtual method
    OnSelChangedEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_TemplateView::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the virtual method
    OnClickEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_TemplateView::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // something selected?
    if (GetSelectedItemFile())
        AfxGetMainWnd()->SendMessage(UM_FORM_OPEN, 1, LPARAM((const char*)GetSelectedItemFile()->GetFileName()));

    // call the virtual method
    OnDblClickEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_TemplateView::OnRightClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the virtual method
    OnRightClickEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_TemplateView::OnRightDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // call the virtual method
    OnRightDblClickEvent();

    *pResult = 0;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_TemplateView::AssertValid() const
    {
        ZITreeView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_TemplateView::Dump(CDumpContext& dc) const
    {
        ZITreeView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
