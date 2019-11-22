// ZBPropertyManager.cpp : implementation file

#include "stdafx.h"
#include "ZBPropertyManager.h"

// processsoft
#include "zBaseLib\PSS_SystemOption.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "ZCPropertyListCtrl.h"
#include "ZBPropertyItems.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// constant definition
const CString _PropertyItemManagerSectionName = _T("_PropertyItemManagerSaveState");
const CString _PropertyItemStateEntityName = _T("_PropertyItemState");

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemManager
void ZBPropertyItemManager::Empty()
{
    FreePropertySet();
    m_pCurrentData = NULL;
}

void ZBPropertyItemManager::SetPropertyListCtrl(ZCPropertyListCtrl* pCtrl)
{
    m_pWndPropertyListCtrl = pCtrl;
}

void ZBPropertyItemManager::FreePropertySet()
{
    ZBPropertyIterator i(&m_PropSet);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        delete pProp;
    }

    m_PropSet.RemoveAll();
}

bool ZBPropertyItemManager::UpdateControlData(const ZIProperties* pData)
{
    if (!pData)
    {
        return true;
    }

    // First, delete all tabs
    DeleteAllTabs();

    // Then all properties
    FreePropertySet();

    // Retrieve the property set from object
    const_cast<ZIProperties*>(pData)->FillProperties(m_PropSet);

    bool RetValue = UpdateControlData();

    m_pCurrentData = const_cast<ZIProperties*>(pData);

    return RetValue;
}

bool ZBPropertyItemManager::UpdateControlData(ZBPropertySet& PropSet)
{
    // First, delete all tabs
    DeleteAllTabs();

    // Then all properties
    FreePropertySet();

    // Duplicate the set
    ZBPropertyIterator i(&PropSet);

    for (ZBProperty* pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        m_PropSet.Add(pProp->Dup());
    }

    bool RetValue = UpdateControlData();

    m_pCurrentData = NULL;

    return RetValue;
}

bool ZBPropertyItemManager::UpdateControlData()
{
    ZBPropertyIterator i(&m_PropSet);

    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // Check the display type first
        switch (m_DisplayType)
        {
            case AllProperties:
            {
                break;
            }

            case StaticProperties:
            {
                if (pProp->IsDynamic())
                {
                    continue;
                }

                break;
            }

            case DynamicProperties:
            {
                if (!pProp->IsDynamic())
                {
                    continue;
                }

                break;
            }
        }

        ZBPropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
        {
            // First, create the category
            pTab = AddNewTab(pProp->GetCategory());

            // Set the category ID
            pTab->SetPropertyID(pProp->GetCategoryID());
            pTab->SetEnabled(true);

            // By default, sets the children visible
            pTab->SetChildrenVisible(true);

            // And set the information for the category item
            SetPropertyStateToProperty(pTab);
        }

        // Check if already exists
        ZBPropertyItem* pPropertyItem = pTab->GetPropertyItem(pProp->GetItemID());

        // Then add property item
        if (!pPropertyItem)
        {
            pPropertyItem = CreatePropertyItem(*pProp);

            if (!pPropertyItem)
            {
                return false;
            }

            pTab->AddPropertyItem(pPropertyItem);
        }

        // Now sets the appropriate initial data to the property item
        SetDataToPropertyItem(pPropertyItem, *pProp);

        // Sets the propertyID for further identification
        pPropertyItem->SetPropertyID(pProp->GetItemID());
        pPropertyItem->SetEnabled(pProp->GetEnable());
        pPropertyItem->SetName(pProp->GetLabel());
        pPropertyItem->SetStringFormat(pProp->GetStringFormat());
        pPropertyItem->SetSaveState(pProp->GetSaveState());
        pPropertyItem->SetSaveStatePerProperty(pProp->GetSaveStatePerProperty());

        if (pProp->GetSaveState())
        {
            // Set information from the property state to the property
            SetPropertyStateToProperty(pPropertyItem);
        }
    }

    // Finally check if unused tabs stay and delete them
    DeleteUnusedTab();

    // ReOrder the categories
    ReOrderCategory();

    return true;
}

bool ZBPropertyItemManager::UpdatePropertyData(ZBPropertyItem* pPropertyItem /*= NULL*/)
{
    ZBProperty* pProp;

    // If no property item specified, update all
    if (!pPropertyItem)
    {
        // Now run through the list of data and fill the property set
        ZBPropertyIterator i(&m_PropSet);

        for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        {
            // First, find the category
            ZBPropertyItemCategory* pTab = TabExist(pProp->GetCategory());

            if (!pTab)
            {
                continue;
            }

            // Check if already exists
            ZBPropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

            if (!pPropItem)
            {
                continue;
            }

            // Sets the appropriate data to the property item
            SetItemDataToProperty(pPropItem, *pProp);

            // Set the enable flag and the stringformat type
            pProp->SetEnable(pPropItem->GetEnabled());
            pProp->SetStringFormat(pPropItem->GetStringFormat());
        }

        // Send the property set to the object
        return (m_pCurrentData) ? m_pCurrentData->SaveProperties(m_PropSet) : true;
    }

    // Otherwise, one value is specified and request only one save
    // Now run through the list of data and fill the property set
    ZBPropertyIterator i(&m_PropSet);

    bool Found = false;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // First, find the category
        ZBPropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Check if already exists
        ZBPropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

        if (!pPropItem || pPropItem != pPropertyItem)
        {
            continue;
        }

        // Sets the appropriate data to the property item
        SetItemDataToProperty(pPropItem, *pProp);

        Found = true;

        break;
    }

    if (pProp && Found && m_pCurrentData)
    {
        // Only if value has changed
        if (pProp->GetHasChanged())
        {
            // Send the property to the object
            return m_pCurrentData->SaveProperty(*pProp);
        }
        else
        {
            return true;
        }
    }

    // Otherwise, not found
    return false;
}

bool ZBPropertyItemManager::CheckCurrentPropertyData(ZBPropertyItem* pPropertyItem, CString& ProposedValue)
{
    // If no item specified, assume the data are entered correctly
    if (!pPropertyItem)
    {
        return true;
    }

    // Otherwise, one value is specified and request only one save
    // Now run through the list of data and fill the property set
    ZBPropertyIterator i(&m_PropSet);

    ZBProperty* pProp;

    bool Found = false;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // First, find the category
        ZBPropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Check if already exists
        ZBPropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

        if (!pPropItem || pPropItem != pPropertyItem)
        {
            continue;
        }

        // Sets the appropriate data to the property item
        SetItemDataToProperty(pPropItem, *pProp);

        Found = true;

        break;
    }

    if (pProp && Found && m_pCurrentData)
    {
        // Send the property to the object
        return m_pCurrentData->CheckPropertyValue(*pProp, ProposedValue, m_PropSet);
    }

    // Otherwise, not found
    return false;
}

bool ZBPropertyItemManager::ProcessExtendedCurrentPropertyData(ZBPropertyItem*    pPropertyItem,
                                                               CString&        ProposedValue,
                                                               bool&            Refresh)
{
    // If no item specified, assume the data are entered correctly
    if (!pPropertyItem)
    {
        return true;
    }

    // Otherwise, one value is specified and request only one save
    // Now run through the list of data and fill the property set
    ZBPropertyIterator i(&m_PropSet);

    ZBProperty* pProp;

    bool Found = false;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // First, find the category
        ZBPropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Check if already exists
        ZBPropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

        if (!pPropItem || pPropItem != pPropertyItem)
        {
            continue;
        }

        // Sets the appropriate data to the property item
        SetItemDataToProperty(pPropItem, *pProp);

        Found = true;

        break;
    }

    if (pProp && Found && m_pCurrentData)
    {
        // Send the property to the object
        if (m_pCurrentData->ProcessExtendedInput(*pProp, ProposedValue, m_PropSet, Refresh))
        {
            ApplyPropertyChanges();
            return true;
        }
    }

    // Otherwise, not found
    return false;
}

bool ZBPropertyItemManager::ProcessMenuCommandCurrentPropertyData(int                MenuCommand,
                                                                  ZBPropertyItem*    pPropertyItem,
                                                                  CString&            ProposedValue,
                                                                  bool&            Refresh)
{
    // If no item specified, assume the data are entered correctly
    if (!pPropertyItem)
    {
        return true;
    }

    // Otherwise, one value is specified and request only one save
    // Now run through the list of data and fill the property set
    ZBPropertyIterator i(&m_PropSet);

    ZBProperty* pProp;

    bool Found = false;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // First, find the category
        ZBPropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Check if already exists
        ZBPropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

        if (!pPropItem || pPropItem != pPropertyItem)
        {
            continue;
        }

        // Sets the appropriate data to the property item
        SetItemDataToProperty(pPropItem, *pProp);

        Found = true;

        break;
    }

    if (pProp && Found && m_pCurrentData)
    {
        // Send the property to the object
        if (m_pCurrentData->ProcessMenuCommand(MenuCommand, *pProp, ProposedValue, m_PropSet, Refresh))
        {
            ApplyPropertyChanges();
            return true;
        }
    }

    // Otherwise, not found
    return false;
}

bool ZBPropertyItemManager::ApplyPropertyChanges()
{
    ZBPropertyIterator i(&m_PropSet);

    ZBProperty* pProp;

    bool Updated = false;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // First, get the category
        ZBPropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Then, get the right property item
        ZBPropertyItem* pPropertyItem = pTab->GetPropertyItem(pProp->GetItemID());

        // If not exits, continue
        if (!pPropertyItem)
        {
            continue;
        }

        // Sets the value, enable and name
        SetDataToPropertyItem(pPropertyItem, *pProp);

        pPropertyItem->SetEnabled(pProp->GetEnable());
        pPropertyItem->SetName(pProp->GetLabel());
        pPropertyItem->SetStringFormat(pProp->GetStringFormat());

        // Set the updated flag
        Updated = true;
    }

    if (Updated)
    {
        m_pWndPropertyListCtrl->RedrawAll();
    }

    return true;
}

ZBPropertyItem* ZBPropertyItemManager::CreatePropertyItem(ZBProperty& Prop)
{
    ZBPropertyItem* pItem = NULL;

    switch (Prop.GetPTType())
    {
        case ZBProperty::PT_EDIT_STRING:
        {
            pItem = new ZBPropertyItemString;
            break;
        }

        case ZBProperty::PT_EDIT_STRING_READONLY:
        {
            // Read-only and cannot be edited
            pItem = new ZBPropertyItemString(NULL, true, false);
            break;
        }

        case ZBProperty::PT_COMBO_STRING:
        {
            pItem = new ZBPropertyItemList;
            break;
        }

        case ZBProperty::PT_COMBO_STRING_READONLY:
        {
            // Read-only
            pItem = new ZBPropertyItemList(NULL, true);
            break;
        }

        case ZBProperty::PT_EDIT_NUMBER:
        {
            if (Prop.GetPTValueType() == ZBProperty::PT_DOUBLE)
            {
                pItem = new ZBPropertyItemNumber(Prop.GetValueDouble());
            }
            else
            {
                if (Prop.GetPTValueType() == ZBProperty::PT_FLOAT)
                {
                    pItem = new ZBPropertyItemNumber(Prop.GetValueFloat());
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_NUMBER_READONLY:
        {
            if (Prop.GetPTValueType() == ZBProperty::PT_DOUBLE)
            {
                // Read-only and cannot be edited
                pItem = new ZBPropertyItemNumber(Prop.GetValueDouble(), true, false);
            }
            else
            {
                if (Prop.GetPTValueType() == ZBProperty::PT_FLOAT)
                {
                    // Read-only and cannot be edited
                    pItem = new ZBPropertyItemNumber(Prop.GetValueFloat(), true, false);
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_MENU:
        {
            pItem = new ZBPropertyItemMenuFileDir(Prop.GetMenu());
            break;
        }

        case ZBProperty::PT_EDIT_MENU_READONLY:
        {
            // Read-only
            pItem = new ZBPropertyItemMenuFileDir(Prop.GetMenu(), true);
            break;
        }

        case ZBProperty::PT_EDIT_FILE:
        {
            // As file is true
            pItem = new ZBPropertyItemMenuFileDir((LPCTSTR)NULL, true);
            break;
        }

        case ZBProperty::PT_EDIT_DIRECTORY:
        {
            // As file is false
            pItem = new ZBPropertyItemMenuFileDir((LPCTSTR)NULL, true);
            break;
        }

        case ZBProperty::PT_EDIT_EXTENDED:
        {
            pItem = new ZBPropertyItemExtended;
            break;
        }

        case ZBProperty::PT_EDIT_EXTENDED_READONLY:
        {
            // Read-only
            pItem = new ZBPropertyItemExtended(NULL, true);
            break;
        }

        case ZBProperty::PT_EDIT_DURATION:
        {
            pItem = new ZBPropertyItemDuration;
            break;
        }

        case ZBProperty::PT_EDIT_DURATION_READONLY:
        {
            // Read-only and cannot be edited
            pItem = new ZBPropertyItemDuration(NULL, true, false);
            break;
        }

        case ZBProperty::PT_EDIT_DATE:
        {
            pItem = new ZBPropertyItemDate;
            break;
        }

        case ZBProperty::PT_EDIT_DATE_READONLY:
        {
            // Read-only and cannot be edited
            pItem = new ZBPropertyItemDate(NULL, true, false);
            break;
        }

        //RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
        case ZBProperty::PT_EDIT_TIME:
        {
            pItem = new ZBPropertyItemTime;
            break;
        }

        case ZBProperty::PT_EDIT_TIME_READONLY:
        {
            // Read-only and cannot be edited
            pItem = new ZBPropertyItemTime(NULL, true, false);
            break;
        }

        case ZBProperty::PT_EDIT_INTELI:
        {
            pItem = new ZBPropertyItemIntelliEdit;
            break;
        }

        case ZBProperty::PT_EDIT_INTELI_READONLY:
        {
            // Read-only and cannot be edited
            pItem = new ZBPropertyItemIntelliEdit(NULL, true, false);
            break;
        }

        case ZBProperty::PT_EDIT_MULTILINE:
        {
            pItem = new ZBPropertyItemMultiLineEdit;
            break;
        }

        case ZBProperty::PT_EDIT_MULTILINE_READONLY:
        {
            // Read-only and cannot be edited
            pItem = new ZBPropertyItemMultiLineEdit(NULL, true, false);
            break;
        }
    }

    if (pItem)
    {
        // Sets drag&drop flag
        pItem->EnableDragNDrop(Prop.IsEnabledDragNDrop());

        // Sets the order
        pItem->SetItemOrder(Prop.GetItemOrder());
        pItem->SetCategoryOrder(Prop.GetCategoryOrder());
    }

    return pItem;
}

void ZBPropertyItemManager::SetDataToPropertyItem(ZBPropertyItem* pPropertyItem, ZBProperty& Prop)
{
    switch (Prop.GetPTType())
    {
        case ZBProperty::PT_EDIT_STRING:
        case ZBProperty::PT_EDIT_STRING_READONLY:
        {
            reinterpret_cast<ZBPropertyItemString*>(pPropertyItem)->SetData(Prop.GetValueString());
            break;
        }

        case ZBProperty::PT_COMBO_STRING:
        case ZBProperty::PT_COMBO_STRING_READONLY:
        {
            reinterpret_cast<ZBPropertyItemList*>(pPropertyItem)->SetData(Prop.GetValueString());

            // If contains value array
            if (Prop.HasValueList())
            {
                // Add all values
                reinterpret_cast<ZBPropertyItemList*>(pPropertyItem)->SetData(Prop.GetArrayOfValues());
            }

            break;
        }

        case ZBProperty::PT_EDIT_NUMBER:
        case ZBProperty::PT_EDIT_NUMBER_READONLY:
        {
            if (Prop.GetPTValueType() == ZBProperty::PT_DOUBLE)
            {
                reinterpret_cast<ZBPropertyItemNumber*>(pPropertyItem)->SetData(Prop.GetValueDouble());
            }
            else
            {
                if (Prop.GetPTValueType() == ZBProperty::PT_FLOAT)
                {
                    reinterpret_cast<ZBPropertyItemNumber*>(pPropertyItem)->SetData(Prop.GetValueFloat());
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_EXTENDED:
        case ZBProperty::PT_EDIT_EXTENDED_READONLY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    reinterpret_cast<ZBPropertyItemExtended*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    reinterpret_cast<ZBPropertyItemExtended*>(pPropertyItem)->SetData(Prop.GetValueDouble());
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    reinterpret_cast<ZBPropertyItemExtended*>(pPropertyItem)->SetData(Prop.GetValueFloat());
                    break;
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_DURATION:
        case ZBProperty::PT_EDIT_DURATION_READONLY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    reinterpret_cast<ZBPropertyItemDuration*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case ZBProperty::PT_DURATION:
                {
                    // JMR-MODIF - Le 2 août 2005 - Conversion explicite permet de corriger bug sur attributs dynamiques.
                    reinterpret_cast<ZBPropertyItemDuration*>(pPropertyItem)->SetData((PSS_Duration&)Prop.GetValueDuration());
                    break;
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_DATE:
        case ZBProperty::PT_EDIT_DATE_READONLY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    reinterpret_cast<ZBPropertyItemDate*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case ZBProperty::PT_DATE:
                {
                    // JMR-MODIF - Le 2 août 2005 - Conversion explicite permet de corriger bug sur attributs dynamiques.
                    reinterpret_cast<ZBPropertyItemDate*>(pPropertyItem)->SetData((PSS_Date&)Prop.GetValueDate());
                    break;
                }
            }

            break;
        }

        // RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
        case ZBProperty::PT_EDIT_TIME:
        case ZBProperty::PT_EDIT_TIME_READONLY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    reinterpret_cast<ZBPropertyItemTime*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case ZBProperty::PT_TIMESPAN:
                {
                    reinterpret_cast<ZBPropertyItemTime*>(pPropertyItem)->SetData((PSS_TimeSpan&)Prop.GetValueTimeSpan());
                    break;
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_MENU:
        case ZBProperty::PT_EDIT_MENU_READONLY:
        case ZBProperty::PT_EDIT_FILE:
        case ZBProperty::PT_EDIT_DIRECTORY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    reinterpret_cast<ZBPropertyItemMenuFileDir*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    reinterpret_cast<ZBPropertyItemMenuFileDir*>(pPropertyItem)->SetData(Prop.GetValueDouble());
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    reinterpret_cast<ZBPropertyItemMenuFileDir*>(pPropertyItem)->SetData(Prop.GetValueFloat());
                    break;
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_INTELI:
        case ZBProperty::PT_EDIT_INTELI_READONLY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    reinterpret_cast<ZBPropertyItemIntelliEdit*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    reinterpret_cast<ZBPropertyItemIntelliEdit*>(pPropertyItem)->SetData((char)Prop.GetValueDouble());
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    reinterpret_cast<ZBPropertyItemIntelliEdit*>(pPropertyItem)->SetData((char)Prop.GetValueFloat());
                    break;
                }
            }

            // If contains value array
            if (Prop.HasValueList())
            {
                // Add all values
                reinterpret_cast<ZBPropertyItemIntelliEdit*>(pPropertyItem)->SetData(Prop.GetArrayOfValues());
            }

            break;
        }

        case ZBProperty::PT_EDIT_MULTILINE:
        case ZBProperty::PT_EDIT_MULTILINE_READONLY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    reinterpret_cast<ZBPropertyItemMultiLineEdit*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    reinterpret_cast<ZBPropertyItemMultiLineEdit*>(pPropertyItem)->SetData((char)Prop.GetValueDouble());
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    reinterpret_cast<ZBPropertyItemMultiLineEdit*>(pPropertyItem)->SetData((char)Prop.GetValueFloat());
                    break;
                }
            }

            break;
        }
    }

    // Sets the order
    pPropertyItem->SetItemOrder(Prop.GetItemOrder());
    pPropertyItem->SetCategoryOrder(Prop.GetCategoryOrder());
}

void ZBPropertyItemManager::SetItemDataToProperty(ZBPropertyItem* pPropertyItem, ZBProperty& Prop)
{
    // Assign the right values
    switch (Prop.GetPTType())
    {
        case ZBProperty::PT_EDIT_STRING:
        case ZBProperty::PT_EDIT_STRING_READONLY:
        {
            Prop.SetValueString(reinterpret_cast<ZBPropertyItemString*>(pPropertyItem)->GetData());
            break;
        }

        case ZBProperty::PT_COMBO_STRING:
        case ZBProperty::PT_COMBO_STRING_READONLY:
        {
            Prop.SetValueString(reinterpret_cast<ZBPropertyItemList*>(pPropertyItem)->GetData());
            break;
        }

        case ZBProperty::PT_EDIT_NUMBER:
        case ZBProperty::PT_EDIT_NUMBER_READONLY:
        {
            if (Prop.GetPTValueType() == ZBProperty::PT_DOUBLE)
            {
                Prop.SetValueDouble(reinterpret_cast<ZBPropertyItemNumber*>(pPropertyItem)->GetDataDouble());
            }
            else
            {
                if (Prop.GetPTValueType() == ZBProperty::PT_FLOAT)
                {
                    Prop.SetValueFloat(reinterpret_cast<ZBPropertyItemNumber*>(pPropertyItem)->GetDataFloat());
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_EXTENDED:
        case ZBProperty::PT_EDIT_EXTENDED_READONLY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    Prop.SetValueString(reinterpret_cast<ZBPropertyItemExtended*>(pPropertyItem)->GetData());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    Prop.SetValueDouble(reinterpret_cast<ZBPropertyItemExtended*>(pPropertyItem)->GetDataDouble());
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    Prop.SetValueFloat(reinterpret_cast<ZBPropertyItemExtended*>(pPropertyItem)->GetDataFloat());
                    break;
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_DURATION:
        case ZBProperty::PT_EDIT_DURATION_READONLY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    Prop.SetValueString(reinterpret_cast<ZBPropertyItemDuration*>(pPropertyItem)->GetData());
                    break;
                }

                case ZBProperty::PT_DURATION:
                {
                    Prop.SetValueDuration(reinterpret_cast<ZBPropertyItemDuration*>(pPropertyItem)->GetDataDuration());
                    break;
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_DATE:
        case ZBProperty::PT_EDIT_DATE_READONLY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    Prop.SetValueString(reinterpret_cast<ZBPropertyItemDate*>(pPropertyItem)->GetData());
                    break;
                }

                case ZBProperty::PT_DATE:
                {
                    Prop.SetValueDate(reinterpret_cast<ZBPropertyItemDate*>(pPropertyItem)->GetDataDate());
                    break;
                }
            }

            break;
        }
        //RS-MODIF 08.08.2005: correction attribut dynamique de temps n'était pas géré
        case ZBProperty::PT_EDIT_TIME:
        case ZBProperty::PT_EDIT_TIME_READONLY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    Prop.SetValueString(reinterpret_cast<ZBPropertyItemTime*>(pPropertyItem)->GetData());
                    break;
                }

                case ZBProperty::PT_TIMESPAN:
                {
                    Prop.SetValueTimeSpan(reinterpret_cast<ZBPropertyItemTime*>(pPropertyItem)->GetDataTime());
                    break;
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_MENU:
        case ZBProperty::PT_EDIT_MENU_READONLY:
        case ZBProperty::PT_EDIT_FILE:
        case ZBProperty::PT_EDIT_DIRECTORY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    Prop.SetValueString(reinterpret_cast<ZBPropertyItemMenuFileDir*>(pPropertyItem)->GetData());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    Prop.SetValueDouble(reinterpret_cast<ZBPropertyItemMenuFileDir*>(pPropertyItem)->GetDataDouble());
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    Prop.SetValueFloat(reinterpret_cast<ZBPropertyItemMenuFileDir*>(pPropertyItem)->GetDataFloat());
                    break;
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_INTELI:
        case ZBProperty::PT_EDIT_INTELI_READONLY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    Prop.SetValueString(reinterpret_cast<ZBPropertyItemIntelliEdit*>(pPropertyItem)->GetData());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    Prop.SetValueDouble(reinterpret_cast<ZBPropertyItemIntelliEdit*>(pPropertyItem)->GetDataDouble());
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    Prop.SetValueFloat(reinterpret_cast<ZBPropertyItemIntelliEdit*>(pPropertyItem)->GetDataFloat());
                    break;
                }
            }

            break;
        }

        case ZBProperty::PT_EDIT_MULTILINE:
        case ZBProperty::PT_EDIT_MULTILINE_READONLY:
        {
            switch (Prop.GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    Prop.SetValueString(reinterpret_cast<ZBPropertyItemMultiLineEdit*>(pPropertyItem)->GetData());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    Prop.SetValueDouble(reinterpret_cast<ZBPropertyItemMultiLineEdit*>(pPropertyItem)->GetDataDouble());
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    Prop.SetValueFloat(reinterpret_cast<ZBPropertyItemMultiLineEdit*>(pPropertyItem)->GetDataFloat());
                    break;
                }
            }

            break;
        }
    }

    // Assign has changed flag
    Prop.SetHasChanged(pPropertyItem->GetHasChanged());

    // Sets the order
    Prop.SetItemOrder(pPropertyItem->GetItemOrder());
    Prop.SetCategoryOrder(pPropertyItem->GetCategoryOrder());
}

void ZBPropertyItemManager::DeleteAllTabs()
{
    // Run through all items
    ZBItemCategoryIterator i(&m_PropertyItemTabSet);

    for (ZBPropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; pItemCat = i.GetNext())
    {
        delete pItemCat;
    }

    m_PropertyItemTabSet.RemoveAll();
}

void ZBPropertyItemManager::DeleteUnusedTab()
{
    // Run through all items
    ZBItemCategoryIterator i(&m_PropertyItemTabSet);

    for (ZBPropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; )
    {
        if (!ExistInPropSet(pItemCat->GetName()))
        {
            delete pItemCat;

            i.Remove();

            // After a remove, get the current element
            pItemCat = i.Get();
        }
        else
        {
            // Retreive the next element
            pItemCat = i.GetNext();
        }
    }
}

bool ZBPropertyItemManager::ExistInPropSet(LPCTSTR pStrTabName)
{
    // Now run through the list of data and fill the property set
    ZBPropertyIterator i(&m_PropSet);

    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (pProp->GetCategory() == pStrTabName)
        {
            return true;
        }
    }

    return false;
}

ZBProperty* ZBPropertyItemManager::GetCorrespondingProperty(ZBPropertyItem* pPropertyItem)
{
    // Now run through the list of data and fill the property set
    ZBPropertyIterator i(&m_PropSet);

    ZBProperty* pProp;

    ZBPropertyItemCategory* pCat = GetTab(pPropertyItem);

    if (!pCat)
    {
        return NULL;
    }

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (pProp->GetCategoryID() == pCat->GetPropertyID() &&
            pProp->GetItemID() == pPropertyItem->GetPropertyID())
        {
            return pProp;
        }
    }

    return NULL;
}

ZBPropertyItemCategory* ZBPropertyItemManager::AddNewTab(LPCTSTR pStrTabName)
{
    ZBPropertyItemCategory* pNewTab = TabExist(pStrTabName);

    if (!pNewTab)
    {
        pNewTab = new ZBPropertyItemCategory(pStrTabName);
        m_PropertyItemTabSet.Add(pNewTab);
    }

    return pNewTab;
}

ZBPropertyItemCategory* ZBPropertyItemManager::TabExist(LPCTSTR pStrTabName)
{
    // Run through all items
    ZBItemCategoryIterator i(&m_PropertyItemTabSet);

    for (ZBPropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; pItemCat = i.GetNext())
    {
        if (pItemCat->GetName() == pStrTabName)
        {
            return pItemCat;
        }
    }

    return NULL;
}

ZBPropertyItemCategory* ZBPropertyItemManager::GetTab(ZBPropertyItem* pPropertyItem)
{
    // Run through all items
    ZBItemCategoryIterator i(&m_PropertyItemTabSet);

    for (ZBPropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; pItemCat = i.GetNext())
    {
        if (pItemCat->PropertyItemExist(pPropertyItem))
        {
            return pItemCat;
        }
    }

    return NULL;
}

void ZBPropertyItemManager::CheckState(int nFromControlIndex, BYTE nFromPropertyItemID)
{
    if (!m_pWndPropertyListCtrl)
    {
        return;
    }

    bool bDoInsert = false;

    // Run through all items
    ZBItemCategoryIterator i(&m_PropertyItemTabSet);

    for (ZBPropertyItemCategory* pPropertyItemTab = i.GetFirst(); pPropertyItemTab; pPropertyItemTab = i.GetNext())
    {
        if (bDoInsert)
        {
            if (pPropertyItemTab->GetEnabled())
            {
                m_pWndPropertyListCtrl->InsertPropertyItem(pPropertyItemTab, ++nFromControlIndex);
                pPropertyItemTab->SetChildrenVisible();
            }
            else
            {
                continue;
            }
        }

        // Now run through category's elements
        ZBPropertyItemIterator j(&pPropertyItemTab->GetPropertyItemSet());

        for (ZBPropertyItem* pPropertyItem = j.GetFirst(); pPropertyItem; pPropertyItem = j.GetNext())
        {
            if (bDoInsert)
            {
                if (pPropertyItem->GetEnabled())
                {
                    m_pWndPropertyListCtrl->InsertPropertyItem(pPropertyItem, ++nFromControlIndex);
                }
            }
            else if (nFromPropertyItemID == pPropertyItem->GetPropertyID() ||
                     nFromPropertyItemID == 0)
            {
                int nItems = m_pWndPropertyListCtrl->GetCount();

                if (nItems != nFromControlIndex + 1)
                {
                    int i = nItems - 1;
                    nItems -= (nFromControlIndex + 1);

                    while (nItems-- > 0)
                    {
                        m_pWndPropertyListCtrl->DeleteString(i--);
                    }
                }

                bDoInsert = true;
            }
        }
    }
}

void ZBPropertyItemManager::DeletePropertyState()
{
    _ZBPropertyStateIterator i(&m_PropertyState);
    _ZBPropertyState* pPropState;

    for (pPropState = i.GetFirst(); pPropState; pPropState = i.GetNext())
    {
        delete pPropState;
    }

    m_PropertyState.RemoveAll();
}

bool ZBPropertyItemManager::SavePropertyState(ZBPropertyItem* pPropertyItem)
{
    _ZBPropertyState* pPropState = GetPropertyState(pPropertyItem);

    // If not found, try to create a new property
    if (!pPropState)
    {
        ZBProperty*    pCorrespondingProperty = GetCorrespondingProperty(pPropertyItem);

        if (pCorrespondingProperty)
        {
            pPropState = new _ZBPropertyState(*pCorrespondingProperty);
            m_PropertyState.Add(pPropState);
        }
    }

    // If ok, then save the state
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

_ZBPropertyState* ZBPropertyItemManager::GetPropertyState(ZBPropertyItem* pPropertyItem)
{
    ZBProperty*    pCorrespondingProperty = GetCorrespondingProperty(pPropertyItem);

    if (pCorrespondingProperty)
    {
        _ZBPropertyStateIterator i(&m_PropertyState);
        _ZBPropertyState* pPropState;

        for (pPropState = i.GetFirst(); pPropState; pPropState = i.GetNext())
        {
            if (pPropState->GetCategoryID() == pCorrespondingProperty->GetCategoryID() &&
                (pPropertyItem->GetSaveStatePerProperty() == false ||
                 pPropState->GetItemID() == pCorrespondingProperty->GetItemID()))
            {
                return pPropState;
            }
        }
    }

    // Not found, will return NULL
    return NULL;
}

bool ZBPropertyItemManager::SetPropertyStateToProperty(ZBPropertyItem* pPropertyItem)
{
    _ZBPropertyState* pPropState = GetPropertyState(pPropertyItem);

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

bool ZBPropertyItemManager::SavePropertyState(ZBPropertyItemCategory* pPropertyCategoryItem)
{
    _ZBPropertyState* pPropState = GetPropertyCategoryState(pPropertyCategoryItem);

    // If not found, try to create a new property
    if (!pPropState)
    {
        pPropState = new _ZBPropertyState(*pPropertyCategoryItem);
        m_PropertyState.Add(pPropState);
    }

    // If ok, then save the state
    if (pPropState)
    {
        // Change the item state
        pPropState->SetCollapsed(!pPropertyCategoryItem->GetChildrenVisible());
        pPropState->SetSize(pPropertyCategoryItem->GetSize());
        pPropState->SetExtendedSize(pPropertyCategoryItem->GetExtendedSize());
        pPropState->SetItemOrder(pPropertyCategoryItem->GetItemOrder());
        pPropState->SetCategoryOrder(pPropertyCategoryItem->GetCategoryOrder());

        return true;
    }

    return false;
}

_ZBPropertyState* ZBPropertyItemManager::GetPropertyCategoryState(ZBPropertyItemCategory* pPropertyCategoryItem)
{
    if (pPropertyCategoryItem)
    {
        _ZBPropertyStateIterator i(&m_PropertyState);
        _ZBPropertyState* pPropState;

        for (pPropState = i.GetFirst(); pPropState; pPropState = i.GetNext())
        {
            if (pPropState->GetCategoryID() == pPropertyCategoryItem->GetPropertyID() &&
                pPropState->GetItemID() == 0)
            {
                return pPropState;
            }
        }
    }

    // Not found, will return NULL
    return NULL;
}

bool ZBPropertyItemManager::SetPropertyStateToProperty(ZBPropertyItemCategory* pPropertyCategoryItem)
{
    _ZBPropertyState* pPropState = GetPropertyCategoryState(pPropertyCategoryItem);

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

bool ZBPropertyItemManager::LoadStateFromIniFile(const CString IniFile)
{
    // First, delete all states
    DeletePropertyState();

    PSS_SystemOption    SystemOption(IniFile, _PropertyItemManagerSectionName);

    CString KeyName;
    CString Line;
    size_t Idx = 0;

    do
    {
        // Format the key
        KeyName.Format(_T("%s%d"), (const char*)_PropertyItemStateEntityName, Idx);
        Line = SystemOption.ReadOption(KeyName, _T(""));

        if (Line.IsEmpty())
        {
            break;
        }

        ++Idx;

        CString str;
        PSS_Tokenizer token;

        // Extract the object number
        str = token.GetFirstToken(Line);

        if (str.IsEmpty())
        {
            continue;
        }

        double ObjectReference = atof((const char*)str);

        // Extract the category ID
        str = token.GetNextToken();

        if (str.IsEmpty())
        {
            continue;
        }

        int CategoryID = atoi((const char*)str);

        // Extract the item ID
        str = token.GetNextToken();

        if (str.IsEmpty())
        {
            continue;
        }

        int ItemID = atoi((const char*)str);

        // Extract the collapsed flag
        str = token.GetNextToken();

        if (str.IsEmpty())
        {
            continue;
        }

        bool Collapsed = (str.GetAt(0) == '1') ? true : false;

        // Extract the size
        str = token.GetNextToken();

        if (str.IsEmpty())
        {
            continue;
        }

        int cx = atoi((const char*)str);

        str = token.GetNextToken();

        if (str.IsEmpty())
        {
            continue;
        }

        int cy = atoi((const char*)str);

        // Extract the extended size
        str = token.GetNextToken();

        if (str.IsEmpty())
        {
            continue;
        }

        int cxExt = atoi((const char*)str);

        str = token.GetNextToken();

        if (str.IsEmpty())
        {
            continue;
        }

        int cyExt = atoi((const char*)str);

        // Extract the Item Order
        str = token.GetNextToken();

        if (str.IsEmpty())
        {
            continue;
        }

        int ItemOrder = atoi((const char*)str);

        // Extract the Category Order
        str = token.GetNextToken();

        if (str.IsEmpty())
        {
            continue;
        }

        int CategoryOrder = atoi((const char*)str);

        // If we are here, all objects have been extracted
        // Create the object state
        _ZBPropertyState* pPropState = new _ZBPropertyState();

        pPropState->SetObjectReference(ObjectReference);
        pPropState->SetCategoryID(CategoryID);
        pPropState->SetItemID(ItemID);
        pPropState->SetCollapsed(Collapsed);
        pPropState->SetSize(CSize(cx, cy));
        pPropState->SetExtendedSize(CSize(cxExt, cyExt));
        pPropState->SetItemOrder(ItemOrder);
        pPropState->SetCategoryOrder(CategoryOrder);

        // Add it to the array of value
        m_PropertyState.Add(pPropState);
    }
    while (Idx < 1000000);    // Sets the maximum loop at 1 million objects
                                // which is big already

    return true;
}

bool ZBPropertyItemManager::SaveStateToIniFile(const CString IniFile)
{
    PSS_SystemOption SystemOption(IniFile, _PropertyItemManagerSectionName);

    _ZBPropertyStateIterator i(&m_PropertyState);
    size_t Idx = 0;
    CString KeyName;
    _ZBPropertyState* pPropState;

    for (pPropState = i.GetFirst(); pPropState; pPropState = i.GetNext(), ++Idx)
    {
        // Format the key
        KeyName.Format(_T("%s%d"), (const char*)_PropertyItemStateEntityName, Idx);

        PSS_Tokenizer token;

        // Build the string
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

        // Write the string to the ini file
        SystemOption.WriteOption(KeyName, token.GetString());
    }

    return true;
}

bool ZBPropertyItemManager::OnDropInternalPropertyItem(ZBPropertyItem* pSrcPropertyItem,
                                                       ZBPropertyItem* pDstPropertyItem,
                                                       bool            Top2Down)
{
    // If the source is a category
    if (ISA(pSrcPropertyItem, ZBPropertyItemCategory))
    {
        return OnDropCategory(dynamic_cast<ZBPropertyItemCategory*>(pSrcPropertyItem),
                              pDstPropertyItem, Top2Down);
    }

    // Now run through the list of data and locate the source and the destination property
    ZBProperty* pSrcProp;
    ZBPropertyIterator i(&m_PropSet);
    bool FoundSrc = false;

    for (pSrcProp = i.GetFirst(); pSrcProp; pSrcProp = i.GetNext())
    {
        // First, find the category
        ZBPropertyItemCategory* pTab = TabExist(pSrcProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Check if already exists
        ZBPropertyItem* pPropItem = pTab->GetPropertyItem(pSrcProp->GetItemID());

        if (!pPropItem || pPropItem != pSrcPropertyItem)
        {
            continue;
        }

        // Sets the appropriate data to the source property item
        SetItemDataToProperty(pPropItem, *pSrcProp);

        FoundSrc = true;

        break;
    }

    if (!FoundSrc)
    {
        return false;
    }

    ZBProperty* pDstProp;
    ZBPropertyIterator l(&m_PropSet);
    bool FoundDst = false;

    for (pDstProp = l.GetFirst(); pDstProp; pDstProp = l.GetNext())
    {
        // First, find the category
        ZBPropertyItemCategory* pTab = TabExist(pDstProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Check if already exists
        ZBPropertyItem* pPropItem = pTab->GetPropertyItem(pDstProp->GetItemID());;

        if (!pPropItem || pPropItem != pDstPropertyItem)
        {
            continue;
        }

        // Sets the appropriate data to the destination property item
        SetItemDataToProperty(pPropItem, *pDstProp);
        FoundDst = true;

        break;
    }

    if (!FoundDst)
    {
        return false;
    }

    if (pSrcProp && pDstProp && m_pCurrentData)
    {
        if (m_pCurrentData->OnDropInternalPropertyItem(*pSrcProp, *pDstProp, Top2Down, m_PropSet))
        {
            ApplyPropertyChanges();
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool ZBPropertyItemManager::OnDropCategory(ZBPropertyItemCategory* pSrcCategoryItem,
                                           ZBPropertyItem*         pDstPropertyItem,
                                           bool                    top2Down)
{
    if (!pDstPropertyItem || !pSrcCategoryItem)
        return false;

    ZBPropertyItemCategory* pDstCategoryItem;

    // if the destination is a category
    if (ISA(pDstPropertyItem, ZBPropertyItemCategory))
        pDstCategoryItem = dynamic_cast<ZBPropertyItemCategory*>(pDstPropertyItem);
    else
        // locate the category of the property item
        pDstCategoryItem = GetTab(pDstPropertyItem);

    if (!pDstCategoryItem)
        return false;

    // now change the category order
    if (pSrcCategoryItem->GetCategoryOrder() == -1 || pDstCategoryItem->GetCategoryOrder() == -1)
        SetInitialCategoryOrder();

    // swap the two category order
    int  srcCategoryOrder = pSrcCategoryItem->GetCategoryOrder();
    int  dstCategoryOrder = pDstCategoryItem->GetCategoryOrder();
    bool foundSrc = false;

    ZBItemCategoryIterator  i(&m_PropertyItemTabSet);
    ZBPropertyItemCategory* pItemCat;

    for (pItemCat = (top2Down ? i.GetFirst() : i.GetLast()); pItemCat; pItemCat = (top2Down ? i.GetNext() : i.GetPrev()))
        // if we found the right source property, break the loop and set the flag
        if (pItemCat == pSrcCategoryItem)
        {
            foundSrc = true;
            break;
        }

    // if the source hasn't been reached, then error
    if (!foundSrc)
        return false;

    // wow, from the source till the destination, copy the element to the previous
    bool foundDst = false;
    int  previousCategoryOrder = pItemCat->GetCategoryOrder();

    for (pItemCat = (top2Down ? i.GetNext() : i.GetPrev()); pItemCat; pItemCat = (top2Down ? i.GetNext() : i.GetPrev()))
    {
    #ifdef _DEBUG
        CString s;
        s.Format(_T(" Before Item = %s Order = %d   ---  "),
            (const char*)pItemCat->GetName(), pItemCat->GetCategoryOrder());

        TRACE(s);
    #endif

        const int order = previousCategoryOrder;

        // save the previous category order
        previousCategoryOrder = pItemCat->GetCategoryOrder();

        // copy the current category order value to the previous element
        pItemCat->SetCategoryOrder(order);

        if (pItemCat == pDstCategoryItem)
        {
            foundDst = true;
            break;
        }

    #ifdef _DEBUG
        s.Format(_T(" After Item = %s Order = %d\n "),
            (const char*)pItemCat->GetName(), pItemCat->GetCategoryOrder());

        TRACE(s);
    #endif
    }

    // if the destination hasn't been reached, then error
    if (!foundSrc || !pItemCat)
        return false;

    // Copy the saved category order value of the droped item
    pSrcCategoryItem->SetCategoryOrder(dstCategoryOrder);

    // re-order the category
    ReOrderCategory();

    // and saves the new order
    SaveAllCategoryOrders();

    return true;
}
//---------------------------------------------------------------------------
void ZBPropertyItemManager::SaveAllCategoryOrders()
{
    // Now run through the list of categories and set category order
    // to the corresponding object state
    ZBItemCategoryIterator i(&m_PropertyItemTabSet);

    for (ZBPropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; pItemCat = i.GetNext())
    {
        SavePropertyState(pItemCat);
    }
}

void ZBPropertyItemManager::SetInitialCategoryOrder()
{
    // Now run through the list of categories and set category order
    int CategoryOrder = 0;

    ZBItemCategoryIterator i(&m_PropertyItemTabSet);

    for (ZBPropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; pItemCat = i.GetNext())
    {
        pItemCat->SetCategoryOrder(CategoryOrder);
        ++CategoryOrder;
    }
}
//---------------------------------------------------------------------------
// Re-order the category
void ZBPropertyItemManager::ReOrderCategory()
{
    // run through all categories and check if category order is correctly set
    bool orderSet = false;

    ZBItemCategoryIterator i(&m_PropertyItemTabSet);

    for (ZBPropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; pItemCat = i.GetNext())
    {
        // order is not set,
        // then re assigns initial order
        // we cannot do in another, since some objects can have more attributes
        // event if they are in the same group of objects.
        if (pItemCat->GetCategoryOrder() == -1)
        {
            if (orderSet)
            {
                SetInitialCategoryOrder();

                // and saves the new order
                SaveAllCategoryOrders();
            }

            return;
        }

        orderSet = true;
    }

    // transfert item to temporary set
    ZBItemCategorySet      tempItemTabSet;
    ZBItemCategoryIterator j(&m_PropertyItemTabSet);

    for (ZBPropertyItemCategory* pItemCat = j.GetFirst(); pItemCat; pItemCat = j.GetNext())
        tempItemTabSet.Add(pItemCat);

    // remove all elements from the initial set, just the pointer, not the element itself
    m_PropertyItemTabSet.RemoveAll();

    // now insert elements in order
    ZBItemCategoryIterator s(&tempItemTabSet);

    for (ZBPropertyItemCategory* pSrcItemCat = s.GetFirst(); pSrcItemCat; pSrcItemCat = s.GetNext())
    {
        // insert in order
        bool                   inserted = false;
        int                    index = 0;
        ZBItemCategoryIterator d(&m_PropertyItemTabSet);

        for (ZBPropertyItemCategory* pDstItemCat = d.GetFirst(); pDstItemCat; pDstItemCat = d.GetNext(), ++index)
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
