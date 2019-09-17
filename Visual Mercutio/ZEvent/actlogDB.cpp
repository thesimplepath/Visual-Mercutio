//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ

#include <StdAfx.h>

// ActLogDB
#include "ActLogDB.h"
#include "zBaseLib\ZBDate.h"






ZUActivityLogDatabase::ZUActivityLogDatabase (CString LogFileName)
  : m_LogFileName(LogFileName), m_pLogRecordset(NULL)
{
}


ZUActivityLogDatabase::~ZUActivityLogDatabase()
{
    Close();
}


void ZUActivityLogDatabase::Create (CString LogFileName)
{
      m_LogFileName = LogFileName;
      if (m_LogFileName.IsEmpty())
          return;
}


BOOL ZUActivityLogDatabase::OpenRead ()
{
   //Open the database and the recordset
    try 
    {
        // First close the database
        Close();
        m_LogDatabase.Open( m_LogFileName, FALSE, TRUE );
        m_pLogRecordset = new ZDActivityLogRecordset( &m_LogDatabase, m_LogFileName );
        if (m_pLogRecordset)
        {
            m_pLogRecordset->Open( dbOpenSnapshot, NULL, dbReadOnly );
        }
        else
        {
            Close();
            return FALSE;
        }
    } 
    catch (CDaoException&)
    {
        return (FALSE);
    }

    return TRUE;
}

BOOL ZUActivityLogDatabase::OpenWrite ()
{
   //Open the database and the recordset
    try 
    {
        // First close the database
        Close();
        m_LogDatabase.Open( m_LogFileName );
        m_pLogRecordset = new ZDActivityLogRecordset( &m_LogDatabase, m_LogFileName );
        if (m_pLogRecordset)
        {
            m_pLogRecordset->Open( dbOpenDynaset, NULL, dbAppendOnly );
        }
        else
        {
            Close();
            return FALSE;
        }
    } 
    catch (CDaoException&)
    {
        return (FALSE);
    }

    return TRUE;
}

BOOL ZUActivityLogDatabase::Close ()
{
    TRY
    {
        if (m_pLogRecordset)
        {
            if (m_pLogRecordset->IsOpen())
                m_pLogRecordset->Close();
            delete m_pLogRecordset;
            m_pLogRecordset = NULL;
        }
        if (m_LogDatabase.IsOpen())
            m_LogDatabase.Close();
    }
    CATCH( CDaoException, e )
    {
        // Do nothing
        return FALSE;
    }
    END_CATCH
    return TRUE;
}


BOOL ZUActivityLogDatabase::AppendToLog (ZBEventActivity& EventActivity)
{
    if (!m_LogDatabase.IsOpen())
        OpenWrite();
    if (!m_pLogRecordset)
        return FALSE;
    try 
    {
        if (!m_pLogRecordset->IsOpen())
            m_pLogRecordset->Open( dbOpenDynaset, NULL, dbAppendOnly );
        if (m_pLogRecordset->IsOpen() && m_pLogRecordset->CanUpdate())
            m_pLogRecordset->AddNew();
    }
    catch (CDaoException&)
    {
        return (FALSE);
    }

    PSS_Date CurrentDate = PSS_Date::GetToday();

    // The current date
    m_pLogRecordset->SetDate( CurrentDate );
    // The Event type
    m_pLogRecordset->SetEventType( EventActivity.GetActivityEventTypeString() );
    // The process file
      m_pLogRecordset->SetProcessFilename( EventActivity.GetProcessFilename() );
    // The form data file
    m_pLogRecordset->SetFormDataFilename( EventActivity.GetExchangeDataFilename() );
    // The process data file
    m_pLogRecordset->SetProcessDataFilename( EventActivity.GetProcessExchangeDataFilename() );
    // The folder name
    m_pLogRecordset->SetFolderName( EventActivity.GetFolderName() );
    // The process name    
    m_pLogRecordset->SetProcessName( EventActivity.GetProcessName() );
    // The process start date
    m_pLogRecordset->SetProcessCreationDate( EventActivity.GetProcessCreationDate() );
    // The process end date
    m_pLogRecordset->SetProcessDueDate( EventActivity.GetProcessDueDate() );
    // The activity type
    m_pLogRecordset->SetActivityType( EventActivity.GetActivityType() );
    // The activity name    
    m_pLogRecordset->SetActivityName( EventActivity.GetActivityName() );
    // The activity start date
    m_pLogRecordset->SetActivityCreationDate( EventActivity.GetActivityCreationDate() );
    // The activity end date
    m_pLogRecordset->SetActivityDueDate( EventActivity.GetActivityDueDate() );
    // The status
      m_pLogRecordset->SetActivityStatus( EventActivity.GetActivityStatus() );
    // The sender
      m_pLogRecordset->SetSender( EventActivity.GetSender() );
    // The receiver
      m_pLogRecordset->SetReceiver( EventActivity.GetReceiver() );
    // The comment
      m_pLogRecordset->SetComments( EventActivity.GetComments() );
    // Is In Backup mode or not
    m_pLogRecordset->SetInBackup( EventActivity.GetIsInBackup() );

    try 
    {
        // Now update the new inserted record
        m_pLogRecordset->Update();
        m_pLogRecordset->Close();
    }
    catch (CDaoException&)
    {
        return (FALSE);
    }

    return TRUE;
}




BOOL ZUActivityLogDatabase::ClearLog ()
{
    if (!m_LogDatabase.IsOpen())
        OpenWrite();
    if (!m_pLogRecordset)
        return FALSE;
    try 
    {
        CString    Query = "DELETE ";
        Query += g_ActivityLogTableName; 
        Query += ".* FROM "; 
        Query += g_ActivityLogTableName; 
        Query += ";";
        
        m_LogDatabase.Execute( Query );

//        m_pLogRecordset->m_strFilter = Query;
//        m_pLogRecordset->Requery();
    } 
    catch (CDaoException&)
    {
        Close();
        return FALSE;
    }

    Close();

    return TRUE;
}
