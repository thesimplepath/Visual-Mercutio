/****************************************************************************************************************
 *												   Classe ZBDuration											*
 ****************************************************************************************************************
 * Cette classe permet de traiter les données des propriétés de durée. Elle s'occupe également des conversions.	*
 ****************************************************************************************************************/

#if !defined(AFX_ZBDuration_H__68FF3F60_E39C_4145_BDF2_811425B343D8__INCLUDED_)
#define AFX_ZBDuration_H__68FF3F60_E39C_4145_BDF2_811425B343D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 15 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#define MAX_DAYS_IN_SPANDURATION	3615897L

class AFX_EXT_CLASS ZBDuration
{
public:

	enum DurationStatus
	{
		valid	= 0,
		invalid	= 1,	// Invalid date (out of range, etc.)
		null	= 2,	// Literally has no value
	};

	double			m_span;

	DurationStatus	m_status;

	// Base time constant for calculation
	int				m_HourPerDay;
	int				m_DayPerWeek;
	int				m_DayPerMonth;
	int				m_DayPerYear;

public:

	// Constructors
	ZBDuration( int HourPerDay	= 8,
				int DayPerWeek	= 5,
				int DayPerMonth	= 22,
				int DayPerYear	= 220);

	ZBDuration( double value,
				int HourPerDay	= 8,
				int DayPerWeek	= 5,
				int DayPerMonth	= 22,
				int DayPerYear	= 220);

	ZBDuration( long lDays,
				int nHours,
				int nMins,
				int nSecs		= 0,
				int HourPerDay	= 8,
				int DayPerWeek	= 5,
				int DayPerMonth	= 22,
				int DayPerYear	= 220 );

	// Copy constructors
	ZBDuration::ZBDuration( const ZBDuration& right );

	// Destructors
	virtual ~ZBDuration();

public:

	void SetStatus( DurationStatus status )
	{
		m_status = status;
	};

	DurationStatus GetStatus() const
	{
		return m_status;
	};

	double GetTotalDays		() const;		// span in days (about -3.65e6 to 3.65e6)
	double GetTotalHours	() const;		// span in hours (about -8.77e7 to 8.77e6)
	double GetTotalMinutes	() const;		// span in minutes (about -5.26e9 to 5.26e9)
	double GetTotalSeconds	() const;		// span in seconds (about -3.16e11 to 3.16e11)

	long GetDays			() const;		// component days in span
	long GetHours			() const;		// component hours in span (-23 to 23)
	long GetMinutes			() const;		// component minutes in span (-59 to 59)
	long GetSeconds			() const;		// component seconds in span (-59 to 59)

	double ConvertWeekToDays ( int value );	// Converts the number of week in number of days
	double ConvertMonthToDays( int value );	// Converts the number of month in number of days

	void AddWeek ( int value );				// add a number of weeks
	void AddMonth( int value );				// add a number of months
	void SubWeek ( int value );				// substract a number of weeks
	void SubMonth( int value );				// substract a number of months

	// Assignment operators
	const ZBDuration& operator=( double value );
	const ZBDuration& operator=( const ZBDuration& right );

	// Comparison operators
	BOOL operator==( const ZBDuration& right ) const;
	BOOL operator!=( const ZBDuration& right ) const;
	BOOL operator< ( const ZBDuration& right ) const;
	BOOL operator> ( const ZBDuration& right ) const;
	BOOL operator<=( const ZBDuration& right ) const;
	BOOL operator>=( const ZBDuration& right ) const;

	// Math operators
	ZBDuration operator+( const ZBDuration& right ) const;
	ZBDuration operator-( const ZBDuration& right ) const;
	const ZBDuration& operator+=( const ZBDuration right );
	const ZBDuration& operator-=( const ZBDuration right );
	ZBDuration operator-() const;

	operator double() const;

	void SetDuration( long lDays, int nHours, int nMins, int nSecs = 0 );

	// Formatting
	CString Format( LPCTSTR pFormat ) const;
	CString Format( UINT nID ) const;

private:

	double GetHalfSecond() const
	{
		return ( 1.0 / ( 2.0 * ( 60.0 * 60.0 * (double)m_HourPerDay ) ) );
	};

	void CheckRange();
};

inline ZBDuration::ZBDuration( int HourPerDay	/*= 8*/,
							   int DayPerWeek	/*= 5*/,
							   int DayPerMonth	/*= 22*/,
							   int DayPerYear	/*= 220*/)
	: m_HourPerDay	( HourPerDay ),
	  m_DayPerWeek	( DayPerWeek ),
	  m_DayPerMonth	( DayPerMonth ),
	  m_DayPerYear	( DayPerYear ),
	  m_span		( 0.0 )
{
	SetStatus( valid );
}

inline ZBDuration::ZBDuration( double	value,
							   int		HourPerDay	/*= 8*/,
							   int		DayPerWeek	/*= 5*/,
							   int		DayPerMonth	/*= 22*/,
							   int		DayPerYear	/*= 220*/)
	: m_HourPerDay	( HourPerDay ),
	  m_DayPerWeek	( DayPerWeek ),
	  m_DayPerMonth	( DayPerMonth ),
	  m_DayPerYear	( DayPerYear ),
	  m_span		( value )
{
	SetStatus( valid );
}

inline ZBDuration::ZBDuration( long	lDays,
							   int	nHours,
							   int	nMins,
							   int	nSecs		/*= 0*/,
							   int	HourPerDay	/*= 8*/,
							   int	DayPerWeek	/*= 5*/,
							   int	DayPerMonth	/*= 22*/,
							   int	DayPerYear	/*= 220*/)
	: m_HourPerDay	( HourPerDay ),
	  m_DayPerWeek	( DayPerWeek ),
	  m_DayPerMonth	( DayPerMonth ),
	  m_DayPerYear	( DayPerYear )
{
	SetDuration( lDays, nHours, nMins, nSecs );
}

inline ZBDuration::ZBDuration( const ZBDuration& right )
{ 
	*this = right; 
}

inline ZBDuration::~ZBDuration()
{
}

inline void ZBDuration::SetDuration( long lDays, int nHours, int nMins, int nSecs /*= 0*/ )
{
	// Set date span by breaking into fractional days (all input ranges valid)
	m_span = lDays +
			 ( (double)nHours ) /   (double)m_HourPerDay +
			 ( (double)nMins  ) / ( (double)m_HourPerDay * 60 ) +
			 ( (double)nSecs  ) / ( (double)m_HourPerDay * 60 * 60 );

	SetStatus( valid );
}

inline double ZBDuration::GetTotalDays() const
{
	ASSERT( GetStatus() == valid );
	return m_span; 
}

inline double ZBDuration::GetTotalHours() const
{
	ASSERT( GetStatus() == valid );
	long lReturns = (long)( m_span * (double)m_HourPerDay + GetHalfSecond() );
	return lReturns;
}

inline double ZBDuration::GetTotalMinutes() const
{
	ASSERT( GetStatus() == valid );
	long lReturns = (long)( m_span * (double)m_HourPerDay * 60 + GetHalfSecond() );
	return lReturns;
}

inline double ZBDuration::GetTotalSeconds() const
{
	ASSERT( GetStatus() == valid );
	long lReturns = (long)( m_span * (double)m_HourPerDay * 60 * 60 + GetHalfSecond() );
	return lReturns;
}

inline long ZBDuration::GetDays() const
{
	ASSERT( GetStatus() == valid );
	return (long)m_span; 
}

inline BOOL ZBDuration::operator==( const ZBDuration& right ) const
{
	return ( m_status == right.m_status && m_span == right.m_span );
}

inline BOOL ZBDuration::operator!=( const ZBDuration& right ) const
{
	return ( m_status != right.m_status || m_span != right.m_span ); 
}

inline BOOL ZBDuration::operator<( const ZBDuration& right ) const
{
	ASSERT( GetStatus() == valid );
	ASSERT( right.GetStatus() == valid );
	return m_span < right.m_span;
}

inline BOOL ZBDuration::operator>( const ZBDuration& right ) const
{
	ASSERT( GetStatus() == valid );
	ASSERT( right.GetStatus() == valid );
	return m_span > right.m_span;
}

inline BOOL ZBDuration::operator<=( const ZBDuration& right ) const
{
	ASSERT( GetStatus() == valid );
	ASSERT( right.GetStatus() == valid );
	return m_span <= right.m_span;
}

inline BOOL ZBDuration::operator>=( const ZBDuration& right ) const
{
	ASSERT( GetStatus() == valid );
	ASSERT( right.GetStatus() == valid );
	return m_span >= right.m_span;
}

inline const ZBDuration& ZBDuration::operator+=( const ZBDuration right )
{
	*this = *this + right;
	return *this;
}

inline const ZBDuration& ZBDuration::operator-=( const ZBDuration right )
{
	*this = *this - right;
	return *this;
}

inline ZBDuration ZBDuration::operator-() const
{
	return -this->m_span;
}

inline ZBDuration::operator double() const
{
	return m_span;
}

inline double ZBDuration::ConvertWeekToDays( int value )
{
	return ( (double)m_DayPerWeek * (double)value );
}

inline double ZBDuration::ConvertMonthToDays( int value )
{
	return (( double)m_DayPerMonth * (double)value );
}

inline void ZBDuration::AddWeek( int value )
{
	*this += ConvertWeekToDays( value );
}

inline void ZBDuration::AddMonth( int value )
{
	*this += ConvertMonthToDays( value );
}

inline void ZBDuration::SubWeek( int value )
{
	*this -= ConvertWeekToDays( value );
}

inline void ZBDuration::SubMonth( int value )
{
	*this -= ConvertMonthToDays( value );
}

inline void ZBDuration::CheckRange()
{
	if( m_span < -MAX_DAYS_IN_SPANDURATION || m_span > MAX_DAYS_IN_SPANDURATION )
	{
		SetStatus( invalid );
	}
}

#ifdef _DEBUG
CDumpContext& AFXAPI operator<<( CDumpContext& dc,ZBDuration src );
#endif

CArchive& AFXAPI operator<<( CArchive& ar, ZBDuration src );
CArchive& AFXAPI operator>>( CArchive& ar, ZBDuration& src );

#endif // !defined(AFX_ZBDuration_H__68FF3F60_E39C_4145_BDF2_811425B343D8__INCLUDED_)