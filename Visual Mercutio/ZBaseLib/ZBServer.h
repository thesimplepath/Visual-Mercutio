//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//  Source file: ZBServer.h

#ifndef ZBServer_h
#define ZBServer_h 1

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// ZAServerOptions
#include "ZAServerOptions.h"

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 9 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Error code definition
#define    _SRV_NOTINITIALIZED        0
#define    _SRV_SUCCESS            1
#define _SRV_EMPTYSTRUCT        2
#define _SRV_MOVED                3
#define _SRV_CORRUPTED            4
#define _SRV_ACCESSDENIED        5
#define _SRV_INVALIDUSERNAME    6
#define _SRV_EMPTYINITFAILED    7
#define _SRV_NOTFOUND            8

///////////////////////////////////////////////////////////////////////////
// Class ZBServer

class AFX_EXT_CLASS ZBServer
{
public:

    ZBServer( const CString IniFile = _T( "" ) );
    ~ZBServer();

    // By default returns true
    virtual BOOL IsLocal() const
    {
        return TRUE;
    };

    // Open the server session
    // Return false if the server is invalid or cannot be reached
    int OpenSession                ( BOOL bCheckStructure = TRUE, BOOL ForceNetwork = FALSE );
    int OpenSessionForceNetwork    ( const CString IniFile, BOOL bCheckStructure = TRUE );
    int OpenSession                ( const CString IniFile, BOOL bCheckStructure = TRUE );

    // Create an initial environment if does not exist
    // Returns the server ini file
    CString CreateInitialEnvironment( const CString ServerDirectory, BOOL EraseExisting = FALSE );

    BOOL            CloseSession();
    BOOL            IsSessionValid() const;
    virtual BOOL    SaveDefinitionToIniFile();

    BOOL CreateEmptyServerObject ( BOOL                IsLocalServer,
                                   const CString    RootPath,
                                   const CString    TemplateDirectory            = _T( "" ),
                                   const CString    FileDirectory                = _T( "" ),
                                   const CString    GlobalFieldNameRepository    = _T( "" ),
                                   const CString    ProcessTemplateDirectory    = _T( "" ),
                                   const CString    ModelTemplateDirectory        = _T( "" ),
                                   const CString    ModelUnitDirectory            = _T( "" ),
                                   const CString    LogFile                        = _T( "" ),
                                   const BOOL        UseDatabase                    = TRUE,
                                   const BOOL        UseFolderNameAsFile            = TRUE,
                                   const BOOL        StoreUserFileByUser            = FALSE,
                                   const BOOL        KeepHistoryOnProcess        = TRUE );

    //    Set the server ini file
    void SetServerIniFile(const CString& value);

    // Get the defined server ini file
    const CString GetServerIniFile() const;

    // Set the path root of the system. Change other depend directories.
    void SetRootPath( const CString value );

    // Contains the root application path.
    const CString GetRootPath() const;

    // Save the location where the template directory are stored.
    const CString GetTemplateDirectory () const;
    void SetTemplateDirectory (CString value);

    // The file directory.
    const CString GetFileDirectory() const;
    void SetFileDirectory( CString value );

    // The global field name repository file.
    const CString GetGlobalFieldNameRepository() const;
    void SetGlobalFieldNameRepository( CString value );

    // Save the location where the process template directory is.
    const CString GetProcessTemplateDirectory() const;
    void SetProcessTemplateDirectory( CString value );

    const CString GetModelTemplateDirectory() const;
    void SetModelTemplateDirectory( CString value );

    CString GetModelUnitDirectory() const;
    void SetModelUnitDirectory( CString value );

    // Save the location where the log file is.
    const CString GetLogFile() const;

    const BOOL GetUseFolderNameAsFile() const;
    void SetUseFolderNameAsFile( BOOL value );

    const BOOL GetStoreUserFileByUser() const;
    void SetStoreUserFileByUser( BOOL value );

    const CString GetSystemDirectory() const;

    const CString GetEventDirectory() const;

    const CString GetInterfaceDirectory() const;

    const CString GetLogDirectory() const;

    const CString GetUserDirectory() const;

    const CString GetUserDefinitionFile() const;
    const CString GetLogDatabaseFile() const;

    const BOOL GetUseLogTextFile() const;
    void SetUseLogTextFile( BOOL value );

    const BOOL GetUseLogDatabaseFile() const;
    void SetUseLogDatabaseFile( BOOL value );

    const BOOL GetKeepHistoryOnProcess() const;
    void SetKeepHistoryOnProcess( BOOL value );

    const CString GetHistoryProcessDatabaseFile() const;

    const CString GetFieldDefinitionIniFile() const;

    const CString GetNormalTemplate() const;
    const CString GetNormalProcessTemplate() const;
    const CString GetNormalModelTemplate() const;

protected:

    BOOL _SaveDefinitionToIniFile();

private:

    int        CheckStructure();
    BOOL    LoadOptions();

private:

    ZBServer( const ZBServer &right );
    const ZBServer & operator=( const ZBServer &right );

// Data Members for Class Attributes

// Implementation
private:

    int                    m_StatusCode;

protected:

    ZAServerOptions        m_ServerOptions;
    CString                m_IniFile;
};

// Class ZBServer

inline BOOL ZBServer::IsSessionValid() const
{
    return ( m_StatusCode == _SRV_SUCCESS ) ? TRUE : FALSE;
}

inline const CString ZBServer::GetRootPath() const
{
    return m_ServerOptions.GetRootPath();
}

inline const CString ZBServer::GetTemplateDirectory() const
{
    return m_ServerOptions.GetTemplateDirectory();
}

inline void ZBServer::SetTemplateDirectory( CString value )
{
    m_ServerOptions.SetTemplateDirectory( value );
}

inline const CString ZBServer::GetFileDirectory() const
{
    return m_ServerOptions.GetFileDirectory();
}

inline void ZBServer::SetFileDirectory( CString value )
{
    m_ServerOptions.SetFileDirectory( value );
}

inline const CString ZBServer::GetGlobalFieldNameRepository() const
{
    return m_ServerOptions.GetGlobalFieldNameRepository();
}

inline void ZBServer::SetGlobalFieldNameRepository( CString value )
{
    m_ServerOptions.SetGlobalFieldNameRepository( value );
}

inline const CString ZBServer::GetProcessTemplateDirectory() const
{
    return m_ServerOptions.GetProcessTemplateDirectory();
}

inline void ZBServer::SetProcessTemplateDirectory( CString value )
{
    m_ServerOptions.SetProcessTemplateDirectory( value );
}

inline const CString ZBServer::GetModelTemplateDirectory() const
{
    return m_ServerOptions.GetModelTemplateDirectory();
}

inline void  ZBServer::SetModelTemplateDirectory( CString value )
{
    m_ServerOptions.SetModelTemplateDirectory( value );
}

inline CString ZBServer::GetModelUnitDirectory() const
{
    return m_ServerOptions.GetModelUnitDirectory();
}

inline void ZBServer::SetModelUnitDirectory( CString value )
{
    m_ServerOptions.SetModelUnitDirectory( value );
}

inline const CString ZBServer::GetLogFile () const
{
    return m_ServerOptions.GetLogFile();
}

inline const BOOL ZBServer::GetUseFolderNameAsFile() const
{
    return m_ServerOptions.GetUseFolderNameAsFile();
}

inline void ZBServer::SetUseFolderNameAsFile( BOOL value )
{
    m_ServerOptions.SetUseFolderNameAsFile( value );
}

inline const BOOL ZBServer::GetStoreUserFileByUser() const
{
    return m_ServerOptions.GetStoreUserFileByUser();
}

inline void ZBServer::SetStoreUserFileByUser( BOOL value )
{
    m_ServerOptions.SetStoreUserFileByUser( value );
}

inline const CString ZBServer::GetSystemDirectory() const
{
    return m_ServerOptions.GetSystemDirectory();
}

inline const CString ZBServer::GetEventDirectory() const
{
    return m_ServerOptions.GetEventDirectory();
}

inline const CString ZBServer::GetInterfaceDirectory() const
{
    return m_ServerOptions.GetInterfaceDirectory();
}

inline const CString ZBServer::GetLogDirectory() const
{
    return m_ServerOptions.GetLogDirectory();
}

inline const CString ZBServer::GetUserDirectory() const
{
    return m_ServerOptions.GetUserDirectory();
}

inline const CString ZBServer::GetUserDefinitionFile() const
{
    return m_ServerOptions.GetUserDefinitionFile();
}

inline const CString ZBServer::GetLogDatabaseFile() const
{
    return m_ServerOptions.GetLogDatabaseFile();
}

inline const BOOL ZBServer::GetUseLogTextFile() const
{
    return m_ServerOptions.GetUseLogTextFile();
}

inline void ZBServer::SetUseLogTextFile( BOOL value )
{
    m_ServerOptions.SetUseLogTextFile( value );
}

inline const BOOL ZBServer::GetUseLogDatabaseFile() const
{
    return m_ServerOptions.GetUseLogDatabaseFile();
}

inline void ZBServer::SetUseLogDatabaseFile( BOOL value )
{
    m_ServerOptions.SetUseLogDatabaseFile( value );
}

inline const BOOL ZBServer::GetKeepHistoryOnProcess() const
{
    return m_ServerOptions.GetKeepHistoryOnProcess();
}

inline void ZBServer::SetKeepHistoryOnProcess( BOOL value )
{
    m_ServerOptions.SetKeepHistoryOnProcess( value );
}

inline const CString ZBServer::GetHistoryProcessDatabaseFile() const
{
    return m_ServerOptions.GetHistoryProcessDatabaseFile();
}

inline const CString ZBServer::GetFieldDefinitionIniFile() const
{
    return m_ServerOptions.GetFieldDefinitionIniFile();
}

inline const CString ZBServer::GetNormalTemplate() const
{
    return m_ServerOptions.GetNormalTemplate();
}

inline const CString ZBServer::GetNormalProcessTemplate() const
{
    return m_ServerOptions.GetNormalProcessTemplate();
}

inline const CString ZBServer::GetNormalModelTemplate() const
{
    return m_ServerOptions.GetNormalModelTemplate();
}

// Set the server ini file
inline void ZBServer::SetServerIniFile(const CString& value)
{
    m_IniFile = value;
}

// Get the defined server ini file
inline const CString ZBServer::GetServerIniFile() const
{
    return m_IniFile;
}

///////////////////////////////////////////////////////////////////////////
// Class ZBCltServer

class AFX_EXT_CLASS ZBCltServer : public ZBServer
{
public:

    ZBCltServer( const CString IniFile = _T( "" ) );
    ~ZBCltServer();

private:

    ZBCltServer( const ZBCltServer &right );
    const ZBCltServer & operator=( const ZBCltServer &right );
};

///////////////////////////////////////////////////////////////////////////
// Class ZBSrvServer 

class AFX_EXT_CLASS ZBSrvServer : public ZBServer
{
public:

    ZBSrvServer( const CString IniFile = _T( "" ) );
    ~ZBSrvServer();

    virtual BOOL IsLocal() const
    {
        return FALSE;
    };

    virtual BOOL SaveDefinitionToIniFile();

private:

    ZBSrvServer( const ZBSrvServer &right );
    const ZBSrvServer & operator=( const ZBSrvServer &right );
};

#endif    // ZBServer_h
