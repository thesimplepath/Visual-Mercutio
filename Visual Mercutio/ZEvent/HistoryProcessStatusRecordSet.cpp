// HistoryProcessStatusRecordSet.cpp : implementation of the ZDHistoryProcessStatusRecordset class
//

#include "stdafx.h"
#include "HistoryProcessStatusRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryProcessStatusRecordset implementation

IMPLEMENT_DYNAMIC(ZDHistoryProcessStatusRecordset, CDaoRecordset)

ZDHistoryProcessStatusRecordset::ZDHistoryProcessStatusRecordset(CDaoDatabase* pdb, CString DatabaseFilename)
    : CDaoRecordset(pdb), m_DatabaseFilename(DatabaseFilename)
{
    //{{AFX_FIELD_INIT(ZDHistoryProcessStatusRecordset)
    m_ProcessStatusID = 0;
    m_ProcessID = 0;
    m_Date = (DATE)0;
    m_StartDate = (DATE)0;
    m_EndDate = (DATE)0;
    m_Status = _T("");
    m_CurrentActivity = 0;
    m_nFields = 7;
    //}}AFX_FIELD_INIT
    m_nDefaultType = dbOpenDynaset;
}

CString ZDHistoryProcessStatusRecordset::GetDefaultDBName()
{
    return _T(m_DatabaseFilename);
}


CString ZDHistoryProcessStatusRecordset::GetDefaultSQL()
{
    return _T(HistoryProcessStatusTableName);
}

void ZDHistoryProcessStatusRecordset::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(ZDHistoryProcessStatusRecordset)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long(pFX, _T("[ProcessStatusID]"), m_ProcessStatusID);
    DFX_DateTime(pFX, _T("[Date]"), m_Date);
    DFX_DateTime(pFX, _T("[StartDate]"), m_StartDate);
    DFX_DateTime(pFX, _T("[EndDate]"), m_EndDate);
    DFX_Long(pFX, _T("[ProcessID]"), m_ProcessID);
    DFX_Text(pFX, _T("[Status]"), m_Status);
    DFX_Long(pFX, _T("[CurrentActivity]"), m_CurrentActivity);
    //}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryProcessStatusRecordset diagnostics

#ifdef _DEBUG
void ZDHistoryProcessStatusRecordset::AssertValid() const
{
    CDaoRecordset::AssertValid();
}

void ZDHistoryProcessStatusRecordset::Dump(CDumpContext& dc) const
{
    CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
