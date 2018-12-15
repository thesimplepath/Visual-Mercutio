#if !defined(AFX_ZDACTIVITYLOGRECORDSET_H__67E841D7_310B_11D3_95D4_0000B45D7C6F__INCLUDED_)
#define AFX_ZDACTIVITYLOGRECORDSET_H__67E841D7_310B_11D3_95D4_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZDActivityLogRecordset.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// ZDActivityLogRecordset DAO recordset

class ZDActivityLogRecordset : public CDaoRecordset
{
public:
    ZDActivityLogRecordset(CDaoDatabase* pDatabase = NULL, CString DatabaseFilename = "");
    DECLARE_DYNAMIC(ZDActivityLogRecordset)

    // Get & Set methods
    COleDateTime    GetDate() const { return m_Date; };
    void    SetDate( COleDateTime value ) { m_Date = value; }
    
    CString    GetEventType() const { return m_EventType; };
    void    SetEventType( CString value ) { m_EventType = value; }
    
    CString    GetProcessFilename() const { return m_ProcessFilename; };
    void    SetProcessFilename( CString value ) { m_ProcessFilename = value; }
    
    CString    GetFormDataFilename() const { return m_FormDataFilename; };
    void    SetFormDataFilename( CString value ) { m_FormDataFilename = value; }

    CString    GetProcessDataFilename() const { return m_ProcessDataFilename; };
    void    SetProcessDataFilename( CString value ) { m_ProcessDataFilename = value; }
    
    CString    GetFolderName() const { return m_FolderName; };
    void    SetFolderName( CString value ) { m_FolderName = value; }
    
    CString    GetActivityType() const { return m_ActivityType; };
    void    SetActivityType( CString value ) { m_ActivityType = value; }
    
    CString    GetProcessName() const { return m_ProcessName; };
    void    SetProcessName( CString value ) { m_ProcessName = value; }
    
    COleDateTime    GetProcessCreationDate() const { return m_ProcessCreationDate; };
    void    SetProcessCreationDate( COleDateTime value ) { m_ProcessCreationDate = value; }
    
    COleDateTime    GetProcessDueDate() const { return m_ProcessDueDate; };
    void    SetProcessDueDate( COleDateTime value ) { m_ProcessDueDate = value; }
    
    CString    GetActivityName() const { return m_ActivityName; };
    void    SetActivityName( CString value ) { m_ActivityName = value; }
    
    COleDateTime    GetActivityCreationDate() const { return m_ActivityCreationDate; };
    void    SetActivityCreationDate( COleDateTime value ) { m_ActivityCreationDate = value; }
    
    COleDateTime    GetActivityDueDate() const { return m_ActivityDueDate; };
    void    SetActivityDueDate( COleDateTime value ) { m_ActivityDueDate = value; }
    
    CString    GetActivityStatus() const { return m_ActivityStatus; };
    void    SetActivityStatus( CString value ) { m_ActivityStatus = value; }
    
    CString    GetSender() const { return m_Sender; };
    void    SetSender( CString value ) { m_Sender = value; }
    
    CString    GetReceiver() const { return m_Receiver; };
    void    SetReceiver( CString value ) { m_Receiver = value; }
    
    CString    GetComments() const { return m_Comments; };
    void    SetComments( CString value ) { m_Comments = value; }

    BOOL    GetInBackup() const { return m_InBackup; };
    void    SetInBackup( BOOL value ) { m_InBackup = value; }
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDActivityLogRecordset)
    public:
    virtual CString GetDefaultDBName();        // Default database name
    virtual CString GetDefaultSQL();        // Default SQL for Recordset
    virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
    //}}AFX_VIRTUAL

private:
// Field/Param Data
    //{{AFX_FIELD(ZDActivityLogRecordset, CDaoRecordset)
    COleDateTime    m_Date;
    CString    m_EventType;
    CString    m_ProcessFilename;
    CString    m_FormDataFilename;
    CString    m_ProcessDataFilename;
    CString    m_FolderName;
    CString    m_ProcessName;
    COleDateTime    m_ProcessCreationDate;
    COleDateTime    m_ProcessDueDate;
    CString    m_ActivityType;
    CString    m_ActivityName;
    COleDateTime    m_ActivityCreationDate;
    COleDateTime    m_ActivityDueDate;
    CString    m_ActivityStatus;
    CString    m_Sender;
    CString    m_Receiver;
    CString    m_Comments;
    BOOL    m_InBackup;
    //}}AFX_FIELD

    CString        m_DatabaseFilename;
// Implementation
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDACTIVITYLOGRECORDSET_H__67E841D7_310B_11D3_95D4_0000B45D7C6F__INCLUDED_)
