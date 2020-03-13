// ZBPropertyManager.cpp : implementation file

#include "stdafx.h"
#include "ZBPropertyManager.h"

// processsoft
#include "zBaseLib\PSS_SystemOption.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "ZCPropertyListCtrl.h"
#include "PSS_PropertyItems.h"

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
    PSS_Properties::IPropertyIterator i(&m_PropSet);
    PSS_Property* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        delete pProp;
    }

    m_PropSet.RemoveAll();
}

bool ZBPropertyItemManager::UpdateControlData(const PSS_Properties* pData)
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
    const_cast<PSS_Properties*>(pData)->FillProperties(m_PropSet);

    bool RetValue = UpdateControlData();

    m_pCurrentData = const_cast<PSS_Properties*>(pData);

    return RetValue;
}

bool ZBPropertyItemManager::UpdateControlData(PSS_Properties::IPropertySet& PropSet)
{
    // First, delete all tabs
    DeleteAllTabs();

    // Then all properties
    FreePropertySet();

    // Duplicate the set
    PSS_Properties::IPropertyIterator i(&PropSet);

    for (PSS_Property* pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        m_PropSet.Add(pProp->Dup());
    }

    bool RetValue = UpdateControlData();

    m_pCurrentData = NULL;

    return RetValue;
}

bool ZBPropertyItemManager::UpdateControlData()
{
    PSS_Properties::IPropertyIterator i(&m_PropSet);

    PSS_Property* pProp;

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

        PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

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
        PSS_PropertyItem* pPropertyItem = pTab->GetPropertyItem(pProp->GetItemID());

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
        pPropertyItem->SetEnabled(pProp->GetEnabled());
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

bool ZBPropertyItemManager::UpdatePropertyData(PSS_PropertyItem* pPropertyItem /*= NULL*/)
{
    PSS_Property* pProp;

    // If no property item specified, update all
    if (!pPropertyItem)
    {
        // Now run through the list of data and fill the property set
        PSS_Properties::IPropertyIterator i(&m_PropSet);

        for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        {
            // First, find the category
            PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

            if (!pTab)
            {
                continue;
            }

            // Check if already exists
            PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

            if (!pPropItem)
            {
                continue;
            }

            // Sets the appropriate data to the property item
            SetItemDataToProperty(pPropItem, *pProp);

            // Set the enable flag and the stringformat type
            pProp->SetEnabled(pPropItem->GetEnabled());
            pProp->SetStringFormat(pPropItem->GetStringFormat());
        }

        // Send the property set to the object
        return (m_pCurrentData) ? m_pCurrentData->SaveProperties(m_PropSet) : true;
    }

    // Otherwise, one value is specified and request only one save
    // Now run through the list of data and fill the property set
    PSS_Properties::IPropertyIterator i(&m_PropSet);

    bool Found = false;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // First, find the category
        PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Check if already exists
        PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

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

bool ZBPropertyItemManager::CheckCurrentPropertyData(PSS_PropertyItem* pPropertyItem, CString& ProposedValue)
{
    // If no item specified, assume the data are entered correctly
    if (!pPropertyItem)
    {
        return true;
    }

    // Otherwise, one value is specified and request only one save
    // Now run through the list of data and fill the property set
    PSS_Properties::IPropertyIterator i(&m_PropSet);

    PSS_Property* pProp;

    bool Found = false;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // First, find the category
        PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Check if already exists
        PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

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

bool ZBPropertyItemManager::ProcessExtendedCurrentPropertyData(PSS_PropertyItem*    pPropertyItem,
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
    PSS_Properties::IPropertyIterator i(&m_PropSet);

    PSS_Property* pProp;

    bool Found = false;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // First, find the category
        PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Check if already exists
        PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

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
                                                                  PSS_PropertyItem*    pPropertyItem,
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
    PSS_Properties::IPropertyIterator i(&m_PropSet);

    PSS_Property* pProp;

    bool Found = false;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // First, find the category
        PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Check if already exists
        PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pProp->GetItemID());

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
    PSS_Properties::IPropertyIterator i(&m_PropSet);

    PSS_Property* pProp;

    bool Updated = false;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // First, get the category
        PSS_PropertyItemCategory* pTab = TabExist(pProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Then, get the right property item
        PSS_PropertyItem* pPropertyItem = pTab->GetPropertyItem(pProp->GetItemID());

        // If not exits, continue
        if (!pPropertyItem)
        {
            continue;
        }

        // Sets the value, enable and name
        SetDataToPropertyItem(pPropertyItem, *pProp);

        pPropertyItem->SetEnabled(pProp->GetEnabled());
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

PSS_PropertyItem* ZBPropertyItemManager::CreatePropertyItem(PSS_Property& Prop)
{
    PSS_PropertyItem* pItem = NULL;

    switch (Prop.GetType())
    {
        case PSS_Property::IE_T_EditString:
        {
            pItem = new PSS_StringPropertyItem();
            break;
        }

        case PSS_Property::IE_T_EditStringReadOnly:
        {
            // Read-only and cannot be edited
            pItem = new PSS_StringPropertyItem(NULL, true, false);
            break;
        }

        case PSS_Property::IE_T_ComboString:
        {
            pItem = new PSS_ListPropertyItem();
            break;
        }

        case PSS_Property::IE_T_ComboStringReadOnly:
        {
            // Read-only
            pItem = new PSS_ListPropertyItem(NULL, true);
            break;
        }

        case PSS_Property::IE_T_EditNumber:
        {
            if (Prop.GetValueType() == PSS_Property::IE_VT_Double)
            {
                pItem = new PSS_NumberPropertyItem(Prop.GetValueDouble());
            }
            else
            {
                if (Prop.GetValueType() == PSS_Property::IE_VT_Float)
                {
                    pItem = new PSS_NumberPropertyItem(Prop.GetValueFloat());
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditNumberReadOnly:
        {
            if (Prop.GetValueType() == PSS_Property::IE_VT_Double)
            {
                // Read-only and cannot be edited
                pItem = new PSS_NumberPropertyItem(Prop.GetValueDouble(), true, false);
            }
            else
            {
                if (Prop.GetValueType() == PSS_Property::IE_VT_Float)
                {
                    // Read-only and cannot be edited
                    pItem = new PSS_NumberPropertyItem(Prop.GetValueFloat(), true, false);
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditMenu:
        {
            pItem = new PSS_MenuFileDirPropertyItem(Prop.GetMenu());
            break;
        }

        case PSS_Property::IE_T_EditMenuReadOnly:
        {
            // Read-only
            pItem = new PSS_MenuFileDirPropertyItem(Prop.GetMenu(), true);
            break;
        }

        case PSS_Property::IE_T_EditFile:
        {
            // As file is true
            pItem = new PSS_MenuFileDirPropertyItem((LPCTSTR)NULL, true);
            break;
        }

        case PSS_Property::IE_T_EditDirectory:
        {
            // As file is false
            pItem = new PSS_MenuFileDirPropertyItem((LPCTSTR)NULL, true);
            break;
        }

        case PSS_Property::IE_T_EditExtended:
        {
            pItem = new PSS_ExtendedPropertyItem();
            break;
        }

        case PSS_Property::IE_T_EditExtendedReadOnly:
        {
            // Read-only
            pItem = new PSS_ExtendedPropertyItem(NULL, true);
            break;
        }

        case PSS_Property::IE_T_EditDuration:
        {
            pItem = new PSS_DurationPropertyItem();
            break;
        }

        case PSS_Property::IE_T_EditDurationReadOnly:
        {
            // Read-only and cannot be edited
            pItem = new PSS_DurationPropertyItem(NULL, true, false);
            break;
        }

        case PSS_Property::IE_T_EditDate:
        {
            pItem = new PSS_DatePropertyItem();
            break;
        }

        case PSS_Property::IE_T_EditDateReadOnly:
        {
            // Read-only and cannot be edited
            pItem = new PSS_DatePropertyItem(NULL, true, false);
            break;
        }

        //RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
        case PSS_Property::IE_T_EditTime:
        {
            pItem = new PSS_TimePropertyItem();
            break;
        }

        case PSS_Property::IE_T_EditTimeReadOnly:
        {
            // Read-only and cannot be edited
            pItem = new PSS_TimePropertyItem(NULL, true, false);
            break;
        }

        case PSS_Property::IE_T_EditIntelli:
        {
            pItem = new PSS_IntelliEditPropertyItem();
            break;
        }

        case PSS_Property::IE_T_EditIntelliReadOnly:
        {
            // Read-only and cannot be edited
            pItem = new PSS_IntelliEditPropertyItem(NULL, true, false);
            break;
        }

        case PSS_Property::IE_T_EditMultiline:
        {
            pItem = new PSS_MultiLineEditPropertyItem();
            break;
        }

        case PSS_Property::IE_T_EditMultilineReadOnly:
        {
            // Read-only and cannot be edited
            pItem = new PSS_MultiLineEditPropertyItem(NULL, true, false);
            break;
        }
    }

    if (pItem)
    {
        // Sets drag&drop flag
        pItem->EnableDragNDrop(Prop.IsDragNDropEnabled());

        // Sets the order
        pItem->SetItemOrder(Prop.GetItemOrder());
        pItem->SetCategoryOrder(Prop.GetCategoryOrder());
    }

    return pItem;
}

void ZBPropertyItemManager::SetDataToPropertyItem(PSS_PropertyItem* pPropertyItem, PSS_Property& Prop)
{
    switch (Prop.GetType())
    {
        case PSS_Property::IE_T_EditString:
        case PSS_Property::IE_T_EditStringReadOnly:
        {
            reinterpret_cast<PSS_StringPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueString());
            break;
        }

        case PSS_Property::IE_T_ComboString:
        case PSS_Property::IE_T_ComboStringReadOnly:
        {
            reinterpret_cast<PSS_ListPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueString());

            // If contains value array
            if (Prop.HasValueList())
            {
                // Add all values
                reinterpret_cast<PSS_ListPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueArray());
            }

            break;
        }

        case PSS_Property::IE_T_EditNumber:
        case PSS_Property::IE_T_EditNumberReadOnly:
        {
            if (Prop.GetValueType() == PSS_Property::IE_VT_Double)
            {
                reinterpret_cast<PSS_NumberPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueDouble());
            }
            else
            {
                if (Prop.GetValueType() == PSS_Property::IE_VT_Float)
                {
                    reinterpret_cast<PSS_NumberPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueFloat());
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditExtended:
        case PSS_Property::IE_T_EditExtendedReadOnly:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    reinterpret_cast<PSS_ExtendedPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case PSS_Property::IE_VT_Double:
                {
                    reinterpret_cast<PSS_ExtendedPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueDouble());
                    break;
                }

                case PSS_Property::IE_VT_Float:
                {
                    reinterpret_cast<PSS_ExtendedPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueFloat());
                    break;
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditDuration:
        case PSS_Property::IE_T_EditDurationReadOnly:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    reinterpret_cast<PSS_DurationPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case PSS_Property::IE_VT_Duration:
                {
                    // JMR-MODIF - Le 2 août 2005 - Conversion explicite permet de corriger bug sur attributs dynamiques.
                    reinterpret_cast<PSS_DurationPropertyItem*>(pPropertyItem)->SetData((PSS_Duration&)Prop.GetValueDuration());
                    break;
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditDate:
        case PSS_Property::IE_T_EditDateReadOnly:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    reinterpret_cast<PSS_DatePropertyItem*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case PSS_Property::IE_VT_Date:
                {
                    // JMR-MODIF - Le 2 août 2005 - Conversion explicite permet de corriger bug sur attributs dynamiques.
                    reinterpret_cast<PSS_DatePropertyItem*>(pPropertyItem)->SetData((PSS_Date&)Prop.GetValueDate());
                    break;
                }
            }

            break;
        }

        // RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
        case PSS_Property::IE_T_EditTime:
        case PSS_Property::IE_T_EditTimeReadOnly:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    reinterpret_cast<PSS_TimePropertyItem*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case PSS_Property::IE_VT_TimeSpan:
                {
                    reinterpret_cast<PSS_TimePropertyItem*>(pPropertyItem)->SetData((PSS_TimeSpan&)Prop.GetValueTimeSpan());
                    break;
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditMenu:
        case PSS_Property::IE_T_EditMenuReadOnly:
        case PSS_Property::IE_T_EditFile:
        case PSS_Property::IE_T_EditDirectory:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    reinterpret_cast<PSS_MenuFileDirPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case PSS_Property::IE_VT_Double:
                {
                    reinterpret_cast<PSS_MenuFileDirPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueDouble());
                    break;
                }

                case PSS_Property::IE_VT_Float:
                {
                    reinterpret_cast<PSS_MenuFileDirPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueFloat());
                    break;
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditIntelli:
        case PSS_Property::IE_T_EditIntelliReadOnly:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    reinterpret_cast<PSS_IntelliEditPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case PSS_Property::IE_VT_Double:
                {
                    reinterpret_cast<PSS_IntelliEditPropertyItem*>(pPropertyItem)->SetData((char)Prop.GetValueDouble());
                    break;
                }

                case PSS_Property::IE_VT_Float:
                {
                    reinterpret_cast<PSS_IntelliEditPropertyItem*>(pPropertyItem)->SetData((char)Prop.GetValueFloat());
                    break;
                }
            }

            // If contains value array
            if (Prop.HasValueList())
            {
                // Add all values
                reinterpret_cast<PSS_IntelliEditPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueArray());
            }

            break;
        }

        case PSS_Property::IE_T_EditMultiline:
        case PSS_Property::IE_T_EditMultilineReadOnly:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    reinterpret_cast<PSS_MultiLineEditPropertyItem*>(pPropertyItem)->SetData(Prop.GetValueString());
                    break;
                }

                case PSS_Property::IE_VT_Double:
                {
                    reinterpret_cast<PSS_MultiLineEditPropertyItem*>(pPropertyItem)->SetData((char)Prop.GetValueDouble());
                    break;
                }

                case PSS_Property::IE_VT_Float:
                {
                    reinterpret_cast<PSS_MultiLineEditPropertyItem*>(pPropertyItem)->SetData((char)Prop.GetValueFloat());
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

void ZBPropertyItemManager::SetItemDataToProperty(PSS_PropertyItem* pPropertyItem, PSS_Property& Prop)
{
    // Assign the right values
    switch (Prop.GetType())
    {
        case PSS_Property::IE_T_EditString:
        case PSS_Property::IE_T_EditStringReadOnly:
        {
            Prop.SetValueString(reinterpret_cast<PSS_StringPropertyItem*>(pPropertyItem)->GetData());
            break;
        }

        case PSS_Property::IE_T_ComboString:
        case PSS_Property::IE_T_ComboStringReadOnly:
        {
            Prop.SetValueString(reinterpret_cast<PSS_ListPropertyItem*>(pPropertyItem)->GetData());
            break;
        }

        case PSS_Property::IE_T_EditNumber:
        case PSS_Property::IE_T_EditNumberReadOnly:
        {
            if (Prop.GetValueType() == PSS_Property::IE_VT_Double)
            {
                Prop.SetValueDouble(reinterpret_cast<PSS_NumberPropertyItem*>(pPropertyItem)->GetDataDouble());
            }
            else
            {
                if (Prop.GetValueType() == PSS_Property::IE_VT_Float)
                {
                    Prop.SetValueFloat(reinterpret_cast<PSS_NumberPropertyItem*>(pPropertyItem)->GetDataFloat());
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditExtended:
        case PSS_Property::IE_T_EditExtendedReadOnly:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    Prop.SetValueString(reinterpret_cast<PSS_ExtendedPropertyItem*>(pPropertyItem)->GetData());
                    break;
                }

                case PSS_Property::IE_VT_Double:
                {
                    Prop.SetValueDouble(reinterpret_cast<PSS_ExtendedPropertyItem*>(pPropertyItem)->GetDataDouble());
                    break;
                }

                case PSS_Property::IE_VT_Float:
                {
                    Prop.SetValueFloat(reinterpret_cast<PSS_ExtendedPropertyItem*>(pPropertyItem)->GetDataFloat());
                    break;
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditDuration:
        case PSS_Property::IE_T_EditDurationReadOnly:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    Prop.SetValueString(reinterpret_cast<PSS_DurationPropertyItem*>(pPropertyItem)->GetData());
                    break;
                }

                case PSS_Property::IE_VT_Duration:
                {
                    Prop.SetValueDuration(reinterpret_cast<PSS_DurationPropertyItem*>(pPropertyItem)->GetDataDuration());
                    break;
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditDate:
        case PSS_Property::IE_T_EditDateReadOnly:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    Prop.SetValueString(reinterpret_cast<PSS_DatePropertyItem*>(pPropertyItem)->GetData());
                    break;
                }

                case PSS_Property::IE_VT_Date:
                {
                    Prop.SetValueDate(reinterpret_cast<PSS_DatePropertyItem*>(pPropertyItem)->GetDataDate());
                    break;
                }
            }

            break;
        }
        //RS-MODIF 08.08.2005: correction attribut dynamique de temps n'était pas géré
        case PSS_Property::IE_T_EditTime:
        case PSS_Property::IE_T_EditTimeReadOnly:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    Prop.SetValueString(reinterpret_cast<PSS_TimePropertyItem*>(pPropertyItem)->GetData());
                    break;
                }

                case PSS_Property::IE_VT_TimeSpan:
                {
                    Prop.SetValueTimeSpan(reinterpret_cast<PSS_TimePropertyItem*>(pPropertyItem)->GetDataTime());
                    break;
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditMenu:
        case PSS_Property::IE_T_EditMenuReadOnly:
        case PSS_Property::IE_T_EditFile:
        case PSS_Property::IE_T_EditDirectory:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    Prop.SetValueString(reinterpret_cast<PSS_MenuFileDirPropertyItem*>(pPropertyItem)->GetData());
                    break;
                }

                case PSS_Property::IE_VT_Double:
                {
                    Prop.SetValueDouble(reinterpret_cast<PSS_MenuFileDirPropertyItem*>(pPropertyItem)->GetDataDouble());
                    break;
                }

                case PSS_Property::IE_VT_Float:
                {
                    Prop.SetValueFloat(reinterpret_cast<PSS_MenuFileDirPropertyItem*>(pPropertyItem)->GetDataFloat());
                    break;
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditIntelli:
        case PSS_Property::IE_T_EditIntelliReadOnly:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    Prop.SetValueString(reinterpret_cast<PSS_IntelliEditPropertyItem*>(pPropertyItem)->GetData());
                    break;
                }

                case PSS_Property::IE_VT_Double:
                {
                    Prop.SetValueDouble(reinterpret_cast<PSS_IntelliEditPropertyItem*>(pPropertyItem)->GetDataDouble());
                    break;
                }

                case PSS_Property::IE_VT_Float:
                {
                    Prop.SetValueFloat(reinterpret_cast<PSS_IntelliEditPropertyItem*>(pPropertyItem)->GetDataFloat());
                    break;
                }
            }

            break;
        }

        case PSS_Property::IE_T_EditMultiline:
        case PSS_Property::IE_T_EditMultilineReadOnly:
        {
            switch (Prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                {
                    Prop.SetValueString(reinterpret_cast<PSS_MultiLineEditPropertyItem*>(pPropertyItem)->GetData());
                    break;
                }

                case PSS_Property::IE_VT_Double:
                {
                    Prop.SetValueDouble(reinterpret_cast<PSS_MultiLineEditPropertyItem*>(pPropertyItem)->GetDataDouble());
                    break;
                }

                case PSS_Property::IE_VT_Float:
                {
                    Prop.SetValueFloat(reinterpret_cast<PSS_MultiLineEditPropertyItem*>(pPropertyItem)->GetDataFloat());
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

    for (PSS_PropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; pItemCat = i.GetNext())
    {
        delete pItemCat;
    }

    m_PropertyItemTabSet.RemoveAll();
}

void ZBPropertyItemManager::DeleteUnusedTab()
{
    // Run through all items
    ZBItemCategoryIterator i(&m_PropertyItemTabSet);

    for (PSS_PropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; )
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
            // Retrieve the next element
            pItemCat = i.GetNext();
        }
    }
}

bool ZBPropertyItemManager::ExistInPropSet(LPCTSTR pStrTabName)
{
    // Now run through the list of data and fill the property set
    PSS_Properties::IPropertyIterator i(&m_PropSet);

    PSS_Property* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (pProp->GetCategory() == pStrTabName)
        {
            return true;
        }
    }

    return false;
}

PSS_Property* ZBPropertyItemManager::GetCorrespondingProperty(PSS_PropertyItem* pPropertyItem)
{
    // Now run through the list of data and fill the property set
    PSS_Properties::IPropertyIterator i(&m_PropSet);

    PSS_Property* pProp;

    PSS_PropertyItemCategory* pCat = GetTab(pPropertyItem);

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

PSS_PropertyItemCategory* ZBPropertyItemManager::AddNewTab(LPCTSTR pStrTabName)
{
    PSS_PropertyItemCategory* pNewTab = TabExist(pStrTabName);

    if (!pNewTab)
    {
        pNewTab = new PSS_PropertyItemCategory(pStrTabName);
        m_PropertyItemTabSet.Add(pNewTab);
    }

    return pNewTab;
}

PSS_PropertyItemCategory* ZBPropertyItemManager::TabExist(LPCTSTR pStrTabName)
{
    // Run through all items
    ZBItemCategoryIterator i(&m_PropertyItemTabSet);

    for (PSS_PropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; pItemCat = i.GetNext())
    {
        if (pItemCat->GetName() == pStrTabName)
        {
            return pItemCat;
        }
    }

    return NULL;
}

PSS_PropertyItemCategory* ZBPropertyItemManager::GetTab(PSS_PropertyItem* pPropertyItem)
{
    // Run through all items
    ZBItemCategoryIterator i(&m_PropertyItemTabSet);

    for (PSS_PropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; pItemCat = i.GetNext())
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

    for (PSS_PropertyItemCategory* pPropertyItemTab = i.GetFirst(); pPropertyItemTab; pPropertyItemTab = i.GetNext())
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
        PSS_PropertyItemCategory::IPropertyItemIterator j(&pPropertyItemTab->GetPropertyItemSet());

        for (PSS_PropertyItem* pPropertyItem = j.GetFirst(); pPropertyItem; pPropertyItem = j.GetNext())
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

bool ZBPropertyItemManager::SavePropertyState(PSS_PropertyItem* pPropertyItem)
{
    _ZBPropertyState* pPropState = GetPropertyState(pPropertyItem);

    // If not found, try to create a new property
    if (!pPropState)
    {
        PSS_Property* pCorrespondingProperty = GetCorrespondingProperty(pPropertyItem);

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

_ZBPropertyState* ZBPropertyItemManager::GetPropertyState(PSS_PropertyItem* pPropertyItem)
{
    PSS_Property* pCorrespondingProperty = GetCorrespondingProperty(pPropertyItem);

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

bool ZBPropertyItemManager::SetPropertyStateToProperty(PSS_PropertyItem* pPropertyItem)
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

bool ZBPropertyItemManager::SavePropertyState(PSS_PropertyItemCategory* pPropertyCategoryItem)
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

_ZBPropertyState* ZBPropertyItemManager::GetPropertyCategoryState(PSS_PropertyItemCategory* pPropertyCategoryItem)
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

bool ZBPropertyItemManager::SetPropertyStateToProperty(PSS_PropertyItemCategory* pPropertyCategoryItem)
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

bool ZBPropertyItemManager::OnDropInternalPropertyItem(PSS_PropertyItem* pSrcPropertyItem,
                                                       PSS_PropertyItem* pDstPropertyItem,
                                                       bool            Top2Down)
{
    // If the source is a category
    if (ISA(pSrcPropertyItem, PSS_PropertyItemCategory))
    {
        return OnDropCategory(dynamic_cast<PSS_PropertyItemCategory*>(pSrcPropertyItem),
                              pDstPropertyItem, Top2Down);
    }

    // Now run through the list of data and locate the source and the destination property
    PSS_Property* pSrcProp;
    PSS_Properties::IPropertyIterator i(&m_PropSet);
    bool FoundSrc = false;

    for (pSrcProp = i.GetFirst(); pSrcProp; pSrcProp = i.GetNext())
    {
        // First, find the category
        PSS_PropertyItemCategory* pTab = TabExist(pSrcProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Check if already exists
        PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pSrcProp->GetItemID());

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

    PSS_Property* pDstProp;
    PSS_Properties::IPropertyIterator l(&m_PropSet);
    bool FoundDst = false;

    for (pDstProp = l.GetFirst(); pDstProp; pDstProp = l.GetNext())
    {
        // First, find the category
        PSS_PropertyItemCategory* pTab = TabExist(pDstProp->GetCategory());

        if (!pTab)
        {
            continue;
        }

        // Check if already exists
        PSS_PropertyItem* pPropItem = pTab->GetPropertyItem(pDstProp->GetItemID());;

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
bool ZBPropertyItemManager::OnDropCategory(PSS_PropertyItemCategory* pSrcCategoryItem,
                                           PSS_PropertyItem*         pDstPropertyItem,
                                           bool                    top2Down)
{
    if (!pDstPropertyItem || !pSrcCategoryItem)
        return false;

    PSS_PropertyItemCategory* pDstCategoryItem;

    // if the destination is a category
    if (ISA(pDstPropertyItem, PSS_PropertyItemCategory))
        pDstCategoryItem = dynamic_cast<PSS_PropertyItemCategory*>(pDstPropertyItem);
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
    PSS_PropertyItemCategory* pItemCat;

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

    for (PSS_PropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; pItemCat = i.GetNext())
    {
        SavePropertyState(pItemCat);
    }
}

void ZBPropertyItemManager::SetInitialCategoryOrder()
{
    // Now run through the list of categories and set category order
    int CategoryOrder = 0;

    ZBItemCategoryIterator i(&m_PropertyItemTabSet);

    for (PSS_PropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; pItemCat = i.GetNext())
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

    for (PSS_PropertyItemCategory* pItemCat = i.GetFirst(); pItemCat; pItemCat = i.GetNext())
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

    for (PSS_PropertyItemCategory* pItemCat = j.GetFirst(); pItemCat; pItemCat = j.GetNext())
        tempItemTabSet.Add(pItemCat);

    // remove all elements from the initial set, just the pointer, not the element itself
    m_PropertyItemTabSet.RemoveAll();

    // now insert elements in order
    ZBItemCategoryIterator s(&tempItemTabSet);

    for (PSS_PropertyItemCategory* pSrcItemCat = s.GetFirst(); pSrcItemCat; pSrcItemCat = s.GetNext())
    {
        // insert in order
        bool                   inserted = false;
        int                    index = 0;
        ZBItemCategoryIterator d(&m_PropertyItemTabSet);

        for (PSS_PropertyItemCategory* pDstItemCat = d.GetFirst(); pDstItemCat; pDstItemCat = d.GetNext(), ++index)
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
