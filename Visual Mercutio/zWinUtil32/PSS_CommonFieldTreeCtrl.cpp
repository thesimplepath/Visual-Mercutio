/****************************************************************************
 * ==> PSS_CommonFieldTreeCtrl ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a common field tree control                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_CommonFieldTreeCtrl.h"

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

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_CommonFieldTreeCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(PSS_CommonFieldTreeCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_CommonFieldTreeCtrl
//---------------------------------------------------------------------------
PSS_CommonFieldTreeCtrl::PSS_CommonFieldTreeCtrl(PSS_FieldRepository* pFieldRepository) :
    PSS_TreeCtrl(),
    m_pFieldRepository(pFieldRepository)
{
    m_FieldDescriptionKey.LoadString(IDS_DESCFIELD_DESCRIPTION);
    m_UserHelpKey.LoadString(IDS_DESCFIELD_USERHELP);
    m_IsReadOnlyKey.LoadString(IDS_DESCFIELD_READONLY);
    m_SortedKey.LoadString(IDS_DESCFIELD_SORTED);
    m_ClassNameKey.LoadString(IDS_DESCFIELD_CLASSNAME);
    m_HistoryKey.LoadString(IDS_DESCFIELD_HISTORY);
}
//---------------------------------------------------------------------------
PSS_CommonFieldTreeCtrl::PSS_CommonFieldTreeCtrl(const PSS_CommonFieldTreeCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_CommonFieldTreeCtrl::~PSS_CommonFieldTreeCtrl()
{
    m_ImageListTree.DeleteImageList();
}
//---------------------------------------------------------------------------
const PSS_CommonFieldTreeCtrl& PSS_CommonFieldTreeCtrl::operator = (const PSS_CommonFieldTreeCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_CommonFieldTreeCtrl::Initialize(PSS_FieldRepository* pFieldRepository)
{
    m_pFieldRepository = pFieldRepository;
    InitializeTree();
    Refresh();
}
//---------------------------------------------------------------------------
void PSS_CommonFieldTreeCtrl::ReInitialize(PSS_FieldRepository* pFieldRepository)
{
    m_pFieldRepository = pFieldRepository;
    Refresh();
}
//---------------------------------------------------------------------------
void PSS_CommonFieldTreeCtrl::Refresh()
{
    DeleteAllItems();
    CreateTree();
}
//---------------------------------------------------------------------------
PSS_FieldObjectDefinition* PSS_CommonFieldTreeCtrl::GetSelectedField()
{
    HTREEITEM hSelected = GetSelectedItem();

    if (hSelected)
    {
        CObject* pObj = reinterpret_cast<CObject*>(GetItemData(hSelected));

        if (pObj)
            return dynamic_cast<PSS_FieldObjectDefinition*>(pObj);
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_CommonFieldTreeCtrl::CreateTree()
{
    for (std::size_t index = 0; index < m_pFieldRepository->GetFieldCount(); ++index)
        AddFieldItem(m_pFieldRepository->GetFieldAt(index));
}
//---------------------------------------------------------------------------
void PSS_CommonFieldTreeCtrl::InitializeTree()
{
    // set styles
    HasButtons();
    HasLines();
    LinesAtRoot();

    LoadImageList(IDB_FIELDINFO_TYPES, 17, 1, RGB(255, 255, 255));
}
//---------------------------------------------------------------------------
void PSS_CommonFieldTreeCtrl::AddFieldItem(PSS_FieldObjectDefinition* pField)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = NULL;
    curTreeItem.hInsertAfter        = TVI_LAST ;
    curTreeItem.item.iImage         = 0;
    curTreeItem.item.iSelectedImage = 0;
    curTreeItem.item.pszText        = (char*)((const char*)pField->GetFieldName());
    curTreeItem.item.lParam         = LPARAM(pField);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    HTREEITEM hRootItem             = InsertItem(&curTreeItem);

    char buffer[300];

    // build the string and inserts the item
    ::sprintf_s(buffer, 300, m_FieldDescriptionKey, pField->GetDescription());
    curTreeItem.hParent             = hRootItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = 1;
    curTreeItem.item.iSelectedImage = 1;
    curTreeItem.item.pszText        = (char*)((const char*)buffer);
    curTreeItem.item.lParam         = LPARAM(NULL);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    InsertItem(&curTreeItem);

    // build the string and inserts the item
    ::sprintf_s(buffer, 300, m_UserHelpKey, pField->GetHelpUserDescription());
    curTreeItem.hParent             = hRootItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = 2;
    curTreeItem.item.iSelectedImage = 2;
    curTreeItem.item.pszText        = (char*)((const char*)buffer);
    curTreeItem.item.lParam         = LPARAM(NULL);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    InsertItem(&curTreeItem);

    // build the string and inserts the item
    ::sprintf_s(buffer, 300, m_ClassNameKey, pField->GetClassName());
    curTreeItem.hParent             = hRootItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = 3;
    curTreeItem.item.iSelectedImage = 3;
    curTreeItem.item.pszText        = (char*)((const char*)buffer);
    curTreeItem.item.lParam         = LPARAM(NULL);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    InsertItem(&curTreeItem);

    // Build the string and inserts the item
    ::sprintf_s(buffer, 300, m_SortedKey, pField->IsSorted() ? "1" : "0");
    curTreeItem.hParent             = hRootItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = 4;
    curTreeItem.item.iSelectedImage = 4;
    curTreeItem.item.pszText        = (char*)((const char*)buffer);
    curTreeItem.item.lParam         = LPARAM(NULL);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    InsertItem(&curTreeItem);

    PSS_HistoryField* pHistory = m_pFieldRepository->FindFieldHistory(pField->GetFieldName());

    if (pHistory)
    {
        // build the string and inserts the item
        ::sprintf_s(buffer, 300, m_IsReadOnlyKey, pHistory->IsReadOnly() ? "1" : "0");
        curTreeItem.hParent             = hRootItem;
        curTreeItem.hInsertAfter        = TVI_LAST;
        curTreeItem.item.iImage         = 5;
        curTreeItem.item.iSelectedImage = 5;
        curTreeItem.item.pszText        = (char*)((const char*)buffer);
        curTreeItem.item.lParam         = LPARAM(NULL);
        curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
        InsertItem(&curTreeItem);

        AddFieldHistoryItem(pHistory, hRootItem);
    }
}
//---------------------------------------------------------------------------
void PSS_CommonFieldTreeCtrl::AddFieldHistoryItem(PSS_HistoryField* pHistory, HTREEITEM hParentTreeItem)
{
    if (!pHistory)
        return;

    const CStringArray& valueArray = pHistory->GetValueArray();

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = 6;
    curTreeItem.item.iSelectedImage = 6;
    curTreeItem.item.pszText        = (char*)((const char*)m_HistoryKey);
    curTreeItem.item.lParam         = LPARAM(NULL);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    HTREEITEM hRootItem             = InsertItem(&curTreeItem);

    const std::size_t valueCount = valueArray.GetSize();

    for (std::size_t i = 0; i < valueCount; ++i)
    {
        curTreeItem.hParent             = hRootItem;
        curTreeItem.hInsertAfter        = TVI_LAST;
        curTreeItem.item.iImage         = 7;
        curTreeItem.item.iSelectedImage = 7;
        curTreeItem.item.pszText        = (char*)((const char*)valueArray.GetAt(i));
        curTreeItem.item.lParam         = LPARAM(NULL);
        curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
        InsertItem(&curTreeItem);
    }
}
//---------------------------------------------------------------------------
