// ZCLogicalSystemTreeCtrl.cpp : implementation file

#include "stdafx.h"
#include "ZCLogicalSystemTreeCtrl.h"

#include "ZBLogicalSystemEntity.h"
// JMR-MODIF - Le 27 février 2006 - Ajout de l'en-tête ZVSelectLogicalSystemDlg.h
#include "ZVSelectLogicalSystemDlg.h"
#include "ZBLogicalSystemObserverMsg.h"

#include "zModel\zModelRes.h"
#include "ZVLogicalSystemInfoDlg.h"

// JMR-MODIF - Le 27 février 2006 - Ajout de l'en-tête zBaseLibRes.h
#include "zBaseLib\zBaseLibRes.h"

#ifdef _DEBUG
#include "zFormsRes\zFormsRes.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 11 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (en commentaires)

const int _LogicalSystemRootTreeItem = 0;
const int _LogicalSystemTreeItem = 1;

/////////////////////////////////////////////////////////////////////////////
// _ZInternalLogicalSystemTreeData

_ZInternalLogicalSystemTreeData::_ZInternalLogicalSystemTreeData()
{
    m_dtp = lstp_Unknown;
    m_pLogicalSystem = NULL;

    m_Str.Empty();
}

_ZInternalLogicalSystemTreeData::_ZInternalLogicalSystemTreeData(ZBLogicalSystemEntity* pLogicalSystem)
{
    m_dtp = lstp_LogicalSystem;
    m_pLogicalSystem = pLogicalSystem;

    m_Str.Empty();
}

_ZInternalLogicalSystemTreeData::_ZInternalLogicalSystemTreeData(CString Str)
{
    m_dtp = lstp_String;
    m_Str = Str;

    m_pLogicalSystem = NULL;
}

_ZInternalLogicalSystemTreeData::~_ZInternalLogicalSystemTreeData()
{
    // In the destructor, just reset all values
    m_dtp = lstp_Unknown;
    m_pLogicalSystem = NULL;

    m_Str.Empty();
}

/////////////////////////////////////////////////////////////////////////////
// ZCLogicalSystemTreeCtrl

BEGIN_MESSAGE_MAP(ZCLogicalSystemTreeCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(ZCLogicalSystemTreeCtrl)
    ON_WM_CREATE()
    ON_WM_LBUTTONDBLCLK()
    ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_COLLAPSE_BRANCH, OnCollapseBranch)
    ON_COMMAND(ID_EXPAND_BRANCH, OnExpandBranch)
    //}}AFX_MSG_MAP
//    ON_WM_CLOSE()
END_MESSAGE_MAP()

ZCLogicalSystemTreeCtrl::ZCLogicalSystemTreeCtrl(const CString                RootName            /*= _T( "" )*/,
                                                 ZBLogicalSystemEntity*    pLogicalSystemRoot    /*= NULL*/) :
    PSS_TreeCtrl(),
    m_RootName(RootName),
    m_pLogicalSystemRoot(pLogicalSystemRoot),
    m_hUserGroupRoot(NULL),
    m_HasBeenInitialized(false)
{}

ZCLogicalSystemTreeCtrl::~ZCLogicalSystemTreeCtrl()
{}

void ZCLogicalSystemTreeCtrl::Initialize(const CString RootName, ZBLogicalSystemEntity* pLogicalSystemRoot)
{
    m_RootName = RootName;
    m_pLogicalSystemRoot = pLogicalSystemRoot;

    DestroyTree();
    LoadTree();
}

// JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release pour permettre un nettoyage de la mémoire.
void ZCLogicalSystemTreeCtrl::Release()
{
    DestroyTree();
}

void ZCLogicalSystemTreeCtrl::Refresh()
{
    // First, save the state
    SaveCollapsedState();

    DestroyTree();
    LoadTree();

    // And then, restore the previously saved state
    RestoreCollapsedStateToTreeCtrl();
}

void ZCLogicalSystemTreeCtrl::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (pMsg && ISA(pMsg, ZBLogicalSystemObserverMsg))
    {
        switch (dynamic_cast<ZBLogicalSystemObserverMsg*>(pMsg)->GetMessageID())
        {
            case UM_INITLOGICALSYSTEM:
            {
                if (dynamic_cast<ZBLogicalSystemObserverMsg*>(pMsg)->GetEntity() &&
                    ISA(dynamic_cast<ZBLogicalSystemObserverMsg*>(pMsg)->GetEntity(), ZBLogicalSystemEntity))
                {
                    ZBLogicalSystemEntity* pLogicalSystem =
                        dynamic_cast<ZBLogicalSystemEntity*>(dynamic_cast<ZBLogicalSystemObserverMsg*>(pMsg)->GetEntity());

                    Initialize(dynamic_cast<ZBLogicalSystemObserverMsg*>(pMsg)->GetRootName(), pLogicalSystem);
                }

                break;
            }

            case UM_CLOSELOGICALSYSTEM:
            {
                DestroyTree();
                break;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZCLogicalSystemTreeCtrl message handlers

int ZCLogicalSystemTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_TreeCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    LoadTree();

    return 0;
}

BOOL ZCLogicalSystemTreeCtrl::DestroyWindow()
{
    DestroyTree();

    return CWnd::DestroyWindow();
}

void ZCLogicalSystemTreeCtrl::DestroyTree()
{
    if (::IsWindow(GetSafeHwnd()))
    {
        DeleteAllItems();
    }

    // Empty the data set first
    EmptyDataSet();
}

void ZCLogicalSystemTreeCtrl::CreateTree()
{
    if (m_HasBeenInitialized == false)
    {
        VERIFY(m_SubMenu.LoadMenu(IDR_LOGICAL_SUBMENUS));

        // Sets styles
        HasButtons();
        HasLines();
        LinesAtRoot();
        ShowSelectionAlways();

        // Load images
        LoadImageList(IDB_IL_LOGICALSYSTEM, 17, 1, RGB(255, 255, 255));
        m_HasBeenInitialized = true;
    }
}

void ZCLogicalSystemTreeCtrl::LoadTree()
{
    // Call the create tree function first,
    // in fact this function is executed only one time for initializing
    // correctly the control
    CreateTree();

    // No user group, do nothing
    if (!m_pLogicalSystemRoot)
    {
        return;
    }

    m_hUserGroupRoot = AddTypeItem(m_RootName, _LogicalSystemRootTreeItem);

    ProcessLogicalSystemGroup(m_pLogicalSystemRoot, m_hUserGroupRoot);

    // Expand the root
    ExpandRoot(TRUE);
}

void ZCLogicalSystemTreeCtrl::ProcessLogicalSystemGroup(ZBLogicalSystemEntity*    pLogicalSystem,
                                                        HTREEITEM                hParentTreeItem)
{
    // First, add the item
    HTREEITEM hGroupItem = AddLogicalSystemItem(pLogicalSystem, hParentTreeItem);

    if (pLogicalSystem->ContainEntity())
    {
        int Count = pLogicalSystem->GetEntityCount();

        for (int i = 0; i < Count; ++i)
        {
            ZBSystemEntity* pEntity = pLogicalSystem->GetEntityAt(i);

            if (!pEntity)
            {
                continue;
            }

            if (ISA(pEntity, ZBLogicalSystemEntity))
            {
                ProcessLogicalSystemGroup(dynamic_cast<ZBLogicalSystemEntity*>(pEntity), hGroupItem);
            }
        }
    }
}

HTREEITEM ZCLogicalSystemTreeCtrl::AddTypeItem(const CString    Name,
                                               int            IconIndex,
                                               HTREEITEM        hParentTreeItem /*= NULL*/)
{
    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent = hParentTreeItem;
    curTreeItem.hInsertAfter = TVI_LAST;
    curTreeItem.item.iImage = IconIndex;
    curTreeItem.item.iSelectedImage = IconIndex;
    curTreeItem.item.pszText = (char*)((const char*)Name);
    curTreeItem.item.lParam = (LPARAM)AddDataToSet(Name);        // Represent a selectable item
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem(&curTreeItem);
}

HTREEITEM ZCLogicalSystemTreeCtrl::AddLogicalSystemItem(ZBLogicalSystemEntity*    pLogicalSystem,
                                                        HTREEITEM                    hParentTreeItem)
{
    if (!pLogicalSystem)
    {
        return NULL;
    }

    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent = hParentTreeItem;
    curTreeItem.hInsertAfter = TVI_LAST;
    curTreeItem.item.iImage = _LogicalSystemTreeItem;
    curTreeItem.item.iSelectedImage = _LogicalSystemTreeItem;
    curTreeItem.item.pszText = (char*)((const char*)pLogicalSystem->GetEntityName());
    curTreeItem.item.lParam = (LPARAM)AddDataToSet(pLogicalSystem);    // Represent a selectable item
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem(&curTreeItem);
}

BOOL ZCLogicalSystemTreeCtrl::ModifyLogicalSystemItem(ZBLogicalSystemEntity* pLogicalSystem, HTREEITEM hItem)
{
    if (!pLogicalSystem)
    {
        return FALSE;
    }

    return SetItemText(hItem, (char*)((const char*)pLogicalSystem->GetEntityName()));
}

void ZCLogicalSystemTreeCtrl::AddLogicalSystem(ZBLogicalSystemEntity* pLogicalSystem,
                                               ZBLogicalSystemEntity* pParentLogicalSystem /*= NULL*/)
{
    if (!m_hUserGroupRoot || !pLogicalSystem)
    {
        return;
    }

    HTREEITEM hParentTreeItem = m_hUserGroupRoot;

    // Find the tree item for the parent
    if (pParentLogicalSystem)
    {
        // Find the model
        _ZInternalLogicalSystemTreeData* pData;
        pData = FindElementFromDataSet(pParentLogicalSystem);

        if (pData)
        {
            // From item, in fact from root
            hParentTreeItem = FindItemData(pData, (HTREEITEM)NULL);
        }

        // If not found, set the root as parent
        if (!hParentTreeItem)
        {
            hParentTreeItem = m_hUserGroupRoot;
        }
    }

    // Insert the group in the tree
    AddLogicalSystemItem(pLogicalSystem, hParentTreeItem);

    // Expand the parent. Unless, if he has no childs, they are not visible
    ExpandBranch(hParentTreeItem);
}

void ZCLogicalSystemTreeCtrl::RemoveLogicalSystem(ZBLogicalSystemEntity* pLogicalSystem)
{
    if (!m_hUserGroupRoot || !pLogicalSystem)
    {
        return;
    }

    _ZInternalLogicalSystemTreeData* pData = FindElementFromDataSet(pLogicalSystem);

    if (pData)
    {
        // From item, in fact from root
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
        {
            DeleteItem(hItem);
        }
    }
}

void ZCLogicalSystemTreeCtrl::ModifyLogicalSystem(ZBLogicalSystemEntity* pLogicalSystem)
{
    if (!m_hUserGroupRoot || !pLogicalSystem)
    {
        return;
    }

    _ZInternalLogicalSystemTreeData* pData = FindElementFromDataSet(pLogicalSystem);

    if (pData)
    {
        // From item, in fact from root
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
        {
            ModifyLogicalSystemItem(pLogicalSystem, hItem);
        }
    }
}

ZBSystemEntity* ZCLogicalSystemTreeCtrl::GetSelectedSystemEntity()
{
    return _GetSystemEntity(GetSelectedItem());
}

ZBSystemEntity* ZCLogicalSystemTreeCtrl::_GetSystemEntity(HTREEITEM hItem)
{
    if (hItem)
    {
        _ZInternalLogicalSystemTreeData* pObj = (_ZInternalLogicalSystemTreeData*)GetItemData(hItem);

        if (pObj != NULL && pObj->m_dtp == _ZInternalLogicalSystemTreeData::lstp_LogicalSystem)
        {
            return pObj->m_pLogicalSystem;
        }
    }

    return NULL;
}

ZBLogicalSystemEntity* ZCLogicalSystemTreeCtrl::GetSelectedLogicalSystem()
{
    return _GetLogicalSystem(GetSelectedItem());
}

ZBLogicalSystemEntity* ZCLogicalSystemTreeCtrl::_GetLogicalSystem(HTREEITEM hItem)
{
    if (hItem)
    {
        _ZInternalLogicalSystemTreeData* pObj = (_ZInternalLogicalSystemTreeData*)GetItemData(hItem);

        if (pObj != NULL && pObj->m_dtp == _ZInternalLogicalSystemTreeData::lstp_LogicalSystem)
        {
            return pObj->m_pLogicalSystem;
        }
    }

    return NULL;
}

ZBLogicalSystemEntity* ZCLogicalSystemTreeCtrl::GetSelectedLogicalSystemOwner()
{
    return _GetOwnerSystem(GetSelectedItem());
}

ZBLogicalSystemEntity* ZCLogicalSystemTreeCtrl::_GetOwnerSystem(HTREEITEM hItem)
{
    if (hItem)
    {
        ZBLogicalSystemEntity* pLogicalSystem = _GetLogicalSystem(hItem);

        if (pLogicalSystem)
        {
            // If a parent defined
            if (pLogicalSystem->GetParent() && ISA(pLogicalSystem->GetParent(), ZBLogicalSystemEntity))
            {
                return dynamic_cast<ZBLogicalSystemEntity*>(pLogicalSystem->GetParent());
            }

            return pLogicalSystem;
        }
    }

    return NULL;
}

bool ZCLogicalSystemTreeCtrl::IsRootSelected() const
{
    if (GetSelectedItem() && (GetSelectedItem() == GetRootItem()))
    {
        return true;
    }

    return false;
}

int ZCLogicalSystemTreeCtrl::HasContextMenu(CWnd* pWnd, CPoint point)
{
    // Now display the right sub-menu
    int IdMenu = -1;
    UINT Flags;
    CPoint pt(point);
    ScreenToClient(&pt);

    HTREEITEM hItem = HitTest(pt, &Flags);

    if ((hItem != NULL) && (TVHT_ONITEM & Flags))
    {
        if (hItem == GetRootItem())
        {
            IdMenu = 0;
        }
        else if (_GetSystemEntity(hItem) == m_pLogicalSystemRoot)
        {
            IdMenu = 1;
        }
        else if (_GetSystemEntity(hItem))
        {
            IdMenu = 2;
        }
    }

    return IdMenu;
}

void ZCLogicalSystemTreeCtrl::DisplayContextMenu(CWnd* pWnd, CPoint point)
{
    int IdMenu = HasContextMenu(pWnd, point);

    if (IdMenu == -1)
    {
        return;
    }

    CMenu* pPopup = m_SubMenu.GetSubMenu(IdMenu);
    ASSERT(pPopup != NULL);
    CWnd* pWndPopupOwner = this;

    while (pWndPopupOwner->GetStyle() & WS_CHILD)
    {
        pWndPopupOwner = pWndPopupOwner->GetParent();
    }

    // And test the hit. 
    UINT    uFlags;
    CPoint    pt(point);
    ScreenToClient(&pt);
    HTREEITEM hItem = HitTest(pt, &uFlags);

    if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
    {
        Select(hItem, TVGN_CARET);
        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);
    }
}

void ZCLogicalSystemTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
    DisplayContextMenu(pWnd, point);
}

void ZCLogicalSystemTreeCtrl::OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pnmhdr;

    *pLResult = TRUE;
}

CObject* ZCLogicalSystemTreeCtrl::GetDragObject(HTREEITEM DragItem)
{
    _ZInternalLogicalSystemTreeData* pObj = (_ZInternalLogicalSystemTreeData*)GetItemData(DragItem);

    if (pObj != NULL && pObj->m_dtp == _ZInternalLogicalSystemTreeData::lstp_LogicalSystem)
    {
        return pObj->m_pLogicalSystem;
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////
// Data set methods

void ZCLogicalSystemTreeCtrl::EmptyDataSet()
{
    _ZInternalLogicalSystemTreeDataIterator i(&m_DataSet);

    for (_ZInternalLogicalSystemTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext())
    {
        delete pElement;
    }

    m_DataSet.RemoveAll();
}

_ZInternalLogicalSystemTreeData* ZCLogicalSystemTreeCtrl::FindElementFromDataSet(ZBLogicalSystemEntity* pLogicalSystem)
{
    _ZInternalLogicalSystemTreeDataIterator i(&m_DataSet);

    for (_ZInternalLogicalSystemTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext())
    {
        if (pElement->m_dtp == _ZInternalLogicalSystemTreeData::lstp_LogicalSystem &&
            pElement->m_pLogicalSystem == pLogicalSystem)
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalLogicalSystemTreeData* ZCLogicalSystemTreeCtrl::FindElementFromDataSet(CString Str)
{
    _ZInternalLogicalSystemTreeDataIterator i(&m_DataSet);

    for (_ZInternalLogicalSystemTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext())
    {
        if (pElement->m_dtp == _ZInternalLogicalSystemTreeData::lstp_String && pElement->m_Str == Str)
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalLogicalSystemTreeData* ZCLogicalSystemTreeCtrl::AddDataToSet(ZBLogicalSystemEntity* pLogicalSystem)
{
    _ZInternalLogicalSystemTreeData* pData = new _ZInternalLogicalSystemTreeData(pLogicalSystem);
    m_DataSet.Add(pData);

    return pData;
}

_ZInternalLogicalSystemTreeData* ZCLogicalSystemTreeCtrl::AddDataToSet(CString Str)
{
    _ZInternalLogicalSystemTreeData* pData = new _ZInternalLogicalSystemTreeData(Str);
    m_DataSet.Add(pData);

    return pData;
}

/////////////////////////////////////////////////////////////////////////////
// ZCLogicalSystemTreeCtrl menu commands

void ZCLogicalSystemTreeCtrl::OnNewLogicalSystem()
{
    ZBLogicalSystemEntity* pLogicalSystem = GetSelectedLogicalSystem();

    // If a group selected
    if (pLogicalSystem != NULL)
    {
        ASSERT(m_pLogicalSystemRoot != NULL);

        // Asks for the name
        ZVLogicalSystemInfoDlg dlg(IDS_NEW_LOGICALSYSTEM_T, pLogicalSystem);

        if (dlg.DoModal() == IDOK)
        {
            ZBLogicalSystemEntity* pNewGroup = m_pLogicalSystemRoot->AddSystem(dlg.GetName(),
                                                                               dlg.GetDescription(),
                                                                               pLogicalSystem);

            if (pNewGroup)
            {
                // Now, add the system to the tree
                ZCLogicalSystemTreeCtrl::AddLogicalSystem(pNewGroup, pLogicalSystem);

                // Modified
                m_pLogicalSystemRoot->SetModifiedFlag();
            }
        }
    }
}

void ZCLogicalSystemTreeCtrl::OnDeleteLogicalSystem()
{
    if (IsRootSelected())
    {
        return;
    }

    ZBLogicalSystemEntity* pLogicalSystem = GetSelectedLogicalSystem();

    if (pLogicalSystem != NULL && pLogicalSystem != m_pLogicalSystemRoot)
    {
        ASSERT(m_pLogicalSystemRoot != NULL);

        // Remove system from the workspace
        m_pLogicalSystemRoot->RemoveSystem(pLogicalSystem);

        // Now delete the system name from the tree
        ZCLogicalSystemTreeCtrl::RemoveLogicalSystem(pLogicalSystem);

        // Modified
        m_pLogicalSystemRoot->SetModifiedFlag();
    }
}

void ZCLogicalSystemTreeCtrl::OnRenameLogicalSystem()
{
    if (IsRootSelected())
    {
        return;
    }

    ZBLogicalSystemEntity* pLogicalSystem = GetSelectedLogicalSystem();

    if (pLogicalSystem != NULL)
    {
        ASSERT(m_pLogicalSystemRoot != NULL);

        ZVLogicalSystemInfoDlg dlg(IDS_RENAME_LOGICALSYSTEM_T,
            (pLogicalSystem->GetParent() && ISA(pLogicalSystem->GetParent(), ZBLogicalSystemEntity)) ? dynamic_cast<ZBLogicalSystemEntity*>(pLogicalSystem->GetParent()) : pLogicalSystem,
                                   pLogicalSystem->GetEntityName(),
                                   pLogicalSystem->GetEntityDescription());

        if (dlg.DoModal() == IDOK)
        {
            pLogicalSystem->SetEntityName(dlg.GetName());
            pLogicalSystem->SetEntityDescription(dlg.GetDescription());

            // Now modify the group name
            ZCLogicalSystemTreeCtrl::ModifyLogicalSystem(pLogicalSystem);

            // Modified
            m_pLogicalSystemRoot->SetModifiedFlag();
        }
    }
}

// JMR-MODIF - Le 27 février 2006 - Ajout de la fonction OnMoveLogicalSystem.
void ZCLogicalSystemTreeCtrl::OnMoveLogicalSystem()
{
    ZBLogicalSystemEntity* pSystem = GetSelectedLogicalSystem();

    if (pSystem != NULL)
    {
        ASSERT(m_pLogicalSystemRoot != NULL);

        ZVSelectLogicalSystemDlg dlg(IDS_LGS_MOVE_T,
                                     m_pLogicalSystemRoot);

        if (dlg.DoModal() == IDOK)
        {
            // If we have selected an entity
            // and if it is not the same
            if (dlg.GetSelectedSystemEntity() &&
                dlg.GetSelectedSystemEntity() != pSystem &&
                ISA(dlg.GetSelectedSystemEntity(), ZBLogicalSystemEntity))
            {
                // Move the element
                // Assigns the new parent
                dynamic_cast<ZBLogicalSystemEntity*>(dlg.GetSelectedSystemEntity())->MoveSystem(pSystem);

                // Modified
                m_pLogicalSystemRoot->SetModifiedFlag();

                // Refresh the tree
                Refresh();
            }
        }
    }
}

void ZCLogicalSystemTreeCtrl::OnLogicalSystemProperties()
{
    ZBSystemEntity* pEntity = GetSelectedSystemEntity();

    if (pEntity != NULL)
    {
        ZBLogicalSystemEntity* pLogicalSystem = GetSelectedLogicalSystem();
        ASSERT(m_pLogicalSystemRoot != NULL);

        ZVLogicalSystemInfoDlg dlg(IDS_LOGICALSYSTEM_PROPERTY_T,
            (pEntity->GetParent() && ISA(pEntity->GetParent(), ZBLogicalSystemEntity)) ? dynamic_cast<ZBLogicalSystemEntity*>(pEntity->GetParent()) : m_pLogicalSystemRoot,
                                   pEntity->GetEntityName(),
                                   pEntity->GetEntityDescription(),
                                   true);    // ModifyMode

        if (dlg.DoModal() == IDOK)
        {
            if (pLogicalSystem != NULL)
            {
                pLogicalSystem->SetEntityDescription(dlg.GetDescription());
            }

            // Modified
            m_pLogicalSystemRoot->SetModifiedFlag();
        }
    }
}

void ZCLogicalSystemTreeCtrl::OnCollapseBranch()
{
    CollapseBranch(GetSelectedItem(), TRUE);
}

void ZCLogicalSystemTreeCtrl::OnExpandBranch()
{
    ExpandBranch(GetSelectedItem(), TRUE);
}

bool ZCLogicalSystemTreeCtrl::CanNewLogicalSystem()
{
    return (GetSelectedLogicalSystem() != NULL) ? true : false;
}

bool ZCLogicalSystemTreeCtrl::CanDeleteLogicalSystem()
{
    return (GetSelectedLogicalSystem() != NULL && GetSelectedLogicalSystem() != m_pLogicalSystemRoot) ? true : false;
}

bool ZCLogicalSystemTreeCtrl::CanRenameLogicalSystem()
{
    return (GetSelectedLogicalSystem() != NULL) ? true : false;
}

bool ZCLogicalSystemTreeCtrl::CanLogicalSystemProperties()
{
    return (GetSelectedSystemEntity() != NULL || IsRootSelected()) ? true : false;
}

void ZCLogicalSystemTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // Display the properties
    ZCLogicalSystemTreeCtrl::OnLogicalSystemProperties();
}
