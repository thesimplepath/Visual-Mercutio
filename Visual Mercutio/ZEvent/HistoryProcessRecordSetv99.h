// HistoryProcessRecordSetv99.h : interface of the ZDHistoryProcessRecordsetVersion99 class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HistoryProcessRecordSetv99_H__293D9E35_F146_11D3_96DD_0000B45D7C6F__INCLUDED_)
#define AFX_HistoryProcessRecordSetv99_H__293D9E35_F146_11D3_96DD_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ZDHistoryProcessRecordsetVersion99 : public CDaoRecordset
{
public:
    ZDHistoryProcessRecordsetVersion99(CDaoDatabase* pDatabase = NULL, CString DatabaseFilename = "");
    DECLARE_DYNAMIC(ZDHistoryProcessRecordsetVersion99)


    const CString GetProcessIDFieldName() const { return _T("[ProcessID]"); };
    const CString GetNameFieldName() const { return _T("[Name]"); };
    const CString GetFilenameFieldName() const { return _T("[Filename]"); };
    const CString GetFolderNameFieldName() const { return _T("[FolderName]"); };
    const CString GetDataFeedFormFieldName() const { return _T("[DataFeedForm]"); };
    const CString GetDataFeedProcFieldName() const { return _T("[DataFeedProc]"); };
    const CString GetStartDateFieldName() const { return _T("[StartDate]"); };
    const CString GetEndDateFieldName() const { return _T("[EndDate]"); };
    const CString GetInitiatorFieldName() const { return _T("[Initiator]"); };

    long    GetProcessID() const { return m_ProcessID; };
    void    SetProcessID( long value ) { m_ProcessID = value; };

    CString    GetName() const { return m_Name; };
    void    SetName( CString value ) { m_Name = value; };

    CString    GetFilename() const { return m_Filename; };
    void    SetFilename( CString value ) { m_Filename = value; };

    CString    GetFolderName() const { return m_FolderName; };
    void    SetFolderName( CString value ) { m_FolderName = value; };

    CString    GetDataFeedForm() const { return m_DataFeedForm; };
    void    SetDataFeedForm( CString value ) { m_DataFeedForm = value; };

    CString    GetDataFeedProc() const { return m_DataFeedProc; };
    void    SetDataFeedProc( CString value ) { m_DataFeedProc = value; };

    COleDateTime    GetStartDate() const { return m_StartDate; };
    void    SetStartDate( COleDateTime value ) { m_StartDate = value; };

    COleDateTime    GetEndDate() const { return m_EndDate; };
    void    SetEndDate( COleDateTime value ) { m_EndDate = value; };

    CString    GetInitiator() const { return m_Initiator; };
    void    SetInitiator( CString value ) { m_Initiator = value; };

private:
// Field/Param Data
    //{{AFX_FIELD(ZDHistoryProcessRecordsetVersion99, CDaoRecordset)
    long    m_ProcessID;
    CString    m_Name;
    CString    m_Filename;
    CString    m_FolderName;
    CString    m_DataFeedForm;
    CString    m_DataFeedProc;
    COleDateTime    m_StartDate;
    COleDateTime    m_EndDate;
    CString    m_Initiator;
    //}}AFX_FIELD

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDHistoryProcessRecordsetVersion99)
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

#endif // !defined(AFX_HistoryProcessRecordSetv99_H__293D9E35_F146_11D3_96DD_0000B45D7C6F__INCLUDED_)

