//	Advanced Dedicated Software
//	Dominique AIGROZ

// Source file: ZBCriptedFileInfo.cpp

#include "StdAfx.h"

// ZBCriptedFileInfo
#include "ZBCriptedFileInfo.h"

// ZFile
#include "File.h"

// Class ZBCriptedFileInfo 

ZBCriptedFileInfo::ZBCriptedFileInfo(size_t TableEntries /*= 40*/)
: m_TableEntries(TableEntries), m_bError(FALSE)
{
	AllocateEntityTable();
}

ZBCriptedFileInfo::ZBCriptedFileInfo(const CString sFileName, size_t TableEntries /*= 40*/)
  : m_sFilename(sFileName), m_TableEntries(TableEntries), m_bError(FALSE)
{
	AllocateEntityTable();
}


ZBCriptedFileInfo::~ZBCriptedFileInfo()
{
}

BOOL ZBCriptedFileInfo::AllocateEntityTable()
{
	if (m_EntityTable.GetSize() != 0 || m_TableEntries == 0)
		return FALSE;
	for (size_t i = 0; i < m_TableEntries; ++i )
		m_EntityTable.Add( ZBCriptedLine() );
	return m_EntityTable.GetSize() != 0;

}
BOOL ZBCriptedFileInfo::CreateEmptyFile(const CString sFileName)
{
	m_sFilename = sFileName;
	return ZBCriptedFileInfo::CreateEmpty();
}


BOOL ZBCriptedFileInfo::CreateEmpty()
{
	if (!EntityTableExist())
	{
		if (!AllocateEntityTable())
			return FALSE;
	}

	CString	text;
	// Create the first area
	for (size_t i = 0; i < m_TableEntries; ++i )
		m_EntityTable[i].GenerateRandomLine();

	WriteEntityTable();
  	return !GetErrorStatus();
}


BOOL ZBCriptedFileInfo::SetString(CString value, size_t Index)
{
	if (Index >= m_TableEntries)
	{
		SetErrorStatus( TRUE );
		return FALSE;
	}
	if (!EntityTableExist())
	{
		if (!AllocateEntityTable())
			return FALSE;
	}

	m_EntityTable[Index].GenerateLine( value );
	return TRUE;
}


BOOL ZBCriptedFileInfo::SetDate(CTime& Date, size_t Index)
{
	if (Index >= m_TableEntries)
	{
		SetErrorStatus( TRUE );
		return FALSE;
	}
	if (!EntityTableExist())
	{
		if (!AllocateEntityTable())
			return FALSE;
	}

	m_EntityTable[Index].GenerateLine( Date );
	return TRUE;
}

BOOL ZBCriptedFileInfo::SetDate(ZBDate& Date, size_t Index)
{
	if (Index >= m_TableEntries)
	{
		SetErrorStatus( TRUE );
		return FALSE;
	}
	if (!EntityTableExist())
	{
		if (!AllocateEntityTable())
			return FALSE;
	}

	m_EntityTable[Index].GenerateLine( Date );
	return TRUE;
}

BOOL ZBCriptedFileInfo::SetInt(int value, size_t Index)
{
	if (Index >= m_TableEntries)
	{
		SetErrorStatus( TRUE );
		return FALSE;
	}
	if (!EntityTableExist())
	{
		if (!AllocateEntityTable())
			return FALSE;
	}

	m_EntityTable[Index].GenerateLine( value );
	return TRUE;
}

CString ZBCriptedFileInfo::GetString( size_t Index )
{
	if (Index >= m_TableEntries)
	{
		SetErrorStatus( TRUE );
		return "";
	}

	return m_EntityTable[Index].GetString();

}
	  
CTime ZBCriptedFileInfo::GetCTime( size_t Index )
{
	if (Index >= m_TableEntries)
	{
		SetErrorStatus( TRUE );
		return 0;
	}

	return m_EntityTable[Index].GetCTime();
}

ZBDate ZBCriptedFileInfo::GetDate( size_t Index )
{
	if (Index >= m_TableEntries)
	{
		SetErrorStatus( TRUE );
		return ZBDate( (time_t)0 );
	}

	return m_EntityTable[Index].GetDate();
}
	  
int ZBCriptedFileInfo::GetInt( size_t Index )
{
	if (Index >= m_TableEntries)
	{
		SetErrorStatus( TRUE );
		return 0;
	}

	return m_EntityTable[Index].GetInt();
}


void ZBCriptedFileInfo::WriteEntityTable()
{
	if (!EntityTableExist())
	{
		SetErrorStatus( TRUE );
		return;
	}

	// JMR-MODIF - le 18 mai 2005
	// Remplaçement d'une constante apparemment obsolète dans la fonction m_FileStream.open : 
	// filebuf::sh_none devient _SH_DENYNO

	// Remove hidden file attribute before open
	// the file in write mode. Otherwise, open fails
    SetFileAttributes( (const char*)GetFilename(), GetFileAttributes((const char*)GetFilename()) & ~FILE_ATTRIBUTE_HIDDEN );
	m_FileStream.open( (const char*)GetFilename(), ios::trunc | ios::out, _SH_DENYNO );
	if (m_FileStream.rdstate() == ios::badbit || m_FileStream.rdstate() == ios::failbit)
  	{
  		SetErrorStatus( TRUE );
  		return;
  	}
	for (size_t i = 0; i < m_TableEntries; ++i )
    	m_FileStream << m_EntityTable[i].GetsEntity() << endl;
  	m_FileStream.close();

    // Set a default date to hide the file modifications
	if (!SetValidFileDate())
  	{
  		SetErrorStatus( TRUE );
  		return;
  	}
}


void ZBCriptedFileInfo::LoadEntityTable()
{
	if (!EntityTableExist())
	{
		if (!AllocateEntityTable())
		{
  			SetErrorStatus( TRUE );
  			return;
		}
	}

	ZFile	File(GetFilename());
	if (!File.Exist())
	{
    	// The filename does not exist
  		SetErrorStatus( TRUE );
  		return;
	}

	// JMR-MODIF - le 18 mai 2005
	// Remplaçement d'une constante apparemment obsolète dans la fonction m_FileStream.open : 
	// filebuf::sh_none devient _SH_DENYNO
	m_FileStream.open( (const char*)GetFilename(), ios::in, _SH_DENYNO );

  	if (m_FileStream.rdstate() == ios::badbit || m_FileStream.rdstate() == ios::failbit)
  	{
  		SetErrorStatus( TRUE );
  		return;
  	}
	for (size_t i = 0; i < m_TableEntries; ++i)
	{
		char	szTemp[1000];
		m_FileStream.getline( szTemp, sizeof( szTemp ) );
		m_EntityTable[i].SetsEntity( szTemp ); 
	}

  	m_FileStream.close();
    // Check if the default date is correct
	if (!IsFileDateValid())
	{
  		SetErrorStatus( TRUE );
  		return;
	}
}


BOOL ZBCriptedFileInfo::SetValidFileDate()
{
	HANDLE hFile = CreateFile(
		(const char*)GetFilename(),	// pointer to name of the file 
		GENERIC_WRITE,		// access (read-write) mode 
		FILE_SHARE_WRITE,	// share mode 
		NULL,	// pointer to security descriptor 
		OPEN_EXISTING,	// how to create 
		FILE_ATTRIBUTE_HIDDEN,	// file attributes 
		NULL 	// handle to file with attributes to copy  
		);
	if (hFile == INVALID_HANDLE_VALUE)
    {
  		return FALSE;
  	}
	FILETIME	FileTime;
	DosDateTimeToFileTime( 0x12c1, 0x5000, &FileTime );	// 10:00  6-1-89
    SetFileTime(	static_cast<HANDLE>( hFile ), 
					&FileTime,		// time the file was created
					&FileTime,		// time the file was last accessed
					&FileTime );	// time the file was last written
	CloseHandle( hFile );
    SetFileAttributes( (const char*)GetFilename(), FILE_ATTRIBUTE_HIDDEN );
	return TRUE;
}

BOOL ZBCriptedFileInfo::IsFileDateValid()
{
	HANDLE hFile = CreateFile(
		(const char*)GetFilename(),	// pointer to name of the file 
		GENERIC_READ,		// access (read-write) mode 
		FILE_SHARE_READ,	// share mode 
		NULL,	// pointer to security descriptor 
		OPEN_EXISTING,	// how to create 
		FILE_ATTRIBUTE_HIDDEN,	// file attributes 
		NULL 	// handle to file with attributes to copy  
		);
	if (hFile == INVALID_HANDLE_VALUE)
    {
    	// If not the user has changed manually the filename
  		return FALSE;
  	}
	FILETIME	FileTime, DummyTime;
	GetFileTime(hFile,			// identifies the file 
				&FileTime,		// address of creation time 
				&DummyTime,		// address of last access time  
				&DummyTime ); 	// address of last write time 
	CloseHandle( hFile );

    // Set a default date to hide the file modifications
	WORD	date;
	WORD	time;
	FileTimeToDosDateTime(	&FileTime,	// pointer to 64-bit file time 
							&date, // pointer to variable for MS-DOS date  
							&time );	 // pointer to variable for MS-DOS time  
    // Test if the filename has the same
    // date and time
    if (date != 0x12c1 && time != 0x5000)
    {
    	// If not the user has changed manually the filename
  		return FALSE;
  	}
	// The file date is valid
	return TRUE;
}