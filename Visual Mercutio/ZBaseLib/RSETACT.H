/****************************************************************************
 * ==> PSS_ActivityLogRecordSet --------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity log record set                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityLogRecordSetH
#define PSS_ActivityLogRecordSetH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Activity log record set
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityLogRecordSet : public CRecordset
{
    DECLARE_DYNAMIC(PSS_ActivityLogRecordSet)

    public:
        CString m_FolderName;
        CString m_File;
        CString m_DataFile;
        CString m_Process;
        CString m_Activity;
        CString m_Status;
        CString m_Sender;
        CString m_Receiver;
        CString m_Comments;
        CTime   m_Date;
        CTime   m_DueDate;

        /**
        * Constructor
        *@param pDatabase - database, can be NULL
        */
        PSS_ActivityLogRecordSet(CDatabase* pDatabase = NULL);

    protected:
        /**
        * Gets the default connection string
        *@return the default connection string
        */
        virtual CString GetDefaultConnect() const;

        /**
        * Gets the default SQL for recordset
        *@return the default SQL for recordset
        */
        virtual CString GetDefaultSQL() const;

        /**
        * RFX support
        *@param pFX - RFX data
        */
        virtual void DoFieldExchange(CFieldExchange* pFX);
};

#endif
