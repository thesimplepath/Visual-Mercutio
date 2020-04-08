/****************************************************************************
 * ==> PSS_WorkspaceTreeCtrl -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace tree controller                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceTreeCtrl.h"

// processsoft
#include "PSS_WorkspaceEnv.h"
#include "PSS_WorkspaceFileEntity.h"
#include "PSS_WorkspaceGroupEntity.h"
#include "PSS_WorkspaceObserverMsg.h"
#include "PSS_FileDialog.h"
#include "PSS_WorkspaceGroupNameDlg.h"
#include "PSS_WorkspaceRenameGroupNameDlg.h"

// resources
#include "zBaseLibRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const int g_WorkspaceEnvTreeItem = 0;
const int g_GroupTreeItem        = 1;
const int g_GroupOpenTreeItem    = 2;
const int g_AnyFileTreeItem      = 3;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WorkspaceTreeCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(PSS_WorkspaceTreeCtrl)
    ON_WM_CREATE()
    ON_WM_LBUTTONDBLCLK()
    ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
    ON_WM_CONTEXTMENU()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WorkspaceTreeCtrl::IData
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData::IData() :
    m_Type(IE_DT_Unknown),
    m_pWorkspaceEnv(NULL),
    m_pGroup(NULL),
    m_pFile(NULL)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData::IData(PSS_WorkspaceEnv* pWorkspaceEnv) :
    m_Type(IE_DT_WorkspaceEnv),
    m_pWorkspaceEnv(pWorkspaceEnv),
    m_pGroup(NULL),
    m_pFile(NULL)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData::IData(PSS_WorkspaceGroupEntity* pGroup) :
    m_Type(IE_DT_Group),
    m_pWorkspaceEnv(NULL),
    m_pGroup(pGroup),
    m_pFile(NULL)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData::IData(PSS_WorkspaceFileEntity* pFile) :
    m_Type(IE_DT_File),
    m_pWorkspaceEnv(NULL),
    m_pGroup(NULL),
    m_pFile(pFile)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData::IData(const CString& str) :
    m_Type(IE_DT_String),
    m_pWorkspaceEnv(NULL),
    m_pGroup(NULL),
    m_pFile(NULL),
    m_Str(str)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData::~IData()
{
    m_Str.Empty();
}
//---------------------------------------------------------------------------
// PSS_WorkspaceTreeCtrl
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::PSS_WorkspaceTreeCtrl(const CString& rootName, PSS_WorkspaceEnv* pWorkspaceEnv) :
    PSS_TreeCtrl(),
    m_hRootWorkspaceEnv(NULL),
    m_pWorkspaceEnv(pWorkspaceEnv),
    m_RootName(rootName)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::~PSS_WorkspaceTreeCtrl()
{}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::Initialize(const CString& rootName, PSS_WorkspaceEnv* pWorkspaceEnv)
{
    m_pWorkspaceEnv = pWorkspaceEnv;
    m_RootName      = rootName;

    LoadTree();
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::Refresh()
{
    DestroyTree();
    LoadTree();
}
//---------------------------------------------------------------------------
PSS_WorkspaceEntity* PSS_WorkspaceTreeCtrl::GetSelectedEntity()
{
    return GetEntity(GetSelectedItem());
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceTreeCtrl::GetSelectedGroup()
{
    return GetGroup(GetSelectedItem());
}
//---------------------------------------------------------------------------
PSS_WorkspaceFileEntity* PSS_WorkspaceTreeCtrl::GetSelectedFile()
{
    return GetFile(GetSelectedItem());
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceTreeCtrl::GetSelectedOwnerGroup()
{
    return GetOwnerGroup(GetSelectedItem());
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceTreeCtrl::IsRootSelected() const
{
    return (GetSelectedItem() && (GetSelectedItem() == GetRootItem()));
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::AddGroup(PSS_WorkspaceGroupEntity* pGroup, PSS_WorkspaceGroupEntity* pParentGroup)
{
    if (!m_hRootWorkspaceEnv || !pGroup)
        return;

    HTREEITEM hParentTreeItem = m_hRootWorkspaceEnv;

    // find the tree item for the parent
    if (pParentGroup)
    {
        // find the model
        IData* pData = FindElementFromDataSet(pParentGroup);

        if (pData)
            // from item, in fact from root
            hParentTreeItem = FindItemData(pData, HTREEITEM(NULL));

        // if not found, set the root as parent
        if (!hParentTreeItem)
            hParentTreeItem = m_hRootWorkspaceEnv;
    }

    // insert the group in the tree
    HTREEITEM hGroupItem = AddGroupItem(pGroup, hParentTreeItem);

    if (hGroupItem)
        EnsureVisible(hGroupItem);
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::RemoveGroup(PSS_WorkspaceGroupEntity* pGroup)
{
    if (!m_hRootWorkspaceEnv || !pGroup)
        return;

    IData* pData = FindElementFromDataSet(pGroup);

    if (pData)
    {
        // from item, in fact from root
        HTREEITEM hItem = FindItemData(pData, HTREEITEM(NULL));

        if (hItem)
        {
            DeleteItem(hItem);
            DeleteElementFromDataSet(pGroup);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::ModifyGroup(PSS_WorkspaceGroupEntity* pGroup)
{
    ModifyEntity(pGroup);
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::AddFile(PSS_WorkspaceFileEntity* pFile, PSS_WorkspaceGroupEntity* pParentGroup)
{
    if (!m_hRootWorkspaceEnv || !pFile || !pParentGroup)
        return;

    HTREEITEM hParentTreeItem = m_hRootWorkspaceEnv;

    // find the tree item for the parent
    if (pParentGroup)
    {
        // find the model
        IData* pData = FindElementFromDataSet(pParentGroup);

        if (pData)
            // from item, in fact from root
            hParentTreeItem = FindItemData(pData, HTREEITEM(NULL));

        // if not found, set the root as parent
        if (!hParentTreeItem)
            hParentTreeItem = m_hRootWorkspaceEnv;
    }

    // insert the file item in the tree
    HTREEITEM hFileItem = AddFileItem(pFile, hParentTreeItem);

    if (hFileItem)
        EnsureVisible(hFileItem);
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::RemoveFile(PSS_WorkspaceFileEntity* pFile)
{
    if (!m_hRootWorkspaceEnv || !pFile)
        return;

    IData* pData = FindElementFromDataSet(pFile);

    if (pData)
    {
        // from item, in fact from root
        HTREEITEM hItem = FindItemData(pData, HTREEITEM(NULL));

        if (hItem)
        {
            DeleteItem(hItem);
            DeleteElementFromDataSet(pFile);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::ModifyFile(PSS_WorkspaceFileEntity* pFile)
{
    ModifyEntity(pFile);
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::OnWksNewGroup()
{
    PSS_WorkspaceGroupEntity* pGroup = GetSelectedGroup();

    // if the root is selected, set the group as the environment
    if (IsRootSelected())
        pGroup = m_pWorkspaceEnv;

    // if a group selected
    if (pGroup)
    {
        ASSERT(m_pWorkspaceEnv);

        // ask for the name
        PSS_WorkspaceGroupNameDlg dlg(pGroup);

        if (dlg.DoModal() == IDOK)
        {
            PSS_WorkspaceGroupEntity* pNewGroup = m_pWorkspaceEnv->AddGroup(dlg.GetGroupName(),
                                                                            dlg.GetExtensions(),
                                                                            pGroup);

            if (pNewGroup)
            {
                // now, add the file from the tree
                AddGroup(pNewGroup, pGroup);

                // modified
                m_pWorkspaceEnv->SetModifiedFlag();
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::OnWksDeleteGroup()
{
    if (IsRootSelected())
        return;

    PSS_WorkspaceGroupEntity* pGroup = GetSelectedGroup();

    if (pGroup)
    {
        ASSERT(m_pWorkspaceEnv);

        // remove group from the workspace
        m_pWorkspaceEnv->RemoveGroup(pGroup);

        // now delete the group name from the tree
        RemoveGroup(pGroup);

        // modified
        m_pWorkspaceEnv->SetModifiedFlag();
    }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::OnWksRenameGroup()
{
    if (IsRootSelected())
        return;

    PSS_WorkspaceGroupEntity* pGroup = GetSelectedGroup();

    if (pGroup)
    {
        ASSERT(m_pWorkspaceEnv);

        PSS_WorkspaceRenameGroupNameDlg dlg(pGroup->GetEntityName(), dynamic_cast<PSS_WorkspaceGroupEntity*>(pGroup->GetParent()));

        if (dlg.DoModal() == IDOK)
        {
            pGroup->SetEntityName(dlg.GetGroupName());

            // now modify the group name
            ModifyGroup(pGroup);

            // modified
            m_pWorkspaceEnv->SetModifiedFlag();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::OnWksAddFile()
{
    if (GetSelectedGroup() || IsRootSelected())
    {
        CString title;
        VERIFY(title.LoadString(IDS_WORKSPACE_FILEADD_T));

        // set the "*.*" files filter
        CString filters;
        VERIFY(filters.LoadString(AFX_IDS_ALLFILTER));

        filters += (char)'\0';
        filters += _T("*.*");
        filters += (char)'\0';

        PSS_FileDialog fileDialog(title, filters, 1);

        if (fileDialog.DoModal() == IDOK)
        {
            ASSERT(m_pWorkspaceEnv);

            // if the root is selected, use add file to project for inserting the file at the best place
            if (IsRootSelected())
                OnAddFileToProject(fileDialog.GetFileName());
            else
            {
                // add file to the workspace
                PSS_WorkspaceFileEntity* pFile = m_pWorkspaceEnv->AddFile(fileDialog.GetFileName(), GetSelectedGroup());

                // add the file from the tree
                AddFile(pFile, GetSelectedGroup());
            }

            // modified
            m_pWorkspaceEnv->SetModifiedFlag();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::OnWksDeleteFile()
{
    PSS_WorkspaceFileEntity* pFile = GetSelectedFile();

    if (pFile)
    {
        ASSERT(m_pWorkspaceEnv);

        // remove file from the workspace
        m_pWorkspaceEnv->RemoveFile(pFile);

        // modified
        m_pWorkspaceEnv->SetModifiedFlag();

        // remove the file from the tree
        RemoveFile(pFile);
    }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::OnWksOpenFile()
{
    if (GetSelectedFile())
    {
        GetSelectedFile()->OpenFile();

        ASSERT(m_pWorkspaceEnv);

        // modified
        m_pWorkspaceEnv->SetModifiedFlag();
    }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::OnWksProperties()
{
    if (GetSelectedEntity())
        if (GetSelectedEntity()->PropertiesVisible())
        {
            ModifyEntity(GetSelectedEntity());

            // modified
            m_pWorkspaceEnv->SetModifiedFlag();
        }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::OnAddFileToProject(const CString& fileName)
{
    PSS_WorkspaceGroupEntity* pGroup = GetFileBestGroup(fileName);

    if (pGroup)
    {
        ASSERT(m_pWorkspaceEnv);

        // add file to the workspace
        PSS_WorkspaceFileEntity* pFile = m_pWorkspaceEnv->AddFile(fileName, pGroup);

        // modified
        m_pWorkspaceEnv->SetModifiedFlag();

        // add the file from the tree
        AddFile(pFile, pGroup);
    }
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceTreeCtrl::CanAddCurrentFileToProject(const CString& fileName)
{
    return (!HasItems() || FileExist(fileName) ? false : true);
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_WorkspaceObserverMsg* pObserverMsg = dynamic_cast<PSS_WorkspaceObserverMsg*>(pMsg);

    if (!pObserverMsg)
        return;

    switch (pObserverMsg->GetMessageID())
    {
        case UM_INITWORKSPACE:  Initialize(pObserverMsg->GetEnv()->GetEntityName(), pObserverMsg->GetEnv()); break;
        case UM_CLOSEWORKSPACE: DestroyTree();                                                               break;
    }
}
//---------------------------------------------------------------------------
int PSS_WorkspaceTreeCtrl::HasContextMenu(CWnd* pWnd, const CPoint& point)
{
    CPoint pt(point);
    ScreenToClient(&pt);

    UINT      flags;
    HTREEITEM hItem = HitTest(pt, &flags);

    int menuID = -1;

    // show the right sub-menu
    if (hItem && (TVHT_ONITEM & flags))
        if (hItem == GetRootItem())
            menuID = 0;
        else
        if (GetGroup(hItem))
            menuID = 1;
        else
        if (GetFile(hItem))
            menuID = 2;

    return menuID;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::ShowContextMenu(CWnd* pWnd, const CPoint& point)
{
    const int menuID = HasContextMenu(pWnd, point);

    if (menuID == -1)
        return;

    CMenu* pPopup = m_SubMenu.GetSubMenu(menuID);
    ASSERT(pPopup);

    CWnd* pWndPopupOwner = this;

    while (pWndPopupOwner->GetStyle() & WS_CHILD)
        pWndPopupOwner = pWndPopupOwner->GetParent();

    CPoint pt(point);
    ScreenToClient(&pt);

    UINT      flags;
    HTREEITEM hItem = HitTest(pt, &flags);

    if (hItem && (TVHT_ONITEM & flags))
    {
        Select(hItem, TVGN_CARET);

        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                               point.x,
                               point.y,
                               pWndPopupOwner);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceTreeCtrl::DestroyWindow()
{
    DestroyTree();

    return CWnd::DestroyWindow();
}
//---------------------------------------------------------------------------
int PSS_WorkspaceTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_TreeCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    VERIFY(m_SubMenu.LoadMenu(IDR_WORKSPACE_SUBMENUS));

    CreateTree();
    LoadTree();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // open the file if it is a file
    OnWksOpenFile();
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
    ShowContextMenu(pWnd, point);
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pnmhdr;

    // expand
    if (pNMTreeView->action == 2)
    {
        // not the root item, only a simple group
        if (pNMTreeView->itemNew.hItem != GetRootItem())
        {
            TVITEM item         = {0};
            item.mask           = TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
            item.hItem          = pNMTreeView->itemNew.hItem;
            item.iImage         = g_GroupOpenTreeItem;
            item.iSelectedImage = g_GroupOpenTreeItem;
            SetItem(&item);
        }
    }
    // collapse
    else
    if (pNMTreeView->action == 1)
        // not the root item, only a simple group
        if (pNMTreeView->itemNew.hItem != GetRootItem())
        {
            TVITEM item         = {0};
            item.mask           = TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
            item.hItem          = pNMTreeView->itemNew.hItem;
            item.iImage         = g_GroupTreeItem;
            item.iSelectedImage = g_GroupTreeItem;
            SetItem(&item);
        }

    *pLResult = TRUE;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::CreateTree()
{
    // set styles
    HasButtons();
    HasLines();
    LinesAtRoot();
    ShowSelectionAlways();

    // load images
    LoadImageList(IDB_IL_WORKSPACEENV, 17, 1, RGB(255, 255, 255));
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::LoadTree()
{
    if (!m_pWorkspaceEnv)
        return;

    m_hRootWorkspaceEnv = AddTypeItem(m_RootName, g_WorkspaceEnvTreeItem);
    ProcessWorkspaceEnv(m_pWorkspaceEnv, m_hRootWorkspaceEnv);

    // expand the root
    ExpandRoot(TRUE);
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::DestroyTree()
{
    if (::IsWindow(GetSafeHwnd()))
        DeleteAllItems();

    // empty the data set first
    EmptyDataSet();
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::ProcessWorkspaceEnv(PSS_WorkspaceEnv* pWorkspaceEnv, HTREEITEM hParentTreeItem)
{
    if (!pWorkspaceEnv || !pWorkspaceEnv->ContainEntity())
        return;

    const int count = pWorkspaceEnv->GetEntityCount();

    for (int i = 0; i < count; ++i)
    {
        PSS_WorkspaceEntity* pEntity = pWorkspaceEnv->GetEntityAt(i);

        if (!pEntity)
            continue;

        PSS_WorkspaceGroupEntity* pGroupEntity = dynamic_cast<PSS_WorkspaceGroupEntity*>(pEntity);

        if (pGroupEntity)
        {
            ProcessGroup(pGroupEntity, hParentTreeItem);
            continue;
        }

        PSS_WorkspaceFileEntity* pFileEntity = dynamic_cast<PSS_WorkspaceFileEntity*>(pEntity);

        if (pFileEntity)
            ProcessFile(pFileEntity, hParentTreeItem);
    }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::ProcessGroup(PSS_WorkspaceGroupEntity* pGroup, HTREEITEM hParentTreeItem)
{
    // add the item
    HTREEITEM hGroupItem = AddGroupItem(pGroup, hParentTreeItem);

    if (!pGroup || !pGroup->ContainEntity())
        return;

    const int count = pGroup->GetEntityCount();

    for (int i = 0; i < count; ++i)
    {
        PSS_WorkspaceEntity* pEntity = pGroup->GetEntityAt(i);

        if (!pEntity)
            continue;

        PSS_WorkspaceGroupEntity* pGroupEntity = dynamic_cast<PSS_WorkspaceGroupEntity*>(pEntity);

        if (pGroupEntity)
            ProcessGroup(pGroupEntity, hGroupItem);

        PSS_WorkspaceFileEntity* pFileEntity = dynamic_cast<PSS_WorkspaceFileEntity*>(pEntity);

        if (pFileEntity)
            ProcessFile(pFileEntity, hGroupItem);
    }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::ProcessFile(PSS_WorkspaceFileEntity* pFile, HTREEITEM hParentTreeItem)
{
    // add the item
    HTREEITEM hFileItem = AddFileItem(pFile, hParentTreeItem);
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::ModifyEntity(PSS_WorkspaceEntity* pEntity)
{
    if (!m_hRootWorkspaceEnv || !pEntity)
        return;

    IData* pData = FindElementFromDataSet(pEntity);

    if (pData)
    {
        // from item, in fact from root
        HTREEITEM hItem = FindItemData(pData, (HTREEITEM)NULL);

        if (hItem)
            ModifyItem(pEntity, hItem);
    }
}
//---------------------------------------------------------------------------
HTREEITEM PSS_WorkspaceTreeCtrl::AddTypeItem(const CString& name, int iconIndex, HTREEITEM hParentTreeItem)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)name);
    curTreeItem.item.lParam         = (LPARAM)AddDataToSet(name);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_WorkspaceTreeCtrl::AddGroupItem(PSS_WorkspaceGroupEntity* pGroup, HTREEITEM hParentTreeItem)
{
    if (!pGroup)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = g_GroupTreeItem;
    curTreeItem.item.iSelectedImage = g_GroupTreeItem;
    curTreeItem.item.pszText        = (char*)((const char*)pGroup->GetEntityName());
    curTreeItem.item.lParam         = (LPARAM)AddDataToSet(pGroup);    // Represent a selectable item
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_WorkspaceTreeCtrl::AddFileItem(PSS_WorkspaceFileEntity* pFile, HTREEITEM hParentTreeItem)
{
    if (!pFile)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = g_AnyFileTreeItem;
    curTreeItem.item.iSelectedImage = g_AnyFileTreeItem;
    curTreeItem.item.pszText        = (char*)((const char*)pFile->GetEntityName());
    curTreeItem.item.lParam         = (LPARAM)AddDataToSet(pFile);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceTreeCtrl::ModifyItem(PSS_WorkspaceEntity* pEntity, HTREEITEM hItem)
{
    if (!pEntity)
        return FALSE;

    return SetItemText(hItem, (char*)((const char*)pEntity->GetEntityName()));
}
//---------------------------------------------------------------------------
PSS_WorkspaceEntity* PSS_WorkspaceTreeCtrl::GetEntity(HTREEITEM hItem)
{
    if (hItem)
    {
        IData* pObj = (IData*)GetItemData(hItem);

        if (pObj)
            switch (pObj->m_Type)
            {
                case IData::IE_DT_WorkspaceEnv: return pObj->m_pWorkspaceEnv;
                case IData::IE_DT_Group:        return pObj->m_pGroup;
                case IData::IE_DT_File:         return pObj->m_pFile;
            }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceTreeCtrl::GetGroup(HTREEITEM hItem)
{
    if (hItem)
    {
        IData* pObj = (IData*)GetItemData(hItem);

        if (pObj && pObj->m_Type == IData::IE_DT_Group)
            return pObj->m_pGroup;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceFileEntity* PSS_WorkspaceTreeCtrl::GetFile(HTREEITEM hItem)
{
    if (hItem)
    {
        IData* pObj = (IData*)GetItemData(hItem);

        if (pObj && pObj->m_Type == IData::IE_DT_File)
            return pObj->m_pFile;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceTreeCtrl::GetOwnerGroup(HTREEITEM hItem)
{
    if (hItem)
    {
        PSS_WorkspaceGroupEntity* pGroup = GetGroup(hItem);

        if (pGroup)
        {
            PSS_WorkspaceGroupEntity* pParentGroup = dynamic_cast<PSS_WorkspaceGroupEntity*>(pGroup->GetParent());

            // if a parent defined
            if (pParentGroup)
                return pParentGroup;

            return pGroup;
        }

        PSS_WorkspaceFileEntity* pFile = GetFile(hItem);

        // is a file selected?
        if (pFile)
        {
            PSS_WorkspaceGroupEntity* pParentFile = dynamic_cast<PSS_WorkspaceGroupEntity*>(pFile->GetParent());

            if (pParentFile)
                return pParentFile;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceTreeCtrl::GetFileBestGroup(const CString& fileName) const
{
    PSS_File file(fileName);
    CString ext = file.GetFileExt();

    // check if there is a point to start the extension string
    if (ext.GetAt(0) == '.')
        ext = ext.Right(ext.GetLength() - 1);

    IDataIterator i(&m_DataSet);

    for (IData* pElement = i.GetFirst(); pElement; pElement = i.GetNext())
        if (pElement->m_Type == IData::IE_DT_Group && pElement->m_pGroup)
            // check if the group contains the file name extension
            if (pElement->m_pGroup->ContainThisExtension(ext))
                return pElement->m_pGroup;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceFileEntity* PSS_WorkspaceTreeCtrl::GetFileEntity(const CString& fileName) const
{
    IDataIterator i(&m_DataSet);

    for (IData* pElement = i.GetFirst(); pElement; pElement = i.GetNext())
        if (pElement->m_Type == IData::IE_DT_File && !pElement->m_pFile->GetFileName().CompareNoCase(fileName))
            return pElement->m_pFile;

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTreeCtrl::EmptyDataSet()
{
    IDataIterator i(&m_DataSet);

    for (IData* pElement = i.GetFirst(); pElement; pElement = i.GetNext())
        delete pElement;

    m_DataSet.RemoveAll();
}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData* PSS_WorkspaceTreeCtrl::FindElementFromDataSet(PSS_WorkspaceEntity* pEntity)
{
    IDataIterator i(&m_DataSet);

    for (IData* pElement = i.GetFirst(); pElement; pElement = i.GetNext())
        if ((pElement->m_Type == IData::IE_DT_WorkspaceEnv && pElement->m_pWorkspaceEnv == pEntity) ||
            (pElement->m_Type == IData::IE_DT_Group        && pElement->m_pGroup        == pEntity) ||
            (pElement->m_Type == IData::IE_DT_File         && pElement->m_pFile         == pEntity))
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData* PSS_WorkspaceTreeCtrl::FindElementFromDataSet(PSS_WorkspaceEnv* pEntity)
{
    IDataIterator i(&m_DataSet);

    for (IData* pElement = i.GetFirst(); pElement; pElement = i.GetNext())
        if (pElement->m_Type == IData::IE_DT_WorkspaceEnv && pElement->m_pWorkspaceEnv == pEntity)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData* PSS_WorkspaceTreeCtrl::FindElementFromDataSet(PSS_WorkspaceGroupEntity* pEntity)
{
    IDataIterator i(&m_DataSet);

    for (IData* pElement = i.GetFirst(); pElement; pElement = i.GetNext())
        if (pElement->m_Type == IData::IE_DT_Group && pElement->m_pGroup == pEntity)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData* PSS_WorkspaceTreeCtrl::FindElementFromDataSet(PSS_WorkspaceFileEntity* pEntity)
{
    IDataIterator i(&m_DataSet);

    for (IData* pElement = i.GetFirst(); pElement; pElement = i.GetNext())
        if (pElement->m_Type == IData::IE_DT_File && pElement->m_pFile == pEntity)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData* PSS_WorkspaceTreeCtrl::FindElementFromDataSet(const CString& entity)
{
    IDataIterator i(&m_DataSet);

    for (IData* pElement = i.GetFirst(); pElement; pElement = i.GetNext())
        if (pElement->m_Type == IData::IE_DT_String && pElement->m_Str == entity)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData* PSS_WorkspaceTreeCtrl::AddDataToSet(PSS_WorkspaceEnv* pEntity)
{
    std::unique_ptr<IData> pData(new IData(pEntity));
    m_DataSet.Add(pData.get());

    return pData.release();
}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData* PSS_WorkspaceTreeCtrl::AddDataToSet(PSS_WorkspaceGroupEntity* pEntity)
{
    std::unique_ptr<IData> pData(new IData(pEntity));
    m_DataSet.Add(pData.get());

    return pData.release();
}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData* PSS_WorkspaceTreeCtrl::AddDataToSet(PSS_WorkspaceFileEntity* pEntity)
{
    std::unique_ptr<IData> pData(new IData(pEntity));
    m_DataSet.Add(pData.get());

    return pData.release();
}
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl::IData* PSS_WorkspaceTreeCtrl::AddDataToSet(const CString& entity)
{
    std::unique_ptr<IData> pData(new IData(entity));
    m_DataSet.Add(pData.get());

    return pData.release();
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceTreeCtrl::DeleteElementFromDataSet(PSS_WorkspaceGroupEntity* pEntity)
{
    IDataIterator it(&m_DataSet);

    for (IData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Type == IData::IE_DT_Group && pElement->m_pGroup == pEntity)
        {
            delete pElement;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceTreeCtrl::DeleteElementFromDataSet(PSS_WorkspaceFileEntity* pEntity)
{
    IDataIterator it(&m_DataSet);

    for (IData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Type == IData::IE_DT_File && pElement->m_pFile == pEntity)
        {
            delete pElement;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceTreeCtrl::DeleteElementFromDataSet(const CString& entity)
{
    IDataIterator it(&m_DataSet);

    for (IData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_Type == IData::IE_DT_String && pElement->m_Str == entity)
        {
            delete pElement;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
