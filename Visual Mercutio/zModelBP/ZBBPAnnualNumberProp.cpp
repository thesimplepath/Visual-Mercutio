/////////////////////////////////////////////////////////////////////////////
// ZBBPAnnualNumberProp.cpp : Implementation of ZBBPAnnualNumberProperties
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
// Created:		 03/2001
// Description:  ZBBPAnnualNumberProperties quantity properties
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBBPAnnualNumberProp.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBBPAnnualNumberProperties construction/destruction

IMPLEMENT_SERIAL( ZBBPAnnualNumberProperties, CObject, def_Version )

using namespace sfl;

//@mfunc | ZBBPAnnualNumberProperties | ZBBPAnnualNumberProperties | Constructor.

//@syntax ZBBPAnnualNumberProperties::ZBBPAnnualNumberProperties();
//@syntax ZBBPAnnualNumberProperties::ZBBPAnnualNumberProperties(const ZBBPAnnualNumberProperties& propBasic);
ZBBPAnnualNumberProperties::ZBBPAnnualNumberProperties( double TotalNumber /*= 1*/ )
{
	// Sets the year quantity to 1
	m_Equalizer.SetTotal( TotalNumber );

	// Calculates the value for one month
	double OneMonthQuantity = TotalNumber / _NumberOfMonthPerYear;

	// Assigns monthly values
	m_Equalizer.SetNumberAt( IndexJanuary, OneMonthQuantity );
	m_Equalizer.SetNumberAt( IndexFebruary, OneMonthQuantity );
	m_Equalizer.SetNumberAt( IndexMarch, OneMonthQuantity );
	m_Equalizer.SetNumberAt( IndexApril, OneMonthQuantity );
	m_Equalizer.SetNumberAt( IndexMay, OneMonthQuantity );
	m_Equalizer.SetNumberAt( IndexJune, OneMonthQuantity );
	m_Equalizer.SetNumberAt( IndexJuly, OneMonthQuantity );
	m_Equalizer.SetNumberAt( IndexAugust, OneMonthQuantity );
	m_Equalizer.SetNumberAt( IndexSeptember, OneMonthQuantity );
	m_Equalizer.SetNumberAt( IndexOctober, OneMonthQuantity );
	m_Equalizer.SetNumberAt( IndexNovember, OneMonthQuantity );
	m_Equalizer.SetNumberAt( IndexDecember, OneMonthQuantity );

	// Sets the lock flag to false
	m_Equalizer.SetLockedTotal( false );
	m_Equalizer.SetLockedFlagAt( IndexJanuary, false );
	m_Equalizer.SetLockedFlagAt( IndexFebruary, false );
	m_Equalizer.SetLockedFlagAt( IndexMarch, false );
	m_Equalizer.SetLockedFlagAt( IndexApril, false );
	m_Equalizer.SetLockedFlagAt( IndexMay, false );
	m_Equalizer.SetLockedFlagAt( IndexJune, false );
	m_Equalizer.SetLockedFlagAt( IndexJuly, false );
	m_Equalizer.SetLockedFlagAt( IndexAugust, false );
	m_Equalizer.SetLockedFlagAt( IndexSeptember, false );
	m_Equalizer.SetLockedFlagAt( IndexOctober, false );
	m_Equalizer.SetLockedFlagAt( IndexNovember, false );
	m_Equalizer.SetLockedFlagAt( IndexDecember, false );

	// Calculates all percents according to values
	m_Equalizer.CalculatePercents();

	// Don't show month details
	SetForceEqualizer( false );
}

ZBBPAnnualNumberProperties::ZBBPAnnualNumberProperties( const ZBBPAnnualNumberProperties& right )
{
	*this = right;
}

//@mfunc Destructor.
ZBBPAnnualNumberProperties::~ZBBPAnnualNumberProperties()
{
}

ZBBPAnnualNumberProperties& ZBBPAnnualNumberProperties::operator=( double value )
{
	SetAndCalculateQuantitiesBasedOnYear( value );
	return *this;
}

ZBBPAnnualNumberProperties ZBBPAnnualNumberProperties::Max( const ZBBPAnnualNumberProperties& Left,
															const ZBBPAnnualNumberProperties& Right )
{
	ZBBPAnnualNumberProperties AnnualPropTemp;

	for ( size_t Index = IndexJanuary; Index < IndexDecember+1; ++Index )
	{
		AnnualPropTemp.SetNumberAt( Index, __max( Left.GetNumberAt( Index ), Right.GetNumberAt( Index ) ) );
	}

	// After having set all maxs.
	// Recalculate the total
	AnnualPropTemp.CalculateNumberYear();
	AnnualPropTemp.CalculatePercents();

	return AnnualPropTemp;
}

ZBBPAnnualNumberProperties ZBBPAnnualNumberProperties::Min( const ZBBPAnnualNumberProperties& Left,
															const ZBBPAnnualNumberProperties& Right )
{
	ZBBPAnnualNumberProperties AnnualPropTemp;

	for ( size_t Index = IndexJanuary; Index < IndexDecember+1; ++Index )
	{
		AnnualPropTemp.SetNumberAt( Index, __min( Left.GetNumberAt( Index ), Right.GetNumberAt( Index ) ) );
	}

	// After having set all maxs.
	// Recalculate the total
	AnnualPropTemp.CalculateNumberYear();
	AnnualPropTemp.CalculatePercents();

	return AnnualPropTemp;
}

ZBBPAnnualNumberProperties ZBBPAnnualNumberProperties::operator/( double value )
{
	ZBBPAnnualNumberProperties AnnualPropTemp;

	// Copy this to the temp object
	AnnualPropTemp = *this;

	// Divide the total
	// RS-MODIF 18.08.05 protection au cas où on divise par zéro
	//double dNewValue = GetNumberYear() / value;
	double dNewValue;

	if ( value < 0 )
	{
		dNewValue = GetNumberYear() / value;
	}
	else
	{
		dNewValue = 0;
	}

	// Sets the new total and calculate all others
	AnnualPropTemp.SetAndCalculateQuantitiesBasedOnYear( dNewValue );

	return AnnualPropTemp;
}

ZBBPAnnualNumberProperties ZBBPAnnualNumberProperties::operator*( double value )
{
	ZBBPAnnualNumberProperties AnnualPropTemp;

	// Copy this to the temp object
	AnnualPropTemp = *this;

	// Multiply the total
	double dNewValue = GetNumberYear() * value;

	// Sets the new total and calculate all others
	AnnualPropTemp.SetAndCalculateQuantitiesBasedOnYear( dNewValue );

	return AnnualPropTemp;
}

ZBBPAnnualNumberProperties ZBBPAnnualNumberProperties::operator+( double value )
{
	ZBBPAnnualNumberProperties AnnualPropTemp;

	// Copy this to the temp object
	AnnualPropTemp = *this;

	// Multiply the total
	double dNewValue = GetNumberYear() + value;

	// Sets the new total and calculate all others
	AnnualPropTemp.SetAndCalculateQuantitiesBasedOnYear( dNewValue );

	return AnnualPropTemp;
}

ZBBPAnnualNumberProperties ZBBPAnnualNumberProperties::operator+( const ZBBPAnnualNumberProperties& Right )
{
	ZBBPAnnualNumberProperties AnnualPropTemp;

	for ( size_t Index = IndexJanuary; Index < IndexDecember+1; ++Index )
	{
		AnnualPropTemp.SetNumberAt( Index, GetNumberAt( Index ) + Right.GetNumberAt( Index ) );
	}

	// After having set all maxs.
	// Recalculate the total
	AnnualPropTemp.CalculateNumberYear();
	AnnualPropTemp.CalculatePercents();

	return AnnualPropTemp;
}

ZBBPAnnualNumberProperties ZBBPAnnualNumberProperties::operator-( double value )
{
	ZBBPAnnualNumberProperties AnnualPropTemp;

	// Copy this to the temp object
	AnnualPropTemp = *this;

	// Multiply the total
	double dNewValue = GetNumberYear() - value;

	// Sets the new total and calculate all others
	AnnualPropTemp.SetAndCalculateQuantitiesBasedOnYear( dNewValue );

	return AnnualPropTemp;
}

ZBBPAnnualNumberProperties ZBBPAnnualNumberProperties::operator-( const ZBBPAnnualNumberProperties& Right )
{
	ZBBPAnnualNumberProperties AnnualPropTemp;

	for ( size_t Index = IndexJanuary; Index < IndexDecember+1; ++Index )
	{
		AnnualPropTemp.SetNumberAt( Index, GetNumberAt( Index ) - Right.GetNumberAt( Index ) );
	}

	// After having set all maxs.
	// Recalculate the total
	AnnualPropTemp.CalculateNumberYear();
	AnnualPropTemp.CalculatePercents();

	return AnnualPropTemp;
}

void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnYear( const double value )
{
	m_Equalizer.SetTotalEqualizeNumbers( value );
}

void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnJanuary( const double value )
{
	m_Equalizer.SetNumberAtEqualize( IndexJanuary, value );
}

void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnFebruary( const double value )
{
	m_Equalizer.SetNumberAtEqualize( IndexFebruary, value );
}

void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnMarch( const double value )
{
	m_Equalizer.SetNumberAtEqualize( IndexMarch, value );
}

void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnApril( const double value )
{
	m_Equalizer.SetNumberAtEqualize( IndexApril, value );
}


void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnMay( const double value )
{
	m_Equalizer.SetNumberAtEqualize( IndexMay, value );
}


void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnJune( const double value )
{
	m_Equalizer.SetNumberAtEqualize( IndexJune, value );
}

void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnJuly( const double value )
{
	m_Equalizer.SetNumberAtEqualize( IndexJuly, value );
}

void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnAugust( const double value )
{
	m_Equalizer.SetNumberAtEqualize( IndexAugust, value );
}

void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnSeptember( const double value )
{
	m_Equalizer.SetNumberAtEqualize( IndexSeptember, value );
}

void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnOctober( const double value )
{
	m_Equalizer.SetNumberAtEqualize( IndexOctober, value );
}

void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnNovember( const double value )
{
	m_Equalizer.SetNumberAtEqualize( IndexNovember, value );
}

void ZBBPAnnualNumberProperties::SetAndCalculateQuantitiesBasedOnDecember( const double value )
{
	m_Equalizer.SetNumberAtEqualize( IndexDecember, value );
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPAnnualNumberProperties operations

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPAnnualNumberProperties& ZBBPAnnualNumberProperties::operator=( const ZBBPAnnualNumberProperties& right )
{
	m_Equalizer			= right.m_Equalizer;
	m_ForceEqualizer	= right.m_ForceEqualizer;

	return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPAnnualNumberProperties::operator==( const ZBBPAnnualNumberProperties propBasic ) const
{
	return (GetNumberYear()				== propBasic.GetNumberYear()			&&
			GetNumberJanuary()			== propBasic.GetNumberJanuary()			&&
			GetNumberFebruary()			== propBasic.GetNumberFebruary()		&&
			GetNumberMarch()			== propBasic.GetNumberMarch()			&&
			GetNumberApril()			== propBasic.GetNumberApril()			&&
			GetNumberJune()				== propBasic.GetNumberJune()			&&
			GetNumberJuly()				== propBasic.GetNumberJuly()			&&
			GetNumberAugust()			== propBasic.GetNumberAugust()			&&
			GetNumberSeptember()		== propBasic.GetNumberSeptember()		&&
			GetNumberOctober()			== propBasic.GetNumberOctober()			&&
			GetNumberNovember()			== propBasic.GetNumberNovember()		&&
			GetNumberDecember()			== propBasic.GetNumberDecember()		&&
			GetLockNumberYear()			== propBasic.GetLockNumberYear()		&&
			GetLockNumberJanuary()		== propBasic.GetLockNumberJanuary()		&&
			GetLockNumberFebruary()		== propBasic.GetLockNumberFebruary()	&&
			GetLockNumberMarch()		== propBasic.GetLockNumberMarch()		&&
			GetLockNumberApril()		== propBasic.GetLockNumberApril()		&&
			GetLockNumberMay()			== propBasic.GetLockNumberMay()			&&
			GetLockNumberJune()			== propBasic.GetLockNumberJune()		&&
			GetLockNumberJuly()			== propBasic.GetLockNumberJuly()		&&
			GetLockNumberAugust()		== propBasic.GetLockNumberAugust()		&&
			GetLockNumberSeptember()	== propBasic.GetLockNumberSeptember()	&&
			GetLockNumberOctober()		== propBasic.GetLockNumberOctober()		&&
			GetLockNumberNovember()		== propBasic.GetLockNumberNovember()	&&
			GetLockNumberDecember()		== propBasic.GetLockNumberDecember()	&&
			GetForceEqualizer()			== propBasic.GetForceEqualizer());
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPAnnualNumberProperties::Merge( ZBBPAnnualNumberProperties* pProperty, DWORD dwChangeFlags )
{
	ZBBPAnnualNumberProperties* pProp = (ZBBPAnnualNumberProperties*)pProperty;

	if ( pProp )
	{
		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_YEAR ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberYear( pProperty->GetNumberYear() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_JANUARY ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberJanuary( pProperty->GetNumberJanuary() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_FEBRUARY ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberFebruary( pProperty->GetNumberFebruary() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_MARCH ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberMarch( pProperty->GetNumberMarch() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_APRIL ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberApril( pProperty->GetNumberApril() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_MAY ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberMay( pProperty->GetNumberMay() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_JUNE ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberJune( pProperty->GetNumberJune() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_JULY ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberJuly( pProperty->GetNumberJuly() );
		}
	
		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_AUGUST ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberAugust( pProperty->GetNumberAugust() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_SEPTEMBER ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberSeptember( pProperty->GetNumberSeptember() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_OCTOBER ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberOctober( pProperty->GetNumberOctober() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_NOVEMBER ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberNovember( pProperty->GetNumberNovember() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_DECEMBER ) && !( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetNumberDecember( pProperty->GetNumberDecember() );
		}
	
		// Now check for lock flag
		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_YEAR ) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberYear( pProperty->GetLockNumberYear() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_JANUARY ) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberJanuary( pProperty->GetLockNumberJanuary() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_FEBRUARY ) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberFebruary( pProperty->GetLockNumberFebruary() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_MARCH) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberMarch( pProperty->GetLockNumberMarch() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_APRIL ) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberApril( pProperty->GetLockNumberApril() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_MAY ) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberMay( pProperty->GetLockNumberMay() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_JUNE ) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberJune( pProperty->GetLockNumberJune() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_JULY ) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberJuly( pProperty->GetLockNumberJuly() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_AUGUST ) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberAugust( pProperty->GetLockNumberAugust() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_SEPTEMBER ) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberSeptember( pProperty->GetLockNumberSeptember() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_OCTOBER ) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberOctober( pProperty->GetLockNumberOctober() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_NOVEMBER ) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberNovember( pProperty->GetLockNumberNovember() );
		}

		if ( ( dwChangeFlags & Z_CHANGE_NUMBER_DECEMBER ) && ( dwChangeFlags & Z_CHANGE_LOCKED_MONTH ) ||
			 ( dwChangeFlags & OD_CHANGE_ALL ) )
		{
			SetLockNumberDecember( pProperty->GetLockNumberDecember() );
		}
	}
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf CODFillProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPAnnualNumberProperties::IsEqual( ZBBPAnnualNumberProperties* pProp )
{
	if ( pProp )
	{
		return ( *this == *pProp );
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPAnnualNumberProperties | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPAnnualNumberProperties::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPAnnualNumberProperties::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPAnnualNumberProperties::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPAnnualNumberProperties::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPAnnualNumberProperties::GetValue(const int nPropId, float& fValue) const
//@syntax BOOL ZBBPAnnualNumberProperties::GetValue(const int nPropId, double& dValue) const
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

BOOL ZBBPAnnualNumberProperties::GetValue( const int nPropId, CString& strValue ) const
{
	// Only used to get quantity values
	switch ( nPropId )
	{
		case Z_NUMBER_YEAR:
		{
			strValue.Format( _T( "%.2f" ), GetNumberYear() );
			break;
		}

		case Z_NUMBER_JANUARY:
		{
			strValue.Format( _T( "%.2f" ), GetNumberJanuary() );
			break;
		}

		case Z_NUMBER_FEBRUARY:
		{
			strValue.Format( _T( "%.2f" ), GetNumberFebruary() );
			break;
		}

		case Z_NUMBER_MARCH:
		{
			strValue.Format( _T( "%.2f" ), GetNumberMarch() );
			break;
		}

		case Z_NUMBER_APRIL:
		{
			strValue.Format( _T( "%.2f" ), GetNumberApril() );
			break;
		}

		case Z_NUMBER_MAY:
		{
			strValue.Format( _T( "%.2f" ), GetNumberMay() );
			break;
		}

		case Z_NUMBER_JUNE:
		{
			strValue.Format( _T( "%.2f" ), GetNumberJune() );
			break;
		}

		case Z_NUMBER_JULY:
		{
			strValue.Format( _T( "%.2f" ), GetNumberJuly() );
			break;
		}

		case Z_NUMBER_AUGUST:
		{
			strValue.Format( _T( "%.2f" ), GetNumberAugust() );
			break;
		}

		case Z_NUMBER_SEPTEMBER:
		{
			strValue.Format( _T( "%.2f" ), GetNumberSeptember() );
			break;
		}

		case Z_NUMBER_OCTOBER:
		{
			strValue.Format( _T( "%.2f" ), GetNumberOctober() );
			break;
		}

		case Z_NUMBER_NOVEMBER:
		{
			strValue.Format( _T( "%.2f" ), GetNumberNovember() );
			break;
		}

		case Z_NUMBER_DECEMBER:
		{
			strValue.Format( _T( "%.2f" ), GetNumberDecember() );
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

BOOL ZBBPAnnualNumberProperties::GetValue( const int nPropId, int& nValue ) const
{
	// Only used to get the lock flag value
	switch ( nPropId )
	{
		case Z_LOCKED_YEAR:
		{
			nValue = static_cast<int>( GetLockNumberYear() );
			break;
		}

		case Z_LOCKED_JANUARY:
		{
			nValue = static_cast<int>( GetLockNumberJanuary() );
			break;
		}

		case Z_LOCKED_FEBRUARY:
		{
			nValue = static_cast<int>( GetLockNumberFebruary() );
			break;
		}

		case Z_LOCKED_MARCH:
		{
			nValue = static_cast<int>( GetLockNumberMarch() );
			break;
		}

		case Z_LOCKED_APRIL:
		{
			nValue = static_cast<int>( GetLockNumberApril() );
			break;
		}

		case Z_LOCKED_MAY:
		{
			nValue = static_cast<int>( GetLockNumberMay() );
			break;
		}

		case Z_LOCKED_JUNE:
		{
			nValue = static_cast<int>( GetLockNumberJune() );
			break;
		}

		case Z_LOCKED_JULY:
		{
			nValue = static_cast<int>( GetLockNumberJuly() );
			break;
		}

		case Z_LOCKED_AUGUST:
		{
			nValue = static_cast<int>( GetLockNumberAugust() );
			break;
		}

		case Z_LOCKED_SEPTEMBER:
		{
			nValue = static_cast<int>( GetLockNumberSeptember() );
			break;
		}

		case Z_LOCKED_OCTOBER:
		{
			nValue = static_cast<int>( GetLockNumberOctober() );
			break;
		}

		case Z_LOCKED_NOVEMBER:
		{
			nValue = static_cast<int>( GetLockNumberNovember() );
			break;
		}

		case Z_LOCKED_DECEMBER:
		{
			nValue = static_cast<int>( GetLockNumberDecember() );
			break;
		}

		case Z_FORCE_EQUALIZER:
		{
			nValue = static_cast<int>( GetForceEqualizer() );
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

BOOL ZBBPAnnualNumberProperties::GetValue( const int nPropId, UINT& nValue ) const
{
	// Only used to get the lock flag value
	switch ( nPropId )
	{
		case Z_LOCKED_YEAR:
		{
			nValue = GetLockNumberYear();
			break;
		}

		case Z_LOCKED_JANUARY:
		{
			nValue = GetLockNumberJanuary();
			break;
		}

		case Z_LOCKED_FEBRUARY:
		{
			nValue = GetLockNumberFebruary();
			break;
		}

		case Z_LOCKED_MARCH:
		{
			nValue = GetLockNumberMarch();
			break;
		}

		case Z_LOCKED_APRIL:
		{
			nValue = GetLockNumberApril();
			break;
		}

		case Z_LOCKED_MAY:
		{
			nValue = GetLockNumberMay();
			break;
		}

		case Z_LOCKED_JUNE:
		{
			nValue = GetLockNumberJune();
			break;
		}

		case Z_LOCKED_JULY:
		{
			nValue = GetLockNumberJuly();
			break;
		}

		case Z_LOCKED_AUGUST:
		{
			nValue = GetLockNumberAugust();
			break;
		}

		case Z_LOCKED_SEPTEMBER:
		{
			nValue = GetLockNumberSeptember();
			break;
		}

		case Z_LOCKED_OCTOBER:
		{
			nValue = GetLockNumberOctober();
			break;
		}

		case Z_LOCKED_NOVEMBER:
		{
			nValue = GetLockNumberNovember();
			break;
		}

		case Z_LOCKED_DECEMBER:
		{
			nValue = GetLockNumberDecember();
			break;
		}

		case Z_FORCE_EQUALIZER:
		{
			nValue = GetForceEqualizer();
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

BOOL ZBBPAnnualNumberProperties::GetValue( const int nPropId, DWORD& dwValue ) const
{
	// Only used to get the lock flag value
	switch ( nPropId )
	{
		case Z_LOCKED_YEAR:
		{
			dwValue = static_cast<DWORD>( GetLockNumberYear() );
			break;
		}

		case Z_LOCKED_JANUARY:
		{
			dwValue = static_cast<DWORD>( GetLockNumberJanuary() );
			break;
		}

		case Z_LOCKED_FEBRUARY:
		{
			dwValue = static_cast<DWORD>( GetLockNumberFebruary() );
			break;
		}

		case Z_LOCKED_MARCH:
		{
			dwValue = static_cast<DWORD>( GetLockNumberMarch() );
			break;
		}

		case Z_LOCKED_APRIL:
		{
			dwValue = static_cast<DWORD>( GetLockNumberApril() );
			break;
		}

		case Z_LOCKED_MAY:
		{
			dwValue = static_cast<DWORD>( GetLockNumberMay() );
			break;
		}

		case Z_LOCKED_JUNE:
		{
			dwValue = static_cast<DWORD>( GetLockNumberJune() );
			break;
		}

		case Z_LOCKED_JULY:
		{
			dwValue = static_cast<DWORD>( GetLockNumberJuly() );
			break;
		}

		case Z_LOCKED_AUGUST:
		{
			dwValue = static_cast<DWORD>( GetLockNumberAugust() );
			break;
		}

		case Z_LOCKED_SEPTEMBER:
		{
			dwValue = static_cast<DWORD>( GetLockNumberSeptember() );
			break;
		}

		case Z_LOCKED_OCTOBER:
		{
			dwValue = static_cast<DWORD>( GetLockNumberOctober() );
			break;
		}

		case Z_LOCKED_NOVEMBER:
		{
			dwValue = static_cast<DWORD>( GetLockNumberNovember() );
			break;
		}

		case Z_LOCKED_DECEMBER:
		{
			dwValue = static_cast<DWORD>( GetLockNumberDecember() );
			break;
		}

		case Z_FORCE_EQUALIZER:
		{
			dwValue = static_cast<DWORD>( GetForceEqualizer() );
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

BOOL ZBBPAnnualNumberProperties::GetValue( const int nPropId, float& fValue ) const
{
	// Only used to get quantity values
	switch ( nPropId )
	{
		case Z_NUMBER_YEAR:
		{
			fValue = static_cast<float>( GetNumberYear() );
			break;
		}

		case Z_NUMBER_JANUARY:
		{
			fValue = static_cast<float>( GetNumberJanuary() );
			break;
		}

		case Z_NUMBER_FEBRUARY:
		{
			fValue = static_cast<float>( GetNumberFebruary() );
			break;
		}

		case Z_NUMBER_MARCH:
		{
			fValue = static_cast<float>( GetNumberMarch() );
			break;
		}

		case Z_NUMBER_APRIL:
		{
			fValue = static_cast<float>( GetNumberApril() );
			break;
		}

		case Z_NUMBER_MAY:
		{
			fValue = static_cast<float>( GetNumberMay() );
			break;
		}

		case Z_NUMBER_JUNE:
		{
			fValue = static_cast<float>( GetNumberJune() );
			break;
		}

		case Z_NUMBER_JULY:
		{
			fValue = static_cast<float>( GetNumberJuly() );
			break;
		}

		case Z_NUMBER_AUGUST:
		{
			fValue = static_cast<float>( GetNumberAugust() );
			break;
		}

		case Z_NUMBER_SEPTEMBER:
		{
			fValue = static_cast<float>( GetNumberSeptember() );
			break;
		}

		case Z_NUMBER_OCTOBER:
		{
			fValue = static_cast<float>( GetNumberOctober() );
			break;
		}

		case Z_NUMBER_NOVEMBER:
		{
			fValue = static_cast<float>( GetNumberNovember() );
			break;
		}

		case Z_NUMBER_DECEMBER:
		{
			fValue = static_cast<float>( GetNumberDecember() );
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

BOOL ZBBPAnnualNumberProperties::GetValue( const int nPropId, double& dValue ) const
{
	// Only used to get quantity values
	switch ( nPropId )
	{
		case Z_NUMBER_YEAR:
		{
			dValue = GetNumberYear();
			break;
		}

		case Z_NUMBER_JANUARY:
		{
			dValue = GetNumberJanuary();
			break;
		}

		case Z_NUMBER_FEBRUARY:
		{
			dValue = GetNumberFebruary();
			break;
		}

		case Z_NUMBER_MARCH:
		{
			dValue = GetNumberMarch();
			break;
		}

		case Z_NUMBER_APRIL:
		{
			dValue = GetNumberApril();
			break;
		}

		case Z_NUMBER_MAY:
		{
			dValue = GetNumberMay();
			break;
		}

		case Z_NUMBER_JUNE:
		{
			dValue = GetNumberJune();
			break;
		}

		case Z_NUMBER_JULY:
		{
			dValue = GetNumberJuly();
			break;
		}

		case Z_NUMBER_AUGUST:
		{
			dValue = GetNumberAugust();
			break;
		}

		case Z_NUMBER_SEPTEMBER:
		{
			dValue = GetNumberSeptember();
			break;
		}

		case Z_NUMBER_OCTOBER:
		{
			dValue = GetNumberOctober();
			break;
		}

		case Z_NUMBER_NOVEMBER:
		{
			dValue = GetNumberNovember();
			break;
		}

		case Z_NUMBER_DECEMBER:
		{
			dValue = GetNumberDecember();
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

//@mfunc | ZBBPAnnualNumberProperties | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPAnnualNumberProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPAnnualNumberProperties::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPAnnualNumberProperties::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPAnnualNumberProperties::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPAnnualNumberProperties::SetValue(const int nPropId, const float fValue)
//@syntax BOOL ZBBPAnnualNumberProperties::SetValue(const int nPropId, const double dValue)
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

BOOL ZBBPAnnualNumberProperties::SetValue( const int nPropId, LPCTSTR lpszValue )
{
	// Only used to set quantity values
	switch ( nPropId )
	{
		case Z_NUMBER_YEAR:
		{
			SetNumberYear( static_cast<float>( atof( lpszValue ) ) );
			break;
		}

		case Z_NUMBER_JANUARY:
		{
			SetNumberJanuary( static_cast<float>( atof( lpszValue ) ) );
			break;
		}

		case Z_NUMBER_FEBRUARY:
		{
			SetNumberFebruary( static_cast<float>( atof( lpszValue ) ) );
			break;
		}

		case Z_NUMBER_MARCH:
		{
			SetNumberMarch( static_cast<float>( atof( lpszValue ) ) );
			break;
		}

		case Z_NUMBER_APRIL:
		{
			SetNumberApril( static_cast<float>( atof( lpszValue ) ) );
			break;
		}

		case Z_NUMBER_MAY:
		{
			SetNumberMay( static_cast<float>( atof( lpszValue ) ) );
			break;
		}

		case Z_NUMBER_JUNE:
		{
			SetNumberJune( static_cast<float>( atof( lpszValue ) ) );
			break;
		}

		case Z_NUMBER_JULY:
		{
			SetNumberJuly( static_cast<float>( atof( lpszValue ) ) );
			break;
		}

		case Z_NUMBER_AUGUST:
		{
			SetNumberAugust( static_cast<float>( atof( lpszValue ) ) );
			break;
		}

		case Z_NUMBER_SEPTEMBER:
		{
			SetNumberSeptember( static_cast<float>( atof( lpszValue ) ) );
			break;
		}

		case Z_NUMBER_OCTOBER:
		{
			SetNumberOctober( static_cast<float>( atof( lpszValue ) ) );
			break;
		}

		case Z_NUMBER_NOVEMBER:
		{
			SetNumberNovember( static_cast<float>( atof( lpszValue ) ) );
			break;
		}

		case Z_NUMBER_DECEMBER:
		{
			SetNumberDecember( static_cast<float>( atof( lpszValue ) ) );
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

BOOL ZBBPAnnualNumberProperties::SetValue( const int nPropId, const int nValue )
{
	// Only used to set locked flags
	switch ( nPropId )
	{
		case Z_LOCKED_YEAR:
		{
			SetLockNumberYearEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_LOCKED_JANUARY:
		{
			SetLockNumberJanuaryEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_LOCKED_FEBRUARY:
		{
			SetLockNumberFebruaryEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_LOCKED_MARCH:
		{
			SetLockNumberMarchEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_LOCKED_APRIL:
		{
			SetLockNumberAprilEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_LOCKED_MAY:
		{
			SetLockNumberMayEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_LOCKED_JUNE:
		{
			SetLockNumberJuneEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_LOCKED_JULY:
		{
			SetLockNumberJulyEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_LOCKED_AUGUST:
		{
			SetLockNumberAugustEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_LOCKED_SEPTEMBER:
		{
			SetLockNumberSeptemberEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_LOCKED_OCTOBER:
		{
			SetLockNumberOctoberEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_LOCKED_NOVEMBER:
		{
			SetLockNumberNovemberEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_LOCKED_DECEMBER:
		{
			SetLockNumberDecemberEx( static_cast<UINT>( nValue ) );
			break;
		}

		case Z_FORCE_EQUALIZER:
		{
			SetForceEqualizerEx( static_cast<UINT>( nValue ) );
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

BOOL ZBBPAnnualNumberProperties::SetValue( const int nPropId, const UINT nValue )
{
	// Only used to set locked flags
	switch ( nPropId )
	{
		case Z_LOCKED_YEAR:
		{
			SetLockNumberYearEx( nValue );
			break;
		}

		case Z_LOCKED_JANUARY:
		{
			SetLockNumberJanuaryEx( nValue );
			break;
		}

		case Z_LOCKED_FEBRUARY:
		{
			SetLockNumberFebruaryEx( nValue );
			break;
		}

		case Z_LOCKED_MARCH:
		{
			SetLockNumberMarchEx( nValue );
			break;
		}

		case Z_LOCKED_APRIL:
		{
			SetLockNumberAprilEx( nValue );
			break;
		}

		case Z_LOCKED_MAY:
		{
			SetLockNumberMayEx( nValue );
			break;
		}

		case Z_LOCKED_JUNE:
		{
			SetLockNumberJuneEx( nValue );
			break;
		}

		case Z_LOCKED_JULY:
		{
			SetLockNumberJulyEx( nValue );
			break;
		}

		case Z_LOCKED_AUGUST:
		{
			SetLockNumberAugustEx( nValue );
			break;
		}

		case Z_LOCKED_SEPTEMBER:
		{
			SetLockNumberSeptemberEx( nValue );
			break;
		}

		case Z_LOCKED_OCTOBER:
		{
			SetLockNumberOctoberEx( nValue );
			break;
		}

		case Z_LOCKED_NOVEMBER:
		{
			SetLockNumberNovemberEx( nValue );
			break;
		}

		case Z_LOCKED_DECEMBER:
		{
			SetLockNumberDecemberEx( nValue );
			break;
		}

		case Z_FORCE_EQUALIZER:
		{
			SetForceEqualizerEx( nValue );
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

BOOL ZBBPAnnualNumberProperties::SetValue( const int nPropId, const DWORD dwValue )
{
	// Only used to set locked flags
	switch ( nPropId )
	{
		case Z_LOCKED_YEAR:
		{
			SetLockNumberYearEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_LOCKED_JANUARY:
		{
			SetLockNumberJanuaryEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_LOCKED_FEBRUARY:
		{
			SetLockNumberFebruaryEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_LOCKED_MARCH:
		{
			SetLockNumberMarchEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_LOCKED_APRIL:
		{
			SetLockNumberAprilEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_LOCKED_MAY:
		{
			SetLockNumberMayEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_LOCKED_JUNE:
		{
			SetLockNumberJuneEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_LOCKED_JULY:
		{
			SetLockNumberJulyEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_LOCKED_AUGUST:
		{
			SetLockNumberAugustEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_LOCKED_SEPTEMBER:
		{
			SetLockNumberSeptemberEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_LOCKED_OCTOBER:
		{
			SetLockNumberOctoberEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_LOCKED_NOVEMBER:
		{
			SetLockNumberNovemberEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_LOCKED_DECEMBER:
		{
			SetLockNumberDecemberEx( static_cast<UINT>( dwValue ) );
			break;
		}

		case Z_FORCE_EQUALIZER:
		{
			SetForceEqualizerEx( static_cast<UINT>( dwValue ) );
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

BOOL ZBBPAnnualNumberProperties::SetValue( const int nPropId, const float fValue )
{
	// Only used to set quantity values
	switch ( nPropId )
	{
		case Z_NUMBER_YEAR:
		{
			SetNumberYear( fValue );
			break;
		}

		case Z_NUMBER_JANUARY:
		{
			SetNumberJanuary( fValue );
			break;
		}

		case Z_NUMBER_FEBRUARY:
		{
			SetNumberFebruary( fValue );
			break;
		}

		case Z_NUMBER_MARCH:
		{
			SetNumberMarch( fValue );
			break;
		}

		case Z_NUMBER_APRIL:
		{
			SetNumberApril( fValue );
			break;
		}

		case Z_NUMBER_MAY:
		{
			SetNumberMay( fValue );
			break;
		}

		case Z_NUMBER_JUNE:
		{
			SetNumberJune( fValue );
			break;
		}

		case Z_NUMBER_JULY:
		{
			SetNumberJuly( fValue );
			break;
		}

		case Z_NUMBER_AUGUST:
		{
			SetNumberAugust( fValue );
			break;
		}

		case Z_NUMBER_SEPTEMBER:
		{
			SetNumberSeptember( fValue );
			break;
		}

		case Z_NUMBER_OCTOBER:
		{
			SetNumberOctober( fValue );
			break;
		}

		case Z_NUMBER_NOVEMBER:
		{
			SetNumberNovember( fValue );
			break;
		}

		case Z_NUMBER_DECEMBER:
		{
			SetNumberDecember( fValue );
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

BOOL ZBBPAnnualNumberProperties::SetValue( const int nPropId, const double dValue )
{
	// Only used to set quantity values
	switch ( nPropId )
	{
		case Z_NUMBER_YEAR:
		{
			SetNumberYear( dValue );
			break;
		}

		case Z_NUMBER_JANUARY:
		{
			SetNumberJanuary( dValue );
			break;
		}

		case Z_NUMBER_FEBRUARY:
		{
			SetNumberFebruary( dValue );
			break;
		}

		case Z_NUMBER_MARCH:
		{
			SetNumberMarch( dValue );
			break;
		}

		case Z_NUMBER_APRIL:
		{
			SetNumberApril( dValue );
			break;
		}

		case Z_NUMBER_MAY:
		{
			SetNumberMay( dValue );
			break;
		}

		case Z_NUMBER_JUNE:
		{
			SetNumberJune( dValue );
			break;
		}

		case Z_NUMBER_JULY:
		{
			SetNumberJuly( dValue );
			break;
		}

		case Z_NUMBER_AUGUST:
		{
			SetNumberAugust( dValue );
			break;
		}

		case Z_NUMBER_SEPTEMBER:
		{
			SetNumberSeptember( dValue );
			break;
		}

		case Z_NUMBER_OCTOBER:
		{
			SetNumberOctober( dValue );
			break;
		}

		case Z_NUMBER_NOVEMBER:
		{
			SetNumberNovember( dValue );
			break;
		}

		case Z_NUMBER_DECEMBER:
		{
			SetNumberDecember( dValue );
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

/////////////////////////////////////////////////////////////////////////////
// ZBBPAnnualNumberProperties diagnostics

#ifdef _DEBUG
void ZBBPAnnualNumberProperties::AssertValid() const
{
	CObject::AssertValid();
}

void ZBBPAnnualNumberProperties::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ZBBPAnnualNumberProperties serialization

//@mfunc Serializes the orientation properties.
//@rdesc void
//@parm The archive to use for serialization.

void ZBBPAnnualNumberProperties::Serialize( CArchive& ar )
{
	if ( ar.IsStoring() )
	{
		TRACE( _T( "ZBBPAnnualNumberProperties::Serialize : Start Save\n" ) );

		PUT_SCHEMA( ar, ZBBPAnnualNumberProperties );

		ar << GetNumberYear();
		ar << GetNumberJanuary();
		ar << GetNumberFebruary();
		ar << GetNumberMarch();
		ar << GetNumberApril();
		ar << GetNumberMay();
		ar << GetNumberJune();
		ar << GetNumberJuly();
		ar << GetNumberAugust();
		ar << GetNumberSeptember();
		ar << GetNumberOctober();
		ar << GetNumberNovember();
		ar << GetNumberDecember();

		// JMR-MODIF - Le 22 juin 2004 - Ajout de la conversion explicite, afin de supprimer une erreur de
		// corruption des fichiers.
		ar << (UINT)GetLockNumberYear();
		ar << (UINT)GetLockNumberJanuary();
		ar << (UINT)GetLockNumberFebruary();
		ar << (UINT)GetLockNumberMarch();
		ar << (UINT)GetLockNumberApril();
		ar << (UINT)GetLockNumberMay();
		ar << (UINT)GetLockNumberJune();
		ar << (UINT)GetLockNumberJuly();
		ar << (UINT)GetLockNumberAugust();
		ar << (UINT)GetLockNumberSeptember();
		ar << (UINT)GetLockNumberOctober();
		ar << (UINT)GetLockNumberNovember();
		ar << (UINT)GetLockNumberDecember();
		ar << (UINT)GetForceEqualizer();

		TRACE( _T( "ZBBPAnnualNumberProperties::Serialize : End Save\n" ) );
	}
	else
	{
		TRACE( _T( "ZBBPAnnualNumberProperties::Serialize : Start Read\n" ) );

		UINT nSchema;
		GET_SCHEMA( ar, nSchema );
		double dValue;
		UINT  nValue;

		ar >> dValue;
		SetNumberYear( dValue );
		ar >> dValue;
		SetNumberJanuary( dValue );
		ar >> dValue;
		SetNumberFebruary( dValue );
		ar >> dValue;
		SetNumberMarch( dValue );
		ar >> dValue;
		SetNumberApril( dValue );
		ar >> dValue;
		SetNumberMay( dValue );
		ar >> dValue;
		SetNumberJune( dValue );
		ar >> dValue;
		SetNumberJuly( dValue );
		ar >> dValue;
		SetNumberAugust( dValue );
		ar >> dValue;
		SetNumberSeptember( dValue );
		ar >> dValue;
		SetNumberOctober( dValue );
		ar >> dValue;
		SetNumberNovember( dValue );
		ar >> dValue;
		SetNumberDecember( dValue );

		ar >> nValue;
		SetLockNumberYearEx( nValue );
		ar >> nValue;
		SetLockNumberJanuaryEx( nValue );
		ar >> nValue;
		SetLockNumberFebruaryEx( nValue );
		ar >> nValue;
		SetLockNumberMarchEx( nValue );
		ar >> nValue;
		SetLockNumberAprilEx( nValue );
		ar >> nValue;
		SetLockNumberMayEx( nValue );
		ar >> nValue;
		SetLockNumberJuneEx( nValue );
		ar >> nValue;
		SetLockNumberJulyEx( nValue );
		ar >> nValue;
		SetLockNumberAugustEx( nValue );
		ar >> nValue;
		SetLockNumberSeptemberEx( nValue );
		ar >> nValue;
		SetLockNumberOctoberEx( nValue );
		ar >> nValue;
		SetLockNumberNovemberEx( nValue );
		ar >> nValue;
		SetLockNumberDecemberEx( nValue );
		ar >> nValue;
		SetForceEqualizerEx( nValue );

		TRACE( _T( "ZBBPAnnualNumberProperties::Serialize : End Read\n" ) );

		CalculatePercents();
	}
}
