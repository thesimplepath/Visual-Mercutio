//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//  Source file: z:\adsoft~1\ZWinUtil\ProcTree.cpp

#include <StdAfx.h>

// ProcTree
#include "ProcTree.h"

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

BEGIN_MESSAGE_MAP(ZCProcessTreeCtrl, ZITreeCtrl)
    //{{AFX_MSG_MAP(ZCProcessTreeCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCProcessTreeCtrl 



ZCProcessTreeCtrl::ZCProcessTreeCtrl (ZProcess* pProcess)
      : m_pProcess(pProcess)
{
}


ZCProcessTreeCtrl::~ZCProcessTreeCtrl()
{
}



void ZCProcessTreeCtrl::Initialize (ZProcess* pProcess)
{
    m_pProcess = pProcess;
    ZCProcessTreeCtrl::FillControl();
}

void ZCProcessTreeCtrl::Refresh()
{
    DeleteAllItems();
    ZCProcessTreeCtrl::FillControl();
}

void ZCProcessTreeCtrl::FillControl()
{
    // Sets styles
    HasButtons();
    HasLines();
    LinesAtRoot();
    // Load images
    LoadImageList( IDB_IL_PROCESSITEM, 17, 1, RGB( 255, 255, 255 ) );
    AddProcess ( m_pProcess, NULL, 0);
    // And finally expand the root
    ExpandRoot();
}

void ZCProcessTreeCtrl::AddProcess (ZBaseActivity* pBaseActivity, HTREEITEM hParentTreeItem, int IconIndex)
{
      ZBaseActivity*        pActivity;
    hParentTreeItem = AddProcessItem (pBaseActivity, hParentTreeItem, IconIndex );
    // Run throughout all activities
    for (size_t i = 0; i < (size_t)pBaseActivity->GetActivityCount(); ++i)
      {
        // Insert all pages from the Template Manager
          pActivity = pBaseActivity->GetActivityAt( i );
        if (pActivity)
        {
              if (pActivity->HasActivities())
            {
                if (pActivity->GetRunMode() == SequenceRun)
                    AddProcess( pActivity, hParentTreeItem, 0 );
                else
                    AddProcess( pActivity, hParentTreeItem, 2 );
            }
            else
                AddSubItem( (ZActivity*)pActivity, hParentTreeItem, 1 );
        }
      }

}

HTREEITEM ZCProcessTreeCtrl::AddProcessItem (ZBaseActivity* pData, HTREEITEM hParentTreeItem, int IconIndex)
{
    TV_INSERTSTRUCT     curTreeItem;

    curTreeItem.hParent = hParentTreeItem; 
    curTreeItem.hInsertAfter = TVI_LAST ;
    curTreeItem.item.iImage = IconIndex;
    curTreeItem.item.iSelectedImage = IconIndex;
    curTreeItem.item.pszText = (char*)((const char*)pData->GetName());
    curTreeItem.item.lParam = (LPARAM)pData;
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return this->InsertItem( &curTreeItem );
}

HTREEITEM ZCProcessTreeCtrl::AddSubItem (ZActivity* pData, HTREEITEM hParentTreeItem, int IconIndex)
{
    TV_INSERTSTRUCT     curTreeItem;

    curTreeItem.hParent = hParentTreeItem; 
    curTreeItem.hInsertAfter = TVI_LAST ;
    curTreeItem.item.iImage = IconIndex;
    curTreeItem.item.iSelectedImage = IconIndex;
    curTreeItem.item.pszText = (char*)((const char*)pData->GetName());
    curTreeItem.item.lParam = (LPARAM)pData;
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return this->InsertItem(&curTreeItem);
}


void ZCProcessTreeCtrl::AddActivityItems (ZBaseActivity* pBaseActivity, HTREEITEM hParentTreeItem, int IconIndex)
{
      ZBaseActivity*        pActivity;
    // Run throughout all activities
    for (size_t i = 0; i < (size_t)pBaseActivity->GetActivityCount(); ++i)
      {
        // Insert all pages from the Template Manager
          pActivity = pBaseActivity->GetActivityAt( i );
          if (pActivity && pActivity->IsKindOf(RUNTIME_CLASS(ZActivity)))
        {
            AddSubItem( (ZActivity*)pActivity, hParentTreeItem, IconIndex );
        }
      }
}

ZProcess* ZCProcessTreeCtrl::GetSelectedProcessItem ()
{
    HTREEITEM hSelected = GetSelectedItem();
    if (hSelected)
    {
        CObject*    pObj = (CObject*)GetItemData( hSelected );
        CRuntimeClass*    pRuntimeClass = pObj->GetRuntimeClass();
        if (strcmp( pRuntimeClass->m_lpszClassName, "ZProcess" ) == 0)
            return reinterpret_cast<ZProcess*>( pObj );
    }
    return NULL;
}

ZProcess* ZCProcessTreeCtrl::GetRootProcessItem ()
{
    HTREEITEM hRoot = GetRootItem();
    if (hRoot)
    {
        CObject*    pObj = (CObject*)GetItemData( hRoot );
        CRuntimeClass*    pRuntimeClass = pObj->GetRuntimeClass();
        if (strcmp( pRuntimeClass->m_lpszClassName, "ZProcess" ) == 0)
            return reinterpret_cast<ZProcess*>( pObj );
    }
    return NULL;
}


ZActivity* ZCProcessTreeCtrl::GetSelectedActivityItem ()
{
    HTREEITEM hSelected = GetSelectedItem();
    if (hSelected)
    {
        CObject*    pObj = (CObject*)GetItemData( hSelected );
        CRuntimeClass*    pRuntimeClass = pObj->GetRuntimeClass();
        if (strcmp( pRuntimeClass->m_lpszClassName, "ZActivity") == 0)
            return reinterpret_cast<ZActivity*>( pObj );
    }
    return NULL;
}


