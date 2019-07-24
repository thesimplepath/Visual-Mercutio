// HistoryActivityRecordSet.cpp : implementation of the ZDHistoryActivityRecordset class
//

#include "stdafx.h"
#include "HistoryActivityRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryActivityRecordset implementation

IMPLEMENT_DYNAMIC(ZDHistoryActivityRecordset, CDaoRecordset)

ZDHistoryActivityRecordset::ZDHistoryActivityRecordset(CDaoDatabase* pdb, CString DatabaseFilename)
    : CDaoRecordset(pdb), m_DatabaseFilename(DatabaseFilename)
{
    //{{AFX_FIELD_INIT(ZDHistoryActivityRecordset)
    m_ActivityID = 0;
    m_ProcessID = 0;
    m_Name = _T("");
    m_Date = (DATE)0;
    m_StartDate = (DATE)0;
    m_EndDate = (DATE)0;
    m_InitialDays = 0;
    m_ForecastedEndDate = (DATE)0;
    m_Initiator = _T("");
    m_Receiver = _T("");
    m_Status = _T("");
    m_Comment = _T("");
    m_InBackup = FALSE;
    m_nFields = 13;
    //}}AFX_FIELD_INIT
    m_nDefaultType = dbOpenDynaset;
}

CString ZDHistoryActivityRecordset::GetDefaultDBName()
{
    return _T(m_DatabaseFilename);
}


CString ZDHistoryActivityRecordset::GetDefaultSQL()
{
    return _T(g_HistoryActivityTableName);
}

void ZDHistoryActivityRecordset::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(ZDHistoryActivityRecordset)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long(pFX, _T("[ActivityID]"), m_ActivityID);
    DFX_Long(pFX, _T("[ProcessID]"), m_ProcessID);
    DFX_Text(pFX, _T("[Name]"), m_Name);
    DFX_DateTime(pFX, _T("[Date]"), m_Date);
    DFX_DateTime(pFX, _T("[StartDate]"), m_StartDate);
    DFX_DateTime(pFX, _T("[EndDate]"), m_EndDate);
    DFX_Long(pFX, _T("[InitialDays]"), m_InitialDays);
    DFX_DateTime(pFX, _T("[ForecastedEndDate]"), m_ForecastedEndDate);
    DFX_Text(pFX, _T("[Initiator]"), m_Initiator);
    DFX_Text(pFX, _T("[Receiver]"), m_Receiver);
    DFX_Text(pFX, _T("[Status]"), m_Status);
    DFX_Text(pFX, _T("[Comment]"), m_Comment);
    DFX_Bool(pFX, _T("[InBackup]"), m_InBackup);
    //}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryActivityRecordset diagnostics

#ifdef _DEBUG
void ZDHistoryActivityRecordset::AssertValid() const
{
    CDaoRecordset::AssertValid();
}

void ZDHistoryActivityRecordset::Dump(CDumpContext& dc) const
{
    CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
