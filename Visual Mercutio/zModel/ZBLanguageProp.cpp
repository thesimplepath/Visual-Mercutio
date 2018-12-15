// **************************************************************************************************************
// * @doc ZBLanguageProp                                                                                        *
// * @module ZBLanguageProp.cpp | Implementation of the <c ZBLanguageProp> class.                                *
// *                                                                                                            *
// * zForms<tm>                                                                                                    *
// * <nl>Copyright <cp> 2001 Advanced Dedicated Software, Inc. All rights reserved.                                *
// *                                                                                                            *
// *                                                                                                            *
// * Author: Dominique Aigroz                                                                                    *
// * <nl>Created: 03/2001                                                                                        *
// *                                                                                                            *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZBLanguageProp.h"

// Resource include
#include "zRBProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 31 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// **************************************************************************************************************
// *                                    ZBLanguageProp construction/destruction                                    *
// **************************************************************************************************************

IMPLEMENT_SERIAL( ZBLanguageProp, CODIntProperty, def_Version )

using namespace sfl;

//@mfunc | ZBLanguageProp | ZBLanguageProp | Constructor.
//
//@syntax ZBLanguageProp::ZBLanguageProp(int nId);
//@syntax ZBLanguageProp::ZBLanguageProp(const ZBLanguageProp& propBasic);
//
//@parmopt int | nId | ZS_BP_PROP_LANGUAGE | The identifier of the property.
//@parm ZBLanguageProp& | propBasic | The language property to copy.
ZBLanguageProp::ZBLanguageProp( int nId )
    : CODIntProperty( nId )
{
    m_Language = FrenchLang;

    VERIFY( RegisterProperties() );
}

ZBLanguageProp::ZBLanguageProp( const ZBLanguageProp& propBasic )
    : CODIntProperty( propBasic.GetId() )
{
    *this = propBasic;

    VERIFY( RegisterProperties() );
}

//@mfunc Destructor.
ZBLanguageProp::~ZBLanguageProp()
{
}

// **************************************************************************************************************
// *                                          ZBLanguageProp operations                                            *
// **************************************************************************************************************

//@mfunc Compare the property identifier with another identifier.
//@rdesc BOOL
//@parm Property identifier to compare to.
BOOL ZBLanguageProp::CompareId( const int nId ) const
{
    int nIdMin = m_nId;
    int nIdMax = m_nId + Z_LANGUAGE;

    return ( nId >= nIdMin && nId <= nIdMax );
}

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBLanguageProp& ZBLanguageProp::operator=( const ZBLanguageProp& propBasic )
{
    SetLanguage( propBasic.GetLanguage() );
    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBLanguageProp::operator==( const ZBLanguageProp propBasic ) const
{
    return ( GetLanguage() == propBasic.GetLanguage() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBLanguageProp::Merge( CODProperty* pProperty, DWORD dwChangeFlags )
{
    ZBLanguageProp* pLanguageProp = (ZBLanguageProp*)pProperty;

    if ( pLanguageProp )
    {
        if ( dwChangeFlags & Z_CHANGE_LANGUAGE )
        {
            m_Language = pLanguageProp->GetLanguage();
        }
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf CODFillProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBLanguageProp::IsEqual( CODProperty* pProp )
{
    if ( GetId() == pProp->GetId() )
    {
        ZBLanguageProp* pLanguageProp = (ZBLanguageProp*)pProp;

        if ( pLanguageProp )
        {
            return ( *this == *pLanguageProp );
        }
    }

    return FALSE;
}

// **************************************************************************************************************
// *                                        IODPropertyContainer interface                                        *
// **************************************************************************************************************

//@mfunc | ZBLanguageProp | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBLanguageProp::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBLanguageProp::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBLanguageProp::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBLanguageProp::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBLanguageProp::GetValue(const int nPropId, float& fValue) const
//
//@rdesc TRUE if the property identifier is supported by this property
// container. FALSE if the property identifier is invalid.
//@parm const int | nPropId | ID of property to retrieve.
//@parm CString& | strValue | Variable to assign return value to.
//@parm int& | nValue | Variable to assign return value to.
//@parm UINT& | nValue | Variable to assign return value to.
//@parm DWORD& | dwValue | Variable to assign return value to.
//@parm float& | fValue | Variable to assign return value to.
//
//@comm See <t Orientation Property Identifiers> for a list property IDs
// supported. This function will throw a <c CODPropertyConversionException>
// exception if the data type of the argument passed in is not compatible
// with the given property identifier.

BOOL ZBLanguageProp::GetValue( const int nPropId, CString& strValue ) const
{
    return FALSE;
}

BOOL ZBLanguageProp::GetValue( const int nPropId, int& nValue ) const
{
    switch ( nPropId )
    {
        case Z_LANGUAGE:
        {
            nValue = m_Language;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBLanguageProp::GetValue( const int nPropId, UINT& nValue ) const
{
    return FALSE;
}

BOOL ZBLanguageProp::GetValue( const int nPropId, DWORD& dwValue ) const
{
    switch ( nPropId )
    {
        case Z_LANGUAGE:
        {
            dwValue = static_cast<DWORD>( m_Language );
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBLanguageProp::GetValue( const int nPropId, float& fValue ) const
{
    switch ( nPropId )
    {
        case Z_LANGUAGE:
        {
            fValue = static_cast<float>( m_Language );
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

//@mfunc | ZBLanguageProp | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBLanguageProp::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBLanguageProp::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBLanguageProp::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBLanguageProp::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBLanguageProp::SetValue(const int nPropId, const float fValue)
//
//@rdesc TRUE if the property identifier is supported by this property
// container. FALSE if the property identifier is invalid.
//@parm const int | nPropId | ID of property to set.
//@parm LPCTSTR | lpszValue | Input value to assign to the specified property.
//@parm const int | nValue | Input value to assign to the specified property.
//@parm const UINT | nValue | Input value to assign to the specified property.
//@parm const DWORD | dwValue | Input value to assign to the specified property.
//@parm const float | fValue | Input value to assign to the specified property.
//
//@comm See <t Orientation Property Identifiers> for a list property IDs
// supported. This function will throw a <c CODPropertyConversionException>
// exception if the data type of the argument passed in is not compatible
// with the given property identifier.

BOOL ZBLanguageProp::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    return FALSE;
}

BOOL ZBLanguageProp::SetValue( const int nPropId, const int nValue )
{
    switch ( nPropId )
    {
        case Z_LANGUAGE:
        {
            m_Language = static_cast<Language>( nValue );
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBLanguageProp::SetValue( const int nPropId, const UINT nValue )
{
    return FALSE;
}

BOOL ZBLanguageProp::SetValue( const int nPropId, const DWORD dwValue )
{
    switch ( nPropId )
    {
        case Z_LANGUAGE:
        {
            m_Language = static_cast<Language>( static_cast<int>( dwValue ) );
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBLanguageProp::SetValue( const int nPropId, const float fValue )
{
    switch ( nPropId )
    {
        case Z_LANGUAGE:
        {
            m_Language = static_cast<Language>( static_cast<int>( fValue ) );
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

// **************************************************************************************************************
// *                                      ZBLanguageProp Property meta-data                                        *
// **************************************************************************************************************

bool ZBLanguageProp::RegisterProperties()
{
    static bool propsRegistered = false;

    if ( !propsRegistered )
    {
        bool success = true;

        if ( success )
        {
            success = RegisterProperty( Z_LANGUAGE,
                                        IDS_Z_LANGUAGE_NAME,
                                        IDS_Z_LANGUAGE_DESC,
                                        _PropertyAccessor( &ZBLanguageProp::GetLanguageInt,
                                                           &ZBLanguageProp::SetLanguageInt ),
                                        VT_INT,
                                        PROP_DIRECT );
        }

        if ( !success )
        {
            ZBLanguageProp::GetPropertyMap().DeleteAll();
        }

        propsRegistered = success;
    }

    return propsRegistered;
}

// **************************************************************************************************************
// *                                            ZBLanguageProp diagnostics                                        *
// **************************************************************************************************************

#ifdef _DEBUG

void ZBLanguageProp::AssertValid() const
{
    CODIntProperty::AssertValid();
}

void ZBLanguageProp::Dump( CDumpContext& dc ) const
{
    CODIntProperty::Dump( dc );
}

#endif //_DEBUG

// **************************************************************************************************************
// *                                        ZBLanguageProp serialization                                        *
// **************************************************************************************************************

//@mfunc Serializes the orientation properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBLanguageProp::Serialize( CArchive& ar )
{
    CODIntProperty::Serialize( ar );

    if ( ar.IsStoring() )
    {
        PUT_SCHEMA( ar, ZBLanguageProp );
        ar << (int)m_Language;
    }
    else
    {
        UINT nSchema;
        GET_SCHEMA( ar, nSchema );

        int value;
        ar >> value;
        m_Language = static_cast<Language>( value );
    }
}
