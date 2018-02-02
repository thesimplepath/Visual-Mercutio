// dbSet.cpp : implementation of the ZDHistoryProcessRecordset class
//

#include "stdafx.h"
#include "HistoryProcessRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryProcessRecordset implementation

IMPLEMENT_DYNAMIC(ZDHistoryProcessRecordset, CDaoRecordset)

ZDHistoryProcessRecordset::ZDHistoryProcessRecordset(CDaoDatabase* pdb, CString DatabaseFilename)
	: CDaoRecordset(pdb), m_DatabaseFilename(DatabaseFilename)
{
	//{{AFX_FIELD_INIT(ZDHistoryProcessRecordset)
	m_ProcessID = 0;
	m_Name = _T("");
	m_Filename = _T("");
	m_FolderName = _T("");
	m_DataFeedForm = _T("");
	m_DataFeedProc = _T("");
	m_Date = (DATE)0;
	m_StartDate = (DATE)0;
	m_EndDate = (DATE)0;
	m_InitialDays = 0;
	m_ForecastedEndDate = (DATE)0;
	m_Initiator = _T("");
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

CString ZDHistoryProcessRecordset::GetDefaultDBName()
{
	return _T(m_DatabaseFilename);
}


CString ZDHistoryProcessRecordset::GetDefaultSQL()
{
	return _T(HistoryProcessTableName);
}

void ZDHistoryProcessRecordset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(ZDHistoryProcessRecordset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ProcessID]"), m_ProcessID);
	DFX_Text(pFX, _T("[Name]"), m_Name);
	DFX_Text(pFX, _T("[Filename]"), m_Filename);
	DFX_Text(pFX, _T("[FolderName]"), m_FolderName);
	DFX_Text(pFX, _T("[DataFeedForm]"), m_DataFeedForm);
	DFX_Text(pFX, _T("[DataFeedProc]"), m_DataFeedProc);
	DFX_DateTime(pFX, _T("[Date]"), m_Date);
	DFX_DateTime(pFX, _T("[StartDate]"), m_StartDate);
	DFX_DateTime(pFX, _T("[EndDate]"), m_EndDate);
	DFX_Long(pFX, _T("[InitialDays]"), m_InitialDays);
	DFX_DateTime(pFX, _T("[ForecastedEndDate]"), m_ForecastedEndDate);
	DFX_Text(pFX, _T("[Initiator]"), m_Initiator);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryProcessRecordset diagnostics

#ifdef _DEBUG
void ZDHistoryProcessRecordset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void ZDHistoryProcessRecordset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
