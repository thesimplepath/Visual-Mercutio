// HistoryProcessRecordSetv99.cpp : implementation of the ZDHistoryProcessRecordsetVersion99 class
//

#include "stdafx.h"
#include "HistoryProcessRecordSetv99.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryProcessRecordsetVersion99 implementation

IMPLEMENT_DYNAMIC(ZDHistoryProcessRecordsetVersion99, CDaoRecordset)

ZDHistoryProcessRecordsetVersion99::ZDHistoryProcessRecordsetVersion99(CDaoDatabase* pdb, CString DatabaseFilename)
    : CDaoRecordset(pdb), m_DatabaseFilename(DatabaseFilename)
{
    //{{AFX_FIELD_INIT(ZDHistoryProcessRecordsetVersion99)
    m_ProcessID = 0;
    m_Name = _T("");
    m_Filename = _T("");
    m_FolderName = _T("");
    m_DataFeedForm = _T("");
    m_DataFeedProc = _T("");
    m_StartDate = (DATE)0;
    m_EndDate = (DATE)0;
    m_Initiator = _T("");
    m_nFields = 9;
    //}}AFX_FIELD_INIT
    m_nDefaultType = dbOpenDynaset;
}

CString ZDHistoryProcessRecordsetVersion99::GetDefaultDBName()
{
    return _T(m_DatabaseFilename);
}


CString ZDHistoryProcessRecordsetVersion99::GetDefaultSQL()
{
    return _T(HistoryProcessTableName);
}

void ZDHistoryProcessRecordsetVersion99::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(ZDHistoryProcessRecordsetVersion99)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long(pFX, _T("[ProcessID]"), m_ProcessID);
    DFX_Text(pFX, _T("[Name]"), m_Name);
    DFX_Text(pFX, _T("[Filename]"), m_Filename);
    DFX_Text(pFX, _T("[FolderName]"), m_FolderName);
    DFX_Text(pFX, _T("[DataFeedForm]"), m_DataFeedForm);
    DFX_Text(pFX, _T("[DataFeedProc]"), m_DataFeedProc);
    DFX_DateTime(pFX, _T("[StartDate]"), m_StartDate);
    DFX_DateTime(pFX, _T("[EndDate]"), m_EndDate);
    DFX_Text(pFX, _T("[Initiator]"), m_Initiator);
    //}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryProcessRecordsetVersion99 diagnostics

#ifdef _DEBUG
void ZDHistoryProcessRecordsetVersion99::AssertValid() const
{
    CDaoRecordset::AssertValid();
}

void ZDHistoryProcessRecordsetVersion99::Dump(CDumpContext& dc) const
{
    CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
