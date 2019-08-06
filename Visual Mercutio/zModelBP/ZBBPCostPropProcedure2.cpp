/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropProcedure2.cpp : Implementation of ZBBPCostPropertiesProcedure2
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// Created:         05/2001
// Modified:     10/2001 for beta 2 version. Stop using CODProperties.
// Description:  ZBBPCostPropertiesProcedure2 cost properties for procedure
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBBPCostPropProcedure2.h"

#include "zBaseLib\PSS_BaseDocument.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 8 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropertiesProcedure2 construction/destruction

IMPLEMENT_SERIAL(ZBBPCostPropertiesProcedure2, CObject, g_DefVersion)

using namespace sfl;

//@mfunc | ZBBPCostPropertiesProcedure2 | ZBBPCostPropertiesProcedure2 | Constructor.
//
//@syntax ZBBPCostPropertiesProcedure2::ZBBPCostPropertiesProcedure2(int nId);
//@syntax ZBBPCostPropertiesProcedure2::ZBBPCostPropertiesProcedure2(const ZBBPCostPropertiesProcedure2& propBasic);
//
//@parmopt int | nId | OD_PROP_ORIENTATION | The identifier of the property.
//@parm ZBBPCostPropertiesProcedure2& | propBasic | The orientation property to copy.
ZBBPCostPropertiesProcedure2::ZBBPCostPropertiesProcedure2()
{
    m_Multiplier            = 1;
    m_ProcessingTime        = 0;
    m_UnitaryCost            = 0;
    m_ProcessingDuration    = 0;
    m_ProcessingDurationMax    = 0;
}

ZBBPCostPropertiesProcedure2::ZBBPCostPropertiesProcedure2( const ZBBPCostPropertiesProcedure2& propBasic )
{
    *this = propBasic;
}

//@mfunc Destructor.
ZBBPCostPropertiesProcedure2::~ZBBPCostPropertiesProcedure2()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropertiesProcedure2 operations

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPCostPropertiesProcedure2& ZBBPCostPropertiesProcedure2::operator=( const ZBBPCostPropertiesProcedure2& propBasic )
{
    SetMultiplier                ( propBasic.GetMultiplier() );
    SetProcessingTime            ( propBasic.GetProcessingTime() );
    SetUnitaryCost                ( propBasic.GetUnitaryCost() );
    SetProcessingDuration        ( propBasic.GetProcessingDuration() );
    SetProcessingDurationMax    ( propBasic.GetProcessingDurationMax() );

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPCostPropertiesProcedure2::operator==( const ZBBPCostPropertiesProcedure2 propBasic ) const
{
    return ( GetMultiplier()            == propBasic.GetMultiplier()            &&
             GetProcessingTime()        == propBasic.GetProcessingTime()        &&
             GetUnitaryCost()            == propBasic.GetUnitaryCost()            &&
             GetProcessingDuration()    == propBasic.GetProcessingDuration()    &&
             GetProcessingDurationMax()    == propBasic.GetProcessingDurationMax() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPCostPropertiesProcedure2::Merge( ZBBPCostPropertiesProcedure2* pProperty, DWORD dwChangeFlags )
{
    if ( pProperty )
    {
        if ( dwChangeFlags & Z_CHANGE_COST_MULTIPLIER )
        {
            m_Multiplier = pProperty->GetMultiplier();
        }

        if ( dwChangeFlags & Z_CHANGE_COST_PROCESSING_TIME )
        {
            m_ProcessingTime = pProperty->GetProcessingTime();
        }

        if ( dwChangeFlags & Z_CHANGE_COST_UNITARY_COST )
        {
            m_UnitaryCost = pProperty->GetUnitaryCost();
        }

        if ( dwChangeFlags & Z_CHANGE_COST_PROCESSING_DURATION )
        {
            m_ProcessingDuration = pProperty->GetProcessingDuration();
        }

        if ( dwChangeFlags & Z_CHANGE_COST_PROCESSING_DURATIONMAX )
        {
            m_ProcessingDurationMax = pProperty->GetProcessingDurationMax();
        }
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf CODFillProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPCostPropertiesProcedure2::IsEqual( ZBBPCostPropertiesProcedure2* pProp )
{
    if ( pProp )
    {
        return ( *this == *pProp );
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPCostPropertiesProcedure2 | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPCostPropertiesProcedure2::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPCostPropertiesProcedure2::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPCostPropertiesProcedure2::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPCostPropertiesProcedure2::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPCostPropertiesProcedure2::GetValue(const int nPropId, float& fValue) const
//@syntax BOOL ZBBPCostPropertiesProcedure2::GetValue(const int nPropId, double& dValue) const
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

BOOL ZBBPCostPropertiesProcedure2::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_COST_MULTIPLIER:
        {
            strValue.Format( _T( "%.0f" ) , m_Multiplier );
            break;
        }

        case Z_COST_PROCESSING_TIME:
        {
            strValue.Format( _T( "%.0f" ), m_ProcessingTime );
            break;
        }

        case Z_COST_UNITARY_COST:
        {
            strValue.Format( _T( "%.0f" ), m_UnitaryCost );
            break;
        }

        case Z_COST_PROCESSING_DURATION:
        {
            strValue.Format( _T( "%.0f" ), m_ProcessingDuration );
            break;
        }

        case Z_COST_PROCESSING_DURATIONMAX:
        {
            strValue.Format( _T( "%.0f" ), m_ProcessingDurationMax );
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

BOOL ZBBPCostPropertiesProcedure2::GetValue( const int nPropId, int& nValue ) const
{
    // Unused
    nValue;

    if ( nPropId >= Z_COST_MULTIPLIER && nPropId <= Z_COST_PROCESSING_DURATIONMAX )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPCostPropertiesProcedure2::GetValue( const int nPropId, UINT& nValue ) const
{
    // Unused
    nValue;

    if ( nPropId >= Z_COST_MULTIPLIER && nPropId <= Z_COST_PROCESSING_DURATIONMAX )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPCostPropertiesProcedure2::GetValue( const int nPropId, DWORD& dwValue ) const
{
    // Unused
    dwValue;

    if ( nPropId >= Z_COST_MULTIPLIER && nPropId <= Z_COST_PROCESSING_DURATIONMAX )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPCostPropertiesProcedure2::GetValue( const int nPropId, float& fValue ) const
{
    switch ( nPropId )
    {
        case Z_COST_MULTIPLIER:
        {
            fValue = m_Multiplier;
            break;
        }

        case Z_COST_UNITARY_COST:
        {
            fValue = m_UnitaryCost;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCostPropertiesProcedure2::GetValue( const int nPropId, double& dValue ) const
{
    switch ( nPropId )
    {
        case Z_COST_PROCESSING_TIME:
        {
            dValue = m_ProcessingTime;
            break;
        }

        case Z_COST_PROCESSING_DURATION:
        {
            dValue = m_ProcessingDuration;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

//@mfunc | ZBBPCostPropertiesProcedure2 | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPCostPropertiesProcedure2::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPCostPropertiesProcedure2::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPCostPropertiesProcedure2::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPCostPropertiesProcedure2::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPCostPropertiesProcedure2::SetValue(const int nPropId, const float fValue)
//@syntax BOOL ZBBPCostPropertiesProcedure2::SetValue(const int nPropId, const double dValue)
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

BOOL ZBBPCostPropertiesProcedure2::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_COST_MULTIPLIER:
        {
            m_Multiplier = static_cast<float>( atof( lpszValue ) );
            break;
        }

        case Z_COST_PROCESSING_TIME:
        {
            m_ProcessingTime = atof( lpszValue );
            break;
        }

        case Z_COST_UNITARY_COST:
        {
            m_UnitaryCost = static_cast<float>( atof( lpszValue ) );
            break;
        }

        case Z_COST_PROCESSING_DURATION:
        {
            m_ProcessingDuration = atof( lpszValue );
            break;
        }

        case Z_COST_PROCESSING_DURATIONMAX:
        {
            m_ProcessingDurationMax = atof( lpszValue );
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCostPropertiesProcedure2::SetValue( const int nPropId, const int nValue )
{
    // Unused
    nValue;

    if ( nPropId >= Z_COST_MULTIPLIER && nPropId <= Z_COST_PROCESSING_DURATIONMAX )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPCostPropertiesProcedure2::SetValue( const int nPropId, const UINT nValue )
{
    // Unused
    nValue;

    if ( nPropId >= Z_COST_MULTIPLIER && nPropId <= Z_COST_PROCESSING_DURATIONMAX )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPCostPropertiesProcedure2::SetValue( const int nPropId, const DWORD dwValue )
{
    // Unused
    dwValue;

    if ( nPropId >= Z_COST_MULTIPLIER && nPropId <= Z_COST_PROCESSING_DURATIONMAX )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPCostPropertiesProcedure2::SetValue( const int nPropId, const float fValue )
{
    switch ( nPropId )
    {
        case Z_COST_MULTIPLIER:
        {
            m_Multiplier = fValue;
            break;
        }

        case Z_COST_UNITARY_COST:
        {
            m_UnitaryCost = fValue;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCostPropertiesProcedure2::SetValue( const int nPropId, const double dValue )
{
    switch ( nPropId )
    {
        case Z_COST_PROCESSING_TIME:
        {
            m_ProcessingTime = dValue;
            break;
        }

        case Z_COST_PROCESSING_DURATION:
        {
            m_ProcessingDuration = dValue;
            break;
        }

        case Z_COST_PROCESSING_DURATIONMAX:
        {
            m_ProcessingDurationMax = dValue;
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
// ZBBPCostPropertiesProcedure2 diagnostics

#ifdef _DEBUG
void ZBBPCostPropertiesProcedure2::AssertValid() const
{
    CObject::AssertValid();
}

void ZBBPCostPropertiesProcedure2::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropertiesProcedure2 serialization

//@mfunc Serializes the orientation properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPCostPropertiesProcedure2::Serialize( CArchive& ar )
{
    CObject::Serialize( ar );

    if ( ar.IsStoring() )
    {
        TRACE( _T( "ZBBPCostPropertiesProcedure2::Serialize : Start Save\n" ) );

        PUT_SCHEMA( ar, ZBBPCostPropertiesProcedure2 );
        ar << m_Multiplier;
        ar << m_ProcessingTime;
        ar << m_UnitaryCost;
        ar << m_ProcessingDuration;
        ar << m_ProcessingDurationMax;

        TRACE( _T( "ZBBPCostPropertiesProcedure2::Serialize : End Save\n" ) );
    }
    else
    {
        TRACE( _T( "ZBBPCostPropertiesProcedure2::Serialize : Start Read\n" ) );

        UINT nSchema;
        GET_SCHEMA( ar, nSchema );
        ar >> m_Multiplier;
        ar >> m_ProcessingTime;
        ar >> m_UnitaryCost;

        if ( ar.m_pDocument &&
             ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 20 )
        {
            ar >> m_ProcessingDuration;
        }

        if ( ar.m_pDocument &&
             ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 21 )
        {
            ar >> m_ProcessingDurationMax;
        }

        TRACE( _T( "ZBBPCostPropertiesProcedure2::Serialize : End Read\n" ) );
    }
}
