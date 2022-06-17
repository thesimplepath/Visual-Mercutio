/****************************************************************************
 * ==> PSS_ActivityLogDatabase ---------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity log database                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef ActLogDB_h
#define ActLogDB_h 1

#pragma warning(disable: 4101)

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ActivityEvent.h"
#include "PSS_ActivityLogRecordset.h"

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
* Activity log database
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityLogDatabase
{
    public:
        /**
        * Constructor
        *@param fileName - log file name
        */
        PSS_ActivityLogDatabase(const CString& fileName = "");

        virtual ~PSS_ActivityLogDatabase();

        /**
        * Creates the logger
        *@param fileName - log file name
        */
        virtual void Create(const CString& fileName);

        /**
        * Gets the log file name
        *@return the log file name
        */
        virtual inline const CString GetFileName() const;

        /**
        * Appends an activity event to the log
        *@param activityEvent - event activity
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AppendToLog(const PSS_ActivityEvent& activityEvent);

        /**
        * Clears the logg
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ClearLog();

        /**
        * Closes the logg
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Close();

    private:
        CDaoDatabase              m_Database;
        PSS_ActivityLogRecordset* m_pRecordset;
        CString                   m_FileName;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityLogDatabase(const PSS_ActivityLogDatabase& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityLogDatabase& operator=(const PSS_ActivityLogDatabase& other);

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

//---------------------------------------------------------------------------
// PSS_ActivityLogDatabase
//---------------------------------------------------------------------------
const CString PSS_ActivityLogDatabase::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------

#endif
