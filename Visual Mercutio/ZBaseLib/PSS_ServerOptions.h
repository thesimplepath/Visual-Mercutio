/****************************************************************************
 * ==> PSS_ServerOptions ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides the server options                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ServerOptionsH
#define PSS_ServerOptionsH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZUSystemOption.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Server options
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ServerOptions
{
    public:
        /**
        * Constructor
        *@param iniFile - initialization file
        *@param sectionName - section name
        */
        PSS_ServerOptions(const CString& iniFile = _T(""), const CString& sectionName = _T(""));

        virtual ~PSS_ServerOptions();

        /**
        * Creates the server options
        *@param iniFile - initialization file
        *@param sectionName - section name
        */
        virtual BOOL Create(const CString& iniFile = _T(""), const CString& sectionName = _T(""));

        /**
        * Creates the empty server options
        *@param rootPath - root path
        *@param templateDirectory - template directory
        *@param fileDirectory - file directory
        *@param globalFieldNameRepository - global field name repository
        *@param processTemplateDirectory - process template directory
        *@param modelTemplateDirectory - model template directory
        *@param modelUnitDirectory - model unit directory
        *@param logFile - log file
        *@param useDatabase - if TRUE, the database will be used
        *@param useFolderNameAsFile - if TRUE, folder name will be used as file
        *@param storeUserFileByUser - if TRUE, the user file will be stored by the user
        *@param keepHistoryOnProcess - if TRUE, the process history will be kept
        */
        virtual BOOL CreateEmptyServerOption(const CString& rootPath,
                                             const CString& templateDirectory         = _T(""),
                                             const CString& fileDirectory             = _T(""),
                                             const CString& globalFieldNameRepository = _T(""),
                                             const CString& processTemplateDirectory  = _T(""),
                                             const CString& modelTemplateDirectory    = _T(""),
                                             const CString& modelUnitDirectory        = _T(""),
                                             const CString& logFile                   = _T(""),
                                             const BOOL     useDatabase               = TRUE,
                                             const BOOL     useFolderNameAsFile       = TRUE,
                                             const BOOL     storeUserFileByUser       = FALSE,
                                             const BOOL     keepHistoryOnProcess      = TRUE);

        /**
        * Loads the options
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadOption();

        /**
        * Saves the options
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveOption();

        /**
        * Sets the ini file
        *@param fileName - init file name
        */
        virtual inline void SetIniFile(const CString& fileName);

        /**
        * Gets the root path
        *@return the root path
        */
        virtual inline const CString GetRootPath() const;

        /**
        * Sets the root path
        *@param value - the root path
        */
        virtual void SetRootPath(const CString& value);

        /**
        * Gets the template directory
        *@return the template directory
        */
        virtual inline const CString GetTemplateDirectory() const;

        /**
        * Sets the template directory
        *@param value - the template directory
        */
        virtual inline void SetTemplateDirectory(const CString& value);

        /**
        * Gets the file directory
        *@return the file directory
        */
        virtual inline const CString GetFileDirectory() const;

        /**
        * Sets the file directory
        *@value - the file directory
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
        * Gets the log file location
        *@return the log file location
        */
        virtual inline const CString GetLogFile() const;

        /**
        * Sets the log file location
        *@param value - the log file location
        */
        virtual inline void SetLogFile(const CString& value);

        /**
        * Gets if the folder name should be used as a file
        *@return TRUE if the folder name should be used as a file, otherwise FALSE
        */
        virtual inline const BOOL GetUseFolderNameAsFile() const;

        /**
        * Sets if the folder name should be used as a file
        *@param if TRUE, the folder name should be used as a file
        */
        virtual inline void SetUseFolderNameAsFile(BOOL value);

        /**
        * Gets if the user file should be stored by the user
        *@return TRUE if the user file should be stored by the user, otherwise FALSE
        */
        virtual inline const BOOL GetStoreUserFileByUser() const;

        /**
        * Sets if the user file should be stored by the user
        *@param valie - if TRUE, the user file should be stored by the user, otherwise FALSE
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
        * Gets the field definition ini file
        *@return the field definition ini file
        */
        virtual inline const CString& GetFieldDefinitionIniFile() const;

        /**
        * Gets the user definition file name
        *@return the user definition file name
        */
        virtual inline const CString GetUserDefinitionFile() const;

        /**
        * Gets the database file name
        *@return the database file name
        */
        virtual inline const CString GetLogDatabaseFile() const;

        /**
        * Gets if the log text file is used
        *@return TRUE if the log text file is used, otherwise FALSE
        */
        virtual inline const BOOL GetUseLogTextFile() const;

        /**
        * Sets if the log text file is used
        *@param value - if TRUE, if the log text file is used
        */
        virtual inline void SetUseLogTextFile(BOOL value);

        /**
        * Gets if the log database file is used
        *@return TRUE if the log database file is used, otherwise FALSE
        */
        virtual inline const BOOL GetUseLogDatabaseFile() const;

        /**
        * Sets if the log database file is used
        *@param value - if TRUE, if the log database file is used
        */
        virtual inline void SetUseLogDatabaseFile(BOOL value);

        /**
        * Gets if the the process history should be kept
        *@return TRUE if the the process history should be kept, otherwise FALSE
        */
        virtual inline const BOOL GetKeepHistoryOnProcess() const;

        /**
        * Sets if the the process history should be kept
        *@param value - if TRUE, the the process history should be kept
        */
        virtual inline void SetKeepHistoryOnProcess(BOOL value);

        /**
        * Gets the history process database file name
        *@return the history process database file name
        */
        virtual inline const CString GetHistoryProcessDatabaseFile() const;

        /**
        * Gets the model template directory
        *@return the model template directory
        */
        virtual inline const CString GetModelTemplateDirectory() const;

        /**
        * Sets the model template directory
        *@param value - the model template directory
        */
        virtual inline void SetModelTemplateDirectory(const CString& value);

        /**
        * Gets the model unit directory
        *@return the model unit directory
        */
        virtual inline CString GetModelUnitDirectory() const;

        /**
        * Sets the model unit directory
        *@param value - the model unit directory
        */
        virtual inline void SetModelUnitDirectory(const CString& value);

        /**
        * Gets the normal template
        *@return the normal template
        */
        virtual inline CString GetNormalTemplate() const;

        /**
        * Gets the normal process template
        *@return the normal process template
        */
        virtual inline CString GetNormalProcessTemplate() const;

        /**
        * Gets the normal model template
        *@return the normal model template
        */
        virtual inline CString GetNormalModelTemplate() const;

    private:
        ZUSystemOption m_Option;
        CString        m_RootPath;
        CString        m_TemplateDirectory;
        CString        m_FileDirectory;
        CString        m_GlobalFieldNameRepository;
        CString        m_ProcessTemplateDirectory;
        CString        m_LogFile;
        CString        m_SystemDirectory;
        CString        m_EventDirectory;
        CString        m_InterfaceDirectory;
        CString        m_LogDirectory;
        CString        m_UserDirectory;
        CString        m_FieldDefinitionIniFile;
        CString        m_UserDefinitionFile;
        CString        m_LogDatabaseFile;
        CString        m_HistoryProcessDatabaseFile;
        CString        m_ModelTemplateDirectory;
        CString        m_ModelUnitDirectory;
        BOOL           m_UseFolderNameAsFile;
        BOOL           m_StoreUserFileByUser;
        BOOL           m_UseLogTextFile;
        BOOL           m_UseLogDatabaseFile;
        BOOL           m_KeepHistoryOnProcess;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ServerOptions(const PSS_ServerOptions& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ServerOptions& operator = (const PSS_ServerOptions& other);
};

//---------------------------------------------------------------------------
// PSS_ServerOptions
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetIniFile(const CString& fileName)
{
    m_Option.SetIniFile(fileName);
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetRootPath() const
{
    return m_RootPath;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetTemplateDirectory() const
{
    return m_TemplateDirectory;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetTemplateDirectory(const CString& value)
{
    m_TemplateDirectory = value;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetFileDirectory() const
{
    return m_FileDirectory;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetFileDirectory(const CString& value)
{
    m_FileDirectory = value;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetGlobalFieldNameRepository() const
{
    return m_GlobalFieldNameRepository;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetGlobalFieldNameRepository(const CString& value)
{
    m_GlobalFieldNameRepository = value;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetProcessTemplateDirectory() const
{
    return m_ProcessTemplateDirectory;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetProcessTemplateDirectory(const CString& value)
{
    m_ProcessTemplateDirectory = value;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetLogFile() const
{
    return m_LogFile;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetLogFile(const CString& value)
{
    m_LogFile = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ServerOptions::GetUseFolderNameAsFile() const
{
    return m_UseFolderNameAsFile;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetUseFolderNameAsFile(BOOL value)
{
    m_UseFolderNameAsFile = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ServerOptions::GetStoreUserFileByUser() const
{
    return m_StoreUserFileByUser;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetStoreUserFileByUser(BOOL value)
{
    m_StoreUserFileByUser = value;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetSystemDirectory() const
{
    return m_SystemDirectory;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetEventDirectory() const
{
    return m_EventDirectory;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetInterfaceDirectory() const
{
    return m_InterfaceDirectory;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetLogDirectory() const
{
    return m_LogDirectory;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetUserDirectory() const
{
    return m_UserDirectory;
}
//---------------------------------------------------------------------------
const CString& PSS_ServerOptions::GetFieldDefinitionIniFile() const
{
    return m_FieldDefinitionIniFile;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetUserDefinitionFile() const
{
    return m_UserDefinitionFile;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetLogDatabaseFile() const
{
    return m_LogDatabaseFile;
}
//---------------------------------------------------------------------------
const BOOL PSS_ServerOptions::GetUseLogTextFile() const
{
    return m_UseLogTextFile;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetUseLogTextFile(BOOL value)
{
    m_UseLogTextFile = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ServerOptions::GetUseLogDatabaseFile() const
{
    return m_UseLogDatabaseFile;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetUseLogDatabaseFile(BOOL value)
{
    m_UseLogDatabaseFile = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ServerOptions::GetKeepHistoryOnProcess() const
{
    return m_KeepHistoryOnProcess;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetKeepHistoryOnProcess(BOOL value)
{
    m_KeepHistoryOnProcess = value;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetHistoryProcessDatabaseFile() const
{
    return m_HistoryProcessDatabaseFile;
}
//---------------------------------------------------------------------------
const CString PSS_ServerOptions::GetModelTemplateDirectory() const
{
    return m_ModelTemplateDirectory;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetModelTemplateDirectory(const CString& value)
{
    m_ModelTemplateDirectory = value;
}
//---------------------------------------------------------------------------
CString PSS_ServerOptions::GetModelUnitDirectory() const
{
    return m_ModelUnitDirectory;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetModelUnitDirectory(const CString& value)
{
    m_ModelUnitDirectory = value;
}
//---------------------------------------------------------------------------
CString PSS_ServerOptions::GetNormalTemplate() const
{
    return GetSystemDirectory() + _T("\\") + g_NormalTemplateFileName;
}
//---------------------------------------------------------------------------
CString PSS_ServerOptions::GetNormalProcessTemplate() const
{
    return GetSystemDirectory() + _T("\\") + g_NormalProcessTemplateFileName;
}
//---------------------------------------------------------------------------
CString PSS_ServerOptions::GetNormalModelTemplate() const
{
    return GetSystemDirectory() + _T("\\") + g_NormalModelTemplateFileName;
}
//---------------------------------------------------------------------------

#endif
