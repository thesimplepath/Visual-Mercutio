#include <StdAfx.h>
#include "ZITmplTr.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

// Class ZITemplateTree

ZITemplateTree::ZITemplateTree (ZITreeCtrl* pTreeCtrl, ZDTemplateManager* pTemplateManager, BOOL IncludeFiles)
  //## begin ZITemplateTree::ZITemplateTree%951679594.hasinit preserve=no
  //## end ZITemplateTree::ZITemplateTree%951679594.hasinit
  //## begin ZITemplateTree::ZITemplateTree%951679594.initialization preserve=yes
    :    m_pTreeCtrl(pTreeCtrl),
        m_pTemplateManager(pTemplateManager),
        m_IncludeFiles(IncludeFiles), m_Invalid(false)
  //## end ZITemplateTree::ZITemplateTree%951679594.initialization
{
  //## begin ZITemplateTree::ZITemplateTree%951679594.body preserve=yes
  //## end ZITemplateTree::ZITemplateTree%951679594.body
}


ZITemplateTree::~ZITemplateTree()
{
  //## begin ZITemplateTree::~ZITemplateTree%.body preserve=yes
  //## end ZITemplateTree::~ZITemplateTree%.body
}



//## Other Operations (implementation)
void ZITemplateTree::Initialize (ZITreeCtrl* pTreeCtrl, ZDTemplateManager* pTemplateManager, BOOL IncludeFiles)
{
  //## begin ZITemplateTree::Initialize%951679595.body preserve=yes
    m_pTreeCtrl = pTreeCtrl;
    m_pTemplateManager = pTemplateManager;
    m_IncludeFiles = IncludeFiles;
    if (m_pTreeCtrl)
    {
        ZITemplateTree::InitializeTree();
        ZITemplateTree::Refresh();
    }
  //## end ZITemplateTree::Initialize%951679595.body
}

void ZITemplateTree::ReInitialize (ZDTemplateManager* pTemplateManager, BOOL IncludeFiles)
{
  //## begin ZITemplateTree::ReInitialize%951679596.body preserve=yes
    m_pTemplateManager = pTemplateManager;
    m_IncludeFiles = IncludeFiles;
    if (m_pTreeCtrl)
        ZITemplateTree::Refresh();
  //## end ZITemplateTree::ReInitialize%951679596.body
}

void ZITemplateTree::Refresh ()
{
  //## begin ZITemplateTree::Refresh%951679597.body preserve=yes
    if (!m_pTreeCtrl)
        return;
    m_Invalid = true;
    m_pTreeCtrl->DeleteAllItems();
    m_Invalid = false;

    if ((size_t)m_pTemplateManager->GetSize() <= 0)
        return;

    // The first template directory is the root
      ZDTemplateDir*    pTemplateDir;
    HTREEITEM        hRootItem;
    // Run throughout all template directory    
    for (size_t i = 0; i < (size_t)m_pTemplateManager->GetSize(); ++i)
      {
        // Insert all pages from the Template Manager
          pTemplateDir = m_pTemplateManager->GetTemplateDirAt( i );
          if (pTemplateDir)
        {
              hRootItem = AddRootItem (pTemplateDir, 0 );
            if (i == 0)
            {
                m_pTreeCtrl->SelectItem( hRootItem );
                m_pTreeCtrl->EnsureVisible( hRootItem );
            }
                //Select( hRootItem, TVGN_FIRSTVISIBLE );
            if (m_IncludeFiles)
                AddFileItems( pTemplateDir, hRootItem, 1 );
        }
      }
  //## end ZITemplateTree::Refresh%951679597.body
}

HTREEITEM ZITemplateTree::AddRootItem (ZDTemplateDir* pData, int IconIndex)
{
  //## begin ZITemplateTree::AddRootItem%951679598.body preserve=yes
    TV_INSERTSTRUCT     curTreeItem;

    curTreeItem.hParent = NULL; 
    curTreeItem.hInsertAfter = TVI_LAST ;
    curTreeItem.item.iImage = IconIndex;
    curTreeItem.item.iSelectedImage = IconIndex;
    curTreeItem.item.pszText = (char*)((const char*)pData->GetTitle());
    curTreeItem.item.lParam = (LPARAM)pData;
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem( &curTreeItem );
  //## end ZITemplateTree::AddRootItem%951679598.body
}

HTREEITEM ZITemplateTree::AddSubItem (ZDTemplateDir* pData, HTREEITEM hParentTreeItem, int IconIndex)
{
  //## begin ZITemplateTree::AddSubItem%951679599.body preserve=yes
    TV_INSERTSTRUCT     curTreeItem;

    curTreeItem.hParent = hParentTreeItem; 
    curTreeItem.hInsertAfter = TVI_LAST ;
    curTreeItem.item.iImage = IconIndex;
    curTreeItem.item.iSelectedImage = IconIndex;
    curTreeItem.item.pszText = (char*)((const char*)pData->GetTitle());
    curTreeItem.item.lParam = (LPARAM)pData;
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
  //## end ZITemplateTree::AddSubItem%951679599.body
}

HTREEITEM ZITemplateTree::AddSubItem (ZDTemplateFile* pData, HTREEITEM hParentTreeItem, int IconIndex)
{
  //## begin ZITemplateTree::AddSubItem%951679600.body preserve=yes
      TV_INSERTSTRUCT     curTreeItem;
    curTreeItem.hParent = hParentTreeItem; 
    curTreeItem.hInsertAfter = TVI_LAST ;
    curTreeItem.item.iImage = IconIndex;
    curTreeItem.item.iSelectedImage = IconIndex;
    curTreeItem.item.pszText = (char*)((const char*)pData->GetTitle());
    curTreeItem.item.lParam = (LPARAM)pData;
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
  //## end ZITemplateTree::AddSubItem%951679600.body
}

void ZITemplateTree::AddFileItems (ZDTemplateDir* pTemplateDir, HTREEITEM hParentTreeItem, int IconIndex)
{
  //## begin ZITemplateTree::AddFileItems%951679601.body preserve=yes
      ZDTemplateFile*    pTemplateFile;
    // Run throughout all template directory    
    for (size_t i = 0; i < (size_t)pTemplateDir->GetSize(); ++i)
      {
        // Insert all files from the Template Directory
          pTemplateFile = pTemplateDir->GetTemplateFileAt( i );
          if (pTemplateFile)
              AddSubItem (pTemplateFile, hParentTreeItem, IconIndex );
      }
  //## end ZITemplateTree::AddFileItems%951679601.body
}

CString ZITemplateTree::GetNameSelectedItem ()
{
  //## begin ZITemplateTree::GetNameSelectedItem%951679602.body preserve=yes
    if (m_Invalid == true || !m_pTreeCtrl)
        return "";
    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();
    if (hSelected)
    {
        return m_pTreeCtrl->GetItemText( hSelected );
    }
    return "";
  //## end ZITemplateTree::GetNameSelectedItem%951679602.body
}

ZDTemplateDir* ZITemplateTree::GetSelectedFolderItem ()
{
  //## begin ZITemplateTree::GetSelectedFolderItem%951679603.body preserve=yes
    if (m_Invalid == true || !m_pTreeCtrl)
        return NULL;
    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();
    if (hSelected)
    {
        if (m_pTreeCtrl->GetRootItem() == NULL)
            return NULL;
        CObject*    pObj = (CObject*)m_pTreeCtrl->GetItemData( hSelected );
        if (pObj->IsKindOf(RUNTIME_CLASS(ZDTemplateDir)))
            return reinterpret_cast<ZDTemplateDir*>( pObj );
    }
    return NULL;
  //## end ZITemplateTree::GetSelectedFolderItem%951679603.body
}

ZDTemplateFile* ZITemplateTree::GetSelectedFileItem ()
{
  //## begin ZITemplateTree::GetSelectedFileItem%951679604.body preserve=yes
    if (m_Invalid == true || !m_pTreeCtrl)
        return NULL;
    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();
    if (hSelected)
    {
        if (m_pTreeCtrl->GetRootItem() == NULL)
            return NULL;
        return DYNAMIC_DOWNCAST(ZDTemplateFile , (CObject*)m_pTreeCtrl->GetItemData( hSelected ) );
    }
    return NULL;
  //## end ZITemplateTree::GetSelectedFileItem%951679604.body
}

BOOL ZITemplateTree::SelectItemName (const CString Name)
{
  //## begin ZITemplateTree::SelectItemName%951679605.body preserve=yes
    if (!m_pTreeCtrl)
        return FALSE;
    HTREEITEM hItemToSelect = m_pTreeCtrl->FindItem( Name, NULL );
    if (hItemToSelect)
        return m_pTreeCtrl->SelectItem( hItemToSelect );
    return FALSE;
  //## end ZITemplateTree::SelectItemName%951679605.body
}

void ZITemplateTree::InitializeTree ()
{
  //## begin ZITemplateTree::InitializeTree%951679606.body preserve=yes
    // Sets styles
    m_pTreeCtrl->HasButtons();
    m_pTreeCtrl->HasLines();
    m_pTreeCtrl->LinesAtRoot();
    // Load images
    m_pTreeCtrl->LoadImageList( IDB_IL_FORMIMAGES, 17, 1, RGB( 255, 255, 255 ) );
  //## end ZITemplateTree::InitializeTree%951679606.body
}

// Additional Declarations
  //## begin ZITemplateTree%38B976C601E6.declarations preserve=yes
  //## end ZITemplateTree%38B976C601E6.declarations

//## begin module%38B979D6016C.epilog preserve=yes
//## end module%38B979D6016C.epilog
