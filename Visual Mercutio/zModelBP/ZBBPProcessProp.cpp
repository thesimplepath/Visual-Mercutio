/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPProcessProperties
//@module ZBBPProcessProp.cpp | Implementation of the <c ZBBPProcessProperties> class.
// 
// zForms<tm>
// <nl>Copyright <cp> 2001 Advanced Dedicated Software, Inc. All rights reserved.
// 
// 
// Author: Dominique Aigroz
// <nl>Created: 03/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ZBBPProcessProp.h"

// Resources
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 8 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

using namespace sfl;

/////////////////////////////////////////////////////////////////////////////
// ZBBPProcessProperties construction/destruction

IMPLEMENT_SERIAL(ZBBPProcessProperties, CODIntProperty, g_DefVersion)

//@mfunc | ZBBPProcessProperties | ZBBPProcessProperties | Constructor.
//
//@syntax ZBBPProcessProperties::ZBBPProcessProperties(int nId);
//@syntax ZBBPProcessProperties::ZBBPProcessProperties(const ZBBPProcessProperties& propProcess);
//
//@parmopt int | nId | OD_PROP_FILL | The identifier of the property.
//@parm ZBBPProcessProperties& | propProcess | The fill property to copy.
ZBBPProcessProperties::ZBBPProcessProperties( int nId )
    : CODIntProperty( nId )
{
    m_ManagementCase = _T( "" );

    RegisterProperties();
}

ZBBPProcessProperties::ZBBPProcessProperties( const ZBBPProcessProperties& propProcess )
    : CODIntProperty( propProcess.GetId() )
{
    m_ManagementCase = propProcess.GetManagementCase();

    RegisterProperties();
}

//@mfunc Destructor.
ZBBPProcessProperties::~ZBBPProcessProperties()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPProcessProperties attributes

//@mfunc Sets the management case.
//@rdesc void
//@parm The new management case name.
void ZBBPProcessProperties::SetManagementCase( LPCTSTR lpszName )
{
    if ( lpszName != NULL )
    {
        m_ManagementCase = lpszName;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Management Case name pointer!\n" ) );
        ASSERT( FALSE );
    }
}

//@mfunc Sets the management case name.
//@rdesc void
//@parm The new management name.
void ZBBPProcessProperties::SetManagementCaseEx( const CString name )
{
    SetManagementCase( name );
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPProcessProperties operations

//@mfunc Compare the property identifier with another identifier.
//@rdesc BOOL
//@parm Property identifier to compare to.
BOOL ZBBPProcessProperties::CompareId( const int nId ) const
{
    int nIdMin = m_nId;
    int nIdMax = m_nId + Z_MANAGEMENT_CASE;

    return ( nId >= nIdMin && nId <= nIdMax );
}

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPProcessProperties& ZBBPProcessProperties::operator=( const ZBBPProcessProperties& propProcess )
{
    SetId( propProcess.GetId() );
    SetManagementCase( propProcess.GetManagementCase() );

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPProcessProperties::operator==( const ZBBPProcessProperties propProcess ) const
{
    return ( GetManagementCase() == propProcess.GetManagementCase() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPProcessProperties::Merge( CODProperty* pProperty, DWORD dwChangeFlags )
{
    ZBBPProcessProperties* pProcessProps = (ZBBPProcessProperties*)pProperty;

    if ( pProcessProps )
    {
        if ( dwChangeFlags & Z_CHANGE_MANAGEMENT_CASE )
        {
            m_ManagementCase = pProcessProps->GetManagementCase();
        }
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf ZBBPProcessProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPProcessProperties::IsEqual( CODProperty* pProp )
{
    if ( GetId() == pProp->GetId() )
    {
        ZBBPProcessProperties* pProcessProp = (ZBBPProcessProperties*)pProp;

        if ( pProcessProp )
        {
            return ( *this == *pProcessProp );
        }
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPProcessProperties | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPProcessProperties::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPProcessProperties::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPProcessProperties::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPProcessProperties::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPProcessProperties::GetValue(const int nPropId, float& fValue) const
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
//@comm See <t Fill Property Identifiers> for a list property IDs supported.
// This function will throw a <c CODPropertyConversionException> exception
// if the data type of the argument passed in is not compatible with the
// given property identifier.

BOOL ZBBPProcessProperties::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_MANAGEMENT_CASE:
        {
            strValue = m_ManagementCase;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPProcessProperties::GetValue( const int nPropId, int& nValue ) const
{
    switch ( nPropId )
    {
        case Z_MANAGEMENT_CASE:
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

BOOL ZBBPProcessProperties::GetValue( const int nPropId, UINT& nValue ) const
{
    switch ( nPropId )
    {
        case Z_MANAGEMENT_CASE:
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

BOOL ZBBPProcessProperties::GetValue( const int nPropId, DWORD& dwValue ) const
{
    switch ( nPropId )
    {
        case Z_MANAGEMENT_CASE:
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

BOOL ZBBPProcessProperties::GetValue( const int nPropId, float& fValue ) const
{
    switch ( nPropId )
    {
        case Z_MANAGEMENT_CASE:
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

//@mfunc | ZBBPProcessProperties | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPProcessProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPProcessProperties::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPProcessProperties::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPProcessProperties::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPProcessProperties::SetValue(const int nPropId, const float fValue)
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
//@comm See <t Fill Property Identifiers> for a list property IDs supported.
// This function will throw a <c CODPropertyConversionException> exception
// if the data type of the argument passed in is not compatible with the
// given property identifier.

BOOL ZBBPProcessProperties::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_MANAGEMENT_CASE:
        {
            m_ManagementCase = lpszValue;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPProcessProperties::SetValue( const int nPropId, const int nValue )
{
    switch ( nPropId )
    {
        case Z_MANAGEMENT_CASE:
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

BOOL ZBBPProcessProperties::SetValue( const int nPropId, const UINT nValue )
{
    switch ( nPropId )
    {
        case Z_MANAGEMENT_CASE:
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

BOOL ZBBPProcessProperties::SetValue( const int nPropId, const DWORD dwValue )
{
    switch ( nPropId )
    {
        case Z_MANAGEMENT_CASE:
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

BOOL ZBBPProcessProperties::SetValue( const int nPropId, const float fValue )
{
    switch ( nPropId )
    {
        case Z_MANAGEMENT_CASE:
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

/////////////////////////////////////////////////////////////////////////////
// ZBBPProcessProperties Property meta-data

bool ZBBPProcessProperties::RegisterProperties()
{
    static bool propsRegistered = false;

    if ( !propsRegistered )
    {
        bool success = RegisterProperty( Z_MANAGEMENT_CASE,
                                         IDS_Z_MANAGEMENT_CASE_NAME,
                                         IDS_Z_MANAGEMENT_CASE_DESC,
                                         _PropertyAccessor( &ZBBPProcessProperties::GetManagementCase,
                                                            &ZBBPProcessProperties::SetManagementCaseEx ),
                                         VT_BSTR,
                                         PROP_DIRECT );

        if ( !success )
        {
            ZBBPProcessProperties::GetPropertyMap().DeleteAll();
        }

        propsRegistered = success;
    }

    return propsRegistered;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPProcessProperties diagnostics

#ifdef _DEBUG
void ZBBPProcessProperties::AssertValid() const
{
    CODIntProperty::AssertValid();
}

void ZBBPProcessProperties::Dump( CDumpContext& dc ) const
{
    CODIntProperty::Dump( dc );

    dc << _T( "Management case name = " ) << m_ManagementCase << _T( "\n" );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBBPProcessProperties serialization

//@mfunc Serializes the line properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPProcessProperties::Serialize( CArchive& ar )
{
    CODIntProperty::Serialize( ar );

    if ( ar.IsStoring() )
    {
        TRACE( _T( "ZBBPProcessProperties::Serialize : Start Save\n" ) );

        PUT_SCHEMA( ar, ZBBPProcessProperties );
        ar << m_ManagementCase;

        TRACE( _T( "ZBBPProcessProperties::Serialize : End Save\n" ) );
    }
    else
    {
        TRACE( _T( "ZBBPProcessProperties::Serialize : Start Read\n" ) );

        UINT nSchema;
        GET_SCHEMA( ar, nSchema );
        ar >> m_ManagementCase;

        TRACE( _T( "ZBBPProcessProperties::Serialize : End Read\n" ) );
    }
}
