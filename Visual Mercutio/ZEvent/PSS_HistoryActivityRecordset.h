/****************************************************************************
 * ==> PSS_HistoryActivityRecordset ----------------------------------------*
 ****************************************************************************
 * Description : Provides an historic activity recordset                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HistoryActivityRecordsetH
#define PSS_HistoryActivityRecordsetH

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
* History activity recordset
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_HistoryActivityRecordset : public CDaoRecordset
{
    DECLARE_DYNAMIC(PSS_HistoryActivityRecordset)

    public:
        /**
        * Constructor
        *@param pDatabase - database
        *@param fileName - database file name
        */
        PSS_HistoryActivityRecordset(CDaoDatabase* pDatabase = NULL, const CString& fileName = "");

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
        * Gets the date field name
        *@return the date field name
        */
        virtual inline CString GetDateFieldName() const;

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
        * Gets the initial days field name
        *@return the initial days field name
        */
        virtual inline CString GetInitialDaysFieldName() const;

        /**
        * Gets the forecasted end date field name
        *@return the forecasted end date field name
        */
        virtual inline CString GetForecastedEndDateFieldName() const;

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
        * Gets the initial days
        *@return the initial days
        */
        virtual inline long GetInitialDays() const;

        /**
        * Sets the inital days
        *@param value - the initial days
        */
        virtual inline void SetInitialDays(long value);

        /**
        * Gets the forecasted end date
        *@return the forecasted end date
        */
        virtual inline COleDateTime GetForecastedEndDate() const;

        /**
        * Sets the forecasted end date
        *@param value - the forecasted end date
        */
        virtual inline void SetForecastedEndDate(const COleDateTime& value);

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
        COleDateTime m_Date;
        COleDateTime m_StartDate;
        COleDateTime m_EndDate;
        COleDateTime m_ForecastedEndDate;
        CString      m_Name;
        CString      m_Initiator;
        CString      m_Receiver;
        CString      m_Status;
        CString      m_Comment;
        CString      m_DatabaseFilename;
        long         m_ActivityID;
        long         m_ProcessID;
        long         m_InitialDays;
        BOOL         m_InBackup;
};

//---------------------------------------------------------------------------
// PSS_HistoryActivityRecordset
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetActivityIDFieldName() const
{
    return _T("[ActivityID]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetProcessIDFieldName() const
{
    return _T("[ProcessID]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetNameFieldName() const
{
    return _T("[Name]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetDateFieldName() const
{
    return _T("[Date]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetStartDateFieldName() const
{
    return _T("[StartDate]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetEndDateFieldName() const
{
    return _T("[EndDate]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetInitialDaysFieldName() const
{
    return _T("[InitialDays]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetForecastedEndDateFieldName() const
{
    return _T("[ForecastedEndDate]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetInitiatorFieldName() const
{
    return _T("[Initiator]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetReceiverFieldName() const
{
    return _T("[Receiver]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetStatusFieldName() const
{
    return _T("[Status]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetCommentFieldName() const
{
    return _T("[Comment]");
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetInBackupFieldName() const
{
    return _T("[InBackup]");
}
//---------------------------------------------------------------------------
long PSS_HistoryActivityRecordset::GetActivityID() const
{
    return m_ActivityID;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetActivityID(long value)
{
    m_ActivityID = value;
}
//---------------------------------------------------------------------------
long PSS_HistoryActivityRecordset::GetProcessID() const
{
    return m_ProcessID;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetProcessID(long value)
{
    m_ProcessID = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetName(const CString& value)
{
    m_Name = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_HistoryActivityRecordset::GetDate() const
{
    return m_Date;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetDate(const COleDateTime& value)
{
    m_Date = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_HistoryActivityRecordset::GetStartDate() const
{
    return m_StartDate;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetStartDate(const COleDateTime& value)
{
    m_StartDate = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_HistoryActivityRecordset::GetEndDate() const
{
    return m_EndDate;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetEndDate(const COleDateTime& value)
{
    m_EndDate = value;
}
//---------------------------------------------------------------------------
long PSS_HistoryActivityRecordset::GetInitialDays() const
{
    return m_InitialDays;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetInitialDays(long value)
{
    m_InitialDays = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_HistoryActivityRecordset::GetForecastedEndDate() const
{
    return m_ForecastedEndDate;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetForecastedEndDate(const COleDateTime& value)
{
    m_ForecastedEndDate = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetInitiator() const
{
    return m_Initiator;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetInitiator(const CString& value)
{
    m_Initiator = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetReceiver() const
{
    return m_Receiver;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetReceiver(const CString& value)
{
    m_Receiver = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetStatus() const
{
    return m_Status;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetStatus(const CString& value)
{
    m_Status = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetComment() const
{
    return m_Comment;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetComment(const CString& value)
{
    m_Comment = value;
}
//---------------------------------------------------------------------------
BOOL PSS_HistoryActivityRecordset::GetInBackup() const
{
    return m_InBackup;
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::SetInBackup(BOOL value)
{
    m_InBackup = value;
}
//---------------------------------------------------------------------------

#endif
