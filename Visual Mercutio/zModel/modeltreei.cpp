// Source file: ModelTreei.cpp

#include <StdAfx.h>

#include "ModelTreei.h"
#include "ProcGraphModelMdl.h"

#include "zBaseLib\ZITreeCtl.h"
#include "ZBModelSet.h"
#include "ZBSymbol.h"
#include "ZBLinkSymbol.h"
#include "ZDProcessGraphPage.h"

#include "ZBModelObserverMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 13 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

const int _ModelDocumentTreeItem    = 0;
const int _ModelPageTreeItem        = 2;

// Class ZIModelTree 

ZIModelTree::ZIModelTree( ZITreeCtrl*            pTreeCtrl,
                          const CString            RootName,
                          ZBModelSet*            pModelSet,
                          UINT                    nIDImageRes,
                          ZBRuntimeClassSet*    pSet            /*= NULL*/ )
    : m_pTreeCtrl            ( pTreeCtrl ),
      m_pModelSet            ( NULL ),
      m_HasBeenInitialized    ( FALSE ),
      m_hRootDocument        ( NULL ),
      m_RootName            ( RootName ),
      m_nIDImageRes            ( nIDImageRes ),
      m_pSet                ( pSet )
{
    if ( pModelSet )
    {
        m_pModelSet = pModelSet->Clone();
    }
}

ZIModelTree::~ZIModelTree()
{
    Empty();
}

void ZIModelTree::FreeModelSet()
{
    if ( m_pModelSet )
    {
        delete m_pModelSet;
        m_pModelSet = NULL;
    }
}

bool ZIModelTree::CreateEmptyModelSet()
{
    FreeModelSet();

    m_pModelSet = new ZBModelSet;

    return m_pModelSet != NULL;
}

void ZIModelTree::Empty()
{
    FreeModelSet();

    if ( m_pTreeCtrl && ::IsWindow( m_pTreeCtrl->GetSafeHwnd() ) )
    {
        m_pTreeCtrl->DeleteAllItems();
    }

    m_pTreeCtrl        = NULL;
    m_hRootDocument    = NULL;

    // Empty the data set first
    EmptyDataSet();
}

void ZIModelTree::Initialize( ZITreeCtrl*            pTreeCtrl,
                              const CString            RootName,
                              ZBModelSet*            pModelSet,
                              UINT                    nIDImageRes,
                              ZBRuntimeClassSet*    pSet            /*= NULL*/ )
{
    m_pTreeCtrl    = pTreeCtrl;
    m_pSet        = pSet;

    if ( pModelSet )
    {
        FreeModelSet();
        m_pModelSet = pModelSet->Clone();
    }

    m_RootName        = RootName;
    m_nIDImageRes    = nIDImageRes;

    // If not model set, create an empty
    if ( !ModelSetExist() )
    {
        CreateEmptyModelSet();
    }

    InitializeTree();
    ZIModelTree::Refresh();

    pTreeCtrl->EnsureVisible( pTreeCtrl->GetRootItem() );
    pTreeCtrl->SelectItem( pTreeCtrl->GetRootItem() );
}

void ZIModelTree::Refresh()
{
    // Empty the data set first
    EmptyDataSet();

    if ( m_pTreeCtrl )
    {
        // Don't forget to save the tree state
        m_pTreeCtrl->SaveCollapsedState();
        m_pTreeCtrl->DeleteAllItems();

        m_hRootDocument = NULL;
        ZIModelTree::CreateTree();

        // When recreated, restore the initial state
        m_pTreeCtrl->RestoreCollapsedStateToTreeCtrl();

        // Immediate update
        m_pTreeCtrl->RedrawWindow();
    }
}

void ZIModelTree::SetRootName( const CString RootName )
{
    m_RootName = RootName;
}

void ZIModelTree::AddModel( ZDProcessGraphModelMdl* pModel )
{
    // If not model set, create an empty
    if ( !ModelSetExist() )
    {
        CreateEmptyModelSet();
    }

    if ( !m_hRootDocument )
    {
        return;
    }

    if ( m_pModelSet->FindModelIndex( pModel ) != -1 )
    {
        return;
    }

    // Add the model
    m_pModelSet->AddModel( pModel );

    // Insert the model in the tree
    ProcessRootModel( pModel, m_hRootDocument );
}

void ZIModelTree::RemoveModel( ZDProcessGraphModelMdl* pModel )
{
    // If not model set, nothing to remove
    if ( !ModelSetExist() )
    {
        return;
    }

    if ( !m_hRootDocument )
    {
        return;
    }

    int ModelIndex = m_pModelSet->FindModelIndex( pModel );

    if ( ModelIndex == -1 )
    {
        return;
    }

    _ZInternalModelTreeData* pData = FindElementFromDataSet( pModel->GetModelName() );

    if ( pData )
    {
        HTREEITEM    hItem = m_pTreeCtrl->FindItemData( pData,
                                                       NULL );    // From item, in fact from root

        if ( hItem )
        {
            m_pTreeCtrl->DeleteItem( hItem );
            DeleteElementFromDataSet(pModel);
        }
    }
}

void ZIModelTree::AddModelSet( ZBModelSet* pModelSet )
{
    // If not model set, create an empty
    if ( !ModelSetExist() )
    {
        CreateEmptyModelSet();
    }

    if ( !m_hRootDocument )
    {
        return;
    }

    ProcessModelSet( pModelSet, m_hRootDocument );
}

void ZIModelTree::RemoveModelSet( ZBModelSet* pModelSet )
{
    // If not model set, nothing to remove
    if ( !ModelSetExist() )
    {
        return;
    }
}

void ZIModelTree::AddSymbol( CODSymbolComponent*        pSymbol,
                             ZDProcessGraphModelMdl*    pModel,
                             bool                        CheckUnique    /*= true*/ )
{
    if ( !pSymbol || ( !ISA( pSymbol, ZBSymbol ) && !ISA( pSymbol, ZBLinkSymbol ) ) )
    {
        return;
    }

    if ( m_pSet && !SymbolIsPartOfSet( pSymbol ) )
    {
        return;
    }

    // If not model set, nothing to remove
    if ( !ModelSetExist() )
    {
        return;
    }

    if ( !m_hRootDocument )
    {
        return;
    }

    HTREEITEM hParentItem = m_hRootDocument;

    if ( pModel )
    {
        _ZInternalModelTreeData* pData;

        if ( CheckUnique )
        {
            // Check if already exist
            pData = FindElementFromDataSet( pSymbol );

            // If exists, do nothing
            if ( pData )
            {
                return;
            }
        }

        ZDProcessGraphPage* pPage = NULL;
        CString NameToFind;

        if ( pModel->GetRoot() )
        {
            pPage = pModel->GetRoot()->FindModelPage( pModel );
        }

        // Find the model
        if ( pPage )
        {
            pData = FindElementFromDataSet( pPage );
        }
        else
        {
            pData = FindElementFromDataSet( pModel->GetModelName() );
        }

        if ( pData )
        {
            hParentItem = m_pTreeCtrl->FindItemData( pData,
                                                     (HTREEITEM)NULL );    // From item, in fact from root
        }
        // If not found, set the root as parent
        if ( !hParentItem )
        {
            hParentItem = m_hRootDocument;
        }
    }

    if ( !hParentItem )
    {
        return;
    }

    if ( ISA( pSymbol, ZBSymbol ) )
    {
        // If it has a child model, run through the model
        // But not a child model reference
        if ( ( (ZBSymbol*)pSymbol )->GetChildModel() && !( (ZBSymbol*)pSymbol )->IsChildModelRef() )
        {
            // Create a root item
            HTREEITEM hRootProcess = AddSymbolItem( (ZBSymbol*)pSymbol, hParentItem );

            // Run the model
            ProcessModelByPageSet( reinterpret_cast<ZDProcessGraphModelMdl*>( ( (ZBSymbol*)pSymbol )->GetChildModel() ), hRootProcess );

            // Ensure visible first and then
            // expand the new branch to make elements visible
            if ( hRootProcess )
            {
                m_pTreeCtrl->EnsureVisible( hRootProcess );
                m_pTreeCtrl->ExpandBranch( hRootProcess );
            }
        }
        else
        {
            ProcessSymbol( reinterpret_cast<ZBSymbol*>( pSymbol ), hParentItem );
        }
    }
    else
    {
        ProcessLinkSymbol( reinterpret_cast<ZBLinkSymbol*>( pSymbol ), hParentItem );
    }
}

void ZIModelTree::RemoveSymbol( CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel )
{
    if ( !pSymbol || ( !ISA( pSymbol, ZBSymbol ) && !ISA( pSymbol, ZBLinkSymbol ) ) )
    {
        return;
    }

    // If not model set, nothing to remove
    if ( !ModelSetExist() )
    {
        return;
    }

    if ( !m_hRootDocument )
    {
        return;
    }

    _ZInternalModelTreeData* pData = FindElementFromDataSet( pSymbol );

    if ( pData )
    {
        HTREEITEM hItem = m_pTreeCtrl->FindItemData( pData,
                                                     (HTREEITEM)NULL );    // From item, in fact from root

        if ( hItem )
        {
            m_pTreeCtrl->DeleteItem( hItem );
            DeleteElementFromDataSet( pSymbol );
        }
    }
}

void ZIModelTree::ModifySymbol( CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel )
{
    if ( !pSymbol || ( !ISA( pSymbol, ZBSymbol ) && !ISA( pSymbol, ZBLinkSymbol ) ) )
    {
        return;
    }

    if ( m_pSet && !SymbolIsPartOfSet( pSymbol ) )
    {
        return;
    }

    // If not model set, nothing to remove
    if ( !ModelSetExist() )
    {
        return;
    }

    if ( !m_hRootDocument )
    {
        return;
    }

    HTREEITEM hParentItem            = m_hRootDocument;
    _ZInternalModelTreeData* pData    = FindElementFromDataSet( pSymbol );

    if ( pData )
    {
        HTREEITEM hItem = m_pTreeCtrl->FindItemData( pData,
                                                     (HTREEITEM)NULL );    // From item, in fact from root

        if ( !hItem )
        {
            return;
        }

        if ( ISA( pSymbol, ZBSymbol ) )
        {
            ModifySymbolItem( reinterpret_cast<ZBSymbol*>( pSymbol ), hItem );
        }
        else
        {
            ModifyLinkSymbolItem( reinterpret_cast<ZBLinkSymbol*>( pSymbol ), hItem );
        }
    }
}

void ZIModelTree::InitializeTree()
{
    if ( m_HasBeenInitialized || !m_pTreeCtrl )
    {
        return;
    }

    // Sets styles
    m_pTreeCtrl->HasButtons();
    m_pTreeCtrl->HasLines();
    m_pTreeCtrl->LinesAtRoot();
    m_pTreeCtrl->ShowSelectionAlways();

    // Load images
    m_pTreeCtrl->LoadImageList( m_nIDImageRes, 17, 1, RGB( 255, 255, 255 ) );
    m_HasBeenInitialized = TRUE;
}

void ZIModelTree::CreateTree()
{
    if ( !m_pModelSet )
    {
        return;
    }

    if ( m_pModelSet && m_pModelSet->GetModelCount() > 1 )
    {
        m_hRootDocument = AddTypeItem ( m_RootName, _ModelDocumentTreeItem );
    }
    else
    {
        m_hRootDocument = NULL;
    }

    ProcessModelSet( m_pModelSet, m_hRootDocument );

    // Expand the root
    m_pTreeCtrl->ExpandRoot( TRUE );
}

void ZIModelTree::ProcessModelSet( ZBModelSet* pModelSet, HTREEITEM hParentTreeItem )
{
    if ( !pModelSet )
    {
        return;
    }

    for ( size_t i = 0; i < pModelSet->GetModelCount(); ++i )
    {
        ZDProcessGraphModelMdl* pModel = pModelSet->GetModelAt( i );

        if ( pModel )
        {
            ProcessRootModel( pModel, hParentTreeItem );
        }
    }
}

void ZIModelTree::ProcessRootModel( ZDProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem )
{
    if ( !pModel )
    {
        return;
    }

    HTREEITEM hRootModel = AddModelItem ( pModel, hParentTreeItem );

    // If we have not parent, that means this model is the root
    if ( hParentTreeItem == NULL )
    {
        m_hRootDocument = hRootModel;
    }

    ProcessModelByPageSet( pModel, hRootModel );

    m_pTreeCtrl->ExpandRoot( TRUE );
}

void ZIModelTree::ProcessModelByPageSet( ZDProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem )
{
    ZBProcessGraphPageSet* pSet = pModel->GetPageSet();

    if ( pSet )
    {
        ZBProcessGraphPageIterator i( pSet );

        for ( ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext() )
        {
            // Create a root item
            HTREEITEM hRootPage = AddPageItem( pPage, hParentTreeItem );

            if ( ISA( pPage->GetpModel(), ZDProcessGraphModelMdl ) )
            {
                // Run the model
                ProcessModel( const_cast<ZDProcessGraphModelMdl*>( pPage->GetpModel() ), hRootPage );
            }
        }
    }
    else
    {
        ProcessModel( pModel, hParentTreeItem );
    }
}

void ZIModelTree::ProcessModel( ZDProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem )
{
    // No model, return
    if ( !pModel )
    {
        return;
    }

    CODComponentSet* pSet = pModel->GetComponents();

    for ( int i = 0; i < pSet->GetSize(); ++i )
    {
        CODComponent* pComp = pSet->GetAt( i );

        // If it is a symbol
        if ( !pComp || ( !ISA( pComp, ZBSymbol ) && !ISA( pComp, ZBLinkSymbol ) ) )
        {
            continue;
        }

        if ( ISA( pComp, ZBSymbol ) )
        {
            // If it has a child model, run through the model
            // But not a child model reference
            if ( ( (ZBSymbol*)pComp )->GetChildModel() && !( (ZBSymbol*)pComp )->IsChildModelRef() )
            {
                if ( m_pSet && !SymbolIsPartOfSet( pComp ) )
                {
                    continue;
                }

                // Create a root item
                HTREEITEM hRootProcess = AddSymbolItem( (ZBSymbol*)pComp, hParentTreeItem );

                // Run the model
                ProcessModelByPageSet( reinterpret_cast<ZDProcessGraphModelMdl*>( ( (ZBSymbol*)pComp )->GetChildModel() ), hRootProcess );
            }
            else
            {
                if ( m_pSet && !SymbolIsPartOfSet( pComp ) )
                {
                    continue;
                }

                ProcessSymbol( (ZBSymbol*)pComp, hParentTreeItem );
            }
        }
        else
        {
            if ( m_pSet && !SymbolIsPartOfSet( pComp ) )
            {
                continue;
            }

            ProcessLinkSymbol( (ZBLinkSymbol*)pComp, hParentTreeItem );
        }
    }
}

void ZIModelTree::ProcessSymbol( ZBSymbol* pSymbol, HTREEITEM hParentTreeItem )
{
    if ( !pSymbol )
    {
        return;
    }

    if ( pSymbol->GetIconIndex() == -1 )
    {
        return;
    }

    if ( m_pSet && !SymbolIsPartOfSet( pSymbol ) )
    {
        return;
    }

    HTREEITEM hItem = AddSymbolItem( pSymbol, hParentTreeItem );

    if ( hItem )
    {
        m_pTreeCtrl->EnsureVisible( hItem );
    }
}

void ZIModelTree::ProcessLinkSymbol( ZBLinkSymbol* pSymbol, HTREEITEM hParentTreeItem )
{
    if ( !pSymbol )
    {
        return;
    }

    if ( pSymbol->GetIconIndex() == -1 )
    {
        return;
    }

    if ( m_pSet && !SymbolIsPartOfSet( pSymbol ) )
    {
        return;
    }

    HTREEITEM hItem = AddLinkSymbolItem( pSymbol, hParentTreeItem );

    if ( hItem )
    {
        m_pTreeCtrl->EnsureVisible( hItem );
    }
}

HTREEITEM ZIModelTree::AddTypeItem( const CString Name, int IconIndex, HTREEITEM hParentTreeItem )
{
    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent                = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage            = IconIndex;
    curTreeItem.item.iSelectedImage    = IconIndex;
    curTreeItem.item.pszText        = (char*)( (const char*)Name );
    curTreeItem.item.lParam            = (LPARAM)AddDataToSet( Name );    // Represent a selectable item
    curTreeItem.item.mask            = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return m_pTreeCtrl->InsertItem( &curTreeItem );
}

HTREEITEM ZIModelTree::AddModelItem( ZDProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem )
{
    if ( !pModel )
    {
        return NULL;
    }

    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent                = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage            = _ModelDocumentTreeItem;
    curTreeItem.item.iSelectedImage    = _ModelDocumentTreeItem;
    curTreeItem.item.pszText        = (char*)( (const char*)pModel->GetModelName() );
    curTreeItem.item.lParam            = (LPARAM)AddDataToSet( pModel );    // Represent a selectable item
    curTreeItem.item.mask            = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return m_pTreeCtrl->InsertItem( &curTreeItem );
}

HTREEITEM ZIModelTree::AddPageItem( ZDProcessGraphPage* pPage, HTREEITEM hParentTreeItem )
{
    if ( !pPage )
    {
        return NULL;
    }

    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent                = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage            = _ModelPageTreeItem;
    curTreeItem.item.iSelectedImage    = _ModelPageTreeItem;
    curTreeItem.item.pszText        = (char*)( (const char*)pPage->GetPageName() );
    curTreeItem.item.lParam            = (LPARAM)AddDataToSet( pPage );    // Represent a selectable item
    curTreeItem.item.mask            = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return m_pTreeCtrl->InsertItem( &curTreeItem );
}

HTREEITEM ZIModelTree::AddSymbolItem( ZBSymbol* pSymbol, HTREEITEM hParentTreeItem )
{
    if ( !pSymbol )
    {
        return NULL;
    }

    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent                = hParentTreeItem; 
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage            = pSymbol->GetIconIndex();
    curTreeItem.item.iSelectedImage    = pSymbol->GetIconIndex();
    curTreeItem.item.pszText        = (char*)( (const char*)pSymbol->GetSymbolName() );
    curTreeItem.item.lParam            = (LPARAM)AddDataToSet( pSymbol );    // Represent a selectable item
    curTreeItem.item.mask            = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return m_pTreeCtrl->InsertItem( &curTreeItem );
}

HTREEITEM ZIModelTree::AddLinkSymbolItem( ZBLinkSymbol* pSymbol, HTREEITEM hParentTreeItem )
{
    if ( !pSymbol )
    {
        return NULL;
    }

    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent                = hParentTreeItem; 
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage            = pSymbol->GetIconIndex();
    curTreeItem.item.iSelectedImage    = pSymbol->GetIconIndex();
    curTreeItem.item.pszText        = (char*)( (const char*)pSymbol->GetSymbolName() );
    curTreeItem.item.lParam            = (LPARAM)AddDataToSet( pSymbol );    // Represent a selectable item
    curTreeItem.item.mask            = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return m_pTreeCtrl->InsertItem( &curTreeItem );
}

BOOL ZIModelTree::ModifyModelItem( ZDProcessGraphModelMdl* pModel, HTREEITEM hItem )
{
    if ( !pModel )
    {
        return FALSE;
    }

    return m_pTreeCtrl->SetItemText( hItem, (char*)( (const char*)pModel->GetModelName() ) );
}

BOOL ZIModelTree::ModifySymbolItem( ZBSymbol* pSymbol, HTREEITEM hItem )
{
    if ( !pSymbol )
    {
        return FALSE;
    }

    return m_pTreeCtrl->SetItemText( hItem, (char*)( (const char*)pSymbol->GetSymbolName() ) );
}

BOOL ZIModelTree::ModifyPageItem( ZDProcessGraphPage* pPage, HTREEITEM hItem )
{
    if ( !pPage )
    {
        return FALSE;
    }

    return m_pTreeCtrl->SetItemText( hItem, (char*)( (const char*)pPage->GetPageName() ) );
}

BOOL ZIModelTree::ModifyLinkSymbolItem( ZBLinkSymbol* pSymbol, HTREEITEM hItem )
{
    if ( !pSymbol )
    {
        return FALSE;
    }

    return m_pTreeCtrl->SetItemText( hItem, (char*)( (const char*)pSymbol->GetSymbolName() ) );
}

CODSymbolComponent* ZIModelTree::GetSelectedSymbol()
{
    if ( m_pTreeCtrl )
    {
        return GetSymbol( m_pTreeCtrl->GetSelectedItem() );
    }

    return NULL;
}

CODSymbolComponent* ZIModelTree::GetSymbol( HTREEITEM hItem )
{
    if ( hItem )
    {
        _ZInternalModelTreeData* pObj = (_ZInternalModelTreeData*)m_pTreeCtrl->GetItemData( hItem );

        if ( pObj != NULL && pObj->m_dtp == _ZInternalModelTreeData::mdtp_Symbol )
        {
            return pObj->m_pSymbol;
        }

        if ( pObj != NULL && pObj->m_dtp == _ZInternalModelTreeData::mdtp_LinkSymbol )
        {
            return pObj->m_pLinkSymbol;
        }
    }

    return NULL;
}

ZDProcessGraphModelMdl* ZIModelTree::GetSelectedModel()
{
    if ( m_pTreeCtrl )
    {
        return GetModel( m_pTreeCtrl->GetSelectedItem() );
    }

    return NULL;
}

ZDProcessGraphModelMdl* ZIModelTree::GetModel( HTREEITEM hItem )
{
    if ( hItem )
    {
        _ZInternalModelTreeData* pObj = (_ZInternalModelTreeData*)m_pTreeCtrl->GetItemData( hItem );

        if ( pObj != NULL && pObj->m_dtp == _ZInternalModelTreeData::mdtp_Model )
        {
            return pObj->m_pModel;
        }
    }

    return NULL;
}

ZDProcessGraphPage* ZIModelTree::GetSelectedPage()
{
    if ( m_pTreeCtrl )
    {
        return GetPage( m_pTreeCtrl->GetSelectedItem() );
    }

    return NULL;
}

ZDProcessGraphPage* ZIModelTree::GetPage( HTREEITEM hItem )
{
    if ( hItem )
    {
        _ZInternalModelTreeData* pObj = (_ZInternalModelTreeData*)m_pTreeCtrl->GetItemData( hItem );

        if ( pObj != NULL && pObj->m_dtp == _ZInternalModelTreeData::mdtp_GraphPage )
        {
            return pObj->m_pGraphPage;
        }
    }

    return NULL;
}

ZDProcessGraphModelMdl* ZIModelTree::GetSelectedOwnerModel()
{
    if ( m_pTreeCtrl )
    {
        return GetOwnerModel( m_pTreeCtrl->GetSelectedItem() );
    }

    return NULL;
}

ZDProcessGraphModelMdl* ZIModelTree::GetOwnerModel( HTREEITEM hItem )
{
    if ( hItem )
    {
        ZDProcessGraphModelMdl* pModel = GetModel( hItem );

        if ( pModel )
        {
            return pModel;
        }

        // Try to check if a page is selected
        ZDProcessGraphPage* pPage = GetPage( hItem );

        // If yes, return the model
        if ( pPage )
        {
            return pPage->GetpModel();
        }

        // Now, try to check if a symbol is selected
        CODSymbolComponent* pSymbol = GetSymbol( hItem );

        if ( pSymbol )
        {
            if ( ISA( pSymbol, ZBSymbol) &&
                 ( (ZBSymbol*)pSymbol )->GetChildModel() &&
                 ISA( ( (ZBSymbol*)pSymbol )->GetChildModel(), ZDProcessGraphModelMdl ) )
            {
                return reinterpret_cast<ZDProcessGraphModelMdl*>( ( (ZBSymbol*)pSymbol )->GetChildModel() );
            }
            else
            {
                return GetOwnerModel( m_pTreeCtrl->GetParentItem( hItem ) );
            }
        }
    }

    return NULL;
}

bool ZIModelTree::IsRootSelected() const
{
    if ( m_pTreeCtrl && m_pTreeCtrl->GetSelectedItem() == m_pTreeCtrl->GetRootItem() )
    {
        return true;
    }

    return false;
}

bool ZIModelTree::IsDocumentSelected() const
{
    if ( m_pTreeCtrl && m_pTreeCtrl->GetSelectedItem() == m_hRootDocument )
    {
        return true;
    }

    return false;
}

void ZIModelTree::OnModelChange()
{
    Refresh();
}

void ZIModelTree::OnDoubleClick()
{
    ZBModelObserverMsg::MessageActionType ActionType = ZBModelObserverMsg::NoAction;
    UINT    Message = 0;

    CODSymbolComponent*    pComp = GetSelectedSymbol();

    if ( pComp && ISA( pComp, ZBSymbol ) )
    {
        if ( reinterpret_cast<ZBSymbol*>( pComp )->GetChildModel() )
        {
            ActionType    = ZBModelObserverMsg::BrowseElement;
            Message        = UM_BROWSE_SYMBOL;
        }
        else
        {
            ActionType    = ZBModelObserverMsg::EnsureElementVisible;
            Message        = UM_ENSUREVISIBLE_SYMBOL;
        }

        // Build the message
        ZBModelObserverMsg MdlMsg( ActionType, NULL, NULL, pComp );
        AfxGetMainWnd()->SendMessageToDescendants( Message, 0, (LPARAM)&MdlMsg );
    }
    else
    {
        ZDProcessGraphPage* pPage = GetSelectedPage();

        if ( pPage )
        {
            ActionType    = ZBModelObserverMsg::BrowseElement;
            Message        = UM_OPEN_MODELPAGE;

            // Build the message
            ZBModelObserverMsg    MdlMsg( ActionType, NULL, NULL, pPage );
            AfxGetMainWnd()->SendMessageToDescendants( Message, 0, (LPARAM)&MdlMsg );
        }
        else
        {
            if ( IsRootSelected() && m_pModelSet && m_pModelSet->GetModelAt( 0 ) )
            {
                ActionType    = ZBModelObserverMsg::BrowseElement;
                Message        = UM_OPEN_MODELPAGE;

                // Build the message
                ZBModelObserverMsg MdlMsg( ActionType, NULL, m_pModelSet->GetModelAt( 0 ) );
                AfxGetMainWnd()->SendMessageToDescendants( Message, 0, (LPARAM)&MdlMsg );
            }
        }
    }
}

void ZIModelTree::DoSelectSymbol()
{
    CODSymbolComponent*    pComp = GetSelectedSymbol();

    if ( pComp && ISA( pComp, ZBSymbol ) )
    {
        UINT Message = UM_ENSUREVISIBLE_SYMBOL;

        // Build the message
        ZBModelObserverMsg MdlMsg( ZBModelObserverMsg::SelectElement, NULL, NULL, pComp );
        AfxGetMainWnd()->SendMessageToDescendants( Message, 0, (LPARAM)&MdlMsg );
    }
    else
    {
        ZDProcessGraphPage* pPage = GetSelectedPage();

        if ( pPage )
        {
            UINT Message = UM_OPEN_MODELPAGE;

            // Build the message
            ZBModelObserverMsg MdlMsg( ZBModelObserverMsg::BrowseElement, NULL, NULL, pPage );
            AfxGetMainWnd()->SendMessageToDescendants( Message, 0, (LPARAM)&MdlMsg );
        }
    }
}

// Data set methods

_ZInternalModelTreeData::_ZInternalModelTreeData()
{
    m_dtp            = mdtp_Unknown;
    m_pSymbol        = NULL;
    m_pLinkSymbol    = NULL;
    m_pGraphPage    = NULL;
    m_pModel        = NULL;
    m_Collapsed        = false;

    m_Str.Empty();
}

_ZInternalModelTreeData::_ZInternalModelTreeData( ZBSymbol* pSymbol )
{
    m_dtp            = mdtp_Symbol;
    m_pSymbol        = pSymbol;

    m_pLinkSymbol    = NULL;
    m_pGraphPage    = NULL;
    m_pModel        = NULL;
    m_Collapsed        = false;

    m_Str.Empty();
}

_ZInternalModelTreeData::_ZInternalModelTreeData( ZBLinkSymbol* pLinkSymbol )
{
    m_dtp            = mdtp_LinkSymbol;
    m_pLinkSymbol    = pLinkSymbol;

    m_pSymbol        = NULL;
    m_pGraphPage    = NULL;
    m_pModel        = NULL;
    m_Collapsed        = false;

    m_Str.Empty();
}

_ZInternalModelTreeData::_ZInternalModelTreeData( ZDProcessGraphPage* pGraphPage )
{
    m_dtp            = mdtp_GraphPage;
    m_pGraphPage    = pGraphPage;

    m_pSymbol        = NULL;
    m_pLinkSymbol    = NULL;
    m_pModel        = NULL;
    m_Collapsed        = false;

    m_Str.Empty();
}

_ZInternalModelTreeData::_ZInternalModelTreeData( ZDProcessGraphModelMdl* pModel )
{
    m_dtp            = mdtp_Model;
    m_pModel        = pModel;

    m_pSymbol        = NULL;
    m_pLinkSymbol    = NULL;
    m_pGraphPage    = NULL;
    m_Collapsed        = false;

    m_Str.Empty();
}

_ZInternalModelTreeData::_ZInternalModelTreeData( CString Str )
{
    m_dtp            = mdtp_String;
    m_Str            = Str;

    m_pSymbol        = NULL;
    m_pLinkSymbol    = NULL;
    m_pGraphPage    = NULL;
    m_Collapsed        = false;
    m_pModel        = NULL;
}

_ZInternalModelTreeData::~_ZInternalModelTreeData()
{
    // In the destructor, just reset all values
    m_dtp            = mdtp_Unknown;
    m_pSymbol        = NULL;
    m_pLinkSymbol    = NULL;
    m_pGraphPage    = NULL;
    m_pModel        = NULL;
    m_Collapsed        = false;

    m_Str.Empty();
}

void ZIModelTree::EmptyDataSet()
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        delete pElement;
    }

    m_DataSet.RemoveAll();
}

_ZInternalModelTreeData* ZIModelTree::FindElementFromDataSet( CODSymbolComponent* pSymbol )
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_Symbol && pElement->m_pSymbol == pSymbol ) ||
             ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_LinkSymbol && pElement->m_pLinkSymbol == pSymbol ) )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalModelTreeData* ZIModelTree::FindElementFromDataSet( ZBSymbol* pSymbol )
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_Symbol && pElement->m_pSymbol == pSymbol )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalModelTreeData* ZIModelTree::FindElementFromDataSet( ZBLinkSymbol* pLinkSymbol )
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_LinkSymbol && pElement->m_pLinkSymbol == pLinkSymbol )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalModelTreeData* ZIModelTree::FindElementFromDataSet( ZDProcessGraphPage* pGraphPage )
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_GraphPage && pElement->m_pGraphPage == pGraphPage )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalModelTreeData* ZIModelTree::FindElementFromDataSet( ZDProcessGraphModelMdl* pModel )
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_Model && pElement->m_pModel == pModel )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalModelTreeData* ZIModelTree::FindElementFromDataSet( CString Str )
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_String && pElement->m_Str == Str )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalModelTreeData* ZIModelTree::AddDataToSet( ZBSymbol* pSymbol )
{
    _ZInternalModelTreeData* pData = new _ZInternalModelTreeData( pSymbol );
    m_DataSet.Add( pData );
    return pData;
}

_ZInternalModelTreeData* ZIModelTree::AddDataToSet( ZBLinkSymbol* pLinkSymbol )
{
    _ZInternalModelTreeData* pData = new _ZInternalModelTreeData( pLinkSymbol );
    m_DataSet.Add( pData );
    return pData;
}

_ZInternalModelTreeData* ZIModelTree::AddDataToSet( ZDProcessGraphPage* pGraphPage )
{
    _ZInternalModelTreeData* pData = new _ZInternalModelTreeData( pGraphPage );
    m_DataSet.Add( pData );
    return pData;
}

_ZInternalModelTreeData* ZIModelTree::AddDataToSet( ZDProcessGraphModelMdl* pModel )
{
    _ZInternalModelTreeData* pData = new _ZInternalModelTreeData( pModel );
    m_DataSet.Add( pData );
    return pData;
}

_ZInternalModelTreeData* ZIModelTree::AddDataToSet( CString Str )
{
    _ZInternalModelTreeData* pData = new _ZInternalModelTreeData( Str );
    m_DataSet.Add( pData );
    return pData;
}

bool ZIModelTree::DeleteElementFromDataSet( CODSymbolComponent* pSymbol )
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_Symbol && pElement->m_pSymbol == pSymbol ) ||
             ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_LinkSymbol && pElement->m_pLinkSymbol == pSymbol ) )
        {
            delete pElement;
            i.Remove();
            return true;
        }
    }

    return false;
}

bool ZIModelTree::DeleteElementFromDataSet( ZBSymbol* pSymbol )
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_Symbol && pElement->m_pSymbol == pSymbol )
        {
            delete pElement;
            i.Remove();
            return true;
        }
    }

    return false;
}

bool ZIModelTree::DeleteElementFromDataSet( ZBLinkSymbol* pLinkSymbol )
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_LinkSymbol && pElement->m_pLinkSymbol == pLinkSymbol )
        {
            delete pElement;
            i.Remove();
            return true;
        }
    }

    return false;
}

bool ZIModelTree::DeleteElementFromDataSet( ZDProcessGraphPage* pGraphPage )
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_GraphPage && pElement->m_pGraphPage == pGraphPage )
        {
            delete pElement;
            i.Remove();
            return true;
        }
    }

    return false;
}

bool ZIModelTree::DeleteElementFromDataSet( ZDProcessGraphModelMdl* pModel )
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_Model && pElement->m_pModel == pModel )
        {
            delete pElement;
            i.Remove();
            return true;
        }
    }

    return false;
}

bool ZIModelTree::DeleteElementFromDataSet( CString Str )
{
    _ZInternalModelTreeDataIterator i( &m_DataSet );

    for ( _ZInternalModelTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalModelTreeData::mdtp_String && pElement->m_Str == Str )
        {
            delete pElement;
            i.Remove();
            return true;
        }
    }

    return false;
}

bool ZIModelTree::SymbolIsPartOfSet( CODComponent* pSymbol ) const
{
    // Run through the set of runtime class pointer and check
    // if the symbol is part of it.
    ZBRuntimeClassIterator i( m_pSet );

    for ( const CRuntimeClass* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pSymbol->IsKindOf( pElement ) )
        {
            return true;
        }
    }

    return false;
}
