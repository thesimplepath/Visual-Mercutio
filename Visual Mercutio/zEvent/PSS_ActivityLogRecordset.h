/****************************************************************************
 * ==> PSS_ActivityLogRecordset --------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity log recordset                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityLogRecordsetH
#define PSS_ActivityLogRecordsetH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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
* Activity log recordset
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ActivityLogRecordset : public CDaoRecordset
{
    DECLARE_DYNAMIC(PSS_ActivityLogRecordset)

    public:
        PSS_ActivityLogRecordset(CDaoDatabase* pDatabase = NULL, const CString& fileName = "");

        /**
        * Gets the date
        *@return the date
        */
        virtual inline COleDateTime GetDate() const;

        /**
        * Sets the date
        *@param value - the date
        */
        virtual inline void SetDate(const COleDateTime& value);

        /**
        * Gets the event type
        *@return the event type
        */
        virtual inline CString GetEventType() const;

        /**
        * Sets the event type
        *@param value - the event type
        */
        virtual inline void SetEventType(const CString& value);

        /**
        * Gets the process file name
        *@return the process file name
        */
        virtual inline CString GetProcessFileName() const;

        /**
        * Sets the process file name
        *@param value - the process file name
        */
        virtual inline void SetProcessFileName(const CString& value);

        /**
        * Gets the form data file name
        *@return the form data file name
        */
        virtual inline CString GetFormDataFileName() const;

        /**
        * Sets the form data file name
        *@param value - the form data file name
        */
        virtual inline void SetFormDataFileName(const CString& value);

        /**
        * Gets the process data file name
        *@return the process data file name
        */
        virtual inline CString GetProcessDataFileName() const;

        /**
        * Sets the process data file name
        *@param value - the process data file name
        */
        virtual inline void SetProcessDataFileName(const CString& value);

        /**
        * Gets the folder name
        *@return the folder name
        */
        virtual inline CString GetFolderName() const;

        /**
        * Sets the folder name
        *@param value - the folder name
        */
        virtual inline void SetFolderName(const CString& value);

        /**
        * Gets the activity type
        *@return the activity type
        */
        virtual inline CString GetActivityType() const;

        /**
        * Sets the activity type
        *@param value - the activity type
        */
        virtual inline void SetActivityType(const CString& value);

        /**
        * Gets the process name
        *@return the process name
        */
        virtual inline CString GetProcessName() const;

        /**
        * Sets the process name
        *@param value - the process name
        */
        virtual inline void SetProcessName(const CString& value);

        /**
        * Gets the process creation date
        *@return the process creation date
        */
        virtual inline COleDateTime GetProcessCreationDate() const;

        /**
        * Sets the process creation date
        *@param value - the process creation date
        */
        virtual inline void SetProcessCreationDate(const COleDateTime& value);

        /**
        * Gets the process due date
        *@return the process due date
        */
        virtual inline COleDateTime GetProcessDueDate() const;

        /**
        * Sets the process due date
        *@param value - the process due date
        */
        virtual inline void SetProcessDueDate(const COleDateTime& value);

        /**
        * Gets the activity name
        *@return the activity name
        */
        virtual inline CString GetActivityName() const;

        /**
        * Sets the activity name
        *@param value - the activity name
        */
        virtual inline void SetActivityName(const CString& value);

        /**
        * Gets the activity creation date
        *@return the activity creation date
        */
        virtual inline COleDateTime GetActivityCreationDate() const;

        /**
        * Sets the activity creation date
        *@param value - the activity creation date
        */
        virtual inline void SetActivityCreationDate(const COleDateTime& value);

        /**
        * Gets the activity due date
        *@return the activity due date
        */
        virtual inline COleDateTime GetActivityDueDate() const;

        /**
        * Sets the activity due date
        *@param value - the activity due date
        */
        virtual inline void SetActivityDueDate(const COleDateTime& value);

        /**
        * Gets the activity status
        *@return the activity status
        */
        virtual inline CString GetActivityStatus() const;

        /**
        * Sets the activity status
        *@param value - the activity status
        */
        virtual inline void SetActivityStatus(const CString& value);

        /**
        * Gets the sender
        *@return the sender
        */
        virtual inline CString GetSender() const;

        /**
        * Sets the sender
        *@param value - the sender
        */
        virtual inline void SetSender(const CString& value);

        /**
        * Gets the receiver
        *@return the receiver
        */
        virtual inline CString GetReceiver() const;

        /**
        * Sets the receiver
        *@param value - the receiver
        */
        virtual inline void SetReceiver(const CString& value);

        /**
        * Gets the comments
        *@return the comments
        */
        virtual inline CString GetComments() const;

        /**
        * Sets the comments
        *@param value - the comments
        */
        virtual inline void SetComments(const CString& value);

        /**
        * Gets the in backup status
        *@return the in backup status
        */
        virtual inline BOOL GetInBackup() const;

        /**
        * Sets the in backup status
        *@param value - if TRUE, the status will be set to in backup
        */
        virtual inline void SetInBackup(BOOL value);

        /**
        * Gets the default database name
        *@return the default database name
        */
        virtual CString GetDefaultDBName();

        /**
        * Gets the default SQL for recordset
        *@return the default SQL for recordset
        */
        virtual CString GetDefaultSQL();

        /**
        * DDX/DDV data exchange
        *@param pFX - DDX/DDV data
        */
        virtual void DoFieldExchange(CDaoFieldExchange* pFX);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    private:
        COleDateTime m_Date;
        COleDateTime m_ProcessCreationDate;
        COleDateTime m_ProcessDueDate;
        COleDateTime m_ActivityCreationDate;
        COleDateTime m_ActivityDueDate;
        CString      m_EventType;
        CString      m_ProcessFileName;
        CString      m_FormDataFileName;
        CString      m_ProcessDataFileName;
        CString      m_FolderName;
        CString      m_ProcessName;
        CString      m_ActivityType;
        CString      m_ActivityName;
        CString      m_ActivityStatus;
        CString      m_Sender;
        CString      m_Receiver;
        CString      m_Comments;
        CString      m_DatabaseFileName;
        BOOL         m_InBackup;
};

//---------------------------------------------------------------------------
// PSS_ActivityLogRecordset
//---------------------------------------------------------------------------
COleDateTime PSS_ActivityLogRecordset::GetDate() const
{
    return m_Date;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetDate(const COleDateTime& value)
{
    m_Date = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetEventType() const
{
    return m_EventType;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetEventType(const CString& value)
{
    m_EventType = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetProcessFileName() const
{
    return m_ProcessFileName;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetProcessFileName(const CString& value)
{
    m_ProcessFileName = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetFormDataFileName() const
{
    return m_FormDataFileName;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetFormDataFileName(const CString& value)
{
    m_FormDataFileName = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetProcessDataFileName() const
{
    return m_ProcessDataFileName;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetProcessDataFileName(const CString& value)
{
    m_ProcessDataFileName = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetFolderName() const
{
    return m_FolderName;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetFolderName(const CString& value)
{
    m_FolderName = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetActivityType() const
{
    return m_ActivityType;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetActivityType(const CString& value)
{
    m_ActivityType = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetProcessName() const
{
    return m_ProcessName;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetProcessName(const CString& value)
{
    m_ProcessName = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_ActivityLogRecordset::GetProcessCreationDate() const
{
    return m_ProcessCreationDate;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetProcessCreationDate(const COleDateTime& value)
{
    m_ProcessCreationDate = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_ActivityLogRecordset::GetProcessDueDate() const
{
    return m_ProcessDueDate;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetProcessDueDate(const COleDateTime& value)
{
    m_ProcessDueDate = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetActivityName() const
{
    return m_ActivityName;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetActivityName(const CString& value)
{
    m_ActivityName = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_ActivityLogRecordset::GetActivityCreationDate() const
{
    return m_ActivityCreationDate;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetActivityCreationDate(const COleDateTime& value)
{
    m_ActivityCreationDate = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_ActivityLogRecordset::GetActivityDueDate() const
{
    return m_ActivityDueDate;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetActivityDueDate(const COleDateTime& value)
{
    m_ActivityDueDate = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetActivityStatus() const
{
    return m_ActivityStatus;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetActivityStatus(const CString& value)
{
    m_ActivityStatus = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetSender() const
{
    return m_Sender;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetSender(const CString& value)
{
    m_Sender = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetReceiver() const
{
    return m_Receiver;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetReceiver(const CString& value)
{
    m_Receiver = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetComments() const
{
    return m_Comments;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetComments(const CString& value)
{
    m_Comments = value;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogRecordset::GetInBackup() const
{
    return m_InBackup;
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::SetInBackup(BOOL value)
{
    m_InBackup = value;
}
//---------------------------------------------------------------------------

#endif
