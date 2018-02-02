// ZBEqualizeNumbers.cpp: implementation of the ZBEqualizeNumbers class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBEqualizeNumbers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 27 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

ZBEqualizeNumbers& ZBEqualizeNumbers::operator=( const ZBEqualizeNumbers& right )
{
	// First, reset the array
	Reset();

	// Copy objects
	ZBEquNumberIterator i( &right.GetNumberSetConst() );

	for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; pNumber = i.GetNext() )
	{
		m_Set.Add( pNumber->Clone() );
	}

	// Copy member variables
	m_LockedTotal	= right.m_LockedTotal;
	m_Total			= right.m_Total;
	m_MinValue		= right.m_MinValue;

	return *this;
}

void ZBEqualizeNumbers::SetNumberAtEqualize( size_t Index, double Number )
{
	double CountLocked		= static_cast<double>( GetLockedCount() );
	double CountUnlocked	= static_cast<double>( GetUnlockedCount() );

	double TotalLocked		= GetSumOfLockedNumbers();
	double TotalUnlocked	= GetSumOfUnlockedNumbers();

	bool Error;
	double PreviousNumber	= GetNumberAt( Index, Error );

	if ( Error )
	{
		return;
	}

	// First, check that the minimum value is respected. If not, then sets
	// the min value.
	if ( Number < m_MinValue )
	{
		Number = m_MinValue;
	}

	// This is what can be removed from elements
	double MaximumValue = TotalUnlocked - PreviousNumber;

	// If the initial number is greather than the maximum value,
	// Then sets all elements to zero and sets the number to the 
	// maximum value
	if ( Number > TotalUnlocked )
	{
		// Sets the new number
		SetNumberAt( Index, TotalUnlocked );

		// Sets all other unlocked value to zero
		SetValueToUnlockedNumbers( 0, Index );
	}
	else
	{
		// Calculate the difference
		double Diff = PreviousNumber - Number;

		// Sets the new number
		SetNumberAt( Index, Number );

		do
		{
			double ValuePerElement = Diff / ( CountUnlocked - 1 );

			// And now add the difference per element, except for the current element
			AddDeltaToUnlockedNumbers( ValuePerElement, Index );

			// Calculate the difference against the real sum
			Diff = GetTotal() - GetSum();
		}
		while ( Diff > 0.01 || Diff < -0.01 );
	}

	// Recalculate all percentages
	CalculatePercents();
}

void ZBEqualizeNumbers::SetPercentAtEqualize( size_t Index, double Percent )
{
	// We need to calculate the new number
	double NewNumber = Percent * GetTotal();

	// Once we have this new number, we call the SetNumberAtEqualize
	// to assign its new value
	SetNumberAtEqualize( Index, NewNumber );
}

void ZBEqualizeNumbers::SetTotalEqualizeNumbers( double Total )
{
	// Assigns the new total
	SetTotal( Total );

	// Equalize all unlocked numbers function of percent
	ZBEquNumberIterator i( &m_Set );

	for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; pNumber = i.GetNext() )
	{
		if ( pNumber->m_Locked == false )
		{
			pNumber->m_Number = pNumber->m_Percent * Total;
		}
	}
}

void ZBEqualizeNumbers::SetTotalReEqualizeNumbers( double Total )
{
	// Calculates the amount to distribute
	// its the total less the sum of locked numbers which will not change
	double RemainingTotal = Total - GetSumOfLockedNumbers();

	// Assigns the new total
	SetTotal( Total );

	// Equalize all unlocked numbers function of percent
	ZBEquNumberIterator i( &m_Set );

	for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; pNumber = i.GetNext() )
	{
		if ( pNumber->m_Locked == false )
		{
			pNumber->m_Number = pNumber->m_Percent * RemainingTotal;
		}
	}
}

void ZBEqualizeNumbers::CalculatePercents()
{
	double TotalSum = GetTotal();

	// Run through the list of elements and calculate the percentage
	ZBEquNumberIterator i( &m_Set );

	for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; pNumber = i.GetNext() )
	{
		// RS-MODIF 18.08.05 division par zéro ou "-1" => valeur négative! et calculs faux!
		if ( TotalSum > 0 )
		{
			pNumber->m_Percent = pNumber->m_Number / TotalSum;
		}
		else pNumber->m_Percent = 0;
	}
}

void ZBEqualizeNumbers::CalculatePercent( size_t Index )
{
	if ( Index < GetCount() )
	{
		_ZBEquNumber* pNumber	= m_Set.GetAt( Index );
		pNumber->m_Percent		= pNumber->m_Number / GetTotal();
	}
}
