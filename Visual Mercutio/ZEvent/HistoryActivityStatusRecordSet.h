// HistoryActivityStatusRecordSet.h : interface of the ZDHistoryActivityStatusRecordset class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HistoryActivityStatusRecordSet_H__293D9E4D_F146_11D3_96DD_0000B45D7C6F__INCLUDED_)
#define AFX_HistoryActivityStatusRecordSet_H__293D9E4D_F146_11D3_96DD_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ZDHistoryActivityStatusRecordset : public CDaoRecordset
{
public:
	ZDHistoryActivityStatusRecordset(CDaoDatabase* pDatabase = NULL, CString DatabaseFilename = "");
	DECLARE_DYNAMIC(ZDHistoryActivityStatusRecordset)

	const CString GetActivityStatusIDFieldName() const { return _T("[ActivityStatusID]"); };
	const CString GetActivityIDFieldName() const { return _T("[ActivityID]"); };
	const CString GetProcessIDFieldName() const { return _T("[ProcessID]"); };
	const CString GetFolderNameFieldName() const { return _T("[FolderName]"); };
	const CString GetNameFieldName() const { return _T("[Name]"); };
	const CString GetDateFieldName() const { return _T("[Date]"); };
	const CString GetStartDateFieldName() const { return _T("[StartDate]"); };
	const CString GetEndDateFieldName() const { return _T("[EndDate]"); };
	const CString GetStatusFieldName() const { return _T("[Status]"); };

	long	GetActivityStatusID() const { return m_ActivityStatusID; };
	void	SetActivityStatusID( long value ) { m_ActivityStatusID = value; };

	long	GetActivityID() const { return m_ActivityID; };
	void	SetActivityID( long value ) { m_ActivityID = value; };

	long	GetProcessID() const { return m_ProcessID; };
	void	SetProcessID( long value ) { m_ProcessID = value; };

	CString	GetFolderName() const { return m_FolderName; };
	void	SetFolderName( CString value ) { m_FolderName = value; };

	CString	GetName() const { return m_Name; };
	void	SetName( CString value ) { m_Name = value; };

	COleDateTime	GetDate() const { return m_Date; };
	void	SetDate( COleDateTime value ) { m_Date = value; };

	COleDateTime	GetStartDate() const { return m_StartDate; };
	void	SetStartDate( COleDateTime value ) { m_StartDate = value; };

	COleDateTime	GetEndDate() const { return m_EndDate; };
	void	SetEndDate( COleDateTime value ) { m_EndDate = value; };

	CString	GetStatus() const { return m_Status; };
	void	SetStatus( CString value ) { m_Status = value; };

private:
// Field/Param Data
	//{{AFX_FIELD(ZDHistoryActivityStatusRecordset, CDaoRecordset)
	long	m_ActivityStatusID;
	long	m_ActivityID;
	long	m_ProcessID;
	CString m_FolderName;
	CString	m_Name;
	COleDateTime	m_Date;
	COleDateTime	m_StartDate;
	COleDateTime	m_EndDate;
	CString m_Status;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZDHistoryActivityStatusRecordset)
	public:
	virtual CString GetDefaultDBName();		// REVIEW:  Get a comment here
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	CString		m_DatabaseFilename;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HistoryActivityStatusRecordSet_H__293D9E4D_F146_11D3_96DD_0000B45D7C6F__INCLUDED_)

