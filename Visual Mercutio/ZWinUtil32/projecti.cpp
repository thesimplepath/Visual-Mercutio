// Source file: ProjectI.cpp

#include <StdAfx.h>

#include "ProjectI.h"

#include "zBaseLib\ZITreeCtl.h"

#include "zBaseLib\ZDDoc.h"
#include "zBaseLib\DocData.h"

#include "zBaseLib\File.h"

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




// Class ZIProjectTree 

ZIProjectTree::ZIProjectTree (ZITreeCtrl* pTreeCtrl, ZDDocument* pDoc, BOOL OnlyVisible)
      : m_pTreeCtrl(pTreeCtrl), 
        m_pDoc(pDoc), 
        m_OnlyVisible(OnlyVisible),
        m_HasBeenInitialized(FALSE)
{
}


ZIProjectTree::~ZIProjectTree()
{
}



void ZIProjectTree::Empty()
{
    m_pDoc = NULL;
    if (m_pTreeCtrl)
        m_pTreeCtrl->DeleteAllItems();
}


void ZIProjectTree::Initialize (ZITreeCtrl* pTreeCtrl, ZDDocument* pDoc, BOOL OnlyVisible)
{
    m_pTreeCtrl = pTreeCtrl;
    m_pDoc = pDoc;
    m_OnlyVisible = OnlyVisible;
    InitializeTree();
    ZIProjectTree::Refresh();
}

void ZIProjectTree::Refresh ()
{
    if (m_pTreeCtrl)
    {
        m_pTreeCtrl->DeleteAllItems();
        ZIProjectTree::CreateTree();
    }
}

void ZIProjectTree::InitializeTree ()
{
    if (m_HasBeenInitialized || !m_pTreeCtrl)
        return;
    // Sets styles
    m_pTreeCtrl->HasButtons();
    m_pTreeCtrl->HasLines();
    m_pTreeCtrl->LinesAtRoot();
    // Load images
    m_pTreeCtrl->LoadImageList( IDB_DOCUMENT_TYPES, 17, 1, RGB( 255, 255, 255 ) );
    m_InternalDocumentType.LoadString( IDS_INTERNALDOCUMENTTYPE );
    m_ExternalDocumentType.LoadString( IDS_EXTERNALDOCUMENTTYPE );
    m_HasBeenInitialized = TRUE;
}

void ZIProjectTree::CreateTree ()
{
    if( !m_pDoc || !m_pDoc->GetActiveDocumentData())
        return;
    HTREEITEM hRoot = NULL;
    if (m_pDoc->DocumentIsTemplate())
    {
        hRoot = AddDocumentTypeItem (m_pDoc->GetStamp().GetTitle(), 0);
    }
    else
    {
        // Extract the filename
        ZFile file(m_pDoc->GetPathName());
        hRoot = AddDocumentTypeItem (file.GetFileTitle(), 0);
    }
    HTREEITEM hRootInternal = AddDocumentTypeItem (m_InternalDocumentType, 1, hRoot);
    HTREEITEM hRootExternal = AddDocumentTypeItem (m_ExternalDocumentType, 2, hRoot);
    for (size_t i = 0; m_pDoc && i < m_pDoc->GetDocumentDataCount(); ++i)
    {
          if (!m_OnlyVisible || (m_OnlyVisible && m_pDoc->GetDocumentDataAt(i) && m_pDoc->GetDocumentDataAt(i)->DocumentDataIsVisible()))
        {
            if (m_pDoc->GetDocumentDataAt(i)->IsBinaryDataValid())
                AddDocumentItem( m_pDoc->GetDocumentDataAt(i), hRootExternal, 4 );
            else
            if (m_pDoc->GetDocumentDataAt(i)->IsURLData())
                AddDocumentItem( m_pDoc->GetDocumentDataAt(i), hRootExternal, 5 );
            else
                AddDocumentItem( m_pDoc->GetDocumentDataAt(i), hRootInternal, 3 );

        }
    }
    m_pTreeCtrl->ExpandBranch(hRoot, TRUE);
}


HTREEITEM ZIProjectTree::AddDocumentTypeItem (const CString DocumentType, int IconIndex, HTREEITEM hParent /*= NULL*/)
{
    TV_INSERTSTRUCT     curTreeItem;

    curTreeItem.hParent = hParent; 
    curTreeItem.hInsertAfter = TVI_LAST ;
    curTreeItem.item.iImage = IconIndex;
    curTreeItem.item.iSelectedImage = IconIndex;
    curTreeItem.item.pszText = (char*)((const char*)DocumentType);
    curTreeItem.item.lParam = (LPARAM)NULL;    // Does not represent a selectable item
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem( &curTreeItem );
}

HTREEITEM ZIProjectTree::AddDocumentItem (ZDDocumentData* pData, HTREEITEM hParentTreeItem, int IconIndex)
{
    if (!pData)
        return NULL;
    TV_INSERTSTRUCT     curTreeItem;

    curTreeItem.hParent = hParentTreeItem; 
    curTreeItem.hInsertAfter = TVI_LAST ;
    curTreeItem.item.iImage = IconIndex;
    curTreeItem.item.iSelectedImage = IconIndex;
    if (pData->IsBinaryDataValid())
        curTreeItem.item.pszText = (char*)((const char*)pData->GetStamp().GetTemplate());
    else
        curTreeItem.item.pszText = (char*)((const char*)pData->GetStamp().GetTitle());
    curTreeItem.item.lParam = (LPARAM)pData;
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
}



ZDDocumentData* ZIProjectTree::GetSelectedDocument ()
{
    if (m_pTreeCtrl)
    {
        HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();
        if (hSelected)
        {
            CObject*    pObj = (CObject*)m_pTreeCtrl->GetItemData( hSelected );
            if (pObj != NULL)
                return reinterpret_cast<ZDDocumentData*>( pObj );
        }
    }
    return NULL;
}

CString    ZIProjectTree::GetSelectedDocumentTitle()
{
    if (m_pTreeCtrl)
    {
        HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();
        if (hSelected)
        {
            CObject*    pObj = (CObject*)m_pTreeCtrl->GetItemData( hSelected );
            if (pObj != NULL)
                return m_pTreeCtrl->GetItemText( hSelected );
        }
    }
    return "";
}


void ZIProjectTree::OnFileListChanged()
{
    Refresh();
}
