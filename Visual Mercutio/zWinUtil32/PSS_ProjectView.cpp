/****************************************************************************
 * ==> PSS_ProjectView -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a project view                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProjectView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_ProjectView, CTreeView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProjectView, CTreeView)
    //{{AFX_MSG_MAP(PSS_ProjectView)
    ON_MESSAGE(UM_DOCUMENTHASBEENSELECTED, OnDocumentHasBeenSelected)
    ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblClick)
    ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProjectView
//---------------------------------------------------------------------------
PSS_ProjectView::PSS_ProjectView() :
    m_VisibleOnly(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ProjectView::~PSS_ProjectView()
{}
//---------------------------------------------------------------------------
void PSS_ProjectView::Initialize(BOOL visibleOnly)
{
    m_VisibleOnly = visibleOnly;
    m_ProjectTree.Initialize((ZITreeCtrl*)&GetTreeCtrl(), NULL, m_VisibleOnly);
}
//---------------------------------------------------------------------------
void PSS_ProjectView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();

    // todo -cFeature -oJean: add draw code here
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProjectView::AssertValid() const
    {
        CTreeView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProjectView::Dump(CDumpContext& dc) const
    {
        CTreeView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
int PSS_ProjectView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CCtrlView::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}
//---------------------------------------------------------------------------
void PSS_ProjectView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // something selected?
    if (!m_ProjectTree.GetSelectedDocumentTitle().IsEmpty())
        AfxGetMainWnd()->SendMessageToDescendants(UM_SETDEFAULTFILE,
                                                  1,
                                                  LPARAM((const char*)m_ProjectTree.GetSelectedDocumentTitle()));

    *pResult = 0;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProjectView::OnDocumentHasBeenSelected(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    ZDDocument* pDoc = (ZDDocument*)lParam;

    if (pDoc)
        m_ProjectTree.Initialize((ZITreeCtrl*)&GetTreeCtrl(), pDoc, m_VisibleOnly);
    else
        m_ProjectTree.Empty();

    return 1;
}
//---------------------------------------------------------------------------
void PSS_ProjectView::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // something selected?
    if (!m_ProjectTree.GetSelectedDocumentTitle().IsEmpty())
        AfxGetMainWnd()->SendMessageToDescendants(UM_SETDEFAULTFILE_OPEN,
                                                  1,
                                                  LPARAM((const char*)m_ProjectTree.GetSelectedDocumentTitle()));

    *pResult = 0;
}
//---------------------------------------------------------------------------
