/****************************************************************************
 * ==> PSS_ActivityLogFile -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity log file                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityLogFileH
#define PSS_ActivityLogFileH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ActivityEvent.h"

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
* Activity log file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityLogFile
{
    public:
        /**
        * Constructor
        *@param fileName - log file name
        */
        PSS_ActivityLogFile(const CString& fileName = "");

        virtual ~PSS_ActivityLogFile();

        /**
        * Creates the file
        *@param fileName - log file name
        */
        virtual void Create(CString LogFileName);

        /**
        * Writes a line in the file
        *@param line - line to write
        *@return TRUE on success, otherwise FALSE
        */
        BOOL WriteLine(CString& Line);

        /**
        * Appends an event to the log
        *@param activityEvent - activity event to append
        *@return TRUE on success, otherwise FALSE
        */
        BOOL AppendToLog(const PSS_ActivityEvent& activityEvent);

        /**
        * Clears the log
        *@return TRUE on success, otherwise FALSE
        */
        BOOL ClearLog();

        /**
        * Closes the log file
        *@return TRUE on success, otherwise FALSE
        */
        BOOL Close();

    private:
        CString m_LogFileName;
        CFile   m_File;
        BOOL    m_IsOpen;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityLogFile(const PSS_ActivityLogFile& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityLogFile& operator = (const PSS_ActivityLogFile& other);

        /**
        * Opens the file, creates it if not exists
        *@return TRUE on success, otherwise FALSE
        */
        BOOL OpenCreate();

        /**
        * Opens the file for read
        *@return TRUE on success, otherwise FALSE
        */
        BOOL OpenRead();

        /**
        * Opens the file for write
        *@return TRUE on success, otherwise FALSE
        */
        BOOL OpenWrite();
};

#endif
