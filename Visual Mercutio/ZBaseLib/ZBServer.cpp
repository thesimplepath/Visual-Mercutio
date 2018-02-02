//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//  Source file: ZBServer.cpp

#include <StdAfx.h>

// ZBServer
#include "ZBServer.h"
#include "File.h"
#include "ZDirectory.h"

// ZNetWork
#include "ZNetWork.h"

// JMR-MODIF - Le 9 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Class ZBServer

ZBServer::ZBServer( const CString IniFile /* = "" */ )
	: m_StatusCode	( _SRV_NOTINITIALIZED ),
	  m_IniFile		( IniFile )
{
}

ZBServer::~ZBServer()
{
}

BOOL ZBServer::CreateEmptyServerObject( BOOL			IsLocalServer,
										const CString	RootPath,
										const CString	TemplateDirectory,
										const CString	FileDirectory,
										const CString	GlobalFieldNameRepository,
										const CString	ProcessTemplateDirectory,
										const CString	ModelTemplateDirectory,
										const CString	ModelUnitDirectory,
										const CString	LogFile,
										const BOOL		UseDatabase,
										const BOOL		UseFolderNameAsFile,
										const BOOL		StoreUserFileByUser,
										const BOOL		KeepHistoryOnProcess)
{
	// If no root directory
	CString Root = ZDirectory::NormalizeDirectory( RootPath );

	if ( Root.IsEmpty() )
	{
		return FALSE;
	}

	// Build the ini file
	m_IniFile = Root + _T( "\\" );
	m_IniFile += (IsLocalServer) ? CString( szLocalIniFilename ) : CString( szGlobalIniFilename );

	return m_ServerOptions.CreateEmptyServerOption( RootPath,
													TemplateDirectory,
													FileDirectory,
													GlobalFieldNameRepository,
													ProcessTemplateDirectory,
													ModelTemplateDirectory,
													ModelUnitDirectory,
													LogFile,
													UseDatabase,
													UseFolderNameAsFile,
													StoreUserFileByUser,
													KeepHistoryOnProcess );
}

int ZBServer::OpenSession( const CString IniFile, BOOL bCheckStructure /*= TRUE*/ )
{
	m_IniFile = IniFile;

	// Check the filename to avoid improper filename
	ZFile file( m_IniFile );
	file.ReBuild();
	m_IniFile = file.GetCompleteFileName();

	return ZBServer::OpenSession( bCheckStructure );
}

int ZBServer::OpenSessionForceNetwork( const CString IniFile, BOOL bCheckStructure /*= TRUE*/ )
{
	m_IniFile = IniFile;

	// Check the filename to avoid improper filename
	ZFile file( m_IniFile );
	file.ReBuild();
	m_IniFile = file.GetCompleteFileName();

	return ZBServer::OpenSession( bCheckStructure, TRUE );
}

int ZBServer::OpenSession( BOOL bCheckStructure /*= TRUE*/, BOOL ForceNetwork /*= FALSE*/ )
{
	// If the ini filename is nothing, not valid
	if ( m_IniFile.IsEmpty() )
	{
		return m_StatusCode = _SRV_CORRUPTED;
	}

	// Check if the path and the ini file exist
	ZFile File( m_IniFile );

	// Check if the ini file exists
	if ( File.Exist() == FALSE )
	{
		if ( ForceNetwork == FALSE )
		{
			return m_StatusCode = _SRV_NOTFOUND;
		}

		// Check if the path exists
		CString Path = File.GetFilePath();

		// Try to open the connection
		ZUNetwork		Net;
		CStringArray	FreeConnections;

		if ( Net.GetFreeConnections( FreeConnections ) == false )
		{
			return m_StatusCode = _SRV_ACCESSDENIED;
		}

		if ( Net.Map( File.GetFilePath(), FreeConnections.GetAt( 0 ) ) == false )
		{
			return m_StatusCode = _SRV_ACCESSDENIED;
		}

		// *************************************************************************
		// Do not remove connection while a problem exist with Windows for WorkGroup
		/*
		if ( Net.RemoveConnection( FreeConnections.GetAt( 0 ) ) == false )
		{
			// Problem removing connection
		}
		*/
		// *************************************************************************
	}

	// Load the options
	if ( !LoadOptions() )
	{
		return FALSE;
	}

	// Check if the structure is correct
	if ( bCheckStructure )
	{
		return CheckStructure();
	}

	return m_StatusCode = _SRV_SUCCESS;
}

CString ZBServer::CreateInitialEnvironment( const CString ServerDirectory, BOOL EraseExisting /*= FALSE*/ )
{
	if ( !CreateEmptyServerObject ( IsLocal(),
									ServerDirectory ) )
	{
		return _T( "" );
	}

	if ( !_SaveDefinitionToIniFile() )
	{
		return _T( "" );
	}

	// Returns the inifile
	return m_IniFile;
}

BOOL ZBServer::CloseSession()
{
	// If the session where never open, or never valid, return true
	if ( !IsSessionValid() )
	{
		return TRUE;
	}

	m_StatusCode = _SRV_NOTINITIALIZED;

	// Saves the options, depends on the server type
	return SaveDefinitionToIniFile();
}

BOOL ZBServer::SaveDefinitionToIniFile()
{
	// In the base class, do nothing
	return TRUE;
}

int ZBServer::CheckStructure()
{
	ZFile file( m_IniFile );

	// Check if the root path is empty
	if ( m_ServerOptions.GetRootPath().IsEmpty() )
	{
		// Then initialize by default the structure
		CString NewIniFile = CreateInitialEnvironment( file.GetFilePath(), FALSE );

		if ( NewIniFile.IsEmpty() )
		{
			return _SRV_EMPTYINITFAILED;
		}

		// Ok, created
		return TRUE;
	}

	// First, check if the directory of the ini file exists
	if ( !ZDirectory::Exist( file.GetFilePath() ) )
	{
		return _SRV_CORRUPTED;
	}

	// Check if the root path defined in the init is the same as the root path
	CString Dir1( ZDirectory::NormalizeDirectory( m_ServerOptions.GetRootPath() ) );
	CString Dir2( ZDirectory::NormalizeDirectory( file.GetFilePath() ) );

	if ( Dir1.CompareNoCase( Dir2 ) != 0 )
	{
		return _SRV_MOVED;
	}

	// Check if the root path defined in the init exists
	if ( !ZDirectory::Exist( m_ServerOptions.GetRootPath() ) )
	{
		return _SRV_MOVED;
	}

	return _SRV_SUCCESS;
}

BOOL ZBServer::LoadOptions()
{
	// Initialize the Global Options
	m_ServerOptions.Create( m_IniFile, szGlobalSection );

	if ( !m_ServerOptions.LoadOption() )
	{
		return FALSE;
	}

	return TRUE;
}

void ZBServer::SetRootPath( const CString value )
{
	// Call the server option member function
	m_ServerOptions.SetRootPath( value );
}

BOOL ZBServer::_SaveDefinitionToIniFile()
{
	// Initialize the Global Options
	m_ServerOptions.Create( m_IniFile, szGlobalSection );

	// Now assign the values
	m_ServerOptions.SetRootPath( GetRootPath() );
	m_ServerOptions.SetTemplateDirectory( GetTemplateDirectory() );
	m_ServerOptions.SetFileDirectory( GetFileDirectory() );
	m_ServerOptions.SetGlobalFieldNameRepository( GetGlobalFieldNameRepository() );
	m_ServerOptions.SetProcessTemplateDirectory( GetProcessTemplateDirectory() );
	m_ServerOptions.SetModelTemplateDirectory( GetModelTemplateDirectory() );
	m_ServerOptions.SetModelUnitDirectory( GetModelUnitDirectory() );
	m_ServerOptions.SetUseFolderNameAsFile( GetUseFolderNameAsFile() );
	m_ServerOptions.SetStoreUserFileByUser( GetStoreUserFileByUser() );
	m_ServerOptions.SetUseLogTextFile( GetUseLogTextFile() );
	m_ServerOptions.SetUseLogDatabaseFile( GetUseLogDatabaseFile() );
	m_ServerOptions.SetKeepHistoryOnProcess( GetKeepHistoryOnProcess() );

	// Saves the options.
	return m_ServerOptions.SaveOption();
}

///////////////////////////////////////////////////////////////////////////
// Class ZBCltServer 

ZBCltServer::ZBCltServer( const CString IniFile /* = "" */ )
	: ZBServer ( IniFile )
{
}

ZBCltServer::~ZBCltServer()
{
}

///////////////////////////////////////////////////////////////////////////
// Class ZBSrvServer

ZBSrvServer::ZBSrvServer( const CString IniFile /* = "" */ )
	: ZBServer ( IniFile )
{
}

ZBSrvServer::~ZBSrvServer()
{
}

BOOL ZBSrvServer::SaveDefinitionToIniFile()
{
	return _SaveDefinitionToIniFile();

	// JMR-MODIF - Le 9 avril 2007 - Le code ci-dessous ne peut jamais être atteint. Mis en commentaires.
	/*
	// Initialize the Global Options
	m_ServerOptions.Create( m_IniFile, szGlobalSection );

	// Now assign the values
	m_ServerOptions.SetTemplateDirectory( GetTemplateDirectory() );
	m_ServerOptions.SetFileDirectory( GetFileDirectory() );
	m_ServerOptions.SetGlobalFieldNameRepository( GetGlobalFieldNameRepository() );
	m_ServerOptions.SetProcessTemplateDirectory( GetProcessTemplateDirectory() );
	m_ServerOptions.SetModelTemplateDirectory( GetModelTemplateDirectory() );
	m_ServerOptions.SetUseFolderNameAsFile( GetUseFolderNameAsFile() );
	m_ServerOptions.SetStoreUserFileByUser( GetStoreUserFileByUser() );
	m_ServerOptions.SetUseLogTextFile( GetUseLogTextFile() );
	m_ServerOptions.SetUseLogDatabaseFile( GetUseLogDatabaseFile() );
	m_ServerOptions.SetKeepHistoryOnProcess( GetKeepHistoryOnProcess() );
	m_ServerOptions.SetRootPath( GetRootPath() );

	// Saves the options.
	return m_ServerOptions.SaveOption();
	*/
}
