/****************************************************************************************************************
 *                                                   Classe ZBProperty                                            *
 ****************************************************************************************************************
 * Cette classe représente les entités de type propriétés.                                                        *
 ****************************************************************************************************************/

#include "stdafx.h"
#include "ZBProperty.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 14 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// ZBProperty
IMPLEMENT_SERIAL(ZBProperty, CObject, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBProperty::ZBProperty( const CString    Category                /*= ""*/,
                        int                CategoryID                /*= -1*/,
                        const CString    Label                    /*= ""*/,
                        int                ItemID                    /*= -1*/,
                        const CString    Description                /*= ""*/,
                        CString            Value                    /*= ""*/,
                        PropertyType    PTType                    /*= PT_EDIT_STRING*/,
                        bool            Enable                    /*= true*/,
                       PSS_StringFormat&    ft                        /*= ZBStringFormat(ZBStringFormat::General)*/,
                        CStringArray*    pArrayOfValues            /*= NULL*/,
                        CMenu*            pMenu                    /*= NULL*/,
                        bool            SaveState                /*= true*/,
                        bool            SaveStatePerProperty    /*= true*/ )
    : m_Category                ( Category ),
      m_CategoryID                ( CategoryID ),
      m_Dynamic                    ( false ),
      m_Label                    ( Label ),
      m_ItemID                    ( ItemID ),
      m_Description                ( Description ),
      m_PTType                    ( PTType ),
      m_Enable                    ( Enable ),
      m_ft                        ( ft ),
      m_HasChanged                ( false ),
      m_pArrayOfValues            ( pArrayOfValues ),
      m_pMenu                    ( pMenu ),
      m_SaveState                ( SaveState ),
      m_SaveStatePerProperty    ( SaveStatePerProperty ),
      m_EnableDragNDrop            ( false ),
      m_CategoryOrder            ( -1 ),
      m_ItemOrder                ( -1 )
{
    m_ValueType                    = PT_UNKNOWN;
    SetValueString                ( Value );
}

ZBProperty::ZBProperty( const UINT        CategoryResID,
                        int                CategoryID,
                        const UINT        LabelResID,
                        int                ItemID,
                        const UINT        DescriptionResID,
                        CString            Value,
                        PropertyType    PTType                    /*= PT_EDIT_STRING*/,
                        bool            Enable                    /*= true*/,
                       PSS_StringFormat&    ft                        /*= ZBStringFormat(ZBStringFormat::General)*/,
                        CStringArray*    pArrayOfValues            /*= NULL*/,
                        CMenu*            pMenu                    /*= NULL*/,
                        bool            SaveState                /*= true*/,
                        bool            SaveStatePerProperty    /*= true*/ )
    : m_CategoryID                ( CategoryID ),
      m_ItemID                    ( ItemID ),
      m_Dynamic                    ( false ),
      m_PTType                    ( PTType ),
      m_Enable                    ( Enable ),
      m_ft                        ( ft ),
      m_HasChanged                ( false ),
      m_pArrayOfValues            ( pArrayOfValues ),
      m_pMenu                    ( pMenu ),
      m_SaveState                ( SaveState ),
      m_SaveStatePerProperty    ( SaveStatePerProperty ),
      m_EnableDragNDrop            ( false ),
      m_CategoryOrder            ( -1 ),
      m_ItemOrder                ( -1 )
{
    m_Category.LoadString        ( CategoryResID );
    m_Label.LoadString            ( LabelResID );
    m_Description.LoadString    ( DescriptionResID );

    m_ValueType                    = PT_UNKNOWN;
    SetValueString                ( Value );
}

ZBProperty::ZBProperty( const CString    Category,
                        int                CategoryID,
                        const CString    Label,
                        int                ItemID,
                        const CString    Description,
                        double            Value,
                        PropertyType    PTType                    /*= PT_EDIT_NUMBER*/,
                        bool            Enable                    /*= true*/,
                       PSS_StringFormat& ft                        /*= ZBStringFormat(ZBStringFormat::General)*/,
                        CStringArray*    pArrayOfValues            /*= NULL*/,
                        CMenu*            pMenu                    /*= NULL*/,
                        bool            SaveState                /*= true*/,
                        bool            SaveStatePerProperty    /*= true*/ )
    : m_Category                ( Category ),
      m_CategoryID                ( CategoryID ),
      m_Dynamic                    ( false ),
      m_Label                    ( Label ),
      m_ItemID                    ( ItemID ),
      m_Description                ( Description ),
      m_PTType                    ( PTType ),
      m_Enable                    ( Enable ),
      m_ft                        ( ft ),
      m_HasChanged                ( false ),
      m_pArrayOfValues            ( pArrayOfValues ),
      m_pMenu                    ( pMenu ),
      m_SaveState                ( SaveState ),
      m_SaveStatePerProperty    ( SaveStatePerProperty ),
      m_EnableDragNDrop            ( false ),
      m_CategoryOrder            ( -1 ),
      m_ItemOrder                ( -1 )
{
    m_ValueType                    = PT_UNKNOWN;
    SetValueDouble                ( Value );
}

ZBProperty::ZBProperty( const UINT        CategoryResID,
                        int                CategoryID,
                        const UINT        LabelResID,
                        int                ItemID,
                        const UINT        DescriptionResID,
                        double            Value,
                        PropertyType    PTType                    /*= PT_EDIT_NUMBER*/,
                        bool            Enable                    /*= true*/,
                       PSS_StringFormat& ft                        /*= ZBStringFormat(ZBStringFormat::General)*/,
                        CStringArray*    pArrayOfValues            /*= NULL*/,
                        CMenu*            pMenu                    /*= NULL*/,
                        bool            SaveState                /*= true*/,
                        bool            SaveStatePerProperty    /*= true*/ )
    : m_CategoryID                ( CategoryID ),
      m_ItemID                    ( ItemID ),
      m_Dynamic                    ( false ),
      m_PTType                    ( PTType ),
      m_Enable                    ( Enable ),
      m_ft                        ( ft ),
      m_HasChanged                ( false ),
      m_pArrayOfValues            ( pArrayOfValues ),
      m_pMenu                    ( pMenu ),
      m_SaveState                ( SaveState ),
      m_SaveStatePerProperty    ( SaveStatePerProperty ),
      m_EnableDragNDrop            ( false ),
      m_CategoryOrder            ( -1 ),
      m_ItemOrder                ( -1 )
{
    m_Category.LoadString        ( CategoryResID );
    m_Label.LoadString            ( LabelResID );
    m_Description.LoadString    ( DescriptionResID );

    m_ValueType                    = PT_UNKNOWN;
    SetValueDouble                ( Value );
}

ZBProperty::ZBProperty( const CString    Category,
                        int                CategoryID,
                        const CString    Label,
                        int                ItemID,
                        const CString    Description,
                        float            Value,
                        PropertyType    PTType                    /*= PT_EDIT_NUMBER*/,
                        bool            Enable                    /*= true*/,
                       PSS_StringFormat& ft                        /*= ZBStringFormat(ZBStringFormat::General)*/,
                        CStringArray*    pArrayOfValues            /*= NULL*/,
                        CMenu*            pMenu                    /*= NULL*/,
                        bool            SaveState                /*= true*/,
                        bool            SaveStatePerProperty    /*= true*/ )
    : m_Category                ( Category ),
      m_CategoryID                ( CategoryID ),
      m_Dynamic                    ( false ),
      m_Label                    ( Label ),
      m_ItemID                    ( ItemID ),
      m_Description                ( Description ),
      m_PTType                    ( PTType ),
      m_Enable                    ( Enable ),
      m_ft                        ( ft ),
      m_HasChanged                ( false ),
      m_pArrayOfValues            ( pArrayOfValues ),
      m_pMenu                    ( pMenu ),
      m_SaveState                ( SaveState ),
      m_SaveStatePerProperty    ( SaveStatePerProperty ),
      m_EnableDragNDrop            ( false ),
      m_CategoryOrder            ( -1 ),
      m_ItemOrder                ( -1 )
{
    m_ValueType                    = PT_UNKNOWN;
    SetValueFloat                ( Value );
}

ZBProperty::ZBProperty( const UINT        CategoryResID,
                        int                CategoryID,
                        const UINT        LabelResID,
                        int                ItemID,
                        const UINT        DescriptionResID,
                        float            Value,
                        PropertyType    PTType                    /*= PT_EDIT_NUMBER*/,
                        bool            Enable                    /*= true*/,
                       PSS_StringFormat& ft                        /*= ZBStringFormat(ZBStringFormat::General)*/,
                        CStringArray*    pArrayOfValues            /*= NULL*/,
                        CMenu*            pMenu                    /*= NULL*/,
                        bool            SaveState                /*= true*/,
                        bool            SaveStatePerProperty    /*= true*/ )
    : m_CategoryID                ( CategoryID ),
      m_ItemID                    ( ItemID ),
      m_Dynamic                    ( false ),
      m_PTType                    ( PTType ),
      m_Enable                    ( Enable ),
      m_ft                        ( ft ),
      m_HasChanged                ( false ),
      m_pArrayOfValues            ( pArrayOfValues ),
      m_pMenu                    ( pMenu ),
      m_SaveState                ( SaveState ),
      m_SaveStatePerProperty    ( SaveStatePerProperty ),
      m_EnableDragNDrop            ( false ),
      m_CategoryOrder            ( -1 ),
      m_ItemOrder                ( -1 )
{
    m_Category.LoadString        ( CategoryResID );
    m_Label.LoadString            ( LabelResID );
    m_Description.LoadString    ( DescriptionResID );

    m_ValueType                    = PT_UNKNOWN;
    SetValueFloat                ( Value );
}

ZBProperty::ZBProperty( const CString    Category,
                        int                CategoryID,
                        const CString    Label,
                        int                ItemID,
                        const CString    Description,
                       PSS_Date&            Value,
                        PropertyType    PTType                    /*= PT_EDIT_DATE*/,
                        bool            Enable                    /*= true*/,
                       PSS_StringFormat& ft                        /*= ZBStringFormat(ZBStringFormat::Date)*/,
                        CStringArray*    pArrayOfValues            /*= NULL*/,
                        CMenu*            pMenu                    /*= NULL*/,
                        bool            SaveState                /*= true*/,
                        bool            SaveStatePerProperty    /*= true*/ )
    : m_Category                ( Category ),
      m_CategoryID                ( CategoryID ),
      m_Dynamic                    ( false ),
      m_Label                    ( Label ),
      m_ItemID                    ( ItemID ),
      m_Description                ( Description ),
      m_PTType                    ( PTType ),
      m_Enable                    ( Enable ),
      m_ft                        ( ft ),
      m_HasChanged                ( false ),
      m_pArrayOfValues            ( pArrayOfValues ),
      m_pMenu                    ( pMenu ),
      m_SaveState                ( SaveState ),
      m_SaveStatePerProperty    ( SaveStatePerProperty ),
      m_EnableDragNDrop            ( false ),
      m_CategoryOrder            ( -1 ),
      m_ItemOrder                ( -1 )
{
    m_ValueType                    = PT_UNKNOWN;
    SetValueDate                ( Value );
}

ZBProperty::ZBProperty( const UINT        CategoryResID,
                        int                CategoryID,
                        const UINT        LabelResID,
                        int                ItemID,
                        const UINT        DescriptionResID,
                       PSS_Date&            Value,
                        PropertyType    PTType                    /*= PT_EDIT_DATE*/,
                        bool            Enable                    /*= true*/,
                       PSS_StringFormat& ft                        /*= ZBStringFormat(ZBStringFormat::Date)*/,
                        CStringArray*    pArrayOfValues            /*= NULL*/,
                        CMenu*            pMenu                    /*= NULL*/,
                        bool            SaveState                /*= true*/,
                        bool            SaveStatePerProperty    /*= true*/ )
    : m_CategoryID                ( CategoryID ),
      m_ItemID                    ( ItemID ),
      m_Dynamic                    ( false ),
      m_PTType                    ( PTType ),
      m_Enable                    ( Enable ),
      m_ft                        ( ft ),
      m_HasChanged                ( false ),
      m_pArrayOfValues            ( pArrayOfValues ),
      m_pMenu                    ( pMenu ),
      m_SaveState                ( SaveState ),
      m_SaveStatePerProperty    ( SaveStatePerProperty ),
      m_EnableDragNDrop            ( false ),
      m_CategoryOrder            ( -1 ),
      m_ItemOrder                ( -1 )
{
    m_Category.LoadString        ( CategoryResID );
    m_Label.LoadString            ( LabelResID );
    m_Description.LoadString    ( DescriptionResID );

    m_ValueType                    = PT_UNKNOWN;
    SetValueDate                ( Value );
}

// Constructors for ZBTimeSpan
ZBProperty::ZBProperty( const CString    Category,
                        int                CategoryID,
                        const CString    Label,
                        int                ItemID,
                        const CString    Description,
                        ZBTimeSpan&        Value,
                        PropertyType    PTType                    /*= PT_EDIT_TIMESPAN*/,
                        bool            Enable                    /*= true*/,
                       PSS_StringFormat& ft                        /*= ZBStringFormat(ZBStringFormat::Time1)*/,
                        CStringArray*    pArrayOfValues            /*= NULL*/,
                        CMenu*            pMenu                    /*= NULL*/,
                        bool            SaveState                /*= true*/,
                        bool            SaveStatePerProperty    /*= true*/ )
    : m_Category                ( Category ),
      m_CategoryID                ( CategoryID ),
      m_Dynamic                    ( false ),
      m_Label                    ( Label ),
      m_ItemID                    ( ItemID ),
      m_Description                ( Description ),
      m_PTType                    ( PTType ),
      m_Enable                    ( Enable ),
      m_ft                        ( ft ),
      m_HasChanged                ( false ),
      m_pArrayOfValues            ( pArrayOfValues ),
      m_pMenu                    ( pMenu ),
      m_SaveState                ( SaveState ),
      m_SaveStatePerProperty    ( SaveStatePerProperty ),
      m_EnableDragNDrop            ( false ),
      m_CategoryOrder            ( -1 ),
      m_ItemOrder                ( -1 )
{
    m_ValueType                    = PT_UNKNOWN;
    SetValueTimeSpan            ( Value );
}

ZBProperty::ZBProperty( const UINT        CategoryResID,
                        int                CategoryID,
                        const UINT        LabelResID,
                        int                ItemID,
                        const UINT        DescriptionResID,
                        ZBTimeSpan&        Value,
                        PropertyType    PTType                    /*= PT_EDIT_TIMESPAN*/,
                        bool            Enable                    /*= true*/,
                       PSS_StringFormat& ft                        /*= ZBStringFormat(ZBStringFormat::Time1)*/,
                        CStringArray*    pArrayOfValues            /*= NULL*/,
                        CMenu*            pMenu                    /*= NULL*/,
                        bool            SaveState                /*= true*/,
                        bool            SaveStatePerProperty    /*= true*/ )
    : m_CategoryID                ( CategoryID ),
      m_ItemID                    ( ItemID ),
      m_Dynamic                    ( false ),
      m_PTType                    ( PTType ),
      m_Enable                    ( Enable ),
      m_ft                        ( ft ),
      m_HasChanged                ( false ),
      m_pArrayOfValues            ( pArrayOfValues ),
      m_pMenu                    ( pMenu ),
      m_SaveState                ( SaveState ),
      m_SaveStatePerProperty    ( SaveStatePerProperty ),
      m_EnableDragNDrop            ( false ),
      m_CategoryOrder            ( -1 ),
      m_ItemOrder                ( -1 )
{
    m_Category.LoadString        ( CategoryResID );
    m_Label.LoadString            ( LabelResID );
    m_Description.LoadString    ( DescriptionResID );

    m_ValueType                    = PT_UNKNOWN;
    SetValueTimeSpan            ( Value );
}

// Constructors for ZBDuration
ZBProperty::ZBProperty( const CString    Category,
                        int                CategoryID,
                        const CString    Label,
                        int                ItemID,
                        const CString    Description,
                       PSS_Duration&        Value,
                        PropertyType    PTType                    /*= PT_EDIT_DURATION*/,
                        bool            Enable                    /*= true*/,
                       PSS_StringFormat& ft                        /*= ZBStringFormat(ZBStringFormat::Duration)*/,
                        CStringArray*    pArrayOfValues            /*= NULL*/,
                        CMenu*            pMenu                    /*= NULL*/,
                        bool            SaveState                /*= true*/,
                        bool            SaveStatePerProperty    /*= true*/ )
    : m_Category                ( Category ),
      m_CategoryID                ( CategoryID ),
      m_Dynamic                    ( false ),
      m_Label                    ( Label ),
      m_ItemID                    ( ItemID ),
      m_Description                ( Description ),
      m_PTType                    ( PTType ),
      m_Enable                    ( Enable ),
      m_ft                        ( ft ),
      m_HasChanged                ( false ),
      m_pArrayOfValues            ( pArrayOfValues ),
      m_pMenu                    ( pMenu ),
      m_SaveState                ( SaveState ),
      m_SaveStatePerProperty    ( SaveStatePerProperty ),
      m_EnableDragNDrop            ( false ),
      m_CategoryOrder            ( -1 ),
      m_ItemOrder                ( -1 )
{
    m_ValueType                    = PT_UNKNOWN;
    SetValueDuration            ( Value );
}

ZBProperty::ZBProperty( const UINT        CategoryResID,
                        int                CategoryID,
                        const UINT        LabelResID,
                        int                ItemID,
                        const UINT        DescriptionResID,
                       PSS_Duration&        Value,
                        PropertyType    PTType                    /*= PT_EDIT_DURATION*/,
                        bool            Enable                    /*= true*/,
                       PSS_StringFormat& ft                        /*= ZBStringFormat(ZBStringFormat::Duration)*/,
                        CStringArray*    pArrayOfValues            /*= NULL*/,
                        CMenu*            pMenu                    /*= NULL*/,
                        bool            SaveState                /*= true*/,
                        bool            SaveStatePerProperty    /*= true*/ )
    : m_CategoryID                ( CategoryID ),
      m_ItemID                    ( ItemID ),
      m_Dynamic                    ( false ),
      m_PTType                    ( PTType ),
      m_Enable                    ( Enable ),
      m_ft                        ( ft ),
      m_HasChanged                ( false ),
      m_pArrayOfValues            ( pArrayOfValues ),
      m_pMenu                    ( pMenu ),
      m_SaveState                ( SaveState ),
      m_SaveStatePerProperty    ( SaveStatePerProperty ),
      m_EnableDragNDrop            ( false ),
      m_CategoryOrder            ( -1 ),
      m_ItemOrder                ( -1 )
{
    m_Category.LoadString        ( CategoryResID );
    m_Label.LoadString            ( LabelResID );
    m_Description.LoadString    ( DescriptionResID );

    m_ValueType                    = PT_UNKNOWN;
    SetValueDuration            ( Value );
}

ZBProperty::~ZBProperty()
{
    // JMR-MODIF - Le 29 mars 2006 - Détruit le pointeur vers le menu.
    if ( m_pMenu != NULL )
    {
        m_pMenu->DestroyMenu();
        m_pMenu = NULL;
    }

    // JMR-MODIF - Le 15 février 2006 - Ajout du code de nettoyage de l'objet.
    m_Category.Empty();
    m_Label.Empty();
    m_Description.Empty();
    m_sValue.Empty();

    m_ft.Release();

    m_pArrayOfValues = NULL;
}

ZBProperty& ZBProperty::operator=( const ZBProperty& src )
{
    m_Category                = src.m_Category;
    m_CategoryID            = src.m_CategoryID;

    m_Dynamic                = src.m_Dynamic;

    m_Label                    = src.m_Label;
    m_ItemID                = src.m_ItemID;
    m_Description            = src.m_Description;
    m_ValueType                = src.m_ValueType;

    m_sValue                = src.m_sValue;
    m_dValue                = src.m_dValue;
    m_fValue                = src.m_fValue;
    m_dtValue                = src.m_dtValue;
    m_tsValue                = src.m_tsValue;
    m_durationValue            = src.m_durationValue;

    m_PTType                = src.m_PTType;
    m_Enable                = src.m_Enable;
    m_ft                    = src.m_ft;
    m_pArrayOfValues        = src.m_pArrayOfValues;
    m_pMenu                    = src.m_pMenu;
    m_HasChanged            = src.m_HasChanged;

    m_SaveState                = src.m_SaveState;
    m_SaveStatePerProperty    = src.m_SaveStatePerProperty;

    m_EnableDragNDrop        = src.m_EnableDragNDrop;

    m_ItemOrder                = src.m_ItemOrder;
    m_CategoryOrder            = src.m_CategoryOrder;

    return *this;
}

void ZBProperty::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        ar << m_Category;
        ar << m_CategoryID;
        ar << (int)m_Dynamic;
        ar << m_Label;
        ar << m_ItemID;
        ar << m_Description;
        ar << (int)m_ValueType;

        ar << m_sValue;
        ar << m_dValue;
        ar << m_fValue;
        ar << m_dtValue;
        ar << m_tsValue;

        // Serialize the duration
        ar << (double)m_durationValue;
        ar << (int)m_durationValue.GetStatus();

        ar << (int)m_PTType;
        ar << (int)m_Enable;
        
        m_ft.Serialize( ar );

        ar << m_pArrayOfValues;

        ar << (int)m_HasChanged;

        ar << (int)m_SaveState;
        ar << (int)m_SaveStatePerProperty;

        ar << (int)m_EnableDragNDrop;

        ar << m_ItemOrder;
        ar << m_CategoryOrder;
    }
    else
    {
        ar >> m_Category;
        ar >> m_CategoryID;

        int value;
        ar >> value;
        m_Dynamic = ( value == 1 ) ? true : false;

        ar >> m_Label;
        ar >> m_ItemID;
        ar >> m_Description;
        ar >> value;
        m_ValueType = (PropertyValueType)value;

        ar >> m_sValue;
        ar >> m_dValue;
        ar >> m_fValue;
        ar >> m_dtValue;
        ar >> m_tsValue;

        // Deserialize the duration
        double dValue;
        ar >> dValue;
        m_durationValue.SetSpan(dValue);

        ar >> value;
        m_durationValue.SetStatus(PSS_Duration::IEStatus(value));

        ar >> value;
        m_PTType = (PropertyType)value;

        ar >> value;
        m_Enable = ( value == 1 ) ? true : false;

        m_ft.Serialize( ar );
        
        ar >> m_pArrayOfValues;

        ar >> value;
        m_HasChanged = ( value == 1 ) ? true : false;

        ar >> value;
        m_SaveState = ( value == 1 ) ? true : false;

        ar >> value;
        m_SaveStatePerProperty = ( value == 1 ) ? true : false;

        ar >> value;
        m_EnableDragNDrop = ( value == 1 ) ? true : false;

        ar >> m_ItemOrder;
        ar >> m_CategoryOrder;
    }
}
