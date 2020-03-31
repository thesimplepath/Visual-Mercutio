/****************************************************************************
 * ==> PSS_UserTree --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user tree                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_UserTree.h"

// processsoft
#include "zRes32\ZRes.h"

#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_UserTree
//---------------------------------------------------------------------------
PSS_UserTree::PSS_UserTree(PSS_TreeCtrl* pTreeCtrl, PSS_UserManager* pUserManager) :
    m_pTreeCtrl(pTreeCtrl), 
    m_pUserManager(pUserManager),
    m_Invalid(false)
{}
//---------------------------------------------------------------------------
PSS_UserTree::PSS_UserTree(const PSS_UserTree& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_UserTree::~PSS_UserTree()
{}
//---------------------------------------------------------------------------
const PSS_UserTree& PSS_UserTree::operator = (const PSS_UserTree& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_UserTree::Initialize(PSS_TreeCtrl* pTreeCtrl, PSS_UserManager* pUserManager)
{
    m_pTreeCtrl    = pTreeCtrl;
    m_pUserManager = pUserManager;

    InitializeTree();
    Refresh();
}
//---------------------------------------------------------------------------
void PSS_UserTree::ReInitialize(PSS_UserManager* pUserManager)
{
    m_pUserManager = pUserManager;

    Refresh();
}
//---------------------------------------------------------------------------
void PSS_UserTree::Refresh()
{
    if (!m_pTreeCtrl)
        return;

    m_Invalid = true;
    m_pTreeCtrl->DeleteAllItems();
    m_Invalid = false;

    CreateTree();
}
//---------------------------------------------------------------------------
PSS_User* PSS_UserTree::GetSelectedUser() const
{
    if (m_Invalid)
        return NULL;

    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();

    if (hSelected)
    {
        CObject* pObj = reinterpret_cast<CObject*>(m_pTreeCtrl->GetItemData(hSelected));

        if (pObj)
            return dynamic_cast<PSS_User*>(pObj);
    }

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_UserTree::GetSelectedDepartement() const
{
    if (m_Invalid)
        return "";

    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();

    if (hSelected)
    {
        CObject* pObj = reinterpret_cast<CObject*>(m_pTreeCtrl->GetItemData(hSelected));

        if (!pObj)
            return m_pTreeCtrl->GetItemText(hSelected);
    }

    return "";
}
//---------------------------------------------------------------------------
void PSS_UserTree::OnUserListChanged()
{
    Refresh();
}
//---------------------------------------------------------------------------
void PSS_UserTree::CreateTree()
{
    // build the departement array
    BuildDepartementArray();

    const std::size_t departmentCount = m_DepartementArray.GetSize();

    for (int index = 0; index < departmentCount; ++index)
    {
        HTREEITEM hRootItem = AddDepartementItem(m_DepartementArray[index], 0);

        const std::size_t userCount = m_pUserManager->GetCount();

        for (int i = 0; i < userCount; ++i)
            // is the same user and the same folder?
            if (m_pUserManager->GetAt(i)->GetDepartement() == m_DepartementArray[index])
                AddUserItem(m_pUserManager->GetAt(i), hRootItem, m_pUserManager->GetAt(i)->IsAdministrator() ? 1 : 2);
    }
}
//---------------------------------------------------------------------------
void PSS_UserTree::InitializeTree()
{
    // set styles
    m_pTreeCtrl->HasButtons();
    m_pTreeCtrl->HasLines();
    m_pTreeCtrl->LinesAtRoot();

    // load images
    m_pTreeCtrl->LoadImageList(IDB_IL_USERIMAGES, 17, 1, RGB(255, 255, 255));
}
//---------------------------------------------------------------------------
HTREEITEM PSS_UserTree::AddDepartementItem(const CString& departement, int iconIndex)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = NULL;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)departement);
    curTreeItem.item.lParam         = LPARAM(NULL);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_UserTree::AddUserItem(PSS_User* pData, HTREEITEM hParentTreeItem, int iconIndex)
{
    if (!pData)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)pData->GetUserName());
    curTreeItem.item.lParam         = LPARAM(pData);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
BOOL PSS_UserTree::DepartementExist(const CString& departement)
{
    const std::size_t departmentCount = m_DepartementArray.GetSize();

    for (int i = 0; i < departmentCount; ++i)
        if (m_DepartementArray[i] == departement)
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_UserTree::BuildDepartementArray()
{
    m_DepartementArray.RemoveAll();

    const std::size_t userCount = m_pUserManager->GetCount();

    for (int i = 0; i < userCount; ++i)
    {
        const CString department = m_pUserManager->GetAt(i)->GetDepartement();

        if (!DepartementExist(department))
            m_DepartementArray.Add(department);
    }
}
//---------------------------------------------------------------------------
