//---------------------------------------------------------------------------
// Author    : Dominique Aigroz            
// HeaderFile: ZBTimeSpan.h
// Created   : 14.12.1994
// Modify    :           
//
//
// Call      : 
//
//---------------------------------------------------------------------------

#if !defined(__ZBTIMESPAN_H)
#define __ZBTIMESPAN_H

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

class AFX_EXT_CLASS ZBTimeSpan : public COleDateTimeSpan
{
public:
// Inherited feature
	typedef COleDateTimeSpan inherited;

public:
	// Constructors
	ZBTimeSpan();
	ZBTimeSpan( double dblSpanSrc );
	ZBTimeSpan( long lDays, int nHours, int nMins, int nSecs );

	// Destructor
	virtual ~ZBTimeSpan();

	// Copy constructors
	ZBTimeSpan( const ZBTimeSpan &right );
	ZBTimeSpan( const CTimeSpan &right );
	ZBTimeSpan( const COleDateTimeSpan &right );
	ZBTimeSpan( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST = -1 );

	BOOL	IsEmpty();
	void	Clear();

	const ZBTimeSpan & operator=( const ZBTimeSpan &right );
	const ZBTimeSpan & operator=( const COleDateTimeSpan &right );
	const ZBTimeSpan & operator=( const CTimeSpan &right );

	//	Make a clone of the object.
	virtual ZBTimeSpan* Clone();

	CString GetStandardFormatedTimeSpan();
	CString GetFormatedTimeSpan( CString Format );
	CString GetFormatedTimeSpan( UINT nFormatID );

	void	ClearTime();
};

inline ZBTimeSpan::ZBTimeSpan( double dblSpanSrc )
	: COleDateTimeSpan( dblSpanSrc )
{
}

inline ZBTimeSpan::ZBTimeSpan( long lDays, int nHours, int nMins, int nSecs )
	: COleDateTimeSpan( lDays, nHours, nMins, nSecs )
{
}


inline ZBTimeSpan::ZBTimeSpan( const ZBTimeSpan &right )
	: COleDateTimeSpan( right )
{
}

inline ZBTimeSpan::ZBTimeSpan( const CTimeSpan &right )
	: COleDateTimeSpan( (long)right.GetDays(), right.GetHours(), right.GetMinutes(), right.GetSeconds() )
{
}

inline ZBTimeSpan::ZBTimeSpan( const COleDateTimeSpan &right )
	: COleDateTimeSpan( right )
{
}

inline BOOL ZBTimeSpan::IsEmpty()
{
	return ( m_span == 0 ) ? TRUE : FALSE;
}

#endif // __ZBTIMESPAN_H