// ******************************************************************************************************************
// *                       Classes _ZInternalPrestationsTreeData et ZCPrestationsTreeCtrl                            *
// ******************************************************************************************************************
// * JMR-MODIF - Le 11 octobre 2005 - Ajout des classes _ZInternalPrestationsTreeData et ZCPrestationsTreeCtrl.        *
// ******************************************************************************************************************
// * Ces classes contiennent les données élémentaires de type prestation, ainsi que le gestionnaire pour ces        *
// * données.                                                                                                        *
// ******************************************************************************************************************

#include "stdafx.h"
#include "ZCPrestationsTreeCtrl.h"

#include "PSS_LogicalPrestationsEntity.h"
#include "ZVSelectPrestationDlg.h"
#include "PSS_LogicalPrestationsObserverMsg.h"

#include "zBaseLib\zBaseLibRes.h"
#include "zModel\zModelRes.h"
#include "ZVPrestationsInfoDlg.h"

#ifdef _DEBUG
#include "zFormsRes\zFormsRes.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int _PrestationsRootTreeItem = 0;
const int _PrestationsTreeItem = 1;

/////////////////////////////////////////////////////////////////////////////
// _ZInternalPrestationsTreeData

_ZInternalPrestationsTreeData::_ZInternalPrestationsTreeData()
{
    m_dtp = ptp_Unknown;
    m_pPrestation = NULL;

    m_Str.Empty();
}

_ZInternalPrestationsTreeData::_ZInternalPrestationsTreeData(PSS_LogicalPrestationsEntity* pLogicalPrestation)
{
    m_dtp = ptp_Prestation;
    m_pPrestation = pLogicalPrestation;

    m_Str.Empty();
}

_ZInternalPrestationsTreeData::_ZInternalPrestationsTreeData(CString Str)
{
    m_dtp = ptp_String;
    m_Str = Str;

    m_pPrestation = NULL;
}

_ZInternalPrestationsTreeData::~_ZInternalPrestationsTreeData()
{
    // In the destructor, just reset all values
    m_dtp = ptp_Unknown;
    m_pPrestation = NULL;

    m_Str.Empty();
}

/////////////////////////////////////////////////////////////////////////////
// ZCPrestationsTreeCtrl

BEGIN_MESSAGE_MAP(ZCPrestationsTreeCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(ZCPrestationsTreeCtrl)
    ON_WM_CREATE()
    ON_WM_LBUTTONDBLCLK()
    ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_COLLAPSE_BRANCH, OnCollapseBranch)
    ON_COMMAND(ID_EXPAND_BRANCH, OnExpandBranch)
    //}}AFX_MSG_MAP
//    ON_WM_CLOSE()
END_MESSAGE_MAP()

ZCPrestationsTreeCtrl::ZCPrestationsTreeCtrl(const CString                    RootName                /*= _T( "" )*/,
                                             PSS_LogicalPrestationsEntity*    pLogicalPrestationRoot    /*= NULL*/) :
    PSS_TreeCtrl(),
    m_RootName(RootName),
    m_pLogicalPrestationRoot(pLogicalPrestationRoot),
    m_hUserGroupRoot(NULL),
    m_HasBeenInitialized(false)
{}

ZCPrestationsTreeCtrl::~ZCPrestationsTreeCtrl()
{}

void ZCPrestationsTreeCtrl::Initialize(const CString RootName, PSS_LogicalPrestationsEntity* pLogicalPrestationRoot)
{
    m_RootName = RootName;
    m_pLogicalPrestationRoot = pLogicalPrestationRoot;

    DestroyTree();
    LoadTree();
}

void ZCPrestationsTreeCtrl::Release()
{
    DestroyTree();
}

void ZCPrestationsTreeCtrl::Refresh()
{
    // First, save the state
    SaveCollapsedState();

    DestroyTree();
    LoadTree();

    // And then, restore the previously saved state
    RestoreCollapsedStateToTreeCtrl();
}

void ZCPrestationsTreeCtrl::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (pMsg && ISA(pMsg, PSS_LogicalPrestationsObserverMsg))
    {
        switch (dynamic_cast<PSS_LogicalPrestationsObserverMsg*>(pMsg)->GetMessageID())
        {
            case g_InitPrestations:
            {
                if (dynamic_cast<PSS_LogicalPrestationsObserverMsg*>(pMsg)->GetEntity() &&
                    ISA(dynamic_cast<PSS_LogicalPrestationsObserverMsg*>(pMsg)->GetEntity(), PSS_LogicalPrestationsEntity))
                {
                    PSS_LogicalPrestationsEntity* pLogicalPrestation =
                        dynamic_cast<PSS_LogicalPrestationsEntity*>(dynamic_cast<PSS_LogicalPrestationsObserverMsg*>(pMsg)->GetEntity());

                    Initialize(dynamic_cast<PSS_LogicalPrestationsObserverMsg*>(pMsg)->GetRootName(), pLogicalPrestation);
                }

                break;
            }

            case g_ClosePrestations:
            {
                DestroyTree();
                break;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZCPrestationsTreeCtrl message handlers

int ZCPrestationsTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_TreeCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    LoadTree();

    return 0;
}

BOOL ZCPrestationsTreeCtrl::DestroyWindow()
{
    DestroyTree();

    return CWnd::DestroyWindow();
}

void ZCPrestationsTreeCtrl::DestroyTree()
{
    if (::IsWindow(GetSafeHwnd()))
    {
        DeleteAllItems();
    }

    // Empty the data set first
    EmptyDataSet();
}

void ZCPrestationsTreeCtrl::CreateTree()
{
    if (m_HasBeenInitialized == false)
    {
        VERIFY(m_SubMenu.LoadMenu(IDR_PRESTATIONS_SUBMENUS));

        // Sets styles
        HasButtons();
        HasLines();
        LinesAtRoot();
        ShowSelectionAlways();

        // Load images
        LoadImageList(IDB_IL_PRESTATIONS, 17, 1, RGB(255, 255, 255));
        m_HasBeenInitialized = true;
    }
}

void ZCPrestationsTreeCtrl::LoadTree()
{
    // Call the create tree function first,
    // in fact this function is executed only one time for initializing
    // correctly the control
    CreateTree();

    // No user group, do nothing
    if (!m_pLogicalPrestationRoot)
    {
        return;
    }

    m_hUserGroupRoot = AddTypeItem(m_RootName, _PrestationsRootTreeItem);

    ProcessLogicalPrestationsGroup(m_pLogicalPrestationRoot, m_hUserGroupRoot);

    // Expand the root
    ExpandRoot(TRUE);
}

void ZCPrestationsTreeCtrl::ProcessLogicalPrestationsGroup(PSS_LogicalPrestationsEntity*    pLogicalPrestation,
                                                           HTREEITEM                    hParentTreeItem)
{
    // First, add the item
    HTREEITEM hGroupItem = AddLogicalPrestationItem(pLogicalPrestation, hParentTreeItem);

    if (pLogicalPrestation->ContainEntity())
    {
        int Count = pLogicalPrestation->GetEntityCount();

        for (int i = 0; i < Count; ++i)
        {
            ZBPrestationsEntity* pEntity = pLogicalPrestation->GetEntityAt(i);

            if (!pEntity)
            {
                continue;
            }

            if (ISA(pEntity, PSS_LogicalPrestationsEntity))
            {
                ProcessLogicalPrestationsGroup(dynamic_cast<PSS_LogicalPrestationsEntity*>(pEntity), hGroupItem);
            }
        }
    }
}

HTREEITEM ZCPrestationsTreeCtrl::AddTypeItem(const CString Name, int IconIndex, HTREEITEM hParentTreeItem /*= NULL*/)
{
    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent = hParentTreeItem;
    curTreeItem.hInsertAfter = TVI_LAST;
    curTreeItem.item.iImage = IconIndex;
    curTreeItem.item.iSelectedImage = IconIndex;
    curTreeItem.item.pszText = (char*)((const char*)Name);
    curTreeItem.item.lParam = (LPARAM)AddDataToSet(Name);    // Represent a selectable item
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem(&curTreeItem);
}

HTREEITEM ZCPrestationsTreeCtrl::AddLogicalPrestationItem(PSS_LogicalPrestationsEntity*    pLogicalPrestation,
                                                          HTREEITEM                    hParentTreeItem)
{
    if (!pLogicalPrestation)
    {
        return NULL;
    }

    TV_INSERTSTRUCT curTreeItem;

    curTreeItem.hParent = hParentTreeItem;
    curTreeItem.hInsertAfter = TVI_LAST;
    curTreeItem.item.iImage = _PrestationsTreeItem;
    curTreeItem.item.iSelectedImage = _PrestationsTreeItem;
    curTreeItem.item.pszText = (char*)((const char*)pLogicalPrestation->GetEntityName());
    curTreeItem.item.lParam = (LPARAM)AddDataToSet(pLogicalPrestation);    // Represent a selectable item
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem(&curTreeItem);
}

BOOL ZCPrestationsTreeCtrl::ModifyLogicalPrestationItem(PSS_LogicalPrestationsEntity*    pLogicalPrestation,
                                                        HTREEITEM                        hItem)
{
    if (!pLogicalPrestation)
    {
        return FALSE;
    }

    return SetItemText(hItem, (char*)((const char*)pLogicalPrestation->GetEntityName()));
}

void ZCPrestationsTreeCtrl::AddPrestation(PSS_LogicalPrestationsEntity* pLogicalPrestation,
                                          PSS_LogicalPrestationsEntity* pParentLogicalPrestation /*= NULL*/)
{
    if (!m_hUserGroupRoot || !pLogicalPrestation)
    {
        return;
    }

    HTREEITEM hParentTreeItem = m_hUserGroupRoot;

    // Find the tree item for the parent
    if (pParentLogicalPrestation)
    {
        // Find the model
        _ZInternalPrestationsTreeData* pData;
        pData = FindElementFromDataSet(pParentLogicalPrestation);

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
    AddLogicalPrestationItem(pLogicalPrestation, hParentTreeItem);

    // Expand the parent. Unless, if he has no childs, they are not visible
    ExpandBranch(hParentTreeItem);
}

void ZCPrestationsTreeCtrl::RemovePrestation(PSS_LogicalPrestationsEntity* pLogicalPrestation)
{
    if (!m_hUserGroupRoot || !pLogicalPrestation)
    {
        return;
    }

    _ZInternalPrestationsTreeData* pData = FindElementFromDataSet(pLogicalPrestation);

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

void ZCPrestationsTreeCtrl::ModifyPrestation(PSS_LogicalPrestationsEntity* pLogicalPrestation)
{
    if (!m_hUserGroupRoot || !pLogicalPrestation)
    {
        return;
    }

    _ZInternalPrestationsTreeData* pData = FindElementFromDataSet(pLogicalPrestation);

    if (pData)
    {
        // From item, in fact from root
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
        {
            ModifyLogicalPrestationItem(pLogicalPrestation, hItem);
        }
    }
}

ZBPrestationsEntity* ZCPrestationsTreeCtrl::GetSelectedPrestationEntity()
{
    return _GetPrestationEntity(GetSelectedItem());
}

ZBPrestationsEntity* ZCPrestationsTreeCtrl::_GetPrestationEntity(HTREEITEM hItem)
{
    if (hItem)
    {
        _ZInternalPrestationsTreeData* pObj = (_ZInternalPrestationsTreeData*)GetItemData(hItem);

        if (pObj != NULL && pObj->m_dtp == _ZInternalPrestationsTreeData::ptp_Prestation)
        {
            return pObj->m_pPrestation;
        }
    }

    return NULL;
}

PSS_LogicalPrestationsEntity* ZCPrestationsTreeCtrl::GetSelectedLogicalPrestation()
{
    return _GetLogicalPrestation(GetSelectedItem());
}

PSS_LogicalPrestationsEntity* ZCPrestationsTreeCtrl::_GetLogicalPrestation(HTREEITEM hItem)
{
    if (hItem)
    {
        _ZInternalPrestationsTreeData* pObj = (_ZInternalPrestationsTreeData*)GetItemData(hItem);

        if (pObj != NULL && pObj->m_dtp == _ZInternalPrestationsTreeData::ptp_Prestation)
        {
            return pObj->m_pPrestation;
        }
    }

    return NULL;
}

PSS_LogicalPrestationsEntity* ZCPrestationsTreeCtrl::GetSelectedLogicalPrestationOwner()
{
    return _GetOwnerPrestation(GetSelectedItem());
}

PSS_LogicalPrestationsEntity* ZCPrestationsTreeCtrl::_GetOwnerPrestation(HTREEITEM hItem)
{
    if (hItem)
    {
        PSS_LogicalPrestationsEntity* pLogicalPrestation = _GetLogicalPrestation(hItem);

        if (pLogicalPrestation)
        {
            // If a parent defined
            if (pLogicalPrestation->GetParent() &&
                ISA(pLogicalPrestation->GetParent(), PSS_LogicalPrestationsEntity))
            {
                return dynamic_cast<PSS_LogicalPrestationsEntity*>(pLogicalPrestation->GetParent());
            }

            return pLogicalPrestation;
        }
    }

    return NULL;
}

bool ZCPrestationsTreeCtrl::IsRootSelected() const
{
    if (GetSelectedItem() && (GetSelectedItem() == GetRootItem()))
    {
        return true;
    }

    return false;
}

int ZCPrestationsTreeCtrl::HasContextMenu(CWnd* pWnd, CPoint point)
{
    // Now display the right sub-menu
    int        IdMenu = -1;
    UINT    Flags;
    CPoint    pt(point);
    ScreenToClient(&pt);

    HTREEITEM hItem = HitTest(pt, &Flags);

    if ((hItem != NULL) && (TVHT_ONITEM & Flags))
    {
        if (hItem == GetRootItem())
        {
            IdMenu = 0;
        }
        else if (_GetPrestationEntity(hItem) == m_pLogicalPrestationRoot)
        {
            IdMenu = 1;
        }
        else if (_GetPrestationEntity(hItem))
        {
            IdMenu = 2;
        }
    }

    return IdMenu;
}

void ZCPrestationsTreeCtrl::DisplayContextMenu(CWnd* pWnd, CPoint point)
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

void ZCPrestationsTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
    DisplayContextMenu(pWnd, point);
}

void ZCPrestationsTreeCtrl::OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pnmhdr;

    *pLResult = TRUE;
}

CObject* ZCPrestationsTreeCtrl::GetDragObject(HTREEITEM DragItem)
{
    _ZInternalPrestationsTreeData* pObj = (_ZInternalPrestationsTreeData*)GetItemData(DragItem);

    if (pObj != NULL && pObj->m_dtp == _ZInternalPrestationsTreeData::ptp_Prestation)
    {
        return pObj->m_pPrestation;
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////
// Data set methods

void ZCPrestationsTreeCtrl::EmptyDataSet()
{
    _ZInternalPrestationsTreeDataIterator i(&m_DataSet);

    for (_ZInternalPrestationsTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext())
    {
        delete pElement;
    }

    m_DataSet.RemoveAll();
}

_ZInternalPrestationsTreeData* ZCPrestationsTreeCtrl::FindElementFromDataSet(PSS_LogicalPrestationsEntity* pLogicalPrestation)
{
    _ZInternalPrestationsTreeDataIterator i(&m_DataSet);

    for (_ZInternalPrestationsTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext())
    {
        if (pElement->m_dtp == _ZInternalPrestationsTreeData::ptp_Prestation &&
            pElement->m_pPrestation == pLogicalPrestation)
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalPrestationsTreeData* ZCPrestationsTreeCtrl::FindElementFromDataSet(CString Str)
{
    _ZInternalPrestationsTreeDataIterator i(&m_DataSet);

    for (_ZInternalPrestationsTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext())
    {
        if (pElement->m_dtp == _ZInternalPrestationsTreeData::ptp_String && pElement->m_Str == Str)
        {
            return pElement;
        }
    }

    return NULL;
}

_ZInternalPrestationsTreeData* ZCPrestationsTreeCtrl::AddDataToSet(PSS_LogicalPrestationsEntity* pLogicalPrestation)
{
    _ZInternalPrestationsTreeData* pData = new _ZInternalPrestationsTreeData(pLogicalPrestation);
    m_DataSet.Add(pData);

    return pData;
}

_ZInternalPrestationsTreeData* ZCPrestationsTreeCtrl::AddDataToSet(CString Str)
{
    _ZInternalPrestationsTreeData* pData = new _ZInternalPrestationsTreeData(Str);
    m_DataSet.Add(pData);

    return pData;
}

/////////////////////////////////////////////////////////////////////////////
// ZCPrestationsTreeCtrl menu commands

void ZCPrestationsTreeCtrl::OnNewPrestation()
{
    PSS_LogicalPrestationsEntity* pLogicalPrestation = GetSelectedLogicalPrestation();

    // If a group selected
    if (pLogicalPrestation != NULL)
    {
        ASSERT(m_pLogicalPrestationRoot != NULL);

        // Asks for the name
        ZVPrestationsInfoDlg dlg(IDS_NEW_PRESTATION_T, pLogicalPrestation);

        if (dlg.DoModal() == IDOK)
        {
            PSS_LogicalPrestationsEntity* pNewGroup = m_pLogicalPrestationRoot->AddPrestation(dlg.GetName(),
                                                                                            dlg.GetDescription(),
                                                                                            pLogicalPrestation);

            if (pNewGroup)
            {
                // Now, add the Prestation to the tree
                ZCPrestationsTreeCtrl::AddPrestation(pNewGroup, pLogicalPrestation);

                // Modified
                m_pLogicalPrestationRoot->SetModifiedFlag();
            }
        }
    }
}

void ZCPrestationsTreeCtrl::OnDeletePrestation()
{
    if (IsRootSelected())
    {
        return;
    }

    PSS_LogicalPrestationsEntity* pLogicalPrestation = GetSelectedLogicalPrestation();

    if (pLogicalPrestation != NULL && pLogicalPrestation != m_pLogicalPrestationRoot)
    {
        ASSERT(m_pLogicalPrestationRoot != NULL);

        // Remove Prestation from the workspace
        m_pLogicalPrestationRoot->RemovePrestation(pLogicalPrestation);

        // Now delete the Prestation name from the tree
        ZCPrestationsTreeCtrl::RemovePrestation(pLogicalPrestation);

        // Modified
        m_pLogicalPrestationRoot->SetModifiedFlag();
    }
}

void ZCPrestationsTreeCtrl::OnRenamePrestation()
{
    if (IsRootSelected())
    {
        return;
    }

    PSS_LogicalPrestationsEntity* pLogicalPrestation = GetSelectedLogicalPrestation();

    if (pLogicalPrestation != NULL)
    {
        ASSERT(m_pLogicalPrestationRoot != NULL);

        ZVPrestationsInfoDlg dlg(IDS_RENAME_PRESTATION_T,
            (pLogicalPrestation->GetParent() && ISA(pLogicalPrestation->GetParent(), PSS_LogicalPrestationsEntity)) ? dynamic_cast<PSS_LogicalPrestationsEntity*>(pLogicalPrestation->GetParent()) : pLogicalPrestation,
                                 pLogicalPrestation->GetEntityName(),
                                 pLogicalPrestation->GetEntityDescription());

        if (dlg.DoModal() == IDOK)
        {
            pLogicalPrestation->SetEntityName(dlg.GetName());
            pLogicalPrestation->SetEntityDescription(dlg.GetDescription());

            // Now modify the group name
            ZCPrestationsTreeCtrl::ModifyPrestation(pLogicalPrestation);

            // Modified
            m_pLogicalPrestationRoot->SetModifiedFlag();
        }
    }
}

void ZCPrestationsTreeCtrl::OnMovePrestation()
{
    ZBPrestationsEntity* pPrestation = GetSelectedLogicalPrestation();

    if (pPrestation != NULL)
    {
        ASSERT(m_pLogicalPrestationRoot != NULL);

        ZVSelectPrestationDlg dlg(IDS_PRS_MOVE_T,
                                  m_pLogicalPrestationRoot,
                                  true);            // AllowPrestationSelection

        if (dlg.DoModal() == IDOK)
        {
            // If we have selected an entity
            // and if it is not the same
            if (dlg.GetSelectedPrestationEntity() &&
                dlg.GetSelectedPrestationEntity() != pPrestation &&
                ISA(dlg.GetSelectedPrestationEntity(), PSS_LogicalPrestationsEntity))
            {
                // Move the element
                // Assigns the new parent
                dynamic_cast<PSS_LogicalPrestationsEntity*>(dlg.GetSelectedPrestationEntity())->MovePrestation(pPrestation);

                // Modified
                m_pLogicalPrestationRoot->SetModifiedFlag();

                // Refresh the tree
                Refresh();
            }
        }
    }
}

void ZCPrestationsTreeCtrl::OnPrestationProperties()
{
    ZBPrestationsEntity* pEntity = GetSelectedPrestationEntity();

    if (pEntity != NULL)
    {
        PSS_LogicalPrestationsEntity* pLogicalPrestation = GetSelectedLogicalPrestation();
        ASSERT(m_pLogicalPrestationRoot != NULL);

        ZVPrestationsInfoDlg dlg(IDS_PRESTATION_PROPERTY_T,
            (pEntity->GetParent() && ISA(pEntity->GetParent(), PSS_LogicalPrestationsEntity)) ? dynamic_cast<PSS_LogicalPrestationsEntity*>(pEntity->GetParent()) : m_pLogicalPrestationRoot,
                                 pEntity->GetEntityName(),
                                 pEntity->GetEntityDescription(),
                                 true);  // ModifyMode

        if (dlg.DoModal() == IDOK)
        {
            if (pLogicalPrestation != NULL)
            {
                pLogicalPrestation->SetEntityDescription(dlg.GetDescription());
            }

            // Modified
            m_pLogicalPrestationRoot->SetModifiedFlag();
        }
    }
}

void ZCPrestationsTreeCtrl::OnCollapseBranch()
{
    CollapseBranch(GetSelectedItem(), TRUE);
}

void ZCPrestationsTreeCtrl::OnExpandBranch()
{
    ExpandBranch(GetSelectedItem(), TRUE);
}

bool ZCPrestationsTreeCtrl::CanNewPrestation()
{
    return (GetSelectedLogicalPrestation() != NULL) ? true : false;
}

bool ZCPrestationsTreeCtrl::CanDeletePrestation()
{
    return (GetSelectedLogicalPrestation() != NULL && GetSelectedLogicalPrestation() != m_pLogicalPrestationRoot) ? true : false;
}

bool ZCPrestationsTreeCtrl::CanRenamePrestation()
{
    return (GetSelectedLogicalPrestation() != NULL) ? true : false;
}

bool ZCPrestationsTreeCtrl::CanPrestationProperties()
{
    return (GetSelectedPrestationEntity() != NULL || IsRootSelected()) ? true : false;
}

void ZCPrestationsTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // Display the properties
    ZCPrestationsTreeCtrl::OnPrestationProperties();
}
