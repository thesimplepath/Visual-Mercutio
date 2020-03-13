/****************************************************************************
 * ==> PSS_PropertyAttributes ----------------------------------------------*
 ****************************************************************************
 * Description : Provides the property attributes                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PropertyAttributes.h"

// std
#include <memory>

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_StringFormatter.h"
#include "zBaseLib\PSS_SystemOption.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const CString g_PropertyAttributeStateSectionName = _T("_PropertyDefaultAttributeSaveState");
const CString g_PropertyAttributeStateEntityName  = _T("_PropertyDefaultAttributeState");
//---------------------------------------------------------------------------
// PSS_PropertyAttributes::IAttribute
//---------------------------------------------------------------------------
PSS_PropertyAttributes::IAttribute::IAttribute(int categoryID, int itemID) :
    m_CategoryID(categoryID),
    m_ItemID(itemID)
{}
//---------------------------------------------------------------------------
PSS_PropertyAttributes::IAttribute::IAttribute(IAttribute& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
const PSS_PropertyAttributes::IAttribute& PSS_PropertyAttributes::IAttribute::operator = (const IAttribute& other)
{
    m_CategoryID = other.m_CategoryID;
    m_ItemID     = other.m_ItemID;

    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_PropertyAttributes::IAttribute& other)
{
    ar >> other.m_CategoryID;
    ar >> other.m_ItemID;

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_PropertyAttributes::IAttribute& other)
{
    ar << other.m_CategoryID;
    ar << other.m_ItemID;

    return ar;
}
//---------------------------------------------------------------------------
PSS_PropertyAttributes::IAttribute* PSS_PropertyAttributes::IAttribute::Clone()
{
    return new IAttribute(*this);
}
//---------------------------------------------------------------------------
// PSS_PropertyAttributes
//---------------------------------------------------------------------------
PSS_PropertyAttributes::PSS_PropertyAttributes() :
    m_ShowTitleText(true)
{}
//---------------------------------------------------------------------------
PSS_PropertyAttributes::PSS_PropertyAttributes(PSS_PropertyAttributes& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PropertyAttributes::~PSS_PropertyAttributes()
{
    RemoveAllAttributes();
}
//---------------------------------------------------------------------------
const PSS_PropertyAttributes& PSS_PropertyAttributes::operator = (const PSS_PropertyAttributes& other)
{
    m_ShowTitleText = other.m_ShowTitleText;

    // remove all existing attributes
    RemoveAllAttributes();

    // copy all attribute elements
    IAttributeIterator it(&other.GetAttributeSet());

    for (IAttribute* pAtt = it.GetFirst(); pAtt; pAtt = it.GetNext())
        AddAttribute(pAtt->Clone());

    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_PropertyAttributes& attributes)
{
    WORD value;
    ar >> value;
    attributes.SetShowTitleText(value == 1);

    PSS_PropertyAttributes::IAttribute attribute;

    int count;
    ar >> count;

    for (int i = 0; i < count; ++i)
    {
        ar >> attribute;
        attributes.AddAttribute(attribute.Clone());
    }

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_PropertyAttributes& attributes)
{
    ar << WORD(attributes.GetShowTitleText());
    ar << int (attributes.GetAttributeCount());

    PSS_PropertyAttributes::IAttributeIterator it(&attributes.GetAttributeSet());

    for (PSS_PropertyAttributes::IAttribute* pAtt = it.GetFirst(); pAtt; pAtt = it.GetNext())
        ar << *pAtt;

    return ar;
}
//---------------------------------------------------------------------------
PSS_PropertyAttributes* PSS_PropertyAttributes::Clone()
{
    return new PSS_PropertyAttributes(*this);
}
//---------------------------------------------------------------------------
bool PSS_PropertyAttributes::LoadStateFromIniFile(const CString& iniFile, int objectID)
{
    // delete all attributes
    RemoveAllAttributes();

    CString entityName;
    entityName.Format(_T("%s%d"), (const char*)g_PropertyAttributeStateSectionName, objectID);

    PSS_SystemOption systemOption(iniFile, entityName);

    CString     keyName;
    CString     line;
    std::size_t index = 0;

    do
    {
        // format the key
        keyName.Format(_T("%s%d"), (const char*)g_PropertyAttributeStateEntityName, index);
        line = systemOption.ReadOption(keyName, _T(""));

        if (line.IsEmpty())
            break;

        ++index;

        PSS_Tokenizer token;

        // Extract the category ID
        CString str = token.GetFirstToken(line);

        if (str.IsEmpty())
            continue;

        const int categoryID = std::atoi((const char*)str);

        // extract the item index
        str = token.GetNextToken();

        if (str.IsEmpty())
            continue;

        const int itemID = std::atoi((const char*)str);

        // all objects were extracted, create the object state
        std::unique_ptr<IAttribute> pAtt(new IAttribute(categoryID, itemID));

        // add it to the value array
        AddAttribute(pAtt.get());
        pAtt.release();
    }
    // set the maximum loop at 1 million objects, which is enough
    while (index < 1000000);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PropertyAttributes::SaveStateToIniFile(const CString& iniFile, int objectID)
{
    CString entityName;
    entityName.Format(_T("%s%d"), (const char*)g_PropertyAttributeStateSectionName, objectID);

    PSS_SystemOption systemOption(iniFile, entityName);

    // need to delete all the existing records before saving
    DeleteAttributesFromIniFile(iniFile, objectID);

    CString     keyName;
    std::size_t index = 0;

    IAttributeIterator it(&GetAttributeSet());

    for (IAttribute* pAtt = it.GetFirst(); pAtt; pAtt = it.GetNext(), ++index)
    {
        // format the key
        keyName.Format(_T("%s%d"), (const char*)g_PropertyAttributeStateEntityName, index);

        PSS_Tokenizer token;

        // build the string
        token.AddToken(pAtt->GetCategoryID());
        token.AddToken(pAtt->GetItemID());

        // Write the string to the ini file
        systemOption.WriteOption(keyName, token.GetString());
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PropertyAttributes::DeleteAttributesFromIniFile(const CString& iniFile, int objectID)
{
    CString entityName;
    entityName.Format(_T("%s%d"), (const char*)g_PropertyAttributeStateSectionName, objectID);

    PSS_SystemOption systemOption(iniFile, entityName);

    CString     keyName;
    CString     line;
    std::size_t index = 0;

    do
    {
        // format the key
        keyName.Format(_T("%s%d"), (const char*)g_PropertyAttributeStateEntityName, index);
        line = systemOption.ReadOption(keyName, _T(""));

        if (line.IsEmpty())
            break;

        ++index;

        systemOption.WriteOption(keyName, _T("0;0"));
    }
    // set the maximum loop at 1 million objects, which is enough
    while (index < 1000000);

    return true;
}
//---------------------------------------------------------------------------
void PSS_PropertyAttributes::RemoveAllAttributes()
{
    IAttributeIterator it(&m_AttributeSet);

    for (IAttribute* pAtt = it.GetFirst(); pAtt; pAtt = it.GetNext())
        delete pAtt;

    m_AttributeSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_PropertyAttributes::AddAttribute(IAttribute* pAttribute)
{
    if (pAttribute)
        if (!FindAttribute(pAttribute->GetCategoryID(), pAttribute->GetItemID()))
            m_AttributeSet.Add(pAttribute);
        else
            // otherwise delete the attribute
            delete pAttribute;
}
//---------------------------------------------------------------------------
void PSS_PropertyAttributes::AddAttributeAt(std::size_t index, IAttribute* pAttribute)
{
    if (pAttribute && index < GetAttributeCount())
    {
        if (!FindAttribute(pAttribute->GetCategoryID(), pAttribute->GetItemID()))
            m_AttributeSet.InsertAt(index, pAttribute);
        else
            delete pAttribute;
    }
    else
        AddAttribute(pAttribute);
}
//---------------------------------------------------------------------------
bool PSS_PropertyAttributes::DeleteAttribute(int categoryID, int itemID)
{
    IAttributeIterator it(&m_AttributeSet);

    for (IAttribute* pAtt = it.GetFirst(); pAtt; pAtt = it.GetNext())
        if (pAtt->GetCategoryID() == categoryID && pAtt->GetItemID() == itemID)
        {
            delete pAtt;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
void PSS_PropertyAttributes::DeleteCategoryAttribute(int categoryID)
{
    std::size_t count = GetAttributeCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        IAttribute* pAtt = GetAttributeAt(i);

        if (pAtt && pAtt->GetCategoryID() == categoryID)
        {
            delete pAtt;
            m_AttributeSet.RemoveAt(i);
            --i;
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_PropertyAttributes::DeleteAttributeAt(std::size_t index)
{
    IAttribute* pAtt = GetAttributeAt(index);

    if (pAtt)
    {
        delete pAtt;
        m_AttributeSet.RemoveAt(index);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
PSS_PropertyAttributes::IAttribute* PSS_PropertyAttributes::FindAttribute(int categoryID, int itemID)
{
    IAttributeIterator it(&m_AttributeSet);

    for (IAttribute* pAtt = it.GetFirst(); pAtt; pAtt = it.GetNext())
        if (pAtt->GetCategoryID() == categoryID && pAtt->GetItemID() == itemID)
            return pAtt;

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_PropertyAttributes::Match(PSS_Properties::IPropertySet& propAttributes,
                                   const CString&                argument,
                                   bool                          caseSensitive,
                                   bool                          partialSearch)
{
    PSS_Properties::IPropertyIterator it(&propAttributes);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        if (!FindAttribute(pProp->GetCategoryID(), pProp->GetItemID()))
            continue;

        CString value;

        // get the formatted value
        switch (pProp->GetValueType())
        {
            case PSS_Property::IE_VT_Double:   value = PSS_StringFormatter::GetFormattedBuffer(pProp->GetValueDouble(),                  pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_Float:    value = PSS_StringFormatter::GetFormattedBuffer(pProp->GetValueFloat(),                   pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_Date:     value = PSS_StringFormatter::GetFormattedBuffer((PSS_Date&)pProp->GetValueDate(),         pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_TimeSpan: value = PSS_StringFormatter::GetFormattedBuffer((PSS_TimeSpan&)pProp->GetValueTimeSpan(), pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_Duration: value = PSS_StringFormatter::GetFormattedBuffer((PSS_Duration&)pProp->GetValueDuration(), pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_String:   value = pProp->GetValueString();                                                                                     break;
            default:                                                                                                                                                break;
        }

        if (value.IsEmpty())
            continue;

        // do the value match only one part of the argument?
        if (partialSearch)
        {
            // is case sensitive?
            if (!caseSensitive)
            {
                // for non case sensitive search, transform the string to lowercase
                CString lowerArgument = argument;
                lowerArgument.MakeLower();

                CString lowerValue = value;
                lowerValue.MakeLower();

                // search for the matching argument and return the result
                if (lowerValue.Find(lowerArgument) != -1)
                    return true;
            }

            // search for the matching argument and return the result
            if (value.Find(argument) != -1)
                return true;
        }

        if (caseSensitive)
        {
            if (argument == value)
                return true;
        }
        else
        if (value.CompareNoCase(argument) == 0)
            return true;
    }

    // does not match
    return false;
}
//---------------------------------------------------------------------------
CString PSS_PropertyAttributes::GetString(PSS_Properties::IPropertySet* pPropAttributes, bool keepOnlyNotEmpty)
{
    if (!pPropAttributes)
        return _T("");

    PSS_Tokenizer                     token('\n');
    PSS_Properties::IPropertyIterator it(pPropAttributes);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        if (!FindAttribute(pProp->GetCategoryID(), pProp->GetItemID()))
            continue;

        CString value;
        CString format;

        if (GetShowTitleText())
        {
            format  = pProp->GetLabel();
            format += _T(": ");
        }

        // get the formatted value
        switch (pProp->GetValueType())
        {
            case PSS_Property::IE_VT_Double:   value += PSS_StringFormatter::GetFormattedBuffer(pProp->GetValueDouble(),                  pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_Float:    value += PSS_StringFormatter::GetFormattedBuffer(pProp->GetValueFloat(),                   pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_Date:     value += PSS_StringFormatter::GetFormattedBuffer((PSS_Date&)pProp->GetValueDate(),         pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_TimeSpan: value += PSS_StringFormatter::GetFormattedBuffer((PSS_TimeSpan&)pProp->GetValueTimeSpan(), pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_Duration: value += PSS_StringFormatter::GetFormattedBuffer((PSS_Duration&)pProp->GetValueDuration(), pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_String:   value += pProp->GetValueString();                                                                                     break;
            default:                                                                                                                                                 break;
        }

        if (value.IsEmpty() && keepOnlyNotEmpty)
            continue;

        token.AddToken(format + value);
    }

    return token.GetString();
}
//---------------------------------------------------------------------------
