/****************************************************************************
 * ==> PSS_ActivityLogDatabase ---------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity log database                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityLogDatabase.h"

// processsoft
#include "zBaseLib\PSS_Date.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ActivityLogDatabase
//---------------------------------------------------------------------------
PSS_ActivityLogDatabase::PSS_ActivityLogDatabase(const CString& fileName) :
    m_pRecordSet(NULL),
    m_FileName(fileName)
{}
//---------------------------------------------------------------------------
PSS_ActivityLogDatabase::PSS_ActivityLogDatabase(const PSS_ActivityLogDatabase& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityLogDatabase::~PSS_ActivityLogDatabase()
{
    // NOTE the fully qualified name is required here to avoid any pure virtual function call issues
    PSS_ActivityLogDatabase::Close();
}
//---------------------------------------------------------------------------
const PSS_ActivityLogDatabase& PSS_ActivityLogDatabase::operator = (const PSS_ActivityLogDatabase& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ActivityLogDatabase::Create(const CString& fileName)
{
    m_FileName = fileName;

    if (m_FileName.IsEmpty())
        return;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogDatabase::AppendToLog(const PSS_ActivityEvent& activityEvent)
{
    if (!m_Database.IsOpen())
        OpenWrite();

    if (!m_pRecordSet)
        return FALSE;

    try
    {
        if (!m_pRecordSet->IsOpen())
            m_pRecordSet->Open(dbOpenDynaset, NULL, dbAppendOnly);

        if (m_pRecordSet->IsOpen() && m_pRecordSet->CanUpdate())
            m_pRecordSet->AddNew();
    }
    catch (CDaoException&)
    {
        return FALSE;
    }

    const PSS_Date currentDate = PSS_Date::GetToday();

    // populate the table record
    m_pRecordSet->SetDate                (currentDate);
    m_pRecordSet->SetEventType           (activityEvent.GetActivityEventTypeString());
    m_pRecordSet->SetProcessFilename     (activityEvent.GetProcessFileName());
    m_pRecordSet->SetFormDataFilename    (activityEvent.GetExchangeDataFileName());
    m_pRecordSet->SetProcessDataFilename (activityEvent.GetProcessExchangeDataFileName());
    m_pRecordSet->SetFolderName          (activityEvent.GetFolderName());
    m_pRecordSet->SetProcessName         (activityEvent.GetProcessName());
    m_pRecordSet->SetProcessCreationDate (activityEvent.GetProcessCreationDate());
    m_pRecordSet->SetProcessDueDate      (activityEvent.GetProcessDueDate());
    m_pRecordSet->SetActivityType        (activityEvent.GetActivityType());
    m_pRecordSet->SetActivityName        (activityEvent.GetActivityName());
    m_pRecordSet->SetActivityCreationDate(activityEvent.GetActivityCreationDate());
    m_pRecordSet->SetActivityDueDate     (activityEvent.GetActivityDueDate());
    m_pRecordSet->SetActivityStatus      (activityEvent.GetActivityStatus());
    m_pRecordSet->SetSender              (activityEvent.GetSender());
    m_pRecordSet->SetReceiver            (activityEvent.GetReceiver());
    m_pRecordSet->SetComments            (activityEvent.GetComments());
    m_pRecordSet->SetInBackup            (activityEvent.GetIsInBackup());

    try
    {
        // update the new inserted recordset
        m_pRecordSet->Update();
        m_pRecordSet->Close();
    }
    catch (CDaoException&)
    {
        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogDatabase::ClearLog()
{
    if (!m_Database.IsOpen())
        OpenWrite();

    if (!m_pRecordSet)
        return FALSE;

    try
    {
        // build the query statement
        CString query  = "DELETE ";
        query         += g_ActivityLogTableName;
        query         += ".* FROM ";
        query         += g_ActivityLogTableName;
        query         += ";";

        // execute the query
        m_Database.Execute(query);
    }
    catch (CDaoException&)
    {
        Close();
        return FALSE;
    }

    Close();
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogDatabase::Close()
{
    TRY
    {
        if (m_pRecordSet)
        {
            if (m_pRecordSet->IsOpen())
                m_pRecordSet->Close();

            delete m_pRecordSet;
            m_pRecordSet = NULL;
        }

        if (m_Database.IsOpen())
            m_Database.Close();
    }
    CATCH(CDaoException, e)
    {
        // do nothing
        return FALSE;
    }
    END_CATCH

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogDatabase::OpenRead()
{
    // open the database and the recordset
    try
    {
        // close the previously opened database, if any
        Close();

        m_Database.Open(m_FileName, FALSE, TRUE);
        m_pRecordSet = new ZDActivityLogRecordset(&m_Database, m_FileName);

        if (m_pRecordSet)
            m_pRecordSet->Open(dbOpenSnapshot, NULL, dbReadOnly);
        else
        {
            Close();
            return FALSE;
        }
    }
    catch (CDaoException&)
    {
        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogDatabase::OpenWrite()
{
    // open the database and the recordset
    try
    {
        // close the previously opened database, if any
        Close();

        m_Database.Open(m_FileName);
        m_pRecordSet = new ZDActivityLogRecordset(&m_Database, m_FileName);

        if (m_pRecordSet)
            m_pRecordSet->Open(dbOpenDynaset, NULL, dbAppendOnly);
        else
        {
            Close();
            return FALSE;
        }
    }
    catch (CDaoException&)
    {
        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
