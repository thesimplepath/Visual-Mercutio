/****************************************************************************
 * ==> PSS_HistoryActivityRecordsetVersion99 -------------------------------*
 ****************************************************************************
 * Description : Provides an historic activity recordset (version 99)       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HistoryActivityRecordsetVersion99H
#define PSS_HistoryActivityRecordsetVersion99H

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
* History activity recordset (version 99)
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_HistoryActivityRecordsetVersion99 : public CDaoRecordset
{
    DECLARE_DYNAMIC(PSS_HistoryActivityRecordsetVersion99)

    public:
        /**
        * Constructor
        *@param pDatabase - database
        *@param fileName - database file name
        */
        PSS_HistoryActivityRecordsetVersion99(CDaoDatabase* pDatabase = NULL, const CString& fileName = "");

        /**
        * Gets the activity identifier field name
        *@return the activity identifier field name
        */
        virtual inline CString GetActivityIDFieldName() const;

        /**
        * Gets the process identifier field name
        *@return the process identifier field name
        */
        virtual inline CString GetProcessIDFieldName() const;

        /**
        * Gets the name field name
        *@return the name field name
        */
        virtual inline CString GetNameFieldName() const;

        /**
        * Gets the start date field name
        *@return the start date field name
        */
        virtual inline CString GetStartDateFieldName() const;

        /**
        * Gets the end date field name
        *@return the end date field name
        */
        virtual inline CString GetEndDateFieldName() const;

        /**
        * Gets the initiator field name
        *@return the initiator field name
        */
        virtual inline CString GetInitiatorFieldName() const;

        /**
        * Gets the receiver field name
        *@return the receiver field name
        */
        virtual inline CString GetReceiverFieldName() const;

        /**
        * Gets the status field name
        *@return the status field name
        */
        virtual inline CString GetStatusFieldName() const;

        /**
        * Gets the comment field name
        *@return the comment field name
        */
        virtual inline CString GetCommentFieldName() const;

        /**
        * Gets the in backup field name
        *@return the in backup field name
        */
        virtual inline CString GetInBackupFieldName() const;

        /**
        * Gets the activity identifier
        *@return the activity identifier
        */
        virtual inline long GetActivityID() const;

        /**
        * Sets the activity identifier
        *@param value - the activity identifier
        */
        virtual inline void SetActivityID(long value);

        /**
        * Gets the process identifier
        *@return the process identifier
        */
        virtual inline long GetProcessID() const;

        /**
        * Sets the process identifier
        *@param value - the process identifier
        */
        virtual inline void SetProcessID(long value);

        /**
        * Gets the name
        *@return the name
        */
        virtual inline CString GetName() const;

        /**
        * Sets the name
        *@param value - the name
        */
        virtual inline void SetName(const CString& value);

        /**
        * Gets the start date
        *@return the start date
        */
        virtual inline COleDateTime GetStartDate() const;

        /**
        * Sets the start date
        *@param value - the start date
        */
        virtual inline void SetStartDate(const COleDateTime& value);

        /**
        * Gets the end date
        *@return the end date
        */
        virtual inline COleDateTime GetEndDate() const;

        /**
        * Sets the end date
        *@param value - the end date
        */
        virtual inline void SetEndDate(const COleDateTime& value);

        /**
        * Gets the initiator
        *@return the initiator
        */
        virtual inline CString GetInitiator() const;

        /**
        * Sets the initiator
        *@param value - the initiator
        */
        virtual inline void SetInitiator(const CString& value);

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
        * Gets the status
        *@return the status
        */
        virtual inline CString GetStatus() const;

        /**
        * Sets the status
        *@return the status
        */
        virtual inline void SetStatus(const CString& value);

        /**
        * Gets the comments
        *@return the comments
        */
        virtual inline CString GetComment() const;

        /**
        * Sets the comments
        *@param value - the comments
        */
        virtual inline void SetComment(const CString& value);

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
        COleDateTime m_StartDate;
        COleDateTime m_EndDate;
        CString      m_Name;
        CString      m_Initiator;
        CString      m_Receiver;
        CString      m_Status;
        CString      m_Comment;
        CString      m_DatabaseFileName;
        long         m_ActivityID;
        long         m_ProcessID;
        BOOL         m_InBackup;
};

//---------------------------------------------------------------------------
// PSS_HistoryActivityRecordsetVersion99
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetActivityIDFieldName() const
{
    return _T("[ActivityID]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetProcessIDFieldName() const
{
    return _T("[ProcessID]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetNameFieldName() const
{
    return _T("[Name]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetStartDateFieldName() const
{
    return _T("[StartDate]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetEndDateFieldName() const
{
    return _T("[EndDate]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetInitiatorFieldName() const
{
    return _T("[Initiator]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetReceiverFieldName() const
{
    return _T("[Receiver]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetStatusFieldName() const
{
    return _T("[Status]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetCommentFieldName() const
{
    return _T("[Comment]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetInBackupFieldName() const
{
    return _T("[InBackup]");
}
//---------------------------------------------------------------------------
long PSS_HistoryActivityRecordsetVersion99::GetActivityID() const
{
    return m_ActivityID;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordsetVersion99::SetActivityID(long value)
{
    m_ActivityID = value;
}
//---------------------------------------------------------------------------
long PSS_HistoryActivityRecordsetVersion99::GetProcessID() const
{
    return m_ProcessID;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordsetVersion99::SetProcessID(long value)
{
    m_ProcessID = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordsetVersion99::SetName(const CString& value)
{
    m_Name = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_HistoryActivityRecordsetVersion99::GetStartDate() const
{
    return m_StartDate;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordsetVersion99::SetStartDate(const COleDateTime& value)
{
    m_StartDate = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_HistoryActivityRecordsetVersion99::GetEndDate() const
{
    return m_EndDate;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordsetVersion99::SetEndDate(const COleDateTime& value)
{
    m_EndDate = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetInitiator() const
{
    return m_Initiator;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordsetVersion99::SetInitiator(const CString& value)
{
    m_Initiator = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetReceiver() const
{
    return m_Receiver;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordsetVersion99::SetReceiver(const CString& value)
{
    m_Receiver = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetStatus() const
{
    return m_Status;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordsetVersion99::SetStatus(const CString& value)
{
    m_Status = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetComment() const
{
    return m_Comment;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordsetVersion99::SetComment(const CString& value)
{
    m_Comment = value;
}
//---------------------------------------------------------------------------
BOOL PSS_HistoryActivityRecordsetVersion99::GetInBackup() const
{
    return m_InBackup;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordsetVersion99::SetInBackup(BOOL value)
{
    m_InBackup = value;
}
//---------------------------------------------------------------------------

#endif
