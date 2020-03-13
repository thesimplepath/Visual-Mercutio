/****************************************************************************
 * ==> PSS_DynamicProperties -----------------------------------------------*
 ****************************************************************************
 * Description : Provides the dynamic properties                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DynamicProperties.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_DynamicProperties, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DynamicProperties
//---------------------------------------------------------------------------
PSS_DynamicProperties::PSS_DynamicProperties()
{}
//---------------------------------------------------------------------------
PSS_DynamicProperties::PSS_DynamicProperties(const PSS_DynamicProperties& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_DynamicProperties::~PSS_DynamicProperties()
{
    // NOTE use fully qualified name here to avoid to call a pure virtual function on destruction
    PSS_DynamicProperties::FreePropertiesSet();
}
//---------------------------------------------------------------------------
PSS_DynamicProperties& PSS_DynamicProperties::operator = (const PSS_DynamicProperties& other)
{
    IDynamicPropertiesIterator it(&other.m_Set);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        AddDynamicProperty(pProp->Dup());

    return *this;
}
//---------------------------------------------------------------------------
PSS_DynamicProperties* PSS_DynamicProperties::Dup() const
{
    return new PSS_DynamicProperties(*this);
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::CreateSymbolProperties()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::FillProperties(PSS_Properties::IPropertySet& propSet, bool numericValues, bool groupValues)
{
    IDynamicPropertiesIterator it(&m_Set);

    // add the properties to the set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        propSet.Add(pProp->Dup());

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::SaveProperties(PSS_Properties::IPropertySet& propSet)
{
    PSS_Properties::IPropertyIterator itProp(&propSet);

    // iterate through the source properties
    for (PSS_Property* pPropSrc = itProp.GetFirst(); pPropSrc; pPropSrc = itProp.GetNext())
    {
        IDynamicPropertiesIterator itDynProp(&m_Set);

        // iterate through the destination properties and fill the property set
        for (PSS_Property* pPropDst = itDynProp.GetFirst(); pPropDst; pPropDst = itDynProp.GetNext())
            if (pPropSrc->GetCategoryID() == pPropDst->GetCategoryID() &&
                pPropSrc->GetItemID()     == pPropDst->GetItemID())
                switch (pPropSrc->GetValueType())
                {
                    case PSS_Property::IE_VT_String:   pPropDst->SetValueString (pPropSrc->GetValueString());    break;
                    case PSS_Property::IE_VT_Double:   pPropDst->SetValueDouble  (pPropSrc->GetValueDouble());   break;
                    case PSS_Property::IE_VT_Float:    pPropDst->SetValueFloat   (pPropSrc->GetValueFloat());    break;
                    case PSS_Property::IE_VT_Date:     pPropDst->SetValueDate    (pPropSrc->GetValueDate());     break;
                    case PSS_Property::IE_VT_TimeSpan: pPropDst->SetValueTimeSpan(pPropSrc->GetValueTimeSpan()); break;
                    case PSS_Property::IE_VT_Duration: pPropDst->SetValueDuration(pPropSrc->GetValueDuration()); break;
                }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::FillProperty(PSS_Property& prop)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::SaveProperty(PSS_Property& prop)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::CheckPropertyValue(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::ProcessExtendedInput(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props, bool& refresh)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::ProcessMenuCommand(int                           menuCmdID,
                                               PSS_Property&                 prop,
                                               CString&                      value,
                                               PSS_Properties::IPropertySet& props,
                                               bool&                         refresh)
{
    return true;
}
//---------------------------------------------------------------------------
void PSS_DynamicProperties::AddDynamicProperty(PSS_Property* pProperty)
{
    if (!pProperty)
        return;

    if (!Exist(pProperty))
        m_Set.Add(pProperty);
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::Exist(PSS_Property* pProperty)
{
    IDynamicPropertiesIterator it(&m_Set);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == pProperty->GetCategoryID() && pProp->GetItemID() == pProperty->GetItemID())
            return true;

    return false;
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::DeleteProperty(PSS_Property* pProperty)
{
    IDynamicPropertiesIterator it(&m_Set);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == pProperty->GetCategoryID() && pProp->GetItemID() == pProperty->GetItemID())
        {
            delete pProp;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
void PSS_DynamicProperties::FreePropertiesSet()
{
    IDynamicPropertiesIterator it(&m_Set);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::OnPrePropertyChanged(const CString& newValue, PSS_Property& prop, PSS_Properties::IPropertySet& props)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::OnPostPropertyChanged(PSS_Property& prop, PSS_Properties::IPropertySet& props, bool& refresh)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::OnDropInternalPropertyItem(PSS_Property&                 srcProperty,
                                                       PSS_Property&                 dstProperty,
                                                       bool                          top2Down,
                                                       PSS_Properties::IPropertySet& props)
{
    return true;
}
//---------------------------------------------------------------------------
void PSS_DynamicProperties::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // serialize the size
        ar << int(m_Set.GetSize());

        IDynamicPropertiesIterator it(&m_Set);

        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            ar << pProp;
    }
    else
    {
        int size;
        ar >> size;

        PSS_Property* pProp;

        for (int i = 0; i < size; ++i)
        {
            ar >> pProp;
            AddDynamicProperty(pProp);
        }
    }
}
//---------------------------------------------------------------------------
