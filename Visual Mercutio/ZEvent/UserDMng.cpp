// UserDMng.cpp: implementation of the ZBUserDirectoryManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UserDMng.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBUserDirectoryManager::ZBUserDirectoryManager( const CString Directory )
:  m_Directory(Directory), m_nBufferLength(sizeof( m_CurrentDir ) - 1)
{
}

ZBUserDirectoryManager::~ZBUserDirectoryManager()
{

}


BOOL	ZBUserDirectoryManager::SetDirectory( const CString value )
{
	if (value.GetAt( value.GetLength()-1 ) == '\\')
		m_Directory = value.Left( value.GetLength()-1 );
	else
		m_Directory = value;

	// Make the queue directory lower case.
	m_Directory.MakeLower();

	// Save the current directory
	SaveCurrentDirectory();

	// Try to see if the directory already exists
	if (SetCurrentDirectory( (const char*)m_Directory ) == 0)
	{
		// The directory does not exists
		// therefore, create it
		if (CreateDirectory( (const char*)m_Directory, NULL ) == 0)
		{
			m_Directory.Empty();
			return FALSE;
		}
	}

	// Sets back the directory
	SetLastCurrentDirectory();
	return TRUE;
}

BOOL	ZBUserDirectoryManager::UserExist( const CString Username )
{
	// Save the current directory
	SaveCurrentDirectory();
	// Try to see if the directory already exists
	if (SetCurrentDirectory( (const char*)BuildUserDirectory( Username ) ) == 0)
		return FALSE;
	// Sets back the directory
	SetLastCurrentDirectory();
	return TRUE;
}

BOOL	ZBUserDirectoryManager::CreateUser( const CString Username )
{
	if (UserExist( Username ))
		return TRUE;
	if (CreateDirectory( (const char*)BuildUserDirectory( Username ), NULL ) == 0)
		return FALSE;
	return TRUE;
}




