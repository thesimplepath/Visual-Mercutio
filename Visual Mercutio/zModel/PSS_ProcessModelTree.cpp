/****************************************************************************
 * ==> PSS_ProcessModelTree ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a process model tree                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessModelTree.h"

// processsoft
#include "zBaseLib\PSS_DropView.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"
#include "PSS_ProcessGraphPage.h"
#include "PSS_ModelObserverMsg.h"

// resources
#include "zModelRes.h"
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
IMPLEMENT_DYNCREATE(PSS_ProcessModelTree, PSS_TreeCtrl)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessModelTree, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(PSS_ProcessModelTree)
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
// PSS_ProcessModelTree
//---------------------------------------------------------------------------
PSS_ProcessModelTree::PSS_ProcessModelTree() :
    PSS_TreeCtrl(),
    m_pModelSet(NULL),
    m_pPopupSubMenu(NULL),
    m_EnableMenuItems(false)
{
    // load the right main menu for components
    m_SymbolPopupMainMenu.LoadMenu(IDR_BASICSYMBOL_POPUP);
    m_SymbolRefPopupMainMenu.LoadMenu(IDR_BASICSYMBOL_REF_POPUP);
}
//---------------------------------------------------------------------------
PSS_ProcessModelTree::~PSS_ProcessModelTree()
{}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::Initialize(const CString&       modelName,
                                      PSS_ModelSet*        pModelSet,
                                      UINT                 imageResID,
                                      PSS_RuntimeClassSet* pSet,
                                      bool                 enableMenuItems)
{
    m_pModelSet       = pModelSet;
    m_EnableMenuItems = enableMenuItems;

    // enable drag and drop
    DisableDragDrop(false);

    // initialize the worker class
    m_ModelTree.Initialize(this, modelName, m_pModelSet, imageResID, pSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::Refresh()
{
    m_ModelTree.Refresh();
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::Empty()
{
    m_ModelTree.Empty();
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::AddModel(PSS_ProcessGraphModelMdl* pModel)
{
    m_ModelTree.AddModel(pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::RemoveModel(PSS_ProcessGraphModelMdl* pModel)
{
    m_ModelTree.RemoveModel(pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::AddModelSet(PSS_ModelSet* pModelSet)
{
    m_ModelTree.AddModelSet(pModelSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::RemoveModelSet(PSS_ModelSet* pModelSet)
{
    m_ModelTree.RemoveModelSet(pModelSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::AddSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel, bool checkUnique)
{
    m_ModelTree.AddSymbol(pSymbol, pModel, checkUnique);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::RemoveSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    m_ModelTree.RemoveSymbol(pSymbol, pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::ModifySymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    m_ModelTree.ModifySymbol(pSymbol, pModel);
}
//---------------------------------------------------------------------------
int PSS_ProcessModelTree::HasContextMenu(CWnd* pWnd, const CPoint& point)
{

    CPoint pt(point);
    ScreenToClient(&pt);

    UINT      flags;
    HTREEITEM hItem  =  HitTest(pt, &flags);
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
void PSS_ProcessModelTree::ShowContextMenu(CWnd* pWnd, const CPoint& point)
{
    const int idMenu = HasContextMenu(pWnd, point);

    if (idMenu == -1)
        return;

    CPoint pt(point);
    ScreenToClient(&pt);

    // test the hit
    UINT      flags;
    HTREEITEM hItem = HitTest(pt, &flags);

    if (hItem && (TVHT_ONITEM & flags))
    {
        Select(hItem, TVGN_CARET);

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
void PSS_ProcessModelTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // browse the symbol
    OnDoubleClick();
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnRButtonDblClk(UINT nFlags, CPoint point)
{
    PSS_TreeCtrl::OnRButtonDblClk(nFlags, point);

    // browse the symbol
    OnDoubleClick();
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnRButtonUp(UINT nFlags, CPoint point)
{
    PSS_TreeCtrl::OnRButtonUp(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnContextMenu(CWnd* pWnd, CPoint point)
{
    ShowContextMenu(pWnd, point);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnModelBrowserEditName()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_EDIT_NAME);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnModelBrowserGoInSymbol()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_GOIN_SYMBOL);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnModelBrowserEditCut()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_EDIT_CUT);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnModelBrowserEditCopy()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_EDIT_COPY);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnModelBrowserEditClear()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_EDIT_CLEAR);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnModelBrowserProperties()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_OD_PROPERTIES);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnModelBrowserBrowseSourceSymbol()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_BROWSE_SOURCESYMBOL);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnModelBrowserSelectSymbol()
{
    m_ModelTree.DoSelectSymbol();
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnInsertModelPage()
{
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_INSERT_MODELPAGE);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnRenameModelPage()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_RENAME_CURRENTMODELPAGE);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnDeleteModelPage()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_DELETE_CURRENTMODELPAGE);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnRefresh()
{
    m_ModelTree.Refresh();
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnCollapseBranch()
{
    CollapseBranch(GetSelectedItem(), TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnExpandBranch()
{
    ExpandBranch(GetSelectedItem(), TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessModelTree::OnDoubleClick()
{
    m_ModelTree.OnDoubleClick();
}
//---------------------------------------------------------------------------
