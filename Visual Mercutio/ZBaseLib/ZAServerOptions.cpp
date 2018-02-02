/////////////////////////////////////////////////////////////////////////////
//@doc ZAServerOptions
//@module ZAServerOptions.cpp | Implementation of the <c ZAServerOptions> class.
// 
// zForms<tm>
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software, Inc. 
// All rights reserved.
// Contact:
// mailto:dominique.aigroz@adsoft-form.com
// http://www.adsoft-form.com

#include <StdAfx.h>

// ZAServerOptions
#include "ZAServerOptions.h"

#include "zBaseLib\ZDirectory.h"

// JMR-MODIF - Le 15 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Class ZAServerOptions

ZAServerOptions::ZAServerOptions( CString IniFile, CString SectionName )
{
	Create( IniFile, SectionName );
}

ZAServerOptions::~ZAServerOptions()
{
}

BOOL ZAServerOptions::Create( CString IniFile, CString SectionName )
{
	m_Option.Create( IniFile, SectionName );

	return TRUE;
}

BOOL ZAServerOptions::LoadOption()
{
	SetRootPath( m_Option.ReadOption( szRootEntry, _T( "" ) ) );

	m_TemplateDirectory = m_Option.ReadOption( szTemplateDirEntry, _T( "" ) );
	m_TemplateDirectory = ZDirectory::NormalizeDirectory( m_TemplateDirectory, true );

	m_FileDirectory = m_Option.ReadOption( szFileDirEntry, _T( "" ) );
	m_FileDirectory = ZDirectory::NormalizeDirectory( m_FileDirectory, true );

	m_ProcessTemplateDirectory = m_Option.ReadOption( szProcessTemplateDirEntry, _T( "" ) );
	m_ProcessTemplateDirectory = ZDirectory::NormalizeDirectory( m_ProcessTemplateDirectory, true );

	m_ModelTemplateDirectory = m_Option.ReadOption( szModelTemplateDirEntry, _T( "" ) );
	m_ModelTemplateDirectory = ZDirectory::NormalizeDirectory( m_ModelTemplateDirectory, true );

	m_ModelUnitDirectory = m_Option.ReadOption( szModelUnitDirEntry, _T( "" ) );
	m_ModelUnitDirectory = ZDirectory::NormalizeDirectory( m_ModelUnitDirectory, true );

	m_GlobalFieldNameRepository = m_Option.ReadOption( szGlobalFieldRepositoryEntry, _T( "" ) );
	m_UseFolderNameAsFile = m_Option.ReadOption( szUseFolderNameAsFilename, 1 );
	m_StoreUserFileByUser = m_Option.ReadOption( szStoreUserFileByUser, 0 );

	m_UseLogTextFile = m_Option.ReadOption( szUseLogTextFile, 1 );
	m_UseLogDatabaseFile = m_Option.ReadOption( szUseLogDatabaseFile, 0 );

	m_KeepHistoryOnProcess = m_Option.ReadOption( szKeepHistoryProcessOnDatabase, 1 );

	return TRUE;
}

BOOL ZAServerOptions::SaveOption()
{
	m_Option.WriteOption( szRootEntry, m_RootPath );
	m_Option.WriteOption( szTemplateDirEntry, m_TemplateDirectory );
	m_Option.WriteOption( szFileDirEntry, m_FileDirectory );
	m_Option.WriteOption( szGlobalFieldRepositoryEntry, m_GlobalFieldNameRepository );
	m_Option.WriteOption( szProcessTemplateDirEntry, m_ProcessTemplateDirectory );
	m_Option.WriteOption( szModelTemplateDirEntry, m_ModelTemplateDirectory );
	m_Option.WriteOption( szModelUnitDirEntry, m_ModelUnitDirectory );
	m_Option.WriteOption( szUseFolderNameAsFilename, m_UseFolderNameAsFile );
	m_Option.WriteOption( szStoreUserFileByUser, m_StoreUserFileByUser );
	m_Option.WriteOption( szUseLogTextFile, m_UseLogTextFile );
	m_Option.WriteOption( szUseLogDatabaseFile, m_UseLogDatabaseFile );
	m_Option.WriteOption( szKeepHistoryProcessOnDatabase, m_KeepHistoryOnProcess );

	return TRUE;
}

void ZAServerOptions::SetRootPath( const CString value )
{
	m_RootPath = value;

	if ( m_RootPath.IsEmpty() )
	{
		return;
	}

	ZDirectory::NormalizeDirectory( m_RootPath );

	// Build directories
	m_SystemDirectory				= m_RootPath			+ _T( "\\System" );
	m_EventDirectory				= m_SystemDirectory		+ _T( "\\Events" );
	m_InterfaceDirectory			= m_SystemDirectory		+ _T( "\\Interfac" );
	m_LogDirectory					= m_SystemDirectory		+ _T( "\\Log" );
	m_UserDirectory					= m_SystemDirectory		+ _T( "\\Users" );
	m_ModelTemplateDirectory		= m_RootPath			+ _T( "\\Model" );
	m_ModelUnitDirectory			= m_RootPath			+ _T( "\\Units" );
	m_UserDefinitionFile			= m_SystemDirectory		+ _T( "\\" ) + sUserDefinitionFilename;
	m_LogDatabaseFile				= m_LogDirectory		+ _T( "\\" ) + sActivityLogDatabase;
	m_LogFile						= m_LogDirectory		+ _T( "\\" ) + sActivityLogFilename;
	m_HistoryProcessDatabaseFile	= m_LogDirectory		+ _T( "\\" ) + sHistoryProcessDatabase;
	m_FieldDefinitionIniFile		= m_RootPath			+ _T( "\\System\\FieldDef.ini" );
}

BOOL ZAServerOptions::CreateEmptyServerOption( const CString	RootPath,
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
											   const BOOL		KeepHistoryOnProcess )
{
	// If no root directory
	CString Root = ZDirectory::NormalizeDirectory( RootPath );

	if ( Root.IsEmpty() )
	{
		return FALSE;
	}

	// Assign the root path
	SetRootPath( Root );

	// Now assign the values
	SetTemplateDirectory( TemplateDirectory.IsEmpty() ? Root + _T( "\\Template" ) : TemplateDirectory );
	SetFileDirectory( FileDirectory.IsEmpty() ? Root + _T( "\\Files" ) : FileDirectory );
	SetGlobalFieldNameRepository( GlobalFieldNameRepository.IsEmpty() ? m_SystemDirectory + _T( "\\Def.pld" ) : GlobalFieldNameRepository );
	SetProcessTemplateDirectory( ProcessTemplateDirectory.IsEmpty() ? Root + _T( "\\ProcTmpl" ) : ProcessTemplateDirectory );
	SetModelTemplateDirectory( ModelTemplateDirectory.IsEmpty() ? Root + _T( "\\Model" ) : ModelTemplateDirectory );
	SetModelUnitDirectory( ModelUnitDirectory.IsEmpty() ? Root + _T( "\\Units" ) : ModelUnitDirectory );
	SetUseFolderNameAsFile( UseFolderNameAsFile );
	SetStoreUserFileByUser( StoreUserFileByUser );
	SetUseLogTextFile( !UseDatabase );
	SetUseLogDatabaseFile( UseDatabase );
	SetKeepHistoryOnProcess( KeepHistoryOnProcess );

	return TRUE;
}
