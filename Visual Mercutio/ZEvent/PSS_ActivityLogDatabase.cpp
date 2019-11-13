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
    m_pRecordset(NULL),
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

    if (!m_pRecordset)
        return FALSE;

    try
    {
        if (!m_pRecordset->IsOpen())
            m_pRecordset->Open(dbOpenDynaset, NULL, dbAppendOnly);

        if (m_pRecordset->IsOpen() && m_pRecordset->CanUpdate())
            m_pRecordset->AddNew();
    }
    catch (CDaoException&)
    {
        return FALSE;
    }

    const PSS_Date currentDate = PSS_Date::GetToday();

    // populate the table record
    m_pRecordset->SetDate                (currentDate);
    m_pRecordset->SetEventType           (activityEvent.GetActivityEventTypeString());
    m_pRecordset->SetProcessFilename     (activityEvent.GetProcessFileName());
    m_pRecordset->SetFormDataFilename    (activityEvent.GetExchangeDataFileName());
    m_pRecordset->SetProcessDataFilename (activityEvent.GetProcessExchangeDataFileName());
    m_pRecordset->SetFolderName          (activityEvent.GetFolderName());
    m_pRecordset->SetProcessName         (activityEvent.GetProcessName());
    m_pRecordset->SetProcessCreationDate (activityEvent.GetProcessCreationDate());
    m_pRecordset->SetProcessDueDate      (activityEvent.GetProcessDueDate());
    m_pRecordset->SetActivityType        (activityEvent.GetActivityType());
    m_pRecordset->SetActivityName        (activityEvent.GetActivityName());
    m_pRecordset->SetActivityCreationDate(activityEvent.GetActivityCreationDate());
    m_pRecordset->SetActivityDueDate     (activityEvent.GetActivityDueDate());
    m_pRecordset->SetActivityStatus      (activityEvent.GetActivityStatus());
    m_pRecordset->SetSender              (activityEvent.GetSender());
    m_pRecordset->SetReceiver            (activityEvent.GetReceiver());
    m_pRecordset->SetComments            (activityEvent.GetComments());
    m_pRecordset->SetInBackup            (activityEvent.GetIsInBackup());

    try
    {
        // update the new inserted recordset
        m_pRecordset->Update();
        m_pRecordset->Close();
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

    if (!m_pRecordset)
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
        if (m_pRecordset)
        {
            if (m_pRecordset->IsOpen())
                m_pRecordset->Close();

            delete m_pRecordset;
            m_pRecordset = NULL;
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
        m_pRecordset = new ZDActivityLogRecordset(&m_Database, m_FileName);

        if (m_pRecordset)
            m_pRecordset->Open(dbOpenSnapshot, NULL, dbReadOnly);
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
        m_pRecordset = new ZDActivityLogRecordset(&m_Database, m_FileName);

        if (m_pRecordset)
            m_pRecordset->Open(dbOpenDynaset, NULL, dbAppendOnly);
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
