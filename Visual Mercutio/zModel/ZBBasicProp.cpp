// **************************************************************************************************************
// * @doc ZBBasicProperties                                                                                        *
// * @module ZBBasicProp.cpp | Implementation of the <c ZBBPProcessProperties> class.                            *
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
#include "ZBBasicProp.h"

#include "zModel\ProcGraphModelDoc.h"

// Resource include
#include "zRBProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 17 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZBBasicProperties, CODIntProperty, def_Version )

using namespace sfl;

// **************************************************************************************************************
// *                                ZBBasicProperties construction/destruction                                    *
// **************************************************************************************************************

//@mfunc | ZBBasicProperties | ZBBasicProperties | Constructor.
//
//@syntax ZBBasicProperties::ZBBasicProperties(int nId);
//@syntax ZBBasicProperties::ZBBasicProperties(const ZBBasicProperties& propBasic);
//
//@parmopt int | nId | OD_PROP_ORIENTATION | The identifier of the property.
//@parm ZBBasicProperties& | propBasic | The orientation property to copy.
ZBBasicProperties::ZBBasicProperties( int nId )
    : CODIntProperty( nId )
{
    m_SymbolName        = _T( "" );
    m_SymbolDescription = _T( "" );
    m_SymbolNumber        = -1;
    m_SymbolRiskLevel    = _T( "" );

    VERIFY( RegisterProperties() );
}

ZBBasicProperties::ZBBasicProperties( const ZBBasicProperties& propBasic )
    : CODIntProperty( propBasic.GetId() )
{
    *this = propBasic;

    VERIFY( RegisterProperties() );
}

//@mfunc Destructor.
ZBBasicProperties::~ZBBasicProperties()
{
}

CString ZBBasicProperties::GetSymbolNumberStr() const
{
    CString Number;

    if ( GetValue( Z_SYMBOL_NUMBER, Number ) )
    {
        return Number;
    }

    return _T( "" );
}

void ZBBasicProperties::SetSymbolNumber( const CString valueStr )
{
    SetValue( Z_SYMBOL_NUMBER, valueStr );
}

// **************************************************************************************************************
// *                                        ZBBasicProperties operations                                        *
// **************************************************************************************************************

//@mfunc Compare the property identifier with another identifier.
//@rdesc BOOL
//@parm Property identifier to compare to.
BOOL ZBBasicProperties::CompareId( const int nId ) const
{
    int nIdMin = m_nId;
    int nIdMax = m_nId + Z_SYMBOL_NUMBER;

    return ( nId >= nIdMin && nId <= nIdMax );
}

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBasicProperties& ZBBasicProperties::operator=( const ZBBasicProperties& propBasic )
{
    SetSymbolName        ( propBasic.GetSymbolName() );
    SetSymbolDescription( propBasic.GetSymbolDescription() );
    SetSymbolNumber        ( propBasic.GetSymbolNumber() );
    SetSymbolRiskLevel    ( propBasic.GetSymbolRiskLevel() );

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBasicProperties::operator==( const ZBBasicProperties propBasic ) const
{
    return ( GetSymbolName()        == propBasic.GetSymbolName()        &&
             GetSymbolDescription()    == propBasic.GetSymbolDescription()    &&
             GetSymbolNumber()        == propBasic.GetSymbolNumber()        &&
             GetSymbolRiskLevel()    == propBasic.GetSymbolRiskLevel() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBasicProperties::Merge( CODProperty* pProperty, DWORD dwChangeFlags )
{
    ZBBasicProperties* pOrientationProp = (ZBBasicProperties*)pProperty;

    if ( pOrientationProp )
    {
        if ( dwChangeFlags & Z_CHANGE_SYMBOL_NAME )
        {
            m_SymbolName = pOrientationProp->GetSymbolName();
        }

        if ( dwChangeFlags & Z_CHANGE_SYMBOL_DESCRIPTION )
        {
            m_SymbolDescription = pOrientationProp->GetSymbolDescription();
        }

        if ( dwChangeFlags & Z_CHANGE_SYMBOL_NUMBER )
        {
            m_SymbolNumber = pOrientationProp->GetSymbolNumber();
        }

        // JMR-MODIF - Le 22 juiééet 2007 - Ajout de la nouvelle propriété de partage pour le niveau du risque.
        if ( dwChangeFlags & Z_CHANGE_SYMBOL_RISK_LEVEL )
        {
            m_SymbolRiskLevel = pOrientationProp->GetSymbolRiskLevel();
        }
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf CODFillProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBasicProperties::IsEqual( CODProperty* pProp )
{
    if ( GetId() == pProp->GetId() )
    {
        ZBBasicProperties* pOrientationProp = (ZBBasicProperties*)pProp;

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

//@mfunc | ZBBasicProperties | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBasicProperties::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBasicProperties::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBasicProperties::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBasicProperties::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBasicProperties::GetValue(const int nPropId, float& fValue) const
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

BOOL ZBBasicProperties::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_SYMBOL_NAME:
        {
            strValue = m_SymbolName;
            break;
        }

        case Z_SYMBOL_DESCRIPTION:
        {
            strValue = m_SymbolDescription;
            break;
        }

        case Z_SYMBOL_NUMBER:
        {
            strValue.Format( _T( "%d" ), m_SymbolNumber );
            break;
        }

        // JMR-MODIF - Le 22 juillet 2007 - Prise en charge de la nouvelle propriété "Niveau du risque".
        case Z_SYMBOL_RISK_LEVEL:
        {
            strValue = m_SymbolRiskLevel;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBasicProperties::GetValue( const int nPropId, int& nValue ) const
{
    switch ( nPropId )
    {
        case Z_SYMBOL_NUMBER:
        {
            nValue = m_SymbolNumber;
            break;
        }

        case Z_SYMBOL_NAME:
        case Z_SYMBOL_DESCRIPTION:
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

BOOL ZBBasicProperties::GetValue( const int nPropId, UINT& nValue ) const
{
    nValue; // unused

    if ( nPropId >= Z_SYMBOL_NAME && nPropId <= Z_SYMBOL_NUMBER )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBasicProperties::GetValue( const int nPropId, DWORD& dwValue ) const
{
    dwValue; // unused

    if ( nPropId >= Z_SYMBOL_NAME && nPropId <= Z_SYMBOL_NUMBER )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBasicProperties::GetValue( const int nPropId, float& fValue ) const
{
    fValue; // unused

    if ( nPropId >= Z_SYMBOL_NAME && nPropId <= Z_SYMBOL_NUMBER )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

//@mfunc | ZBBasicProperties | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBasicProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBasicProperties::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBasicProperties::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBasicProperties::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBasicProperties::SetValue(const int nPropId, const float fValue)
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

BOOL ZBBasicProperties::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_SYMBOL_NAME:
        {
            m_SymbolName = lpszValue;
            break;
        }

        case Z_SYMBOL_DESCRIPTION:
        {
            m_SymbolDescription = lpszValue;
            break;
        }

        case Z_SYMBOL_NUMBER:
        {
            m_SymbolNumber = atoi( lpszValue );
            break;
        }

        // JMR-MODIF - Le 22 juillet 2007 - Prise en charge de la nouvelle propriété "Niveau du risque".
        case Z_SYMBOL_RISK_LEVEL:
        {
            m_SymbolRiskLevel = lpszValue;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBasicProperties::SetValue( const int nPropId, const int nValue )
{
    switch ( nPropId )
    {
        case Z_SYMBOL_NUMBER:
        {
            m_SymbolNumber = nValue;
            break;
        }

        case Z_SYMBOL_NAME:
        case Z_SYMBOL_DESCRIPTION:
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

BOOL ZBBasicProperties::SetValue( const int nPropId, const UINT nValue )
{
    nValue; // unused

    if ( nPropId >= Z_SYMBOL_NAME && nPropId <= Z_SYMBOL_NUMBER )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBasicProperties::SetValue( const int nPropId, const DWORD dwValue )
{
    dwValue; // unused

    if ( nPropId >= Z_SYMBOL_NAME && nPropId <= Z_SYMBOL_NUMBER )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBasicProperties::SetValue( const int nPropId, const float fValue )
{
    fValue; // unused

    if ( nPropId >= Z_SYMBOL_NAME && nPropId <= Z_SYMBOL_NUMBER )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

// **************************************************************************************************************
// *                                    ZBBasicProperties Property meta-data                                    *
// **************************************************************************************************************

bool ZBBasicProperties::RegisterProperties()
{
    static bool propsRegistered = false;

    if ( !propsRegistered )
    {
        bool success = true;

        if ( success )
        {
            success = RegisterProperty( Z_SYMBOL_NAME,
                                        IDS_Z_SYMBOL_NAME_NAME,
                                        IDS_Z_SYMBOL_NAME_DESC,
                                        _PropertyAccessor( &ZBBasicProperties::GetSymbolName,
                                                           &ZBBasicProperties::SetSymbolName ),
                                        VT_BSTR,
                                        PROP_DIRECT );
        }

        if ( success )
        {
            success = RegisterProperty( Z_SYMBOL_DESCRIPTION,
                                        IDS_Z_SYMBOL_DESCRIPTION_NAME,
                                        IDS_Z_SYMBOL_DESCRIPTION_DESC,
                                        _PropertyAccessor( &ZBBasicProperties::GetSymbolDescription,
                                                           &ZBBasicProperties::SetSymbolDescription ),
                                        VT_BSTR,
                                        PROP_DIRECT );
        }

        if ( success )
        {
            success = RegisterProperty( Z_SYMBOL_NUMBER,
                                        IDS_Z_SYMBOL_NUMBER_NAME,
                                        IDS_Z_SYMBOL_NUMBER_DESC,
                                        _PropertyAccessor( &ZBBasicProperties::GetSymbolNumber,
                                                           &ZBBasicProperties::SetSymbolNumber ),
                                        VT_INT,
                                        PROP_DIRECT );
        }

        // JMR-MODIF - Le 22 juillet 2007 - Ajout de la nouvelle propriété "Niveau du risque".
        if ( success )
        {
            success = RegisterProperty( Z_SYMBOL_RISK_LEVEL,
                                        IDS_Z_SYMBOL_RISK_LEVEL_NAME,
                                        IDS_Z_SYMBOL_RISK_LEVEL_DESC,
                                        _PropertyAccessor( &ZBBasicProperties::GetSymbolRiskLevel,
                                                           &ZBBasicProperties::SetSymbolRiskLevel ),
                                        VT_BSTR,
                                        PROP_DIRECT );
        }

        if ( !success )
        {
            ZBBasicProperties::GetPropertyMap().DeleteAll();
        }

        propsRegistered = success;
    }

    return propsRegistered;
}

// **************************************************************************************************************
// *                                        ZBBasicProperties diagnostics                                        *
// **************************************************************************************************************

#ifdef _DEBUG
void ZBBasicProperties::AssertValid() const
{
    CODIntProperty::AssertValid();
}

void ZBBasicProperties::Dump( CDumpContext& dc ) const
{
    CODIntProperty::Dump( dc );
}
#endif //_DEBUG

// **************************************************************************************************************
// *                                        ZBBasicProperties serialization                                        *
// **************************************************************************************************************

//@mfunc Serializes the orientation properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBasicProperties::Serialize( CArchive& ar )
{
    CODIntProperty::Serialize( ar );

    if ( ar.IsStoring() )
    {
        PUT_SCHEMA( ar, ZBBasicProperties );

        ar << m_SymbolName;
        ar << m_SymbolDescription;
        ar << m_SymbolNumber;

        // JMR-MODIF - Le 22 juillet 2007 - Sérialisation de la nouvelle propriété "Niveau du risque".
        if ( ar.m_pDocument )
        {
            if ( dynamic_cast<ZDBaseDocument*>( ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 27 )
            {
                ar << m_SymbolRiskLevel;
            }
        }
    }
    else
    {
        UINT nSchema;
        GET_SCHEMA( ar, nSchema );

        ar >> m_SymbolName;
        ar >> m_SymbolDescription;
        ar >> m_SymbolNumber;

        // JMR-MODIF - Le 22 juillet 2007 - Sérialisation de la nouvelle propriété "Niveau du risque".
        if ( ar.m_pDocument )
        {
            if ( dynamic_cast<ZDBaseDocument*>( ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 27 )
            {
                ar >> m_SymbolRiskLevel;
            }
        }
    }
}
