//## begin module%345A3B2B01F4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%345A3B2B01F4.cm

//## begin module%345A3B2B01F4.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%345A3B2B01F4.cp

//## Module: TmplDir%345A3B2B01F4; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\TmplDir.cpp

//## begin module%345A3B2B01F4.additionalIncludes preserve=no
//## end module%345A3B2B01F4.additionalIncludes

//## begin module%345A3B2B01F4.includes preserve=yes
#include <StdAfx.h>
#include <direct.h> 
#include <dos.h>
//## end module%345A3B2B01F4.includes

// TmplDir
#include "TmplDir.h"
//## begin module%345A3B2B01F4.declarations preserve=no
//## end module%345A3B2B01F4.declarations

//## begin module%345A3B2B01F4.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_DYNCREATE(ZDTemplateDir, CObject)
//## end module%345A3B2B01F4.additionalDeclarations


// Class ZDTemplateDir 





ZDTemplateDir::ZDTemplateDir()
  //## begin ZDTemplateDir::ZDTemplateDir%.hasinit preserve=no
  //## end ZDTemplateDir::ZDTemplateDir%.hasinit
  //## begin ZDTemplateDir::ZDTemplateDir%.initialization preserve=yes
  //## end ZDTemplateDir::ZDTemplateDir%.initialization
{
  //## begin ZDTemplateDir::ZDTemplateDir%.body preserve=yes
  //## end ZDTemplateDir::ZDTemplateDir%.body
}

ZDTemplateDir::ZDTemplateDir (CString Directory, CString Title, CString FileExtension)
  //## begin ZDTemplateDir::ZDTemplateDir%878377698.hasinit preserve=no
  //## end ZDTemplateDir::ZDTemplateDir%878377698.hasinit
  //## begin ZDTemplateDir::ZDTemplateDir%878377698.initialization preserve=yes
  : m_FileExtension(FileExtension)
  //## end ZDTemplateDir::ZDTemplateDir%878377698.initialization
{
  //## begin ZDTemplateDir::ZDTemplateDir%878377698.body preserve=yes
  	Create( Directory, Title );
  //## end ZDTemplateDir::ZDTemplateDir%878377698.body
}


ZDTemplateDir::~ZDTemplateDir()
{
  //## begin ZDTemplateDir::~ZDTemplateDir%.body preserve=yes
	FreeList();
  //## end ZDTemplateDir::~ZDTemplateDir%.body
}



//## Other Operations (implementation)
ZDTemplateFile* ZDTemplateDir::FindFile (CString Filename)
{
  //## begin ZDTemplateDir::FindFile%878329362.body preserve=yes
	// Run through the list and tries to locate the specified filename
  	for (int i = 0; i < m_DirectoryList.GetSize(); ++i)
  		if (((ZDTemplateFile*)(m_DirectoryList[i]))->GetFilename().CompareNoCase(Filename) == 0)
  			return ((ZDTemplateFile*)(m_DirectoryList[i]));
  	return NULL;
  //## end ZDTemplateDir::FindFile%878329362.body
}

ZDTemplateFile* ZDTemplateDir::FindTitle (CString Title)
{
  //## begin ZDTemplateDir::FindTitle%878329363.body preserve=yes
	// Run through the list and tries to locate the specified filename
  	for (int i = 0; i < m_DirectoryList.GetSize(); ++i)
  		if (((ZDTemplateFile*)(m_DirectoryList[i]))->GetStamp().GetTitle().CompareNoCase(Title) == 0)
  			return ((ZDTemplateFile*)(m_DirectoryList[i]));
  	return NULL;
  //## end ZDTemplateDir::FindTitle%878329363.body
}

BOOL ZDTemplateDir::Create (CString Directory, CString Title)
{
  //## begin ZDTemplateDir::Create%878329366.body preserve=yes
	// Fist free the file list
  	m_TemplateFileList.RemoveAll();
  	// Save the directory & the title
  	m_Directory = Directory;
  	m_Title = Title;

	// First, free the list	
	FreeList();
	
#ifndef _WIN32
  	// Scans the directory
	char 		drive[_MAX_DRIVE];
	char 		dir[_MAX_DIR];
	char 		fname[_MAX_FNAME];
	char 		ext[_MAX_EXT];
	unsigned 	uOldDrive;
   	unsigned 	uNumberOfDrives;

	// Keep the current drive	
	_dos_getdrive( &uOldDrive );

	// Extract and set the new drive 
	_splitpath( Directory, drive, dir, fname, ext );
  	_dos_setdrive( ((unsigned)*drive) - 'A' + 1, &uNumberOfDrives );
	chdir( Directory );
#else
	char	szCurrentDir[300];
	GetCurrentDirectory( sizeof( szCurrentDir ), szCurrentDir );
	SetCurrentDirectory( Directory );
#endif

	// Search files from the current directory.	
    CString	sFiles = "*." + m_FileExtension;
    CString	sCompleteFile;

#ifndef _WIN32
    struct find_t FileInfo;

    if (!_dos_findfirst( sFiles, _A_NORMAL | _A_RDONLY | _A_HIDDEN, &FileInfo )) 
    {
    	do
    	{
    		// Build the complete file
		 	sCompleteFile = Directory + "\\" + FileInfo.name;
			
			ZDTemplateFile*	pFile = new ZDTemplateFile( sCompleteFile );
			if (!pFile->IsPersistent())
			{
				delete pFile;
				continue;
			}
			// Add the filename to the file list
			m_TemplateFileList.Add( pFile->GetTitle() );
			// Add the file object to the array
			m_DirectoryList.Add( pFile );
    	}
	    // Search for additional files.
        while (!_dos_findnext (&FileInfo));
    }

	// Restore the previous drive
  	_dos_setdrive( uOldDrive, &uNumberOfDrives );
#else
	WIN32_FIND_DATA		FileInfo;
	HANDLE				hFile;
    if ((hFile=FindFirstFile( sFiles, &FileInfo )) != INVALID_HANDLE_VALUE)
    {
    	do
    	{
			if (FileInfo.dwFileAttributes & FILE_ATTRIBUTE_NORMAL ||
				FileInfo.dwFileAttributes & FILE_ATTRIBUTE_READONLY ||
				FileInfo.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN ||
				FileInfo.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
			{
    			// Build the complete file
		 		sCompleteFile = Directory + "\\" + FileInfo.cFileName;
				
				ZDTemplateFile*	pFile = new ZDTemplateFile( sCompleteFile );
				if (!pFile->IsPersistent())
				{
					delete pFile;
					continue;
				}
				// Add the filename to the file list
				m_TemplateFileList.Add( pFile->GetTitle() );
				// Add the file object to the array
				m_DirectoryList.Add( pFile );
			}
    	}
	    // Search for additional files.
        while (FindNextFile (hFile, &FileInfo) != 0);
    }
	// Restore initial directory
	SetCurrentDirectory( szCurrentDir );
#endif
  	return m_DirectoryList.GetSize() > 0;
  //## end ZDTemplateDir::Create%878329366.body
}

void ZDTemplateDir::FreeList ()
{
  //## begin ZDTemplateDir::FreeList%878377699.body preserve=yes
	// Free all file objects allocated 
  	for (int i = 0; i < m_DirectoryList.GetSize(); ++i)
  		delete ((ZDTemplateFile*)(m_DirectoryList[i]));
  	m_DirectoryList.RemoveAll();
  //## end ZDTemplateDir::FreeList%878377699.body
}

// Additional Declarations
  //## begin ZDTemplateDir%345A3B3E037A.declarations preserve=yes
  //## end ZDTemplateDir%345A3B3E037A.declarations

//## begin module%345A3B2B01F4.epilog preserve=yes
//## end module%345A3B2B01F4.epilog
