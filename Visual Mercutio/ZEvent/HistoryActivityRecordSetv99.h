// HistoryActivityRecordSetv99.h : interface of the ZDHistoryActivityRecordsetVersion99 class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HistoryActivityRecordSetv99_H__293D9E4D_F146_11D3_96DD_0000B45D7C6F__INCLUDED_)
#define AFX_HistoryActivityRecordSetv99_H__293D9E4D_F146_11D3_96DD_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ZDHistoryActivityRecordsetVersion99 : public CDaoRecordset
{
public:
    ZDHistoryActivityRecordsetVersion99(CDaoDatabase* pDatabase = NULL, CString DatabaseFilename = "");
    DECLARE_DYNAMIC(ZDHistoryActivityRecordsetVersion99)

    CString GetActivityIDFieldName() const { return _T("[ActivityID]"); };
    CString GetProcessIDFieldName() const { return _T("[ProcessID]"); };
    CString GetNameFieldName() const { return _T("[Name]"); };
    CString GetStartDateFieldName() const { return _T("[StartDate]"); };
    CString GetEndDateFieldName() const { return _T("[EndDate]"); };
    CString GetInitiatorFieldName() const { return _T("[Initiator]"); };
    CString GetReceiverFieldName() const { return _T("[Receiver]"); };
    CString GetStatusFieldName() const { return _T("[Status]"); };
    CString GetCommentFieldName() const { return _T("[Comment]"); };
    CString GetInBackupFieldName() const { return _T("[InBackup]"); };

    long    GetActivityID() const { return m_ActivityID; };
    void    SetActivityID( long value ) { m_ActivityID = value; };

    long    GetProcessID() const { return m_ProcessID; };
    void    SetProcessID( long value ) { m_ProcessID = value; };

    CString    GetName() const { return m_Name; };
    void    SetName( CString value ) { m_Name = value; };

    COleDateTime    GetStartDate() const { return m_StartDate; };
    void    SetStartDate( COleDateTime value ) { m_StartDate = value; };

    COleDateTime    GetEndDate() const { return m_EndDate; };
    void    SetEndDate( COleDateTime value ) { m_EndDate = value; };

    CString    GetInitiator() const { return m_Initiator; };
    void    SetInitiator( CString value ) { m_Initiator = value; };

    CString    GetReceiver() const { return m_Receiver; };
    void    SetReceiver( CString value ) { m_Receiver = value; };

    CString    GetStatus() const { return m_Status; };
    void    SetStatus( CString value ) { m_Status = value; };

    CString    GetComment() const { return m_Comment; };
    void    SetComment( CString value ) { m_Comment = value; };

    BOOL    GetInBackup() const { return m_InBackup; };
    void    SetInBackup( BOOL value ) { m_InBackup = value; }

private:
// Field/Param Data
    //{{AFX_FIELD(ZDHistoryActivityRecordsetVersion99, CDaoRecordset)
    long    m_ActivityID;
    long    m_ProcessID;
    CString    m_Name;
    COleDateTime    m_StartDate;
    COleDateTime    m_EndDate;
    CString    m_Initiator;
    CString m_Receiver;
    CString m_Status;
    CString    m_Comment;
    BOOL    m_InBackup;
    //}}AFX_FIELD

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDHistoryActivityRecordsetVersion99)
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
    CString        m_DatabaseFilename;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HistoryActivityRecordSetv99_H__293D9E4D_F146_11D3_96DD_0000B45D7C6F__INCLUDED_)

