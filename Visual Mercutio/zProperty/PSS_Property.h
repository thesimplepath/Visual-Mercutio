/****************************************************************************
 * ==> PSS_Property --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a property                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertyH
#define PSS_PropertyH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_Property
    #define PSS_Property ZBProperty
#endif

// processsoft
#include "zBaseLib\PSS_StringFormat.h"
#include "zBaseLib\PSS_Date.h"
#include "zBaseLib\PSS_TimeSpan.h"
#include "zBaseLib\PSS_Duration.h"

#ifdef _ZPROPERTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Property
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Property : public CObject
{
    DECLARE_SERIAL(PSS_Property)

    public:
        /**
        * The property type
        */
        enum IEType
        {
            IE_T_EditString,
            IE_T_EditStringReadOnly,
            IE_T_EditDate,
            IE_T_EditDateReadOnly,
            IE_T_EditTime,
            IE_T_EditTimeReadOnly,
            IE_T_EditDuration,
            IE_T_EditDurationReadOnly,
            IE_T_EditNumber,
            IE_T_EditNumberReadOnly,
            IE_T_EditMenu,
            IE_T_EditMenuReadOnly,
            IE_T_EditIntelli,
            IE_T_EditIntelliReadOnly,
            IE_T_EditMultiline,
            IE_T_EditMultilineReadOnly,
            IE_T_ComboString,
            IE_T_ComboStringReadOnly,
            IE_T_ComboNumber,
            IE_T_ComboNumberReadOnly,
            IE_T_EditFont,
            IE_T_EditFile,
            IE_T_EditDirectory,
            IE_T_EditMultiFiles,
            IE_T_EditMultiDirectories,
            IE_T_EditExtended,
            IE_T_EditExtendedReadOnly
        };

        /**
        * Property value type
        */
        enum IEValueType
        {
            IE_VT_Unknown,
            IE_VT_String,
            IE_VT_Double,
            IE_VT_Float,
            IE_VT_Date,
            IE_VT_TimeSpan,
            IE_VT_Duration
        };

        /**
        * Constructor
        *@param category - the category
        *@param categoryID - the category identifier
        *@param label - the label
        *@param itemID - the item identifier
        *@param description - the description
        *@param value - the value
        *@param type - the value type
        *@param enabled - if true, the property will be enabled, disabled otherwise
        *@param format - the string format
        *@param pValueArray - the value array
        *@param pMenu - the context popup menu
        *@param saveState - if true, the state may be saved
        *@param saveStatePerProperty - if true, the state will be saved per property
        *@note The pValueArray is kept as a reference to the source array, and will not be deleted internally.
        *      This array should be deleted by the owner
        */
        PSS_Property(const CString&    category             =  _T(""),
                     int               categoryID           = -1,
                     const CString&    label                =  _T(""),
                     int               itemID               = -1,
                     const CString&    description          =  _T(""),
                     const CString&    value                =  _T(""),
                     IEType            type                 =  IE_T_EditString,
                     bool              enabled              =  true,
                     PSS_StringFormat& format               =  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                     CStringArray*     pValueArray          =  NULL,
                     CMenu*            pMenu                =  NULL,
                     bool              saveState            =  true,
                     bool              saveStatePerProperty =  true);

        /**
        * Constructor
        *@param categoryResID - the category resource identifier
        *@param categoryID - the category identifier
        *@param labelResID - the label resource identifier
        *@param itemID - the item identifier
        *@param descriptionResID - the description resource identifier
        *@param value - the value
        *@param type - the value type
        *@param enabled - if true, the property will be enabled, disabled otherwise
        *@param format - the string format
        *@param pValueArray - the value array
        *@param pMenu - the context popup menu
        *@param saveState - if true, the state may be saved
        *@param saveStatePerProperty - if true, the state will be saved per property
        *@note The pValueArray is kept as a reference to the source array, and will not be deleted internally.
        *      This array should be deleted by the owner
        */
        PSS_Property(const UINT        categoryResID,
                     int               categoryID,
                     const UINT        labelResID,
                     int               itemID,
                     const UINT        descriptionResID,
                     const CString&    value,
                     IEType            type                 = IE_T_EditString,
                     bool              enabled              = true,
                     PSS_StringFormat& format               = PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                     CStringArray*     pValueArray          = NULL,
                     CMenu*            pMenu                = NULL,
                     bool              saveState            = true,
                     bool              saveStatePerProperty = true);

        /**
        * Constructor
        *@param category - the category
        *@param categoryID - the category identifier
        *@param label - the label
        *@param itemID - the item identifier
        *@param description - the description
        *@param value - the value
        *@param type - the value type
        *@param enabled - if true, the property will be enabled, disabled otherwise
        *@param format - the string format
        *@param pValueArray - the value array
        *@param pMenu - the context popup menu
        *@param saveState - if true, the state may be saved
        *@param saveStatePerProperty - if true, the state will be saved per property
        *@note The pValueArray is kept as a reference to the source array, and will not be deleted internally.
        *      This array should be deleted by the owner
        */
        PSS_Property(const CString&    category,
                     int               categoryID,
                     const CString&    label,
                     int               itemID,
                     const CString&    description,
                     double            value,
                     IEType            type                 = IE_T_EditNumber,
                     bool              enabled              = true,
                     PSS_StringFormat& format               = PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                     CStringArray*     pValueArray          = NULL,
                     CMenu*            pMenu                = NULL,
                     bool              saveState            = true,
                     bool              saveStatePerProperty = true);

        /**
        * Constructor
        *@param categoryResID - the category resource identifier
        *@param categoryID - the category identifier
        *@param labelResID - the label resource identifier
        *@param itemID - the item identifier
        *@param descriptionResID - the description resource identifier
        *@param value - the value
        *@param type - the value type
        *@param enabled - if true, the property will be enabled, disabled otherwise
        *@param format - the string format
        *@param pValueArray - the value array
        *@param pMenu - the context popup menu
        *@param saveState - if true, the state may be saved
        *@param saveStatePerProperty - if true, the state will be saved per property
        *@note The pValueArray is kept as a reference to the source array, and will not be deleted internally.
        *      This array should be deleted by the owner
        */
        PSS_Property(const UINT        categoryResID,
                     int               categoryID,
                     const UINT        labelResID,
                     int               itemID,
                     const UINT        descriptionResID,
                     double            value,
                     IEType            type                 = IE_T_EditNumber,
                     bool              enabled              = true,
                     PSS_StringFormat& format               = PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                     CStringArray*     pValueArray          = NULL,
                     CMenu*            pMenu                = NULL,
                     bool              saveState            = true,
                     bool              saveStatePerProperty = true);

        /**
        * Constructor
        *@param category - the category
        *@param categoryID - the category identifier
        *@param label - the label
        *@param itemID - the item identifier
        *@param description - the description
        *@param value - the value
        *@param type - the value type
        *@param enabled - if true, the property will be enabled, disabled otherwise
        *@param format - the string format
        *@param pValueArray - the value array
        *@param pMenu - the context popup menu
        *@param saveState - if true, the state may be saved
        *@param saveStatePerProperty - if true, the state will be saved per property
        *@note The pValueArray is kept as a reference to the source array, and will not be deleted internally.
        *      This array should be deleted by the owner
        */
        PSS_Property(const CString&    category,
                     int               categoryID,
                     const CString&    label,
                     int               itemID,
                     const CString&    description,
                     float             value,
                     IEType            type                 = IE_T_EditNumber,
                     bool              enabled              = true,
                     PSS_StringFormat& format               = PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                     CStringArray*     pValueArray          = NULL,
                     CMenu*            pMenu                = NULL,
                     bool              saveState            = true,
                     bool              saveStatePerProperty = true);

        /**
        * Constructor
        *@param categoryResID - the category resource identifier
        *@param categoryID - the category identifier
        *@param labelResID - the label resource identifier
        *@param itemID - the item identifier
        *@param descriptionResID - the description resource identifier
        *@param value - the value
        *@param type - the value type
        *@param enabled - if true, the property will be enabled, disabled otherwise
        *@param format - the string format
        *@param pValueArray - the value array
        *@param pMenu - the context popup menu
        *@param saveState - if true, the state may be saved
        *@param saveStatePerProperty - if true, the state will be saved per property
        *@note The pValueArray is kept as a reference to the source array, and will not be deleted internally.
        *      This array should be deleted by the owner
        */
        PSS_Property(const UINT        categoryResID,
                     int               categoryID,
                     const UINT        labelResID,
                     int               itemID,
                     const UINT        descriptionResID,
                     float             value,
                     IEType            type                 = IE_T_EditNumber,
                     bool              enabled              = true,
                     PSS_StringFormat& format               = PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                     CStringArray*     pValueArray          = NULL,
                     CMenu*            pMenu                = NULL,
                     bool              saveState            = true,
                     bool              saveStatePerProperty = true);

        /**
        * Constructor
        *@param category - the category
        *@param categoryID - the category identifier
        *@param label - the label
        *@param itemID - the item identifier
        *@param description - the description
        *@param value - the value
        *@param type - the value type
        *@param enabled - if true, the property will be enabled, disabled otherwise
        *@param format - the string format
        *@param pValueArray - the value array
        *@param pMenu - the context popup menu
        *@param saveState - if true, the state may be saved
        *@param saveStatePerProperty - if true, the state will be saved per property
        *@note The pValueArray is kept as a reference to the source array, and will not be deleted internally.
        *      This array should be deleted by the owner
        */
        PSS_Property(const CString&    category,
                     int               categoryID,
                     const CString&    label,
                     int               itemID,
                     const CString&    description,
                     PSS_Date&         value,
                     IEType            type                 = IE_T_EditDate,
                     bool              enabled              = true,
                     PSS_StringFormat& format               = PSS_StringFormat(PSS_StringFormat::IE_FT_Date),
                     CStringArray*     pValueArray          = NULL,
                     CMenu*            pMenu                = NULL,
                     bool              saveState            = true,
                     bool              saveStatePerProperty = true);

        /**
        * Constructor
        *@param categoryResID - the category resource identifier
        *@param categoryID - the category identifier
        *@param labelResID - the label resource identifier
        *@param itemID - the item identifier
        *@param descriptionResID - the description resource identifier
        *@param value - the value
        *@param type - the value type
        *@param enabled - if true, the property will be enabled, disabled otherwise
        *@param format - the string format
        *@param pValueArray - the value array
        *@param pMenu - the context popup menu
        *@param saveState - if true, the state may be saved
        *@param saveStatePerProperty - if true, the state will be saved per property
        *@note The pValueArray is kept as a reference to the source array, and will not be deleted internally.
        *      This array should be deleted by the owner
        */
        PSS_Property(const UINT        categoryResID,
                     int               categoryID,
                     const UINT        labelResID,
                     int               itemID,
                     const UINT        descriptionResID,
                     PSS_Date&         value,
                     IEType            type                 = IE_T_EditDate,
                     bool              enabled              = true,
                     PSS_StringFormat& format               = PSS_StringFormat(PSS_StringFormat::IE_FT_Date),
                     CStringArray*     pValueArray          = NULL,
                     CMenu*            pMenu                = NULL,
                     bool              saveState            = true,
                     bool              saveStatePerProperty = true);

        /**
        * Constructor
        *@param category - the category
        *@param categoryID - the category identifier
        *@param label - the label
        *@param itemID - the item identifier
        *@param description - the description
        *@param value - the value
        *@param type - the value type
        *@param enabled - if true, the property will be enabled, disabled otherwise
        *@param format - the string format
        *@param pValueArray - the value array
        *@param pMenu - the context popup menu
        *@param saveState - if true, the state may be saved
        *@param saveStatePerProperty - if true, the state will be saved per property
        *@note The pValueArray is kept as a reference to the source array, and will not be deleted internally.
        *      This array should be deleted by the owner
        */
        PSS_Property(const CString   category,
                   int               categoryID,
                   const CString     label,
                   int               itemID,
                   const CString     description,
                   PSS_TimeSpan&     value,
                   IEType            type                 = IE_T_EditTime,
                   bool              enabled              = true,
                   PSS_StringFormat& format               = PSS_StringFormat(PSS_StringFormat::IE_FT_Time1),
                   CStringArray*     pValueArray          = NULL,
                   CMenu*            pMenu                = NULL,
                   bool              saveState            = true,
                   bool              saveStatePerProperty = true);

        /**
        * Constructor
        *@param categoryResID - the category resource identifier
        *@param categoryID - the category identifier
        *@param labelResID - the label resource identifier
        *@param itemID - the item identifier
        *@param descriptionResID - the description resource identifier
        *@param value - the value
        *@param type - the value type
        *@param enabled - if true, the property will be enabled, disabled otherwise
        *@param format - the string format
        *@param pValueArray - the value array
        *@param pMenu - the context popup menu
        *@param saveState - if true, the state may be saved
        *@param saveStatePerProperty - if true, the state will be saved per property
        *@note The pValueArray is kept as a reference to the source array, and will not be deleted internally.
        *      This array should be deleted by the owner
        */
        PSS_Property(const UINT      categoryResID,
                   int               categoryID,
                   const UINT        labelResID,
                   int               itemID,
                   const UINT        descriptionResID,
                   PSS_TimeSpan&     value,
                   IEType            type                 = IE_T_EditTime,
                   bool              enabled              = true,
                   PSS_StringFormat& format               = PSS_StringFormat(PSS_StringFormat::IE_FT_Time1),
                   CStringArray*     pValueArray          = NULL,
                   CMenu*            pMenu                = NULL,
                   bool              saveState            = true,
                   bool              saveStatePerProperty = true);

        /**
        * Constructor
        *@param category - the category
        *@param categoryID - the category identifier
        *@param label - the label
        *@param itemID - the item identifier
        *@param description - the description
        *@param value - the value
        *@param type - the value type
        *@param enabled - if true, the property will be enabled, disabled otherwise
        *@param format - the string format
        *@param pValueArray - the value array
        *@param pMenu - the context popup menu
        *@param saveState - if true, the state may be saved
        *@param saveStatePerProperty - if true, the state will be saved per property
        *@note The pValueArray is kept as a reference to the source array, and will not be deleted internally.
        *      This array should be deleted by the owner
        */
        PSS_Property(const CString&    category,
                     int               categoryID,
                     const CString&    label,
                     int               itemID,
                     const CString&    description,
                     PSS_Duration&     value,
                     IEType            type                 = IE_T_EditDuration,
                     bool              enabled              = true,
                     PSS_StringFormat& format               = PSS_StringFormat(PSS_StringFormat::IE_FT_Duration),
                     CStringArray*     pValueArray          = NULL,
                     CMenu*            pMenu                = NULL,
                     bool              saveState            = true,
                     bool              saveStatePerProperty = true);

        /**
        * Constructor
        *@param categoryResID - the category resource identifier
        *@param categoryID - the category identifier
        *@param labelResID - the label resource identifier
        *@param itemID - the item identifier
        *@param descriptionResID - the description resource identifier
        *@param value - the value
        *@param type - the value type
        *@param enabled - if true, the property will be enabled, disabled otherwise
        *@param format - the string format
        *@param pValueArray - the value array
        *@param pMenu - the context popup menu
        *@param saveState - if true, the state may be saved
        *@param saveStatePerProperty - if true, the state will be saved per property
        *@note The pValueArray is kept as a reference to the source array, and will not be deleted internally.
        *      This array should be deleted by the owner
        */
        PSS_Property(const UINT      categoryResID,
                   int               categoryID,
                   const UINT        labelResID,
                   int               itemID,
                   const UINT        descriptionResID,
                   PSS_Duration&     value,
                   IEType            type                 = IE_T_EditDuration,
                   bool              enabled              = true,
                   PSS_StringFormat& format               = PSS_StringFormat(PSS_StringFormat::IE_FT_Duration),
                   CStringArray*     pValueArray          = NULL,
                   CMenu*            pMenu                = NULL,
                   bool              saveState            = true,
                   bool              saveStatePerProperty = true);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_Property(const PSS_Property& other);

        virtual ~PSS_Property();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_Property& operator = (const PSS_Property& other);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual inline PSS_Property* Dup() const;

        /**
        * Gets the category
        *@return the category
        */
        virtual inline CString GetCategory() const;

        /**
        * Sets the category
        *@param value - the category
        */
        virtual inline void SetCategory(const CString& value);

        /**
        * Gets the category identifier
        *@return the category identifier
        */
        virtual inline int GetCategoryID() const;

        /**
        * Sets the category identifier
        *@param value - the category identifier
        */
        virtual inline void SetCategoryID(int value);

        /**
        * Gets the label
        *@return the label
        */
        virtual inline CString GetLabel() const;

        /**
        * Sets the label
        *@param value - the label
        */
        virtual inline void SetLabel(const CString& value);

        /**
        * Gets the item identifier
        *@return the item identifier
        */
        virtual inline int GetItemID() const;

        /**
        * Sets the item identifier
        *@param value - the item identifier
        */
        virtual inline void SetItemID(int value);

        /**
        * Gets the description
        *@return the description
        */
        virtual inline CString GetDescription() const;

        /**
        * Sets the description
        *@param value - the description
        */
        virtual inline void SetDescription(const CString& value);

        /**
        * Gets the value as a string
        *@return the value as a string
        */
        virtual inline CString GetValueString() const;

        /**
        * Sets the value as a string
        *@param value - the value to set
        */
        virtual inline void SetValueString(const CString& value);

        /**
        * Gets the value as a double
        *@return the value as a double
        */
        virtual inline double GetValueDouble() const;

        /**
        * Sets the value as a double
        *@param value - the value to set
        */
        virtual inline void SetValueDouble(double value);

        /**
        * Gets the value as a float
        *@return the value as a float
        */
        virtual inline float GetValueFloat() const;

        /**
        * Sets the value as a float
        *@param value - the value to set
        */
        virtual inline void SetValueFloat(float value);

        /**
        * Gets the value as a date
        *@return the value as a date
        */
        virtual inline PSS_Date GetValueDate() const;

        /**
        * Sets the value as a date
        *@param value - the value to set
        */
        virtual inline void SetValueDate(const PSS_Date& value);

        /**
        * Gets the value as a time span
        *@return the value as a time span
        */
        virtual inline PSS_TimeSpan GetValueTimeSpan() const;

        /**
        * Sets the value as a time span
        *@param value - the value to set
        */
        virtual inline void SetValueTimeSpan(const PSS_TimeSpan& value);

        /**
        * Gets the value as a duration
        *@return the value as a duration
        */
        virtual inline PSS_Duration GetValueDuration() const;

        /**
        * Sets the value as a duration
        *@param value - the value to set
        */
        virtual inline void SetValueDuration(const PSS_Duration& value);

        /**
        * Gets if the property is enabled
        *@return true if the property is enabled, otherwise false
        */
        virtual inline bool GetEnabled() const;

        /**
        * Sets the property as enabled
        *@param value - if true, the property is enabled
        */
        virtual inline void SetEnabled(bool value);

        /**
        * Gets the property save state
        *@return the property save state
        */
        virtual inline bool GetSaveState() const;

        /**
        * Sets the property save state
        *@param value - the property save state
        */
        virtual inline void SetSaveState(bool value);

        /**
        * Gets the property save state per property
        *@return the property save state per property
        */
        virtual inline bool GetSaveStatePerProperty() const;

        /**
        * Sets the property save state per property
        *@param value - the property save state per property
        */
        virtual inline void SetSaveStatePerProperty(bool value);

        /**
        * Gets the string format
        *@return the string format
        */
        virtual inline PSS_StringFormat& GetStringFormat();

        /**
        * Sets the string format
        *@param value - the string format
        */
        virtual inline void SetStringFormat(PSS_StringFormat& value);

        /**
        * Gets the value array
        *@return the value array
        */
        virtual inline CStringArray* GetValueArray() const;

        /**
        * Sets the value array
        *@param pValueArray - the value array
        */
        virtual inline void SetValueArray(CStringArray* pValueArray);

        /**
        * Gets the popup menu
        *@return the popup menu
        */
        virtual inline CMenu* GetMenu() const;

        /**
        * Sets the popup menu
        *@param pMenu - the popup menu
        */
        virtual inline void SetMenu(CMenu* pMenu);

        /**
        * Gets if the property has changed
        *@return true if the property has changed, otherwise false
        */
        virtual inline bool GetHasChanged() const;

        /**
        * Sets if the property has changed
        *@param value - if true, the property has changed
        */
        virtual inline void SetHasChanged(bool value);

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

        /**
        * Gets the property type
        *@return the property type
        */
        virtual inline IEType GetType() const;

        /**
        * Gets the property value type
        *@return the property value type
        */
        virtual inline IEValueType GetValueType() const;

        /**
        * Checks if the property is dynamic
        *@return true if the property is dynamic, otherwise false
        */
        virtual inline bool IsDynamic() const;

        /**
        * Sets the property as dynamic
        *@param value - if true, the property is dynamic
        */
        virtual inline void SetDynamic(bool value = true);

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
        * Checks if the property contains a value list
        *@return true if the property contains a value list, otherwise false
        */
        virtual inline bool HasValueList() const;

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CStringArray*    m_pValueArray;
        CMenu*           m_pMenu;
        IEType           m_Type;
        IEValueType      m_ValueType;
        PSS_StringFormat m_Format;
        PSS_Date         m_DateValue;
        PSS_TimeSpan     m_TimeSpanValue;
        PSS_Duration     m_DurationValue;
        CString          m_Category;
        CString          m_Label;
        CString          m_Description;
        CString          m_StrValue;
        double           m_DoubleValue;
        float            m_FloatValue;
        int              m_CategoryID;
        int              m_ItemID;
        int              m_CategoryOrder;
        int              m_ItemOrder;
        bool             m_Dynamic;
        bool             m_Enabled;
        bool             m_HasChanged;
        bool             m_SaveState;
        bool             m_SaveStatePerProperty;
        bool             m_EnableDragNDrop;
};

//---------------------------------------------------------------------------
// PSS_Property
//---------------------------------------------------------------------------
PSS_Property::PSS_Property(const PSS_Property& other) :
    CObject(),
    m_pValueArray(NULL),
    m_pMenu(NULL),
    m_Type(IE_T_EditString),
    m_ValueType(IE_VT_Unknown),
    m_Format(PSS_StringFormat(PSS_StringFormat::IE_FT_General)),
    m_DoubleValue(0.0),
    m_FloatValue(0.0f),
    m_CategoryID(-1),
    m_ItemID(-1),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Dynamic(false),
    m_Enabled(false),
    m_HasChanged(false),
    m_SaveState(false),
    m_SaveStatePerProperty(false),
    m_EnableDragNDrop(false)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_Property* PSS_Property::Dup() const
{
    return new PSS_Property(*this);
}
//---------------------------------------------------------------------------
CString PSS_Property::GetCategory() const
{
    return m_Category;
}
//---------------------------------------------------------------------------
void PSS_Property::SetCategory(const CString& value)
{
    m_Category = value;
}
//---------------------------------------------------------------------------
int PSS_Property::GetCategoryID() const
{
    return m_CategoryID;
}
//---------------------------------------------------------------------------
void PSS_Property::SetCategoryID(int value)
{
    m_CategoryID = value;
}
//---------------------------------------------------------------------------
CString PSS_Property::GetLabel() const
{
    return m_Label;
}
//---------------------------------------------------------------------------
void PSS_Property::SetLabel(const CString& value)
{
    m_Label = value;
}
//---------------------------------------------------------------------------
int PSS_Property::GetItemID() const
{
    return m_ItemID;
}
//---------------------------------------------------------------------------
void PSS_Property::SetItemID(int value)
{
    m_ItemID = value;
}
//---------------------------------------------------------------------------
CString PSS_Property::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
void PSS_Property::SetDescription(const CString& value)
{
    m_Description = value;
}
//---------------------------------------------------------------------------
CString PSS_Property::GetValueString() const
{
    return m_StrValue;
}
//---------------------------------------------------------------------------
void PSS_Property::SetValueString(const CString& value)
{
    m_StrValue  = value;
    m_ValueType = IE_VT_String;
}
//---------------------------------------------------------------------------
double PSS_Property::GetValueDouble() const
{
    return m_DoubleValue;
}
//---------------------------------------------------------------------------
void PSS_Property::SetValueDouble(double value)
{
    m_DoubleValue = value;
    m_ValueType   = IE_VT_Double;
}
//---------------------------------------------------------------------------
float PSS_Property::GetValueFloat() const
{
    return m_FloatValue;
}
//---------------------------------------------------------------------------
void PSS_Property::SetValueFloat(float value)
{
    m_FloatValue = value;
    m_ValueType  = IE_VT_Float;
}
//---------------------------------------------------------------------------
PSS_Date PSS_Property::GetValueDate() const
{
    return m_DateValue;
}
//---------------------------------------------------------------------------
void PSS_Property::SetValueDate(const PSS_Date& value)
{
    m_DateValue = value;
    m_ValueType = IE_VT_Date;
}
//---------------------------------------------------------------------------
PSS_TimeSpan PSS_Property::GetValueTimeSpan() const
{
    return m_TimeSpanValue;
}
//---------------------------------------------------------------------------
void PSS_Property::SetValueTimeSpan(const PSS_TimeSpan& value)
{
    m_TimeSpanValue = value;
    m_ValueType     = IE_VT_TimeSpan;
}
//---------------------------------------------------------------------------
PSS_Duration PSS_Property::GetValueDuration() const
{
    return m_DurationValue;
}
//---------------------------------------------------------------------------
void PSS_Property::SetValueDuration(const PSS_Duration& value)
{
    m_DurationValue = value;
    m_ValueType     = IE_VT_Duration;
}
//---------------------------------------------------------------------------
bool PSS_Property::GetEnabled() const
{
    return m_Enabled;
}
//---------------------------------------------------------------------------
void PSS_Property::SetEnabled(bool value)
{
    m_Enabled = value;
}
//---------------------------------------------------------------------------
bool PSS_Property::GetSaveState() const
{
    return m_SaveState;
}
//---------------------------------------------------------------------------
void PSS_Property::SetSaveState(bool value)
{
    m_SaveState = value;
}
//---------------------------------------------------------------------------
bool PSS_Property::GetSaveStatePerProperty() const
{
    return m_SaveStatePerProperty;
}
//---------------------------------------------------------------------------
void PSS_Property::SetSaveStatePerProperty(bool value)
{
    m_SaveStatePerProperty = value;
}
//---------------------------------------------------------------------------
PSS_StringFormat& PSS_Property::GetStringFormat()
{
    return m_Format;
}
//---------------------------------------------------------------------------
void PSS_Property::SetStringFormat(PSS_StringFormat& value)
{
    m_Format = value;
}
//---------------------------------------------------------------------------
CStringArray* PSS_Property::GetValueArray() const
{
    return m_pValueArray;
}
//---------------------------------------------------------------------------
void PSS_Property::SetValueArray(CStringArray* pValueArray)
{
    m_pValueArray = pValueArray;
}
//---------------------------------------------------------------------------
CMenu* PSS_Property::GetMenu() const
{
    return m_pMenu;
}
//---------------------------------------------------------------------------
void PSS_Property::SetMenu(CMenu *value)
{
    m_pMenu = value;
}
//---------------------------------------------------------------------------
bool PSS_Property::GetHasChanged() const
{
    return m_HasChanged;
}
//---------------------------------------------------------------------------
void PSS_Property::SetHasChanged(bool value)
{
    m_HasChanged = value;
}
//---------------------------------------------------------------------------
int PSS_Property::GetCategoryOrder() const
{
    return m_CategoryOrder;
}
//---------------------------------------------------------------------------
void PSS_Property::SetCategoryOrder(int value)
{
    m_CategoryOrder = value;
}
//---------------------------------------------------------------------------
int PSS_Property::GetItemOrder() const
{
    return m_ItemOrder;
}
//---------------------------------------------------------------------------
void PSS_Property::SetItemOrder(int value)
{
    m_ItemOrder = value;
}
//---------------------------------------------------------------------------
PSS_Property::IEType PSS_Property::GetType() const
{
    return m_Type;
}
//---------------------------------------------------------------------------
PSS_Property::IEValueType PSS_Property::GetValueType() const
{
    return m_ValueType;
}
//---------------------------------------------------------------------------
bool PSS_Property::IsDynamic() const
{
    return m_Dynamic;
}
//---------------------------------------------------------------------------
void PSS_Property::SetDynamic(bool value)
{
    m_Dynamic = value;
}
//---------------------------------------------------------------------------
bool PSS_Property::IsDragNDropEnabled() const
{
    return m_EnableDragNDrop;
}
//---------------------------------------------------------------------------
void PSS_Property::EnableDragNDrop(bool value)
{
    m_EnableDragNDrop = value;
}
//---------------------------------------------------------------------------
bool PSS_Property::HasValueList() const
{
    return (m_pValueArray && m_pValueArray->GetSize() > 0);
}
//---------------------------------------------------------------------------

#endif
