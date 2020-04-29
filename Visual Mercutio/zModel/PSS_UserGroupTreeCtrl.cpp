/****************************************************************************
 * ==> PSS_UserGroupTreeCtrl -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an user group tree controller                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UserGroupTreeCtrl.h"

// processsoft
#include "zBaseLib\zBaseLibRes.h"
#include "PSS_UserRoleEntity.h"
#include "PSS_ProcessGraphModelDoc.h"
#include "PSS_SelectUserGroupDlg.h"
#include "PSS_UserGroupObserverMsg.h"
#include "PSS_UserGroupInfoDlg.h"

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
// Global constants
//---------------------------------------------------------------------------
const int g_UserGroupRootTreeItem = 0;
const int g_UserGroupTreeItem     = 1;
const int g_UserRoleAdminTreeItem = 2;
const int g_UserRoleTreeItem      = 3;
//---------------------------------------------------------------------------
// PSS_UserGroupTreeCtrl::ITreeData
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::ITreeData::ITreeData() :
    CObject(),
    m_pGroup(NULL),
    m_pRole(NULL),
    m_Type(IE_DT_Unknown)
{}
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::ITreeData::ITreeData(PSS_UserGroupEntity* pGroup) :
    CObject(),
    m_pGroup(pGroup),
    m_pRole(NULL),
    m_Type(IE_DT_Group)
{}
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::ITreeData::ITreeData(PSS_UserRoleEntity* pRole) :
    CObject(),
    m_pGroup(NULL),
    m_pRole(pRole),
    m_Type(IE_DT_Role)
{}
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::ITreeData::ITreeData(const CString& str) :
    CObject(),
    m_pGroup(NULL),
    m_pRole(NULL),
    m_Type(IE_DT_String),
    m_Str(str)
{}
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::ITreeData::~ITreeData()
{}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UserGroupTreeCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(PSS_UserGroupTreeCtrl)
    ON_WM_CREATE()
    ON_WM_LBUTTONDBLCLK()
    ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_COLLAPSE_BRANCH, OnCollapseBranch)
    ON_COMMAND(ID_EXPAND_BRANCH, OnExpandBranch)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UserGroupTreeCtrl
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::PSS_UserGroupTreeCtrl(const CString& rootName, PSS_UserGroupEntity* pUserGroupRoot) :
    PSS_TreeCtrl(),
    m_pUserGroupRoot(pUserGroupRoot),
    m_hUserGroupRoot(NULL),
    m_RootName(rootName),
    m_HasBeenInitialized(false)
{}
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::~PSS_UserGroupTreeCtrl()
{
    // NOTE the fully qualified name is used here to avoid to call a pure virtual function during the destruction
    PSS_UserGroupTreeCtrl::Release();
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::Initialize(const CString& rootName, PSS_UserGroupEntity* pUserGroupRoot)
{
    m_pUserGroupRoot = pUserGroupRoot;
    m_RootName       = rootName;

    DestroyTree();
    LoadTree();
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::Release()
{
    DestroyTree();
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::Refresh()
{
    // save the state
    SaveCollapsedState();

    DestroyTree();
    LoadTree();

    // restore the previously saved state
    RestoreCollapsedStateToTreeCtrl();
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserGroupTreeCtrl::GetSelectedEntity()
{
    return GetEntity(GetSelectedItem());
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity* PSS_UserGroupTreeCtrl::GetSelectedGroup()
{
    return GetGroup(GetSelectedItem());
}
//---------------------------------------------------------------------------
PSS_UserRoleEntity* PSS_UserGroupTreeCtrl::GetSelectedRole()
{
    return GetRole(GetSelectedItem());
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity* PSS_UserGroupTreeCtrl::GetSelectedOwnerGroup()
{
    return GetOwnerGroup(GetSelectedItem());
}
//---------------------------------------------------------------------------
bool PSS_UserGroupTreeCtrl::IsRootSelected() const
{
    return (GetSelectedItem() && (GetSelectedItem() == GetRootItem()));
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::AddGroup(PSS_UserGroupEntity* pGroup, PSS_UserGroupEntity* pParentGroup)
{
    if (!m_hUserGroupRoot || !pGroup)
        return;

    HTREEITEM hParentTreeItem = m_hUserGroupRoot;

    // find the tree item for the parent
    if (pParentGroup)
    {
        // find the model
        ITreeData* pData = FindElementFromDataSet(pParentGroup);

        if (pData)
            hParentTreeItem = FindItemData(pData, HTREEITEM(NULL));

        // if not found, set the root as parent
        if (!hParentTreeItem)
            hParentTreeItem = m_hUserGroupRoot;
    }

    // insert the group in the tree
    AddGroupItem(pGroup, hParentTreeItem);

    // expand the parent
    ExpandBranch(hParentTreeItem);
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::RemoveGroup(PSS_UserGroupEntity* pGroup)
{
    if (!m_hUserGroupRoot || !pGroup)
        return;

    ITreeData* pData = FindElementFromDataSet(pGroup);

    if (pData)
    {
        // from item, in fact from root
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
            DeleteItem(hItem);
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::ModifyGroup(PSS_UserGroupEntity* pGroup)
{
    if (!m_hUserGroupRoot || !pGroup)
        return;

    ITreeData* pData = FindElementFromDataSet(pGroup);

    if (pData)
    {
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
            ModifyGroupItem(pGroup, hItem);
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::AddRole(PSS_UserRoleEntity* pRole, PSS_UserGroupEntity* pParentGroup)
{
    if (!m_hUserGroupRoot || !pRole || !pParentGroup)
        return;

    HTREEITEM hParentTreeItem = m_hUserGroupRoot;

    // find the tree item for the parent
    if (pParentGroup)
    {
        // find the model
        ITreeData* pData = FindElementFromDataSet(pParentGroup);

        if (pData)
            hParentTreeItem = FindItemData(pData, HTREEITEM(NULL));

        // if not found, set the root as parent
        if (!hParentTreeItem)
            hParentTreeItem = m_hUserGroupRoot;
    }

    // insert the file item in the tree
    AddRoleItem(pRole, hParentTreeItem);

    // expand the parent
    ExpandBranch(hParentTreeItem);
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::RemoveRole(PSS_UserRoleEntity* pRole)
{
    if (!m_hUserGroupRoot || !pRole)
        return;

    ITreeData* pData = FindElementFromDataSet(pRole);

    if (pData)
    {
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
            DeleteItem(hItem);
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::ModifyRole(PSS_UserRoleEntity* pRole)
{
    if (!m_hUserGroupRoot || !pRole)
        return;

    ITreeData* pData = FindElementFromDataSet(pRole);

    if (pData)
    {
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
            ModifyRoleItem(pRole, hItem);
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnUgpNewGroup()
{
    bool isSesterces = false;

    CFrameWnd* pWnd = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

    // check if sesterces is used
    if (pWnd)
    {
        CFrameWnd* pActiveFrame = pWnd->GetActiveFrame();

        if (pActiveFrame)
        {
            PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pActiveFrame->GetActiveDocument());

            if (pDoc)
                isSesterces = pDoc->GetIntegrateCostSimulation();
        }
    }

    PSS_UserGroupEntity* pGroup = GetSelectedGroup();

    // if a group selected
    if (pGroup)
    {
        PSS_Assert(m_pUserGroupRoot);

        // ask for the name
        PSS_UserGroupInfoDlg dlg(IDS_UGP_NEWGROUP_T, pGroup, _T(""), _T(""), 0, !isSesterces);

        if (dlg.DoModal() == IDOK)
        {
            PSS_UserGroupEntity* pNewGroup = m_pUserGroupRoot->AddGroup(dlg.GetName(),
                                                                        dlg.GetDescription(),
                                                                        dlg.GetCost(),
                                                                        pGroup);

            if (pNewGroup)
            {
                // add the file from the tree
                AddGroup(pNewGroup, pGroup);

                // modified
                m_pUserGroupRoot->SetModifiedFlag();
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnUgpDeleteGroup()
{
    if (IsRootSelected())
        return;

    PSS_UserGroupEntity* pGroup = GetSelectedGroup();

    if (pGroup && pGroup != m_pUserGroupRoot)
    {
        PSS_Assert(m_pUserGroupRoot);

        // remove group from the workspace
        m_pUserGroupRoot->RemoveGroup(pGroup);

        // delete the group name from the tree
        RemoveGroup(pGroup);

        // modified
        m_pUserGroupRoot->SetModifiedFlag();
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnUgpRenameGroup()
{
    if (IsRootSelected())
        return;

    bool isSesterces = false;

    CFrameWnd* pWnd = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

    // check if sesterces is used
    if (pWnd)
    {
        CFrameWnd* pActiveFrame = pWnd->GetActiveFrame();

        if (pActiveFrame)
        {
            PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pActiveFrame->GetActiveDocument());

            if (pDoc)
                isSesterces = pDoc->GetIntegrateCostSimulation();
        }
    }

    PSS_UserGroupEntity* pGroup = GetSelectedGroup();

    if (pGroup)
    {
        PSS_Assert(m_pUserGroupRoot);

        PSS_UserGroupEntity* pParent = dynamic_cast<PSS_UserGroupEntity*>(pGroup->GetParent());

        PSS_UserGroupInfoDlg dlg(IDS_UGP_RENAMEGROUP_T,
                                 pParent ? pParent : pGroup,
                                 pGroup->GetEntityName(),
                                 pGroup->GetEntityDescription(),
                                 pGroup->GetEntityCost(),
                                 !isSesterces);

        if (dlg.DoModal() == IDOK)
        {
            pGroup->SetEntityName(dlg.GetName());
            pGroup->SetEntityDescription(dlg.GetDescription());
            pGroup->SetEntityCost(dlg.GetCost());

            // modify the group name
            ModifyGroup(pGroup);

            // modified
            m_pUserGroupRoot->SetModifiedFlag();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnUgpAddRole()
{
    PSS_UserGroupEntity* pGroup = GetSelectedGroup();

    // if a group selected
    if (pGroup)
    {
        // ask for the name
        PSS_UserGroupInfoDlg dlg(IDS_UGP_NEWROLE_T, pGroup, _T(""), _T(""), 0, true);

        if (dlg.DoModal() == IDOK)
        {
            PSS_Assert(m_pUserGroupRoot);

            // add the role to the group
            PSS_UserRoleEntity* pRole = m_pUserGroupRoot->AddRole(dlg.GetName(), dlg.GetDescription(), pGroup);

            // modified
            m_pUserGroupRoot->SetModifiedFlag();

            // add the file from the tree
            AddRole(pRole, GetSelectedGroup());
        }
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnUgpDeleteRole()
{
    PSS_UserRoleEntity* pRole = GetSelectedRole();

    if (pRole)
    {
        PSS_Assert(m_pUserGroupRoot);

        // remove file from the workspace
        m_pUserGroupRoot->RemoveRole(pRole);

        // modified
        m_pUserGroupRoot->SetModifiedFlag();

        // remove the file from the tree
        RemoveRole(pRole);
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnUgpRenameRole()
{
    PSS_UserRoleEntity* pRole = GetSelectedRole();

    if (pRole)
    {
        PSS_Assert(m_pUserGroupRoot);

        PSS_UserGroupEntity* pParent = dynamic_cast<PSS_UserGroupEntity*>(pRole->GetParent());

        PSS_UserGroupInfoDlg dlg(IDS_UGP_RENAMEROLE_T,
                                 pParent ? pParent : m_pUserGroupRoot,
                                 pRole->GetEntityName(),
                                 pRole->GetEntityDescription(),
                                 0,
                                 true);

        if (dlg.DoModal() == IDOK)
        {
            pRole->SetEntityName(dlg.GetName());
            pRole->SetEntityDescription(dlg.GetDescription());

            // modify the role name
            ModifyRole(pRole);

            // modified
            m_pUserGroupRoot->SetModifiedFlag();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnUgpMove()
{
    PSS_UserEntity* pEntity = GetSelectedEntity();

    if (pEntity)
    {
        PSS_Assert(m_pUserGroupRoot);

        PSS_SelectUserGroupDlg dlg(IDS_UGP_MOVE_T, m_pUserGroupRoot, true, false);

        if (dlg.DoModal() == IDOK)
        {
            PSS_UserGroupEntity* pSelectedEntity = dynamic_cast<PSS_UserGroupEntity*>(dlg.GetSelectedUserEntity());

            // if we have selected an entity and if it is not the same
            if (pSelectedEntity && pSelectedEntity != pEntity)
            {
                // move the element and assign the new parent
                dynamic_cast<PSS_UserGroupEntity*>(dlg.GetSelectedUserEntity())->MoveEntity(pEntity);

                // modified
                m_pUserGroupRoot->SetModifiedFlag();

                // refresh the tree
                Refresh();
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnUgpProperties()
{
    bool isSesterces = false;

    CFrameWnd* pWnd = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

    // check if sesterces is used
    if (pWnd)
    {
        CFrameWnd* pActiveFrame = pWnd->GetActiveFrame();

        if (pActiveFrame)
        {
            PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pActiveFrame->GetActiveDocument());

            if (pDoc)
                isSesterces = pDoc->GetIntegrateCostSimulation();
        }
    }

    PSS_UserEntity* pEntity = GetSelectedEntity();

    if (pEntity)
    {
        PSS_UserGroupEntity* pGroup = GetSelectedGroup();
        PSS_Assert(m_pUserGroupRoot);

        PSS_UserGroupEntity* pParent = dynamic_cast<PSS_UserGroupEntity*>(pEntity->GetParent());

        PSS_UserGroupInfoDlg dlg(IDS_UGP_PROPERTY_T,
                                 pParent ? pParent : m_pUserGroupRoot,
                                 pEntity->GetEntityName(),
                                 pEntity->GetEntityDescription(),
                                 pGroup ? pGroup->GetEntityCost() : 0,
                                 pGroup ? !isSesterces : true,
                                 true);

        if (dlg.DoModal() == IDOK)
        {
            pEntity->SetEntityDescription(dlg.GetDescription());

            if (pGroup)
                pGroup->SetEntityCost(dlg.GetCost());

            // modified
            m_pUserGroupRoot->SetModifiedFlag();
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_UserGroupTreeCtrl::CanUgpNewGroup()
{
    return GetSelectedGroup();
}
//---------------------------------------------------------------------------
bool PSS_UserGroupTreeCtrl::CanUgpDeleteGroup()
{
    return (GetSelectedGroup() && GetSelectedGroup() != m_pUserGroupRoot);
}
//---------------------------------------------------------------------------
bool PSS_UserGroupTreeCtrl::CanUgpRenameGroup()
{
    return GetSelectedGroup();
}
//---------------------------------------------------------------------------
bool PSS_UserGroupTreeCtrl::CanUgpAddRole()
{
    return GetSelectedGroup();
}
//---------------------------------------------------------------------------
bool PSS_UserGroupTreeCtrl::CanUgpDeleteRole()
{
    return GetSelectedRole();
}
//---------------------------------------------------------------------------
bool PSS_UserGroupTreeCtrl::CanUgpRenameRole()
{
    return GetSelectedRole();
}
//---------------------------------------------------------------------------
bool PSS_UserGroupTreeCtrl::CanUgpMove()
{
    return (GetSelectedEntity() || IsRootSelected());
}
//---------------------------------------------------------------------------
bool PSS_UserGroupTreeCtrl::CanUgpProperties()
{
    return (GetSelectedEntity() || IsRootSelected());
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_UserGroupObserverMsg* pObserverMsg = dynamic_cast<PSS_UserGroupObserverMsg*>(pMsg);

    if (pObserverMsg)
        switch (dynamic_cast<PSS_UserGroupObserverMsg*>(pMsg)->GetMessageID())
        {
            case g_InitUserGroup:
            {
                PSS_UserGroupEntity* pGroup = dynamic_cast<PSS_UserGroupEntity*>(pObserverMsg->GetEntity());
                Initialize(pObserverMsg->GetRootName(), pGroup);
                break;
            }

            case g_CloseUserGroup:
                DestroyTree();
                break;
        }
}
//---------------------------------------------------------------------------
int PSS_UserGroupTreeCtrl::HasContextMenu(CWnd* pWnd, const CPoint& point)
{
    CPoint pt(point);
    ScreenToClient(&pt);

    UINT      flags;
    HTREEITEM hItem  = HitTest(pt, &flags);
    int       idMenu = -1;

    // show the right sub-menu
    if (hItem && (TVHT_ONITEM & flags))
        if (hItem == GetRootItem())
            idMenu = 0;
        else
        if (GetGroup(hItem) == m_pUserGroupRoot)
            idMenu = 1;
        else
        if (GetGroup(hItem))
            idMenu = 2;
        else
        if (GetRole(hItem))
            idMenu = 3;

    return idMenu;
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::ShowContextMenu(CWnd* pWnd, const CPoint& point)
{
    const int idMenu = HasContextMenu(pWnd, point);

    if (idMenu == -1)
        return;

    CMenu* pPopup = m_SubMenu.GetSubMenu(idMenu);
    PSS_Assert(pPopup);

    CWnd* pWndPopupOwner = this;

    while (pWndPopupOwner->GetStyle() & WS_CHILD)
        pWndPopupOwner = pWndPopupOwner->GetParent();

    CPoint pt(point);
    ScreenToClient(&pt);

    UINT      flags;
    HTREEITEM hItem = HitTest(pt, &flags);

    // check the hit
    if (hItem && (TVHT_ONITEM & flags))
    {
        Select(hItem, TVGN_CARET);
        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_UserGroupTreeCtrl::DestroyWindow()
{
    DestroyTree();

    return CWnd::DestroyWindow();
}
//---------------------------------------------------------------------------
int PSS_UserGroupTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_TreeCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    LoadTree();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // show the properties
    OnUgpProperties();
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
    ShowContextMenu(pWnd, point);
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pnmhdr;
    *pLResult                = TRUE;
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnCollapseBranch()
{
    CollapseBranch(GetSelectedItem(), TRUE);
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::OnExpandBranch()
{
    ExpandBranch(GetSelectedItem(), TRUE);
}
//---------------------------------------------------------------------------
CObject* PSS_UserGroupTreeCtrl::GetDragObject(HTREEITEM dragItem)
{
    ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(dragItem));

    if (pObj)
        switch (pObj->m_Type)
        {
            case ITreeData::IE_DT_Group: return pObj->m_pGroup;
            case ITreeData::IE_DT_Role:  return pObj->m_pRole;
        }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::CreateTree()
{
    if (m_HasBeenInitialized)
        return;

    VERIFY(m_SubMenu.LoadMenu(IDR_USERGROUP_SUBMENUS));

    // set styles
    HasButtons();
    HasLines();
    LinesAtRoot();
    ShowSelectionAlways();

    // load images
    LoadImageList(IDB_IL_USERGROUP, 17, 1, RGB(255, 255, 255));

    m_HasBeenInitialized = true;
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::LoadTree()
{
    // create the tree. NOTE this function will do nothing if already created
    CreateTree();

    // no user group, do nothing
    if (!m_pUserGroupRoot)
        return;

    m_hUserGroupRoot = AddTypeItem(m_RootName, g_UserGroupRootTreeItem);

    ProcessGroup(m_pUserGroupRoot, m_hUserGroupRoot);

    // expand the root
    ExpandRoot(TRUE);
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::DestroyTree()
{
    if (::IsWindow(GetSafeHwnd()))
    {
        DeleteAllItems();
    }

    // Empty the data set first
    EmptyDataSet();
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::EmptyDataSet()
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        delete pElement;

    m_DataSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::ProcessGroup(PSS_UserGroupEntity* pGroup, HTREEITEM hParentTreeItem)
{
    bool isMessenger = true;

    CFrameWnd* pWnd = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

    // check if sesterces is used
    if (pWnd)
    {
        CFrameWnd* pActiveFrame = pWnd->GetActiveFrame();

        if (pActiveFrame)
        {
            PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pActiveFrame->GetActiveDocument());

            if (pDoc && !pDoc->GetUseWorkflow())
                isMessenger = false;
        }
    }

    // add the item
    HTREEITEM hGroupItem = AddGroupItem(pGroup, hParentTreeItem);

    if (pGroup->ContainEntity())
    {
        const int count = pGroup->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            PSS_UserEntity* pEntity = pGroup->GetEntityAt(i);

            if (!pEntity)
                continue;

            PSS_UserGroupEntity* pGroupEntity = dynamic_cast<PSS_UserGroupEntity*>(pEntity);

            if (pGroupEntity)
                ProcessGroup(pGroupEntity, hGroupItem);

            if (isMessenger)
            {
                PSS_UserRoleEntity* pRoleEntity = dynamic_cast<PSS_UserRoleEntity*>(pEntity);

                if (pRoleEntity)
                    ProcessRole(pRoleEntity, hGroupItem);
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupTreeCtrl::ProcessRole(PSS_UserRoleEntity* pRole, HTREEITEM hParentTreeItem)
{
    // add the item
    HTREEITEM hFileItem = AddRoleItem(pRole, hParentTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_UserGroupTreeCtrl::AddTypeItem(const CString& name, int iconIndex, HTREEITEM hParentTreeItem)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)name);
    curTreeItem.item.lParam         = LPARAM(AddDataToSet(name));
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_UserGroupTreeCtrl::AddGroupItem(PSS_UserGroupEntity* pGroup, HTREEITEM hParentTreeItem)
{
    if (!pGroup)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = g_UserGroupTreeItem;
    curTreeItem.item.iSelectedImage = g_UserGroupTreeItem;
    curTreeItem.item.pszText        = (char*)((const char*)pGroup->GetEntityName());
    curTreeItem.item.lParam         = LPARAM(AddDataToSet(pGroup));
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_UserGroupTreeCtrl::AddRoleItem(PSS_UserRoleEntity* pRole, HTREEITEM hParentTreeItem)
{
    if (!pRole)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = g_UserRoleTreeItem;
    curTreeItem.item.iSelectedImage = g_UserRoleTreeItem;
    curTreeItem.item.pszText        = (char*)((const char*)pRole->GetEntityName());
    curTreeItem.item.lParam         = LPARAM(AddDataToSet(pRole));
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
BOOL PSS_UserGroupTreeCtrl::ModifyGroupItem(PSS_UserGroupEntity* pGroup, HTREEITEM hItem)
{
    if (!pGroup)
        return FALSE;

    return SetItemText(hItem, (char*)((const char*)pGroup->GetEntityName()));
}
//---------------------------------------------------------------------------
BOOL PSS_UserGroupTreeCtrl::ModifyRoleItem(PSS_UserRoleEntity* pRole, HTREEITEM hItem)
{
    if (!pRole)
        return FALSE;

    return SetItemText(hItem, (char*)((const char*)pRole->GetEntityName()));
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserGroupTreeCtrl::GetEntity(HTREEITEM hItem)
{
    if (hItem)
    {
        ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(hItem));

        if (pObj)
            switch (pObj->m_Type)
            {
                case ITreeData::IE_DT_Group: return pObj->m_pGroup;
                case ITreeData::IE_DT_Role:  return pObj->m_pRole;
            }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity* PSS_UserGroupTreeCtrl::GetGroup(HTREEITEM hItem)
{
    if (hItem)
    {
        ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(hItem));

        if (pObj && pObj->m_Type == ITreeData::IE_DT_Group)
            return pObj->m_pGroup;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_UserRoleEntity* PSS_UserGroupTreeCtrl::GetRole(HTREEITEM hItem)
{
    if (hItem)
    {
        ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(hItem));

        if (pObj && pObj->m_Type == ITreeData::IE_DT_Role)
            return pObj->m_pRole;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity* PSS_UserGroupTreeCtrl::GetOwnerGroup(HTREEITEM hItem)
{
    if (hItem)
    {
        PSS_UserGroupEntity* pGroup = GetGroup(hItem);

        if (pGroup)
        {
            PSS_UserGroupEntity* pParent = dynamic_cast<PSS_UserGroupEntity*>(pGroup->GetParent());

            // if a parent defined
            if (pParent)
                return pParent;

            return pGroup;
        }

        // check if a file is selected
        PSS_UserRoleEntity* pRole = GetRole(hItem);

        if (pRole)
        {
            PSS_UserGroupEntity* pParent = dynamic_cast<PSS_UserGroupEntity*>(pRole->GetParent());

            if (pParent)
                return pParent;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::ITreeData* PSS_UserGroupTreeCtrl::FindElementFromDataSet(PSS_UserGroupEntity* pGroup)
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Type == ITreeData::IE_DT_Group && pElement->m_pGroup == pGroup)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::ITreeData* PSS_UserGroupTreeCtrl::FindElementFromDataSet(PSS_UserRoleEntity* pRole)
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Type == ITreeData::IE_DT_Role && pElement->m_pRole == pRole)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::ITreeData* PSS_UserGroupTreeCtrl::FindElementFromDataSet(const CString& str)
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Type == ITreeData::IE_DT_String && pElement->m_Str == str)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::ITreeData* PSS_UserGroupTreeCtrl::AddDataToSet(PSS_UserGroupEntity* pGroup)
{
    std::unique_ptr<ITreeData> pData(new ITreeData(pGroup));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::ITreeData* PSS_UserGroupTreeCtrl::AddDataToSet(PSS_UserRoleEntity* pRole)
{
    std::unique_ptr<ITreeData> pData(new ITreeData(pRole));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
PSS_UserGroupTreeCtrl::ITreeData* PSS_UserGroupTreeCtrl::AddDataToSet(const CString& str)
{
    std::unique_ptr<ITreeData> pData(new ITreeData(str));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
