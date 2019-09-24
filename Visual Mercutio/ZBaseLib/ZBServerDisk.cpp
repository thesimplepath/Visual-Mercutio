//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//  Source file: ZBServerDisk.cpp

#include <StdAfx.h>

// ZBServerDisk
#include "ZBServerDisk.h"
#include "PSS_File.h"
#include "ZDirectory.h"

// Class ZBServerDisk 


ZBServerDisk::ZBServerDisk (PSS_Server* pServer /*= NULL*/, const CString EmptyImageServerIniFile /*= ""*/ )
: m_pServer(pServer), m_EmptyImageServerIniFile(EmptyImageServerIniFile)
{
    m_ServerCreationStart.LoadString( IDS_SERVERCREATIONSTART );
    m_ServerCreationSuccess.LoadString( IDS_SERVERCREATIONSUCCESS );
    m_FailedToCreateServer.LoadString( IDS_SERVERCREATIONFAIL );

    m_FailedToCreateDir.LoadString( IDS_SERVERCREATIONDIRFAIL );
    m_FailedToCopyFile.LoadString( IDS_SERVERCREATIONFILEFAIL );

    m_FailedToInitializeParameters.LoadString( IDS_SERVERCREATIONPARAMFAIL );
}

ZBServerDisk::~ZBServerDisk()
{
}

void ZBServerDisk::Initialize(PSS_Server* pServer, const CString EmptyImageServerIniFile /*= ""*/ )
{
    m_pServer = pServer;
    m_EmptyImageServerIniFile = EmptyImageServerIniFile;
}


bool ZBServerDisk::DeleteServer( bool CheckStructure /*= true*/ )
{
    if (!m_pServer)
        return false;

    if (!m_pServer->OpenSession(CheckStructure))
        return false;

    if (!ZDirectory::DeleteDirectory( m_pServer->GetRootPath(), TRUE, TRUE ))
        return false;
    return true;
}

bool ZBServerDisk::CreateServer()
{
    m_Log.Empty();
    m_Log += m_ServerCreationStart + "\n\n";
    if (!m_pServer)
    {
        m_Log += m_FailedToCreateServer;
        return false;
    }
    // Open the session of the empty server
    if (!m_EmptyImageServer.OpenSession( m_EmptyImageServerIniFile ))
        return false;
    // Create the structure
    if (!CreateServerDirectoryStructure())
    {
        m_Log += m_FailedToCreateServer;
        return false;
    }
    // Copy the empty server
    if (!CopyServerDirectory( m_EmptyImageServer ))
    {
        m_Log += m_FailedToCreateServer;
        return false;
    }
    // Save the definition to the ini file
    if (!m_pServer->SaveDefinitionToIniFile())
    {
        m_Log += m_FailedToInitializeParameters;
        m_Log += m_FailedToCreateServer;
        return false;
    }
    // No error
    return true;
}


bool ZBServerDisk::CopyServer(PSS_Server& SourceServer )
{
    if (!m_pServer)
        return false;
    // Open the source server session
    if (!SourceServer.OpenSession())
        return false;
    // Copy the source server
    if (!CopyServerDirectory( SourceServer ))
        return false;
    // Save the definition to the ini file
    if (!m_pServer->SaveDefinitionToIniFile())
        return false;
    // No error
    return true;
}


bool ZBServerDisk::CopyServerDirectory(PSS_Server& SourceServer )
{
    if (!m_pServer)
        return false;
    // The session should be already open for source server
    if (!SourceServer.IsSessionValid())
    {
        // If not, try to open it
        if (!SourceServer.OpenSession())
            return false;
    }
    // Copy all files, from all sub-directory
    if (!ZDirectory::CopyAllFileFromToDirectory( SourceServer.GetRootPath(), 
                                                 m_pServer->GetRootPath(), 
                                                 TRUE,    // Overwrite files
                                                 TRUE,    // Include sub-directory
                                                 TRUE))    // Create destination dir, if does not exits
        return false;
    // No error
    return true;
}


bool ZBServerDisk::CreateServerDirectoryStructure()
{
    // Create the root directory
    if (!ZDirectory::Exist( m_pServer->GetRootPath() ) && 
        !ZDirectory::CreateDirectory( m_pServer->GetRootPath() ))
    {
        CString    Text;
        Text.Format( IDS_SERVERCREATIONDIRFAIL, m_pServer->GetRootPath() );
        m_Log += Text + "\n";
        return false;
    }
    // Create the forms template directory
    if (!ZDirectory::Exist( m_pServer->GetTemplateDirectory() ) &&
        !ZDirectory::CreateDirectory( m_pServer->GetTemplateDirectory() ))
    {
        CString    Text;
        Text.Format( IDS_SERVERCREATIONDIRFAIL, m_pServer->GetTemplateDirectory() );
        m_Log += Text + "\n";
        return false;
    }
    // Create the process template directory
    if (!ZDirectory::Exist( m_pServer->GetProcessTemplateDirectory() ) &&
        !ZDirectory::CreateDirectory( m_pServer->GetProcessTemplateDirectory() ))
    {
        CString    Text;
        Text.Format( IDS_SERVERCREATIONDIRFAIL, m_pServer->GetProcessTemplateDirectory() );
        m_Log += Text + "\n";
        return false;
    }
    // Create the user file directory
    if (!ZDirectory::Exist( m_pServer->GetFileDirectory() ) &&
        !ZDirectory::CreateDirectory( m_pServer->GetFileDirectory() ))
    {
        CString    Text;
        Text.Format( IDS_SERVERCREATIONDIRFAIL, m_pServer->GetFileDirectory() );
        m_Log += Text + "\n";
        return false;
    }
    // Create the sytem directory
    if (!ZDirectory::Exist( m_pServer->GetSystemDirectory() ) &&
        !ZDirectory::CreateDirectory( m_pServer->GetSystemDirectory() ))
    {
        CString    Text;
        Text.Format( IDS_SERVERCREATIONDIRFAIL, m_pServer->GetSystemDirectory() );
        m_Log += Text + "\n";
        return false;
    }
    // Create the log directory
    if (!ZDirectory::Exist( m_pServer->GetLogDirectory() ) &&
        !ZDirectory::CreateDirectory( m_pServer->GetLogDirectory() ))
    {
        CString    Text;
        Text.Format( IDS_SERVERCREATIONDIRFAIL, m_pServer->GetLogDirectory() );
        m_Log += Text + "\n";
        return false;
    }
    // Create the event directory
    if (!ZDirectory::Exist( m_pServer->GetEventDirectory() ) &&
        !ZDirectory::CreateDirectory( m_pServer->GetEventDirectory() ))
    {
        CString    Text;
        Text.Format( IDS_SERVERCREATIONDIRFAIL, m_pServer->GetEventDirectory() );
        m_Log += Text + "\n";
        return false;
    }
    // Create the user directory
    if (!ZDirectory::Exist( m_pServer->GetUserDirectory() ) &&
        !ZDirectory::CreateDirectory( m_pServer->GetUserDirectory() ))
    {
        CString    Text;
        Text.Format( IDS_SERVERCREATIONDIRFAIL, m_pServer->GetUserDirectory() );
        m_Log += Text + "\n";
        return false;
    }
    return true;
}