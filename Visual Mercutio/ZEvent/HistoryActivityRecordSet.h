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
class ZDHistoryActivityRecordset : public CDaoRecordset
{
public:
    ZDHistoryActivityRecordset(CDaoDatabase* pDatabase = NULL, CString DatabaseFilename = "");
    DECLARE_DYNAMIC(ZDHistoryActivityRecordset)

    CString GetActivityIDFieldName() const
    {
        return _T("[ActivityID]");
    };
    CString GetProcessIDFieldName() const
    {
        return _T("[ProcessID]");
    };
    CString GetNameFieldName() const
    {
        return _T("[Name]");
    };
    CString GetDateFieldName() const
    {
        return _T("[Date]");
    };
    CString GetStartDateFieldName() const
    {
        return _T("[StartDate]");
    };
    CString GetEndDateFieldName() const
    {
        return _T("[EndDate]");
    };
    CString GetInitialDaysFieldName() const
    {
        return _T("[InitialDays]");
    };
    CString GetForecastedEndDateFieldName() const
    {
        return _T("[ForecastedEndDate]");
    };
    CString GetInitiatorFieldName() const
    {
        return _T("[Initiator]");
    };
    CString GetReceiverFieldName() const
    {
        return _T("[Receiver]");
    };
    CString GetStatusFieldName() const
    {
        return _T("[Status]");
    };
    CString GetCommentFieldName() const
    {
        return _T("[Comment]");
    };
    CString GetInBackupFieldName() const
    {
        return _T("[InBackup]");
    };

    long    GetActivityID() const
    {
        return m_ActivityID;
    };
    void    SetActivityID(long value)
    {
        m_ActivityID = value;
    };

    long    GetProcessID() const
    {
        return m_ProcessID;
    };
    void    SetProcessID(long value)
    {
        m_ProcessID = value;
    };

    CString    GetName() const
    {
        return m_Name;
    };
    void    SetName(CString value)
    {
        m_Name = value;
    };

    COleDateTime    GetDate() const
    {
        return m_Date;
    };
    void    SetDate(COleDateTime value)
    {
        m_Date = value;
    };

    COleDateTime    GetStartDate() const
    {
        return m_StartDate;
    };
    void    SetStartDate(COleDateTime value)
    {
        m_StartDate = value;
    };

    COleDateTime    GetEndDate() const
    {
        return m_EndDate;
    };
    void    SetEndDate(COleDateTime value)
    {
        m_EndDate = value;
    };

    long    GetInitialDays() const
    {
        return m_InitialDays;
    };
    void    SetInitialDays(long value)
    {
        m_InitialDays = value;
    };

    COleDateTime    GetForecastedEndDate() const
    {
        return m_ForecastedEndDate;
    };
    void    SetForecastedEndDate(COleDateTime value)
    {
        m_ForecastedEndDate = value;
    };

    CString    GetInitiator() const
    {
        return m_Initiator;
    };
    void    SetInitiator(CString value)
    {
        m_Initiator = value;
    };

    CString    GetReceiver() const
    {
        return m_Receiver;
    };
    void    SetReceiver(CString value)
    {
        m_Receiver = value;
    };

    CString    GetStatus() const
    {
        return m_Status;
    };
    void    SetStatus(CString value)
    {
        m_Status = value;
    };

    CString    GetComment() const
    {
        return m_Comment;
    };
    void    SetComment(CString value)
    {
        m_Comment = value;
    };

    BOOL    GetInBackup() const
    {
        return m_InBackup;
    };
    void    SetInBackup(BOOL value)
    {
        m_InBackup = value;
    }

private:
    // Field/Param Data
        //{{AFX_FIELD(ZDHistoryActivityRecordset, CDaoRecordset)
    long    m_ActivityID;
    long    m_ProcessID;
    CString    m_Name;
    COleDateTime    m_Date;
    COleDateTime    m_StartDate;
    COleDateTime    m_EndDate;
    long    m_InitialDays;
    COleDateTime    m_ForecastedEndDate;
    CString    m_Initiator;
    CString m_Receiver;
    CString m_Status;
    CString    m_Comment;
    BOOL    m_InBackup;
    //}}AFX_FIELD

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDHistoryActivityRecordset)
public:
    virtual CString GetDefaultDBName();        // REVIEW:  Get a comment here
    virtual CString GetDefaultSQL();     // default SQL for Recordset
    virtual void DoFieldExchange(CDaoFieldExchange* pFX);    // RFX support
    //}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
    CString m_DatabaseFilename;
};

#endif
