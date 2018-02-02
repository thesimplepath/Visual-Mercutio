// ZBTokenizer.cpp: implementation of the ZBTokenizer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBTokenizer.h"

// JMR-MODIF - Le 10 février 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBTokenizer::ZBTokenizer( const char SeparatorChar )
	: m_SeparatorChar	( SeparatorChar ),
	  m_pCurrent		( NULL ),
	  m_pNext			( NULL )
{
}

ZBTokenizer::ZBTokenizer( const CString Line, const char SeparatorChar )
	: m_SeparatorChar	( SeparatorChar ),
	  m_pCurrent		( NULL ),
	  m_pNext			( NULL )
{
	InitializeString( Line );
}

ZBTokenizer::~ZBTokenizer()
{
	// JMR-MODIF - Le 25 août 2005 - Ajout du code de nettoyage de l'objet.
	m_Line.Empty();
}

CString ZBTokenizer::GetString()
{
	m_Line.ReleaseBuffer();

	return m_Line;
}

void ZBTokenizer::InitializeString( const CString Line )
{
	m_Line = Line;
}

CString ZBTokenizer::GetFirstToken( const CString Line )
{
	m_Line = Line;

	return _GetFirstToken();
}

CString ZBTokenizer::GetNextToken()
{
	if ( !m_pCurrent )
	{
		m_Line.ReleaseBuffer();
		return _T( "" );
	}

	// Locates the separator char 
	m_pNext = strchr( m_pCurrent,m_SeparatorChar );

	if ( !m_pNext )
	{
		// If still the last element into the buffer
		if ( !*m_pCurrent )
		{
			m_Line.ReleaseBuffer();
			return _T( "" );
		}

		// Copy the user
		CString	Token = m_pCurrent;

		// Sets current to NULL
		m_pCurrent = NULL;

		return Token;
	}

	// Where next is found, put end of string char.
	*m_pNext = 0x00;

	// Copy the user
	CString	Token = m_pCurrent;

	// Put back the separator char
	*m_pNext = m_SeparatorChar;

	// Sets current to the next char after the next pointer
	m_pCurrent = ++m_pNext;

	return Token;
}

BOOL ZBTokenizer::AddToken( const CString Token )
{
	if ( m_Line.IsEmpty() )
	{
		m_Line += Token;
	}
	else
	{
		m_Line += m_SeparatorChar;
		m_Line += Token;
	}

	return !m_Line.IsEmpty();
}

BOOL ZBTokenizer::AddToken( int iValue )
{
	CString Str;
	Str.Format( _T( "%d" ), iValue );

	return ZBTokenizer::AddToken( Str );
}

BOOL ZBTokenizer::AddToken( float fValue )
{
	CString Str;
	Str.Format( _T( "%f" ), fValue );

	return ZBTokenizer::AddToken( Str );
}

BOOL ZBTokenizer::AddToken( double dValue )
{
	CString Str;
	Str.Format( _T( "%f" ), dValue );

	return ZBTokenizer::AddToken( Str );
}

size_t ZBTokenizer::GetTokenCount()
{
	CString	str		= _GetFirstToken();
	size_t	Counter	= 0;

	// Run through all tokens
	while ( !str.IsEmpty() )
	{
		++Counter;

		// Get the next token
		str = GetNextToken();
	}

	// Release the buffer after a count
	m_Line.ReleaseBuffer();

	return Counter;
}

BOOL ZBTokenizer::GetTokenAt( size_t Index, CString& Value )
{
	CString	str		= _GetFirstToken();
	size_t	Counter	= 0;

	// Run through all tokens
	while ( !str.IsEmpty() )
	{
		// If we've reached the right index
		if ( Counter == Index )
		{
			// Copy the token to the value string
			Value = str;
			m_Line.ReleaseBuffer();

			// Returns ok
			return TRUE;
		}

		// Increment the counter
		++Counter;

		// Get the next token
		str = GetNextToken();
	}

	m_Line.ReleaseBuffer();

	// Return false for an invalid index
	return FALSE;
}

BOOL ZBTokenizer::TokenExist( const CString Token )
{
	CString str = _GetFirstToken();

	// Run through all tokens
	while ( !str.IsEmpty() )
	{
		// If we found the same deliverable,
		// then sets the Found flag to true
		if ( str == Token )
		{
			m_Line.ReleaseBuffer();
			return TRUE;
		}

		// Get the next token
		str = GetNextToken();
	}

	m_Line.ReleaseBuffer();

	return FALSE;
}

BOOL ZBTokenizer::TokenExist( int iValue )
{
	CString Str;
	Str.Format( _T( "%d" ), iValue );

	return ZBTokenizer::TokenExist( Str );
}

BOOL ZBTokenizer::TokenExist( float fValue )
{
	CString Str;
	Str.Format( _T( "%f" ), fValue );

	return ZBTokenizer::TokenExist( Str );
}

BOOL ZBTokenizer::TokenExist( double dValue )
{
	CString Str;
	Str.Format( _T( "%f" ), dValue );

	return ZBTokenizer::TokenExist( Str );
}

BOOL ZBTokenizer::AddUniqueToken( const CString Token )
{
	// If the token doesn't exists, add it
	if ( !TokenExist( Token ) )
	{
		AddToken( Token );
		return TRUE;
	}

	return FALSE;
}

BOOL ZBTokenizer::AddUniqueToken( int iValue )
{
	CString Str;
	Str.Format( _T( "%d" ), iValue );

	return ZBTokenizer::AddUniqueToken( Str );
}

BOOL ZBTokenizer::AddUniqueToken( float fValue )
{
	CString Str;
	Str.Format( _T( "%f" ), fValue );

	return ZBTokenizer::AddUniqueToken( Str );
}

BOOL ZBTokenizer::AddUniqueToken( double dValue )
{
	CString Str;
	Str.Format( _T( "%f" ), dValue );

	return ZBTokenizer::AddUniqueToken( Str );
}

BOOL ZBTokenizer::RemoveToken( const CString Token )
{
	BOOL Removed = FALSE;
	ZBTokenizer	finalTokens( m_Line, m_SeparatorChar );

	CString str = _GetFirstToken();

	// Run through all tokens
	while ( !str.IsEmpty() )
	{
		// If we found the same deliverable,
		// then sets the Found flag to true
		if ( str != Token )
		{
			finalTokens.AddToken( Token );
		}
		else
		{
			Removed = TRUE;
		}

		// Get the next token
		str = GetNextToken();
	}

	// Replace the token line only if the token has been removed
	if ( Removed )
	{
		m_Line = finalTokens.GetString();
	}
	else
	{
		// Just release the buffer
		m_Line.ReleaseBuffer();
	}

	return Removed;
}

BOOL ZBTokenizer::RemoveToken( int iValue )
{
	CString Str;
	Str.Format( _T( "%d" ), iValue );

	return ZBTokenizer::RemoveToken( Str );
}

BOOL ZBTokenizer::RemoveToken( float fValue )
{
	CString Str;
	Str.Format( _T( "%f" ), fValue );

	return ZBTokenizer::RemoveToken( Str );
}

BOOL ZBTokenizer::RemoveToken( double dValue )
{
	CString Str;
	Str.Format( _T( "%f" ), dValue );

	return ZBTokenizer::RemoveToken( Str );
}

void ZBTokenizer::FillArray( CStringArray& Array )
{
	CString s = _GetFirstToken();

	// Run through all tokens
	while ( !s.IsEmpty() )
	{
		Array.Add( s );

		// Get the next token
		s = GetNextToken();
	}
}

BOOL ZBTokenizer::ClearAllTokens()
{
	m_Line.Empty();
	return m_Line.IsEmpty();
}
