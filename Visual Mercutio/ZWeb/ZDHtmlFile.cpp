// ******************************************************************************************************
// *											   Classe ZDHtmlFile									*
// ******************************************************************************************************
// * Cette classe effectue les opération de base pour la manipulation de fichiers html.					*
// ******************************************************************************************************

#include "stdafx.h"
#include "ZDHtmlFile.h"

// JMR-MODIF - Le 26 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

// ******************************************************************************************************
// *										   Construction / destruction								*
// ******************************************************************************************************

ZDHtmlFile::ZDHtmlFile( CString Filename /*= ""*/ )
	: m_pCurrent( NULL ),
	  m_Filename( Filename )
{
}

ZDHtmlFile::~ZDHtmlFile()
{
}

// ******************************************************************************************************
// *										   Opérateurs de flux de données							*
// ******************************************************************************************************

ZDHtmlFile& ZDHtmlFile::operator<<( const char* cpChar )
{
	WriteLine( CString( cpChar ) );
	return *this;
}

ZDHtmlFile& ZDHtmlFile::operator<<( float value )
{
	CString s;
	s.Format( _T( "%f" ), value );
	WriteLine( s );

	return *this;
}

ZDHtmlFile& ZDHtmlFile::operator<<( double value )
{
	CString s;
	s.Format( _T( "%f" ), value );
	WriteLine( s );

	return *this;
}

ZDHtmlFile& ZDHtmlFile::operator<<( DWORD value )
{
	CString s;
	s.Format( _T( "%d" ), value );
	WriteLine( s );

	return *this;
}

ZDHtmlFile& ZDHtmlFile::operator<<( UINT value )
{
	CString s;
	s.Format( _T( "%d" ), value );
	WriteLine( s );

	return *this;
}

ZDHtmlFile& ZDHtmlFile::operator<<( WORD value )
{
	CString s;
	s.Format( _T( "%d" ), value );
	WriteLine( s );

	return *this;
}

ZDHtmlFile& ZDHtmlFile::operator<<( short value )
{
	CString s;
	s.Format( _T( "%d" ), value );
	WriteLine( s );

	return *this;
}

ZDHtmlFile& ZDHtmlFile::operator<<( LONG value )
{
	CString s;
	s.Format( _T( "%ld" ), value );
	WriteLine( s );

	return *this;
}

// ******************************************************************************************************
// *								  Fonctions publiques de la classe ZDHtmlFile						*
// ******************************************************************************************************

BOOL ZDHtmlFile::Create( CString Filename )
{
	m_Filename = Filename;
	return OpenFileCreate();
}

BOOL ZDHtmlFile::OpenFileCreate()
{
	TRY
	{
		// Construct a CFile object in read mode
		if ( !m_File.Open( m_Filename, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate ) )
		{
			return FALSE;
		}
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << _T( "File could not be opened " ) << e->m_cause << _T( "\n" );
		#endif

		return FALSE;
	}
	END_CATCH

	return TRUE;
}

BOOL ZDHtmlFile::OpenFileRead()
{
	TRY
	{
		// Construct a CFile object in read mode
		if ( !m_File.Open( m_Filename, CFile::modeRead | CFile::typeBinary ) )
		{
			return FALSE;
		}
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << _T( "File could not be opened " ) << e->m_cause << _T( "\n" );
		#endif

		return FALSE;
	}
	END_CATCH

	return TRUE;
}

BOOL ZDHtmlFile::CloseFile()
{
	TRY
	{
		m_File.Close();
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File could not be opened " << e->m_cause << "\n";
		#endif

		return FALSE;
	}
	END_CATCH

	return TRUE;
}

int ZDHtmlFile::ReadLine( CString& Line, bool RemoveNewLineChar /*= false*/ )
{
	// Nothing into the buffer
	if ( !m_pCurrent )
	{
		// Reads information from the file and
		// fills the buffer
		if ( ReadFileBuffer() <= 0 )
		{
			return 0;
		}
	}

	// The buffer is filled and we have a new occurence
	if ( m_pCurrent )
	{
		// if next return char found
		if ( ( m_pNext = strchr( m_pCurrent, '\n' ) ) )
		{
			// Used to save the previous char
			char chPreviousChar = 0;

			if ( RemoveNewLineChar )
			{
				// Where \n is found, put end of string char.
				*( m_pNext - 1 ) = 0x00;
			}
			else
			{
				chPreviousChar = *( m_pNext + 1 );
				*( m_pNext + 1 ) = 0x00;
			}

			// Copy the line to buffer
			Line = m_pCurrent;

			// Put back the char
			if ( !RemoveNewLineChar )
			{
				*( m_pNext + 1 ) = chPreviousChar;
			}

			// Sets current to the next char after the \n pointer
			m_pCurrent = m_pNext+1;
		}
		else
		{
			// It is necessary to read the next buffer
			// and to merge the previous buffer and the new one
			CString EndLine( m_pCurrent );

			// Reads information from the file and
			// fills the buffer
			if ( ReadFileBuffer() <= 0 )
			{
				return 0;
			}

			// Build the final line with the EndLine + the
			// beginning of the new buffer read
			
			// Locate the next return char
			if ( !( m_pNext = strchr( m_pCurrent, '\n' ) ) )
			{
				return 0;
			}

			// Where \n is found, put end of string char.
			if ( m_pNext != m_pCurrent )
			{
				// Used to save the previous char
				char chPreviousChar = 0;

				if ( RemoveNewLineChar )
				{
					*( m_pNext - 1 ) = 0x00;
				}
				else
				{
					*( m_pNext + 1 ) = 0x00;
				}

				// Copy the line to buffer
				Line = EndLine + m_pCurrent;
			}
			else
			{
				// Copy the line to buffer
				Line = EndLine.Left( EndLine.GetLength() - 1 );
			}

			// Sets current to the next char after the \n pointer
			m_pCurrent = m_pNext + 1;
		}
	}

	return Line.GetLength();
}

BOOL ZDHtmlFile::WriteLine( CString& Line, bool AddNewLineChar /*= false*/ )
{
	TRY
	{
		if ( AddNewLineChar )
		{
			Line += _T( "\r\n" );
		}

		m_File.Write( Line, Line.GetLength() );
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << _T( "Could not write to file" ) << e->m_cause << _T( "\n" );
		#endif

		return FALSE;
	}
	END_CATCH

	return TRUE;
}

// ******************************************************************************************************
// *								   Fonctions privées de la classe ZDHtmlFile						*
// ******************************************************************************************************

int ZDHtmlFile::ReadFileBuffer()
{
	int ReadChar;

	// Read info from the file
	ReadChar = m_File.Read( m_FileBuffer, sizeof( m_FileBuffer ) - 1 );

	// If char read
	if ( ReadChar )
	{
		// Sets current pointer
		m_pCurrent = m_FileBuffer;
	}

	// Sets end of line
	m_FileBuffer[ReadChar] = 0x00;

	// Returns the number of char read
	return ReadChar;
}
