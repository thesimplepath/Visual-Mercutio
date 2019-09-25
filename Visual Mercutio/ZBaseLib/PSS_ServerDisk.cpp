/****************************************************************************
 * ==> PSS_ServerDisk ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a server disk                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ServerDisk.h"

// processsoft
#include "PSS_File.h"
#include "ZDirectory.h"

//---------------------------------------------------------------------------
// PSS_ServerDisk
//---------------------------------------------------------------------------
PSS_ServerDisk::PSS_ServerDisk(PSS_Server* pServer, const CString& emptyImageServerIniFile) :
    m_pServer(pServer),
    m_EmptyImageServerIniFile(emptyImageServerIniFile)
{
    // initialize the error messages
    m_ServerCreationStart.LoadString(IDS_SERVERCREATIONSTART);
    m_ServerCreationSuccess.LoadString(IDS_SERVERCREATIONSUCCESS);
    m_FailedToCreateServer.LoadString(IDS_SERVERCREATIONFAIL);
    m_FailedToCreateDir.LoadString(IDS_SERVERCREATIONDIRFAIL);
    m_FailedToCopyFile.LoadString(IDS_SERVERCREATIONFILEFAIL);
    m_FailedToInitializeParameters.LoadString(IDS_SERVERCREATIONPARAMFAIL);
}
//---------------------------------------------------------------------------
PSS_ServerDisk::PSS_ServerDisk(const PSS_ServerDisk& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ServerDisk::~PSS_ServerDisk()
{}
//---------------------------------------------------------------------------
const PSS_ServerDisk& PSS_ServerDisk::operator = (const PSS_ServerDisk& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ServerDisk::Initialize(PSS_Server* pServer, const CString& emptyImageServerIniFile)
{
    m_pServer                 = pServer;
    m_EmptyImageServerIniFile = emptyImageServerIniFile;
}
//---------------------------------------------------------------------------
bool PSS_ServerDisk::CreateServer()
{
    m_Log.Empty();
    m_Log += m_ServerCreationStart + "\n\n";

    if (!m_pServer)
    {
        m_Log += m_FailedToCreateServer;
        return false;
    }

    // open the empty server session
    if (!m_EmptyImageServer.OpenSession(m_EmptyImageServerIniFile))
        return false;

    // create the structure
    if (!CreateServerDirectoryStructure())
    {
        m_Log += m_FailedToCreateServer;
        return false;
    }

    // copy the empty server
    if (!CopyServerDirectory(m_EmptyImageServer))
    {
        m_Log += m_FailedToCreateServer;
        return false;
    }

    // save the definition to the ini file
    if (!m_pServer->SaveDefinitionToIniFile())
    {
        m_Log += m_FailedToInitializeParameters;
        m_Log += m_FailedToCreateServer;
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ServerDisk::CopyServer(PSS_Server& SourceServer)
{
    if (!m_pServer)
        return false;

    // open the source server session
    if (!SourceServer.OpenSession())
        return false;

    // copy the source server
    if (!CopyServerDirectory(SourceServer))
        return false;

    // save the definition to the ini file
    if (!m_pServer->SaveDefinitionToIniFile())
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ServerDisk::DeleteServer(bool checkStructure)
{
    if (!m_pServer)
        return false;

    // open a session on the server to delete
    if (!m_pServer->OpenSession(checkStructure))
        return false;

    // delete the server structure
    if (!ZDirectory::DeleteDirectory(m_pServer->GetRootPath(), TRUE, TRUE))
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ServerDisk::CreateServerDirectoryStructure()
{
    // create the root directory
    if (!ZDirectory::Exist(m_pServer->GetRootPath()) &&
        !ZDirectory::CreateDirectory(m_pServer->GetRootPath()))
    {
        CString text;
        text.Format(IDS_SERVERCREATIONDIRFAIL, m_pServer->GetRootPath());
        m_Log += text + "\n";
        return false;
    }

    // create the forms template directory
    if (!ZDirectory::Exist(m_pServer->GetTemplateDirectory()) &&
        !ZDirectory::CreateDirectory(m_pServer->GetTemplateDirectory()))
    {
        CString text;
        text.Format(IDS_SERVERCREATIONDIRFAIL, m_pServer->GetTemplateDirectory());
        m_Log += text + "\n";
        return false;
    }

    // create the process template directory
    if (!ZDirectory::Exist(m_pServer->GetProcessTemplateDirectory()) &&
        !ZDirectory::CreateDirectory(m_pServer->GetProcessTemplateDirectory()))
    {
        CString text;
        text.Format(IDS_SERVERCREATIONDIRFAIL, m_pServer->GetProcessTemplateDirectory());
        m_Log += text + "\n";
        return false;
    }

    // create the user file directory
    if (!ZDirectory::Exist(m_pServer->GetFileDirectory()) &&
        !ZDirectory::CreateDirectory(m_pServer->GetFileDirectory()))
    {
        CString text;
        text.Format(IDS_SERVERCREATIONDIRFAIL, m_pServer->GetFileDirectory());
        m_Log += text + "\n";
        return false;
    }

    // create the sytem directory
    if (!ZDirectory::Exist(m_pServer->GetSystemDirectory()) &&
        !ZDirectory::CreateDirectory(m_pServer->GetSystemDirectory()))
    {
        CString text;
        text.Format(IDS_SERVERCREATIONDIRFAIL, m_pServer->GetSystemDirectory());
        m_Log += text + "\n";
        return false;
    }

    // create the log directory
    if (!ZDirectory::Exist(m_pServer->GetLogDirectory()) &&
        !ZDirectory::CreateDirectory(m_pServer->GetLogDirectory()))
    {
        CString text;
        text.Format(IDS_SERVERCREATIONDIRFAIL, m_pServer->GetLogDirectory());
        m_Log += text + "\n";
        return false;
    }

    // create the event directory
    if (!ZDirectory::Exist(m_pServer->GetEventDirectory()) &&
        !ZDirectory::CreateDirectory(m_pServer->GetEventDirectory()))
    {
        CString text;
        text.Format(IDS_SERVERCREATIONDIRFAIL, m_pServer->GetEventDirectory());
        m_Log += text + "\n";
        return false;
    }

    // create the user directory
    if (!ZDirectory::Exist(m_pServer->GetUserDirectory()) &&
        !ZDirectory::CreateDirectory(m_pServer->GetUserDirectory()))
    {
        CString text;
        text.Format(IDS_SERVERCREATIONDIRFAIL, m_pServer->GetUserDirectory());
        m_Log += text + "\n";
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ServerDisk::CopyServerDirectory(PSS_Server& SourceServer)
{
    if (!m_pServer)
        return false;

    // the session should be already open for the source server
    if (!SourceServer.IsSessionValid())
        // if not, open it
        if (!SourceServer.OpenSession())
            return false;

    // copy all files, from all sub-directory
    return ZDirectory::CopyAllFileFromToDirectory(SourceServer.GetRootPath(), m_pServer->GetRootPath(), TRUE, TRUE, TRUE);
}
//---------------------------------------------------------------------------
