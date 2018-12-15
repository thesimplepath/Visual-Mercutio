// **************************************************************************************************************
// * @doc ZBBasicModelProperties                                                                                *
// * @module ZBBasicModelProp.cpp | Implementation of the <c ZBBPProcessProperties> class.                        *
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
#include "ZBBasicModelProp.h"

// Resource include
#include "zRBProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 28 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

using namespace sfl;

IMPLEMENT_SERIAL( ZBBasicModelProperties, CODIntProperty, def_Version )

// **************************************************************************************************************
// *                                ZBBasicModelProperties construction/destruction                                *
// **************************************************************************************************************

//@mfunc | ZBBasicModelProperties | ZBBasicModelProperties | Constructor.
//
//@syntax ZBBasicModelProperties::ZBBasicModelProperties(int nId);
//@syntax ZBBasicModelProperties::ZBBasicModelProperties(const ZBBasicModelProperties& propBasic);
//
//@parmopt int | nId | OD_PROP_ORIENTATION | The identifier of the property.
//@parm ZBBasicModelProperties& | propBasic | The orientation property to copy.
ZBBasicModelProperties::ZBBasicModelProperties( int nId )
    : CODIntProperty( nId )
{
    m_ModelName            = _T( "" );
    m_ModelDescription    = _T( "" );

    VERIFY( RegisterProperties() );
}

ZBBasicModelProperties::ZBBasicModelProperties( const ZBBasicModelProperties& propBasic )
    : CODIntProperty( propBasic.GetId() )
{
    *this = propBasic;

    VERIFY( RegisterProperties() );
}

//@mfunc Destructor.
ZBBasicModelProperties::~ZBBasicModelProperties()
{
}

// **************************************************************************************************************
// *                                      ZBBasicModelProperties operations                                        *
// **************************************************************************************************************

//@mfunc Compare the property identifier with another identifier.
//@rdesc BOOL
//@parm Property identifier to compare to.
BOOL ZBBasicModelProperties::CompareId( const int nId ) const
{
    int nIdMin = m_nId;
    int nIdMax = m_nId + Z_MODEL_DESCRIPTION;

    return ( nId >= nIdMin && nId <= nIdMax );
}

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBasicModelProperties& ZBBasicModelProperties::operator=( const ZBBasicModelProperties& propBasic )
{
    SetModelName( propBasic.GetModelName() );
    SetModelDescription( propBasic.GetModelDescription() );

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBasicModelProperties::operator==( const ZBBasicModelProperties propBasic ) const
{
    return ( GetModelName()            == propBasic.GetModelName() &&
             GetModelDescription()    == propBasic.GetModelDescription() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBasicModelProperties::Merge( CODProperty* pProperty, DWORD dwChangeFlags )
{
    ZBBasicModelProperties* pOrientationProp = (ZBBasicModelProperties*)pProperty;

    if ( pOrientationProp )
    {
        if ( dwChangeFlags & Z_CHANGE_MODEL_NAME )
        {
            m_ModelName = pOrientationProp->GetModelName();
        }

        if ( dwChangeFlags & Z_CHANGE_MODEL_DESCRIPTION )
        {
            m_ModelDescription = pOrientationProp->GetModelDescription();
        }
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf CODFillProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBasicModelProperties::IsEqual( CODProperty* pProp )
{
    if ( GetId() == pProp->GetId() )
    {
        ZBBasicModelProperties* pOrientationProp = (ZBBasicModelProperties*)pProp;

        if ( pOrientationProp )
        {
            return ( *this == *pOrientationProp );
        }
    }

    return FALSE;
}

// **************************************************************************************************************
// *                                       IODPropertyContainer interface                                        *
// **************************************************************************************************************

//@mfunc | ZBBasicModelProperties | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBasicModelProperties::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBasicModelProperties::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBasicModelProperties::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBasicModelProperties::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBasicModelProperties::GetValue(const int nPropId, float& fValue) const
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

BOOL ZBBasicModelProperties::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_MODEL_NAME:
        {
            strValue = m_ModelName;
            break;
        }

        case Z_MODEL_DESCRIPTION:
        {
            strValue = m_ModelDescription;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBasicModelProperties::GetValue( const int nPropId, int& nValue ) const
{
    switch ( nPropId )
    {
        case Z_MODEL_NAME:
        case Z_MODEL_DESCRIPTION:
        {
            throw new CODPropertyConversionException();
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBasicModelProperties::GetValue( const int nPropId, UINT& nValue ) const
{
    nValue; // unused

    if ( nPropId >= Z_MODEL_NAME && nPropId <= Z_MODEL_DESCRIPTION )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBasicModelProperties::GetValue( const int nPropId, DWORD& dwValue ) const
{
    dwValue; // unused

    if ( nPropId >= Z_MODEL_NAME && nPropId <= Z_MODEL_DESCRIPTION )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBasicModelProperties::GetValue( const int nPropId, float& fValue ) const
{
    fValue; // unused

    if ( nPropId >= Z_MODEL_NAME && nPropId <= Z_MODEL_DESCRIPTION )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

//@mfunc | ZBBasicModelProperties | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBasicModelProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBasicModelProperties::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBasicModelProperties::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBasicModelProperties::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBasicModelProperties::SetValue(const int nPropId, const float fValue)
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

BOOL ZBBasicModelProperties::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_MODEL_NAME:
        {
            m_ModelName = lpszValue;
            break;
        }

        case Z_MODEL_DESCRIPTION:
        {
            m_ModelDescription = lpszValue;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBasicModelProperties::SetValue( const int nPropId, const int nValue )
{
    switch ( nPropId )
    {
        case Z_MODEL_NAME:
        case Z_MODEL_DESCRIPTION:
        {
            throw new CODPropertyConversionException();
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBasicModelProperties::SetValue( const int nPropId, const UINT nValue )
{
    nValue; // unused

    if ( nPropId >= Z_MODEL_NAME && nPropId <= Z_MODEL_DESCRIPTION )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBasicModelProperties::SetValue( const int nPropId, const DWORD dwValue )
{
    dwValue; // unused

    if ( nPropId >= Z_MODEL_NAME && nPropId <= Z_MODEL_DESCRIPTION )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBasicModelProperties::SetValue( const int nPropId, const float fValue )
{
    fValue; // unused

    if ( nPropId >= Z_MODEL_NAME && nPropId <= Z_MODEL_DESCRIPTION )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

// **************************************************************************************************************
// *                                    ZBBasicModelProperties Property meta-data                                *
// **************************************************************************************************************

bool ZBBasicModelProperties::RegisterProperties()
{
    static bool propsRegistered = false;
    
    if ( !propsRegistered )
    {
        bool success = true;

        if ( success )
        {
            success = RegisterProperty( Z_MODEL_NAME,
                                        IDS_Z_MODEL_NAME_NAME,
                                        IDS_Z_MODEL_NAME_DESC,
                                        _PropertyAccessor( &ZBBasicModelProperties::GetModelName,
                                                           &ZBBasicModelProperties::SetModelName ),
                                        VT_BSTR,
                                        PROP_DIRECT );
        }

        if ( success )
        {
            success = RegisterProperty( Z_MODEL_DESCRIPTION,
                                        IDS_Z_MODEL_DESCRIPTION_NAME,
                                        IDS_Z_MODEL_DESCRIPTION_DESC,
                                        _PropertyAccessor( &ZBBasicModelProperties::GetModelDescription,
                                                           &ZBBasicModelProperties::SetModelDescription ),
                                        VT_BSTR,
                                        PROP_DIRECT );
        }

        if (!success)
        {
            ZBBasicModelProperties::GetPropertyMap().DeleteAll();
        }

        propsRegistered = success;
    }

    return propsRegistered;
}

// **************************************************************************************************************
// *                                        ZBBasicModelProperties diagnostics                                    *
// **************************************************************************************************************

#ifdef _DEBUG
void ZBBasicModelProperties::AssertValid() const
{
    CODIntProperty::AssertValid();
}

void ZBBasicModelProperties::Dump( CDumpContext& dc ) const
{
    CODIntProperty::Dump( dc );
}
#endif //_DEBUG

// **************************************************************************************************************
// *                                    ZBBasicModelProperties serialization                                    *
// **************************************************************************************************************

//@mfunc Serializes the orientation properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBasicModelProperties::Serialize( CArchive& ar )
{
    CODIntProperty::Serialize( ar );

    if ( ar.IsStoring() )
    {
        PUT_SCHEMA( ar, ZBBasicModelProperties );
        ar << m_ModelName;
        ar << m_ModelDescription;
    }
    else
    {
        UINT nSchema;
        GET_SCHEMA( ar, nSchema );
        ar >> m_ModelName;
        ar >> m_ModelDescription;
    }
}
