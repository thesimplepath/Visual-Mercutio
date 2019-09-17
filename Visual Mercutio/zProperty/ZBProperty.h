// ZBProperty.h: interface for the ZBProperty class.

#if !defined(AFX_ZBPROPERTY_H__DB8536DE_36AB_4B13_94D5_CFF9BB4FE4E3__INCLUDED_)
#define AFX_ZBPROPERTY_H__DB8536DE_36AB_4B13_94D5_CFF9BB4FE4E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\ZBStringFormat.h"
#include "zBaseLib\ZBDate.h"
#include "zBaseLib\ZBTimeSpan.h"
#include "zBaseLib\ZBDuration.h"

#ifdef _ZPROPERTYEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 23 septembre 2005 - Ajout des décorations unicode _T(), nettoyage du code inutile.(En commentaires)

////////////////////////////////////////////////////////////////////////////
// ZBProperty
//
// Implement the property object which describes a property

class AFX_EXT_CLASS ZBProperty : public CObject
{
    DECLARE_SERIAL( ZBProperty )

public:

    enum PropertyType
    {
        PT_EDIT_STRING,
        PT_EDIT_STRING_READONLY,
        PT_EDIT_DATE,
        PT_EDIT_DATE_READONLY,
        PT_EDIT_TIME,
        PT_EDIT_TIME_READONLY,
        //RS-MODIF 08.08.2005 suppression confusions PT_EDIT_TIME et PT_EDIT_TIMESPAN
        //PT_EDIT_TIMESPAN,
        //PT_EDIT_TIMESPAN_READONLY,
        PT_EDIT_DURATION,
        PT_EDIT_DURATION_READONLY,
        PT_EDIT_NUMBER,
        PT_EDIT_NUMBER_READONLY,
        PT_EDIT_MENU,
        PT_EDIT_MENU_READONLY,
        PT_EDIT_INTELI,
        PT_EDIT_INTELI_READONLY,
        PT_EDIT_MULTILINE,
        PT_EDIT_MULTILINE_READONLY,
        PT_COMBO_STRING,
        PT_COMBO_STRING_READONLY,
        PT_COMBO_NUMBER,
        PT_COMBO_NUMBER_READONLY,
        PT_EDIT_FONT,
        PT_EDIT_FILE,
        PT_EDIT_DIRECTORY,
        PT_EDIT_MULTIFILES,
        PT_EDIT_MULTIDIRECTORIES,
        PT_EDIT_EXTENDED,
        PT_EDIT_EXTENDED_READONLY
    };

    enum PropertyValueType
    {
        PT_UNKNOWN,
        PT_STRING,
        PT_DOUBLE,
        PT_FLOAT,
        PT_DATE,
        PT_TIMESPAN,
        PT_DURATION
    };

public:

    // Constructors for String
    ZBProperty( const CString    Category                = _T( "" ),
                int                CategoryID                = -1,
                const CString    Label                    = _T( "" ),
                int                ItemID                    = -1,
                const CString    Description                = _T( "" ),
                CString            Value                    = _T( "" ),
                PropertyType    PTType                    = PT_EDIT_STRING,
                bool            Enable                    = true,
                ZBStringFormat&    ft                        = ZBStringFormat( ZBStringFormat::General ),
                CStringArray*    pArrayOfValues            = NULL,
                CMenu*            pMenu                    = NULL,
                bool            SaveState                = true,
                bool            SaveStatePerProperty    = true );

    ZBProperty( const UINT        CategoryResID,
                int                CategoryID,
                const UINT        LabelResID,
                int                ItemID,
                const UINT        DescriptionResID,
                CString            Value,
                PropertyType    PTType                    = PT_EDIT_STRING,
                bool            Enable                    = true,
                ZBStringFormat&    ft                        = ZBStringFormat( ZBStringFormat::General ),
                CStringArray*    pArrayOfValues            = NULL,
                CMenu*            pMenu                    = NULL,
                bool            SaveState                = true,
                bool            SaveStatePerProperty    = true );

    // Constructors for double
    ZBProperty( const CString    Category,
                int                CategoryID,
                const CString    Label,
                int                ItemID,
                const CString    Description,
                double            Value,
                PropertyType    PTType                    = PT_EDIT_NUMBER,
                bool            Enable                    = true,
                ZBStringFormat&    ft                        = ZBStringFormat( ZBStringFormat::General ),
                CStringArray*    pArrayOfValues            = NULL,
                CMenu*            pMenu                    = NULL,
                bool            SaveState                = true,
                bool            SaveStatePerProperty    = true );

    ZBProperty( const UINT        CategoryResID,
                int                CategoryID,
                const UINT        LabelResID,
                int                ItemID,
                const UINT        DescriptionResID,
                double            Value,
                PropertyType    PTType                    = PT_EDIT_NUMBER,
                bool            Enable                    = true,
                ZBStringFormat&    ft                        = ZBStringFormat( ZBStringFormat::General ),
                CStringArray*    pArrayOfValues            = NULL,
                CMenu*            pMenu                    = NULL,
                bool            SaveState                = true,
                bool            SaveStatePerProperty    = true );

    // Constructors for float
    ZBProperty( const CString    Category,
                int                CategoryID,
                const CString    Label,
                int                ItemID,
                const CString    Description,
                float            Value,
                PropertyType    PTType                    = PT_EDIT_NUMBER,
                bool            Enable                    = true,
                ZBStringFormat&    ft                        = ZBStringFormat( ZBStringFormat::General ),
                CStringArray*    pArrayOfValues            = NULL,
                CMenu*            pMenu                    = NULL,
                bool            SaveState                = true,
                bool            SaveStatePerProperty    = true );

    ZBProperty( const UINT        CategoryResID,
                int                CategoryID,
                const UINT        LabelResID,
                int                ItemID,
                const UINT        DescriptionResID,
                float            Value,
                PropertyType    PTType                    = PT_EDIT_NUMBER,
                bool            Enable                    = true,
                ZBStringFormat&    ft                        = ZBStringFormat( ZBStringFormat::General ),
                CStringArray*    pArrayOfValues            = NULL,
                CMenu*            pMenu                    = NULL,
                bool            SaveState                = true,
                bool            SaveStatePerProperty    = true );

    // Constructors for ZBDate
    ZBProperty( const CString    Category,
                int                CategoryID,
                const CString    Label,
                int                ItemID,
                const CString    Description,
               PSS_Date&            Value,
                PropertyType    PTType                    = PT_EDIT_DATE,
                bool            Enable                    = true,
                ZBStringFormat&    ft                        = ZBStringFormat( ZBStringFormat::Date ),
                CStringArray*    pArrayOfValues            = NULL,
                CMenu*            pMenu                    = NULL,
                bool            SaveState                = true,
                bool            SaveStatePerProperty    = true );

    ZBProperty( const UINT        CategoryResID,
                int                CategoryID,
                const UINT        LabelResID,
                int                ItemID,
                const UINT        DescriptionResID,
               PSS_Date&            Value,
                PropertyType    PTType                    = PT_EDIT_DATE,
                bool            Enable                    = true,
                ZBStringFormat&    ft                        = ZBStringFormat( ZBStringFormat::Date ),
                CStringArray*    pArrayOfValues            = NULL,
                CMenu*            pMenu                    = NULL,
                bool            SaveState                = true,
                bool            SaveStatePerProperty    = true );

    // Constructors for ZBTimeSpan
    ZBProperty( const CString    Category,
                int                CategoryID,
                const CString    Label,
                int                ItemID,
                const CString    Description,
                ZBTimeSpan&        Value,
                //RS-MODIF 08.08.2005 suppression confusions PT_EDIT_TIME et PT_EDIT_TIMESPAN
                //PropertyType    PTType                    = PT_EDIT_TIMESPAN,
                PropertyType    PTType                    = PT_EDIT_TIME,
                bool            Enable                    = true,
                ZBStringFormat&    ft                        = ZBStringFormat( ZBStringFormat::Time1 ),
                CStringArray*    pArrayOfValues            = NULL,
                CMenu*            pMenu                    = NULL,
                bool            SaveState                = true,
                bool            SaveStatePerProperty    = true );

    ZBProperty( const UINT        CategoryResID,
                int                CategoryID,
                const UINT        LabelResID,
                int                ItemID,
                const UINT        DescriptionResID,
                ZBTimeSpan&        Value,
                //RS-MODIF 08.08.2005 suppression confusions PT_EDIT_TIME et PT_EDIT_TIMESPAN
                //PropertyType    PTType                    = PT_EDIT_TIMESPAN,
                PropertyType    PTType                    = PT_EDIT_TIME,
                bool            Enable                    = true,
                ZBStringFormat&    ft                        = ZBStringFormat( ZBStringFormat::Time1 ),
                CStringArray*    pArrayOfValues            = NULL,
                CMenu*            pMenu                    = NULL,
                bool            SaveState                = true,
                bool            SaveStatePerProperty    = true );

    // Constructors for ZBDuration
    ZBProperty( const CString    Category,
                int                CategoryID,
                const CString    Label,
                int                ItemID,
                const CString    Description,
                ZBDuration&        Value,
                PropertyType    PTType                    = PT_EDIT_DURATION,
                bool            Enable                    = true,
                ZBStringFormat&    ft                        = ZBStringFormat( ZBStringFormat::Duration ),
                CStringArray*    pArrayOfValues            = NULL,
                CMenu*            pMenu                    = NULL,
                bool            SaveState                = true,
                bool            SaveStatePerProperty    = true );

    ZBProperty( const UINT        CategoryResID,
                int                CategoryID,
                const UINT        LabelResID,
                int                ItemID,
                const UINT        DescriptionResID,
                ZBDuration&        Value,
                PropertyType    PTType                    = PT_EDIT_DURATION,
                bool            Enable                    = true,
                ZBStringFormat&    ft                        = ZBStringFormat( ZBStringFormat::Duration ),
                CStringArray*    pArrayOfValues            = NULL,
                CMenu*            pMenu                    = NULL,
                bool            SaveState                = true,
                bool            SaveStatePerProperty    = true );

    virtual ~ZBProperty();

    // Allow copy constructor and assignement operator
    ZBProperty( const ZBProperty& src )
    {
        *this = src;
    }

    ZBProperty& operator=( const ZBProperty& src );

    /* Create a duplicate copy of this object. */
    virtual ZBProperty* Dup() const
    {
        return ( new ZBProperty( *this ) );
    }

    CString GetCategory() const;
    void SetCategory( CString value );

    int GetCategoryID() const;
    void SetCategoryID( int value );

    bool IsDynamic() const;
    void SetDynamic( bool value = true );

    CString GetLabel() const;
    void SetLabel( CString value );

    int GetItemID() const;
    void SetItemID( int value );

    CString GetDescription() const;
    void SetDescription( CString value );

    CString GetValueString() const;
    void SetValueString( CString value );

    double GetValueDouble() const;
    void SetValueDouble( double value );

    float GetValueFloat() const;
    void SetValueFloat( float value );

    PSS_Date GetValueDate() const;
    void SetValueDate(PSS_Date& value );

    ZBTimeSpan GetValueTimeSpan() const;
    void SetValueTimeSpan( ZBTimeSpan& value );

    ZBDuration GetValueDuration() const;
    void SetValueDuration( ZBDuration& value );

    bool GetEnable() const;
    void SetEnable( bool value );

    bool GetSaveState() const;
    void SetSaveState( bool value );

    bool GetSaveStatePerProperty() const;
    void SetSaveStatePerProperty( bool value );

    ZBStringFormat& GetStringFormat();
    void SetStringFormat( ZBStringFormat& value );

    CStringArray* GetpArrayOfValues() const;
    void SetpArrayOfValues( CStringArray* value );

    CMenu* GetpMenu() const;
    void SetpMenu( CMenu* value );

    PropertyType GetPTType() const;

    PropertyValueType GetPTValueType() const;

    bool HasValueList() const;

    // Has changed flag
    bool GetHasChanged() const;
    void SetHasChanged( bool value );

    bool IsEnabledDragNDrop() const;
    void EnableDragNDrop( bool value = true );

    int GetItemOrder() const;
    void SetItemOrder( int value );
    
    int GetCategoryOrder() const;
    void SetCategoryOrder( int value );

    // Serialize the property object
    virtual void Serialize( CArchive& ar );

private:

    void FreeString();

private:

    PropertyType        m_PTType;
    PropertyValueType    m_ValueType;
    PSS_Date                m_dtValue;
    ZBTimeSpan            m_tsValue;
    ZBDuration            m_durationValue;
    ZBStringFormat        m_ft;

    CStringArray*        m_pArrayOfValues;

    CString                m_Category;
    CString                m_Label;
    CString                m_Description;
    CString                m_sValue;

    double                m_dValue;

    float                m_fValue;

    bool                m_Dynamic;
    bool                m_Enable;
    bool                m_HasChanged;
    bool                m_SaveState;
    bool                m_SaveStatePerProperty;
    bool                m_EnableDragNDrop;

    int                    m_CategoryID;
    int                    m_ItemID;
    int                    m_ItemOrder;
    int                    m_CategoryOrder;

    CMenu*                m_pMenu;
};

inline CString ZBProperty::GetCategory() const
{
    return m_Category;
}

inline void ZBProperty::SetCategory( CString value )
{
    m_Category = value;
}

inline int ZBProperty::GetCategoryID() const
{
    return m_CategoryID;
}

inline void ZBProperty::SetCategoryID( int value )
{
    m_CategoryID = value;
}

inline bool ZBProperty::IsDynamic() const
{
    return m_Dynamic;
}

inline void ZBProperty::SetDynamic( bool value /*= true*/ )
{
    m_Dynamic = value;
}

inline CString ZBProperty::GetLabel() const
{
    return m_Label;
}

inline void ZBProperty::SetLabel( CString value )
{
    m_Label = value;
}

inline int ZBProperty::GetItemID() const
{
    return m_ItemID;
}

inline void ZBProperty::SetItemID( int value )
{
    m_ItemID = value;
}

inline CString ZBProperty::GetDescription() const
{
    return m_Description;
}

inline void ZBProperty::SetDescription( CString value )
{
    m_Description = value;
}

inline CString ZBProperty::GetValueString() const
{
    return m_sValue;
}

inline void ZBProperty::SetValueString( CString value )
{
    m_sValue        = value;
    m_ValueType        = PT_STRING;
}

inline double ZBProperty::GetValueDouble() const
{
    return m_dValue;
}

inline void ZBProperty::SetValueDouble( double value )
{
    m_dValue        = value;
    m_ValueType        = PT_DOUBLE;
}

inline float ZBProperty::GetValueFloat() const
{
    return m_fValue;
}

inline void ZBProperty::SetValueFloat( float value )
{
    m_fValue        = value;
    m_ValueType        = PT_FLOAT;
}

inline PSS_Date ZBProperty::GetValueDate() const
{
    return m_dtValue;
}

inline void ZBProperty::SetValueDate(PSS_Date& value )
{
    m_dtValue        = value;
    m_ValueType        = PT_DATE;
}

inline void ZBProperty::SetValueTimeSpan( ZBTimeSpan& value )
{
    m_tsValue        = value;
    m_ValueType        = PT_TIMESPAN;
}

inline ZBTimeSpan ZBProperty::GetValueTimeSpan() const
{
    return m_tsValue;
}

inline void ZBProperty::SetValueDuration( ZBDuration& value )
{
    m_durationValue    = value;
    m_ValueType        = PT_DURATION;
}

inline ZBDuration ZBProperty::GetValueDuration() const
{
    return m_durationValue;
}

inline bool ZBProperty::GetEnable() const
{
    return m_Enable;
}

inline void ZBProperty::SetEnable( bool value )
{
    m_Enable = value;
}

inline ZBStringFormat& ZBProperty::GetStringFormat()
{
    return m_ft;
}

inline void ZBProperty::SetStringFormat( ZBStringFormat& value )
{
    m_ft = value;
}

inline CStringArray* ZBProperty::GetpArrayOfValues() const
{
    return m_pArrayOfValues;
}

inline void ZBProperty::SetpArrayOfValues( CStringArray *value )
{
    m_pArrayOfValues = value;
}

inline CMenu* ZBProperty::GetpMenu() const
{
    return m_pMenu;
}

inline void ZBProperty::SetpMenu( CMenu *value )
{
    m_pMenu = value;
}

inline bool ZBProperty::HasValueList() const
{
    return ( m_pArrayOfValues && m_pArrayOfValues->GetSize() > 0 ) ? true : false;
}

inline ZBProperty::PropertyType    ZBProperty::GetPTType() const
{
    return m_PTType;
}

inline ZBProperty::PropertyValueType ZBProperty::GetPTValueType() const
{
    return m_ValueType;
}

inline bool ZBProperty::GetHasChanged() const
{
    return m_HasChanged;
}

inline void ZBProperty::SetHasChanged( bool value )
{
    m_HasChanged = value;
}

inline bool ZBProperty::GetSaveState() const
{
    return m_SaveState;
}

inline void ZBProperty::SetSaveState( bool value )
{
    m_SaveState = value;
}

inline bool ZBProperty::GetSaveStatePerProperty() const
{
    return m_SaveStatePerProperty;
}

inline void ZBProperty::SetSaveStatePerProperty( bool value )
{
    m_SaveStatePerProperty = value;
}

inline bool ZBProperty::IsEnabledDragNDrop() const
{
    return m_EnableDragNDrop;
}

inline void ZBProperty::EnableDragNDrop( bool value /*= true*/ )
{
    m_EnableDragNDrop = value;
}

inline int ZBProperty::GetItemOrder() const
{
    return m_ItemOrder;
}

inline void ZBProperty::SetItemOrder( int value )
{
    m_ItemOrder = value;
}

inline int ZBProperty::GetCategoryOrder() const
{
    return m_CategoryOrder;
}

inline void ZBProperty::SetCategoryOrder( int value )
{
    m_CategoryOrder = value;
}

#endif // !defined(AFX_ZBPROPERTY_H__DB8536DE_36AB_4B13_94D5_CFF9BB4FE4E3__INCLUDED_)