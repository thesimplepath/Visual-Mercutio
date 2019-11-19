/****************************************************************************
 * ==> PSS_ProcessHistoryDatabase ------------------------------------------*
 ****************************************************************************
 * Description : Provides a process history database                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessHistoryDatabaseH
#define PSS_ProcessHistoryDatabaseH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ActivityEvent.h"
#include "PSS_ProcessHistoryDAODatabase.h"

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
* Process history database
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessHistoryDatabase
{
    public:
        /**
        * Database type
        */
        enum IEType
        {
            IE_DT_DAO,
            IE_DT_ODBC
        };

        /**
        * Constructor
        *@param fileName - the database file name
        *@param type - the database type
        */
        PSS_ProcessHistoryDatabase(const CString& fileName = "", IEType type = IE_DT_DAO);

        virtual ~PSS_ProcessHistoryDatabase();

        /**
        * Creates the database
        *@param fileName - the database file name
        *@param type - the database type
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const CString& fileName = "", IEType type = IE_DT_DAO);

        /**
        * Initializes the database
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Initialize();

        /**
        * Gets the database file name
        *@return the database file name
        */
        virtual inline const CString GetDatabaseFileName() const;

        /**
        * Sets the database file name
        *@param value - the database file name
        */
        virtual inline void SetDatabaseFileName(const CString& value);

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
        PSS_ProcessHistoryDAODatabase* m_pProcessHistoDAO;
        IEType                         m_Type;
        CString                        m_FileName;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProcessHistoryDatabase(const PSS_ProcessHistoryDatabase& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ProcessHistoryDatabase& operator = (const PSS_ProcessHistoryDatabase& other);
};

//---------------------------------------------------------------------------
// PSS_ProcessHistoryDatabase
//---------------------------------------------------------------------------
const CString PSS_ProcessHistoryDatabase::GetDatabaseFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_ProcessHistoryDatabase::SetDatabaseFileName(const CString& value)
{
    m_FileName = value;
}
//---------------------------------------------------------------------------

#endif
