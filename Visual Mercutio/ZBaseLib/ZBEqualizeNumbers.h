// ZBEqualizeNumbers.h: interface for the ZBEqualizeNumbers class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBEQUALIZENUMBERS_H__7C8AF995_1480_437E_A59F_7807B589393C__INCLUDED_)
#define AFX_ZBEQUALIZENUMBERS_H__7C8AF995_1480_437E_A59F_7807B589393C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 31 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class _ZBEquNumber
{
public:

	_ZBEquNumber( double Number = 0, bool Locked = false )
	{
		m_Number = Number;
		m_Locked = Locked;
		m_Percent = 0;
	};

	//@cmember
	/* Copy constructor. */
	_ZBEquNumber(const _ZBEquNumber& right)
	{
		*this = right;
	};

	virtual ~_ZBEquNumber()
	{
	};

	//@cmember
	/* Assigns operator. */
	_ZBEquNumber& operator=(const _ZBEquNumber& right)
	{
		m_Number = right.m_Number;
		m_Locked = right.m_Locked;
		m_Percent = right.m_Percent;
		return *this;
	};

	_ZBEquNumber* Clone()
	{
		return new _ZBEquNumber(*this);
	};

public:

	double	m_Number;
	double	m_Percent;
	bool	m_Locked;
};

using namespace sfl;

//@type ZBEquNumberSet | An array of _ZBEquNumber pointers.
//@iex typedef CCArray_T<_ZBEquNumber*,_ZBEquNumber*> ZBEquNumberSet;
typedef CCArray_T<_ZBEquNumber*, _ZBEquNumber*> ZBEquNumberSet;

//@type ZBEquNumberIterator | An iterator for ZBEquNumberSet collections.
//@iex typedef Iterator_T<_ZBEquNumber*> ZBEquNumberIterator;
typedef Iterator_T<_ZBEquNumber*> ZBEquNumberIterator;

//@type ZBdoubleSet | An array of double.
//@iex typedef CCArray_T<double,double> ZBdoubleSet;
typedef CCArray_T<double, double> ZBdoubleSet;

//@type ZBEquNumberIterator | An iterator for ZBdoubleSet collections.
//@iex typedef Iterator_T<double> ZBEquNumberIterator;
typedef Iterator_T<double> ZBdoubleIterator;

class AFX_EXT_CLASS ZBEqualizeNumbers
{
public:

	//////////////////////////////////////////////////////////////////////
	// Construction/Destruction
	//////////////////////////////////////////////////////////////////////
	ZBEqualizeNumbers( const double MinValue = 0 )
		: m_MinValue( MinValue )
	{
	};

	//@cmember
	/* Copy constructor. */
	ZBEqualizeNumbers( const ZBEqualizeNumbers& right )
	{
		*this = right;
	};

	virtual ~ZBEqualizeNumbers()
	{
		Reset();
	};

	//@cmember
	/* Assigns operator. */
	ZBEqualizeNumbers& operator=( const ZBEqualizeNumbers& right );

	void SetTotal( double Total )
	{
		m_Total = Total;
	};

	// Set the total with equalization
	void SetTotalEqualizeNumbers( double Total );

	// Set the total and re-equalize the remaining number with the difference
	void SetTotalReEqualizeNumbers( double Total );

	double GetTotal() const
	{
		return m_Total;
	};

	// Get and Set for the total locked flag
	bool GetLockedTotal() const;
	void SetLockedTotal( bool value );

	void FillSet( ZBEquNumberSet& set )
	{
		Reset();

		ZBEquNumberIterator i( &set );

		for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; pNumber = i.GetNext() )
		{
			m_Set.Add( pNumber );
		}
	};

	void FillSet( ZBdoubleSet& set, bool Locked = false )
	{
		Reset();

		int Count = set.GetSize();

		for ( int i = 0; i < Count; ++i )
		{
			m_Set.Add( new _ZBEquNumber( set.GetAt(i), Locked ) );
		}
	};

	void AddNumber( double Number, bool Locked = false )
	{
		m_Set.Add( new _ZBEquNumber( Number, Locked ) );
	};

	void SetNumberAt( size_t Index, double Number, bool Locked )
	{
		if ( Index < GetCount() )
		{
			m_Set.GetAt( Index )->m_Number = Number;
			m_Set.GetAt( Index )->m_Locked = Locked;
		}
		else
		{
			m_Set.SetAtGrow( Index, new _ZBEquNumber( Number, Locked ) );
		}
	};

	void SetNumberAt( size_t Index, double Number )
	{
		if ( Index < GetCount() )
		{
			m_Set.GetAt( Index )->m_Number = Number;
		}
		else
		{
			m_Set.SetAtGrow( Index, new _ZBEquNumber( Number ) );
		}
	};

	// Set a specific number and equalize all other numbers
	void SetNumberAtEqualize( size_t Index, double Number );

	// Set a specific percent and equalize all other numbers
	void SetPercentAtEqualize( size_t Index, double Percent );

	void SetLockedFlagAt( size_t Index, bool Locked )
	{
		if ( Index < GetCount() )
		{
			m_Set.GetAt( Index )->m_Locked = Locked;
		}
		else
		{
			m_Set.SetAtGrow( Index, new _ZBEquNumber( 0, Locked ) );
		}
	};

	double GetNumberAt( size_t Index, bool& Error ) const
	{
		if ( Index < GetCount() )
		{
			Error = false;
			return m_Set.GetAt( Index )->m_Number;
		}
		else
		{
			Error = true;
		}

		return 0;
	};

	bool GetLockedFlagAt( size_t Index, bool& Error ) const
	{
		if ( Index < GetCount() )
		{
			Error = false;
			return m_Set.GetAt( Index )->m_Locked;
		}
		else
		{
			Error = true;
		}

		return 0;
	};

	void Reset()
	{
		int Count = m_Set.GetSize();

		for ( int i = 0; i < Count; ++i )
		{
			if ( m_Set.GetAt( i ) )
			{
				delete m_Set.GetAt( i );
			}
		}

		m_Set.RemoveAll();
	};

	// Return the sum of all numbers
	double GetSum() const
	{
		ZBEquNumberIterator i( &m_Set );
		double Sum = 0;

		for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; pNumber = i.GetNext() )
		{
			Sum += pNumber->m_Number;
		}

		return Sum;
	};

	// Return the sum of all locked numbers only
	double GetSumOfLockedNumbers() const
	{
		ZBEquNumberIterator i( &m_Set );
		double Sum = 0;

		for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; pNumber = i.GetNext() )
		{
			if ( pNumber->m_Locked == true )
			{
				Sum += pNumber->m_Number;
			}
		}

		return Sum;
	};

	// Return the sum of all unlocked numbers only
	double GetSumOfUnlockedNumbers() const
	{
		ZBEquNumberIterator i( &m_Set );
		double Sum = 0;

		for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; pNumber = i.GetNext() )
		{
			if ( pNumber->m_Locked == false )
			{
				Sum += pNumber->m_Number;
			}
		}

		return Sum;
	};

	// Return the count of all numbers
	size_t GetCount() const
	{
		return m_Set.GetSize();
	};

	// Return the count of all locked numbers only
	size_t GetLockedCount() const
	{
		ZBEquNumberIterator i( &m_Set );
		size_t Counter = 0;

		for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; pNumber = i.GetNext() )
		{
			if ( pNumber->m_Locked == true )
			{
				++Counter;
			}
		}

		return Counter;
	};

	// Return the count of all unlocked numbers only
	size_t GetUnlockedCount() const
	{
		ZBEquNumberIterator i( &m_Set );
		size_t Counter = 0;

		for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; pNumber = i.GetNext() )
		{
			if ( pNumber->m_Locked == false )
			{
				++Counter;
			}
		}

		return Counter;
	};

	// Set the same value to locked numbers
	void SetValueToLockedNumbers( double Value, int IndexExcepted = -1 )
	{
		ZBEquNumberIterator i( &m_Set );
		int n = 0;

		for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; ++n, pNumber = i.GetNext() )
		{
			if ( pNumber->m_Locked == true && n != IndexExcepted )
			{
				pNumber->m_Number = Value;
			}
		}
	};

	// Set the same value to unlocked numbers
	void SetValueToUnlockedNumbers( double Value, int IndexExcepted = -1 )
	{
		ZBEquNumberIterator i( &m_Set );
		int n = 0;

		for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; ++n, pNumber = i.GetNext() )
		{
			if ( pNumber->m_Locked == false && n != IndexExcepted )
			{
				pNumber->m_Number = Value;
			}
		}
	};

	// Add a delta to locked numbers
	// Returns true if all numbers have been updated by the specific delta
	// false if the system has forced one number due to the minvalue 
	bool AddDeltaToLockedNumbers( double Delta, int IndexExcepted = -1 )
	{
		bool DeltaRespected = true;
		ZBEquNumberIterator i( &m_Set );
		int n = 0;

		for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; ++n, pNumber = i.GetNext() )
		{
			if ( pNumber->m_Locked == true && n != IndexExcepted )
			{
				if ( ( pNumber->m_Number + Delta ) < m_MinValue )
				{
					pNumber->m_Number	= m_MinValue;
					DeltaRespected		= false;
				}
				else
				{
					pNumber->m_Number += Delta;
				}
			}
		}

		return DeltaRespected;
	};

	// Add a delta to unlocked numbers
	// Returns true if all numbers have been updated by the specific delta
	// false if the system has forced one number due to the minvalue 
	bool AddDeltaToUnlockedNumbers( double Delta, int IndexExcepted = -1 )
	{
		bool DeltaRespected = true;
		ZBEquNumberIterator i( &m_Set );
		int n = 0;

		for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; ++n, pNumber = i.GetNext() )
		{
			if ( pNumber->m_Locked == false && n != IndexExcepted )
			{
				if ( ( pNumber->m_Number + Delta ) < m_MinValue )
				{
					pNumber->m_Number	 = m_MinValue;
					DeltaRespected		= false;
				}
				else
				{
					pNumber->m_Number += Delta;
				}
			}
		}

		return DeltaRespected;
	};

	// Substract a delta to locked numbers
	// Returns true if all numbers have been updated by the specific delta
	// false if the system has forced one number due to the minvalue 
	bool SubstDeltaToLockedNumbers( double Delta, int IndexExcepted = -1 )
	{
		bool DeltaRespected = true;
		ZBEquNumberIterator i( &m_Set );
		int n = 0;

		for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; ++n, pNumber = i.GetNext() )
		{
			if ( pNumber->m_Locked == true && n != IndexExcepted )
			{
				if ( ( pNumber->m_Number - Delta ) < m_MinValue )
				{
					pNumber->m_Number	= m_MinValue;
					DeltaRespected		= false;
				}
				else
				{
					pNumber->m_Number -= Delta;
				}
			}
		}

		return DeltaRespected;
	};

	// Substract a delta to unlocked numbers
	// Returns true if all numbers have been updated by the specific delta
	// false if the system has forced one number due to the minvalue 
	bool SubstDeltaToUnlockedNumbers( double Delta, int IndexExcepted = -1 )
	{
		bool DeltaRespected = true;
		ZBEquNumberIterator i( &m_Set );
		int n = 0;

		for ( _ZBEquNumber* pNumber = i.GetFirst(); pNumber; ++n, pNumber = i.GetNext() )
		{
			if ( pNumber->m_Locked == false && n != IndexExcepted )
			{
				if ( ( pNumber->m_Number - Delta ) < m_MinValue )
				{
					pNumber->m_Number	= m_MinValue;
					DeltaRespected		= false;
				}
				else
				{
					pNumber->m_Number -= Delta;
				}
			}
		}

		return DeltaRespected;
	};

	// Used to calculate the percent of all numbers
	void CalculatePercents();

	// Used to calculate the percent of a specific element
	void CalculatePercent( size_t Index );

	const ZBEquNumberSet& GetNumberSetConst() const
	{
		return m_Set;
	};

private:

	ZBEquNumberSet	m_Set;
	bool			m_LockedTotal;
	double			m_Total;
	double			m_MinValue;
};

inline bool ZBEqualizeNumbers::GetLockedTotal() const
{
	return m_LockedTotal;
}

inline void ZBEqualizeNumbers::SetLockedTotal( bool value )
{
	m_LockedTotal = value;
}

#endif // !defined(AFX_ZBEQUALIZENUMBERS_H__7C8AF995_1480_437E_A59F_7807B589393C__INCLUDED_)