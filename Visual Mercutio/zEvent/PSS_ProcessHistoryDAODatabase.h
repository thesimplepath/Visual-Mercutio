/****************************************************************************
 * ==> PSS_ProcessHistoryDAODatabase ---------------------------------------*
 ****************************************************************************
 * Description : Provides a process history DAO database                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessHistoryDAOH
#define PSS_ProcessHistoryDAOH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ActivityEvent.h"
#include "PSS_HistoryProcessRecordset.h"
#include "PSS_HistoryActivityRecordSet.h"
#include "PSS_HistoryActivityStatusRecordset.h"
#include "PSS_HistoryProcessStatusRecordset.h"
#include "PSS_HistoryFolderStatusRecordset.h"

#ifdef _ZEVENTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Process history DAO database
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessHistoryDAODatabase
{
    public:
        /**
        * Constructor
        *@param fileName - the database file name
        */
        PSS_ProcessHistoryDAODatabase(const CString& fileName = "");

        virtual ~PSS_ProcessHistoryDAODatabase();

        /**
        * Creates the database
        *@param fileName - the database file name
        */
        virtual void Create(const CString& fileName);

        /**
        * Appends an event to the historic
        *@param activityEvent - event to append
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AppendEventToHistoric(const PSS_ActivityEvent& activityEvent);

        /**
        * Closes the database
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Close();

    private:
        CDaoDatabase                        m_ProcessHistoryDatabase;
        PSS_HistoryActivityRecordset*       m_pHistoryActivityRecordset;
        PSS_HistoryActivityStatusRecordset* m_pHistoryActivityStatusRecordset;
        PSS_HistoryProcessRecordset*        m_pHistoryProcessRecordset;
        PSS_HistoryProcessStatusRecordset*  m_pHistoryProcessStatusRecordset;
        PSS_HistoryFolderStatusRecordset*   m_pHistoryFolderStatusRecordset;
        CString                             m_DatabaseFileName;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProcessHistoryDAODatabase(const PSS_ProcessHistoryDAODatabase& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ProcessHistoryDAODatabase& operator = (const PSS_ProcessHistoryDAODatabase& other);

        /**
        * Finds a process
        *@param activityEvent - the activity event
        *@return the process identifier, -1 if not found or on error
        */
        long FindProcess(const PSS_ActivityEvent& activityEvent);

        /**
        * Finds an activity
        *@param processID - the process identifier
        *@param currentDate - the current date
        *@param activityEvent - the activity event
        *@return the process identifier, -1 if not found or on error
        */
        long FindActivity(long processID, const PSS_Date& currentDate, const PSS_ActivityEvent& activityEvent);

        /**
        * Adds a new process record
        *@param activityEvent - the activity event
        *@return true on success, otherwise false
        */
        bool AddNewProcessRecord(const PSS_ActivityEvent& activityEvent);

        /**
        * Adds a process status record
        *@param processID - the process identifier
        *@param activityEvent - the activity event
        *@return true on success, otherwise false
        */
        bool AddProcessStatusRecord(long processID, const PSS_ActivityEvent& activityEvent);

        /**
        * Modifies a process status record
        *@param processID - the process identifier
        *@param activityEvent - the activity event
        *@return true on success, otherwise false
        */
        bool ModifyProcessStatusRecord(long processID, const PSS_ActivityEvent& activityEvent);

        /**
        * Adds an activity status record
        *@param processID - the process identifier
        *@param activityID - the activity identifier
        *@param activityEvent - the activity event
        *@return true on success, otherwise false
        */
        bool AddActivityStatusRecord(long processID, long activityID, const PSS_ActivityEvent& activityEvent);

        /**
        * Modifies an activity status record
        *@param processID - the process identifier
        *@param activityID - the activity identifier
        *@param activityEvent - the activity event
        *@return true on success, otherwise false
        */
        bool ModifyActivityStatusRecord(long processID, long activityID, const PSS_ActivityEvent& activityEvent);

        /**
        * Adds a folder status record
        *@param processID - the process identifier
        *@param activityID - the activity identifier
        *@param activityEvent - the activity event
        *@return true on success, otherwise false
        */
        bool AddFolderStatusRecord(long processID, long activityID, const PSS_ActivityEvent& activityEvent);

        /**
        * Modifies a folder status record
        *@param processID - the process identifier
        *@param activityID - the activity identifier
        *@param activityEvent - the activity event
        *@return true on success, otherwise false
        */
        bool ModifyFolderStatusRecord(long processID, long activityID, const PSS_ActivityEvent& activityEvent);

        /**
        * Opens the database for read
        *@return TRUE on success, otherwise FALSE
        */
        BOOL OpenRead();
 
        /**
        * Opens the database for write
        *@return TRUE on success, otherwise FALSE
        */
        BOOL OpenWrite();
};

#endif
