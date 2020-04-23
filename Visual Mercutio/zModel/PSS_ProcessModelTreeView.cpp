/****************************************************************************
 * ==> PSS_ProcessModelTreeView --------------------------------------------*
 ****************************************************************************
 * Description : Provides a process model tree view                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessModelTreeView.h"

// processsoft
#include "zBaseLib\PSS_DropView.h"
#include "zBaseLib\PSS_TreeCtrl.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"
#include "PSS_ProcessGraphPage.h"
#include "PSS_ModelObserverMsg.h"

// resources
#ifdef _DEBUG
    #include "zFormsRes\zFormsRes.h"
#endif

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_ProcessModelTreeView, PSS_TreeView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessModelTreeView, PSS_TreeView)
    //{{AFX_MSG_MAP(PSS_ProcessModelTreeView)
    ON_WM_LBUTTONDBLCLK()
    ON_WM_RBUTTONDBLCLK()
    ON_WM_RBUTTONUP()
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_MBRS_EDIT_NAME, OnModelBrowserEditName)
    ON_COMMAND(ID_MBRS_GOIN_SYMBOL, OnModelBrowserGoInSymbol)
    ON_COMMAND(ID_MBRS_EDIT_CUT, OnModelBrowserEditCut)
    ON_COMMAND(ID_MBRS_EDIT_COPY, OnModelBrowserEditCopy)
    ON_COMMAND(ID_MBRS_EDIT_CLEAR, OnModelBrowserEditClear)
    ON_COMMAND(ID_MBRS_OD_PROPERTIES, OnModelBrowserProperties)
    ON_COMMAND(ID_MBRS_SELECT_SYMBOL, OnModelBrowserSelectSymbol)
    ON_COMMAND(ID_MBRS_BROWSE_SOURCESYMBOL, OnModelBrowserBrowseSourceSymbol)
    ON_COMMAND(ID_MBRS_INSERT_MODELPAGE, OnInsertModelPage)
    ON_COMMAND(ID_MBRS_RENAME_MODELPAGE, OnRenameModelPage)
    ON_COMMAND(ID_MBRS_DELETE_MODELPAGE, OnDeleteModelPage)
    ON_COMMAND(ID_REFRESH, OnRefresh)
    ON_COMMAND(ID_COLLAPSE_BRANCH, OnCollapseBranch)
    ON_COMMAND(ID_EXPAND_BRANCH, OnExpandBranch)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessModelTreeView
//---------------------------------------------------------------------------
PSS_ProcessModelTreeView::PSS_ProcessModelTreeView() :
    PSS_TreeView(),
    m_pModelSet(NULL),
    m_pPopupSubMenu(NULL),
    m_EnableMenuItems(false)
{}
//---------------------------------------------------------------------------
PSS_ProcessModelTreeView::~PSS_ProcessModelTreeView()
{}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::Initialize(const CString&       modelName,
                                          PSS_ModelSet*        pModelSet,
                                          UINT                 imageResID,
                                          PSS_RuntimeClassSet* pSet,
                                          bool                 enableMenuItems)
{
    m_pModelSet       = pModelSet;
    m_EnableMenuItems = enableMenuItems;

    // enable drag and drop
    ((PSS_TreeCtrl*)&GetTreeCtrl())->DisableDragDrop(false);

    // initialize the worker class
    m_ModelTree.Initialize((PSS_TreeCtrl*)&GetTreeCtrl(), modelName, m_pModelSet, imageResID, pSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::Refresh()
{
    m_ModelTree.Refresh();
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::Empty()
{
    m_ModelTree.Empty();
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::AddModel(PSS_ProcessGraphModelMdl* pModel)
{
    m_ModelTree.AddModel(pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::RemoveModel(PSS_ProcessGraphModelMdl* pModel)
{
    m_ModelTree.RemoveModel(pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::AddModelSet(PSS_ModelSet* pModelSet)
{
    m_ModelTree.AddModelSet(pModelSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::RemoveModelSet(PSS_ModelSet* pModelSet)
{
    m_ModelTree.RemoveModelSet(pModelSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::AddSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel, bool checkUnique)
{
    m_ModelTree.AddSymbol(pSymbol, pModel, checkUnique);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::RemoveSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    m_ModelTree.RemoveSymbol(pSymbol, pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::ModifySymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    m_ModelTree.ModifySymbol(pSymbol, pModel);
}
//---------------------------------------------------------------------------
int PSS_ProcessModelTreeView::HasContextMenu(CWnd* pWnd, const CPoint& point)
{
    CPoint pt(point);
    ScreenToClient(&pt);

    UINT      flags;
    HTREEITEM hItem = ((PSS_TreeCtrl*)&GetTreeCtrl())->HitTest(pt, &flags);
    int       idMenu = -1;

    // show the right sub-menu
    if (hItem && (TVHT_ONITEM & flags))
    {
        CODSymbolComponent* pComp       = m_ModelTree.GetSymbol(hItem);
        PSS_Symbol*         pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
        PSS_LinkSymbol*     pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pSymbol || pLinkSymbol)
        {
            if (pSymbol)
                idMenu = pSymbol->GetRightSubMenu();
            else
                idMenu = pLinkSymbol->GetRightSubMenu();
        }
        else
        if (m_ModelTree.GetPage(hItem))
            idMenu = 0;
    }

    return idMenu;
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::ShowContextMenu(CWnd* pWnd, const CPoint& point)
{
    const int idMenu = HasContextMenu(pWnd, point);

    if (idMenu == -1)
        return;

    CPoint pt(point);
    ScreenToClient(&pt);

    // test the hit
    UINT      flags;
    HTREEITEM hItem = ((PSS_TreeCtrl*)&GetTreeCtrl())->HitTest(pt, &flags);

    if (hItem && (TVHT_ONITEM & flags))
    {
        ((PSS_TreeCtrl*)&GetTreeCtrl())->Select(hItem, TVGN_CARET);

        // check if local or referenced symbol
        bool                local       = true;
        CODSymbolComponent* pComp       = m_ModelTree.GetSymbol(hItem);
        PSS_Symbol*         pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
        PSS_LinkSymbol*     pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pSymbol)
            local = pSymbol->IsLocal();
        else
        if (pLinkSymbol)
            local = pLinkSymbol->IsLocal();

        CMenu* pPopup = NULL;

        if (local)
            pPopup = m_SymbolPopupMainMenu.GetSubMenu(idMenu);
        else
            pPopup = m_SymbolRefPopupMainMenu.GetSubMenu(idMenu);

        ASSERT(pPopup);
        CWnd* pWndPopupOwner = this;

        while (pWndPopupOwner->GetStyle() & WS_CHILD)
            pWndPopupOwner = pWndPopupOwner->GetParent();

        // if needed to enable all menu items
        if (m_EnableMenuItems)
        {
            UINT count = pPopup->GetMenuItemCount();

            for (UINT i = 0; i < count; ++i)
                pPopup->EnableMenuItem(i, MF_BYPOSITION | MF_ENABLED);
        }

        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                               point.x,
                               point.y,
                               m_EnableMenuItems ? this : pWndPopupOwner);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnDraw(CDC* pDC)
{}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // browse the symbol
    OnDoubleClick();
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
    PSS_TreeView::OnRButtonDblClk(nFlags, point);

    // browse the symbol
    OnDoubleClick();
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnRButtonUp(UINT nFlags, CPoint point)
{
    PSS_TreeView::OnRButtonUp(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnContextMenu(CWnd* pWnd, CPoint point)
{
    ShowContextMenu(pWnd, point);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnModelBrowserEditName()
{
    m_ModelTree.DoSelectSymbol();

    CWnd* pWnd = ::AfxGetMainWnd();

    if (pWnd)
        pWnd->SendMessage(WM_COMMAND, ID_EDIT_NAME);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnModelBrowserGoInSymbol()
{
    m_ModelTree.DoSelectSymbol();

    CWnd* pWnd = ::AfxGetMainWnd();

    if (pWnd)
        pWnd->SendMessage(WM_COMMAND, ID_GOIN_SYMBOL);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnModelBrowserEditCut()
{
    m_ModelTree.DoSelectSymbol();

    CWnd* pWnd = ::AfxGetMainWnd();

    if (pWnd)
        pWnd->SendMessage(WM_COMMAND, ID_EDIT_CUT);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnModelBrowserEditCopy()
{
    m_ModelTree.DoSelectSymbol();

    CWnd* pWnd = ::AfxGetMainWnd();

    if (pWnd)
        pWnd->SendMessage(WM_COMMAND, ID_EDIT_COPY);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnModelBrowserEditClear()
{
    m_ModelTree.DoSelectSymbol();

    CWnd* pWnd = ::AfxGetMainWnd();

    if (pWnd)
        pWnd->SendMessage(WM_COMMAND, ID_EDIT_CLEAR);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnModelBrowserProperties()
{
    m_ModelTree.DoSelectSymbol();

    CWnd* pWnd = ::AfxGetMainWnd();

    if (pWnd)
        pWnd->SendMessage(WM_COMMAND, ID_OD_PROPERTIES);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnModelBrowserBrowseSourceSymbol()
{
    m_ModelTree.DoSelectSymbol();

    CWnd* pWnd = ::AfxGetMainWnd();

    if (pWnd)
        pWnd->SendMessage(WM_COMMAND, ID_BROWSE_SOURCESYMBOL);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnModelBrowserSelectSymbol()
{
    m_ModelTree.DoSelectSymbol();
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnInsertModelPage()
{
    CWnd* pWnd = ::AfxGetMainWnd();

    if (pWnd)
        pWnd->SendMessage(WM_COMMAND, ID_INSERT_MODELPAGE);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnRenameModelPage()
{
    m_ModelTree.DoSelectSymbol();

    CWnd* pWnd = ::AfxGetMainWnd();

    if (pWnd)
        pWnd->SendMessage(WM_COMMAND, ID_RENAME_CURRENTMODELPAGE);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnDeleteModelPage()
{
    m_ModelTree.DoSelectSymbol();

    CWnd* pWnd = ::AfxGetMainWnd();

    if (pWnd)
        pWnd->SendMessage(WM_COMMAND, ID_DELETE_CURRENTMODELPAGE);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnRefresh()
{
    m_ModelTree.Refresh();
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnCollapseBranch()
{
    CollapseBranch(((PSS_TreeCtrl*)&GetTreeCtrl())->GetSelectedItem(), TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnExpandBranch()
{
    ExpandBranch(((PSS_TreeCtrl*)&GetTreeCtrl())->GetSelectedItem(), TRUE);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessModelTreeView::AssertValid() const
    {
        PSS_TreeView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessModelTreeView::Dump(CDumpContext& dc) const
    {
        PSS_TreeView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_ProcessModelTreeView::OnDoubleClick()
{
    m_ModelTree.OnDoubleClick();
}
//---------------------------------------------------------------------------
