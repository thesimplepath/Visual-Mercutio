/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropProcess.cpp : Implementation of ZBBPSimPropertiesProcess
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
// Description:  ZBBPSimPropertiesProcess simulation properties for process
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBBPSimPropProcess.h"

// JMR-MODIF - Le 14 mars 2006 - Ajout de l'en-tête BaseDoc.h pour la sérialisation.
#include "zBaseLib\BaseDoc.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 28 septembre 2005 - Ajout des décorations unicode _T( ), et nettoyage du code non utilisé.

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesProcess construction/destruction

IMPLEMENT_SERIAL( ZBBPSimPropertiesProcess, CObject, def_Version )

using namespace sfl;

//@mfunc | ZBBPSimPropertiesProcess | ZBBPSimPropertiesProcess | Constructor.
//
//@syntax ZBBPSimPropertiesProcess::ZBBPSimPropertiesProcess(int nId);
//@syntax ZBBPSimPropertiesProcess::ZBBPSimPropertiesProcess(const ZBBPSimPropertiesProcess& propBasic);
//
//@parmopt int | nId | OD_PROP_ORIENTATION | The identifier of the property.
//@parm ZBBPSimPropertiesProcess& | propBasic | The orientation property to copy.
ZBBPSimPropertiesProcess::ZBBPSimPropertiesProcess()
{
    m_ProcessWorkloadForecast    = (double)1;
    m_ProcessCostForecast        = (double)0;

    // JMR-MODIF - Le 14 mars 2006 - Ajout de l'initialisation de la variable pour le coût HMO.
    m_ProcessCost                = (double)0;
}

ZBBPSimPropertiesProcess::ZBBPSimPropertiesProcess( const ZBBPSimPropertiesProcess& propBasic )
{
    *this = propBasic;
}

//@mfunc Destructor.
ZBBPSimPropertiesProcess::~ZBBPSimPropertiesProcess()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesProcess operations

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPSimPropertiesProcess& ZBBPSimPropertiesProcess::operator=( const ZBBPSimPropertiesProcess& propBasic )
{
    SetProcessWorkloadForecast    ( const_cast<ZBBPSimPropertiesProcess&>( propBasic ).GetProcessWorkloadForecast() );
    SetProcessCostForecast        ( const_cast<ZBBPSimPropertiesProcess&>( propBasic ).GetProcessCostForecast() );
    // JMR-MODIF - Le 14 mars 2006 - Ajout de la copie de la variable du coût HMO.
    SetProcessCost                ( const_cast<ZBBPSimPropertiesProcess&>( propBasic ).GetProcessCost() );

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPSimPropertiesProcess::operator==( const ZBBPSimPropertiesProcess propBasic ) const
{
    // JMR-MODIF - Le 14 mars 2006 - Ajout de la comparaison pour la variable du coût HMO.
    return ( const_cast<ZBBPSimPropertiesProcess*>( this )->GetProcessWorkloadForecast() == const_cast<ZBBPSimPropertiesProcess&>( propBasic ).GetProcessWorkloadForecast()    &&
             const_cast<ZBBPSimPropertiesProcess*>( this )->GetProcessCostForecast()     == const_cast<ZBBPSimPropertiesProcess&>( propBasic ).GetProcessCostForecast()        &&
             const_cast<ZBBPSimPropertiesProcess*>( this )->GetProcessCost()             == const_cast<ZBBPSimPropertiesProcess&>( propBasic ).GetProcessCost() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPSimPropertiesProcess::Merge( ZBBPSimPropertiesProcess* pProperty, DWORD dwChangeFlags )
{
    if ( dwChangeFlags & Z_CHANGE_SIM_PROCESS_WORKLOAD_FORECAST )
    {
        m_ProcessWorkloadForecast = pProperty->GetProcessWorkloadForecast();
    }

    if ( dwChangeFlags & Z_CHANGE_SIM_PROCESS_COST_FORECAST )
    {
        m_ProcessCostForecast = pProperty->GetProcessCostForecast();
    }

    // JMR-MODIF - Le 14 mars 2006 - Ajout de la propriété de partage pour la variable du coût HMO.
    if ( dwChangeFlags & Z_CHANGE_SIM_PROCESS_COST_HMO )
    {
        m_ProcessCost = pProperty->GetProcessCost();
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf CODFillProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPSimPropertiesProcess::IsEqual( ZBBPSimPropertiesProcess* pProp )
{
    if ( pProp )
    {
        return ( *this == *pProp );
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPSimPropertiesProcess | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPSimPropertiesProcess::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPSimPropertiesProcess::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPSimPropertiesProcess::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPSimPropertiesProcess::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPSimPropertiesProcess::GetValue(const int nPropId, float& fValue) const
//@syntax BOOL ZBBPSimPropertiesProcess::GetValue(const int nPropId, double& dValue) const
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

BOOL ZBBPSimPropertiesProcess::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_SIM_PROCESS_WORKLOAD_FORECAST:
        {
            strValue.Format( _T( "%.0f" ), (double)m_ProcessWorkloadForecast );
            break;
        }

        case Z_SIM_PROCESS_COST_FORECAST:
        {
            strValue.Format( _T( "%.0f" ), (double)m_ProcessCostForecast );
            break;
        }

        // JMR-MODIF - Le 14 mars 2006 - Ajout de la prise en charge de la variable HMO.
        case Z_SIM_PROCESS_COST_HMO:
        {
            strValue.Format( _T( "%.0f" ), (double)m_ProcessCost );
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

BOOL ZBBPSimPropertiesProcess::GetValue( const int nPropId, int& nValue ) const
{
    nValue; // unused

    // JMR-MODIF - Le 14 mars 2006 - Remplacé la déclaration Z_SIM_PROCESS_COST_FORECAST par Z_SIM_PROCESS_COST_HMO.
    if ( nPropId >= Z_SIM_PROCESS_WORKLOAD_FORECAST && nPropId <= Z_SIM_PROCESS_COST_HMO )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPSimPropertiesProcess::GetValue( const int nPropId, UINT& nValue ) const
{
    nValue; // unused

    // JMR-MODIF - Le 14 mars 2006 - Remplacé la déclaration Z_SIM_PROCESS_COST_FORECAST par Z_SIM_PROCESS_COST_HMO.
    if ( nPropId >= Z_SIM_PROCESS_WORKLOAD_FORECAST && nPropId <= Z_SIM_PROCESS_COST_HMO )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPSimPropertiesProcess::GetValue( const int nPropId, DWORD& dwValue ) const
{
    dwValue; // unused

    // JMR-MODIF - Le 14 mars 2006 - Remplacé la déclaration Z_SIM_PROCESS_COST_FORECAST par Z_SIM_PROCESS_COST_HMO.
    if ( nPropId >= Z_SIM_PROCESS_WORKLOAD_FORECAST && nPropId <= Z_SIM_PROCESS_COST_HMO )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPSimPropertiesProcess::GetValue( const int nPropId, float& fValue ) const
{
    switch ( nPropId )
    {
        case Z_SIM_PROCESS_WORKLOAD_FORECAST:
        {
            fValue = static_cast<float>( (double)m_ProcessWorkloadForecast );
            break;
        }

        case Z_SIM_PROCESS_COST_FORECAST:
        {
            fValue = static_cast<float>( (double)m_ProcessCostForecast );
            break;
        }

        // JMR-MODIF - Le 14 mars 2006 - Ajout de la prise en charge de la variable HMO.
        case Z_SIM_PROCESS_COST_HMO:
        {
            fValue = static_cast<float>( (double)m_ProcessCost );
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPSimPropertiesProcess::GetValue( const int nPropId, double& dValue ) const
{
    switch ( nPropId )
    {
        case Z_SIM_PROCESS_WORKLOAD_FORECAST:
        {
            dValue = (double)m_ProcessWorkloadForecast;
            break;
        }

        case Z_SIM_PROCESS_COST_FORECAST:
        {
            dValue = (double)m_ProcessCostForecast;
            break;
        }

        // JMR-MODIF - Le 14 mars 2006 - Ajout de la prise en charge de la variable HMO.
        case Z_SIM_PROCESS_COST_HMO:
        {
            dValue = (double)m_ProcessCost;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

//@mfunc | ZBBPSimPropertiesProcess | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPSimPropertiesProcess::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPSimPropertiesProcess::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPSimPropertiesProcess::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPSimPropertiesProcess::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPSimPropertiesProcess::SetValue(const int nPropId, const float fValue)
//@syntax BOOL ZBBPSimPropertiesProcess::SetValue(const int nPropId, const double dValue)
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

BOOL ZBBPSimPropertiesProcess::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_SIM_PROCESS_WORKLOAD_FORECAST:
        {
            m_ProcessWorkloadForecast = atof( lpszValue );
            break;
        }

        case Z_SIM_PROCESS_COST_FORECAST:
        {
            m_ProcessCostForecast = atof( lpszValue );
            break;
        }

        // JMR-MODIF - Le 14 mars 2006 - Ajout de la prise en charge de la variable HMO.
        case Z_SIM_PROCESS_COST_HMO:
        {
            m_ProcessCost = atof( lpszValue );
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPSimPropertiesProcess::SetValue( const int nPropId, const int nValue )
{
    nValue; // unused

    // JMR-MODIF - Le 14 mars 2006 - Remplacé la déclaration Z_SIM_PROCESS_COST_FORECAST par Z_SIM_PROCESS_COST_HMO.
    if ( nPropId >= Z_SIM_PROCESS_WORKLOAD_FORECAST && nPropId <= Z_SIM_PROCESS_COST_HMO )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPSimPropertiesProcess::SetValue( const int nPropId, const UINT nValue )
{
    nValue; // unused

    // JMR-MODIF - Le 14 mars 2006 - Remplacé la déclaration Z_SIM_PROCESS_COST_FORECAST par Z_SIM_PROCESS_COST_HMO.
    if ( nPropId >= Z_SIM_PROCESS_WORKLOAD_FORECAST && nPropId <= Z_SIM_PROCESS_COST_HMO )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPSimPropertiesProcess::SetValue( const int nPropId, const DWORD dwValue )
{
    dwValue; // unused

    // JMR-MODIF - Le 14 mars 2006 - Remplacé la déclaration Z_SIM_PROCESS_COST_FORECAST par Z_SIM_PROCESS_COST_HMO.
    if ( nPropId >= Z_SIM_PROCESS_WORKLOAD_FORECAST && nPropId <= Z_SIM_PROCESS_COST_HMO )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPSimPropertiesProcess::SetValue( const int nPropId, const float fValue )
{
    switch ( nPropId )
    {
        case Z_SIM_PROCESS_WORKLOAD_FORECAST:
        {
            m_ProcessWorkloadForecast = (double)fValue;
            break;
        }

        case Z_SIM_PROCESS_COST_FORECAST:
        {
            m_ProcessCostForecast = (double)fValue;
            break;
        }

        // JMR-MODIF - Le 14 mars 2006 - Ajout de la prise en charge de la variable HMO.
        case Z_SIM_PROCESS_COST_HMO:
        {
            m_ProcessCost = (double)fValue;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPSimPropertiesProcess::SetValue( const int nPropId, const double dValue )
{
    switch ( nPropId )
    {
        case Z_SIM_PROCESS_WORKLOAD_FORECAST:
        {
            m_ProcessWorkloadForecast = dValue;
            break;
        }

        case Z_SIM_PROCESS_COST_FORECAST:
        {
            m_ProcessCostForecast = dValue;
            break;
        }

        // JMR-MODIF - Le 14 mars 2006 - Ajout de la prise en charge de la variable HMO.
        case Z_SIM_PROCESS_COST_HMO:
        {
            m_ProcessCost = dValue;
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
// ZBBPSimPropertiesProcess diagnostics

#ifdef _DEBUG
void ZBBPSimPropertiesProcess::AssertValid() const
{
    CObject::AssertValid();
}

void ZBBPSimPropertiesProcess::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesProcess serialization

//@mfunc Serializes the orientation properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPSimPropertiesProcess::Serialize( CArchive& ar )
{
    m_ProcessWorkloadForecast.Serialize( ar );
    m_ProcessCostForecast.Serialize( ar );

    // JMR-MODIF - Le 14 mars 2006 - Ajout du code de sérialisation pour le coût HMO.
    if ( ar.IsStoring() )
    {
        m_ProcessCost.Serialize( ar );
    }
    else
    {
        if ( ar.m_pDocument &&
             dynamic_cast<ZDBaseDocument*>( ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 24 )
        {
            m_ProcessCost.Serialize( ar );
        }
    }

    if ( ar.IsStoring() )
    {
        TRACE( _T( "ZBBPSimPropertiesProcess::Serialize : Start Save\n" ) );

        PUT_SCHEMA( ar, ZBBPSimPropertiesProcess );

        TRACE( _T( "ZBBPSimPropertiesProcess::Serialize : End Save\n" ) );
    }
    else
    {
        TRACE( _T( "ZBBPSimPropertiesProcess::Serialize : Start Read\n" ) );

        UINT nSchema;
        GET_SCHEMA( ar, nSchema );

        TRACE( _T( "ZBBPSimPropertiesProcess::Serialize : End Read\n" ) );
    }
}
