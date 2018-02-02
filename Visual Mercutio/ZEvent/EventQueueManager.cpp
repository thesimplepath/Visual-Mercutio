// Source file: EventQueueManager.cpp

#include <StdAfx.h>

#include "EventQueueManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZBEventQueueManager 


ZBEventQueueManager::ZBEventQueueManager()
{
}

ZBEventQueueManager::~ZBEventQueueManager()
{
}

BOOL ZBEventQueueManager::Create( const CString Directory )
{
	if (Directory.GetAt( Directory.GetLength()-1 ) == '\\')
		m_Directory = Directory.Left( Directory.GetLength()-1 );
	else
		m_Directory = Directory;

	// Make the queue directory lower case.
	m_Directory.MakeLower();

	return TRUE;
}

BOOL	ZBEventQueueManager::DispatchToEventQueue( ZBEventActivity& EventActivity )
{
	CString	Filename = BuildActivityEventFilename( EventActivity );
	m_EventActivityFile.ExportActivityToFile( Filename, &EventActivity );
	return TRUE;
}

CString	ZBEventQueueManager::BuildActivityEventFilename( ZBEventActivity& EventActivity )
{
	CString	File = m_Directory + "\\" + EventActivity.GetFilename() + EventActivity.GetFileExtension();
	for (int i = 0; i < 20; ++i)
	{
		// Check if the file exists
		CFileStatus status;
		if (CFile::GetStatus( File, status ))
		{
			TRACE("SLEEP IN DISPATCH TO EVENT QUEUE");
			::Sleep(100);
			continue;
		}
		else
			break;
	}
	if (i < 20)
		return File;
	char FileBuffer[MAX_PATH];
	// If the filename already exists, choose another name
	GetTempFileName( m_Directory,	// pointer to directory name for temporary file
	  "Exp",						// pointer to file name prefix
	  0,							// number used to create temporary file name
	  FileBuffer);					// pointer to buffer that receives the new 
									// file name
	TRACE("TEMPORARY FILE CREATED");
	return FileBuffer;
}


