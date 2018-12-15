/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropProcedure.cpp : Implementation of ZBBPSimPropertiesProcedure
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
// Description:  ZBBPSimPropertiesProcedure simulation properties for procedure
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBBPSimPropProcedure.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesProcedure construction/destruction

IMPLEMENT_SERIAL( ZBBPSimPropertiesProcedure, CObject, def_Version )

using namespace sfl;

//@mfunc | ZBBPSimPropertiesProcedure | ZBBPSimPropertiesProcedure | Constructor.
//
//@syntax ZBBPSimPropertiesProcedure::ZBBPSimPropertiesProcedure(int nId);
//@syntax ZBBPSimPropertiesProcedure::ZBBPSimPropertiesProcedure(const ZBBPSimPropertiesProcedure& propBasic);
//
//@parmopt int | nId | OD_PROP_ORIENTATION | The identifier of the property.
//@parm ZBBPSimPropertiesProcedure& | propBasic | The orientation property to copy.
ZBBPSimPropertiesProcedure::ZBBPSimPropertiesProcedure()
{
    m_ProcedureActivation            = (double)1;
    m_ProcedureCost                    = (double)0;
    m_ProcedureWorkloadForecast        = (double)1;
    m_ProcedureCostForecast            = (double)0;
    m_ProcedureWorkloadPerActivity    = 0;
    m_ProcedureCostPerActivity        = 0;
}

ZBBPSimPropertiesProcedure::ZBBPSimPropertiesProcedure( const ZBBPSimPropertiesProcedure& propBasic )
{
    *this = propBasic;
}

//@mfunc Destructor.
ZBBPSimPropertiesProcedure::~ZBBPSimPropertiesProcedure()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesProcedure operations

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPSimPropertiesProcedure& ZBBPSimPropertiesProcedure::operator=( const ZBBPSimPropertiesProcedure& propBasic )
{
    SetProcedureActivation            ( (double)const_cast<ZBBPSimPropertiesProcedure&>( propBasic ).GetProcedureActivation() );
    SetProcedureCost                ( (double)const_cast<ZBBPSimPropertiesProcedure&>( propBasic ).GetProcedureCost() );
    SetProcedureWorkloadForecast    ( (double)const_cast<ZBBPSimPropertiesProcedure&>( propBasic ).GetProcedureWorkloadForecast() );
    SetProcedureCostForecast        ( (double)const_cast<ZBBPSimPropertiesProcedure&>( propBasic ).GetProcedureCostForecast() );
    SetProcedureWorkloadPerActivity    ( (double)const_cast<ZBBPSimPropertiesProcedure&>( propBasic ).GetProcedureWorkloadPerActivity() );
    SetProcedureCostPerActivity        ( (double)const_cast<ZBBPSimPropertiesProcedure&>( propBasic ).GetProcedureCostPerActivity() );

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPSimPropertiesProcedure::operator==( const ZBBPSimPropertiesProcedure propBasic ) const
{
    return ( const_cast<ZBBPSimPropertiesProcedure*>( this )->GetProcedureActivation()            == const_cast<ZBBPSimPropertiesProcedure&>( propBasic ).GetProcedureActivation()            &&
             const_cast<ZBBPSimPropertiesProcedure*>( this )->GetProcedureCost()                == const_cast<ZBBPSimPropertiesProcedure&>( propBasic ).GetProcedureCost()                    &&
             const_cast<ZBBPSimPropertiesProcedure*>( this )->GetProcedureWorkloadForecast()    == const_cast<ZBBPSimPropertiesProcedure&>( propBasic ).GetProcedureWorkloadForecast()        &&
             const_cast<ZBBPSimPropertiesProcedure*>( this )->GetProcedureCostForecast()        == const_cast<ZBBPSimPropertiesProcedure&>( propBasic ).GetProcedureCostForecast()            &&
             const_cast<ZBBPSimPropertiesProcedure*>( this )->GetProcedureWorkloadPerActivity()    == const_cast<ZBBPSimPropertiesProcedure&>( propBasic ).GetProcedureWorkloadPerActivity()    &&
             const_cast<ZBBPSimPropertiesProcedure*>( this )->GetProcedureCostPerActivity()        == const_cast<ZBBPSimPropertiesProcedure&>( propBasic ).GetProcedureCostPerActivity() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPSimPropertiesProcedure::Merge( ZBBPSimPropertiesProcedure* pProperty, DWORD dwChangeFlags )
{
    if ( dwChangeFlags & Z_CHANGE_SIM_PROCEDURE_ACTIVATION )
    {
        m_ProcedureActivation = pProperty->GetProcedureActivation();
    }

    if ( dwChangeFlags & Z_CHANGE_SIM_PROCEDURE_COST )
    {
        m_ProcedureCost = pProperty->GetProcedureCost();
    }

    if ( dwChangeFlags & Z_CHANGE_SIM_PROCEDURE_WORKLOAD_FORECAST )
    {
        m_ProcedureWorkloadForecast = pProperty->GetProcedureWorkloadForecast();
    }

    if ( dwChangeFlags & Z_CHANGE_SIM_PROCEDURE_COST_FORECAST )
    {
        m_ProcedureCostForecast = pProperty->GetProcedureCostForecast();
    }

    if ( dwChangeFlags & Z_CHANGE_SIM_PROCEDURE_WORKLOAD_P_ACTIV_FORECAST )
    {
        m_ProcedureWorkloadPerActivity = pProperty->GetProcedureWorkloadPerActivity();
    }

    if ( dwChangeFlags & Z_CHANGE_SIM_PROCEDURE_COST_P_ACTIV_FORECAST )
    {
        m_ProcedureCostPerActivity = pProperty->GetProcedureCostPerActivity();
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf CODFillProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPSimPropertiesProcedure::IsEqual( ZBBPSimPropertiesProcedure* pProp )
{
    if ( pProp )
    {
        return ( *this == *pProp );
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPSimPropertiesProcedure | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPSimPropertiesProcedure::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPSimPropertiesProcedure::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPSimPropertiesProcedure::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPSimPropertiesProcedure::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPSimPropertiesProcedure::GetValue(const int nPropId, float& fValue) const
//@syntax BOOL ZBBPSimPropertiesProcedure::GetValue(const int nPropId, double& fValue) const
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

BOOL ZBBPSimPropertiesProcedure::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_SIM_PROCEDURE_ACTIVATION:
        {
            strValue.Format( _T( "%.0f" ), (double)m_ProcedureActivation );
            break;
        }

        case Z_SIM_PROCEDURE_COST:
        {
            strValue.Format( _T( "%.0f" ), (double)m_ProcedureCost );
            break;
        }

        case Z_SIM_PROCEDURE_WORKLOAD_FORECAST:
        {
            strValue.Format( _T( "%.0f" ), (double)m_ProcedureWorkloadForecast );
            break;
        }

        case Z_SIM_PROCEDURE_COST_FORECAST:
        {
            strValue.Format( _T( "%.0f" ), (double)m_ProcedureCostForecast );
            break;
        }

        case Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV:
        {
            strValue.Format( _T( "%.0f" ), (double)m_ProcedureWorkloadPerActivity );
            break;
        }

        case Z_SIM_PROCEDURE_COST_P_ACTIV:
        {
            strValue.Format( _T( "%.0f" ), (double)m_ProcedureCostPerActivity );
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

BOOL ZBBPSimPropertiesProcedure::GetValue( const int nPropId, int& nValue ) const
{
    nValue; // unused

    if ( nPropId >= Z_SIM_PROCEDURE_ACTIVATION && nPropId <= Z_SIM_PROCEDURE_COST_P_ACTIV )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPSimPropertiesProcedure::GetValue( const int nPropId, UINT& nValue ) const
{
    nValue; // unused

    if ( nPropId >= Z_SIM_PROCEDURE_ACTIVATION && nPropId <= Z_SIM_PROCEDURE_COST_P_ACTIV )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPSimPropertiesProcedure::GetValue( const int nPropId, DWORD& dwValue ) const
{
    dwValue; // unused

    if ( nPropId >= Z_SIM_PROCEDURE_ACTIVATION && nPropId <= Z_SIM_PROCEDURE_COST_P_ACTIV )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPSimPropertiesProcedure::GetValue( const int nPropId, float& fValue ) const
{
    switch ( nPropId )
    {
        case Z_SIM_PROCEDURE_ACTIVATION:
        {
            fValue = static_cast<float>( (double)m_ProcedureActivation );
            break;
        }

        case Z_SIM_PROCEDURE_COST:
        {
            fValue = static_cast<float>( (double)m_ProcedureCost );
            break;
        }

        case Z_SIM_PROCEDURE_WORKLOAD_FORECAST:
        {
            fValue = static_cast<float>( (double)m_ProcedureWorkloadForecast );
            break;
        }

        case Z_SIM_PROCEDURE_COST_FORECAST:
        {
            fValue = static_cast<float>( (double)m_ProcedureCostForecast );
            break;
        }

        case Z_SIM_PROCEDURE_COST_P_ACTIV:
        {
            fValue = static_cast<float>( (double)m_ProcedureCostPerActivity );
            break;
        }

        case Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV:
        {
            fValue = static_cast<float>( (double)m_ProcedureWorkloadPerActivity );
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPSimPropertiesProcedure::GetValue( const int nPropId, double& dValue ) const
{
    switch ( nPropId )
    {
        case Z_SIM_PROCEDURE_ACTIVATION:
        {
            dValue = (double)m_ProcedureActivation;
            break;
        }

        case Z_SIM_PROCEDURE_COST:
        {
            dValue = (double)m_ProcedureCost;
            break;
        }

        case Z_SIM_PROCEDURE_WORKLOAD_FORECAST:
        {
            dValue = (double)m_ProcedureWorkloadForecast;
            break;
        }

        case Z_SIM_PROCEDURE_COST_FORECAST:
        {
            dValue = (double)m_ProcedureCostForecast;
            break;
        }

        case Z_SIM_PROCEDURE_COST_P_ACTIV:
        {
            dValue = (double)m_ProcedureCostPerActivity;
            break;
        }

        case Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV:
        {
            dValue = (double)m_ProcedureWorkloadPerActivity;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

//@mfunc | ZBBPSimPropertiesProcedure | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPSimPropertiesProcedure::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPSimPropertiesProcedure::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPSimPropertiesProcedure::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPSimPropertiesProcedure::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPSimPropertiesProcedure::SetValue(const int nPropId, const float fValue)
//@syntax BOOL ZBBPSimPropertiesProcedure::SetValue(const int nPropId, const double dValue)
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

BOOL ZBBPSimPropertiesProcedure::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_SIM_PROCEDURE_ACTIVATION:
        {
            m_ProcedureActivation = atof( lpszValue );
            break;
        }

        case Z_SIM_PROCEDURE_COST:
        {
            m_ProcedureCost = atof( lpszValue );
            break;
        }

        case Z_SIM_PROCEDURE_WORKLOAD_FORECAST:
        {
            m_ProcedureWorkloadForecast = atof( lpszValue );
            break;
        }

        case Z_SIM_PROCEDURE_COST_FORECAST:
        {
            m_ProcedureCostForecast = atof( lpszValue );
            break;
        }

        case Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV:
        {
            m_ProcedureWorkloadPerActivity = atof( lpszValue );
            break;
        }

        case Z_SIM_PROCEDURE_COST_P_ACTIV:
        {
            m_ProcedureCostPerActivity = atof( lpszValue );
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPSimPropertiesProcedure::SetValue( const int nPropId, const int nValue )
{
    nValue; // unused

    if ( nPropId >= Z_SIM_PROCEDURE_ACTIVATION && nPropId <= Z_SIM_PROCEDURE_COST_P_ACTIV )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPSimPropertiesProcedure::SetValue( const int nPropId, const UINT nValue )
{
    nValue; // unused

    if ( nPropId >= Z_SIM_PROCEDURE_ACTIVATION && nPropId <= Z_SIM_PROCEDURE_COST_P_ACTIV )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPSimPropertiesProcedure::SetValue( const int nPropId, const DWORD dwValue )
{
    dwValue; // unused

    if ( nPropId >= Z_SIM_PROCEDURE_ACTIVATION && nPropId <= Z_SIM_PROCEDURE_COST_P_ACTIV )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPSimPropertiesProcedure::SetValue( const int nPropId, const float fValue )
{
    switch ( nPropId )
    {
        case Z_SIM_PROCEDURE_ACTIVATION:
        {
            m_ProcedureActivation = (double)fValue;
            break;
        }

        case Z_SIM_PROCEDURE_COST:
        {
            m_ProcedureCost = (double)fValue;
            break;
        }

        case Z_SIM_PROCEDURE_WORKLOAD_FORECAST:
        {
            m_ProcedureWorkloadForecast = (double)fValue;
            break;
        }

        case Z_SIM_PROCEDURE_COST_FORECAST:
        {
            m_ProcedureCostForecast = (double)fValue;
            break;
        }

        case Z_SIM_PROCEDURE_COST_P_ACTIV:
        {
            m_ProcedureCostPerActivity = (double)fValue;
            break;
        }

        case Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV:
        {
            m_ProcedureWorkloadPerActivity = (double)fValue;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPSimPropertiesProcedure::SetValue( const int nPropId, const double dValue )
{
    switch ( nPropId )
    {
        case Z_SIM_PROCEDURE_ACTIVATION:
        {
            m_ProcedureActivation = dValue;
            break;
        }

        case Z_SIM_PROCEDURE_COST:
        {
            m_ProcedureCost = dValue;
            break;
        }

        case Z_SIM_PROCEDURE_WORKLOAD_FORECAST:
        {
            m_ProcedureWorkloadForecast = dValue;
            break;
        }

        case Z_SIM_PROCEDURE_COST_FORECAST:
        {
            m_ProcedureCostForecast = dValue;
            break;
        }

        case Z_SIM_PROCEDURE_COST_P_ACTIV:
        {
            m_ProcedureCostPerActivity = dValue;
            break;
        }

        case Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV:
        {
            m_ProcedureWorkloadPerActivity = dValue;
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
// ZBBPSimPropertiesProcedure diagnostics

#ifdef _DEBUG
void ZBBPSimPropertiesProcedure::AssertValid() const
{
    CObject::AssertValid();
}

void ZBBPSimPropertiesProcedure::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesProcedure serialization

//@mfunc Serializes the orientation properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPSimPropertiesProcedure::Serialize( CArchive& ar )
{
    m_ProcedureActivation.Serialize( ar );
    m_ProcedureCost.Serialize( ar );
    m_ProcedureWorkloadForecast.Serialize( ar );
    m_ProcedureCostForecast.Serialize( ar );

    if ( ar.IsStoring() )
    {
        TRACE( _T( "ZBBPSimPropertiesProcedure::Serialize : Start Save\n" ) );

        PUT_SCHEMA( ar, ZBBPSimPropertiesProcedure );

        ar << m_ProcedureWorkloadPerActivity;
        ar << m_ProcedureCostPerActivity;

        TRACE( _T( "ZBBPSimPropertiesProcedure::Serialize : End Save\n" ) );
    }
    else
    {
        TRACE( _T( "ZBBPSimPropertiesProcedure::Serialize : Start Read\n" ) );

        UINT nSchema;
        GET_SCHEMA( ar, nSchema );

        ar >> m_ProcedureWorkloadPerActivity;
        ar >> m_ProcedureCostPerActivity;

        TRACE( _T( "ZBBPSimPropertiesProcedure::Serialize : End Read\n" ) );
    }
}
