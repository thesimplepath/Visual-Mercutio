/****************************************************************************
 * ==> PSS_ProcessHistoryDAODatabase ---------------------------------------*
 ****************************************************************************
 * Description : Provides a process history DAO database                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ProcessHistoryDAODatabase.h"

// processoft
#include "zBaseLib\PSS_Date.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ProcessHistoryDAODatabase
//---------------------------------------------------------------------------
PSS_ProcessHistoryDAODatabase::PSS_ProcessHistoryDAODatabase(const CString& fileName) :
    m_pHistoryActivityRecordset(NULL),
    m_pHistoryActivityStatusRecordset(NULL),
    m_pHistoryProcessRecordset(NULL),
    m_pHistoryProcessStatusRecordset(NULL),
    m_pHistoryFolderStatusRecordset(NULL),
    m_DatabaseFileName(fileName)
{}
//---------------------------------------------------------------------------
PSS_ProcessHistoryDAODatabase::PSS_ProcessHistoryDAODatabase(const PSS_ProcessHistoryDAODatabase& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ProcessHistoryDAODatabase::~PSS_ProcessHistoryDAODatabase()
{
    // NOTE use fully qualified name here to avoid any pure virtual function calls
    PSS_ProcessHistoryDAODatabase::Close();
}
//---------------------------------------------------------------------------
const PSS_ProcessHistoryDAODatabase& PSS_ProcessHistoryDAODatabase::operator = (const PSS_ProcessHistoryDAODatabase& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ProcessHistoryDAODatabase::Create(const CString& fileName)
{
    m_DatabaseFileName = fileName;

    if (m_DatabaseFileName.IsEmpty())
        return;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessHistoryDAODatabase::AppendEventToHistoric(const PSS_ActivityEvent& activityEvent)
{
    // check if the process exists
    long processID = FindProcess(activityEvent);

    // if not found, create a new process record
    if (processID == -1)
    {
        if (!AddNewProcessRecord(activityEvent))
        {
            m_pHistoryActivityRecordset->Close();
            return FALSE;
        }

        processID = FindProcess(activityEvent);

        // if still -1, error
        if (processID == -1)
        {
            m_pHistoryActivityRecordset->Close();
            return FALSE;
        }
    }

    if (!m_ProcessHistoryDatabase.IsOpen())
        OpenWrite();

    if (!m_pHistoryActivityRecordset)
        return FALSE;

    try
    {
        if (!m_pHistoryActivityRecordset->IsOpen())
            m_pHistoryActivityRecordset->Open(dbOpenDynaset, NULL, dbAppendOnly);

        if (m_pHistoryActivityRecordset->IsOpen() && m_pHistoryActivityRecordset->CanUpdate())
            m_pHistoryActivityRecordset->AddNew();
    }
    catch (CDaoException&)
    {
        return (FALSE);
    }

    const PSS_Date CurrentDate = PSS_Date::GetToday();

    // assign information
    m_pHistoryActivityRecordset->SetDate(CurrentDate);
    m_pHistoryActivityRecordset->SetProcessID(processID);
    m_pHistoryActivityRecordset->SetName(activityEvent.GetActivityName());
    m_pHistoryActivityRecordset->SetStartDate(activityEvent.GetActivityCreationDate());
    m_pHistoryActivityRecordset->SetEndDate(CurrentDate);
    m_pHistoryActivityRecordset->SetInitialDays(long(activityEvent.GetActivityDueDate() - activityEvent.GetActivityCreationDate()));
    m_pHistoryActivityRecordset->SetForecastedEndDate(activityEvent.GetActivityDueDate());
    m_pHistoryActivityRecordset->SetInitiator(activityEvent.GetSender());
    m_pHistoryActivityRecordset->SetReceiver(activityEvent.GetReceiver());
    m_pHistoryActivityRecordset->SetStatus(activityEvent.GetActivityStatus());
    m_pHistoryActivityRecordset->SetComment(activityEvent.GetComments());
    m_pHistoryActivityRecordset->SetInBackup(activityEvent.GetIsInBackup());

    long activityID = -1;

    try
    {
        // update the newly inserted record
        m_pHistoryActivityRecordset->Update();
        m_pHistoryActivityRecordset->Close();

        activityID = FindActivity(processID, CurrentDate, activityEvent);
    }
    catch (CDaoException&)
    {
        return (FALSE);
    }

    // modify the process status
    if (!ModifyProcessStatusRecord(processID, activityEvent))
        return FALSE;

    if (!ModifyActivityStatusRecord(processID, activityID, activityEvent))
        return FALSE;

    if (!ModifyFolderStatusRecord(processID, activityID, activityEvent))
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessHistoryDAODatabase::Close()
{
    TRY
    {
        // Close the history activity recordset
        if (m_pHistoryActivityRecordset)
        {
            if (m_pHistoryActivityRecordset->IsOpen())
                m_pHistoryActivityRecordset->Close();

            delete m_pHistoryActivityRecordset;
            m_pHistoryActivityRecordset = NULL;
        }

        // close the history folder status recordset
        if (m_pHistoryFolderStatusRecordset)
        {
            if (m_pHistoryFolderStatusRecordset->IsOpen())
                m_pHistoryFolderStatusRecordset->Close();

            delete m_pHistoryFolderStatusRecordset;
            m_pHistoryFolderStatusRecordset = NULL;
        }

        // close the history activity status recordset
        if (m_pHistoryActivityStatusRecordset)
        {
            if (m_pHistoryActivityStatusRecordset->IsOpen())
                m_pHistoryActivityStatusRecordset->Close();

            delete m_pHistoryActivityStatusRecordset;
            m_pHistoryActivityStatusRecordset = NULL;
        }

        // close the history process recordset
        if (m_pHistoryProcessRecordset)
        {
            if (m_pHistoryProcessRecordset->IsOpen())
                m_pHistoryProcessRecordset->Close();

            delete m_pHistoryProcessRecordset;
            m_pHistoryProcessRecordset = NULL;
        }

        // close the history process status recordset
        if (m_pHistoryProcessStatusRecordset)
        {
            if (m_pHistoryProcessStatusRecordset->IsOpen())
                m_pHistoryProcessStatusRecordset->Close();

            delete m_pHistoryProcessStatusRecordset;
            m_pHistoryProcessStatusRecordset = NULL;
        }

        if (m_ProcessHistoryDatabase.IsOpen())
            m_ProcessHistoryDatabase.Close();
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
long PSS_ProcessHistoryDAODatabase::FindProcess(const PSS_ActivityEvent& activityEvent)
{
    if (!m_ProcessHistoryDatabase.IsOpen())
        OpenWrite();

    if (!m_pHistoryProcessRecordset)
        return -1;

    try
    {
        if (!m_pHistoryProcessRecordset->IsOpen())
            m_pHistoryProcessRecordset->Open(dbOpenDynaset, NULL, dbConsistent);
    }
    catch (CDaoException&)
    {
        return -1;
    }

    // build the find key string
    CString findKey = m_pHistoryProcessRecordset->GetNameFieldName();

    if (activityEvent.GetProcessName().Find('\'') != -1)
        findKey += _T(" = \"");
    else
        findKey += _T(" = '");

    findKey += activityEvent.GetProcessName();

    if (activityEvent.GetProcessName().Find('\'') != -1)
        findKey += _T("\"");
    else
        findKey += _T("'");

    findKey += _T(" AND ");
    findKey += m_pHistoryProcessRecordset->GetFileNameFieldName();

    if (activityEvent.GetProcessFileName().Find('\'') != -1)
        findKey += _T(" = \"");
    else
        findKey += _T(" = '");

    findKey += activityEvent.GetProcessFileName();

    if (activityEvent.GetProcessFileName().Find('\'') != -1)
        findKey += _T("\"");
    else
        findKey += _T("'");

    findKey += _T(" AND ");
    findKey += m_pHistoryProcessRecordset->GetFolderNameFieldName();

    if (activityEvent.GetFolderName().Find('\'') != -1)
        findKey += _T(" = \"");
    else
        findKey += _T(" = '");

    findKey += activityEvent.GetFolderName();

    if (activityEvent.GetFolderName().Find('\'') != -1)
        findKey += _T("\"");
    else
        findKey += _T("'");

    try
    {
        if (!m_pHistoryProcessRecordset->FindFirst(findKey))
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
//---------------------------------------------------------------------------
long PSS_ProcessHistoryDAODatabase::FindActivity(long processID, const PSS_Date& currentDate, const PSS_ActivityEvent& activityEvent)
{
    if (!m_ProcessHistoryDatabase.IsOpen())
        OpenWrite();

    if (!m_pHistoryActivityRecordset)
        return -1;

    try
    {
        if (!m_pHistoryActivityRecordset->IsOpen())
            m_pHistoryActivityRecordset->Open(dbOpenDynaset, NULL, dbConsistent);
    }
    catch (CDaoException&)
    {
        return -1;
    }

    // Build the find key string
    CString findKey = m_pHistoryActivityRecordset->GetProcessIDFieldName();

    CString procID;
    procID.Format(_T("%d"), processID);

    findKey += _T(" = ");
    findKey += procID;
    findKey += _T(" AND ");
    findKey += m_pHistoryActivityRecordset->GetDateFieldName();
    findKey += _T(" = #");
    findKey += currentDate.GetFormattedDate(_T("%m/%d/%Y %H:%M:%S"));
    findKey += _T("#");
    findKey += _T(" AND ");
    findKey += m_pHistoryActivityRecordset->GetNameFieldName();

    if (activityEvent.GetActivityName().Find('\'') != -1)
        findKey += _T(" = \"");
    else
        findKey += _T(" = '");

    findKey += activityEvent.GetActivityName();

    if (activityEvent.GetActivityName().Find('\'') != -1)
        findKey += _T("\"");
    else
        findKey += _T("'");

    try
    {
        if (!m_pHistoryActivityRecordset->FindFirst(findKey))
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
//---------------------------------------------------------------------------
bool PSS_ProcessHistoryDAODatabase::AddNewProcessRecord(const PSS_ActivityEvent& activityEvent)
{
    if (!m_ProcessHistoryDatabase.IsOpen())
        OpenWrite();

    if (!m_pHistoryProcessRecordset)
        return false;

    try
    {
        if (!m_pHistoryProcessRecordset->IsOpen())
            m_pHistoryProcessRecordset->Open(dbOpenDynaset, NULL, dbAppendOnly);

        if (m_pHistoryProcessRecordset->IsOpen() && m_pHistoryProcessRecordset->CanUpdate())
            m_pHistoryProcessRecordset->AddNew();
    }
    catch (CDaoException&)
    {
        m_pHistoryProcessRecordset->Close();
        return false;
    }

    const PSS_Date currentDate = PSS_Date::GetToday();

    // assign information
    m_pHistoryProcessRecordset->SetDate(currentDate);
    m_pHistoryProcessRecordset->SetName(activityEvent.GetProcessName());
    m_pHistoryProcessRecordset->SetFileName(activityEvent.GetProcessFileName());
    m_pHistoryProcessRecordset->SetFolderName(activityEvent.GetFolderName());
    m_pHistoryProcessRecordset->SetDataFeedForm(activityEvent.GetExchangeDataFileName());
    m_pHistoryProcessRecordset->SetDataFeedProc(activityEvent.GetProcessExchangeDataFileName());
    m_pHistoryProcessRecordset->SetStartDate(activityEvent.GetProcessCreationDate());
    m_pHistoryProcessRecordset->SetEndDate(activityEvent.GetProcessDueDate());
    m_pHistoryProcessRecordset->SetInitialDays(long(activityEvent.GetProcessDueDate() - activityEvent.GetProcessCreationDate()));
    m_pHistoryProcessRecordset->SetForecastedEndDate(activityEvent.GetProcessDueDate());
    m_pHistoryProcessRecordset->SetInitiator(activityEvent.GetSender());

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
//---------------------------------------------------------------------------
bool PSS_ProcessHistoryDAODatabase::AddProcessStatusRecord(long processID, const PSS_ActivityEvent& activityEvent)
{
    if (!m_ProcessHistoryDatabase.IsOpen())
        OpenWrite();

    if (!m_pHistoryProcessStatusRecordset)
        return false;

    try
    {
        if (!m_pHistoryProcessStatusRecordset->IsOpen())
            m_pHistoryProcessStatusRecordset->Open(dbOpenDynaset, NULL, dbAppendOnly);

        if (m_pHistoryProcessStatusRecordset->IsOpen() && m_pHistoryProcessStatusRecordset->CanUpdate())
            m_pHistoryProcessStatusRecordset->AddNew();
    }
    catch (CDaoException&)
    {
        return false;
    }

    const PSS_Date currentDate = PSS_Date::GetToday();

    // assign information
    m_pHistoryProcessStatusRecordset->SetProcessID(processID);
    m_pHistoryProcessStatusRecordset->SetDate(currentDate);
    m_pHistoryProcessStatusRecordset->SetStartDate(activityEvent.GetProcessCreationDate());
    m_pHistoryProcessStatusRecordset->SetEndDate(currentDate);
    m_pHistoryProcessStatusRecordset->SetStatus(activityEvent.GetActivityStatus());
    m_pHistoryProcessStatusRecordset->SetCurrentActivity(-1);

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
//---------------------------------------------------------------------------
bool PSS_ProcessHistoryDAODatabase::ModifyProcessStatusRecord(long processID, const PSS_ActivityEvent& activityEvent)
{
    if (!m_ProcessHistoryDatabase.IsOpen())
        OpenWrite();

    if (!m_pHistoryProcessStatusRecordset)
        return false;

    try
    {
        if (!m_pHistoryProcessStatusRecordset->IsOpen())
            m_pHistoryProcessStatusRecordset->Open(dbOpenDynaset, NULL, dbConsistent);
    }
    catch (CDaoException&)
    {
        return false;
    }

    // build the find key string
    CString process;
    process.Format(_T("%ld"), processID);

    const CString findKey = m_pHistoryProcessStatusRecordset->GetProcessIDFieldName() + _T(" = ") + process;

    try
    {
        if (!m_pHistoryProcessStatusRecordset->FindFirst(findKey))
        {
            m_pHistoryProcessStatusRecordset->Close();
            return AddProcessStatusRecord(processID, activityEvent);
        }
    }
    catch (CDaoException&)
    {
        return false;
    }

    // modify the record
    try
    {
        // start to update the record
        if (m_pHistoryProcessStatusRecordset->IsOpen() && m_pHistoryProcessStatusRecordset->CanUpdate())
            m_pHistoryProcessStatusRecordset->Edit();
    }
    catch (CDaoException&)
    {
        m_pHistoryProcessStatusRecordset->Close();
        return false;
    }

    PSS_Date CurrentDate = PSS_Date::GetToday();

    // assign information
    m_pHistoryProcessStatusRecordset->SetProcessID(processID);
    m_pHistoryProcessStatusRecordset->SetDate(CurrentDate);
    m_pHistoryProcessStatusRecordset->SetStartDate(activityEvent.GetProcessCreationDate());
    m_pHistoryProcessStatusRecordset->SetEndDate(CurrentDate);
    m_pHistoryProcessStatusRecordset->SetStatus(activityEvent.GetActivityStatus());
    m_pHistoryProcessStatusRecordset->SetCurrentActivity(-1);

    try
    {
        // update the edited record
        m_pHistoryProcessStatusRecordset->Update();
        m_pHistoryProcessStatusRecordset->Close();
    }
    catch (CDaoException&)
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessHistoryDAODatabase::AddActivityStatusRecord(long processID, long activityID, const PSS_ActivityEvent& activityEvent)
{
    if (!m_ProcessHistoryDatabase.IsOpen())
        OpenWrite();

    if (!m_pHistoryActivityStatusRecordset)
        return false;

    try
    {
        if (!m_pHistoryActivityStatusRecordset->IsOpen())
            m_pHistoryActivityStatusRecordset->Open(dbOpenDynaset, NULL, dbAppendOnly);

        if (m_pHistoryActivityStatusRecordset->IsOpen() && m_pHistoryActivityStatusRecordset->CanUpdate())
            m_pHistoryActivityStatusRecordset->AddNew();
    }
    catch (CDaoException&)
    {
        return false;
    }

    const PSS_Date currentDate = PSS_Date::GetToday();

    // assign information
    m_pHistoryActivityStatusRecordset->SetActivityID(activityID);
    m_pHistoryActivityStatusRecordset->SetProcessID(processID);
    m_pHistoryActivityStatusRecordset->SetFolderName(activityEvent.GetFolderName());
    m_pHistoryActivityStatusRecordset->SetName(activityEvent.GetActivityName());
    m_pHistoryActivityStatusRecordset->SetDate(currentDate);
    m_pHistoryActivityStatusRecordset->SetStartDate(activityEvent.GetActivityCreationDate());
    m_pHistoryActivityStatusRecordset->SetEndDate(currentDate);
    m_pHistoryActivityStatusRecordset->SetStatus(activityEvent.GetActivityStatus());

    try
    {
        // update the new inserted record
        m_pHistoryActivityStatusRecordset->Update();
        m_pHistoryActivityStatusRecordset->Close();
    }
    catch (CDaoException&)
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessHistoryDAODatabase::ModifyActivityStatusRecord(long                     processID,
                                                               long                     activityID,
                                                               const PSS_ActivityEvent& activityEvent)
{
    if (!m_ProcessHistoryDatabase.IsOpen())
        OpenWrite();

    if (!m_pHistoryActivityStatusRecordset)
        return false;

    try
    {
        if (!m_pHistoryActivityStatusRecordset->IsOpen())
            m_pHistoryActivityStatusRecordset->Open(dbOpenDynaset, NULL, dbConsistent);
    }
    catch (CDaoException&)
    {
        return false;
    }

    // Build the find key string
    CString process;
    process.Format(_T("%ld"), processID);

    CString findKey  = m_pHistoryActivityStatusRecordset->GetProcessIDFieldName();
    findKey         += _T(" = ");
    findKey         += process;
    findKey         += _T(" AND ");
    findKey         += m_pHistoryActivityStatusRecordset->GetNameFieldName();

    if (activityEvent.GetActivityName().Find('\'') != -1)
        findKey += _T(" = \"");
    else
        findKey += _T(" = '");

    findKey += activityEvent.GetActivityName();

    if (activityEvent.GetActivityName().Find('\'') != -1)
        findKey += _T("\"");
    else
        findKey += _T("'");

    findKey += _T(" AND ");
    findKey += m_pHistoryActivityStatusRecordset->GetFolderNameFieldName();

    if (activityEvent.GetFolderName().Find('\'') != -1)
        findKey += _T(" = \"");
    else
        findKey += _T(" = '");

    findKey += activityEvent.GetFolderName();

    if (activityEvent.GetFolderName().Find('\'') != -1)
        findKey += _T("\"");
    else
        findKey += _T("'");

    try
    {
        if (!m_pHistoryActivityStatusRecordset->FindFirst(findKey))
        {
            m_pHistoryActivityStatusRecordset->Close();
            return AddActivityStatusRecord(processID, activityID, activityEvent);
        }
    }
    catch (CDaoException&)
    {
        return false;
    }

    // modify the record
    try
    {
        // start to update the record
        if (m_pHistoryActivityStatusRecordset->IsOpen() && m_pHistoryActivityStatusRecordset->CanUpdate())
            m_pHistoryActivityStatusRecordset->Edit();
    }
    catch (CDaoException&)
    {
        m_pHistoryActivityStatusRecordset->Close();
        return false;
    }

    const PSS_Date currentDate = PSS_Date::GetToday();

    // assign information
    m_pHistoryActivityStatusRecordset->SetActivityID(activityID);
    m_pHistoryActivityStatusRecordset->SetProcessID(processID);
    m_pHistoryActivityStatusRecordset->SetFolderName(activityEvent.GetFolderName());
    m_pHistoryActivityStatusRecordset->SetName(activityEvent.GetActivityName());
    m_pHistoryActivityStatusRecordset->SetDate(currentDate);
    m_pHistoryActivityStatusRecordset->SetStartDate(activityEvent.GetActivityCreationDate());
    m_pHistoryActivityStatusRecordset->SetEndDate(currentDate);
    m_pHistoryActivityStatusRecordset->SetStatus(activityEvent.GetActivityStatus());

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
//---------------------------------------------------------------------------
bool PSS_ProcessHistoryDAODatabase::AddFolderStatusRecord(long processID, long activityID, const PSS_ActivityEvent& activityEvent)
{
    if (!m_ProcessHistoryDatabase.IsOpen())
        OpenWrite();

    if (!m_pHistoryFolderStatusRecordset)
        return false;

    try
    {
        if (!m_pHistoryFolderStatusRecordset->IsOpen())
            m_pHistoryFolderStatusRecordset->Open(dbOpenDynaset, NULL, dbAppendOnly);

        if (m_pHistoryFolderStatusRecordset->IsOpen() && m_pHistoryFolderStatusRecordset->CanUpdate())
            m_pHistoryFolderStatusRecordset->AddNew();
    }
    catch (CDaoException&)
    {
        return false;
    }

    const PSS_Date currentDate = PSS_Date::GetToday();

    // assign information
    m_pHistoryFolderStatusRecordset->SetActivityID(activityID);
    m_pHistoryFolderStatusRecordset->SetProcessID(processID);
    m_pHistoryFolderStatusRecordset->SetFolderName(activityEvent.GetFolderName());
    m_pHistoryFolderStatusRecordset->SetName(activityEvent.GetActivityName());
    m_pHistoryFolderStatusRecordset->SetDate(currentDate);
    m_pHistoryFolderStatusRecordset->SetStartDate(activityEvent.GetActivityCreationDate());
    m_pHistoryFolderStatusRecordset->SetEndDate(currentDate);
    m_pHistoryFolderStatusRecordset->SetStatus(activityEvent.GetActivityStatus());

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
//---------------------------------------------------------------------------
bool PSS_ProcessHistoryDAODatabase::ModifyFolderStatusRecord(long processID, long activityID, const PSS_ActivityEvent& activityEvent)
{
    if (!m_ProcessHistoryDatabase.IsOpen())
        OpenWrite();

    if (!m_pHistoryFolderStatusRecordset)
        return false;

    try
    {
        if (!m_pHistoryFolderStatusRecordset->IsOpen())
            m_pHistoryFolderStatusRecordset->Open(dbOpenDynaset, NULL, dbConsistent);
    }
    catch (CDaoException&)
    {
        return false;
    }

    // build the find key string
    CString process;
    process.Format(_T("%ld"), processID);

    CString findKey  = m_pHistoryFolderStatusRecordset->GetProcessIDFieldName();
    findKey         += _T(" = ");
    findKey         += process;
    findKey         += _T(" AND ");
    findKey         += m_pHistoryFolderStatusRecordset->GetFolderNameFieldName();

    if (activityEvent.GetFolderName().Find('\'') != -1)
        findKey += _T(" = \"");
    else
        findKey += _T(" = '");

    findKey += activityEvent.GetFolderName();

    if (activityEvent.GetFolderName().Find('\'') != -1)
        findKey += _T("\"");
    else
        findKey += _T("'");

    try
    {
        if (!m_pHistoryFolderStatusRecordset->FindFirst(findKey))
        {
            m_pHistoryFolderStatusRecordset->Close();
            return AddFolderStatusRecord(processID, activityID, activityEvent);
        }
    }
    catch (CDaoException&)
    {
        return false;
    }

    // modify the record
    try
    {
        // start to update the record
        if (m_pHistoryFolderStatusRecordset->IsOpen() && m_pHistoryFolderStatusRecordset->CanUpdate())
            m_pHistoryFolderStatusRecordset->Edit();
    }
    catch (CDaoException&)
    {
        m_pHistoryFolderStatusRecordset->Close();
        return false;
    }

    const PSS_Date currentDate = PSS_Date::GetToday();

    // assign information
    m_pHistoryFolderStatusRecordset->SetActivityID(activityID);
    m_pHistoryFolderStatusRecordset->SetProcessID(processID);
    m_pHistoryFolderStatusRecordset->SetFolderName(activityEvent.GetFolderName());
    m_pHistoryFolderStatusRecordset->SetName(activityEvent.GetActivityName());
    m_pHistoryFolderStatusRecordset->SetDate(currentDate);
    m_pHistoryFolderStatusRecordset->SetStartDate(activityEvent.GetActivityCreationDate());
    m_pHistoryFolderStatusRecordset->SetEndDate(currentDate);
    m_pHistoryFolderStatusRecordset->SetStatus(activityEvent.GetActivityStatus());

    try
    {
        // update the edited record
        m_pHistoryFolderStatusRecordset->Update();
        m_pHistoryFolderStatusRecordset->Close();
    }
    catch (CDaoException&)
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessHistoryDAODatabase::OpenRead()
{
    // open the database and the recordset
    try
    {
        // close the previously opened database
        Close();

        // open the database
        m_ProcessHistoryDatabase.Open(m_DatabaseFileName, FALSE, TRUE);

        // create the history activity recordset
        m_pHistoryActivityRecordset =
                new PSS_HistoryActivityRecordset(&m_ProcessHistoryDatabase, m_DatabaseFileName);

        if (m_pHistoryActivityRecordset)
            m_pHistoryActivityRecordset->Open(dbOpenDynaset, NULL, dbReadOnly);
        else
        {
            Close();
            return FALSE;
        }

        // create the history folder status recordset
        m_pHistoryFolderStatusRecordset =
                new PSS_HistoryFolderStatusRecordset(&m_ProcessHistoryDatabase, m_DatabaseFileName);

        if (m_pHistoryFolderStatusRecordset)
            m_pHistoryFolderStatusRecordset->Open(dbOpenDynaset, NULL, dbReadOnly);
        else
        {
            Close();
            return FALSE;
        }

        // create the history activity status recordset
        m_pHistoryActivityStatusRecordset =
                new PSS_HistoryActivityStatusRecordset(&m_ProcessHistoryDatabase, m_DatabaseFileName);

        if (m_pHistoryActivityStatusRecordset)
            m_pHistoryActivityStatusRecordset->Open(dbOpenDynaset, NULL, dbReadOnly);
        else
        {
            Close();
            return FALSE;
        }

        // create the history process recordset
        m_pHistoryProcessRecordset =
                new PSS_HistoryProcessRecordset(&m_ProcessHistoryDatabase, m_DatabaseFileName);

        if (m_pHistoryProcessRecordset)
            m_pHistoryProcessRecordset->Open(dbOpenDynaset, NULL, dbReadOnly);
        else
        {
            Close();
            return FALSE;
        }

        // create the history process status recordset
        m_pHistoryProcessStatusRecordset =
                new PSS_HistoryProcessStatusRecordset(&m_ProcessHistoryDatabase, m_DatabaseFileName);

        if (m_pHistoryProcessStatusRecordset)
            m_pHistoryProcessStatusRecordset->Open(dbOpenDynaset, NULL, dbReadOnly);
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
//---------------------------------------------------------------------------
BOOL PSS_ProcessHistoryDAODatabase::OpenWrite()
{
    // open the database and the recordset
    try
    {
        // close the previously opened database
        Close();

        // open the database
        m_ProcessHistoryDatabase.Open(m_DatabaseFileName);

        // create the history activity recordset
        m_pHistoryActivityRecordset =
                new PSS_HistoryActivityRecordset(&m_ProcessHistoryDatabase, m_DatabaseFileName);

        if (!m_pHistoryActivityRecordset)
        {
            Close();
            return FALSE;
        }

        // create the history folder status recordset
        m_pHistoryFolderStatusRecordset =
                new PSS_HistoryFolderStatusRecordset(&m_ProcessHistoryDatabase, m_DatabaseFileName);

        if (!m_pHistoryFolderStatusRecordset)
        {
            Close();
            return FALSE;
        }

        // create the history activity status recordset
        m_pHistoryActivityStatusRecordset =
                new PSS_HistoryActivityStatusRecordset(&m_ProcessHistoryDatabase, m_DatabaseFileName);

        if (!m_pHistoryActivityStatusRecordset)
        {
            Close();
            return FALSE;
        }

        // create the history process recordset
        m_pHistoryProcessRecordset =
                new PSS_HistoryProcessRecordset(&m_ProcessHistoryDatabase, m_DatabaseFileName);

        if (!m_pHistoryProcessRecordset)
        {
            Close();
            return FALSE;
        }

        // create the history process status recordset
        m_pHistoryProcessStatusRecordset =
                new PSS_HistoryProcessStatusRecordset(&m_ProcessHistoryDatabase, m_DatabaseFileName);

        if (!m_pHistoryProcessStatusRecordset)
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
//---------------------------------------------------------------------------
