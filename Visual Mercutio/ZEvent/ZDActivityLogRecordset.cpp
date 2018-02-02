// ZDActivityLogRecordset.cpp : implementation file
//

#include "stdafx.h"
#include "ZDActivityLogRecordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDActivityLogRecordset

IMPLEMENT_DYNAMIC(ZDActivityLogRecordset, CDaoRecordset)

ZDActivityLogRecordset::ZDActivityLogRecordset(CDaoDatabase* pdb, CString DatabaseFilename)
	: CDaoRecordset(pdb), m_DatabaseFilename(DatabaseFilename)
{
	//{{AFX_FIELD_INIT(ZDActivityLogRecordset)
	m_Date = (DATE)0;
	m_EventType = _T("");
	m_ProcessFilename = _T("");
	m_FormDataFilename = _T("");
	m_ProcessDataFilename = _T("");
	m_FolderName = _T("");
	m_ProcessName = _T("");
	m_ProcessCreationDate = (DATE)0;
	m_ProcessDueDate = (DATE)0;
	m_ActivityType = _T("");
	m_ActivityName = _T("");
	m_ActivityCreationDate = (DATE)0;
	m_ActivityDueDate = (DATE)0;
	m_ActivityStatus = _T("");
	m_Sender = _T("");
	m_Receiver = _T("");
	m_Comments = _T("");
	m_InBackup = FALSE;
	m_nFields = 18;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString ZDActivityLogRecordset::GetDefaultDBName()
{
	return _T(m_DatabaseFilename);
}

CString ZDActivityLogRecordset::GetDefaultSQL()
{
	return _T(ActivityLogTableName);
}

void ZDActivityLogRecordset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(ZDActivityLogRecordset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_DateTime(pFX, _T("[Date]"), m_Date);
	DFX_Text(pFX, _T("[EventType]"), m_EventType);
	DFX_Text(pFX, _T("[ProcessFilename]"), m_ProcessFilename);
	DFX_Text(pFX, _T("[FormDataFilename]"), m_FormDataFilename);
	DFX_Text(pFX, _T("[ProcessDataFilename]"), m_ProcessDataFilename);
	DFX_Text(pFX, _T("[FolderName]"), m_FolderName);
	DFX_Text(pFX, _T("[ProcessName]"), m_ProcessName);
	DFX_DateTime(pFX, _T("[ProcessCreationDate]"), m_ProcessCreationDate);
	DFX_DateTime(pFX, _T("[ProcessDueDate]"), m_ProcessDueDate);
	DFX_Text(pFX, _T("[ActivityType]"), m_ActivityType);
	DFX_Text(pFX, _T("[ActivityName]"), m_ActivityName);
	DFX_DateTime(pFX, _T("[ActivityCreationDate]"), m_ActivityCreationDate);
	DFX_DateTime(pFX, _T("[ActivityDueDate]"), m_ActivityDueDate);
	DFX_Text(pFX, _T("[ActivityStatus]"), m_ActivityStatus);
	DFX_Text(pFX, _T("[Sender]"), m_Sender);
	DFX_Text(pFX, _T("[Receiver]"), m_Receiver);
	DFX_Text(pFX, _T("[Comments]"), m_Comments);
	DFX_Bool(pFX, _T("[InBackup]"), m_InBackup);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZDActivityLogRecordset diagnostics

#ifdef _DEBUG
void ZDActivityLogRecordset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void ZDActivityLogRecordset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
