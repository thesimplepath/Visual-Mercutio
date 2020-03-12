/****************************************************************************
 * ==> PSS_SymbolAttributesTreeCtrl ----------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol attributes tree controller               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SymbolAttributesTreeCtrl.h"

// processsoft
#include "zProperty\ZIProperties.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int g_CategoryTreeItem  = 0;
const int g_AttributeTreeItem = 1;
//---------------------------------------------------------------------------
// PSS_SymbolAttributesTreeCtrl::ITreeData
//---------------------------------------------------------------------------
PSS_SymbolAttributesTreeCtrl::ITreeData::ITreeData() :
    CObject(),
    m_pPropAttribute(NULL),
    m_Type(IE_DT_Unknown)
{}
//---------------------------------------------------------------------------
PSS_SymbolAttributesTreeCtrl::ITreeData::ITreeData(int category, int item) :
    CObject(),
    m_pPropAttribute(new PSS_PropertyAttributes::IAttribute(category, item)),
    m_Type(item == -1 ? IE_DT_Category : IE_DT_Item)
{}
//---------------------------------------------------------------------------
PSS_SymbolAttributesTreeCtrl::ITreeData::ITreeData(PSS_PropertyAttributes::IAttribute* pPropAttribute) :
    CObject(),
    m_pPropAttribute(NULL),
    m_Type(IE_DT_Item)
{
    if (pPropAttribute)
        m_pPropAttribute = pPropAttribute->Clone();
}
//---------------------------------------------------------------------------
PSS_SymbolAttributesTreeCtrl::ITreeData::~ITreeData()
{
    if (m_pPropAttribute)
        delete m_pPropAttribute;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SymbolAttributesTreeCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(PSS_SymbolAttributesTreeCtrl)
    ON_WM_CREATE()
    ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
    ON_WM_LBUTTONUP()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SymbolAttributesTreeCtrl
//---------------------------------------------------------------------------
PSS_SymbolAttributesTreeCtrl::PSS_SymbolAttributesTreeCtrl(PSS_PropertyAttributes* pPropAttributes, ZBPropertySet* pPropSet) :
    PSS_TreeCtrl(),
    m_pPropAttributes(pPropAttributes),
    m_pPropSet(pPropSet),
    m_HasBeenInitialized(false)
{}
//---------------------------------------------------------------------------
PSS_SymbolAttributesTreeCtrl::~PSS_SymbolAttributesTreeCtrl()
{
    // NOTE use the fully qualified name here to avoid to call a pure virtual function during the destruction
    PSS_SymbolAttributesTreeCtrl::EmptyDataSet();
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributesTreeCtrl::Initialize()
{
    LoadTree();
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributesTreeCtrl::Initialize(PSS_PropertyAttributes* pPropAttributes, ZBPropertySet* pPropSet)
{
    m_pPropAttributes = pPropAttributes;
    m_pPropSet        = pPropSet;

    LoadTree();
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributesTreeCtrl::Refresh()
{
    DestroyTree();
    LoadTree();
}
//---------------------------------------------------------------------------
bool PSS_SymbolAttributesTreeCtrl::FillMatchingCheckedItems()
{
    // no property item to show or not property set, do nothing
    if (!m_pPropAttributes || !m_pPropSet)
        return false;

    // need to remove all existing attributes
    m_pPropAttributes->RemoveAllAttributes();

    ITreeDataIterator it(&m_DataSet);

    // iterate the internal element set and check if items are checked. If yes, add them to the property attributes 
    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
    {
        if (pElement->m_Type == ITreeData::IE_DT_Item && pElement->m_pPropAttribute)
        {
            // find the right item
            HTREEITEM hTreeItem = FindItemData(pElement, HTREEITEM(NULL));

            // if found and checked, add it to the attributes set
            if (hTreeItem && GetCheck(hTreeItem))
                m_pPropAttributes->AddAttribute(pElement->m_pPropAttribute->GetCategoryID(),
                                                pElement->m_pPropAttribute->GetItemID());
        }
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributesTreeCtrl::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
BOOL PSS_SymbolAttributesTreeCtrl::DestroyWindow()
{
    DestroyTree();

    return CWnd::DestroyWindow();
}
//---------------------------------------------------------------------------
int PSS_SymbolAttributesTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_TreeCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    LoadTree();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributesTreeCtrl::OnItemExpanded(LPNMHDR pnmhdr, LRESULT* pLResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pnmhdr;
    *pLResult                = TRUE;

}
//---------------------------------------------------------------------------
void PSS_SymbolAttributesTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{

    PSS_TreeCtrl::OnLButtonUp(nFlags, point);

    UINT      flags;
    HTREEITEM hItem = HitTest(point, &flags);

    if (hItem && (TVHT_ONITEM & flags))
    {
        ITreeData* pObj = reinterpret_cast<ITreeData*>(GetItemData(hItem));

        if (pObj->m_Type == ITreeData::IE_DT_Category && pObj->m_pPropAttribute)
        {
            // populate the checked flag to all childrens
            const BOOL checked = GetCheck(hItem);

            if (ItemHasChildren(hItem))
            {
                HTREEITEM hChildItem = GetChildItem(hItem);

                while (hChildItem)
                {
                    SetCheck(hChildItem, checked);
                    hChildItem = GetNextSiblingItem(hChildItem);
                }
            }
        }
        else
        {
            // check if all group attributes are selected or not, then check or not the parent category
            HTREEITEM hParentItem = GetParentItem(hItem);

            if (hParentItem)
            {
                BOOL      checked    = TRUE;
                HTREEITEM hChildItem = GetChildItem(hParentItem);

                while (hChildItem)
                {
                    // the first unchecked item break the loop
                    if (!GetCheck(hChildItem))
                    {
                        checked = FALSE;
                        break;
                    }

                    hChildItem = GetNextSiblingItem(hChildItem);
                }

                // change the checked flag of the category
                SetCheck(hParentItem, checked);
            }
        }
    }
}
//---------------------------------------------------------------------------
CObject* PSS_SymbolAttributesTreeCtrl::GetDragObject(HTREEITEM dragItem)
{
    // not implemented, because the attribute isn't derived from CObject
    return NULL;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributesTreeCtrl::CreateTree()
{
    if (m_HasBeenInitialized)
        return;

    // set styles
    HasButtons();
    HasLines();
    LinesAtRoot();
    ShowCheckBoxes();
    ShowSelectionAlways();

    // load images
    LoadImageList(IDB_IL_ATTRIBUTESIMAGES, 17, 1, RGB(255, 255, 255));
    m_HasBeenInitialized = true;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributesTreeCtrl::LoadTree()
{
    // create the tree. NOTE this function will do nothing if already created
    CreateTree();

    // no property item to show or not property set, do nothing
    if (!m_pPropAttributes || !m_pPropSet)
        return;

    ZBPropertyIterator itProp(m_pPropSet);

    // iterate through the property set
    for (PSS_Property* pProp = itProp.GetFirst(); pProp; pProp = itProp.GetNext())
        ProcessProperty(pProp);

    PSS_PropertyAttributes::IAttributeIterator itAttr(&m_pPropAttributes->GetAttributeSet());

    // iterate through all attributes and check the matching element in the tree control. Copy all element attributes
    for (PSS_PropertyAttributes::IAttribute* pAttribute = itAttr.GetFirst(); pAttribute; pAttribute = itAttr.GetNext())
        CheckAttribute(pAttribute);

    HTREEITEM hCurrent = GetRootItem();

    // iterate through all elements and check if all children are checked, then check the category
    while (hCurrent)
    {
        // check if all children are checked
        if (ItemHasChildren(hCurrent))
        {
            HTREEITEM hChildItem = GetChildItem(hCurrent);
            BOOL      checked    = TRUE;

            while (hChildItem)
            {
                // the first unchecked item break the loop
                if (!GetCheck(hChildItem))
                {
                    checked = FALSE;
                    break;
                }

                hChildItem = GetNextSiblingItem(hChildItem);
            }

            // change the checked flag
            SetCheck(hCurrent, checked);
        }

        // get the next top level item
        hCurrent = CTreeCtrl::GetNextItem(hCurrent, TVGN_NEXT);
    }

    // expand the root
    ExpandRoot(TRUE);
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributesTreeCtrl::DestroyTree()
{
    if (::IsWindow(GetSafeHwnd()))
        DeleteAllItems();

    // empty the data set
    EmptyDataSet();
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributesTreeCtrl::EmptyDataSet()
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        delete pElement;

    m_DataSet.RemoveAll();
}
//---------------------------------------------------------------------------
bool PSS_SymbolAttributesTreeCtrl::ProcessProperty(PSS_Property* pProp)
{
    ASSERT(pProp);

    bool result = true;

    // get the parent
    HTREEITEM hCategoryItem = GetParentProperty(pProp);

    if (!hCategoryItem)
    {
        hCategoryItem = AddPropertyItem(pProp->GetCategory(), pProp->GetCategoryID());

        if (!hCategoryItem)
            result = false;
    }

    AddPropertyItem(pProp->GetLabel(), pProp->GetCategoryID(), pProp->GetItemID(), hCategoryItem);

    return result;
}
//---------------------------------------------------------------------------
HTREEITEM PSS_SymbolAttributesTreeCtrl::GetParentProperty(PSS_Property* pProp)
{
    ASSERT(pProp);

    HTREEITEM hTreeItem = NULL;

    // Find the model
    ITreeData* pData = FindElementFromDataSet(pProp->GetCategoryID());

    if (pData)
        hTreeItem = FindItemData(pData, HTREEITEM(NULL));

    return hTreeItem;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributesTreeCtrl::CheckAttribute(PSS_PropertyAttributes::IAttribute* pAttribute)
{
    ASSERT(pAttribute);

    HTREEITEM hTreeItem = NULL;

    // find the attribute item for the parent. Find the model
    ITreeData* pData = FindElementFromDataSet(pAttribute);

    if (pData)
        hTreeItem = FindItemData(pData, HTREEITEM(NULL));

    // if not found, set the root as parent
    if (hTreeItem)
        SetCheck(hTreeItem, TRUE);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_SymbolAttributesTreeCtrl::AddPropertyItem(const CString& label,
                                                        int            category,
                                                        int            item,
                                                        HTREEITEM      hParentTreeItem)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent      = hParentTreeItem;
    curTreeItem.hInsertAfter = TVI_LAST;
    curTreeItem.item.pszText = (char*)((const char*)label);
    curTreeItem.item.lParam  = LPARAM(AddDataToSet(category, item));
    curTreeItem.item.mask    = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    if (!hParentTreeItem)
    {
        curTreeItem.item.iImage         = g_CategoryTreeItem;
        curTreeItem.item.iSelectedImage = g_CategoryTreeItem;
    }
    else
    {
        curTreeItem.item.iImage         = g_AttributeTreeItem;
        curTreeItem.item.iSelectedImage = g_AttributeTreeItem;
    }

    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
PSS_SymbolAttributesTreeCtrl::ITreeData* PSS_SymbolAttributesTreeCtrl::FindElementFromDataSet(int category, int item)
{
    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        // search for category only
        if (item == -1)
        {
            if (pElement->m_Type == ITreeData::IE_DT_Category &&
                pElement->m_pPropAttribute                    &&
                pElement->m_pPropAttribute->GetCategoryID() == category)
                return pElement;
        }
        else
        if (pElement->m_Type == ITreeData::IE_DT_Item               &&
            pElement->m_pPropAttribute                              &&
            pElement->m_pPropAttribute->GetCategoryID() == category &&
            pElement->m_pPropAttribute->GetItemID()     == item)
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_SymbolAttributesTreeCtrl::ITreeData* PSS_SymbolAttributesTreeCtrl::FindElementFromDataSet(PSS_PropertyAttributes::IAttribute* pPropAttribute)
{
    if (!pPropAttribute)
        return NULL;

    ITreeDataIterator it(&m_DataSet);

    for (ITreeData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pElement->m_pPropAttribute                                                     &&
            pElement->m_pPropAttribute->GetCategoryID() == pPropAttribute->GetCategoryID() &&
            pElement->m_pPropAttribute->GetItemID()     == pPropAttribute->GetItemID())
            return pElement;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_SymbolAttributesTreeCtrl::ITreeData* PSS_SymbolAttributesTreeCtrl::AddDataToSet(int category, int item)
{
    std::unique_ptr<ITreeData> pData(new ITreeData(category, item));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
PSS_SymbolAttributesTreeCtrl::ITreeData* PSS_SymbolAttributesTreeCtrl::AddDataToSet(PSS_PropertyAttributes::IAttribute* pPropAttribute)
{
    std::unique_ptr<ITreeData> pData(new ITreeData(pPropAttribute));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
