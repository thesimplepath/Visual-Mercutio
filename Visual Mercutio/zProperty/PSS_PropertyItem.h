/****************************************************************************
 * ==> PSS_PropertyItem ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a property item                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertyItemH
#define PSS_PropertyItemH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\PSS_TypedPtrList.h"
#include "zBaseLib\PSS_SmartString.h"
#include "zBaseLib\PSS_StringFormat.h"
#include "zBaseLib\PSS_StringFormatter.h"
#include "zBaseLib\PSS_Duration.h"
#include "zBaseLib\PSS_Date.h"
#include "zBaseLib\PSS_TimeSpan.h"
#include "zProperty\PSS_InPlaceEdit.h"

#ifdef _ZPROPERTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// scope symbols in stingray foundation library
using namespace sfl;

/**
* Property item
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PropertyItem : public CObject
{
    DECLARE_DYNAMIC(PSS_PropertyItem)

    public:
        /**
        * Property item number type
        */
        enum class IENumberType
        {
            IE_NT_String,
            IE_NT_Double,
            IE_NT_Float,
            IE_NT_Date,
            IE_NT_Time,
            IE_NT_Duration
        };

        /**
        * Constructor
        *@param pName - the item name
        *@param isReadOnly - if true, the item will be read-only
        *@param canBeEdited - if true, the item can be edited
        */
        inline PSS_PropertyItem(LPCTSTR pName = NULL, bool isReadOnly = false, bool canBeEdited = true);

        virtual inline ~PSS_PropertyItem();

        /**
        * Gets the name
        *@return the name
        */
        virtual inline const CString& GetName() const;

        /**
        * Sets the name
        *@param pName - the name
        */
        virtual inline void SetName(LPCTSTR pName);

        /**
        * Gets if the item is enabled
        *@return true if the item is enabled, otherwise false
        */
        virtual inline bool GetEnabled() const;

        /**
        * Sets if the item is enabled
        *@param enabled - if true, the item will be enabled
        */
        virtual inline bool SetEnabled(bool enabled = true);

        /**
        * Gets if the item is read-only
        *@return true if the item is read-only, otherwise false
        */
        virtual inline bool IsReadOnly() const;

        /**
        * Gets if the item can be edited
        *@return true if the item can be edited, otherwise false
        */
        virtual inline bool CanBeEdited() const;

        /**
        * Gets if the item has changed
        *@return true if the item has changed, otherwise false
        */
        virtual inline bool GetHasChanged() const;

        /**
        * Sets if the item has changed
        *@param value - if true, the item has changed
        */
        virtual inline void SetHasChanged(bool value = true);

        /**
        * Gets the property item identifier
        *@return the property item identifier
        */
        virtual inline int GetPropertyID() const;

        /**
        * Sets the property item identifier
        *@param propID - the property item identifier
        */
        virtual inline void SetPropertyID(int propID);

        /**
        * Gets the size
        *@return the size
        */
        virtual inline CSize GetSize() const;

        /**
        * Sets the size
        *@param value - the size
        */
        virtual inline void SetSize(const CSize& value);

        /**
        * Gets the extended size
        *@return the extended size
        */
        virtual inline CSize GetExtendedSize() const;

        /**
        * Sets the extended size
        *@param value - the extended size
        */
        virtual inline void SetExtendedSize(const CSize& value);

        /**
        * Gets the save state
        *@return the save state
        */
        virtual inline bool GetSaveState() const;

        /**
        * Sets the save state
        *@param value - the save state
        */
        virtual inline void SetSaveState(bool value);

        /**
        * Gets the save state per property
        *@return the save state per property
        */
        virtual inline bool GetSaveStatePerProperty() const;

        /**
        * Sets the save state per property
        *@param value - the save state per property
        */
        virtual inline void SetSaveStatePerProperty(bool value);

        /**
        * Draws the value
        *@param pDc - device context to draw on
        *@param rect - the rect surrounding the value to draw
        */
        virtual void DrawValue(CDC* pDC, CRect& rect);

        /**
        * Creates an in-place control
        *@param pWndParent - the parent window
        *@param rect - the rectangle surrounding the control to create
        *@param[out] pWndInPlaceControl - the newly created in-place control window on function ends
        *@param extendedSize - the control extended size
        */
        virtual void CreateInPlaceControl(CWnd*             pWndParent,
                                          const CRect&      rect,
                                          PSS_InPlaceEdit*& pWndInPlaceControl,
                                          const CSize&      extendedSize = CSize(0, 0));

        /**
        * Deletes an in-place control
        *@param pWndInPlaceControl - the in-place control window to delete
        */
        virtual void DestroyInPlaceControl(PSS_InPlaceEdit*& pWndInPlaceControl);

        /**
        * Gets the data as a float value
        *@return the data as a float value
        */
        virtual inline float GetDataFloat() const;

        /**
        * Gets the data as a double value
        *@return the data as a double value
        */
        virtual inline double GetDataDouble() const;

        /**
        * Gets the data as a date value
        *@return the data as a date value
        */
        virtual inline PSS_Date GetDataDate() const;

        /**
        * Gets the data as a time value
        *@return the data as a time value
        */
        virtual inline PSS_TimeSpan GetDataTime() const;

        /**
        * Gets the data as a duration value
        *@return the data as a duration value
        */
        virtual inline PSS_Duration GetDataDuration() const;

        /**
        * Gets the data as a string value
        *@return the data as a string value
        */
        virtual inline CString GetData() const;

        /**
        * Sets the data
        *@param value - the data
        */
        virtual inline void SetData(float               value);
        virtual inline void SetData(double              value);
        virtual inline void SetData(const PSS_Date&     value);
        virtual inline void SetData(const PSS_TimeSpan& value);
        virtual inline void SetData(const PSS_Duration& value);
        virtual inline void SetData(const CString&      value);

        /**
        * Gets the data as a string value array
        *@param pValues - the string value array to fill with the result
        */
        virtual inline void GetData(CStringArray* pValues) const;

        /**
        * Sets the data from a string value array
        *@param pValues - the string value array containing the data
        */
        virtual inline void SetData(CStringArray* pValues);

        /**
        * Gets the string format
        *@return the string format
        */
        virtual inline PSS_StringFormat& GetStringFormat();

        /**
        * Sets the string format
        *@param value - the string format
        */
        virtual inline void SetStringFormat(const PSS_StringFormat& value);

        /**
        * Checks if the drag&drop is enabled
        *@return true if the drag&drop is enabled, otherwise false
        */
        virtual inline bool IsDragNDropEnabled() const;

        /**
        * Enables the drag&drop
        *@param value - if true, the drag&drop is enabled
        */
        virtual inline void EnableDragNDrop(bool value = true);

        /**
        * Gets the category order
        *@return the category order
        */
        virtual inline int GetCategoryOrder() const;

        /**
        * Sets the category order
        *@param value - the category order
        */
        virtual inline void SetCategoryOrder(int value);

        /**
        * Gets the item order
        *@return the item order
        */
        virtual inline int GetItemOrder() const;

        /**
        * Sets the item order
        *@param value - the item order
        */
        virtual inline void SetItemOrder(int value);

    protected:
        IENumberType m_Type;
        CString      m_StrValue;
        PSS_Date     m_DateValue;
        PSS_TimeSpan m_TimeValue;
        PSS_Duration m_DurationValue;
        double       m_DoubleValue;
        float        m_FloatValue;

    private:
        PSS_StringFormat m_Format;
        CString          m_Name;
        CSize            m_Size;
        CSize            m_ExtendedSize;
        int              m_PropertyID;
        int              m_CategoryOrder;
        int              m_ItemOrder;
        bool             m_Enabled;
        bool             m_ReadOnly;
        bool             m_CanBeEdited;
        bool             m_HasChanged;
        bool             m_SaveState;
        bool             m_SaveStatePerProperty;
        bool             m_DragNDropEnabled;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PropertyItem(const PSS_PropertyItem& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_PropertyItem& operator = (const PSS_PropertyItem& other);
};

//---------------------------------------------------------------------------
// PSS_PropertyItem
//---------------------------------------------------------------------------
PSS_PropertyItem::PSS_PropertyItem(LPCTSTR pName, bool readOnly, bool canBeEdited) :
    CObject(),
    m_Type(IENumberType::IE_NT_String),
    m_DoubleValue(0.0),
    m_FloatValue(0.0f),
    m_Name(pName ? pName : _T("")),
    m_PropertyID(0),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Enabled(true),
    m_ReadOnly(readOnly),
    m_CanBeEdited(canBeEdited),
    m_HasChanged(false),
    m_SaveState(true),
    m_SaveStatePerProperty(true),
    m_DragNDropEnabled(false)
{}
//---------------------------------------------------------------------------
PSS_PropertyItem::~PSS_PropertyItem()
{}
//---------------------------------------------------------------------------
const CString& PSS_PropertyItem::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetName(LPCTSTR pName)
{
    m_Name = (pName ? pName : _T(""));
}
//---------------------------------------------------------------------------
bool PSS_PropertyItem::GetEnabled() const
{
    return m_Enabled;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItem::SetEnabled(bool enabled)
{
    const bool changed = (m_Enabled != enabled);
    m_Enabled          =  enabled;

    return changed;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItem::IsReadOnly() const
{
    return m_ReadOnly;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItem::CanBeEdited() const
{
    return m_CanBeEdited;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItem::GetHasChanged() const
{
    return m_HasChanged;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetHasChanged(bool value)
{
    m_HasChanged = value;
}
//---------------------------------------------------------------------------
int PSS_PropertyItem::GetPropertyID() const
{
    return m_PropertyID;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetPropertyID(int nPropertyID)
{
    m_PropertyID = nPropertyID;
}
//---------------------------------------------------------------------------
CSize PSS_PropertyItem::GetSize() const
{
    return m_Size;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetSize(const CSize& value)
{
    m_Size = value;
}
//---------------------------------------------------------------------------
CSize PSS_PropertyItem::GetExtendedSize() const
{
    return m_ExtendedSize;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetExtendedSize(const CSize& value)
{
    m_ExtendedSize = value;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItem::GetSaveState() const
{
    return m_SaveState;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetSaveState(bool value)
{
    m_SaveState = value;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItem::GetSaveStatePerProperty() const
{
    return m_SaveStatePerProperty;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetSaveStatePerProperty(bool value)
{
    m_SaveStatePerProperty = value;
}
//---------------------------------------------------------------------------
float PSS_PropertyItem::GetDataFloat() const
{
    return m_FloatValue;
}
//---------------------------------------------------------------------------
double PSS_PropertyItem::GetDataDouble() const
{
    return m_DoubleValue;
}
//---------------------------------------------------------------------------
PSS_Date PSS_PropertyItem::GetDataDate() const
{
    return m_DateValue;
}
//---------------------------------------------------------------------------
PSS_TimeSpan PSS_PropertyItem::GetDataTime() const
{
    return m_TimeValue;
}
//---------------------------------------------------------------------------
PSS_Duration PSS_PropertyItem::GetDataDuration() const
{
    return m_DurationValue;
}
//---------------------------------------------------------------------------
CString PSS_PropertyItem::GetData() const
{
    CString text;

    switch (m_Type)
    {
        case IENumberType::IE_NT_String:
            return m_StrValue;

        case IENumberType::IE_NT_Double:
            // convert the value to a string using the specified format
            text = PSS_StringFormatter::GetFormattedBuffer(m_DoubleValue,
                                                           const_cast<PSS_PropertyItem*>(this)->GetStringFormat());
            break;

        case IENumberType::IE_NT_Float:
            // convert the value to a string using the specified format
            text = PSS_StringFormatter::GetFormattedBuffer(m_FloatValue,
                                                           const_cast<PSS_PropertyItem*>(this)->GetStringFormat());
            break;

        case IENumberType::IE_NT_Duration:
            // convert the value to a string using the specified format
            text = PSS_StringFormatter::GetFormattedBuffer((PSS_Duration&)m_DurationValue,
                                                           const_cast<PSS_PropertyItem*>(this)->GetStringFormat());
            break;

        case IENumberType::IE_NT_Date:
            // convert the value to a string using the specified format
            text = PSS_StringFormatter::GetFormattedBuffer((PSS_Date&)m_DateValue,
                                                           const_cast<PSS_PropertyItem*>(this)->GetStringFormat());
            break;

        case IENumberType::IE_NT_Time:
            // convert the value to a string using the specified format
            text = PSS_StringFormatter::GetFormattedBuffer((PSS_TimeSpan&)m_TimeValue,
                                                           const_cast<PSS_PropertyItem*>(this)->GetStringFormat());
            break;
    }

    return text;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetData(float value)
{
    m_Type       = IENumberType::IE_NT_Float;
    m_FloatValue = value;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetData(double value)
{
    m_Type        = IENumberType::IE_NT_Double;
    m_DoubleValue = value;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetData(const PSS_Date& value)
{
    m_Type      = IENumberType::IE_NT_Date;
    m_DateValue = value;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetData(const PSS_TimeSpan& value)
{
    m_Type      = IENumberType::IE_NT_Time;
    m_TimeValue = value;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetData(const PSS_Duration& value)
{
    m_Type          = IENumberType::IE_NT_Duration;
    m_DurationValue = value;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetData(const CString& text)
{
    switch (m_Type)
    {
        case IENumberType::IE_NT_String:
            m_StrValue = text;
            break;

        case IENumberType::IE_NT_Double:
        {
            double value;

            if (PSS_StringFormatter::ConvertFormattedBuffer(text, value, GetStringFormat()))
                m_DoubleValue = value;

            break;

        }

        case IENumberType::IE_NT_Float:
        {
            float value;

            if (PSS_StringFormatter::ConvertFormattedBuffer(text, value, GetStringFormat()))
                m_FloatValue = value;

            break;
        }

        case IENumberType::IE_NT_Duration:
        {
            PSS_Duration value;

            if (PSS_StringFormatter::ConvertFormattedBuffer(text, (PSS_Duration&)value, GetStringFormat()))
                m_DurationValue = value;

            break;
        }

        case IENumberType::IE_NT_Date:
        {
            PSS_Date value;

            if (PSS_StringFormatter::ConvertFormattedBuffer(text, (PSS_Date&)value, GetStringFormat()))
                m_DateValue = value;

            break;
        }

        case IENumberType::IE_NT_Time:
        {
            PSS_TimeSpan value;

            if (PSS_StringFormatter::ConvertFormattedBuffer(text, (PSS_TimeSpan&)value, GetStringFormat()))
                m_TimeValue = value;

            break;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::GetData(CStringArray* pValues) const
{}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetData(CStringArray* pValues)
{}
//---------------------------------------------------------------------------
PSS_StringFormat& PSS_PropertyItem::GetStringFormat()
{
    return m_Format;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetStringFormat(const PSS_StringFormat& value)
{
    m_Format = value;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItem::IsDragNDropEnabled() const
{
    return m_DragNDropEnabled;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::EnableDragNDrop(bool value)
{
    m_DragNDropEnabled = value;
}
//---------------------------------------------------------------------------
int PSS_PropertyItem::GetCategoryOrder() const
{
    return m_CategoryOrder;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetCategoryOrder(int value)
{
    m_CategoryOrder = value;
}
//---------------------------------------------------------------------------
int PSS_PropertyItem::GetItemOrder() const
{
    return m_ItemOrder;
}
//---------------------------------------------------------------------------
void PSS_PropertyItem::SetItemOrder(int value)
{
    m_ItemOrder = value;
}
//---------------------------------------------------------------------------

/**
* Property item category
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PropertyItemCategory : public PSS_PropertyItem
{
    DECLARE_DYNAMIC(PSS_PropertyItemCategory)

    public:
        typedef CCArray_T <PSS_PropertyItem*, PSS_PropertyItem*> IPropertyItemSet;
        typedef Iterator_T<PSS_PropertyItem*>                    IPropertyItemIterator;

        /**
        * Constructor
        *@param pName - the property name
        *@param isReadOnly - if true, the property will be read-only
        *@param canBeEdited - if true, the property can be edited
        */
        inline PSS_PropertyItemCategory(LPCTSTR pName = NULL, bool isReadOnly = false, bool canBeEdited = true);

        virtual inline ~PSS_PropertyItemCategory();

        /**
        * Adds a property item
        *@param pPropertyItem - the property item to add
        */
        virtual inline void AddPropertyItem(PSS_PropertyItem* pPropertyItem);

        /**
        * Checks if a property item exists
        *@param propID - the property identifier
        *@return true if the property item exists, otherwise false
        */
        virtual inline bool PropertyItemExist(int propID);

        /**
        * Checks if a property item exists
        *@param pItemName - the item name
        *@return true if the property item exists, otherwise false
        */
        virtual inline bool PropertyItemExist(LPCTSTR pItemName);

        /**
        * Checks if a property item exists
        *@param pPropertyItem - the property item to find
        *@return true if the property item exists, otherwise false
        */
        virtual bool PropertyItemExist(PSS_PropertyItem* pPropertyItem);

        /**
        * Gets if the children are visible
        *@return true if the children are visible, otherwise false
        */
        virtual inline bool GetChildrenVisible() const;

        /**
        * Sets the children as visible
        *@param visible - if true, the children are visible
        */
        virtual inline void SetChildrenVisible(bool visible = true);

        /**
        * Gets the item number
        *@return the item number
        */
        virtual inline int GetItemNumber() const;

        /**
        * Gets the enabled item number
        *@return the enabled item number
        */
        virtual int GetEnabledItemNumber() const;

        /**
        * Gets the property item
        *@param propID - the property item identifier
        *@return the property item, NULL if not found or on error
        */
        virtual PSS_PropertyItem* GetPropertyItem(int propID);

        /**
        * Gets the property item
        *@param pItemName - the property item name
        *@return the property item, NULL if not found or on error
        */
        virtual PSS_PropertyItem* GetPropertyItem(LPCTSTR pItemName);

        /**
        * Gets the property item set
        *@return the property item set
        */
        virtual inline       IPropertyItemSet& GetPropertyItemSet();
        virtual inline const IPropertyItemSet& GetPropertyItemSet() const;

        /**
        * Removes all the property items
        */
        void RemoveAllPropertyItems();

    private:
        IPropertyItemSet m_PropertyItemSet;
        bool             m_ChildrenVisible;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PropertyItemCategory(const PSS_PropertyItemCategory& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_PropertyItemCategory& operator = (const PSS_PropertyItemCategory& other);
};

//---------------------------------------------------------------------------
// PSS_PropertyItemCategory
//---------------------------------------------------------------------------
PSS_PropertyItemCategory::PSS_PropertyItemCategory(LPCTSTR pName, bool readOnly, bool canBeEdited) :
    PSS_PropertyItem(pName, readOnly, canBeEdited),
    m_ChildrenVisible(false)
{}
//---------------------------------------------------------------------------
PSS_PropertyItemCategory::~PSS_PropertyItemCategory()
{
    // NOTE use the fully qualified name here to avoid to call a pure virtual function on destruction
    PSS_PropertyItemCategory::RemoveAllPropertyItems();
}
//---------------------------------------------------------------------------
void PSS_PropertyItemCategory::AddPropertyItem(PSS_PropertyItem* pPropertyItem)
{
    m_PropertyItemSet.Add(pPropertyItem);
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemCategory::PropertyItemExist(int propID)
{
    return GetPropertyItem(propID);
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemCategory::PropertyItemExist(LPCTSTR pItemName)
{
    return GetPropertyItem(pItemName);
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemCategory::GetChildrenVisible() const
{
    return m_ChildrenVisible;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemCategory::SetChildrenVisible(bool visible)
{
    m_ChildrenVisible = visible;
}
//---------------------------------------------------------------------------
int PSS_PropertyItemCategory::GetItemNumber() const
{
    return m_PropertyItemSet.GetSize();
}
//---------------------------------------------------------------------------
PSS_PropertyItemCategory::IPropertyItemSet& PSS_PropertyItemCategory::GetPropertyItemSet()
{
    return m_PropertyItemSet;
}
//---------------------------------------------------------------------------
const PSS_PropertyItemCategory::IPropertyItemSet& PSS_PropertyItemCategory::GetPropertyItemSet() const
{
    return m_PropertyItemSet;
}
//---------------------------------------------------------------------------

#endif
