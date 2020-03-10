/****************************************************************************
 * ==> PSS_Property --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a property                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_Property.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_Property, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_Property
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const CString&    category,
                           int               categoryID,
                           const CString&    label,
                           int               itemID,
                           const CString&    description,
                           const CString&    value,
                           IEType            type,
                           bool              enabled,
                           PSS_StringFormat& format,
                           CStringArray*     pValueArray,
                           CMenu*            pMenu,
                           bool              saveState,
                           bool              saveStatePerProperty) :
    CObject(),
    m_pValueArray(pValueArray),
    m_pMenu(pMenu),
    m_Type(type),
    m_ValueType(IE_VT_Unknown),
    m_Format(format),
    m_Category(category),
    m_Label(label),
    m_Description(description),
    m_CategoryID(categoryID),
    m_ItemID(itemID),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(enabled),
    m_HasChanged(false),
    m_SaveState(saveState),
    m_SaveStatePerProperty(saveStatePerProperty),
    m_EnableDragNDrop(false)
{
    SetValueString(value);
}
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const UINT        categoryResID,
                           int               categoryID,
                           const UINT        labelResID,
                           int               itemID,
                           const UINT        descriptionResID,
                           const CString&    value,
                           IEType            type,
                           bool              enabled,
                           PSS_StringFormat& format,
                           CStringArray*     pValueArray,
                           CMenu*            pMenu,
                           bool              saveState,
                           bool              saveStatePerProperty) :
    CObject(),
    m_pValueArray(pValueArray),
    m_pMenu(pMenu),
    m_Type(type),
    m_ValueType(IE_VT_Unknown),
    m_Format(format),
    m_CategoryID(categoryID),
    m_ItemID(itemID),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(enabled),
    m_HasChanged(false),
    m_SaveState(saveState),
    m_SaveStatePerProperty(saveStatePerProperty),
    m_EnableDragNDrop(false)
{
    m_Category.LoadString(categoryResID);
    m_Label.LoadString(labelResID);
    m_Description.LoadString(descriptionResID);

    SetValueString(value);
}
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const CString&    category,
                           int               categoryID,
                           const CString&    label,
                           int               itemID,
                           const CString&    description,
                           double            value,
                           IEType            type,
                           bool              enabled,
                           PSS_StringFormat& format,
                           CStringArray*     pValueArray,
                           CMenu*            pMenu,
                           bool              saveState,
                           bool              saveStatePerProperty) :
    CObject(),
    m_pValueArray(pValueArray),
    m_pMenu(pMenu),
    m_Type(type),
    m_ValueType(IE_VT_Unknown),
    m_Format(format),
    m_Category(category),
    m_Label(label),
    m_Description(description),
    m_CategoryID(categoryID),
    m_ItemID(itemID),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(enabled),
    m_HasChanged(false),
    m_SaveState(saveState),
    m_SaveStatePerProperty(saveStatePerProperty),
    m_EnableDragNDrop(false)
{
    SetValueDouble(value);
}
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const UINT        categoryResID,
                           int               categoryID,
                           const UINT        labelResID,
                           int               itemID,
                           const UINT        descriptionResID,
                           double            value,
                           IEType            type,
                           bool              enabled,
                           PSS_StringFormat& format,
                           CStringArray*     pValueArray,
                           CMenu*            pMenu,
                           bool              saveState,
                           bool              saveStatePerProperty) :
    CObject(),
    m_pValueArray(pValueArray),
    m_pMenu(pMenu),
    m_Type(type),
    m_ValueType(IE_VT_Unknown),
    m_Format(format),
    m_CategoryID(categoryID),
    m_ItemID(itemID),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(enabled),
    m_HasChanged(false),
    m_SaveState(saveState),
    m_SaveStatePerProperty(saveStatePerProperty),
    m_EnableDragNDrop(false)
{
    m_Category.LoadString(categoryResID);
    m_Label.LoadString(labelResID);
    m_Description.LoadString(descriptionResID);

    SetValueDouble(value);
}
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const CString&    category,
                           int               categoryID,
                           const CString&    label,
                           int               itemID,
                           const CString&    description,
                           float             value,
                           IEType            type,
                           bool              enabled,
                           PSS_StringFormat& format,
                           CStringArray*     pValueArray,
                           CMenu*            pMenu,
                           bool              saveState,
                           bool              saveStatePerProperty) :
    CObject(),
    m_pValueArray(pValueArray),
    m_pMenu(pMenu),
    m_Type(type),
    m_ValueType(IE_VT_Unknown),
    m_Format(format),
    m_Category(category),
    m_Label(label),
    m_Description(description),
    m_CategoryID(categoryID),
    m_ItemID(itemID),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(enabled),
    m_HasChanged(false),
    m_SaveState(saveState),
    m_SaveStatePerProperty(saveStatePerProperty),
    m_EnableDragNDrop(false)
{
    SetValueFloat(value);
}
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const UINT        categoryResID,
                           int               categoryID,
                           const UINT        labelResID,
                           int               itemID,
                           const UINT        descriptionResID,
                           float             value,
                           IEType            type,
                           bool              enabled,
                           PSS_StringFormat& format,
                           CStringArray*     pValueArray,
                           CMenu*            pMenu,
                           bool              saveState,
                           bool              saveStatePerProperty) :
    CObject(),
    m_pValueArray(pValueArray),
    m_pMenu(pMenu),
    m_Type(type),
    m_ValueType(IE_VT_Unknown),
    m_Format(format),
    m_CategoryID(categoryID),
    m_ItemID(itemID),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(enabled),
    m_HasChanged(false),
    m_SaveState(saveState),
    m_SaveStatePerProperty(saveStatePerProperty),
    m_EnableDragNDrop(false)
{
    m_Category.LoadString(categoryResID);
    m_Label.LoadString(labelResID);
    m_Description.LoadString(descriptionResID);

    SetValueFloat(value);
}
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const CString&    category,
                           int               categoryID,
                           const CString&    label,
                           int               itemID,
                           const CString&    description,
                           PSS_Date&         value,
                           IEType            type,
                           bool              enabled,
                           PSS_StringFormat& format,
                           CStringArray*     pValueArray,
                           CMenu*            pMenu,
                           bool              saveState,
                           bool              saveStatePerProperty) :
    CObject(),
    m_pValueArray(pValueArray),
    m_pMenu(pMenu),
    m_Type(type),
    m_ValueType(IE_VT_Unknown),
    m_Format(format),
    m_Category(category),
    m_Label(label),
    m_Description(description),
    m_CategoryID(categoryID),
    m_ItemID(itemID),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(enabled),
    m_HasChanged(false),
    m_SaveState(saveState),
    m_SaveStatePerProperty(saveStatePerProperty),
    m_EnableDragNDrop(false)
{
    SetValueDate(value);
}
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const UINT        categoryResID,
                           int               categoryID,
                           const UINT        labelResID,
                           int               itemID,
                           const UINT        descriptionResID,
                           PSS_Date&         value,
                           IEType            type,
                           bool              enabled,
                           PSS_StringFormat& format,
                           CStringArray*     pValueArray,
                           CMenu*            pMenu,
                           bool              saveState,
                           bool              saveStatePerProperty) :
    CObject(),
    m_pValueArray(pValueArray),
    m_pMenu(pMenu),
    m_Type(type),
    m_ValueType(IE_VT_Unknown),
    m_Format(format),
    m_CategoryID(categoryID),
    m_ItemID(itemID),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(enabled),
    m_HasChanged(false),
    m_SaveState(saveState),
    m_SaveStatePerProperty(saveStatePerProperty),
    m_EnableDragNDrop(false)
{
    m_Category.LoadString(categoryResID);
    m_Label.LoadString(labelResID);
    m_Description.LoadString(descriptionResID);

    SetValueDate(value);
}
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const CString     category,
                           int               categoryID,
                           const CString     label,
                           int               itemID,
                           const CString     description,
                           PSS_TimeSpan&     value,
                           IEType            type,
                           bool              enabled,
                           PSS_StringFormat& format,
                           CStringArray*     pValueArray,
                           CMenu*            pMenu,
                           bool              saveState,
                           bool              saveStatePerProperty) :
    CObject(),
    m_pValueArray(pValueArray),
    m_pMenu(pMenu),
    m_Type(type),
    m_ValueType(IE_VT_Unknown),
    m_Format(format),
    m_Category(category),
    m_Label(label),
    m_Description(description),
    m_CategoryID(categoryID),
    m_ItemID(itemID),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(enabled),
    m_HasChanged(false),
    m_SaveState(saveState),
    m_SaveStatePerProperty(saveStatePerProperty),
    m_EnableDragNDrop(false)
{
    SetValueTimeSpan(value);
}
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const UINT        categoryResID,
                           int               categoryID,
                           const UINT        labelResID,
                           int               itemID,
                           const UINT        descriptionResID,
                           PSS_TimeSpan&     value,
                           IEType            type,
                           bool              enabled,
                           PSS_StringFormat& format,
                           CStringArray*     pValueArray,
                           CMenu*            pMenu,
                           bool              saveState,
                           bool              saveStatePerProperty) :
    CObject(),
    m_pValueArray(pValueArray),
    m_pMenu(pMenu),
    m_Type(type),
    m_ValueType(IE_VT_Unknown),
    m_Format(format),
    m_CategoryID(categoryID),
    m_ItemID(itemID),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(enabled),
    m_HasChanged(false),
    m_SaveState(saveState),
    m_SaveStatePerProperty(saveStatePerProperty),
    m_EnableDragNDrop(false)
{
    m_Category.LoadString(categoryResID);
    m_Label.LoadString(labelResID);
    m_Description.LoadString(descriptionResID);

    SetValueTimeSpan(value);
}
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const CString&    category,
                           int               categoryID,
                           const CString&    label,
                           int               itemID,
                           const CString&    description,
                           PSS_Duration&     value,
                           IEType            type,
                           bool              enabled,
                           PSS_StringFormat& format,
                           CStringArray*     pValueArray,
                           CMenu*            pMenu,
                           bool              saveState,
                           bool              saveStatePerProperty) :
    CObject(),
    m_pValueArray(pValueArray),
    m_pMenu(pMenu),
    m_Type(type),
    m_ValueType(IE_VT_Unknown),
    m_Format(format),
    m_Category(category),
    m_Label(label),
    m_Description(description),
    m_CategoryID(categoryID),
    m_ItemID(itemID),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(enabled),
    m_HasChanged(false),
    m_SaveState(saveState),
    m_SaveStatePerProperty(saveStatePerProperty),
    m_EnableDragNDrop(false)
{
    SetValueDuration(value);
}
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const UINT        categoryResID,
                           int               categoryID,
                           const UINT        labelResID,
                           int               itemID,
                           const UINT        descriptionResID,
                           PSS_Duration&     value,
                           IEType            type,
                           bool              enabled,
                           PSS_StringFormat& format,
                           CStringArray*     pValueArray,
                           CMenu*            pMenu,
                           bool              saveState,
                           bool              saveStatePerProperty) :
    CObject(),
    m_pValueArray(pValueArray),
    m_pMenu(pMenu),
    m_Type(type),
    m_ValueType(IE_VT_Unknown),
    m_Format(format),
    m_CategoryID(categoryID),
    m_ItemID(itemID),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(enabled),
    m_HasChanged(false),
    m_SaveState(saveState),
    m_SaveStatePerProperty(saveStatePerProperty),
    m_EnableDragNDrop(false)
{
    m_Category.LoadString(categoryResID);
    m_Label.LoadString(labelResID);
    m_Description.LoadString(descriptionResID);

    SetValueDuration(value);
}
//---------------------------------------------------------------------------
PSS_Property::~PSS_Property()
{
    if (m_pMenu)
        m_pMenu->DestroyMenu();

    m_Category.Empty();
    m_Label.Empty();
    m_Description.Empty();
    m_StrValue.Empty();

    m_Format.Release();
}
//---------------------------------------------------------------------------
PSS_Property& PSS_Property::operator = (const PSS_Property& other)
{
    m_pValueArray          = other.m_pValueArray;
    m_pMenu                = other.m_pMenu;
    m_Type                 = other.m_Type;
    m_ValueType            = other.m_ValueType;
    m_Format               = other.m_Format;
    m_DateValue            = other.m_DateValue;
    m_TimeSpanValue        = other.m_TimeSpanValue;
    m_DurationValue        = other.m_DurationValue;
    m_Category             = other.m_Category;
    m_Label                = other.m_Label;
    m_Description          = other.m_Description;
    m_StrValue             = other.m_StrValue;
    m_DoubleValue          = other.m_DoubleValue;
    m_FloatValue           = other.m_FloatValue;
    m_CategoryID           = other.m_CategoryID;
    m_ItemID               = other.m_ItemID;
    m_CategoryOrder        = other.m_CategoryOrder;
    m_ItemOrder            = other.m_ItemOrder;
    m_Dynamic              = other.m_Dynamic;
    m_Enabled              = other.m_Enabled;
    m_HasChanged           = other.m_HasChanged;
    m_SaveState            = other.m_SaveState;
    m_SaveStatePerProperty = other.m_SaveStatePerProperty;
    m_EnableDragNDrop      = other.m_EnableDragNDrop;

    return *this;
}
//---------------------------------------------------------------------------
void PSS_Property::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar << m_Category;
        ar << m_CategoryID;
        ar << int(m_Dynamic);
        ar << m_Label;
        ar << m_ItemID;
        ar << m_Description;
        ar << int(m_ValueType);

        // serialize the values
        ar << m_StrValue;
        ar << m_DoubleValue;
        ar << m_FloatValue;
        ar << m_DateValue;
        ar << m_TimeSpanValue;

        // serialize the duration
        ar << double(m_DurationValue);
        ar << int(m_DurationValue.GetStatus());

        ar << int(m_Type);
        ar << int(m_Enabled);

        m_Format.Serialize(ar);

        ar << m_pValueArray;

        ar << int(m_HasChanged);

        ar << int(m_SaveState);
        ar << int(m_SaveStatePerProperty);

        ar << int(m_EnableDragNDrop);

        ar << m_ItemOrder;
        ar << m_CategoryOrder;
    }
    else
    {
        ar >> m_Category;
        ar >> m_CategoryID;

        int value;
        ar >> value;
        m_Dynamic = (value == 1);

        ar >> m_Label;
        ar >> m_ItemID;
        ar >> m_Description;
        ar >> value;
        m_ValueType = IEValueType(value);

        ar >> m_StrValue;
        ar >> m_DoubleValue;
        ar >> m_FloatValue;
        ar >> m_DateValue;
        ar >> m_TimeSpanValue;

        // deserialize the duration
        double duration;
        ar >> duration;
        m_DurationValue.SetSpan(duration);

        ar >> value;
        m_DurationValue.SetStatus(PSS_Duration::IEStatus(value));

        ar >> value;
        m_Type = IEType(value);

        ar >> value;
        m_Enabled = (value == 1);

        m_Format.Serialize(ar);

        ar >> m_pValueArray;

        ar >> value;
        m_HasChanged = (value == 1);

        ar >> value;
        m_SaveState = (value == 1);

        ar >> value;
        m_SaveStatePerProperty = (value == 1);

        ar >> value;
        m_EnableDragNDrop = (value == 1);

        ar >> m_ItemOrder;
        ar >> m_CategoryOrder;
    }
}
//---------------------------------------------------------------------------
