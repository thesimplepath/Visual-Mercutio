// ZCSymbolAttributesTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ZCSymbolAttributesTreeCtrl.h"


// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"
// ZIProperties
#include "zProperty\ZIProperties.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const int _CategoryTreeItem = 0;
const int _AttributeTreeItem = 1;

/////////////////////////////////////////////////////////////////////////////
// ZCSymbolAttributesTreeCtrl

ZCSymbolAttributesTreeCtrl::ZCSymbolAttributesTreeCtrl(ZBPropertyAttributes* pPropAttributes /*= NULL*/,
                                                       ZBPropertySet* pPropSet /*= NULL*/)
    : m_pPropAttributes(pPropAttributes),
    m_pPropSet(pPropSet),
    m_HasBeenInitialized(false)
{}

ZCSymbolAttributesTreeCtrl::~ZCSymbolAttributesTreeCtrl()
{
    EmptyDataSet();
}

void ZCSymbolAttributesTreeCtrl::Initialize()
{
    LoadTree();
}

void ZCSymbolAttributesTreeCtrl::Initialize(ZBPropertyAttributes* pPropAttributes, ZBPropertySet* pPropSet)
{
    m_pPropAttributes = pPropAttributes;
    m_pPropSet = pPropSet;
    LoadTree();
}

void ZCSymbolAttributesTreeCtrl::Refresh()
{
    DestroyTree();
    LoadTree();
}

void ZCSymbolAttributesTreeCtrl::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}


BEGIN_MESSAGE_MAP(ZCSymbolAttributesTreeCtrl, ZITreeCtrl)
    //{{AFX_MSG_MAP(ZCSymbolAttributesTreeCtrl)
    ON_WM_CREATE()
    ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
    ON_WM_LBUTTONUP()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZCSymbolAttributesTreeCtrl message handlers


int ZCSymbolAttributesTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (ZITreeCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    LoadTree();

    return 0;
}

BOOL ZCSymbolAttributesTreeCtrl::DestroyWindow()
{
    DestroyTree();

    return CWnd::DestroyWindow();
}

void ZCSymbolAttributesTreeCtrl::DestroyTree()
{
    if (::IsWindow(GetSafeHwnd()))
        DeleteAllItems();
    // Empty the data set first
    EmptyDataSet();
}

void ZCSymbolAttributesTreeCtrl::CreateTree()
{
    if (m_HasBeenInitialized == false)
    {
        // Sets styles
        HasButtons();
        HasLines();
        LinesAtRoot();
        ShowCheckBoxes();
        ShowSelectionAlways();
        // Load images
        LoadImageList(IDB_IL_ATTRIBUTESIMAGES, 17, 1, RGB(255, 255, 255));
        m_HasBeenInitialized = true;
    }
}


void ZCSymbolAttributesTreeCtrl::LoadTree()
{
    // Call the create tree function first,
    // in fact this function is executed only one time for initializing
    // correctly the control
    CreateTree();
    // No property item to show or not property set, do nothing
    if (!m_pPropAttributes || !m_pPropSet)
        return;

    // Run through the property set
    ZBPropertyIterator i(m_pPropSet);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        ProcessProperty(pProp);
    }

    // Now, run through all attributes and check the corresponding element
    // in the tree control
    // Copy all attribute elements
    _ZBPropertyAttributeIterator j(&m_pPropAttributes->GetAttributeSetConst());
    for (_ZBPropertyAttribute* pAttribute = j.GetFirst(); pAttribute != NULL; pAttribute = j.GetNext())
    {
        CheckAttribute(pAttribute);
    }
    // Now run through all elements and check 
    // if all childs are checked, then check the category
    HTREEITEM hCurrent = GetRootItem();
    while (hCurrent != NULL)
    {
        BOOL Checked = FALSE;
        // Check if all childs are checked
        if (ItemHasChildren(hCurrent))
        {
            BOOL Checked = TRUE;

            HTREEITEM hChildItem = GetChildItem(hCurrent);
            while (hChildItem != NULL)
            {
                // The first unchecked item break the loop
                if (!GetCheck(hChildItem))
                {
                    Checked = FALSE;
                    break;
                }
                hChildItem = GetNextSiblingItem(hChildItem);
            }
            // Change the checked flag
            SetCheck(hCurrent, Checked);
        }
        // Retrieve the next top level item
        hCurrent = CTreeCtrl::GetNextItem(hCurrent, TVGN_NEXT);
    }

    // Expand the root
    ExpandRoot(TRUE);

}

bool ZCSymbolAttributesTreeCtrl::ProcessProperty(ZBProperty* pProp)
{
    ASSERT(pProp);

    bool bRetValue = true;
    // First, retrieve the parent
    HTREEITEM hCategoryItem = GetParentProperty(pProp);

    if (!hCategoryItem)
    {
        hCategoryItem = AddPropertyItem(pProp->GetCategory(), pProp->GetCategoryID());
        if (!hCategoryItem)
            bRetValue = false;
    }
    AddPropertyItem(pProp->GetLabel(), pProp->GetCategoryID(), pProp->GetItemID(), hCategoryItem);

    return bRetValue;
}


HTREEITEM ZCSymbolAttributesTreeCtrl::AddPropertyItem(const CString Label, int Category, int Item /*= -1*/, HTREEITEM hParentTreeItem /*= NULL*/)
{
    TV_INSERTSTRUCT     curTreeItem;

    curTreeItem.hParent = hParentTreeItem;
    curTreeItem.hInsertAfter = TVI_LAST;
    if (hParentTreeItem == NULL)
    {
        curTreeItem.item.iImage = _CategoryTreeItem;
        curTreeItem.item.iSelectedImage = _CategoryTreeItem;
    }
    else
    {
        curTreeItem.item.iImage = _AttributeTreeItem;
        curTreeItem.item.iSelectedImage = _AttributeTreeItem;
    }
    curTreeItem.item.pszText = (char*)((const char*)Label);
    curTreeItem.item.lParam = (LPARAM)AddDataToSet(Category, Item);    // Represent a selectable item
    curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return InsertItem(&curTreeItem);
}


HTREEITEM ZCSymbolAttributesTreeCtrl::GetParentProperty(ZBProperty* pProp)
{
    ASSERT(pProp);

    HTREEITEM hTreeItem = NULL;
    // Find the model
    _ZInternalPropertyTreeData* pData;
    pData = FindElementFromDataSet(pProp->GetCategoryID());

    if (pData)
    {
        hTreeItem = FindItemData(pData, (HTREEITEM)NULL); // From item, in fact from root
    }
    return hTreeItem;
}




void ZCSymbolAttributesTreeCtrl::CheckAttribute(_ZBPropertyAttribute* pAttribute)
{
    ASSERT(pAttribute);

    HTREEITEM hTreeItem = NULL;
    // Find the attribute item for the parent
    // Find the model
    _ZInternalPropertyTreeData* pData;
    pData = FindElementFromDataSet(pAttribute);

    if (pData)
    {
        hTreeItem = FindItemData(pData, (HTREEITEM)NULL); // From item, in fact from root
    }
    // If not found, set the root as parent
    if (hTreeItem)
        SetCheck(hTreeItem, TRUE);
}


bool ZCSymbolAttributesTreeCtrl::FillCorrespondingCheckedItems()
{
    // No property item to show or not property set, do nothing
    if (!m_pPropAttributes || !m_pPropSet)
        return false;

    // First, we need to remove all existing attributes 
    m_pPropAttributes->RemoveAllAttributes();

    // Run the set of internal elements and
    // Check if items are checked.
    // If yes, add them to the property attributes 
    HTREEITEM hTreeItem;
    _ZInternalPropertyTreeDataIterator i(&m_DataSet);
    for (_ZInternalPropertyTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext())
    {
        if (pElement->m_dtp == _ZInternalPropertyTreeData::patp_Item &&
            pElement->m_pPropAttribute)
        {
            // Find the right item
            hTreeItem = FindItemData(pElement, (HTREEITEM)NULL); // From item, in fact from root
            // If found and checked,
            // add it to the attributes set
            if (hTreeItem && GetCheck(hTreeItem))
                m_pPropAttributes->AddAttribute(pElement->m_pPropAttribute->GetCategoryID(),
                                                pElement->m_pPropAttribute->GetItemID());
        }
    }

    return true;
}


void ZCSymbolAttributesTreeCtrl::OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pnmhdr;
    /*
        // Expand
        if (pNMTreeView->action == 2)
        {
            // Not the root item, only a simple group
            if (pNMTreeView->itemNew.hItem != GetRootItem())
            {
                TVITEM item        = { 0 };
                item.mask        = TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
                item.hItem        = pNMTreeView->itemNew.hItem;
                item.iImage = _UserGroupOpenTreeItem;
                item.iSelectedImage = _UserGroupOpenTreeItem;
                SetItem( &item );
            }
        }
        else
            // Collapse
            if (pNMTreeView->action == 1)
            {
                // Not the root item, only a simple group
                if (pNMTreeView->itemNew.hItem != GetRootItem())
                {
                    TVITEM item        = { 0 };
                    item.mask        = TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
                    item.hItem        = pNMTreeView->itemNew.hItem;
                    item.iImage = _UserGroupTreeItem;
                    item.iSelectedImage = _UserGroupTreeItem;
                    SetItem( &item );
                }
            }
    */
    *pLResult = TRUE;

}


CObject* ZCSymbolAttributesTreeCtrl::GetDragObject(HTREEITEM DragItem)
{
    _ZInternalPropertyTreeData*    pObj = (_ZInternalPropertyTreeData*)GetItemData(DragItem);
    // Not implemented, due to the fact 
    // _ZBPropertyAttribute is not derived from CObject
//    if (pObj != NULL)
//        return pObj->m_pPropAttribute;
    return NULL;
}

// Data set methods

_ZInternalPropertyTreeData::_ZInternalPropertyTreeData()
{
    m_dtp = patp_Unknown;
    m_pPropAttribute = NULL;
}
_ZInternalPropertyTreeData::_ZInternalPropertyTreeData(int Category, int Item /*= -1*/)
{
    m_dtp = (Item == -1) ? patp_Category : patp_Item;
    m_pPropAttribute = new _ZBPropertyAttribute(Category, Item);
}
_ZInternalPropertyTreeData::_ZInternalPropertyTreeData(_ZBPropertyAttribute* pPropAttribute)
{
    m_dtp = patp_Item;
    m_pPropAttribute = pPropAttribute->Clone();
}

_ZInternalPropertyTreeData::~_ZInternalPropertyTreeData()
{
    // In the destructor, just reset all values
    m_dtp = patp_Unknown;
    delete m_pPropAttribute;
    m_pPropAttribute = NULL;
}





void ZCSymbolAttributesTreeCtrl::EmptyDataSet()
{
    _ZInternalPropertyTreeDataIterator i(&m_DataSet);

    for (_ZInternalPropertyTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext())
    {
        delete pElement;
    }
    m_DataSet.RemoveAll();
}


_ZInternalPropertyTreeData* ZCSymbolAttributesTreeCtrl::FindElementFromDataSet(int Category, int Item /*= -1*/)
{
    _ZInternalPropertyTreeDataIterator i(&m_DataSet);

    for (_ZInternalPropertyTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext())
    {
        // Search for category only
        if (Item == -1)
        {
            if (pElement->m_dtp == _ZInternalPropertyTreeData::patp_Category &&
                pElement->m_pPropAttribute &&
                pElement->m_pPropAttribute->GetCategoryID() == Category)
                return pElement;
        }
        else
        {
            if (pElement->m_dtp == _ZInternalPropertyTreeData::patp_Item &&
                pElement->m_pPropAttribute &&
                pElement->m_pPropAttribute->GetCategoryID() == Category &&
                pElement->m_pPropAttribute->GetItemID() == Item)
                return pElement;
        }
    }
    return NULL;
}

_ZInternalPropertyTreeData* ZCSymbolAttributesTreeCtrl::FindElementFromDataSet(_ZBPropertyAttribute* pPropAttribute)
{
    if (!pPropAttribute)
        return NULL;

    _ZInternalPropertyTreeDataIterator i(&m_DataSet);

    for (_ZInternalPropertyTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext())
    {
        if (pElement->m_pPropAttribute &&
            pElement->m_pPropAttribute->GetCategoryID() == pPropAttribute->GetCategoryID() &&
            pElement->m_pPropAttribute->GetItemID() == pPropAttribute->GetItemID())
            return pElement;
    }
    return NULL;
}

_ZInternalPropertyTreeData* ZCSymbolAttributesTreeCtrl::AddDataToSet(int Category, int Item /*= -1*/)
{
    _ZInternalPropertyTreeData* pData = new _ZInternalPropertyTreeData(Category, Item);
    m_DataSet.Add(pData);
    return pData;
}

_ZInternalPropertyTreeData* ZCSymbolAttributesTreeCtrl::AddDataToSet(_ZBPropertyAttribute* pPropAttribute)
{
    _ZInternalPropertyTreeData* pData = new _ZInternalPropertyTreeData(pPropAttribute);
    m_DataSet.Add(pData);
    return pData;
}





void ZCSymbolAttributesTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{

    ZITreeCtrl::OnLButtonUp(nFlags, point);

    UINT Flags;

    HTREEITEM hItem = HitTest(point, &Flags);
    if ((hItem != NULL) && (TVHT_ONITEM & Flags))
    {
        _ZInternalPropertyTreeData*    pObj = (_ZInternalPropertyTreeData*)GetItemData(hItem);
        if (pObj->m_dtp == _ZInternalPropertyTreeData::patp_Category &&
            pObj->m_pPropAttribute)
        {
            // Populate the checked flag to all childrens
            BOOL Checked = GetCheck(hItem);

            if (ItemHasChildren(hItem))
            {

                HTREEITEM hChildItem = GetChildItem(hItem);
                while (hChildItem != NULL)
                {
                    SetCheck(hChildItem, Checked);
                    hChildItem = GetNextSiblingItem(hChildItem);
                }
            }
        }
        else
        {
            // Check if all attributes of the group are selected or not
            // then check or not the parent category
            HTREEITEM hParentItem = GetParentItem(hItem);
            if (hParentItem != NULL)
            {
                BOOL Checked = TRUE;
                HTREEITEM hChildItem = GetChildItem(hParentItem);
                while (hChildItem != NULL)
                {
                    // The first unchecked item break the loop
                    if (!GetCheck(hChildItem))
                    {
                        Checked = FALSE;
                        break;
                    }
                    hChildItem = GetNextSiblingItem(hChildItem);
                }
                // Change the checked flag of the category
                SetCheck(hParentItem, Checked);

            }
        }

    }
}
