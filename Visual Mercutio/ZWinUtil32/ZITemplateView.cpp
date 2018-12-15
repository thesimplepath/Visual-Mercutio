// ZITemplateView.cpp : implementation file
//

#include "stdafx.h"
#include "ZITemplateView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZITemplateView

IMPLEMENT_DYNCREATE(ZITemplateView, ZITreeView)

ZITemplateView::ZITemplateView()
    :    m_pTemplateManager(NULL),
        m_IncludeFiles(TRUE)
{
}

ZITemplateView::~ZITemplateView()
{
}


void ZITemplateView::Initialize (ZDTemplateManager* pTemplateManager, BOOL IncludeFiles)
{
    m_pTemplateManager = pTemplateManager;
    m_IncludeFiles = IncludeFiles;
    // Enable drag and drop
    ((ZITreeCtrl*)&GetTreeCtrl())->DisableDragDrop( false );

    m_TemplateTree.Initialize( (ZITreeCtrl*)&GetTreeCtrl(), m_pTemplateManager, m_IncludeFiles );
}

void ZITemplateView::ReInitialize (ZDTemplateManager* pTemplateManager, BOOL IncludeFiles)
{
    m_pTemplateManager = pTemplateManager;
    m_IncludeFiles = IncludeFiles;
    m_TemplateTree.ReInitialize( m_pTemplateManager, m_IncludeFiles );
}

void ZITemplateView::Refresh ()
{
    m_TemplateTree.Refresh();
}

CString ZITemplateView::GetNameSelectedItem ()
{
    return m_TemplateTree.GetNameSelectedItem();
}

ZDTemplateDir* ZITemplateView::GetSelectedFolderItem ()
{
    return m_TemplateTree.GetSelectedFolderItem();
}

ZDTemplateFile* ZITemplateView::GetSelectedFileItem ()
{
    return m_TemplateTree.GetSelectedFileItem();
}

BOOL ZITemplateView::SelectItemName (const CString Name)
{
    return m_TemplateTree.SelectItemName(Name);
}

BEGIN_MESSAGE_MAP(ZITemplateView, ZITreeView)
    //{{AFX_MSG_MAP(ZITemplateView)
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

/////////////////////////////////////////////////////////////////////////////
// ZITemplateView drawing

void ZITemplateView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
    // TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// ZITemplateView diagnostics

#ifdef _DEBUG
void ZITemplateView::AssertValid() const
{
    ZITreeView::AssertValid();
}

void ZITemplateView::Dump(CDumpContext& dc) const
{
    ZITreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZITemplateView message handlers



afx_msg LRESULT ZITemplateView::OnInitializeTemplateManager( WPARAM wParam, LPARAM lParam )
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (ZDTemplateManager*)lParam;
    m_IncludeFiles = (BOOL)wParam;

    if (m_pTemplateManager)
    {
        ZITemplateView::Initialize( m_pTemplateManager, m_IncludeFiles );
    }
    else
    {
//        m_TemplateTree.Empty();
    }
    return 1;
}


afx_msg LRESULT ZITemplateView::OnReloadTemplateManager( WPARAM wParam, LPARAM lParam )
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pTemplateManager = (ZDTemplateManager*)lParam;

    if (m_pTemplateManager)
    {
        ZITemplateView::ReInitialize( m_pTemplateManager, m_IncludeFiles );
    }
    else
    {
//        m_TemplateTree.Empty();
    }
    return 1;
}


void ZITemplateView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // Call the virtual method
    OnSelChangedEvent();

    // If something selected.
//    if (!m_ProjectTree.GetSelectedDocumentTitle().IsEmpty())
//        AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE, 
//                                                   1, // Change the file
//                                                   (LPARAM)(const char*)m_ProjectTree.GetSelectedDocumentTitle() );

    *pResult = 0;
}


void ZITemplateView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // Call the virtual method
    OnClickEvent();

    *pResult = 0;
}

void ZITemplateView::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // If something selected.
    if (GetSelectedFileItem())
        AfxGetMainWnd()->SendMessage( UM_FORM_OPEN, 
                                                   1, // Change the file
                                                   (LPARAM)(const char*)GetSelectedFileItem ()->GetFilename() );

    // Call the virtual method
    OnDblClickEvent();

    *pResult = 0;
}


void ZITemplateView::OnRightClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // Call the virtual method
    OnRightClickEvent();

    *pResult = 0;
}

void ZITemplateView::OnRightDblClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // Call the virtual method
    OnRightDblClickEvent();

    *pResult = 0;
}

