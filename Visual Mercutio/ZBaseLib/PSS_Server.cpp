/****************************************************************************
 * ==> PSS_Server ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides several servers                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Server.h"

 // processsoft
#include "PSS_File.h"
#include "PSS_Directory.h"
#include "ZNetWork.h"

//---------------------------------------------------------------------------
// PSS_Server
//---------------------------------------------------------------------------
PSS_Server::PSS_Server(const CString& iniFile) :
    m_IniFile(iniFile),
    m_StatusCode(M_Srv_NotInitialized)
{}
//---------------------------------------------------------------------------
PSS_Server::PSS_Server(const PSS_Server& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Server::~PSS_Server()
{}
//---------------------------------------------------------------------------
const PSS_Server& PSS_Server::operator = (const PSS_Server& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_Server::IsLocal() const
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Server::OpenSession(BOOL checkStructure, BOOL forceNetwork)
{
    // no ini file name?
    if (m_IniFile.IsEmpty())
        return m_StatusCode = M_Srv_Corrupted;

    // check if the path and the ini file exist
    PSS_File file(m_IniFile);

    // check if the ini file exists
    if (!file.Exist())
    {
        if (!forceNetwork)
            return m_StatusCode = M_Srv_NotFound;

        // check if the path exists
        const CString path = file.GetFilePath();

        // open the connection
        ZUNetwork    net;
        CStringArray freeConnections;

        if (!net.GetFreeConnections(freeConnections))
            return m_StatusCode = M_Srv_AccessDenied;

        if (!net.Map(file.GetFilePath(), freeConnections.GetAt(0)))
            return m_StatusCode = M_Srv_AccessDenied;
    }

    // load the options
    if (!LoadOptions())
        return FALSE;

    // check if the structure is correct
    if (checkStructure)
        return CheckStructure();

    return m_StatusCode = M_Srv_Success;
}
//---------------------------------------------------------------------------
BOOL PSS_Server::OpenSession(const CString& iniFile, BOOL checkStructure)
{
    m_IniFile = iniFile;

    // check the filename to avoid improper filename
    PSS_File file(m_IniFile);
    file.Rebuild();
    m_IniFile = file.GetCompleteFileName();

    return OpenSession(checkStructure);
}
//---------------------------------------------------------------------------
BOOL PSS_Server::OpenSessionForceNetwork(const CString& iniFile, BOOL checkStructure)
{
    m_IniFile = iniFile;

    // check the filename to avoid improper filename
    PSS_File file(m_IniFile);
    file.Rebuild();
    m_IniFile = file.GetCompleteFileName();

    return OpenSession(checkStructure, TRUE);
}
//---------------------------------------------------------------------------
CString PSS_Server::CreateInitialEnvironment(const CString& serverDir, BOOL eraseExisting)
{
    if (!CreateEmptyServerObject(IsLocal(), serverDir))
        return _T("");

    if (!SaveDefinitionToIniFilePvt())
        return _T("");

    // return the ini file
    return m_IniFile;
}
//---------------------------------------------------------------------------
BOOL PSS_Server::CloseSession()
{
    // is the session already opened?
    if (!IsSessionValid())
        return TRUE;

    m_StatusCode = M_Srv_NotInitialized;

    // save the options, depends on the server type
    return SaveDefinitionToIniFile();
}
//---------------------------------------------------------------------------
BOOL PSS_Server::SaveDefinitionToIniFile()
{
    // in the base class, do nothing
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Server::CreateEmptyServerObject(BOOL           isLocalServer,
                                         const CString& rootPath,
                                         const CString& templateDir,
                                         const CString& fileDir,
                                         const CString& globalFieldNameRepository,
                                         const CString& processTemplateDir,
                                         const CString& modelTemplateDir,
                                         const CString& modelUnitDir,
                                         const CString& logFile,
                                         BOOL           useDatabase,
                                         BOOL           useFolderNameAsFile,
                                         BOOL           storeUserFileByUser,
                                         BOOL           keepHistoryOnProcess)
{
    // if no root directory
    const CString root = PSS_Directory::NormalizeDirectory(rootPath);

    if (root.IsEmpty())
        return FALSE;

    // build the ini file
    m_IniFile  = root + _T("\\");
    m_IniFile += (isLocalServer) ? CString(g_LocalIniFileName) : CString(g_GlobalIniFileName);

    return m_ServerOptions.CreateEmptyServerOption(rootPath,
                                                   templateDir,
                                                   fileDir,
                                                   globalFieldNameRepository,
                                                   processTemplateDir,
                                                   modelTemplateDir,
                                                   modelUnitDir,
                                                   logFile,
                                                   useDatabase,
                                                   useFolderNameAsFile,
                                                   storeUserFileByUser,
                                                   keepHistoryOnProcess);
}
//---------------------------------------------------------------------------
void PSS_Server::SetRootPath(const CString& value)
{
    // call the server option member function
    m_ServerOptions.SetRootPath(value);
}
//---------------------------------------------------------------------------
BOOL PSS_Server::CheckStructure()
{
    PSS_File file(m_IniFile);

    // check if the root path is empty
    if (m_ServerOptions.GetRootPath().IsEmpty())
    {
        // initialize the default structure
        const CString newIniFile = CreateInitialEnvironment(file.GetFilePath(), FALSE);

        if (newIniFile.IsEmpty())
            return M_Srv_EmptyInitFailed;

        // ok, created
        return TRUE;
    }

    // check if the ini file dir exists
    if (!PSS_Directory::Exist(file.GetFilePath()))
        return M_Srv_Corrupted;

    // check if the root path defined in the init is the same as the root path
    const CString dir1(PSS_Directory::NormalizeDirectory(m_ServerOptions.GetRootPath()));
    const CString dir2(PSS_Directory::NormalizeDirectory(file.GetFilePath()));

    if (dir1.CompareNoCase(dir2) != 0)
        return M_Srv_Moved;

    // check if the root path defined in the init exists
    if (!PSS_Directory::Exist(m_ServerOptions.GetRootPath()))
        return M_Srv_Moved;

    return M_Srv_Success;
}
//---------------------------------------------------------------------------
BOOL PSS_Server::LoadOptions()
{
    // initialize the global options
    m_ServerOptions.Create(m_IniFile, szGlobalSection);

    return m_ServerOptions.LoadOption();
}
//---------------------------------------------------------------------------
BOOL PSS_Server::SaveDefinitionToIniFilePvt()
{
    // initialize the Global Options
    m_ServerOptions.Create(m_IniFile, szGlobalSection);

    // assign the values
    m_ServerOptions.SetRootPath(GetRootPath());
    m_ServerOptions.SetTemplateDirectory(GetTemplateDirectory());
    m_ServerOptions.SetFileDirectory(GetFileDirectory());
    m_ServerOptions.SetGlobalFieldNameRepository(GetGlobalFieldNameRepository());
    m_ServerOptions.SetProcessTemplateDirectory(GetProcessTemplateDirectory());
    m_ServerOptions.SetModelTemplateDirectory(GetModelTemplateDirectory());
    m_ServerOptions.SetModelUnitDirectory(GetModelUnitDirectory());
    m_ServerOptions.SetUseFolderNameAsFile(GetUseFolderNameAsFile());
    m_ServerOptions.SetStoreUserFileByUser(GetStoreUserFileByUser());
    m_ServerOptions.SetUseLogTextFile(GetUseLogTextFile());
    m_ServerOptions.SetUseLogDatabaseFile(GetUseLogDatabaseFile());
    m_ServerOptions.SetKeepHistoryOnProcess(GetKeepHistoryOnProcess());

    // save the options
    return m_ServerOptions.SaveOption();
}
//---------------------------------------------------------------------------
// PSS_CltServer
//---------------------------------------------------------------------------
PSS_CltServer::PSS_CltServer(const CString& iniFile) :
    PSS_Server(iniFile)
{}
//---------------------------------------------------------------------------
PSS_CltServer::PSS_CltServer(const PSS_CltServer& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_CltServer::~PSS_CltServer()
{}
//---------------------------------------------------------------------------
const PSS_CltServer& PSS_CltServer::operator = (const PSS_CltServer& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
// PSS_CltServer
//---------------------------------------------------------------------------
PSS_SrvServer::PSS_SrvServer(const CString& iniFile) :
    PSS_Server(iniFile)
{}
//---------------------------------------------------------------------------
PSS_SrvServer::PSS_SrvServer(const PSS_SrvServer& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_SrvServer::~PSS_SrvServer()
{}
//---------------------------------------------------------------------------
const PSS_SrvServer& PSS_SrvServer::operator = (const PSS_SrvServer& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_SrvServer::IsLocal() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SrvServer::SaveDefinitionToIniFile()
{
    return PSS_Server::SaveDefinitionToIniFilePvt();
}
//---------------------------------------------------------------------------
