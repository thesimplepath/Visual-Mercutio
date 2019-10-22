/****************************************************************************
 * ==> PSS_FieldView -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a field view                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FieldView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_FieldView, ZITreeView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FieldView, ZITreeView)
    //{{AFX_MSG_MAP(PSS_FieldView)
    ON_MESSAGE(UM_DOCUMENTHASBEENSELECTED, OnDocumentHasBeenSelected)
    ON_MESSAGE(UM_INITIALIZE_FIELDREPOSITORY, OnInitializeFieldRepository)
    ON_MESSAGE(UM_RELOAD_FIELDLIST, OnReloadFieldList)
    ON_MESSAGE(UM_FIELD_ADDED, OnFieldAdded)
    ON_MESSAGE(UM_FIELD_REMOVED, OnFieldRemoved)
    ON_MESSAGE(UM_FIELD_RENAMED, OnFieldRenamed)
    ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblClick)
    ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FieldView
//---------------------------------------------------------------------------
PSS_FieldView::PSS_FieldView() :
    ZITreeView(),
    m_pDoc(NULL),
    m_pFieldRepository(NULL)
{}
//---------------------------------------------------------------------------
PSS_FieldView::~PSS_FieldView()
{}
//---------------------------------------------------------------------------
void PSS_FieldView::Initialize(PSS_Document* pDoc, PSS_FieldRepository* pFieldRepository)
{
    m_pDoc             = pDoc;
    m_pFieldRepository = pFieldRepository;
    m_FieldTree.Initialize((PSS_TreeCtrl*)&GetTreeCtrl(), m_pDoc, m_pFieldRepository);
}
//---------------------------------------------------------------------------
void PSS_FieldView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();

    // todo -cFeature -oJean: add draw code here
}
//---------------------------------------------------------------------------
void PSS_FieldView::PostNcDestroy()
{
    // don't call the base class which deletes the object
    // ZITreeView::PostNcDestroy();
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FieldView::AssertValid() const
    {
        ZITreeView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FieldView::Dump(CDumpContext& dc) const
    {
        ZITreeView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
int PSS_FieldView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CCtrlView::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_FieldView::OnInitializeFieldRepository(WPARAM wParam, LPARAM lParam)
{

    m_pFieldRepository = (PSS_FieldRepository*)lParam;

    if (!m_pFieldRepository)
        m_FieldTree.Empty();

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_FieldView::OnDocumentHasBeenSelected(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pDoc = (PSS_Document*)lParam;

    if (m_pDoc)
        m_FieldTree.Initialize((PSS_TreeCtrl*)&GetTreeCtrl(), m_pDoc, m_pFieldRepository);
    else
        m_FieldTree.Empty();

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_FieldView::OnReloadFieldList(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 0;

    m_FieldTree.Refresh();
    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_FieldView::OnFieldAdded(WPARAM wParam, LPARAM lParam)
{
    return 0;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_FieldView::OnFieldRemoved(WPARAM wParam, LPARAM lParam)
{
    return 0;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_FieldView::OnFieldRenamed(WPARAM wParam, LPARAM lParam)
{
    return 0;
}
//---------------------------------------------------------------------------
void PSS_FieldView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_FieldView::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    *pResult = 0;
}
//---------------------------------------------------------------------------
