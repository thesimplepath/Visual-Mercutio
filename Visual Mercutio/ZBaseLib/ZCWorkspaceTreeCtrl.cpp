// ZCWorkspaceTreeCtrl.cpp : implementation file

#include "stdafx.h"
#include "ZCWorkspaceTreeCtrl.h"

#include "ZBWorkspaceEnv.h"
#include "ZBWorkspaceFileEntity.h"
#include "ZBWorkspaceGroupEntity.h"
#include "ZBWorkspaceObserverMsg.h"

#include "zBaseLibRes.h"
#include "PSS_FileDialog.h"
#include "ZVWorkspaceGroupNameDlg.h"
#include "ZVWorkspaceRenameGroupNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

const int _WorkspaceEnvTreeItem    = 0;
const int _GroupTreeItem        = 1;
const int _GroupOpenTreeItem    = 2;
const int _AnyFileTreeItem        = 3;

BEGIN_MESSAGE_MAP( ZCWorkspaceTreeCtrl, ZITreeCtrl )
    //{{AFX_MSG_MAP(ZCWorkspaceTreeCtrl)
    ON_WM_CREATE()
    ON_WM_LBUTTONDBLCLK()
    ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
    ON_WM_CONTEXTMENU()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZCWorkspaceTreeCtrl

ZCWorkspaceTreeCtrl::ZCWorkspaceTreeCtrl( const CString RootName /*= ""*/, ZBWorkspaceEnv* pWorkspaceEnv /*= NULL*/ )
    : m_RootName            ( RootName ),
      m_pWorkspaceEnv        ( pWorkspaceEnv ),
      m_hRootWorkspaceEnv    ( NULL )
{
}

ZCWorkspaceTreeCtrl::~ZCWorkspaceTreeCtrl()
{
}

void ZCWorkspaceTreeCtrl::Initialize( const CString RootName, ZBWorkspaceEnv* pWorkspaceEnv )
{
    m_RootName        = RootName;
    m_pWorkspaceEnv    = pWorkspaceEnv;
    LoadTree();
}

void ZCWorkspaceTreeCtrl::Refresh()
{
    DestroyTree();
    LoadTree();
}

void ZCWorkspaceTreeCtrl::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
    if ( pMsg && ISA( pMsg, ZBWorkspaceObserverMsg ) )
    {
        switch ( dynamic_cast<ZBWorkspaceObserverMsg*>( pMsg )->GetMessageID() )
        {
            case UM_INITWORKSPACE:
            {
                Initialize( dynamic_cast<ZBWorkspaceObserverMsg*>( pMsg )->GetpEnv()->GetEntityName(),
                            dynamic_cast<ZBWorkspaceObserverMsg*>( pMsg )->GetpEnv() );
                break;
            }

            case UM_CLOSEWORKSPACE:
            {
                DestroyTree();
                break;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZCWorkspaceTreeCtrl message handlers

int ZCWorkspaceTreeCtrl::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
    if ( ZITreeCtrl::OnCreate( lpCreateStruct ) == -1 )
    {
        return -1;
    }

    VERIFY( m_SubMenu.LoadMenu( IDR_WORKSPACE_SUBMENUS ) );
    
    CreateTree();
    LoadTree();

    return 0;
}

BOOL ZCWorkspaceTreeCtrl::DestroyWindow()
{
    DestroyTree();

    return CWnd::DestroyWindow();
}

void ZCWorkspaceTreeCtrl::DestroyTree()
{
    if ( ::IsWindow( GetSafeHwnd() ) )
    {
        DeleteAllItems();
    }

    // Empty the data set first
    EmptyDataSet();
}

void ZCWorkspaceTreeCtrl::CreateTree()
{
    // Sets styles
    HasButtons();
    HasLines();
    LinesAtRoot();
    ShowSelectionAlways();

    // Load images
    LoadImageList( IDB_IL_WORKSPACEENV, 17, 1, RGB( 255, 255, 255 ) );
}

void ZCWorkspaceTreeCtrl::LoadTree()
{
    if ( !m_pWorkspaceEnv )
    {
        return;
    }

    m_hRootWorkspaceEnv = AddTypeItem ( m_RootName, _WorkspaceEnvTreeItem );

    ProcessWorkspaceEnv( m_pWorkspaceEnv, m_hRootWorkspaceEnv );

    // Expand the root
    ExpandRoot( TRUE );
}

void ZCWorkspaceTreeCtrl::ProcessWorkspaceEnv( ZBWorkspaceEnv* pWorkspaceEnv, HTREEITEM hParentTreeItem )
{
    if ( pWorkspaceEnv->ContainEntity() )
    {
        int Count = pWorkspaceEnv->GetEntityCount();

        for ( int i = 0; i < Count; ++i )
        {
            ZBWorkspaceEntity* pEntity = pWorkspaceEnv->GetEntityAt( i );

            if ( !pEntity )
            {
                continue;
            }

            if ( ISA( pEntity, ZBWorkspaceGroupEntity ) )
            {
                ProcessGroup( dynamic_cast<ZBWorkspaceGroupEntity*>( pEntity ), hParentTreeItem );
            }

            if ( ISA( pEntity, ZBWorkspaceFileEntity ) )
            {
                ProcessFile( dynamic_cast<ZBWorkspaceFileEntity*>( pEntity ), hParentTreeItem );
            }
        }
    }
}

void ZCWorkspaceTreeCtrl::ProcessGroup( ZBWorkspaceGroupEntity* pGroup, HTREEITEM hParentTreeItem )
{
    // First, add the item
    HTREEITEM hGroupItem = AddGroupItem ( pGroup, hParentTreeItem );

    if ( pGroup->ContainEntity() )
    {
        int Count = pGroup->GetEntityCount();

        for ( int i = 0; i < Count; ++i )
        {
            ZBWorkspaceEntity* pEntity = pGroup->GetEntityAt( i );

            if ( !pEntity )
            {
                continue;
            }

            if ( ISA( pEntity, ZBWorkspaceGroupEntity ) )
            {
                ProcessGroup( dynamic_cast<ZBWorkspaceGroupEntity*>( pEntity ), hGroupItem );
            }

            if ( ISA( pEntity, ZBWorkspaceFileEntity ) )
            {
                ProcessFile( dynamic_cast<ZBWorkspaceFileEntity*>( pEntity ), hGroupItem );
            }
        }
    }
}

void ZCWorkspaceTreeCtrl::ProcessFile( ZBWorkspaceFileEntity* pFile, HTREEITEM hParentTreeItem )
{
    // First, add the item
    HTREEITEM hFileItem = AddFileItem ( pFile, hParentTreeItem );
}

HTREEITEM ZCWorkspaceTreeCtrl::AddTypeItem( const CString    Name,
                                            int                IconIndex,
                                            HTREEITEM        hParentTreeItem    /*= NULL*/ )
{
    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent                = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage            = IconIndex;
    curTreeItem.item.iSelectedImage    = IconIndex;
    curTreeItem.item.pszText        = (char*)( (const char*)Name );
    curTreeItem.item.lParam            = (LPARAM)AddDataToSet( Name );        // Represent a selectable item
    curTreeItem.item.mask            = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem( &curTreeItem );
}

HTREEITEM ZCWorkspaceTreeCtrl::AddGroupItem( ZBWorkspaceGroupEntity* pGroup, HTREEITEM hParentTreeItem )
{
    if ( !pGroup )
    {
        return NULL;
    }

    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent                = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage            = _GroupTreeItem;
    curTreeItem.item.iSelectedImage    = _GroupTreeItem;
    curTreeItem.item.pszText        = (char*)( (const char*)pGroup->GetEntityName() );
    curTreeItem.item.lParam            = (LPARAM)AddDataToSet( pGroup );    // Represent a selectable item
    curTreeItem.item.mask            = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem( &curTreeItem );
}


HTREEITEM ZCWorkspaceTreeCtrl::AddFileItem( ZBWorkspaceFileEntity* pFile, HTREEITEM hParentTreeItem )
{
    if ( !pFile )
    {
        return NULL;
    }

    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent                = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage            = _AnyFileTreeItem;
    curTreeItem.item.iSelectedImage    = _AnyFileTreeItem;
    curTreeItem.item.pszText        = (char*)( (const char*)pFile->GetEntityName() );
    curTreeItem.item.lParam            = (LPARAM)AddDataToSet( pFile );    // Represent a selectable item
    curTreeItem.item.mask            = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem( &curTreeItem );
}

BOOL ZCWorkspaceTreeCtrl::ModifyItem( ZBWorkspaceEntity* pEntity, HTREEITEM hItem )
{
    if ( !pEntity )
    {
        return FALSE;
    }

    return SetItemText( hItem, (char*)( (const char*)pEntity->GetEntityName() ) );
}

void ZCWorkspaceTreeCtrl::AddGroup( ZBWorkspaceGroupEntity* pGroup, ZBWorkspaceGroupEntity* pParentGroup /*= NULL*/ )
{
    if ( !m_hRootWorkspaceEnv || !pGroup )
    {
        return;
    }

    HTREEITEM hParentTreeItem = m_hRootWorkspaceEnv;

    // Find the tree item for the parent
    if ( pParentGroup )
    {
        // Find the model
        _ZInternalWksTreeData* pData;
        pData = FindElementFromDataSet( pParentGroup );

        if ( pData )
        {
            // From item, in fact from root
            hParentTreeItem = FindItemData( pData, (HTREEITEM)NULL );
        }

        // If not found, set the root as parent
        if ( !hParentTreeItem )
        {
            hParentTreeItem = m_hRootWorkspaceEnv;
        }
    }

    // Insert the group in the tree
    HTREEITEM hGroupItem = AddGroupItem( pGroup, hParentTreeItem );

    if ( hGroupItem )
    {
        EnsureVisible( hGroupItem );
    }
}

void ZCWorkspaceTreeCtrl::RemoveGroup( ZBWorkspaceGroupEntity* pGroup )
{
    if ( !m_hRootWorkspaceEnv || !pGroup )
    {
        return;
    }

    _ZInternalWksTreeData* pData = FindElementFromDataSet( pGroup );

    if ( pData )
    {
        // From item, in fact from root
        HTREEITEM hItem = FindItemData( pData, (HTREEITEM)NULL );

        if ( hItem )
        {
            DeleteItem( hItem );
            DeleteElementFromDataSet( pGroup );
        }
    }
}

void ZCWorkspaceTreeCtrl::ModifyGroup( ZBWorkspaceGroupEntity* pGroup )
{
    ModifyEntity( pGroup );
}

void ZCWorkspaceTreeCtrl::AddFile( ZBWorkspaceFileEntity* pFile, ZBWorkspaceGroupEntity* pParentGroup )
{
    if ( !m_hRootWorkspaceEnv || !pFile || !pParentGroup )
    {
        return;
    }

    HTREEITEM hParentTreeItem = m_hRootWorkspaceEnv;

    // Find the tree item for the parent
    if ( pParentGroup )
    {
        // Find the model
        _ZInternalWksTreeData* pData;
        pData = FindElementFromDataSet( pParentGroup );

        if ( pData )
        {
            // From item, in fact from root
            hParentTreeItem = FindItemData( pData, (HTREEITEM)NULL );
        }

        // If not found, set the root as parent
        if ( !hParentTreeItem )
        {
            hParentTreeItem = m_hRootWorkspaceEnv;
        }
    }

    // Insert the file item in the tree
    HTREEITEM hFileItem = AddFileItem( pFile, hParentTreeItem );

    if ( hFileItem )
    {
        EnsureVisible( hFileItem );
    }
}

void ZCWorkspaceTreeCtrl::ModifyEntity( ZBWorkspaceEntity* pEntity )
{
    if ( !m_hRootWorkspaceEnv || !pEntity )
    {
        return;
    }

    _ZInternalWksTreeData* pData = FindElementFromDataSet( pEntity );

    if ( pData )
    {
        // From item, in fact from root
        HTREEITEM hItem = FindItemData( pData, (HTREEITEM)NULL );

        if ( hItem )
        {
            ModifyItem( pEntity, hItem );
        }
    }
}

void ZCWorkspaceTreeCtrl::RemoveFile( ZBWorkspaceFileEntity* pFile )
{
    if ( !m_hRootWorkspaceEnv || !pFile )
    {
        return;
    }

    _ZInternalWksTreeData* pData = FindElementFromDataSet( pFile );

    if ( pData )
    {
        // From item, in fact from root
        HTREEITEM hItem = FindItemData( pData, (HTREEITEM)NULL );

        if ( hItem )
        {
            DeleteItem( hItem );
            DeleteElementFromDataSet( pFile );
        }
    }
}

void ZCWorkspaceTreeCtrl::ModifyFile( ZBWorkspaceFileEntity* pFile )
{
    ModifyEntity( pFile );
}

ZBWorkspaceEntity* ZCWorkspaceTreeCtrl::GetSelectedEntity()
{
    return _GetEntity( GetSelectedItem() );
}

ZBWorkspaceEntity* ZCWorkspaceTreeCtrl::_GetEntity( HTREEITEM hItem )
{
    if ( hItem )
    {
        _ZInternalWksTreeData* pObj = (_ZInternalWksTreeData*)GetItemData( hItem );

        if ( pObj != NULL && pObj->m_dtp == _ZInternalWksTreeData::wktp_WorkspaceEnv )
        {
            return pObj->m_pWorkspaceEnv;
        }

        if ( pObj != NULL && pObj->m_dtp == _ZInternalWksTreeData::wktp_Group )
        {
            return pObj->m_pGroup;
        }

        if ( pObj != NULL && pObj->m_dtp == _ZInternalWksTreeData::wktp_File )
        {
            return pObj->m_pFile;
        }
    }

    return NULL;
}

ZBWorkspaceGroupEntity* ZCWorkspaceTreeCtrl::GetSelectedGroup()
{
    return _GetGroup( GetSelectedItem() );
}

ZBWorkspaceGroupEntity* ZCWorkspaceTreeCtrl::_GetGroup( HTREEITEM hItem )
{
    if ( hItem )
    {
        _ZInternalWksTreeData*    pObj = (_ZInternalWksTreeData*)GetItemData( hItem );

        if ( pObj != NULL && pObj->m_dtp == _ZInternalWksTreeData::wktp_Group )
        {
            return pObj->m_pGroup;
        }
    }

    return NULL;
}

ZBWorkspaceFileEntity* ZCWorkspaceTreeCtrl::GetSelectedFile()
{
    return _GetFile( GetSelectedItem() );
}

ZBWorkspaceFileEntity* ZCWorkspaceTreeCtrl::_GetFile( HTREEITEM hItem )
{
    if ( hItem )
    {
        _ZInternalWksTreeData*    pObj = (_ZInternalWksTreeData*)GetItemData( hItem );

        if ( pObj != NULL && pObj->m_dtp == _ZInternalWksTreeData::wktp_File )
        {
            return pObj->m_pFile;
        }
    }

    return NULL;
}

ZBWorkspaceGroupEntity* ZCWorkspaceTreeCtrl::GetSelectedOwnerGroup()
{
    return _GetOwnerGroup( GetSelectedItem() );
}

ZBWorkspaceGroupEntity* ZCWorkspaceTreeCtrl::_GetOwnerGroup( HTREEITEM hItem )
{
    if ( hItem )
    {
        ZBWorkspaceGroupEntity* pGroup = _GetGroup( hItem );

        if ( pGroup )
        {
            // If a parent defined
            if ( pGroup->GetParent() && ISA( pGroup->GetParent(), ZBWorkspaceGroupEntity ) )
            {
                return dynamic_cast<ZBWorkspaceGroupEntity*>( pGroup->GetParent() );
            }

            return pGroup;
        }

        // Now, try to check if a file is selected
        ZBWorkspaceFileEntity* pFile = _GetFile( hItem );

        if ( pFile && pFile->GetParent() && ISA( pFile->GetParent(), ZBWorkspaceGroupEntity ) )
        {
            return dynamic_cast<ZBWorkspaceGroupEntity*>( pFile->GetParent() );
        }
    }

    return NULL;
}

bool ZCWorkspaceTreeCtrl::IsRootSelected() const
{
    if ( GetSelectedItem() && ( GetSelectedItem() == GetRootItem() ) )
    {
        return true;
    }

    return false;
}

int ZCWorkspaceTreeCtrl::HasContextMenu( CWnd* pWnd, CPoint point )
{
    // Now display the right sub-menu
    int IdMenu = -1;
    UINT Flags;
    CPoint pt( point );
    ScreenToClient( &pt );

    HTREEITEM hItem = HitTest( pt, &Flags );

    if ( ( hItem != NULL ) && ( TVHT_ONITEM & Flags ) )
    {
        if ( hItem == GetRootItem() )
        {
            IdMenu = 0;
        }
        else if ( _GetGroup( hItem ) )
        {
            IdMenu = 1;
        }
        else if ( _GetFile( hItem ) )
        {
            IdMenu = 2;
        }
    }

    return IdMenu;
}

void ZCWorkspaceTreeCtrl::DisplayContextMenu( CWnd* pWnd, CPoint point )
{
    int IdMenu = HasContextMenu( pWnd, point );

    if ( IdMenu == -1 )
    {
        return;
    }

    CMenu* pPopup = m_SubMenu.GetSubMenu( IdMenu );
    ASSERT( pPopup != NULL );
    CWnd* pWndPopupOwner = this;
    
    while ( pWndPopupOwner->GetStyle() & WS_CHILD )
    {
        pWndPopupOwner = pWndPopupOwner->GetParent();
    }

    // And test the hit.
    UINT uFlags;
    CPoint pt( point );
    ScreenToClient( &pt );
    HTREEITEM hItem = HitTest( pt, &uFlags );

    if ( ( hItem != NULL ) && ( TVHT_ONITEM & uFlags ) )
    {
        Select( hItem, TVGN_CARET );

        pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                                point.x,
                                point.y,
                                pWndPopupOwner );
    }
}

void ZCWorkspaceTreeCtrl::OnContextMenu( CWnd* pWnd, CPoint point )
{
    DisplayContextMenu( pWnd, point );
}

void ZCWorkspaceTreeCtrl::OnItemExpanded( LPNMHDR pnmhdr, LRESULT *pLResult )
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pnmhdr;

    // Expand
    if ( pNMTreeView->action == 2 )
    {
        // Not the root item, only a simple group
        if ( pNMTreeView->itemNew.hItem != GetRootItem() )
        {
            TVITEM item            = { 0 };
            item.mask            = TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
            item.hItem            = pNMTreeView->itemNew.hItem;
            item.iImage            = _GroupOpenTreeItem;
            item.iSelectedImage    = _GroupOpenTreeItem;

            SetItem( &item );
        }
    }
    // Collapse
    else if ( pNMTreeView->action == 1 )
    {
        // Not the root item, only a simple group
        if ( pNMTreeView->itemNew.hItem != GetRootItem() )
        {
            TVITEM item            = { 0 };
            item.mask            = TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
            item.hItem            = pNMTreeView->itemNew.hItem;
            item.iImage            = _GroupTreeItem;
            item.iSelectedImage    = _GroupTreeItem;

            SetItem( &item );
        }
    }

    *pLResult = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Data set methods

_ZInternalWksTreeData::_ZInternalWksTreeData()
{
    m_dtp            = wktp_Unknown; 
    m_pWorkspaceEnv    = NULL;
    m_pGroup        = NULL;
    m_pFile            = NULL;

    m_Str.Empty();
}

_ZInternalWksTreeData::_ZInternalWksTreeData( ZBWorkspaceEnv* pWorkspaceEnv )
{
    m_dtp            = wktp_WorkspaceEnv; 
    m_pWorkspaceEnv    = pWorkspaceEnv;
    m_pGroup        = NULL;
    m_pFile            = NULL;

    m_Str.Empty();
}

_ZInternalWksTreeData::_ZInternalWksTreeData( ZBWorkspaceGroupEntity* pGroup )
{
    m_dtp            = wktp_Group; 
    m_pGroup        = pGroup;
    m_pWorkspaceEnv    = NULL;
    m_pFile            = NULL;

    m_Str.Empty();
}

_ZInternalWksTreeData::_ZInternalWksTreeData( ZBWorkspaceFileEntity* pFile )
{
    m_dtp            = wktp_File; 
    m_pFile            = pFile;
    m_pWorkspaceEnv    = NULL;
    m_pGroup        = NULL;

    m_Str.Empty();
}

_ZInternalWksTreeData::_ZInternalWksTreeData( CString Str )
{
    m_dtp            = wktp_String; 
    m_Str            = Str;
    m_pWorkspaceEnv    = NULL;
    m_pGroup        = NULL;
    m_pFile            = NULL;
}

_ZInternalWksTreeData::~_ZInternalWksTreeData()
{
    // In the destructor, just reset all values
    m_dtp            = wktp_Unknown; 
    m_pWorkspaceEnv    = NULL;
    m_pGroup        = NULL;
    m_pFile            = NULL;

    m_Str.Empty();
}

ZBWorkspaceGroupEntity* ZCWorkspaceTreeCtrl::GetFileBestGroup( const CString Filename ) const
{
    PSS_File file( Filename );
    CString ext = file.GetFileExt();

    // Check if there is a point to start the extension string
    if ( ext.GetAt( 0 ) == '.' )
    {
        ext = ext.Right( ext.GetLength() - 1 );
    }

    _ZInternalWksTreeDataIterator i( &m_DataSet );

    for ( _ZInternalWksTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalWksTreeData::wktp_Group && pElement->m_pGroup != NULL )
        {
            // Check if the group contains the filename extension
            if ( pElement->m_pGroup->ContainThisExtension( ext ) )
            {
                return pElement->m_pGroup;
            }
        }
    }

    return NULL;
}

ZBWorkspaceFileEntity* ZCWorkspaceTreeCtrl::GetFileEntity( const CString Filename ) const
{
    _ZInternalWksTreeDataIterator i( &m_DataSet );

    for ( _ZInternalWksTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalWksTreeData::wktp_File &&
             pElement->m_pFile->GetFilename().CompareNoCase( Filename ) == 0 )
        {
            return pElement->m_pFile;
        }
    }

    return NULL;
}

void ZCWorkspaceTreeCtrl::EmptyDataSet()
{
    _ZInternalWksTreeDataIterator i( &m_DataSet );

    for ( _ZInternalWksTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        delete pElement;
    }

    m_DataSet.RemoveAll();
}

_ZInternalWksTreeData* ZCWorkspaceTreeCtrl::FindElementFromDataSet( ZBWorkspaceEntity* pEntity )
{
    _ZInternalWksTreeDataIterator i( &m_DataSet );

    for ( _ZInternalWksTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( ( pElement->m_dtp == _ZInternalWksTreeData::wktp_WorkspaceEnv    && pElement->m_pWorkspaceEnv == pEntity )    ||
             ( pElement->m_dtp == _ZInternalWksTreeData::wktp_Group            && pElement->m_pGroup == pEntity )            ||
             ( pElement->m_dtp == _ZInternalWksTreeData::wktp_File            && pElement->m_pFile == pEntity ) )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalWksTreeData* ZCWorkspaceTreeCtrl::FindElementFromDataSet( ZBWorkspaceEnv* pWorkspaceEnv )
{
    _ZInternalWksTreeDataIterator i( &m_DataSet );

    for ( _ZInternalWksTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp            == _ZInternalWksTreeData::wktp_WorkspaceEnv &&
             pElement->m_pWorkspaceEnv    == pWorkspaceEnv )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalWksTreeData* ZCWorkspaceTreeCtrl::FindElementFromDataSet( ZBWorkspaceGroupEntity* pGroup )
{
    _ZInternalWksTreeDataIterator i( &m_DataSet );

    for ( _ZInternalWksTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalWksTreeData::wktp_Group && pElement->m_pGroup == pGroup )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalWksTreeData* ZCWorkspaceTreeCtrl::FindElementFromDataSet( ZBWorkspaceFileEntity* pFile )
{
    _ZInternalWksTreeDataIterator i( &m_DataSet );

    for ( _ZInternalWksTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalWksTreeData::wktp_File && pElement->m_pFile == pFile )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalWksTreeData* ZCWorkspaceTreeCtrl::FindElementFromDataSet( CString Str )
{
    _ZInternalWksTreeDataIterator i( &m_DataSet );

    for ( _ZInternalWksTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalWksTreeData::wktp_String && pElement->m_Str == Str )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalWksTreeData* ZCWorkspaceTreeCtrl::AddDataToSet( ZBWorkspaceEnv* pWorkspaceEnv )
{
    _ZInternalWksTreeData* pData = new _ZInternalWksTreeData( pWorkspaceEnv );
    m_DataSet.Add( pData );

    return pData;
}

_ZInternalWksTreeData* ZCWorkspaceTreeCtrl::AddDataToSet( ZBWorkspaceGroupEntity* pGroup )
{
    _ZInternalWksTreeData* pData = new _ZInternalWksTreeData( pGroup );
    m_DataSet.Add( pData );

    return pData;
}

_ZInternalWksTreeData* ZCWorkspaceTreeCtrl::AddDataToSet( ZBWorkspaceFileEntity* pFile )
{
    _ZInternalWksTreeData* pData = new _ZInternalWksTreeData( pFile );
    m_DataSet.Add( pData );

    return pData;
}

_ZInternalWksTreeData* ZCWorkspaceTreeCtrl::AddDataToSet( CString Str )
{
    _ZInternalWksTreeData* pData = new _ZInternalWksTreeData( Str );
    m_DataSet.Add( pData );

    return pData;
}

bool ZCWorkspaceTreeCtrl::DeleteElementFromDataSet( ZBWorkspaceGroupEntity* pGroup )
{
    _ZInternalWksTreeDataIterator i( &m_DataSet );

    for ( _ZInternalWksTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalWksTreeData::wktp_Group && pElement->m_pGroup == pGroup )
        {
            delete pElement;
            i.Remove();

            return true;
        }
    }

    return false;
}

bool ZCWorkspaceTreeCtrl::DeleteElementFromDataSet( ZBWorkspaceFileEntity* pFile )
{
    _ZInternalWksTreeDataIterator i( &m_DataSet );

    for ( _ZInternalWksTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalWksTreeData::wktp_File && pElement->m_pFile == pFile )
        {
            delete pElement;
            i.Remove();

            return true;
        }
    }

    return false;
}

bool ZCWorkspaceTreeCtrl::DeleteElementFromDataSet( CString Str )
{
    _ZInternalWksTreeDataIterator i( &m_DataSet );

    for ( _ZInternalWksTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalWksTreeData::wktp_String && pElement->m_Str == Str )
        {
            delete pElement;
            i.Remove();

            return true;
        }
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////
// ZCWorkspaceTreeCtrl menu commands

void ZCWorkspaceTreeCtrl::OnWksNewGroup()
{
    ZBWorkspaceGroupEntity* pGroup = GetSelectedGroup();

    // If the root is selected, set the group as the environment
    if ( IsRootSelected() )
    {
        pGroup = m_pWorkspaceEnv;
    }

    // If a group selected
    if ( pGroup != NULL )
    {
        ASSERT( m_pWorkspaceEnv != NULL );

        // Asks for the name
        ZVWorkspaceGroupNameDlg dlg( pGroup );

        if ( dlg.DoModal() == IDOK )
        {
            ZBWorkspaceGroupEntity* pNewGroup = m_pWorkspaceEnv->AddGroup( dlg.GetGroupName(),
                                                                           dlg.GetExtensions(),
                                                                           pGroup );

            if ( pNewGroup )
            {
                // Now, add the file from the tree
                ZCWorkspaceTreeCtrl::AddGroup( pNewGroup, pGroup );

                // Modified
                m_pWorkspaceEnv->SetModifiedFlag();
            }
        }
    }
}

void ZCWorkspaceTreeCtrl::OnWksDeleteGroup()
{
    if ( IsRootSelected() )
    {
        return;
    }

    ZBWorkspaceGroupEntity* pGroup = GetSelectedGroup();

    if ( pGroup != NULL )
    {
        ASSERT( m_pWorkspaceEnv != NULL );

        // Remove group from the workspace
        m_pWorkspaceEnv->RemoveGroup( pGroup );

        // Now delete the group name from the tree
        ZCWorkspaceTreeCtrl::RemoveGroup( pGroup );

        // Modified
        m_pWorkspaceEnv->SetModifiedFlag();
    }
}

void ZCWorkspaceTreeCtrl::OnWksRenameGroup()
{
    if ( IsRootSelected() )
    {
        return;
    }

    ZBWorkspaceGroupEntity* pGroup = GetSelectedGroup();

    if ( pGroup != NULL )
    {
        ASSERT( m_pWorkspaceEnv != NULL );

        ZVWorkspaceRenameGroupNameDlg dlg( pGroup->GetEntityName(),
                                           ( pGroup->GetParent() && ISA( pGroup->GetParent(), ZBWorkspaceGroupEntity ) ) ? dynamic_cast<ZBWorkspaceGroupEntity*>( pGroup->GetParent() ) : NULL );

        if ( dlg.DoModal() == IDOK )
        {
            pGroup->SetEntityName( dlg.GetGroupName() );

            // Now modify the group name
            ZCWorkspaceTreeCtrl::ModifyGroup( pGroup );

            // Modified
            m_pWorkspaceEnv->SetModifiedFlag();
        }
    }
}

void ZCWorkspaceTreeCtrl::OnWksAddFile()
{
    if ( GetSelectedGroup() != NULL || IsRootSelected() )
    {
        CString title;
        VERIFY( title.LoadString( IDS_WORKSPACE_FILEADD_T ) );

        // Set the "*.*" files filter
        CString strFilter;
        VERIFY( strFilter.LoadString( AFX_IDS_ALLFILTER ) );

        strFilter += (char)'\0';    // Next string please
        strFilter += _T( "*.*" );
        strFilter += (char)'\0';    // Last string

        PSS_FileDialog fileDialog( title, strFilter, 1 );

        if ( fileDialog.DoModal() == IDOK )
        {
            ASSERT( m_pWorkspaceEnv != NULL );

            // If the root is selected, then use addfile to project for inserting the file at the best place.
            if ( IsRootSelected() )
            {
                OnAddFileToProject( fileDialog.GetFileName() );
            }
            else
            {
                // Add file to the workspace
                ZBWorkspaceFileEntity* pFile = m_pWorkspaceEnv->AddFile( fileDialog.GetFileName(),
                                                                         GetSelectedGroup() );

                // Now, add the file from the tree
                ZCWorkspaceTreeCtrl::AddFile( pFile, GetSelectedGroup() );
            }

            // Modified
            m_pWorkspaceEnv->SetModifiedFlag();
        }
    }
}

void ZCWorkspaceTreeCtrl::OnWksDeleteFile()
{
    ZBWorkspaceFileEntity* pFile = GetSelectedFile();

    if ( pFile != NULL )
    {
        ASSERT( m_pWorkspaceEnv != NULL );

        // Remove file from the workspace
        m_pWorkspaceEnv->RemoveFile( pFile );

        // Modified
        m_pWorkspaceEnv->SetModifiedFlag();

        // Now, remove the file from the tree
        ZCWorkspaceTreeCtrl::RemoveFile( pFile );
    }
}

// Cette fonction est appelée lorsque l'utilisateur désire ouvrir un fichier associé au projet.
void ZCWorkspaceTreeCtrl::OnWksOpenFile()
{
    if ( GetSelectedFile() != NULL )
    {
        GetSelectedFile()->OpenFile();

        ASSERT( m_pWorkspaceEnv != NULL );

        // Modified
        m_pWorkspaceEnv->SetModifiedFlag();
    }
}

void ZCWorkspaceTreeCtrl::OnWksProperties()
{
    if ( GetSelectedEntity() != NULL )
    {
        if ( GetSelectedEntity()->DisplayProperties() )
        {
            ModifyEntity( GetSelectedEntity() );

            // Modified
            m_pWorkspaceEnv->SetModifiedFlag();
        }
    }
}

void ZCWorkspaceTreeCtrl::OnAddFileToProject( const CString Filename )
{
    ZBWorkspaceGroupEntity* pGroup = GetFileBestGroup( Filename );

    if ( pGroup )
    {
        ASSERT( m_pWorkspaceEnv != NULL );

        // Add file to the workspace
        ZBWorkspaceFileEntity* pFile = m_pWorkspaceEnv->AddFile( Filename, pGroup );

        // Modified
        m_pWorkspaceEnv->SetModifiedFlag();

        // Now, add the file from the tree
        ZCWorkspaceTreeCtrl::AddFile( pFile, pGroup );
    }
}

bool ZCWorkspaceTreeCtrl::CanAddCurrentFileToProject( const CString Filename )
{
    return ( !HasItems() || FileExist( Filename) ) ? false : true;
}

void ZCWorkspaceTreeCtrl::OnLButtonDblClk( UINT nFlags, CPoint point )
{
    // Open the file if it is a file
    ZCWorkspaceTreeCtrl::OnWksOpenFile();
}
