/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPUnitProperties2
//@module ZBBPUnitProp2.cpp | Implementation of the <c ZBBPUnitProperties2> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 03/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ZBBPUnitProp2.h"

#include "zBaseLib\BaseDoc.h"

// Resources
#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 26 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

using namespace sfl;

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties2 construction/destruction

IMPLEMENT_SERIAL( ZBBPUnitProperties2, CObject, def_Version )

//@mfunc | ZBBPUnitProperties2 | ZBBPUnitProperties2 | Constructor.
//
//@syntax ZBBPUnitProperties2::ZBBPUnitProperties2(int nId);
//@syntax ZBBPUnitProperties2::ZBBPUnitProperties2(const ZBBPUnitProperties2& propProcess);
//
//@parmopt int | nId | OD_PROP_FILL | The identifier of the property.
//@parm ZBBPUnitProperties2& | propProcess | The fill property to copy.
ZBBPUnitProperties2::ZBBPUnitProperties2() 
{
    m_UnitName                = _T( "" );
    m_UnitCost                = 0;
    m_UnitGUID                = _T( "" );
    m_DoubleValidationType    = 0;
}

ZBBPUnitProperties2::ZBBPUnitProperties2( const ZBBPUnitProperties2& propProcess )
{
    *this = propProcess;
}

//@mfunc Destructor.
ZBBPUnitProperties2::~ZBBPUnitProperties2()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties2 attributes

//@mfunc Sets the task list.
//@rdesc void
//@parm The new task list.
void ZBBPUnitProperties2::SetUnitName( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_UnitName = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Task List pointer!\n" ) );
        ASSERT( FALSE );
    }
}

//@mfunc Sets the task list.
//@rdesc void
//@parm The new task list.
void ZBBPUnitProperties2::SetUnitNameEx( const CString value )
{
    SetUnitName( value );
}

//@mfunc Sets the unit guid.
//@rdesc void
//@parm The new unit guid.
void ZBBPUnitProperties2::SetUnitGUID( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_UnitGUID = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid unit GUID pointer!\n" ) );
        ASSERT( FALSE );
    }
}

//@mfunc Sets the unit guid.
//@rdesc void
//@parm The new unit guid.
void ZBBPUnitProperties2::SetUnitGUIDEx( const CString value )
{
    SetUnitGUID( value );
}

void ZBBPUnitProperties2::GetUnitDoubleValidationTypeStringArray( CStringArray& sar ) const
{
    CString s;
    s.LoadString( IDS_DOUBLEVALID_NONE );
    sar.Add( s );
    s.LoadString( IDS_DOUBLEVALID_EMPLOYEE );
    sar.Add( s );
    s.LoadString( IDS_DOUBLEVALID_MANAGER );
    sar.Add( s );
}

int ZBBPUnitProperties2::ConvertUnitDoubleValidationString2Type( const CString Type ) const
{
    CString s;
    s.LoadString( IDS_DOUBLEVALID_NONE );

    if ( s == Type )
    {
        return 0;
    }

    s.LoadString( IDS_DOUBLEVALID_EMPLOYEE );

    if ( s == Type )
    {
        return 1;
    }

    s.LoadString( IDS_DOUBLEVALID_MANAGER );

    if ( s == Type )
    {
        return 2;
    }

    // Error
    return -1;
}

CString ZBBPUnitProperties2::GetUnitDoubleValidationTypeString( const int Value ) const
{
    CString s;

    switch ( Value )
    {
        case 0:
        {
            s.LoadString( IDS_DOUBLEVALID_NONE );
            break;
        }

        case 1:
        {
            s.LoadString( IDS_DOUBLEVALID_EMPLOYEE );
            break;
        }

        case 2:
        {
            s.LoadString( IDS_DOUBLEVALID_MANAGER );
            break;
        }
    }

    return s;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties2 operations

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPUnitProperties2& ZBBPUnitProperties2::operator=( const ZBBPUnitProperties2& propProcess )
{
    SetUnitName( propProcess.GetUnitName() );
    SetUnitCost( propProcess.GetUnitCost() );
    SetUnitGUID( propProcess.GetUnitGUID() );
    SetUnitDoubleValidationType( propProcess.GetUnitDoubleValidationType() );

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPUnitProperties2::operator==( const ZBBPUnitProperties2 propProcess ) const
{
    return ( GetUnitName()                    == propProcess.GetUnitName()                    &&
             GetUnitCost()                    == propProcess.GetUnitCost()                    &&
             GetUnitDoubleValidationType()    == propProcess.GetUnitDoubleValidationType()    &&
             GetUnitGUID()                    == propProcess.GetUnitGUID() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPUnitProperties2::Merge( ZBBPUnitProperties2* pProperty, DWORD dwChangeFlags )
{
    if ( pProperty )
    {
        if ( dwChangeFlags & Z_CHANGE_UNIT_NAME )
        {
            m_UnitName = pProperty->GetUnitName();
        }

        if ( dwChangeFlags & Z_CHANGE_UNIT_COST )
        {
            m_UnitCost = pProperty->GetUnitCost();
        }

        if ( dwChangeFlags & Z_CHANGE_UNIT_GUID )
        {
            m_UnitGUID = pProperty->GetUnitGUID();
        }

        if ( dwChangeFlags & Z_CHANGE_UNIT_DOUBLE_VALIDATION )
        {
            m_DoubleValidationType = pProperty->GetUnitDoubleValidationType();
        }
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf ZBBPUnitProperties2::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPUnitProperties2::IsEqual( ZBBPUnitProperties2* pProp )
{
    if ( pProp )
    {
        return ( *this == *pProp );
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPUnitProperties2 | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPUnitProperties2::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPUnitProperties2::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPUnitProperties2::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPUnitProperties2::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPUnitProperties2::GetValue(const int nPropId, float& fValue) const
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

BOOL ZBBPUnitProperties2::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_UNIT_NAME:
        {
            strValue = m_UnitName;
            break;
        }

        case Z_UNIT_GUID:
        {
            strValue = m_UnitGUID;
            break;
        }

        default:
        {
            throw new CODPropertyConversionException();
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPUnitProperties2::GetValue( const int nPropId, int& nValue ) const
{
    switch ( nPropId )
    {
        case Z_UNIT_DOUBLE_VALIDATION:
        {
            nValue = m_DoubleValidationType;
            break;
        }

        case Z_UNIT_NAME:
        case Z_UNIT_COST:
        case Z_UNIT_GUID:
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

BOOL ZBBPUnitProperties2::GetValue( const int nPropId, UINT& nValue ) const
{
    switch ( nPropId )
    {
        case Z_UNIT_DOUBLE_VALIDATION:
        {
            nValue = m_DoubleValidationType;
            break;
        }

        case Z_UNIT_NAME:
        case Z_UNIT_COST:
        case Z_UNIT_GUID:
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

BOOL ZBBPUnitProperties2::GetValue( const int nPropId, DWORD& dwValue ) const
{
    switch ( nPropId )
    {
        case Z_UNIT_DOUBLE_VALIDATION:
        case Z_UNIT_NAME:
        case Z_UNIT_COST:
        case Z_UNIT_GUID:
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

BOOL ZBBPUnitProperties2::GetValue( const int nPropId, float& fValue ) const
{
    switch ( nPropId )
    {
        case Z_UNIT_COST:
        {
            fValue = m_UnitCost;
            break;
        }

        case Z_UNIT_DOUBLE_VALIDATION:
        case Z_UNIT_NAME:
        case Z_UNIT_GUID:
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

//@mfunc | ZBBPUnitProperties2 | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPUnitProperties2::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPUnitProperties2::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPUnitProperties2::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPUnitProperties2::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPUnitProperties2::SetValue(const int nPropId, const float fValue)
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

BOOL ZBBPUnitProperties2::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_UNIT_NAME:
        {
            m_UnitName = lpszValue;
            break;
        }

        case Z_UNIT_GUID:
        {
            m_UnitGUID = lpszValue;
            break;
        }

        default:
        {
            throw new CODPropertyConversionException();
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPUnitProperties2::SetValue( const int nPropId, const int nValue )
{
    switch ( nPropId )
    {
        case Z_UNIT_DOUBLE_VALIDATION:
        {
            m_DoubleValidationType = nValue;
            break;
        }

        case Z_UNIT_NAME:
        case Z_UNIT_COST:
        case Z_UNIT_GUID:
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

BOOL ZBBPUnitProperties2::SetValue( const int nPropId, const UINT nValue )
{
    switch ( nPropId )
    {
        case Z_UNIT_DOUBLE_VALIDATION:
        {
            m_DoubleValidationType = nValue;
            break;
        }

        case Z_UNIT_NAME:
        case Z_UNIT_COST:
        case Z_UNIT_GUID:
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

BOOL ZBBPUnitProperties2::SetValue( const int nPropId, const DWORD dwValue )
{
    switch ( nPropId )
    {
        case Z_UNIT_DOUBLE_VALIDATION:
        case Z_UNIT_NAME:
        case Z_UNIT_COST:
        case Z_UNIT_GUID:
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

BOOL ZBBPUnitProperties2::SetValue( const int nPropId, const float fValue )
{
    switch ( nPropId )
    {
        case Z_UNIT_COST:
        {
            m_UnitCost = fValue;
            break;
        }

        case Z_UNIT_DOUBLE_VALIDATION:
        case Z_UNIT_NAME:
        case Z_UNIT_GUID:
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
// ZBBPUnitProperties2 diagnostics

#ifdef _DEBUG
void ZBBPUnitProperties2::AssertValid() const
{
    CObject::AssertValid();
}

void ZBBPUnitProperties2::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );

    dc << _T( "Unit name = " ) << m_UnitName << _T( "\n" );
    dc << _T( "Unit Cost = " ) << m_UnitCost << _T( "\n" );
    dc << _T( "Unit GUID = " ) << m_UnitGUID << _T( "\n" );
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties2 serialization

//@mfunc Serializes the line properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPUnitProperties2::Serialize( CArchive& ar )
{
    CObject::Serialize( ar );

    if ( ar.IsStoring() )
    {
        TRACE( _T( "ZBBPUnitProperties2::Serialize : Start Save\n" ) );

        PUT_SCHEMA( ar, ZBBPUnitProperties2 );
        ar << m_UnitName;
        ar << m_UnitCost;
        ar << m_UnitGUID;
        ar << m_DoubleValidationType;

        TRACE( _T( "ZBBPUnitProperties2::Serialize : End Save\n" ) );
    }
    else
    {
        TRACE( _T( "ZBBPUnitProperties2::Serialize : Start Read\n" ) );

        UINT nSchema;
        GET_SCHEMA( ar, nSchema );

        if ( !ar.m_pDocument ||
             dynamic_cast<ZDBaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 19 )
        {
            ar >> m_UnitName;
            ar >> m_UnitCost;
            ar >> m_UnitGUID;
        }
        else
        {
            ar >> m_UnitName;
            ar >> m_UnitCost;
            m_UnitGUID.Empty();
        }

        if ( !ar.m_pDocument ||
             ( (ZDBaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 20 )
        {
            ar >> m_DoubleValidationType;
        }

        TRACE( _T( "ZBBPUnitProperties2::Serialize : End Read\n" ) );
    }
}
