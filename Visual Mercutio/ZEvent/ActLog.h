/****************************************************************************
 * ==> PSS_ActivityLog -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity logger                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityLogH
#define PSS_ActivityLogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "ActEvent.h"
#include "ActLogFl.h"
#include "ActLogDB.h"

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
* Activity logger
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityLog
{
    public:
        /**
        * Constructor
        *@param fileName - log file name
        *@param useDatabase - if TRUE, a database will be used instead of a file
        */
        PSS_ActivityLog(const CString& fileName = "", BOOL useDatabase = FALSE);

        virtual ~PSS_ActivityLog();

        /**
        * Creates the logger
        *@param fileName - log file name
        *@param useDatabase - if TRUE, a database will be used instead of a file
        */
        virtual BOOL Create(const CString& fileName, BOOL useDatabase = FALSE);

        /**
        * Initializes the logger
        */
        virtual BOOL Initialize();

        /**
        * Gets the log file name
        *@return the log file name
        */
        virtual inline const CString GetFileName() const;

        /**
        * Sets the log file name
        *@param value - the log file name
        */
        virtual inline void SetFileName(const CString& value);

        /**
        * Appends an activity to the log
        *@param eventActivity - event activity
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AppendToLog(const ZBEventActivity& eventActivity);

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
        ZUActivityLogDatabase* m_pActivityLogDatabase;
        ZUActivityLogFile*     m_pActivityLogFile;
        CString                m_FileName;
        BOOL                   m_UseDatabase;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityLog(const PSS_ActivityLog& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityLog& operator = (const PSS_ActivityLog& other);
};

//---------------------------------------------------------------------------
// PSS_ActivityLog
//---------------------------------------------------------------------------
const CString PSS_ActivityLog::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_ActivityLog::SetFileName(const CString& value)
{
    m_FileName = value;
}
//---------------------------------------------------------------------------

#endif
