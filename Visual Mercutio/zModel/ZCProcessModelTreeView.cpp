// ZCProcessModelTreeView.cpp : implementation file

#include "stdafx.h"
#include "ZCProcessModelTreeView.h"

#include "zBaseLib\ZIDropView.h"
#include "zBaseLib\ZITreeCtl.h"
#include "ZBSymbol.h"
#include "ZBLinkSymbol.h"

#include "ZDProcessGraphPage.h"
#include "ZBModelObserverMsg.h"

#ifdef _DEBUG
#include "zFormsRes\zFormsRes.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 14 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZCProcessModelTreeView

IMPLEMENT_DYNCREATE( ZCProcessModelTreeView, ZITreeView )

BEGIN_MESSAGE_MAP( ZCProcessModelTreeView, ZITreeView )
	//{{AFX_MSG_MAP(ZCProcessModelTreeView)
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

ZCProcessModelTreeView::ZCProcessModelTreeView()
	: m_pModelSet		( NULL ),
	  m_pPopupSubMenu	( NULL ),
	  m_EnableMenuItems	( false )
{
}

ZCProcessModelTreeView::~ZCProcessModelTreeView()
{
}

void ZCProcessModelTreeView::Initialize( const CString		ModelName,
										 ZBModelSet*		pModelSet,
										 UINT				nIDImageRes,
										 ZBRuntimeClassSet*	pSet			/*= NULL*/,
										 bool				EnableMenuItems	/*= true*/ )
{
	m_pModelSet			= pModelSet;
	m_EnableMenuItems	= EnableMenuItems;

	// Enable drag and drop
	( (ZITreeCtrl*)&GetTreeCtrl() )->DisableDragDrop( false );

	// Initialize the worker class
	m_ModelTree.Initialize( (ZITreeCtrl*)&GetTreeCtrl(), ModelName, m_pModelSet, nIDImageRes, pSet );
}

void ZCProcessModelTreeView::Refresh()
{
	m_ModelTree.Refresh();
}

void ZCProcessModelTreeView::Empty()
{
	m_ModelTree.Empty();
}

void ZCProcessModelTreeView::AddModel( ZDProcessGraphModelMdl* pModel )
{
	m_ModelTree.AddModel( pModel );
}

void ZCProcessModelTreeView::RemoveModel( ZDProcessGraphModelMdl* pModel )
{
	m_ModelTree.RemoveModel( pModel );
}

void ZCProcessModelTreeView::AddModelSet( ZBModelSet* pModelSet )
{
	m_ModelTree.AddModelSet( pModelSet );
}

void ZCProcessModelTreeView::RemoveModelSet( ZBModelSet* pModelSet )
{
	m_ModelTree.RemoveModelSet( pModelSet );
}

void ZCProcessModelTreeView::AddSymbol( CODSymbolComponent*		pSymbol,
										ZDProcessGraphModelMdl*	pModel,
										bool					CheckUnique )
{
	m_ModelTree.AddSymbol( pSymbol, pModel, CheckUnique );
}

void ZCProcessModelTreeView::RemoveSymbol( CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel )
{
	m_ModelTree.RemoveSymbol( pSymbol, pModel );
}

void ZCProcessModelTreeView::ModifySymbol( CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel )
{
	m_ModelTree.ModifySymbol( pSymbol, pModel );
}

void ZCProcessModelTreeView::OnDoubleClick()
{
	m_ModelTree.OnDoubleClick();
}

int ZCProcessModelTreeView::HasContextMenu( CWnd* pWnd, CPoint point )
{
	// Now display the right sub-menu
	int IdMenu = -1;
	UINT Flags;
	CPoint pt( point );
	ScreenToClient( &pt );

	HTREEITEM hItem = ( (ZITreeCtrl*)&GetTreeCtrl() )->HitTest( pt, &Flags );

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

void ZCProcessModelTreeView::DisplayContextMenu( CWnd* pWnd, CPoint point )
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
	HTREEITEM hItem = ( (ZITreeCtrl*)&GetTreeCtrl() )->HitTest( pt, &uFlags );

	if ( ( hItem != NULL ) && ( TVHT_ONITEM & uFlags ) )
	{
		( (ZITreeCtrl*)&GetTreeCtrl() )->Select( hItem, TVGN_CARET );

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
// ZCProcessModelTreeView drawing

void ZCProcessModelTreeView::OnDraw( CDC* pDC )
{
}

/////////////////////////////////////////////////////////////////////////////
// ZCProcessModelTreeView message handlers

void ZCProcessModelTreeView::OnContextMenu( CWnd* pWnd, CPoint point )
{
	DisplayContextMenu( pWnd, point );
}

void ZCProcessModelTreeView::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	// Browse the symbol
	OnDoubleClick();
}

void ZCProcessModelTreeView::OnRButtonDblClk( UINT nFlags, CPoint point )
{
	ZITreeView::OnRButtonDblClk( nFlags, point );

	// Browse the symbol
	OnDoubleClick();
}

void ZCProcessModelTreeView::OnRButtonUp( UINT nFlags, CPoint point )
{
	ZITreeView::OnRButtonUp( nFlags, point );
}

void ZCProcessModelTreeView::OnRefresh()
{
	m_ModelTree.Refresh();
}

void ZCProcessModelTreeView::OnModelBrowserEditName()
{
	m_ModelTree.DoSelectSymbol();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_EDIT_NAME );
}

void ZCProcessModelTreeView::OnModelBrowserGoInSymbol()
{
	m_ModelTree.DoSelectSymbol();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_GOIN_SYMBOL );
}

void ZCProcessModelTreeView::OnModelBrowserEditCut()
{
	m_ModelTree.DoSelectSymbol();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_EDIT_CUT );
}

void ZCProcessModelTreeView::OnModelBrowserEditCopy()
{
	m_ModelTree.DoSelectSymbol();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_EDIT_COPY );
}

void ZCProcessModelTreeView::OnModelBrowserEditClear()
{
	m_ModelTree.DoSelectSymbol();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_EDIT_CLEAR );
}

void ZCProcessModelTreeView::OnModelBrowserProperties()
{
	m_ModelTree.DoSelectSymbol();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_OD_PROPERTIES );
}

void ZCProcessModelTreeView::OnModelBrowserBrowseSourceSymbol()
{
	m_ModelTree.DoSelectSymbol();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_BROWSE_SOURCESYMBOL );
}

void ZCProcessModelTreeView::OnModelBrowserSelectSymbol()
{
	m_ModelTree.DoSelectSymbol();
}

void ZCProcessModelTreeView::OnInsertModelPage()
{
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_INSERT_MODELPAGE );
}

void ZCProcessModelTreeView::OnRenameModelPage()
{
	m_ModelTree.DoSelectSymbol();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_RENAME_CURRENTMODELPAGE );
}

void ZCProcessModelTreeView::OnDeleteModelPage()
{
	m_ModelTree.DoSelectSymbol();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_DELETE_CURRENTMODELPAGE );
}

void ZCProcessModelTreeView::OnCollapseBranch()
{
	CollapseBranch( ( (ZITreeCtrl*)&GetTreeCtrl() )->GetSelectedItem(), TRUE );
}

void ZCProcessModelTreeView::OnExpandBranch()
{
	ExpandBranch( ( (ZITreeCtrl*)&GetTreeCtrl() )->GetSelectedItem(), TRUE );
}

/////////////////////////////////////////////////////////////////////////////
// ZCProcessModelTreeView diagnostics

#ifdef _DEBUG
void ZCProcessModelTreeView::AssertValid() const
{
	ZITreeView::AssertValid();
}

void ZCProcessModelTreeView::Dump( CDumpContext& dc ) const
{
	ZITreeView::Dump( dc );
}
#endif //_DEBUG
