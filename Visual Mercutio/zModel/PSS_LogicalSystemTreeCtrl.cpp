/****************************************************************************
 * ==> PSS_LogicalSystemTreeCtrl -------------------------------------------*
 ****************************************************************************
 * Description : Provides a logical system tree controller                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LogicalSystemTreeCtrl.h"

// processsoft
#include "zBaseLib\zBaseLibRes.h"
#include "PSS_LogicalSystemEntity.h"
#include "ZVSelectLogicalSystemDlg.h"
#include "PSS_LogicalSystemObserverMsg.h"
#include "PSS_LogicalSystemInfoDlg.h"

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
// Global constants
//---------------------------------------------------------------------------
const int g_LogicalSystemRootTreeItem = 0;
const int g_LogicalSystemTreeItem     = 1;
//---------------------------------------------------------------------------
// PSS_LogicalSystemTreeCtrl::ITreeData
//---------------------------------------------------------------------------
PSS_LogicalSystemTreeCtrl::ITreeData::ITreeData() :
    CObject(),
    m_pLogicalSystem(NULL),
    m_Type(IE_DT_Unknown)
{}
//---------------------------------------------------------------------------
PSS_LogicalSystemTreeCtrl::ITreeData::ITreeData(PSS_LogicalSystemEntity* pLogicalSystem) :
    CObject(),
    m_pLogicalSystem(pLogicalSystem),
    m_Type(IE_DT_LogicalSystem)
{}
//---------------------------------------------------------------------------
PSS_LogicalSystemTreeCtrl::ITreeData::ITreeData(const CString& str) :
    CObject(),
    m_pLogicalSystem(NULL),
    m_Type(IE_DT_String),
    m_Str(str)
{}
//---------------------------------------------------------------------------
PSS_LogicalSystemTreeCtrl::ITreeData::~ITreeData()
{}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_LogicalSystemTreeCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(PSS_LogicalSystemTreeCtrl)
    ON_WM_CREATE()
    ON_WM_LBUTTONDBLCLK()
    ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_COLLAPSE_BRANCH, OnCollapseBranch)
    ON_COMMAND(ID_EXPAND_BRANCH, OnExpandBranch)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_LogicalSystemTreeCtrl
//---------------------------------------------------------------------------
PSS_LogicalSystemTreeCtrl::PSS_LogicalSystemTreeCtrl(const CString& rootName, PSS_LogicalSystemEntity* pLogicalSystemRoot) :
    PSS_TreeCtrl(),
    m_pLogicalSystemRoot(pLogicalSystemRoot),
    m_hUserGroupRoot(NULL),
    m_RootName(rootName),
    m_HasBeenInitialized(false)
{}
//---------------------------------------------------------------------------
PSS_LogicalSystemTreeCtrl::~PSS_LogicalSystemTreeCtrl()
{}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::Initialize(const CString& rootName, PSS_LogicalSystemEntity* pLogicalSystemRoot)
{
    m_pLogicalSystemRoot = pLogicalSystemRoot;
    m_RootName           = rootName;

    DestroyTree();
    LoadTree();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::Release()
{
    DestroyTree();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::Refresh()
{
    // save the state
    SaveCollapsedState();

    DestroyTree();
    LoadTree();

    // restore the previously saved state
    RestoreCollapsedStateToTreeCtrl();
}
//---------------------------------------------------------------------------
PSS_SystemEntity* PSS_LogicalSystemTreeCtrl::GetSelectedSystemEntity()
{
    return GetSystemEntity(GetSelectedItem());
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity* PSS_LogicalSystemTreeCtrl::GetSelectedLogicalSystem()
{
    return GetLogicalSystem(GetSelectedItem());
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity* PSS_LogicalSystemTreeCtrl::GetSelectedLogicalSystemOwner()
{
    return GetOwnerSystem(GetSelectedItem());
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemTreeCtrl::IsRootSelected() const
{
    HTREEITEM hItem = GetSelectedItem();
    return (hItem && (hItem == GetRootItem()));
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::AddLogicalSystem(PSS_LogicalSystemEntity* pLogicalSystem,
                                                 PSS_LogicalSystemEntity* pParentLogicalSystem)
{
    if (!m_hUserGroupRoot || !pLogicalSystem)
        return;

    HTREEITEM hParentTreeItem = m_hUserGroupRoot;

    // find the tree item for the parent
    if (pParentLogicalSystem)
    {
        // find the model
        ITreeData* pData = FindElementFromDataSet(pParentLogicalSystem);

        if (pData)
            hParentTreeItem = FindItemData(pData, HTREEITEM(NULL));

        // if not found, set the root as parent
        if (!hParentTreeItem)
            hParentTreeItem = m_hUserGroupRoot;
    }

    // insert the group in the tree
    AddLogicalSystemItem(pLogicalSystem, hParentTreeItem);

    // expand the parent
    ExpandBranch(hParentTreeItem);
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::RemoveLogicalSystem(PSS_LogicalSystemEntity* pLogicalSystem)
{
    if (!m_hUserGroupRoot || !pLogicalSystem)
        return;

    ITreeData* pData = FindElementFromDataSet(pLogicalSystem);

    if (pData)
    {
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
            DeleteItem(hItem);
    }
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::ModifyLogicalSystem(PSS_LogicalSystemEntity* pLogicalSystem)
{
    if (!m_hUserGroupRoot || !pLogicalSystem)
        return;

    ITreeData* pData = FindElementFromDataSet(pLogicalSystem);

    if (pData)
    {
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
            ModifyLogicalSystemItem(pLogicalSystem, hItem);
    }
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::OnNewLogicalSystem()
{
    PSS_LogicalSystemEntity* pLogicalSystem = GetSelectedLogicalSystem();

    // if a group selected
    if (pLogicalSystem)
    {
        ASSERT(m_pLogicalSystemRoot);

        // asks for the name
        PSS_LogicalSystemInfoDlg dlg(IDS_NEW_LOGICALSYSTEM_T, pLogicalSystem);

        if (dlg.DoModal() == IDOK)
        {
            PSS_LogicalSystemEntity* pNewGroup = m_pLogicalSystemRoot->AddSystem(dlg.GetName(),
                                                                                 dlg.GetDescription(),
                                                                                 pLogicalSystem);

            if (pNewGroup)
            {
                // add the system to the tree
                AddLogicalSystem(pNewGroup, pLogicalSystem);

                // modified
                m_pLogicalSystemRoot->SetModifiedFlag();
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::OnDeleteLogicalSystem()
{
    if (IsRootSelected())
        return;

    PSS_LogicalSystemEntity* pLogicalSystem = GetSelectedLogicalSystem();

    if (pLogicalSystem && pLogicalSystem != m_pLogicalSystemRoot)
    {
        ASSERT(m_pLogicalSystemRoot);

        // remove system from the workspace
        m_pLogicalSystemRoot->RemoveSystem(pLogicalSystem);

        // delete the system name from the tree
        RemoveLogicalSystem(pLogicalSystem);

        // modified
        m_pLogicalSystemRoot->SetModifiedFlag();
    }
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::OnRenameLogicalSystem()
{
    if (IsRootSelected())
        return;

    PSS_LogicalSystemEntity* pLogicalSystem = GetSelectedLogicalSystem();

    if (pLogicalSystem)
    {
        ASSERT(m_pLogicalSystemRoot);

        PSS_LogicalSystemEntity* pParent = dynamic_cast<PSS_LogicalSystemEntity*>(pLogicalSystem->GetParent());

        PSS_LogicalSystemInfoDlg dlg(IDS_RENAME_LOGICALSYSTEM_T,
                                     pParent ? pParent : pLogicalSystem,
                                     pLogicalSystem->GetEntityName(),
                                     pLogicalSystem->GetEntityDescription());

        if (dlg.DoModal() == IDOK)
        {
            pLogicalSystem->SetEntityName(dlg.GetName());
            pLogicalSystem->SetEntityDescription(dlg.GetDescription());

            // modify the group name
            ModifyLogicalSystem(pLogicalSystem);

            // modified
            m_pLogicalSystemRoot->SetModifiedFlag();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::OnMoveLogicalSystem()
{
    PSS_LogicalSystemEntity* pSystem = GetSelectedLogicalSystem();

    if (pSystem)
    {
        ASSERT(m_pLogicalSystemRoot);

        ZVSelectLogicalSystemDlg dlg(IDS_LGS_MOVE_T, m_pLogicalSystemRoot);

        if (dlg.DoModal() == IDOK)
        {
            PSS_LogicalSystemEntity* pSelectedEntity = dynamic_cast<PSS_LogicalSystemEntity*>(dlg.GetSelectedSystemEntity());

            // if an entity was selected, and if it's not the same
            if (pSelectedEntity && pSelectedEntity != pSystem)
            {
                // move the element and assign the new parent
                pSelectedEntity->MoveSystem(pSystem);

                // modified
                m_pLogicalSystemRoot->SetModifiedFlag();

                // refresh the tree
                Refresh();
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::OnLogicalSystemProperties()
{
    PSS_SystemEntity* pEntity = GetSelectedSystemEntity();

    if (pEntity)
    {
        PSS_LogicalSystemEntity* pLogicalSystem = GetSelectedLogicalSystem();
        ASSERT(m_pLogicalSystemRoot);

        PSS_LogicalSystemEntity* pParent = dynamic_cast<PSS_LogicalSystemEntity*>(pEntity->GetParent());

        PSS_LogicalSystemInfoDlg dlg(IDS_LOGICALSYSTEM_PROPERTY_T,
                                     pParent ? pParent : m_pLogicalSystemRoot,
                                     pEntity->GetEntityName(),
                                     pEntity->GetEntityDescription(),
                                     true);

        if (dlg.DoModal() == IDOK)
        {
            if (pLogicalSystem)
                pLogicalSystem->SetEntityDescription(dlg.GetDescription());

            // modified
            m_pLogicalSystemRoot->SetModifiedFlag();
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemTreeCtrl::CanNewLogicalSystem()
{
    return GetSelectedLogicalSystem();
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemTreeCtrl::CanDeleteLogicalSystem()
{
    return (GetSelectedLogicalSystem() && GetSelectedLogicalSystem() != m_pLogicalSystemRoot);
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemTreeCtrl::CanRenameLogicalSystem()
{
    return GetSelectedLogicalSystem();
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemTreeCtrl::CanLogicalSystemProperties()
{
    return (GetSelectedSystemEntity() || IsRootSelected());
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_LogicalSystemObserverMsg* pLogicalSystemMsg = dynamic_cast<PSS_LogicalSystemObserverMsg*>(pMsg);

    if (pLogicalSystemMsg)
        switch (pLogicalSystemMsg->GetMessageID())
        {
            case g_InitLogicalSystem:
            {
                PSS_LogicalSystemEntity* pLogicalSystem = dynamic_cast<PSS_LogicalSystemEntity*>(pLogicalSystemMsg->GetEntity());

                if (pLogicalSystem)
                    Initialize(pLogicalSystemMsg->GetRootName(), pLogicalSystem);

                break;
            }

            case g_CloseLogicalSystem:
                DestroyTree();
                break;
        }
}
//---------------------------------------------------------------------------
int PSS_LogicalSystemTreeCtrl::HasContextMenu(CWnd* pWnd, const CPoint& point)
{
    CPoint pt(point);
    ScreenToClient(&pt);

    UINT      flags;
    HTREEITEM hItem  =  HitTest(pt, &flags);
    int       idMenu = -1;

    // show the right sub-menu
    if (hItem && (TVHT_ONITEM & flags))
        if (hItem == GetRootItem())
            idMenu = 0;
        else
        if (GetSystemEntity(hItem) == m_pLogicalSystemRoot)
            idMenu = 1;
        else
        if (GetSystemEntity(hItem))
            idMenu = 2;

    return idMenu;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::ShowContextMenu(CWnd* pWnd, const CPoint& point)
{
    const int idMenu = HasContextMenu(pWnd, point);

    if (idMenu == -1)
        return;

    CMenu* pPopup = m_SubMenu.GetSubMenu(idMenu);
    ASSERT(pPopup);

    CWnd* pWndPopupOwner = this;

    while (pWndPopupOwner->GetStyle() & WS_CHILD)
        pWndPopupOwner = pWndPopupOwner->GetParent();

    CPoint pt(point);
    ScreenToClient(&pt);

    // test the hit
    UINT      flags;
    HTREEITEM hItem = HitTest(pt, &flags);

    if (hItem && (TVHT_ONITEM & flags))
    {
        Select(hItem, TVGN_CARET);
        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_LogicalSystemTreeCtrl::DestroyWindow()
{
    DestroyTree();

    return CWnd::DestroyWindow();
}
//---------------------------------------------------------------------------
int PSS_LogicalSystemTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_TreeCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    LoadTree();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // show the properties
    OnLogicalSystemProperties();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
    ShowContextMenu(pWnd, point);
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::OnItemExpanded(LPNMHDR pnmhdr, LRESULT* pLResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pnmhdr;
    *pLResult                = TRUE;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::OnCollapseBranch()
{
    CollapseBranch(GetSelectedItem(), TRUE);
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::OnExpandBranch()
{
    ExpandBranch(GetSelectedItem(), TRUE);
}
//---------------------------------------------------------------------------
CObject* PSS_LogicalSystemTreeCtrl::GetDragObject(HTREEITEM dragItem)
{
    ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(dragItem));

    if (pObj && pObj->m_Type == ITreeData::IE_DT_LogicalSystem)
        return pObj->m_pLogicalSystem;

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::CreateTree()
{
    if (m_HasBeenInitialized)
        return;

    VERIFY(m_SubMenu.LoadMenu(IDR_LOGICAL_SUBMENUS));

    // set styles
    HasButtons();
    HasLines();
    LinesAtRoot();
    ShowSelectionAlways();

    // load images
    LoadImageList(IDB_IL_LOGICALSYSTEM, 17, 1, RGB(255, 255, 255));
    m_HasBeenInitialized = true;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::LoadTree()
{
    // create the tree. NOTE this function will do nothing if already created
    CreateTree();

    // no user group, do nothing
    if (!m_pLogicalSystemRoot)
        return;

    m_hUserGroupRoot = AddTypeItem(m_RootName, g_LogicalSystemRootTreeItem);

    ProcessLogicalSystemGroup(m_pLogicalSystemRoot, m_hUserGroupRoot);

    // expand the root
    ExpandRoot(TRUE);
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::DestroyTree()
{
    if (::IsWindow(GetSafeHwnd()))
        DeleteAllItems();

    // empty the data set
    EmptyDataSet();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::EmptyDataSet()
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        delete pElement;

    m_DataSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemTreeCtrl::ProcessLogicalSystemGroup(PSS_LogicalSystemEntity* pLogicalSystem, HTREEITEM hParentTreeItem)
{
    // add the item
    HTREEITEM hGroupItem = AddLogicalSystemItem(pLogicalSystem, hParentTreeItem);

    if (pLogicalSystem->ContainEntity())
    {
        const int count = pLogicalSystem->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            PSS_LogicalSystemEntity* pEntity = dynamic_cast<PSS_LogicalSystemEntity*>(pLogicalSystem->GetEntityAt(i));

            if (!pEntity)
                continue;

            ProcessLogicalSystemGroup(pEntity, hGroupItem);
        }
    }
}
//---------------------------------------------------------------------------
HTREEITEM PSS_LogicalSystemTreeCtrl::AddTypeItem(const CString& name, int iconIndex, HTREEITEM hParentTreeItem)
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
HTREEITEM PSS_LogicalSystemTreeCtrl::AddLogicalSystemItem(PSS_LogicalSystemEntity* pLogicalSystem, HTREEITEM hParentTreeItem)
{
    if (!pLogicalSystem)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = g_LogicalSystemTreeItem;
    curTreeItem.item.iSelectedImage = g_LogicalSystemTreeItem;
    curTreeItem.item.pszText        = (char*)((const char*)pLogicalSystem->GetEntityName());
    curTreeItem.item.lParam         = (LPARAM)AddDataToSet(pLogicalSystem);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
BOOL PSS_LogicalSystemTreeCtrl::ModifyLogicalSystemItem(PSS_LogicalSystemEntity* pLogicalSystem, HTREEITEM hItem)
{
    if (!pLogicalSystem)
        return FALSE;

    return SetItemText(hItem, (char*)((const char*)pLogicalSystem->GetEntityName()));
}
//---------------------------------------------------------------------------
PSS_SystemEntity* PSS_LogicalSystemTreeCtrl::GetSystemEntity(HTREEITEM hItem)
{
    if (hItem)
    {
        ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(hItem));

        if (pObj && pObj->m_Type == ITreeData::IE_DT_LogicalSystem)
            return pObj->m_pLogicalSystem;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity* PSS_LogicalSystemTreeCtrl::GetLogicalSystem(HTREEITEM hItem)
{
    if (hItem)
    {
        ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(hItem));

        if (pObj && pObj->m_Type == ITreeData::IE_DT_LogicalSystem)
            return pObj->m_pLogicalSystem;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity* PSS_LogicalSystemTreeCtrl::GetOwnerSystem(HTREEITEM hItem)
{
    if (hItem)
    {
        PSS_LogicalSystemEntity* pLogicalSystem = GetLogicalSystem(hItem);

        if (pLogicalSystem)
        {
            PSS_LogicalSystemEntity* pParent = dynamic_cast<PSS_LogicalSystemEntity*>(pLogicalSystem->GetParent());

            // if a parent defined
            if (pParent)
                return pParent;

            return pLogicalSystem;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LogicalSystemTreeCtrl::ITreeData* PSS_LogicalSystemTreeCtrl::FindElementFromDataSet(PSS_LogicalSystemEntity* pLogicalSystem)
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Type == ITreeData::IE_DT_LogicalSystem && pElement->m_pLogicalSystem == pLogicalSystem)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LogicalSystemTreeCtrl::ITreeData* PSS_LogicalSystemTreeCtrl::FindElementFromDataSet(const CString& str)
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Type == ITreeData::IE_DT_String && pElement->m_Str == str)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LogicalSystemTreeCtrl::ITreeData* PSS_LogicalSystemTreeCtrl::AddDataToSet(PSS_LogicalSystemEntity* pLogicalSystem)
{
    std::unique_ptr<ITreeData> pData(new ITreeData(pLogicalSystem));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
PSS_LogicalSystemTreeCtrl::ITreeData* PSS_LogicalSystemTreeCtrl::AddDataToSet(const CString& str)
{
    std::unique_ptr<ITreeData> pData(new ITreeData(str));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
