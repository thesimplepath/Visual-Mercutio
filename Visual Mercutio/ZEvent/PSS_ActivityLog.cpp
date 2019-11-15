/****************************************************************************
 * ==> PSS_ActivityLog -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity logger                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityLog.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ActivityLog
//---------------------------------------------------------------------------
PSS_ActivityLog::PSS_ActivityLog(const CString& fileName, BOOL useDatabase) :
    m_pActivityLogDatabase(NULL),
    m_pActivityLogFile(NULL),
    m_FileName(fileName),
    m_UseDatabase(useDatabase)
{}
//---------------------------------------------------------------------------
PSS_ActivityLog::PSS_ActivityLog(const PSS_ActivityLog& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityLog::~PSS_ActivityLog()
{
    if (m_UseDatabase && m_pActivityLogDatabase)
    {
        m_pActivityLogDatabase->Close();
        delete m_pActivityLogDatabase;
    }
    else
    if (m_pActivityLogFile)
    {
        m_pActivityLogFile->Close();
        delete m_pActivityLogFile;
    }
}
//---------------------------------------------------------------------------
const PSS_ActivityLog& PSS_ActivityLog::operator = (const PSS_ActivityLog& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLog::Create(const CString& fileName, BOOL useDatabase)
{
    m_FileName    = fileName;
    m_UseDatabase = useDatabase;

    return Initialize();
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLog::Initialize()
{
    if (m_FileName.IsEmpty())
        return FALSE;

    if (m_UseDatabase)
        m_pActivityLogDatabase = new PSS_ActivityLogDatabase(m_FileName);
    else
        m_pActivityLogFile = new PSS_ActivityLogFile(m_FileName);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLog::AppendToLog(const PSS_ActivityEvent& activityEvent)
{
    if (m_UseDatabase && m_pActivityLogDatabase)
        return m_pActivityLogDatabase->AppendToLog(activityEvent);
    else
    if (m_pActivityLogFile)
        return m_pActivityLogFile->AppendToLog(activityEvent);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLog::ClearLog()
{
    if (m_UseDatabase && m_pActivityLogDatabase)
        return m_pActivityLogDatabase->ClearLog();
    else
    if (m_pActivityLogFile)
        return m_pActivityLogFile->ClearLog();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLog::Close()
{
    if (m_UseDatabase && m_pActivityLogDatabase)
        return m_pActivityLogDatabase->Close();
    else
    if (m_pActivityLogFile)
        return m_pActivityLogFile->Close();

    return FALSE;
}
//---------------------------------------------------------------------------
