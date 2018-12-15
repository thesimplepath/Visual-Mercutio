// ZIFieldView.cpp : implementation file
//

#include "stdafx.h"
#include "ZIFieldView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIFieldView

IMPLEMENT_DYNCREATE(ZIFieldView, ZITreeView)

ZIFieldView::ZIFieldView()
 : m_pDoc(NULL), m_pFieldRepository(NULL)
{
}

ZIFieldView::~ZIFieldView()
{
}

void ZIFieldView::Initialize( ZDDocument* pDoc, ZBFieldRepository* pFieldRepository )
{
    m_pDoc = pDoc;
    m_pFieldRepository = pFieldRepository;
    m_FieldTree.Initialize( (ZITreeCtrl*)&GetTreeCtrl(), m_pDoc, m_pFieldRepository );
}




BEGIN_MESSAGE_MAP(ZIFieldView, ZITreeView)
    //{{AFX_MSG_MAP(ZIFieldView)
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

/////////////////////////////////////////////////////////////////////////////
// ZIFieldView drawing

void ZIFieldView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
    // TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// ZIFieldView diagnostics

#ifdef _DEBUG
void ZIFieldView::AssertValid() const
{
    ZITreeView::AssertValid();
}

void ZIFieldView::Dump(CDumpContext& dc) const
{
    ZITreeView::Dump(dc);
}
#endif //_DEBUG





/////////////////////////////////////////////////////////////////////////////
// ZIFieldView message handlers



afx_msg LRESULT ZIFieldView::OnDocumentHasBeenSelected( WPARAM wParam, LPARAM lParam )
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    m_pDoc = (ZDDocument*)lParam;

    if (m_pDoc)
    {
        m_FieldTree.Initialize( (ZITreeCtrl*)&GetTreeCtrl(), m_pDoc, m_pFieldRepository );
    }
    else
    {
        m_FieldTree.Empty();
    }
    return 1;
}


afx_msg LRESULT ZIFieldView::OnInitializeFieldRepository( WPARAM wParam, LPARAM lParam )
{

    m_pFieldRepository = (ZBFieldRepository*)lParam;

    if (m_pFieldRepository)
    {
    }
    else
    {
        m_FieldTree.Empty();
    }
    return 1;
}


afx_msg LRESULT ZIFieldView::OnReloadFieldList( WPARAM wParam, LPARAM lParam )
{
    if (!::IsWindow(GetSafeHwnd()))
        return 0;

    m_FieldTree.Refresh();
    return 1;
}

afx_msg LRESULT ZIFieldView::OnFieldAdded( WPARAM wParam, LPARAM lParam )
{
    return 0;
}

afx_msg LRESULT ZIFieldView::OnFieldRemoved( WPARAM wParam, LPARAM lParam )
{
    return 0;
}
afx_msg LRESULT ZIFieldView::OnFieldRenamed( WPARAM wParam, LPARAM lParam )
{
    return 0;
}

void ZIFieldView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // If something selected.
//    if (!m_FieldTree.GetSelectedDocumentTitle().IsEmpty())
//        AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE, 
//                                                   1, // Change the file
//                                                   (LPARAM)(const char*)m_FieldTree.GetSelectedDocumentTitle() );

    *pResult = 0;
}

void ZIFieldView::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // If something selected.
//    if (!m_FieldTree.GetSelectedDocumentTitle().IsEmpty())
//        AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE_OPEN, 
//                                                   1, // Change the file
//                                                   (LPARAM)(const char*)m_FieldTree.GetSelectedDocumentTitle() );

    *pResult = 0;
}

int ZIFieldView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CCtrlView::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    return 0;
}

void ZIFieldView::PostNcDestroy() 
{
    // TODO: Don't call the base class which deletes the object
    
//    ZITreeView::PostNcDestroy();
}
