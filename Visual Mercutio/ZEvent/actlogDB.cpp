/****************************************************************************
 * ==> PSS_ActivityLogDatabase ---------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity log database                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "ActLogDB.h"

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
    m_pLogRecordSet(NULL),
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
BOOL PSS_ActivityLogDatabase::AppendToLog(const ZBEventActivity& eventActivity)
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
    m_pRecordSet->SetEventType           (eventActivity.GetActivityEventTypeString());
    m_pRecordSet->SetProcessFilename     (eventActivity.GetProcessFilename());
    m_pRecordSet->SetFormDataFilename    (eventActivity.GetExchangeDataFilename());
    m_pRecordSet->SetProcessDataFilename (eventActivity.GetProcessExchangeDataFilename());
    m_pRecordSet->SetFolderName          (eventActivity.GetFolderName());
    m_pRecordSet->SetProcessName         (eventActivity.GetProcessName());
    m_pRecordSet->SetProcessCreationDate (eventActivity.GetProcessCreationDate());
    m_pRecordSet->SetProcessDueDate      (eventActivity.GetProcessDueDate());
    m_pRecordSet->SetActivityType        (eventActivity.GetActivityType());
    m_pRecordSet->SetActivityName        (eventActivity.GetActivityName());
    m_pRecordSet->SetActivityCreationDate(eventActivity.GetActivityCreationDate());
    m_pRecordSet->SetActivityDueDate     (eventActivity.GetActivityDueDate());
    m_pRecordSet->SetActivityStatus      (eventActivity.GetActivityStatus());
    m_pRecordSet->SetSender              (eventActivity.GetSender());
    m_pRecordSet->SetReceiver            (eventActivity.GetReceiver());
    m_pRecordSet->SetComments            (eventActivity.GetComments());
    m_pRecordSet->SetInBackup            (eventActivity.GetIsInBackup());

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
        const CString query = "DELETE " + g_ActivityLogTableName + ".* FROM " + g_ActivityLogTableName + ";";

        // execute the query
        m_Database.Execute(Query);
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
