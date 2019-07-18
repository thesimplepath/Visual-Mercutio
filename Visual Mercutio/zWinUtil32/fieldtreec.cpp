// Source file: fieldtreec.cpp

#include <StdAfx.h>
#include "FieldTreeC.h"

// resources
#ifndef _WIN32
    #include "ZWinUtilRes.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32Res.h"
#endif
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZCCommonFieldTree, ZITreeCtrl)
    //{{AFX_MSG_MAP(ZCCommonFieldTree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCCommonFieldTree 


ZCCommonFieldTree::ZCCommonFieldTree (ZBFieldRepository* pFieldRepository)
      : m_pFieldRepository(pFieldRepository)
{
    m_FieldDescriptionKey.LoadString( IDS_DESCFIELD_DESCRIPTION );
    m_IsReadOnlyKey.LoadString( IDS_DESCFIELD_READONLY );
    m_SortedKey.LoadString( IDS_DESCFIELD_SORTED );
    m_UserHelpKey.LoadString( IDS_DESCFIELD_USERHELP );
    m_ClassNameKey.LoadString( IDS_DESCFIELD_CLASSNAME );
    m_HistoryKey.LoadString( IDS_DESCFIELD_HISTORY );
}


ZCCommonFieldTree::~ZCCommonFieldTree()
{
    m_ImageListTree.DeleteImageList();
}



void ZCCommonFieldTree::Initialize (ZBFieldRepository* pFieldRepository)
{
    m_pFieldRepository = pFieldRepository;
    ZCCommonFieldTree::InitializeTree();
    ZCCommonFieldTree::Refresh();
}

void ZCCommonFieldTree::ReInitialize (ZBFieldRepository* pFieldRepository)
{
    m_pFieldRepository = pFieldRepository;
    ZCCommonFieldTree::Refresh();
}

void ZCCommonFieldTree::InitializeTree ()
{
    // Sets styles
    HasButtons();
    HasLines();
    LinesAtRoot();

    LoadImageList( IDB_FIELDINFO_TYPES, 17, 1, RGB( 255, 255, 255 ) );
}

void ZCCommonFieldTree::Refresh ()
{
    DeleteAllItems();
    ZCCommonFieldTree::CreateTree();
}

void ZCCommonFieldTree::CreateTree ()
{
    for (size_t Index = 0; Index < m_pFieldRepository->GetFieldCount(); ++Index)
        AddFieldItem (m_pFieldRepository->GetFieldAt(Index));
}

void ZCCommonFieldTree::AddFieldItem (ZAObjectDefinition* pField)
{
    TV_INSERTSTRUCT     curTreeItem;

    curTreeItem.hParent = NULL; 
    curTreeItem.hInsertAfter = TVI_LAST ;
    curTreeItem.item.iImage = 0;
    curTreeItem.item.iSelectedImage = 0;
    curTreeItem.item.pszText = (char*)((const char*)pField->GetFieldName());
    curTreeItem.item.lParam = (LPARAM)pField;    // Represent the field item
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    HTREEITEM hRootItem = InsertItem( &curTreeItem );

    char    Buffer[300];
    // Build the string and inserts the item
    sprintf( Buffer, m_FieldDescriptionKey, pField->GetDescription());
    curTreeItem.hParent = hRootItem; 
    curTreeItem.hInsertAfter = TVI_LAST;
    curTreeItem.item.iImage = 1;
    curTreeItem.item.iSelectedImage = 1;
    curTreeItem.item.pszText = (char*)((const char*)Buffer);
    curTreeItem.item.lParam = (LPARAM)NULL;    
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    InsertItem( &curTreeItem );

    // Build the string and inserts the item
    sprintf( Buffer, m_UserHelpKey, pField->GetHelpUserDescription());
    curTreeItem.hParent = hRootItem; 
    curTreeItem.hInsertAfter = TVI_LAST;
    curTreeItem.item.iImage = 2;
    curTreeItem.item.iSelectedImage = 2;
    curTreeItem.item.pszText = (char*)((const char*)Buffer);
    curTreeItem.item.lParam = (LPARAM)NULL;    
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    InsertItem( &curTreeItem );

    // Build the string and inserts the item
    sprintf( Buffer, m_ClassNameKey, pField->GetClassName());
    curTreeItem.hParent = hRootItem; 
    curTreeItem.hInsertAfter = TVI_LAST;
    curTreeItem.item.iImage = 3;
    curTreeItem.item.iSelectedImage = 3;
    curTreeItem.item.pszText = (char*)((const char*)Buffer);
    curTreeItem.item.lParam = (LPARAM)NULL;    
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    InsertItem( &curTreeItem );
    
    // Build the string and inserts the item
    sprintf( Buffer, m_SortedKey, (pField->IsSorted()) ? "1" : "0" );
    curTreeItem.hParent = hRootItem; 
    curTreeItem.hInsertAfter = TVI_LAST;
    curTreeItem.item.iImage = 4;
    curTreeItem.item.iSelectedImage = 4;
    curTreeItem.item.pszText = (char*)((const char*)Buffer);
    curTreeItem.item.lParam = (LPARAM)NULL;    
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    InsertItem( &curTreeItem );

    ZAHistoryField* pHistory = m_pFieldRepository->FindFieldHistory( pField->GetFieldName() );

    if (pHistory)
    {
        // Build the string and inserts the item
        sprintf( Buffer, m_IsReadOnlyKey, (pHistory->IsReadOnly()) ? "1" : "0" );
        curTreeItem.hParent = hRootItem; 
        curTreeItem.hInsertAfter = TVI_LAST;
        curTreeItem.item.iImage = 5;
        curTreeItem.item.iSelectedImage = 5;
        curTreeItem.item.pszText = (char*)((const char*)Buffer);
        curTreeItem.item.lParam = (LPARAM)NULL;    
        curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
        InsertItem( &curTreeItem );

        AddFieldHistoryItem( pHistory, hRootItem);
    }
}

void ZCCommonFieldTree::AddFieldHistoryItem (ZAHistoryField* pHistory, HTREEITEM hParentTreeItem)
{
    if (!pHistory)
        return;
    const CStringArray& ValueArray = pHistory->GetValueArray();

    TV_INSERTSTRUCT     curTreeItem;

    curTreeItem.hParent = hParentTreeItem; 
    curTreeItem.hInsertAfter = TVI_LAST;
    curTreeItem.item.iImage = 6;
    curTreeItem.item.iSelectedImage = 6;
    curTreeItem.item.pszText = (char*)((const char*)m_HistoryKey);
    curTreeItem.item.lParam = (LPARAM)NULL;    
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    HTREEITEM hRootItem = InsertItem( &curTreeItem );

    for (size_t i = 0; i  < (size_t)ValueArray.GetSize(); ++i)
    {
        curTreeItem.hParent = hRootItem; 
        curTreeItem.hInsertAfter = TVI_LAST;
        curTreeItem.item.iImage = 7;
        curTreeItem.item.iSelectedImage = 7;
        curTreeItem.item.pszText = (char*)((const char*)ValueArray.GetAt(i));
        curTreeItem.item.lParam = (LPARAM)NULL;
        curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
        InsertItem(&curTreeItem);
    }
}



ZAObjectDefinition*        ZCCommonFieldTree::GetSelectedField()
{
    HTREEITEM hSelected = GetSelectedItem();
    if (hSelected)
    {
        CObject*    pObj = (CObject*)GetItemData( hSelected );
        if (pObj != NULL)
            return reinterpret_cast<ZAObjectDefinition*>( pObj );
    }
    return NULL;
}

