/****************************************************************************
 * ==> PSS_RulesTreeCtrl ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a rules tree controller                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RulesTreeCtrl.h"

// processsoft
#include "PSS_LogicalRulesEntity.h"
#include "PSS_LogicalRulesObserverMsg.h"
#include "ZVSelectRuleDlg.h"
#include "PSS_RulesInfoDlg.h"

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
const int g_RulesRootTreeItem = 0;
const int g_RulesTreeItem     = 1;
//---------------------------------------------------------------------------
// PSS_RulesTreeCtrl::ITreeData
//---------------------------------------------------------------------------
PSS_RulesTreeCtrl::ITreeData::ITreeData() :
    m_pRule(NULL),
    m_Type(IE_DT_Unknown)
{}
//---------------------------------------------------------------------------
PSS_RulesTreeCtrl::ITreeData::ITreeData(PSS_LogicalRulesEntity* pLogicalRule) :
    m_pRule(pLogicalRule),
    m_Type(IE_DT_Rule)
{}
//---------------------------------------------------------------------------
PSS_RulesTreeCtrl::ITreeData::ITreeData(const CString& str) :
    m_pRule(NULL),
    m_Type(IE_DT_String),
    m_Str(str)
{}
//---------------------------------------------------------------------------
PSS_RulesTreeCtrl::ITreeData::~ITreeData()
{}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_RulesTreeCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(PSS_RulesTreeCtrl)
    ON_WM_CREATE()
    ON_WM_LBUTTONDBLCLK()
    ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_COLLAPSE_BRANCH, OnCollapseBranch)
    ON_COMMAND(ID_EXPAND_BRANCH, OnExpandBranch)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_RulesTreeCtrl
//---------------------------------------------------------------------------
PSS_RulesTreeCtrl::PSS_RulesTreeCtrl(const CString& rootName, PSS_LogicalRulesEntity* pLogicalRuleRoot) :
    PSS_TreeCtrl(),
    m_pLogicalRuleRoot(pLogicalRuleRoot),
    m_hUserGroupRoot(NULL),
    m_RootName(rootName),
    m_HasBeenInitialized(false)
{}
//---------------------------------------------------------------------------
PSS_RulesTreeCtrl::~PSS_RulesTreeCtrl()
{}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::Initialize(const CString& rootName, PSS_LogicalRulesEntity* pLogicalRuleRoot)
{
    m_pLogicalRuleRoot = pLogicalRuleRoot;
    m_RootName         = rootName;

    DestroyTree();
    LoadTree();
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::Release()
{
    DestroyTree();
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::Refresh()
{
    // save the state
    SaveCollapsedState();

    DestroyTree();
    LoadTree();

    // restore the previously saved state
    RestoreCollapsedStateToTreeCtrl();
}
//---------------------------------------------------------------------------
PSS_RulesEntity* PSS_RulesTreeCtrl::GetSelectedRuleEntity()
{
    return GetRuleEntity(GetSelectedItem());
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity* PSS_RulesTreeCtrl::GetSelectedLogicalRule()
{
    return GetLogicalRule(GetSelectedItem());
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity* PSS_RulesTreeCtrl::GetSelectedLogicalRuleOwner()
{
    return GetOwnerRule(GetSelectedItem());
}
//---------------------------------------------------------------------------
bool PSS_RulesTreeCtrl::IsRootSelected() const
{
    HTREEITEM hItem = GetSelectedItem();
    return (hItem && (hItem == GetRootItem()));
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::AddRule(PSS_LogicalRulesEntity* pLogicalRule, PSS_LogicalRulesEntity* pParentLogicalRule)
{
    if (!m_hUserGroupRoot || !pLogicalRule)
        return;

    HTREEITEM hParentTreeItem = m_hUserGroupRoot;

    // find the tree item for the parent
    if (pParentLogicalRule)
    {
        // find the model
        ITreeData* pData = FindElementFromDataSet(pParentLogicalRule);

        if (pData)
            hParentTreeItem = FindItemData(pData, HTREEITEM(NULL));

        // if not found, set the root as parent
        if (!hParentTreeItem)
            hParentTreeItem = m_hUserGroupRoot;
    }

    // insert the group in the tree
    AddLogicalRuleItem(pLogicalRule, hParentTreeItem);

    // expand the parent
    ExpandBranch(hParentTreeItem);
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::RemoveRule(PSS_LogicalRulesEntity* pLogicalRule)
{
    if (!m_hUserGroupRoot || !pLogicalRule)
        return;

    ITreeData* pData = FindElementFromDataSet(pLogicalRule);

    if (pData)
    {
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
            DeleteItem(hItem);
    }
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::ModifyRule(PSS_LogicalRulesEntity* pLogicalRule)
{
    if (!m_hUserGroupRoot || !pLogicalRule)
        return;

    ITreeData* pData = FindElementFromDataSet(pLogicalRule);

    if (pData)
    {
        HTREEITEM hItem = FindItemData(pData, NULL);

        if (hItem)
            ModifyLogicalRuleItem(pLogicalRule, hItem);
    }
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::OnNewRule()
{
    PSS_LogicalRulesEntity* pLogicalRule = GetSelectedLogicalRule();

    // if a group selected
    if (pLogicalRule)
    {
        ASSERT(m_pLogicalRuleRoot);

        // ask for the name
        PSS_RulesInfoDlg dlg(IDS_NEW_RULE_T, pLogicalRule);

        if (dlg.DoModal() == IDOK)
        {
            PSS_LogicalRulesEntity* pNewGroup = m_pLogicalRuleRoot->AddRule(dlg.GetName(),
                                                                            dlg.GetDescription(),
                                                                            pLogicalRule);

            if (pNewGroup)
            {
                // add the rule to the tree
                AddRule(pNewGroup, pLogicalRule);

                // modified
                m_pLogicalRuleRoot->SetModifiedFlag();
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::OnDeleteRule()
{
    if (IsRootSelected())
        return;

    PSS_LogicalRulesEntity* pLogicalRule = GetSelectedLogicalRule();

    if (pLogicalRule && pLogicalRule != m_pLogicalRuleRoot)
    {
        ASSERT(m_pLogicalRuleRoot);

        // remove rule from the workspace
        m_pLogicalRuleRoot->RemoveRule(pLogicalRule);

        // delete the rule name from the tree
        RemoveRule(pLogicalRule);

        // modified
        m_pLogicalRuleRoot->SetModifiedFlag();
    }
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::OnRenameRule()
{
    if (IsRootSelected())
        return;

    PSS_LogicalRulesEntity* pLogicalRule = GetSelectedLogicalRule();

    if (pLogicalRule)
    {
        ASSERT(m_pLogicalRuleRoot);

        PSS_LogicalRulesEntity* pParent = dynamic_cast<PSS_LogicalRulesEntity*>(pLogicalRule->GetParent());

        PSS_RulesInfoDlg dlg(IDS_RENAME_RULE_T,
                             pParent ? pParent : pLogicalRule,
                             pLogicalRule->GetEntityName(),
                             pLogicalRule->GetEntityDescription());

        if (dlg.DoModal() == IDOK)
        {
            pLogicalRule->SetEntityName(dlg.GetName());
            pLogicalRule->SetEntityDescription(dlg.GetDescription());

            // modify the group name
            ModifyRule(pLogicalRule);

            // modified
            m_pLogicalRuleRoot->SetModifiedFlag();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::OnMoveRule()
{
    PSS_RulesEntity* pRule = GetSelectedLogicalRule();

    if (pRule)
    {
        ASSERT(m_pLogicalRuleRoot);

        ZVSelectRuleDlg dlg(IDS_RUL_MOVE_T, m_pLogicalRuleRoot, true);

        if (dlg.DoModal() == IDOK)
        {
            PSS_LogicalRulesEntity* pEntity = dynamic_cast<PSS_LogicalRulesEntity*>(dlg.GetSelectedRuleEntity());

            // if an entity was selcted, and if it's not the same
            if (pEntity && pEntity != pRule)
            {
                // move the element and assign the new parent
                pEntity->MoveRule(pRule);

                // modified
                m_pLogicalRuleRoot->SetModifiedFlag();

                // refresh the tree
                Refresh();
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::OnRuleProperties()
{
    PSS_RulesEntity* pEntity = GetSelectedRuleEntity();

    if (pEntity)
    {
        PSS_LogicalRulesEntity* pLogicalRule = GetSelectedLogicalRule();
        ASSERT(m_pLogicalRuleRoot);

        PSS_LogicalRulesEntity* pParent = dynamic_cast<PSS_LogicalRulesEntity*>(pEntity->GetParent());

        PSS_RulesInfoDlg dlg(IDS_RULE_PROPERTY_T,
                             pParent ? pParent : m_pLogicalRuleRoot,
                             pEntity->GetEntityName(),
                             pEntity->GetEntityDescription(),
                             true);

        if (dlg.DoModal() == IDOK)
        {
            if (pLogicalRule)
                pLogicalRule->SetEntityDescription(dlg.GetDescription());

            // modified
            m_pLogicalRuleRoot->SetModifiedFlag();
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_RulesTreeCtrl::CanNewRule()
{
    return GetSelectedLogicalRule();
}
//---------------------------------------------------------------------------
bool PSS_RulesTreeCtrl::CanDeleteRule()
{
    return (GetSelectedLogicalRule() && GetSelectedLogicalRule() != m_pLogicalRuleRoot);
}
//---------------------------------------------------------------------------
bool PSS_RulesTreeCtrl::CanRenameRule()
{
    return GetSelectedLogicalRule();
}
//---------------------------------------------------------------------------
bool PSS_RulesTreeCtrl::CanRuleProperties()
{
    return (GetSelectedRuleEntity() || IsRootSelected());
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_LogicalRulesObserverMsg* pRuleMsg = dynamic_cast<PSS_LogicalRulesObserverMsg*>(pMsg);

    if (pRuleMsg)
        switch (pRuleMsg->GetMessageID())
        {
            case g_InitRules:
            {
                PSS_LogicalRulesEntity* pLogicalRule = dynamic_cast<PSS_LogicalRulesEntity*>(pRuleMsg->GetEntity());

                if (pLogicalRule)
                    Initialize(pRuleMsg->GetRootName(), pLogicalRule);

                break;
            }

            case g_CloseRules:
                DestroyTree();
                break;
        }
}
//---------------------------------------------------------------------------
int PSS_RulesTreeCtrl::HasContextMenu(CWnd* pWnd, const CPoint& point)
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
        if (GetRuleEntity(hItem) == m_pLogicalRuleRoot)
            idMenu = 1;
        else
        if (GetRuleEntity(hItem))
            idMenu = 2;

    return idMenu;
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::ShowContextMenu(CWnd* pWnd, const CPoint& point)
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

    if ((hItem != NULL) && (TVHT_ONITEM & flags))
    {
        Select(hItem, TVGN_CARET);
        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_RulesTreeCtrl::DestroyWindow()
{
    DestroyTree();

    return CWnd::DestroyWindow();
}
//---------------------------------------------------------------------------
int PSS_RulesTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_TreeCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    LoadTree();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // show the properties
    OnRuleProperties();
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
    ShowContextMenu(pWnd, point);
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::OnItemExpanded(LPNMHDR pnmhdr, LRESULT* pLResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pnmhdr;
    *pLResult                = TRUE;
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::OnCollapseBranch()
{
    CollapseBranch(GetSelectedItem(), TRUE);
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::OnExpandBranch()
{
    ExpandBranch(GetSelectedItem(), TRUE);
}
//---------------------------------------------------------------------------
CObject* PSS_RulesTreeCtrl::GetDragObject(HTREEITEM dragItem)
{
    ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(dragItem));

    if (pObj && pObj->m_Type == ITreeData::IE_DT_Rule)
        return pObj->m_pRule;

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::CreateTree()
{
    if (m_HasBeenInitialized)
        return;

    VERIFY(m_SubMenu.LoadMenu(IDR_RULES_SUBMENUS));

    // set styles
    HasButtons();
    HasLines();
    LinesAtRoot();
    ShowSelectionAlways();

    // load images
    LoadImageList(IDB_IL_RULES, 17, 1, RGB(255, 255, 255));
    m_HasBeenInitialized = true;
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::LoadTree()
{
    // create the tree. NOTE this function will do nothing if already created
    CreateTree();

    // no user group, do nothing
    if (!m_pLogicalRuleRoot)
        return;

    m_hUserGroupRoot = AddTypeItem(m_RootName, g_RulesRootTreeItem);

    ProcessLogicalRulesGroup(m_pLogicalRuleRoot, m_hUserGroupRoot);

    // expand the root
    ExpandRoot(TRUE);
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::DestroyTree()
{
    if (::IsWindow(GetSafeHwnd()))
        DeleteAllItems();

    // empty the data set first
    EmptyDataSet();
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::EmptyDataSet()
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        delete pElement;

    m_DataSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_RulesTreeCtrl::ProcessLogicalRulesGroup(PSS_LogicalRulesEntity* pLogicalRule, HTREEITEM hParentTreeItem)
{
    // add the item
    HTREEITEM hGroupItem = AddLogicalRuleItem(pLogicalRule, hParentTreeItem);

    if (pLogicalRule->ContainEntity())
    {
        const int count = pLogicalRule->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            PSS_LogicalRulesEntity* pEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pLogicalRule->GetEntityAt(i));

            if (!pEntity)
                continue;

            ProcessLogicalRulesGroup(pEntity, hGroupItem);
        }
    }
}
//---------------------------------------------------------------------------
HTREEITEM PSS_RulesTreeCtrl::AddTypeItem(const CString& name, int iconIndex, HTREEITEM hParentTreeItem)
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
HTREEITEM PSS_RulesTreeCtrl::AddLogicalRuleItem(PSS_LogicalRulesEntity* pLogicalRule,
                                                HTREEITEM               hParentTreeItem)
{
    if (!pLogicalRule)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = g_RulesTreeItem;
    curTreeItem.item.iSelectedImage = g_RulesTreeItem;
    curTreeItem.item.pszText        = (char*)((const char*)pLogicalRule->GetEntityName());
    curTreeItem.item.lParam         = LPARAM(AddDataToSet(pLogicalRule));
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
BOOL PSS_RulesTreeCtrl::ModifyLogicalRuleItem(PSS_LogicalRulesEntity* pLogicalRule,
                                              HTREEITEM               hItem)
{
    if (!pLogicalRule)
        return FALSE;

    return SetItemText(hItem, (char*)((const char*)pLogicalRule->GetEntityName()));
}
//---------------------------------------------------------------------------
PSS_RulesEntity* PSS_RulesTreeCtrl::GetRuleEntity(HTREEITEM hItem)
{
    if (hItem)
    {
        ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(hItem));

        if (pObj && pObj->m_Type == ITreeData::IE_DT_Rule)
            return pObj->m_pRule;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity* PSS_RulesTreeCtrl::GetLogicalRule(HTREEITEM hItem)
{
    if (hItem)
    {
        ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(hItem));

        if (pObj && pObj->m_Type == ITreeData::IE_DT_Rule)
            return pObj->m_pRule;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity* PSS_RulesTreeCtrl::GetOwnerRule(HTREEITEM hItem)
{
    if (hItem)
    {
        PSS_LogicalRulesEntity* pLogicalRule = GetLogicalRule(hItem);

        if (pLogicalRule)
        {
            PSS_LogicalRulesEntity* pParent = dynamic_cast<PSS_LogicalRulesEntity*>(pLogicalRule->GetParent());

            // if a parent defined
            if (pParent)
                return pParent;

            return pLogicalRule;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_RulesTreeCtrl::ITreeData* PSS_RulesTreeCtrl::FindElementFromDataSet(PSS_LogicalRulesEntity* pLogicalRule)
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Type == ITreeData::IE_DT_Rule && pElement->m_pRule == pLogicalRule)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_RulesTreeCtrl::ITreeData* PSS_RulesTreeCtrl::FindElementFromDataSet(const CString& str)
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Type == ITreeData::IE_DT_String && pElement->m_Str == str)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_RulesTreeCtrl::ITreeData* PSS_RulesTreeCtrl::AddDataToSet(PSS_LogicalRulesEntity* pLogicalRule)
{
    std::unique_ptr<ITreeData> pData(new ITreeData(pLogicalRule));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
PSS_RulesTreeCtrl::ITreeData* PSS_RulesTreeCtrl::AddDataToSet(const CString& str)
{
    std::unique_ptr<ITreeData> pData(new ITreeData(str));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
