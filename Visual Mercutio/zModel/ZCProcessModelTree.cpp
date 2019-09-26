// ZCProcessModelTree.cpp : implementation file

#include "stdafx.h"
#include "ZCProcessModelTree.h"

#include "zBaseLib\PSS_DropView.h"
#include "ZBSymbol.h"
#include "ZBLinkSymbol.h"

#include "ZDProcessGraphPage.h"
#include "ZBModelObserverMsg.h"

#ifdef _DEBUG
#include "zFormsRes\zFormsRes.h"
#endif

#include "zModelRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 14 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZCProcessModelTree

IMPLEMENT_DYNCREATE( ZCProcessModelTree, ZITreeCtrl )

BEGIN_MESSAGE_MAP( ZCProcessModelTree, ZITreeCtrl )
    //{{AFX_MSG_MAP(ZCProcessModelTree)
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

ZCProcessModelTree::ZCProcessModelTree()
    : m_pModelSet        ( NULL ),
      m_pPopupSubMenu    ( NULL ),
      m_EnableMenuItems    ( false )
{
    // Load the right main menu for components
    m_SymbolPopupMainMenu.LoadMenu( IDR_BASICSYMBOL_POPUP );
    m_SymbolRefPopupMainMenu.LoadMenu( IDR_BASICSYMBOL_REF_POPUP );
}

ZCProcessModelTree::~ZCProcessModelTree()
{
}

void ZCProcessModelTree::Initialize( const CString        ModelName,
                                     ZBModelSet*        pModelSet,
                                     UINT                nIDImageRes,
                                     ZBRuntimeClassSet*    pSet            /*= NULL*/,
                                     bool                EnableMenuItems    /*= true*/ )
{
    m_pModelSet            = pModelSet;
    m_EnableMenuItems    = EnableMenuItems;

    // Enable drag and drop
    DisableDragDrop( false );

    // Initialize the worker class
    m_ModelTree.Initialize( this, ModelName, m_pModelSet, nIDImageRes, pSet );
}

void ZCProcessModelTree::Refresh()
{
    m_ModelTree.Refresh();
}

void ZCProcessModelTree::Empty()
{
    m_ModelTree.Empty();
}

void ZCProcessModelTree::AddModel( ZDProcessGraphModelMdl* pModel )
{
    m_ModelTree.AddModel( pModel );
}

void ZCProcessModelTree::RemoveModel( ZDProcessGraphModelMdl* pModel )
{
    m_ModelTree.RemoveModel( pModel );
}

void ZCProcessModelTree::AddModelSet( ZBModelSet* pModelSet )
{
    m_ModelTree.AddModelSet( pModelSet );
}

void ZCProcessModelTree::RemoveModelSet( ZBModelSet* pModelSet )
{
    m_ModelTree.RemoveModelSet( pModelSet );
}

void ZCProcessModelTree::AddSymbol( CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel, bool CheckUnique )
{
    m_ModelTree.AddSymbol( pSymbol, pModel, CheckUnique );
}

void ZCProcessModelTree::RemoveSymbol( CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel )
{
    m_ModelTree.RemoveSymbol( pSymbol, pModel );
}

void ZCProcessModelTree::ModifySymbol( CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel )
{
    m_ModelTree.ModifySymbol( pSymbol, pModel );
}

void ZCProcessModelTree::OnDoubleClick()
{
    m_ModelTree.OnDoubleClick();
}

int ZCProcessModelTree::HasContextMenu( CWnd* pWnd, CPoint point )
{
    // Now display the right sub-menu
    int IdMenu = -1;
    UINT Flags;
    CPoint pt( point );
    ScreenToClient( &pt );

    HTREEITEM hItem = HitTest( pt, &Flags );

    if ( ( hItem != NULL ) && ( TVHT_ONITEM & Flags ) )
    {
        CODSymbolComponent* pComp = m_ModelTree.GetSymbol( hItem );

        if ( pComp && ( ISA( pComp, ZBSymbol ) || ISA( pComp, ZBLinkSymbol ) ) )
        {
            if ( ISA( pComp, ZBSymbol ) )
            {
                IdMenu = dynamic_cast<ZBSymbol*>( pComp )->GetRightSubMenu();
            }
            else if ( ISA( pComp, ZBLinkSymbol ) )
            {
                IdMenu = dynamic_cast<ZBLinkSymbol*>( pComp )->GetRightSubMenu();
            }
        }
        else if ( m_ModelTree.GetPage( hItem ) )
        {
            IdMenu = 0;
        }
    }

    return IdMenu;
}

void ZCProcessModelTree::DisplayContextMenu( CWnd* pWnd, CPoint point )
{
    int IdMenu = HasContextMenu( pWnd, point );

    if ( IdMenu == -1 )
    {
        return;
    }

    // And test the hit.
    UINT uFlags;
    CPoint pt( point );
    ScreenToClient( &pt );
    HTREEITEM hItem = HitTest( pt, &uFlags );

    if ( ( hItem != NULL ) && ( TVHT_ONITEM & uFlags ) )
    {
        Select( hItem, TVGN_CARET );

        // Test if local or referenced symbol
        bool Local = true;
        CODSymbolComponent* pComp = m_ModelTree.GetSymbol( hItem );

        if ( pComp && ( ISA( pComp, ZBSymbol ) || ISA( pComp, ZBLinkSymbol ) ) )
        {
            if ( ISA( pComp, ZBSymbol ) )
            {
                Local = dynamic_cast<ZBSymbol*>( pComp )->IsLocal();
            }
            else if ( ISA( pComp, ZBLinkSymbol ) )
            {
                Local = dynamic_cast<ZBLinkSymbol*>( pComp )->IsLocal();
            }
        }

        CMenu* pPopup = NULL;

        if ( Local )
        {
            pPopup = m_SymbolPopupMainMenu.GetSubMenu( IdMenu );
        }
        else
        {
            pPopup = m_SymbolRefPopupMainMenu.GetSubMenu( IdMenu );
        }

        ASSERT( pPopup != NULL );
        CWnd* pWndPopupOwner = this;
        
        while ( pWndPopupOwner->GetStyle() & WS_CHILD )
        {
            pWndPopupOwner = pWndPopupOwner->GetParent();
        }

        // If required to enable all menu items
        if ( m_EnableMenuItems )
        {
            UINT Count = pPopup->GetMenuItemCount();

            for ( UINT i = 0; i < Count; ++i )
            {
                pPopup->EnableMenuItem( i, MF_BYPOSITION | MF_ENABLED );
            }
        }

        pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                                point.x,
                                point.y,
                                ( m_EnableMenuItems ) ? this : pWndPopupOwner );
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZCProcessModelTree message handlers

void ZCProcessModelTree::OnContextMenu( CWnd* pWnd, CPoint point )
{
    DisplayContextMenu( pWnd, point );
}

void ZCProcessModelTree::OnLButtonDblClk( UINT nFlags, CPoint point )
{
    // Browse the symbol
    OnDoubleClick();
}

void ZCProcessModelTree::OnRButtonDblClk( UINT nFlags, CPoint point )
{
    ZITreeCtrl::OnRButtonDblClk( nFlags, point );

    // Browse the symbol
    OnDoubleClick();
}

void ZCProcessModelTree::OnRButtonUp( UINT nFlags, CPoint point )
{
    ZITreeCtrl::OnRButtonUp( nFlags, point );
}

void ZCProcessModelTree::OnRefresh()
{
    m_ModelTree.Refresh();
}

void ZCProcessModelTree::OnModelBrowserEditName()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_EDIT_NAME );
}

void ZCProcessModelTree::OnModelBrowserGoInSymbol()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_GOIN_SYMBOL );
}

void ZCProcessModelTree::OnModelBrowserEditCut()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_EDIT_CUT );
}

void ZCProcessModelTree::OnModelBrowserEditCopy()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_EDIT_COPY );
}

void ZCProcessModelTree::OnModelBrowserEditClear()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_EDIT_CLEAR );
}

void ZCProcessModelTree::OnModelBrowserProperties()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_OD_PROPERTIES );
}

void ZCProcessModelTree::OnModelBrowserBrowseSourceSymbol()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_BROWSE_SOURCESYMBOL );
}

void ZCProcessModelTree::OnModelBrowserSelectSymbol()
{
    m_ModelTree.DoSelectSymbol();
}

void ZCProcessModelTree::OnInsertModelPage()
{
    AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_INSERT_MODELPAGE );
}

void ZCProcessModelTree::OnRenameModelPage()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_RENAME_CURRENTMODELPAGE );
}

void ZCProcessModelTree::OnDeleteModelPage()
{
    m_ModelTree.DoSelectSymbol();
    AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_DELETE_CURRENTMODELPAGE );
}

void ZCProcessModelTree::OnCollapseBranch()
{
    CollapseBranch( GetSelectedItem(), TRUE );
}

void ZCProcessModelTree::OnExpandBranch()
{
    ExpandBranch( GetSelectedItem(), TRUE );
}
