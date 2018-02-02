// ZBStringFormat.h: interface for the ZBStringFormat class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSTRINGFORMAT_H__9B99CE23_7F0D_4879_9BAE_365F1037FE64__INCLUDED_)
#define AFX_ZBSTRINGFORMAT_H__9B99CE23_7F0D_4879_9BAE_365F1037FE64__INCLUDED_

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

// JMR-MODIF - Le 1er février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBStringFormat : public CObject
{
	DECLARE_SERIAL( ZBStringFormat )

public:

	enum FormatType{ General,
					 Number,
					 Currency,
					 Accounting,	// with thousand separator
					 Accounting1,	// with thousand separator and automatic decimal
					 DateTime,		// dd/mm/yy hour:min
					 DateTime1,		// dd/mm/yy hour:min:sec
					 DateTime2,		// dd/mth/yy hour:min
					 DateTime3,		// dd/mth/yy hour:min:sec
					 DateTime4,		// dd-mth-yy hour::min
					 DateTime5,		// dd-mth-yy hour::min::sec
					 Date,			// dd/mm/yy
					 Date1,			// dd/mth/yy
					 Date2,			// mth-yy
					 Date3,			// month-yy
					 Date4,			// month dd, yy
					 Time,			// hour:min
					 Time1,			// hour:min:sec
					 Time2,			// days-hour:min
					 Time3,			// days-hour:min:sec
					 Duration,		// dys-hour:min
					 Duration1,		// dys-hour:min:sec
					 Duration2,		// nnd hour:min:sec
					 Duration3,		// nnd hour:min
					 Duration4,		// nn days hour:min
					 Duration5,		// nn days hour:min:sec
					 Duration6,		// nnd ##:##:##
					 Duration7,		// nn days ##:##:##
					 Percentage,
					 Scientific,
					 Custom };

public:

	// Inherited feature
	typedef CObject inherited;

public:

	ZBStringFormat(	FormatType	ft				= General,
					bool		UseSeparator	= false,
					int			DecimalPlace	= -1,
					CString		Currency		= _T( "" ),
					LCID		lcid			= 0 );

	ZBStringFormat( CString CustomFormat, LCID lcid = 0 );

	ZBStringFormat( const ZBStringFormat &right );

	virtual ~ZBStringFormat();

	const ZBStringFormat & operator=( const ZBStringFormat &right );

	void Release();

	// Set a new language
	void SetLanguage( USHORT usPrimaryLanguage, USHORT usSubLanguage, WORD wSortID = SORT_DEFAULT )
	{
		WORD li = MAKELANGID( usPrimaryLanguage, usSubLanguage );
		m_lcid	= MAKELCID	( li,			// Language identifier
							  wSortID );	// Sorting identifier
	};

	// Get and Set methods
	FormatType Getft() const;
	void Setft( FormatType value );

	bool GetUseSeparator() const;
	void SetUseSeparator( bool value );
	
	int GetDecimalPlace() const;
	void SetDecimalPlace( int value );
	
	CString GetCurrency() const;
	void SetCurrency( CString value );
	
	CString GetCustomFormat() const;
	void SetCustomFormat( CString value );
	
	LCID Getlcid() const;
	void Setlcid( LCID value );

	// Serialization function required for MFC mecanism.
	virtual void Serialize ( CArchive& ar );

// Serialization debug features
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

private:

	FormatType	m_ft;
	bool		m_UseSeparator;
	int			m_DecimalPlace;
	CString		m_Currency;
	CString		m_CustomFormat;
	LCID		m_lcid;
};

inline ZBStringFormat::FormatType ZBStringFormat::Getft() const
{
	return m_ft;
}
inline void ZBStringFormat::Setft( ZBStringFormat::FormatType value )
{
	m_ft = value;
}

inline bool ZBStringFormat::GetUseSeparator() const
{
	return m_UseSeparator;
}

inline void ZBStringFormat::SetUseSeparator( bool value )
{
	m_UseSeparator = value;
}

inline int ZBStringFormat::GetDecimalPlace() const
{
	return m_DecimalPlace;
}

inline void ZBStringFormat::SetDecimalPlace( int value )
{
	m_DecimalPlace = value;
}

inline CString ZBStringFormat::GetCurrency() const
{
	return m_Currency;
}

inline void ZBStringFormat::SetCurrency( CString value )
{
	m_Currency = value;
}

inline CString ZBStringFormat::GetCustomFormat() const
{
	return m_CustomFormat;
}

inline void ZBStringFormat::SetCustomFormat( CString value )
{
	m_CustomFormat = value;
}

inline LCID ZBStringFormat::Getlcid() const
{
	return m_lcid;
}

inline void ZBStringFormat::Setlcid( LCID value )
{
	m_lcid = value;
}

#endif // !defined(AFX_ZBSTRINGFORMAT_H__9B99CE23_7F0D_4879_9BAE_365F1037FE64__INCLUDED_)