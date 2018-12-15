// ZCUserGroupTreeCtrl.cpp : implementation file

#include "stdafx.h"
#include "ZCUserGroupTreeCtrl.h"

#include "ZBUserRoleEntity.h"
#include "ZVSelectUserGroupDlg.h"
#include "ZBUserGroupObserverMsg.h"

#include "zBaseLib\zBaseLibRes.h"
#include "ZVUserGroupInfoDlg.h"

// RS-MODIF 12.12.04 we need doc informations
#include "zModel\ProcGraphModelDoc.h"

#ifdef _DEBUG
#include "zFormsRes\zFormsRes.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 11 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (en commentaires)

const int _UserGroupRootTreeItem    = 0;
const int _UserGroupTreeItem        = 1;
const int _UserRoleAdminTreeItem    = 2;
const int _UserRoleTreeItem            = 3;

/////////////////////////////////////////////////////////////////////////////
// ZCUserGroupTreeCtrl

BEGIN_MESSAGE_MAP( ZCUserGroupTreeCtrl, ZITreeCtrl )
    //{{AFX_MSG_MAP(ZCUserGroupTreeCtrl)
    ON_WM_CREATE()
    ON_WM_LBUTTONDBLCLK()
    ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_COLLAPSE_BRANCH, OnCollapseBranch)
    ON_COMMAND(ID_EXPAND_BRANCH, OnExpandBranch)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZCUserGroupTreeCtrl::ZCUserGroupTreeCtrl( const CString            RootName /*= _T( "" )*/,
                                          ZBUserGroupEntity*    pUserGroupRoot /*= NULL*/ )
    : m_RootName            ( RootName ),
      m_pUserGroupRoot        ( pUserGroupRoot ),
      m_hUserGroupRoot        ( NULL ),
      m_HasBeenInitialized    ( false )
{
}

ZCUserGroupTreeCtrl::~ZCUserGroupTreeCtrl()
{
    // JMR-MODIF - le 23 août 2005 - Ajout de l'appel à DestroyTree dans le destructeur.
    Release();
}

void ZCUserGroupTreeCtrl::Initialize( const CString RootName, ZBUserGroupEntity* pUserGroupRoot )
{
    m_RootName            = RootName;
    m_pUserGroupRoot    = pUserGroupRoot;

    DestroyTree();
    LoadTree();
}

// JMR-MODIF - Le le 23 août 2005 - Ajout de la fonction Release pour permettre un nettoyage de la mémoire.
void ZCUserGroupTreeCtrl::Release()
{
    DestroyTree();
}

void ZCUserGroupTreeCtrl::Refresh()
{
    // First, save the state
    SaveCollapsedState();

    DestroyTree();
    LoadTree();

    // And then, restore the previously saved state
    RestoreCollapsedStateToTreeCtrl();
}

BOOL ZCUserGroupTreeCtrl::DestroyWindow()
{
    DestroyTree();
    
    return CWnd::DestroyWindow();
}

/////////////////////////////////////////////////////////////////////////////
// ZCUserGroupTreeCtrl message handlers

int ZCUserGroupTreeCtrl::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
    if ( ZITreeCtrl::OnCreate( lpCreateStruct ) == -1 )
    {
        return -1;
    }

    LoadTree();

    return 0;
}

void ZCUserGroupTreeCtrl::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
    if ( pMsg && ISA( pMsg, ZBUserGroupObserverMsg ) )
    {
        switch ( dynamic_cast<ZBUserGroupObserverMsg*>( pMsg )->GetMessageID() )
        {
            case UM_INITUSERGROUP:
            {
                if ( dynamic_cast<ZBUserGroupObserverMsg*>( pMsg )->GetpEntity() &&
                     ISA( dynamic_cast<ZBUserGroupObserverMsg*>( pMsg )->GetpEntity(), ZBUserGroupEntity ) )
                {
                    ZBUserGroupEntity* pGroup =
                        dynamic_cast<ZBUserGroupEntity*>( dynamic_cast<ZBUserGroupObserverMsg*>( pMsg )->GetpEntity() );

                    Initialize( dynamic_cast<ZBUserGroupObserverMsg*>( pMsg )->GetRootName(), pGroup );
                }
                break;
            }

            case UM_CLOSEUSERGROUP:
            {
                DestroyTree();
                break;
            }
        }
    }
}

void ZCUserGroupTreeCtrl::OnContextMenu( CWnd* pWnd, CPoint point )
{
    DisplayContextMenu( pWnd, point );
}

void ZCUserGroupTreeCtrl::OnItemExpanded( LPNMHDR pnmhdr, LRESULT *pLResult )
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pnmhdr;

    *pLResult = TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// Commandes de menus

void ZCUserGroupTreeCtrl::OnUgpNewGroup()
{
    ZBUserGroupEntity* pGroup = GetSelectedGroup();

    // RS-MODIF 12.12.04 test if we use sesterces
    bool IsSesterces = false;

    ZDProcessGraphModelDoc* test =
        (ZDProcessGraphModelDoc*)( (CFrameWnd*)AfxGetMainWnd() )->GetActiveFrame()->GetActiveDocument();

    if ( test != NULL )
    {
        if ( test->GetIntegrateCostSimulation() ) IsSesterces = true;
    }

    // If a group selected
    if ( pGroup != NULL )
    {
        ASSERT( m_pUserGroupRoot != NULL );

        // Asks for the name
        // RS-MODIF 12.12.04
        ZVUserGroupInfoDlg dlg( IDS_UGP_NEWGROUP_T,
                                pGroup,
                                _T( "" ),
                                _T( "" ),
                                0,                // Name, description, cost
                                !IsSesterces );    // is not a role,but if sesterces is not activated we deactivate

        if ( dlg.DoModal() == IDOK )
        {
            ZBUserGroupEntity* pNewGroup = m_pUserGroupRoot->AddGroup( dlg.GetName(),
                                                                       dlg.GetDescription(),
                                                                       dlg.GetCost(),
                                                                       pGroup );

            if ( pNewGroup )
            {
                // Now, add the file from the tree
                ZCUserGroupTreeCtrl::AddGroup( pNewGroup, pGroup );

                // Modified
                m_pUserGroupRoot->SetModifiedFlag();
            }
        }
    }
}

void ZCUserGroupTreeCtrl::OnUgpDeleteGroup()
{
    if ( IsRootSelected() )
    {
        return;
    }

    ZBUserGroupEntity* pGroup = GetSelectedGroup();

    if ( pGroup != NULL && pGroup != m_pUserGroupRoot )
    {
        ASSERT( m_pUserGroupRoot != NULL );

        // Remove group from the workspace
        m_pUserGroupRoot->RemoveGroup( pGroup );

        // Now delete the group name from the tree
        ZCUserGroupTreeCtrl::RemoveGroup( pGroup );

        // Modified
        m_pUserGroupRoot->SetModifiedFlag();
    }
}

// Cette fonction permet de renommer un groupe, et mets à jour tous les objets concernés.
void ZCUserGroupTreeCtrl::OnUgpRenameGroup()
{
    if ( IsRootSelected() )
    {
        return;
    }

    // RS-MODIF 12.12.04 test if we use sesterces
    bool IsSesterces = false;

    ZDProcessGraphModelDoc* test =
        (ZDProcessGraphModelDoc*)( (CFrameWnd*)AfxGetMainWnd() )->GetActiveFrame()->GetActiveDocument();

    if ( test != NULL )
    {
        if ( test->GetIntegrateCostSimulation() )
        {
            IsSesterces = true;
        }
    }

    ZBUserGroupEntity* pGroup = GetSelectedGroup();

    if ( pGroup != NULL )
    {
        ASSERT( m_pUserGroupRoot != NULL );

        ZVUserGroupInfoDlg dlg( IDS_UGP_RENAMEGROUP_T, 
                                ( pGroup->GetParent() && ISA( pGroup->GetParent(), ZBUserGroupEntity ) ) ? dynamic_cast<ZBUserGroupEntity*>( pGroup->GetParent() ) : pGroup,
                                pGroup->GetEntityName(), 
                                pGroup->GetEntityDescription(), 
                                pGroup->GetEntityCost(),
                                // RS-MODIF 12.12.04 only if sesterces activated
                                !IsSesterces );

        if ( dlg.DoModal() == IDOK )
        {
            pGroup->SetEntityName( dlg.GetName() );
            pGroup->SetEntityDescription( dlg.GetDescription() );
            pGroup->SetEntityCost( dlg.GetCost() );

            // Now modify the group name
            ZCUserGroupTreeCtrl::ModifyGroup( pGroup );

            // Modified
            m_pUserGroupRoot->SetModifiedFlag();
        }
    }
}

void ZCUserGroupTreeCtrl::OnUgpAddRole()
{
    ZBUserGroupEntity* pGroup = GetSelectedGroup();

    // If a group selected
    if ( pGroup != NULL )
    {
        // Asks for the name
        ZVUserGroupInfoDlg dlg( IDS_UGP_NEWROLE_T,
                                pGroup, 
                                _T( "" ),
                                _T( "" ),
                                0,        // Name, description, cost
                                true );    // Is a role

        if ( dlg.DoModal() == IDOK )
        {
            ASSERT( m_pUserGroupRoot != NULL );

            // Add the role to the group
            ZBUserRoleEntity* pRole = m_pUserGroupRoot->AddRole( dlg.GetName(), dlg.GetDescription(), pGroup );

            // Modified
            m_pUserGroupRoot->SetModifiedFlag();

            // Now, add the file from the tree
            ZCUserGroupTreeCtrl::AddRole( pRole, GetSelectedGroup() );
        }
    }
}

void ZCUserGroupTreeCtrl::OnUgpDeleteRole()
{
    ZBUserRoleEntity* pRole = GetSelectedRole();

    if ( pRole != NULL )
    {
        ASSERT( m_pUserGroupRoot != NULL );

        // Remove file from the workspace
        m_pUserGroupRoot->RemoveRole( pRole );

        // Modified
        m_pUserGroupRoot->SetModifiedFlag();

        // Now, remove the file from the tree
        ZCUserGroupTreeCtrl::RemoveRole( pRole );
    }
}

void ZCUserGroupTreeCtrl::OnUgpRenameRole()
{
    ZBUserRoleEntity* pRole = GetSelectedRole();

    if ( pRole != NULL )
    {
        ASSERT( m_pUserGroupRoot != NULL );

        ZVUserGroupInfoDlg dlg( IDS_UGP_RENAMEROLE_T, 
                                ( pRole->GetParent() && ISA( pRole->GetParent(), ZBUserGroupEntity ) ) ? dynamic_cast<ZBUserGroupEntity*>( pRole->GetParent() ) : m_pUserGroupRoot,
                                pRole->GetEntityName(),
                                pRole->GetEntityDescription(),
                                0,
                                true ); // Is a role

        if ( dlg.DoModal() == IDOK )
        {
            pRole->SetEntityName( dlg.GetName() );
            pRole->SetEntityDescription( dlg.GetDescription() );

            // Now modify the role name
            ZCUserGroupTreeCtrl::ModifyRole( pRole );

            // Modified
            m_pUserGroupRoot->SetModifiedFlag();
        }
    }
}

void ZCUserGroupTreeCtrl::OnUgpMove()
{
    ZBUserEntity* pEntity = GetSelectedEntity();

    if ( pEntity != NULL )
    {
        // JMR-MODIF - Le 27 février 2006 - La ligne ci-dessous ne sert à rien => Supprimée.
//        ZBUserGroupEntity* pGroup = GetSelectedGroup();

        ASSERT( m_pUserGroupRoot != NULL );

        ZVSelectUserGroupDlg dlg( IDS_UGP_MOVE_T,
                                  m_pUserGroupRoot,
                                  true,                // AllowGroupSelection 
                                  false );            // AllowRoleSelection

        if ( dlg.DoModal() == IDOK )
        {
            // If we have selected an entity
            // and if it is not the same
            if ( dlg.GetSelectedUserEntity() && 
                 dlg.GetSelectedUserEntity() != pEntity &&
                 ISA( dlg.GetSelectedUserEntity(), ZBUserGroupEntity ) )
            {
                // Move the element
                // Assigns the new parent
                dynamic_cast<ZBUserGroupEntity*>(dlg.GetSelectedUserEntity())->MoveEntity( pEntity );

                // Modified
                m_pUserGroupRoot->SetModifiedFlag();

                // Refresh the tree
                Refresh();
            }
        }
    }
}

void ZCUserGroupTreeCtrl::OnUgpProperties()
{
    ZBUserEntity* pEntity = GetSelectedEntity();

    // RS-MODIF 12.12.04 test if we use sesterces
    bool IsSesterces = false;

    ZDProcessGraphModelDoc* test =
        (ZDProcessGraphModelDoc*)( (CFrameWnd*)AfxGetMainWnd() )->GetActiveFrame()->GetActiveDocument();

    if ( test != NULL )
    {
        if ( test->GetIntegrateCostSimulation() )
        {
            IsSesterces = true;
        }
    }

    if ( pEntity != NULL )
    {
        ZBUserGroupEntity* pGroup = GetSelectedGroup();
        ASSERT( m_pUserGroupRoot != NULL );

        ZVUserGroupInfoDlg dlg( IDS_UGP_PROPERTY_T,
                                ( pEntity->GetParent() && ISA( pEntity->GetParent(), ZBUserGroupEntity ) ) ? dynamic_cast<ZBUserGroupEntity*>( pEntity->GetParent() ) : m_pUserGroupRoot,
                                pEntity->GetEntityName(),
                                pEntity->GetEntityDescription(),
                                ( pGroup != NULL ) ? pGroup->GetEntityCost() : 0,
                                // RS-MODIF 12.12.04, is not a role only if it is a group and sesterces activated
                                ( pGroup != NULL ) ? !IsSesterces : true,
                                //( pGroup != NULL ) ? false : true,    // If it is a role
                                true );                                    // ModifyMode

        if ( dlg.DoModal() == IDOK )
        {
            pEntity->SetEntityDescription( dlg.GetDescription() );

            if ( pGroup != NULL )
            {
                pGroup->SetEntityCost( dlg.GetCost() );
            }

            // Modified
            m_pUserGroupRoot->SetModifiedFlag();
        }
    }
}

void ZCUserGroupTreeCtrl::OnCollapseBranch()
{
    CollapseBranch( GetSelectedItem(), TRUE );
}

void ZCUserGroupTreeCtrl::OnExpandBranch()
{
    ExpandBranch( GetSelectedItem(), TRUE );
}

void ZCUserGroupTreeCtrl::OnLButtonDblClk( UINT nFlags, CPoint point )
{
    // Display the properties
    ZCUserGroupTreeCtrl::OnUgpProperties();
}

void ZCUserGroupTreeCtrl::EmptyDataSet()
{
    _ZInternalUserGroupTreeDataIterator i( &m_DataSet );

    for ( _ZInternalUserGroupTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        delete pElement;
    }

    m_DataSet.RemoveAll();
}

void ZCUserGroupTreeCtrl::CreateTree()
{
    if ( m_HasBeenInitialized == false )
    {
        VERIFY( m_SubMenu.LoadMenu( IDR_USERGROUP_SUBMENUS ) );

        // Sets styles
        HasButtons();
        HasLines();
        LinesAtRoot();
        ShowSelectionAlways();

        // Load images
        LoadImageList( IDB_IL_USERGROUP, 17, 1, RGB( 255, 255, 255 ) );

        m_HasBeenInitialized = true;
    }
}

void ZCUserGroupTreeCtrl::LoadTree()
{
    // Call the create tree function first,
    // in fact this function is executed only one time for initializing
    // correctly the control
    CreateTree();

    // No user group, do nothing
    if ( !m_pUserGroupRoot )
    {
        return;
    }

    m_hUserGroupRoot = AddTypeItem ( m_RootName, _UserGroupRootTreeItem );

    ProcessGroup( m_pUserGroupRoot, m_hUserGroupRoot );

    // Expand the root
    ExpandRoot( TRUE );
}

void ZCUserGroupTreeCtrl::DestroyTree()
{
    if ( ::IsWindow( GetSafeHwnd() ) )
    {
        DeleteAllItems();
    }

    // Empty the data set first
    EmptyDataSet();
}

void ZCUserGroupTreeCtrl::ProcessGroup( ZBUserGroupEntity* pGroup, HTREEITEM hParentTreeItem )
{
    // RS-MODIF 20.12.04 test if we use Messenger
    bool IsMessenger = true;

    ZDProcessGraphModelDoc* test =
        (ZDProcessGraphModelDoc*)( (CFrameWnd*)AfxGetMainWnd() )->GetActiveFrame()->GetActiveDocument();

    if ( test != NULL )
    {
        if ( !test->GetUseWorkflow() )
        {
            IsMessenger = false;
        }
    }

    // First, add the item
    HTREEITEM hGroupItem = AddGroupItem ( pGroup, hParentTreeItem );

    if ( pGroup->ContainEntity() )
    {
        int Count = pGroup->GetEntityCount();

        for ( int i = 0; i < Count; ++i )
        {
            ZBUserEntity* pEntity = pGroup->GetEntityAt( i );

            if ( !pEntity )
            {
                continue;
            }

            if ( ISA( pEntity, ZBUserGroupEntity ) )
            {
                ProcessGroup( dynamic_cast<ZBUserGroupEntity*>( pEntity ), hGroupItem );
            }

            // RS-MODIF 20.12.04 only if Messenger roles are displayed
            //if (ISA(pEntity,ZBUserRoleEntity))
            if ( ISA( pEntity, ZBUserRoleEntity ) && IsMessenger )
            {
                ProcessRole( dynamic_cast<ZBUserRoleEntity*>( pEntity ), hGroupItem );
            }
        }
    }
}

void ZCUserGroupTreeCtrl::ProcessRole( ZBUserRoleEntity* pRole, HTREEITEM hParentTreeItem )
{
    // First, add the item
    HTREEITEM hFileItem = AddRoleItem ( pRole, hParentTreeItem );
}

HTREEITEM ZCUserGroupTreeCtrl::AddTypeItem ( const CString Name, int IconIndex, HTREEITEM hParentTreeItem /*= NULL*/ )
{
    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent                = hParentTreeItem; 
    curTreeItem.hInsertAfter        = TVI_LAST ;
    curTreeItem.item.iImage            = IconIndex;
    curTreeItem.item.iSelectedImage    = IconIndex;
    curTreeItem.item.pszText        = (char*)( (const char*)Name );
    curTreeItem.item.lParam            = (LPARAM)AddDataToSet( Name );    // Represent a selectable item
    curTreeItem.item.mask            = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem( &curTreeItem );
}

HTREEITEM ZCUserGroupTreeCtrl::AddGroupItem( ZBUserGroupEntity* pGroup, HTREEITEM hParentTreeItem )
{
    if ( !pGroup )
    {
        return NULL;
    }

    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent                = hParentTreeItem; 
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage            = _UserGroupTreeItem;
    curTreeItem.item.iSelectedImage    = _UserGroupTreeItem;
    curTreeItem.item.pszText        = (char*)( (const char*)pGroup->GetEntityName() );
    curTreeItem.item.lParam            = (LPARAM)AddDataToSet( pGroup );    // Represent a selectable item
    curTreeItem.item.mask            = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem( &curTreeItem );
}

BOOL ZCUserGroupTreeCtrl::ModifyGroupItem ( ZBUserGroupEntity* pGroup, HTREEITEM hItem )
{
    if ( !pGroup )
    {
        return FALSE;
    }

    return SetItemText( hItem, (char*)( (const char*)pGroup->GetEntityName() ) );
}

HTREEITEM ZCUserGroupTreeCtrl::AddRoleItem ( ZBUserRoleEntity* pRole, HTREEITEM hParentTreeItem )
{
    if ( !pRole )
    {
        return NULL;
    }

    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent                = hParentTreeItem; 
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage            = _UserRoleTreeItem;
    curTreeItem.item.iSelectedImage    = _UserRoleTreeItem;
    curTreeItem.item.pszText        = (char*)( (const char*)pRole->GetEntityName() );
    curTreeItem.item.lParam            = (LPARAM)AddDataToSet( pRole );    // Represent a selectable item
    curTreeItem.item.mask            = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem( &curTreeItem );
}

BOOL ZCUserGroupTreeCtrl::ModifyRoleItem ( ZBUserRoleEntity* pRole, HTREEITEM hItem )
{
    if ( !pRole )
    {
        return FALSE;
    }

    return SetItemText( hItem, (char*)( (const char*)pRole->GetEntityName() ) );
}

void ZCUserGroupTreeCtrl::AddGroup( ZBUserGroupEntity* pGroup, ZBUserGroupEntity* pParentGroup /*= NULL*/ )
{
    if ( !m_hUserGroupRoot || !pGroup )
    {
        return;
    }

    HTREEITEM hParentTreeItem = m_hUserGroupRoot;

    // Find the tree item for the parent
    if ( pParentGroup )
    {
        // Find the model
        _ZInternalUserGroupTreeData* pData;
        pData = FindElementFromDataSet( pParentGroup );

        if ( pData )
        {
            // From item, in fact from root
            hParentTreeItem = FindItemData( pData, (HTREEITEM)NULL );
        }

        // If not found, set the root as parent
        if ( !hParentTreeItem )
        {
            hParentTreeItem = m_hUserGroupRoot;
        }
    }

    // Insert the group in the tree
    AddGroupItem( pGroup, hParentTreeItem );

    // Expand the parent. Unless, if he has no childs, they are not visible
    ExpandBranch( hParentTreeItem );
}

void ZCUserGroupTreeCtrl::RemoveGroup( ZBUserGroupEntity* pGroup )
{
    if ( !m_hUserGroupRoot || !pGroup )
    {
        return;
    }

    _ZInternalUserGroupTreeData* pData = FindElementFromDataSet( pGroup );

    if ( pData )
    {
        // From item, in fact from root
        HTREEITEM hItem = FindItemData( pData, NULL );

        if ( hItem )
        {
            DeleteItem( hItem );
        }
    }
}

void ZCUserGroupTreeCtrl::ModifyGroup( ZBUserGroupEntity* pGroup )
{
    if ( !m_hUserGroupRoot || !pGroup )
    {
        return;
    }

    _ZInternalUserGroupTreeData* pData = FindElementFromDataSet( pGroup );

    if ( pData )
    {
        // From item, in fact from root
        HTREEITEM hItem = FindItemData( pData, NULL );

        if ( hItem )
        {
            ModifyGroupItem( pGroup, hItem );
        }
    }
}

void ZCUserGroupTreeCtrl::AddRole( ZBUserRoleEntity* pRole, ZBUserGroupEntity* pParentGroup )
{
    if ( !m_hUserGroupRoot || !pRole || !pParentGroup )
    {
        return;
    }

    HTREEITEM hParentTreeItem = m_hUserGroupRoot;

    // Find the tree item for the parent
    if ( pParentGroup )
    {
        // Find the model
        _ZInternalUserGroupTreeData* pData;
        pData = FindElementFromDataSet( pParentGroup );

        if ( pData )
        {
            hParentTreeItem = FindItemData( pData, (HTREEITEM)NULL ); // From item, in fact from root
        }

        // If not found, set the root as parent
        if ( !hParentTreeItem )
        {
            hParentTreeItem = m_hUserGroupRoot;
        }
    }

    // Insert the file item in the tree
    AddRoleItem( pRole, hParentTreeItem );

    // Expand the parent. Unless, if he has no childs, they are not visible
    ExpandBranch( hParentTreeItem );
}

void ZCUserGroupTreeCtrl::RemoveRole( ZBUserRoleEntity* pRole )
{
    if ( !m_hUserGroupRoot || !pRole )
    {
        return;
    }

    _ZInternalUserGroupTreeData* pData = FindElementFromDataSet( pRole );

    if ( pData )
    {
        // From item, in fact from root
        HTREEITEM hItem = FindItemData( pData, NULL );

        if ( hItem )
        {
            DeleteItem( hItem );
        }
    }
}

void ZCUserGroupTreeCtrl::ModifyRole( ZBUserRoleEntity* pRole )
{
    if ( !m_hUserGroupRoot || !pRole )
    {
        return;
    }

    _ZInternalUserGroupTreeData* pData = FindElementFromDataSet( pRole );

    if ( pData )
    {
        // From item, in fact from root
        HTREEITEM hItem = FindItemData( pData, NULL );

        if ( hItem )
        {
            ModifyRoleItem( pRole, hItem );
        }
    }
}

ZBUserEntity* ZCUserGroupTreeCtrl::GetSelectedEntity()
{
    return _GetEntity( GetSelectedItem() );
}

ZBUserEntity* ZCUserGroupTreeCtrl::_GetEntity( HTREEITEM hItem )
{
    if ( hItem )
    {
        _ZInternalUserGroupTreeData* pObj = (_ZInternalUserGroupTreeData*)GetItemData( hItem );

        if ( pObj != NULL && pObj->m_dtp == _ZInternalUserGroupTreeData::wktp_Group )
        {
            return pObj->m_pGroup;
        }

        if ( pObj != NULL && pObj->m_dtp == _ZInternalUserGroupTreeData::wktp_Role )
        {
            return pObj->m_pRole;
        }
    }

    return NULL;
}

ZBUserGroupEntity* ZCUserGroupTreeCtrl::GetSelectedGroup()
{
    return _GetGroup( GetSelectedItem() );
}

ZBUserGroupEntity* ZCUserGroupTreeCtrl::_GetGroup( HTREEITEM hItem )
{
    if ( hItem )
    {
        _ZInternalUserGroupTreeData* pObj = (_ZInternalUserGroupTreeData*)GetItemData( hItem );

        if ( pObj != NULL && pObj->m_dtp == _ZInternalUserGroupTreeData::wktp_Group )
        {
            return pObj->m_pGroup;
        }
    }

    return NULL;
}

ZBUserRoleEntity* ZCUserGroupTreeCtrl::GetSelectedRole()
{
    return _GetRole( GetSelectedItem() );
}

ZBUserRoleEntity* ZCUserGroupTreeCtrl::_GetRole( HTREEITEM hItem )
{
    if ( hItem )
    {
        _ZInternalUserGroupTreeData* pObj = (_ZInternalUserGroupTreeData*)GetItemData( hItem );

        if ( pObj != NULL && pObj->m_dtp == _ZInternalUserGroupTreeData::wktp_Role )
        {
            return pObj->m_pRole;
        }
    }

    return NULL;
}

ZBUserGroupEntity* ZCUserGroupTreeCtrl::GetSelectedOwnerGroup()
{
    return _GetOwnerGroup( GetSelectedItem() );
}

ZBUserGroupEntity* ZCUserGroupTreeCtrl::_GetOwnerGroup( HTREEITEM hItem )
{
    if ( hItem )
    {
        ZBUserGroupEntity* pGroup = _GetGroup( hItem );

        if ( pGroup )
        {
            // If a parent defined
            if ( pGroup->GetParent() && ISA( pGroup->GetParent(), ZBUserGroupEntity ) )
            {
                return dynamic_cast<ZBUserGroupEntity*>( pGroup->GetParent() );
            }

            return pGroup;
        }

        // Now, try to check if a file is selected
        ZBUserRoleEntity* pRole = _GetRole( hItem );

        if ( pRole && pRole->GetParent() && ISA( pRole->GetParent(), ZBUserGroupEntity ) )
        {
            return dynamic_cast<ZBUserGroupEntity*>( pRole->GetParent() );
        }
    }

    return NULL;
}

bool ZCUserGroupTreeCtrl::IsRootSelected() const
{
    if ( GetSelectedItem() && ( GetSelectedItem() == GetRootItem() ) )
    {
        return true;
    }

    return false;
}

int ZCUserGroupTreeCtrl::HasContextMenu( CWnd* pWnd, CPoint point )
{
    // Now display the right sub-menu
    int        IdMenu = -1;
    UINT    Flags;
    CPoint    pt        ( point );
    ScreenToClient    ( &pt );

    HTREEITEM hItem = HitTest( pt, &Flags );

    if ( ( hItem != NULL ) && ( TVHT_ONITEM & Flags ) )
    {
        if ( hItem == GetRootItem() )
        {
            IdMenu = 0;
        }
        else if ( _GetGroup( hItem ) == m_pUserGroupRoot )
        {
            IdMenu = 1;
        }
        else if ( _GetGroup( hItem ) )
        {
            IdMenu = 2;
        }
        else if ( _GetRole( hItem ) )
        {
            IdMenu = 3;
        }
    }

    return IdMenu;
}

void ZCUserGroupTreeCtrl::DisplayContextMenu( CWnd* pWnd, CPoint point )
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
    UINT    uFlags;
    CPoint    pt        ( point );
    ScreenToClient    ( &pt );
    HTREEITEM hItem = HitTest( pt, &uFlags );

    if ( ( hItem != NULL ) && ( TVHT_ONITEM & uFlags ) )
    {
        Select( hItem, TVGN_CARET );
        pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner );
    }
}

CObject* ZCUserGroupTreeCtrl::GetDragObject( HTREEITEM DragItem )
{
    _ZInternalUserGroupTreeData* pObj = (_ZInternalUserGroupTreeData*)GetItemData( DragItem );

    if ( pObj != NULL && pObj->m_dtp == _ZInternalUserGroupTreeData::wktp_Group )
    {
        return pObj->m_pGroup;
    }
    else if ( pObj != NULL && pObj->m_dtp == _ZInternalUserGroupTreeData::wktp_Role )
    {
        return pObj->m_pRole;
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////
// Data set methods

_ZInternalUserGroupTreeData::_ZInternalUserGroupTreeData()
{
    m_dtp        = wktp_Unknown; 
    m_pGroup    = NULL;
    m_pRole        = NULL;

    m_Str.Empty();
}

_ZInternalUserGroupTreeData::_ZInternalUserGroupTreeData( ZBUserGroupEntity* pGroup )
{
    m_dtp        = wktp_Group; 
    m_pGroup    = pGroup;
    m_pRole        = NULL;

    m_Str.Empty();
}

_ZInternalUserGroupTreeData::_ZInternalUserGroupTreeData( ZBUserRoleEntity* pRole )
{
    m_dtp        = wktp_Role; 
    m_pRole        = pRole;
    m_pGroup    = NULL;

    m_Str.Empty();
}

_ZInternalUserGroupTreeData::_ZInternalUserGroupTreeData( CString Str )
{
    m_dtp        = wktp_String; 
    m_Str        = Str;
    m_pGroup    = NULL;
    m_pRole        = NULL;
}

_ZInternalUserGroupTreeData::~_ZInternalUserGroupTreeData()
{
    // In the destructor, just reset all values
    m_dtp        = wktp_Unknown; 
    m_pGroup    = NULL;
    m_pRole        = NULL;

    m_Str.Empty();
}

_ZInternalUserGroupTreeData* ZCUserGroupTreeCtrl::FindElementFromDataSet( ZBUserGroupEntity* pGroup )
{
    _ZInternalUserGroupTreeDataIterator i( &m_DataSet );

    for ( _ZInternalUserGroupTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalUserGroupTreeData::wktp_Group && pElement->m_pGroup == pGroup )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalUserGroupTreeData* ZCUserGroupTreeCtrl::FindElementFromDataSet( ZBUserRoleEntity* pRole )
{
    _ZInternalUserGroupTreeDataIterator i( &m_DataSet );

    for ( _ZInternalUserGroupTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalUserGroupTreeData::wktp_Role && pElement->m_pRole == pRole )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalUserGroupTreeData* ZCUserGroupTreeCtrl::FindElementFromDataSet( CString Str )
{
    _ZInternalUserGroupTreeDataIterator i( &m_DataSet );

    for ( _ZInternalUserGroupTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_dtp == _ZInternalUserGroupTreeData::wktp_String && pElement->m_Str == Str )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalUserGroupTreeData* ZCUserGroupTreeCtrl::AddDataToSet( ZBUserGroupEntity* pGroup )
{
    _ZInternalUserGroupTreeData* pData = new _ZInternalUserGroupTreeData( pGroup );
    m_DataSet.Add( pData );

    return pData;
}

_ZInternalUserGroupTreeData* ZCUserGroupTreeCtrl::AddDataToSet( ZBUserRoleEntity* pRole )
{
    _ZInternalUserGroupTreeData* pData = new _ZInternalUserGroupTreeData( pRole );
    m_DataSet.Add( pData );

    return pData;
}

_ZInternalUserGroupTreeData* ZCUserGroupTreeCtrl::AddDataToSet( CString Str )
{
    _ZInternalUserGroupTreeData* pData = new _ZInternalUserGroupTreeData( Str );
    m_DataSet.Add( pData );

    return pData;
}

bool ZCUserGroupTreeCtrl::CanUgpNewGroup()
{
    return ( GetSelectedGroup() != NULL ) ? true : false;
}

bool ZCUserGroupTreeCtrl::CanUgpDeleteGroup()
{
    return ( GetSelectedGroup() != NULL && GetSelectedGroup() != m_pUserGroupRoot ) ? true : false;
}

bool ZCUserGroupTreeCtrl::CanUgpRenameGroup()
{
    return ( GetSelectedGroup() != NULL ) ? true : false;
}

bool ZCUserGroupTreeCtrl::CanUgpAddRole()
{
    return ( GetSelectedGroup() != NULL ) ? true : false;
}

bool ZCUserGroupTreeCtrl::CanUgpDeleteRole()
{
    return ( GetSelectedRole() != NULL ) ? true : false;
}

bool ZCUserGroupTreeCtrl::CanUgpRenameRole()
{
    return ( GetSelectedRole() != NULL ) ? true : false;
}

bool ZCUserGroupTreeCtrl::CanUgpMove()
{
    return ( GetSelectedEntity() != NULL || IsRootSelected() ) ? true : false;
}

bool ZCUserGroupTreeCtrl::CanUgpProperties()
{
    return ( GetSelectedEntity() != NULL || IsRootSelected() ) ? true : false;
}
