// rsetact.cpp : implementation file
//
#include <StdAfx.h>

#include "RSetAct.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDActivityLogRecordSet

IMPLEMENT_DYNAMIC(ZDActivityLogRecordSet, CRecordset)

ZDActivityLogRecordSet::ZDActivityLogRecordSet(CDatabase* pdb)
    : CRecordset(pdb)
{
    //{{AFX_FIELD_INIT(ZDActivityLogRecordSet)
    m_FolderName = "";
    m_File = "";
    m_DataFile = "";
    m_Process = "";
    m_Activity = "";
    m_Status = "";
    m_Sender = "";
    m_Receiver = "";
    m_Comments = "";
    m_nFields = 11;
    //}}AFX_FIELD_INIT
}


CString ZDActivityLogRecordSet::GetDefaultConnect()
{
    return "ODBC;DSN=ADSoft Server Database;";
}

CString ZDActivityLogRecordSet::GetDefaultSQL()
{
    return "ActivityLog";
}

void ZDActivityLogRecordSet::DoFieldExchange(CFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(ZDActivityLogRecordSet)
    pFX->SetFieldType(CFieldExchange::outputColumn);
    RFX_Date(pFX, "Date", m_Date);
    RFX_Text(pFX, "FolderName", m_FolderName);
    RFX_Text(pFX, "File", m_File);
    RFX_Text(pFX, "DataFile", m_DataFile);
    RFX_Text(pFX, "Process", m_Process);
    RFX_Text(pFX, "Activity", m_Activity);
    RFX_Date(pFX, "DueDate", m_DueDate);
    RFX_Text(pFX, "Status", m_Status);
    RFX_Text(pFX, "Sender", m_Sender);
    RFX_Text(pFX, "Receiver", m_Receiver);
    RFX_Text(pFX, "Comments", m_Comments);
    //}}AFX_FIELD_MAP
}
