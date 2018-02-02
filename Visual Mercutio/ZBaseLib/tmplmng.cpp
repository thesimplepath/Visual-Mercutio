//## begin module%345A3C2E0244.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%345A3C2E0244.cm

//## begin module%345A3C2E0244.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%345A3C2E0244.cp

//## Module: TmplMng%345A3C2E0244; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\TmplMng.cpp

//## begin module%345A3C2E0244.additionalIncludes preserve=no
//## end module%345A3C2E0244.additionalIncludes

//## begin module%345A3C2E0244.includes preserve=yes
#include <StdAfx.h>
//## end module%345A3C2E0244.includes

// TmplMng
#include "TmplMng.h"
//## begin module%345A3C2E0244.declarations preserve=no
//## end module%345A3C2E0244.declarations

//## begin module%345A3C2E0244.additionalDeclarations preserve=yes
#ifndef _WIN32
	#include <ver.h>
#else
	#include <WinVer.h>
#endif

#include <direct.h> 
#include <dos.h>
//## end module%345A3C2E0244.additionalDeclarations


// Class ZDTemplateManager 




ZDTemplateManager::ZDTemplateManager()
  //## begin ZDTemplateManager::ZDTemplateManager%.hasinit preserve=no
  //## end ZDTemplateManager::ZDTemplateManager%.hasinit
  //## begin ZDTemplateManager::ZDTemplateManager%.initialization preserve=yes
  //## end ZDTemplateManager::ZDTemplateManager%.initialization
{
  //## begin ZDTemplateManager::ZDTemplateManager%.body preserve=yes
  //## end ZDTemplateManager::ZDTemplateManager%.body
}

ZDTemplateManager::ZDTemplateManager (CString RootDirectory, CString FileExtension)
  //## begin ZDTemplateManager::ZDTemplateManager%878377701.hasinit preserve=no
  //## end ZDTemplateManager::ZDTemplateManager%878377701.hasinit
  //## begin ZDTemplateManager::ZDTemplateManager%878377701.initialization preserve=yes
  //## end ZDTemplateManager::ZDTemplateManager%878377701.initialization
{
  //## begin ZDTemplateManager::ZDTemplateManager%878377701.body preserve=yes
  	Create( RootDirectory, FileExtension );
  //## end ZDTemplateManager::ZDTemplateManager%878377701.body
}


ZDTemplateManager::~ZDTemplateManager()
{
  //## begin ZDTemplateManager::~ZDTemplateManager%.body preserve=yes
	FreeList();
  //## end ZDTemplateManager::~ZDTemplateManager%.body
}



//## Other Operations (implementation)
BOOL ZDTemplateManager::Create (CString RootDirectory, CString FileExtension)
{
  //## begin ZDTemplateManager::Create%878329367.body preserve=yes
  	// Assigns the root directory.
  	m_RootDirectory = RootDirectory;
  	// Assign the extension type
  	m_FileExtension = FileExtension;
  	return Scan();
  //## end ZDTemplateManager::Create%878329367.body
}

BOOL ZDTemplateManager::Scan ()
{
  //## begin ZDTemplateManager::Scan%878329368.body preserve=yes
	// Fist free the template dir list
  	m_TemplateDirList.RemoveAll();
  	// First, free the list
	FreeList();

#ifndef _WIN32
	// Scan the root directory. and its sub-directories
	char 		drive[_MAX_DRIVE];
	char 		dir[_MAX_DIR];
	char 		fname[_MAX_FNAME];
	char 		ext[_MAX_EXT];
	unsigned 	uOldDrive;
   	unsigned 	uNumberOfDrives;
	
	// Keep the current drive	
	_dos_getdrive( &uOldDrive );

	// Search files from the current directory.	
	_splitpath( m_RootDirectory, drive, dir, fname, ext );
  	_dos_setdrive( ((unsigned)*drive) - 'A' + 1, &uNumberOfDrives );
	chdir( m_RootDirectory );
#else
	char	szCurrentDir[300];
	GetCurrentDirectory( sizeof( szCurrentDir ), szCurrentDir );
	SetCurrentDirectory( m_RootDirectory );
#endif

	// Create a page for the root directory
	CString	sRootTitle( GetRootCaption() );
	// Add the title to the template dir list
	m_TemplateDirList.Add( sRootTitle );
	// Add the TemplateDir
    ZDTemplateDir*	pDir = new ZDTemplateDir( m_RootDirectory, sRootTitle, m_FileExtension );
  	m_TemplateList.Add( pDir );

#ifndef _WIN32
    struct find_t FileInfo;
    // Now search for subdirectories.
    if (!_dos_findfirst ("*.*", _A_SUBDIR, &FileInfo)) 
    {
    	do
    	{
	        if ((FileInfo.attrib & 0x10) != 0x00)
	            if ((strcmp (FileInfo.name, ".") != 0) &&
	            	(strcmp (FileInfo.name, "..") != 0)) 
	            {
					// Add the title to the template dir list
					m_TemplateDirList.Add( FileInfo.name );
					// Add the TemplateDir
	                ZDTemplateDir*	pDir = new ZDTemplateDir( m_RootDirectory + "\\" + FileInfo.name, FileInfo.name, m_FileExtension );
				  	m_TemplateList.Add( pDir );
	            }
		} 
	    // Search for additional subdirectories.
        while (!_dos_findnext (&FileInfo));
    }

	// Restore the previous drive
  	_dos_setdrive( uOldDrive, &uNumberOfDrives );
#else
	WIN32_FIND_DATA		FileInfo;
	HANDLE				hFile;
    // Now search for subdirectories.
    if ((hFile=FindFirstFile( "*.*", &FileInfo )) != INVALID_HANDLE_VALUE) 
    {
    	do
    	{
			if (FileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
	            if ((strcmp (FileInfo.cFileName, ".") != 0) &&
	            	(strcmp (FileInfo.cFileName, "..") != 0)) 
	            {
					// Add the title to the template dir list
					m_TemplateDirList.Add( FileInfo.cFileName );
					// Add the TemplateDir
	                ZDTemplateDir*	pDir = new ZDTemplateDir( m_RootDirectory + "\\" + FileInfo.cFileName, FileInfo.cFileName, m_FileExtension );
				  	m_TemplateList.Add( pDir );
	            }
			}
		} 
	    // Search for additional files.
        while (FindNextFile (hFile, &FileInfo) != 0);
    }
	// Restore initial directory
	SetCurrentDirectory( szCurrentDir );
#endif

	return m_TemplateList.GetSize() > 0;
  //## end ZDTemplateManager::Scan%878329368.body
}

void ZDTemplateManager::FreeList ()
{
  //## begin ZDTemplateManager::FreeList%878377702.body preserve=yes
	// Free all file objects allocated 
  	for (int i = 0; i < m_TemplateList.GetSize(); ++i)
  		delete ((ZDTemplateDir*)(m_TemplateList[i]));
  	m_TemplateList.RemoveAll();
  //## end ZDTemplateManager::FreeList%878377702.body
}

ZDTemplateDir* ZDTemplateManager::FindTemplateDir (CString TemplateDir)
{
  //## begin ZDTemplateManager::FindTemplateDir%878492724.body preserve=yes
	// Run through the list and find the right templatedir
  	for (int i = 0; i < m_TemplateList.GetSize(); ++i)
  		if (((ZDTemplateDir*)(m_TemplateList[i]))->GetTitle().CompareNoCase(TemplateDir) == 0)
  			return ((ZDTemplateDir*)(m_TemplateList[i]));
  	return NULL;
  //## end ZDTemplateManager::FindTemplateDir%878492724.body
}

ZDTemplateFile* ZDTemplateManager::FindTemplate (CString TemplateName)
{
  //## begin ZDTemplateManager::FindTemplate%915657290.body preserve=yes
	// Run through the list and find the right template name
	ZDTemplateFile*	pTmplFile;
  	for (int i = 0; i < m_TemplateList.GetSize(); ++i)
  		if ((pTmplFile=((ZDTemplateDir*)(m_TemplateList[i]))->FindTitle( TemplateName )) != NULL)
  			return pTmplFile;
  	return NULL;
  //## end ZDTemplateManager::FindTemplate%915657290.body
}

CString ZDTemplateManager::GetRootCaption ()
{
  //## begin ZDTemplateManager::GetRootCaption%902335798.body preserve=yes
	CString		sRootTitle;
	sRootTitle.LoadString( IDS_ROOTTEMPLATETITLE );
	return sRootTitle;
  //## end ZDTemplateManager::GetRootCaption%902335798.body
}

BOOL ZDTemplateManager::MoveTemplateFile (CString Filename, CString SourceTemplateDir, CString DestinationTemplateDir)
{
  //## begin ZDTemplateManager::MoveTemplateFile%902335799.body preserve=yes
  	// Search the source template
	ZDTemplateDir* pSource = FindTemplateDir( SourceTemplateDir );
	if (!pSource)
		return FALSE;
  	// Search the file in the source template
    ZDTemplateFile* pFile = pSource->FindFile( Filename );
	if (!pFile)
		return FALSE;
  	// Search the destination template
	ZDTemplateDir* pDestination = FindTemplateDir( DestinationTemplateDir );
	if (!pDestination)
		return FALSE;
	// Call the basic fonction
	return MoveTemplateFile( *pFile, *pSource, *pDestination );
  //## end ZDTemplateManager::MoveTemplateFile%902335799.body
}

BOOL ZDTemplateManager::MoveTemplateFile (ZDTemplateFile& Filename, ZDTemplateDir& SourceTemplateDir, ZDTemplateDir& DestinationTemplateDir)
{
  //## begin ZDTemplateManager::MoveTemplateFile%902335800.body preserve=yes
	CString		sTemp;

	// Extract the filename
	CString		File;
	char 		drive[_MAX_DRIVE];
	char 		dir[_MAX_DIR];
	char 		fname[_MAX_FNAME];
	char 		ext[_MAX_EXT];
	_splitpath( (const char*)Filename.GetFilename(), drive, dir, fname, ext );
	File = fname;
	File += ext;

	DWORD	dwRet;
	// Buffer is in an array
	// for further use with VerFindFile
	char		szTemp[_MAX_PATH];
	char		szPreviousVer[_MAX_PATH];
	UINT		wPreviousVerLen=sizeof( szPreviousVer );
	UINT		wLen=sizeof( szTemp );

#ifndef _WIN32
	VerFindFile(VFFF_ISSHAREDFILE,
				(const char*)File,
				(const char*)SourceTemplateDir.GetDirectory(),
				(const char*)SourceTemplateDir.GetDirectory(),
				szTemp,
				&wLen,
				szPreviousVer,
				&wPreviousVerLen );
#else
		VerFindFile(VFFF_ISSHAREDFILE,
					const_cast<char*>( static_cast<const char*>( File ) ),
					const_cast<char*>( static_cast<const char*>( SourceTemplateDir.GetDirectory() ) ),
					const_cast<char*>( static_cast<const char*>( SourceTemplateDir.GetDirectory() ) ),
					szTemp,
					&wLen,
					szPreviousVer,
					&wPreviousVerLen );
#endif // _WIN32

#ifndef _WIN32
	dwRet = VerInstallFile( VIFF_FORCEINSTALL,
							(const char*)File,
							(const char*)File,
							(const char*)SourceTemplateDir.GetDirectory(),
							(const char*)DestinationTemplateDir.GetDirectory(),
							szPreviousVer,
							szTemp,
							&wLen );
#else
		dwRet = VerInstallFile( VIFF_FORCEINSTALL,
								const_cast<char*>( static_cast<const char*>( File ) ),
								const_cast<char*>( static_cast<const char*>( File ) ),
								const_cast<char*>( static_cast<const char*>( SourceTemplateDir.GetDirectory() ) ),
								const_cast<char*>( static_cast<const char*>( DestinationTemplateDir.GetDirectory() ) ),
								szPreviousVer,
								szTemp,
								&wLen );
#endif // _WIN32
	CString		str;
	if (dwRet == VIF_FILEINUSE ||
		dwRet == VIF_TEMPFILE)
	{
		return FALSE;
/*		
		// If in use not necessary to copy it
		if (MustSkipFileInUse( iFile ))
			return TRUE;

		AfxFormatString1( str, IDS_FILEINUSE, (const char*)sSrcFile );
		switch (AfxMessageBox( str, MB_ABORTRETRYIGNORE ))
		{
			case IDABORT: return FALSE;
			case IDRETRY: continue;
			case IDIGNORE: 
			{
				AfxMessageBox( IDS_IGNOREWARNING, MB_OK );
				return TRUE;
			}
		}
*/
	}
	if( dwRet == VIF_CANNOTREADSRC )
	{
		return FALSE;
/*
		AfxFormatString1( str, IDS_CANNOTREADSRC, (const char*)sSrcFile );
		ZISelectSource	SelectSource( str, GetSourceDir() );
		switch (SelectSource.DoModal())
		{
			case IDCANCEL: return FALSE;
			// Assign the new path
			case IDRETRY: 
			{
				m_sSourceDir = SelectSource.m_sDirectory;
				// Rebuild the source file
				sSrc = BuildSourceFile( iFile );
				continue;
			}
			case IDIGNORE: 
			{
				AfxMessageBox( IDS_IGNOREWARNING, MB_OK );
				return TRUE;
			}
		}
*/		
	}
	if( dwRet == VIF_CANNOTCREATE )
	{
		return FALSE;
/*
		AfxFormatString1( str, IDS_CANNOTCREATE, (const char*)sSrcFile );
		switch (AfxMessageBox( str, MB_ABORTRETRYIGNORE ))
		{
			case IDABORT: return FALSE;
			case IDRETRY: continue;
			case IDIGNORE: 
			{
				AfxMessageBox( IDS_IGNOREWARNING, MB_OK );
				return TRUE;
			}
		}
*/
	}
  	// Once the file is moved,
  	// delete it
  	CFile::Remove( Filename.GetFilename() );
  	// Refresh the complete list
  	return Scan();
  //## end ZDTemplateManager::MoveTemplateFile%902335800.body
}

// Additional Declarations
  //## begin ZDTemplateManager%345A3E310190.declarations preserve=yes
  //## end ZDTemplateManager%345A3E310190.declarations

//## begin module%345A3C2E0244.epilog preserve=yes
//## end module%345A3C2E0244.epilog
