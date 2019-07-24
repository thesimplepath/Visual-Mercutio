/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPDecisionListProperties
//@module ZBBPDecisionListProp.cpp | Implementation of the <c ZBBPDecisionListProperties> class.
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

#include "ZBBPDecisionListProp.h"

// Resources
#include "zRMdlBP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 13 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

using namespace sfl;

/////////////////////////////////////////////////////////////////////////////
// ZBBPDecisionListProperties construction/destruction

IMPLEMENT_SERIAL(ZBBPDecisionListProperties, CODIntProperty, g_DefVersion)

//@mfunc | ZBBPDecisionListProperties | ZBBPDecisionListProperties | Constructor.
//
//@syntax ZBBPDecisionListProperties::ZBBPDecisionListProperties(int nId);
//@syntax ZBBPDecisionListProperties::ZBBPDecisionListProperties(const ZBBPDecisionListProperties& propProcess);
//
//@parmopt int | nId | OD_PROP_FILL | The identifier of the property.
//@parm ZBBPDecisionListProperties& | propProcess | The fill property to copy.
ZBBPDecisionListProperties::ZBBPDecisionListProperties( int nId )
    : CODIntProperty( nId )
{
    m_DecisionList = _T( "" );

    RegisterProperties();
}

ZBBPDecisionListProperties::ZBBPDecisionListProperties( const ZBBPDecisionListProperties& propProcess )
    : CODIntProperty( propProcess.GetId() )
{
    m_DecisionList  = propProcess.GetDecisionList();

    RegisterProperties();
}

//@mfunc Destructor.
ZBBPDecisionListProperties::~ZBBPDecisionListProperties()
{
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
void ZBBPDecisionListProperties::SetDecisionList( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_DecisionList = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Decision List pointer!\n" ) );
        ASSERT( FALSE );
    }
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
void ZBBPDecisionListProperties::SetDecisionListEx( const CString value )
{
    SetDecisionList( value );
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPDecisionListProperties operations

//@mfunc Compare the property identifier with another identifier.
//@rdesc BOOL
//@parm Property identifier to compare to.
BOOL ZBBPDecisionListProperties::CompareId( const int nId ) const
{
    int nIdMin = m_nId;
    int nIdMax = m_nId + Z_DECISION_LIST;

    return ( nId >= nIdMin && nId <= nIdMax );
}

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPDecisionListProperties& ZBBPDecisionListProperties::operator=( const ZBBPDecisionListProperties& propProcess )
{
    SetId( propProcess.GetId() );
    SetDecisionList( propProcess.GetDecisionList() );

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPDecisionListProperties::operator==( const ZBBPDecisionListProperties propProcess ) const
{
    return ( GetDecisionList() == propProcess.GetDecisionList() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPDecisionListProperties::Merge( CODProperty* pProperty, DWORD dwChangeFlags )
{
    ZBBPDecisionListProperties* pProcessProps = (ZBBPDecisionListProperties*)pProperty;

    if ( pProcessProps )
    {
        if ( dwChangeFlags & Z_CHANGE_DECISION_LIST )
        {
            m_DecisionList = pProcessProps->GetDecisionList();
        }
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf ZBBPDecisionListProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPDecisionListProperties::IsEqual( CODProperty* pProp )
{
    if ( GetId() == pProp->GetId() )
    {
        ZBBPDecisionListProperties* pProcessProp = (ZBBPDecisionListProperties*)pProp;

        if ( pProcessProp )
        {
            return ( *this == *pProcessProp );
        }
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPDecisionListProperties | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPDecisionListProperties::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPDecisionListProperties::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPDecisionListProperties::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPDecisionListProperties::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPDecisionListProperties::GetValue(const int nPropId, float& fValue) const
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

BOOL ZBBPDecisionListProperties::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_DECISION_LIST:
        {
            strValue = m_DecisionList;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPDecisionListProperties::GetValue( const int nPropId, int& nValue ) const
{
    switch ( nPropId )
    {
        case Z_DECISION_LIST:
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

BOOL ZBBPDecisionListProperties::GetValue( const int nPropId, UINT& nValue ) const
{
    switch ( nPropId )
    {
        case Z_DECISION_LIST:
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

BOOL ZBBPDecisionListProperties::GetValue( const int nPropId, DWORD& dwValue ) const
{
    switch ( nPropId )
    {
        case Z_DECISION_LIST:
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

BOOL ZBBPDecisionListProperties::GetValue( const int nPropId, float& fValue ) const
{
    switch ( nPropId )
    {
        case Z_DECISION_LIST:
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

//@mfunc | ZBBPDecisionListProperties | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPDecisionListProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPDecisionListProperties::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPDecisionListProperties::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPDecisionListProperties::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPDecisionListProperties::SetValue(const int nPropId, const float fValue)
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

BOOL ZBBPDecisionListProperties::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_DECISION_LIST:
        {
            m_DecisionList = lpszValue;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPDecisionListProperties::SetValue( const int nPropId, const int nValue )
{
    switch ( nPropId )
    {
        case Z_DECISION_LIST:
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

BOOL ZBBPDecisionListProperties::SetValue( const int nPropId, const UINT nValue )
{
    switch ( nPropId )
    {
        case Z_DECISION_LIST:
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

BOOL ZBBPDecisionListProperties::SetValue( const int nPropId, const DWORD dwValue )
{
    switch ( nPropId )
    {
        case Z_DECISION_LIST:
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

BOOL ZBBPDecisionListProperties::SetValue( const int nPropId, const float fValue )
{
    switch ( nPropId )
    {
        case Z_DECISION_LIST:
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
// ZBBPDecisionListProperties Property meta-data

bool ZBBPDecisionListProperties::RegisterProperties()
{
    static bool propsRegistered = false;

    if ( !propsRegistered )
    {
        bool success = true;

        if ( success )
        {
            success = RegisterProperty( Z_DECISION_LIST,
                                        IDS_Z_DECISION_LIST_NAME,
                                        IDS_Z_DECISION_LIST_DESC,
                                        _PropertyAccessor( &ZBBPDecisionListProperties::GetDecisionList,
                                                           &ZBBPDecisionListProperties::SetDecisionListEx ),
                                        VT_BSTR,
                                        PROP_DIRECT );
        }

        if ( !success )
        {
            ZBBPDecisionListProperties::GetPropertyMap().DeleteAll();
        }

        propsRegistered = success;
    }

    return propsRegistered;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPDecisionListProperties diagnostics

#ifdef _DEBUG
void ZBBPDecisionListProperties::AssertValid() const
{
    CODIntProperty::AssertValid();
}

void ZBBPDecisionListProperties::Dump( CDumpContext& dc ) const
{
    CODIntProperty::Dump( dc );

    dc << _T( "Decision list = " ) << m_DecisionList << _T( "\n" );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBBPDecisionListProperties serialization

//@mfunc Serializes the line properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPDecisionListProperties::Serialize( CArchive& ar )
{
    CODIntProperty::Serialize( ar );

    if ( ar.IsStoring() )
    {
        TRACE( _T( "ZBBPDecisionListProperties::Serialize : Start Save\n" ) );

        PUT_SCHEMA( ar, ZBBPDecisionListProperties );
        ar << m_DecisionList;

        TRACE( _T( "ZBBPDecisionListProperties::Serialize : End Save\n" ) );
    }
    else
    {
        TRACE( _T( "ZBBPDecisionListProperties::Serialize : Start Read\n" ) );

        UINT nSchema;
        GET_SCHEMA( ar, nSchema );
        ar >> m_DecisionList;

        TRACE( _T( "ZBBPDecisionListProperties::Serialize : End Read\n" ) );
    }
}
