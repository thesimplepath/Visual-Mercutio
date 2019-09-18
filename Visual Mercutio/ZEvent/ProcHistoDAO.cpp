//    Advanced Dedicated Software
//    Dominique AIGROZ

#include <StdAfx.h>
#include "ProcHistoDAO.h"

// processoft
#include "zBaseLib\PSS_Date.h"

// JMR-MODIF - Le 2 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (en commentaires)

ZDProcessHistoryDAO::ZDProcessHistoryDAO( CString DatabaseFileName )
    : m_DatabaseFileName                ( DatabaseFileName ),
      m_pHistoryActivityRecordset        ( NULL ),
      m_pHistoryActivityStatusRecordset    ( NULL ),
      m_pHistoryProcessRecordset        ( NULL ),
      m_pHistoryProcessStatusRecordset    ( NULL ),
      m_pHistoryFolderStatusRecordset    ( NULL )
{
}

ZDProcessHistoryDAO::~ZDProcessHistoryDAO()
{
    Close();
}

void ZDProcessHistoryDAO::Create( CString DatabaseFileName )
{
    m_DatabaseFileName = DatabaseFileName;

    if ( m_DatabaseFileName.IsEmpty() )
    {
        return;
    }
}

BOOL ZDProcessHistoryDAO::OpenRead()
{
    //Open the database and the recordset
    try
    {
        // First close the database
        Close();

        // Open the database
        m_ProcessHistoryDatabase.Open( m_DatabaseFileName, FALSE, TRUE );

        // Create the history activity recordset
        m_pHistoryActivityRecordset =
            new ZDHistoryActivityRecordset( &m_ProcessHistoryDatabase, m_DatabaseFileName );

        if ( m_pHistoryActivityRecordset )
        {
            m_pHistoryActivityRecordset->Open( dbOpenDynaset, NULL, dbReadOnly );
        }
        else
        {
            Close();
            return FALSE;
        }

        // Create the history folder status recordset
        m_pHistoryFolderStatusRecordset =
            new ZDHistoryFolderStatusRecordset( &m_ProcessHistoryDatabase, m_DatabaseFileName );

        if ( m_pHistoryFolderStatusRecordset )
        {
            m_pHistoryFolderStatusRecordset->Open( dbOpenDynaset, NULL, dbReadOnly );
        }
        else
        {
            Close();
            return FALSE;
        }

        // Create the history activity status recordset
        m_pHistoryActivityStatusRecordset =
            new ZDHistoryActivityStatusRecordset( &m_ProcessHistoryDatabase, m_DatabaseFileName );

        if ( m_pHistoryActivityStatusRecordset )
        {
            m_pHistoryActivityStatusRecordset->Open( dbOpenDynaset, NULL, dbReadOnly );
        }
        else
        {
            Close();
            return FALSE;
        }

        // Create the history process recordset
        m_pHistoryProcessRecordset =
            new ZDHistoryProcessRecordset( &m_ProcessHistoryDatabase, m_DatabaseFileName );

        if ( m_pHistoryProcessRecordset )
        {
            m_pHistoryProcessRecordset->Open( dbOpenDynaset, NULL, dbReadOnly );
        }
        else
        {
            Close();
            return FALSE;
        }

        // Create the history process status recordset
        m_pHistoryProcessStatusRecordset =
            new ZDHistoryProcessStatusRecordset( &m_ProcessHistoryDatabase, m_DatabaseFileName );

        if ( m_pHistoryProcessStatusRecordset )
        {
            m_pHistoryProcessStatusRecordset->Open( dbOpenDynaset, NULL, dbReadOnly );
        }
        else
        {
            Close();
            return FALSE;
        }
    }
    catch (CDaoException&)
    {
        return ( FALSE );
    }

    return TRUE;
}

BOOL ZDProcessHistoryDAO::OpenWrite()
{
    //Open the database and the recordset
    try
    {
        // First close the database
        Close();

        // Open the database
        m_ProcessHistoryDatabase.Open( m_DatabaseFileName );

        // Create the history activity recordset
        m_pHistoryActivityRecordset =
            new ZDHistoryActivityRecordset( &m_ProcessHistoryDatabase, m_DatabaseFileName );

        if ( !m_pHistoryActivityRecordset )
        {
            Close();
            return FALSE;
        }

        // Create the history folder status recordset
        m_pHistoryFolderStatusRecordset =
            new ZDHistoryFolderStatusRecordset( &m_ProcessHistoryDatabase, m_DatabaseFileName );

        if ( !m_pHistoryFolderStatusRecordset )
        {
            Close();
            return FALSE;
        }

        // Create the history activity status recordset
        m_pHistoryActivityStatusRecordset =
            new ZDHistoryActivityStatusRecordset( &m_ProcessHistoryDatabase, m_DatabaseFileName );

        if ( !m_pHistoryActivityStatusRecordset )
        {
            Close();
            return FALSE;
        }

        // Create the history process recordset
        m_pHistoryProcessRecordset =
            new ZDHistoryProcessRecordset( &m_ProcessHistoryDatabase, m_DatabaseFileName );

        if ( !m_pHistoryProcessRecordset )
        {
            Close();
            return FALSE;
        }

        // Create the history process status recordset
        m_pHistoryProcessStatusRecordset =
            new ZDHistoryProcessStatusRecordset( &m_ProcessHistoryDatabase, m_DatabaseFileName );

        if ( !m_pHistoryProcessStatusRecordset )
        {
            Close();
            return FALSE;
        }
    }
    catch (CDaoException&)
    {
        return ( FALSE );
    }

    return TRUE;;
}

BOOL ZDProcessHistoryDAO::Close ()
{
    TRY
    {
        // Close the history activity recordset
        if ( m_pHistoryActivityRecordset )
        {
            if ( m_pHistoryActivityRecordset->IsOpen() )
            {
                m_pHistoryActivityRecordset->Close();
            }

            delete m_pHistoryActivityRecordset;
            m_pHistoryActivityRecordset = NULL;
        }

        // Close the history folder status recordset
        if ( m_pHistoryFolderStatusRecordset )
        {
            if ( m_pHistoryFolderStatusRecordset->IsOpen() )
            {
                m_pHistoryFolderStatusRecordset->Close();
            }

            delete m_pHistoryFolderStatusRecordset;
            m_pHistoryFolderStatusRecordset = NULL;
        }

        // Close the history activity status recordset
        if ( m_pHistoryActivityStatusRecordset )
        {
            if ( m_pHistoryActivityStatusRecordset->IsOpen() )
            {
                m_pHistoryActivityStatusRecordset->Close();
            }

            delete m_pHistoryActivityStatusRecordset;
            m_pHistoryActivityStatusRecordset = NULL;
        }

        // Close the history process recordset
        if ( m_pHistoryProcessRecordset )
        {
            if ( m_pHistoryProcessRecordset->IsOpen() )
            {
                m_pHistoryProcessRecordset->Close();
            }

            delete m_pHistoryProcessRecordset;
            m_pHistoryProcessRecordset = NULL;
        }

        // Close the history process status recordset
        if ( m_pHistoryProcessStatusRecordset )
        {
            if ( m_pHistoryProcessStatusRecordset->IsOpen() )
            {
                m_pHistoryProcessStatusRecordset->Close();
            }

            delete m_pHistoryProcessStatusRecordset;
            m_pHistoryProcessStatusRecordset = NULL;
        }

        if ( m_ProcessHistoryDatabase.IsOpen() )
        {
            m_ProcessHistoryDatabase.Close();
        }
    }
    CATCH( CDaoException, e )
    {
        // Do nothing
        return FALSE;
    }
    END_CATCH

    return TRUE;
}

long ZDProcessHistoryDAO::FindProcess( ZBEventActivity& EventActivity )
{
    if ( !m_ProcessHistoryDatabase.IsOpen() )
    {
        OpenWrite();
    }

    if ( !m_pHistoryProcessRecordset )
    {
        return -1;
    }

    try
    {
        if ( !m_pHistoryProcessRecordset->IsOpen() )
        {
            m_pHistoryProcessRecordset->Open( dbOpenDynaset, NULL, dbConsistent );
        }
    }
    catch (CDaoException&)
    {
        return -1;
    }

    // Build the find key string
    CString FindKey;
    FindKey = m_pHistoryProcessRecordset->GetNameFieldName();

    if ( EventActivity.GetProcessName().Find( '\'' ) != -1 )
    {
        FindKey += _T( " = \"" );
    }
    else
    {
        FindKey += _T( " = '" );
    }

    FindKey += EventActivity.GetProcessName();

    if ( EventActivity.GetProcessName().Find( '\'' ) != -1 )
    {
        FindKey += _T( "\"" );
    }
    else
    {
        FindKey += _T( "'" );
    }

    FindKey += _T( " AND " );
    FindKey += m_pHistoryProcessRecordset->GetFilenameFieldName();

    if ( EventActivity.GetProcessFilename().Find( '\'' ) != -1 )
    {
        FindKey += _T( " = \"" );
    }
    else
    {
        FindKey += _T( " = '" );
    }

    FindKey += EventActivity.GetProcessFilename();

    if ( EventActivity.GetProcessFilename().Find( '\'' ) != -1 )
    {
        FindKey += _T( "\"" );
    }
    else
    {
        FindKey += _T( "'" );
    }

    FindKey += _T( " AND " );
    FindKey += m_pHistoryProcessRecordset->GetFolderNameFieldName();

    if ( EventActivity.GetFolderName().Find( '\'' ) != -1 )
    {
        FindKey += _T( " = \"" );
    }
    else
    {
        FindKey += _T( " = '" );
    }

    FindKey += EventActivity.GetFolderName();

    if ( EventActivity.GetFolderName().Find( '\'' ) != -1 )
    {
        FindKey += _T( "\"" );
    }
    else
    {
        FindKey += _T( "'" );
    }

    try
    {
        if ( !m_pHistoryProcessRecordset->FindFirst( FindKey ) )
        {
            m_pHistoryProcessRecordset->Close();
            return -1;
        }
    }
    catch (CDaoException&)
    {
        m_pHistoryProcessRecordset->Close();
        return -1;
    }

    m_pHistoryProcessRecordset->Close();
    return m_pHistoryProcessRecordset->GetProcessID();
}

long ZDProcessHistoryDAO::FindActivity( long ProcessID, PSS_Date& CurrentDate, ZBEventActivity& EventActivity )
{
    if ( !m_ProcessHistoryDatabase.IsOpen() )
    {
        OpenWrite();
    }

    if ( !m_pHistoryActivityRecordset )
    {
        return -1;
    }

    try
    {
        if ( !m_pHistoryActivityRecordset->IsOpen() )
        {
            m_pHistoryActivityRecordset->Open( dbOpenDynaset, NULL, dbConsistent );
        }
    }
    catch (CDaoException&)
    {
        return -1;
    }

    // Build the find key string
    CString FindKey;
    FindKey = m_pHistoryActivityRecordset->GetProcessIDFieldName();

    CString ProcIDstr;
    ProcIDstr.Format( _T( "%d" ), ProcessID );

    FindKey += _T( " = " );
    FindKey += ProcIDstr;

    FindKey += _T( " AND " );
    FindKey += m_pHistoryActivityRecordset->GetDateFieldName();
    FindKey += _T( " = #" );
    FindKey += CurrentDate.GetFormattedDate( _T( "%m/%d/%Y %H:%M:%S" ) );
    FindKey += _T( "#" );

    FindKey += _T( " AND " );
    FindKey += m_pHistoryActivityRecordset->GetNameFieldName();

    if ( EventActivity.GetActivityName().Find( '\'' ) != -1 )
    {
        FindKey += _T( " = \"" );
    }
    else
    {
        FindKey += _T( " = '" );
    }

    FindKey += EventActivity.GetActivityName();

    if ( EventActivity.GetActivityName().Find( '\'' ) != -1 )
    {
        FindKey += _T( "\"" );
    }
    else
    {
        FindKey += _T( "'" );
    }

    try
    {
        if ( !m_pHistoryActivityRecordset->FindFirst( FindKey ) )
        {
            m_pHistoryActivityRecordset->Close();
            return -1;
        }
    }
    catch (CDaoException&)
    {
        m_pHistoryActivityRecordset->Close();
        return -1;
    }

    m_pHistoryActivityRecordset->Close();
    return m_pHistoryActivityRecordset->GetActivityID();
}

bool ZDProcessHistoryDAO::AddNewProcessRecord( ZBEventActivity& EventActivity )
{
    if ( !m_ProcessHistoryDatabase.IsOpen() )
    {
        OpenWrite();
    }

    if ( !m_pHistoryProcessRecordset )
    {
        return false;
    }

    try
    {
        if ( !m_pHistoryProcessRecordset->IsOpen() )
        {
            m_pHistoryProcessRecordset->Open( dbOpenDynaset, NULL, dbAppendOnly );
        }

        if ( m_pHistoryProcessRecordset->IsOpen() && m_pHistoryProcessRecordset->CanUpdate() )
        {
            m_pHistoryProcessRecordset->AddNew();
        }
    }
    catch (CDaoException&)
    {
        m_pHistoryProcessRecordset->Close();
        return false;
    }

    // Assign information
    PSS_Date    CurrentDate = PSS_Date::GetToday();

    // The current date
    m_pHistoryProcessRecordset->SetDate( CurrentDate );

    // The process name    
    m_pHistoryProcessRecordset->SetName( EventActivity.GetProcessName() );

    // The process file
    m_pHistoryProcessRecordset->SetFilename( EventActivity.GetProcessFilename() );

    // The folder name
    m_pHistoryProcessRecordset->SetFolderName( EventActivity.GetFolderName() );

    // The form data file
    m_pHistoryProcessRecordset->SetDataFeedForm( EventActivity.GetExchangeDataFilename() );

    // The process data file
    m_pHistoryProcessRecordset->SetDataFeedProc( EventActivity.GetProcessExchangeDataFilename() );

    // The process start date
    m_pHistoryProcessRecordset->SetStartDate( EventActivity.GetProcessCreationDate() );

    // The process end date or forecasted end date if not finished
    m_pHistoryProcessRecordset->SetEndDate( EventActivity.GetProcessDueDate() );

    // Set the initial days
    m_pHistoryProcessRecordset->SetInitialDays( (long)( EventActivity.GetProcessDueDate() - EventActivity.GetProcessCreationDate() ) );

    // Set the forecasted end date
    m_pHistoryProcessRecordset->SetForecastedEndDate( EventActivity.GetProcessDueDate() );

    // The initiator
    m_pHistoryProcessRecordset->SetInitiator( EventActivity.GetSender() );

    try
    {
        // Now update the new inserted record
        m_pHistoryProcessRecordset->Update();
        m_pHistoryProcessRecordset->Close();
    }
    catch (CDaoException&)
    {
        m_pHistoryProcessRecordset->Close();
        return false;
    }

    return true;
}

bool ZDProcessHistoryDAO::ModifyProcessStatusRecord( long ProcessID, ZBEventActivity& EventActivity )
{
    if ( !m_ProcessHistoryDatabase.IsOpen() )
    {
        OpenWrite();
    }

    if ( !m_pHistoryProcessStatusRecordset )
    {
        return false;
    }

    try
    {
        if ( !m_pHistoryProcessStatusRecordset->IsOpen() )
        {
            m_pHistoryProcessStatusRecordset->Open( dbOpenDynaset, NULL, dbConsistent );
        }
    }
    catch (CDaoException&)
    {
        return false;
    }

    // Build the find key string
    CString ProcessStr;
    ProcessStr.Format( _T( "%ld" ), ProcessID );

    CString FindKey;
    FindKey = m_pHistoryProcessStatusRecordset->GetProcessIDFieldName();
    FindKey += _T( " = " );
    FindKey += ProcessStr;

    try
    {
        if ( !m_pHistoryProcessStatusRecordset->FindFirst( FindKey ) )
        {
            m_pHistoryProcessStatusRecordset->Close();
            return AddProcessStatusRecord( ProcessID, EventActivity );
        }
    }
    catch (CDaoException&)
    {
        return false;
    }

    // Modify the record
    try
    {
        if ( m_pHistoryProcessStatusRecordset->IsOpen() && m_pHistoryProcessStatusRecordset->CanUpdate() )
        {
            // Start update the record
            m_pHistoryProcessStatusRecordset->Edit();
        }
    }
    catch (CDaoException&)
    {
        m_pHistoryProcessStatusRecordset->Close();
        return false;
    }

    // Assign information
    PSS_Date CurrentDate = PSS_Date::GetToday();

    // The process ID
    m_pHistoryProcessStatusRecordset->SetProcessID( ProcessID );

    // The current date
    m_pHistoryProcessStatusRecordset->SetDate( CurrentDate );

    // The process start date
    m_pHistoryProcessStatusRecordset->SetStartDate( EventActivity.GetProcessCreationDate() );

    // The process end date or forecasted end date if not finished
    m_pHistoryProcessStatusRecordset->SetEndDate( CurrentDate );

    // The status
    m_pHistoryProcessStatusRecordset->SetStatus( EventActivity.GetActivityStatus() );

    // The current activity
    m_pHistoryProcessStatusRecordset->SetCurrentActivity( -1 );    // Not implemented yet

    try
    {
        // Now update the edited record
        m_pHistoryProcessStatusRecordset->Update();
        m_pHistoryProcessStatusRecordset->Close();
    }
    catch (CDaoException&)
    {
        return false;
    }

    return true;
}

bool ZDProcessHistoryDAO::AddProcessStatusRecord( long ProcessID, ZBEventActivity& EventActivity )
{
    if ( !m_ProcessHistoryDatabase.IsOpen() )
    {
        OpenWrite();
    }

    if ( !m_pHistoryProcessStatusRecordset )
    {
        return false;
    }

    try
    {
        if ( !m_pHistoryProcessStatusRecordset->IsOpen() )
        {
            m_pHistoryProcessStatusRecordset->Open( dbOpenDynaset, NULL, dbAppendOnly );
        }

        if ( m_pHistoryProcessStatusRecordset->IsOpen() && m_pHistoryProcessStatusRecordset->CanUpdate() )
        {
            m_pHistoryProcessStatusRecordset->AddNew();
        }
    }
    catch (CDaoException&)
    {
        return false;
    }

    PSS_Date CurrentDate = PSS_Date::GetToday();

    // The process ID
    m_pHistoryProcessStatusRecordset->SetProcessID( ProcessID );

    // The current date
    m_pHistoryProcessStatusRecordset->SetDate( CurrentDate );

    // The process start date
    m_pHistoryProcessStatusRecordset->SetStartDate( EventActivity.GetProcessCreationDate() );

    // The process end date or forecasted end date if not finished
    m_pHistoryProcessStatusRecordset->SetEndDate( CurrentDate );

    // The status
    m_pHistoryProcessStatusRecordset->SetStatus( EventActivity.GetActivityStatus() );

    // The current activity
    m_pHistoryProcessStatusRecordset->SetCurrentActivity( -1 );    // Not implemented yet

    try
    {
        // Now update the new inserted record
        m_pHistoryProcessStatusRecordset->Update();
        m_pHistoryProcessStatusRecordset->Close();
    }
    catch (CDaoException&)
    {
        return false;
    }

    return true;
}

bool ZDProcessHistoryDAO::ModifyActivityStatusRecord( long                ProcessID,
                                                      long                ActivityID,
                                                      ZBEventActivity&    EventActivity )
{
    if ( !m_ProcessHistoryDatabase.IsOpen() )
    {
        OpenWrite();
    }

    if ( !m_pHistoryActivityStatusRecordset )
    {
        return false;
    }

    try
    {
        if ( !m_pHistoryActivityStatusRecordset->IsOpen() )
        {
            m_pHistoryActivityStatusRecordset->Open( dbOpenDynaset, NULL, dbConsistent );
        }
    }
    catch (CDaoException&)
    {
        return false;
    }

    // Build the find key string
    CString ProcessStr;
    ProcessStr.Format( _T( "%ld" ), ProcessID );

    CString FindKey;
    FindKey = m_pHistoryActivityStatusRecordset->GetProcessIDFieldName();
    FindKey += _T( " = " );
    FindKey += ProcessStr;

    FindKey += _T( " AND " );
    FindKey += m_pHistoryActivityStatusRecordset->GetNameFieldName();

    if ( EventActivity.GetActivityName().Find( '\'' ) != -1 )
    {
        FindKey += _T( " = \"" );
    }
    else
    {
        FindKey += _T( " = '" );
    }

    FindKey += EventActivity.GetActivityName();

    if ( EventActivity.GetActivityName().Find( '\'' ) != -1 )
    {
        FindKey += _T( "\"" );
    }
    else
    {
        FindKey += _T( "'" );
    }

    FindKey += _T( " AND " );
    FindKey += m_pHistoryActivityStatusRecordset->GetFolderNameFieldName();

    if ( EventActivity.GetFolderName().Find( '\'' ) != -1 )
    {
        FindKey += _T( " = \"" );
    }
    else
    {
        FindKey += _T( " = '" );
    }

    FindKey += EventActivity.GetFolderName();

    if ( EventActivity.GetFolderName().Find( '\'' ) != -1 )
    {
        FindKey += _T( "\"" );
    }
    else
    {
        FindKey += _T( "'" );
    }

    try
    {
        if ( !m_pHistoryActivityStatusRecordset->FindFirst( FindKey ) )
        {
            m_pHistoryActivityStatusRecordset->Close();
            return AddActivityStatusRecord( ProcessID, ActivityID, EventActivity );
        }
    }
    catch (CDaoException&)
    {
        return false;
    }

    // Modify the record
    try
    {
        if ( m_pHistoryActivityStatusRecordset->IsOpen() && m_pHistoryActivityStatusRecordset->CanUpdate() )
        {
            // Start update the record
            m_pHistoryActivityStatusRecordset->Edit();
        }
    }
    catch (CDaoException&)
    {
        m_pHistoryActivityStatusRecordset->Close();
        return false;
    }

    // Assign information
    PSS_Date CurrentDate = PSS_Date::GetToday();

    // The activity ID
    m_pHistoryActivityStatusRecordset->SetActivityID( ActivityID );

    // The process ID
    m_pHistoryActivityStatusRecordset->SetProcessID( ProcessID );

    // The folder name
    m_pHistoryActivityStatusRecordset->SetFolderName( EventActivity.GetFolderName() );

    // The activity name
    m_pHistoryActivityStatusRecordset->SetName( EventActivity.GetActivityName() );

    // The current date
    m_pHistoryActivityStatusRecordset->SetDate( CurrentDate );

    // The activity start date
    m_pHistoryActivityStatusRecordset->SetStartDate( EventActivity.GetActivityCreationDate() );

    // The activity end date or forecasted end date if not finished
    m_pHistoryActivityStatusRecordset->SetEndDate( CurrentDate );

    // The status
    m_pHistoryActivityStatusRecordset->SetStatus( EventActivity.GetActivityStatus() );

    try
    {
        // Now update the edited record
        m_pHistoryActivityStatusRecordset->Update();
        m_pHistoryActivityStatusRecordset->Close();
    }
    catch (CDaoException&)
    {
        return false;
    }

    return true;
}

bool ZDProcessHistoryDAO::AddActivityStatusRecord( long ProcessID, long ActivityID, ZBEventActivity& EventActivity )
{
    if ( !m_ProcessHistoryDatabase.IsOpen() )
    {
        OpenWrite();
    }

    if ( !m_pHistoryActivityStatusRecordset )
    {
        return false;
    }

    try
    {
        if ( !m_pHistoryActivityStatusRecordset->IsOpen() )
        {
            m_pHistoryActivityStatusRecordset->Open( dbOpenDynaset, NULL, dbAppendOnly );
        }

        if ( m_pHistoryActivityStatusRecordset->IsOpen() && m_pHistoryActivityStatusRecordset->CanUpdate() )
        {
            m_pHistoryActivityStatusRecordset->AddNew();
        }
    }
    catch (CDaoException&)
    {
        return false;
    }

    PSS_Date CurrentDate = PSS_Date::GetToday();

    // The activity ID
    m_pHistoryActivityStatusRecordset->SetActivityID( ActivityID );

    // The process ID
    m_pHistoryActivityStatusRecordset->SetProcessID( ProcessID );

    // The activity name
    m_pHistoryActivityStatusRecordset->SetFolderName( EventActivity.GetFolderName() );

    // The activity name
    m_pHistoryActivityStatusRecordset->SetName( EventActivity.GetActivityName() );

    // The current date
    m_pHistoryActivityStatusRecordset->SetDate( CurrentDate );

    // The activity start date
    m_pHistoryActivityStatusRecordset->SetStartDate( EventActivity.GetActivityCreationDate() );

    // The activity end date or forecasted end date if not finished
    m_pHistoryActivityStatusRecordset->SetEndDate( CurrentDate );

    // The status
    m_pHistoryActivityStatusRecordset->SetStatus( EventActivity.GetActivityStatus() );

    try
    {
        // Now update the new inserted record
        m_pHistoryActivityStatusRecordset->Update();
        m_pHistoryActivityStatusRecordset->Close();
    }
    catch (CDaoException&)
    {
        return false;
    }

    return true;
}

bool ZDProcessHistoryDAO::ModifyFolderStatusRecord( long ProcessID, long ActivityID, ZBEventActivity& EventActivity )
{
    if ( !m_ProcessHistoryDatabase.IsOpen() )
    {
        OpenWrite();
    }

    if ( !m_pHistoryFolderStatusRecordset )
    {
        return false;
    }

    try
    {
        if ( !m_pHistoryFolderStatusRecordset->IsOpen() )
        {
            m_pHistoryFolderStatusRecordset->Open( dbOpenDynaset, NULL, dbConsistent );
        }
    }
    catch (CDaoException&)
    {
        return false;
    }

    // Build the find key string
    CString ProcessStr;
    ProcessStr.Format( _T( "%ld" ), ProcessID );

    CString FindKey;
    FindKey = m_pHistoryFolderStatusRecordset->GetProcessIDFieldName();
    FindKey += _T( " = " );
    FindKey += ProcessStr;

    FindKey += _T( " AND " );
    FindKey += m_pHistoryFolderStatusRecordset->GetFolderNameFieldName();

    if ( EventActivity.GetFolderName().Find( '\'' ) != -1 )
    {
        FindKey += _T( " = \"" );
    }
    else
    {
        FindKey += _T( " = '" );
    }

    FindKey += EventActivity.GetFolderName();

    if ( EventActivity.GetFolderName().Find( '\'' ) != -1 )
    {
        FindKey += _T( "\"" );
    }
    else
    {
        FindKey += _T( "'" );
    }

    try
    {
        if ( !m_pHistoryFolderStatusRecordset->FindFirst( FindKey ) )
        {
            m_pHistoryFolderStatusRecordset->Close();
            return AddFolderStatusRecord( ProcessID, ActivityID, EventActivity );
        }
    }
    catch (CDaoException&)
    {
        return false;
    }

    // Modify the record
    try
    {
        if ( m_pHistoryFolderStatusRecordset->IsOpen() && m_pHistoryFolderStatusRecordset->CanUpdate() )
        {
            // Start update the record
            m_pHistoryFolderStatusRecordset->Edit();
        }
    }
    catch (CDaoException&)
    {
        m_pHistoryFolderStatusRecordset->Close();
        return false;
    }

    // Assign information
    PSS_Date CurrentDate = PSS_Date::GetToday();

    // The activity ID
    m_pHistoryFolderStatusRecordset->SetActivityID( ActivityID );

    // The process ID
    m_pHistoryFolderStatusRecordset->SetProcessID( ProcessID );

    // The folder name
    m_pHistoryFolderStatusRecordset->SetFolderName( EventActivity.GetFolderName() );

    // The activity name
    m_pHistoryFolderStatusRecordset->SetName( EventActivity.GetActivityName() );

    // The current date
    m_pHistoryFolderStatusRecordset->SetDate( CurrentDate );

    // The activity start date
    m_pHistoryFolderStatusRecordset->SetStartDate( EventActivity.GetActivityCreationDate() );

    // The activity end date or forecasted end date if not finished
    m_pHistoryFolderStatusRecordset->SetEndDate( CurrentDate );

    // The status
    m_pHistoryFolderStatusRecordset->SetStatus( EventActivity.GetActivityStatus() );

    try
    {
        // Now update the edited record
        m_pHistoryFolderStatusRecordset->Update();
        m_pHistoryFolderStatusRecordset->Close();
    }
    catch (CDaoException&)
    {
        return false;
    }

    return true;
}

bool ZDProcessHistoryDAO::AddFolderStatusRecord( long ProcessID, long ActivityID, ZBEventActivity& EventActivity )
{
    if ( !m_ProcessHistoryDatabase.IsOpen() )
    {
        OpenWrite();
    }

    if ( !m_pHistoryFolderStatusRecordset )
    {
        return false;
    }

    try
    {
        if ( !m_pHistoryFolderStatusRecordset->IsOpen() )
        {
            m_pHistoryFolderStatusRecordset->Open( dbOpenDynaset, NULL, dbAppendOnly );
        }

        if ( m_pHistoryFolderStatusRecordset->IsOpen() && m_pHistoryFolderStatusRecordset->CanUpdate() )
        {
            m_pHistoryFolderStatusRecordset->AddNew();
        }
    }
    catch (CDaoException&)
    {
        return false;
    }

    PSS_Date CurrentDate = PSS_Date::GetToday();

    // The activity ID
    m_pHistoryFolderStatusRecordset->SetActivityID( ActivityID );

    // The process ID
    m_pHistoryFolderStatusRecordset->SetProcessID( ProcessID );

    // The activity name
    m_pHistoryFolderStatusRecordset->SetFolderName( EventActivity.GetFolderName() );

    // The activity name
    m_pHistoryFolderStatusRecordset->SetName( EventActivity.GetActivityName() );

    // The current date
    m_pHistoryFolderStatusRecordset->SetDate( CurrentDate );

    // The activity start date
    m_pHistoryFolderStatusRecordset->SetStartDate( EventActivity.GetActivityCreationDate() );

    // The activity end date or forecasted end date if not finished
    m_pHistoryFolderStatusRecordset->SetEndDate( CurrentDate );

    // The status
    m_pHistoryFolderStatusRecordset->SetStatus( EventActivity.GetActivityStatus() );

    try
    {
        // Now update the new inserted record
        m_pHistoryFolderStatusRecordset->Update();
        m_pHistoryFolderStatusRecordset->Close();
    }
    catch (CDaoException&)
    {
        return false;
    }

    return true;
}

BOOL ZDProcessHistoryDAO::AppendEventToHistoric( ZBEventActivity& EventActivity )
{
    // Check the existence of the process
    long ProcessID = FindProcess( EventActivity );

    // If not found, create a new process recored
    if ( ProcessID == -1 )
    {
        if ( !AddNewProcessRecord( EventActivity ) )
        {
            m_pHistoryActivityRecordset->Close();
            return FALSE;
        }

        ProcessID = FindProcess( EventActivity );

        // If still -1, error
        if ( ProcessID == -1 )
        {
            m_pHistoryActivityRecordset->Close();
            return FALSE;
        }
    }

    if ( !m_ProcessHistoryDatabase.IsOpen() )
    {
        OpenWrite();
    }

    if ( !m_pHistoryActivityRecordset )
    {
        return FALSE;
    }

    try
    {
        if ( !m_pHistoryActivityRecordset->IsOpen() )
        {
            m_pHistoryActivityRecordset->Open( dbOpenDynaset, NULL, dbAppendOnly );
        }

        if ( m_pHistoryActivityRecordset->IsOpen() && m_pHistoryActivityRecordset->CanUpdate() )
        {
            m_pHistoryActivityRecordset->AddNew();
        }
    }
    catch (CDaoException&)
    {
        return ( FALSE );
    }

    // Assign information
    PSS_Date CurrentDate = PSS_Date::GetToday();

    // The current date
    m_pHistoryActivityRecordset->SetDate( CurrentDate );

    // The processID
    m_pHistoryActivityRecordset->SetProcessID( ProcessID );

    // The activity name    
    m_pHistoryActivityRecordset->SetName( EventActivity.GetActivityName() );

    // The activity start date
    m_pHistoryActivityRecordset->SetStartDate( EventActivity.GetActivityCreationDate() );

    // The activity end date
    m_pHistoryActivityRecordset->SetEndDate( CurrentDate );

    // Set the initial days
    m_pHistoryActivityRecordset->SetInitialDays((long)( EventActivity.GetActivityDueDate() - EventActivity.GetActivityCreationDate() ) );

    // Set the forecasted end date
    m_pHistoryActivityRecordset->SetForecastedEndDate( EventActivity.GetActivityDueDate() );

    // The sender
    m_pHistoryActivityRecordset->SetInitiator( EventActivity.GetSender() );

    // The destinator
    m_pHistoryActivityRecordset->SetReceiver( EventActivity.GetReceiver() );

    // The status
    m_pHistoryActivityRecordset->SetStatus( EventActivity.GetActivityStatus() );

    // The comment
    m_pHistoryActivityRecordset->SetComment( EventActivity.GetComments() );

    // Is In Backup mode or not
    m_pHistoryActivityRecordset->SetInBackup( EventActivity.GetIsInBackup() );

    long ActivityID = -1;

    try
    {
        // Now update the new inserted record
        m_pHistoryActivityRecordset->Update();
        m_pHistoryActivityRecordset->Close();

        ActivityID = FindActivity( ProcessID, CurrentDate, EventActivity );
    }
    catch (CDaoException&)
    {
        return ( FALSE );
    }
    
    // Modify the process status
    if ( !ModifyProcessStatusRecord( ProcessID, EventActivity ) )
    {
        return FALSE;
    }

    if ( !ModifyActivityStatusRecord( ProcessID, ActivityID, EventActivity ) )
    {
        return FALSE;
    }

    if ( !ModifyFolderStatusRecord( ProcessID, ActivityID, EventActivity ) )
    {
        return FALSE;
    }

    return TRUE;
}
