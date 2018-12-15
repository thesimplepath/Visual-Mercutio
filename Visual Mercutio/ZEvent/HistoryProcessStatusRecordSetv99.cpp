// HistoryProcessStatusRecordSetv99.cpp : implementation of the ZDHistoryProcessStatusRecordsetVersion99 class
//

#include "stdafx.h"
#include "HistoryProcessStatusRecordSetv99.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryProcessStatusRecordsetVersion99 implementation

IMPLEMENT_DYNAMIC(ZDHistoryProcessStatusRecordsetVersion99, CDaoRecordset)

ZDHistoryProcessStatusRecordsetVersion99::ZDHistoryProcessStatusRecordsetVersion99(CDaoDatabase* pdb, CString DatabaseFilename)
    : CDaoRecordset(pdb), m_DatabaseFilename(DatabaseFilename)
{
    //{{AFX_FIELD_INIT(ZDHistoryProcessStatusRecordsetVersion99)
    m_ProcessStatusID = 0;
    m_ProcessID = 0;
    m_Date = (DATE)0;
    m_Status = _T("");
    m_CurrentActivity = 0;
    m_nFields = 5;
    //}}AFX_FIELD_INIT
    m_nDefaultType = dbOpenDynaset;
}

CString ZDHistoryProcessStatusRecordsetVersion99::GetDefaultDBName()
{
    return _T(m_DatabaseFilename);
}


CString ZDHistoryProcessStatusRecordsetVersion99::GetDefaultSQL()
{
    return _T(HistoryProcessStatusTableName);
}

void ZDHistoryProcessStatusRecordsetVersion99::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(ZDHistoryProcessStatusRecordsetVersion99)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long(pFX, _T("[ProcessStatusID]"), m_ProcessStatusID);
    DFX_DateTime(pFX, _T("[Date]"), m_Date);
    DFX_Long(pFX, _T("[ProcessID]"), m_ProcessID);
    DFX_Text(pFX, _T("[Status]"), m_Status);
    DFX_Long(pFX, _T("[CurrentActivity]"), m_CurrentActivity);
    //}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryProcessStatusRecordsetVersion99 diagnostics

#ifdef _DEBUG
void ZDHistoryProcessStatusRecordsetVersion99::AssertValid() const
{
    CDaoRecordset::AssertValid();
}

void ZDHistoryProcessStatusRecordsetVersion99::Dump(CDumpContext& dc) const
{
    CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
