/****************************************************************************
 * ==> PSS_ServerOptions ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides the server options                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ServerOptions.h"

// processsoft
#include "PSS_Directory.h"

//---------------------------------------------------------------------------
// PSS_ServerOptions
//---------------------------------------------------------------------------
PSS_ServerOptions::PSS_ServerOptions(const CString& iniFile, const CString& sectionName) :
    m_UseFolderNameAsFile(FALSE),
    m_StoreUserFileByUser(FALSE),
    m_UseLogTextFile(FALSE),
    m_UseLogDatabaseFile(FALSE),
    m_KeepHistoryOnProcess(FALSE)
{
    Create(iniFile, sectionName);
}
//---------------------------------------------------------------------------
PSS_ServerOptions::PSS_ServerOptions(const PSS_ServerOptions& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ServerOptions::~PSS_ServerOptions()
{}
//---------------------------------------------------------------------------
const PSS_ServerOptions& PSS_ServerOptions::operator = (const PSS_ServerOptions& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_ServerOptions::Create(const CString& iniFile, const CString& sectionName)
{
    m_Option.Create(iniFile, sectionName);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ServerOptions::CreateEmptyServerOption(const CString& rootPath,
                                                const CString& templateDirectory,
                                                const CString& fileDirectory,
                                                const CString& globalFieldNameRepository,
                                                const CString& processTemplateDirectory,
                                                const CString& modelTemplateDirectory,
                                                const CString& modelUnitDirectory,
                                                const CString& logFile,
                                                const BOOL     useDatabase,
                                                const BOOL     useFolderNameAsFile,
                                                const BOOL     storeUserFileByUser,
                                                const BOOL     keepHistoryOnProcess)
{
    // if no root directory
    const CString root = PSS_Directory::NormalizeDirectory(rootPath);

    if (root.IsEmpty())
        return FALSE;

    // set the root path
    SetRootPath(root);

    // set the values
    SetTemplateDirectory        (templateDirectory.IsEmpty()         ? root              + _T("\\Template") : templateDirectory);
    SetFileDirectory            (fileDirectory.IsEmpty()             ? root              + _T("\\Files")    : fileDirectory);
    SetGlobalFieldNameRepository(globalFieldNameRepository.IsEmpty() ? m_SystemDirectory + _T("\\Def.pld")  : globalFieldNameRepository);
    SetProcessTemplateDirectory (processTemplateDirectory.IsEmpty()  ? root              + _T("\\ProcTmpl") : processTemplateDirectory);
    SetModelTemplateDirectory   (modelTemplateDirectory.IsEmpty()    ? root              + _T("\\Model")    : modelTemplateDirectory);
    SetModelUnitDirectory       (modelUnitDirectory.IsEmpty()        ? root              + _T("\\Units")    : modelUnitDirectory);
    SetUseFolderNameAsFile      (useFolderNameAsFile);
    SetStoreUserFileByUser      (storeUserFileByUser);
    SetUseLogTextFile           (!useDatabase);
    SetUseLogDatabaseFile       (useDatabase);
    SetKeepHistoryOnProcess     (keepHistoryOnProcess);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ServerOptions::LoadOption()
{
    SetRootPath(m_Option.ReadOption(szRootEntry, _T("")));

    m_TemplateDirectory         = PSS_Directory::NormalizeDirectory(m_Option.ReadOption(szTemplateDirEntry,             _T("")), true);
    m_FileDirectory             = PSS_Directory::NormalizeDirectory(m_Option.ReadOption(szFileDirEntry,                 _T("")), true);
    m_ProcessTemplateDirectory  = PSS_Directory::NormalizeDirectory(m_Option.ReadOption(szProcessTemplateDirEntry,      _T("")), true);
    m_ModelTemplateDirectory    = PSS_Directory::NormalizeDirectory(m_Option.ReadOption(szModelTemplateDirEntry,        _T("")), true);
    m_ModelUnitDirectory        = PSS_Directory::NormalizeDirectory(m_Option.ReadOption(szModelUnitDirEntry,            _T("")), true);
    m_GlobalFieldNameRepository =                                   m_Option.ReadOption(szGlobalFieldRepositoryEntry,   _T(""));
    m_UseFolderNameAsFile       =                                   m_Option.ReadOption(szUseFolderNameAsFileName,      1);
    m_StoreUserFileByUser       =                                   m_Option.ReadOption(szStoreUserFileByUser,          0);
    m_UseLogTextFile            =                                   m_Option.ReadOption(szUseLogTextFile,               1);
    m_UseLogDatabaseFile        =                                   m_Option.ReadOption(szUseLogDatabaseFile,           0);
    m_KeepHistoryOnProcess      =                                   m_Option.ReadOption(szKeepHistoryProcessOnDatabase, 1);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ServerOptions::SaveOption()
{
    m_Option.WriteOption(szRootEntry,                    m_RootPath);
    m_Option.WriteOption(szTemplateDirEntry,             m_TemplateDirectory);
    m_Option.WriteOption(szFileDirEntry,                 m_FileDirectory);
    m_Option.WriteOption(szGlobalFieldRepositoryEntry,   m_GlobalFieldNameRepository);
    m_Option.WriteOption(szProcessTemplateDirEntry,      m_ProcessTemplateDirectory);
    m_Option.WriteOption(szModelTemplateDirEntry,        m_ModelTemplateDirectory);
    m_Option.WriteOption(szModelUnitDirEntry,            m_ModelUnitDirectory);
    m_Option.WriteOption(szUseFolderNameAsFileName,      m_UseFolderNameAsFile);
    m_Option.WriteOption(szStoreUserFileByUser,          m_StoreUserFileByUser);
    m_Option.WriteOption(szUseLogTextFile,               m_UseLogTextFile);
    m_Option.WriteOption(szUseLogDatabaseFile,           m_UseLogDatabaseFile);
    m_Option.WriteOption(szKeepHistoryProcessOnDatabase, m_KeepHistoryOnProcess);

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ServerOptions::SetRootPath(const CString& value)
{
    m_RootPath = value;

    if (m_RootPath.IsEmpty())
        return;

    PSS_Directory::NormalizeDirectory(m_RootPath);

    // build directories
    m_SystemDirectory            = m_RootPath        + _T("\\System");
    m_EventDirectory             = m_SystemDirectory + _T("\\Events");
    m_InterfaceDirectory         = m_SystemDirectory + _T("\\Interfac");
    m_LogDirectory               = m_SystemDirectory + _T("\\Log");
    m_UserDirectory              = m_SystemDirectory + _T("\\Users");
    m_ModelTemplateDirectory     = m_RootPath        + _T("\\Model");
    m_ModelUnitDirectory         = m_RootPath        + _T("\\Units");
    m_UserDefinitionFile         = m_SystemDirectory + _T("\\") + g_UserDefinitionFileName;
    m_LogDatabaseFile            = m_LogDirectory    + _T("\\") + g_ActivityLogDatabase;
    m_LogFile                    = m_LogDirectory    + _T("\\") + g_ActivityLogFileName;
    m_HistoryProcessDatabaseFile = m_LogDirectory    + _T("\\") + g_HistoryProcessDatabase;
    m_FieldDefinitionIniFile     = m_RootPath        + _T("\\System\\FieldDef.ini");
}
//---------------------------------------------------------------------------
