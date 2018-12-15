// HistoryProcessStatusRecordSet.h : interface of the ZDHistoryProcessStatusRecordset class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HistoryProcessStatusRecordSet_H__293D9E35_F146_11D3_96DD_0000B45D7C6F__INCLUDED_)
#define AFX_HistoryProcessStatusRecordSet_H__293D9E35_F146_11D3_96DD_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ZDHistoryProcessStatusRecordset : public CDaoRecordset
{
public:
    ZDHistoryProcessStatusRecordset(CDaoDatabase* pDatabase = NULL, CString DatabaseFilename = "");
    DECLARE_DYNAMIC(ZDHistoryProcessStatusRecordset)


    const CString GetProcessStatusIDFieldName() const { return _T("[ProcessStatusID]"); };
    const CString GetProcessIDFieldName() const { return _T("[ProcessID]"); };
    const CString GetDateFieldName() const { return _T("[Date]"); };
    const CString GetStartDateFieldName() const { return _T("[StartDate]"); };
    const CString GetEndDateFieldName() const { return _T("[EndDate]"); };
    const CString GetStatusFieldName() const { return _T("[Status]"); };
    const CString GetCurrentActivityFieldName() const { return _T("[CurrentActivity]"); };

    long    GetProcessStatusID() const { return m_ProcessStatusID; };
    void    SetProcessStatusID( long value ) { m_ProcessStatusID = value; };

    long    GetProcessID() const { return m_ProcessID; };
    void    SetProcessID( long value ) { m_ProcessID = value; };

    COleDateTime    GetDate() const { return m_Date; };
    void    SetDate( COleDateTime value ) { m_Date = value; };

    COleDateTime    GetStartDate() const { return m_StartDate; };
    void    SetStartDate( COleDateTime value ) { m_StartDate = value; };

    COleDateTime    GetEndDate() const { return m_EndDate; };
    void    SetEndDate( COleDateTime value ) { m_EndDate = value; };

    CString    GetStatus() const { return m_Status; };
    void    SetStatus( CString value ) { m_Status = value; };

    long    GetCurrentActivity() const { return m_CurrentActivity; };
    void    SetCurrentActivity( long value ) { m_CurrentActivity = value; };


private:
// Field/Param Data
    //{{AFX_FIELD(ZDHistoryProcessStatusRecordset, CDaoRecordset)
    long    m_ProcessStatusID;
    long    m_ProcessID;
    COleDateTime    m_Date;
    COleDateTime    m_StartDate;
    COleDateTime    m_EndDate;
    CString    m_Status;
    long    m_CurrentActivity;
    //}}AFX_FIELD

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDHistoryProcessStatusRecordset)
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

#endif // !defined(AFX_HistoryProcessStatusRecordSet_H__293D9E35_F146_11D3_96DD_0000B45D7C6F__INCLUDED_)

