// HistoryFolderStatusRecordSet.cpp : implementation of the ZDHistoryFolderStatusRecordset class
//

#include "stdafx.h"
#include "HistoryFolderStatusRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryFolderStatusRecordset implementation

IMPLEMENT_DYNAMIC(ZDHistoryFolderStatusRecordset, CDaoRecordset)

ZDHistoryFolderStatusRecordset::ZDHistoryFolderStatusRecordset(CDaoDatabase* pdb, CString DatabaseFilename)
    : CDaoRecordset(pdb), m_DatabaseFilename(DatabaseFilename)
{
    //{{AFX_FIELD_INIT(ZDHistoryFolderStatusRecordset)
    m_ActivityStatusID = 0;
    m_ActivityID = 0;
    m_ProcessID = 0;
    m_FolderName = _T("");
    m_Name = _T("");
    m_Date = (DATE)0;
    m_StartDate = (DATE)0;
    m_EndDate = (DATE)0;
    m_Status = _T("");
    m_nFields = 9;
    //}}AFX_FIELD_INIT
    m_nDefaultType = dbOpenDynaset;
}

CString ZDHistoryFolderStatusRecordset::GetDefaultDBName()
{
    return _T(m_DatabaseFilename);
}


CString ZDHistoryFolderStatusRecordset::GetDefaultSQL()
{
    return _T(g_HistoryFolderStatusTableName);
}

void ZDHistoryFolderStatusRecordset::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(ZDHistoryFolderStatusRecordset)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long(pFX, _T("[ActivityStatusID]"), m_ActivityStatusID);
    DFX_Long(pFX, _T("[ActivityID]"), m_ActivityID);
    DFX_Long(pFX, _T("[ProcessID]"), m_ProcessID);
    DFX_Text(pFX, _T("[FolderName]"), m_FolderName);
    DFX_Text(pFX, _T("[Name]"), m_Name);
    DFX_DateTime(pFX, _T("[Date]"), m_Date);
    DFX_DateTime(pFX, _T("[StartDate]"), m_StartDate);
    DFX_DateTime(pFX, _T("[EndDate]"), m_EndDate);
    DFX_Text(pFX, _T("[Status]"), m_Status);
    //}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZDHistoryFolderStatusRecordset diagnostics

#ifdef _DEBUG
void ZDHistoryFolderStatusRecordset::AssertValid() const
{
    CDaoRecordset::AssertValid();
}

void ZDHistoryFolderStatusRecordset::Dump(CDumpContext& dc) const
{
    CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
