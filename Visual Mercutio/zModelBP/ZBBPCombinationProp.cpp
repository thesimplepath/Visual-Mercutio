/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPCombinationProperties
//@module ZBBPCombinationProp.cpp | Implementation of the <c ZBBPCombinationProperties> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// Author: Dom
// <nl>Created: 05/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ZBBPCombinationProp.h"

#include "zBaseLib\ZBTokenizer.h"

#include "zBaseLib\BaseDoc.h"

// Resources
#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace sfl;

// JMR-MODIF - Le 6 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBBPCombinationProperties construction/destruction

IMPLEMENT_SERIAL(ZBBPCombinationProperties, CObject, g_DefVersion)

//@mfunc | ZBBPCombinationProperties | ZBBPCombinationProperties | Constructor.
//
//@syntax ZBBPCombinationProperties::ZBBPCombinationProperties(int nId);
//@syntax ZBBPCombinationProperties::ZBBPCombinationProperties(const ZBBPCombinationProperties& propProcess);
//
//@parmopt int | nId | OD_PROP_FILL | The identifier of the property.
//@parm ZBBPCombinationProperties& | propProcess | The fill property to copy.
ZBBPCombinationProperties::ZBBPCombinationProperties()
{
    m_CombinationName            = _T( "" );
    m_CombinationDeliverables    = _T( "" );
    m_CombinationActivationPerc = 0;
    m_CombinationMaster            = _T( "" );
}

ZBBPCombinationProperties::ZBBPCombinationProperties( const ZBBPCombinationProperties& propProcess )
{
    m_CombinationName            = propProcess.GetCombinationName();
    m_CombinationDeliverables    = propProcess.GetCombinationDeliverables();
    m_CombinationActivationPerc    = propProcess.GetCombinationActivationPerc();
    m_CombinationMaster            = propProcess.GetCombinationMaster();
}

//@mfunc Destructor.
ZBBPCombinationProperties::~ZBBPCombinationProperties()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPCombinationProperties operations

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPCombinationProperties& ZBBPCombinationProperties::operator=( const ZBBPCombinationProperties& propProcess )
{
    SetCombinationName            ( propProcess.GetCombinationName() );
    SetCombinationDeliverables    ( propProcess.GetCombinationDeliverables() );
    SetCombinationActivationPerc( propProcess.GetCombinationActivationPerc() );
    SetCombinationMaster        ( propProcess.GetCombinationMaster() );

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPCombinationProperties::operator==( const ZBBPCombinationProperties propProcess ) const
{
    return ( GetCombinationName()            == propProcess.GetCombinationName()                &&
             GetCombinationDeliverables()    == propProcess.GetCombinationDeliverables()        &&
             GetCombinationActivationPerc()    == propProcess.GetCombinationActivationPerc()    &&
             GetCombinationMaster()            == propProcess.GetCombinationMaster() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPCombinationProperties::Merge( ZBBPCombinationProperties* pProperty, DWORD dwChangeFlags )
{
    if ( pProperty )
    {
        if ( dwChangeFlags & Z_CHANGE_COMBINATION_NAME )
        {
            m_CombinationName = pProperty->GetCombinationName();
        }

        if ( dwChangeFlags & Z_CHANGE_COMBINATION_DELIVERABLES )
        {
            m_CombinationDeliverables = pProperty->GetCombinationDeliverables();
        }

        if ( dwChangeFlags & Z_CHANGE_COMBINATION_ACTIVATION_PERC )
        {
            m_CombinationActivationPerc = pProperty->GetCombinationActivationPerc();
        }

        if ( dwChangeFlags & Z_CHANGE_COMBINATION_MASTER )
        {
            m_CombinationMaster = pProperty->GetCombinationMaster();
        }
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf ZBBPCombinationProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPCombinationProperties::IsEqual( ZBBPCombinationProperties* pProp )
{
    if ( pProp != NULL )
    {
        return ( *this == *pProp );
    }

    return FALSE;
}

bool ZBBPCombinationProperties::IsDeliverableInCombination( LPCTSTR lpszValue )
{
    ZBTokenizer token;    // Initialize the token with ; as separator

    CString str = token.GetFirstToken( lpszValue );
    
    // Run through all tokens
    while ( !str.IsEmpty() )
    {
        // If we found the same deliverable,
        // then sets the Found flag to true
        if ( str == lpszValue )
        {
            return true;
        }

        // Get the next token
        str = token.GetNextToken();
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPCombinationProperties attributes

void ZBBPCombinationProperties::SetCombinationName( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_CombinationName = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Combination name pointer!\n" ) );
        ASSERT( FALSE );
    }
}

void ZBBPCombinationProperties::SetCombinationNameEx( const CString value )
{
    SetCombinationName( value );
}

void ZBBPCombinationProperties::SetCombinationDeliverables( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_CombinationDeliverables = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Combination Deliverables list pointer!\n" ) );
        ASSERT( FALSE );
    }
}

void ZBBPCombinationProperties::SetCombinationDeliverablesEx( const CString value )
{
    SetCombinationDeliverables( value );
}

void ZBBPCombinationProperties::SetCombinationMaster( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_CombinationMaster = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Combination master name pointer!\n" ) );
        ASSERT( FALSE );
    }
}

void ZBBPCombinationProperties::SetCombinationMasterEx( const CString value )
{
    SetCombinationMaster( value );
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPCombinationProperties | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPCombinationProperties::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPCombinationProperties::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPCombinationProperties::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPCombinationProperties::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPCombinationProperties::GetValue(const int nPropId, float& fValue) const
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

BOOL ZBBPCombinationProperties::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_COMBINATION_NAME:
        {
            strValue = m_CombinationName;
            break;
        }

        case Z_COMBINATION_DELIVERABLES:
        {
            strValue = m_CombinationDeliverables;
            break;
        }

        case Z_COMBINATION_MASTER:
        {
            strValue = m_CombinationMaster;
            break;
        }

        default:
        {
            ASSERT( FALSE );
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCombinationProperties::GetValue( const int nPropId, int& nValue ) const
{
    switch ( nPropId )
    {
        case Z_COMBINATION_NAME:
        case Z_COMBINATION_DELIVERABLES:
        case Z_COMBINATION_ACTIVATION_PERC:
        case Z_COMBINATION_MASTER:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCombinationProperties::GetValue( const int nPropId, UINT& nValue ) const
{
    switch ( nPropId )
    {
        case Z_COMBINATION_NAME:
        case Z_COMBINATION_DELIVERABLES:
        case Z_COMBINATION_ACTIVATION_PERC:
        case Z_COMBINATION_MASTER:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCombinationProperties::GetValue( const int nPropId, DWORD& dwValue ) const
{
    switch ( nPropId )
    {
        case Z_COMBINATION_NAME:
        case Z_COMBINATION_DELIVERABLES:
        case Z_COMBINATION_ACTIVATION_PERC:
        case Z_COMBINATION_MASTER:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCombinationProperties::GetValue( const int nPropId, float& fValue ) const
{
    switch ( nPropId )
    {
        case Z_COMBINATION_NAME:
        case Z_COMBINATION_DELIVERABLES:
        case Z_COMBINATION_MASTER:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        case Z_COMBINATION_ACTIVATION_PERC:
        {
            fValue = m_CombinationActivationPerc;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

//@mfunc | ZBBPCombinationProperties | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPCombinationProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPCombinationProperties::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPCombinationProperties::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPCombinationProperties::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPCombinationProperties::SetValue(const int nPropId, const float fValue)
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

BOOL ZBBPCombinationProperties::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_COMBINATION_NAME:
        {
            m_CombinationName = lpszValue;
            break;
        }

        case Z_COMBINATION_DELIVERABLES:
        {
            m_CombinationDeliverables = lpszValue;
            break;
        }

        case Z_COMBINATION_MASTER:
        {
            m_CombinationMaster = lpszValue;
            break;
        }

        default:
        {
            ASSERT( FALSE );
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCombinationProperties::SetValue( const int nPropId, const int nValue )
{
    switch ( nPropId )
    {
        case Z_COMBINATION_NAME:
        case Z_COMBINATION_DELIVERABLES:
        case Z_COMBINATION_ACTIVATION_PERC:
        case Z_COMBINATION_MASTER:
        {
            ASSERT( FALSE );
            return FALSE;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCombinationProperties::SetValue( const int nPropId, const UINT nValue )
{
    switch ( nPropId )
    {
        case Z_COMBINATION_NAME:
        case Z_COMBINATION_DELIVERABLES:
        case Z_COMBINATION_ACTIVATION_PERC:
        case Z_COMBINATION_MASTER:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCombinationProperties::SetValue( const int nPropId, const DWORD dwValue )
{
    switch ( nPropId )
    {
        case Z_COMBINATION_NAME:
        case Z_COMBINATION_DELIVERABLES:
        case Z_COMBINATION_ACTIVATION_PERC:
        case Z_COMBINATION_MASTER:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCombinationProperties::SetValue( const int nPropId, const float fValue )
{
    switch ( nPropId )
    {
        case Z_COMBINATION_NAME:
        case Z_COMBINATION_DELIVERABLES:
        case Z_COMBINATION_MASTER:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        case Z_COMBINATION_ACTIVATION_PERC:
        {
            m_CombinationActivationPerc = fValue;
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
// ZBBPCombinationProperties Property meta-data 

/////////////////////////////////////////////////////////////////////////////
// ZBBPCombinationProperties diagnostics

#ifdef _DEBUG
void ZBBPCombinationProperties::AssertValid() const
{
    CObject::AssertValid();
}

void ZBBPCombinationProperties::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );

    dc << _T( "Name = " )            << m_CombinationName            << _T( "\n" );
    dc << _T( "Deliverables = " )    << m_CombinationDeliverables    << _T( "\n" );
    dc << _T( "Master = " )            << m_CombinationMaster            << _T( "\n" );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ZBBPCombinationProperties serialization

//@mfunc Serializes the line properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPCombinationProperties::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        TRACE( _T( "ZBBPCombinationProperties::Serialize : Start Save\n" ) );

        ar << m_CombinationName;
        ar << m_CombinationDeliverables;
        ar << m_CombinationActivationPerc;
        ar << m_CombinationMaster;

        TRACE( _T( "ZBBPCombinationProperties::Serialize : End Save\n" ) );
    }
    else
    {
        TRACE( _T( "ZBBPCombinationProperties::Serialize : Start Read\n" ) );

        ar >> m_CombinationName;
        ar >> m_CombinationDeliverables;
        ar >> m_CombinationActivationPerc;

        // Check the version for new file format.
        if ( ar.m_pDocument &&
             dynamic_cast<ZDBaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 19 )
        {
            ar >> m_CombinationMaster;
        }
        else
        {
            m_CombinationMaster.Empty();
        }

        TRACE( _T( "ZBBPCombinationProperties::Serialize : End Read\n" ) );
    }
}
