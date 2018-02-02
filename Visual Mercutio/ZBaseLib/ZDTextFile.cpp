// ******************************************************************************************************
// *										   Classe ZDTextFile										*
// ******************************************************************************************************
// * JMR-MODIF - Le 27 juin 2007 - Ajout de la classe ZDTextFile.										*
// ******************************************************************************************************
// * Cette classe effectue les opération de base pour la manipulation de fichiers textes.				*
// ******************************************************************************************************

#include "stdafx.h"
#include "ZDTextFile.h"

// ******************************************************************************************************
// *										   Construction / destruction								*
// ******************************************************************************************************

ZDTextFile::ZDTextFile( CString Filename /*= ""*/ )
	: m_pCurrent( NULL ),
	  m_Filename( Filename )
{
}

ZDTextFile::~ZDTextFile()
{
}

// ******************************************************************************************************
// *										   Opérateurs de flux de données							*
// ******************************************************************************************************

ZDTextFile& ZDTextFile::operator<<( const char* cpChar )
{
	WriteLine( CString( cpChar ) );
	return *this;
}

ZDTextFile& ZDTextFile::operator<<( float value )
{
	CString s;
	s.Format( _T( "%f" ), value );
	WriteLine( s );

	return *this;
}

ZDTextFile& ZDTextFile::operator<<( double value )
{
	CString s;
	s.Format( _T( "%f" ), value );
	WriteLine( s );

	return *this;
}

ZDTextFile& ZDTextFile::operator<<( DWORD value )
{
	CString s;
	s.Format( _T( "%d" ), value );
	WriteLine( s );

	return *this;
}

ZDTextFile& ZDTextFile::operator<<( UINT value )
{
	CString s;
	s.Format( _T( "%d" ), value );
	WriteLine( s );

	return *this;
}

ZDTextFile& ZDTextFile::operator<<( WORD value )
{
	CString s;
	s.Format( _T( "%d" ), value );
	WriteLine( s );

	return *this;
}

ZDTextFile& ZDTextFile::operator<<( short value )
{
	CString s;
	s.Format( _T( "%d" ), value );
	WriteLine( s );

	return *this;
}

ZDTextFile& ZDTextFile::operator<<( LONG value )
{
	CString s;
	s.Format( _T( "%ld" ), value );
	WriteLine( s );

	return *this;
}

ZDTextFile& ZDTextFile::operator>>( CString& value )
{
	if ( ReadLine( value ) == 0 )
	{
		value = _T( "" );
	}

	int m_Index = value.Find( _T( "\n" ) );

	if ( m_Index > 0 )
	{
		CString m_Copy = _T( "" );

		for ( int i = 0; i < value.GetLength() - 2; i++ )
		{
			m_Copy += value.GetAt( i );
		}

		value = m_Copy;
	}

	return *this;
}

// ******************************************************************************************************
// *								  Fonctions publiques de la classe ZDTextFile						*
// ******************************************************************************************************

// Ouvre le fichier en écriture.
BOOL ZDTextFile::OpenWrite( CString Filename )
{
	m_Filename = Filename;
	return OpenFileWrite();
}

// Ouvre le fichier en lecture.
BOOL ZDTextFile::OpenRead( CString Filename )
{
	m_Filename = Filename;
	return OpenFileRead();
}

// Crée et ouvre le fichier en écriture. Crée le fichier si celui-ci n'existe pas.
BOOL ZDTextFile::OpenFileWrite()
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

// Ouvre le fichier en lecture.
BOOL ZDTextFile::OpenFileRead()
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

BOOL ZDTextFile::CloseFile()
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

int ZDTextFile::ReadLine( CString& Line, bool RemoveNewLineChar /*= false*/ )
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

BOOL ZDTextFile::WriteLine( CString& Line, bool AddNewLineChar /*= false*/ )
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
// *								   Fonctions privées de la classe ZDTextFile						*
// ******************************************************************************************************

int ZDTextFile::ReadFileBuffer()
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
