// Source file: UserTreeI.cpp

#include <StdAfx.h>

// UserTreeI
#include "UserTreeI.h"
#include "zRes32\ZRes.h"

#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZIUserTree 


ZIUserTree::ZIUserTree (ZITreeCtrl* pTreeCtrl, ZUUserManager* pUserManager)
      : m_pTreeCtrl(pTreeCtrl), 
        m_pUserManager(pUserManager),
        m_Invalid(false)
{
}


ZIUserTree::~ZIUserTree()
{
}



void ZIUserTree::Initialize (ZITreeCtrl* pTreeCtrl, ZUUserManager* pUserManager)
{
    m_pTreeCtrl = pTreeCtrl;
    m_pUserManager = pUserManager;
    InitializeTree();
    ZIUserTree::Refresh();
}

void ZIUserTree::ReInitialize (ZUUserManager* pUserManager)
{
    m_pUserManager = pUserManager;
    ZIUserTree::Refresh();
}

void ZIUserTree::Refresh ()
{
    if (m_pTreeCtrl)
    {
        m_Invalid = true;
        m_pTreeCtrl->DeleteAllItems();
        m_Invalid = false;
        ZIUserTree::CreateTree();
    }
}

void ZIUserTree::InitializeTree ()
{
    // Sets styles
    m_pTreeCtrl->HasButtons();
    m_pTreeCtrl->HasLines();
    m_pTreeCtrl->LinesAtRoot();
    // Load images
    m_pTreeCtrl->LoadImageList( IDB_IL_USERIMAGES, 17, 1, RGB( 255, 255, 255 ) );
}

void ZIUserTree::CreateTree ()
{

    // Build Departement Array
    BuildDepartementArray();
    HTREEITEM hRootItem;
    for (int Index = 0; Index < m_DepartementArray.GetSize(); ++Index)
    {
        hRootItem = AddDepartementItem (m_DepartementArray[Index], 0);
        for (int i = 0; i < m_pUserManager->GetCount(); ++i)
        {
            // If the same user and the same folder
            if (m_pUserManager->GetAt(i)->GetDepartement() == m_DepartementArray[Index])
            {
                AddUserItem( m_pUserManager->GetAt(i), hRootItem, (m_pUserManager->GetAt(i)->IsAdministrator()) ? 1 : 2 );
            }
        }
    }
}

void ZIUserTree::BuildDepartementArray()
{
    m_DepartementArray.RemoveAll();
    for (int i = 0; i < m_pUserManager->GetCount(); ++i)
    {
        if (!DepartementExist( m_pUserManager->GetAt(i)->GetDepartement() ))
            m_DepartementArray.Add( m_pUserManager->GetAt(i)->GetDepartement() );
    }

}

BOOL ZIUserTree::DepartementExist( const CString Departement )
{
    for (int i = 0; i < m_DepartementArray.GetSize(); ++i)
        if (m_DepartementArray[i] == Departement)
            return TRUE;
    return FALSE;
}

HTREEITEM ZIUserTree::AddDepartementItem (const CString Departement, int IconIndex)
{
    TV_INSERTSTRUCT     curTreeItem;

    curTreeItem.hParent = NULL; 
    curTreeItem.hInsertAfter = TVI_LAST ;
    curTreeItem.item.iImage = IconIndex;
    curTreeItem.item.iSelectedImage = IconIndex;
    curTreeItem.item.pszText = (char*)((const char*)Departement);
    curTreeItem.item.lParam = (LPARAM)NULL;    // Does not represent a selectable item
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem( &curTreeItem );
}

HTREEITEM ZIUserTree::AddUserItem (ZUser* pData, HTREEITEM hParentTreeItem, int IconIndex)
{
    if (!pData)
        return NULL;
    TV_INSERTSTRUCT     curTreeItem;

    curTreeItem.hParent = hParentTreeItem; 
    curTreeItem.hInsertAfter = TVI_LAST ;
    curTreeItem.item.iImage = IconIndex;
    curTreeItem.item.iSelectedImage = IconIndex;
    curTreeItem.item.pszText = (char*)((const char*)pData->GetUserName());
    curTreeItem.item.lParam = (LPARAM)pData;
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
}



ZUser* ZIUserTree::GetSelectedUser ()
{
    if (m_Invalid == true)
        return NULL;
    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();
    if (hSelected)
    {
        CObject*    pObj = (CObject*)m_pTreeCtrl->GetItemData( hSelected );
        if (pObj != NULL)
            return reinterpret_cast<ZUser*>( pObj );
    }
    return NULL;
}

CString    ZIUserTree::GetSelectedDepartement()
{
    if (m_Invalid == true)
        return "";
    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();
    if (hSelected)
    {
        CObject*    pObj = (CObject*)m_pTreeCtrl->GetItemData( hSelected );
        if (pObj == NULL)
            return m_pTreeCtrl->GetItemText( hSelected );
    }
    return "";
}


void ZIUserTree::OnUserListChanged()
{
    Refresh();
}
