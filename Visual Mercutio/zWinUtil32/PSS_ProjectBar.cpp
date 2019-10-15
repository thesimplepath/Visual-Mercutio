/****************************************************************************
 * ==> PSS_ProjectBar ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a project bar                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProjectBar.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProjectBar, CCJControlBar)
    //{{AFX_MSG_MAP(PSS_ProjectBar)
    ON_WM_CREATE()
    ON_MESSAGE(UM_DOCUMENTHASBEENSELECTED, OnDocumentHasBeenSelected)
    ON_NOTIFY(TVN_SELCHANGED, IDC_PROJECTWINDOWLIST_CTRL, OnSelChanged)
    ON_NOTIFY(NM_DBLCLK, IDC_PROJECTWINDOWLIST_CTRL, OnDblClick)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProjectBar
//---------------------------------------------------------------------------
PSS_ProjectBar::PSS_ProjectBar(BOOL visibleOnly) :
    m_VisibleOnly(visibleOnly)
{}
//---------------------------------------------------------------------------
PSS_ProjectBar::~PSS_ProjectBar()
{}
//---------------------------------------------------------------------------
void PSS_ProjectBar::Initialize(BOOL visibleOnly)
{
    m_VisibleOnly = visibleOnly;
}
//---------------------------------------------------------------------------
int PSS_ProjectBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CCJControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_ProjectWindowCtrl.Create(WS_TABSTOP | WS_VISIBLE | WS_CHILD | TVS_DISABLEDRAGDROP,
                                    CRect(0, 0, 0, 0),
                                    this,
                                    IDC_PROJECTWINDOWLIST_CTRL))
    {
        TRACE0("Failed to create project window tree control\n");
        return -1;
    }

    m_ProjectWindowCtrl.ModifyStyleEx(0, WS_EX_STATICEDGE);
    SetChild(&m_ProjectWindowCtrl);

    return 0;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProjectBar::OnDocumentHasBeenSelected(WPARAM wParam, LPARAM lParam)
{
    PSS_Document* pDoc = (PSS_Document*)lParam;

    if (pDoc)
        m_ProjectWindowCtrl.Initialize(pDoc, m_VisibleOnly);
    else
        m_ProjectWindowCtrl.Empty();

    return 1;
}
//---------------------------------------------------------------------------
void PSS_ProjectBar::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // something selected?
    if (!m_ProjectWindowCtrl.GetSelectedDocumentTitle().IsEmpty())
        AfxGetMainWnd()->SendMessageToDescendants(UM_SETDEFAULTFILE,
                                                  1,
                                                  LPARAM((const char*)m_ProjectWindowCtrl.GetSelectedDocumentTitle()));

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_ProjectBar::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (!AfxGetMainWnd())
        return;

    // something selected?
    if (!m_ProjectWindowCtrl.GetSelectedDocumentTitle().IsEmpty())
        AfxGetMainWnd()->SendMessageToDescendants(UM_SETDEFAULTFILE_OPEN,
                                                  1,
                                                  LPARAM((const char*)m_ProjectWindowCtrl.GetSelectedDocumentTitle()));

    *pResult = 0;
}
//---------------------------------------------------------------------------
