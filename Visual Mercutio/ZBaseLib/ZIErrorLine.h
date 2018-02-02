// ZIErrorLine.h: interface for the ZIErrorLine class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZIERRORLINE_H__2C224866_0F00_4FFF_8BC0_DFDCA073C4A5__INCLUDED_)
#define AFX_ZIERRORLINE_H__2C224866_0F00_4FFF_8BC0_DFDCA073C4A5__INCLUDED_

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

// JMR-MODIF - Le 11 octobre 2006 - Ajout des décorations unicode _T(), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZIErrorLine : public CString
{
public:

	ZIErrorLine( const CString	message		= _T( "" ),
				 int			line		= -1,
				 int			error		= -1,
				 int			type		= -1 );

	ZIErrorLine( UINT			nIDSmessage,
				 int			line		= -1,
				 int			error		= -1,
				 int			type		= -1 );

	virtual ~ZIErrorLine()
	{
		// Do nothing in the destructor
	};

	ZIErrorLine& operator=( const ZIErrorLine& src );

	/////////////////////////////////////////////////////////
	// standard member accessors
	virtual int GetLineNumber() const
	{
		return m_LineNumber;
	};

	virtual void SetLineNumber( int line )
	{
		m_LineNumber = line;
		BuildString();
	};

	virtual int GetErrorNumber() const
	{
		return m_ErrorNumber;
	};

	virtual void SetErrorNumber( int error )
	{
		m_ErrorNumber = error;
		BuildString();
	};

	virtual CString GetErrorMessage() const
	{
		return m_ErrorMessage;
	};

	virtual void SetErrorMessage( const CString& message )
	{
		m_ErrorMessage = message;
		BuildString();
	};

	virtual int GetErrorType() const
	{
		return m_ErrorType;
	};

	virtual void SetErrorType( int type )
	{
		m_ErrorType = type;
		BuildString();
	};

	/////////////////////////////////////////////////////////
	// Copy constructors, assignment operators

	// Copy constructor
	ZIErrorLine( const ZIErrorLine& genericErrorLineSrc )
		: CString( genericErrorLineSrc )
	{
		*this = genericErrorLineSrc;
	};

	// Copy constructor
	ZIErrorLine( const CString& stringSrc )
		: CString( stringSrc )
	{
		Parse();
	};

	// From a single character
	ZIErrorLine( TCHAR ch, int nRepeat = 1 )
		: CString( ch, nRepeat )
	{
		Parse();
	};

	// From an ANSI string (converts to TCHAR)
	ZIErrorLine( LPCSTR lpsz )
		: CString( lpsz )
	{
		Parse();
	};

	// From a UNICODE string (converts to TCHAR)
	ZIErrorLine( LPCWSTR lpsz )
		: CString( lpsz )
	{
		Parse();
	};

	// Subset of characters from an ANSI string (converts to TCHAR)
	ZIErrorLine( LPCSTR lpch, int nLength )
		: CString( lpch, nLength )
	{
		Parse();
	};

	// Subset of characters from a UNICODE string (converts to TCHAR)
	ZIErrorLine( LPCWSTR lpch, int nLength )
		: CString( lpch, nLength )
	{
		Parse();
	};

	// From unsigned characters
	ZIErrorLine( const unsigned char* psz )
		: CString( psz )
	{
		Parse();
	};

	///////////////////////////////////
	// Operators

	// Ref-counted copy from another CString
	const ZIErrorLine& operator=( const CString& stringSrc )
	{
		dynamic_cast<CString&>(*this) = CString::operator=( stringSrc );
		Parse();

		return *this;
	};

	// Set string content to single character
	const ZIErrorLine& operator=( TCHAR ch )
	{
		dynamic_cast<CString&>(*this) = CString::operator=( ch );
		Parse();

		return *this;
	};

#ifdef _UNICODE
	const ZIErrorLine& operator=( char ch )
	{
		dynamic_cast<CString&>(*this) = CString::operator=( ch );
		Parse();

		return *this;
	};
#endif

	// Copy string content from ANSI string (converts to TCHAR)
	const ZIErrorLine& operator=( LPCSTR lpsz )
	{
		dynamic_cast<CString&>(*this) = CString::operator=( lpsz );
		Parse();

		return *this;
	};

	// Copy string content from UNICODE string (converts to TCHAR)
	const ZIErrorLine& operator=( LPCWSTR lpsz )
	{
		dynamic_cast<CString&>(*this) = CString::operator=( lpsz );
		Parse();

		return *this;
	};

	// Copy string content from unsigned chars
	const ZIErrorLine& operator=( const unsigned char* psz )
	{
		dynamic_cast<CString&>(*this) = CString::operator=( psz );
		Parse();

		return *this;
	};

	////////////////////////
	// String concatenation

	// Concatenate from another CString
	const ZIErrorLine& operator+=( const CString& string )
	{
		dynamic_cast<CString&>(*this) = CString::operator=( string );
		Parse();

		return *this;
	};

	// Concatenate a single character
	const ZIErrorLine& operator+=( TCHAR ch )
	{
		dynamic_cast<CString&>(*this) = CString::operator=( ch );
		Parse();

		return *this;
	};

#ifdef _UNICODE
	// Concatenate an ANSI character after converting it to TCHAR
	const ZIErrorLine& operator+=( char ch )
	{
		dynamic_cast<CString&>(*this) = CString::operator=( ch );
		Parse();

		return *this;
	};
#endif

	// Concatenate a UNICODE character after converting it to TCHAR
	const ZIErrorLine& operator+=( LPCTSTR lpsz )
	{
		dynamic_cast<CString&>(*this) = CString::operator=( lpsz );
		Parse();

		return *this;
	};

protected:

	virtual void BuildString()
	{
		// Do nothing
	};

	virtual void Parse()
	{
		// Do nothing
	};

	// AssignString let assigning the string without parsing
	// it again. Typically used in BuildString function
	void AssignString( const CString str )
	{
		dynamic_cast<CString&>(*this) = CString::operator=( str );
	}

private:

	int		m_LineNumber;
	int		m_ErrorNumber;
	CString	m_ErrorMessage;
	int		m_ErrorType;
};

#endif // !defined(AFX_ZIERRORLINE_H__2C224866_0F00_4FFF_8BC0_DFDCA073C4A5__INCLUDED_)