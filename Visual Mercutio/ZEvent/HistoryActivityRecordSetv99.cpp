// HistoryActivityRecordSetv99.cpp : implementation of the ZDHistoryActivityRecordsetVersion99 class
//

#include "stdafx.h"
#include "HistoryActivityRecordSetv99.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryActivityRecordsetVersion99 implementation

IMPLEMENT_DYNAMIC(ZDHistoryActivityRecordsetVersion99, CDaoRecordset)

ZDHistoryActivityRecordsetVersion99::ZDHistoryActivityRecordsetVersion99(CDaoDatabase* pdb, CString DatabaseFilename)
    : CDaoRecordset(pdb), m_DatabaseFilename(DatabaseFilename)
{
    //{{AFX_FIELD_INIT(ZDHistoryActivityRecordsetVersion99)
    m_ActivityID = 0;
    m_ProcessID = 0;
    m_Name = _T("");
    m_StartDate = (DATE)0;
    m_EndDate = (DATE)0;
    m_Initiator = _T("");
    m_Receiver = _T("");
    m_Status = _T("");
    m_Comment = _T("");
    m_InBackup = FALSE;
    m_nFields = 10;
    //}}AFX_FIELD_INIT
    m_nDefaultType = dbOpenDynaset;
}

CString ZDHistoryActivityRecordsetVersion99::GetDefaultDBName()
{
    return _T(m_DatabaseFilename);
}


CString ZDHistoryActivityRecordsetVersion99::GetDefaultSQL()
{
    return _T(HistoryActivityTableName);
}

void ZDHistoryActivityRecordsetVersion99::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(ZDHistoryActivityRecordsetVersion99)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long(pFX, _T("[ActivityID]"), m_ActivityID);
    DFX_Long(pFX, _T("[ProcessID]"), m_ProcessID);
    DFX_Text(pFX, _T("[Name]"), m_Name);
    DFX_DateTime(pFX, _T("[StartDate]"), m_StartDate);
    DFX_DateTime(pFX, _T("[EndDate]"), m_EndDate);
    DFX_Text(pFX, _T("[Initiator]"), m_Initiator);
    DFX_Text(pFX, _T("[Receiver]"), m_Receiver);
    DFX_Text(pFX, _T("[Status]"), m_Status);
    DFX_Text(pFX, _T("[Comment]"), m_Comment);
    DFX_Bool(pFX, _T("[InBackup]"), m_InBackup);
    //}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryActivityRecordsetVersion99 diagnostics

#ifdef _DEBUG
void ZDHistoryActivityRecordsetVersion99::AssertValid() const
{
    CDaoRecordset::AssertValid();
}

void ZDHistoryActivityRecordsetVersion99::Dump(CDumpContext& dc) const
{
    CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
