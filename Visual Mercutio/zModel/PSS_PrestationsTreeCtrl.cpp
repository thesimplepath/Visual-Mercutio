/****************************************************************************
 * ==> PSS_PrestationsTreeCtrl ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a prestations tree controller                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PrestationsTreeCtrl.h"

// processsoft
#include "PSS_LogicalPrestationsEntity.h"
#include "PSS_LogicalPrestationsObserverMsg.h"
#include "PSS_SelectPrestationDlg.h"
#include "PSS_PrestationsInfoDlg.h"

// resources
#include "zBaseLib\zBaseLibRes.h"
#include "zModel\zModelRes.h"
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
const int g_PrestationsRootTreeItem = 0;
const int g_PrestationsTreeItem     = 1;
//---------------------------------------------------------------------------
// PSS_PrestationsTreeCtrl::ITreeData
//---------------------------------------------------------------------------
PSS_PrestationsTreeCtrl::ITreeData::ITreeData() :
    CObject(),
    m_pPrestation(NULL),
    m_Type(IE_DT_Unknown)
{}
//---------------------------------------------------------------------------
PSS_PrestationsTreeCtrl::ITreeData::ITreeData(PSS_LogicalPrestationsEntity* pLogicalPrestation) :
    CObject(),
    m_pPrestation(pLogicalPrestation),
    m_Type(IE_DT_Prestation)
{}
//---------------------------------------------------------------------------
PSS_PrestationsTreeCtrl::ITreeData::ITreeData(const CString& str) :
    CObject(),
    m_pPrestation(NULL),
    m_Type(IE_DT_String),
    m_Str(str)
{}
//---------------------------------------------------------------------------
PSS_PrestationsTreeCtrl::ITreeData::~ITreeData()
{}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PrestationsTreeCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(PSS_PrestationsTreeCtrl)
    ON_WM_CREATE()
    ON_WM_LBUTTONDBLCLK()
    ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_COLLAPSE_BRANCH, OnCollapseBranch)
    ON_COMMAND(ID_EXPAND_BRANCH, OnExpandBranch)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PrestationsTreeCtrl
//---------------------------------------------------------------------------
PSS_PrestationsTreeCtrl::PSS_PrestationsTreeCtrl(const CString& rootName, PSS_LogicalPrestationsEntity* pLogicalPrestationRoot) :
    PSS_TreeCtrl(),
    m_pLogicalPrestationRoot(pLogicalPrestationRoot),
    m_hUserGroupRoot(NULL),
    m_RootName(rootName),
    m_HasBeenInitialized(false)
{}
//---------------------------------------------------------------------------
PSS_PrestationsTreeCtrl::~PSS_PrestationsTreeCtrl()
{}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::Initialize(const CString& rootName, PSS_LogicalPrestationsEntity* pLogicalPrestationRoot)
{
    m_pLogicalPrestationRoot = pLogicalPrestationRoot;
    m_RootName               = rootName;

    DestroyTree();
    LoadTree();
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::Release()
{
    DestroyTree();
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::Refresh()
{
    // save the state
    SaveCollapsedState();

    DestroyTree();
    LoadTree();

    // restore the previously saved state
    RestoreCollapsedStateToTreeCtrl();
}
//---------------------------------------------------------------------------
PSS_PrestationsEntity* PSS_PrestationsTreeCtrl::GetSelectedPrestationEntity()
{
    return GetPrestationEntity(GetSelectedItem());
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity* PSS_PrestationsTreeCtrl::GetSelectedLogicalPrestation()
{
    return GetLogicalPrestation(GetSelectedItem());
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity* PSS_PrestationsTreeCtrl::GetSelectedLogicalPrestationOwner()
{
    return GetOwnerPrestation(GetSelectedItem());
}
//---------------------------------------------------------------------------
bool PSS_PrestationsTreeCtrl::IsRootSelected() const
{
    HTREEITEM hItem = GetSelectedItem();
    return (hItem && (hItem == GetRootItem()));
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::AddPrestation(PSS_LogicalPrestationsEntity* pLogicalPrestation,
                                            PSS_LogicalPrestationsEntity* pParentLogicalPrestation)
{
    if (!m_hUserGroupRoot || !pLogicalPrestation)
        return;

    HTREEITEM hParentTreeItem = m_hUserGroupRoot;

    // find the tree item for the parent
    if (pParentLogicalPrestation)
    {
        // find the model
        ITreeData* pData = FindElementFromDataSet(pParentLogicalPrestation);

        if (pData)
            hParentTreeItem = FindItemData(pData, HTREEITEM(NULL));

        // if not found, set the root as parent
        if (!hParentTreeItem)
            hParentTreeItem = m_hUserGroupRoot;
    }

    // insert the group in the tree
    AddLogicalPrestationItem(pLogicalPrestation, hParentTreeItem);

    // expand the parent
    ExpandBranch(hParentTreeItem);
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::RemovePrestation(PSS_LogicalPrestationsEntity* pLogicalPrestation)
{
    if (!m_hUserGroupRoot || !pLogicalPrestation)
        return;

    ITreeData* pData = FindElementFromDataSet(pLogicalPrestation);

    if (pData)
    {
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
            DeleteItem(hItem);
    }
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::ModifyPrestation(PSS_LogicalPrestationsEntity* pLogicalPrestation)
{
    if (!m_hUserGroupRoot || !pLogicalPrestation)
        return;

    ITreeData* pData = FindElementFromDataSet(pLogicalPrestation);

    if (pData)
    {
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
            ModifyLogicalPrestationItem(pLogicalPrestation, hItem);
    }
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::OnNewPrestation()
{
    PSS_LogicalPrestationsEntity* pLogicalPrestation = GetSelectedLogicalPrestation();

    // if a group selected
    if (pLogicalPrestation)
    {
        ASSERT(m_pLogicalPrestationRoot);

        // ask for the name
        PSS_PrestationsInfoDlg dlg(IDS_NEW_PRESTATION_T, pLogicalPrestation);

        if (dlg.DoModal() == IDOK)
        {
            PSS_LogicalPrestationsEntity* pNewGroup = m_pLogicalPrestationRoot->AddPrestation(dlg.GetName(),
                                                                                              dlg.GetDescription(),
                                                                                              pLogicalPrestation);

            if (pNewGroup)
            {
                // add the prestation to the tree
                AddPrestation(pNewGroup, pLogicalPrestation);

                // modified
                m_pLogicalPrestationRoot->SetModifiedFlag();
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::OnDeletePrestation()
{
    if (IsRootSelected())
        return;

    PSS_LogicalPrestationsEntity* pLogicalPrestation = GetSelectedLogicalPrestation();

    if (pLogicalPrestation && pLogicalPrestation != m_pLogicalPrestationRoot)
    {
        ASSERT(m_pLogicalPrestationRoot);

        // remove prestation from the workspace
        m_pLogicalPrestationRoot->RemovePrestation(pLogicalPrestation);

        // delete the prestation name from the tree
        RemovePrestation(pLogicalPrestation);

        // modified
        m_pLogicalPrestationRoot->SetModifiedFlag();
    }
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::OnRenamePrestation()
{
    if (IsRootSelected())
        return;

    PSS_LogicalPrestationsEntity* pLogicalPrestation = GetSelectedLogicalPrestation();

    if (pLogicalPrestation)
    {
        ASSERT(m_pLogicalPrestationRoot);

        PSS_LogicalPrestationsEntity* pParent = dynamic_cast<PSS_LogicalPrestationsEntity*>(pLogicalPrestation->GetParent());

        PSS_PrestationsInfoDlg dlg(IDS_RENAME_PRESTATION_T,
                                   pParent ? pParent : pLogicalPrestation,
                                   pLogicalPrestation->GetEntityName(),
                                   pLogicalPrestation->GetEntityDescription());

        if (dlg.DoModal() == IDOK)
        {
            pLogicalPrestation->SetEntityName(dlg.GetName());
            pLogicalPrestation->SetEntityDescription(dlg.GetDescription());

            // modify the group name
            ModifyPrestation(pLogicalPrestation);

            // modified
            m_pLogicalPrestationRoot->SetModifiedFlag();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::OnMovePrestation()
{
    ZBPrestationsEntity* pPrestation = GetSelectedLogicalPrestation();

    if (pPrestation)
    {
        ASSERT(m_pLogicalPrestationRoot);

        PSS_SelectPrestationDlg dlg(IDS_PRS_MOVE_T, m_pLogicalPrestationRoot, true);

        if (dlg.DoModal() == IDOK)
        {
            PSS_LogicalPrestationsEntity* pEntity = dynamic_cast<PSS_LogicalPrestationsEntity*>(dlg.GetSelectedPrestationEntity());

            // if an entity was selected, and if it's not the same
            if (pEntity && pEntity != pPrestation)
            {
                // move the element, and assign the new parent
                pEntity->MovePrestation(pPrestation);

                // modified
                m_pLogicalPrestationRoot->SetModifiedFlag();

                // refresh the tree
                Refresh();
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::OnPrestationProperties()
{
    PSS_PrestationsEntity* pEntity = GetSelectedPrestationEntity();

    if (pEntity)
    {
        PSS_LogicalPrestationsEntity* pLogicalPrestation = GetSelectedLogicalPrestation();
        ASSERT(m_pLogicalPrestationRoot);

        PSS_LogicalPrestationsEntity* pParent = dynamic_cast<PSS_LogicalPrestationsEntity*>(pEntity->GetParent());

        PSS_PrestationsInfoDlg dlg(IDS_PRESTATION_PROPERTY_T,
                                   pParent ? pParent : m_pLogicalPrestationRoot,
                                   pEntity->GetEntityName(),
                                   pEntity->GetEntityDescription(),
                                   true);

        if (dlg.DoModal() == IDOK)
        {
            if (pLogicalPrestation)
                pLogicalPrestation->SetEntityDescription(dlg.GetDescription());

            // modified
            m_pLogicalPrestationRoot->SetModifiedFlag();
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_PrestationsTreeCtrl::CanNewPrestation()
{
    return GetSelectedLogicalPrestation();
}
//---------------------------------------------------------------------------
bool PSS_PrestationsTreeCtrl::CanDeletePrestation()
{
    return (GetSelectedLogicalPrestation() && GetSelectedLogicalPrestation() != m_pLogicalPrestationRoot);
}
//---------------------------------------------------------------------------
bool PSS_PrestationsTreeCtrl::CanRenamePrestation()
{
    return GetSelectedLogicalPrestation();
}
//---------------------------------------------------------------------------
bool PSS_PrestationsTreeCtrl::CanPrestationProperties()
{
    return (GetSelectedPrestationEntity() || IsRootSelected());
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_LogicalPrestationsObserverMsg* pPrestationMsg = dynamic_cast<PSS_LogicalPrestationsObserverMsg*>(pMsg);

    if (pPrestationMsg)
        switch (pPrestationMsg->GetMessageID())
        {
            case g_InitPrestations:
            {
                PSS_LogicalPrestationsEntity* pLogicalPrestation =
                        dynamic_cast<PSS_LogicalPrestationsEntity*>(pPrestationMsg->GetEntity());

                if (pLogicalPrestation)
                    Initialize(pPrestationMsg->GetRootName(), pLogicalPrestation);

                break;
            }

            case g_ClosePrestations:
                DestroyTree();
                break;
        }
}
//---------------------------------------------------------------------------
int PSS_PrestationsTreeCtrl::HasContextMenu(CWnd* pWnd, const CPoint& point)
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
        if (GetPrestationEntity(hItem) == m_pLogicalPrestationRoot)
            idMenu = 1;
        else
        if (GetPrestationEntity(hItem))
            idMenu = 2;

    return idMenu;
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::ShowContextMenu(CWnd* pWnd, const CPoint& point)
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
BOOL PSS_PrestationsTreeCtrl::DestroyWindow()
{
    DestroyTree();

    return CWnd::DestroyWindow();
}
//---------------------------------------------------------------------------
int PSS_PrestationsTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_TreeCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    LoadTree();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // show the properties
    OnPrestationProperties();
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
    ShowContextMenu(pWnd, point);
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::OnItemExpanded(LPNMHDR pnmhdr, LRESULT* pLResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pnmhdr;
    *pLResult                = TRUE;
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::OnCollapseBranch()
{
    CollapseBranch(GetSelectedItem(), TRUE);
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::OnExpandBranch()
{
    ExpandBranch(GetSelectedItem(), TRUE);
}
//---------------------------------------------------------------------------
CObject* PSS_PrestationsTreeCtrl::GetDragObject(HTREEITEM dragItem)
{
    ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(dragItem));

    if (pObj && pObj->m_Type == ITreeData::IE_DT_Prestation)
        return pObj->m_pPrestation;

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::CreateTree()
{
    if (m_HasBeenInitialized)
        return;

    VERIFY(m_SubMenu.LoadMenu(IDR_PRESTATIONS_SUBMENUS));

    // set styles
    HasButtons();
    HasLines();
    LinesAtRoot();
    ShowSelectionAlways();

    // load images
    LoadImageList(IDB_IL_PRESTATIONS, 17, 1, RGB(255, 255, 255));
    m_HasBeenInitialized = true;
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::LoadTree()
{
    // create the tree. NOTE this function will do nothing if already created
    CreateTree();

    // no user group, do nothing
    if (!m_pLogicalPrestationRoot)
        return;

    m_hUserGroupRoot = AddTypeItem(m_RootName, g_PrestationsRootTreeItem);

    ProcessLogicalPrestationsGroup(m_pLogicalPrestationRoot, m_hUserGroupRoot);

    // expand the root
    ExpandRoot(TRUE);
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::DestroyTree()
{
    if (::IsWindow(GetSafeHwnd()))
        DeleteAllItems();

    // empty the data set first
    EmptyDataSet();
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::EmptyDataSet()
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        delete pElement;

    m_DataSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_PrestationsTreeCtrl::ProcessLogicalPrestationsGroup(PSS_LogicalPrestationsEntity* pLogicalPrestation,
                                                             HTREEITEM                     hParentTreeItem)
{
    // add the item
    HTREEITEM hGroupItem = AddLogicalPrestationItem(pLogicalPrestation, hParentTreeItem);

    if (pLogicalPrestation->ContainEntity())
    {
        const int count = pLogicalPrestation->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            PSS_LogicalPrestationsEntity* pEntity =
                    dynamic_cast<PSS_LogicalPrestationsEntity*>(pLogicalPrestation->GetEntityAt(i));

            if (!pEntity)
                continue;

            ProcessLogicalPrestationsGroup(pEntity, hGroupItem);
        }
    }
}
//---------------------------------------------------------------------------
HTREEITEM PSS_PrestationsTreeCtrl::AddTypeItem(const CString& name, int iconIndex, HTREEITEM hParentTreeItem)
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
HTREEITEM PSS_PrestationsTreeCtrl::AddLogicalPrestationItem(PSS_LogicalPrestationsEntity* pLogicalPrestation,
                                                            HTREEITEM                     hParentTreeItem)
{
    if (!pLogicalPrestation)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = g_PrestationsTreeItem;
    curTreeItem.item.iSelectedImage = g_PrestationsTreeItem;
    curTreeItem.item.pszText        = (char*)((const char*)pLogicalPrestation->GetEntityName());
    curTreeItem.item.lParam         = LPARAM(AddDataToSet(pLogicalPrestation));
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
BOOL PSS_PrestationsTreeCtrl::ModifyLogicalPrestationItem(PSS_LogicalPrestationsEntity* pLogicalPrestation,
                                                          HTREEITEM                     hItem)
{
    if (!pLogicalPrestation)
        return FALSE;

    return SetItemText(hItem, (char*)((const char*)pLogicalPrestation->GetEntityName()));
}
//---------------------------------------------------------------------------
PSS_PrestationsEntity* PSS_PrestationsTreeCtrl::GetPrestationEntity(HTREEITEM hItem)
{
    if (hItem)
    {
        ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(hItem));

        if (pObj && pObj->m_Type == ITreeData::IE_DT_Prestation)
            return pObj->m_pPrestation;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity* PSS_PrestationsTreeCtrl::GetLogicalPrestation(HTREEITEM hItem)
{
    if (hItem)
    {
        ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(hItem));

        if (pObj && pObj->m_Type == ITreeData::IE_DT_Prestation)
            return pObj->m_pPrestation;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity* PSS_PrestationsTreeCtrl::GetOwnerPrestation(HTREEITEM hItem)
{
    if (hItem)
    {
        PSS_LogicalPrestationsEntity* pLogicalPrestation = GetLogicalPrestation(hItem);

        if (pLogicalPrestation)
        {
            PSS_LogicalPrestationsEntity* pParent = dynamic_cast<PSS_LogicalPrestationsEntity*>(pLogicalPrestation->GetParent());

            // if a parent defined
            if (pParent)
                return pParent;

            return pLogicalPrestation;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PrestationsTreeCtrl::ITreeData* PSS_PrestationsTreeCtrl::FindElementFromDataSet(PSS_LogicalPrestationsEntity* pLogicalPrestation)
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Type == ITreeData::IE_DT_Prestation && pElement->m_pPrestation == pLogicalPrestation)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PrestationsTreeCtrl::ITreeData* PSS_PrestationsTreeCtrl::FindElementFromDataSet(const CString& str)
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Type == ITreeData::IE_DT_String && pElement->m_Str == str)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PrestationsTreeCtrl::ITreeData* PSS_PrestationsTreeCtrl::AddDataToSet(PSS_LogicalPrestationsEntity* pLogicalPrestation)
{
    std::unique_ptr<ITreeData> pData(new ITreeData(pLogicalPrestation));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
PSS_PrestationsTreeCtrl::ITreeData* PSS_PrestationsTreeCtrl::AddDataToSet(const CString& str)
{
    std::unique_ptr<ITreeData> pData(new ITreeData(str));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
