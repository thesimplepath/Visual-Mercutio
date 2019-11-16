/****************************************************************************
 * ==> PSS_Server ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides several servers                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ServerH
#define PSS_ServerH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ServerOptions.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Srv_NotInitialized  0
#define M_Srv_Success         1
#define M_Srv_EmptyStruct     2
#define M_Srv_Moved           3
#define M_Srv_Corrupted       4
#define M_Srv_AccessDenied    5
#define M_Srv_InvalidUserName 6
#define M_Srv_EmptyInitFailed 7
#define M_Srv_NotFound        8
//---------------------------------------------------------------------------

/**
* Basic server
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Server
{
    public:
        /**
        * Constructor
        *@param iniFile - initialization file
        */
        PSS_Server(const CString& iniFile = _T(""));

        virtual ~PSS_Server();

        /**
        * Checks if the server is local
        *@return TRUE if the server is local, otherwise FALSE
        */
        virtual BOOL IsLocal() const;

        /**
        * Opens the server session
        *@param checkStructure - if TRUE, the structure will be checked
        *@param forceNetwork - if TRUE, the network will be forced
        *@return TRUE on success, FALSE if the server is invalid or cannot be reached
        */
        virtual BOOL OpenSession(BOOL checkStructure = TRUE, BOOL forceNetwork = FALSE);

        /**
        * Opens the server session
        *@param iniFile - initialization file
        *@param checkStructure - if TRUE, the structure will be checked
        *@return TRUE on success, FALSE if the server is invalid or cannot be reached
        */
        virtual BOOL OpenSession(const CString& iniFile, BOOL checkStructure = TRUE);

        /**
        * Opens the server session and force the network
        *@param iniFile - initialization file
        *@param checkStructure - if TRUE, the structure will be checked
        *@return TRUE on success, FALSE if the server is invalid or cannot be reached
        */
        virtual BOOL OpenSessionForceNetwork(const CString& iniFile, BOOL checkStructure = TRUE);

        /**
        * Creates an initial environment
        *@param serverDir - server directory
        *@param eraseExisting - if TRUE and a server already exists, erases it and replace by the newly created one
        *@returns the server ini file
        */
        virtual CString CreateInitialEnvironment(const CString& serverDir, BOOL eraseExisting = FALSE);

        /**
        * Closes the server session
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CloseSession();

        /**
        * Checks if server session is valid
        *@return TRUE if server session is valid, otherwise FALSE
        */
        virtual inline BOOL IsSessionValid() const;

        /**
        * Saves the definition to initialization file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveDefinitionToIniFile();

        /**
        * Creates an empty server object
        *@param isLocalServer - if TRUE, server will be a local server
        *@param rootPath - server root path
        *@param templateDir - template directory
        *@param globalFieldNameRepository - global field name repository
        *@param processTemplateDir - process template directory
        *@param modelTemplateDir - model template directory
        *@param modelUnitDir - model unit directory
        *@param logFile - log file
        *@param useDatabase - if TRUE, database will be used
        *@param useFolderNameAsFile - if TRUE, the folder name will be used as file
        *@param storeUserFileByUser - if TRUE, the user file will be stored by the user
        *@param keepHistoryOnProcess - if TRUE, the process history will be kept on process
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateEmptyServerObject(BOOL           isLocalServer,
                                             const CString& rootPath,
                                             const CString& templateDir               = _T(""),
                                             const CString& fileDir                   = _T(""),
                                             const CString& globalFieldNameRepository = _T(""),
                                             const CString& processTemplateDir        = _T(""),
                                             const CString& modelTemplateDir          = _T(""),
                                             const CString& modelUnitDir              = _T(""),
                                             const CString& logFile                   = _T(""),
                                             BOOL           useDatabase               = TRUE,
                                             BOOL           useFolderNameAsFile       = TRUE,
                                             BOOL           storeUserFileByUser       = FALSE,
                                             BOOL           keepHistoryOnProcess      = TRUE);

        /**
        * Gets the server ini file
        *@return the server ini file
        */
        virtual inline const CString GetServerIniFile() const;

        /**
        * Sets the server ini file
        *@param value - the server ini file
        */
        virtual inline void SetServerIniFile(const CString& value);

        /**
        * Gets the root application path
        *@return the root application path
        */
        virtual inline const CString GetRootPath() const;

        /**
        * Sets the root application path
        *@param value - the root application path
        *@note The other directories which depend on it will also be updated
        */
        virtual void SetRootPath(const CString& value);

        /**
        * Gets the template directory location
        *@return the template directory location
        */
        virtual inline const CString GetTemplateDirectory() const;

        /**
        * Sets the template directory location
        *@param value - the template directory location
        */
        virtual inline void SetTemplateDirectory(const CString& value);

        /**
        * Gets the file directory
        *@return the file directory
        */
        virtual inline const CString GetFileDirectory() const;

        /**
        * Sets the file directory
        *@param value - the file directory
        */
        virtual inline void SetFileDirectory(const CString& value);

        /**
        * Gets the global field name repository file
        *@return the global field name repository file
        */
        virtual inline const CString GetGlobalFieldNameRepository() const;

        /**
        * Sets the global field name repository file
        *@param value - the global field name repository file
        */
        virtual inline void SetGlobalFieldNameRepository(const CString& value);

        /**
        * Gets the process template directory location
        *@return the process template directory location
        */
        virtual inline const CString GetProcessTemplateDirectory() const;

        /**
        * Sets the process template directory location
        *@param value - the process template directory location
        */
        virtual inline void SetProcessTemplateDirectory(const CString& value);

        /**
        * Gets the model template directory location
        *@return the model template directory location
        */
        virtual inline const CString GetModelTemplateDirectory() const;

        /**
        * Sets the model template directory location
        *@param value - the model template directory location
        */
        virtual inline void SetModelTemplateDirectory(const CString& value);

        /**
        * Gets the model unit directory location
        *@return the model unit directory location
        */
        virtual inline CString GetModelUnitDirectory() const;

        /**
        * Sets the model unit directory location
        *@param value - the model unit directory location
        */
        virtual inline void SetModelUnitDirectory(const CString& value);

        /**
        * Gets the log file name
        *@return the log file name
        */
        virtual inline const CString GetLogFile() const;

        /**
        * Gets if the folder name may be used as a file
        *@return TRUE if the folder name may be used as a file, otherwise FALSE
        */
        virtual inline const BOOL GetUseFolderNameAsFile() const;

        /**
        * Sets if the folder name may be used as a file
        *@param value - if TRUE, the folder name may be used as a file
        */
        virtual inline void SetUseFolderNameAsFile(BOOL value);

        /**
        * Gets if the user file should be stored by the user
        *@return TRUE if the user file should be stored by the user, otherwise FALSE
        */
        virtual inline const BOOL GetStoreUserFileByUser() const;

        /**
        * Sets if the user file should be stored by the user
        *@param value - if TRUE, the user file will be stored by the user
        */
        virtual inline void SetStoreUserFileByUser(BOOL value);

        /**
        * Gets the system directory
        *@return the system directory
        */
        virtual inline const CString GetSystemDirectory() const;

        /**
        * Gets the event directory
        *@return the event directory
        */
        virtual inline const CString GetEventDirectory() const;

        /**
        * Gets the interface directory
        *@return the interface directory
        */
        virtual inline const CString GetInterfaceDirectory() const;

        /**
        * Gets the log directory
        *@return the log directory
        */
        virtual inline const CString GetLogDirectory() const;

        /**
        * Gets the user directory
        *@return the user directory
        */
        virtual inline const CString GetUserDirectory() const;

        /**
        * Gets the user definition file name
        *@return the user definition file name
        */
        virtual inline const CString GetUserDefinitionFile() const;

        /**
        * Gets the log database file name
        *@return the log database file name
        */
        virtual inline const CString GetLogDatabaseFile() const;

        /**
        * Gets if the log should be written in a text file
        *@return TRUE if the log should be written in a text file, otherwise FALSE
        */
        virtual inline const BOOL GetUseLogTextFile() const;

        /**
        * Sets if the log should be written in a text file
        *@param value - if TRUE, if the log will be written in a text file
        */
        virtual inline void SetUseLogTextFile(BOOL value);

        /**
        * Gets if the log should be written in a database
        *@return TRUE if the log should be written in a database, otherwise FALSE
        */
        virtual inline const BOOL GetUseLogDatabaseFile() const;

        /**
        * Sets if the log should be written in a database
        *@param value - if TRUE, the log will be written in a database
        */
        virtual inline void SetUseLogDatabaseFile(BOOL value);

        /**
        * Gets if the history should be kept on process
        *@return TRUE if the history should be kept on process, otherwise FALSE
        */
        virtual inline const BOOL GetKeepHistoryOnProcess() const;

        /**
        * Sets if the history should be kept on process
        *@param value - if TRUE, the history will be kept on process
        */
        virtual inline void SetKeepHistoryOnProcess(BOOL value);

        /**
        * Gets the history process database file name
        *@return the history process database file name
        */
        virtual inline const CString GetHistoryProcessDatabaseFile() const;

        /**
        * Gets the field definition initalization file name
        *@return the field definition initalization file name
        */
        virtual inline const CString GetFieldDefinitionIniFile() const;

        /**
        * Gets the normal template
        *@return the normal template
        */
        virtual inline const CString GetNormalTemplate() const;

        /**
        * Gets the normal process template
        *@return the normal process template
        */
        virtual inline const CString GetNormalProcessTemplate() const;

        /**
        * Gets the normal model template
        *@return the normal model template
        */
        virtual inline const CString GetNormalModelTemplate() const;

    protected:
        PSS_ServerOptions m_ServerOptions;
        CString           m_IniFile;

        /**
        * Saves the definition to initialization file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveDefinitionToIniFilePvt();

    private:
        int m_StatusCode;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Server(const PSS_Server& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Server& operator = (const PSS_Server& other);

        /**
        * Checks the server structure
        *@return TRUE on success, otherwise FALSE
        */
        BOOL CheckStructure();

        /**
        * Loads the server options
        *@return TRUE on success, otherwise FALSE
        */
        BOOL LoadOptions();
};

//---------------------------------------------------------------------------
// PSS_Server
//---------------------------------------------------------------------------
BOOL PSS_Server::IsSessionValid() const
{
    return (m_StatusCode == M_Srv_Success);
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetServerIniFile() const
{
    return m_IniFile;
}
//---------------------------------------------------------------------------
void PSS_Server::SetServerIniFile(const CString& value)
{
    m_IniFile = value;
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetRootPath() const
{
    return m_ServerOptions.GetRootPath();
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetTemplateDirectory() const
{
    return m_ServerOptions.GetTemplateDirectory();
}
//---------------------------------------------------------------------------
void PSS_Server::SetTemplateDirectory(const CString& value)
{
    m_ServerOptions.SetTemplateDirectory(value);
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetFileDirectory() const
{
    return m_ServerOptions.GetFileDirectory();
}
//---------------------------------------------------------------------------
void PSS_Server::SetFileDirectory(const CString& value)
{
    m_ServerOptions.SetFileDirectory(value);
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetGlobalFieldNameRepository() const
{
    return m_ServerOptions.GetGlobalFieldNameRepository();
}
//---------------------------------------------------------------------------
void PSS_Server::SetGlobalFieldNameRepository(const CString& value)
{
    m_ServerOptions.SetGlobalFieldNameRepository(value);
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetProcessTemplateDirectory() const
{
    return m_ServerOptions.GetProcessTemplateDirectory();
}
//---------------------------------------------------------------------------
void PSS_Server::SetProcessTemplateDirectory(const CString& value)
{
    m_ServerOptions.SetProcessTemplateDirectory(value);
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetModelTemplateDirectory() const
{
    return m_ServerOptions.GetModelTemplateDirectory();
}
//---------------------------------------------------------------------------
void PSS_Server::SetModelTemplateDirectory(const CString& value)
{
    m_ServerOptions.SetModelTemplateDirectory(value);
}
//---------------------------------------------------------------------------
CString PSS_Server::GetModelUnitDirectory() const
{
    return m_ServerOptions.GetModelUnitDirectory();
}
//---------------------------------------------------------------------------
void PSS_Server::SetModelUnitDirectory(const CString& value)
{
    m_ServerOptions.SetModelUnitDirectory(value);
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetLogFile() const
{
    return m_ServerOptions.GetLogFile();
}
//---------------------------------------------------------------------------
const BOOL PSS_Server::GetUseFolderNameAsFile() const
{
    return m_ServerOptions.GetUseFolderNameAsFile();
}
//---------------------------------------------------------------------------
void PSS_Server::SetUseFolderNameAsFile(BOOL value)
{
    m_ServerOptions.SetUseFolderNameAsFile(value);
}
//---------------------------------------------------------------------------
const BOOL PSS_Server::GetStoreUserFileByUser() const
{
    return m_ServerOptions.GetStoreUserFileByUser();
}
//---------------------------------------------------------------------------
void PSS_Server::SetStoreUserFileByUser(BOOL value)
{
    m_ServerOptions.SetStoreUserFileByUser(value);
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetSystemDirectory() const
{
    return m_ServerOptions.GetSystemDirectory();
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetEventDirectory() const
{
    return m_ServerOptions.GetEventDirectory();
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetInterfaceDirectory() const
{
    return m_ServerOptions.GetInterfaceDirectory();
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetLogDirectory() const
{
    return m_ServerOptions.GetLogDirectory();
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetUserDirectory() const
{
    return m_ServerOptions.GetUserDirectory();
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetUserDefinitionFile() const
{
    return m_ServerOptions.GetUserDefinitionFile();
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetLogDatabaseFile() const
{
    return m_ServerOptions.GetLogDatabaseFile();
}
//---------------------------------------------------------------------------
const BOOL PSS_Server::GetUseLogTextFile() const
{
    return m_ServerOptions.GetUseLogTextFile();
}
//---------------------------------------------------------------------------
void PSS_Server::SetUseLogTextFile(BOOL value)
{
    m_ServerOptions.SetUseLogTextFile(value);
}
//---------------------------------------------------------------------------
const BOOL PSS_Server::GetUseLogDatabaseFile() const
{
    return m_ServerOptions.GetUseLogDatabaseFile();
}
//---------------------------------------------------------------------------
void PSS_Server::SetUseLogDatabaseFile(BOOL value)
{
    m_ServerOptions.SetUseLogDatabaseFile(value);
}
//---------------------------------------------------------------------------
const BOOL PSS_Server::GetKeepHistoryOnProcess() const
{
    return m_ServerOptions.GetKeepHistoryOnProcess();
}
//---------------------------------------------------------------------------
void PSS_Server::SetKeepHistoryOnProcess(BOOL value)
{
    m_ServerOptions.SetKeepHistoryOnProcess(value);
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetHistoryProcessDatabaseFile() const
{
    return m_ServerOptions.GetHistoryProcessDatabaseFile();
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetFieldDefinitionIniFile() const
{
    return m_ServerOptions.GetFieldDefinitionIniFile();
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetNormalTemplate() const
{
    return m_ServerOptions.GetNormalTemplate();
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetNormalProcessTemplate() const
{
    return m_ServerOptions.GetNormalProcessTemplate();
}
//---------------------------------------------------------------------------
const CString PSS_Server::GetNormalModelTemplate() const
{
    return m_ServerOptions.GetNormalModelTemplate();
}
//---------------------------------------------------------------------------

/**
* Class attributes server
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CltServer : public PSS_Server
{
    public:
        /**
        * Constructor
        *@param iniFile - initialization file
        */
        PSS_CltServer(const CString& iniFile = _T(""));

        virtual ~PSS_CltServer();

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_CltServer(const PSS_CltServer& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_CltServer& operator = (const PSS_CltServer& other);
};

/**
* SRV server
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SrvServer : public PSS_Server
{
    public:
        /**
        * Constructor
        *@param iniFile - initialization file
        */
        PSS_SrvServer(const CString& iniFile = _T(""));

        virtual ~PSS_SrvServer();

        /**
        * Checks if the server is local
        *@return TRUE if the server is local, otherwise FALSE
        */
        virtual BOOL IsLocal() const;

        /**
        * Saves the definition to initialization file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveDefinitionToIniFile();

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SrvServer(const PSS_SrvServer& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_SrvServer& operator = (const PSS_SrvServer& other);
};

#endif
