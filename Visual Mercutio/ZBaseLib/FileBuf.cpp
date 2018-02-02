//## begin module%37F6428900F8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%37F6428900F8.cm

//## begin module%37F6428900F8.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%37F6428900F8.cp

//## Module: FileBuf%37F6428900F8; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FileBuf.cpp

//## begin module%37F6428900F8.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%37F6428900F8.additionalIncludes

//## begin module%37F6428900F8.includes preserve=yes
//## end module%37F6428900F8.includes

// FileBuf
#include "FileBuf.h"

//## begin module%37F6428900F8.declarations preserve=no
//## end module%37F6428900F8.declarations

//## begin module%37F6428900F8.additionalDeclarations preserve=yes
// FileMg
#include "FileMg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 24 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZBFileBuffer, CObject, def_Version )
//## end module%37F6428900F8.additionalDeclarations

ZBFileBuffer::ZBFileBuffer( const ZBFileBuffer &right )
	//## begin ZBFileBuffer::ZBFileBuffer%copy.hasinit preserve=no
	//## end ZBFileBuffer::ZBFileBuffer%copy.hasinit
	//## begin ZBFileBuffer::ZBFileBuffer%copy.initialization preserve=yes
	//## end ZBFileBuffer::ZBFileBuffer%copy.initialization
{
	//## begin ZBFileBuffer::ZBFileBuffer%copy.body preserve=yes
	*this = right;
	//## end ZBFileBuffer::ZBFileBuffer%copy.body
}

ZBFileBuffer::ZBFileBuffer ( const CString Filename )
	//## begin ZBFileBuffer::ZBFileBuffer%938884129.hasinit preserve=no
	//## end ZBFileBuffer::ZBFileBuffer%938884129.hasinit
	//## begin ZBFileBuffer::ZBFileBuffer%938884129.initialization preserve=yes
	: m_FileBuffer( NULL ),
	  m_BufferSize( 0 )
	//## end ZBFileBuffer::ZBFileBuffer%938884129.initialization
{
	//## begin ZBFileBuffer::ZBFileBuffer%938884129.body preserve=yes
	if ( !Filename.IsEmpty() )
	{
		CreateBufferFromFile( Filename );
	}
	//## end ZBFileBuffer::ZBFileBuffer%938884129.body
}

ZBFileBuffer::ZBFileBuffer ( ZFile& File )
	//## begin ZBFileBuffer::ZBFileBuffer%938884130.hasinit preserve=no
	//## end ZBFileBuffer::ZBFileBuffer%938884130.hasinit
	//## begin ZBFileBuffer::ZBFileBuffer%938884130.initialization preserve=yes
	: m_FileBuffer( NULL ),
	  m_BufferSize( 0 )
	//## end ZBFileBuffer::ZBFileBuffer%938884130.initialization
{
	//## begin ZBFileBuffer::ZBFileBuffer%938884130.body preserve=yes
	CreateBufferFromFile( File );
	//## end ZBFileBuffer::ZBFileBuffer%938884130.body
}

ZBFileBuffer::~ZBFileBuffer()
{
	//## begin ZBFileBuffer::~ZBFileBuffer%.body preserve=yes
	Clear();
	//## end ZBFileBuffer::~ZBFileBuffer%.body
}

const ZBFileBuffer & ZBFileBuffer::operator=( const ZBFileBuffer &right )
{
	//## begin ZBFileBuffer::operator=%.body preserve=yes
	m_File			= right.m_File;
	m_BufferSize	= right.m_BufferSize;

	if ( m_FileBuffer )
	{
		m_FileBuffer = malloc( right.GetBufferSize() );

		if ( m_FileBuffer != 0 )
		{
			memcpy( m_FileBuffer, ( (ZBFileBuffer&)right ).GetFileBuffer(), right.GetBufferSize() );
		}
	}

	return *this;
	//## end ZBFileBuffer::operator=%.body
}

//## Other Operations (implementation)
BOOL ZBFileBuffer::CreateBufferFromFile ( const CString Filename )
{
	//## begin ZBFileBuffer::CreateBufferFromFile%938884131.body preserve=yes
	return CreateBufferFromFile( ZFile( Filename ) );
	//## end ZBFileBuffer::CreateBufferFromFile%938884131.body
}

BOOL ZBFileBuffer::CreateBufferFromFile ( ZFile& File )
{
	//## begin ZBFileBuffer::CreateBufferFromFile%938884132.body preserve=yes
	m_File = File;
	return CreateBufferFromFile();
	//## end ZBFileBuffer::CreateBufferFromFile%938884132.body
}

BOOL ZBFileBuffer::CreateBufferFromFile ()
{
	//## begin ZBFileBuffer::CreateBufferFromFile%938933073.body preserve=yes
	// check if the file exists
	if ( !m_File.Exist() )
	{
		return FALSE;
	}

	// Firs, rebuild all data members
	m_File.ReBuild();
	CFile File;

	TRY
	{
		// Construct a CFile object in read mode
		if ( !File.Open( m_File.GetCompleteFileName(), CFile::modeRead | CFile::typeBinary ) )
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
	{
		// File is now open.
		CFileStatus rStatus;

		if ( !File.GetStatus( rStatus ) )
		{
			return FALSE;
		}

		// Allocate a new buffer with the file size
		m_FileBuffer = malloc( (size_t)rStatus.m_size + 1 );

		if ( m_FileBuffer == 0 )
		{
			return FALSE;
		}

		// Clear the buffer
		memset( m_FileBuffer, 0, (size_t)rStatus.m_size + 1 );
		m_BufferSize = (size_t)rStatus.m_size + 1;

		// Read char from the file
		UINT ReadChar;

		// Read info from the file
		ReadChar = File.Read( m_FileBuffer, (UINT)rStatus.m_size);

		// Check the number of char read from file
		if ( ReadChar != rStatus.m_size )
		{
			Clear();
			return FALSE;
		}
		// Otherwise, everthing ok.
		// Close the file
	}

	TRY
	{
		File.Close();
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
		afxDump << _T( "File could not be opened " ) << e->m_cause << _T( "\n" );
		#endif
	}
	END_CATCH
	{
		return TRUE;
	}

	//## end ZBFileBuffer::CreateBufferFromFile%938933073.body
}

CString ZBFileBuffer::CreateFileFromBuffer ()
{
	//## begin ZBFileBuffer::CreateFileFromBuffer%938884133.body preserve=yes
	return CreateFileFromBuffer( m_File );
	//## end ZBFileBuffer::CreateFileFromBuffer%938884133.body
}

CString ZBFileBuffer::CreateFileFromBuffer ( const CString Filename )
{
	//## begin ZBFileBuffer::CreateFileFromBuffer%938933074.body preserve=yes
	CFile File;

	TRY
	{
		// Construct a CFile object in read mode
		if ( !File.Open( Filename, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate ) )
		{
			return _T( "" );
		}
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
		afxDump << _T( "File could not be opened " ) << e->m_cause << _T( "\n" );
		#endif

		return _T( "" );
	}
	END_CATCH

	TRY
	{
		// Write the buffer to the file
		File.Write( m_FileBuffer, m_BufferSize - 1 );
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
		afxDump << _T( "File could not be opened " ) << e->m_cause << _T( "\n" );
		#endif

		File.Close();
		return _T( "" );
	}
	END_CATCH
	{
		// Otherwise, everthing ok.
		// Close the file
	}

	TRY
	{
		File.Close();
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
		afxDump << _T( "File could not be opened " ) << e->m_cause << _T( "\n" );
		#endif
	}
	END_CATCH

	return Filename;
	//## end ZBFileBuffer::CreateFileFromBuffer%938933074.body
}

CString ZBFileBuffer::CreateFileFromBuffer ( ZFile& File )
{
	//## begin ZBFileBuffer::CreateFileFromBuffer%938933075.body preserve=yes
	return CreateFileFromBuffer( File.GetCompleteFileName() );
	//## end ZBFileBuffer::CreateFileFromBuffer%938933075.body
}

CString ZBFileBuffer::CreateTemporaryFileFromBuffer ()
{
	//## begin ZBFileBuffer::CreateTemporaryFileFromBuffer%938959772.body preserve=yes
	ZFileManager FileManager;
	return CreateFileFromBuffer( FileManager.GetTemporaryFileName ( FileManager.GetTemporaryPath(),
																	_T( "" ),
																	m_File.GetFileExt() ) );
	//## end ZBFileBuffer::CreateTemporaryFileFromBuffer%938959772.body
}

CArchive& operator >> ( CArchive& ar, ZBFileBuffer& FileBuffer )
{
	//## begin ZBFileBuffer::operator >>%938884134.body preserve=yes
	ar >> FileBuffer.m_File;
	ar >> FileBuffer.m_BufferSize;

	// If we have serialized binary information
	if ( FileBuffer.m_BufferSize > 0 )
	{
		FileBuffer.m_FileBuffer = malloc( FileBuffer.m_BufferSize );

		if ( FileBuffer.m_FileBuffer != 0 )
		{
			// Clear the buffer
			memset( FileBuffer.m_FileBuffer, 0, FileBuffer.m_BufferSize );

			// Read binary information
			ar.Read( FileBuffer.m_FileBuffer, FileBuffer.m_BufferSize );
		}
	}
	else
	{
		FileBuffer.m_FileBuffer = NULL;
	}

	return ar;
	//## end ZBFileBuffer::operator >>%938884134.body
}

CArchive& operator << ( CArchive& ar, ZBFileBuffer& FileBuffer )
{
	//## begin ZBFileBuffer::operator <<%938884135.body preserve=yes
	ar << FileBuffer.m_File;
	ar << FileBuffer.m_BufferSize;

	// If we need to serialize binary information
	if ( FileBuffer.m_BufferSize > 0 )
	{
		// Write binary information
		ar.Write( FileBuffer.m_FileBuffer, FileBuffer.m_BufferSize );
	}

	return ar;
	//## end ZBFileBuffer::operator <<%938884135.body
}

void ZBFileBuffer::Serialize ( CArchive& ar )
{
	//## begin ZBFileBuffer::Serialize%938884136.body preserve=yes
	if ( ar.IsStoring() )
	{
		// Write the elements
		ar << *this;
	}
	else
	{
		ar >> *this;
	}
	//## end ZBFileBuffer::Serialize%938884136.body
}

void ZBFileBuffer::Clear ()
{
	//## begin ZBFileBuffer::Clear%938884137.body preserve=yes
	if ( m_FileBuffer )
	{
		delete m_FileBuffer;
		m_FileBuffer = NULL;
		m_BufferSize = 0;
	}
	//## end ZBFileBuffer::Clear%938884137.body
}

ZBFileBuffer* ZBFileBuffer::Clone ()
{
	//## begin ZBFileBuffer::Clone%938884138.body preserve=yes
	ZBFileBuffer* pFileBuffer = new ZBFileBuffer( *this );
	return pFileBuffer;
	//## end ZBFileBuffer::Clone%938884138.body
}

// Additional Declarations
//## begin ZBFileBuffer%37F63DEC0032.declarations preserve=yes
//## end ZBFileBuffer%37F63DEC0032.declarations

//## begin module%37F6428900F8.epilog preserve=yes
//## end module%37F6428900F8.epilog