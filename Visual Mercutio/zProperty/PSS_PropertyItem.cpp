/****************************************************************************
 * ==> PSS_PropertyItem ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a property item                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PropertyItem.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_PropertyItem, CObject)
//---------------------------------------------------------------------------
// PSS_PropertyItem
//---------------------------------------------------------------------------
PSS_PropertyItem::PSS_PropertyItem(const PSS_PropertyItem& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_PropertyItem& PSS_PropertyItem::operator = (const PSS_PropertyItem& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::DrawValue(CDC* pDC, CRect& rect)
{}
//---------------------------------------------------------------------------
void PSS_PropertyItem::CreateInPlaceControl(CWnd*           pWndParent,
                                            const CRect&    rect,
                                            ZIInPlaceEdit*& pWndInPlaceControl,
                                            const CSize&    extendedSize)
{
    DestroyInPlaceControl(pWndInPlaceControl);
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::DestroyInPlaceControl(ZIInPlaceEdit*& pWndInPlaceControl)
{
    if (pWndInPlaceControl)
    {
        // check if the value has changed, request the control to save its value
        if (pWndInPlaceControl->GetHasChanged())
            pWndInPlaceControl->SaveValue();

        delete pWndInPlaceControl;
        pWndInPlaceControl = NULL;
    }
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_PropertyItemCategory, PSS_PropertyItem)
//---------------------------------------------------------------------------
// PSS_PropertyItemCategory
//---------------------------------------------------------------------------
PSS_PropertyItemCategory::PSS_PropertyItemCategory(const PSS_PropertyItemCategory& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_PropertyItemCategory& PSS_PropertyItemCategory::operator = (const PSS_PropertyItemCategory& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemCategory::PropertyItemExist(PSS_PropertyItem* pPropertyItem)
{
    IPropertyItemIterator it(&m_PropertyItemSet);

    // iterate through all items
    for (PSS_PropertyItem* pItem = it.GetFirst(); pItem; pItem = it.GetNext())
        // is the same pointer?
        if (pItem == pPropertyItem)
            return true;

    return false;
}
//---------------------------------------------------------------------------
int PSS_PropertyItemCategory::GetEnabledItemNumber() const
{
    int enabledItemNumber = 0;

    IPropertyItemIterator it(&m_PropertyItemSet);

    // iterate through all items
    for (PSS_PropertyItem* pItem = it.GetFirst(); pItem; pItem = it.GetNext())
        // if enabled, increment the counter
        if (pItem->GetEnabled())
            ++enabledItemNumber;

    return enabledItemNumber;
}
//---------------------------------------------------------------------------
PSS_PropertyItem* PSS_PropertyItemCategory::GetPropertyItem(int propID)
{
    IPropertyItemIterator it(&m_PropertyItemSet);

    // iterate through all items
    for (PSS_PropertyItem* pItem = it.GetFirst(); pItem; pItem = it.GetNext())
        // is the same ID?
        if (pItem->GetPropertyID() == propID)
            return pItem;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PropertyItem* PSS_PropertyItemCategory::GetPropertyItem(LPCTSTR pItemName)
{
    IPropertyItemIterator it(&m_PropertyItemSet);

    // iterate through all items
    for (PSS_PropertyItem* pItem = it.GetFirst(); pItem; pItem = it.GetNext())
        // is the same name?
        if (pItem->GetName() == pItemName)
            return pItem;

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemCategory::RemoveAllPropertyItems()
{
    IPropertyItemIterator it(&m_PropertyItemSet);

    // iterate through all items
    for (PSS_PropertyItem* pItem = it.GetFirst(); pItem; pItem = it.GetNext())
        delete pItem;

    // remove all elements
    m_PropertyItemSet.RemoveAll();
}
//---------------------------------------------------------------------------
