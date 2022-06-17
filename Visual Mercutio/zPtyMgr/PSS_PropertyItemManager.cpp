/****************************************************************************
 * ==> PSS_PropertyItemManager ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a property item manager                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PropertyItemManager.h"

// processsoft
#include "zBaseLib\PSS_SystemOption.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "PSS_PropertyListCtrl.h"
#include "PSS_PropertyItems.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const CString g_PropertyItemManagerSectionName = _T("_PropertyItemManagerSaveState");
const CString g_PropertyItemStateEntityName    = _T("_PropertyItemState");
//---------------------------------------------------------------------------
// PSS_PropertyItemManager
//---------------------------------------------------------------------------
PSS_PropertyItemManager::PSS_PropertyItemManager(const PSS_PropertyItemManager& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_PropertyItemManager& PSS_PropertyItemManager::operator = (const PSS_PropertyItemManager& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::Empty()
{
    FreePropertySet();
    m_pCurrentData = NULL;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::SetPropertyListCtrl(PSS_PropertyListCtrl* pCtrl)
{
    m_pWndPropertyListCtrl = pCtrl;
}
//---------------------------------------------------------------------------
PSS_PropertyItemCategory* PSS_PropertyItemManager::GetTab(PSS_PropertyItem* pPropertyItem)
{
    IItemCategoryIterator it(&m_PropertyItemTabSet);

    // iterate through all items
    for (PSS_PropertyItemCategory* pItemCat = it.GetFirst(); pItemCat; pItemCat = it.GetNext())
        if (pItemCat->PropertyItemExist(pPropertyItem))
            return pItemCat;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_Property* PSS_PropertyItemManager::GetMatchingProperty(PSS_PropertyItem* pPropertyItem)
{
    PSS_PropertyItemCategory* pCat = GetTab(pPropertyItem);

    if (!pCat)
        return NULL;

    PSS_Properties::IPropertyIterator it(&m_PropSet);

    // iterate through the data and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == pCat->GetPropertyID() && pProp->GetItemID() == pPropertyItem->GetPropertyID())
            return pProp;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PropertyItemCategory* PSS_PropertyItemManager::AddNewTab(LPCTSTR pTabName)
{
    PSS_PropertyItemCategory* pTab = TabExist(pTabName);

    if (!pTab)
    {
        std::unique_ptr<PSS_PropertyItemCategory> pNewTab(new PSS_PropertyItemCategory(pTabName));
        m_PropertyItemTabSet.Add(pNewTab.get());
        pTab = pNewTab.release();
    }

    return pTab;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::CheckState(int fromControlIndex, BYTE fromPropertyItemID)
{
    if (!m_pWndPropertyListCtrl)
        return;

    bool doInsert = false;

    IItemCategoryIterator itCat(&m_PropertyItemTabSet);

    // iterate through all items
    for (PSS_PropertyItemCategory* pPropertyItemTab = itCat.GetFirst(); pPropertyItemTab; pPropertyItemTab = itCat.GetNext())
    {
        if (doInsert)
            if (pPropertyItemTab->GetEnabled())
            {
                m_pWndPropertyListCtrl->InsertPropertyItem(pPropertyItemTab, ++fromControlIndex);
                pPropertyItemTab->SetChildrenVisible();
            }
            else
                continue;

        PSS_PropertyItemCategory::IPropertyItemIterator itItem(&pPropertyItemTab->GetPropertyItemSet());

        // iterate through categories elements
        for (PSS_PropertyItem* pPropertyItem = itItem.GetFirst(); pPropertyItem; pPropertyItem = itItem.GetNext())
            if (doInsert)
            {
                if (pPropertyItem->GetEnabled())
                    m_pWndPropertyListCtrl->InsertPropertyItem(pPropertyItem, ++fromControlIndex);
            }
            else
            if (fromPropertyItemID == pPropertyItem->GetPropertyID() || fromPropertyItemID == 0)
            {
                int items = m_pWndPropertyListCtrl->GetCount();

                if (items != fromControlIndex + 1)
                {
                    int i  = items - 1;
                    items -= (fromControlIndex + 1);

                    while (items > 0)
                    {
                        m_pWndPropertyListCtrl->DeleteString(i);
                        --i;
                        --items;
                    }
                }

                doInsert = true;
            }
    }
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::UpdateControlData(const PSS_Properties* pData)
{
    if (!pData)
        return true;

    // delete all tabs
    DeleteAllTabs();

    // delete all properties
    FreePropertySet();

    // get the property set from object
    const_cast<PSS_Properties*>(pData)->FillProperties(m_PropSet);

    const bool result = UpdateControlData();

    m_pCurrentData = const_cast<PSS_Properties*>(pData);

    return result;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::UpdateControlData(PSS_Properties::IPropertySet& propSet)
{
    // delete all tabs
    DeleteAllTabs();

    // delete all properties
    FreePropertySet();

    PSS_Properties::IPropertyIterator it(&propSet);

    // duplicate the set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        m_PropSet.Add(pProp->Dup());

    bool result = UpdateControlData();

    m_pCurrentData = NULL;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::UpdatePropertyData(PSS_PropertyItem* pPropertyItem /*= NULL*/)
{
    // if no property item specified, update all
    if (!pPropertyItem)
    {
        PSS_Properties::IPropertyIterator it(&m_PropSet);

        // iterate through the list of data and fill the property set
        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        {
            // find the category
            PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

            if (!pTab)
                continue;

            // check if already exists
            PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

            if (!pPropItem)
                continue;

            // Sets the appropriate data to the property item
            SetItemDataToProperty(pPropItem, *pProp);

            // enables the property and the string format type
            pProp->SetEnabled(pPropItem->GetEnabled());
            pProp->SetStringFormat(pPropItem->GetStringFormat());
        }

        // send the property set to the object
        return (m_pCurrentData) ? m_pCurrentData->SaveProperties(m_PropSet) : true;
    }

    // one value is specified and needs only one save
    PSS_Properties::IPropertyIterator it(&m_PropSet);
    PSS_Property* pFoundProp = NULL;

    // iterate through the data and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        // find the category
        PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
            continue;

        // check if already exists
        PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

        if (!pPropItem || pPropItem != pPropertyItem)
            continue;

        // set the appropriate data to the property item
        SetItemDataToProperty(pPropItem, *pProp);

        pFoundProp = pProp;

        break;
    }

    if (pFoundProp && m_pCurrentData)
        // only if value has changed
        if (pFoundProp->GetHasChanged())
            // send the property to the object
            return m_pCurrentData->SaveProperty(*pFoundProp);
        else
            return true;

    // not found
    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::CheckCurrentPropertyData(PSS_PropertyItem* pPropertyItem, CString& proposedValue)
{
    // if no item specified, assume the data are entered correctly
    if (!pPropertyItem)
        return true;

    // one value is specified and needs only one save
    PSS_Properties::IPropertyIterator it(&m_PropSet);
    PSS_Property* pFoundProp = NULL;

    // iterate through the data and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        // find the category
        PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
            continue;

        // check if already exists
        PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

        if (!pPropItem || pPropItem != pPropertyItem)
            continue;

        // set the appropriate data to the property item
        SetItemDataToProperty(pPropItem, *pProp);

        pFoundProp = pProp;

        break;
    }

    // send the property to the object
    if (pFoundProp && m_pCurrentData)
        return m_pCurrentData->CheckPropertyValue(*pFoundProp, proposedValue, m_PropSet);

    // not found
    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::ProcessExtendedCurrentPropertyData(PSS_PropertyItem* pPropertyItem,
                                                                 CString&          proposedValue,
                                                                 bool&             refresh)
{
    // if no item specified, assume the data are entered correctly
    if (!pPropertyItem)
        return true;

    // one value is specified and needs only one save
    PSS_Properties::IPropertyIterator it(&m_PropSet);
    PSS_Property* pFoundProp = NULL;

    // Now run through the list of data and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        // find the category
        PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
            continue;

        // check if already exists
        PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

        if (!pPropItem || pPropItem != pPropertyItem)
            continue;

        //set the appropriate data to the property item
        SetItemDataToProperty(pPropItem, *pProp);

        pFoundProp = pProp;

        break;
    }

    if (pFoundProp && m_pCurrentData)
        // send the property to the object
        if (m_pCurrentData->ProcessExtendedInput(*pFoundProp, proposedValue, m_PropSet, refresh))
        {
            ApplyPropertyChanges();
            return true;
        }

    // not found
    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::ProcessMenuCommandCurrentPropertyData(int               menuCmdID,
                                                                    PSS_PropertyItem* pPropertyItem,
                                                                    CString&          proposedValue,
                                                                    bool&             refresh)
{
    // if no item specified, assume the data are entered correctly
    if (!pPropertyItem)
        return true;

    // one value is specified and needs only one save
    PSS_Properties::IPropertyIterator it(&m_PropSet);
    PSS_Property* pFoundProp = NULL;

    // iterate through the data and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        // find the category
        PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
            continue;

        // check if already exists
        PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

        if (!pPropItem || pPropItem != pPropertyItem)
            continue;

        // set the appropriate data to the property item
        SetItemDataToProperty(pPropItem, *pProp);

        pFoundProp = pProp;

        break;
    }

    if (pFoundProp && m_pCurrentData)
        // send the property to the object
        if (m_pCurrentData->ProcessMenuCommand(menuCmdID, *pFoundProp, proposedValue, m_PropSet, refresh))
        {
            ApplyPropertyChanges();
            return true;
        }

    // not found
    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::SavePropertyState(PSS_PropertyItem* pPropertyItem)
{
    IPropertyState* pPropState = GetPropertyState(pPropertyItem);

    // if not found, create a new property
    if (!pPropState)
    {
        PSS_Property* pCorrespondingProperty = GetMatchingProperty(pPropertyItem);

        if (pCorrespondingProperty)
        {
            std::unique_ptr<IPropertyState> pNewPropState(new IPropertyState(*pCorrespondingProperty));
            m_PropertyState.Add(pNewPropState.get());
            pPropState = pNewPropState.release();
        }
    }

    // save the state
    if (pPropState)
    {
        pPropState->SetSize(pPropertyItem->GetSize());
        pPropState->SetExtendedSize(pPropertyItem->GetExtendedSize());
        pPropState->SetItemOrder(pPropertyItem->GetItemOrder());
        pPropState->SetCategoryOrder(pPropertyItem->GetCategoryOrder());

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::SavePropertyState(PSS_PropertyItemCategory* pPropertyCategoryItem)
{
    IPropertyState* pPropState = GetPropertyCategoryState(pPropertyCategoryItem);

    // if not found, create a new property
    if (!pPropState)
    {
        std::unique_ptr<IPropertyState> pNewPropState(new IPropertyState(*pPropertyCategoryItem));
        m_PropertyState.Add(pNewPropState.get());
        pPropState = pNewPropState.release();
    }

    // save the state
    if (pPropState)
    {
        // change the item state
        pPropState->SetCollapsed(!pPropertyCategoryItem->GetChildrenVisible());
        pPropState->SetSize(pPropertyCategoryItem->GetSize());
        pPropState->SetExtendedSize(pPropertyCategoryItem->GetExtendedSize());
        pPropState->SetItemOrder(pPropertyCategoryItem->GetItemOrder());
        pPropState->SetCategoryOrder(pPropertyCategoryItem->GetCategoryOrder());

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::SetPropertyStateToProperty(PSS_PropertyItem* pPropertyItem)
{
    IPropertyState* pPropState = GetPropertyState(pPropertyItem);

    if (pPropState)
    {
        pPropertyItem->SetSize(pPropState->GetSize());
        pPropertyItem->SetExtendedSize(pPropState->GetExtendedSize());
        pPropertyItem->SetItemOrder(pPropState->GetItemOrder());
        pPropertyItem->SetCategoryOrder(pPropState->GetCategoryOrder());

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::SetPropertyStateToProperty(PSS_PropertyItemCategory* pPropertyCategoryItem)
{
    IPropertyState* pPropState = GetPropertyCategoryState(pPropertyCategoryItem);

    if (pPropState)
    {
        pPropertyCategoryItem->SetChildrenVisible(!pPropState->GetCollapsed());
        pPropertyCategoryItem->SetSize(pPropState->GetSize());
        pPropertyCategoryItem->SetExtendedSize(pPropState->GetExtendedSize());
        pPropertyCategoryItem->SetItemOrder(pPropState->GetItemOrder());
        pPropertyCategoryItem->SetCategoryOrder(pPropState->GetCategoryOrder());

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
PSS_PropertyItemManager::IPropertyState* PSS_PropertyItemManager::GetPropertyState(PSS_PropertyItem* pPropertyItem)
{
    PSS_Property* pCorrespondingProperty = GetMatchingProperty(pPropertyItem);

    if (pCorrespondingProperty)
    {
        IPropertyStateIterator it(&m_PropertyState);

        for (IPropertyState* pPropState = it.GetFirst(); pPropState; pPropState = it.GetNext())
            if (pPropState->GetCategoryID() == pCorrespondingProperty->GetCategoryID() &&
                (!pPropertyItem->GetSaveStatePerProperty() || pPropState->GetItemID() == pCorrespondingProperty->GetItemID()))
                return pPropState;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PropertyItemManager::IPropertyState* PSS_PropertyItemManager::GetPropertyCategoryState(PSS_PropertyItemCategory* pPropertyCategoryItem)
{
    if (pPropertyCategoryItem)
    {
        IPropertyStateIterator it(&m_PropertyState);

        for (IPropertyState* pPropState = it.GetFirst(); pPropState; pPropState = it.GetNext())
            if (pPropState->GetCategoryID() == pPropertyCategoryItem->GetPropertyID() && !pPropState->GetItemID())
                return pPropState;
    }

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::LoadStateFromIniFile(const CString& iniFile)
{
    // delete all states
    DeletePropertyState();

    PSS_SystemOption SystemOption(iniFile, g_PropertyItemManagerSectionName);

    std::size_t index = 0;

    do
    {
        CString keyName;

        // format the key
        keyName.Format(_T("%s%d"), (const char*)g_PropertyItemStateEntityName, index);

        const CString line = SystemOption.ReadOption(keyName, _T(""));

        if (line.IsEmpty())
            break;

        ++index;

        PSS_Tokenizer token;

        // extract the object number
        CString str = token.GetFirstToken(line);

        if (str.IsEmpty())
            continue;

        const double objectReference = std::atof((const char*)str);

        // Extract the category ID
        str = token.GetNextToken();

        if (str.IsEmpty())
            continue;

        const int categoryID = std::atoi((const char*)str);

        // Extract the item ID
        str = token.GetNextToken();

        if (str.IsEmpty())
            continue;

        const int itemID = std::atoi((const char*)str);

        // extract the collapsed flag
        str = token.GetNextToken();

        if (str.IsEmpty())
            continue;

        const bool collapsed = (str.GetAt(0) == '1');

        // extract the size
        str = token.GetNextToken();

        if (str.IsEmpty())
            continue;

        const int cx = std::atoi((const char*)str);

        str = token.GetNextToken();

        if (str.IsEmpty())
            continue;

        const int cy = std::atoi((const char*)str);

        // extract the extended size
        str = token.GetNextToken();

        if (str.IsEmpty())
            continue;

        const int cxExt = std::atoi((const char*)str);

        str = token.GetNextToken();

        if (str.IsEmpty())
            continue;

        const int cyExt = std::atoi((const char*)str);

        // extract the Item Order
        str = token.GetNextToken();

        if (str.IsEmpty())
            continue;

        const int itemOrder = std::atoi((const char*)str);

        // extract the category order
        str = token.GetNextToken();

        if (str.IsEmpty())
            continue;

        const int categoryOrder = std::atoi((const char*)str);

        // all objects were extracted, create the object state
        std::unique_ptr<IPropertyState> pPropState(new IPropertyState());
        pPropState->SetObjectReference(objectReference);
        pPropState->SetCategoryID(categoryID);
        pPropState->SetItemID(itemID);
        pPropState->SetCollapsed(collapsed);
        pPropState->SetSize(CSize(cx, cy));
        pPropState->SetExtendedSize(CSize(cxExt, cyExt));
        pPropState->SetItemOrder(itemOrder);
        pPropState->SetCategoryOrder(categoryOrder);

        // add it to the array of value
        m_PropertyState.Add(pPropState.get());
        pPropState.release();
    }
    // set the maximum loop to 1 million objects, which should be enough
    while (index < 1000000);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::SaveStateToIniFile(const CString& iniFile)
{
    PSS_SystemOption SystemOption(iniFile, g_PropertyItemManagerSectionName);

    IPropertyStateIterator it(&m_PropertyState);
    std::size_t            index = 0;

    for (IPropertyState* pPropState = it.GetFirst(); pPropState; pPropState = it.GetNext(), ++index)
    {
        CString keyName;

        // format the key
        keyName.Format(_T("%s%d"), (const char*)g_PropertyItemStateEntityName, index);

        PSS_Tokenizer token;

        // build the string
        token.AddToken(pPropState->GetObjectReference());
        token.AddToken(pPropState->GetCategoryID());
        token.AddToken(pPropState->GetItemID());
        token.AddToken(pPropState->GetCollapsed());
        token.AddToken(pPropState->GetSize().cx);
        token.AddToken(pPropState->GetSize().cy);
        token.AddToken(pPropState->GetExtendedSize().cx);
        token.AddToken(pPropState->GetExtendedSize().cy);
        token.AddToken(pPropState->GetItemOrder());
        token.AddToken(pPropState->GetCategoryOrder());

        // write the string to the ini file
        SystemOption.WriteOption(keyName, token.GetString());
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::OnDropInternalPropertyItem(PSS_PropertyItem* pSrcPropertyItem,
                                                         PSS_PropertyItem* pDstPropertyItem,
                                                         bool              top2Down)
{
    // if the source is a category
    if (ISA(pSrcPropertyItem, PSS_PropertyItemCategory))
        return OnDropCategory(dynamic_cast<PSS_PropertyItemCategory*>(pSrcPropertyItem), pDstPropertyItem, top2Down);

    PSS_Properties::IPropertyIterator it(&m_PropSet);
    PSS_Property* pFoundSrc = NULL;

    // iterate through the data and locate the source and the destination property
    for (PSS_Property* pSrcProp = it.GetFirst(); pSrcProp; pSrcProp = it.GetNext())
    {
        // find the category
        PSS_PropertyItemCategory* pTab = TabExist(pSrcProp->GetCategory());

        if (!pTab)
            continue;

        // check if already exists
        PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pSrcProp->GetItemID());

        if (!pPropItem || pPropItem != pSrcPropertyItem)
            continue;

        // set the appropriate data to the source property item
        SetItemDataToProperty(pPropItem, *pSrcProp);

        pFoundSrc = pSrcProp;

        break;
    }

    if (!pFoundSrc)
        return false;

    PSS_Property* pFoundDst = NULL;

    for (PSS_Property* pDstProp = it.GetFirst(); pDstProp; pDstProp = it.GetNext())
    {
        // find the category
        PSS_PropertyItemCategory* pTab = TabExist(pDstProp->GetCategory());

        if (!pTab)
            continue;

        // check if already exists
        PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pDstProp->GetItemID());

        if (!pPropItem || pPropItem != pDstPropertyItem)
            continue;

        // set the appropriate data to the destination property item
        SetItemDataToProperty(pPropItem, *pDstProp);

        pFoundDst = pDstProp;

        break;
    }

    if (!pFoundDst)
        return false;

    if (pFoundSrc && pFoundDst && m_pCurrentData)
        if (m_pCurrentData->OnDropInternalPropertyItem(*pFoundSrc, *pFoundDst, top2Down, m_PropSet))
        {
            ApplyPropertyChanges();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
PSS_PropertyItemCategory* PSS_PropertyItemManager::TabExist(LPCTSTR pTabName)
{
    IItemCategoryIterator it(&m_PropertyItemTabSet);

    // iterate through all items
    for (PSS_PropertyItemCategory* pItemCat = it.GetFirst(); pItemCat; pItemCat = it.GetNext())
        if (pItemCat->GetName() == pTabName)
            return pItemCat;

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::ApplyPropertyChanges()
{
    PSS_Properties::IPropertyIterator it(&m_PropSet);

    bool updated = false;

    // iterate through properties
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        // get the category
        PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
            continue;

        // get the property item
        PSS_PropertyItem* pPropertyItem = pTab->GetPropertyItem(pProp->GetItemID());

        // if not exits, continue
        if (!pPropertyItem)
            continue;

        // set the value, enable and name
        SetDataToPropertyItem(pPropertyItem, *pProp);

        pPropertyItem->SetEnabled(pProp->GetEnabled());
        pPropertyItem->SetName(pProp->GetLabel());
        pPropertyItem->SetStringFormat(pProp->GetStringFormat());

        // set the updated flag
        updated = true;
    }

    if (updated)
    {
        m_pWndPropertyListCtrl->RedrawAll();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::UpdateControlData()
{
    PSS_Properties::IPropertyIterator it(&m_PropSet);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        // check the show type
        switch (m_ShowType)
        {
            case IEPropertyShowType::IE_ST_AllProperties:
                break;

            case IEPropertyShowType::IE_ST_StaticProperties:
                if (pProp->IsDynamic())
                    continue;

                break;

            case IEPropertyShowType::IE_ST_DynamicProperties:
                if (!pProp->IsDynamic())
                    continue;

                break;
        }

        PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
        {
            // create the category
            pTab = AddNewTab(pProp->GetCategory());

            // set the category ID
            pTab->SetPropertyID(pProp->GetCategoryID());
            pTab->SetEnabled(true);

            // by default, set the children visible
            pTab->SetChildrenVisible(true);

            // set the information for the category item
            SetPropertyStateToProperty(pTab);
        }

        // check if already exists
        PSS_PropertyItem* pPropertyItem = pTab->GetPropertyItem(pProp->GetItemID());

        // add property item
        if (!pPropertyItem)
        {
            pPropertyItem = CreatePropertyItem(*pProp);

            if (!pPropertyItem)
                return false;

            pTab->AddPropertyItem(pPropertyItem);
        }

        // enable char filtering
        if (pPropertyItem && pProp->GetCharFilterState())
        {
            PSS_MultiLineEditPropertyItem* pMultilineEdit = dynamic_cast<PSS_MultiLineEditPropertyItem*>(pPropertyItem);

            if (pMultilineEdit)
                pMultilineEdit->EnableCharFilter(true);
        }

        // set the appropriate initial data to the property item
        SetDataToPropertyItem(pPropertyItem, *pProp);

        // set the property identifier for further identification
        pPropertyItem->SetPropertyID(pProp->GetItemID());
        pPropertyItem->SetEnabled(pProp->GetEnabled());
        pPropertyItem->SetName(pProp->GetLabel());
        pPropertyItem->SetStringFormat(pProp->GetStringFormat());
        pPropertyItem->SetSaveState(pProp->GetSaveState());
        pPropertyItem->SetSaveStatePerProperty(pProp->GetSaveStatePerProperty());

        // set information from the property state to the property
        if (pProp->GetSaveState())
            SetPropertyStateToProperty(pPropertyItem);
    }

    // check if unused tabs remains and delete them
    DeleteUnusedTab();

    // reorder the categories
    ReorderCategory();

    return true;
}
//---------------------------------------------------------------------------
PSS_PropertyItem* PSS_PropertyItemManager::CreatePropertyItem(PSS_Property& prop)
{
    std::unique_ptr<PSS_PropertyItem> pItem;

    switch (prop.GetType())
    {
        case PSS_Property::IEType::IE_T_EditString:
            pItem.reset(new PSS_StringPropertyItem());
            break;

        case PSS_Property::IEType::IE_T_EditStringReadOnly:
            // read-only and cannot be edited
            pItem.reset(new PSS_StringPropertyItem(NULL, true, false));
            break;

        case PSS_Property::IEType::IE_T_ComboString:
            pItem.reset(new PSS_ListPropertyItem());
            break;

        case PSS_Property::IEType::IE_T_ComboStringReadOnly:
            // read-only
            pItem.reset(new PSS_ListPropertyItem(NULL, true));
            break;

        case PSS_Property::IEType::IE_T_EditNumber:
            if (prop.GetValueType() == PSS_Property::IEValueType::IE_VT_Double)
                pItem.reset(new PSS_NumberPropertyItem(prop.GetValueDouble()));
            else
            if (prop.GetValueType() == PSS_Property::IEValueType::IE_VT_Float)
                pItem.reset(new PSS_NumberPropertyItem(prop.GetValueFloat()));

            break;

        case PSS_Property::IEType::IE_T_EditNumberReadOnly:
            if (prop.GetValueType() == PSS_Property::IEValueType::IE_VT_Double)
                // read-only and cannot be edited
                pItem.reset(new PSS_NumberPropertyItem(prop.GetValueDouble(), true, false));
            else
            if (prop.GetValueType() == PSS_Property::IEValueType::IE_VT_Float)
                // read-only and cannot be edited
                pItem.reset(new PSS_NumberPropertyItem(prop.GetValueFloat(), true, false));

            break;

        case PSS_Property::IEType::IE_T_EditMenu:
            pItem.reset(new PSS_MenuFileDirPropertyItem(prop.GetMenu()));
            break;

        case PSS_Property::IEType::IE_T_EditMenuReadOnly:
            // read-only
            pItem.reset(new PSS_MenuFileDirPropertyItem(prop.GetMenu(), true));
            break;

        case PSS_Property::IEType::IE_T_EditFile:
            // as file is true
            pItem.reset(new PSS_MenuFileDirPropertyItem(LPCTSTR(NULL), true));
            break;

        case PSS_Property::IEType::IE_T_EditDirectory:
            // as file is false
            pItem.reset(new PSS_MenuFileDirPropertyItem(LPCTSTR(NULL), true));
            break;

        case PSS_Property::IEType::IE_T_EditExtended:
            pItem.reset(new PSS_ExtendedPropertyItem());
            break;

        case PSS_Property::IEType::IE_T_EditExtendedReadOnly:
            // read-only
            pItem.reset(new PSS_ExtendedPropertyItem(NULL, true));
            break;

        case PSS_Property::IEType::IE_T_EditDuration:
            pItem.reset(new PSS_DurationPropertyItem());
            break;

        case PSS_Property::IEType::IE_T_EditDurationReadOnly:
            // read-only and cannot be edited
            pItem.reset(new PSS_DurationPropertyItem(NULL, true, false));
            break;

        case PSS_Property::IEType::IE_T_EditDate:
            pItem.reset(new PSS_DatePropertyItem());
            break;

        case PSS_Property::IEType::IE_T_EditDateReadOnly:
            // read-only and cannot be edited
            pItem.reset(new PSS_DatePropertyItem(NULL, true, false));
            break;

        case PSS_Property::IEType::IE_T_EditTime:
            pItem.reset(new PSS_TimePropertyItem());
            break;

        case PSS_Property::IEType::IE_T_EditTimeReadOnly:
            // read-only and cannot be edited
            pItem.reset(new PSS_TimePropertyItem(NULL, true, false));
            break;

        case PSS_Property::IEType::IE_T_EditIntelli:
            pItem.reset(new PSS_IntelliEditPropertyItem());
            break;

        case PSS_Property::IEType::IE_T_EditIntelliReadOnly:
            // read-only and cannot be edited
            pItem.reset(new PSS_IntelliEditPropertyItem(NULL, true, false));
            break;

        case PSS_Property::IEType::IE_T_EditMultiline:
            pItem.reset(new PSS_MultiLineEditPropertyItem());
            break;

        case PSS_Property::IEType::IE_T_EditMultilineReadOnly:
            // read-only and cannot be edited
            pItem.reset(new PSS_MultiLineEditPropertyItem(NULL, true, false));
            break;
    }

    if (pItem.get())
    {
        // set drag&drop flag
        pItem->EnableDragNDrop(prop.IsDragNDropEnabled());

        // set the order
        pItem->SetItemOrder(prop.GetItemOrder());
        pItem->SetCategoryOrder(prop.GetCategoryOrder());
    }

    return pItem.release();
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::SetDataToPropertyItem(PSS_PropertyItem* pPropertyItem, PSS_Property& prop)
{
    switch (prop.GetType())
    {
        case PSS_Property::IEType::IE_T_EditString:
        case PSS_Property::IEType::IE_T_EditStringReadOnly:
        {
            PSS_StringPropertyItem* pStringPropItem = dynamic_cast<PSS_StringPropertyItem*>(pPropertyItem);

            if (pStringPropItem)
                pStringPropItem->SetData(prop.GetValueString());

            break;
        }

        case PSS_Property::IEType::IE_T_ComboString:
        case PSS_Property::IEType::IE_T_ComboStringReadOnly:
        {
            PSS_ListPropertyItem* pListPropItem = dynamic_cast<PSS_ListPropertyItem*>(pPropertyItem);

            if (pListPropItem)
            {
                pListPropItem->SetData(prop.GetValueString());

                // if contains a value array
                if (prop.HasValueList())
                    // add all values
                    pListPropItem->SetData(prop.GetValueArray());
            }

            break;
        }

        case PSS_Property::IEType::IE_T_EditNumber:
        case PSS_Property::IEType::IE_T_EditNumberReadOnly:
        {
            PSS_NumberPropertyItem* pNumberPropItem = dynamic_cast<PSS_NumberPropertyItem*>(pPropertyItem);

            if (pNumberPropItem)
                if (prop.GetValueType() == PSS_Property::IEValueType::IE_VT_Double)
                    pNumberPropItem->SetData(prop.GetValueDouble());
                else
                if (prop.GetValueType() == PSS_Property::IEValueType::IE_VT_Float)
                    pNumberPropItem->SetData(prop.GetValueFloat());

            break;
        }

        case PSS_Property::IEType::IE_T_EditExtended:
        case PSS_Property::IEType::IE_T_EditExtendedReadOnly:
        {
            PSS_ExtendedPropertyItem* pExtendedPropItem = dynamic_cast<PSS_ExtendedPropertyItem*>(pPropertyItem);

            if (pExtendedPropItem)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String: pExtendedPropItem->SetData(prop.GetValueString()); break;
                    case PSS_Property::IEValueType::IE_VT_Double: pExtendedPropItem->SetData(prop.GetValueDouble()); break;
                    case PSS_Property::IEValueType::IE_VT_Float:  pExtendedPropItem->SetData(prop.GetValueFloat());  break;
                }

            break;
        }

        case PSS_Property::IEType::IE_T_EditDuration:
        case PSS_Property::IEType::IE_T_EditDurationReadOnly:
        {
            PSS_DurationPropertyItem* pDurationPropItem = dynamic_cast<PSS_DurationPropertyItem*>(pPropertyItem);

            if (pDurationPropItem)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String:   pDurationPropItem->SetData(               prop.GetValueString());   break;
                    case PSS_Property::IEValueType::IE_VT_Duration: pDurationPropItem->SetData((PSS_Duration&)prop.GetValueDuration()); break;
                }

            break;
        }

        case PSS_Property::IEType::IE_T_EditDate:
        case PSS_Property::IEType::IE_T_EditDateReadOnly:
        {
            PSS_DatePropertyItem* pDatePropItem = dynamic_cast<PSS_DatePropertyItem*>(pPropertyItem);

            if (pDatePropItem)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String: pDatePropItem->SetData(           prop.GetValueString()); break;
                    case PSS_Property::IEValueType::IE_VT_Date:   pDatePropItem->SetData((PSS_Date&)prop.GetValueDate());   break;
                }

            break;
        }

        case PSS_Property::IEType::IE_T_EditTime:
        case PSS_Property::IEType::IE_T_EditTimeReadOnly:
        {
            PSS_TimePropertyItem* pTimePropItem = dynamic_cast<PSS_TimePropertyItem*>(pPropertyItem);

            if (pTimePropItem)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String:   pTimePropItem->SetData(               prop.GetValueString());   break;
                    case PSS_Property::IEValueType::IE_VT_TimeSpan: pTimePropItem->SetData((PSS_TimeSpan&)prop.GetValueTimeSpan()); break;
                }

            break;
        }

        case PSS_Property::IEType::IE_T_EditMenu:
        case PSS_Property::IEType::IE_T_EditMenuReadOnly:
        case PSS_Property::IEType::IE_T_EditFile:
        case PSS_Property::IEType::IE_T_EditDirectory:
        {
            PSS_MenuFileDirPropertyItem* pMenuFileDirPropItem = dynamic_cast<PSS_MenuFileDirPropertyItem*>(pPropertyItem);

            if (pMenuFileDirPropItem)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String: pMenuFileDirPropItem->SetData(prop.GetValueString()); break;
                    case PSS_Property::IEValueType::IE_VT_Double: pMenuFileDirPropItem->SetData(prop.GetValueDouble()); break;
                    case PSS_Property::IEValueType::IE_VT_Float:  pMenuFileDirPropItem->SetData(prop.GetValueFloat());  break;
                }

            break;
        }

        case PSS_Property::IEType::IE_T_EditIntelli:
        case PSS_Property::IEType::IE_T_EditIntelliReadOnly:
        {
            PSS_IntelliEditPropertyItem* pIntelliEditPropItem = dynamic_cast<PSS_IntelliEditPropertyItem*>(pPropertyItem);

            if (pIntelliEditPropItem)
            {
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String: pIntelliEditPropItem->SetData(      prop.GetValueString()); break;
                    case PSS_Property::IEValueType::IE_VT_Double: pIntelliEditPropItem->SetData((char)prop.GetValueDouble()); break;
                    case PSS_Property::IEValueType::IE_VT_Float:  pIntelliEditPropItem->SetData((char)prop.GetValueFloat());  break;
                }

                // if contains a value array
                if (prop.HasValueList())
                    // add all values
                    pIntelliEditPropItem->SetData(prop.GetValueArray());
            }

            break;
        }

        case PSS_Property::IEType::IE_T_EditMultiline:
        case PSS_Property::IEType::IE_T_EditMultilineReadOnly:
        {
            PSS_MultiLineEditPropertyItem* pMultilineEditPropItem = dynamic_cast<PSS_MultiLineEditPropertyItem*>(pPropertyItem);

            if (pMultilineEditPropItem)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String: pMultilineEditPropItem->SetData(      prop.GetValueString()); break;
                    case PSS_Property::IEValueType::IE_VT_Double: pMultilineEditPropItem->SetData((char)prop.GetValueDouble()); break;
                    case PSS_Property::IEValueType::IE_VT_Float:  pMultilineEditPropItem->SetData((char)prop.GetValueFloat());  break;
                }

            break;
        }
    }

    // set the order
    pPropertyItem->SetItemOrder(prop.GetItemOrder());
    pPropertyItem->SetCategoryOrder(prop.GetCategoryOrder());
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::SetItemDataToProperty(PSS_PropertyItem* pPropertyItem, PSS_Property& prop)
{
    // assign the values
    switch (prop.GetType())
    {
        case PSS_Property::IEType::IE_T_EditString:
        case PSS_Property::IEType::IE_T_EditStringReadOnly:
        {
            PSS_StringPropertyItem* pStringPropItem = dynamic_cast<PSS_StringPropertyItem*>(pPropertyItem);

            if (pStringPropItem)
                prop.SetValueString(pStringPropItem->GetData());

            break;
        }

        case PSS_Property::IEType::IE_T_ComboString:
        case PSS_Property::IEType::IE_T_ComboStringReadOnly:
        {
            PSS_ListPropertyItem* pListPropItem = dynamic_cast<PSS_ListPropertyItem*>(pPropertyItem);

            if (pListPropItem)
                prop.SetValueString(pListPropItem->GetData());

            break;
        }

        case PSS_Property::IEType::IE_T_EditNumber:
        case PSS_Property::IEType::IE_T_EditNumberReadOnly:
        {
            PSS_NumberPropertyItem* pNumberPropItem = dynamic_cast<PSS_NumberPropertyItem*>(pPropertyItem);

            if (pNumberPropItem)
                if (prop.GetValueType() == PSS_Property::IEValueType::IE_VT_Double)
                    prop.SetValueDouble(pNumberPropItem->GetDataDouble());
                else
                if (prop.GetValueType() == PSS_Property::IEValueType::IE_VT_Float)
                    prop.SetValueFloat(pNumberPropItem->GetDataFloat());

            break;
        }

        case PSS_Property::IEType::IE_T_EditExtended:
        case PSS_Property::IEType::IE_T_EditExtendedReadOnly:
        {
            PSS_ExtendedPropertyItem* pExtendedPropItem = dynamic_cast<PSS_ExtendedPropertyItem*>(pPropertyItem);

            if (pExtendedPropItem)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String: prop.SetValueString(pExtendedPropItem->GetData());       break;
                    case PSS_Property::IEValueType::IE_VT_Double: prop.SetValueDouble(pExtendedPropItem->GetDataDouble()); break;
                    case PSS_Property::IEValueType::IE_VT_Float:  prop.SetValueFloat (pExtendedPropItem->GetDataFloat());  break;
                }

            break;
        }

        case PSS_Property::IEType::IE_T_EditDuration:
        case PSS_Property::IEType::IE_T_EditDurationReadOnly:
        {
            PSS_DurationPropertyItem* pDurationPropItem = dynamic_cast<PSS_DurationPropertyItem*>(pPropertyItem);

            if (pDurationPropItem)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String:   prop.SetValueString  (pDurationPropItem->GetData());         break;
                    case PSS_Property::IEValueType::IE_VT_Duration: prop.SetValueDuration(pDurationPropItem->GetDataDuration()); break;
                }

            break;
        }

        case PSS_Property::IEType::IE_T_EditDate:
        case PSS_Property::IEType::IE_T_EditDateReadOnly:
        {
            PSS_DatePropertyItem* pDatePropItem = dynamic_cast<PSS_DatePropertyItem*>(pPropertyItem);

            if (pDatePropItem)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String: prop.SetValueString(pDatePropItem->GetData());     break;
                    case PSS_Property::IEValueType::IE_VT_Date:   prop.SetValueDate  (pDatePropItem->GetDataDate()); break;
                }

            break;
        }

        case PSS_Property::IEType::IE_T_EditTime:
        case PSS_Property::IEType::IE_T_EditTimeReadOnly:
        {
            PSS_TimePropertyItem* pTimePropItem = dynamic_cast<PSS_TimePropertyItem*>(pPropertyItem);

            if (pTimePropItem)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String:   prop.SetValueString  (pTimePropItem->GetData());     break;
                    case PSS_Property::IEValueType::IE_VT_TimeSpan: prop.SetValueTimeSpan(pTimePropItem->GetDataTime()); break;
                }

            break;
        }

        case PSS_Property::IEType::IE_T_EditMenu:
        case PSS_Property::IEType::IE_T_EditMenuReadOnly:
        case PSS_Property::IEType::IE_T_EditFile:
        case PSS_Property::IEType::IE_T_EditDirectory:
        {
            PSS_MenuFileDirPropertyItem* pMenuFileDirProp = dynamic_cast<PSS_MenuFileDirPropertyItem*>(pPropertyItem);

            if (pMenuFileDirProp)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String: prop.SetValueString(pMenuFileDirProp->GetData());       break;
                    case PSS_Property::IEValueType::IE_VT_Double: prop.SetValueDouble(pMenuFileDirProp->GetDataDouble()); break;
                    case PSS_Property::IEValueType::IE_VT_Float:  prop.SetValueFloat (pMenuFileDirProp->GetDataFloat());  break;
                }

            break;
        }

        case PSS_Property::IEType::IE_T_EditIntelli:
        case PSS_Property::IEType::IE_T_EditIntelliReadOnly:
        {
            PSS_IntelliEditPropertyItem* pIntelliEditPropItem = dynamic_cast<PSS_IntelliEditPropertyItem*>(pPropertyItem);

            if (pIntelliEditPropItem)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String: prop.SetValueString(pIntelliEditPropItem->GetData());       break;
                    case PSS_Property::IEValueType::IE_VT_Double: prop.SetValueDouble(pIntelliEditPropItem->GetDataDouble()); break;
                    case PSS_Property::IEValueType::IE_VT_Float:  prop.SetValueFloat (pIntelliEditPropItem->GetDataFloat());  break;
                }

            break;
        }

        case PSS_Property::IEType::IE_T_EditMultiline:
        case PSS_Property::IEType::IE_T_EditMultilineReadOnly:
        {
            PSS_MultiLineEditPropertyItem* pMultilineEditPropItem = dynamic_cast<PSS_MultiLineEditPropertyItem*>(pPropertyItem);

            if (pMultilineEditPropItem)
                switch (prop.GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_String: prop.SetValueString(pMultilineEditPropItem->GetData());       break;
                    case PSS_Property::IEValueType::IE_VT_Double: prop.SetValueDouble(pMultilineEditPropItem->GetDataDouble()); break;
                    case PSS_Property::IEValueType::IE_VT_Float:  prop.SetValueFloat (pMultilineEditPropItem->GetDataFloat());  break;
                }

            break;
        }
    }

    if (pPropertyItem)
    {
        // assign has changed flag
        prop.SetHasChanged(pPropertyItem->GetHasChanged());

        // set the order
        prop.SetItemOrder(pPropertyItem->GetItemOrder());
        prop.SetCategoryOrder(pPropertyItem->GetCategoryOrder());
    }
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::FreePropertySet()
{
    PSS_Properties::IPropertyIterator it(&m_PropSet);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    m_PropSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::DeleteUnusedTab()
{
    IItemCategoryIterator it(&m_PropertyItemTabSet);

    // iterate through all items
    for (PSS_PropertyItemCategory* pItemCat = it.GetFirst(); pItemCat;)
        if (!ExistInPropSet(pItemCat->GetName()))
        {
            delete pItemCat;

            it.Remove();

            // after a remove, get the current element
            pItemCat = it.Get();
        }
        else
            // get the next element
            pItemCat = it.GetNext();
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::DeleteAllTabs()
{
    IItemCategoryIterator it(&m_PropertyItemTabSet);

    // iterate through all items
    for (PSS_PropertyItemCategory* pItemCat = it.GetFirst(); pItemCat; pItemCat = it.GetNext())
        delete pItemCat;

    m_PropertyItemTabSet.RemoveAll();
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::ExistInPropSet(LPCTSTR pTabName)
{
    PSS_Properties::IPropertyIterator it(&m_PropSet);

    // iterate through the data and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategory() == pTabName)
            return true;

    return false;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::DeletePropertyState()
{
    IPropertyStateIterator it(&m_PropertyState);

    for (IPropertyState* pPropState = it.GetFirst(); pPropState; pPropState = it.GetNext())
        delete pPropState;

    m_PropertyState.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::SetInitialCategoryOrder()
{
    IItemCategoryIterator it(&m_PropertyItemTabSet);
    int                   categoryOrder = 0;

    // iterate through the categories and set category order
    for (PSS_PropertyItemCategory* pItemCat = it.GetFirst(); pItemCat; pItemCat = it.GetNext())
    {
        pItemCat->SetCategoryOrder(categoryOrder);
        ++categoryOrder;
    }
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::ReorderCategory()
{
    IItemCategoryIterator it(&m_PropertyItemTabSet);
    bool                  orderSet = false;

    // iterate through all categories and check if category order is correctly set
    for (PSS_PropertyItemCategory* pItemCat = it.GetFirst(); pItemCat; pItemCat = it.GetNext())
    {
        // order is not set, reassign the initial order. Cannot be done in another, since some objects may have
        // more attributes event if they are in the same object group
        if (pItemCat->GetCategoryOrder() == -1)
        {
            if (orderSet)
            {
                SetInitialCategoryOrder();

                // save the new order
                SaveAllCategoryOrders();
            }

            return;
        }

        orderSet = true;
    }

    IItemCategorySet tempItemTabSet;

    // transfert item to temporary set
    for (PSS_PropertyItemCategory* pItemCat = it.GetFirst(); pItemCat; pItemCat = it.GetNext())
        tempItemTabSet.Add(pItemCat);

    // remove all elements from the initial set, just the pointer, not the element itself
    m_PropertyItemTabSet.RemoveAll();

    // insert elements in order
    IItemCategoryIterator itTemp(&tempItemTabSet);

    for (PSS_PropertyItemCategory* pSrcItemCat = itTemp.GetFirst(); pSrcItemCat; pSrcItemCat = itTemp.GetNext())
    {
        // insert in order
        bool inserted = false;
        int  index    = 0;

        for (PSS_PropertyItemCategory* pDstItemCat = it.GetFirst(); pDstItemCat; pDstItemCat = it.GetNext(), ++index)
            if (pSrcItemCat->GetCategoryOrder() < pDstItemCat->GetCategoryOrder())
            {
                inserted = true;

                m_PropertyItemTabSet.InsertAt(index, pSrcItemCat);
                break;
            }

        // if not inserted, then add it to the end
        if (!inserted)
            m_PropertyItemTabSet.Add(pSrcItemCat);
    }

    // remove all elements from the temporary set
    tempItemTabSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::SaveAllCategoryOrders()
{
    IItemCategoryIterator it(&m_PropertyItemTabSet);

    // iterate through the categories and set category order to the corresponding object state
    for (PSS_PropertyItemCategory* pItemCat = it.GetFirst(); pItemCat; pItemCat = it.GetNext())
        SavePropertyState(pItemCat);
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::OnDropCategory(PSS_PropertyItemCategory* pSrcCategoryItem,
                                             PSS_PropertyItem*         pDstPropertyItem,
                                             bool                      top2Down)
{
    if (!pDstPropertyItem || !pSrcCategoryItem)
        return false;

    PSS_PropertyItemCategory* pDstCategoryItem = dynamic_cast<PSS_PropertyItemCategory*>(pDstPropertyItem);

    // if the destination isn't a category
    if (!pDstCategoryItem)
        // locate the category of the property item
        pDstCategoryItem = GetTab(pDstPropertyItem);

    if (!pDstCategoryItem)
        return false;

    // change the category order
    if (pSrcCategoryItem->GetCategoryOrder() == -1 || pDstCategoryItem->GetCategoryOrder() == -1)
        SetInitialCategoryOrder();

    // swap the two category order
    const int                 srcCategoryOrder = pSrcCategoryItem->GetCategoryOrder();
    const int                 dstCategoryOrder = pDstCategoryItem->GetCategoryOrder();
    PSS_PropertyItemCategory* pFoundSrc        = NULL;

    IItemCategoryIterator  it(&m_PropertyItemTabSet);

    for (PSS_PropertyItemCategory* pItemCat = (top2Down ? it.GetFirst() : it.GetLast());
         pItemCat;
         pItemCat = (top2Down ? it.GetNext() : it.GetPrev()))
        // if the source property was found, break the loop and set the flag
        if (pItemCat == pSrcCategoryItem)
        {
            pFoundSrc = pItemCat;
            break;
        }

    // the source was reached?
    if (!pFoundSrc)
        return false;

    int                       previousCategoryOrder = pFoundSrc->GetCategoryOrder();
    PSS_PropertyItemCategory* pFoundDst             = NULL;

    // from the source until the destination, copy the element to the previous
    for (PSS_PropertyItemCategory* pItemCat = (top2Down ? it.GetNext() : it.GetPrev());
         pItemCat;
         pItemCat = (top2Down ? it.GetNext() : it.GetPrev()))
    {
        #ifdef _DEBUG
            CString str;
            str.Format(_T(" Before Item = %s Order = %d   ---  "),
                (const char*)pItemCat->GetName(), pItemCat->GetCategoryOrder());

            TRACE(str);
        #endif

        const int order = previousCategoryOrder;

        // save the previous category order
        previousCategoryOrder = pItemCat->GetCategoryOrder();

        // copy the current category order value to the previous element
        pItemCat->SetCategoryOrder(order);

        if (pItemCat == pDstCategoryItem)
        {
            pFoundDst = pItemCat;
            break;
        }

        #ifdef _DEBUG
            str.Format(_T(" After Item = %s Order = %d\n "),
                (const char*)pItemCat->GetName(), pItemCat->GetCategoryOrder());

            TRACE(str);
        #endif
    }

    // the destination was reached?
    if (!pFoundDst)
        return false;

    // copy the saved category order value of the droped item
    pSrcCategoryItem->SetCategoryOrder(dstCategoryOrder);

    // reorder the category
    ReorderCategory();

    // save the new order
    SaveAllCategoryOrders();

    return true;
}
//---------------------------------------------------------------------------
