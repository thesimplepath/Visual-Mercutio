// findfile.cpp : 
//

#include "stdafx.h"
#include "findfile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZUFindFile

int ZUFindFile::m_iLevel = 0;


ZUFindFile::ZUFindFile(CStringArray& FileArray)
: m_FoundedFile(FileArray)
{
}


int	ZUFindFile::CopyFoundFileArray(CStringArray& FileArray)
{
	FileArray.RemoveAll();
	for (int i = 0; i < m_FoundedFile.GetSize() ;++i)
		FileArray.Add( m_FoundedFile.GetAt( i ) );
	return FileArray.GetSize();
}


int ZUFindFile::FindFile(const CString&  sExeFilename, CString sDefaultDir)
{
	// Assign the filename to search	
	m_sFilenameToSearch = sExeFilename;

	// Find a good hard drive
	CString		sFile;
	unsigned 	uOldDrive;
   	
   	m_FoundedFile.RemoveAll();
	// Keep the current drive	
	uOldDrive = _getdrive();
//    TRACE1( "The current drive is: %c\n", 'A' + uOldDrive - 1 );
   	
   	// If in one specific directory
   	if (!sDefaultDir.IsEmpty())
   	{
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
    	_splitpath( sDefaultDir, drive, dir, fname, ext );
		// Change drive
	   	_chdrive( *drive - 'A' + 1 );
	
       	if (sDefaultDir.GetAt(sDefaultDir.GetLength() - 1)  == '\\')
       		sDefaultDir = sDefaultDir.Left(sDefaultDir.GetLength() - 1);
		if (chdir( sDefaultDir ) == 0)
			FindFileInCurrentDir();
    	
   	}
	else
	{
		char	DriveLetter[5];
		for( int iDrive=0 ; iDrive < 26 ; iDrive++ )
		{
			sprintf( DriveLetter, "%c:", 'A' + iDrive );
			if( GetDriveType( DriveLetter ) == DRIVE_FIXED )
				FindFileInDrive( sExeFilename, iDrive );
		}
	}
	// Restore the previous drive
  	_chdrive( uOldDrive );
	
	return m_FoundedFile.GetSize();
}

int  ZUFindFile::FindFileInDrive(const CString&  sFilename, int iDrive)
{
	// Initialize the buffer that will
	// contain the result
	m_sFoundedFilename = "";

	// JMR-MODIF - Le 18 mai 2005 - Conversion explicite d'un nombre en chaîne de caractères
	// exigée par la nouvelle classe CString.
	char* myBuffer = new char[18];
	CString sDrive = itoa(iDrive, myBuffer, 10);
	delete[] myBuffer;

	CString		sDir = sDrive + 'A';
	sDir += ":\\";

	// Change drive
   	_chdrive( iDrive+1 );
	if (chdir( sDir ) != 0)
		return 0;

	m_iLevel = 0;
	ProcessMainSubDir();
	return m_FoundedFile.GetSize();
}


int ZUFindFile::ProcessMainSubDir()
{
	++m_iLevel;
//	TRACE1( " IN %d\n", m_iLevel );
	// Check the level
	// to avoid stack overflow
	if (m_iLevel < 300 )
	{
		CStringArray 	DirArray;
		int				iSize = GetMainSubDir(DirArray);
		for (int i = 0; i < iSize ;++i)
		{
			FindFileInCurrentDir();
			if (chdir( DirArray[i] ) != 0 )
			{
		#ifdef _DEBUG
//			TRACE1( " ERROR NUMBER = %d  ", errno );
//			TRACE1( " UNABLE CHANGED DIR = %s\n", DirArray[i]);
		#endif
				continue;
			}
//			TRACE1( " CHANGED DIR = %s\n", DirArray[i]);
			ProcessMainSubDir();
		}
	}
	--m_iLevel;
//	TRACE1( " OUT %d\n", m_iLevel );
	return 0;
}



int ZUFindFile::GetMainSubDir(CStringArray& DirArray)
{
    // Now search for a subdirectory.  If a subdirectory is
    // found, change to it and call SearchDir recursively.
	if (_getcwd( m_FullPath.GetBufferSetLength(1024), 1024 ) == NULL)
	{
#ifdef _DEBUG
//	TRACE1( " ERROR NUMBER = %d\n", errno );
#endif
	    m_FullPath.ReleaseBuffer();
		return 0;
	}
    m_FullPath.ReleaseBuffer();
#ifdef _DEBUG
//	TRACE1( " VERIFIED PATH = %s\n", m_FullPath );
#endif
	
    DirArray.RemoveAll();
    struct _finddata_t	FileInfo;
	long				hFile;
    if ((hFile=_findfirst ("*.*", &FileInfo)) != -1L) 
    {
    	do
    	{
			MSG	msg;
			if (PeekMessage(&msg, (HWND) NULL, 0, 0, PM_REMOVE)) 
			{ 
			    TranslateMessage(&msg);         
			    DispatchMessage(&msg);     
			}
	        if ((FileInfo.attrib & 0x10) != 0x00)
	            if ((strcmp (FileInfo.name, ".") != 0) &&
	            	(strcmp (FileInfo.name, "..") != 0)) 
	            {
	            	// Do the full path function
	            	if (m_FullPath.GetAt(m_FullPath.GetLength() - 1)  == '\\')
						m_sFoundedFilename = m_FullPath + FileInfo.name;
	            	else
						m_sFoundedFilename = m_FullPath + "\\" + FileInfo.name;
//			        VERIFY( _fullpath( m_FullPath.GetBufferSetLength(1024), FileInfo.name, 1024) != NULL );
//			        m_FullPath.ReleaseBuffer();
			        DirArray.Add( m_sFoundedFilename );
	            }
		}
        while (!_findnext (hFile, &FileInfo));
    }
    return DirArray.GetSize();
}



void ZUFindFile::FindFileInCurrentDir()
{
     // Find the first file in the current directory.
    struct _finddata_t FileInfo;
	long			   hFile;

    if ((hFile=_findfirst (m_sFilenameToSearch, &FileInfo)) != -1L) 
    {
        _fullpath (m_sFoundedFilename.GetBufferSetLength(128), FileInfo.name, 128);
        m_sFoundedFilename.ReleaseBuffer();
        m_FoundedFile.Add( m_sFoundedFilename );

		// Search for additional files         
        while (!_findnext (hFile, &FileInfo))
        {
            if (!(FileInfo.attrib & _A_SUBDIR))
			{
                if ((strcmp (FileInfo.name, ".") != 0) &&
                	(strcmp (FileInfo.name, "..") != 0)) 
                {
			        _fullpath (m_sFoundedFilename.GetBufferSetLength(128), FileInfo.name, 128);
			        m_sFoundedFilename.ReleaseBuffer();
			        m_FoundedFile.Add( m_sFoundedFilename );
                }
			}
        }
    }
}











BOOL ZUFindFile::FirstSubDir(struct _finddata_t* pFileInfo)
{
    // Now search for a subdirectory.  If a subdirectory is
    // found, change to it and call SearchDir recursively.
	long			   hFile;
 
    if ((hFile=_findfirst ("*.*", pFileInfo)) != -1L) 
    {
    	do
    	{
	        if ((pFileInfo->attrib & 0x10) != 0x00)
	            if ((strcmp (pFileInfo->name, ".") != 0) &&
	            	(strcmp (pFileInfo->name, "..") != 0)) 
	            {
			        _fullpath (m_sFoundedFilename.GetBufferSetLength(512), pFileInfo->name, 512);
			        m_sFoundedFilename.ReleaseBuffer();
	                VERIFY( chdir (pFileInfo->name) == 0 );
	                return TRUE;
	            }
		}
        while (!_findnext (hFile, pFileInfo));
    }
    return FALSE;
}


BOOL ZUFindFile::NextSubDir(long hFile, struct _finddata_t* pFileInfo)
{
    if (!_findnext (hFile, pFileInfo))
    {
    	do
    	{
	        if ((pFileInfo->attrib & 0x10) != 0x00)
	            if ((strcmp (pFileInfo->name, ".") != 0) &&
	            	(strcmp (pFileInfo->name, "..") != 0)) 
	            {
			        _fullpath (m_sFoundedFilename.GetBufferSetLength(128), pFileInfo->name, 128);
			        m_sFoundedFilename.ReleaseBuffer();
	                VERIFY( chdir (pFileInfo->name) == 0 );
	                return TRUE;
	            }
		}
        while (!_findnext (hFile, pFileInfo));
    }
    return FALSE;
}

BOOL ZUFindFile::FindFileInSubDir()
{
    // Now search for a subdirectory.  If a subdirectory is
    // found, change to it and call SearchDir recursively.
 
    struct _finddata_t m_FileInfo;
	long			   hFile;

    if ((hFile=_findfirst ("*.*", &m_FileInfo)) != -1L) 
    {
        if ((m_FileInfo.attrib & 0x10) != 0x00)
            if ((strcmp (m_FileInfo.name, ".") != 0) &&
            	(strcmp (m_FileInfo.name, "..") != 0)) 
            {
            	TRY
            	{
	                chdir (m_FileInfo.name);
	                FindFileInCurrentDir ();
	                chdir ("..");
	            }
	            CATCH( CMemoryException, e )
	            {
	            	return FALSE;
	            }
	            END_CATCH
            }
 
	    // Search for additional subdirectories.
 
        while (!_findnext (hFile, &m_FileInfo))
            if ((m_FileInfo.attrib & 0x10) != 0x00)
                if ((strcmp (m_FileInfo.name, ".") != 0) &&
                	(strcmp (m_FileInfo.name, "..") != 0)) 
                {
	            	TRY
	            	{
	                    chdir (m_FileInfo.name);
	                    FindFileInCurrentDir ();
	                    chdir ("..");
		            }
		            CATCH( CMemoryException, e )
		            {
		            	return FALSE;
		            }
		            END_CATCH
                }
    }
    return FALSE;
}



