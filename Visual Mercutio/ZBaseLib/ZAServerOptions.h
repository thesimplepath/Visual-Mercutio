/////////////////////////////////////////////////////////////////////////////
//@doc ZAServerOptions
//@module ZAServerOptions.h | Interface of the <c ZAServerOptions> class.
//
// Advanced Dedicated Software Classes
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software,
// All rights reserved.
// Contact:
// mailto:dominique.aigroz@adsoft-form.com
// http://www.adsoft-form.com
//
// This source code is part of the zForms library.
// See these sources for detailed information regarding
// zForms libraries.
//
// Author:       Dom
// <nl>Created:		 03/2000
// <nl>Description:  ZAServerOptions manages the server option parameters
//

#ifndef ZAServerOptions_h
#define ZAServerOptions_h 1

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// ZUSystemOption
#include "zBaseLib\ZUSystemOption.h"

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 15 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Class ZAServerOptions

class AFX_EXT_CLASS ZAServerOptions
{
public:

	ZAServerOptions( CString IniFile = _T( "" ), CString SectionName = _T( "" ) );
	~ZAServerOptions();

	BOOL Create( CString IniFile = _T( "" ), CString SectionName = _T( "" ) );

	BOOL CreateEmptyServerOption( const CString	RootPath,
								  const CString	TemplateDirectory			= _T( "" ),
								  const CString	FileDirectory				= _T( "" ),
								  const CString	GlobalFieldNameRepository	= _T( "" ),
								  const CString	ProcessTemplateDirectory	= _T( "" ),
								  const CString	ModelTemplateDirectory		= _T( "" ),
								  const CString	ModelUnitDirectory			= _T( "" ),
								  const CString	LogFile						= _T( "" ),
								  const BOOL	UseDatabase					= TRUE,
								  const BOOL	UseFolderNameAsFile			= TRUE,
								  const BOOL	StoreUserFileByUser			= FALSE,
								  const BOOL	KeepHistoryOnProcess		= TRUE );

	// Loads the options.
	BOOL LoadOption();

	// Saves the options.
	BOOL SaveOption();

	// Sets the ini file.
	void SetIniFile( const CString& File );

	// Set the path root of the system. Change other depend directories.
	void SetRootPath( const CString value );

	// Contains the root application path.
	const CString GetRootPath() const;

	// Save the location where the template directory are stored.
	const CString GetTemplateDirectory() const;
	void SetTemplateDirectory( CString value );

	// The file directory.
	const CString GetFileDirectory() const;
	void SetFileDirectory( CString value );

	// The global field name repository file.
	const CString GetGlobalFieldNameRepository() const;
	void SetGlobalFieldNameRepository( CString value );

	// Save the location where the process template directory is.
	const CString GetProcessTemplateDirectory() const;
	void SetProcessTemplateDirectory( CString value );

	// Save the location where the log file is.
	const CString GetLogFile() const;
	void SetLogFile( CString value );

	const BOOL GetUseFolderNameAsFile() const;
	void SetUseFolderNameAsFile( BOOL value );

	const BOOL GetStoreUserFileByUser() const;
	void SetStoreUserFileByUser( BOOL value );

	const CString GetSystemDirectory() const;

	const CString GetEventDirectory() const;

	const CString GetInterfaceDirectory() const;

	const CString GetLogDirectory() const;

	const CString GetUserDirectory() const;

	// Contains the field definition ini file.
	const CString& GetFieldDefinitionIniFile() const;

	const CString GetUserDefinitionFile() const;
	const CString GetLogDatabaseFile() const;

	const BOOL GetUseLogTextFile() const;
	void SetUseLogTextFile( BOOL value );

	const BOOL GetUseLogDatabaseFile() const;
	void SetUseLogDatabaseFile( BOOL value );

	const BOOL GetKeepHistoryOnProcess() const;
	void SetKeepHistoryOnProcess( BOOL value );

	const CString GetHistoryProcessDatabaseFile() const;

	const CString GetModelTemplateDirectory() const
	{
		return m_ModelTemplateDirectory;
	};

	void SetModelTemplateDirectory( CString value )
	{
		m_ModelTemplateDirectory = value;
	};

	CString GetModelUnitDirectory() const
	{
		return m_ModelUnitDirectory;
	};

	void SetModelUnitDirectory( CString value )
	{
		m_ModelUnitDirectory = value;
	};

	CString GetNormalTemplate() const;
	CString GetNormalProcessTemplate() const;
	CString GetNormalModelTemplate() const;

private:

	ZAServerOptions( const ZAServerOptions &right );
	const ZAServerOptions & operator=( const ZAServerOptions &right );

private:

	ZUSystemOption	m_Option;

	CString			m_RootPath;
	CString			m_TemplateDirectory;
	CString			m_FileDirectory;
	CString			m_GlobalFieldNameRepository;
	CString			m_ProcessTemplateDirectory;
	CString			m_LogFile;
	CString			m_SystemDirectory;
	CString			m_EventDirectory;
	CString			m_InterfaceDirectory;
	CString			m_LogDirectory;
	CString			m_UserDirectory;
	CString			m_FieldDefinitionIniFile;
	CString			m_UserDefinitionFile;
	CString			m_LogDatabaseFile;
	CString			m_HistoryProcessDatabaseFile;
	CString			m_ModelTemplateDirectory;
	CString			m_ModelUnitDirectory;

	BOOL			m_UseFolderNameAsFile;
	BOOL			m_StoreUserFileByUser;
	BOOL			m_UseLogTextFile;
	BOOL			m_UseLogDatabaseFile;
	BOOL			m_KeepHistoryOnProcess;
};

inline void ZAServerOptions::SetIniFile( const CString& File )
{
	m_Option.SetIniFile( File );
}

inline const CString ZAServerOptions::GetRootPath() const
{
	return m_RootPath;
}

inline const CString ZAServerOptions::GetTemplateDirectory() const
{
	return m_TemplateDirectory;
}

inline void ZAServerOptions::SetTemplateDirectory( CString value )
{
	m_TemplateDirectory = value;
}

inline const CString ZAServerOptions::GetFileDirectory() const
{
	return m_FileDirectory;
}

inline void ZAServerOptions::SetFileDirectory( CString value )
{
	m_FileDirectory = value;
}

inline const CString ZAServerOptions::GetGlobalFieldNameRepository() const
{
	return m_GlobalFieldNameRepository;
}

inline void ZAServerOptions::SetGlobalFieldNameRepository( CString value )
{
	m_GlobalFieldNameRepository = value;
}

inline const CString ZAServerOptions::GetProcessTemplateDirectory() const
{
	return m_ProcessTemplateDirectory;
}

inline void ZAServerOptions::SetProcessTemplateDirectory( CString value )
{
	m_ProcessTemplateDirectory = value;
}

inline const CString ZAServerOptions::GetLogFile() const
{
	return m_LogFile;
}

inline void ZAServerOptions::SetLogFile( CString value )
{
	m_LogFile = value;
}

inline const BOOL ZAServerOptions::GetUseFolderNameAsFile() const
{
	return m_UseFolderNameAsFile;
}

inline void ZAServerOptions::SetUseFolderNameAsFile( BOOL value )
{
	m_UseFolderNameAsFile = value;
}

inline const BOOL ZAServerOptions::GetStoreUserFileByUser() const
{
	return m_StoreUserFileByUser;
}

inline void ZAServerOptions::SetStoreUserFileByUser( BOOL value )
{
	m_StoreUserFileByUser = value;
}

inline const CString ZAServerOptions::GetSystemDirectory() const
{
	return m_SystemDirectory;
}

inline const CString ZAServerOptions::GetEventDirectory() const
{
	return m_EventDirectory;
}

inline const CString ZAServerOptions::GetInterfaceDirectory() const
{
	return m_InterfaceDirectory;
}

inline const CString ZAServerOptions::GetLogDirectory() const
{
	return m_LogDirectory;
}

inline const CString ZAServerOptions::GetUserDirectory() const
{
	return m_UserDirectory;
}

inline const CString& ZAServerOptions::GetFieldDefinitionIniFile() const
{
	return m_FieldDefinitionIniFile;
}

inline const CString ZAServerOptions::GetUserDefinitionFile() const
{
	return m_UserDefinitionFile;
}

inline const CString ZAServerOptions::GetLogDatabaseFile() const
{
	return m_LogDatabaseFile;
}

inline const BOOL ZAServerOptions::GetUseLogTextFile() const
{
	return m_UseLogTextFile;
}

inline void ZAServerOptions::SetUseLogTextFile( BOOL value )
{
	m_UseLogTextFile = value;
}

inline const BOOL ZAServerOptions::GetUseLogDatabaseFile() const
{
	return m_UseLogDatabaseFile;
}

inline void ZAServerOptions::SetUseLogDatabaseFile( BOOL value )
{
	m_UseLogDatabaseFile = value;
}

inline const BOOL ZAServerOptions::GetKeepHistoryOnProcess() const
{
	return m_KeepHistoryOnProcess;
}

inline void ZAServerOptions::SetKeepHistoryOnProcess( BOOL value )
{
	m_KeepHistoryOnProcess = value;
}

inline const CString ZAServerOptions::GetHistoryProcessDatabaseFile() const
{
	return m_HistoryProcessDatabaseFile;
}

inline CString ZAServerOptions::GetNormalTemplate() const
{
	return GetSystemDirectory() + _T( "\\" ) + sNormalTemplateFilename;
}

inline CString ZAServerOptions::GetNormalProcessTemplate() const
{
	return GetSystemDirectory() + _T( "\\" ) + sNormalProcessTemplateFilename;
}

inline CString ZAServerOptions::GetNormalModelTemplate() const
{
	return GetSystemDirectory() + _T( "\\" ) + sNormalModelTemplateFilename;
}

#endif	   // ZAServerOptions_h