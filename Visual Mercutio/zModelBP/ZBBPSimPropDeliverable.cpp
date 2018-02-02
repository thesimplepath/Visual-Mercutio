/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropDeliverable.cpp : Implementation of ZBBPSimPropertiesDeliverable
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
// Created:		 05/2001
// Description:  ZBBPSimPropertiesDeliverable simulation properties for deliverables
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBBPSimPropDeliverable.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 8 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesDeliverable construction/destruction

IMPLEMENT_SERIAL( ZBBPSimPropertiesDeliverable, CObject, def_Version )

using namespace sfl;

//@mfunc | ZBBPSimPropertiesDeliverable | ZBBPSimPropertiesDeliverable | Constructor.
//
//@syntax ZBBPSimPropertiesDeliverable::ZBBPSimPropertiesDeliverable(int nId);
//@syntax ZBBPSimPropertiesDeliverable::ZBBPSimPropertiesDeliverable(const ZBBPSimPropertiesDeliverable& propBasic);
//
//@parmopt int | nId | OD_PROP_ORIENTATION | The identifier of the property.
//@parm ZBBPSimPropertiesDeliverable& | propBasic | The orientation property to copy.
ZBBPSimPropertiesDeliverable::ZBBPSimPropertiesDeliverable()
{
	m_Cost				= (double)0;
	m_WorkloadForecast	= (double)0;
}

ZBBPSimPropertiesDeliverable::ZBBPSimPropertiesDeliverable( const ZBBPSimPropertiesDeliverable& propBasic )
{
	*this = propBasic;
}

//@mfunc Destructor.
ZBBPSimPropertiesDeliverable::~ZBBPSimPropertiesDeliverable()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesDeliverable operations

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPSimPropertiesDeliverable& ZBBPSimPropertiesDeliverable::operator=( const ZBBPSimPropertiesDeliverable& propBasic )
{
	SetCost				( const_cast<ZBBPSimPropertiesDeliverable&>( propBasic ).GetCost() );
	SetWorkloadForecast	( const_cast<ZBBPSimPropertiesDeliverable&>( propBasic ).GetWorkloadForecast() );

	return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPSimPropertiesDeliverable::operator==( const ZBBPSimPropertiesDeliverable propBasic ) const
{
	return ( const_cast<ZBBPSimPropertiesDeliverable*>( this )->GetCost()				== const_cast<ZBBPSimPropertiesDeliverable&>( propBasic ).GetCost() &&
			 const_cast<ZBBPSimPropertiesDeliverable*>( this )->GetWorkloadForecast()	== const_cast<ZBBPSimPropertiesDeliverable&>( propBasic ).GetWorkloadForecast() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPSimPropertiesDeliverable::Merge( ZBBPSimPropertiesDeliverable* pProperty, DWORD dwChangeFlags )
{
	if ( dwChangeFlags & Z_CHANGE_SIM_DELIV_COST )
	{
		m_Cost = pProperty->GetCost();
	}

	if ( dwChangeFlags & Z_CHANGE_SIM_DELIV_WORKLOAD_FORECAST )
	{
		m_WorkloadForecast = pProperty->GetWorkloadForecast();
	}
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf CODFillProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPSimPropertiesDeliverable::IsEqual( ZBBPSimPropertiesDeliverable* pProp )
{
	if ( pProp )
	{
		return ( *this == *pProp );
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPSimPropertiesDeliverable | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPSimPropertiesDeliverable::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPSimPropertiesDeliverable::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPSimPropertiesDeliverable::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPSimPropertiesDeliverable::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPSimPropertiesDeliverable::GetValue(const int nPropId, float& fValue) const
//@syntax BOOL ZBBPSimPropertiesDeliverable::GetValue(const int nPropId, double& dValue) const
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

BOOL ZBBPSimPropertiesDeliverable::GetValue( const int nPropId, CString& strValue ) const
{
	switch ( nPropId )
	{
		case Z_SIM_DELIV_COST:
		{
			strValue.Format( _T( "%.0f" ), (double)m_Cost * (float)100 );
			break;
		}

		case Z_SIM_DELIV_WORKLOAD_FORECAST:
		{
			strValue.Format( _T( "%.0f" ), (double)m_WorkloadForecast * (float)100 );
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBBPSimPropertiesDeliverable::GetValue( const int nPropId, int& nValue ) const
{
	// Unused
	nValue;

	if ( nPropId >= Z_SIM_DELIV_COST && nPropId <= Z_SIM_DELIV_WORKLOAD_FORECAST )
	{
		throw new CODPropertyConversionException();
	}

	return FALSE;
}

BOOL ZBBPSimPropertiesDeliverable::GetValue( const int nPropId, UINT& nValue ) const
{
	// Unused
	nValue;

	if ( nPropId >= Z_SIM_DELIV_COST && nPropId <= Z_SIM_DELIV_WORKLOAD_FORECAST )
	{
		throw new CODPropertyConversionException();
	}

	return FALSE;
}

BOOL ZBBPSimPropertiesDeliverable::GetValue( const int nPropId, DWORD& dwValue ) const
{
	// Unused
	dwValue;

	if ( nPropId >= Z_SIM_DELIV_COST && nPropId <= Z_SIM_DELIV_WORKLOAD_FORECAST )
	{
		throw new CODPropertyConversionException();
	}

	return FALSE;
}

BOOL ZBBPSimPropertiesDeliverable::GetValue( const int nPropId, float& fValue ) const
{
	switch ( nPropId )
	{
		case Z_SIM_DELIV_COST:
		{
			fValue = static_cast<float>( (double)m_Cost );
			break;
		}

		case Z_SIM_DELIV_WORKLOAD_FORECAST:
		{
			fValue = static_cast<float>( (double)m_WorkloadForecast );
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBBPSimPropertiesDeliverable::GetValue( const int nPropId, double& dValue ) const
{
	switch ( nPropId )
	{
		case Z_SIM_DELIV_COST:
		{
			dValue = (double)m_Cost;
			break;
		}

		case Z_SIM_DELIV_WORKLOAD_FORECAST:
		{
			dValue = (double)m_WorkloadForecast;
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

//@mfunc | ZBBPSimPropertiesDeliverable | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPSimPropertiesDeliverable::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPSimPropertiesDeliverable::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPSimPropertiesDeliverable::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPSimPropertiesDeliverable::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPSimPropertiesDeliverable::SetValue(const int nPropId, const float fValue)
//@syntax BOOL ZBBPSimPropertiesDeliverable::SetValue(const int nPropId, const double dValue)
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

BOOL ZBBPSimPropertiesDeliverable::SetValue( const int nPropId, LPCTSTR lpszValue )
{
	switch ( nPropId )
	{
		case Z_SIM_DELIV_COST:
		{
			m_Cost = atof( lpszValue ) / (double)100;
			break;
		}

		case Z_SIM_DELIV_WORKLOAD_FORECAST:
		{
			m_WorkloadForecast = atof( lpszValue ) / (double)100;
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBBPSimPropertiesDeliverable::SetValue( const int nPropId, const int nValue )
{
	// Unused
	nValue;

	if ( nPropId >= Z_SIM_DELIV_COST && nPropId <= Z_SIM_DELIV_WORKLOAD_FORECAST )
	{
		throw new CODPropertyConversionException();
	}

	return FALSE;
}

BOOL ZBBPSimPropertiesDeliverable::SetValue( const int nPropId, const UINT nValue )
{
	// Unused
	nValue;

	if ( nPropId >= Z_SIM_DELIV_COST && nPropId <= Z_SIM_DELIV_WORKLOAD_FORECAST )
	{
		throw new CODPropertyConversionException();
	}

	return FALSE;
}

BOOL ZBBPSimPropertiesDeliverable::SetValue( const int nPropId, const DWORD dwValue )
{
	// Unused
	dwValue;

	if ( nPropId >= Z_SIM_DELIV_COST && nPropId <= Z_SIM_DELIV_WORKLOAD_FORECAST )
	{
		throw new CODPropertyConversionException();
	}

	return FALSE;
}

BOOL ZBBPSimPropertiesDeliverable::SetValue( const int nPropId, const float fValue )
{
	switch ( nPropId )
	{
		case Z_SIM_DELIV_COST:
		{
			m_Cost = (double)fValue;
			break;
		}

		case Z_SIM_DELIV_WORKLOAD_FORECAST:
		{
			m_WorkloadForecast = (double)fValue;
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBBPSimPropertiesDeliverable::SetValue( const int nPropId, const double dValue )
{
	switch ( nPropId )
	{
		case Z_SIM_DELIV_COST:
		{
			m_Cost = dValue;
			break;
		}

		case Z_SIM_DELIV_WORKLOAD_FORECAST:
		{
			m_WorkloadForecast = dValue;
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
// ZBBPSimPropertiesDeliverable diagnostics

#ifdef _DEBUG
void ZBBPSimPropertiesDeliverable::AssertValid() const
{
	CObject::AssertValid();
}

void ZBBPSimPropertiesDeliverable::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesDeliverable serialization

//@mfunc Serializes the orientation properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPSimPropertiesDeliverable::Serialize( CArchive& ar )
{
	m_Cost.Serialize( ar );
	m_WorkloadForecast.Serialize( ar );

	if ( ar.IsStoring() )
	{
		TRACE( _T( "ZBBPSimPropertiesDeliverable::Serialize : Start Save\n" ) );

		PUT_SCHEMA( ar, ZBBPSimPropertiesDeliverable );

		TRACE( _T( "ZBBPSimPropertiesDeliverable::Serialize : End Save\n" ) );
	}
	else
	{
		TRACE( _T( "ZBBPSimPropertiesDeliverable::Serialize : Start Read\n" ) );

		UINT nSchema;
		GET_SCHEMA( ar, nSchema );

		TRACE( _T( "ZBBPSimPropertiesDeliverable::Serialize : End Read\n" ) );
	}
}
